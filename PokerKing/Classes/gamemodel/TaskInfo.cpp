//
//  TaskInfo.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-17.
//
//

#include "TaskInfo.h"


USING_NS_CC_EXT;

TaskInfo* TaskInfo::create()
{
    TaskInfo* pTaskInfo = new TaskInfo();
    
    if (pTaskInfo && pTaskInfo->init())
    {
        pTaskInfo->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pTaskInfo);
    }
    
    return pTaskInfo;

}


void TaskInfo::parseTaskInfo(CCDictionary * TaskInfoDic)
{    
    mTaskId = ((CCString *)TaskInfoDic->objectForKey("taskId"))->intValue();
    
    if(TaskInfoDic->objectForKey("description"))
    mDescription = ((CCString *)TaskInfoDic->objectForKey("description"))->getCString();
    
    if(TaskInfoDic->objectForKey("isDaily"))
    mIsDaily = ((CCString *)TaskInfoDic->objectForKey("isDaily"))->intValue();
    
    mStatus = ((CCString *)TaskInfoDic->objectForKey("status"))->intValue();
    
}


bool TaskInfo::init()
{
    mTaskId = 1;
    mDescription = "";
    mIsDaily = 1;
    mStatus = 0;
    return true;
}