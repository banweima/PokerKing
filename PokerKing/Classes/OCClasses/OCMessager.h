//
//  OCMessager.h
//  blackjack
//
//  Created by Niu Xiaoming on 12-12-2.
//
//

#import <Foundation/Foundation.h>

NSString * str;

@interface OCMessager : NSObject

+(void) testLog;
+(void) testLogWithStr:(NSString*)_str;
+(void) hMessageBox:(NSString*)pszMsg title:(NSString*)pszTitle;

@end
