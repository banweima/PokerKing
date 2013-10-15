//
//  PlayCard.cpp
//  blackjack
//
//  Created by Banson Niu on 9/12/12.
//
//

#include "PlayCard.h"
#include "Constants.h"

PlayCard::PlayCard()
: mIsFlipped(false)
, mCardValue(0)
, mIsSelected(false)
, shadowCard(NULL)
{
    
}

PlayCard::~PlayCard()
{
}

PlayCard* PlayCard::create(CardClass cclass, CardSuit suit, CardType type, bool flipped)
{
    return create(cclass, suit, type, flipped, false);
    
}

PlayCard* PlayCard::create(CardClass cclass, CardSuit suit, CardType type, bool flipped, bool canSelect)
{
    PlayCard *sprite=new PlayCard();
    
	if (sprite && sprite->init(cclass, suit, type, flipped, canSelect))
	{
		sprite->autorelease();
        
		return sprite;
	}
    
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool PlayCard::init(CardClass cclass, CardSuit suit, CardType type, bool flipped, bool canSelect)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCSprite::init());
        
//        mSpriteBatchNode = CCSpriteBatchNode::create("plist/porkerlist.png");
        
        winH = getWinH(); //iPhone 5 still use 480;
        
        mSpriteBatchNode = CCNode::create();
        this->addChild(mSpriteBatchNode);
        
        this->setupPlayCard(cclass, suit, type, flipped);
        
        if(canSelect)
        {
            CCSprite* standaloneNormal = CCSprite::createWithSpriteFrameName("stamp_pk");
            shadowCard =
            CCMenuItemSprite::create(standaloneNormal,
                                     standaloneNormal,
                                     this,
                                     menu_selector(PlayCard::onCardClicked));
            shadowCard->setPosition(mSpriteBatchNode->getPositionX(), mSpriteBatchNode->getPositionY());
            
            CCMenu* menu = CCMenu::create(shadowCard, NULL);
            shadowCard->setOpacity(0);
            shadowCard->setScale(CardScaleFactor);
            
            this->addChild(menu);
            menu->setPosition(ccp(0,0));
        }
        bRet = true;
    } while (0);
	return bRet;
}

void PlayCard::setupPlayCard(CardClass cclass, CardSuit suit, CardType type, bool flipped)
{
    mCardClass = cclass;
    mCardSuit = suit;
    mCardType = type;
    mIsFlipped = flipped;

    mCardBgSprite = CCSprite::createWithSpriteFrameName("base_bg_1");
//    mCardBgSprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("card_bk_%d", cclass)->getCString());
    mCardFrontBgSprite = CCSprite::createWithSpriteFrameName("base_front_1");
//    mCardFrontBgSprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("base_front_%d", cclass)->getCString());
    mCardFrontSprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_%d", this->getSuitName(suit), type)->getCString());
    
    mSpriteBatchNode->addChild(mCardBgSprite);
    mSpriteBatchNode->addChild(mCardFrontBgSprite);
    mSpriteBatchNode->addChild(mCardFrontSprite);
    
    this->mCardValue = type>10?10:type;
    if(this->mCardValue==1)
        this->mCardValue = 11;
    
    mSpriteBatchNode->setScale(CardScaleFactor);
    
    
    this->setFlipped(flipped);
}

void PlayCard::setCardScale(float scale)
{
    mSpriteBatchNode->setScale(scale);
    if(shadowCard != NULL)
    {
        shadowCard->setScale(scale);
    }
}

const char* PlayCard::getSuitName(CardSuit suit)
{
    switch (suit) {
        case Diamonds:
            return "diamond";
        case Spades:
            return "spade";
        case Clubs:
            return "club";
        default:
            return "heart";
    }
}

CardClass PlayCard::getCardClass()
{
    return mCardClass;
}

CardSuit PlayCard::getCardSuit()
{
    return mCardSuit;
}

CardType PlayCard::getCardType()
{
    return mCardType;
}

bool PlayCard::isFlipped()
{
    return mIsFlipped;
}

void PlayCard::setFlipped(bool flipped)
{
    mIsFlipped = flipped;
    
    if(mIsFlipped) {
        mCardBgSprite->setVisible(true);
        mCardFrontBgSprite->setVisible(false);
        mCardFrontSprite->setVisible(false);
    } else {
        mCardBgSprite->setVisible(false);
        mCardFrontBgSprite->setVisible(true);
        mCardFrontSprite->setVisible(true);
    }
}

float PlayCard::getCardWidth()
{
    return mCardFrontSprite->getContentSize().width * this->getScale();
}

float PlayCard::getCardHeight()
{
    return mCardFrontSprite->getContentSize().height * this->getScale();
}

////////////////////////////////////////////////////////////////
//
// Returns true if this is an ace with a value of 11.
//

bool PlayCard::isConvertibleAce()
{
    //log("Checking to see if this card is convertible with value " + this._value);
    
    // See if this is an ace with a value of 11:
    if ((mCardType == Ace) && (mCardValue == 11))
    {
        //log("This card is convertible");
        
        return true;
    }
    
    return false;
}

////////////////////////////////////////////////////////////////
//
// Returns true if this is an ace with a value of 1.
//

bool PlayCard::isConvertedAce()
{
    //log("Checking to see if this card is converted with value " + this._value);
    
    // See if this is an ace with a value of 11:
    if ((mCardType == Ace) && (mCardValue == 1))
    {
        //log("This card is converted");
        
        return true;
    }
    
    return false;
}

////////////////////////////////////////////////////////////////
//
// Convert an ace from a value of 11 to a value of 1.
//

void PlayCard::convertAceToLowValue()
{
    // Only convert if it's actually convertible:
    if (isConvertibleAce())
    {
        //log("This card is being converted");
        
        mCardValue	= 1;
    }
}

////////////////////////////////////////////////////////////////
//
// Convert an ace from a value of 1 to a value of 11.
//

void PlayCard::convertAceToHighValue()
{
    // Only reconvert if it's actually converted:
    if (isConvertedAce())
    {
        //log("This card is being reconverted");
        
        mCardValue	= 11;
    }
}

////////////////////////////////////////////////////////////////
//
// This flips a card over instantly.
//

void PlayCard::flipInstantly()
{
    mIsFlipped = !mIsFlipped;
    if (isVisible())
    {
        // Hide the back and show the front:
        setFlipped(mIsFlipped);
    }
}

////////////////////////////////////////////////////////////////
//
// Move the card somewhere below the screen:
//

void PlayCard::moveBelowScreen(float newX)
{
    setPosition(ccp(newX, -getCardHeight()/2));
}

////////////////////////////////////////////////////////////////
//
// Move the card somewhere below the screen:
//

void PlayCard::moveAboveScreen(float newX)
{    
    setPosition(ccp(newX, winH + getCardWidth()/2));
}

////////////////////////////////////////////////////////////////
//
// Moves to a new globally specified location.
//

void PlayCard::moveToPosition(float newX, float newY, float newAngle)
{
    setPosition(ccp(newX, newY));
    setRotation(newAngle);
}

////////////////////////////////////////////////////////////////
//
// Function to move the card to a new position.
//
//   float targetX
//   float targetY
//   float targetAngle - degrees clockwise
//   int   timeDelay   - milliseconds
//

void PlayCard::moveTo(float targetX, float targetY, float timeDelay)
{
    this->runAction(CCSpawn::create(
                                CCDelayTime::create(timeDelay),
                                CCMoveTo::create(MovementTime, ccp(targetX, targetY)),
                                NULL
                                ));
}

////////////////////////////////////////////////////////////////
//
// Starts animation to move the card to below the screen
// with a defined target horizontal position, angle and
// time delay before starting to move.
//

void PlayCard::moveToBelowScreen(float targetX, float targetAngle, float timeDelay)
{
    // Move the card:
    moveTo(targetX, -getCardHeight()/2, timeDelay);
}

////////////////////////////////////////////////////////////////
//
// Starts animation to move the card to above the screen
// with a defined target horizontal position, angle and
// time delay before starting to move.
//

void PlayCard::moveToAboveScreen(float targetX, float targetAngle, float timeDelay)
{
    
    // Move the card:
    moveTo(targetX, winH + getCardHeight()/2, timeDelay);
}

void PlayCard::flipCard()
{
    this->setFlipped(!isFlipped());
}

////////////////////////////////////////////////////////////////
//
// Function to flip a card over.
//

void PlayCard::flipCard(float timeDelay)
{
    CCSize size = this->getContentSize();
    this->runAction(CCSequence::create(
                               CCDelayTime::create(timeDelay),
                               CCSpawn::create(
                                               CCScaleTo::create(FlippingTime/2, 0, getScaleY()),
                                               CCFadeTo::create(FlippingTime/2, 0.2),
                                               NULL
                                               ),
                               CCCallFunc::create(this, callfunc_selector(PlayCard::flipCard)),
                               CCSpawn::create(
                                               CCScaleTo::create(FlippingTime/2, getScaleY(), getScaleY()),
                                               CCFadeTo::create(FlippingTime/2, 1),
                                               NULL
                                               ),
                                NULL
                               ));
}

////////////////////////////////////////////////////////////////
//
// Adds a shaking action to the card.
//

void PlayCard::startShaking(float timeDelay, float shakeTime, float newShakeDeltaX, float newShakeDeltaY, float newShakeDeltaAngle)
{
    // Set the shake start time:
//    this._shakeStartTime	= this._currentTime + timeDelay;
//    this._shakeEndTime		= this._shakeStartTime + shakeTime;
//    this._shakeDeltaX		= newShakeDeltaX;
//    this._shakeDeltaY		= newShakeDeltaY;
//    this._shakeDeltaAngle	= newShakeDeltaAngle;
    
//    this->runAction(CCSequence::create(
//                                    CCDelayTime::create(timeDelay),
//                                    CCCallFunc::create(this, callfunc_selector(PlayCard::shaking)),
//                                    CCDelayTime::create(shakeTime),
//                                    CCCallFunc::create(this, callfunc_selector(PlayCard::endShaking)),
//                                    NULL
//                                ));
}

void PlayCard::onCardClicked(cocos2d::CCObject *object)
{
    //flipCard(0.3);
    mIsSelected = !mIsSelected;
    
    if(mIsSelected)
    {
        shadowCard->setOpacity(200);
    }
    else
    {
        shadowCard->setOpacity(0);
    }
}

bool PlayCard::isSelected()
{
    return mIsSelected;
}

void PlayCard::resetCard(CardSuit suit, CardType type)
{
    float scale = mCardFrontSprite->getScale();
    
    mSpriteBatchNode->removeChild(mCardFrontSprite, true);

    mCardFrontSprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_%d", this->getSuitName(suit), type)->getCString());
    mSpriteBatchNode->addChild(mCardFrontSprite);
    
    mCardFrontSprite->setScale(scale);
    mCardFrontSprite->setVisible(!mIsFlipped);
    
    mCardSuit = suit;
    mCardType = type;
    
    this->mCardValue = type>10?10:type;
    if(this->mCardValue==1)
        this->mCardValue = 11;

}