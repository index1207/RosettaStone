// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Loaders/CardLoader.hpp>

#include <fstream>

namespace RosettaStone::Battlegrounds
{
void CardLoader::Load(std::array<Card, NUM_ALL_CARDS>& cards)
{
    // Read card data from JSON file
    std::ifstream cardFile(RESOURCES_DIR "cards.json");
    nlohmann::json j;

    if (!cardFile.is_open())
    {
        throw std::runtime_error("Can't open cards.json");
    }

    cardFile >> j;

    std::size_t idx = 0;

    for (auto& cardData : j)
    {
        const int normalDbfID =
            cardData["battlegroundsNormalDbfId"].is_null()
                ? 0
                : cardData["battlegroundsNormalDbfId"].get<int>();
        const int premiumDbfID =
            cardData["battlegroundsPremiumDbfId"].is_null()
                ? 0
                : cardData["battlegroundsPremiumDbfId"].get<int>();
        const bool isBattlegroundsHero =
            !cardData["battlegroundsHero"].is_null();

        if (!isBattlegroundsHero && normalDbfID == 0 && premiumDbfID == 0)
        {
            continue;
        }

        const std::string id = cardData["id"].get<std::string>();

        // NOTE: Check invalid card type for 'Placeholder'
        // See https://hearthstone.gamepedia.com/Placeholder_Card
        if (id == "PlaceholderCard")
        {
            continue;
        }

        const CardSet cardSet =
            cardData["set"].is_null()
                ? CardSet::INVALID
                : StrToEnum<CardSet>(cardData["set"].get<std::string>());
        const int dbfID =
            cardData["dbfId"].is_null() ? 0 : cardData["dbfId"].get<int>();

        const std::string name = cardData["name"].is_null()
                                     ? ""
                                     : cardData["name"].get<std::string>();
        const std::string text = cardData["text"].is_null()
                                     ? ""
                                     : cardData["text"].get<std::string>();

        const CardType type =
            cardData["type"].is_null()
                ? CardType::INVALID
                : StrToEnum<CardType>(cardData["type"].get<std::string>());
        const Race race =
            cardData["race"].is_null()
                ? Race::INVALID
                : StrToEnum<Race>(cardData["race"].get<std::string>());

        const int techLevel = cardData["techLevel"].is_null()
                                  ? 0
                                  : cardData["techLevel"].get<int>();
        const int attack =
            cardData["attack"].is_null() ? 0 : cardData["attack"].get<int>();
        const int health =
            cardData["health"].is_null() ? 0 : cardData["health"].get<int>();

        std::map<GameTag, int> gameTags;
        for (auto& mechanic : cardData["mechanics"])
        {
            GameTag gameTag = StrToEnum<GameTag>(mechanic.get<std::string>());
            gameTags.emplace(gameTag, 1);
        }

        Card card;
        card.id = id;
        card.dbfID = dbfID;
        card.normalDbfID = normalDbfID;
        card.premiumDbfID = premiumDbfID;
        card.name = name;
        card.text = text;
        card.isCurHero = isBattlegroundsHero;

        card.gameTags = gameTags;
        card.gameTags[GameTag::CARD_SET] = static_cast<int>(cardSet);
        card.gameTags[GameTag::CARDTYPE] = static_cast<int>(type);
        card.gameTags[GameTag::CARDRACE] = static_cast<int>(race);
        card.gameTags[GameTag::TECH_LEVEL] = techLevel;
        card.gameTags[GameTag::ATK] = attack;
        card.gameTags[GameTag::HEALTH] = health;

        cards.at(idx) = card;
        ++idx;
    }

    cardFile.close();
}
}  // namespace RosettaStone::Battlegrounds
