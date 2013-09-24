//
//  TaskLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-5.
//
//

#ifndef __PokerKing__TaskLayer__
#define __PokerKing__TaskLayer__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCListView.h"
#include "MainBoardScene.h"
#include "TaskInfo.h"
#include "AlertLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TaskLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public CCListViewDelegate
{
private:
    
    CCMenuItemImage * mDaily;
    CCMenuItemImage * mAll;

    CCArray * pDailyTask;
    CCArray * pAllTask;
    
    CCLabelTTF * mWarning;
    
    CCListView *m_pDailyListView;
    CCListView *m_pAllListView;

    TaskInfo * pTaskInfo;
    bool isDailyTask;
    
    int clickedItemIndex;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TaskLayer, create);
    
    bool init();
    
    TaskLayer();
    virtual ~TaskLayer();
    
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
     void onDailyClicked(CCObject * pSender);
    
    void getAllTask();
    void getAllTask_Done(CCObject * data);
//    void getDailyTask_Done(CCObject * data);

    void onCompleteClicked(CCObject * pSender);
    void completeTask_Done(CCObject * data);
    
    void setMenuItemImageSelected(CCObject * targetItem);
};


#endif /* defined(__PokerKing__TaskLayer__) */
