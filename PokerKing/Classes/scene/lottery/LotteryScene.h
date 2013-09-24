//
//  LotteryScene.h
//  blackjack
//
//  Created by Niu Xiaoming on 13-4-8.
//
//

#ifndef __blackjack__LotteryScene__
#define __blackjack__LotteryScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameLevelInfo.h"
#include "LotteryLayer.h"

USING_NS_CC;

class LotteryScene : public CCScene
{    
public:
    static LotteryScene* create();
    bool init();
    
    void setupScene();
};


#endif /* defined(__blackjack__LotteryScene__) */
