//
//  BossBoardLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-19.
//
//

#include "BossBoardLayer.h"
#include "CCBUtility.h"
#include "GameRoomScene.h"
#include "CardDeck.h"
#include "Loading.h"
#include "BlackjackScene.h"

static BossBoardLayer *pBossBoardLayer = NULL;

BossBoardLayer* BossBoardLayer::sharedBossBoardLayer(void)
{
    if (!pBossBoardLayer)
    {
        pBossBoardLayer = new BossBoardLayer();
        
        if(pBossBoardLayer && pBossBoardLayer->init())
        {
            
        }
    }
    
    return pBossBoardLayer;
}


BossBoardLayer::BossBoardLayer()
:m_bTouchedMenu(false)
,mContent(NULL)
,mMenu(NULL)
,mLabel1(NULL)
,mLabel2(NULL)
,mLabel3(NULL)
,mLabel4(NULL)
,mLabel5(NULL)
,mMenuGo1(NULL)
,mMenuGo2(NULL)
,mMenuGo3(NULL)
,mMenuGo4(NULL)
,mMenuGo5(NULL)

{}

BossBoardLayer::~BossBoardLayer()
{
    CC_SAFE_RELEASE(mContent);
    CC_SAFE_RELEASE(mMenu);
}

bool BossBoardLayer::init()
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

void BossBoardLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/BossList.ccbi", "BossListLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    this->setTouchEnabled(true);
    
    mLabel1->setVisible(false);
    mLabel2->setVisible(false);
    mLabel3->setVisible(false);
    mLabel4->setVisible(false);
    mLabel5->setVisible(false);
    
    mMenuGo1->setVisible(false);
    mMenuGo2->setVisible(false);
    mMenuGo3->setVisible(false);
    mMenuGo4->setVisible(false);
    mMenuGo5->setVisible(false);
    
    hasBoss1 = false;
    hasBoss2 = false;
    hasBoss3 = false;
    hasBoss4 = false;
    hasBoss5 = false;
}

void BossBoardLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler BossBoardLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCancelClicked", BossBoardLayer::onCancelClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuGo1", BossBoardLayer::onBossSelected1);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuGo2", BossBoardLayer::onBossSelected2);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuGo3", BossBoardLayer::onBossSelected3);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuGo4", BossBoardLayer::onBossSelected4);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuGo5", BossBoardLayer::onBossSelected5);

    
    return NULL;
}

SEL_CCControlHandler BossBoardLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool BossBoardLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenu", CCMenu * , mMenu);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabel1", CCLabelTTF * , mLabel1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabel2", CCLabelTTF * , mLabel2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabel3", CCLabelTTF * , mLabel3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabel4", CCLabelTTF * , mLabel4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabel5", CCLabelTTF * , mLabel5);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuGo1", CCMenuItemImage * , mMenuGo1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuGo2", CCMenuItemImage * , mMenuGo2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuGo3", CCMenuItemImage * , mMenuGo3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuGo4", CCMenuItemImage * , mMenuGo4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuGo5", CCMenuItemImage * , mMenuGo5);


    return false;
}



void BossBoardLayer::onCancelClicked(cocos2d::CCObject *pSender)
{
    pBossBoardLayer->removeFromParentAndCleanup(true);
}

BossBoardLayer * BossBoardLayer::addBossBoardToLayer(cocos2d::CCLayer *parentLayer)
{
    pBossBoardLayer->removeFromParentAndCleanup(false);
    
    parentLayer->addChild(pBossBoardLayer, Child_Order_Mid + 1);

    return pBossBoardLayer;
}


void BossBoardLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(pBossBoardLayer, kCCMenuHandlerPriority - 1, true);
    CCLayer::registerWithTouchDispatcher(); 
}

bool BossBoardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
    return true;
}

void BossBoardLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void BossBoardLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void BossBoardLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void BossBoardLayer::getBossInfo()
{
    getBossInfo(NULL, NULL);
}

void BossBoardLayer::getBossInfo(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    GameServerAction::sharedGameServerAction()->showUserBoss(BossStatus_Active, this, callfuncND_selector(BossBoardLayer::getBossInfo_Done));
}


void BossBoardLayer::getBossInfo_Done(cocos2d::CCObject *pNode, void *data)
{
    if((bool) data)
    {
        
        CCArray * bossInfoList = GameInfo::sharedGameInfo()->getBossInfoList();
        if(bossInfoList)
        {
            int bossCount = bossInfoList->count();
            RaidBossInfo * bossInfo = NULL;
            std::string bossString = "";
            
            if(bossCount > 0)
            {
                hasBoss1 = true;
                bossInfo = (RaidBossInfo *) bossInfoList->objectAtIndex(0);
                bossString = CCString::createWithFormat("%s (%d/%d)", bossInfo->getOnlineBossName().c_str(), bossInfo->getCurrentHP(), bossInfo->getMaxHP())->getCString();
                mLabel1->setString(bossString.c_str());
                mLabel1->setVisible(true);
                mMenuGo1->setVisible(true);
            }
            
            if (bossCount > 1)
            {
                hasBoss2 = true;
                bossInfo = (RaidBossInfo *) bossInfoList->objectAtIndex(1);
                bossString = CCString::createWithFormat("%s (%d/%d)", bossInfo->getOnlineBossName().c_str(), bossInfo->getCurrentHP(), bossInfo->getMaxHP())->getCString();
                mLabel2->setString(bossString.c_str());
                mLabel2->setVisible(true);
                mMenuGo2->setVisible(true);
            }
            
            if (bossCount > 2)
            {
                hasBoss3 = true;
                bossInfo = (RaidBossInfo *) bossInfoList->objectAtIndex(2);
                bossString = CCString::createWithFormat("%s (%d/%d)", bossInfo->getOnlineBossName().c_str(), bossInfo->getCurrentHP(), bossInfo->getMaxHP())->getCString();
                mLabel3->setString(bossString.c_str());
                mLabel3->setVisible(true);
                mMenuGo3->setVisible(true);
            }
            
            if (bossCount > 3)
            {
                hasBoss4 = true;
                bossInfo = (RaidBossInfo *) bossInfoList->objectAtIndex(3);
                bossString = CCString::createWithFormat("%s (%d/%d)", bossInfo->getOnlineBossName().c_str(), bossInfo->getCurrentHP(), bossInfo->getMaxHP())->getCString();
                mLabel4->setString(bossString.c_str());
                mLabel4->setVisible(true);
                mMenuGo4->setVisible(true);
            }
            
            if (bossCount > 4)
            {
                hasBoss5 = true;
                bossInfo = (RaidBossInfo *) bossInfoList->objectAtIndex(4);
                bossString = CCString::createWithFormat("%s (%d/%d)", bossInfo->getOnlineBossName().c_str(), bossInfo->getCurrentHP(), bossInfo->getMaxHP())->getCString();
                mLabel5->setString(bossString.c_str());
                mLabel5->setVisible(true);
                mMenuGo5->setVisible(true);
            }
            
        }

    }
    
    if (mTarget && mCallFuncND) {
            (mTarget->*mCallFuncND)(NULL,data);
        }
    
}

void BossBoardLayer::onBossSelected1(cocos2d::CCObject *pSender)
{
    if(hasBoss1)
    {
        BattleInfo::sharedBattleInfo()->setBattleType(BossBattle);
        BattleInfo::sharedBattleInfo()->setRaidBoss((RaidBossInfo *)GameInfo::sharedGameInfo()->getBossInfoList()->objectAtIndex(0));
        gotoGame();
    }
}

void BossBoardLayer::onBossSelected2(cocos2d::CCObject *pSender)
{
    if(hasBoss2)
    {
        BattleInfo::sharedBattleInfo()->setBattleType(BossBattle);
        BattleInfo::sharedBattleInfo()->setRaidBoss((RaidBossInfo *)GameInfo::sharedGameInfo()->getBossInfoList()->objectAtIndex(1));
        gotoGame();
    }
}

void BossBoardLayer::onBossSelected3(cocos2d::CCObject *pSender)
{
    if(hasBoss3)
    {
        BattleInfo::sharedBattleInfo()->setBattleType(BossBattle);
        BattleInfo::sharedBattleInfo()->setRaidBoss((RaidBossInfo *)GameInfo::sharedGameInfo()->getBossInfoList()->objectAtIndex(2));
        gotoGame();
    }
}

void BossBoardLayer::onBossSelected4(cocos2d::CCObject *pSender)
{
    if(hasBoss4)
    {
        BattleInfo::sharedBattleInfo()->setBattleType(BossBattle);
        BattleInfo::sharedBattleInfo()->setRaidBoss((RaidBossInfo *)GameInfo::sharedGameInfo()->getBossInfoList()->objectAtIndex(3));
        gotoGame();
    }
}

void BossBoardLayer::onBossSelected5(cocos2d::CCObject *pSender)
{
    if(hasBoss5)
    {
        BattleInfo::sharedBattleInfo()->setBattleType(BossBattle);
        BattleInfo::sharedBattleInfo()->setRaidBoss((RaidBossInfo *)GameInfo::sharedGameInfo()->getBossInfoList()->objectAtIndex(4));
        gotoGame();
    }
}

void BossBoardLayer::gotoGame()
{
    GameInfo::sharedGameInfo()->setCurrentGameType(BlackJack);
    
    //Prepare the card for the game
    CardDeck::resetCardDeck();
    CardDeck::sharedCardDeck(4);

    Loading::sharedLoading()->addLoadingToLayer(this);
    
    GameServerAction::sharedGameServerAction()->getGameRoomInfo(BlackJack, this, callfuncND_selector(BossBoardLayer::gotoGame_Done));
}

void BossBoardLayer::gotoGame_Done(cocos2d::CCNode *pNode, void *data)
{
    if((bool)data)
    {
//        GameRoomLayer *gameRoomLayer = GameRoomLayer::create();
//        gameRoomLayer->setRoomLevelList();
        
        BlackjackScene* pScene = BlackjackScene::create((RoomLevelInfo *)GameLevelInfo::sharedGameLevelInfo()->getCurrentRoomLevels()->objectAtIndex(BattleInfo::sharedBattleInfo()->getRaidBoss()->getBossType() - 1));
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, pScene, ccBLACK));
//        switch (BattleInfo::sharedBattleInfo()->getRaidBoss()->getBossType())
//        {
//            case 1:
//            if(gameRoomLayer->checkRoomLevel(Hongkong_R))
//            {
//               gameRoomLayer->goToHongkong(NULL);
//               pBossBoardLayer->removeFromParentAndCleanup(true);
//            }
//            break;
//            case 2:
//            if(gameRoomLayer->checkRoomLevel(Macau_R))
//            {
//                gameRoomLayer->goToMacau(NULL);
//                pBossBoardLayer->removeFromParentAndCleanup(true);
//            }
//            break;
//            case 3:
//            if(gameRoomLayer->checkRoomLevel(MonteCarlo_R))
//            {
//                gameRoomLayer->goToMonteCarlo(NULL);
//                pBossBoardLayer->removeFromParentAndCleanup(true);
//            }
//            break;
//            case 4:
//            if(gameRoomLayer->checkRoomLevel(LasVegas_R))
//            {
//                gameRoomLayer->goToLasVegas(NULL);
//                pBossBoardLayer->removeFromParentAndCleanup(true);
//            }
//            break;
//        }
    
    }
    
    Loading::sharedLoading()->removeLoading();

}
