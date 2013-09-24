//
//  CardDeckCard.cpp
//  blackjack
//
//  Created by Banson Niu on 9/17/12.
//
//

#include "CardDeckCard.h"

CardDeckCard* CardDeckCard::create(CardSuit suit, CardType type, int value)
{
    CardDeckCard *cardDeckCard=new CardDeckCard();
    
	if (cardDeckCard && cardDeckCard->init(suit, type, value))
	{
		cardDeckCard->autorelease();
		return cardDeckCard;
	}
    
	CC_SAFE_DELETE(cardDeckCard);
	return NULL;
}

CardDeckCard* CardDeckCard::create(int cardIndex)
{
    int cardValue = cardIndex % 52;
    
    CardSuit suit = (CardSuit)(cardValue/13 + 1);
    CardType type = (CardType)(cardValue % 13 + 1);
    int value = cardValue % 13 + 1;
    
    CardDeckCard *cardDeckCard=new CardDeckCard();
    
	if (cardDeckCard && cardDeckCard->init(suit, type, value))
	{
		cardDeckCard->autorelease();
		return cardDeckCard;
	}
    
	CC_SAFE_DELETE(cardDeckCard);
	return NULL;
}

bool CardDeckCard::init(CardSuit suit, CardType type, int value)
{   
    bool bRet = false;
    do
    {
        setCard(suit, type, value);
        
        bRet = true;
    } while (0);
	return bRet;
}

void CardDeckCard::setCard(CardSuit suit, CardType type, int value)
{
    mCardSuit = suit;
    mCardType = type;
    mCardValue = value;
}

int CardDeckCard::getRankingValue()
{
    // Check for special types:
    if (mCardType == Ace)
        return 14;
    else if (mCardType == King)
        return 13;
    else if (mCardType == Queen)
        return 12;
    else if (mCardType == Jack)
        return 11;
    
    return this->mCardValue;
}

CCString* CardDeckCard::toString()
{
    std::string string = "";
    
    // Check on the type first:
    if (mCardType == Ace)
        string	= string + "Ace";
    else if (mCardType == Two)
        string	= string + "Two";
    else if (mCardType == Three)
        string	= string + "Three";
    else if (mCardType == Four)
        string	= string + "Four";
    else if (mCardType == Five)
        string	= string + "Five";
    else if (mCardType == Six)
        string	= string + "Six";
    else if (mCardType == Seven)
        string	= string + "Seven";
    else if (mCardType == Eight)
        string	= string + "Eight";
    else if (mCardType == Nine)
        string	= string + "Nine";
    else if (mCardType == Ten)
        string	= string + "Ten";
    else if (mCardType == Jack)
        string	= string + "Jack";
    else if (mCardType == Queen)
        string	= string + "Queen";
    else if (mCardType == King)
        string	= string + "King";
    
    // Add the "of":
    string	= string + " of ";
    
    // Check on the suit:
    if (mCardSuit == Diamonds)
        string	= string + "diamonds";
    else if (mCardSuit == Spades)
        string	= string + "spades";
    else if (mCardSuit == Clubs)
        string	= string + "clubs";
    else if (mCardSuit == Hearts)
        string	= string + "hearts";
    
    return CCString::create(string);
}