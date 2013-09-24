//
//  PlayerInfo.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-12.
//
//

#ifndef __PokerKing__PlayerInfo__
#define __PokerKing__PlayerInfo__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;


class PlayerInfo : public CCObject
{
private:
    CC_SYNTHESIZE(long, mPlayerID, PlayerID);
    CC_SYNTHESIZE(CCArray *, mPlayerCards, PlayerCards);
    CC_SYNTHESIZE(long, mPlayerBet, PlayerBet);

    
public:
    static PlayerInfo* create();
    void parsePlayerInfo(CCDictionary * playerInfoDic);
    bool init();
};

#endif /* defined(__PokerKing__PlayerInfo__) */
