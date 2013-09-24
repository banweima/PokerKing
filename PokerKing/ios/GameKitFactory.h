//
//  LeaderBoardFactory.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-4-30.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
#import "PlayerModel.h"

@interface GameKitFactory : NSObject <GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate,
    GKFriendRequestComposeViewControllerDelegate>{
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;

}


// This assists in caching game center data until 
@property (readwrite, retain) PlayerModel * player;

@property (assign, readonly) BOOL gameCenterAvailable;

@property (assign, readonly) BOOL userAuthenticated;

+ (GameKitFactory *)sharedGameKitFactory;
- (void) authenticateLocalUser;
 
- (void) showLeaderboard;
- (void) showLeaderboard:(const char *)leaderboard;
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;

- (void) submitScore:(const char *)leaderboard : (long) score;

- (void)showAchievementsViewController;

- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController;

- (void) submitAchievement:(const char *)achievementID :(double)percentage;

- (void) retrieveFriends;
- (void) loadPlayerData: (NSArray *) identifiers;

- (void) inviteFriends: (NSArray*) identifiers;

- (void) loadAchievements;
@end



