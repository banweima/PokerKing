//
//  UserInfo.cpp
//  blackjack
//
//  Created by Banson Niu on 10/17/12.
//
//

#include "UserInfo.h"
#include "cocos-ext.h"
#include "JSONValueUtil.h"
#include "UserInfo.h"
#include "GameServer.h"
#include "Constants.h"
#include "GameServerAction.h"
#include "HttpImageLoader.h"


USING_NS_CC_EXT;

static UserInfo *pUserInfo = NULL;

UserInfo* UserInfo::sharedUserInfo(void)
{
    if (!pUserInfo)
    {
        pUserInfo = new UserInfo();
        if(pUserInfo && pUserInfo->init())
        {
            
        }
    }
    
    return pUserInfo;
}

UserInfo::UserInfo()
{
    
}

UserInfo::~UserInfo()
{
    CC_SAFE_RELEASE(mAvartaImage);
    CC_SAFE_RELEASE(mItemList);
    CC_SAFE_RELEASE(mFriendsList);
}

void UserInfo::parseUserInfo(CCDictionary * userInfoDict)
{
    this->setUserID(((CCString *)userInfoDict->objectForKey("userId"))->doubleValue());
//    this->setUserName(((CCString *)userInfoDict->objectForKey("nickName"))->getCString());
//    this->setGender(((CCString *)userInfoDict->objectForKey("gender"))->getCString());
//    this->setThumbnail(((CCString *)userInfoDict->objectForKey("image"))->getCString());
    this->setLevel(((CCString *)userInfoDict->objectForKey("level"))->intValue());
    this->setExp(((CCString *)userInfoDict->objectForKey("exp"))->doubleValue());
    this->setGold(((CCString *)userInfoDict->objectForKey("gold"))->doubleValue());
    this->setDiamond(((CCString *)userInfoDict->objectForKey("diamond"))->doubleValue());
    
    mItemList->removeAllObjects();
    
    
    CCArray * userItemList = (CCArray *)userInfoDict->objectForKey("items");
    if(userItemList)
    {
        GameItem * pGameItem = GameItem::create();
        
        for(int i = 0; i < userItemList->count(); i ++)
        {
            CCDictionary * itemDic = (CCDictionary *)userItemList->objectAtIndex(i);
            pGameItem = GameItem::create();
            pGameItem->parseGameItem(itemDic);
            mItemList->addObject(pGameItem);
            if(pGameItem->getItemId() == "4")
            {
                mMedal = pGameItem->getQuantity();
            }
        }
    }
}


bool UserInfo::init()
{
    mUserID = 10000;
    mUserName = "Guest";
    mThumbnail = "";
    mLevel = 1;
    mGold = 0;
    mDiamond = 0;
    mExp = 0;
    mGender = "m";
    mSNSID = "";
    mItemList = CCArray::create();
    mItemList->retain();
    mMedal = 0;
    hasAvarteDone = false;
    return true;
}


int UserInfo::getMagicItemAmount(std::string itemId)
{
    for(int i = 0; i < mItemList->count(); i++)
    {
        GameItem * pItem = (GameItem *) mItemList->objectAtIndex(i);
        
        if (pItem->getItemId() == itemId)
        {
            return pItem->getQuantity();
        }
    
    }
    return 0;
}


void UserInfo::uploadUserInfo()
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        for(int i = 0; i < 3; i ++)
        {
            if(GameServerAction::sharedGameServerAction()->updateUserInfo(NULL, NULL))
            {
            
                return;
            }
            
            [NSThread sleepForTimeInterval:10];
        }
    });
}

void UserInfo::retrieveAvartaImage(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    
    mTarget = target;
    mCallFuncND = callback;
    
    if(hasAvarteDone)
    {
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            }
    }
    else
    {
        if(LoadStringFromXML(PlayerImageFileName) == mThumbnail)
        {
            CCImage* img = new CCImage();
            const char * imgPathName = (CCFileUtils::sharedFileUtils()->getWriteablePath() + PlayerImageFileName).c_str();
            
            
            if(img->initWithImageFile(imgPathName))
            {
                CCLog("img size = %d, %d", img->getWidth(), img->getHeight());

                CCTexture2D* texture2D = new CCTexture2D();
                texture2D->initWithImage(img);
                
                mAvartaImage = CCSprite::createWithTexture(texture2D);
                mAvartaImage->retain();
                hasAvarteDone = true;
                
                if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
                } 
            }
            else
            {
                HttpImageLoader *imageLoader1 = HttpImageLoader::create();
                imageLoader1->retrieveImageData(mThumbnail.c_str(), PlayerImageFileName ,this, callfuncND_selector(UserInfo::retrieveAvartaImage_Done));
            }
        }
        else
        {
            SaveStringToXML(PlayerImageFileName, mThumbnail);
            
            HttpImageLoader *imageLoader1 = HttpImageLoader::create();
            imageLoader1->retrieveImageData(mThumbnail.c_str(), PlayerImageFileName,this, callfuncND_selector(UserInfo::retrieveAvartaImage_Done));
        }
    }

}

void UserInfo::retrieveAvartaImage_Done(cocos2d::CCNode *node, void *data)
{
    CCLog("retrieveAvartaImage_Done");
    
    CCTexture2D* tex2d = (CCTexture2D*)data;
    
    mAvartaImage = CCSprite::createWithTexture(tex2d);
    
    mAvartaImage->retain();
    hasAvarteDone = true;
    if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            } 
}

CCSprite * UserInfo::addAvartaToLayer(cocos2d::CCLayer *parentLayer)
{
    if(mAvartaImage->getParent())
    {
        mAvartaImage->removeFromParentAndCleanup(false);
    }
    
    parentLayer->addChild(mAvartaImage,Child_Order_Low);
    
    return mAvartaImage;
}

void UserInfo::retrieveFriendsList()
{
    GameServerAction::sharedGameServerAction()->getFriends(this, callfuncO_selector(UserInfo::retrieveFriendsList_Done));
}

void UserInfo::retrieveFriendsList_Done(cocos2d::CCObject *data)
{
    if(data)
    {

        mFriendsList = CCArray::create();
        mFriendsList->retain();
        
        CCDictionary *dict = (CCDictionary *)data;
        
        CCArray * etList = (CCArray *)dict->objectForKey("friends");
    
        if(!etList || etList->count() < 1)
        {
            return;
        }
        SimpleUserInfo * simpleUserInfo = NULL;
        CCDictionary * dic = NULL;
        for(int i = 0; i < etList->count(); i ++)
        {
            dic = (CCDictionary *)etList->objectAtIndex(i);

            simpleUserInfo = SimpleUserInfo::create();
            simpleUserInfo->parseSimpleUserInfo(dic);
            simpleUserInfo->retrieveAvartaImage(NULL, NULL);
            mFriendsList->addObject(simpleUserInfo);
        }

    }
}
