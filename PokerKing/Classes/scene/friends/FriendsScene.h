//
//  FriendsScene.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-25.
//
//

#ifndef __PokerKing__FriendsScene__
#define __PokerKing__FriendsScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class FriendsScene : public CCScene
{
public:
    static FriendsScene* create();
    bool init();
    
    void setupScene();
};


#endif /* defined(__PokerKing__FriendsScene__) */
