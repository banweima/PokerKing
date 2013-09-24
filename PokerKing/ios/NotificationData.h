//
//  NotificationData.h
//  blackjack
//
//  Created by Niu Xiaoming on 13-4-24.
//
//

#ifndef __blackjack__NotificationData__
#define __blackjack__NotificationData__

#include "cocos2d.h"
#include "cocos-ext.h"

enum RepeatFrequency{
    Year = 0,
	Month,
	Day,
	Hour,
    Minute,
    Second
};

class NotificationData
{

public:

    int mYear;
    int mMonth;
    int mDay;
    int mHour;
    int mMinute;
    int mSecond;
    const char* mTime; //设置日期格式 "HH:mm:ss" 
    const char* mBody;
    RepeatFrequency mFrequency;
    
    
    NotificationData();
    virtual ~NotificationData();

};
#endif /* defined(__blackjack__NotificationData__) */
