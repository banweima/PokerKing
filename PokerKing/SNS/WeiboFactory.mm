//
//  WeiboFactory.m
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-6.
//
//

#import "WeiboFactory.h"
#import "Constants.h"
#import "GameInfo.h"

@implementation WeiboFactory


@synthesize hasDidLogin;
@synthesize hasCancelLogin;
@synthesize hasLoginFail;


//静态初始化 对外接口
static WeiboFactory *sharedHelper = nil;

static SinaWeibo *sinaweibo = nil;

+ (WeiboFactory *)sharedWeiboFactory
{
    if (!sharedHelper) {
        sharedHelper = [[WeiboFactory alloc] init];
    }
    return sharedHelper;
}

- (id)init {
    if ((self = [super init])) {

        if (sinaweibo == nil)
        {
            hasDidLogin = FALSE;
            hasCancelLogin = FALSE;
            hasLoginFail = FALSE;
            sinaweibo = [[SinaWeibo alloc] initWithAppKey:kAppKey appSecret:kAppSecret appRedirectURI:kAppRedirectURI andDelegate:self];
            
            if ([self hasAuthInfo])
            {
                NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
                NSDictionary *sinaweiboInfo = [defaults objectForKey:SNS_WeiboAuth_Key];
                sinaweibo.accessToken = [sinaweiboInfo objectForKey:SNS_Token_Key];
                sinaweibo.expirationDate = [sinaweiboInfo objectForKey:SNS_ExpirationDate_Key];
                sinaweibo.userID = [sinaweiboInfo objectForKey:SNS_UserID_Key];
                NSLog(@"sinaweibo has logged in already userID = %@ accesstoken = %@ expirationDate = %@", sinaweibo.userID, sinaweibo.accessToken, sinaweibo.expirationDate);
                [self getUserInfo];
            }
            else
            {
                hasDidLogin = FALSE;
//                hasCancelLogin = FALSE;
//                hasLoginFail = FALSE;
            }
        }
    }
    return self;
}

- (void) loginWeibo
{
    hasDidLogin = FALSE;
    hasCancelLogin = FALSE;
    hasLoginFail = FALSE;
    [sinaweibo logIn];
}

- (void) logoutWeibo
{
    [sinaweibo logOut];
}


- (void)getUserInfo
{
    [sinaweibo requestWithURL:@"users/show.json"
    params:[NSMutableDictionary dictionaryWithObject:sinaweibo.userID forKey:@"uid"] httpMethod:@"GET"
    delegate:self];
}


- (void)getFriendsInfo
{
    [sinaweibo requestWithURL:@"friendships/friends.json"
    params:[NSMutableDictionary dictionaryWithObject:sinaweibo.userID forKey:@"uid"] httpMethod:@"GET"
    delegate:self];
}

- (void) postStatus: (NSString *) postString
{
    NSLog(@"Post status %@", postString);
    [sinaweibo requestWithURL:@"statuses/update.json"
                               params:[NSMutableDictionary dictionaryWithObjectsAndKeys:postString, @"status", nil]
                           httpMethod:@"POST"
                             delegate:self];
}

- (void) uploadStatus: (NSString *) uploadString
{
    NSLog(@"Post status %@", uploadString);
    
    UIImage * image= [UIImage imageNamed:@"Icon-0.png"];
    
    [sinaweibo requestWithURL:@"statuses/upload.json"
                               params:[NSMutableDictionary dictionaryWithObjectsAndKeys:uploadString, @"status",UIImagePNGRepresentation(image), @"pic", nil]
                           httpMethod:@"POST"
                             delegate:self];
}

- (void) createFriend: (NSString *) friendId
{
    
    NSLog(@"createFriend with %@", friendId);

    [sinaweibo requestWithURL:@"friendships/create.json"
                               params:[NSMutableDictionary dictionaryWithObjectsAndKeys: friendId, @"uid", nil]
                           httpMethod:@"POST"
                             delegate:self];
}

- (BOOL) hasAuthInfo
{
    hasDidLogin = FALSE;
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSDictionary *sinaweiboInfo = [defaults objectForKey:SNS_WeiboAuth_Key];
    return ([sinaweiboInfo objectForKey:SNS_Token_Key] && [sinaweiboInfo objectForKey:SNS_ExpirationDate_Key] && [sinaweiboInfo objectForKey:SNS_UserID_Key]);
}

#pragma mark - SinaWeibo Delegate
// 用户成功登陆
// 注意需要将登陆成功的用户信息缓存下来以便下次使用
- (void)sinaweiboDidLogIn:(SinaWeibo *)sinaweibo
{
    NSLog(@"sinaweiboDidLogIn userID = %@ accesstoken = %@ expirationDate = %@", sinaweibo.userID, sinaweibo.accessToken, sinaweibo.expirationDate);
    [self storeAuthData];
    
    hasCancelLogin = FALSE;
    hasLoginFail = FALSE;
    [self getUserInfo];
}

// 用户退出登陆
// 注意需要清除已经缓存的用户信息
- (void)sinaweiboDidLogOut:(SinaWeibo *)sinaweibo
{
    NSLog(@"sinaweiboDidLogOut");
    [self removeAuthData];
    hasDidLogin = FALSE;
    hasCancelLogin = FALSE;
    hasLoginFail = FALSE;
}

// 用户取消登陆过程
- (void)sinaweiboLogInDidCancel:(SinaWeibo *)sinaweibo
{
    NSLog(@"sinaweiboLogInDidCancel");
    [self removeAuthData];
    hasDidLogin = FALSE;
    hasCancelLogin = TRUE;
}


// 登陆失败
- (void)sinaweibo:(SinaWeibo *)sinaweibo logInDidFailWithError:(NSError *)error
{
    NSLog(@"sinaweibo logInDidFailWithError %@", error);
    [self removeAuthData];
    hasDidLogin = FALSE;
    hasLoginFail = TRUE;
}

// 缓存的 token 无效或者已经过期
// 注意需要清除缓存的用户信息
- (void)sinaweibo:(SinaWeibo *)sinaweibo accessTokenInvalidOrExpired:(NSError *)error
{
    NSLog(@"sinaweiboAccessTokenInvalidOrExpired %@", error);
    [self removeAuthData];
    hasDidLogin = FALSE;
}


- (void)removeAuthData
{
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:SNS_WeiboAuth_Key];
}

- (void)storeAuthData
{
    NSDictionary *authData = [NSDictionary dictionaryWithObjectsAndKeys:
                              sinaweibo.accessToken, SNS_Token_Key,
                              sinaweibo.expirationDate, SNS_ExpirationDate_Key,
                              sinaweibo.userID, SNS_UserID_Key,
                              sinaweibo.refreshToken, @"refresh_token", nil];
    [[NSUserDefaults standardUserDefaults] setObject:authData forKey:SNS_WeiboAuth_Key];
    [[NSUserDefaults standardUserDefaults] synchronize];
}


#pragma mark - SinaWeiboRequest Delegate
// 请求失败
- (void)request:(SinaWeiboRequest *)request didFailWithError:(NSError *)error
{
    // 当一个 delegate 需要处理多个请求回调时,可以通过 url 来判断当前的 request
    if ([request.url hasSuffix:@"users/show.json"])
    {
        NSLog(@"Get user info failed!");
        hasDidLogin = TRUE;
    }
    else if ([request.url hasSuffix:@"statuses/upload.json"])
    {
        NSLog(@"Post status failed!");
    }
    else if([request.url hasSuffix:@"friendships/create.json"])
    {
    
    }
}


// 请求成功
- (void)request:(SinaWeiboRequest *)request didFinishLoadingWithResult:(id)result
{
    NSLog(@"Success -- %@",request.url);
    
    if ([request.url hasSuffix:@"users/show.json"])
    {
        NSDictionary * userInfo = [result retain];
        UserInfo::sharedUserInfo()->setUserName(((NSString *)[userInfo objectForKey:@"screen_name"]).UTF8String);
        
        UserInfo::sharedUserInfo()->setThumbnail(((NSString *)[userInfo objectForKey:@"avatar_large"]).UTF8String);
        CCLOG(UserInfo::sharedUserInfo()->getThumbnail().c_str());
        //profile_image_url
        //avatar_large
        UserInfo::sharedUserInfo()->setGender(((NSString *)[userInfo objectForKey:@"gender"]).UTF8String );
        hasDidLogin = TRUE;
        
    }
    else if ([request.url hasSuffix:@"statuses/upload.json"])
    {
        NSDictionary * userInfo = [result retain];
        for(NSObject * obj in [userInfo allKeys])
        {
            NSLog(@"key: %@, value: %@",obj, [userInfo objectForKey:obj]);
        }
    }
    else if([request.url hasSuffix:@"friendships/create.json"])
    {
        NSDictionary * userInfo = [result retain];
        for(NSObject * obj in [userInfo allKeys])
        {
            NSLog(@"key: %@, value: %@",obj, [userInfo objectForKey:obj]);
        }
    }
}

@end
