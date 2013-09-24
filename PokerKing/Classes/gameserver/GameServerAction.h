//
//  GameServerAction.h
//  blackjack
//
//  Created by Niu Xiaoming on 12-11-18.
//
//

#ifndef blackjack_GameServerAction_h
#define blackjack_GameServerAction_h

//Login
#define Act_login "userAuth.action"


//User
#define Act_get_user "userProfile.action"
#define Act_update_user "updateUserProfile.action"
//Get Game Room level
#define Act_get_room_info   "showRoom.action"

#define Act_consume_item "consumeItem.action"

#define Act_get_IAPProducts "productInfo.action"

#define Act_start_battle "startBattle.action"
#define Act_end_battle "endBattle.action"

#define Act_check_receipt "iapPurchase.action"
#define Act_get_items "showItem.action"
#define Act_buy_item "buyItem.action"

#define Act_broadcast "broadCastInfo.action"

#define Act_ranking "rankTimes.action"

#define Act_share_boss "shareBoss.action"

#define Act_show_userboss "showUserBoss.action"

#define Act_show_events "showEvent.action"

#define Act_gameuser_info "gameUserInfo.action"

#define Act_friends_player "showNoFriend.action"

#define Act_friends_request "sendRequestFriend.action"

#define Act_friends_show "showFriends.action"

#define Act_friends_accept "acceptRequestFriend.action"

#define Act_friends_cancel "cancelRequestFriend.action"

#define Act_friends_remove "removeFriends.action"

#define Act_friends_query_request "querryRequestFriend.action"

#define Act_friends_invitation_access  "accessCode.action"

//#define Act_rank_blackjack "showBlackJackRank.action"

#define Act_rank_all "showTotalTimes.action"

//#define Act_rank_game "showResultGame.action"

#define Act_get_task "taskInfo.action"

#define Act_complete_task "taskComplete.action"

#define Act_chat_send "addChatContent.action"

#define Act_chat_get "showChatContent.action"


#include "cocos2d.h"
#include "UserInfo.h"
#include "cocos-ext.h"
#include "JSONValueUtil.h"
#include "GameServer.h"
#include "GameInfo.h"
#include "GameServerResponse.h"
#include "BattleInfo.h"
#include "GameLevelInfo.h"
#include "BroadCast.h"
#include "GameRoomLayer.h"

USING_NS_CC;

class GameServerAction : public CCObject
{
private:
    GameServerAction (void);
    virtual ~GameServerAction(void);
    virtual bool init(void);
    
//    void upload21MatchResult_Done(CCObject *data);
    
    void useMagicItem_Done(CCObject *data);
    
//    bool checkResponseIsOK(GameServerResponse * response);
    
    void getGameRoomInfo_Done(CCObject * data);
    
    void doLogin_Done(CCObject * data);
    
    void updateUserInfo_Done(CCObject * data);
//    void doCheckIn_Done(CCObject* data);
    
    void getUserInfo_Done(CCObject * data);
    
    void startBattle_Done(CCObject * data);
    
    void endBattle_Done(CCObject * data);
    
    void checkIAPReceipt_Done(CCObject * data);
    
    void retrieveProductList_Done(CCObject * data);
    void getItem_Done(CCObject * data);
    void buyItem_Done(CCObject * data);
    
    void retrieveBroadcast_Done(CCObject * data);
    
    void getRanking_Done(CCObject * data);
    
    void shareBoss_Done(CCObject * data);
    
    void showUserBoss_Done(CCObject * data);
    
    void showEvents_Done(CCObject * data);
    
    void getNormalPlayer_Done(CCObject * data);
    
    void getFriends_Done(CCObject * data);

    void getFriendsRequest_Done(CCObject * data);

    void sendFriendInvitation_Done(CCObject * data);
    
    void removeFriend_Done(CCObject * data);
    
    void acceptFriendRequest_Done(CCObject * data);
    
    void rejectFriendRequest_Done(CCObject * data);
    
    void getBlackjackRank_Done(CCObject * data);
    
    void showTotalTimes_Done(CCObject * data);
    
    void sendChatContent_Done(CCObject * data);
    
    void getChatContent_Done(CCObject * data);
    
    void getTask_Done(CCObject * data);
    
    void completeTask_Done(CCObject * data);
    
    void accessFriendInvitationCode_Done(CCObject * data);
    
    void getGameUserInfo_Done(CCObject * data);
public:
    void useMagicItem(std::string itemId, int count, CCObject *target, SEL_CallFuncND callback);

    void getGameRoomInfo(GameType gameType, CCObject *target, SEL_CallFuncND callback);
    
    void getUserInfo(CCObject *target, SEL_CallFuncND callback);
    
    /** returns a shared instance of the director */
    static GameServerAction* sharedGameServerAction(void);
    
    bool startBattle(GameType gameType, BattleType battleType, long battlePrice, RoomType roomLevel,CCObject *target, SEL_CallFuncND callback);
    
    bool endBattle(long battleResultPrice, int intSpecialWin, RoomType roomLevel, CCObject *target, SEL_CallFuncND callback);
    
    
    void updateBattle(GameType gameType, BattleType battleType, long battlePrice, CCObject *target, SEL_CallFuncO callback);
    
    void updateBattle_Done(CCObject * data);
    
    
    bool doLogin(SNSType snsType,CCObject *target, SEL_CallFuncND callback);
    
    bool updateUserInfo(CCObject *target, SEL_CallFuncND callback);
    
    bool retrieveProductList(CCObject *target, SEL_CallFuncND callback);
    
    bool checkIAPReceipt(std::string receipt, std::string productId, int quantity, CCObject *target, SEL_CallFuncND callback);
    
    bool getItems(CCObject *target, SEL_CallFuncND callback);
    
    bool buyItem(std::string itemId, int quantity, CCObject *target, SEL_CallFuncND callback);
    
    bool retrieveBroadcast(CCObject *target, SEL_CallFuncND callback);
    
    bool getRanking(CCObject *target, SEL_CallFuncND callback);
    
    bool shareBoss(long bossInstance,CCObject *target, SEL_CallFuncO callback);
    
    bool showUserBoss(BossStatus bossStatus,CCObject *target, SEL_CallFuncND callback);
    
    bool showUserBoss(CCObject *target, SEL_CallFuncND callback);
    
    bool showEvents(CCObject *target, SEL_CallFuncND callback);
    
    bool getNormalPlayer(CCObject * target, SEL_CallFuncO callback);
    
    bool getFriends(CCObject * target, SEL_CallFuncO callback);
    
    bool getFriendsRequest(CCObject * target, SEL_CallFuncO callback);
    
    bool sendFriendInvitation(long userId, CCObject * target, SEL_CallFuncND callback);
    
    bool removeFriend(long userId, CCObject * target, SEL_CallFuncND callback);
    
    bool acceptFriendRequest(long userId, CCObject * target, SEL_CallFuncND callback);
    
    bool rejectFriendRequest(long userId, CCObject * target, SEL_CallFuncND callback);
    
    bool getBlackjackRank(CCObject * target, SEL_CallFuncO callback);
    
    bool showTotalTimes(int typeId, CCObject * target, SEL_CallFuncO callback);
    
    bool sendChatContent(std::string chatContent, CCObject * target, SEL_CallFuncO callback);
    
    bool getChatContent(CCObject * target, SEL_CallFuncO callback);
    
    bool getTask(CCObject * target, SEL_CallFuncO callback);
    
    bool completeTask(int taskId,CCObject * target, SEL_CallFuncO callback);
    
    bool accessFriendInvitationCode(std::string accessCode, CCObject * target, SEL_CallFuncO callback);
    
    bool getGameUserInfo(long userId,CCObject * target, SEL_CallFuncO callback);
private:
    CCObject *mTarget;
    SEL_CallFuncO mCallFuncO;
    SEL_CallFuncND mCallFuncND;
};



#endif
