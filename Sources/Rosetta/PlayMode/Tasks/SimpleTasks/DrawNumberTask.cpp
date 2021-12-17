// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawNumberTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus DrawNumberTask::Impl(Player* player)
{
    std::vector<Entity*> cards;

    for (int i = 0; i < player->game->taskStack.num[0]; ++i)
    {
        Entity* card = Generic::Draw(player, nullptr);
        cards.emplace_back(card);
    }

    if (cards.empty() || cards.at(0) == nullptr)
    {
        return TaskStatus::COMPLETE;
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawNumberTask::CloneImpl()
{
    return std::make_unique<DrawNumberTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
