//
//  LotteryLayer.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 13-4-8.
//
//

#include "LotteryLayer.h"
#include "CCBUtility.h"
#include "Constants.h"
#include "CardDeck.h"
#include "HttpImageLoader.h"
#include "platform.h"
#include "SimpleAudioEngine.h"
#include "MainBoardScene.h"
#import <AudioToolbox/AudioToolbox.h>



LotteryLayer::LotteryLayer()
: mRedBalls(NULL)
, mBlueBalls(NULL)
{}


LotteryLayer::~LotteryLayer()
{
    CC_SAFE_RELEASE_NULL(mRedBalls);
    CC_SAFE_RELEASE_NULL(mBlueBalls);

}

bool LotteryLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        this->setupLayer();
        
        bRet = true;
    } while (0);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("guitar3.wav", true);
    
    return bRet;
}

void LotteryLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/lottery.ccbi", "LotteryLayer", CCLayerLoader::loader(), this);
    this->addChild(node);
        
    this->setAccelerometerEnabled(true);
}

void LotteryLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
    
}


SEL_MenuHandler LotteryLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFriendsClicked", LotteryLayer::onFriendsClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRankClicked", LotteryLayer::onRankClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSettingClicked", LotteryLayer::onSettingClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", LotteryLayer::onHomeClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStartClicked", LotteryLayer::onStartClicked);
    return NULL;
}

SEL_CCControlHandler LotteryLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool LotteryLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRedBalls", CCLabelTTF *, mRedBalls);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBlueBalls", CCLabelTTF *, mBlueBalls);
    return false;
}

void LotteryLayer::onFriendsClicked(CCObject * pSender)
{
    gotoOtherScene(Friends_Scene);
}

void LotteryLayer::onRankClicked(CCObject * pSender)
{
    gotoOtherScene(Rank_Scene);
}

void LotteryLayer::onHomeClicked(CCObject * pSender)
{
    gotoOtherScene(MainBoard_Scene);
}

void LotteryLayer::onSettingClicked(CCObject * pSender)
{
    gotoOtherScene(Setting_Scene);
}

void LotteryLayer::gotoOtherScene(GameScene otherScene)
{
    SceneControler::sharedSceneControler()->gotoScene(otherScene);
}


void LotteryLayer::didAccelerate(CCAcceleration *pAccelerationValue)
{
    double x = pAccelerationValue->x;
    double y = pAccelerationValue->y;
    double z = pAccelerationValue->z;
    
    
    
    if((x > 2 || x < -2) ||
      (y > 2 || y < -2) ||
      (z > 2 || z < -2))
      {
        this->onStartClicked(NULL);
      }
}

void LotteryLayer::onStartClicked(cocos2d::CCObject *pSender)
{
    srand((unsigned)time(0));
    
    mRedBalls->setString(CCString::createWithFormat("%d %d %d %d %d %d",
    rand()%36+1,rand()%36+1,rand()%36+1,rand()%36+1,rand()%36+1,rand()%36+1)->getCString());
    
    mBlueBalls->setString(CCString::createWithFormat("%d",
    rand()%16+1)->getCString());
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}
