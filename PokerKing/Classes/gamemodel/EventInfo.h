//
//  EventInfo.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-16.
//
//

#ifndef __PokerKing__EventInfo__
#define __PokerKing__EventInfo__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"

USING_NS_CC;


class EventInfo : public CCObject
{
public:
    CC_SYNTHESIZE(std::string, mTitle, Title);
    CC_SYNTHESIZE(std::string, mDescription, Description);
    CC_SYNTHESIZE(std::string, mImageUrl, ImageUrl);
    CC_SYNTHESIZE_READONLY(CCSprite *, mEventImage, EventIamge);

public:
    static EventInfo* create();
    void parseEventInfo(CCDictionary * EventInfoDic);
    bool init();
    void retrieveEventImage(cocos2d::CCObject *target, SEL_CallFuncND callback);
    CCSprite * addEventImageToLayer(CCLayer * parentLayer);
    
private:
    void retrieveAvartaImage_Done(CCObject* data);
    CCObject *mTarget;
    SEL_CallFuncND mCallFuncND;
};

#endif /* defined(__PokerKing__EventInfo__) */
