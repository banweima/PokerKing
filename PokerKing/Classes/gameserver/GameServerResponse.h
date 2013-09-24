//
//  GameServerResponse.h
//  blackjack
//
//  Created by Niu Xiaoming on 12-11-18.
//
//

#ifndef __blackjack__GameServerResponse__
#define __blackjack__GameServerResponse__

#include "cocos2d.h"

USING_NS_CC;

class GameServerResponse : public CCObject
{
private:
    CC_SYNTHESIZE(bool, mIsSuccess, IsSuccess);
    CC_SYNTHESIZE(int, mResponseCode, ResponseCode);
    CC_SYNTHESIZE(CCString *, mResponseContent, ResponseContent);
    CC_SYNTHESIZE(CCString *, mServerError, ServerError);
    CC_SYNTHESIZE(CCDictionary *, mResponseDictionary, ResponseDictionary);
    
public:
    static GameServerResponse* create();
    bool init();
};

#endif /* defined(__blackjack__GameServerResponse__) */
