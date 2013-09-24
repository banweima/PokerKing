//
//  TaskScene.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-5.
//
//

#ifndef __PokerKing__TaskScene__
#define __PokerKing__TaskScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class TaskScene : public CCScene
{
public:
    static TaskScene* create();
    bool init();
    
    void setupScene();
};

#endif /* defined(__PokerKing__TaskScene__) */
