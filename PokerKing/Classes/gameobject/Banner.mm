//
//  Banner.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-10-1.
//
//

#include "Banner.h"
#include "Constants.h"
#include "GameInfo.h"
#include "ImageController.h"

Banner::~Banner()
{
    CC_SAFE_RELEASE(mBgSprite);

}

Banner* Banner::create()
{
    Banner * banner=new Banner();
    
	if (banner && banner->init())
	{
		banner->autorelease();
		return banner;
	}
    
	CC_SAFE_DELETE(banner);
	return NULL;
}

bool Banner::init()
{
    bool bRet = false;
    do
    {

        CC_BREAK_IF(!CCLayerColor::init());
        
        ImageController * imageController = new ImageController();
            imageController->retrieveAvartaImage(GameInfo::sharedGameInfo()->getBannerImageUrl(), this, callfuncO_selector(Banner::showBannerImage));
            
        
        bRet = true;
    } while (0);
	return bRet;
}

void Banner::onBannerClicked(CCNode * pSender)
{
    NSString * value = [[NSString alloc] initWithFormat:@"%s", GameInfo::sharedGameInfo()->getBannerJumpUrl().c_str() ];
    [[UIApplication sharedApplication]openURL:[NSURL URLWithString:value]];
}

void Banner::showBannerImage(cocos2d::CCObject *data)
{
    if(data)
    {
        setBgSprite((CCSprite *) data);
        int h = getWinH();
        int w = getWinW();
        mBgSprite->setPosition(ccp(0, h));
        mBgSprite->setAnchorPoint(ccp(0,1));
        mBgSprite->setScaleX(w/mBgSprite->getContentSize().width);
        mBgSprite->setScaleY((h-480)/mBgSprite->getContentSize().height);
        this->addChild(mBgSprite,-200);
        
        s = CCSprite::createWithSpriteFrameName("main_top_board");
    
        mBannnerMenuItem = CCMenuItemSprite::create(s, s, s, this, menu_selector(Banner::onBannerClicked));
        mBannnerMenuItem->retain();
        mBannnerMenuItem->setAnchorPoint(ccp(0,1));
        mBannnerMenuItem->setOpacity(0);
        mBannnerMenuItem->setScaleY((h-480)/mBannnerMenuItem->getContentSize().height);
        
        mBannnerMenu = CCMenu::create(mBannnerMenuItem, NULL);

        mBannnerMenu->setPosition(ccp(0,h));
        
        mBannnerMenu->retain();
        this->addChild(mBannnerMenu);
    }
}