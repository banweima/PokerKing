//
//  LocalNotificationFactory.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 13-4-24.
//
//

#include "NotificationFactory.h"


void NotificationFactory::RegisterLocalNotification(NotificationData * nfData)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    NSDate *itemDate = NULL;
    if(nfData->mTime == NULL)
    {
        NSCalendar *calendar = [NSCalendar autoupdatingCurrentCalendar];

        
        NSDateComponents *dateComps = [[NSDateComponents alloc] init];
        [dateComps setYear:nfData->mYear];
        [dateComps setMonth:nfData->mMonth];
        [dateComps setDay:nfData->mDay];
        [dateComps setHour:nfData->mHour];
        [dateComps setMinute:nfData->mMinute];
        [dateComps setSecond:nfData->mSecond];
        itemDate = [calendar dateFromComponents:dateComps];
        [dateComps release];
    }
    else
    {
        NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init] autorelease]; 
        //注意dateFormatter的格式一定要按字符串的样子来，如果不对，转换出来是nill。
        //时区格式，可以不用设置
        //NSTimeZone *timeZone = [NSTimeZone localTimeZone];
        //[formatter setTimeZone:timeZone];
        [dateFormatter setDateFormat:@"HH:mm:ss"]; //设置日期格式

        itemDate = [dateFormatter dateFromString:
        [[NSString alloc] initWithCString:nfData->mTime encoding:NSUTF8StringEncoding]];  //开始日期，将NSString转为NSDate
    }
    
    UILocalNotification *localNotif = [[UILocalNotification alloc] init];
    if (localNotif == nil)
        return;
    localNotif.fireDate = itemDate;
    localNotif.timeZone = [NSTimeZone defaultTimeZone];
 
    switch (nfData->mFrequency) {
        case Year:
        localNotif.repeatInterval = NSYearCalendarUnit;
        break;
        case Month:
        localNotif.repeatInterval = NSMonthCalendarUnit;
        break;
        case Day:
        localNotif.repeatInterval = NSDayCalendarUnit;
        break;
        case Hour:
        localNotif.repeatInterval = NSHourCalendarUnit;
        break;
        case Minute:
        localNotif.repeatInterval = NSMinuteCalendarUnit;
        break;
        case Second:
        localNotif.repeatInterval = NSSecondCalendarUnit;
        break;
    }
    
    
    localNotif.alertBody = [[NSString alloc] initWithCString:nfData->mBody encoding:NSUTF8StringEncoding];

//    localNotif.alertAction = NSLocalizedString(@"View Details", nil);
 
    localNotif.soundName = UILocalNotificationDefaultSoundName;
    localNotif.applicationIconBadgeNumber = 1;
 
//    NSDictionary *infoDict = [NSDictionary dictionaryWithObject:@"TestEvent" forKey:@"TestEventKey"];
//    localNotif.userInfo = infoDict;
 
    [[UIApplication sharedApplication] scheduleLocalNotification:localNotif];
    [localNotif release];
    
    #else
        //Android代码
    #endif
    
}


void NotificationFactory::CancelAllNotification()
{
    [[UIApplication sharedApplication] cancelAllLocalNotifications];
}