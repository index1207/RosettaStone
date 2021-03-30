// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CHOICE_ENUMS_HPP
#define ROSETTASTONE_CHOICE_ENUMS_HPP

namespace RosettaStone
{
//! The type of discover.
enum class DiscoverType
{
    INVALID,
    DECK,
    BASIC_TOTEM,
    CHOOSE_ONE,
    FOUR_COST_CARD,
    SIX_COST_MINION_SUMMON,
    LEGENDARY_MINION_SUMMON,
    TAUNT_MINION,
    DEATHRATTLE_MINION,
    RUSH_MINION,
    SPELLPOWER_MINION,
    DEATHRATTLE_MINION_DIED,
    SPELL,
    SPELL_THREE_COST_OR_LESS,
    SECRET,
    DEMON,
    DRAGON,
    LACKEY,
    HEISTBARON_TOGWAGGLE,
    MADAME_LAZUL,
    SWAMPQUEEN_HAGATHA,
    TORTOLLAN_PILGRIM,
    FROM_STACK,
    SIAMAT,
    SIR_FINLEY_OF_THE_SANDS,
    VULPERA_SCOUNDREL,
    BODY_WRAPPER,
    RINLINGS_RIFLE,
};

//! The action type of choice.
enum class ChoiceAction
{
    INVALID,             //!< Invalid action.
    CHANGE_HERO_POWER,   //!< Change hero power.
    HAND,                //!< Hand.
    HAND_AND_STACK,      //!< Hand and stack.
    DECK,                //!< Deck.
    ENCHANTMENT,         //!< Enchantment.
    DRAW_FROM_DECK,      //!< Draw from deck.
    CAST_SPELL,          //!< Cast spell.
    SUMMON,              //!< Summon.
    STACK,               //!< Stack.
    ENVOY_OF_LAZUL,      //!< Envoy Of Lazul.
    SIGHTLESS_WATCHER,   //!< Sightless Watcher.
    SWAMPQUEEN_HAGATHA,  //!< Swampqueen Hagatha.
    TORTOLLAN_PILGRIM,   //!< Tortollan Pilgrim.
    SIAMAT,              //!< Siamat.
    VULPERA_SCOUNDREL,   //!< Vulpera Scoundrel.
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CHOICE_ENUMS_HPP
