//
//  TaskLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-5.
//
//

#include "TaskLayer.h"
#include "CCBUtility.h"
#include "SceneControler.h"
#include "UserInfoLayer.h"
#include "GameServerAction.h"
#include "Loading.h"
#include "SimpleUserInfo.h"


TaskLayer::TaskLayer()
: mDaily(NULL)
, mAll(NULL)
, pDailyTask(NULL)
, pAllTask(NULL)
, m_pDailyListView(NULL)
, m_pAllListView(NULL)
, isDailyTask(false)
, mWarning(NULL)
, pTaskInfo(NULL)
{}

TaskLayer::~TaskLayer()
{
    CC_SAFE_RELEASE(mDaily);
    CC_SAFE_RELEASE(mAll);
    CC_SAFE_RELEASE(pDailyTask);
    CC_SAFE_RELEASE(pAllTask);
    CC_SAFE_RELEASE(m_pAllListView);
    CC_SAFE_RELEASE(m_pDailyListView);
    CC_SAFE_RELEASE(mWarning);
}

bool TaskLayer::init()
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

void TaskLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/task.ccbi", "TaskLayer", CCLayerLoader::loader(), this);
    this->addChild(node);
    
    mWarning->setVisible(false);
    getAllTask();
}

void TaskLayer::addListView()
{
    if(isDailyTask)
    {
        if(m_pAllListView)
        {
            m_pAllListView->setVisible(false);
        }
        
        if(!m_pDailyListView)
        {        
            m_pDailyListView = CCListView::viewWithMode(CCListViewModeVertical);
            m_pDailyListView->retain();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            CCSize listSize = CCSizeMake(winSize.width, mAll->getPositionY() - 20);
    
            m_pDailyListView->setContentSize(listSize);
            m_pDailyListView->setDelegate(this);
            m_pDailyListView->setAnchorPoint(ccp(0,0));
            m_pDailyListView->setPosition(ccp(0, 0));
            m_pDailyListView->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
            this->addChild(m_pDailyListView);
        }
        m_pDailyListView->setVisible(true);
    }
    else
    {
        if(m_pDailyListView)
        {
            m_pDailyListView->setVisible(false);
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

void TaskLayer::visit()
{
    CCLayer::visit();
//    if (m_bFresh) {
//        m_pListView->reload();
//        m_bFresh = false;
//    }
}

void TaskLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler TaskLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAllClicked", TaskLayer::onAllClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDailyClicked", TaskLayer::onDailyClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", TaskLayer::onHomeClicked);
    return NULL;
}

SEL_CCControlHandler TaskLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool TaskLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDaily", CCMenuItemImage *, mDaily);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAll", CCMenuItemImage *, mAll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWarning", CCLabelTTF *, mWarning);
    
    return false;
}

void TaskLayer::CCListView_numberOfCells(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCLOG("ListViewDemoLayer::CCListView_numberOfCells");
    if(isDailyTask)
    {
        data->nNumberOfRows = pDailyTask->count();
    }
    else
    {
        data->nNumberOfRows = pAllTask->count();
    }
}

void TaskLayer::CCListView_cellForRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCSize listSize;
    
    if(isDailyTask)
    {
        listSize = m_pDailyListView->getContentSize();
    }
    else
    {
        listSize = m_pAllListView->getContentSize();
    }
    
    CCSize cellSize = CCSizeMake(listSize.width, 46);
    
    CCListViewCell *cell = CCListViewCell::node();
    cell->setOpacity(0);
    cell->setContentSize(cellSize);
    cell->setSelectionColor(ccc4(200, 100, 150, 0)); //set invisible back color after selected

    data->cell = cell;
    
    std::string cellValue = "";
    TaskInfo * tInfo = NULL;
    
    if(isDailyTask)
    {
        tInfo = (TaskInfo *)pDailyTask->objectAtIndex(data->nRow);
    }
    else
    {
        tInfo = (TaskInfo *)pAllTask->objectAtIndex(data->nRow);

    }
    
    cellValue = tInfo->getDescription();

    
    CCSprite *bgSprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("rank_item1", data->nRow%4+1)->getCString());
    
    bgSprite->setPosition(ccp(cellSize.width/2, cellSize.height/2));
    cell->addChild(bgSprite);
    
//    cell->setScaleX(bgSprite->getContentSize().width/listSize.width);
    
    CCLabelTTF *cellLabel = CCLabelTTF::create(cellValue.c_str(), "Arial", 18);
    cellLabel->setAnchorPoint(ccp(0,0.5));
    cellLabel->setPosition(ccp((bgSprite->getPositionX() - bgSprite->getContentSize().width/2) * 1.25, cellSize.height/2));
    cell->addChild(cellLabel);
    
    
    
    if(tInfo->getStatus() == 0)
    {
        CCSprite *completeBtn = CCSprite::createWithSpriteFrameName("button_22");
    
    
        SEL_MenuHandler menuHandler = menu_selector(TaskLayer::onCompleteClicked);


        CCMenuItemSprite* completeMenuItem = NULL;
        CCMenu *  m_pMenu = NULL;
        completeMenuItem= CCMenuItemSprite::create(completeBtn, completeBtn, completeBtn, this, menuHandler);

        completeMenuItem->setAnchorPoint(ccp(0,0.5));
        completeMenuItem->setPosition(ccp( bgSprite->getContentSize().width - completeMenuItem->getContentSize().width,cellSize.height/2));
        
        m_pMenu = CCMenu::create(completeMenuItem,NULL);
        m_pMenu->setAnchorPoint(ccp(0,0));
        m_pMenu->setPosition(ccp(0,0));
        cell->addChild(m_pMenu, 0 ,data->nRow);
    }
    else
    {
        CCSprite *doneSprite = CCSprite::createWithSpriteFrameName("task_completed");
        doneSprite->setAnchorPoint(ccp(0,0.5));
        doneSprite->setPosition(ccp( bgSprite->getContentSize().width - doneSprite->getContentSize().width,cellSize.height/2));
        doneSprite->setScale(cell->getContentSize().height/doneSprite->getContentSize().height);
        cell->addChild(doneSprite);

    }
    
    
}

void TaskLayer::CCListView_didClickCellAtRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCLOG("Item %d Clicked", data->nRow);
    
//    UserInfoLayer::sharedUserInfoLayer()->addUserInfoLayerToLayer(this);
}

void TaskLayer::CCListView_didScrollToRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
}

void TaskLayer::onHomeClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->goBackScene();
}

void TaskLayer::onAllClicked(cocos2d::CCObject *pSender)
{
    isDailyTask = false;
    setMenuItemImageSelected(pSender);

    addListView();
}


void TaskLayer::onDailyClicked(cocos2d::CCObject *pSender)
{
    isDailyTask = true;
    setMenuItemImageSelected(pSender);

    addListView();
}

void TaskLayer::getAllTask()
{
    mWarning->setVisible(false);
    mWarning->setString("");
    Loading::sharedLoading()->addLoadingToLayer(this);
    GameServerAction::sharedGameServerAction()->getTask(this, callfuncO_selector(TaskLayer::getAllTask_Done));
}


//void TaskLayer::getDailyTask_Done(CCObject * data)
//{
//    if(data)
//    {
//        if(pDailyTask)
//        {
//            pDailyTask->release();
//        }
//        
//        pDailyTask = CCArray::create();
//        pDailyTask->retain();
//        
//        CCDictionary *dict = (CCDictionary *)data;
//        
//        CCArray * etList = (CCArray *)dict->objectForKey("simpleUser");
//    
//        if(!etList || etList->count() < 1)
//        {
//            Loading::sharedLoading()->removeLoading();
//            mWarning->setVisible(true);
//            mWarning->setString("暂时没有排行信息！");
//            return;
//        }
//        
//        SimpleUserInfo * simpleUserInfo = NULL;
//        CCDictionary * dic = NULL;
//        for(int i = 0; i < etList->count(); i ++)
//        {
//            dic = (CCDictionary *)etList->objectAtIndex(i);
//
//            simpleUserInfo = SimpleUserInfo::create();
//            simpleUserInfo->parseSimpleUserInfo(dic);
//            simpleUserInfo->retrieveAvartaImage(NULL, NULL);
//            pDailyTask->addObject(simpleUserInfo);
//        }
//        
//        addListView();
//    }
//    
//    Loading::sharedLoading()->removeLoading();
//}

void TaskLayer::getAllTask_Done(CCObject * data)
{
    Loading::sharedLoading()->removeLoading();
    if(data)
    {
        if(pAllTask)
        {
            pAllTask->release();
        }
        
        pAllTask = CCArray::create();
        pAllTask->retain();
        
        if(pDailyTask)
        {
            pDailyTask->release();
        }
        
        pDailyTask = CCArray::create();
        pDailyTask->retain();
        
        CCDictionary *dict = (CCDictionary *)data;
        
        CCArray * etList = (CCArray *)dict->objectForKey("taskInfo");
    
        if(!etList || etList->count() < 1)
        {
            mWarning->setVisible(true);
            mWarning->setString("暂时没有排行信息！");
            return;
        }
        
        TaskInfo * taskInfo = NULL;
        CCDictionary * dic = NULL;
        for(int i = 0; i < etList->count(); i ++)
        {
            dic = (CCDictionary *)etList->objectAtIndex(i);

            taskInfo = TaskInfo::create();
            taskInfo->parseTaskInfo(dic);
            if(taskInfo->getIsDaily() == 0)
            {
                pAllTask->addObject(taskInfo);
            }
            else
            {
                pDailyTask->addObject(taskInfo);
            }
        }
        
        onDailyClicked(mDaily);
    }
    
    
}

void TaskLayer::onCompleteClicked(CCObject * pSender)
{
    Loading::sharedLoading()->addLoadingToLayer(this);
    clickedItemIndex = ((CCMenuItemImage *)pSender)->getParent()->getTag();
    
    CCLOG("Menu Clicked %d", clickedItemIndex);
    
    GameServerAction::sharedGameServerAction()->completeTask(((TaskInfo *)pDailyTask->objectAtIndex(clickedItemIndex))->getTaskId(),this, callfuncO_selector(TaskLayer::completeTask_Done));
}

void TaskLayer::completeTask_Done(CCObject * data)
{
    Loading::sharedLoading()->removeLoading();
    if(data)
    {        
        CCDictionary *dict = (CCDictionary *)data;
        
        if(dict->objectForKey("errorMessage"))
        {
            AlertLayer * shareAlert = AlertLayer::create("任务", ((CCString * )dict->objectForKey("errorMessage"))->getCString() , false, NULL, NULL);
    
            this->addChild(shareAlert, Child_Order_Top);
            
            return;
        
        }
        
        CCDictionary * taskDic = (CCDictionary *)dict->objectForKey("taskInfo");
        
//        CCDictionary * taskDic = (CCDictionary *)((CCArray *)dict->objectForKey("taskInfo"))->objectAtIndex(0);
        
        pTaskInfo = TaskInfo::create();
        pTaskInfo->parseTaskInfo(taskDic);
        
        if(pTaskInfo->getStatus() == 0)
        {
            AlertLayer * shareAlert = AlertLayer::create("任务", "您还没有达到要求，继续加油！" , false, NULL, NULL);
    
            this->addChild(shareAlert, Child_Order_Top);
        }
        else
        {
            CCListViewCell * cell = NULL;
            
            if(isDailyTask)
            {
                cell = m_pDailyListView->cellAtRow(clickedItemIndex);
            }
            else
            {
                cell = m_pAllListView->cellAtRow(clickedItemIndex);
            }
            CCNode * node = cell->getChildByTag(clickedItemIndex);
            node->setVisible(false);
            
            CCSprite *doneSprite = CCSprite::createWithSpriteFrameName("task_completed");
            doneSprite->setAnchorPoint(ccp(0,0.5));
            doneSprite->setPosition(ccp(cell->getContentSize().width - doneSprite->getContentSize().width, cell->getContentSize().height/2));
            doneSprite->setScale(cell->getContentSize().height/doneSprite->getContentSize().height);
            cell->addChild(doneSprite);
            
            AlertLayer * shareAlert = AlertLayer::create("任务", "恭喜你完成了任务，后面有更多的好礼等着你！" , false, NULL, NULL);
    
            this->addChild(shareAlert, Child_Order_Top);
        }
    }
}

void TaskLayer::setMenuItemImageSelected(cocos2d::CCObject *targetItem)
{
    CCArray * itemList = ((CCMenu *)((CCMenuItemImage*)targetItem)->getParent())->getChildren();
    for(int i = 0; i < itemList->count(); i++)
    {
        ((CCMenuItemImage *)itemList->objectAtIndex(i))->unselected();
    }

    ((CCMenuItemImage*)targetItem)->selected();
}
