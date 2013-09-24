//
//  BattleInfo.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 13-3-28.
//
//

#include "BattleInfo.h"
#include "PlayerInfo.h"

USING_NS_CC_EXT;


static BattleInfo *pBattleInfo = NULL;

BattleInfo* BattleInfo::sharedBattleInfo(void)
{
    if (!pBattleInfo)
    {
        pBattleInfo = new BattleInfo();
        if(pBattleInfo && pBattleInfo->init())
        {
        }
    }
    
    return pBattleInfo;
}

BattleInfo::BattleInfo()
:mRaidBoss(NULL)
{

}

BattleInfo::~BattleInfo()
{
}


void BattleInfo::parseBattleInfo(CCDictionary * battleInfoDic)
{    
    mBattleID = ((CCString *)battleInfoDic->objectForKey("battleID"))->doubleValue();
    mBattleOwnerUserID = ((CCString *)battleInfoDic->objectForKey("battleOwnerUserID"))->doubleValue();
    mBattleStatus =(BattleStatus) ((CCString *)battleInfoDic->objectForKey("battleStatus"))->intValue();
    mBattlePrize = ((CCString *)battleInfoDic->objectForKey("battlePrize"))->doubleValue();;
    mBattleType = (BattleType) ((CCString *)battleInfoDic->objectForKey("battleType"))->intValue();

    
    mBattlePlayerList = CCArray::create();
    
    if(GameInfo::sharedGameInfo()->getCurrentGameType() == Texas)
    {
        CCArray * playerList = (CCArray *)battleInfoDic->objectForKey("battlePlayerList");
        PlayerInfo * playerInfo = NULL;
        
        for(int i = 0; i < playerList->count(); i ++)
        {
            CCDictionary * playerDic = (CCDictionary *)playerList->objectAtIndex(i);

            playerInfo = PlayerInfo::create();
            playerInfo->parsePlayerInfo(playerDic);
            mBattlePlayerList->addObject(playerInfo);
        }
        mDealerCards = (CCArray *)battleInfoDic->objectForKey("dealerCards");
    }
    
    if(mBattleType == BossBattle)
    {
        if(!mRaidBoss)
        {
            mRaidBoss = RaidBossInfo::create();
            mRaidBoss->retain();
        }
        
        mRaidBoss->parseRaidBossInfo((CCDictionary *) battleInfoDic->objectForKey("bossBattleInfo"));
    }
}


bool BattleInfo::init()
{
    mBattleID = 555;
    mBattleOwnerUserID = 1;
    mBattleStatus = Waiting;
    mBattlePrize = 100;
    mBattleType = SingleBattle;
    mBattleResult = BattlePush;
    return true;
}
