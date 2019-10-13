// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ENRAGE_EFFECT_HPP
#define ROSETTASTONE_ENRAGE_EFFECT_HPP

#include <Rosetta/Auras/Aura.hpp>

namespace RosettaStone
{
//!
//! \brief EnrageEffect class.
//!
//! Enrage is the informal name for a minion ability where the stated effect
//! becomes active only when the minion is damaged. If the minion regains
//! undamaged status, either through healing or a forced resetting of its
//! maximum Health, the Enrage effect will be canceled.
//!
class EnrageEffect : public Aura
{
 public:
    //! Constructs enrage effect with given \p type and \p effects.
    //! \param type The type of aura.
    //! \param effects A list of effect.
    EnrageEffect(AuraType type, std::vector<Effect*> effects);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of enrage effect.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Entity* owner,
                  [[maybe_unused]] bool cloning = false) override;

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    void Clone(Entity* clone) override;

 private:
    //! Constructs enrage effect with given \p prototype and \p owner.
    //! \param prototype An enrage effect for prototype.
    //! \param owner An owner of adaptive effect.
    EnrageEffect(EnrageEffect& prototype, Entity& owner);

    Entity* m_target = nullptr;
    bool m_enraged = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ENRAGE_EFFECT_HPP
