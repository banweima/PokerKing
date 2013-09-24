//
//  RaidBossInfo.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-3.
//
//

#include "RaidBossInfo.h"



USING_NS_CC_EXT;

RaidBossInfo* RaidBossInfo::create()
{
    RaidBossInfo* pRaidBossInfo = new RaidBossInfo();
    
    if (pRaidBossInfo && pRaidBossInfo->init())
    {
        pRaidBossInfo->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRaidBossInfo);
    }
    
    return pRaidBossInfo;

}


void RaidBossInfo::parseRaidBossInfo(CCDictionary * RaidBossInfoDic)
{
    mBossType = ((CCString *)RaidBossInfoDic->objectForKey("bossType"))->intValue();
    
    mBossInstance = ((CCString *)RaidBossInfoDic->objectForKey("bossInstance"))->doubleValue();
    
    if(RaidBossInfoDic->objectForKey("bossName"))
    mOnlineBossName = ((CCString *)RaidBossInfoDic->objectForKey("bossName"))->getCString();
    
    if(RaidBossInfoDic->objectForKey("bossImage"))
    mOnlineBossImageUrl = ((CCString *)RaidBossInfoDic->objectForKey("bossImage"))->getCString();
    
    mStatus = (BossStatus)((CCString *)RaidBossInfoDic->objectForKey("status"))->intValue();
    
    mCurrentHP = ((CCString *)RaidBossInfoDic->objectForKey("currentHP"))->doubleValue();
    

    mMaxHP = ((CCString *)RaidBossInfoDic->objectForKey("maxHP"))->doubleValue();
}


bool RaidBossInfo::init()
{
    mBossInstance  = 0;
    mOnlineBossName = "";
    mOnlineBossImageUrl = "";
    mBossType = 1;
    mCurrentHP = 0;
    mMaxHP = 1;
    mStatus = BossStatus_Active;
    return true;
}

std::string RaidBossInfo::getBossName()
{
    switch (mBossType) {
      case 1:
        return "赌神润发";
      case 2:
        return "赌神德华";
      case 3:
        return "赌神星驰";
      default:
        return "赌神某某";
    }
}

std::string RaidBossInfo::getBossImage()
{
    switch (mBossType) {
//      case 1:
//        return "赌神润发";
//      case 2:
//        return "赌神德华";
//      case 3:
//        return "赌神星驰";
      default:
        return "Dealer";
    }
}