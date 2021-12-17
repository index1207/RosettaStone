﻿// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/CardSets/YoDCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using TagValues = std::vector<TagValue>;
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using TaskList = std::vector<std::shared_ptr<ITask>>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void YoDCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // -------------------------------------------- HERO - MAGE
    // [YOD_009] The Amazing Reno - COST:10 [ATK:0/HP:30]
    // - Faction: Neutral, Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Make all minions disappear.
    //       <i>*Poof!*</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - HERO_POWER = 56075
    // --------------------------------------------------------
}

void YoDCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // -------------------------------------- HERO_POWER - MAGE
    // [YOD_009h] What Does This Do? (*) - COST:0
    // - Faction: Neutral, Set: YoD
    // --------------------------------------------------------
    // Text: <b>Passive Hero Power</b> At the start of your turn,
    //       cast a random spell.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [YOD_001] Rising Winds - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> <b>Choose One -</b>
    //       Draw a card; or Summon a 3/2 Eagle.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // - TWINSPELL_COPY = 56141
    // - TWINSPELL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("YOD_001", CardDef(power, PlayReqs{},
                                     ChooseCardIDs{ "YOD_001b", "YOD_001c" }));

    // ----------------------------------------- MINION - DRUID
    // [YOD_003] Winged Guardian - COST:7 [ATK:6/HP:8]
    // - Race: Beast, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Reborn</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - REBORN = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("YOD_003", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [YOD_040] Steel Beetle - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a spell that
    //       costs (5) or more, gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::Has5MoreCostSpellInHand()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<ArmorTask>(5) }));
    cards.emplace("YOD_040", CardDef(power));
}

void YoDCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [YOD_001b] Take Flight (*) - COST:2
    // - Faction: Neutral, Set: YoD
    // --------------------------------------------------------
    // Text: Draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("YOD_001b", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [YOD_001c] Swoop In (*) - COST:2
    // - Faction: Neutral, Set: YoD
    // --------------------------------------------------------
    // Text: Summon a 3/2 Eagle.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("YOD_001t", SummonSide::SPELL));
    cards.emplace(
        "YOD_001c",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ----------------------------------------- MINION - DRUID
    // [YOD_001t] Eagle (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: YoD
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("YOD_001t", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [YOD_001ts] Rising Winds (*) - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b>
    //       Draw a card; or Summon a 3/2 Eagle.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace(
        "YOD_001ts",
        CardDef(power, PlayReqs{}, ChooseCardIDs{ "YOD_001b", "YOD_001c" }));
}

void YoDCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - HUNTER
    // [YOD_004] Chopshop Copter - COST:3 [ATK:2/HP:4]
    // - Race: Mechanical, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: After a friendly Mech dies,
    //       add a random Mech to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MECHANICAL))
    };
    power.GetTrigger()->tasks = {
        std::make_shared<RandomMinionTask>(
            TagValues{ { GameTag::CARDRACE, static_cast<int>(Race::MECHANICAL),
                         RelaSign::EQ } }),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("YOD_004", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [YOD_005] Fresh Scent - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Give a Beast +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 56142
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("YOD_005e", EntityType::TARGET));
    cards.emplace(
        "YOD_005",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_TARGET_WITH_RACE, 20 } }));

    // ---------------------------------------- MINION - HUNTER
    // [YOD_036] Rotnest Drake - COST:5 [ATK:6/HP:5]
    // - Race: Dragon, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
                  std::make_shared<DestroyTask>(EntityType::STACK) }));
    cards.emplace("YOD_036", CardDef(power));
}

void YoDCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [YOD_005e] Fresh Scent (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("YOD_005e"));
    cards.emplace("YOD_005e", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [YOD_005ts] Fresh Scent (*) - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a Beast +2/+2.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("YOD_005e", EntityType::TARGET));
    cards.emplace(
        "YOD_005ts",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_TARGET_WITH_RACE, 20 } }));
}

void YoDCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ MINION - MAGE
    // [YOD_007] Animated Avalanche - COST:7 [ATK:7/HP:6]
    // - Race: Elemental, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental
    //       last turn, summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsPlayElementalMinionLastTurn()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SummonCopyTask>(
                  EntityType::SOURCE, false, false, SummonSide::SPELL) }));
    cards.emplace("YOD_007", CardDef(power));

    // ------------------------------------------ MINION - MAGE
    // [YOD_008] Arcane Amplifier - COST:3 [ATK:2/HP:5]
    // - Race: Elemental, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Hero Power deals 2 extra damage.
    // --------------------------------------------------------
    // GameTag:
    // - HEROPOWER_DAMAGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<Aura>(
        AuraType::HERO,
        EffectList{ std::make_shared<Effect>(GameTag::HEROPOWER_DAMAGE,
                                             EffectOperator::ADD, 2) }));
    cards.emplace("YOD_008", CardDef(power));
}

void YoDCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void YoDCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - PALADIN
    // [YOD_010] Shotbot - COST:2 [ATK:2/HP:2]
    // - Race: Mechanical, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("YOD_010", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [YOD_012] Air Raid - COST:2
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Twinspell</b>
    //       Summon two 1/1 Silver Hand Recruits with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 56144
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_101t", 2, SummonSide::SPELL, true));
    power.AddPowerTask(
        std::make_shared<SetGameTagTask>(EntityType::STACK, GameTag::TAUNT, 1));
    cards.emplace(
        "YOD_012",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // --------------------------------------- MINION - PALADIN
    // [YOD_043] Scalelord - COST:5 [ATK:5/HP:6]
    // - Race: Dragon, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your Murlocs <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::MINIONS));
    power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC)) }));
    power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::STACK, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("YOD_043", CardDef(power));
}

void YoDCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - PALADIN
    // [YOD_012ts] Air Raid (*) - COST:2
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 1/1 Silver Hand Recruits with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_101t", 2, SummonSide::SPELL, true));
    power.AddPowerTask(
        std::make_shared<SetGameTagTask>(EntityType::STACK, GameTag::TAUNT, 1));
    cards.emplace(
        "YOD_012ts",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));
}

void YoDCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - PRIEST
    // [YOD_013] Cleric of Scales - COST:1 [ATK:1/HP:1]
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       <b>Discover</b> a spell from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [YOD_014] Aeon Reaver - COST:6 [ATK:4/HP:4]
    // - Race: Dragon, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal damage to a minion equal
    //       to its Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::SOURCE, GameTag::ATK));
    power.AddPowerTask(std::make_shared<DamageNumberTask>(EntityType::TARGET));
    cards.emplace(
        "YOD_014",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------------- SPELL - PRIEST
    // [YOD_015] Dark Prophecy - COST:3
    // - Set: YoD, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Discover</b> a 2 Cost minion.
    //       Summon it and give it +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [YOD_015e] Prophecized (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------
}

void YoDCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- MINION - ROGUE
    // [YOD_016] Skyvateer - COST:2 [ATK:1/HP:3]
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b> <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("YOD_016", CardDef(power));

    // ----------------------------------------- MINION - ROGUE
    // [YOD_017] Shadow Sculptor - COST:5 [ATK:3/HP:2]
    // - Faction: Horde, Set: YoD, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Draw a card for each card
    //       you've played this turn.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [YOD_018] Waxmancy - COST:3
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Battlecry</b> minion.
    //       Reduce its Cost by (2).
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ ENCHANTMENT - ROGUE
    // [YOD_018e] Forged in Wax (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
}

void YoDCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - SHAMAN
    // [YOD_020] Explosive Evolution - COST:2
    // - Set: YoD, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Transform a minion into a random one that costs (3) more.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<TransformMinionTask>(EntityType::TARGET, 3));
    cards.emplace(
        "YOD_020",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------------- SPELL - SHAMAN
    // [YOD_041] Eye of the Storm - COST:10
    // - Set: YoD, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon three 5/6 Elementals with <b>Taunt</b>.
    //       <b>Overload:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("YOD_041t", 3, SummonSide::SPELL));
    cards.emplace(
        "YOD_041",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ---------------------------------------- WEAPON - SHAMAN
    // [YOD_042] The Fist of Ra-den - COST:4 [ATK:1/HP:0]
    // - Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a spell, summon a <b>Legendary</b>
    //       minion of that Cost. Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - SHAMAN
    // [YOD_041t] Stormblocker (*) - COST:5 [ATK:5/HP:6]
    // - Race: Elemental, Set: YoD
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("YOD_041t", CardDef(power));
}

void YoDCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - WARLOCK
    // [YOD_025] Twisted Knowledge - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> 2 Warlock cards.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DiscoverTask>(
        CardType::INVALID, CardClass::WARLOCK, Race::INVALID, Rarity::INVALID,
        ChoiceAction::STACK, 2));
    power.AddAfterChooseTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("YOD_025", CardDef(power));

    // --------------------------------------- MINION - WARLOCK
    // [YOD_026] Fiendish Servant - COST:1 [ATK:2/HP:1]
    // - Race: Demon, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give this minion's Attack
    //       to a random friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [YOD_027] Chaos Gazer - COST:3 [ATK:4/HP:3]
    // - Race: Demon, Set: YoD, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Corrupt a playable card in your
    //       opponent's hand. They have 1 turn to play it!
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [YOD_026e] Servant's Sacrifice (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [YOD_027e] Withering Away (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Discard this at the end of your turn.
    // --------------------------------------------------------
}

void YoDCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARRIOR
    // [YOD_022] Risky Skipper - COST:1 [ATK:1/HP:3]
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you play a minion, deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    power.GetTrigger()->triggerSource = TriggerSource::MINIONS_EXCEPT_SELF;
    power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_MINIONS, 1) };
    cards.emplace("YOD_022", CardDef(power));

    // ---------------------------------------- SPELL - WARRIOR
    // [YOD_023] Boom Squad - COST:1
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Lackey</b>, Mech, or Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - GEARS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [YOD_024] Bomb Wrangler - COST:3 [ATK:2/HP:3]
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, summon a 1/1 Boom Bot.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    power.GetTrigger()->triggerSource = TriggerSource::SELF;
    power.GetTrigger()->tasks = { std::make_shared<SummonTask>("GVG_110t", 1) };
    cards.emplace("YOD_024", CardDef(power));
}

void YoDCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void YoDCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_006] Escaped Manasaber - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Faction: Neutral, Set: YoD, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>Whenever this attacks,
    //       gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_028] Skydiving Instructor - COST:3 [ATK:2/HP:2]
    // - Faction: Neutral, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1 Cost minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_029] Hailbringer - COST:5 [ATK:3/HP:4]
    // - Race: Elemental, Faction: Neutral, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Ice Shards
    //       that <b>Freeze</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 2
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_030] Licensed Adventurer - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Quest</b>,
    //       add a Coin to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - QUEST = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsControllingQuest()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddCardTask>(EntityType::HAND,
                                                      "GAME_005") }));
    cards.emplace("YOD_030", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_032] Frenzied Felwing - COST:4 [ATK:3/HP:3]
    // - Race: Demon, Faction: Neutral, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: Costs (1) less for each damage dealt to
    //       your opponent this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_033] Boompistol Bully - COST:5 [ATK:5/HP:5]
    // - Faction: Neutral, Set: YoD, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Enemy <b>Battlecry</b> cards
    //       cost (5) more next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_035] Grand Lackey Erkh - COST:4 [ATK:2/HP:3]
    // - Faction: Neutral, Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a <b>Lackey</b>,
    //       add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsLackey())
    };
    power.GetTrigger()->tasks = { std::make_shared<AddLackeyTask>(1) };
    cards.emplace("YOD_035", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_038] Sky Gen'ral Kragg - COST:4 [ATK:2/HP:3]
    // - Race: Pirate, Faction: Neutral, Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b>
    //       If you've played a <b>Quest</b> this game,
    //       summon a 4/2 Parrot with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - QUEST = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [YOD_029t] Ice Shard - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Faction: Neutral, Set: YoD
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [YOD_032e] Frenzied (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Cost reduced.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [YOD_033e] Smokescreen (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Your <b>Battlecry</b> cards cost (5) more.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_038t] Sharkbait - COST:4 [ATK:4/HP:2]
    // - Race: Beast, Faction: Neutral, Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddDruid(cards);
    AddDruidNonCollect(cards);

    AddHunter(cards);
    AddHunterNonCollect(cards);

    AddMage(cards);
    AddMageNonCollect(cards);

    AddPaladin(cards);
    AddPaladinNonCollect(cards);

    AddPriest(cards);
    AddPriestNonCollect(cards);

    AddRogue(cards);
    AddRogueNonCollect(cards);

    AddShaman(cards);
    AddShamanNonCollect(cards);

    AddWarlock(cards);
    AddWarlockNonCollect(cards);

    AddWarrior(cards);
    AddWarriorNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode
