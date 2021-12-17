// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Actions/Attack.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
AttackTask::AttackTask(EntityType attacker, EntityType defender, bool force)
    : m_attackerType(attacker), m_defenderType(defender), m_force(force)
{
    // Do nothing
}

TaskStatus AttackTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_attackerType, player, m_source, m_target);
    auto defenders =
        IncludeTask::GetEntities(m_defenderType, player, m_source, m_target);

    if (defenders.empty())
    {
        return TaskStatus::STOP;
    }

    const auto defender = dynamic_cast<Character*>(defenders[0]);
    if (defender == nullptr)
    {
        return TaskStatus::STOP;
    }

    for (auto& playable : playables)
    {
        const auto attacker = dynamic_cast<Character*>(playable);
        if (attacker == nullptr)
        {
            continue;
        }

        if (!m_force && attacker->CantAttack())
        {
            continue;
        }

        if (defender->card->IsUntouchable())
        {
            continue;
        }

        std::unique_ptr<EventMetaData> temp =
            std::move(player->game->currentEventData);
        Generic::Attack(attacker->player, attacker, defender, true);
        player->game->currentEventData = std::move(temp);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AttackTask::CloneImpl()
{
    return std::make_unique<AttackTask>(m_attackerType, m_defenderType,
                                        m_force);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
