//
//  PlayerInfo.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-12.
//
//

#include "PlayerInfo.h"


USING_NS_CC_EXT;

PlayerInfo* PlayerInfo::create()
{
    PlayerInfo* pPlayerInfo = new PlayerInfo();
    
    if (pPlayerInfo && pPlayerInfo->init())
    {
        pPlayerInfo->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pPlayerInfo);
    }
    
    return pPlayerInfo;

}


void PlayerInfo::parsePlayerInfo(CCDictionary * playerInfoDic)
{    
    mPlayerID = ((CCString *)playerInfoDic->objectForKey("playerID"))->doubleValue();
    
    mPlayerCards = (CCArray *)playerInfoDic->objectForKey("cardsInDeck");
    
    mPlayerBet = ((CCString *)playerInfoDic->objectForKey("playerBet"))->doubleValue();
}


bool PlayerInfo::init()
{
    mPlayerID = 0;
    mPlayerCards = NULL;
    mPlayerBet = 0;
    return true;
}
