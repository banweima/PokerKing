//
//  WordBoard.cpp
//  blackjack
//
//  Created by Banson Niu on 10/15/12.
//
//

#include "WordBoard.h"
#include "Constants.h"

WordBoard::~WordBoard()
{
    CC_SAFE_RELEASE(mBgSprite1);
    CC_SAFE_RELEASE(mTextLabel);
}

WordBoard* WordBoard::create()
{
    WordBoard * wordBoard=new WordBoard();
    
	if (wordBoard && wordBoard->init())
	{
		wordBoard->autorelease();
		return wordBoard;
	}
    
	CC_SAFE_DELETE(wordBoard);
	return NULL;
}

bool WordBoard::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCSprite::init());
        
        setBgSprite1(CCSprite::createWithSpriteFrameName("talk"));
        setTextLabel(CCLabelTTF::create("", "Helvetica", 12));
        
        this->addChild(mBgSprite1);
        this->addChild(mTextLabel);
        //        mBgSprite->addChild(mCountText);
        //        mCountText->setPosition(ccp(mBgSprite->getContentSize().width/2, mBgSprite->getContentSize().height/2));
        
        mBgSprite1->setScaleX(0.5);

        
        mTextLabel->setColor(ccWHITE);
        bRet = true;
    } while (0);
	return bRet;
}

void WordBoard::setText(std::string content, std::string fontName, float fontSize)
{
    mTextLabel->setFontName(fontName.c_str());
    mTextLabel->setFontSize(fontSize);
    mTextLabel->setString(content.c_str());
}

void WordBoard::setText(std::string content)
{
    mTextLabel->setString(content.c_str());
}


std::string WordBoard::getText()
{
    return mTextLabel->getString();
}