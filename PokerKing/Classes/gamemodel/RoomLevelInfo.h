//
//  RoomLevelInfo.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-21.
//
//

#ifndef __PokerKing__RoomLevelInfo__
#define __PokerKing__RoomLevelInfo__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

enum RoomType
{
    Hongkong_R = 1,
    Macau_R,
    MonteCarlo_R,
    LasVegas_R
};

class RoomLevelInfo : public CCObject
{
public:
    CC_SYNTHESIZE(int, mLevelScore, LevelScore);
    CC_SYNTHESIZE(int, mMinHand, MinHand);
    CC_SYNTHESIZE(long, mMaxHand, MaxHand);
    CC_SYNTHESIZE(RoomType, mRoomLevel, RoomLevel);

    
public:
    static RoomLevelInfo* create();
    void parseRoomLevelInfo(CCDictionary * RoomLevelInfoDic);
    bool init();
    void copyData(RoomLevelInfo* pRoomInfo);
};

#endif /* defined(__PokerKing__RoomLevelInfo__) */
