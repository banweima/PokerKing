//
//  Banner.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-10-1.
//
//

#ifndef __PokerKing__Banner__
#define __PokerKing__Banner__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Banner : public CCLayerColor
{
private:
    CC_SYNTHESIZE(CCSprite*, mBgSprite, BgSprite);
    CC_SYNTHESIZE(CCMenuItemSprite*, mBannnerMenuItem, BannerMenuItem);
    CC_SYNTHESIZE(CCMenu*, mBannnerMenu, BannerMenu);
    
    CCSprite * s;
public:
    ~Banner();
    static Banner* create();
    bool init();
    void addBanner(cocos2d::CCLayer * pLayer);
    
private:
    void onBannerClicked(CCNode * pSender);
    void showBannerImage(CCObject * data);
//    void onEnter();
//    void onExit();
    
};
#endif /* defined(__PokerKing__Banner__) */
