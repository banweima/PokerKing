//
//  SettingScene.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-7.
//
//

#ifndef __PokerKing__SettingScene__
#define __PokerKing__SettingScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class SettingScene : public CCScene
{
public:
    static SettingScene* create();
    bool init();
    
    void setupScene();
};

#endif /* defined(__PokerKing__SettingScene__) */
