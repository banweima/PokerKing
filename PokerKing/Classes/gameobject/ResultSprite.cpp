//
//  ResultSprite.cpp
//  blackjack
//
//  Created by Banson Niu on 10/16/12.
//
//

#include "ResultSprite.h"
#include "BattleInfo.h"

ResultSprite::ResultSprite()
: mEqualSprite(NULL)
, mWinSprite(NULL)
, mLoseSprite(NULL)
, mBossWinSprite(NULL)
, mBossLoseSprite(NULL)
, mBlackjackSprite(NULL)
{
}

ResultSprite::~ResultSprite()
{
    CC_SAFE_RELEASE_NULL(mEqualSprite);
    CC_SAFE_RELEASE_NULL(mWinSprite);
    CC_SAFE_RELEASE_NULL(mLoseSprite);
    CC_SAFE_RELEASE_NULL(mBossLoseSprite);
    CC_SAFE_RELEASE_NULL(mBossWinSprite);
    CC_SAFE_RELEASE_NULL(mBlackjackSprite);
}

ResultSprite* ResultSprite::create()
{
    ResultSprite *resultSprite=new ResultSprite();
    
	if (resultSprite && resultSprite->init())
	{
		resultSprite->autorelease();
		return resultSprite;
	}
    
	CC_SAFE_DELETE(resultSprite);
	return NULL;
}

bool ResultSprite::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCSprite::init());
        
        mEqualSprite = CCSprite::createWithSpriteFrameName("gamecenter");
        mWinSprite = CCSprite::createWithSpriteFrameName("battle_win");
        mLoseSprite = CCSprite::createWithSpriteFrameName("battle_lose");
        mBlackjackSprite = CCSprite::createWithSpriteFrameName("Blackjack");
        
        mBossWinSprite = CCSprite::createWithSpriteFrameName("boss_win");
        mBossLoseSprite = CCSprite::createWithSpriteFrameName("boss_lose");
        
        this->addChild(mEqualSprite);
        this->addChild(mWinSprite);
        this->addChild(mLoseSprite);
        this->addChild(mBlackjackSprite);
        this->addChild(mBossWinSprite);
        this->addChild(mBossLoseSprite);
        
        mEqualSprite->setVisible(false);
        mWinSprite->setVisible(false);
        mLoseSprite->setVisible(false);
        mBlackjackSprite->setVisible(false);
        mBossLoseSprite->setVisible(false);
        mBossWinSprite->setVisible(false);
        
        bRet = true;
    } while (0);
	return bRet;
}

void ResultSprite::setType(ResultType type)
{
    // Set the count text:
    mType = type;
    mEqualSprite->setVisible(false);
    mWinSprite->setVisible(false);
    mLoseSprite->setVisible(false);
    mBlackjackSprite->setVisible(false);
    mBossLoseSprite->setVisible(false);
    mBossWinSprite->setVisible(false);
    
    bool isBoss = (BattleInfo::sharedBattleInfo()->getBattleType() == BossBattle);
    
    switch (mType) {
        case Equal:
            mEqualSprite->setVisible(true);
            break;
            
        case Win:
            
            mWinSprite->setVisible(!isBoss);
            mBossWinSprite->setVisible(isBoss);
            break;
            
        case Lose:
            mLoseSprite->setVisible(!isBoss);
            mBossLoseSprite->setVisible(isBoss);
            break;
        
        case BJ:
            mBlackjackSprite->setVisible(true);
            
        default:
            break;
    }
}

ResultType ResultSprite::getType()
{
    return mType;
}

const CCSize & ResultSprite::getContentSize()
{
    switch (mType) {
    case Equal:
        return mEqualSprite->getContentSize();
        
    case Win:
        return mWinSprite->getContentSize();
        
    case Lose:
        return mLoseSprite->getContentSize();
        
    default:
        return mBlackjackSprite->getContentSize();
    }
}
