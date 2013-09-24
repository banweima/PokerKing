//
//  GameItem.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-25.
//
//

#ifndef __PokerKing__GameItem__
#define __PokerKing__GameItem__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;


class GameItem : public CCObject
{
public:
    CC_SYNTHESIZE(std::string, mItemId, ItemId);
    CC_SYNTHESIZE(std::string, mItemName, ItemName);
    CC_SYNTHESIZE(int, mQuantity, Quantity);
    CC_SYNTHESIZE(int, mGameType, GAmeType);
    CC_SYNTHESIZE(std::string, mComment, Comment);
    CC_SYNTHESIZE(int, mPrice, Price);
    
public:
    static GameItem* create();
    void parseGameItem(CCDictionary * GameItemDic);
    bool init();
    
    CCString * getValueFromDic(std::string);
};


#endif /* defined(__PokerKing__GameItem__) */
