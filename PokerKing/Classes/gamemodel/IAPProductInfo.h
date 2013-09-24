//
//  IAPProductInfo.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-21.
//
//

#ifndef __PokerKing__IAPProductInfo__
#define __PokerKing__IAPProductInfo__

#include <iostream>


#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;


class IAPProductInfo : public CCObject
{
public:
    CC_SYNTHESIZE(int, mDiamondAmount, DiamondAmount);
    CC_SYNTHESIZE(float, mPrice, Price);
    CC_SYNTHESIZE(std::string, mProductName, ProductName);
    CC_SYNTHESIZE(std::string, mProductId, ProductId);

    
public:
    static IAPProductInfo* create();
    void parseIAPProductInfo(CCDictionary * IAPProductInfoDic);
    bool init();
};

#endif /* defined(__PokerKing__IAPProductInfo__) */
