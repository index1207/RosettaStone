// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <stdexcept>
#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
IncludeTask::IncludeTask(EntityType entityType,
                         std::vector<EntityType> excludeTypes, bool addFlag)
    : ITask(entityType),
      m_excludeTypes(std::move(excludeTypes)),
      m_addFlag(addFlag)
{
    // Do nothing
}

std::vector<Playable*> IncludeTask::GetEntities(EntityType entityType,
                                                Player* player, Entity* source,
                                                Entity* target)
{
    std::vector<Playable*> entities;

    switch (entityType)
    {
        case EntityType::SOURCE:
            if (source != nullptr)
            {
                entities.emplace_back(dynamic_cast<Playable*>(source));
            }
            break;
        case EntityType::TARGET:
            if (target != nullptr)
            {
                entities.emplace_back(dynamic_cast<Playable*>(target));
            }
            break;
        case EntityType::ALL:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->GetHero());
            for (auto& minion : player->opponent->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::ALL_NOSOURCE:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->GetHero());
            for (auto& minion : player->opponent->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::FRIENDS:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->GetHero());
            break;
        case EntityType::ENEMIES:
            for (auto& minion : player->opponent->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::ENEMIES_NOTARGET:
            if (target == player->opponent->GetHero())
            {
                for (auto& minion : player->opponent->GetFieldZone()->GetAll())
                {
                    entities.emplace_back(minion);
                }
            }
            else
            {
                for (auto& minion : player->opponent->GetFieldZone()->GetAll())
                {
                    if (target == minion)
                    {
                        continue;
                    }

                    entities.emplace_back(minion);
                }

                entities.emplace_back(player->opponent->GetHero());
            }
            break;
        case EntityType::HERO:
            entities.emplace_back(player->GetHero());
            break;
        case EntityType::ENEMY_HERO:
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::HEROES:
            entities.emplace_back(player->GetHero());
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::HERO_POWER:
            entities.emplace_back(player->GetHero()->heroPower);
            break;
        case EntityType::WEAPON:
            if (player->GetHero()->HasWeapon())
            {
                entities.emplace_back(&player->GetWeapon());
            }
            break;
        case EntityType::ENEMY_WEAPON:
            if (player->opponent->GetHero()->HasWeapon())
            {
                entities.emplace_back(&player->opponent->GetWeapon());
            }
            break;
        case EntityType::HAND:
            for (auto& card : player->GetHandZone()->GetAll())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::HAND_SPELL:
            for (auto& card : player->GetHandZone()->GetAll())
            {
                if (card->card->GetCardType() == CardType::SPELL)
                {
                    entities.emplace_back(card);
                }
            }
            break;
        case EntityType::ENEMY_HAND:
            for (auto& card : player->opponent->GetHandZone()->GetAll())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::DECK:
            for (auto& card : player->GetDeckZone()->GetAll())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::ENEMY_DECK:
            for (auto& card : player->opponent->GetDeckZone()->GetAll())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::ALL_MINIONS:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            for (auto& minion : player->opponent->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::ALL_MINIONS_NOSOURCE:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            for (auto& minion : player->opponent->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::ALL_MINIONS_NOEVENTSOURCE:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                if (player->game->currentEventData->eventSource == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            for (auto& minion : player->opponent->GetFieldZone()->GetAll())
            {
                if (player->game->currentEventData->eventSource == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS_NOSOURCE:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS_NOEVENTSOURCE:
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                if (player->game->currentEventData->eventSource == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS_HAND:
            for (auto& card : player->GetHandZone()->GetAll())
            {
                if (card->card->GetCardType() == CardType::MINION)
                {
                    entities.emplace_back(card);
                }
            }
            break;
        case EntityType::MINIONS_HAND_DECK_FIELD:
            for (auto& card : player->GetHandZone()->GetAll())
            {
                if (card->card->GetCardType() == CardType::MINION)
                {
                    entities.emplace_back(card);
                }
            }
            for (auto& card : player->GetDeckZone()->GetAll())
            {
                if (card->card->GetCardType() == CardType::MINION)
                {
                    entities.emplace_back(card);
                }
            }
            for (auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::ENEMY_MINIONS:
            for (auto& minion : player->opponent->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::ENEMY_SECRETS:
            for (auto& secret : player->opponent->GetSecretZone()->GetAll())
            {
                entities.emplace_back(secret);
            }
            break;
        case EntityType::GRAVEYARD:
            for (auto& entity : player->GetGraveyardZone()->GetAll())
            {
                entities.emplace_back(entity);
            }
            break;
        case EntityType::STACK:
            entities = player->game->taskStack.playables;
            break;
        case EntityType::STACK_NUM0:
            entities.emplace_back(
                player->game->entityList[player->game->taskStack.num[0]]);
            break;
        case EntityType::STACK_NUM1:
            entities.emplace_back(
                player->game->entityList[player->game->taskStack.num[1]]);
            break;
        case EntityType::EVENT_SOURCE:
            if (auto eventData = player->game->currentEventData.get();
                eventData)
            {
                entities.emplace_back(eventData->eventSource);
            }
            break;
        case EntityType::EVENT_TARGET:
            if (auto eventData = player->game->currentEventData.get();
                eventData)
            {
                entities.emplace_back(eventData->eventTarget);
            }
            break;
        default:
            throw std::invalid_argument(
                "IncludeTask::GetEntities() - Invalid entity type");
    }

    return entities;
}

TaskStatus IncludeTask::Impl(Player* player)
{
    const auto entities = GetEntities(m_entityType, player, m_source, m_target);

    if (!m_excludeTypes.empty())
    {
        std::vector<Playable*> exceptEntities;
        for (auto& excludeType : m_excludeTypes)
        {
            auto temp = GetEntities(excludeType, player, m_source, m_target);
            exceptEntities.insert(exceptEntities.end(), temp.begin(),
                                  temp.end());
        }

        std::vector<Playable*> result = entities;
        EraseIf(result, [&](Entity* entity) {
            for (auto& excludeEntity : exceptEntities)
            {
                if (entity == excludeEntity)
                {
                    return true;
                }
            }

            return false;
        });

        if (m_addFlag)
        {
            player->game->taskStack.AddPlayables(result);
        }
        else
        {
            player->game->taskStack.playables = result;
        }
    }
    else if (m_addFlag)
    {
        player->game->taskStack.AddPlayables(entities);
    }
    else
    {
        player->game->taskStack.playables = entities;
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> IncludeTask::CloneImpl()
{
    return std::make_unique<IncludeTask>(m_entityType, m_excludeTypes,
                                         m_addFlag);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
