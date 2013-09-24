//
//  LoginScene.h
//  blackjack
//
//  Created by Banson Niu on 10/17/12.
//
//

#ifndef __blackjack__LoginScene__
#define __blackjack__LoginScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LoginLayer.h"
#include "AlertLayer.h"

USING_NS_CC;

class LoginScene : public CCScene
{    
public:
    static LoginScene* create();
    bool init();
    void setupScene();

};

#endif /* defined(__blackjack__LoginScene__) */
