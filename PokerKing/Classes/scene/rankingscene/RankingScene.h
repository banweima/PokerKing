//
//  RankingScene.h
//  blackjack
//
//  Created by Banson Niu on 9/12/12.
//
//

#ifndef __blackjack__RankingScene__
#define __blackjack__RankingScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class RankingScene : public CCScene
{
public:
    static RankingScene* create();
    bool init();
    
    void setupScene();
};

#endif /* defined(__blackjack__RankingScene__) */
