//
//  SimpleUserInfo.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-27.
//
//

#include "SimpleUserInfo.h"
#include "cocos-ext.h"
#include "JSONValueUtil.h"
#include "SimpleUserInfo.h"
#include "GameServer.h"
#include "Constants.h"
#include "GameServerAction.h"
#include "HttpImageLoader.h"
#include "CCImage.h"


USING_NS_CC_EXT;

SimpleUserInfo* SimpleUserInfo::create(void)
{

    SimpleUserInfo * pSimpleUserInfo = new SimpleUserInfo();

    if (pSimpleUserInfo && pSimpleUserInfo->init())
    {
        pSimpleUserInfo->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pSimpleUserInfo);
    }
    
    return pSimpleUserInfo;
}

SimpleUserInfo::SimpleUserInfo()
{
    
}

SimpleUserInfo::~SimpleUserInfo()
{
    CC_SAFE_RELEASE_NULL(mAvartaImage);
}

void SimpleUserInfo::parseSimpleUserInfo(CCDictionary * SimpleUserInfoDict)
{
    this->setUserID(((CCString *)SimpleUserInfoDict->objectForKey("userId"))->doubleValue());
    this->setUserName(((CCString *)SimpleUserInfoDict->objectForKey("nickName"))->getCString());
    this->setGender(((CCString *)SimpleUserInfoDict->objectForKey("gender"))->getCString());
    this->setThumbnail(((CCString *)SimpleUserInfoDict->objectForKey("image"))->getCString());
    this->setLevel(((CCString *)SimpleUserInfoDict->objectForKey("level"))->intValue());
    this->setExp(((CCString *)SimpleUserInfoDict->objectForKey("exp"))->doubleValue());
    this->setGold(((CCString *)SimpleUserInfoDict->objectForKey("gold"))->doubleValue());
    
    
    if(SimpleUserInfoDict->objectForKey("bossImageUrl"))
    {
    
    }
}


bool SimpleUserInfo::init()
{
    mUserID = 10000;
    mUserName = "Guest";
    mThumbnail = "http://mobage.cn/img_u3/6610003/0.jpg?c=0";
    mLevel = 1;
    mGold = 2000;
    mExp = 1234;
    mGender = "m";
    hasAvarteDone = false;
    mAvartaImage = NULL;
    mTodayRecord = CCArray::create();
    mTodayRecord->retain();
    
    mTotalRecord = CCArray::create();
    mTotalRecord->retain();
    
    return true;
}

void SimpleUserInfo::retrieveAvartaImage(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    
    mTarget = target;
    mCallFuncND = callback;
    
    CCLOG("retrieveAvartaImage UserId: %d",mUserID);
    
    if(hasAvarteDone)
    {
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            }
    }
    else
    {
        if(mThumbnail == "")
        {
            if (mGender == "m")
            {
                mAvartaImage = CCSprite::createWithSpriteFrameName("crown_king");
            }
            else
            {
                mAvartaImage = CCSprite::createWithSpriteFrameName("crown_queen");
            }
            
            mAvartaImage->retain();
            if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
                }
            
            CCLOG("UserId: %d  Done",mUserID);
            return;
        
        }
        
        CCString * userImageKey = CCString::createWithFormat("u%d", mUserID);
        CCString * userImageFileName = CCString::createWithFormat("u%d.png", mUserID);
        
        if(LoadStringFromXML(userImageKey->getCString()) == mThumbnail)
        {
            CCImage* img = new CCImage();
            const char * imgPathName = (CCFileUtils::sharedFileUtils()->getWriteablePath() + userImageFileName->getCString()).c_str();
            
            
            if(img->initWithImageFileThreadSafe(imgPathName))
            {
                CCLog("Load from cache, image size = %d, %d", img->getWidth(), img->getHeight());

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
                imageLoader1->retrieveImageData(mThumbnail.c_str(), userImageFileName->getCString(),this, callfuncND_selector(SimpleUserInfo::retrieveAvartaImage_Done));
            }
        }
        else
        {
            CCLog("Load from network");
            SaveStringToXML(userImageKey->getCString(), mThumbnail);
            
            HttpImageLoader *imageLoader1 = HttpImageLoader::create();
            imageLoader1->retrieveImageData(mThumbnail.c_str(), userImageFileName->getCString(),this, callfuncND_selector(SimpleUserInfo::retrieveAvartaImage_Done));
        }
    }
}

void SimpleUserInfo::retrieveAvartaImage_Done(cocos2d::CCNode *node, void *data)
{
    CCLog("retrieveAvartaImage_Done");
    CCLOG("UserId: %d  Done",mUserID);
    CCTexture2D* tex2d = (CCTexture2D*)data;
    
    mAvartaImage = CCSprite::createWithTexture(tex2d);
    
    mAvartaImage->retain();
    hasAvarteDone = true;
    if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            } 
}

CCSprite * SimpleUserInfo::addAvartaToLayer(cocos2d::CCNode *parentLayer)
{
    if(mAvartaImage->getParent())
    {
        mAvartaImage->removeFromParentAndCleanup(false);
    }
    
    parentLayer->addChild(mAvartaImage,Child_Order_Low);
    
    return mAvartaImage;
}

