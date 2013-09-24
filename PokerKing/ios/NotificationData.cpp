//
//  NotificationData.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 13-4-24.
//
//

#include "NotificationData.h"


NotificationData::NotificationData()
:mYear(0)
,mMonth(0)
,mDay(0)
,mHour(0)
,mMinute(0)
,mSecond(0)
,mTime(NULL)
,mBody(NULL)
,mFrequency(Day)
{

}

NotificationData::~NotificationData()
{
}