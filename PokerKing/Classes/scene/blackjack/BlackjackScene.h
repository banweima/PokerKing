//
//  BlackjackScene.h
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#ifndef __blackjack__BlackjackScene__
#define __blackjack__BlackjackScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameLevelInfo.h"

USING_NS_CC;

class BlackjackScene : public CCScene
{    
public:
    static BlackjackScene* create(RoomLevelInfo* gameLevelInfo);
    bool init(RoomLevelInfo* gameLevelInfo);
    
    void setupScene(RoomLevelInfo* gameLevelInfo);
    
    
};

#endif /* defined(__blackjack__BlackjackScene__) */
