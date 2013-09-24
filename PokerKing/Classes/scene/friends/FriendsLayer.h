//
//  FriendsLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-25.
//
//

#ifndef __PokerKing__FriendsLayer__
#define __PokerKing__FriendsLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCListView.h"
#include "MainBoardScene.h"
#include "GameInfo.h"
#include "GameServerAction.h"
#include "GameItem.h"
#include "Loading.h"
#include "AlertLayer.h"

enum FriendsTab
{
    NormalPlyers,
    RealFriends,
    FriendsRequest
};


USING_NS_CC;
USING_NS_CC_EXT;

class FriendsLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public CCListViewDelegate
{
private:
    CCSprite* mFriendsBanner;
    CCMenuItemImage * mFriends;
    CCMenuItemImage * mPlayers;
    CCMenuItemImage * mRequest;
    
    CCArray * pPlayerList;
    CCArray * pFriendsList;
    CCArray * pRequestList;
    
    CCListView *m_pPlayerListView;
    CCListView *m_pFriendsListView;
    CCListView *m_pRequestListView;

    CCLabelTTF * mWarning;
    
    int mIndexImgWidth;
    FriendsTab friendsTab;
    int clickedItemIndex;
    int etListCount;
    
    SimpleUserInfo * mSimpleUserInfo;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FriendsLayer, create);
    
    bool init();
    
    FriendsLayer();
    virtual ~FriendsLayer();
    
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
     void onHomeClicked(CCObject *pSender);

    void onFriendsClicked(CCObject *pSender);
    void onPlayersClicked(CCObject *pSender);
    void onRequestClicked(CCObject *pSender);
    
    void onInviteClicked(CCObject * pSender);
    void onRemoveClicked(CCObject * pSender);
    void onAcceptClicked(CCObject * pSender);
    void onRejectClicked(CCObject * pSender);
    
    
    void getNormalPlayer_Done(cocos2d::CCObject *data);
    
    void getRealFriends_Done(cocos2d::CCObject *data);
    
    void getFriendsRequest_Done(cocos2d::CCObject *data);
    
    void sendInvitation_Done(cocos2d::CCNode * pNode, void *data);
    
    void removeFriend_Done(cocos2d::CCNode * pNode, void *data);
    
    void acceptFriend_Done(cocos2d::CCNode * pNode, void *data);
    
    void rejectFriend_Done(cocos2d::CCNode * pNode, void *data);
    
    void addSimpleUser(cocos2d::CCNode * pNode, void *data);
    
    void addListView();
    
    void setListInvisible();
    
    void setMenuItemImageSelected(CCObject * targetItem);
    
    void onInvitationClicked(CCObject * pSender);
};



#endif /* defined(__PokerKing__FriendsLayer__) */
