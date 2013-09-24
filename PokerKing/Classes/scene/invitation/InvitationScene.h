//
//  InvitationScene.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-13.
//
//

#ifndef __PokerKing__InvitationScene__
#define __PokerKing__InvitationScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class InvitationScene : public CCScene
{
public:
    static InvitationScene* create();
    bool init();
    
    void setupScene();
};



#endif /* defined(__PokerKing__InvitationScene__) */
