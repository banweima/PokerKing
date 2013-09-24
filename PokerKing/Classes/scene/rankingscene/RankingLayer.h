//
//  RankingLayer.h
//  blackjack
//
//  Created by Banson Niu on 9/12/12.
//
//

#ifndef __blackjack__RankingLayer__
#define __blackjack__RankingLayer__

#include <list.h>
#include <string.h>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCListView.h"
#include "MainBoardScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RankingLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public CCListViewDelegate
{
private:
    
    CCMenuItemImage * mToday;
    CCMenuItemImage * mAll;

    CCArray * pTodayRanking;
    CCArray * pAllRanking;
    
    CCArray * pTodayUsers;
    CCArray * pAllUsers;
    
    CCLabelTTF * mWarning;
    
    CCListView *m_pTodayListView;
    CCListView *m_pAllListView;

    bool isTodayRank;

    int mIndexImgWidth;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RankingLayer, create);
    
    bool init();
    
    RankingLayer();
    virtual ~RankingLayer();
    
    void setupLayer();
    
    virtual void visit();
    
    // for CCB
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    // for CCListView
    virtual void CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data);
    
private:
    void addListView();

     void onHomeClicked(CCObject *pSender);
    
     void onAllClicked(CCObject *pSender);
     void onTodayClicked(CCObject * pSender);
    
    void getRanking_Done(CCObject * data);
    
};

#endif /* defined(__blackjack__RankingLayer__) */
