// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

#include <algorithm>
#include <utility>

namespace RosettaStone::PlayMode
{
Enchantment::Enchantment(Player* player, Card* card,
                         std::map<GameTag, int> tags, Entity* target, int id)
    : Playable(player, card, std::move(tags), id), m_target(target)
{
    // Do nothing
}

std::shared_ptr<Enchantment> Enchantment::GetInstance(Playable* owner,
                                                      Card* card,
                                                      Entity* target, int num1,
                                                      int num2)
{
    const int id = owner->player->game->GetNextID();

    std::map<GameTag, int> tags;
    tags[GameTag::ENTITY_ID] = id;
    tags[GameTag::CONTROLLER] = owner->player->playerID;
    tags[GameTag::ZONE] = static_cast<int>(ZoneType::SETASIDE);

    if (num1 > 0)
    {
        tags[GameTag::TAG_SCRIPT_DATA_NUM_1] = num1;

        if (num2 > 0)
        {
            tags[GameTag::TAG_SCRIPT_DATA_NUM_2] = num2;
        }
    }

    auto instance =
        std::make_shared<Enchantment>(owner->player, card, tags, target, id);

    target->appliedEnchantments.emplace_back(instance);

    if (card->gameTags[GameTag::TAG_ONE_TURN_EFFECT] == 1)
    {
        instance->m_isOneTurnActive = true;
        owner->game->oneTurnEffectEnchantments.emplace_back(instance);
    }

    instance->orderOfPlay = owner->game->GetNextOOP();

    if (!card->power.GetDeathrattleTask().empty())
    {
        dynamic_cast<Playable*>(target)->SetGameTag(GameTag::DEATHRATTLE, 1);
    }

    return instance;
}

Entity* Enchantment::GetTarget() const
{
    return m_target;
}

int Enchantment::GetScriptTag1() const
{
    return GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1);
}

int Enchantment::GetScriptTag2() const
{
    return GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2);
}

bool Enchantment::IsOneTurnActive() const
{
    return m_isOneTurnActive;
}

Card* Enchantment::GetCapturedCard() const
{
    return m_capturedCard;
}

void Enchantment::SetCapturedCard(Card* card)
{
    m_capturedCard = card;
}

void Enchantment::Remove()
{
    if (const auto deathrattleTask = card->power.GetDeathrattleTask();
        !deathrattleTask.empty() &&
        m_target->zone->GetType() == ZoneType::GRAVEYARD)
    {
        for (auto& power : card->power.GetDeathrattleTask())
        {
            std::unique_ptr<ITask> clonedPower = power->Clone();

            clonedPower->SetPlayer(m_target->player);
            clonedPower->SetSource(m_target);
            clonedPower->SetTarget(this);

            game->taskQueue.Enqueue(std::move(clonedPower));
        }
    }

    if (ongoingEffect != nullptr)
    {
        ongoingEffect->Remove();
    }

    if (activatedTrigger != nullptr)
    {
        activatedTrigger->Remove();
    }
}
}  // namespace RosettaStone::PlayMode
