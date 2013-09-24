//
//  JSONValueUtil.h
//  madattack
//
//  Created by Pan ZF/Banson Niu on 12-9-1.
//
//

#ifndef __madattack__JsonToDic__
#define __madattack__JsonToDic__

#include <iostream>
#include "cocos2d.h"
#include "json/json.h"

USING_NS_CC;


class JSONValueUtil : public CCObject
{
public:
    static CCDictionary* JSONValue(const char* JsonStr);
private:
    static CCDictionary* ParseJsonData(Json::Value &dict);
    static CCArray* ParseJsonArray(Json::Value &dict);
};
#endif /* defined(__madattack__JsonToDic__) */
