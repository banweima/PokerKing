//
//  VideoPokerScene.h
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#ifndef __blackjack__VideoPokerScene__
#define __blackjack__VideoPokerScene__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "RoomLevelInfo.h"

USING_NS_CC;

class VideoPokerScene : public CCScene
{
public:
    static VideoPokerScene* create(RoomLevelInfo * mRoomLevelInfo);
    bool init(RoomLevelInfo * mRoomLevelInfo);
    
    void setupScene(RoomLevelInfo * mRoomLevelInfo);
};

#endif /* defined(__blackjack__VideoPokerScene__) */
