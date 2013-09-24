//
//  GameLevelInfo.cpp
//  blackjack
//
//  Created by Banson Niu on 10/28/12.
//
//

#include "GameLevelInfo.h"



static GameLevelInfo *pGameLevelInfo = NULL;

GameLevelInfo* GameLevelInfo::sharedGameLevelInfo(void)
{
    if (!pGameLevelInfo)
    {
        pGameLevelInfo = new GameLevelInfo();
        if(pGameLevelInfo && pGameLevelInfo->init())
        {
        }
    }
    
    return pGameLevelInfo;
}

GameLevelInfo::GameLevelInfo()
{

}

GameLevelInfo::~GameLevelInfo()
{
    CC_SAFE_RELEASE_NULL(mBlackjackRooms);
    CC_SAFE_RELEASE_NULL(mTexasRooms);
    CC_SAFE_RELEASE_NULL(mCaribbeanRooms);
    CC_SAFE_RELEASE_NULL(mVideoPokerRooms);
}

bool GameLevelInfo::init()
{
    mBlackjackRooms = CCArray::createWithCapacity(8);
    mBlackjackRooms->retain();
    
    mTexasRooms = CCArray::createWithCapacity(8);
    mTexasRooms->retain();
    
    mVideoPokerRooms = CCArray::createWithCapacity(8);
    mVideoPokerRooms->retain();
    
    mCaribbeanRooms = CCArray::createWithCapacity(8);
    mCaribbeanRooms->retain();
    
    for(int i = 0; i < 4; i ++)
    {
        mBlackjackRooms->addObject(RoomLevelInfo::create());
        mTexasRooms->addObject(RoomLevelInfo::create());
        mVideoPokerRooms->addObject(RoomLevelInfo::create());
        mCaribbeanRooms->addObject(RoomLevelInfo::create());
    }
    return true;
}

void GameLevelInfo::parseGameLevelInfo(cocos2d::CCDictionary *GameLevelInfoDic)
{
    CCArray * roomInfoList = (CCArray *)GameLevelInfoDic->objectForKey("roomInfor");
    
    RoomLevelInfo * pRoomLevelInfo = RoomLevelInfo::create();
    
    for(int i = 0; i < roomInfoList->count(); i ++)
    {
        CCDictionary * roomDic = (CCDictionary *)roomInfoList->objectAtIndex(i);
 
        pRoomLevelInfo->parseRoomLevelInfo(roomDic);
        
        switch ((GameType)((CCString *)roomDic->objectForKey("gameType"))->intValue()) {
            case BlackJack:
            {
                ((RoomLevelInfo *)mBlackjackRooms->objectAtIndex(((CCString *)roomDic->objectForKey("roomLevel"))->intValue() - 1))->copyData(pRoomLevelInfo);
                break;
            }
            case Texas:
            {
                ((RoomLevelInfo *)mTexasRooms->objectAtIndex(((CCString *)roomDic->objectForKey("roomLevel"))->intValue() - 1))->copyData(pRoomLevelInfo);
                break;
            }
            case VideoPoker:
            {
                ((RoomLevelInfo *)mVideoPokerRooms->objectAtIndex(((CCString *)roomDic->objectForKey("roomLevel"))->intValue() - 1))->copyData(pRoomLevelInfo);
                break;
            }
            case Caribbean:
            {
                ((RoomLevelInfo *)mCaribbeanRooms->objectAtIndex(((CCString *)roomDic->objectForKey("roomLevel"))->intValue() - 1))->copyData(pRoomLevelInfo);
                break;
            }
            default:
            break;
        }
    }
}

CCArray * GameLevelInfo::getCurrentRoomLevels()
{
    switch (GameInfo::sharedGameInfo()->getCurrentGameType()) {
        case BlackJack:
        {
            return mBlackjackRooms;
        }
        case Caribbean:
        {
            return mCaribbeanRooms;
        }
        case VideoPoker:
        {
            return mVideoPokerRooms;
        }
        case Lottery:
        break;
        
        case Texas:
        {
             return mTexasRooms;
        }
    }
}