//
//  FileHelper.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-12.
//
//

#include "FileHelper.h"


string FileHelper::getFileByName(string pFileName){
    //第一先获取文件的路径
    string path = CCFileUtils::sharedFileUtils()->getWriteablePath() + pFileName;
    CCLOG("path = %s",path.c_str());
    
    //创建一个文件指针
    FILE* file = fopen(path.c_str(), "r");
    
    if (file) {
        char* buf;  //要获取的字符串
        int len;    //获取的长度
        /*获取长度*/
        fseek(file, 0, SEEK_END);   //移到尾部
        len = ftell(file);          //提取长度
        rewind(file);               //回归原位
        CCLOG("count the file content len = %d",len);
        //分配buf空间
        buf = (char*)malloc(sizeof(char) * len + 1);
        if (!buf) {
            CCLOG("malloc space is not enough.");
            return NULL;
        }
        
        //读取文件
        //读取进的buf，单位大小，长度，文件指针
        int rLen = fread(buf, sizeof(char), len, file);
        buf[rLen] = '\0';
        CCLOG("has read Length = %d",rLen);
        CCLOG("has read content = %s",buf);
        
        string result = buf;
        fclose(file);
        free(buf);
        return result;
    }
    else
        CCLOG("open file error.");
    
    return NULL;
}

CCTexture2D* FileHelper::getImageFileByName(string pFileName){
 
    //第一先获取文件的路径
    string path = CCFileUtils::sharedFileUtils()->getWriteablePath() + pFileName;
    CCLOG("path = %s",path.c_str());
    
    //创建一个文件指针
    FILE* file = fopen(path.c_str(), "r");
    
    if (file) {
        char* buf;  //要获取的字符串
        int len;    //获取的长度
        /*获取长度*/
        fseek(file, 0, SEEK_END);   //移到尾部
        len = ftell(file);          //提取长度
        rewind(file);               //回归原位
        CCLOG("count the file content len = %d",len);
        //分配buf空间
        buf = (char*)malloc(sizeof(char) * len + 1);
        if (!buf) {
            CCLOG("malloc space is not enough.");
            return NULL;
        }
        
        //读取文件
        //读取进的buf，单位大小，长度，文件指针
        int rLen = fread(buf, sizeof(char), len, file);
        buf[rLen] = '\0';
        CCLOG("has read Length = %d",rLen);
        CCLOG("has read content = %s",buf);
        
        CCImage* img = new CCImage();
        img->initWithImageData((unsigned char*)buf, len);
        CCLog("img size = %d, %d", img->getWidth(), img->getHeight());
        CCTexture2D* texture2D = new CCTexture2D();
        texture2D->initWithImage(img);
        texture2D->retain();
        
        string result = buf;
        fclose(file);
        free(buf);
        return texture2D;
    }
    else
        CCLOG("open file error.");
    
    return NULL;
}

bool FileHelper::saveFile(char *pContent, string pFileName){
    //第一获取储存的文件路径
    string path = CCFileUtils::sharedFileUtils()->getWriteablePath() + pFileName;
    CCLOG("wanna save file path = %s",path.c_str());
    CCLOG("content: %s", pContent);
    //创建一个文件指针
    //路径、模式
    
    FILE* file = fopen(path.c_str(), "w");
    
    if (file) {
        fputs(pContent, file);
        fclose(file);
    }
    else
        CCLOG("save file error.");
    
    return false;
}