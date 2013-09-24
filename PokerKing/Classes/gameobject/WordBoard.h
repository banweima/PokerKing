//
//  WordBoard.h
//  blackjack
//
//  Created by Banson Niu on 10/15/12.
//
//

#ifndef __blackjack__WordBoard__
#define __blackjack__WordBoard__

#include "cocos2d.h"

USING_NS_CC;

class WordBoard : public CCSprite
{
private:
    CC_SYNTHESIZE_RETAIN(CCSprite*, mBgSprite1, BgSprite1);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, mTextLabel, TextLabel);
    
    CCSpriteBatchNode* mSpriteBatchNode;
    
public:
    ~WordBoard();
    static WordBoard* create();
    bool init();
    
    void setText(std::string content, std::string fontName, float fontSize);
    void setText(std::string content);
    std::string  getText();

};

#endif /* defined(__blackjack__WordBoard__) */
