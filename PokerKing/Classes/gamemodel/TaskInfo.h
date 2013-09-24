//
//  TaskInfo.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-17.
//
//

#ifndef __PokerKing__TaskInfo__
#define __PokerKing__TaskInfo__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"

USING_NS_CC;


class TaskInfo : public CCObject
{
public:
    CC_SYNTHESIZE(int, mTaskId, TaskId);
    CC_SYNTHESIZE(std::string, mDescription, Description);
    CC_SYNTHESIZE(int, mIsDaily, IsDaily);
    CC_SYNTHESIZE(int, mStatus, Status);


public:
    static TaskInfo* create();
    void parseTaskInfo(CCDictionary * TaskInfoDic);
    bool init();

};


#endif /* defined(__PokerKing__TaskInfo__) */
