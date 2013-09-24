//
//  BroadCast.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-30.
//
//

#ifndef __PokerKing__BroadCast__
#define __PokerKing__BroadCast__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServerAction.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BroadCast : public CCSprite
{
private:
    CCSprite* mBgSprite;
    CCLabelTTF* mContentText;
    CCArray * mBCContentList;
    
    CCSpriteBatchNode* mSpriteBatchNode;
    int BCCount;
    
    void hideAll();
    void retrieveBroadCast_Done(CCNode * pSender, void * data);
    
    void retrieveBroadCast();
    void playContentList();
    
    CCPoint lastPoint;
    bool isRolling;
public:
    
    BroadCast();
    virtual ~BroadCast();
    static BroadCast* sharedBroadCast(void);
    bool init();
    
    void playContent(std::string content);
    void parseBCContent(CCDictionary * bcDic);
    BroadCast * addBCToLayer(CCLayer * parentLayer);
    void pauseRolling();

};


#endif /* defined(__PokerKing__BroadCast__) */
