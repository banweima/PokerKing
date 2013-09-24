//
//  FriendsLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-25.
//
//

#include "FriendsLayer.h"
#include "CCBUtility.h"
#include "StoreKitFactory.h"
#include "SimpleUserInfo.h"
#include "UserInfoLayer.h"
#include "CursorTextField.h"
#include "SceneControler.h"

FriendsLayer::FriendsLayer()
: mFriendsBanner(NULL)
, pPlayerList(NULL)
, pFriendsList(NULL)
, pRequestList(NULL)
, mFriends(NULL)
, mPlayers(NULL)
, mRequest(NULL)
, m_pFriendsListView(NULL)
, m_pPlayerListView(NULL)
, m_pRequestListView(NULL)
, mWarning(NULL)
, etListCount(0)
{}

FriendsLayer::~FriendsLayer()
{
    CC_SAFE_RELEASE(mFriendsBanner);
    CC_SAFE_RELEASE(pPlayerList);
    CC_SAFE_RELEASE(pRequestList);
    CC_SAFE_RELEASE(pFriendsList);
    CC_SAFE_RELEASE(m_pPlayerListView);
    CC_SAFE_RELEASE(m_pRequestListView);
    CC_SAFE_RELEASE(m_pFriendsListView);
    CC_SAFE_RELEASE(mFriends);
    CC_SAFE_RELEASE(mPlayers);
    CC_SAFE_RELEASE(mRequest);
    CC_SAFE_RELEASE(mWarning);

}

bool FriendsLayer::init()
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

void FriendsLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/friends.ccbi", "FriendsLayer", CCLayerLoader::loader(), this);
    this->addChild(node);
    
    mWarning->setVisible(false);
    
    onFriendsClicked(mFriends);
    
//    CursorTextField * m_pCursorTextField = CursorTextField::textFieldWithPlaceHolder("Input Text", "Thonburi", 18);
//    
//    m_pCursorTextField->setPosition(ccp(200,200));
//    this->addChild(m_pCursorTextField);

}

void FriendsLayer::addListView()
{
    
    switch (friendsTab) {
        case NormalPlyers:
        {
            if(!m_pPlayerListView && pPlayerList->count() > 0)
            {
                m_pPlayerListView = CCListView::viewWithMode(CCListViewModeVertical);
                m_pPlayerListView->retain();
                CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                CCSize listSize = CCSizeMake(winSize.width, mFriends->getPositionY() - 20);
        
                m_pPlayerListView->setContentSize(listSize);
                m_pPlayerListView->setDelegate(this);
                m_pPlayerListView->setAnchorPoint(ccp(0,0));
                m_pPlayerListView->setPosition(ccp(0, 10));
                m_pPlayerListView->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
                this->addChild(m_pPlayerListView);
            }
            m_pPlayerListView->setVisible(true);
            break;
        }
        
        case RealFriends:
        {
            if(!m_pFriendsListView && pFriendsList->count() > 0)
            {
                m_pFriendsListView = CCListView::viewWithMode(CCListViewModeVertical);
                m_pFriendsListView->retain();
                CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                CCSize listSize = CCSizeMake(winSize.width, mFriends->getPositionY() - 20);
        
                m_pFriendsListView->setContentSize(listSize);
                m_pFriendsListView->setDelegate(this);
                m_pFriendsListView->setAnchorPoint(ccp(0,0));
                m_pFriendsListView->setPosition(ccp(0, 10));
                m_pFriendsListView->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
                this->addChild(m_pFriendsListView);
            }
            m_pFriendsListView->setVisible(true);
            break;
        }
        
        case FriendsRequest:
        {
            if(!m_pRequestListView && pRequestList->count() > 0)
            {
                m_pRequestListView = CCListView::viewWithMode(CCListViewModeVertical);
                m_pRequestListView->retain();
                CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                CCSize listSize = CCSizeMake(winSize.width, mFriends->getPositionY() - 20);
        
                m_pRequestListView->setContentSize(listSize);
                m_pRequestListView->setDelegate(this);
                m_pRequestListView->setAnchorPoint(ccp(0,0));
                m_pRequestListView->setPosition(ccp(0, 10));
                m_pRequestListView->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
                this->addChild(m_pRequestListView);
            }
            m_pFriendsListView->setVisible(true);
            break;
        }
    }
}

void FriendsLayer::setListInvisible()
{
    switch (friendsTab) {
        case NormalPlyers:
        if(m_pPlayerListView)
        m_pPlayerListView->setVisible(false);
        break;
        case RealFriends:
        if(m_pFriendsListView)
        m_pFriendsListView->setVisible(false);
        break;
        case FriendsRequest:
        if(m_pRequestListView)
        m_pRequestListView->setVisible(false);
        break;
    }
}

void FriendsLayer::visit()
{
    CCLayer::visit();
//    if (m_bFresh) {
//        if(isItemSales)
//        {
//            m_pItemListView->reload();
//        }
//        else
//        {
//            m_pIAPListView->reload();
//        }
//        m_bFresh = false;
//    }
}

void FriendsLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler FriendsLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", FriendsLayer::onHomeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFriendsClicked", FriendsLayer::onFriendsClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPlayersClicked", FriendsLayer::onPlayersClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRequestClicked", FriendsLayer::onRequestClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onInvitationClicked", FriendsLayer::onInvitationClicked);
    
    return NULL;
}


SEL_CCControlHandler FriendsLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool FriendsLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFriendsBanner", CCSprite *, mFriendsBanner);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFriends", CCMenuItemImage *, mFriends);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayers", CCMenuItemImage *, mPlayers);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRequest", CCMenuItemImage *, mRequest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWarning", CCLabelTTF *, mWarning);
    
    return false;
}

void FriendsLayer::CCListView_numberOfCells(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCLOG("ListViewDemoLayer::CCListView_numberOfCells");
    switch (friendsTab) {
        case NormalPlyers:
        data->nNumberOfRows = pPlayerList->count();
        break;
        case RealFriends:
        data->nNumberOfRows = pFriendsList->count();
        break;
        case FriendsRequest:
        data->nNumberOfRows = pRequestList->count();
        break;
    }
    
    CCLOG("Cell Count: %d", data->nNumberOfRows);
}

void FriendsLayer::CCListView_cellForRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCSize listSize;
    
    switch (friendsTab) {
        case NormalPlyers:
        listSize = m_pPlayerListView->getContentSize();
        break;
        case RealFriends:
        listSize = m_pFriendsListView->getContentSize();
        break;
        case FriendsRequest:
        listSize = m_pRequestListView->getContentSize();
        break;
    }

    
    CCSize cellSize = CCSizeMake(listSize.width, listSize.height/5);
    
    CCListViewCell *cell = CCListViewCell::node();
    cell->setOpacity(0);
    cell->setContentSize(cellSize);
    cell->setSelectionColor(ccc4(200, 100, 150, 0)); //set invisible back color after selected

    data->cell = cell;
    
    std::string cellNameValue = "";
    std::string cellLvValue = "";
    
    switch (friendsTab) {
      case NormalPlyers:
        cellNameValue = ((SimpleUserInfo *)pPlayerList->objectAtIndex(data->nRow))->getUserName();
        cellLvValue = CCString::createWithFormat("Lv %d", ((SimpleUserInfo *)pPlayerList->objectAtIndex(data->nRow))->getLevel())->getCString();
        break;
        case RealFriends:
        cellNameValue = ((SimpleUserInfo *)pFriendsList->objectAtIndex(data->nRow))->getUserName();
        cellLvValue = CCString::createWithFormat("Lv %d", ((SimpleUserInfo *)pFriendsList->objectAtIndex(data->nRow))->getLevel())->getCString();
        break;
        case FriendsRequest:
        cellNameValue = ((SimpleUserInfo *)pRequestList->objectAtIndex(data->nRow))->getUserName();
        cellLvValue = CCString::createWithFormat("Lv %d", ((SimpleUserInfo *)pRequestList->objectAtIndex(data->nRow))->getLevel())->getCString();
        break;
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

    CCLOG("Trying get avarta!!");
    CCSprite * playerImage = NULL;
    switch (friendsTab) {
      case NormalPlyers:
        playerImage = ((SimpleUserInfo *)pPlayerList->objectAtIndex(data->nRow))->getAvartaIamge();
        break;
        case RealFriends:
        playerImage = ((SimpleUserInfo *)pFriendsList->objectAtIndex(data->nRow))->getAvartaIamge();
        break;
        case FriendsRequest:
        playerImage = ((SimpleUserInfo *)pRequestList->objectAtIndex(data->nRow))->getAvartaIamge();
        break;
    }

    
    if(playerImage)
    {
        playerImage->setAnchorPoint(ccp(0,0.5));
        playerImage->setScale(bgSprite->getContentSize().height/playerImage->getContentSize().height);
        playerImage->setPosition(frameSprite->getPosition());
        
        cell->addChild(playerImage);
    }
    
    cell->addChild(frameSprite);
    
    CCLabelTTF *cellLvLabel = CCLabelTTF::create(cellLvValue.c_str(), "Arial", 10, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    cellLvLabel->setAnchorPoint(ccp(0,1));
    cellLvLabel->setPosition(ccp(frameSprite->getPositionX() + frameSprite->getContentSize().width * 1.2 * fScale, frameSprite->getPositionY() + frameSprite->getContentSize().height * fScale/2));
    cell->addChild(cellLvLabel);
    
    CCLabelTTF *cellNameLabel = CCLabelTTF::create(cellNameValue.c_str(), "Arial", 18, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    cellNameLabel->setAnchorPoint(ccp(0,0));
    cellNameLabel->setPosition(ccp(frameSprite->getPositionX() + frameSprite->getContentSize().width * 1.2 * fScale, frameSprite->getPositionY() - frameSprite->getContentSize().height * fScale/2));
    cell->addChild(cellNameLabel);
    
    
    
    CCSprite *okBtn1 = CCSprite::createWithSpriteFrameName("button_22");
    CCSprite *cancelBtn1 = CCSprite::createWithSpriteFrameName("button_cancel");
    
    SEL_MenuHandler menuHandler = NULL;
    SEL_MenuHandler menuHandler2 = NULL;
    
    switch (friendsTab) {
      case NormalPlyers:
        menuHandler = menu_selector(FriendsLayer::onInviteClicked);
        break;
        case RealFriends:
        menuHandler = menu_selector(FriendsLayer::onRemoveClicked);
        break;
        case FriendsRequest:
        menuHandler = menu_selector(FriendsLayer::onAcceptClicked);
        menuHandler2 = menu_selector(FriendsLayer::onRejectClicked);
        break;
    }

    CCMenuItemSprite* okMenuItem = NULL;
    CCMenuItemSprite* cancelMenuItem = NULL;
    CCMenu *  m_pMenu = NULL;
    
    if(friendsTab == FriendsRequest)
    {
        okMenuItem= CCMenuItemSprite::create(okBtn1, okBtn1, okBtn1, this, menuHandler);

        okMenuItem->setAnchorPoint(ccp(0,0.5));
        okMenuItem->setPosition(ccp( bgSprite->getContentSize().width - okMenuItem->getContentSize().width,cellSize.height/2));
        
        cancelMenuItem= CCMenuItemSprite::create(cancelBtn1, cancelBtn1, cancelBtn1, this, menuHandler2);

        cancelMenuItem->setAnchorPoint(ccp(0,0.5));
        cancelMenuItem->setPosition(ccp( okMenuItem->getPositionX() + okMenuItem->getContentSize().width,cellSize.height/2));
        
        m_pMenu = CCMenu::create(okMenuItem, cancelMenuItem,NULL);
    }
    else
    {
        okMenuItem= CCMenuItemSprite::create(okBtn1, okBtn1, okBtn1, this, menuHandler);

        okMenuItem->setAnchorPoint(ccp(0,0.5));
        okMenuItem->setPosition(ccp( bgSprite->getContentSize().width - okMenuItem->getContentSize().width,cellSize.height/2));
        
        m_pMenu = CCMenu::create(okMenuItem, NULL);
    }
    
    m_pMenu->setAnchorPoint(ccp(0,0));
    m_pMenu->setPosition(ccp(0,0));
    cell->addChild(m_pMenu, 0 ,data->nRow);
}

void FriendsLayer::CCListView_didClickCellAtRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCLOG("Item %d Clicked", data->nRow);
    
    SimpleUserInfo * sc = NULL;
    switch (friendsTab) {
      case NormalPlyers:
        sc = ((SimpleUserInfo *)pPlayerList->objectAtIndex(data->nRow));
        break;
        case RealFriends:
        sc = ((SimpleUserInfo *)pFriendsList->objectAtIndex(data->nRow));
        break;
        case FriendsRequest:
        sc = ((SimpleUserInfo *)pRequestList->objectAtIndex(data->nRow));
        break;
    }
    
    UserInfoLayer::sharedUserInfoLayer()->addUserInfoLayerToLayer(this, sc);
}

void FriendsLayer::CCListView_didScrollToRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
}

void FriendsLayer::onHomeClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->goBackScene();
}


void FriendsLayer::onFriendsClicked(cocos2d::CCObject *pSender)
{
    setListInvisible();
    setMenuItemImageSelected(pSender);
    friendsTab = RealFriends;
    mWarning->setVisible(false);
    mWarning->setString("");
    Loading::sharedLoading()->addLoadingToLayer(this);
    GameServerAction::sharedGameServerAction()->getFriends(this, callfuncO_selector(FriendsLayer::getRealFriends_Done));
}

void FriendsLayer::onPlayersClicked(cocos2d::CCObject *pSender)
{
    setListInvisible();
    setMenuItemImageSelected(pSender);
    friendsTab = NormalPlyers;
    mWarning->setVisible(false);
    mWarning->setString("");
    Loading::sharedLoading()->addLoadingToLayer(this);
    GameServerAction::sharedGameServerAction()->getNormalPlayer(this, callfuncO_selector(FriendsLayer::getNormalPlayer_Done));
}

void FriendsLayer::onRequestClicked(cocos2d::CCObject *pSender)
{
    setListInvisible();
    setMenuItemImageSelected(pSender);
    friendsTab = FriendsRequest;
    mWarning->setVisible(false);
    mWarning->setString("");
    Loading::sharedLoading()->addLoadingToLayer(this);
    GameServerAction::sharedGameServerAction()->getFriendsRequest(this, callfuncO_selector(FriendsLayer::getFriendsRequest_Done));
}

void FriendsLayer::getNormalPlayer_Done(cocos2d::CCObject *data)
{
    if(data)
    {
        if(pPlayerList)
        {
            pPlayerList->release();
        }
        
        pPlayerList = CCArray::create();
        pPlayerList->retain();
        
        CCDictionary *dict = (CCDictionary *)data;
        
        CCArray * etList = (CCArray *)dict->objectForKey("simpleUser");
    
        if(!etList || etList->count() < 1)
        {
            Loading::sharedLoading()->removeLoading();
            mWarning->setVisible(true);
            mWarning->setString("暂时没有在线玩家！");
            return;
        }
        etListCount = etList->count();
        
        CCDictionary * dic = NULL;
        for(int i = 0; i < etList->count(); i ++)
        {
            dic = (CCDictionary *)etList->objectAtIndex(i);

            mSimpleUserInfo = SimpleUserInfo::create();
            mSimpleUserInfo->retain();
            mSimpleUserInfo->parseSimpleUserInfo(dic);
            mSimpleUserInfo->retrieveAvartaImage(this, callfuncND_selector(FriendsLayer::addSimpleUser));
        }
    }
    else
    {
        mWarning->setVisible(true);
        mWarning->setString("暂时没有在线玩家！");
    }
    
    Loading::sharedLoading()->removeLoading();

}

void FriendsLayer::getRealFriends_Done(cocos2d::CCObject *data)
{
    if(data)
    {
        if(pFriendsList)
        {
            pFriendsList->release();
        }
        
        pFriendsList = CCArray::create();
        pFriendsList->retain();
        
        CCDictionary *dict = (CCDictionary *)data;
        
        CCArray * etList = (CCArray *)dict->objectForKey("friends");
    
        if(!etList || etList->count() < 1)
        {
            Loading::sharedLoading()->removeLoading();
            mWarning->setVisible(true);
            mWarning->setString("您暂时还没有好友！");
            return;
        }
        etListCount = etList->count();
        CCDictionary * dic = NULL;
        for(int i = 0; i < etList->count(); i ++)
        {
            dic = (CCDictionary *)etList->objectAtIndex(i);

            mSimpleUserInfo = SimpleUserInfo::create();
            mSimpleUserInfo->parseSimpleUserInfo(dic);
            mSimpleUserInfo->retrieveAvartaImage(NULL, NULL);
            mSimpleUserInfo->retrieveAvartaImage(this, callfuncND_selector(FriendsLayer::addSimpleUser));
        }
    }
    else
    {
        mWarning->setVisible(true);
        mWarning->setString("您暂时还没有好友！");
    }

    Loading::sharedLoading()->removeLoading();
}

void FriendsLayer::getFriendsRequest_Done(cocos2d::CCObject *data)
{
    if(data)
    {
        if(pRequestList)
        {
            pRequestList->release();
        }
        
        pRequestList = CCArray::create();
        pRequestList->retain();

        
        CCDictionary *dict = (CCDictionary *)data;
        
        CCArray * etList = (CCArray *)dict->objectForKey("requestFriends");
    
        if(!etList || etList->count() < 1)
        {
            Loading::sharedLoading()->removeLoading();
            mWarning->setVisible(true);
            mWarning->setString("您暂时还没有好友申请！");
            return;
        }
        
        etListCount = etList->count();
        mSimpleUserInfo = NULL;
        CCDictionary * dic = NULL;
        for(int i = 0; i < etList->count(); i ++)
        {
            dic = (CCDictionary *)etList->objectAtIndex(i);

            mSimpleUserInfo = SimpleUserInfo::create();
            mSimpleUserInfo->parseSimpleUserInfo(dic);
            mSimpleUserInfo->retrieveAvartaImage(this, callfuncND_selector(FriendsLayer::addSimpleUser));
            
        }
    }
    else
    {
        mWarning->setVisible(true);
        mWarning->setString("您暂时还没有好友申请！");
    }
    Loading::sharedLoading()->removeLoading();
}

void FriendsLayer::onInviteClicked(cocos2d::CCObject *pSender)
{
    Loading::sharedLoading()->addLoadingToLayer(this);
    
    clickedItemIndex = ((CCMenuItemImage *)pSender)->getParent()->getTag();
    
    CCLOG("Menu Clicked %d", clickedItemIndex);
    
    GameServerAction::sharedGameServerAction()->sendFriendInvitation(((SimpleUserInfo *)pPlayerList->objectAtIndex(clickedItemIndex))->getUserID(), this, callfuncND_selector(FriendsLayer::sendInvitation_Done));

}

void FriendsLayer::sendInvitation_Done(cocos2d::CCNode * pNode, void *data)
{
    std::string msg = "";
    std::string title = "好友邀请";
    if((bool)data)
    {
        msg = "邀请好友成功，请等待对方答复";
        CCListViewCell * cell = m_pPlayerListView->cellAtRow(clickedItemIndex);
        cell->getChildByTag(clickedItemIndex)->setVisible(false);
        
        CCLabelTTF *cellLabel = CCLabelTTF::create("已邀请", "Arial", 18, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        cellLabel->setAnchorPoint(ccp(1,0.5));
        cellLabel->setPosition(ccp(cell->getContentSize().width - cellLabel->getContentSize().width,cell->getContentSize().height/2));
        cell->addChild(cellLabel);
        
    }
    else
    {
        msg = "邀请发送失败，请稍后再试";
    }
    Loading::sharedLoading()->removeLoading();
    
    AlertLayer * shareAlert = AlertLayer::create(title.c_str(), msg.c_str() , false, NULL, NULL);
    
    this->addChild(shareAlert, Child_Order_Top);

}

void FriendsLayer::onRemoveClicked(cocos2d::CCObject *pSender)
{
    Loading::sharedLoading()->addLoadingToLayer(this);
    clickedItemIndex = ((CCMenuItemImage *)pSender)->getParent()->getTag();
    
    CCLOG("Menu Clicked %d", clickedItemIndex);
    
    GameServerAction::sharedGameServerAction()->removeFriend(((SimpleUserInfo *)pFriendsList->objectAtIndex(clickedItemIndex))->getUserID(), this, callfuncND_selector(FriendsLayer::removeFriend_Done));

}

void FriendsLayer::removeFriend_Done(cocos2d::CCNode *pNode, void *data)
{
    Loading::sharedLoading()->removeLoading();
    
    if((bool)data)
    {
        CCListViewCell * cell = m_pFriendsListView->cellAtRow(clickedItemIndex);
        cell->getChildByTag(clickedItemIndex)->setVisible(false);
        
        CCLabelTTF *cellLabel = CCLabelTTF::create("已移除", "Arial", 18, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        cellLabel->setAnchorPoint(ccp(1,0.5));
        cellLabel->setPosition(ccp(cell->getContentSize().width - cellLabel->getContentSize().width,cell->getContentSize().height/2));
        cell->addChild(cellLabel);
        
    }
    else
    {
        std::string msg = "";
        std::string title = "好友移除";
        msg = "移除好友失败，请稍后再试";
        AlertLayer * shareAlert = AlertLayer::create(title.c_str(), msg.c_str() , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }
}


void FriendsLayer::onAcceptClicked(cocos2d::CCObject *pSender)
{
    Loading::sharedLoading()->addLoadingToLayer(this);
    clickedItemIndex = ((CCMenuItemImage *)pSender)->getParent()->getTag();
    
    CCLOG("Menu Clicked %d", clickedItemIndex);
    
    GameServerAction::sharedGameServerAction()->acceptFriendRequest(((SimpleUserInfo *)pRequestList->objectAtIndex(clickedItemIndex))->getUserID(), this, callfuncND_selector(FriendsLayer::acceptFriend_Done));
}

void FriendsLayer::acceptFriend_Done(cocos2d::CCNode *pNode, void *data)
{
    Loading::sharedLoading()->removeLoading();
    
    if((bool)data)
    {
        CCListViewCell * cell = m_pRequestListView->cellAtRow(clickedItemIndex);
        cell->getChildByTag(clickedItemIndex)->setVisible(false);
        
        CCLabelTTF *cellLabel = CCLabelTTF::create("已加为好友", "Arial", 18, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        cellLabel->setAnchorPoint(ccp(1,0.5));
        cellLabel->setPosition(ccp(cell->getContentSize().width - cellLabel->getContentSize().width,cell->getContentSize().height/2));
        cell->addChild(cellLabel);
        
    }
    else
    {
        std::string msg = "";
        std::string title = "好友邀请";
        msg = "加为好友失败，请稍后再试";
        AlertLayer * shareAlert = AlertLayer::create(title.c_str(), msg.c_str() , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }

}

void FriendsLayer::onRejectClicked(cocos2d::CCObject *pSender)
{
    Loading::sharedLoading()->addLoadingToLayer(this);
    clickedItemIndex = ((CCMenuItemImage *)pSender)->getParent()->getTag();
    
    CCLOG("Menu Clicked %d", clickedItemIndex);
    
    GameServerAction::sharedGameServerAction()->rejectFriendRequest(((SimpleUserInfo *)pRequestList->objectAtIndex(clickedItemIndex))->getUserID(), this, callfuncND_selector(FriendsLayer::rejectFriend_Done));

}


void FriendsLayer::rejectFriend_Done(cocos2d::CCNode *pNode, void *data)
{
    Loading::sharedLoading()->removeLoading();
    
    if((bool)data)
    {
        CCListViewCell * cell = m_pRequestListView->cellAtRow(clickedItemIndex);
        cell->getChildByTag(clickedItemIndex)->setVisible(false);
        
        CCLabelTTF *cellLabel = CCLabelTTF::create("已拒绝邀请", "Arial", 18, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        cellLabel->setAnchorPoint(ccp(1,0.5));
        cellLabel->setPosition(ccp(cell->getContentSize().width - cellLabel->getContentSize().width,cell->getContentSize().height/2));
        cell->addChild(cellLabel);
    }
    else
    {
        std::string msg = "";
        std::string title = "好友邀请";
        msg = "拒绝邀请失败，请稍后再试";
        AlertLayer * shareAlert = AlertLayer::create(title.c_str(), msg.c_str() , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }

}


void FriendsLayer::setMenuItemImageSelected(cocos2d::CCObject *targetItem)
{
    CCArray * itemList = ((CCMenu *)((CCMenuItemImage*)targetItem)->getParent())->getChildren();
    for(int i = 0; i < itemList->count(); i++)
    {
        ((CCMenuItemImage *)itemList->objectAtIndex(i))->unselected();
    }

    ((CCMenuItemImage*)targetItem)->selected();
}

void FriendsLayer::onInvitationClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->gotoScene(Invitation_Scene);
}


void FriendsLayer::addSimpleUser(cocos2d::CCNode *pNode, void *data)
{
    
    if((bool)data)
    {
        switch (friendsTab) {
          case NormalPlyers:
            pPlayerList->addObject(mSimpleUserInfo);
            break;
            case RealFriends:
            pFriendsList->addObject(mSimpleUserInfo);
            break;
            case FriendsRequest:
            pRequestList->addObject(mSimpleUserInfo);
            break;
        }
        
    }
    
    CCLOG("etListCount: %d", etListCount);
    
    etListCount --;
    if(etListCount == 0)
    {
        addListView();
    }
}
