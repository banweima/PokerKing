//
//  Helpers.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-27.
//
//

#ifndef __PokerKing__Helpers__
#define __PokerKing__Helpers__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"
#include "support/base64.h"
#include "CCCrypto.h"
#include "md5.h"

USING_NS_CC;


class Helpers : public CCObject
{    
public:
    
    static CCString * getValueFromDic(CCDictionary * dic, std::string key);
    
    static CCString * getRandomString(int strLen);
    
    static std::string encryptBaseString(std::string sourceString);
    
    static std::string decryptBaseString(std::string s);
    
    static std::string parseEncryptBaseString(std::string sourceString);
    
    static std::string b64Encode(unsigned char const* , unsigned int len);
    static std::string b64Decode(std::string const& s);

private:
    static string toUpper(string s);
    static string toReverse(string s);
    static string substring(string s, int startPos, int endPos);
    static string trimString(string s);
};

#endif /* defined(__PokerKing__Helpers__) */
