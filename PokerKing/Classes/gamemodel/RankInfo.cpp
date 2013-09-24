//
//  RankInfo.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-25.
//
//

#include "RankInfo.h"


USING_NS_CC_EXT;

RankInfo* RankInfo::create()
{
    RankInfo* pRankInfo = new RankInfo();
    
    if (pRankInfo && pRankInfo->init())
    {
        pRankInfo->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRankInfo);
    }
    
    return pRankInfo;

}


void RankInfo::parseRankInfo(CCDictionary * RankInfoDic)
{    
    mDrawTime = ((CCString *)RankInfoDic->objectForKey("drawTime"))->doubleValue();
    mLoseMoney = ((CCString *)RankInfoDic->objectForKey("loseMoney"))->doubleValue();
    mLoseTime = ((CCString *)RankInfoDic->objectForKey("loseTime"))->doubleValue();
    mTotalMoney = ((CCString *)RankInfoDic->objectForKey("totalMoney"))->doubleValue();
    mUserId = ((CCString *)RankInfoDic->objectForKey("userId"))->doubleValue();
    mWinMoney = ((CCString *)RankInfoDic->objectForKey("winMoney"))->doubleValue();
    mWinTime = ((CCString *)RankInfoDic->objectForKey("winTime"))->doubleValue();
   
}


bool RankInfo::init()
{
    mDrawTime = 0;
    mLoseMoney = 0;
    mLoseTime = 0;
    mTotalMoney = 0;
    mUserId = 0;
    mWinMoney = 0;
    mWinTime = 0;
    
    return true;
}