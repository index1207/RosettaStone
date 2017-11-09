/*************************************************************************
> File Name: Deck.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Deck class that stores a list of cards.
> Created Time: 2017/10/13
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Models/Deck.h>

#include <algorithm>
#include <iostream>

namespace Hearthstonepp
{
	Deck::Deck() :
		m_name("Empty"), m_class(CardClass::INVALID), m_numOfCards(0)
	{

	}

	Deck::Deck(std::string name, const CardClass playerClass) :
		m_name(std::move(name)), m_class(playerClass), m_numOfCards(0)
	{

	}

	std::string Deck::GetName() const
	{
		return m_name;
	}

	CardClass Deck::GetClass() const
	{
		return m_class;
	}

	unsigned int Deck::GetNumOfCards() const
	{
		return m_numOfCards;
	}

	size_t Deck::GetUniqueNumOfCards() const
	{
		return m_cards.size();
	}

	unsigned int Deck::GetNumCardInDeck(std::string cardID)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&cardID](const std::pair<std::string, int>& elem) { return elem.first == cardID; });

		if (isCardExistInDeck != m_cards.end())
		{
			return (*isCardExistInDeck).second;
		}

		return 0;
	}

	std::vector<Card*> Deck::GetPrimitiveDeck() const
	{
		Cards* cards = Cards::GetInstance();

		std::vector<Card*> deck;
		for (auto& pair : m_cards)
		{
			Card* card = const_cast<Card*>(cards->FindCardByID(pair.first));
			for (int i = 0; i < pair.second; ++i)
			{
				deck.push_back(card);
			}	
		}

		return deck;
	}

	std::pair<std::string, int> Deck::GetCard(size_t idx) const
	{
		return m_cards.at(idx);
	}

	void Deck::ShowCardList() const
	{
		int idx = 1;

		for (auto& cardInfo : m_cards)
		{
			const Card* card = Cards::GetInstance()->FindCardByID(cardInfo.first);
			if (card == nullptr)
			{
				continue;
			}

			std::cout << idx << ". ";
			card->ShowBriefInfo();
			std::cout << "(" << cardInfo.second << " card(s))\n";
			
			idx++;
		}

	}

	void Deck::AddCard(std::string cardID, int numCardToAdd)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&cardID](const std::pair<std::string, int>& elem) { return elem.first == cardID; });

		if (isCardExistInDeck != m_cards.end())
		{
			(*isCardExistInDeck).second += numCardToAdd;
		}
		else
		{
			m_cards.emplace_back(std::make_pair(cardID, numCardToAdd));
		}

		m_numOfCards += numCardToAdd;
	}

	void Deck::DeleteCard(std::string cardID, const int numCardToDelete)
	{
		auto isCardExistInDeck = std::find_if(m_cards.begin(), m_cards.end(),
			[&cardID](const std::pair<std::string, int>& elem) { return elem.first == cardID; });

		if (isCardExistInDeck != m_cards.end())
		{
			(*isCardExistInDeck).second -= numCardToDelete;

			if ((*isCardExistInDeck).second == 0)
			{
				m_cards.erase(isCardExistInDeck);
			}

			m_numOfCards -= numCardToDelete;
		}
	}
}