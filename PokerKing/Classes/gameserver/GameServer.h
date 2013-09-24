//
//  GameServer.h
//  blackjack
//
//  Created by Niu Xiaoming on 12-11-18.
//
//

#ifndef __blackjack__GameServer__
#define __blackjack__GameServer__

#include <iostream>

#include "GameInfo.h"
#include "GameServerAction.h"
#include "GameServerResponse.h"


USING_NS_CC;

class GameServer : public CCObject
{
private:
    CCObject *mCallBackTarget;
    SEL_CallFuncO mCallbackFuncO;
    
public:
//    static GameServer* create();
    bool doGameServerAction(CCObject *target, SEL_CallFuncO call, std::string action, std::string postValue);
    void doGameServerAction_Done(CCNode* pSender, void* data);
    
    GameServer(void);
    virtual ~GameServer(void);
    virtual bool init(void);
    
    /** returns a shared instance of the director */
    static GameServer* sharedGameServer(void);
    
    bool hasCallInProgress;
};


#endif /* defined(__blackjack__GameServer__) */
