//
//  MainMenuLayer.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#include "GameRoomLayer.h"
#include "BlackjackScene.h"
#include "CCBUtility.h"
#include "GameInfo.h"
#include "JSONValueUtil.h"
#include "AlertLayer.h"
#include "Loading.h"
#include "GameServerAction.h"
#include "GameKitFactory.h"
#include "Constants.h"
#include "TexasScene.h"
#include "UserInfo.h"
#include "BroadCast.h"
#include "SceneControler.h"
#include "BossBoardLayer.h"

GameRoomLayer::GameRoomLayer()
: mHongKong(NULL)
, mMacau(NULL)
, mLasVegas(NULL)
, mMonteCarlo(NULL)
, mDuration(0.15)
,mUserName(NULL)
, mMaleFrame(NULL)
,mUserLevel(NULL)
,mUserGold(NULL)
,mUserDiamond(NULL)
, mShopButton(NULL)
,mUserMedal(NULL)
{}

GameRoomLayer::~GameRoomLayer()
{
    CC_SAFE_RELEASE(mHongKong);
    CC_SAFE_RELEASE(mMacau);
    CC_SAFE_RELEASE(mLasVegas);
    CC_SAFE_RELEASE(mMonteCarlo);
    CC_SAFE_RELEASE(mUserName);
    CC_SAFE_RELEASE(mUserLevel);
    CC_SAFE_RELEASE(mUserGold);
    CC_SAFE_RELEASE(mUserDiamond);
    CC_SAFE_RELEASE(mMaleFrame);
    CC_SAFE_RELEASE(mShopButton);
    CC_SAFE_RELEASE(mUserMedal);
}

bool GameRoomLayer::init()
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

void GameRoomLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/gameroom.ccbi", "GameRoomLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    mUserName->setString(UserInfo::sharedUserInfo()->getUserName().c_str());
    
    mUserLevel->setString(CCString::createWithFormat("%d",
            UserInfo::sharedUserInfo()->getLevel())->getCString());
    
    mUserGold->setString(CCString::createWithFormat("%d",
            UserInfo::sharedUserInfo()->getGold())->getCString());
    
    mUserDiamond->setString(CCString::createWithFormat("%d",
            UserInfo::sharedUserInfo()->getDiamond())->getCString());

    mUserMedal->setString(CCString::createWithFormat("%d",
                UserInfo::sharedUserInfo()->getMedal())->getCString());
    
    UserInfo::sharedUserInfo()->retrieveAvartaImage(this, callfuncND_selector(GameRoomLayer::getPlayerImage));
    
    getGameRoomInfo();
    
    mShopButton->runAction(CCRepeatForever::create(
        CCRotateBy::create(mDuration, 10)));
    
    BroadCast::sharedBroadCast()->addBCToLayer(this);
}

void GameRoomLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler GameRoomLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHongKongClicked", GameRoomLayer::onHongKongClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMacauClicked", GameRoomLayer::onMacauClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLasVegasClicked", GameRoomLayer::onLasVegasClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMonteCarloClicked", GameRoomLayer::onMonteCarloClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLeadBoardClicked", GameRoomLayer::onLeaderBoarderClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSettingClicked", GameRoomLayer::onSettingClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onShopButtonClicked", GameRoomLayer::onShopButtonClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFriendsClicked", GameRoomLayer::onFriendsClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", GameRoomLayer::onHomeClicked);
    
    return NULL;
}

SEL_CCControlHandler GameRoomLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool GameRoomLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHongKong", CCMenuItemImage *, mHongKong);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMacau", CCMenuItemImage *, mMacau);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLasVegas", CCMenuItemImage *, mLasVegas);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMonteCarlo", CCMenuItemImage *, mMonteCarlo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserName", CCLabelTTF * , mUserName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserLevel", CCLabelTTF * , mUserLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserGold", CCLabelTTF * , mUserGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserDiamond", CCLabelTTF * , mUserDiamond);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserMedal", CCLabelTTF * , mUserMedal);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMaleFrame", CCSprite *, mMaleFrame);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShopButton", CCMenuItemImage *, mShopButton);
    
    return false;
}

void GameRoomLayer::getGameRoomInfo()
{
    Loading::sharedLoading()->addLoadingToLayer(this);
    
    GameServerAction::sharedGameServerAction()->getGameRoomInfo(BlackJack, this, callfuncND_selector(GameRoomLayer::getGameRoomInfo_Done));
}

void GameRoomLayer::getGameRoomInfo_Done(cocos2d::CCNode *pSender, void *data)
{
    Loading::sharedLoading()->removeLoading();
    
    setRoomLevelList();
    
    if(GameInfo::sharedGameInfo()->getCurrentGameType() == BlackJack)
    {
        showUserBoss();
    }
}

void GameRoomLayer::setRoomLevelList()
{
    roomLevelList = GameLevelInfo::sharedGameLevelInfo()->getCurrentRoomLevels();
    roomLevelList->retain();
}

void GameRoomLayer::onHongKongClicked(cocos2d::CCObject *pSender)
{
    if(!checkRoomLevel(Hongkong_R))
    {
        return;
    }
    
    if(mHongKong != NULL) {
        mHongKong->runAction(CCSequence::create(
                                                    CCRotateTo::create(mDuration, 0),
                                                    CCCallFuncN::create(this, callfuncN_selector(GameRoomLayer::goToHongkong)),
                                                    NULL
                                                    ));
    }
}

void GameRoomLayer::onMacauClicked(cocos2d::CCObject *pSender)
{
    if(!checkRoomLevel(Macau_R))
    {
        return;
    }
    
    if(mMacau != NULL) {
        mMacau->runAction(CCSequence::create(
                                                    CCRotateTo::create(mDuration, 0),
                                                    CCCallFuncN::create(this, callfuncN_selector(GameRoomLayer::goToMacau)),
                                                    NULL
                                                    ));
    }
}

void GameRoomLayer::onLasVegasClicked(cocos2d::CCObject *pSender)
{
    if(!checkRoomLevel(LasVegas_R))
    {
        return;
    }
    
    if(mLasVegas != NULL) {
        mLasVegas->runAction(CCSequence::create(
                                                    CCRotateTo::create(mDuration, 0),
                                                    CCCallFuncN::create(this, callfuncN_selector(GameRoomLayer::goToLasVegas)),
                                                    NULL
                                                    ));
    }
}

void GameRoomLayer::onMonteCarloClicked(cocos2d::CCObject *pSender)
{
    if(!checkRoomLevel(MonteCarlo_R))
    {
        return;
    }
    
    if(mMonteCarlo != NULL) {
        mMonteCarlo->runAction(CCSequence::create(
                                                        CCRotateTo::create(mDuration, 0),
                                                        CCCallFuncN::create(this, callfuncN_selector(GameRoomLayer::goToMonteCarlo)),
                                                        NULL
                                                        ));
    }
}

void GameRoomLayer::goToHongkong(CCNode* node)
{
    GameInfo::sharedGameInfo()->setCurrentRoomType(Hongkong_R);
    goToGameScene((RoomLevelInfo *)roomLevelList->objectAtIndex(0));
}

void GameRoomLayer::goToMacau(CCNode* node)
{
    GameInfo::sharedGameInfo()->setCurrentRoomType(Macau_R);
    goToGameScene((RoomLevelInfo *)roomLevelList->objectAtIndex(1));
}

void GameRoomLayer::goToMonteCarlo(CCNode* node)
{
    GameInfo::sharedGameInfo()->setCurrentRoomType(MonteCarlo_R);
    goToGameScene((RoomLevelInfo *)roomLevelList->objectAtIndex(2));
}

void GameRoomLayer::goToLasVegas(CCNode* node)
{
    GameInfo::sharedGameInfo()->setCurrentRoomType(LasVegas_R);
    goToGameScene((RoomLevelInfo *)roomLevelList->objectAtIndex(3));
}



void GameRoomLayer::goToGameScene(RoomLevelInfo *levelInfo)
{
    switch (GameInfo::sharedGameInfo()->getCurrentGameType()) {
        case BlackJack:
        {
        BlackjackScene* pScene = BlackjackScene::create(levelInfo);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, pScene, ccBLACK));
        break;
        }
        case Caribbean:
        {
        CaribbeanScene* pCaribbeanScene = CaribbeanScene::create(levelInfo);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, pCaribbeanScene, ccBLACK));
        break;
        }
        case VideoPoker:
        {
        VideoPokerScene * pVideoPokerScene = VideoPokerScene::create(levelInfo);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, pVideoPokerScene, ccBLACK));
        break;
        }
        case Lottery:
        break;
        
        case Texas:
        {
            TexasScene * pTexasScene = TexasScene::create(levelInfo);
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, pTexasScene, ccBLACK));  
        }
        break;
    }

}


void GameRoomLayer::onHomeClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(MainBoard_Scene);
}

void GameRoomLayer::onLeaderBoarderClicked(cocos2d::CCObject *pSender)
{
//    switch (GameInfo::sharedGameInfo()->getCurrentGameType()) {
//        case BlackJack:
//        [[GameKitFactory sharedGameKitFactory] showLeaderboard: LeaderBoard_BlackjackWinner];
//        break;
//        
//        case Caribbean:
//        [[GameKitFactory sharedGameKitFactory] showLeaderboard: LeaderBoard_CaribbeanWinner];
//        break;
//        
//        case VideoPoker:
//        
//        [[GameKitFactory sharedGameKitFactory] showLeaderboard:LeaderBoard_VideoPokerWinner];
//        break;
//        
//        case Lottery:
//        [[GameKitFactory sharedGameKitFactory] showLeaderboard:LeaderBoard_LotteryWinner];
//        break;
//        
//        default:
//        [[GameKitFactory sharedGameKitFactory] showLeaderboard];
//        break;
//    }
    
    SceneControler::sharedSceneControler()->gotoScene(Rank_Scene);
}

void GameRoomLayer::onShopButtonClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(Shop_Scene);
}

void GameRoomLayer::onFriendsClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(Friends_Scene);
}

void GameRoomLayer::onSettingClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(Setting_Scene);
}

void GameRoomLayer::getPlayerImage()
{    
    CCSprite* sprite = UserInfo::sharedUserInfo()->addAvartaToLayer(this);
    
    sprite->setScale(0.65f * mMaleFrame->getContentSize().width/sprite->getContentSize().width);
    sprite->setPosition(mMaleFrame->getPosition());
    sprite->setAnchorPoint(mMaleFrame->getAnchorPoint());
    
    mMaleFrame->removeFromParentAndCleanup(false);
    this->addChild(mMaleFrame);
}

bool GameRoomLayer::checkRoomLevel(RoomType roomType)
{
    RoomLevelInfo * levelInfo = (RoomLevelInfo *)roomLevelList->objectAtIndex(roomType - 1);
    if(UserInfo::sharedUserInfo()->getGold() >= levelInfo->getMinHand()
    && UserInfo::sharedUserInfo()->getLevel()>= levelInfo->getLevelScore())
    {
        return true;
    }
    else
    {
        CCString * msg = CCString::createWithFormat("对不起，该房间需要%d级，和%d金币。。",levelInfo->getLevelScore(), levelInfo->getMinHand());
    
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"选择房间"
                                    message:[[NSString alloc] initWithCString:msg->getCString() encoding:NSUTF8StringEncoding]
                                   delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];

            [alerView show];
            [alerView release];
        return false;
    }
}

void GameRoomLayer::showUserBoss()
{
    BossBoardLayer::sharedBossBoardLayer()->getBossInfo(this, callfuncND_selector(GameRoomLayer::showUserBoss_Done));
}

void GameRoomLayer::showUserBoss_Done(cocos2d::CCNode *pNode, void *data)
{
    if(GameInfo::sharedGameInfo()->getBossInfoList()->count() > 0)
    {
        BossBoardLayer::sharedBossBoardLayer()->addBossBoardToLayer(this);
    }
}
