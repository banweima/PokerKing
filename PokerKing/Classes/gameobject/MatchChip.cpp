//
//  MatchChip.cpp
//  blackjack
//
//  Created by Banson Niu on 10/15/12.
//
//

#include "MatchChip.h"
#include "Constants.h"

MatchChip::~MatchChip()
{
    CC_SAFE_RELEASE(mBgSprite1);
    CC_SAFE_RELEASE(mBgSprite2);
    CC_SAFE_RELEASE(mCountText);
}

MatchChip* MatchChip::create()
{
    MatchChip *matchChip=new MatchChip();
    
	if (matchChip && matchChip->init())
	{
		matchChip->autorelease();
		return matchChip;
	}
    
	CC_SAFE_DELETE(matchChip);
	return NULL;
}

bool MatchChip::init()
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
        
        this->setScale(1.5);
        
        bRet = true;
    } while (0);
	return bRet;
}

////////////////////////////////////////////////////////////////
//
// Set the current card count:
//
void MatchChip::setCount(int newCount)
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


int MatchChip::getCount()
{
    return CCString::create( mCountText->getString())->intValue();
}

////////////////////////////////////////////////////////////////
//
// Set the image under the count to be the normal one:
//

void MatchChip::setNormal()
{
    // The background image is the normal one:
    //    SpriteSheetManager.setSpriteFrameWithName(this._backgroundSprite,'BlackjackSpriteSheetNumberSpaceUnder');
    mCountText->setColor(ccBLACK);
}

////////////////////////////////////////////////////////////////
//
// Set the image under the count to be the busted one:
//

void MatchChip::setBusted()
{
    // The background image is the normal one:
    //    SpriteSheetManager.setSpriteFrameWithName(this._backgroundSprite,'BlackjackSpriteSheetNumberSpaceBust');
    mCountText->setColor(ccRED);
}

////////////////////////////////////////////////////////////////
//
// Sets the count to display or not:
//

void MatchChip::setPingVisible(bool newPingIsVisible)
{
    // See if it should be visible but it's not yet visible:
    mBgSprite1->setVisible(newPingIsVisible);
    mBgSprite2->setVisible(newPingIsVisible);
}