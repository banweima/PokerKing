//
//  GameServerAction.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 12-11-22.
//
//

#include "GameServerAction.h"
#include "Constants.h"
#include "UserInfo.h"



USING_NS_CC_EXT;

//static GameServerAction *pGameServerAction = NULL;

GameServerAction* GameServerAction::sharedGameServerAction(void)
{
    GameServerAction *pGameServerAction = NULL;
    if (!pGameServerAction)
    {
        pGameServerAction = new GameServerAction();
        if(pGameServerAction && pGameServerAction->init())
        {
        }
    }
    
    return pGameServerAction;
}

GameServerAction::GameServerAction()
:mTarget(NULL)
, mCallFuncO(NULL)
, mCallFuncND(NULL)
{}

GameServerAction::~GameServerAction()
{
    
}

bool GameServerAction::init()
{
    return true;
}


void GameServerAction::useMagicItem( std::string itemId, int count,cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    if(GameInfo::sharedGameInfo()->getEnv() != Standalone)
    {
        std::string postValue = CCString::createWithFormat("itemId=%s&itemNum=%d", itemId.c_str(), count)->getCString();
//        CCLOG("postData=%s", postValue.c_str());
        
        GameServer * gServer = GameServer::sharedGameServer();
        bool callSuccess = gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::useMagicItem_Done), Act_consume_item, postValue);
        
        if(!callSuccess)
        {
            CCLOG("useMagicItem Fail");
        }
    
    }
    else
    {
        //int currentCount = UserInfo::sharedUserInfo()->getMagicItemAmount(MagicItem_Switch);
        //UserInfo::sharedUserInfo()->setMagicItemAmount(MagicItem_Switch,currentCount - count);
        
        
        
    }

}

void GameServerAction::useMagicItem_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();

        CCDictionary *userInfoDict = (CCDictionary *)dict->objectForKey("userInfo");
        
        UserInfo::sharedUserInfo()->parseUserInfo(userInfoDict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("useMagicItem Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }
}


//bool GameServerAction::checkResponseIsOK(GameServerResponse *response)
//{
//    
//    if (response->getIsSuccess()) {
//        
//        CCDictionary *dict = response->getResponseDictionary();
//        
//        CCString* result = (CCString *)dict->objectForKey("result");
//        return result->isEqual(CCString::create("ok"));
//        
//    } else {
//        CCLOG("Error = %s", response->getServerError());
//        return false;
//    }
//}

void GameServerAction::getGameRoomInfo(GameType gameType, CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    if((GameInfo::sharedGameInfo())->getEnv() != Standalone)
    {
        //aid is the Game ID, change to gid
        GameServer * gServer = GameServer::sharedGameServer();
        gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::getGameRoomInfo_Done), Act_get_room_info, "");
    }
    else
    {
        GameServerResponse *response = GameServerResponse::create();
        response->setIsSuccess(true);
        response->setResponseCode(200);
        response->setResponseContent(CCString::create("{\"level1\":{\"levelscore\":10000,\"minhand\":200,\"maxhand\":2000},\"level2\":{\"levelscore\":10000,\"minhand\":2000,\"maxhand\":20000},\"level3\":{\"levelscore\":10000,\"minhand\":10000,\"maxhand\":100000},\"level4\":{\"levelscore\":10000,\"minhand\":10000,\"maxhand\":999999}}"));
        response->setResponseDictionary(JSONValueUtil::JSONValue("{\"level1\":{\"levelscore\":10000,\"minhand\":200,\"maxhand\":2000},\"level2\":{\"levelscore\":10000,\"minhand\":2000,\"maxhand\":20000},\"level3\":{\"levelscore\":10000,\"minhand\":10000,\"maxhand\":100000},\"level4\":{\"levelscore\":10000,\"minhand\":10000,\"maxhand\":999999}}"));
        response->setServerError(CCString::create(""));
        
        this->getGameRoomInfo_Done(response);
    }
}

void GameServerAction::getGameRoomInfo_Done(CCObject * data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();
        GameLevelInfo::sharedGameLevelInfo()->parseGameLevelInfo(dict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            } 
        
    } else {
        CCLOG("getGameRoomInfo Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)false);
            } 
    }
}


bool GameServerAction::startBattle(GameType gameType, BattleType battleType, long battlePrice, RoomType roomLevel, CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    if((GameInfo::sharedGameInfo())->getEnv() != Standalone)
    {
        std::string postValue = "";

        switch (battleType)
        {
          case SingleBattle:
            postValue = CCString::createWithFormat("userId=%d&battleType=%d&gameType=%d&battlePrize=%d&level=%d&bossInstance=0", UserInfo::sharedUserInfo()->getUserID(),  (int)battleType, (int)gameType,battlePrice,(int)roomLevel)->getCString();
            break;

          case BossBattle:
            postValue = CCString::createWithFormat("userId=%d&battleType=%d&gameType=%d&battlePrize=%d&bossInstance=%d", UserInfo::sharedUserInfo()->getUserID(),  (int)battleType, (int)gameType,battlePrice,BattleInfo::sharedBattleInfo()->getRaidBoss()->getBossInstance())->getCString();
            break;
        }

//        CCLOG("postData=%s", postValue.c_str());
        
        GameServer * gServer = GameServer::sharedGameServer();
        return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::startBattle_Done), Act_start_battle, postValue);
    }
    else
    {
//        GameServerResponse *response = GameServerResponse::create();
//        response->setIsSuccess(true);
//        response->setResponseCode(200);
//        response->setResponseContent(CCString::create("{\"battleInfo\":{\"battleCreateTime\":\"2013-05-07 13:55:45\",\"battleID\":3671268365221000070,\"battleOwnerUserID\":10000,\"battlePlayerList\":[{\"cardsInDeck\":[9,46],\"playerBet\":200,\"playerID\":10000},{\"cardsInDeck\":[6,37],\"playerBet\":200, \"playerID\":10001}],\"battlePrize\":200,\"battleStatus\":\"Fighting\",\"battleType\":\"Arena\",\"dealerCards\":[8,27,36,6,41],\"gameType\":\"Texas\"}}"));
//        response->setResponseDictionary(JSONValueUtil::JSONValue("{\"battleInfo\":{\"battleCreateTime\":\"2013-05-07 13:55:45\",\"battleID\":3671268365221000070,\"battleOwnerUserID\":10000,\"battlePlayerList\":[{\"cardsInDeck\":[9,46],\"playerBet\":200,\"playerID\":10000},{\"cardsInDeck\":[6,37],\"playerBet\":200, \"playerID\":10001}],\"battlePrize\":200,\"battleStatus\":\"Fighting\",\"battleType\":\"Arena\",\"dealerCards\":[8,27,36,6,41],\"gameType\":\"Texas\"}}"));
//        response->setServerError(CCString::create(""));
//        
//        this->startBattle_Done(response);
        
        return true;
    }
}


void GameServerAction::startBattle_Done(CCObject * data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();
        
        CCDictionary* battleInfoDic = (CCDictionary *)dict->objectForKey("battleInfo");

        BattleInfo * batInfo = BattleInfo::sharedBattleInfo();
        batInfo->parseBattleInfo(battleInfoDic);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            } 
    } else {
        CCLOG("startBattle Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)false);
            } 
    }
}

bool GameServerAction::doLogin(SNSType snsType, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    std::string postValue = "";
    switch (snsType)
    {
        case Weibo:
        {
            NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
                NSDictionary *sinaweiboInfo = [defaults objectForKey:SNS_WeiboAuth_Key];
            NSString * value = [[NSString alloc] initWithFormat:@"userType=2&snsId=%@&snsToken=%@&deviceToken=%@",[sinaweiboInfo objectForKey:SNS_UserID_Key],[sinaweiboInfo objectForKey:SNS_Token_Key],
            [[NSUserDefaults standardUserDefaults] objectForKey:Device_Token_Key]];

            postValue = [value UTF8String];
            
            break;
        }
        
        case GameCenter:
        {            
            NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
            NSDictionary *snsInfo = [defaults objectForKey:SNS_GameCenterAuth_Key];
            NSString * value = [[NSString alloc] initWithFormat:@"userType=1&snsId=%@&snsToken=&deviceToken=%@",[snsInfo objectForKey:SNS_UserID_Key],(NSString *)[[NSUserDefaults standardUserDefaults] objectForKey:Device_Token_Key]];

            postValue = [value UTF8String];

            break;
        }
    }

//    CCLOG("postData=%s", postValue.c_str());

    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::doLogin_Done), Act_login, postValue);
    
    

}


void GameServerAction::doLogin_Done(cocos2d::CCObject *data)
{
   GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {

        CCDictionary *dict = response->getResponseDictionary();
        GameInfo* gameInfo = GameInfo::sharedGameInfo();
    
        gameInfo->setToken(((CCString *)dict->objectForKey("token"))->getCString());
        gameInfo->setGameServerUrl(((CCString *)dict->objectForKey("gameServerUrl"))->getCString());
        
        CCDictionary *userInfoDict = (CCDictionary *)dict->objectForKey("userinfo");
        
        UserInfo::sharedUserInfo()->parseUserInfo(userInfoDict);
        
        if(dict->objectForKey("snsId"))
        {
            UserInfo::sharedUserInfo()->setSNSID(((CCString *)dict->objectForKey("snsId"))->getCString());
        }
        
        CCLOG("uid=%d token=%s gameserver=%s", UserInfo::sharedUserInfo()->getUserID(), gameInfo->getToken().c_str(), gameInfo->getGameServerUrl().c_str());
    
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            }   
   

        
    } else {
        CCLOG("login Fail");
        if (mTarget && mCallFuncND) {
                    (mTarget->*mCallFuncND)(NULL, (void *)false);
                }
    } 
}


bool GameServerAction::updateUserInfo(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    std::string postValue = CCString::createWithFormat("nickName=%s&gender=%s&image=%s", UserInfo::sharedUserInfo()->getUserName().c_str(), UserInfo::sharedUserInfo()->getGender().c_str(),UserInfo::sharedUserInfo()->getThumbnail().c_str())->getCString();
//        CCLOG("postData=%s", postValue.c_str());
    
        GameServer * gServer = GameServer::sharedGameServer();
        return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::updateUserInfo_Done), Act_update_user, postValue);



}


void GameServerAction::updateUserInfo_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
    
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL, (void *)true);
            }   
    
    } else {
        CCLOG("login Fail");
        if (mTarget && mCallFuncND) {
                    (mTarget->*mCallFuncND)(NULL, (void *)false);
                }
    } 

}

void GameServerAction::getUserInfo(CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;

    GameServer::sharedGameServer()->doGameServerAction(this, callfuncO_selector(GameServerAction::getUserInfo_Done), Act_get_user, "");
}

void GameServerAction::getUserInfo_Done(CCObject * data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();
        
        UserInfo::sharedUserInfo()->parseUserInfo(dict);
        
        if (mTarget && mCallFuncND) {
        (mTarget->*mCallFuncND)(NULL, (void *) true);
        }
        
    } else {
        CCLOG("Error = %s", response->getServerError());
        if (mTarget && mCallFuncND) {
        (mTarget->*mCallFuncND)(NULL, (void *) false);
    }
    }
    
    
}


bool GameServerAction::endBattle(long battleResultPrice,int intSpecialWin, RoomType roomLevel,cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    if((GameInfo::sharedGameInfo())->getEnv() != Standalone)
    {
        std::string postValue = "";
        
        switch (BattleInfo::sharedBattleInfo()->getBattleType())
        {
          case SingleBattle:
            postValue = CCString::createWithFormat("userId=%d&battleType=%d&gameType=%d&result=%d&battleId=%d&level=%d&isSpecialWin=%d", UserInfo::sharedUserInfo()->getUserID(),  (int)BattleInfo::sharedBattleInfo()->getBattleType(),(int)GameInfo::sharedGameInfo()->getCurrentGameType() , battleResultPrice,BattleInfo::sharedBattleInfo()->getBattleID(),(int)roomLevel,intSpecialWin)->getCString();
            break;

          case BossBattle:
            postValue = CCString::createWithFormat("userId=%d&battleType=%d&gameType=%d&result=%d&battleId=%d&bossInstance=%d&level=%d&isSpecialWin=%d", UserInfo::sharedUserInfo()->getUserID(),  (int)BattleInfo::sharedBattleInfo()->getBattleType(),(int)GameInfo::sharedGameInfo()->getCurrentGameType() , battleResultPrice,BattleInfo::sharedBattleInfo()->getBattleID(), BattleInfo::sharedBattleInfo()->getRaidBoss()->getBossInstance(),(int)roomLevel,intSpecialWin)->getCString();
            break;
        }
        
//        CCLOG("postData=%s", postValue.c_str());
        
        GameServer * gServer = GameServer::sharedGameServer();
        return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::endBattle_Done), Act_end_battle, postValue);
    }
    else
    {
        return true;
    }

}

void GameServerAction::endBattle_Done(cocos2d::CCObject *data)
{

    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();
        
        if(BattleInfo::sharedBattleInfo()->getBattleType() == BossBattle)
        {
            CCDictionary* userInfoDic = (CCDictionary *)dict->objectForKey("userInfo");
            UserInfo::sharedUserInfo()->parseUserInfo(userInfoDic);
            CCDictionary* bossInfoDic = (CCDictionary *)dict->objectForKey("bossInstance");
            BattleInfo::sharedBattleInfo()->getRaidBoss()->parseRaidBossInfo(bossInfoDic);
        }
        else
        {
            CCDictionary* userInfoDic = (CCDictionary *)dict->objectForKey("userInfo");
            UserInfo::sharedUserInfo()->parseUserInfo(userInfoDic);
        }
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("endBattle Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }

}

bool GameServerAction::checkIAPReceipt(std::string receipt, std::string productId, int quantity, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    if((GameInfo::sharedGameInfo())->getEnv() != Standalone)
    {
        //aid is the Game ID, change to gid
        std::string postValue = CCString::createWithFormat("receipt=%s&sandbox=%s&productId=%s&quantity=%d", receipt.c_str(), (GameInfo::sharedGameInfo()->getEnv() == Production)?"false":"true", productId.c_str(), quantity)->getCString();
//        CCLOG("postData=%s", postValue.c_str());
        
        GameServer * gServer = GameServer::sharedGameServer();
        return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::checkIAPReceipt_Done), Act_check_receipt, postValue);
    }
    else
    {
        return true;
    }
}

void GameServerAction::checkIAPReceipt_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();
        
        //CCDictionary* userInfoDic = (CCDictionary *)dict->objectForKey("userinfo");

//        UserInfo::sharedUserInfo()->parseUserInfo(dict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("checkIAPReceipt Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }


}

bool GameServerAction::retrieveProductList(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
        
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::retrieveProductList_Done), Act_get_IAPProducts, "");


}

void GameServerAction::retrieveProductList_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();

        GameInfo::sharedGameInfo()->parseProductList(dict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("startBattle Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }

}

bool GameServerAction::getItems(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
        
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::getItem_Done), Act_get_items, "");


}

void GameServerAction::getItem_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();

        GameInfo::sharedGameInfo()->parseItemList(dict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("getItems Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }

}

bool GameServerAction::buyItem(std::string itemId, int quantity, CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    if((GameInfo::sharedGameInfo())->getEnv() != Standalone)
    {
        //aid is the Game ID, change to gid
        std::string postValue = CCString::createWithFormat("itemId=%s&itemNum=%d", itemId.c_str(), quantity)->getCString();
//        CCLOG("postData=%s", postValue.c_str());
        
        GameServer * gServer = GameServer::sharedGameServer();
        return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::buyItem_Done), Act_buy_item, postValue);
    }
    else
    {
        return true;
    }
}

void GameServerAction::buyItem_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();
        CCDictionary *userInfoDict = (CCDictionary *)dict->objectForKey("userInfo");
        UserInfo::sharedUserInfo()->parseUserInfo(userInfoDict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("buyItem Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }


}

bool GameServerAction::retrieveBroadcast(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
        
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::retrieveBroadcast_Done), Act_broadcast, "");
    
    
//    GameServerResponse *response = GameServerResponse::create();
//        response->setIsSuccess(true);
//        response->setResponseCode(200);
//        response->setResponseContent(CCString::create("{\"broadCastProfile\":[{\"content\":\"欢庆上线，所有玩家无限玩\"}]}"));
//        response->setResponseDictionary(JSONValueUtil::JSONValue("{\"broadCastProfile\":[{\"content\":\"欢庆上线，所有玩家无限玩\"}]}"));
//        response->setServerError(CCString::create(""));
//        
//        this->retrieveBroadcast_Done(response);
//    return true;
}

void GameServerAction::retrieveBroadcast_Done(CCObject * data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();

        BroadCast::sharedBroadCast()->parseBCContent(dict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("retrieveBroadcast Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }

}


bool GameServerAction::getRanking(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
        
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::getRanking_Done), Act_ranking, "");
}

void GameServerAction::getRanking_Done(cocos2d::CCObject *data)
{

    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();

        //BroadCast::sharedBroadCast()->parseBCContent(dict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("getRanking Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }
}

bool GameServerAction::shareBoss(long bossInstance, cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;
    
    std::string postValue = CCString::createWithFormat("bossInstance=%d&env=%d", bossInstance, GameInfo::sharedGameInfo()->getEnv())->getCString();

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::shareBoss_Done), Act_share_boss, postValue);
}

void GameServerAction::shareBoss_Done(cocos2d::CCObject *data)
{

    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }
        
    } else {
        CCLOG("shareBoss Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }
}

bool GameServerAction::showUserBoss(BossStatus bossStatus, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    std::string postValue = CCString::createWithFormat("status=%d", bossStatus)->getCString();
    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::showUserBoss_Done), Act_show_userboss, postValue);
}

bool GameServerAction::showUserBoss(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::showUserBoss_Done), Act_show_userboss, "status=0");
}


void GameServerAction::showUserBoss_Done(cocos2d::CCObject *data)
{

    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        
        CCDictionary *dict = response->getResponseDictionary();

        GameInfo::sharedGameInfo()->parseUserBossList(dict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("showUserBoss Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }
}


bool GameServerAction::showEvents(cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
        
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::showEvents_Done), Act_show_events, "enable=1");
}

void GameServerAction::showEvents_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        GameInfo::sharedGameInfo()->parseEventsList(dict);
        
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("showEvents Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }
}

bool GameServerAction::getNormalPlayer(cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;
        
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::getNormalPlayer_Done), Act_friends_player, "");
}

void GameServerAction::getNormalPlayer_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }
        
    } else {
        CCLOG("getNormalPlayer Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }

}

bool GameServerAction::sendFriendInvitation(long userId, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    

    //aid is the Game ID, change to gid
    std::string postValue = CCString::createWithFormat("userId=%d", userId)->getCString();

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::sendFriendInvitation_Done), Act_friends_request, postValue);

}

void GameServerAction::sendFriendInvitation_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("sendFriendInvitation Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }
}

bool GameServerAction::getFriends(cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;
        
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::getFriends_Done), Act_friends_show, "");
}


void GameServerAction::getFriends_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }
        
    } else {
        CCLOG("getFriends Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }
}

bool GameServerAction::getFriendsRequest(cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;
        
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::getFriendsRequest_Done), Act_friends_query_request, "");

}

void GameServerAction::getFriendsRequest_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }
    } else {
        CCLOG("getFriendsRequest Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }

}

bool GameServerAction::removeFriend(long userId, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    

    //aid is the Game ID, change to gid
    std::string postValue = CCString::createWithFormat("userId=%d", userId)->getCString();

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::removeFriend_Done), Act_friends_remove, postValue);

}

void GameServerAction::removeFriend_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("sendFriendInvitation Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }
}

bool GameServerAction::acceptFriendRequest(long userId, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    

    //aid is the Game ID, change to gid
    std::string postValue = CCString::createWithFormat("userId=%d", userId)->getCString();

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::acceptFriendRequest_Done), Act_friends_accept, postValue);
}

void GameServerAction::acceptFriendRequest_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("acceptFriendRequest Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }

}

bool GameServerAction::rejectFriendRequest(long userId, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    mTarget = target;
    mCallFuncND = callback;
    

    std::string postValue = CCString::createWithFormat("userId=%d", userId)->getCString();

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::rejectFriendRequest_Done), Act_friends_cancel, postValue);
}


void GameServerAction::rejectFriendRequest_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
        
    } else {
        CCLOG("rejectFriendRequest Fail");
        if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)false);
            }
    }
}

bool GameServerAction::getBlackjackRank(cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::rejectFriendRequest_Done), Act_rank_all, "");

}

void GameServerAction::getBlackjackRank_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }        
    } else {
        CCLOG("getBlackjackRank Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }
}


bool GameServerAction::showTotalTimes(int typeId,cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;

    std::string postValue = CCString::createWithFormat("typeId=%d", typeId)->getCString();
    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::showTotalTimes_Done), Act_rank_all, postValue);

}

void GameServerAction::showTotalTimes_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }        
    } else {
        CCLOG("getBlackjackRank Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }
}

bool GameServerAction::sendChatContent(std::string chatContent, cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;


    std::string postValue = CCString::createWithFormat("content=%s", chatContent.c_str())->getCString();
    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::sendChatContent_Done), Act_chat_send, postValue);

}

void GameServerAction::sendChatContent_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }        
    } else {
        CCLOG("sendChatContent Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }
}

bool GameServerAction::getChatContent(cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::getChatContent_Done), Act_chat_send, "");

}

void GameServerAction::getChatContent_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }        
    } else {
        CCLOG("getChatContent Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }
}

bool GameServerAction::getTask(cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::getTask_Done), Act_get_task, "");
}


void GameServerAction::getTask_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }        
    } else {
        CCLOG("getTask Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }

}

bool GameServerAction::completeTask(int taskId, cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;

    std::string postValue = CCString::createWithFormat("taskId=%d", taskId)->getCString();
    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::completeTask_Done), Act_complete_task, postValue);
}


void GameServerAction::completeTask_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }        
    } else {
        CCLOG("completeTask Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }

}

bool GameServerAction::accessFriendInvitationCode(std::string accessCode, cocos2d::CCObject *target, SEL_CallFuncO callback)
{

    mTarget = target;
    mCallFuncO = callback;
    

    //aid is the Game ID, change to gid
    std::string postValue = CCString::createWithFormat("inviteCode=%s", accessCode.c_str())->getCString();

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::accessFriendInvitationCode_Done), Act_friends_invitation_access, postValue);
}

void GameServerAction::accessFriendInvitationCode_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }        
    } else {
        CCLOG("completeTask Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }
}

bool GameServerAction::getGameUserInfo(long userId, cocos2d::CCObject *target, SEL_CallFuncO callback)
{

    mTarget = target;
    mCallFuncO = callback;
    
    std::string postValue = CCString::createWithFormat("userId=%d", userId)->getCString();

    
    GameServer * gServer = GameServer::sharedGameServer();
    return gServer->doGameServerAction(this, callfuncO_selector(GameServerAction::accessFriendInvitationCode_Done), Act_gameuser_info, postValue);
}

void GameServerAction::getGameUserInfo_Done(cocos2d::CCObject *data)
{
    GameServerResponse *response = (GameServerResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    if (response->getIsSuccess()) {
        CCDictionary *dict = response->getResponseDictionary();
        
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(dict);
            }        
    } else {
        CCLOG("completeTask Fail");
        if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
    }
}