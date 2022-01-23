// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_COMPLEX_TASK_HPP
#define ROSETTASTONE_PLAYMODE_COMPLEX_TASK_HPP

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using TaskList = std::vector<std::shared_ptr<ITask>>;

//!
//! \brief ComplexTask class.
//!
//! This class lists complex tasks such as "Summon a minion from your deck.".
//!
class ComplexTask
{
 public:
    //! Returns a list of task for drawing card(s) from your deck.
    //! \param amount The amount to draw card.
    //! \param list A list of self conditions to filter card(s).
    //! \param addToStack A flag to store card to stack.
    static TaskList DrawCardFromDeck(int amount, const SelfCondList& list,
                                     bool addToStack = false)
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::DECK),
            std::make_shared<SimpleTasks::FilterStackTask>(list),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK,
                                                      amount),
            std::make_shared<SimpleTasks::DrawStackTask>(addToStack)
        };
    }

    //! Returns a list of task for summoning a minion from your deck.
    static TaskList SummonMinionFromDeck()
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::DECK),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, 1),
            std::make_shared<SimpleTasks::SummonStackTask>(true)
        };
    }

    //! Returns a list of task for summoning a \p race minion from your deck.
    //! \param race The race of minion(s) to summon.
    static TaskList SummonRaceMinionFromDeck(Race race)
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::DECK),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
                std::make_shared<SelfCondition>(SelfCondition::IsRace(race)) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, 1),
            std::make_shared<SimpleTasks::SummonStackTask>(true)
        };
    }

    //! Returns a list of task for summoning a \p cost minion from your deck.
    //! \param cost The cost of minion(s) to summon.
    static TaskList SummonCostMinionFromDeck(int cost)
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::DECK),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsMinion()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsCost(cost, RelaSign::EQ)) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, 1),
            std::make_shared<SimpleTasks::SummonStackTask>(true)
        };
    }

    //! Returns a list of task for casting a secret from your deck.
    static TaskList CastSecretFromDeck()
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::DECK),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsSecret()),
                std::make_shared<SelfCondition>(
                    SelfCondition::NotExistInSecretZone()) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, 1),
            std::make_shared<SimpleTasks::CastSpellStackTask>(true)
        };
    }

    //! Returns a list of task for equipping a weapon from your deck.
    static TaskList EquipWeaponFromDeck()
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::DECK),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsWeapon()) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, 1),
            std::make_shared<SimpleTasks::WeaponStackTask>(true)
        };
    }

    //! Returns a list of task for destroying random enemy minion(s).
    //! \param num The number of minion(s) to destroy.
    static TaskList DestroyRandomEnemyMinion(int num)
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(
                EntityType::ENEMY_MINIONS),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, num),
            std::make_shared<SimpleTasks::DestroyTask>(EntityType::STACK)
        };
    }

    //! Returns a list of task for giving buff to a random minion in hand.
    //! \param enchantmentCardID The ID of enchantment card to give buff.
    static TaskList GiveBuffToRandomMinionInHand(
        std::string_view enchantmentCardID)
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::HAND),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, 1),
            std::make_shared<SimpleTasks::AddEnchantmentTask>(enchantmentCardID,
                                                              EntityType::STACK)
        };
    }

    //! Returns a list of task for giving buff to a random minion in field.
    //! \param enchantmentCardID The ID of enchantment card to give buff.
    static TaskList GiveBuffToRandomMinionInField(
        std::string_view enchantmentCardID)
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::MINIONS),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, 1),
            std::make_shared<SimpleTasks::AddEnchantmentTask>(enchantmentCardID,
                                                              EntityType::STACK)
        };
    }

    //! Returns a list of task for activating a secret card.
    //! \param tasks A list of task of secret card.
    static TaskList ActivateSecret(TaskList tasks)
    {
        TaskList ret{ std::move(tasks) };
        ret.emplace_back(std::make_shared<SimpleTasks::SetGameTagTask>(
            EntityType::SOURCE, GameTag::REVEALED, 1));
        ret.emplace_back(std::make_shared<SimpleTasks::MoveToGraveyardTask>(
            EntityType::SOURCE));

        return ret;
    }

    //! Returns a list of task for processing the keyword 'Dormant'.
    //! \param awakenTasks A list of task to execute when the minion awakens.
    static TaskList ProcessDormant(TaskList awakenTasks)
    {
        TaskList ret;

        ret.emplace_back(std::make_shared<SimpleTasks::CustomTask>(
            []([[maybe_unused]] Player* player, Entity* source,
               [[maybe_unused]] Playable* target) {
                const int value =
                    source->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2);
                if (value <= source->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1))
                {
                    source->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2,
                                       value + 1);
                }

                if (value + 1 ==
                    source->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1))
                {
                    source->SetGameTag(GameTag::UNTOUCHABLE, 0);
                    source->SetGameTag(GameTag::EXHAUSTED, 1);
                }
            }));
        ret.emplace_back(std::make_shared<SimpleTasks::ConditionTask>(
            EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                    SelfCondition::IsAwaken()) }));
        ret.emplace_back(std::make_shared<SimpleTasks::FlagTask>(
            true, std::move(awakenTasks)));

        return ret;
    }

    //! Returns a list of task for processing the text "Repeatable this turn".
    static TaskList RepeatableThisTurn()
    {
        TaskList ret;

        ret.emplace_back(std::make_shared<SimpleTasks::CustomTask>(
            [](Player* player, Entity* source,
               [[maybe_unused]] Playable* target) {
                std::map<GameTag, int> tags;
                tags.emplace(GameTag::GHOSTLY, 1);

                Playable* playable = Entity::GetFromCard(
                    player, source->card, tags, player->GetHandZone());
                Generic::AddCardToHand(player, playable);

                player->game->UpdateAura();
                player->game->ghostlyCards.emplace_back(
                    playable->GetGameTag(GameTag::ENTITY_ID));
            }));

        return ret;
    }

    //! Returns a list of task for copying a random card(s) in your hand.
    //! \param amount The amount to copy card(s).
    //! \param list A list of self conditions to filter card(s).
    static TaskList CopyCardInHand(int amount, const SelfCondList& list)
    {
        return TaskList{ std::make_shared<SimpleTasks::IncludeTask>(
                             EntityType::HAND),
                         std::make_shared<SimpleTasks::FilterStackTask>(list),
                         std::make_shared<SimpleTasks::RandomTask>(
                             EntityType::STACK, amount),
                         std::make_shared<SimpleTasks::CopyTask>(
                             EntityType::STACK, ZoneType::HAND) };
    }
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_COMPLEX_TASK_HPP
