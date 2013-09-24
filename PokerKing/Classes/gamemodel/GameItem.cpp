//
//  GameItem.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-25.
//
//

#include "GameItem.h"



USING_NS_CC_EXT;

GameItem* GameItem::create()
{
    GameItem* pGameItem = new GameItem();
    
    if (pGameItem && pGameItem->init())
    {
        pGameItem->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pGameItem);
    }
    
    return pGameItem;

}


void GameItem::parseGameItem(CCDictionary * GameItemDic)
{
    if(GameItemDic->objectForKey("itemId"))
    {
        mItemId = ((CCString *)GameItemDic->objectForKey("itemId"))->getCString();
    }
    else if(GameItemDic->objectForKey("id"))
    {
        mItemId = ((CCString *)GameItemDic->objectForKey("id"))->getCString();
    }
    
    if(GameItemDic->objectForKey("itemName"))
    mItemName = ((CCString *)GameItemDic->objectForKey("itemName"))->getCString();
    
    if(GameItemDic->objectForKey("itemNum"))
    mQuantity = ((CCString *)GameItemDic->objectForKey("itemNum"))->intValue();
    
    if(GameItemDic->objectForKey("gameType"))
    mGameType = ((CCString *)GameItemDic->objectForKey("gameType"))->intValue();
    
    if(GameItemDic->objectForKey("comment"))
    mComment = ((CCString *)GameItemDic->objectForKey("comment"))->getCString();
    
    
    if(GameItemDic->objectForKey("itemPrice"))
    mPrice = ((CCString *)GameItemDic->objectForKey("itemPrice"))->intValue();
}


bool GameItem::init()
{
    mItemId  = "1";
    mItemName = "魔术棒";
    mQuantity = 1;
    mGameType = 0;
    mComment = "随便用用";
    mPrice = 1;
    return true;
}
