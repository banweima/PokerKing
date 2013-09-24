/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCWebView.h"
#include "CCWebViewImpl.h"

NS_CC_EXT_BEGIN

CCWebView::CCWebView(void)
: m_pWebViewImpl(NULL)
{
}

CCWebView::~CCWebView(void)
{
    CC_SAFE_DELETE(m_pWebViewImpl);
}

CCWebView* CCWebView::create(const CCSize& size)
{
    CCWebView* pRet = new CCWebView();
    
    if (pRet != NULL && pRet->initWithSize(size))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool CCWebView::initWithSize(const CCSize& size)
{
    m_pWebViewImpl = __createSystemWebView(this);
    m_pWebViewImpl->initWithSize(size);
    m_pWebViewImpl->setContentSize(size);
    this->setPosition(ccp(0, 0));
    
    return true;
}

void CCWebView::loadURL(CCString* pURL)
{
    if (pURL != NULL)
    {
        m_strURL = std::string(pURL->getCString());
        if (m_pWebViewImpl != NULL)
        {
            m_pWebViewImpl->loadURL(m_strURL);
        }
    }
}

/* override function */
void CCWebView::setPosition(const CCPoint& pos)
{
    CCControl::setPosition(pos);
    if (m_pWebViewImpl != NULL)
    {
        m_pWebViewImpl->setPosition(pos);
    }
}

void CCWebView::setContentSize(const CCSize& size)
{
    CCControl::setContentSize(size);
    if (m_pWebViewImpl != NULL)
    {
        m_pWebViewImpl->setContentSize(size);
    }
}

void CCWebView::visit(void)
{
    CCControl::visit();
    if (m_pWebViewImpl != NULL)
    {
        m_pWebViewImpl->visit();
    }
}

void CCWebView::onExit(void)
{
    CCControl::onExit();
    if (m_pWebViewImpl != NULL)
    {
        m_pWebViewImpl->removeWebView();
    }
}

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

NS_CC_EXT_END
