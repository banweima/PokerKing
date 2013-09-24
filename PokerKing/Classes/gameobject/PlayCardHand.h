//
//  PlayCardHand.h
//  blackjack
//
//  Created by Banson Niu on 9/17/12.
//
//

#ifndef __blackjack__PlayCardHandLayer__
#define __blackjack__PlayCardHandLayer__

#include "cocos2d.h"
#include "PlayCard.h"
#include "Constants.h"
#include "PlayCard.h"
#include "CardDeck.h"
#include "GameInfo.h"
#include "CardDeckCard.h"

USING_NS_CC;

enum PokerHand {
    PokerHand_NA = 0,
    Mass,
    AK,
    OnePair,
    TwoPair,
    ThreeOfOneKind,
    Straight,
    Flush,
    FullHouse,
    FourOfOneKind,
    StraightFlush,
    RoyalStraightFlush
};

class PlayCardHand : public CCLayer
{
private:
    CC_SYNTHESIZE(CCArray*, mCardArray, CardArray);

    CCArray* mPreparedCards;
    
    CC_SYNTHESIZE(bool, mIsDealerHand, IsDealerHand);
    
    CC_SYNTHESIZE(float, mCardScale, CardScale);

    float mSwitchTargetDepth;
    
    CC_SYNTHESIZE(CCObject*, mpTarget, Target);
    CC_SYNTHESIZE(SEL_CallFunc, mpSelector, Selector);
    
    bool mIsHandBusted;
    
    bool mIsAce;
    int preparedCardIndex;
    bool mIsCardCanSelect;
    PokerHand mCurrentPokerHand;

public:
    PlayCardHand();
    ~PlayCardHand();
    static PlayCardHand* create(bool isDealer);
    bool init(bool isDealer);
    void setupPlayCardHand(bool isDealer);
    
    void switchingMotion();
    void deltaMotion();
    
    void addNextCardToHand();
    int getCardTotalNumber();
    int getCardCount();
    bool hasBlackjack();
    bool has21WithMoreThanTwoCards();
    bool canSplitCards();
    void clearHand();
    
    void startSwitchingMotion(float xDelta, float yDelta, float startDepth, float finalDepth,
                              float finalScale, float finalDarkening, float motionTime);
    void startDeltaMotion(float newDeltaX, float newDeltaY, float delayTime, float moveTime);
    void addNextCardToHand(bool keepFlipped, float timeDelay, CCObject* pTarget=NULL, SEL_CallFunc pSelector=NULL);
    void addNextCardToHandTest(bool keepFlipped, float timeDelay, CCObject* pTarget=NULL, SEL_CallFunc pSelector=NULL);
    void addCardToHand(CardSuit suit, CardType type, bool keepFlipped, float timeDelay);
    void addDealtCard(PlayCard *newCard);
    void flipCards();
    int getNumberOfCards();
    bool getDealerWouldHit();
    bool upCardIsAnAce();
    
    bool hasBusted();
    PlayCard* getCard(int cardIndex);
    PlayCard* getUpCard();
    PlayCard* getSplitCard();
    bool getSplitCardSuit();
    bool getSplitCardType();
    void popLastCard();
    void maximizeCount();
    bool got5CardsWithoutBusting();
    bool gotPerfectTwenty();
    bool gotConnectedCards();
    bool gotSameSuitCards();
    bool gotDoubleAces();
    
    PokerHand getPokerHand(bool needReorder, bool isDealer);
    
    void removeCard(int cardIndex);
    void removeLastCard();
    
    void prepareCards(CCArray* cards);
    CardDeckCard* getNextPreparedCard();
    
    void setCardCanSelect(bool canSelect);
    int getOnePairCarType();
    
private:
    void setupPlayCardHandLayer();
    void fixCardSpacing(float lastCardTimeDelay);
    void setDepth();
    void setDepth(float depth);
    void NotifyBusted(float dt);
};


#endif /* defined(__blackjack__PlayCardHandLayer__) */
