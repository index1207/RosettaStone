// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/PlayerAuraEffects.hpp>

#include <stdexcept>

namespace RosettaStone
{
int PlayerAuraEffects::GetValue(GameTag tag) const
{
    switch (tag)
    {
        case GameTag::TIMEOUT:
            return m_timeOut;
        case GameTag::SPELLPOWER_DOUBLE:
        case GameTag::SPELL_HEALING_DOUBLE:
            return m_spellPowerDouble;
        case GameTag::HEALING_DOES_DAMAGE:
            return m_healingDoesDamage;
        case GameTag::CAN_TARGET_MINION_BY_HERO_POWER:
            return m_canTargetMinionByHeroPower;
        case GameTag::CANT_BE_FROZEN:
            return m_cantBeFrozen;
        case GameTag::RESOURCES_USED:
            return m_resourcesUsed;
        case GameTag::EXTRA_TRIGGER_SECRET:
            return m_extraTriggerSecret;
        case GameTag::MEGA_WINDFURY:
            return m_megaWindfury;
        case GameTag::CHOOSE_BOTH:
            return m_chooseBoth;
        default:
            throw std::invalid_argument(
                "PlayerAuraEffects::GetValue() - Invalid game tag!");
    }
}

void PlayerAuraEffects::SetValue(GameTag tag, int value)
{
    switch (tag)
    {
        case GameTag::TIMEOUT:
            m_timeOut = value;
            break;
        case GameTag::SPELLPOWER_DOUBLE:
        case GameTag::SPELL_HEALING_DOUBLE:
            m_spellPowerDouble = value;
            break;
        case GameTag::HEALING_DOES_DAMAGE:
            m_healingDoesDamage = value;
            break;
        case GameTag::CAN_TARGET_MINION_BY_HERO_POWER:
            m_canTargetMinionByHeroPower = value;
            break;
        case GameTag::CANT_BE_FROZEN:
            m_cantBeFrozen = value;
            break;
        case GameTag::RESOURCES_USED:
            m_resourcesUsed = value;
            break;
        case GameTag::EXTRA_TRIGGER_SECRET:
            m_extraTriggerSecret = value;
            break;
        case GameTag::MEGA_WINDFURY:
            m_megaWindfury = value;
            break;
        case GameTag::CHOOSE_BOTH:
            m_chooseBoth = value;
            break;
        default:
            throw std::invalid_argument(
                "PlayerAuraEffects::SetValue() - Invalid game tag!");
    }
}
}  // namespace RosettaStone
