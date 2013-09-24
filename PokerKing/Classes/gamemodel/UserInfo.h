//
//  UserInfo.h
//  blackjack
//
//  Created by Banson Niu on 10/17/12.
//
//

#ifndef __blackjack__UserInfo__
#define __blackjack__UserInfo__

#include "cocos2d.h"
#include "GameItem.h"
#include "FileHelper.h"
#include "SimpleUserInfo.h"



USING_NS_CC;

class UserInfo : public CCObject
{
private:
    CC_SYNTHESIZE(long, mUserID, UserID);
    CC_SYNTHESIZE(std::string, mSNSID, SNSID);
    CC_SYNTHESIZE(std::string, mUserName, UserName);
    CC_SYNTHESIZE(std::string, mThumbnail, Thumbnail);
    CC_SYNTHESIZE(std::string, mGender, Gender); //0: Male; 1: Female; 2:Unknown
    CC_SYNTHESIZE(int, mLevel, Level);
    CC_SYNTHESIZE(long, mExp, Exp);
    CC_SYNTHESIZE(long, mGold, Gold);
    CC_SYNTHESIZE(long, mDiamond, Diamond);
    CC_SYNTHESIZE(long, mMedal, Medal);
    
    CC_SYNTHESIZE_READONLY(CCSprite *, mAvartaImage, AvartaIamge);
    
    CC_SYNTHESIZE(CCArray *, mItemList, ItemList);
    CC_SYNTHESIZE(CCArray *, mFriendsList, FriendsList);

public:    
    static UserInfo* sharedUserInfo(void);
    
    UserInfo();
    virtual ~UserInfo();
    virtual bool init(void);
    void parseUserInfo(CCDictionary * userInfoDict);

//    void getDetailUserInfo(CCObject *target, SEL_CallFuncND call);
    int getMagicItemAmount(std::string itemId);

    void uploadUserInfo();
    
    void updateUserInfo();
    
    void retrieveAvartaImage(cocos2d::CCObject *target, SEL_CallFuncND callback);
    
    CCSprite * addAvartaToLayer(CCLayer * parentLayer);
    
    void retrieveFriendsList();
    
    
private:
    CCObject *mTarget;
    SEL_CallFuncND mCallFuncND;
    bool hasAvarteDone;
    void retrieveAvartaImage_Done(CCNode* node, void* data);
    
    
    void retrieveFriendsList_Done(cocos2d::CCObject *data);
    
    
};

#endif /* defined(__blackjack__UserInfo__) */
