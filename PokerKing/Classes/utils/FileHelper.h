//
//  FileHelper.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-12.
//
//

#ifndef __PokerKing__FileHelper__
#define __PokerKing__FileHelper__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

/** 负责操作文件储存和读取
 */

class FileHelper {
public:
    /** 读取本地文件，返回数据 */
    static string getFileByName(string pFileName);
    static CCTexture2D* getImageFileByName(string pFileName);
    
    /** 储存内容到文件 */
    static bool saveFile(char* pContent,string pFileName);
    
};


#endif /* defined(__PokerKing__FileHelper__) */
