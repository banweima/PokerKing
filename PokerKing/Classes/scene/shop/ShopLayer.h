//
//  ShopLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-27.
//
//

#ifndef __PokerKing__ShopLayer__
#define __PokerKing__ShopLayer__

#include <list.h>
#include <string.h>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCListView.h"
#include "MainBoardScene.h"
#include "GameInfo.h"
#include "GameServerAction.h"
#include "GameItem.h"
#include "Loading.h"
#include "AlertLayer.h"


USING_NS_CC;
USING_NS_CC_EXT;

class ShopLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public CCListViewDelegate
{
private:
    CCSprite* mShopBanner;
    CCMenuItemImage * mDiamond;
    CCMenuItemImage * mItem;
    
    CCLabelTTF * mUserDiamond;
    CCLabelTTF * mUserGold;
    CCLabelTTF * mUserItem;
    
    CCArray * pIAPDataList;
    CCArray * pItemDataList;
    
    CCListView *m_pItemListView;
    CCListView *m_pIAPListView;
    bool m_bFresh;
    int mIndexImgWidth;
    bool isItemSales;
    bool hasItemInfo;
    bool hasProductInfo;
    int buyItemAmount;
    GameItem * buyItem;
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ShopLayer, create);
    
    bool init();
    
    ShopLayer();
    virtual ~ShopLayer();
    
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
    void buyItem_Done(cocos2d::CCNode *pNode, void *data);
    void updateUserInfo(cocos2d::CCNode *pNode, void *data);
    
    void onDiamondClicked(CCObject *pSender);
    void onItemClicked(CCObject *pSender);
    
    void addListView();
    void checkReceipt_Done(cocos2d::CCNode *pNode, void *data);
    
    void onInputNumber(CCObject * data);
    
    void confirmBuyItem(cocos2d::CCNode *pNode, void *data);
    
    void showUserInfo();
    void getItemInfo();
    void getItem_Done(cocos2d::CCNode *pNode, void *data);
    void getProductInfo();
    void getProduct_Done(cocos2d::CCNode *pNode, void *data);

};


#endif /* defined(__PokerKing__ShopLayer__) */
