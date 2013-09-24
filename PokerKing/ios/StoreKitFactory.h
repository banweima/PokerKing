//
//  StoreKitFactory.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-4.
//
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import "Constants.h"

@interface StoreKitFactory : NSObject
 <SKRequestDelegate,SKProductsRequestDelegate,SKStoreProductViewControllerDelegate,SKPaymentTransactionObserver>
{
    NSString * currentTier;
}

@property (retain, readonly) NSString * currentTier;

+ (StoreKitFactory *)sharedStoreKitFactory;

- (BOOL) canMakePayments;

- (void) requestProductData: (NSString *) IAP_Tier;

- (void)requestProUpgradeProductData;

- (void)removeReceiptData;

- (void)storeReceiptData: (NSString *) receipt;

@end
