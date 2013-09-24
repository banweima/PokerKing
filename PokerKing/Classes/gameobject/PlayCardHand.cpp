//
//  PlayCardHand.cpp
//  blackjack
//
//  Created by Banson Niu on 9/17/12.
//
//

#include "PlayCardHand.h"
#include "GameInfo.h"


PlayCardHand::PlayCardHand()
: mpSelector(NULL)
,mpTarget(NULL)
,mIsAce(false)
,mIsCardCanSelect(false)
,mCardScale(1.0)
{
}

PlayCardHand::~PlayCardHand()
{
    CC_SAFE_RELEASE_NULL(mCardArray);
}

PlayCardHand* PlayCardHand::create(bool isDealer)
{
    PlayCardHand *layer=new PlayCardHand();
    
	if (layer && layer->init(isDealer))
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool PlayCardHand::init(bool isDealer)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        
//        mSpriteBatchNode = CCSpriteBatchNode::create("plist/porkerlist.png");
//        this->addChild(mSpriteBatchNode);
        this->setupPlayCardHand(isDealer);
        
        bRet = true;
    } while (0);
	return bRet;
}

void PlayCardHand::setupPlayCardHand(bool isDealer)
{
    this->mIsDealerHand = isDealer;
    this->mIsHandBusted = false;
    
    this->mCardArray = CCArray::create();
    this->mCardArray->retain();
    
    this->mPreparedCards = CCArray::create();
    this->mPreparedCards->retain();
}

void PlayCardHand::setDepth()
{
    this->setDepth(mSwitchTargetDepth);
}

void PlayCardHand::setDepth(float depth)
{   
    PlayCard* card;
    // Loop over all the cards and move them to their new positions:
    for (int cardIndex = 0; cardIndex < mCardArray->count(); ++cardIndex)
    {
        card = (PlayCard*)mCardArray->objectAtIndex(cardIndex);
        card->getParent()->reorderChild(card, depth + cardIndex*2);
    }
}

////////////////////////////////////////////////////////////////
//
// This function sets up a movement for the hand
// from one location to another and back with a new
// depth and a new scaling when done.
//

void PlayCardHand::startSwitchingMotion(
                            float xDelta,			// X delta half-way through the motion
                            float yDelta,			// Y delta half-way through the motion
                            float startDepth,		// New depth to start with
                            float finalDepth,		// New depth to set half way through the motion
                            float finalScale,		// New scaling to set by the end
                            float finalDarkening,	// New darkening amount
                            float motionTime)		// Time for the entire motion
{
    // Set the parameters:
//    this._switchXDelta			= xDelta;
//    this._switchYDelta			= yDelta;
    
//    this._switchStartDepth		= startDepth;
//    this._switchStartScale		= this._scale;
//    this._switchStartDarkening	= this._darkening;
    
    mSwitchTargetDepth		= finalDepth;
//    this._switchTargetScale		= finalScale;
//    this._switchTargetDarkening	= finalDarkening;
//    
//    this._switchStartTime		= this._currentTime;
//    this._switchEndTime			= this._switchStartTime + motionTime;
//    this._switchMotionTime		= motionTime;
//    
//    this._switchHalfWay			= false;
    
    // Set the initial depth:
    this->setDepth(startDepth);
    
    CCSize size = this->getContentSize();
    
    for (int i = 0; i < mCardArray->count(); i++) {
        PlayCard* card = (PlayCard*)mCardArray->objectAtIndex(i);
        card->runAction(CCSpawn::create(
                                  CCScaleTo::create(motionTime, finalScale),
                                  CCFadeTo::create(motionTime, 0.2),
                                  CCSequence::create(
                                                     CCDelayTime::create(motionTime/2),
                                                     CCCallFunc::create(this, callfunc_selector(PlayCardHand::setDepth)),
                                                     NULL
                                                     ),
                                  NULL));
    }
}

////////////////////////////////////////////////////////////////
//
// Set up an additional delta motion to temporarily move
// the cards in the hand, especially for splitting
//

void PlayCardHand::startDeltaMotion(float newDeltaX, float newDeltaY, float delayTime, float moveTime)
{
    this->runAction(CCSequence::create(
                                    CCDelayTime::create(delayTime),
                                    CCMoveBy::create(moveTime, ccp(newDeltaX, newDeltaY)),
                                    NULL));
}

////////////////////////////////////////////////////////////////
//
// Add the next card from the deck.
//

void PlayCardHand::addNextCardToHand(bool keepFlipped, float timeDelay, CCObject* pTarget/*=NULL*/, SEL_CallFunc pSelector/*=NULL*/)
{
    this->setTarget(pTarget);
    this->setSelector(pSelector);
    
    CardDeckCard* nextCard = NULL;
    
    // Check whether it is Standalone mode
    if(GameInfo::sharedGameInfo()->getCurrentGameType() == Texas)
    {
       // Get the next card from PrepareCards
        nextCard = getNextPreparedCard();
    }
    else
    {
        // Get the next card from the deck:
        nextCard = CardDeck::sharedCardDeck()->getNextCard();
    }
    
    
    // Add it to the hand:
    addCardToHand(nextCard->getSuit(), nextCard->getType(), keepFlipped, timeDelay);
}

void PlayCardHand::addNextCardToHandTest(bool keepFlipped, float timeDelay, CCObject* pTarget/*=NULL*/, SEL_CallFunc pSelector/*=NULL*/)
{
    this->setTarget(pTarget);
    this->setSelector(pSelector);
    
    // Get the next card from the deck:
    CardDeckCard* nextCard = CardDeck::sharedCardDeck()->getNextCard();
    
    if (mIsAce)
        nextCard->setCard(Diamonds, Ace, 11);
    else
        nextCard->setCard(Diamonds, Ten, 10);
    mIsAce = !mIsAce;
    
    // Add it to the hand:
    addCardToHand(nextCard->getSuit(), nextCard->getType(), keepFlipped, timeDelay);
}

////////////////////////////////////////////////////////////////
//
// Add a specific card alredy in a specific location:
//

void PlayCardHand::addDealtCard(PlayCard *newCard)
{
    // Get the card position:
    //log("New card X        = " + newCard.getX());
    //log("New card Y        = " + newCard.getY());
    //log("New card Angle    = " + newCard.getAngle());
    
    // Get the node position:
    //log("New card node X = " + newCard.getNodeX());
    //log("New card node Y = " + newCard.getNodeY());
    
    // Get the screen position:
//    var	screenLocation			= newCard.getScreenLocation();
    
    //log("New card screen X = " + screenLocation.getX());
    //log("New card screen Y = " + screenLocation.getY());
    
    // Create a new playing card but do not make it flipped:
    PlayCard *card = PlayCard::create((CardClass)GameInfo::sharedGameInfo()->getCurrentRoomType(), newCard->getCardSuit(), newCard->getCardType(), false, mIsCardCanSelect);
    
    // Make it visible and active so it can handle updates:
    card->setVisible(true);
    
    // Move the card to a specified screen location:
    card->moveToPosition(newCard->getPosition().x, newCard->getPosition().y, newCard->getRotation());
    
    // Add the card to the list of cards in this hand:
    mCardArray->addObject(card);
    this->addChild(card);
    
    // Reset the spacing of all the cards and stagger the time a bit between card movements:
    fixCardSpacing(0);
}

////////////////////////////////////////////////////////////////
//
// Add a card to the hand.
//
//   PlayingCard.Suit newCardSuit
//   PlayingCard.Type newCardType
//   bool             keepFlipped - True if the card is the dealer's hole card that's flipped over
//   int              newDepth
//   int              timeDelay
//
void PlayCardHand::addCardToHand(CardSuit suit, CardType type, bool keepFlipped, float timeDelay)
{
    // Create a new playing card:
    PlayCard* card = PlayCard::create((CardClass)GameInfo::sharedGameInfo()->getCurrentRoomType(), suit, type, true, mIsCardCanSelect);
    
    card->setScale(mCardScale);
    
    // Add the card to the list of cards in this hand:
    mCardArray->addObject(card);
    this->addChild(card);
        
    // See if this is the dealer's hand:
    if (mIsDealerHand == true)
    {
        // Move it below the screen:
        card->moveAboveScreen(0.0);
    }
    else
    {
        // Move it above the screen:
        card->moveBelowScreen(0.0);
    }
    
    // Reset the spacing of all the cards and stagger the time a bit between card movements:
    this->fixCardSpacing(timeDelay);
    
    // Also flip it after a while unless it's being kept flipped:
    if (keepFlipped == false)
    {
        card->flipCard(timeDelay * 2);
        
        if (this->getNumberOfCards() > 1)
            this->scheduleOnce(schedule_selector(PlayCardHand::NotifyBusted), timeDelay * 2 +FlippingTime);
    }
}

void PlayCardHand::NotifyBusted(float dt)
{
    if(mpTarget!=NULL && mpSelector!=NULL)
    {
        (mpTarget->*mpSelector)();
    }
}

////////////////////////////////////////////////////////////////
//
// This function fixes the spacing of cards.
//
void PlayCardHand::fixCardSpacing(float lastCardTimeDelay)
{
    float distanceBetweenCards	= 65.0;
    float maximumDistanceAllowed	= 90.0;
    float maximumAngleChange		= 20.0;
    
    float newCardX				= 0.0;
    float newCardY				= 0.0;
    float newCardAngle			= 0.0;
    float newCardDepth			= 0;
    
    // See if there are any cards that need to be moved over:
    if ( mCardArray->count() > 1 )
    {
        int	cardIndex = 0;
        
        // Figure out the desired width if allowed:
        float desiredWidth = distanceBetweenCards * (mCardArray->count() - 1);
        
        //log("Desired width is " + desiredWidth);
        
        // See if the desired width exceeds the maximum:
        if (desiredWidth > maximumDistanceAllowed)
        {
            // Recalibrate to use a shorter distance between cards:
            distanceBetweenCards	= maximumDistanceAllowed / (mCardArray->count() - 1);
            
            //log("Resetting distance between cards to " + distanceBetweenCards);
        }
        
        // Loop over all the cards and move them to their new positions:
        for (cardIndex = 0; cardIndex < mCardArray->count(); ++cardIndex)
        {
            // See if this is the dealer's hand:
            if (mIsDealerHand == true)
            {
                // Set the new card position:
                newCardX		= distanceBetweenCards * (cardIndex - 0.5 * (mCardArray->count() - 1));
                newCardY		= 0.0;
                newCardAngle	= 0.5 * maximumAngleChange - maximumAngleChange * cardIndex / (mCardArray->count() - 1);
                newCardDepth	= this->getZOrder() + 2 * ((mCardArray->count() - 1) - cardIndex);
            }
            else
            {
                // Set the new card position:
                newCardX		= distanceBetweenCards * (cardIndex - 0.5 * (mCardArray->count() - 1));
                newCardY		= 0.0;
                newCardAngle	= -0.5 * maximumAngleChange + maximumAngleChange * cardIndex / (mCardArray->count() - 1);
                newCardDepth	= this->getZOrder() + 2 * cardIndex;
            }
            
            float timeDelay;
            // Figure out the delay:
            if (cardIndex == (mCardArray->count() - 1))
                timeDelay	= lastCardTimeDelay;
            else
                timeDelay	= 0.0;
            
            newCardAngle = 0.0;
            
            PlayCard *playCard = (PlayCard *)mCardArray->objectAtIndex(cardIndex);
            // Move the card to its new position:
            playCard->moveTo(newCardX, newCardY, timeDelay);
            
            // Set the new card depth:
            playCard->getParent()->reorderChild(playCard, newCardDepth);
            
//            CCLog("X = " + newCardX + " Y = " + newCardY + " A = " + newCardAngle);
        }
    }
    else if ( mCardArray->count() == 1 )
    {
        PlayCard *playCard = (PlayCard *)mCardArray->objectAtIndex(0);
        // Move the only card to the middle:
        playCard->moveTo(0.0,0.0,0.0);
    }
}

////////////////////////////////////////////////////////////////
//
// This flips any cards that are flipped over.
//

void PlayCardHand::flipCards()
{
    // Loop over all the cards and add up the value:
    for (int cardIndex = 0; cardIndex < mCardArray->count(); ++cardIndex)
    {
        PlayCard *pCard = (PlayCard*)mCardArray->objectAtIndex(cardIndex);
        // If this card is flipped, flip it over:
        if (pCard->isFlipped())
        {
            // Flip it over:
            pCard->flipCard(0.1);
        }
    }
}


void PlayCardHand::removeCard(int cardIndex)
{
    if(cardIndex >= 0 || cardIndex < mCardArray->count())
    {
        mCardArray->removeObjectAtIndex(cardIndex);
        this->getChildren()->removeObjectAtIndex(cardIndex);
    }
}

void PlayCardHand::removeLastCard()
{
    mCardArray->removeLastObject();
    this->getChildren()->removeLastObject();
}

////////////////////////////////////////////////////////////////
//
// Get the number of cards in the hand.
//

int PlayCardHand::getNumberOfCards()
{
    if(mCardArray == NULL)
        return 0;
    
    return mCardArray->count();
}

////////////////////////////////////////////////////////////////
//
// Get the total current card count.
// Only use for BlackJack

int PlayCardHand::getCardCount()
{
    int	cardIndex	= 0;
    int	cardCount	= 0;
    
    bool	keepGoing	= true;
    
    PlayCard *pCard;
    
    // Keep going:
    while (keepGoing)
    {
        bool	valueChanged = false;
        
        //log("Computing card count");
        
        // Reset the card count:
        cardCount	= 0;
        
        // Loop over all the cards and add up the value:
        for (cardIndex = 0; cardIndex < mCardArray->count(); ++cardIndex)
        {
            pCard = (PlayCard*)mCardArray->objectAtIndex(cardIndex);
            //log("Adding value of card " + cardIndex + " which is " + this._cardList[cardIndex].getCardValue());
            cardCount	+= pCard->getCardValue();
        }
        
        //log("Got total count of " + cardCount);
        
        // See if the card count is over 21:
        if (cardCount > 21)
        {
            //log("Trying to see if any aces can be converted to a value of 1 from list of " + this._cardList.length + " cards");
            
            // Go through and see if there are any aces that can be changed to a value of 1 to avoid busting:
            for (cardIndex = 0; cardIndex < mCardArray->count(); ++cardIndex)
            {
                pCard = (PlayCard*)mCardArray->objectAtIndex(cardIndex);
                // See if this is an ace with a value of 11 still:
                if (pCard->isConvertibleAce() == true)
                {
                    // This now turns into an ace with a value of 1:
                    pCard->convertAceToLowValue();
                    
                    //log("Changed value of card " + cardIndex);
                    
                    // A value was changed:
                    valueChanged	= true;
                    
                    break;
                }
            }
        }
        
        // If a value was not changed, don't keep going:
        if (valueChanged == false)
        {
            keepGoing = false;
        }
    }
    
    // If the card count is more than 21 then this hand is busted:
    if (cardCount > TotalHandLimit)
    {
        mIsHandBusted = true;
    }
    else
    {
        mIsHandBusted = false;
    }
    
    return cardCount;
}

////////////////////////////////////////////////////////////////
//
// Returns true if the dealer would hit.
//

bool PlayCardHand::getDealerWouldHit()
{
    int	currentCardCount = getCardCount();
    
    // If the count is above a certain number then the dealer would not hit:
    if (currentCardCount > DealerHitLimit)
    {
        // If the dealer has more than 16 there's no need to hit:
        return false;
    }
    // If the dealer has less then he does have to hit:
    else if (currentCardCount < DealerHitLimit)
    {
        // If the dealer has less than 16 then he needs to hit:
        return true;
    }
    
    // If the dealer has exactly 16 then if there's an ace he has to hit:
    bool	foundAce = false;
    
    PlayCard *pCard;
    for (int cardIndex = 0; cardIndex < mCardArray->count(); ++cardIndex)
    {
        pCard = (PlayCard*)mCardArray->objectAtIndex(cardIndex);
        if (pCard->getCardType() == Ace && pCard->isConvertedAce() == false)
        {
            foundAce = true;
            break;
        }
    }
    
    // If an ace was found, the dealer must hit on a soft 17:
    if (foundAce == true)
    {
        return true;
    }
    
    // The dealer is exempt from hitting:
    return false;
}

////////////////////////////////////////////////////////////////
//
// Returns true if the hand is a regular natural blackjack:
//

bool PlayCardHand::hasBlackjack()
{
    //return true;//Roger test blackjack
    // First the hand must only have two hands:
    if (mCardArray->count() == 2)
    {
        PlayCard* card0 = (PlayCard*)mCardArray->objectAtIndex(0);
        PlayCard* card1 =(PlayCard*)mCardArray->objectAtIndex(1);
        // Then one card must be an ace and the other one a face card:
        if (card0->getCardType() == Ace)
        {
            // See if the other card is a face card:
            if ((card1->getCardType() == Ten)   ||
                (card1->getCardType() == Jack)  ||
                (card1->getCardType() == Queen) ||
                (card1->getCardType() == King))
            {
                // This is a blackjack:
                return true;
            }
        }
        // See if the other card was an ace:
        else if (card1->getCardType() == Ace)
        {
            // See if the other card is a face card:
            if ((card0->getCardType() == Ten)   ||
                (card0->getCardType() == Jack)  ||
                (card0->getCardType() == Queen) ||
                (card0->getCardType() == King))
            {
                // This is a blackjack:
                return true;
            }
        }
    }
    
    // No blackjack for you:
    return false;
}

////////////////////////////////////////////////////////////////
//
// Determines if the hand is 21 with more than two cards:
//

bool PlayCardHand::has21WithMoreThanTwoCards()
{
    // See if the hand has two or fewer cards:
    if (mCardArray->count() <= 2)
        return false;
    
    // See if the count is not 21:
    if (getCardCount() != 21)
        return false;
    
    // The player does have 21 with 3 or more cards:
    return true;
}

////////////////////////////////////////////////////////////////
//
// Returns true if the hand can be split:
//

bool PlayCardHand::canSplitCards()
{
    // If there are not exactly two cards,
    // the hand cannot be split:
    if (mCardArray->count() != 2)
        return false;
    
    PlayCard* card0 = (PlayCard*)mCardArray->objectAtIndex(0);
    PlayCard* card1 =(PlayCard*)mCardArray->objectAtIndex(1);
    // If the two cards are not the same type,
    // the hand cannot be split:
    if (card0->getCardType() != card1->getCardType())
    {
        //log("The cards are the same type and can be split:");
        return false;
    }
    
    // The hand can be split:
    return true;
}

////////////////////////////////////////////////////////////////
//

bool PlayCardHand::upCardIsAnAce()
{
    // If there are not exactly two cards,
    // insurance cannot be taken out:
    if (mCardArray->count() != 2)
        return false;
    
    PlayCard* card0 = (PlayCard*)mCardArray->objectAtIndex(0);
    // If the first card is not still covered,
    // insurance cannot be taken out:
    if (!card0->isFlipped())
        return false;
    
    PlayCard* card1 =(PlayCard*)mCardArray->objectAtIndex(1);
    // If the up card is not an ace,
    // insurance cannot be taken out:
    if (card1->getCardType() != Ace)
        return false;
    
    // It looks like everything is good to go for insurance:
    return true;
}

////////////////////////////////////////////////////////////////
//
// Returns true if the player has busted:
//

bool PlayCardHand::hasBusted()
{
    return mIsHandBusted;
}

////////////////////////////////////////////////////////////////
//
// Clear the hand.
//

void PlayCardHand::clearHand()
{
    CCLog("test: clearHand");
    
    PlayCard* card;
    for(int i=0; i<mCardArray->count(); i++)
    {
        card = (PlayCard*)mCardArray->objectAtIndex(i);
        card->removeFromParentAndCleanup(true);
    }
    
    if(mCardArray->count()>0)
        mCardArray->removeAllObjects();
}

////////////////////////////////////////////////////////////////
//
// Get a particular card, if it exists:
//

PlayCard* PlayCardHand::getCard(int cardIndex)
{
    // See if the card exists:
    if (cardIndex < 0)
        return false;
    else if (cardIndex >= mCardArray->count())
        return false;
    
    return (PlayCard*)mCardArray->objectAtIndex(cardIndex);
}

////////////////////////////////////////////////////////////////
//
// Returns the dealer's upcard:
//

PlayCard* PlayCardHand::getUpCard()
{
    return (PlayCard*)mCardArray->objectAtIndex(1);
}

////////////////////////////////////////////////////////////////
//
// Get the suit and type of the card that will be split:
//

PlayCard* PlayCardHand::getSplitCard()
{
    return (PlayCard*)mCardArray->objectAtIndex(1);
}

bool PlayCardHand::getSplitCardSuit()
{
    // Make sure there are cards:
    if (mCardArray->count() != 2)
    {
        //log("ERROR: could not split card");
        return false;
    }
    
    PlayCard* card = (PlayCard*)mCardArray->objectAtIndex(1);
    return card->getCardSuit();
}

bool PlayCardHand::getSplitCardType()
{
    // Make sure there are cards:
    if (mCardArray->count() != 2)
    {
        //log("ERROR: could not split card");
        return false;
    }
    
    PlayCard* card = (PlayCard*)mCardArray->objectAtIndex(1);
    return card->getCardType();
}

////////////////////////////////////////////////////////////////
//
// Pop the last card in the hand:
//

void PlayCardHand::popLastCard()
{
    PlayCard* card = (PlayCard*)mCardArray->lastObject();
    card->removeFromParentAndCleanup(true);
    
    mCardArray->removeLastObject();
}

////////////////////////////////////////////////////////////////
//
// This resets any aces that are of value 1 back to a value of 11:
//

void PlayCardHand::maximizeCount()
{
    // Go through and see if there are any aces that are 1's that need to be 11's again:
    for (int cardIndex = 0; cardIndex < mCardArray->count(); ++cardIndex)
    {
        PlayCard* card = (PlayCard*)mCardArray->objectAtIndex(cardIndex);
        // See if this is an ace with a value of 1 already:
        if (card->isConvertedAce())
        {
            // This now turns into an ace with a value of 11:
            card->convertAceToHighValue();
            
            //log("Changed value of card " + cardIndex);
        }
    }
}

////////////////////////////////////////////////////////////////
//
// Returns true if the player got at least 5 cards without busting:
//

bool PlayCardHand::got5CardsWithoutBusting()
{
//    if (this.logCardHand == true)
//        log("PlayingCardHand:     got5CardsWithoutBusting()");
    
    // This is checked after each new draw, so only check for when
    // the player has five cards, because having 6 cards and
    // busting implies that the player got 5 cards without busting
    // or he would not have been allowed to draw that 6th card:
    if ( mCardArray->count() == 5 )
    {
        CCLog("got5CardsWithoutBusting() = true");
        
        // The player obviously got 5 cards without busting:
        return true;
    }
    else if ( mCardArray->count() < 5 )
    {
        CCLog("got5CardsWithoutBusting() = false");
        
        // The player doesn't have 5 cards yet:
        return false;
    }
    else
    {
        // The player has more than 6 cards but already got credit last time
        // so he didn't get 5 cards with busting just now:
        return false;
    }
    
    // See if the player busted:
    if ( !mIsHandBusted )
    {
        CCLog("got5CardsWithoutBusting() = true");
        
        // He made it:
        return true;
    }
    
    CCLog(" got5CardsWithoutBusting() = false");
    
    // He has failed:
    return false;
}

////////////////////////////////////////////////////////////////
//
// Returns true if the player got a perfect 20 in the first two cards:
//

bool PlayCardHand::gotPerfectTwenty()
{
    CCLog("PlayingCardHand: gotPerfectTwenty()");
    
    // See if the two types add up to 20:
    if (getCardCount() == 20)
    {
        CCLog("gotPerfectTwenty() = true");
        
        return true;
    }
    
    CCLog("gotPerfectTwenty() = false");
    
    return false;
}

////////////////////////////////////////////////////////////////
//
// Returns true if the two cards are connected and in the same suit:
//

bool PlayCardHand::gotConnectedCards()
{
    CCLog("PlayingCardHand: gotConnectedCards()");
    
    PlayCard* card0 = (PlayCard*)mCardArray->objectAtIndex(0);
    PlayCard* card1 =(PlayCard*)mCardArray->objectAtIndex(1);
    // Make sure the first two cards have the same suit:
    if (card0->getCardSuit() == card1->getCardSuit())
    {
        // Now see if the two cards are only one value apart:
        if (((card0->getCardType() == Ace)   && (card1->getCardType() == Two))   ||
            ((card1->getCardType() == Ace)   && (card0->getCardType() == Two))   ||
            ((card0->getCardType() == Two)   && (card1->getCardType() == Three)) ||
            ((card1->getCardType() == Two)   && (card0->getCardType() == Three)) ||
            ((card0->getCardType() == Three) && (card1->getCardType() == Four))  ||
            ((card1->getCardType() == Three) && (card0->getCardType() == Four))  ||
            ((card0->getCardType() == Four)  && (card1->getCardType() == Five))  ||
            ((card1->getCardType() == Four)  && (card0->getCardType() == Five))  ||
            ((card0->getCardType() == Five)  && (card1->getCardType() == Six))   ||
            ((card1->getCardType() == Five)  && (card0->getCardType() == Six))   ||
            ((card0->getCardType() == Six)   && (card1->getCardType() == Seven)) ||
            ((card1->getCardType() == Six)   && (card0->getCardType() == Seven)) ||
            ((card0->getCardType() == Seven) && (card1->getCardType() == Eight)) ||
            ((card1->getCardType() == Seven) && (card0->getCardType() == Eight)) ||
            ((card0->getCardType() == Eight) && (card1->getCardType() == Nine))  ||
            ((card1->getCardType() == Eight) && (card0->getCardType() == Nine))  ||
            ((card0->getCardType() == Nine)  && (card1->getCardType() == Ten))   ||
            ((card1->getCardType() == Nine)  && (card0->getCardType() == Ten))   ||
            ((card0->getCardType() == Ten)   && (card1->getCardType() == Jack))  ||
            ((card1->getCardType() == Ten)   && (card0->getCardType() == Jack))  ||
            ((card0->getCardType() == Jack)  && (card1->getCardType() == Queen)) ||
            ((card1->getCardType() == Jack)  && (card0->getCardType() == Queen)) ||
            ((card0->getCardType() == Queen) && (card1->getCardType() == King))  ||
            ((card1->getCardType() == Queen) && (card0->getCardType() == King)))
        {
            CCLog("gotConnectedCards() = true");
            
            return true;
        }
    }
    
    CCLog("gotConnectedCards() = false");
    
    return false;
}

////////////////////////////////////////////////////////////////
//
// Detect if the two initial cards have the same suit:
//

bool PlayCardHand::gotSameSuitCards()
{
    PlayCard* card0 = (PlayCard*)mCardArray->objectAtIndex(0);
    PlayCard* card1 =(PlayCard*)mCardArray->objectAtIndex(1);
    // See if the suit of the first two cards is the same:
    if ( card0->getCardSuit() == card1->getCardSuit() )
    {
        return true;
    }
    
    return false;
}

////////////////////////////////////////////////////////////////
//
// Detect if the first two cards are both aces:
//

bool PlayCardHand::gotDoubleAces()
{
    PlayCard* card0 = (PlayCard*)mCardArray->objectAtIndex(0);
    PlayCard* card1 =(PlayCard*)mCardArray->objectAtIndex(1);
    // See if the first two cards are both aces:
    if ((card0->getCardType() == Ace) &&
        (card1->getCardType() == Ace))
    {
        return true;
    }
    
    return false;
}


////////////////////////////////////////////////////////////////
//
// Get the PokerHand for Caribbean & VideoPoker
//

PokerHand PlayCardHand::getPokerHand(bool needReorder, bool isDealer)
{
    PokerHand  pokerHand = Mass;
    
    bool isFlush            = false;
    bool isStraight         = true;
    bool hasAce             = false;
    bool isFourOfOneKind    = false;
    bool isThreeOfOneKind   = false;
    int  PairCount          = 0;
    int  straightIndex      = 0;
    
    int DiamondsCount   = 0;
    int SpadesCount     = 0;
    int ClubsCount      = 0;
    int HeartsCount     = 0;

    int AllTypeCount [] = {0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0};
    
    int typeIndex = 0;
    
    for(int i = 0; i < mCardArray->count(); i++)
    {
        switch(this->getCard(i)->getCardSuit())
        {
            case Diamonds:
                DiamondsCount ++;
                break;
            case Spades:
                SpadesCount ++;
                break;
            case Clubs:
                ClubsCount ++;
                break;
            case Hearts:
                HeartsCount ++;
                break;
                
        }
        
        typeIndex = (int)this->getCard(i)->getCardType();
        
        AllTypeCount[typeIndex] ++;
    }
    
    if(DiamondsCount == 5||
        SpadesCount == 5 ||
        ClubsCount == 5 ||
        HeartsCount == 5)
    {
        isFlush = true;
    }
    
    for(int j = 1; j <= 13; j++)
    {
        if(AllTypeCount[j] == 4)
        {
            isFourOfOneKind = true;
            isStraight = false;
            break;
        }
        
        if(AllTypeCount[j] == 3)
        {
            isThreeOfOneKind = true;
            isStraight = false;
        }
        
        if(AllTypeCount[j] == 2)
        {
            PairCount ++;
            isStraight = false;
        }
        
        if(isStraight && AllTypeCount[j] == 1)
        {
            straightIndex = j;
            
            if(j == 1)
            {
                hasAce = true;
            }
            
            for(int s = 1; s <= 4; s++)
            {
                if(AllTypeCount[j+s] != 1)
                {
                    isStraight = false;
                    break;
                }
            }
        }
        
    }
    
    if(isFlush && isStraight && straightIndex == 10)
    {
        pokerHand = RoyalStraightFlush;
    }
    else if(isFlush && isStraight)
    {
        pokerHand = StraightFlush;
    }
    else if(isFourOfOneKind)
    {
        pokerHand = FourOfOneKind;
    }
    else if(isThreeOfOneKind && PairCount == 1)
    {
        pokerHand = FullHouse;
    }
    else if(isFlush)
    {
        pokerHand = Flush;
    }
    else if(isStraight)
    {
        pokerHand = Straight;
    }
    else if(isThreeOfOneKind)
    {
        pokerHand = ThreeOfOneKind;
    }
    else if(PairCount == 2)
    {
        pokerHand = TwoPair;
    }
    else if(PairCount == 1)
    {
        pokerHand = OnePair;
    }
    else if(AllTypeCount[1] == 1 && AllTypeCount[13] == 1)
    {
        pokerHand = AK;
    }
    else
    {
        pokerHand = Mass;
    }
    
    if (needReorder) {

    
        CCPoint points [] = {this->getCard(0)->getPosition(),
                            this->getCard(1)->getPosition(),
                            this->getCard(2)->getPosition(),
                            this->getCard(3)->getPosition(),
                            this->getCard(4)->getPosition()};

        int currentCardIndex    = 0;
        int sameKindCount       = 0;
        int sameKindCountIndex  = 0;
        int aceIndex            = -1;
        bool isFirstPair        = true;
        
        //Sort the five cards
        switch (pokerHand) {
          case Mass:
          case AK:
          case Straight:
          case Flush:
          case StraightFlush:
          case RoyalStraightFlush:
            for(int k = 1; k <= 13; k++)
            {
                if(AllTypeCount[k] == 1)
                {
                    for(int l = 0; l < 5; l++)
                    {
                        if(this->getCard(l)->getCardType() == k)
                        {
                            if(k == 1 && isStraight && straightIndex == 1) //For Straight 1,2,3,4,5
                            {
                                this->getCard(l)->moveTo(points[0].x, points[0].y, 0);
                                this->reorderChild(this->getCard(l), 0);
                                currentCardIndex++;
                            }
                            else if(k == 1)
                            {
                                this->getCard(l)->moveTo(points[4].x, points[4].y, 0);
                                this->reorderChild(this->getCard(l), 4);
                            }
                            else
                            {
                                this->getCard(l)->moveTo(points[currentCardIndex].x, points[currentCardIndex].y, 0);
                                this->reorderChild(this->getCard(l), currentCardIndex);                            currentCardIndex++;
                            }
                            break;
                        }
                    }
                }
            }
            break;

            case FourOfOneKind:
            case ThreeOfOneKind:
            case OnePair:
            for(int k = 1; k <= 13; k++)
            {
                if(AllTypeCount[k] > 1)
                {
                    sameKindCount = AllTypeCount[k];
                    sameKindCountIndex = sameKindCount;
                    for(int l = 0; l < 5; l++)
                    {
                        if(this->getCard(l)->getCardType() == k)
                        {
                            this->getCard(l)->moveTo(points[5 - sameKindCountIndex].x, points[5 - sameKindCountIndex].y, 0);
                            this->reorderChild(this->getCard(l), 5 - sameKindCountIndex);
                            sameKindCountIndex--;
                        }
                    }
                    
                    if(aceIndex >= 0)
                    {
                        this->getCard(aceIndex)->moveTo(points[4 - sameKindCount].x, points[4 - sameKindCount].y, 0);
                        this->reorderChild(this->getCard(aceIndex), 4 - sameKindCount);
                    }
                }
                else if(AllTypeCount[k] == 1)
                {
                    for(int l = 0; l < 5; l++)
                    {
                        if(this->getCard(l)->getCardType() == k)
                        {
                            if(k == 1) //special for ACE
                            {
                                aceIndex = l;
                            }
                            else
                            {
                                this->getCard(l)->moveTo(points[currentCardIndex].x, points[currentCardIndex].y, 0);
                                this->reorderChild(this->getCard(l), currentCardIndex);
                                currentCardIndex++;
                            }

                        }
                    }
                }
            }
            break;
            
            case TwoPair:
            
            isFirstPair = true;
            for(int k = 1; k <= 13; k++)
            {
                if(AllTypeCount[k] == 2)
                {
                    if(isFirstPair)
                    {
                        sameKindCountIndex = 4;
                    }
                    else
                    {
                        sameKindCountIndex = 2;
                    }
                    for(int l = 0; l < 5; l++)
                    {
                        if(this->getCard(l)->getCardType() == k)
                        {
                            this->getCard(l)->moveTo(points[5 - sameKindCountIndex].x, points[5 - sameKindCountIndex].y, 0);
                            this->reorderChild(this->getCard(l), 5 - sameKindCountIndex);
                            sameKindCountIndex--;
                        }
                    }
                    isFirstPair = false;
                }
                else if(AllTypeCount[k] == 1)
                {
                    for(int l = 0; l < 5; l++)
                    {
                        if(this->getCard(l)->getCardType() == k)
                        {

                                this->getCard(l)->moveTo(points[0].x, points[0].y, 0);
                                this->reorderChild(this->getCard(l), 0);
                        }
                    }
                }

            }
            break;
            
            case FullHouse:
            
            for(int k = 1; k <= 13; k++)
            {
                if(AllTypeCount[k] == 3)
                {
                    sameKindCountIndex = 3;
                    for(int l = 0; l < 5; l++)
                    {
                        if(this->getCard(l)->getCardType() == k)
                        {
                            this->getCard(l)->moveTo(points[5 - sameKindCountIndex].x, points[5 - sameKindCountIndex].y, 0);
                            this->reorderChild(this->getCard(l), 5 - sameKindCountIndex);
                            sameKindCountIndex--;
                        }
                    }
                }
                else if(AllTypeCount[k] == 2)
                {
                    sameKindCountIndex = 2;
                    for(int l = 0; l < 5; l++)
                    {
                        if(this->getCard(l)->getCardType() == k)
                        {
                            this->getCard(l)->moveTo(points[2 - sameKindCountIndex].x, points[2 - sameKindCountIndex].y, 0);
                            this->reorderChild(this->getCard(l), 2 - sameKindCountIndex);
                            sameKindCountIndex--;
                        }
                    }
                }
            }

            break;
        }
        

        //Change the Cards array order by from min to max as same as the display order
        for(int i = 0; i < 5; i++)
        {
            for(int j = i; j < 5; j++)
            {
                if(i == ((CCNode *)this->mCardArray->objectAtIndex(j))->getZOrder())
                {
                    this->mCardArray->exchangeObjectAtIndex(i, j);
                    break;
                }
            }
        }
        
        if(isDealer)
        {
            for(int i = 0; i < 5; i++)
            {
              ((CCNode *)this->mCardArray->objectAtIndex(4-i))->_setZOrder(i);
            }

        }
    }
    
    mCurrentPokerHand = pokerHand;
    return pokerHand;
}

void PlayCardHand::prepareCards(cocos2d::CCArray *cards)
{
    CCLog("prepareCards count: %d", cards->count());
    mPreparedCards->initWithArray(cards);
    preparedCardIndex = 0;
}

CardDeckCard*  PlayCardHand::getNextPreparedCard()
{
    int cardValue = ((CCString *)(mPreparedCards->objectAtIndex(preparedCardIndex)))->intValue();
    CardDeckCard* card =  CardDeckCard::create(cardValue);
    preparedCardIndex++;
    return card;
}

void PlayCardHand::setCardCanSelect(bool canSelect)
{
    mIsCardCanSelect = canSelect;
}

int PlayCardHand::getOnePairCarType()
{
    if(mCurrentPokerHand != OnePair)
    {
        return -1;
    }
    
    int AllTypeCount [] = {0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0};
    
    int typeIndex = 0;
    
    for(int i = 0; i < mCardArray->count(); i++)
    {
        typeIndex = (int)this->getCard(i)->getCardType();
        
        if(AllTypeCount[typeIndex] == 1)
        {
            return typeIndex;
        }
        else
        {
            AllTypeCount[typeIndex] = 1;
        }
    }

    return -1;
}