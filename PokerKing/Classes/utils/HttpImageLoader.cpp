//
//  HttpImageLoader.cpp
//  blackjack
//
//  Created by Banson Niu on 9/22/12.
//
//

#include "HttpImageLoader.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;




HttpImageLoader::HttpImageLoader()
{
}

HttpImageLoader::~HttpImageLoader()
{
}

HttpImageLoader* HttpImageLoader::create()
{
    HttpImageLoader *loader=new HttpImageLoader();

    if (loader)
    {
        loader->autorelease();
        return loader;
    }

    CC_SAFE_DELETE(loader);
    return NULL;
}


void HttpImageLoader::retrieveImageData(const char* url, std::string saveFileName, CCObject* pTarget, SEL_CallFuncND pSelector)
{
    if(url==NULL || pTarget==NULL || pSelector==NULL)
        return;
    
    mpTarget = pTarget;
    mpSelector = pSelector;
    
    imageFileName = saveFileName;

    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(url);
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, callfuncND_selector(HttpImageLoader::retrieveImageData_ReqDone));
    CCHttpClient::getInstance()->send(request);
    request->release();

}

void HttpImageLoader::retrieveImageData_ReqDone(CCNode* sender, void*data)
{
    CCHttpResponse *response = (CCHttpResponse *)data;
//    CCLog("Response Code = %d", response->getResponseCode());
    
    if(response->isSucceed())
    {
        std::vector<char>* str = response->getResponseData();

        unsigned char* imgData = (unsigned char*)str->data();
        
        
        CCImage* img = new CCImage();
        img->initWithImageData(imgData, str->size());
//        CCLog("img size = %d, %d", img->getWidth(), img->getHeight());
        
        const char * imgPathName = (CCFileUtils::sharedFileUtils()->getWriteablePath() + imageFileName).c_str();
        
        img->saveToFile(imgPathName);

        CCTexture2D* texture2D = new CCTexture2D();
        texture2D->initWithImage(img);
        
        if (mpTarget && mpSelector)
        {
            (mpTarget->*mpSelector)((CCNode *)this, texture2D);
        }
    }
    else
    {
        if (mpTarget && mpSelector)
        {
            (mpTarget->*mpSelector)((CCNode *)this, NULL);
        }
    }
}