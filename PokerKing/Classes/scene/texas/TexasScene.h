//
//  TexasScene.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-12.
//
//

#ifndef __PokerKing__TexasScene__
#define __PokerKing__TexasScene__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

#include "RoomLevelInfo.h"

USING_NS_CC;

class TexasScene : public CCScene
{
public:
    static TexasScene* create(RoomLevelInfo * mRoomLevelInfo);
    bool init(RoomLevelInfo * mRoomLevelInfo);
    
    void setupScene(RoomLevelInfo * mRoomLevelInfo);
};


#endif /* defined(__PokerKing__TexasScene__) */
