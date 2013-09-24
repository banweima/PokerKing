//
//  StoreKitFactory.m
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-4.
//
//

#import "StoreKitFactory.h"
#import "NSData+Base64.h"

@implementation StoreKitFactory

@synthesize currentTier;

static StoreKitFactory *sharedHelper = nil;


+ (StoreKitFactory *) sharedStoreKitFactory {
    if (!sharedHelper) {
        sharedHelper = [[StoreKitFactory alloc] init];
    }
    return sharedHelper;
}


- (id)init {
    if ((self = [super init])) {
//        gameCenterAvailable = [self isGameCenterAvailable];
//        if (gameCenterAvailable) {
//            NSNotificationCenter *nc = 
//            [NSNotificationCenter defaultCenter];
//            [nc addObserver:self 
//                   selector:@selector(authenticationChanged) 
//                       name:GKPlayerAuthenticationDidChangeNotificationName 
//                     object:nil];
//        }
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self]; 
    }
    return self;
}


- (BOOL) canMakePayments
{
    return [SKPaymentQueue canMakePayments];
}


- (void) requestProductData: (NSString *) IAP_Tier
{
    currentTier = IAP_Tier;
    //[currentTier retain];
    
    SKProductsRequest *request= [[SKProductsRequest alloc]
initWithProductIdentifiers:
            [NSSet setWithObject:currentTier]];
    request.delegate = self;
    [request start];
}

- (void)productsRequest:(SKProductsRequest *)request
didReceiveResponse:(SKProductsResponse *)response
{
    NSLog(@"-----------收到产品反馈信息--------------");
    NSArray *myProduct = response.products;
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
    NSLog(@"产品付费数量: %d", [myProduct count]);
    
    // populate UI
    for(SKProduct *product in myProduct)
    {
        NSLog(@"product info");
        NSLog(@"SKProduct 描述信息%@", [product description]);
        NSLog(@"产品标题 %@" , product.localizedTitle);
        NSLog(@"产品描述信息: %@" , product.localizedDescription);
        NSLog(@"价格: %@" , product.price);
        NSLog(@"Product id: %@" , product.productIdentifier);
    }
    
    SKMutablePayment *payment = [SKMutablePayment paymentWithProductIdentifier: currentTier];
    payment.quantity = 1;
    
    NSLog(@"---------发送购买请求------------");
    
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    [request autorelease];    
}


- (void)requestProUpgradeProductData
{
    NSLog(@"------请求升级数据---------");
    NSSet *productIdentifiers = [NSSet setWithObject:@"com.productid"];
    SKProductsRequest* productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    productsRequest.delegate = self;
    [productsRequest start];     
 
}


//弹出错误信息
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error{
    NSLog(@"-------弹出错误信息----------");
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:[error localizedDescription]
                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
    [alerView show];
    [alerView release];
}    
 
-(void) requestDidFinish:(SKRequest *)request
{
    NSLog(@"----------反馈信息结束--------------");    
 
}    
 
-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction{
    NSLog(@"-----PurchasedTransaction----");
    NSArray *transactions =[[NSArray alloc] initWithObjects:transaction, nil];
    [self paymentQueue:[SKPaymentQueue defaultQueue] updatedTransactions:transactions];
    [transactions release];
}     
 
//<SKPaymentTransactionObserver> 千万不要忘记绑定，代码如下：
//----监听购买结果
//[[SKPaymentQueue defaultQueue] addTransactionObserver:self];    
 
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions//交易结果
{
    NSLog(@"-----paymentQueue--------");
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased://交易完成
                [self completeTransaction:transaction];
                
                [self storeReceiptData:[transaction.transactionReceipt base64Encoding]];
                NSLog(@"-----交易完成 Base64--------%@", [transaction.transactionReceipt base64Encoding]);
                NSLog(@"-----交易完成 ASCII--------%@", [[NSString alloc] initWithData:transaction.transactionReceipt encoding:NSASCIIStringEncoding]);
//                NSLog(@"不允许程序内付费购买");
                UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert"
                                                                    message:@"购买成功啦～娃哈哈"
                                                                   delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
 
                [alerView show];
                [alerView release];
                break;
            case SKPaymentTransactionStateFailed://交易失败
                [self failedTransaction:transaction];
                 NSLog(@"-----交易失败 --------");
                UIAlertView *alerView2 =  [[UIAlertView alloc] initWithTitle:@"Alert"
                                                                    message:@"购买失败，请重新尝试购买～"
                                                                   delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];    
 
                [alerView2 show];
                [alerView2 release];
                break;
            case SKPaymentTransactionStateRestored://已经购买过该商品
                [self restoreTransaction:transaction];
                 NSLog(@"-----已经购买过该商品 --------");
            case SKPaymentTransactionStatePurchasing:      //商品添加进列表
                 NSLog(@"-----商品添加进列表 --------");
                break;
            default:
                break;
        }
    }
}
- (void) completeTransaction: (SKPaymentTransaction *)transaction    
 
{
    NSLog(@"-----completeTransaction--------");
    // Your application should implement these two methods.
    NSString *product = transaction.payment.productIdentifier;
    if ([product length] > 0) {    
 
        NSArray *tt = [product componentsSeparatedByString:@"."];
        NSString *bookid = [tt lastObject];
        if ([bookid length] > 0) {
            [self recordTransaction:bookid];
            [self provideContent:bookid];
        }
    }    
 
    // Remove the transaction from the payment queue.    
 
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];    
 
}    
 
//记录交易
-(void)recordTransaction:(NSString *)product{
    NSLog(@"-----记录交易--------");
}    
 
//处理下载内容
-(void)provideContent:(NSString *)product{
    NSLog(@"-----下载--------");
}    
 
- (void) failedTransaction: (SKPaymentTransaction *)transaction{
    NSLog(@"失败");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
    }
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];    
 
}
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction{    
 
}    
 
- (void) restoreTransaction: (SKPaymentTransaction *)transaction    
 
{
    NSLog(@" 交易恢复处理");    
 
}    
 
-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error{
    NSLog(@"-------paymentQueue----");
}    
 
#pragma mark connection delegate
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    NSLog(@"%@",  [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease]);
}
- (void)connectionDidFinishLoading:(NSURLConnection *)connection{    
 
}    
 
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response{
    switch([(NSHTTPURLResponse *)response statusCode]) {
        case 200:
        case 206:
            break;
        case 304:
            break;
        case 400:
            break;
        case 404:
            break;
        case 416:
            break;
        case 403:
            break;
        case 401:
        case 500:
            break;
        default:
            break;
    }
}    
 
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    NSLog(@"test");
}    
 
-(void)dealloc
{
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];//解除监听
    [super dealloc];
}

- (void)removeReceiptData
{
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:IAP_Receipt];
}

- (void)storeReceiptData: (NSString *) receipt
{
    [[NSUserDefaults standardUserDefaults] setObject:receipt forKey:IAP_Receipt];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

@end
