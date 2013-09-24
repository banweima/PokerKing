//
//  GameServerResponse.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 12-11-18.
//
//

#include "GameServerResponse.h"


GameServerResponse* GameServerResponse::create()
{
    GameServerResponse* pGameServerResponse = new GameServerResponse();
    
    if (pGameServerResponse && pGameServerResponse->init())
    {
        pGameServerResponse->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pGameServerResponse);
    }
    
    return pGameServerResponse;

}

bool GameServerResponse::init()
{
    return true;
}