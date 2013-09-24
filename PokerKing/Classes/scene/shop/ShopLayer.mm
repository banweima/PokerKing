//
//  ShopLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-27.
//
//

#include "ShopLayer.h"
#include "CCBUtility.h"
#include "StoreKitFactory.h"
#include "NumbersLayer.h"
#include "SceneControler.h"

ShopLayer::ShopLayer()
: mShopBanner(NULL)
, m_bFresh(true)
, isItemSales(false)
, m_pIAPListView(NULL)
, m_pItemListView(NULL)
, pIAPDataList(NULL)
, pItemDataList(NULL)
, mDiamond(NULL)
, mItem(NULL)
, buyItemAmount(0)
, buyItem(NULL)
, mUserDiamond(NULL)
, mUserGold(NULL)
, mUserItem(NULL)
, hasItemInfo(false)
, hasProductInfo(false)
{}

ShopLayer::~ShopLayer()
{
    CC_SAFE_RELEASE(mShopBanner);
    CC_SAFE_RELEASE(pIAPDataList);
    CC_SAFE_RELEASE(pItemDataList);
    CC_SAFE_RELEASE(mDiamond);
    CC_SAFE_RELEASE(mItem);
    CC_SAFE_RELEASE(mUserDiamond);

}

bool ShopLayer::init()
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

void ShopLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/shop.ccbi", "ShopLayer", CCLayerLoader::loader(), this);
    this->addChild(node);
    showUserInfo();
    isItemSales = true;
    getItemInfo();
}

void ShopLayer::getItemInfo()
{
    GameServerAction::sharedGameServerAction()->getItems(this, callfuncND_selector(ShopLayer::getItem_Done));
}

void ShopLayer::getProductInfo()
{
    GameServerAction::sharedGameServerAction()->retrieveProductList(this, callfuncND_selector(ShopLayer::getProduct_Done));
}

void ShopLayer::addListView()
{
    if(isItemSales)
    {
        if(m_pIAPListView)
        {
            m_pIAPListView->setVisible(false);
        }
        
        if(!m_pItemListView)
        {
            pItemDataList = GameInfo::sharedGameInfo()->getItemList();

        
            m_pItemListView = CCListView::viewWithMode(CCListViewModeVertical);
            m_pItemListView->retain();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            CCSize listSize = CCSizeMake(winSize.width, (mDiamond->getPositionY() - 20)*0.8);
    
            m_pItemListView->setContentSize(listSize);
            m_pItemListView->setDelegate(this);
            m_pItemListView->setAnchorPoint(ccp(0,0));
            m_pItemListView->setPosition(ccp(0, (mDiamond->getPositionY() - 20)*0.2));
            m_pItemListView->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
            this->addChild(m_pItemListView);
        }
        m_pItemListView->setVisible(true);
    }
    else
    {
        if(m_pItemListView)
        {
            m_pItemListView->setVisible(false);
        }
        
        if(!m_pIAPListView)
        {
            pIAPDataList = GameInfo::sharedGameInfo()->getIAPProductList();
        
        
            m_pIAPListView = CCListView::viewWithMode(CCListViewModeVertical);
            m_pIAPListView->retain();
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            CCSize listSize = CCSizeMake(winSize.width, (mDiamond->getPositionY() - 20)*0.8);
    
            m_pIAPListView->setContentSize(listSize);
            m_pIAPListView->setDelegate(this);
            m_pItemListView->setAnchorPoint(ccp(0,0));
            m_pIAPListView->setPosition(ccp(0, (mDiamond->getPositionY() - 20)*0.2));
            m_pIAPListView->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
            this->addChild(m_pIAPListView);
        }
        
        m_pIAPListView->setVisible(true);
    }
}

void ShopLayer::visit()
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

void ShopLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler ShopLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", ShopLayer::onHomeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDiamondClicked", ShopLayer::onDiamondClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onItemClicked", ShopLayer::onItemClicked);
    
    return NULL;
}


SEL_CCControlHandler ShopLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool ShopLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShopBanner", CCSprite *, mShopBanner);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDiamond", CCMenuItemImage *, mDiamond);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItem", CCMenuItemImage *, mItem);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserDiamond", CCLabelTTF *, mUserDiamond);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserGold", CCLabelTTF *, mUserGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserItem", CCLabelTTF *, mUserItem);
    
    return false;
}

void ShopLayer::CCListView_numberOfCells(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCLOG("ListViewDemoLayer::CCListView_numberOfCells");
    if(isItemSales)
    {
        data->nNumberOfRows = pItemDataList->count();
    }
    else
    {
        data->nNumberOfRows = pIAPDataList->count();
    }
    
}

void ShopLayer::CCListView_cellForRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCSize listSize;
    
    if(isItemSales)
    {
        listSize = m_pItemListView->getContentSize();
    }
    else
    {
        listSize = m_pIAPListView->getContentSize();
    }
    
    CCSize cellSize = CCSizeMake(listSize.width, 46);
    
    CCListViewCell *cell = CCListViewCell::node();
    cell->setOpacity(0);
    cell->setContentSize(cellSize);
    cell->setSelectionColor(ccc4(200, 100, 150, 0)); //set invisible back color after selected

    data->cell = cell;
    
    CCSprite *bgSprite = CCSprite::createWithSpriteFrameName("rank_item1");
    
    bgSprite->setPosition(ccp(cellSize.width/2, cellSize.height/2));
    cell->addChild(bgSprite);
    
    std::string cellValue = "";
    
    if(isItemSales)
    {
        GameItem * gItem = (GameItem *)pItemDataList->objectAtIndex(data->nRow);
        cellValue = CCString::createWithFormat("1枚钻石 兑换 %d %s", gItem->getPrice(), gItem->getItemName().c_str())->getCString();
    }
    else
    {
        cellValue = ((IAPProductInfo *)pIAPDataList->objectAtIndex(data->nRow))->getProductName();

        CCSprite * rmbSprite = CCSprite::createWithSpriteFrameName("rmb");
        rmbSprite->setAnchorPoint(ccp(0.5,0.5));
        rmbSprite->cocos2d::CCNode::setPosition(bgSprite->getPositionX() - bgSprite->getContentSize().width/2 + rmbSprite->getContentSize().width, cellSize.height/2);
        cell->addChild(rmbSprite);
        
        CCSprite * zsSprite = CCSprite::createWithSpriteFrameName("zuanshi");
        zsSprite->setAnchorPoint(ccp(0.5,0.5));
        zsSprite->cocos2d::CCNode::setPosition(bgSprite->getPositionX() + bgSprite->getContentSize().width/2 - zsSprite->getContentSize().width, cellSize.height/2);
        cell->addChild(zsSprite);
    }
    
    
    CCLabelTTF *cellLabel = CCLabelTTF::create(cellValue.c_str(), "Arial", 18);
    cellLabel->setPosition(ccp(cellSize.width/2, cellSize.height/2));
    cell->addChild(cellLabel);
}

void ShopLayer::CCListView_didClickCellAtRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    
    
    if(isItemSales)
    {
        buyItem = (GameItem *)pItemDataList->objectAtIndex(data->nRow);
        NumbersLayer* nLayer =  NumbersLayer::sharedNumbersLayer();
        nLayer->addNumbersToLayer("购买数量", this, this, callfuncO_selector(ShopLayer::onInputNumber));
    }
    else
    {
        NSLog(@"IAP Product ID: %@", [[NSString alloc] initWithCString:((IAPProductInfo *)pIAPDataList->objectAtIndex(data->nRow))->getProductId().c_str() encoding:NSUTF8StringEncoding]);
        
        [[StoreKitFactory sharedStoreKitFactory] removeReceiptData];
        if ([[StoreKitFactory sharedStoreKitFactory] canMakePayments]) {
        
            [[StoreKitFactory sharedStoreKitFactory] requestProductData: [[NSString alloc] initWithCString:((IAPProductInfo *)pIAPDataList->objectAtIndex(data->nRow))->getProductId().c_str() encoding:NSUTF8StringEncoding]];
        }
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        // No explicit autorelease pool needed here.
        // The code runs in background, not strangling
        // the main run loop.
            for (int i = 0; i < 60; i++)
            {
                if([[NSUserDefaults standardUserDefaults]objectForKey:IAP_Receipt])
                {
                    break;
                }
                
                [NSThread sleepForTimeInterval:1];
            }
            
            if([[NSUserDefaults standardUserDefaults]objectForKey:IAP_Receipt])
            {
                GameServerAction::sharedGameServerAction()->checkIAPReceipt(((NSString *)[[NSUserDefaults standardUserDefaults]objectForKey:IAP_Receipt]).UTF8String, [[StoreKitFactory sharedStoreKitFactory] currentTier].UTF8String, 1, this, callfuncND_selector(ShopLayer::checkReceipt_Done));
            }
            
        });

    }
}

void ShopLayer::CCListView_didScrollToRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
}

void ShopLayer::onInputNumber(cocos2d::CCObject *data)
{
    if(data)
    {
        buyItemAmount = ((CCString *) data)->intValue();
        if(buyItemAmount > UserInfo::sharedUserInfo()->getDiamond())
        {
            AlertLayer * shareAlert = AlertLayer::create("杂货店", "您所持有的钻石不足" , false, NULL, NULL);
    
            this->addChild(shareAlert, Child_Order_Top);
        }
        else if(buyItemAmount > 0)
        {
            CCString * msg = CCString::createWithFormat("您将花费 %d 颗钻石购买 %d %s", buyItemAmount, buyItemAmount * buyItem->getPrice(), buyItem->getItemName().c_str());

            AlertLayer * shareAlert = AlertLayer::create("杂货店", msg->getCString() , true, this, callfuncND_selector(ShopLayer::confirmBuyItem));
    
            this->addChild(shareAlert, AlertLayer_Tag);
        }
    }
}

void ShopLayer::confirmBuyItem(cocos2d::CCNode *pNode, void *data)
{
    if((bool)data)
    {
        Loading::sharedLoading()->addLoadingToLayer(this);
        GameServerAction::sharedGameServerAction()->buyItem(buyItem->getItemId(), buyItemAmount, this, callfuncND_selector(ShopLayer::buyItem_Done));
    }
}

void ShopLayer::onHomeClicked(cocos2d::CCObject *pSender)
{
//    SceneControler::sharedSceneControler()->gotoScene(MainBoard_Scene);
    SceneControler::sharedSceneControler()->goBackScene();
}

void ShopLayer::buyItem_Done(cocos2d::CCNode *pNode, void *data)
{
    Loading::sharedLoading()->removeLoading();
    showUserInfo();
    if((bool)data)
    {
        AlertLayer * shareAlert = AlertLayer::create("杂货店", "购买成功啦" , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }
    else
    {
        AlertLayer * shareAlert = AlertLayer::create("杂货店", "购买失败, 请稍后重试" , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }
}

void ShopLayer::updateUserInfo(cocos2d::CCNode *pNode, void *data)
{
    
}

void ShopLayer::onItemClicked(cocos2d::CCObject *pSender)
{
    if(!isItemSales)
    {
        isItemSales = true;
        
        if(hasItemInfo)
        {
            addListView();
        }
        else
        {
            getItemInfo();
        }
    }
}

void ShopLayer::onDiamondClicked(cocos2d::CCObject *pSender)
{
    if(isItemSales)
    {
        isItemSales = false;
        
        if(hasProductInfo)
        {
            addListView();
        }
        else
        {
            getProductInfo();
        }
    }
}

void ShopLayer::checkReceipt_Done(cocos2d::CCNode *pNode, void *data)
{
    Loading::sharedLoading()->removeLoading();
    showUserInfo();
    if((bool)data)
    {
//        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"杂货店"
//                                message:@"购买成功啦"
//                               delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];
//
//        [alerView show];
//        [alerView release];
        
        AlertLayer * shareAlert = AlertLayer::create("杂货店", "购买成功啦" , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }
    else
    {
        AlertLayer * shareAlert = AlertLayer::create("杂货店", "购买失败, 请稍后重试" , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }
}

void ShopLayer::showUserInfo()
{
    mUserDiamond->setString(CCString::createWithFormat("%d",UserInfo::sharedUserInfo()->getDiamond())->getCString());
    mUserGold->setString(CCString::createWithFormat("%d",UserInfo::sharedUserInfo()->getGold())->getCString());
    mUserItem->setString(CCString::createWithFormat("%d",UserInfo::sharedUserInfo()->getMagicItemAmount(MagicItem_Switch_ID))->getCString());
}

void ShopLayer::getItem_Done(cocos2d::CCNode *pNode, void *data)
{
    hasItemInfo = (bool)data;
    if((bool)data)
    {
        addListView();
    }
    else
    {
        AlertLayer * shareAlert = AlertLayer::create("杂货店", "获取购买信息失败, 请稍后重试" , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }
}

void ShopLayer::getProduct_Done(cocos2d::CCNode *pNode, void *data)
{
    hasProductInfo = (bool)data;
    if((bool)data)
    {
        addListView();
    }
    else
    {
        AlertLayer * shareAlert = AlertLayer::create("杂货店", "获取购买信息失败, 请稍后重试" , false, NULL, NULL);
    
        this->addChild(shareAlert, Child_Order_Top);
    }
}