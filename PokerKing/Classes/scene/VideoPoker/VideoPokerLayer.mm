//
//  VideoPokerLayer.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#include "VideoPokerLayer.h"
#include "RankingScene.h"
#include "CCBUtility.h"
#include "PlayCard.h"
#include "Constants.h"
#include "CardDeck.h"
#include "HttpImageLoader.h"
#include "platform.h"
#include "SimpleAudioEngine.h"
#include "GameRoomScene.h"
#include "GameKitFactory.h"
#include "MainBoardScene.h"
#include "Loading.h"
#include "BattleInfo.h"
#include "GameServerAction.h"
#include "Banner.h"


VideoPokerLayer::VideoPokerLayer()
: 
mPlayerHandNode(NULL)
, mPlayerCountNode(NULL)
, betCount(0)
, winCount(0)
, totalBonus(0)
, mTotalBonus(NULL)
, mWinChipsSprite(NULL)
, mRoomLevelInfo(NULL)
, mIsFirstHit(true)
, mGold(NULL)
, mLevel(NULL)
, mFX(NULL)
, hadFriendSupport(false)
, mDeal(NULL)
{}

VideoPokerLayer::~VideoPokerLayer()
{
    CC_SAFE_RELEASE(mTotalBonus);
    CC_SAFE_RELEASE(mGold);
    CC_SAFE_RELEASE(mLevel);

    CC_SAFE_RELEASE(mDeal);
    
    CC_SAFE_RELEASE(mPlayerHandNode);
    CC_SAFE_RELEASE(mPlayerCountNode);
    CC_SAFE_RELEASE(mFX);
}

bool VideoPokerLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        this->setupLayer();
        
        bRet = true;
    } while (0);

    setTouchEnabled(true);
    return bRet;
}

void VideoPokerLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/videopoker.ccbi", "VideoPokerLayer", CCLayerLoader::loader(), this);
    this->addChild(node);

    int wh = getWinH();
    if(wh>480)
    {
        Banner * banner = Banner::create();
        banner->retain();
        this->addChild(banner,-100);
    }


    mPlayerHand = PlayCardHand::create(false);
    
    mPlayerHand->setCardCanSelect(true);
    
    int w = getContentSize().width;
    int h = getContentSize().height;
    int handH = h/3;

    mPlayerHand->setPosition(ccp(w/2, h/3));
    
    mPlayerHandNode->addChild(mPlayerHand);
    
    mPlayerCount = CardCount::create();
    
    mPlayerCount->setPosition(ccp(w/2, h/2 - handH*0.35));
    
    mPlayerCountNode->addChild(mPlayerCount);
    
   
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();    
    
    mWinChipsSprite = CCLabelTTF::create("", "Thonburi", 16);
    mWinChipsSprite->setPosition( ccp(size.width/2, size.height/2 - 30) );
    this->addChild(mWinChipsSprite);
    
    
    showUserInfo();
    
    mPlayerCount->setVisible(false);
    
    mFX->stopSystem();
}

void VideoPokerLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader)
{
    
}


SEL_MenuHandler VideoPokerLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFriendsClicked", VideoPokerLayer::onFriendsClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRankClicked", VideoPokerLayer::onRankClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSettingClicked", VideoPokerLayer::onSettingClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", VideoPokerLayer::onHomeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDealClicked", VideoPokerLayer::onDealClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBetClicked", VideoPokerLayer::onBetClicked);

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMaxClicked", VideoPokerLayer::onMaxClicked);



    
    return NULL;
}

SEL_CCControlHandler VideoPokerLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool VideoPokerLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {


    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTotalBonus", CCLabelTTF *, mTotalBonus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGold", CCLabelTTF *, mGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel", CCLabelTTF *, mLevel);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerHandNode", CCNode *, mPlayerHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerCountNode", CCNode *, mPlayerCountNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFX", CCParticleSystemQuad *, mFX);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDeal", CCMenuItemImage *, mDeal);
    return false;
}


void VideoPokerLayer::onFriendsClicked(CCObject * pSender)
{
    gotoOtherScene(Friends_Scene);
}

void VideoPokerLayer::onRankClicked(CCObject * pSender)
{
    gotoOtherScene(Rank_Scene);
}

void VideoPokerLayer::onHomeClicked(CCObject * pSender)
{
    gotoOtherScene(BackScene);
}

void VideoPokerLayer::onSettingClicked(CCObject * pSender)
{
    gotoOtherScene(Setting_Scene);
}


void VideoPokerLayer::gotoOtherScene(GameScene otherScene)
{
    if(!mIsFirstHit && otherScene == BackScene)
    {
        SceneControler::sharedSceneControler()->gotoSceneWithAlert(otherScene, "翻翻乐", "您已经在牌局中，现在离开无法收回已下注的金币。\r\n确定要离开吗？", this);
    }
    else
    {
        SceneControler::sharedSceneControler()->gotoScene(otherScene);
    }
}

void VideoPokerLayer::setHideButton(CCNode* node)
{
    node->setVisible(false);
}

void VideoPokerLayer::hideButton(CCNode* node)
{
    if (node==NULL) {
        return;
    }
    
    node->runAction(CCSequence::create(
                            CCSpawn::create(
                                CCScaleTo::create(HideButtonTime, 0.1),
                               CCFadeOut::create(HideButtonTime),
                                    NULL),
                           CCCallFuncN::create(this, callfuncN_selector(VideoPokerLayer::setHideButton)),
                           NULL));
}

void VideoPokerLayer::showButton(CCNode* node)
{
    if (node==NULL) {
        return;
    }
    
    node->setVisible(true);
    node->setScale(0.1);
    node->runAction(CCSpawn::create(
                                    CCScaleTo::create(HideButtonTime, 1.0),
                                    CCFadeIn::create(HideButtonTime),
                                    NULL));
}

void VideoPokerLayer::onDealClicked(CCObject * pSender)
{
    if(mIsFirstHit)
    {
        mFX->stopSystem();
        if(UserInfo::sharedUserInfo()->getGold() < betCount)
        {
            AlertLayer * shareAlert = AlertLayer::create("翻翻乐", "您金币不足，请先去兑换", true, this, (SEL_CallFuncND)callfuncND_selector(VideoPokerLayer::gotoShop));
            this->addChild(shareAlert, Child_Order_Top);
        }
        else
        {
            startOnlineBattle();
        }
    }
    else
    {
        mDeal->setEnabled(false);
        mIsFirstHit = !mIsFirstHit;
        
        int cardCount = mPlayerHand->getNumberOfCards();
        PlayCard * changeCard;
        CardDeckCard * cardDeckCard;
        for(int i = 0; i< cardCount; i++)
        {
            changeCard = mPlayerHand->getCard(i);

            if(!changeCard->isSelected())
            {
                changeCard->flipCard();
                
                cardDeckCard = CardDeck::sharedCardDeck()->getNextCard();

                changeCard->resetCard(cardDeckCard->getSuit(), cardDeckCard->getType());
                
                changeCard->flipCard(0.1);
            }
        
        }
        this->checkPokerHand();
        this->winCalc();
    }
}


void VideoPokerLayer::checkPokerHand()
{
    mPlayerPokerHand = mPlayerHand->getPokerHand(false,false);
    
    mPlayerCount->setVisible(true);
    mPlayerCount->setPokerHand(mPlayerPokerHand);
}


void VideoPokerLayer::setRoomLevelInfo(RoomLevelInfo *RoomLevelInfo)
{
    mRoomLevelInfo = RoomLevelInfo;
    mRoomLevelInfo->retain();
    onBetClicked();
}

////////////////////////////////////////////////////////////////
//
// Hit.
//

void VideoPokerLayer::onBetClicked()
{
    if(!mIsFirstHit)
    {
        return;
    }
    
    betCount += mRoomLevelInfo->getMinHand();
    if(betCount > mRoomLevelInfo->getMaxHand())
    {
        betCount = mRoomLevelInfo->getMinHand();
    }
    mWinChipsSprite->setString(CCString::createWithFormat("Bet: %d", betCount)->getCString());
    
}
////////////////////////////////////////////////////////////////
//
// Start.
void VideoPokerLayer::onMaxClicked()
{
    if(!mIsFirstHit)
    {
        return;
    }
    betCount = mRoomLevelInfo->getMaxHand();
    mWinChipsSprite->setString(CCString::createWithFormat("Bet: %d", betCount)->getCString());
}

void VideoPokerLayer::winCalc()
{

    if(!hadFriendSupport)
    {
        friendSupport();
        
        if(hadFriendSupport)
        {
            return;
        }
    }
    
        
    //All the Odds is base on the basic bet count 'ante', so if OnePair wins, the Odds is 3.
    int isPlayerWin = -1;
    
    if(mPlayerPokerHand > OnePair)
    {
        isPlayerWin = 1;
    }
    else if(mPlayerPokerHand == OnePair)
    {
        if(mPlayerHand->getOnePairCarType() == 1 ||
        mPlayerHand->getOnePairCarType() >= 11 )
        {
            isPlayerWin = 1;
        }
    }
    
        
    
    //Need discuss with Junjie
    
    int Odds = 0;
    long extraBonus = 0;

    if(1 == isPlayerWin)
    {
        switch (mPlayerPokerHand)
        {
            case OnePair:
            Odds = 1 -1;
            break;
            case TwoPair:
            Odds = 2 -1;
            break;
            case ThreeOfOneKind:
            Odds = 3 -1;
            mFX->setTotalParticles(150);
            break;
            case Straight:
            Odds = 4 -1;
            mFX->setTotalParticles(150);
            break;
            case Flush:
            Odds = 6 - 1;
            mFX->setTotalParticles(200);
            break;
            case FullHouse:
            Odds = 9 - 1;
            mFX->setTotalParticles(200);
            break;
            case FourOfOneKind:
            Odds = 25 - 1;
            mFX->setTotalParticles(250);
            break;
            case StraightFlush:
            Odds = 50 -1;
            extraBonus = (long)(totalBonus * 0.1);
            mFX->setTotalParticles(250);
            break;
            case RoyalStraightFlush:
            Odds = 250 - 1;
            extraBonus = totalBonus;
            mFX->setTotalParticles(300);
            break;
        }
        
        winCount = betCount * Odds + extraBonus;
        CCLog("winCount: %d", winCount);
//        [[GameKitFactory sharedGameKitFactory] submitScore:LeaderBoard_VideoPokerWinner :winCount ];
    }
    else
    {
        winCount = -1 * betCount;
    }
    
    if(isPlayerWin == 1)
    {
        
        if(mPlayerPokerHand >= ThreeOfOneKind)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.mp3");
            mFX->resetSystem();
        }
    }
    else
    {
    
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Loser.wav");
    }

    
    mWinChipsSprite->setString(CCString::createWithFormat("Bet: %d   Win: %d", betCount,winCount)->getCString());

    mPlayerCount->setWin(isPlayerWin);
    

    uploadMatchResult(winCount);
    
}

void VideoPokerLayer::startOnlineBattle()
{
    Loading::sharedLoading()->addLoadingToLayer(this,10);

    GameServerAction::sharedGameServerAction()->startBattle(VideoPoker,SingleBattle,betCount, mRoomLevelInfo->getRoomLevel(),
    this, callfuncND_selector(VideoPokerLayer::startOnlineBattle_done));

}

void VideoPokerLayer::startOnlineBattle_done(CCNode* pSender, void* data)
{
    if((bool)data)
    {
        startGame();
    }
    else
    {
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"翻翻乐"
                                message:@"大侠，网络不给力请重试！"
                               delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];

        [alerView show];
        [alerView release];
        Loading::sharedLoading()->removeLoading();
    }
    
}

void VideoPokerLayer::startGame()
{    
    mWinChipsSprite->setString("");
    
    // Clear the hand before starting a new game:
    mPlayerHand->clearHand();
    
    // Reset the counts and hide them:
    mPlayerCount->setCount(0);
    
    mPlayerCount->setVisible(true);
    
    
    CardDeck::sharedCardDeck()->shuffleCardDeck();

    mPlayerHand->setVisible(true);

    this->reorderChild(mPlayerHand, 0);
    
    mPlayerHand->addNextCardToHand(false,0);
    mPlayerHand->addNextCardToHand(false,0);
    mPlayerHand->addNextCardToHand(false,0);
    mPlayerHand->addNextCardToHand(false,0);
    mPlayerHand->addNextCardToHand(false,0);
    
    mPlayerHand->setAnchorPoint(ccp(0,0));
    mPlayerHand->setPosition(ccp(getWinW() /6,getWinH()/4));
    
    float posX = 0;
//    float posY = getWinH() /8;
    for(int i = 0; i< 5; i++)
    {
        mPlayerHand->getCard(i)->setCardScale(0.75);

        mPlayerHand->getCard(i)->setAnchorPoint(ccp(0,0));
        //CCLOG("Card %d width: %f", i, mPlayerHand->getCard(i)->getCardWidth());
        posX = (getWinW() /6) * (i);
        mPlayerHand->getCard(i)->moveTo(posX, 0,0);
    }
    
    this->checkPokerHand();
    
    mIsFirstHit = !mIsFirstHit;

    Loading::sharedLoading()->removeLoading();
}


void VideoPokerLayer::uploadMatchResult(float result)
{
    
    hadFriendSupport = false;
    
    GameServerAction::sharedGameServerAction()->endBattle((long)result, 0, mRoomLevelInfo->getRoomLevel(), this, callfuncND_selector(VideoPokerLayer::uploadMatchResult_Done));
}

void VideoPokerLayer::uploadMatchResult_Done(CCNode* pSender, void* data)
{
    if((bool)data)
    {
        showUserInfo();
    }
    else
    {
        
        NSString * msg = [[NSString alloc] initWithFormat:@"非常抱歉，服务器未能正常处理该次牌局的结果，请记录下牌局ID:%d  通过QQ群，可以获得双倍赔偿！",(int)BattleInfo::sharedBattleInfo()->getBattleID()];
        
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"翻翻乐"
                                message:msg
                               delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];

        [alerView show];
        [alerView release];
    }
    
    mDeal->setEnabled(true);
}

void VideoPokerLayer::showUserInfo()
{
    long userCoinAmount = UserInfo::sharedUserInfo()->getGold();
    
    CCString * userCoinString = NULL;
    
    if(userCoinAmount < 10000)
    {
        userCoinString = CCString::createWithFormat("%d",userCoinAmount);
    }
    else if(userCoinAmount < 1000000)
    {
        userCoinString = CCString::createWithFormat("%d千",userCoinAmount / 1000);
    }
    else if(userCoinAmount < 1000000000)
    {
        userCoinString = CCString::createWithFormat("%d百万",userCoinAmount / 1000000);
    }
    else if(userCoinAmount < 1000000000000)
    {
        userCoinString = CCString::createWithFormat("%d十亿",userCoinAmount / 1000000000);
    }
    
    mGold->setString(userCoinString->getCString());
    
    mLevel->setString(CCString::createWithFormat("%d",UserInfo::sharedUserInfo()->getLevel())->getCString());

}

void VideoPokerLayer::friendSupport()
{
    int supportRand = arc4random() % 100 + 1;
    
    int friendsCount = UserInfo::sharedUserInfo()->getFriendsList()->count();
    
    int friendSupportValue = FriendSupportRate + friendsCount;
    
    friendSupportValue = (friendSupportValue > 20)?20:friendSupportValue;
    
    if(supportRand < friendSupportValue)
    {
        hadFriendSupport = true;
        
        CCSprite * friendSprite = CCSprite::createWithSpriteFrameName("bet_blue");
        friendSprite->setAnchorPoint(ccp(0,0.5));
        friendSprite->setPosition(ccp(getWinW(),getWinH()/2));
        
        CCSprite * friendHead = NULL;
        CCLabelTTF *cellNameLabel = CCLabelTTF::create("", "Arial", 18, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        cellNameLabel->setAnchorPoint(ccp(0,0));

        if(friendsCount > 0)
        {
            int friendIndex = arc4random() % friendsCount;
            SimpleUserInfo * friendInfo = (SimpleUserInfo *)UserInfo::sharedUserInfo()->getFriendsList()->objectAtIndex(friendIndex);
            
            if(friendInfo->getGender() == "m")
            {
                friendHead = CCSprite::createWithSpriteFrameName("crown_king");
            }
            else
            {
                friendHead = CCSprite::createWithSpriteFrameName("crown_queen");
            }
            
            cellNameLabel->setString(friendInfo->getUserName().c_str());
        
        }
        else
        {
            friendHead = CCSprite::createWithSpriteFrameName("crown_queen");
            cellNameLabel->setString("好友越多，助力越多");
        }
        
        friendHead->setAnchorPoint(ccp(0,0.5));
        friendHead->setPosition(ccp(5.0,friendSprite->getContentSize().height/2));
        

        cellNameLabel->setAnchorPoint(ccp(0,0.5));
        cellNameLabel->setPosition(ccp(friendHead->getPositionX() + friendHead->getContentSize().width + 2,friendHead->getPositionY()));
        
        friendSprite->addChild(friendHead);
        friendSprite->addChild(cellNameLabel);
        
        this->addChild(friendSprite);

        friendSprite->runAction(CCSequence::create(
                                    CCMoveTo::create(0.5, ccp(getWinW() - friendSprite->getContentSize().width,friendSprite->getPositionY())),
                                    CCCallFunc::create(this, callfunc_selector(VideoPokerLayer::showFriendSupportMessage)),
                                    CCDelayTime::create(0.5),
                                    CCMoveTo::create(0.5, ccp(getWinW(),friendSprite->getPositionY())),
                                    NULL));
    }
}

void VideoPokerLayer::showFriendSupportMessage()
{
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"翻翻乐"
                                message:@"好友来助力，可以多选一次！"
                               delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];

    [alerView show];
    [alerView release];
    
    mDeal->setEnabled(true);
    mIsFirstHit = false;
}

void VideoPokerLayer::gotoShop(cocos2d::CCNode *pSender, void *data)
{
    gotoOtherScene(Shop_Scene);
}

void VideoPokerLayer::onEnter()
{
    CCLOG("onEnter");
    showUserInfo();
    CCLayer::onEnter();
}