//
//  WeiboFactory.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-6.
//
//

#import <Foundation/Foundation.h>
#import "SinaWeibo.h"
#import "SinaWeiboRequest.h"


#define kAppKey @"3036750988"
#define kAppSecret @"87f417eac7728ff3a0129ddaac2a269b"
#define kAppRedirectURI @"http://www.sample.com"

@interface WeiboFactory : NSObject
<SinaWeiboDelegate,SinaWeiboRequestDelegate>
{
    NSObject * targetObject;
    SEL targetSel;
    BOOL hasDidLogin;
    BOOL hasCancelLogin;
    BOOL hasLoginFail;
}

@property (assign, readonly) BOOL hasDidLogin;
@property (assign, readonly) BOOL hasCancelLogin;
@property (assign, readonly) BOOL hasLoginFail;


+ (WeiboFactory *)sharedWeiboFactory;

- (BOOL) hasAuthInfo;

- (void) loginWeibo;

- (void) logoutWeibo;

- (void) getUserInfo;
- (void) postStatus: (NSString *) postString ;
- (void) uploadStatus: (NSString *) uploadString ;

- (void) createFriend: (NSString *) friendId ;

- (void) getFriendsInfo;

- (void)removeAuthData;

@end
