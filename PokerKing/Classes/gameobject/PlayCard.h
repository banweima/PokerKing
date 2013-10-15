//
//  PlayCard.h
//  blackjack
//
//  Created by Banson Niu on 9/12/12.
//
//

#ifndef __blackjack__PlayCard__
#define __blackjack__PlayCard__

#include "cocos2d.h"

USING_NS_CC;

enum CardClass {
    HongKong_Card = 1,
    Macau_Card,
    MonteCarlo_Card,
    LasVegas_Card
};

enum CardSuit {
    Diamonds = 1,
    Spades,
    Clubs,
    Hearts
};

enum CardType {
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

class PlayCard : public CCSprite
{
private:
//    CCSpriteBatchNode *mSpriteBatchNode;
    CCNode * mSpriteBatchNode;
    
    CC_SYNTHESIZE(CCSprite*, mCardBgSprite, CardBgSprite);
    CC_SYNTHESIZE(CCSprite*, mCardFrontBgSprite, CardFrontBgSprite);
    CC_SYNTHESIZE(CCSprite*, mCardFrontSprite, CardFrontSprite);
    
    CCMenuItemSprite* shadowCard;
    
    bool mIsFlipped;
    bool mIsSelected;
    
    int winH;
public:
    PlayCard();
    ~PlayCard();
    
    static PlayCard* create(CardClass cclass, CardSuit suit, CardType type, bool flipped);
    
    static PlayCard* create(CardClass cclass, CardSuit suit, CardType type, bool flipped, bool canSelect);
    
    bool init(CardClass cclass, CardSuit suit, CardType type, bool flipped, bool canSelect);
    
    void setupPlayCard(CardClass cclass, CardSuit suit, CardType type, bool flipped);
    
    CardClass getCardClass();
    CardSuit getCardSuit();
    CardType getCardType();
    
    CC_SYNTHESIZE(CardClass, mCardClass, CardClass);
    CC_SYNTHESIZE(CardSuit, mCardSuit, CardSuit);
    CC_SYNTHESIZE(CardType, mCardType, CardType);
    CC_SYNTHESIZE(int, mCardValue, CardValue);
    
    float getCardWidth();
    float getCardHeight();
    
    bool isFlipped();
    void setFlipped(bool flipped);
    bool isConvertibleAce();
    bool isConvertedAce();
    void convertAceToLowValue();
    void convertAceToHighValue();
    void moveBelowScreen(float newX);
    void moveAboveScreen(float newX);
    void moveToPosition(float newX, float newY, float newAngle);
    void moveTo(float targetX, float targetY, float timeDelay);
    
    void flipCard();
    void flipCard(float timeDelay);
    void moveToAboveScreen(float targetX, float targetAngle, float timeDelay);
    void moveToBelowScreen(float targetX, float targetAngle, float timeDelay);
    
    void startShaking(float timeDelay, float shakeTime, float newShakeDeltaX, float newShakeDeltaY, float newShakeDeltaAngle);
    
    void setCardScale(float scale);
    void onCardClicked(CCObject * object);
    bool isSelected();
    void resetCard(CardSuit suit, CardType type);
    
private:
    const char* getSuitName(CardSuit suit);
    void flipInstantly();
    
};

#endif /* defined(__blackjack__PlayCard__) */
