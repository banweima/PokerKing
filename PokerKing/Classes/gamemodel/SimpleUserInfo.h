//
//  SimpleUserInfo.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-27.
//
//

#ifndef __PokerKing__SimpleUserInfo__
#define __PokerKing__SimpleUserInfo__

#include "cocos2d.h"
#include "GameItem.h"
#include "FileHelper.h"



USING_NS_CC;

class SimpleUserInfo : public CCObject
{
private:
    CC_SYNTHESIZE(long, mUserID, UserID);
    CC_SYNTHESIZE(std::string, mUserName, UserName);
    CC_SYNTHESIZE(std::string, mThumbnail, Thumbnail);
    CC_SYNTHESIZE(std::string, mGender, Gender); //0: Male; 1: Female; 2:Unknown
    CC_SYNTHESIZE(int, mLevel, Level);
    CC_SYNTHESIZE(long, mExp, Exp);
    CC_SYNTHESIZE(long, mGold, Gold);
    CC_SYNTHESIZE(std::string, mSNS, SNS);
    CC_SYNTHESIZE_READONLY(CCSprite *, mAvartaImage, AvartaIamge);
    
    CC_SYNTHESIZE(CCArray *, mTodayRecord, TodayRecord);
    CC_SYNTHESIZE(CCArray *, mTotalRecord, TotalRecord);
    
public:    
    static SimpleUserInfo* create(void);
    
    SimpleUserInfo();
    virtual ~SimpleUserInfo();
    virtual bool init(void);
    void parseSimpleUserInfo(CCDictionary * SimpleUserInfoDict);
    
    void retrieveAvartaImage(cocos2d::CCObject *target, SEL_CallFuncND callback);
    
    CCSprite * addAvartaToLayer(CCNode * parentLayer);
    
private:
    CCObject *mTarget;
    SEL_CallFuncND mCallFuncND;
    bool hasAvarteDone;
    void retrieveAvartaImage_Done(CCNode* node, void* data);
    
};


#endif /* defined(__PokerKing__SimpleUserInfo__) */
