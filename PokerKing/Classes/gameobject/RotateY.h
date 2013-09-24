//
//  RotateY.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-24.
//
//

#ifndef __PokerKing__RotateY__
#define __PokerKing__RotateY__

#include "cocos2d.h"

USING_NS_CC;


/** @brief Rotates a CCNode object clockwise a number of degrees by modifying it's rotation attribute.
*/
class RotateY : public CCActionInterval
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, float fDeltaAngle);

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static RotateY* actionWithDuration(float duration, float fDeltaAngle);
    /** creates the action */
    static RotateY* create(float duration, float fDeltaAngle);
    
    void SetRotateY(float fa);
    
protected:
    float m_fAngle;
    float m_fStartAngle;
};


#endif /* defined(__PokerKing__RotateY__) */
