//
//  CardCount.cpp
//  blackjack
//
//  Created by Banson Niu on 9/18/12.
//
//

#include "CardCount.h"
#include "Constants.h"

CardCount::~CardCount()
{
    CC_SAFE_RELEASE(mBgSprite1);
    CC_SAFE_RELEASE(mBgSprite2);
    CC_SAFE_RELEASE(mCountText);
}

CardCount* CardCount::create()
{
    CardCount *cardCount=new CardCount();
    
	if (cardCount && cardCount->init())
	{
		cardCount->autorelease();
		return cardCount;
	}
    
	CC_SAFE_DELETE(cardCount);
	return NULL;
}

bool CardCount::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCSprite::init());
        
        setBgSprite1(CCSprite::createWithSpriteFrameName("number"));
        setBgSprite2(CCSprite::createWithSpriteFrameName("number"));
        setCountText(CCLabelTTF::create("", "Helvetica", 18));

        this->addChild(mBgSprite1);
        this->addChild(mBgSprite2);
        this->addChild(mCountText);
//        mBgSprite->addChild(mCountText);
//        mCountText->setPosition(ccp(mBgSprite->getContentSize().width/2, mBgSprite->getContentSize().height/2));
        
        bRet = true;
    } while (0);
	return bRet;
}

////////////////////////////////////////////////////////////////
//
// Set the current card count:
//
void CardCount::setCount(int newCount)
{
    // Set the count text:
    mCountText->setString(CCString::createWithFormat("%d", newCount)->getCString());
    
    // Make sure the background matches:
    if (newCount <= 21)
        setNormal();
    else
        setBusted();
    
    mBgSprite2->setOpacity(160);
    mBgSprite2->setScale(1.0);
    mBgSprite2->runAction(CCSpawn::create(
                                   CCScaleTo::create(PingAnimationTime, 2.5),
                                   //Alpha
                                   CCFadeOut::create(PingAnimationTime),
                                   NULL
                                ));
}


////////////////////////////////////////////////////////////////
//
// Set the current PokerHand:
//
void CardCount::setPokerHand(PokerHand pokerHand)
{
switch (pokerHand)
            {
            case Mass:
            case AK:
            mCountText->setString("高牌");
            break;
            case OnePair:
            mCountText->setString("单对");
            break;
            case TwoPair:
            mCountText->setString("两对");
            break;
            case ThreeOfOneKind:
            mCountText->setString("三张");
            break;
            case Straight:
            mCountText->setString("顺子");
            break;
            case Flush:
            mCountText->setString("同花");
            break;
            case FullHouse:
            mCountText->setString("葫芦");
            break;
            case FourOfOneKind:
            mCountText->setString("四张");
            break;
            case StraightFlush:
            mCountText->setString("同花顺");
            break;
            case RoyalStraightFlush:
            mCountText->setString("皇家同花顺");;
            break;

            }

    // Set the count text:
    

}

////////////////////////////////////////////////////////////////
//
// Set the win:
//
void CardCount::setWin(int isPlayerWin)
{
    // Set the count text:
    switch (isPlayerWin) {
  case 1:
    mCountText->setString("获胜");
    break;

  case 0:
    mCountText->setString("平局");
    break;
    
    
    case -1:
    mCountText->setString("失利");
    break;

}
    
    

}

////////////////////////////////////////////////////////////////
//
// Set the image under the count to be the normal one:
//

void CardCount::setNormal()
{
    // The background image is the normal one:
//    SpriteSheetManager.setSpriteFrameWithName(this._backgroundSprite,'BlackjackSpriteSheetNumberSpaceUnder');
    mCountText->setColor(ccBLACK);
}

////////////////////////////////////////////////////////////////
//
// Set the image under the count to be the busted one:
//

void CardCount::setBusted()
{
    // The background image is the normal one:
//    SpriteSheetManager.setSpriteFrameWithName(this._backgroundSprite,'BlackjackSpriteSheetNumberSpaceBust');
    mCountText->setColor(ccRED);
}

////////////////////////////////////////////////////////////////
//
// Sets the count to display or not:
//

void CardCount::setPingVisible(bool newPingIsVisible)
{
    // See if it should be visible but it's not yet visible:
    mBgSprite1->setVisible(newPingIsVisible);
    mBgSprite2->setVisible(newPingIsVisible);
}
