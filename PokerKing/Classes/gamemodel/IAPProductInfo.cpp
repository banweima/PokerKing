//
//  IAPProductInfo.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-21.
//
//

#include "IAPProductInfo.h"


USING_NS_CC_EXT;

IAPProductInfo* IAPProductInfo::create()
{
    IAPProductInfo* pIAPProductInfo = new IAPProductInfo();
    
    if (pIAPProductInfo && pIAPProductInfo->init())
    {
        pIAPProductInfo->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pIAPProductInfo);
    }
    
    return pIAPProductInfo;

}


void IAPProductInfo::parseIAPProductInfo(CCDictionary * IAPProductInfoDic)
{    
    mDiamondAmount = ((CCString *)IAPProductInfoDic->objectForKey("diamond"))->intValue();
    
    mPrice = ((CCString *)IAPProductInfoDic->objectForKey("unit"))->floatValue();
    
    mProductName = ((CCString *)IAPProductInfoDic->objectForKey("productName"))->getCString();
    
    mProductId = ((CCString *)IAPProductInfoDic->objectForKey("productId"))->getCString();
}


bool IAPProductInfo::init()
{
    mDiamondAmount = 10;
    mPrice = 6.0f;
    mProductName = "一小袋钻石";
    mProductId = "pokerking.diamond.tier01";
    return true;
}