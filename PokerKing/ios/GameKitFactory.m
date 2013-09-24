//
//  LeaderBoardFactory.m
//  PokerKing
//
//  Created by Niu Xiaoming on 13-4-30.
//
//

#import "GameKitFactory.h"
#import <GameKit/GameKit.h>
#import "Constants.h"

@implementation GameKitFactory


@synthesize gameCenterAvailable;
@synthesize player;
@synthesize userAuthenticated;

//静态初始化 对外接口
static GameKitFactory *sharedHelper = nil;

static UIViewController* currentModalViewController = nil;

+ (GameKitFactory *) sharedGameKitFactory {
    if (!sharedHelper) {
        sharedHelper = [[GameKitFactory alloc] init];
    }
    return sharedHelper;
}
 
//用于验证
- (BOOL)isGameCenterAvailable {
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer =@"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer 
                                           options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}
 
- (id)init {
    if ((self = [super init])) {
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable) {
            NSNotificationCenter *nc = 
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self 
                   selector:@selector(authenticationChanged) 
                       name:GKPlayerAuthenticationDidChangeNotificationName 
                     object:nil];
        }
    }
    return self;
}
 
//后台回调登陆验证
- (void)authenticationChanged { 
    
    if ([GKLocalPlayer localPlayer].isAuthenticated &&!userAuthenticated) {
        NSLog(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
        [self storeAuthData];
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated) {
        NSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
        [self removeAuthData];
    }
    
}
 
- (void)authenticateLocalUser { 
    
    if (!gameCenterAvailable) return;
    
    NSLog(@"Authenticating local user...");
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        // No explicit autorelease pool needed here.
        // The code runs in background, not strangling
        // the main run loop. 
            
        if ([GKLocalPlayer localPlayer].authenticated == NO)
        {
            [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:nil];
            NSLog(@"Authenticated Success!");
        } else {
            NSLog(@"Already authenticated!");
        }
        
        dispatch_async(dispatch_get_main_queue(), ^{
                

            });
            
                    
        });


    
}

- (void)removeAuthData
{
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:SNS_GameCenterAuth_Key];
}

- (void)storeAuthData
{
    NSDictionary *authData = [NSDictionary dictionaryWithObjectsAndKeys:
[GKLocalPlayer localPlayer].playerID, SNS_UserID_Key, nil];

    [[NSUserDefaults standardUserDefaults] setObject:authData forKey:SNS_GameCenterAuth_Key];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

#pragma mark - 
#pragma mark Show LeaderBoard
 
//显示排行榜
- (void) showLeaderboard
{
    [self showLeaderboard:nil];
}

- (void) showLeaderboard:(const char *)leaderboard
{
    if (!gameCenterAvailable) return;
    
    GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
    if (leaderboardController != nil) {
        leaderboardController.leaderboardDelegate = self;
        
        if(leaderboard != nil)
        {
            [leaderboardController setCategory:[[NSString alloc] initWithCString:leaderboard encoding:NSUTF8StringEncoding]];
        }
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        currentModalViewController = [[UIViewController alloc] init];
        [window addSubview:currentModalViewController.view];
        [currentModalViewController presentModalViewController:leaderboardController animated:YES];
    }

}
 
//关闭排行榜回调
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController{
    if(currentModalViewController !=nil){
        [currentModalViewController dismissModalViewControllerAnimated:NO];
        [currentModalViewController release];
        [currentModalViewController.view removeFromSuperview];
        currentModalViewController = nil;
    }
}

- (void) submitScore:(const char *)leaderboard :(long)score
{
    GKScore * submitScore = [[GKScore alloc] init];
    [submitScore setValue:score]; 
    [submitScore setCategory:[[NSString alloc] initWithCString:leaderboard encoding:NSUTF8StringEncoding]];
    // New feature in iOS5 tells GameCenter which leaderboard is the default per user.
    // This can be used to show a user's favorite course/track associated leaderboard, or just show the latest score submitted.
    [submitScore setShouldSetDefaultLeaderboard:YES];
    
//    // New feature in iOS5 allows you to set the context to which the score was sent. For instance this will set the context to be 
//    //the count of the button press per run time. Information stored in context isn't accessable in standard GKLeaderboardViewController,
//    //instead it's accessable from GKLeaderboard's loadScoresWithCompletionHandler:
//    [submitScore setContext:context++];
    
    if ([GKLocalPlayer localPlayer].authenticated) {
        if (!submitScore.value) {
            // Unable to validate data. 
            return;
        }
        
        // Store the scores if there is an error. 
        [submitScore reportScoreWithCompletionHandler:^(NSError *error){
            if (!error || (![error code] && ![error domain])) {
                // Score submitted correctly. Resubmit others
//                [self resubmitStoredScores];
            } else {
                // Store score for next authentication. 
//                [self storeScore:score];
            }
        }];
    }
    
    [submitScore release];

}



#pragma mark - 
#pragma mark achievements

// View a list of unlocked achievements 
- (void)showAchievementsViewController
{
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    currentModalViewController = [[UIViewController alloc] init];
    [window addSubview:currentModalViewController.view];
    
    if (currentModalViewController) {
        [currentModalViewController dismissModalViewControllerAnimated:NO];
    }
    GKAchievementViewController * achievementViewController = [[GKAchievementViewController alloc] init];
    [achievementViewController setAchievementDelegate:self];
    
    
    [currentModalViewController presentModalViewController:achievementViewController animated:YES];
}

// Dismiss the achievement viewController 
- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController 
{
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    currentModalViewController = [[UIViewController alloc] init];
    [window addSubview:currentModalViewController.view];
    
    if (currentModalViewController) {
        // If there could be multiple modal ViewControllers up, a check is necessary.
        [currentModalViewController dismissModalViewControllerAnimated: YES];
    }
}

- (void) submitAchievement:(const char *)achievementID :(double)percentage
{
    // Submit an achievement for pressing this button 
    GKAchievement * achievement = [[[GKAchievement alloc] initWithIdentifier:[[NSString alloc] initWithCString:achievementID encoding:NSUTF8StringEncoding]] autorelease];
    
    [achievement setPercentComplete: percentage];
    [achievement setShowsCompletionBanner:true];
    
    if (achievement) {
        // Submit the achievement. 
        [achievement reportAchievementWithCompletionHandler: ^(NSError *error){
            if (error) {
                // Store achievement to be submitted at a later time. 
                //[self storeAchievement:achievement];
            } else {
//                if ([storedAchievements objectForKey:achievement.identifier]) {
//                    // Achievement is reported, remove from store. 
//                    [storedAchievements removeObjectForKey:achievement.identifier];
//                } 
//                [self resubmitStoredAchievements];
            }
        }];
    }

}

- (void) loadAchievements
{
    [GKAchievement loadAchievementsWithCompletionHandler:^(NSArray *achievements, NSError *error) {
          if (error != nil)
          {
              // Handle the error.
          }
          if (achievements != nil)
          {
              // Process the array of achievements.
          }
    }];
}


#pragma mark - 
#pragma mark Friends

- (void) retrieveFriends
{
    GKLocalPlayer *lp = [GKLocalPlayer localPlayer];
    
    if (lp.authenticated)
    {
        [lp loadFriendsWithCompletionHandler:^(NSArray *friends, NSError *error) {
         if (friends != nil)
         {
            [self loadPlayerData: friends];
         }
        }];
    }
}

- (void) loadPlayerData: (NSArray *) identifiers
{

    [GKPlayer loadPlayersForIdentifiers:identifiers
        withCompletionHandler:^(NSArray *players, NSError *error)
        {
          if (error != nil)
          {
              // Handle the error.
          }
          if (players != nil)
          {
              // Process the array of GKPlayer objects.
          }
        }];

}

- (void) inviteFriends: (NSArray*) identifiers
{
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    currentModalViewController = [[UIViewController alloc] init];
    [window addSubview:currentModalViewController.view];
    
    GKFriendRequestComposeViewController *friendRequestViewController =
[[GKFriendRequestComposeViewController alloc] init];
    friendRequestViewController.composeViewDelegate = self;
    if (identifiers)
    {
        [friendRequestViewController addRecipientsWithPlayerIDs: identifiers];
    }
    [currentModalViewController presentViewController: friendRequestViewController animated: YES
completion:nil];
    [friendRequestViewController release];
}

- (void)friendRequestComposeViewControllerDidFinish:(GKFriendRequestComposeViewController
 *)viewController
{
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    currentModalViewController = [[UIViewController alloc] init];
    [window addSubview:currentModalViewController.view];
    
    [currentModalViewController dismissViewControllerAnimated:YES completion:nil];

}

@end
