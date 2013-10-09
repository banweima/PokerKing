//
//  GameInfo.h
//  blackjack
//
//  Created by Banson Niu on 10/17/12.
//
//

#ifndef __blackjack__GameInfo__
#define __blackjack__GameInfo__

#include "cocos2d.h"
#include "UserInfo.h"
#include "IAPProductInfo.h"
#include "GameItem.h"
#include "EventInfo.h"
#include "RoomLevelInfo.h"


USING_NS_CC;

enum ENV {
    Dev = 0,
    Sandbox,
    Production,
    Standalone
};


enum GameType {
    BlackJack = 0,
    Caribbean,
    VideoPoker,
    Lottery,
    Texas
};

enum SNSType
{
    None = 0,
    GameCenter,
    Weibo,
    QQ
};

class GameInfo : public CCObject
{
private:
    
    CC_SYNTHESIZE(std::string, mLoginServerUrl, LoginServerUrl);
    CC_PROPERTY(std::string, mGameServerUrl, GameServerUrl);
    
    CC_SYNTHESIZE(std::string, mGameDownloadUrl, GameDownloadUrl);
    CC_SYNTHESIZE(std::string, mBannerJumpUrl, BannerJumpUrl);
    CC_SYNTHESIZE(std::string, mBannerImageUrl, BannerImageUrl);
    CC_SYNTHESIZE(std::string, mToken, Token);
    
    CC_SYNTHESIZE(GameType, mCurrentGameType, CurrentGameType);
    CC_SYNTHESIZE(RoomType, mCurrentRoomType, CurrentRoomType);
    CC_SYNTHESIZE(SNSType, mCurrentSNSType, CurrentSNSType);
    
    CC_SYNTHESIZE(CCString *, mDeviceToken, DeviceToken);
    
    CC_SYNTHESIZE(CCArray *, mIAPProductList, IAPProductList);
    
    CC_SYNTHESIZE(CCArray *, mItemList, ItemList);
    
    CC_SYNTHESIZE(CCArray *, mEventsList, EventsList);
    
    CC_SYNTHESIZE(CCArray *, mBossInfoList, BossInfoList);
    
    CC_SYNTHESIZE(CCArray *, mFriendsList, FriendsList);

    
public:
    CC_PROPERTY(ENV, mEnv, Env);
    GameInfo(void);
    virtual ~GameInfo(void);
    virtual bool init(void);
    
    /** returns a shared instance of the director */
    static GameInfo* sharedGameInfo(void);

    std::string getLoginName();
    std::string getLoginPassword();
    
    void parseProductList(CCDictionary * productInfoDict);
    void parseItemList(CCDictionary * itemDict);
    
    void parseEventsList(CCDictionary * itemDict);
    
    void parseUserBossList(CCDictionary * itemDict);
};

#endif /* defined(__blackjack__GameInfo__) */
