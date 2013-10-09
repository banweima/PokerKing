//
//  GameInfo.cpp
//  blackjack
//
//  Created by Banson Niu on 10/17/12.
//
//

#include "GameInfo.h"
#include "Constants.h"
#include "cocos-ext.h"
#include "GameServerAction.h"

USING_NS_CC_EXT;

static GameInfo *pGameInfo = NULL;

GameInfo* GameInfo::sharedGameInfo(void)
{
    if (!pGameInfo)
    {
        pGameInfo = new GameInfo();
        if(pGameInfo && pGameInfo->init())
        {
        }
    }
    
    return pGameInfo;
}

GameInfo::GameInfo()
: mEnv(Dev),
mLoginServerUrl(""),
mGameServerUrl(""),
mToken(""),
mDeviceToken(NULL)
, mGameDownloadUrl("")
, mBannerJumpUrl("")
, mBannerImageUrl("")
{}

GameInfo::~GameInfo()
{
    CC_SAFE_RELEASE(mIAPProductList);
    CC_SAFE_RELEASE(mDeviceToken);
    CC_SAFE_RELEASE(mItemList);
    CC_SAFE_RELEASE(mEventsList);
}

bool GameInfo::init()
{
    mCurrentGameType = BlackJack;
    mCurrentRoomType = Hongkong_R;
    
    mIAPProductList = CCArray::create();
    mIAPProductList->retain();
    
    mItemList = CCArray::create();
    mItemList->retain();
    
    mEventsList = CCArray::create();
    mEventsList->retain();
    
    mBossInfoList = CCArray::create();
    mBossInfoList->retain();
    
    mFriendsList = CCArray::create();
    mFriendsList->retain();
    
    mGameDownloadUrl = "https://itunes.apple.com/cn/app/wei-bo/id350962117?l=en&mt=8";
    mBannerJumpUrl = "http://www.weibo.com";
    mBannerImageUrl = "http://stock.591hx.com/images/hnimg/201309/11/62/4570829793271345294.jpg";
    return true;
}

std::string GameInfo::getLoginName()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey(UserName, "");
}

std::string GameInfo::getLoginPassword()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey(Password, "");
}

void GameInfo::setEnv(ENV var)
{
    mEnv = var;
    
    switch (mEnv) {
        case Dev:
            mLoginServerUrl = LoginServer_Dev;
            break;
        case Sandbox:
            mLoginServerUrl = LoginServer_Sandbox;
            break;
        case Production:
            mLoginServerUrl = LoginServer_Production;
            break;
        default:
            break;
    }
}

ENV GameInfo::getEnv()
{
    return mEnv;
}

void GameInfo::setGameServerUrl(std::string url)
{
    mGameServerUrl = url + "/";
}

std::string GameInfo::getGameServerUrl()
{
    return mGameServerUrl;
}

void GameInfo::parseProductList(cocos2d::CCDictionary *productInfoDict)
{

    mIAPProductList = CCArray::create();
    mIAPProductList->retain();
    
    CCArray * productList = (CCArray *)productInfoDict->objectForKey("product");
    if(!productList)
    return;
    
    IAPProductInfo * productInfo = NULL;
    CCDictionary * productDic = NULL;
    for(int i = 0; i < productList->count(); i ++)
    {
        productDic = (CCDictionary *)productList->objectAtIndex(i);

        productInfo = IAPProductInfo::create();
        productInfo->parseIAPProductInfo(productDic);
        mIAPProductList->addObject(productInfo);
    }
}

void GameInfo::parseItemList(CCDictionary * itemDict)
{
    mItemList = CCArray::create();
    mItemList->retain();
    
    CCArray * itemList = (CCArray *)itemDict->objectForKey("ItemInfor");
    
    if(!itemList)
    return;
    
    GameItem * gameItem = NULL;
    CCDictionary * dic = NULL;
    for(int i = 0; i < itemList->count(); i ++)
    {
        dic = (CCDictionary *)itemList->objectAtIndex(i);

        gameItem = GameItem::create();
        gameItem->parseGameItem(dic);
        mItemList->addObject(gameItem);
    }
}


void GameInfo::parseEventsList(CCDictionary * itemDict)
{
    mEventsList = CCArray::create();
    mEventsList->retain();
    
    CCArray * etList = (CCArray *)itemDict->objectForKey("eventInfo");
    
    if(!etList)
    return;
    
    EventInfo * eventInfo = NULL;
    CCDictionary * dic = NULL;
    for(int i = 0; i < etList->count(); i ++)
    {
        dic = (CCDictionary *)etList->objectAtIndex(i);

        eventInfo = EventInfo::create();
        eventInfo->parseEventInfo(dic);
        mEventsList->addObject(eventInfo);
    }
}

void GameInfo::parseUserBossList(CCDictionary * itemDict)
{
    if(mBossInfoList)
    {
        mBossInfoList->release();
        mBossInfoList = CCArray::create();
        mBossInfoList->retain();
    }
    
    CCArray * etList = (CCArray *)itemDict->objectForKey("bossInstance");
    
    if(!etList)
    return;
    
    RaidBossInfo * bossInfo = NULL;
    CCDictionary * dic = NULL;
    for(int i = 0; i < etList->count(); i ++)
    {
        dic = (CCDictionary *)etList->objectAtIndex(i);

        bossInfo = RaidBossInfo::create();
        bossInfo->parseRaidBossInfo(dic);
        mBossInfoList->addObject(bossInfo);
    }
}
