// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DiscoverTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

#include <utility>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
DiscoverCriteria::DiscoverCriteria(CardType _cardType, CardClass _cardClass,
                                   Race _race, Rarity _rarity)
    : cardType(_cardType), cardClass(_cardClass), race(_race), rarity(_rarity)
{
    // Do nothing
}

bool DiscoverCriteria::Evaluate(Card* card) const
{
    return (cardType == CardType::INVALID || cardType == card->GetCardType()) &&
           (race == Race::INVALID || race == card->GetRace()) &&
           (rarity == Rarity::INVALID || rarity == card->GetRarity());
}

DiscoverTask::DiscoverTask(CardType cardType, CardClass cardClass, Race race,
                           Rarity rarity, ChoiceAction choiceAction, int repeat,
                           bool keepAll)
    : m_discoverCriteria(cardType, cardClass, race, rarity),
      m_choiceAction(choiceAction),
      m_repeat(repeat),
      m_keepAll(keepAll)
{
    // Do nothing
}

DiscoverTask::DiscoverTask(const std::vector<std::string>& cardIDs,
                           ChoiceAction choiceAction, int numberOfChoices,
                           bool doShuffle)
    : m_choiceAction(choiceAction),
      m_numberOfChoices(numberOfChoices),
      m_doShuffle(doShuffle)
{
    for (auto& cardID : cardIDs)
    {
        m_cards.emplace_back(Cards::FindCardByID(cardID));
    }
}

DiscoverTask::DiscoverTask(DiscoverType discoverType, int numberOfChoices,
                           int repeat, bool doShuffle)
    : m_discoverType(discoverType),
      m_numberOfChoices(numberOfChoices),
      m_repeat(repeat),
      m_doShuffle(doShuffle)
{
    // Do nothing
}

DiscoverTask::DiscoverTask(std::vector<Card*> cards, DiscoverType discoverType,
                           CardType cardType, CardClass cardClass, Race race,
                           Rarity rarity, ChoiceAction choiceAction,
                           int numberOfChoices, bool doShuffle, int repeat,
                           bool keepAll)
    : m_cards(std::move(cards)),
      m_discoverType(discoverType),
      m_discoverCriteria(cardType, cardClass, race, rarity),
      m_choiceAction(choiceAction),
      m_numberOfChoices(numberOfChoices),
      m_repeat(repeat),
      m_doShuffle(doShuffle),
      m_keepAll(keepAll)
{
    // Do nothing
}

std::vector<Card*> DiscoverTask::GetChoices(std::vector<Card*> cardsToDiscover,
                                            int numberOfChoices, bool doShuffle)
{
    std::vector<Card*> result;

    if (numberOfChoices >= static_cast<int>(cardsToDiscover.size()))
    {
        result = cardsToDiscover;
    }
    else
    {
        result.reserve(numberOfChoices);

        if (doShuffle)
        {
            Random::shuffle(cardsToDiscover);
        }

        for (int i = 0; i < numberOfChoices; ++i)
        {
            result.emplace_back(cardsToDiscover[i]);
        }
    }

    return result;
}

TaskStatus DiscoverTask::Impl(Player* player)
{
    std::vector<Card*> result;
    std::vector<Card*> cardsToDiscover;

    if (!m_cards.empty())
    {
        result = GetChoices(m_cards, m_numberOfChoices, m_doShuffle);
    }
    else if (m_discoverType != DiscoverType::INVALID)
    {
        cardsToDiscover =
            Discover(player->game, player, m_discoverType, m_choiceAction);
        result = GetChoices(cardsToDiscover, m_numberOfChoices, m_doShuffle);
    }
    else
    {
        cardsToDiscover = Discover(player->game, player, m_discoverCriteria);
        result = GetChoices(cardsToDiscover, m_numberOfChoices, m_doShuffle);
    }

    if (result.empty())
    {
        return TaskStatus::STOP;
    }

    if (m_keepAll)
    {
        for (std::size_t i = 0;
             i < result.size() && !player->GetHandZone()->IsFull(); ++i)
        {
            const auto entity = Entity::GetFromCard(
                player, result[i], std::nullopt, player->GetHandZone());
            Generic::AddCardToHand(player, entity);
        }
    }

    Generic::CreateChoiceCards(player, m_source, ChoiceType::GENERAL,
                               m_choiceAction, result);

    if (m_repeat > 1)
    {
        Choice* currentChoice = player->choice;

        for (int i = 1; i < m_repeat; ++i)
        {
            auto choice = new Choice(player, cardsToDiscover);
            choice->choiceType = ChoiceType::GENERAL;
            choice->choiceAction = m_choiceAction;
            choice->source = m_source;
            choice->depth = i + 1;

            currentChoice->nextChoice = choice;
            currentChoice = choice;
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DiscoverTask::CloneImpl()
{
    return std::make_unique<DiscoverTask>(
        m_cards, m_discoverType, m_discoverCriteria.cardType,
        m_discoverCriteria.cardClass, m_discoverCriteria.race,
        m_discoverCriteria.rarity, m_choiceAction, m_numberOfChoices,
        m_doShuffle, m_repeat, m_keepAll);
}

std::vector<Card*> DiscoverTask::Discover(Game* game, Player* player,
                                          DiscoverType discoverType,
                                          ChoiceAction& choiceAction) const
{
    std::vector<Card*> allCards =
        Cards::GetDiscoverCards(player->baseClass, game->GetFormatType());

    std::vector<Card*> cards;
    choiceAction = ChoiceAction::INVALID;

    switch (discoverType)
    {
        case DiscoverType::INVALID:
            throw std::invalid_argument(
                "DiscoverTask::Discover() - Invalid discover type");
        case DiscoverType::BASIC_TOTEM:
            choiceAction = ChoiceAction::SUMMON;
            cards = { Cards::FindCardByID("AT_132_SHAMANa"),
                      Cards::FindCardByID("AT_132_SHAMANb"),
                      Cards::FindCardByID("AT_132_SHAMANc"),
                      Cards::FindCardByID("AT_132_SHAMANd") };
            break;
        case DiscoverType::CHOOSE_ONE:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->HasGameTag(GameTag::CHOOSE_ONE))
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::FOUR_COST_CARD:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCost() == 4)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SIX_COST_MINION_SUMMON:
            choiceAction = ChoiceAction::SUMMON;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->GetCost() == 6)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::LEGENDARY_MINION_SUMMON:
            choiceAction = ChoiceAction::SUMMON;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->GetRarity() == Rarity::LEGENDARY)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::TAUNT_MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->HasGameTag(GameTag::TAUNT) == 1)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DEATHRATTLE_MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->HasGameTag(GameTag::DEATHRATTLE) == 1)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::RUSH_MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->HasGameTag(GameTag::RUSH) == 1)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SPELLPOWER_MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->HasGameTag(GameTag::SPELLPOWER) == 1)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DEATHRATTLE_MINION_DIED:
            choiceAction = ChoiceAction::HAND_AND_STACK;
            for (auto& playable : player->GetGraveyardZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::MINION &&
                    playable->HasDeathrattle() && playable->isDestroyed)
                {
                    cards.emplace_back(playable->card);
                }
            }
            break;
        case DiscoverType::SPELL:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SPELL_THREE_COST_OR_LESS:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL &&
                    card->GetCost() <= 3)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SECRET:
            choiceAction = ChoiceAction::CAST_SPELL;
            for (auto& card : allCards)
            {
                if (card->IsSecret())
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DEMON:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetRace() == Race::DEMON)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DRAGON:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetRace() == Race::DRAGON)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::LACKEY:
            choiceAction = ChoiceAction::HAND;
            for (const auto& card : Cards::GetAllCards())
            {
                if (card->IsLackey())
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::HEISTBARON_TOGWAGGLE:
            choiceAction = ChoiceAction::HAND;
            cards = { Cards::FindCardByID("LOOT_998h"),
                      Cards::FindCardByID("LOOT_998j"),
                      Cards::FindCardByID("LOOT_998l"),
                      Cards::FindCardByID("LOOT_998k") };
            break;
        case DiscoverType::MADAME_LAZUL:
            choiceAction = ChoiceAction::HAND;
            for (auto& playable : player->opponent->GetHandZone()->GetAll())
            {
                cards.emplace_back(playable->card);
            }
            break;
        case DiscoverType::SWAMPQUEEN_HAGATHA:
            choiceAction = ChoiceAction::SWAMPQUEEN_HAGATHA;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL &&
                    card->GetCardClass() == CardClass::SHAMAN)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::TORTOLLAN_PILGRIM:
        {
            choiceAction = ChoiceAction::TORTOLLAN_PILGRIM;

            std::vector<int> list;
            for (auto& playable : player->GetDeckZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::SPELL)
                {
                    list.emplace_back(playable->card->dbfID);
                }
            }

            std::sort(list.begin(), list.end());
            const auto last = std::unique(list.begin(), list.end());
            list.erase(last, list.end());
            Random::shuffle(list.begin(), list.end());

            for (auto& dbfID : list)
            {
                cards.emplace_back(Cards::FindCardByDbfID(dbfID));
            }

            break;
        }
        case DiscoverType::FROM_STACK:
        {
            choiceAction = ChoiceAction::STACK;
            for (auto& playable : game->taskStack.playables)
            {
                cards.emplace_back(playable->card);
            }
            break;
        }
        case DiscoverType::SIAMAT:
            choiceAction = ChoiceAction::SIAMAT;
            cards = { Cards::FindCardByID("ULD_178a2"),
                      Cards::FindCardByID("ULD_178a"),
                      Cards::FindCardByID("ULD_178a3"),
                      Cards::FindCardByID("ULD_178a4") };
            break;
        case DiscoverType::SIR_FINLEY_OF_THE_SANDS:
            choiceAction = ChoiceAction::CHANGE_HERO_POWER;
            cards = {
                Cards::FindCardByID("HERO_01bp2"),
                Cards::FindCardByID("HERO_02bp2"),
                Cards::FindCardByID("HERO_03bp2"),
                Cards::FindCardByID("HERO_04bp2"),
                Cards::FindCardByID("HERO_05bp2"),
                Cards::FindCardByID("HERO_06bp2"),
                Cards::FindCardByID("HERO_07bp2"),
                Cards::FindCardByID("HERO_08bp2"),
                Cards::FindCardByID("HERO_09bp2"),
                Cards::FindCardByID("HERO_10bp2"),
            };
            break;
        case DiscoverType::VULPERA_SCOUNDREL:
            choiceAction = ChoiceAction::VULPERA_SCOUNDREL;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL)
                {
                    cards.emplace_back(card);
                }
            }
            Random::shuffle(cards.begin(), cards.end());
            cards.resize(3);
            cards.emplace_back(Cards::FindCardByID("ULD_209t"));
            break;
        case DiscoverType::BODY_WRAPPER:
            choiceAction = ChoiceAction::DECK;
            for (auto& playable : player->GetGraveyardZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::MINION &&
                    playable->isDestroyed)
                {
                    cards.emplace_back(playable->card);
                }
            }
            break;
        case DiscoverType::RINLINGS_RIFLE:
            choiceAction = ChoiceAction::CAST_SPELL;
            for (auto& card : allCards)
            {
                if (card->IsSecret())
                {
                    cards.emplace_back(card);
                }
            }
            break;
    }

    return cards;
}

std::vector<Card*> DiscoverTask::Discover(Game* game, Player* player,
                                          DiscoverCriteria criteria) const
{
    const FormatType format = game->GetFormatType();
    std::vector<Card*> cards;

    if (criteria.cardClass == CardClass::INVALID ||
        criteria.cardClass == CardClass::PLAYER_CLASS ||
        criteria.cardClass == CardClass::ANOTHER_CLASS)
    {
        auto allCards = (format == FormatType::STANDARD)
                            ? Cards::GetAllStandardCards()
                            : Cards::GetAllWildCards();

        for (auto& card : allCards)
        {
            if (!criteria.Evaluate(card))
            {
                continue;
            }

            if (criteria.cardClass == CardClass::INVALID)
            {
                cards.emplace_back(card);
            }
            else if (criteria.cardClass == CardClass::PLAYER_CLASS)
            {
                if (card->GetCardClass() ==
                        player->GetHero()->card->GetCardClass() &&
                    card->GetCardClass() != CardClass::NEUTRAL)
                {
                    cards.emplace_back(card);
                }
            }
            else
            {
                if (card->GetCardClass() !=
                        player->GetHero()->card->GetCardClass() &&
                    card->GetCardClass() != CardClass::NEUTRAL)
                {
                    cards.emplace_back(card);
                }
            }
        }
    }
    else
    {
        auto allCards = (format == FormatType::STANDARD)
                            ? Cards::GetStandardCards(criteria.cardClass)
                            : Cards::GetWildCards(criteria.cardClass);

        for (auto& card : allCards)
        {
            if (!criteria.Evaluate(card))
            {
                continue;
            }

            if (card->GetCardClass() == criteria.cardClass)
            {
                cards.emplace_back(card);
            }
        }
    }

    return cards;
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
