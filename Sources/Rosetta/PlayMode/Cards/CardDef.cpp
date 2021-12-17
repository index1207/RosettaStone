// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Cards/CardDef.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
CardDef::CardDef(Power _power) : power(std::move(_power))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::map<PlayReq, int> _playReqs)
    : power(std::move(_power)), playReqs(std::move(_playReqs))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::vector<std::string> _chooseCardIDs)
    : power(std::move(_power)), chooseCardIDs(std::move(_chooseCardIDs))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::string _corruptCardID)
    : power(std::move(_power)), corruptCardID(std::move(_corruptCardID))
{
    // Do nothing
}

CardDef::CardDef(Power _power, int _questProgressTotal, int _heroPowerDbfID)
    : power(std::move(_power)),
      questProgressTotal(_questProgressTotal),
      heroPowerDbfID(_heroPowerDbfID)
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::map<PlayReq, int> _playReqs,
                 std::vector<std::string> _chooseCardIDs)
    : power(std::move(_power)),
      playReqs(std::move(_playReqs)),
      chooseCardIDs(std::move(_chooseCardIDs))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::map<PlayReq, int> _playReqs,
                 std::string _corruptCardID)
    : power(std::move(_power)),
      playReqs(std::move(_playReqs)),
      corruptCardID(std::move(_corruptCardID))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::vector<std::string> _chooseCardIDs,
                 std::string _corruptCardID)
    : power(std::move(_power)),
      chooseCardIDs(std::move(_chooseCardIDs)),
      corruptCardID(std::move(_corruptCardID))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::map<PlayReq, int> _playReqs,
                 std::vector<std::string> _chooseCardIDs,
                 std::vector<std::string> _entourages)
    : power(std::move(_power)),
      playReqs(std::move(_playReqs)),
      chooseCardIDs(std::move(_chooseCardIDs)),
      entourages(std::move(_entourages))
{
    // Do nothing
}
}  // namespace RosettaStone::PlayMode
