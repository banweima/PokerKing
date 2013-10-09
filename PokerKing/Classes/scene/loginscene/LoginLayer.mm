//
//  LoginLayer.cpp
//  blackjack
//
//  Created by Banson Niu on 10/17/12.
//
//

#include "LoginLayer.h"
#include "cocos-ext.h"
#include "GameInfo.h"
#include "MainBoardScene.h"
#include "GameServer.h"
#include "GameServerAction.h"
#include "GameServerResponse.h"
#include "WeiboFactory.h"
#include "GameKitFactory.h"
#include "GameInfo.h"
#include "CCBUtility.h"
#include "Banner.h"

#define LoginLayerTag   123

LoginLayer::LoginLayer()
:mText(NULL)
,mWarning(NULL)
,mWeibo(NULL)
,mBackground(NULL)
{
    
}

LoginLayer::~LoginLayer()
{
    CC_SAFE_RELEASE(mText);
    CC_SAFE_RELEASE(mWarning);
    CC_SAFE_RELEASE(mWeibo);
    CC_SAFE_RELEASE(mBackground);
}

bool LoginLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        this->setupLoginLayer();
        bRet = true;
    } while (0);
	return bRet;
}

void LoginLayer::setupLoginLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/login.ccbi", "LoginLayer", CCLayerLoader::loader(), this);

    this->addChild(node,0,LoginLayerTag);
    
    mBackground->setScaleY(getWinH()/mBackground->getContentSize().height);
    
    mWarning->setVisible(false);
    mText = CCLabelTTF::create("", "Helvetica", 16);
    mText->setColor(ccWHITE);
    mText->setPosition(mWarning->getPosition());
    this->addChild(mText);
    mText->retain();
    
    if([[WeiboFactory sharedWeiboFactory] hasAuthInfo])
    {
        weiboLogin(NULL);
    }
}


void LoginLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler LoginLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onWeiboClicked", LoginLayer::onWeiboClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGameCenterClicked", LoginLayer::gameCenterLogin);
    
    return NULL;
}

SEL_CCControlHandler LoginLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool LoginLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWarning", CCSprite *, mWarning);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWeibo", CCMenuItemImage *, mWeibo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBackground", CCSprite *, mBackground);
    
    return false;
}

void LoginLayer::doLogin()
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    // No explicit autorelease pool needed here.
    // The code runs in background, not strangling
    // the main run loop. 

        switch (GameInfo::sharedGameInfo()->getCurrentSNSType())
        {
            case Weibo:
            {
                for (int i = 0; i < 120; i++)
                {
                    //NSLog(@"%@", [[WeiboFactory sharedWeiboFactory] hasCancelLogin]?@"Yes":@"No");
                    if([[WeiboFactory sharedWeiboFactory] hasDidLogin] || [[WeiboFactory sharedWeiboFactory] hasCancelLogin])
                    {
                        break;
                    }
                    
                    [NSThread sleepForTimeInterval:1];
                }
                
                if(![[WeiboFactory sharedWeiboFactory] hasDidLogin] || [[WeiboFactory sharedWeiboFactory] hasCancelLogin])
                {
                    Loading::sharedLoading()->removeLoading();
                    return;
                }
                
                for (int i = 0; i < 3; i++)
                {
                    if([[WeiboFactory sharedWeiboFactory] hasAuthInfo])
                    {
                        NSLog(@"Weibo auth store!");
                        break;
                    }
                    NSLog(@"----------Weibo auth not store!-----------");
                    [NSThread sleepForTimeInterval:1];
                }
                break;
            }

            case GameCenter:
            {
                for (int i = 0; i < 10; i++)
                {
                    if([[GameKitFactory sharedGameKitFactory] userAuthenticated])
                    {
                        break;
                    }
                    [NSThread sleepForTimeInterval:1];
                }
                break;
            }
        }
        
        
        dispatch_async(dispatch_get_main_queue(), ^{

            bool callSuccess;
            switch (GameInfo::sharedGameInfo()->getCurrentSNSType())
            {
                case Weibo:
                {
                    if(![[WeiboFactory sharedWeiboFactory] hasAuthInfo])
                    {
                        NSLog(@"userAuthenticated false!");
                        mText->setString("新浪微博登录失败，请重试！");
                        mWarning->setVisible(true);
                        return;
                    }
                    
                    callSuccess = GameServerAction::sharedGameServerAction()->doLogin(Weibo, this, callfuncND_selector(LoginLayer::startMainBoard));
                    
                    break;
                }
                
                case GameCenter:
                {
                    if(![[GameKitFactory sharedGameKitFactory] userAuthenticated])
                    {
                        NSLog(@"userAuthenticated false!");
                        mText->setString("GameCenter登录失败，请重试！");
                        mWarning->setVisible(true);
                        return;
                    }
                    
                    callSuccess = GameServerAction::sharedGameServerAction()->doLogin(GameCenter, this, callfuncND_selector(LoginLayer::startMainBoard));
                    
                    
                    break;
                }
            }
            
            if(!callSuccess)
            {
                mText->setString("服务器登录失败，请重试！");
                mWarning->setVisible(true);
            }

        });
            
                    
    });


}


void LoginLayer::startSA(cocos2d::CCObject *object)
{    
    GameInfo::sharedGameInfo()->setEnv(Standalone);
    CCScene *pScene = MainBoardScene::create();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LoginLayer::startMainBoard(cocos2d::CCNode *pSender, void *data)
{
    if((bool)data)
    {
        UserInfo::sharedUserInfo()->uploadUserInfo();
        CCScene *pScene = MainBoardScene::create();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    else
    {
        mText->setString("服务器登录失败，请重试！");
        mWarning->setVisible(true);
        Loading::sharedLoading()->removeLoading();
    }
    
}

void LoginLayer::onWeiboClicked(cocos2d::CCObject *object)
{
    if(mWeibo != NULL) {
        
        mWeibo->runAction(CCSequence::create(
                                    CCScaleTo::create(0.1,1.1),
                                    CCCallFuncN::create(this, callfuncN_selector(LoginLayer::weiboLogin)),
                                    CCScaleTo::create(0.1,0.9),
                                    NULL));
    }

}

void LoginLayer::weiboLogin(cocos2d::CCObject *object)
{
    Loading::sharedLoading()->addLoadingToLayer(this);
    [[WeiboFactory sharedWeiboFactory] loginWeibo];
    GameInfo::sharedGameInfo()->setCurrentSNSType(Weibo);
    doLogin();
}

void LoginLayer::gameCenterLogin(CCObject * object)
{
    [[GameKitFactory sharedGameKitFactory] authenticateLocalUser];
    GameInfo::sharedGameInfo()->setCurrentSNSType(GameCenter);
    doLogin();
    
}
