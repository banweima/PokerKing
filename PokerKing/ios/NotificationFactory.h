//
//  LocalNotificationFactory.h
//  blackjack
//
//  Created by Niu Xiaoming on 13-4-24.
//
//

#ifndef __blackjack__NotificationFactory__
#define __blackjack__NotificationFactory__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "NotificationData.h"


USING_NS_CC;
USING_NS_CC_EXT;

class NotificationFactory
{
public:
    static void RegisterLocalNotification(NotificationData * nfData);
    
    static void CancelAllNotification();
    
};


#endif /* defined(__blackjack__LocalNotificationFactory__) */
