//
//  CardDeck.h
//  blackjack
//
//  Created by Banson Niu on 9/17/12.
//
//

#ifndef __blackjack__CardDeck__
#define __blackjack__CardDeck__

#include "cocos2d.h"
#include "PlayCard.h"
#include "CardDeckCard.h"

USING_NS_CC;

class CardDeck : public CCObject
{
public:
    int mNumberDecks	; // We're going to use 4 decks:
    int mNumberSuitsPerDeck; // 4 suits of course:
    int mNumberCardsPerSuit; // 13 cards per suit of course:
    int mMaximumCardsInDeck; // 52 cards in a deck:
    int mNumberShuffles; // 4 shuffles:
    
    CardSuit mCardSuitArray[4];
    CardType mCardTypeArray[13];
    int mCardValueArray[13];
    
    

private:
    int mNumberOfCards;
    CC_SYNTHESIZE(CCArray*, mCards, Cards);
    
    // Set up the current card index indicating the next card that will be pulled off the deck and dealt:
    int mCurrentCardIndex;
    
    // Set the number of cards remaining:
    int mNumberRemainingCards;
    
    int mNewDeckCardIndex;
    
public:
    CardDeck();
    ~CardDeck();
    
    bool init();
    
    static CardDeck* sharedCardDeck();
    static CardDeck* sharedCardDeck(int numberDecks);
    
    static void resetCardDeck();
    
    CardDeckCard* getNextCard();
    bool needsShuffle();
    void shuffleCardDeck();
};

#endif /* defined(__blackjack__CardDeck__) */
