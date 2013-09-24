//
//  CardDeckCard.h
//  blackjack
//
//  Created by Banson Niu on 9/17/12.
//
//

#ifndef __blackjack__CardDeckCard__
#define __blackjack__CardDeckCard__

#include "cocos2d.h"
#include "PlayCard.h"

USING_NS_CC;

class CardDeckCard : public CCObject
{
public:
    CC_SYNTHESIZE(CardSuit, mCardSuit, Suit);
    CC_SYNTHESIZE(CardType, mCardType, Type);
    CC_SYNTHESIZE(int, mCardValue, Value);
    
public:
    static CardDeckCard* create(CardSuit suit, CardType type, int value);
    
    static CardDeckCard* create(int cardIndex);
    
    bool init(CardSuit suit, CardType type, int value);
    
    void setCard(CardSuit suit, CardType type, int value);
    int getRankingValue();
    
    CCString* toString();
};

#endif /* defined(__blackjack__CardDeckCard__) */
