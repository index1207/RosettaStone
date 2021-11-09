// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonCopyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

#include <algorithm>
#include <chrono>
#include <random>

namespace RosettaStone::PlayMode::SimpleTasks
{
SummonCopyTask::SummonCopyTask(EntityType entityType, bool randomFlag,
                               bool addToStack, SummonSide side)
    : ITask(entityType),
      m_side(side),
      m_randomFlag(randomFlag),
      m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus SummonCopyTask::Impl(Player* player)
{
    if (player->GetFieldZone()->IsFull())
    {
        return TaskStatus::STOP;
    }

    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    if (playables.empty())
    {
        return TaskStatus::STOP;
    }

    if (m_randomFlag)
    {
        const unsigned int seed =
            std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::shuffle(std::begin(playables), std::end(playables), rng);
    }

    const auto field = player->GetFieldZone();
    int space = MAX_FIELD_SIZE - field->GetCount();
    int alternateCount = 0;

    auto playablesSize = static_cast<int>(playables.size());
    space = playablesSize > space ? space : playablesSize;

    if (playables[0]->zone == nullptr ||
        playables[0]->zone->GetType() != ZoneType::PLAY)
    {
        for (int i = 0; i < space; ++i)
        {
            if (field->IsFull())
            {
                break;
            }

            const auto minion = dynamic_cast<Minion*>(
                Entity::GetFromCard(player, playables[i]->card));

            Generic::Summon(minion,
                            SummonTask::GetPosition(m_source, m_side, m_target,
                                                    alternateCount),
                            m_source);

            if (m_addToStack)
            {
                m_source->game->taskStack.playables.emplace_back(minion);
            }
        }
    }
    else
    {
        for (int i = 0; i < playablesSize; ++i)
        {
            if (field->IsFull())
            {
                break;
            }

            auto minion = dynamic_cast<Minion*>(playables[i]);

            if (minion->player != player)
            {
                minion->SetGameTag(GameTag::CONTROLLER, player->playerID);
            }

            const int zonePos = SummonTask::GetPosition(
                m_source, m_side, m_target, alternateCount);

            const auto copy = dynamic_cast<Minion*>(
                Entity::GetFromCard(player, minion->card, minion->GetGameTags(),
                                    player->GetFieldZone()));
            Generic::Summon(copy, zonePos, m_source);
            minion->CopyInternalAttributes(copy);

            if (!minion->appliedEnchantments.empty())
            {
                for (auto& enchantment : minion->appliedEnchantments)
                {
                    auto instance = Enchantment::GetInstance(
                        minion, enchantment->card, copy);

                    if (const auto value1 = enchantment->GetGameTag(
                            GameTag::TAG_SCRIPT_DATA_NUM_1);
                        value1 > 0)
                    {
                        instance->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1,
                                             value1);

                        if (const auto value2 = enchantment->GetGameTag(
                                GameTag::TAG_SCRIPT_DATA_NUM_2);
                            value2 > 0)
                        {
                            instance->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2,
                                                 value2);
                        }
                    }

                    if (enchantment->IsOneTurnActive())
                    {
                        instance->game->oneTurnEffectEnchantments.emplace_back(
                            instance);
                    }
                }
            }

            if (minion->ongoingEffect != nullptr &&
                copy->ongoingEffect == nullptr)
            {
                minion->ongoingEffect->Clone(copy);
            }

            if (m_addToStack)
            {
                if (m_side == SummonSide::TARGET)
                {
                    m_source->game->taskStack.playables.emplace_back(copy);
                }
                else
                {
                    m_source->game->taskStack.playables.emplace_back(minion);
                }
            }
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SummonCopyTask::CloneImpl()
{
    return std::make_unique<SummonCopyTask>(m_entityType, m_randomFlag,
                                            m_addToStack, m_side);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
