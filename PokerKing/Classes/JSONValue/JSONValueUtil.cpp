//
//  JSONValueUtil.cpp
//  madattack
//
//  Created by Pan ZF/Banson Niu on 12-9-1.
//
//

#include "JSONValueUtil.h"
#include "Json/json.h"

CCDictionary* JSONValueUtil::JSONValue(const char* JsonStr)
{
    Json::Reader reader;
	Json::Value dict;
    
    if(!reader.parse(JsonStr, dict))
        return NULL;
    
    CCDictionary* returnDic = JSONValueUtil::ParseJsonData(dict);
    
    return returnDic;
}

CCDictionary* JSONValueUtil::ParseJsonData(Json::Value &dict)
{
    CCDictionary *dic = CCDictionary::create();
    
    Json::Value::Members member = dict.getMemberNames();
    for(Json::Value::Members::iterator iter=member.begin(); iter!=member.end(); iter++)
    {
        const char* node_name = (*iter).c_str();
        if(dict[*iter].isArray())
        {
            if(node_name != NULL && strlen(node_name) > 0)
            {
                CCArray* tmpArray = JSONValueUtil::ParseJsonArray(dict[*iter]);
                if(tmpArray != NULL && tmpArray->count()>0)
                {
                    dic->setObject(tmpArray, *iter);
                }
            }
        }
        else if(dict[*iter].isObject())
        {
            if(node_name != NULL && strlen(node_name) > 0)
            {
                CCDictionary* tmpDic = JSONValueUtil::ParseJsonData(dict[*iter]);
                if(tmpDic != NULL && tmpDic->count() > 0)
                {
                    dic->setObject(tmpDic, *iter);
                }
            }
        }
        else if(dict[*iter].isInt())
        {
            if(node_name != NULL && strlen(node_name) > 0)
            {
                CCString *str = CCString::createWithFormat("%d", dict[*iter].asInt());
                dic->setObject(str, *iter);
            }
        }
        else if(dict[*iter].isDouble())
        {
            if(node_name != NULL && strlen(node_name) > 0)
            {
                CCString *str = CCString::createWithFormat("%f", dict[*iter].asDouble());
                dic->setObject(str, *iter);
            }
        }
        else if(dict[*iter].isString())
        {
            if(node_name != NULL && strlen(node_name) > 0)
            {
                CCString *str = CCString::create(dict[*iter].asString());
                dic->setObject(str, node_name);
            }
        }
    }
    
    return dic;
}

CCArray* JSONValueUtil::ParseJsonArray(Json::Value &dict)
{
    CCArray *array = CCArray::create();
    
    for(int i=0; i<dict.size(); i++)
    {
        if(dict[i].isArray())
        {
            CCArray* tmpArray = JSONValueUtil::ParseJsonArray(dict[i]);
            if(tmpArray != NULL && tmpArray->count()>0)
            {
                array->addObject(tmpArray);
            }
        }
        else if(dict[i].isObject())
        {
            CCDictionary* tmpDic = JSONValueUtil::ParseJsonData(dict[i]);
            if(tmpDic != NULL && tmpDic->count() > 0)
            {
                array->addObject(tmpDic);
            }
        }
        else if(dict[i].isInt())
        {
            CCString *str = CCString::createWithFormat("%d", dict[i].asInt());
            array->addObject(str);
        }
        else if(dict[i].isDouble())
        {
            CCString *str = CCString::createWithFormat("%f", dict[i].asDouble());
            array->addObject(str);
        }
        else if(dict[i].isString())
        {
            CCString *str = CCString::createWithFormat("%s", dict[i].asString().c_str());
            array->addObject(str);
        }
    }
    
    return array;
}
