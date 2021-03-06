//
//  InvitationLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-13.
//
//

#include "InvitationLayer.h"

#include "CCBUtility.h"
#include "Constants.h"
#include "SceneControler.h"
#include "NumbersLayer.h"
#include "UserInfo.h"
#include "WeiboFactory.h"
#include "AlertLayer.h"
#include "GameInfo.h"
#include "Banner.h"


InvitationLayer::InvitationLayer()
: mAccept(NULL)
, mSend(NULL)
, mCode(NULL)
, mNumber(NULL)
, mCodeInput(NULL)
, mInviteCode(NULL)
, mFriendsNumber(NULL)
{}

InvitationLayer::~InvitationLayer()
{
    CC_SAFE_RELEASE(mAccept);
    CC_SAFE_RELEASE(mSend);
    CC_SAFE_RELEASE(mCode);
    CC_SAFE_RELEASE(mNumber);
    CC_SAFE_RELEASE(mCodeInput);
    CC_SAFE_RELEASE(mInviteCode);
    CC_SAFE_RELEASE(mFriendsNumber);
    
}

bool InvitationLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        this->setupLayer();
        
        bRet = true;
    } while (0);
    
	return bRet;
}

void InvitationLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/invitation.ccbi", "InvitationLayer", CCLayerLoader::loader(), this);
    
    this->addChild(node);
    
    int h = getWinH();
    if(h>480)
    {
        Banner * banner = Banner::create();
        banner->retain();
        this->addChild(banner,-100);
    }
    
    mCode->setString( CCString::createWithFormat("%l", UserInfo::sharedUserInfo()->getUserID())->getCString());
    
    mCode->setString(CCString::createWithFormat("%d", UserInfo::sharedUserInfo()->getUserID())->getCString());
    
    mFriendsNumber->setString(CCString::createWithFormat("%d", UserInfo::sharedUserInfo()->getFriendsList()->count())->getCString());
    
}

void InvitationLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler InvitationLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", InvitationLayer::onHomeClicked);

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAcceptClicked", InvitationLayer::onAcceptClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSendClicked", InvitationLayer::onSendClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onInviteTextClicked", InvitationLayer::onInviteCodeClicked);
    
    
    return NULL;
}

SEL_CCControlHandler InvitationLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    
    return NULL;
}

bool InvitationLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAccept", CCMenuItemImage *, mAccept);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSend", CCMenuItemImage *, mSend);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCode", CCLabelTTF *, mCode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNumber", CCLabelTTF *, mNumber);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCodeInput", CCLabelTTF *, mCodeInput);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInviteCode", CCLabelTTF *, mInviteCode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFriendsNumber", CCLabelTTF *, mFriendsNumber);

    
    return false;
}


void InvitationLayer::onHomeClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->goBackScene();
}

void InvitationLayer::onAcceptClicked(cocos2d::CCObject *pSender)
{
    CCLOG("onAcceptClicked");
    GameServerAction::sharedGameServerAction()->accessFriendInvitationCode( mInviteCode->getString(), this, callfuncO_selector( InvitationLayer::acceptCode_Done));
}

void InvitationLayer::acceptCode_Done(CCObject *data)
{
    std::string msg = "";
    std::string title = "好友邀请";
    if(data)
    {
       CCDictionary * dict = (CCDictionary* )data;
       msg = ((CCString *)((CCDictionary *) dict->objectForKey("invitedInfo"))->objectForKey("repDesc"))->getCString();
    }
    else
    {
        msg = "发送失败，请稍后再试";
    }
    
    AlertLayer * shareAlert = AlertLayer::create(title.c_str(), msg.c_str() , false, NULL, NULL);
    
    this->addChild(shareAlert, Child_Order_Top);
}

void InvitationLayer::onSendClicked(cocos2d::CCObject *pSender)
{
    CCLOG("onSendClicked");
    
//    NSString * value = [[NSString alloc] initWithFormat:@"PokerKing来了，轻松又好玩的扑克游戏，更有赌王等你来挑战。填写我的邀请码，豪礼一起拿！ 我的邀请码 %s", mCode->getString()];
    
    NSString * value = [[NSString alloc] initWithFormat:@"PokerKing来了，轻松又好玩的扑克游戏，更有赌王等你来挑战。填写邀请码，豪礼一起拿！ 我的邀请码 %s \n下载地址：%s", mCode->getString(), GameInfo::sharedGameInfo()->getGameDownloadUrl().c_str() ];
    
    [[WeiboFactory sharedWeiboFactory] uploadStatus:value];
    
    AlertLayer * shareAlert = AlertLayer::create("微博", "发送成功！", false, NULL, NULL);
    
    this->addChild(shareAlert, Child_Order_Top);
    
}

void InvitationLayer::onInviteCodeClicked(cocos2d::CCObject *pSender)
{
    mInviteCode->setString("");
    NumbersLayer* nLayer =  NumbersLayer::sharedNumbersLayer();
        nLayer->addNumbersToLayer("输入邀请码", this, this, callfuncO_selector(InvitationLayer::onInputNumber));
}

void InvitationLayer::onInputNumber(cocos2d::CCObject *data)
{
    if(data)
    {
        mInviteCode->setString(((CCString * )data)->getCString());
    }
}
