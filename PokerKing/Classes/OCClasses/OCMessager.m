//
//  OCMessager.m
//  blackjack
//
//  Created by Niu Xiaoming on 12-12-2.
//
//

#import "OCMessager.h"

@implementation OCMessager

+(void) testLog{
    str = @"Himi->string is: ";
    NSLog(@"HSprite: testLog");
}
 
+(void) testLogWithStr:(NSString*)_str{
    str = [NSString stringWithFormat:@"%@%@",str,_str];
    NSLog(@"%@",str);
}
 
+(void) hMessageBox:(NSString*)pszMsg title:(NSString*)pszTitle{
 
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: pszTitle
                                                          message: pszMsg
                                                         delegate: nil
                                                cancelButtonTitle: @"OK"
                                                otherButtonTitles: nil];
    [messageBox autorelease];
    [messageBox show];
}

@end
