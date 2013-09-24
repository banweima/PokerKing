//
//  ImageController.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-10.
//
//

#ifndef __PokerKing__ImageController__
#define __PokerKing__ImageController__

#include "cocos2d.h"
#include "FileHelper.h"
#include "HttpImageLoader.h"


USING_NS_CC;


class ImageController : public CCObject
{    
public:

    ImageController();
    ~ImageController();
    void retrieveAvartaImage(std::string imageUrl, cocos2d::CCObject *target, SEL_CallFuncO callback);
    
    
private:
    CCObject *mTarget;
    SEL_CallFuncO mCallFuncO;

    void retrieveAvartaImage_Done(CCNode* node, void* data);
};

#endif /* defined(__PokerKing__ImageController__) */
