// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>

using namespace RosettaStone;
using namespace Battlegrounds;

TEST_CASE("[Cards] - GetAllCards")
{
    const auto cards = Cards::GetInstance().GetAllCards();

    CHECK_FALSE(cards.empty());
    CHECK_EQ(static_cast<int>(cards.size()), NUM_BATTLEGROUNDS_CARDS);
}