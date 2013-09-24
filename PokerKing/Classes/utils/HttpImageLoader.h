//
//  HttpImageLoader.h
//  blackjack
//
//  Created by Banson Niu on 9/22/12.
//
//

#ifndef __blackjack__HttpImageLoader__
#define __blackjack__HttpImageLoader__

#include "cocos2d.h"
#include "FileHelper.h"
#include "Constants.h"

USING_NS_CC;

class HttpImageLoader : public CCObject
{
private:
    CCObject* mpTarget;
    SEL_CallFuncND mpSelector;
    
private:
    char* mImageData();
    std::string imageFileName;
    
public:
    static HttpImageLoader* create();
    HttpImageLoader();
    ~HttpImageLoader();
    
public:
    void retrieveImageData(const char* url, std::string saveFileName, CCObject* pTarget, SEL_CallFuncND pSelector);
    void retrieveImageData_ReqDone(CCNode* sender, void*data);
    
};

#endif /* defined(__blackjack__HttpImageLoader__) */
