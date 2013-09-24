//
//  ImageController.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-10.
//
//

#include "ImageController.h"
#include "Helpers.h"

ImageController::ImageController()
{

}

ImageController::~ImageController()
{

}

void ImageController::retrieveAvartaImage(std::string imageUrl, cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    mTarget = target;
    mCallFuncO = callback;
    
    if(strlen(imageUrl.c_str()) < 1)
    {
        CCLOG("imageUrl is empty.");
        if (mTarget && mCallFuncO) {
            (mTarget->*mCallFuncO)(NULL);
        }
        
    }
    
    
    
    CCLOG("imageUrl: %s",imageUrl.c_str());
    
    CCString * userImageFileName = CCString::createWithFormat("%s.png", Helpers::getRandomString(16)->getCString());
    
    std::string imageFile = LoadStringFromXML(imageUrl.c_str());
    
    if(imageFile.length() > 3)
    {
        CCImage* img = new CCImage();
        const char * imgPathName = (CCFileUtils::sharedFileUtils()->getWriteablePath() + imageFile).c_str();
        
        if(img->initWithImageFile(imgPathName))
        {
            CCLog("img size = %d, %d", img->getWidth(), img->getHeight());

            CCTexture2D* texture2D = new CCTexture2D();
            texture2D->initWithImage(img);
            
            CCSprite * mAvartaImage = CCSprite::createWithTexture(texture2D);
            mAvartaImage->retain();

            
            if (mTarget && mCallFuncO) {
            (mTarget->*mCallFuncO)(mAvartaImage);
            } 
        }
        else
        {
            HttpImageLoader *imageLoader = HttpImageLoader::create();
            imageLoader->retrieveImageData(imageUrl.c_str(), userImageFileName->getCString(),this, callfuncND_selector(ImageController::retrieveAvartaImage_Done));
        }
    }
    else
    {
        
        SaveStringToXML(imageUrl.c_str(), userImageFileName->getCString());
        
        HttpImageLoader *imageLoader = HttpImageLoader::create();
        imageLoader->retrieveImageData(imageUrl.c_str(), userImageFileName->getCString(),this, callfuncND_selector(ImageController::retrieveAvartaImage_Done));
    }
}

void ImageController::retrieveAvartaImage_Done(cocos2d::CCNode *node, void *data)
{
    CCLog("retrieveAvartaImage_Done");
    if(data)
    {

        CCTexture2D* tex2d = (CCTexture2D*)data;
        
        CCSprite * mAvartaImage = CCSprite::createWithTexture(tex2d);
        
        mAvartaImage->retain();

        if (mTarget && mCallFuncO) {
                    (mTarget->*mCallFuncO)(mAvartaImage);
                }
    }
    else
    {
        if (mTarget && mCallFuncO) {
                    (mTarget->*mCallFuncO)(NULL);
                }
    }
}
