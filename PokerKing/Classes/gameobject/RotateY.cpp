//
//  RotateY.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-24.
//
//

#include "RotateY.h"


//
// RotateBy
//
long tick = 0;

RotateY* RotateY::actionWithDuration(float duration, float fDeltaAngle)
{
    return RotateY::create(duration, fDeltaAngle);
}

RotateY* RotateY::create(float duration, float fDeltaAngle)
{
    RotateY *pRotateBy = new RotateY();
    pRotateBy->initWithDuration(duration, fDeltaAngle);
    pRotateBy->autorelease();

    tick = 0;

    return pRotateBy;
}

bool RotateY::initWithDuration(float duration, float fDeltaAngle)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fAngle = fDeltaAngle;
        return true;
    }

    return false;
}

CCObject* RotateY::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    RotateY* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (RotateY*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new RotateY();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_fAngle);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void RotateY::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_fStartAngle = 0;//pTarget->getRotation();
}

void RotateY::update(float time)
{
    // XXX: shall I add % 360
    if (m_pTarget)
    {
        tick++;
//        CCLOG("tick %d", tick);
//        CCLOG("Angle %f", m_fStartAngle + m_fAngle * tick);
        SetRotateY(m_fStartAngle + m_fAngle * tick);
    }
}

CCActionInterval* RotateY::reverse(void)
{
    return RotateY::create(m_fDuration, -m_fAngle);
}

void RotateY::SetRotateY(float fa)
{
    
    float ra = (float)CC_DEGREES_TO_RADIANS(fa);
    float i = sinf(ra) * m_pTarget->getCamera()->getZEye();
    float j = cosf(ra) * m_pTarget->getCamera()->getZEye();
    m_pTarget->getCamera()->setEyeXYZ(i, 0, j);
    
//    int isXYNegative = 1;
//
//    fa = ((int)fa) % 360;
//    CCLOG("fa %f", fa);
//    if((fa> 0 && fa < 90) || (fa> 180 && fa < 270))
//    {
//        isXYNegative = -1;
//    }
//    else
//    {
//        isXYNegative = 1;
//    }
//
//    
//    float x = isXYNegative * abs(sinf(30) * cosf(fa) *  CCCamera::getZEye());
//    float y = isXYNegative * abs(cosf(30) * cosf(fa) *  CCCamera::getZEye());
//    float z =  sinf(fa) *  CCCamera::getZEye();
//    m_pTarget->getCamera()->setEyeXYZ(x, 0, y);
}
