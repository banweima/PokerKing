//
//  Constants.h
//  blackjack
//
//  Created by Banson Niu on 9/17/12.
//
//

#ifndef blackjack_Constants_h
#define blackjack_Constants_h

#define getWinW() CCDirector::sharedDirector()->getWinSize().width
#define getWinH() CCDirector::sharedDirector()->getWinSize().height

#define TotalHandLimit 21

#define DealerHitLimit 16

#define PingAnimationTime 0.3

#define CardScaleFactor 1.0

#define HideButtonTime 0.2

#define MovementTime 0.3
#define FlippingTime 0.15


#define UserName "username"
#define Password "password"

#define BlackjackRoundWager "BlackjackRoundWager"
#define CaribbeanRoundWager "CaribbeanRoundWager"
#define VideoPokerRoundWager "VideoPokerRoundWager"


#define LoginServer_Dev "http://127.0.0.1:8080/CasinoGod/" //"http://121.199.13.234:8080/CasinoGod/"//
#define LoginServer_Sandbox "http://112.124.3.221:8080/CasinoGod/"
#define LoginServer_Production "http://112.124.3.221:8080/CasinoGod/"


#define MagicItem_Switch "MagicItem_Switch"
#define MagicItem_Switch_ID "3"

#define LeaderBoard_BiggestWinner "pokerking.BiggestWinner"
#define LeaderBoard_BlackjackWinner "pokerking.BlackjackWinner"
#define LeaderBoard_CaribbeanWinner "pokerking.CaribbeanWinner"
#define LeaderBoard_VideoPokerWinner "pokerking.VideoPokerWinner"
#define LeaderBoard_LotteryWinner "pokerking.LotteryWinner"

#define Achievement_Blackjack_FirstWin "pokerking.blackjack.firstwin"

#define IAP_Diamond_Tier01 @"pokerking.diamond.tier01"

#define SNS_WeiboAuth_Key @"SinaWeiboAuthData"
#define SNS_GameCenterAuth_Key @"GameCenterAuthData"

#define SNS_Token_Key  @"AccessTokenKey"
#define SNS_ExpirationDate_Key @"ExpirationDateKey"
#define SNS_UserID_Key @"UserIDKey"

#define Device_Token_Key @"DeviceToken"

#define IAP_Receipt @"IAPReceipt"


#define kTagLoading 1
#define kTagBroadCast 2

#define Child_Order_Low 100
#define Child_Order_Mid 1000
#define Child_Order_Top 10000

#define NumbersLayer_Tag Child_Order_Mid + 1
#define AlertLayer_Tag Child_Order_Top + 1


#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey
#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey


#define PlayerImageFileName "PlayerImage.png"

#define SmallCharacters "abcdefghijklmnopqrstuvwxyz"

#define NeedBJInsurance "BlackjackInsurance"
#define NeedBJBigSmall  "BlackjackBigSmall"

#define FriendSupportRate   90

#endif
