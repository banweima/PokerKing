//
//  CaribbeanScene.h
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#ifndef __blackjack__CaribbeanScene__
#define __blackjack__CaribbeanScene__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

#include "RoomLevelInfo.h"

USING_NS_CC;

class CaribbeanScene : public CCScene
{
public:
    static CaribbeanScene* create(RoomLevelInfo * mRoomLevelInfo);
    bool init(RoomLevelInfo * mRoomLevelInfo);
    
    void setupScene(RoomLevelInfo * mRoomLevelInfo);
};

#endif /* defined(__blackjack__CaribbeanScene__) */
