//
//  MainBoardScene.h
//  blackjack
//
//  Created by Niu Xiaoming on 13-3-23.
//
//

#ifndef __blackjack__MainBoardScene__
#define __blackjack__MainBoardScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class MainBoardScene : public CCScene
{
public:
    static MainBoardScene* create();
    bool init();
    
    void setupScene();
};

#endif /* defined(__blackjack__MainBoardScene__) */
