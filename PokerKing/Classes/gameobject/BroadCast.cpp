//
//  BroadCast.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-30.
//
//

#include "BroadCast.h"
#include "Constants.h"

#define Rolling_Speed 50

static BroadCast *pBroadCast = NULL;

BroadCast::BroadCast()
{


}

BroadCast::~BroadCast()
{
    CC_SAFE_RELEASE(mBgSprite);
    CC_SAFE_RELEASE(mContentText);
    CC_SAFE_RELEASE(mBCContentList);
}

BroadCast* BroadCast::sharedBroadCast(void)
{
    if (!pBroadCast)
    {
        pBroadCast = new BroadCast();
        
        if(pBroadCast && pBroadCast->init())
        {

        }
    }
    
    return pBroadCast;
}

bool BroadCast::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCSprite::init());
        
        mBgSprite = CCSprite::createWithSpriteFrameName("r_line_2");
        mBgSprite->retain();
        
        mContentText =  CCLabelTTF::create("", "Helvetica", 18);
        mContentText->retain();
        
        int w = getWinW();
        int y = getWinH();
        mBgSprite->setScaleX(w/mBgSprite->getContentSize().width);
        mBgSprite->setPosition(ccp(0, 0.8 * y));
        mBgSprite->setAnchorPoint(ccp(0,0.5));
        mBgSprite->setVisible(false);
        
        
        this->addChild(mBgSprite,200);
        this->addChild(mContentText,100);
        
        mContentText->setVisible(false);

        mContentText->setPosition(ccp(w, 0.8 * y));
        mContentText->setAnchorPoint(ccp(0,0.5));


        this->setVisible(true);
        bRet = true;
        
        mBCContentList = CCArray::create();
        mBCContentList->retain();
        
        BCCount = -1;
        isRolling = false;
        schedule(schedule_selector(BroadCast::retrieveBroadCast),180.0f);
        
    } while (0);
	return bRet;
}

void BroadCast::playContentList()
{
    if(BCCount >= 0)
    {
        isRolling = true;
        playContent(((CCString *)mBCContentList->objectAtIndex(BCCount))->getCString());
        BCCount--;
    }
}

void BroadCast::playContent(std::string content)
{
    mContentText->setString(content.c_str());
    mContentText->setVisible(true);
    mBgSprite->setVisible(true);
    
    mContentText->runAction(CCSequence::create(
                                    CCMoveTo::create((mContentText->getContentSize().width +mContentText->getPositionX()) / Rolling_Speed, ccp(-1 * mContentText->getContentSize().width,mContentText->getPositionY())),
                                    CCDelayTime::create(0.5),
                                    CCCallFunc::create(this, callfunc_selector(BroadCast::hideAll)),
                                    NULL));

}

void BroadCast::hideAll()
{
    mContentText->setVisible(false);
    mBgSprite->setVisible(false);
    mContentText->setPosition(ccp(getWinW() + 10, 0.8 * getWinH()));
    if(BCCount >= 0)
    {
        playContentList();
    }
    else
    {
        isRolling = false;
    }
}

void BroadCast::retrieveBroadCast()
{
    GameServerAction::sharedGameServerAction()->retrieveBroadcast(this,callfuncND_selector(BroadCast::retrieveBroadCast_Done));

}


void BroadCast::retrieveBroadCast_Done(cocos2d::CCNode *pSender, void *data)
{
    if((bool)data)
    {
        if(mBCContentList->count() > 0)
        {
            BCCount = mBCContentList->count() - 1;
            playContentList();
        }
    }
}

void BroadCast::parseBCContent(cocos2d::CCDictionary *bcDic)
{
    mBCContentList->removeAllObjects();
    
    
    CCArray * bcList = (CCArray *)bcDic->objectForKey("broadCastProfile");
    if(bcList)
    {        
        for(int i = 0; i < bcList->count(); i ++)
        {
            CCDictionary * itemDic = (CCDictionary *)bcList->objectAtIndex(i);
            mBCContentList->addObject((CCString *) itemDic->valueForKey("content"));
        }
    }

}

BroadCast * BroadCast::addBCToLayer(CCLayer *parentLayer)
{
    pBroadCast->removeFromParentAndCleanup(false);
    
    parentLayer->addChild(pBroadCast, 100, kTagLoading);
    
    if(isRolling)
    {
        mContentText->setPosition(lastPoint);
        playContentList();
    }
    
    return pBroadCast;
}

void BroadCast::pauseRolling()
{
    if(isRolling)
    {
        lastPoint = mContentText->getPosition();
        BCCount++;
    }

}