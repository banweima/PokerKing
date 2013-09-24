//
//  EventInfo.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-16.
//
//

#include "EventInfo.h"
#include "ImageController.h"


USING_NS_CC_EXT;

EventInfo* EventInfo::create()
{
    EventInfo* pEventInfo = new EventInfo();
    
    if (pEventInfo && pEventInfo->init())
    {
        pEventInfo->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pEventInfo);
    }
    
    return pEventInfo;

}


void EventInfo::parseEventInfo(CCDictionary * EventInfoDic)
{    
    mTitle = ((CCString *)EventInfoDic->objectForKey("title"))->getCString();
    
    mDescription = ((CCString *)EventInfoDic->objectForKey("description"))->getCString();
    
    mImageUrl = ((CCString *)EventInfoDic->objectForKey("imageUrl"))->getCString();
    
}


bool EventInfo::init()
{
    mTitle = "";
    mDescription = "";
    mImageUrl = "";
    return true;
}


CCSprite * EventInfo::addEventImageToLayer(cocos2d::CCLayer *parentLayer)
{
    if(mEventImage->getParent())
    {
        mEventImage->removeFromParentAndCleanup(false);
    }
    
    parentLayer->addChild(mEventImage,Child_Order_Low);
    
    return mEventImage;
}

void EventInfo::retrieveEventImage(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    ImageController * imageCon = new ImageController();
    imageCon->retrieveAvartaImage(mImageUrl, this, callfuncO_selector(EventInfo::retrieveAvartaImage_Done));
}

void EventInfo::retrieveAvartaImage_Done(cocos2d::CCObject *data)
{

    if(data)
    {
        mEventImage = (CCSprite *) data;
        mEventImage->retain();
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            } 
    }
}
