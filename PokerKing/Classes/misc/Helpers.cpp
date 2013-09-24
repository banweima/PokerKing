//
//  Helpers.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-27.
//
//

#include "Helpers.h"
#include <algorithm>
#include <string>
#include <functional>

static const std::string dataChars = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


CCString * Helpers::getValueFromDic(CCDictionary * dic, std::string key)
{
    if(dic->objectForKey(key))
    {
        return (CCString *)dic->objectForKey(key);
    }


}

CCString * Helpers::getRandomString(int strLen)
{
    if(strLen < 3)
    {
        return NULL;
    }
    else
    {
        std::string resultString = "";
        for(int i = 0; i < strLen; i ++)
        {
            int charIndex = arc4random() % 26;
            resultString += SmallCharacters[charIndex];
        
        }
        return CCString::create(resultString);
    }

}

std::string Helpers::encryptBaseString(std::string sourceString)
{
    int len = sourceString.length();
    unsigned char * md5Data = new unsigned char[16];

    CCCrypto::MD5((void *)sourceString.data(),len , md5Data);
    
    MD5 md5;
	md5.update(sourceString);
    string md5Value = toUpper(md5.toString());
//    CCLOG(CCString::create(md5Value)->getCString());
    
    string base64Value = b64Encode((unsigned char const*)sourceString.c_str(), sourceString.length());
    
//    CCLOG(base64Value.c_str());
    
    std::replace(base64Value.begin(),base64Value.end(), '=', (char)0);
    
//    CCLOG(base64Value.c_str());
    
    string rev = toReverse(base64Value);
    
//    CCLOG(rev.c_str());
    
    int r = arc4random() % 31;
    r = (r%2 == 0)?(r+1):r;
//    CCLOG("%d",r);
    
    string firstHalf = substring(md5Value, 0, r);
    string secondHalf = substring(md5Value, r, md5Value.length());
    CCString * C3 = CCString::createWithFormat("%s%s%s",firstHalf.c_str(),rev.c_str(),secondHalf.c_str());

//    CCLOG(firstHalf.c_str());
//    CCLOG(secondHalf.c_str());
//    CCLOG(C3->getCString());
    
    CCString * kk = CCString::createWithFormat("%d", r+9);
    
    string k = b64Encode((unsigned char const*)kk->getCString(), kk->length());

    std::replace(k.begin(),k.end(), '=', (char)0);
//    CCLOG(k.c_str());
    
    CCString * C4 = CCString::createWithFormat("%s%s",C3->getCString(),k.c_str());
    
//    CCLOG(C4->getCString());

    return C4->m_sString;
}

std::string Helpers::decryptBaseString(std::string s)
{
//    CCLOG(s.c_str());
    
    string sourceString =  trimString(s);
    
//    CCLOG(sourceString.c_str());
    
    int len = sourceString.length();
    string k = substring(sourceString, len-3, len);
    
    int r =  CCString::create(b64Decode(k))->intValue() - 9;
    
    string firstHalf = substring(sourceString, 0, r);
    string secondHalf = substring(sourceString, len - 3 - (32- r), len - 3);
    
    string md5Comp = CCString::createWithFormat("%s%s",firstHalf.c_str(),secondHalf.c_str())->m_sString;
    
    string c = substring(sourceString, r, len - 3 - (32- r));

    string base64 = toReverse(c.c_str());
    
    string finalValue = b64Decode(base64);
//    CCLOG(finalValue.c_str());
    MD5 md5;
	md5.update(finalValue);
    string md5Value = toUpper(md5.toString());
    
//    CCLOG(md5Comp.c_str());
    
    if(md5Comp.compare(md5Value) == 0)
    {
        return finalValue;
    }
    
    return "";
}

static inline bool baseData(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Helpers::b64Encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for(i = 0; (i <4) ; i++)
                ret += dataChars[char_array_4[i]];
            i = 0;
        }
    }
    
    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        
        for (j = 0; (j < i + 1); j++)
            ret += dataChars[char_array_4[j]];
        
        while((i++ < 3))
            ret += '=';
        
    }
    
    return ret;
    
}

std::string Helpers::b64Decode(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    
    while (in_len-- && ( encoded_string[in_] != '=') && baseData(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = dataChars.find(char_array_4[i]);
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        
        for (j = 0; j <4; j++)
            char_array_4[j] = dataChars.find(char_array_4[j]);
        
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    
    return ret;
}

string Helpers::toUpper(string s)
{
    string temp(s);
    for (int i=0;i<(int)s.size();i++)
    {
        temp[i]=toupper(s[i]);
    }
    return temp;
}

string Helpers::toReverse(string s)
{
    
    string t(s);
    int size = (int)s.size();
    
//    int asc = 0;
//    for(int k = 0; k < 10; k++)
//    {
//        asc = s[size -1 -k];
//        if((asc >= 65 && asc <= 90 ) || (asc >= 97 && asc <= 122) || (asc >= 48 && asc <= 57))
//        {
//            break;
//        }
//        else
//        {
//            size--;
//        }
//    }
    int tIndex = 0;
    for (int i=size -1;i>-1;i--)
    {
        if(s[i] != 0)
        {
            t[tIndex]=s[i];
            tIndex++;
        }
    }
    return t;
}

string Helpers::substring(string s, int startPos, int endPos)
{
    string temp = "";
    
    
    int size = (int)s.size();
    
    int endIndex = size<endPos?size:endPos;
    
    int startIndex = startPos < 0?0:startPos;
    
    int tempIndex = 0;
    for (int i=startIndex;i<endIndex;i++)
    {
        temp.append(&s[i]);
        tempIndex++;
    }
    temp[tempIndex]=0;
//    CCLOG(temp.c_str());
    
    return temp;
}

string Helpers::trimString(string s)
{
   string t(s);
    int size = (int)s.size();

    int asc = 0;
    int tIndex = 0;
    for (int i=0;i < size;i++)
    {
        asc = s[i];
        
        if((asc >= 65 && asc <= 90 ) || (asc >= 97 && asc <= 122) || (asc >= 48 && asc <= 57) ||asc==43||asc==47)
        {
            t[tIndex]=s[i];
            tIndex++;
        }
    }
    t.resize(tIndex);
    return t;
}
