//
//  MainBoardLayer.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 13-3-23.
//
//

#include "MainBoardLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "OCMessager.h"
#include "UIDevice+IdentifierAddition.h"

#endif

#include "GameInfo.h"

#include "RankingScene.h"
#include "CCBUtility.h"

#include "GameRoomScene.h"
#include "CaribbeanScene.h"
#include "VideoPokerScene.h"
#include "LotteryScene.h"
#include "NotificationFactory.h"
#include "GameKitFactory.h"
#include "StoreKitFactory.h"
#include "WeiboFactory.h"
#include "SettingScene.h"
#include "UserInfo.h"
#include "WhiteBoardLayer.h"
#include "BossBoardLayer.h"
#include "SceneControler.h"


static int isFirstTimeEnter=0;

MainBoardLayer::MainBoardLayer()
: mBlackJack(NULL)
, mCaribbean(NULL)
, mVideoPoker(NULL)
, mLottery(NULL)
, mDuration(0.15)
, mShopButton(NULL)
, mMaleFrame(NULL)
,mUserName(NULL)
,mUserLevel(NULL)
,mUserGold(NULL)
,mUserDiamond(NULL)
,mUserMedal(NULL)
{}

MainBoardLayer::~MainBoardLayer()
{
    CC_SAFE_RELEASE(mBlackJack);
    CC_SAFE_RELEASE(mCaribbean);
    CC_SAFE_RELEASE(mVideoPoker);
    CC_SAFE_RELEASE(mLottery);
    CC_SAFE_RELEASE(mShopButton);
    CC_SAFE_RELEASE(mMaleFrame);
    CC_SAFE_RELEASE(mUserName);
    CC_SAFE_RELEASE(mUserLevel);
    CC_SAFE_RELEASE(mUserGold);
    CC_SAFE_RELEASE(mUserDiamond);
    CC_SAFE_RELEASE(mUserMedal);
}

bool MainBoardLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        this->setupLayer();
        
        bRet = true;
    } while (0);
    
	return bRet;
}

void MainBoardLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/mainboard.ccbi", "MainBoardLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    isFirstTimeEnter++;
    
    mShopButton->runAction(CCRepeatForever::create(
        CCRotateBy::create(mDuration, 10)));
    
    showUserInfo(NULL, (void *) true);
    
    BroadCast::sharedBroadCast()->addBCToLayer(this);
    

    
    if(isFirstTimeEnter < 2)
    {
        UserInfo::sharedUserInfo()->retrieveFriendsList();
        
        WhiteBoardLayer * wbLayer =  WhiteBoardLayer::sharedWhiteBoardLayer();
        wbLayer->getEventsInfo();
        wbLayer->addWhiteBoardToLayer(this);
    }
    else
    {
        GameServerAction::sharedGameServerAction()->getUserInfo(this, callfuncND_selector(MainBoardLayer::showUserInfo));
    }
}

void MainBoardLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler MainBoardLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBlackJackClicked", MainBoardLayer::onBlackJackClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCaribbeanClicked", MainBoardLayer::onCaribbeanClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onVideoPokerClicked", MainBoardLayer::onVideoPokerClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLotteryClicked", MainBoardLayer::onLotteryClicked);

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRankClicked", MainBoardLayer::onLeaderBoarderClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSettingClicked", MainBoardLayer::onSettingClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onShopButtonClicked", MainBoardLayer::onShopButtonClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFriendsClicked", MainBoardLayer::onFriendsClicked);
    
    return NULL;
}

SEL_CCControlHandler MainBoardLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool MainBoardLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBlackJack", CCMenuItemImage *, mBlackJack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCaribbean", CCMenuItemImage *, mCaribbean);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mVideoPoker", CCMenuItemImage *, mVideoPoker);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLottery", CCMenuItemImage *, mLottery);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShopButton", CCMenuItemImage *, mShopButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMaleFrame", CCSprite *, mMaleFrame);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserName", CCLabelTTF * , mUserName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserLevel", CCLabelTTF * , mUserLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserGold", CCLabelTTF * , mUserGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserDiamond", CCLabelTTF * , mUserDiamond);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserMedal", CCLabelTTF * , mUserMedal);
    
    return false;
}

void MainBoardLayer::onBlackJackClicked(cocos2d::CCObject *pSender)
{
    if(mBlackJack != NULL) {
        
        mBlackJack->runAction(CCSequence::create(
                                    //CCBlink::create(mDuration, 10),
                                    CCCallFuncN::create(this, callfuncN_selector(MainBoardLayer::goToBlackjack)),
                                    NULL));
        
        NotificationFactory::CancelAllNotification();
//        mBlackJack->runAction(CCRepeatForever::create(
//        CCRotateBy::create(mDuration, 10)));
        
    }
    
}

void MainBoardLayer::onCaribbeanClicked(cocos2d::CCObject *pSender)
{
    if(mCaribbean != NULL) {
    
//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    //iOS代码
//    [OCMessager testLog];
//    [OCMessager testLogWithStr:[[UIDevice currentDevice] uniqueGlobalDeviceIdentifier] ];
//    [OCMessager hMessageBox:[[UIDevice currentDevice] uniqueDeviceIdentifier]  title:@"Himi"];
//    #else
//        //Android代码
//    #endif


    
//    NotificationData * nfData = new NotificationData();
//    nfData->mMinute = 1;
//    nfData->mFrequency = Hour;
//    nfData->mBody = "Just for test";
//    nfData->mTime = "23:30:00";
//    NotificationFactory::RegisterLocalNotification(nfData);
    
    mCaribbean->runAction(CCSequence::create(
                                    //CCBlink::create(mDuration, 10),
                                    CCCallFuncN::create(this, callfuncN_selector(MainBoardLayer::goToCaribbean)),
                                    NULL));
    }
    
}

void MainBoardLayer::onVideoPokerClicked(cocos2d::CCObject *pSender)
{
    if(mVideoPoker != NULL) {
        
        mVideoPoker->runAction(CCSequence::create(
                                    //CCBlink::create(mDuration, 10),
                                    CCScaleTo::create(mDuration,1.1),
                                    CCCallFuncN::create(this, callfuncN_selector(MainBoardLayer::goToVideoPoker)),
                                    NULL));
    }
}

void MainBoardLayer::onLotteryClicked(cocos2d::CCObject *pSender)
{
    if(mLottery != NULL) {
        
        mLottery->runAction(CCSequence::create(
                                    //CCBlink::create(mDuration, 10),
                                    CCScaleTo::create(mDuration,1.1),
                                    CCCallFuncN::create(this, callfuncN_selector(MainBoardLayer::goToInvitation)),//Just goto invitation now
                                    NULL));
    }
}

void MainBoardLayer::goToBlackjack(CCNode *pSender)
{
    GameInfo::sharedGameInfo()->setCurrentGameType(BlackJack);
    
    //Prepare the card for the game
    CardDeck::resetCardDeck();
    CardDeck::sharedCardDeck(4);
    
    Loading* loading = Loading::sharedLoading();
    loading->addLoadingToLayer(this);
    
    SceneControler::sharedSceneControler()->gotoScene(GameRoom_Scene);
}

void MainBoardLayer::goToCaribbean(CCNode *pSender)
{
    //GameInfo::sharedGameInfo()->setCurrentGameType(Caribbean);
    
//    GameInfo::sharedGameInfo()->setCurrentGameType(Texas);
//    
//    //Prepare the card for the game
//    CardDeck::resetCardDeck();
//    CardDeck::sharedCardDeck(1);
//
//    Loading* loading = Loading::sharedLoading();
//    loading->addLoadingToLayer(this);
//    
//    SceneControler::sharedSceneControler()->gotoScene(GameRoom_Scene);

//    AlertLayer * shareAlert = AlertLayer::create("大厅", "德州扑克暂未开放，敬请期待！" , false, NULL, NULL);
//            this->addChild(shareAlert, Child_Order_Top);
    SceneControler::sharedSceneControler()->gotoScene(Task_Scene);
}

void MainBoardLayer::goToVideoPoker(CCNode *pSender)
{
    GameInfo::sharedGameInfo()->setCurrentGameType(VideoPoker);
    //Prepare the card for the game
    CardDeck::resetCardDeck();
    CardDeck::sharedCardDeck(1);
    
    Loading* loading = Loading::sharedLoading();
    loading->addLoadingToLayer(this);
    
    SceneControler::sharedSceneControler()->gotoScene(GameRoom_Scene);
}

void MainBoardLayer::goToLottery(CCNode *pSender)
{
    Loading* loading = Loading::sharedLoading();
    loading->addLoadingToLayer(this);
    
    SceneControler::sharedSceneControler()->gotoScene(Lottery_Scene);
}

void MainBoardLayer::goToInvitation(CCNode *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(Invitation_Scene);
}


void MainBoardLayer::onLeaderBoarderClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(Rank_Scene);
}

void MainBoardLayer::onSettingClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(Setting_Scene);

}

void MainBoardLayer::getPlayerImage(CCNode* node, void* data)
{    
    CCSprite* sprite = UserInfo::sharedUserInfo()->addAvartaToLayer(this);
    
    sprite->setScale(0.65f * mMaleFrame->getContentSize().width/sprite->getContentSize().width);
    sprite->setPosition(mMaleFrame->getPosition());
    sprite->setAnchorPoint(mMaleFrame->getAnchorPoint());
    
    mMaleFrame->getParent()->removeChild(mMaleFrame, false);
    this->addChild(mMaleFrame,Child_Order_Mid);
}

void MainBoardLayer::onShopButtonClicked(cocos2d::CCObject *object)
{
    SceneControler::sharedSceneControler()->gotoScene(Shop_Scene);
}

void MainBoardLayer::showUserInfo(cocos2d::CCNode *pNode, void *data)
{
    if((bool)data)
    {
        CCLog("User Name: %s",UserInfo::sharedUserInfo()->getUserName().c_str());
        mUserName->setString(UserInfo::sharedUserInfo()->getUserName().c_str());
        
        mUserLevel->setString(CCString::createWithFormat("%d",
                UserInfo::sharedUserInfo()->getLevel())->getCString());
        
        mUserGold->setString(CCString::createWithFormat("%d",
                UserInfo::sharedUserInfo()->getGold())->getCString());
        
        mUserDiamond->setString(CCString::createWithFormat("%d",
                UserInfo::sharedUserInfo()->getDiamond())->getCString());
        
        mUserMedal->setString(CCString::createWithFormat("%d",
                UserInfo::sharedUserInfo()->getMedal())->getCString());
        
        UserInfo::sharedUserInfo()->retrieveAvartaImage(this, callfuncND_selector(MainBoardLayer::getPlayerImage));
    }
}



//void MainBoardLayer::showUserBoss(cocos2d::CCNode *pNode, void *data)
//{
//    BossBoardLayer::sharedBossBoardLayer()->getBossInfo(this, callfuncND_selector(MainBoardLayer::showUserBoss_Done));
//}
//
//void MainBoardLayer::showUserBoss_Done(cocos2d::CCNode *pNode, void *data)
//{
//    if(GameInfo::sharedGameInfo()->getBossInfoList()->count() > 0)
//    {
//        BossBoardLayer::sharedBossBoardLayer()->addBossBoardToLayer(this);
//    }
//    else
//    {
//        SceneControler::sharedSceneControler()->gotoScene(GameRoom_Scene);
//    }
//    Loading::sharedLoading()->removeLoading();
//}


void MainBoardLayer::onFriendsClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(Friends_Scene);
}