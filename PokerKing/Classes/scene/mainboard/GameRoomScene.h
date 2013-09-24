//
//  GameRoomScene.h
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#ifndef __blackjack__GameRoomScene__
#define __blackjack__GameRoomScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class GameRoomScene : public CCScene
{
public:
    static GameRoomScene* create();

    bool init();
    
    void setupScene();
};

#endif /* defined(__blackjack__GameRoomScene__) */
