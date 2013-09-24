//
//  CCBUtility.cpp
//  blackjack
//
//  Created by Banson Niu on 9/12/12.
//
//

#include "CCBUtility.h"

CCNode* CCBUtility::loadCCB(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader, CCObject *pOwner) {
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    //    ccNodeLoaderLibrary->registerCCNodeLoader("TestHeaderLayer", TestHeaderLayerLoader::loader());
    if(pCCNodeName != NULL && pCCNodeLoader != NULL) {
        ccNodeLoaderLibrary->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
    }
    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
   CCNode * node = ccbReader->readNodeGraphFromFile(pCCBFileName, pOwner);
    
    return node;
}