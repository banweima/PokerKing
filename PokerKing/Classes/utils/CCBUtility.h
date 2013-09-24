//
//  CCBUtility.h
//  blackjack
//
//  Created by Banson Niu on 9/12/12.
//
//

#ifndef __blackjack__CCBUtility__
#define __blackjack__CCBUtility__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCBUtility
{
public:
    static CCNode* loadCCB(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader, CCObject *pOwner);
    
};

#endif /* defined(__blackjack__CCBUtility__) */
