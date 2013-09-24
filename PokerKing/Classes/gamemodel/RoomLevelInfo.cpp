//
//  RoomLevelInfo.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-21.
//
//

#include "RoomLevelInfo.h"


USING_NS_CC_EXT;

RoomLevelInfo* RoomLevelInfo::create()
{
    RoomLevelInfo* pRoomLevelInfo = new RoomLevelInfo();
    
    if (pRoomLevelInfo && pRoomLevelInfo->init())
    {
        pRoomLevelInfo->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRoomLevelInfo);
    }
    
    return pRoomLevelInfo;

}


void RoomLevelInfo::parseRoomLevelInfo(CCDictionary * RoomLevelInfoDic)
{    
    mLevelScore = ((CCString *)RoomLevelInfoDic->objectForKey("levelScore"))->intValue();
    
    mMinHand = ((CCString *)RoomLevelInfoDic->objectForKey("minHand"))->intValue();
    
    mMaxHand = ((CCString *)RoomLevelInfoDic->objectForKey("maxHand"))->intValue();
    
    mRoomLevel = (RoomType) ((CCString *)RoomLevelInfoDic->objectForKey("roomLevel"))->intValue();
}


bool RoomLevelInfo::init()
{
    mLevelScore = 5;
    mMinHand = 200;
    mMaxHand = 2000;
    return true;
}

void RoomLevelInfo::copyData(RoomLevelInfo *pRoomInfo)
{
    mLevelScore = pRoomInfo->getLevelScore();
    mMinHand = pRoomInfo->getMinHand();
    mMaxHand = pRoomInfo->getMaxHand();
    mRoomLevel = pRoomInfo->getRoomLevel();
}
