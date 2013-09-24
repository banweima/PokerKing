//
//  GameLevelInfo.h
//  blackjack
//
//  Created by Banson Niu on 10/28/12.
//
//

#ifndef __blackjack__GameLevelInfo__
#define __blackjack__GameLevelInfo__

#include "cocos2d.h"
#include "RoomLevelInfo.h"
#include "GameInfo.h"

USING_NS_CC;

class GameLevelInfo : public CCObject
{
public:
    CC_SYNTHESIZE_RETAIN(CCArray *, mBlackjackRooms, BlackjackRooms);
    CC_SYNTHESIZE_RETAIN(CCArray *, mTexasRooms, TexasRooms);
    CC_SYNTHESIZE_RETAIN(CCArray *, mVideoPokerRooms, VideoPokerRooms);
    CC_SYNTHESIZE_RETAIN(CCArray *, mCaribbeanRooms, CaribbeanRooms);


public:
    static GameLevelInfo* sharedGameLevelInfo(void);
    GameLevelInfo();
    virtual ~GameLevelInfo();
    void parseGameLevelInfo(CCDictionary * battleInfoDic);
    virtual bool init(void);
    
    CCArray * getCurrentRoomLevels();
    
    

};

#endif /* defined(__blackjack__GameLevelInfo__) */
