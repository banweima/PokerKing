//
//  blackjackAppDelegate.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"
#include "cocos2d.h"
#include "GameInfo.h"
#include "LoginScene.h"
#include "MainBoardScene.h"
#include "Helpers.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    TargetPlatform target = getTargetPlatform();
    
    if (target == kTargetIpad)
    {
        // ipad
        
        if (pDirector->enableRetinaDisplay(true))
        {
            // ipad hd
            CCFileUtils::sharedFileUtils()->setResourceDirectory("ipadhd");
        }
        else
        {
            CCFileUtils::sharedFileUtils()->setResourceDirectory("ipad");
        }
    }
    else if (target == kTargetIphone)
    {
        // iphone
        
        if (pDirector->enableRetinaDisplay(true))
        {
            // iphone hd
            CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        }
    }

//    string s = Helpers::encryptBaseString("userType=2&snsId=2605248414&snsToken=2.00iH3_qCeetV_Da9f17a16b0sV7aUC&deviceToken好大=(null)");
//    
//    string e = Helpers::decryptBaseString(s);
//    
//    CCLOG(e.c_str());
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 100);
    
    //GameInfo::sharedGameInfo()->setEnv(Standalone);
//    GameInfo::sharedGameInfo()->setEnv(Dev);
//    GameInfo::sharedGameInfo()->setEnv(Sandbox);
    GameInfo::sharedGameInfo()->setEnv(Production);

    // create a scene. it's an autorelease object
    CCScene *pScene = NULL;

    if((GameInfo::sharedGameInfo())->getEnv() == Standalone)
    {
        pScene = MainBoardScene::create();
    }
    else
    {
        pScene = LoginScene::create();
    }
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

