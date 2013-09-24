//
//  ShopScene.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-26.
//
//

#ifndef __PokerKing__ShopScene__
#define __PokerKing__ShopScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class ShopScene : public CCScene
{
public:
    static ShopScene* create();
    bool init();
    
    void setupScene();
};

#endif /* defined(__PokerKing__ShopScene__) */
