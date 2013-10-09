//
//  RankingLayer.cpp
//  blackjack
//
//  Created by Banson Niu on 9/12/12.
//
//

#include "RankingLayer.h"
#include "CCBUtility.h"
#include "SceneControler.h"
#include "UserInfoLayer.h"
#include "GameServerAction.h"
#include "Loading.h"
#include "SimpleUserInfo.h"
#include "RankInfo.h"
#include "Banner.h"

RankingLayer::RankingLayer()
: mToday(NULL)
, mAll(NULL)
, pTodayRanking(NULL)
, pAllRanking(NULL)
, m_pTodayListView(NULL)
, m_pAllListView(NULL)
, isTodayRank(false)
, mWarning(NULL)
, mSimpleUserInfo(NULL)
, etListCount(0)
{}

RankingLayer::~RankingLayer()
{
    CC_SAFE_RELEASE(mToday);
    CC_SAFE_RELEASE(mAll);
    CC_SAFE_RELEASE(pTodayRanking);
    CC_SAFE_RELEASE(pAllRanking);
    CC_SAFE_RELEASE(m_pAllListView);
    CC_SAFE_RELEASE(m_pTodayListView);
    CC_SAFE_RELEASE(mWarning);
}

bool RankingLayer::init()
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

void RankingLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/rank.ccbi", "RankLayer", CCLayerLoader::loader(), this);
    this->addChild(node);
    
    int wh = getWinH();
    if(wh>480)
    {
        Banner * banner = Banner::create();
        banner->retain();
        this->addChild(banner,-100);
    }
    
    mWarning->setVisible(false);
    
    onTodayClicked(NULL);
    
}

void RankingLayer::addListView()
{
    if(isTodayRank)
    {
        if(m_pAllListView)
        {
            m_pAllListView->setVisible(false);
        }
        
        if(!m_pTodayListView)
        {        
            m_pTodayListView = CCListView::viewWithMode(CCListViewModeVertical);
            m_pTodayListView->retain();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            CCSize listSize = CCSizeMake(winSize.width, mAll->getPositionY() - 20);
    
            m_pTodayListView->setContentSize(listSize);
            m_pTodayListView->setDelegate(this);
            m_pTodayListView->setAnchorPoint(ccp(0,0));
            m_pTodayListView->setPosition(ccp(0, 0));
            m_pTodayListView->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
            this->addChild(m_pTodayListView);
        }
        m_pTodayListView->setVisible(true);
    }
    else
    {
        if(m_pTodayListView)
        {
            m_pTodayListView->setVisible(false);
        }
        
        if(!m_pAllListView)
        {     
            m_pAllListView = CCListView::viewWithMode(CCListViewModeVertical);
            m_pAllListView->retain();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            CCSize listSize = CCSizeMake(winSize.width, mAll->getPositionY() - 20);
    
            m_pAllListView->setContentSize(listSize);
            m_pAllListView->setDelegate(this);
            m_pAllListView->setPosition(ccp(0, 0));
            m_pAllListView->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
            this->addChild(m_pAllListView);
        }
        
        m_pAllListView->setVisible(true);
    }


}

void RankingLayer::visit()
{
    CCLayer::visit();
//    if (m_bFresh) {
//        m_pListView->reload();
//        m_bFresh = false;
//    }
}

void RankingLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler RankingLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAllClicked", RankingLayer::onAllClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTodayClicked", RankingLayer::onTodayClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", RankingLayer::onHomeClicked);
    return NULL;
}

SEL_CCControlHandler RankingLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool RankingLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mToday", CCMenuItemImage *, mToday);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAll", CCMenuItemImage *, mAll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWarning", CCLabelTTF *, mWarning);
    
    return false;
}

void RankingLayer::CCListView_numberOfCells(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCLOG("ListViewDemoLayer::CCListView_numberOfCells");
    if(isTodayRank)
    {
        data->nNumberOfRows = pTodayRanking->count();
    }
    else
    {
        data->nNumberOfRows = pAllRanking->count();
    }
}

void RankingLayer::CCListView_cellForRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCSize listSize;
    
    if(isTodayRank)
    {
        listSize = m_pTodayListView->getContentSize();
    }
    else
    {
        listSize = m_pAllListView->getContentSize();
    }
    
    CCSize cellSize = CCSizeMake(listSize.width, listSize.height/5);
    
    CCListViewCell *cell = CCListViewCell::node();
    cell->setOpacity(0);
    cell->setContentSize(cellSize);
    cell->setSelectionColor(ccc4(200, 100, 150, 0)); //set invisible back color after selected

    data->cell = cell;
    
    std::string cellValue = "";
    
    if(isTodayRank)
    {
        cellValue = CCString::createWithFormat("%s    %d", ((SimpleUserInfo *)pTodayUsers->objectAtIndex(data->nRow))->getUserName().c_str(),((RankInfo *) pTodayRanking->objectAtIndex(data->nRow))->getWinMoney())->getCString();
    }
    else
    {
        cellValue = CCString::createWithFormat("%s    %d",((SimpleUserInfo *)pAllUsers->objectAtIndex(data->nRow))->getUserName().c_str(), ((RankInfo *) pAllRanking->objectAtIndex(data->nRow))->getWinMoney())->getCString();

    }
    
    CCSprite *bgSprite = CCSprite::createWithSpriteFrameName("rank_item1");
    
    bgSprite->setPosition(ccp(cellSize.width/2, cellSize.height/2));
    bgSprite->setScaleX(cellSize.width * 0.9/bgSprite->getContentSize().width);
    bgSprite->setScaleY(cellSize.height * 0.85 /bgSprite->getContentSize().height);
    cell->addChild(bgSprite);
    
    float fScale = 0;
    CCSprite * frameSprite = CCSprite::createWithSpriteFrameName("friend_item_frame1");
    frameSprite->setAnchorPoint(ccp(0,0.5));
    
    fScale = bgSprite->getContentSize().height / frameSprite->getContentSize().height;
    frameSprite->setScale(fScale);
    frameSprite->setPosition(ccp(cellSize.width * 0.05 + (bgSprite->getPositionX() - bgSprite->getContentSize().width/2), cellSize.height/2));

    CCSprite * playerImage = NULL;
    if (isTodayRank) {
      
        playerImage = ((SimpleUserInfo *)pTodayUsers->objectAtIndex(data->nRow))->getAvartaIamge();
    }
    else
    {
        playerImage = ((SimpleUserInfo *)pAllUsers->objectAtIndex(data->nRow))->getAvartaIamge();

    }

    
    if(playerImage)
    {
        playerImage->setAnchorPoint(ccp(0,0.5));
        playerImage->setScale(bgSprite->getContentSize().height/playerImage->getContentSize().height);
        playerImage->setPosition(frameSprite->getPosition());
        
        playerImage->removeFromParentAndCleanup(false);
        
        cell->addChild(playerImage);
    }
    
    cell->addChild(frameSprite);
    
    CCLabelTTF *cellLabel = CCLabelTTF::create(cellValue.c_str(), "Arial", 18);
    
    cellLabel->setAnchorPoint(ccp(0,0.5));
    cellLabel->setPosition(ccp(frameSprite->getPositionX() + frameSprite->getContentSize().width * 1.2 * fScale, frameSprite->getPositionY()));
    
    cell->addChild(cellLabel);
    
    CCLabelTTF * rankLabel = CCLabelTTF::create(CCString::createWithFormat("%d", data->nRow + 1)->getCString(), "Arial", 18);
    rankLabel->setAnchorPoint(ccp(0,0.5));
    rankLabel->setPosition(ccp(frameSprite->getPositionX() - rankLabel->getContentSize().width * 1.5, frameSprite->getPositionY()));
    
    cell->addChild(rankLabel);
}

void RankingLayer::CCListView_didClickCellAtRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCLOG("Item %d Clicked", data->nRow);
    SimpleUserInfo * sc = NULL;
    if(isTodayRank)
    {
        sc = (SimpleUserInfo *)pTodayUsers->objectAtIndex(data->nRow);
    }
    else
    {
        sc = (SimpleUserInfo *)pAllUsers->objectAtIndex(data->nRow);
    }
    
    UserInfoLayer::sharedUserInfoLayer()->addUserInfoLayerToLayer(this, sc);
}

void RankingLayer::CCListView_didScrollToRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
}

void RankingLayer::onHomeClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->goBackScene();
}

void RankingLayer::onAllClicked(cocos2d::CCObject *pSender)
{
    isTodayRank = false;
    mWarning->setVisible(false);
    mWarning->setString("");
    Loading::sharedLoading()->addLoadingToLayer(this);
    GameServerAction::sharedGameServerAction()->showTotalTimes(2,this, callfuncO_selector(RankingLayer::getRanking_Done));
    
}


void RankingLayer::getRanking_Done(CCObject * data)
{
    if(data)
    {
        if(isTodayRank)
        {
            pTodayRanking = CCArray::create();
            pTodayRanking->retain();
            
            pTodayUsers = CCArray::create();
            pTodayUsers->retain();
        }
        else
        {
            pAllRanking = CCArray::create();
            pAllRanking->retain();

            pAllUsers = CCArray::create();
            pAllUsers->retain();
        }
        
        CCDictionary *dict = (CCDictionary *)data;
        
        CCArray * rankList = (CCArray *)dict->objectForKey("rankUserInfoList");
    
        if(!rankList || rankList->count() < 1)
        {
            Loading::sharedLoading()->removeLoading();
            mWarning->setVisible(true);
            mWarning->setString("暂时没有排行信息！");
            return;
        }
        
        RankInfo * rankInfo = NULL;
        CCDictionary * dicRank = NULL;
        for(int i = 0; i < rankList->count(); i ++)
        {
            dicRank = (CCDictionary *)rankList->objectAtIndex(i);

            rankInfo = RankInfo::create();
            rankInfo->parseRankInfo(dicRank);

            if(isTodayRank)
            {
                pTodayRanking->addObject(rankInfo);
            }
            else
            {
                pAllRanking->addObject(rankInfo);
            }
            
        }
        
        CCArray * snsList = (CCArray *)dict->objectForKey("snsId");
    
        if(!snsList || snsList->count() < 1)
        {
            Loading::sharedLoading()->removeLoading();
            mWarning->setVisible(true);
            mWarning->setString("暂时没有排行信息！");
            return;
        }
        
        CCArray * userList = (CCArray *)dict->objectForKey("simpleUser");
    
        if(!userList || userList->count() < 1)
        {
            Loading::sharedLoading()->removeLoading();
            mWarning->setVisible(true);
            mWarning->setString("暂时没有排行信息！");
            return;
        }
        
        etListCount = userList->count();
        
        CCDictionary * dic = NULL;
        for(int i = 0; i < userList->count(); i ++)
        {
            dic = (CCDictionary *)userList->objectAtIndex(i);

            mSimpleUserInfo = SimpleUserInfo::create();
            mSimpleUserInfo->retain();
            mSimpleUserInfo->parseSimpleUserInfo(dic);
            if(snsList->objectAtIndex(i))
            {
                mSimpleUserInfo->setSNS(((CCString *)snsList->objectAtIndex(i))->getCString());
            }
            mSimpleUserInfo->retrieveAvartaImage(this, callfuncND_selector(RankingLayer::addSimpleUser));
        }
        //addListView();
    }
    
    Loading::sharedLoading()->removeLoading();
}


void RankingLayer::onTodayClicked(cocos2d::CCObject *pSender)
{
    isTodayRank = true;
    mWarning->setVisible(false);
    mWarning->setString("");
    Loading::sharedLoading()->addLoadingToLayer(this);
    GameServerAction::sharedGameServerAction()->showTotalTimes(3,this, callfuncO_selector(RankingLayer::getRanking_Done));

}


void RankingLayer::addSimpleUser(cocos2d::CCNode *pNode, void *data)
{
    
    if((bool)data)
    {
        if (isTodayRank) {
            pTodayUsers->addObject(mSimpleUserInfo);
        }
        else{
            pAllUsers->addObject(mSimpleUserInfo);
        }
        
    }
    
    CCLOG("etListCount: %d", etListCount);
    
    etListCount --;
    if(etListCount == 0)
    {
        CCLOG("addListView");
        addListView();
    }
}


