//
//  GameServer.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 12-11-18.
//
//

#include "GameServer.h"

#include "cocos-ext.h"
#include "JSONValueUtil.h"
#include "Helpers.h"


USING_NS_CC_EXT;


//static GameServer * pGameServer = NULL;

GameServer* GameServer::sharedGameServer(void)
{

    GameServer * pGameServer = new GameServer();
    if(pGameServer && pGameServer->init())
    {
    }

    
    return pGameServer;
}

GameServer::GameServer()
{
}

GameServer::~GameServer()
{

}

bool GameServer::init()
{
    SaveStringToXML("hasCallInProgress", "false");
    return true;
}

bool GameServer::doGameServerAction(CCObject *target, SEL_CallFuncO callback, std::string action, std::string postValue)
{
    std::string hasCallInProgress = "";
    hasCallInProgress = LoadStringFromXML("hasCallInProgress");

    while (strcmp(hasCallInProgress.c_str(), "true") == 0) {
        [NSThread sleepForTimeInterval:1];
        CCLOG("Sleep...");
        hasCallInProgress = LoadStringFromXML("hasCallInProgress");
    }
    
    SaveStringToXML("hasCallInProgress", "true");
    
    GameInfo * gameinfo = GameInfo::sharedGameInfo();
    if ((gameinfo->getGameServerUrl()=="" && gameinfo->getLoginServerUrl() == "")
    || action.length() < 1) {
        return false;
    }
    
    mCallBackTarget = target;
    mCallbackFuncO = callback;

    
    
    CCString *url = NULL;
    CCString * postData = NULL;
    
    if(action == Act_login)
    {
        url = CCString::createWithFormat("%s%s", gameinfo->getLoginServerUrl().c_str(),action.c_str());
        postData = CCString::createWithFormat("%s",postValue.c_str());
    }
    else
    {
        url = CCString::createWithFormat("%s%s", gameinfo->getGameServerUrl().c_str(),action.c_str());
//        url = CCString::createWithFormat("%s%s?authToken=%s&account=%d", gameinfo->getGameServerUrl().c_str(),action.c_str(),gameinfo->getToken().c_str(),UserInfo::sharedUserInfo()->getUserID());
        postData = CCString::createWithFormat("authToken=%s&account=%d&%s",gameinfo->getToken().c_str(),UserInfo::sharedUserInfo()->getUserID(),postValue.c_str());
    }
    
    
    CCLOG("url=%s", url->getCString());

    CCLOG("postData=%s", postData->getCString());
    
    std::string encryptedPost = CCString::createWithFormat("postdata=%s", Helpers::encryptBaseString(postData->m_sString).c_str())->m_sString;
    
    CCLOG("encryptedPost=%s", encryptedPost.c_str());
    
    try {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl(url->getCString());
        
        request->setRequestType(CCHttpRequest::kHttpPost);
        request->setRequestData(encryptedPost.c_str(), encryptedPost.length());
        request->setResponseCallback(this, callfuncND_selector(GameServer::doGameServerAction_Done));

        
        CCHttpClient::getInstance()->send(request);
        request->release();
    }
    catch(...)
    {
        if (mCallBackTarget && mCallbackFuncO) {
                (mCallBackTarget->*mCallbackFuncO)(NULL);
            }
    }
    return true;
}

void GameServer::doGameServerAction_Done(cocos2d::CCNode *pSender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse *)data;
    CCLog("Response Code = %d", response->getResponseCode());
    
    GameServerResponse * gsResponse = GameServerResponse::create();
    
    gsResponse->setResponseCode(response->getResponseCode());
    
    gsResponse->setIsSuccess(response->isSucceed());
    
    if(response->isSucceed())
    {
        try {
        std::vector<char>* str = response->getResponseData();
        char * responseString = new char[str->size()];
        std::copy(str->begin(), str->end(), responseString);
        responseString[str->size()] =0;
        
        CCString * strData = CCString::createWithFormat("%s",responseString);
        gsResponse->setResponseContent(strData);
        CCLOG("response = %s", strData->getCString());

        std::string decryptedData = Helpers::decryptBaseString(strData->m_sString);
        
        CCLOG("decryptedData = %s", decryptedData.c_str());

          gsResponse->setResponseDictionary(JSONValueUtil::JSONValue(decryptedData.c_str()));
        } catch (...) {
          gsResponse->setIsSuccess(false);
        }
        
        if(!gsResponse->getResponseDictionary())
        {
            gsResponse->setIsSuccess(false);
        }
    }
    else {
        
        gsResponse->setServerError(CCString::create(response->getErrorBuffer()));
        CCLOG("Error = %s", response->getErrorBuffer());
    }
    
    
    
    if (mCallBackTarget && mCallbackFuncO) {
                (mCallBackTarget->*mCallbackFuncO)(gsResponse);
            }
    
    SaveStringToXML("hasCallInProgress", "false");
    
}
