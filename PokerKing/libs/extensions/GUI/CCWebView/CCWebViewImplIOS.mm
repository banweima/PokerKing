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

#include "CCWebViewImplIOS.h"
#include "CCWebView.h"
#import "EAGLView.h"
#import "WebViewImplIOS.h"

NS_CC_EXT_BEGIN

CCWebViewImpl* __createSystemWebView(CCWebView* pWebView)
{
    return new CCWebViewImplIOS(pWebView);
}

#define GET_IMPL ((WebViewImplIOS*)m_pSysWebView)

CCWebViewImplIOS::CCWebViewImplIOS(CCWebView* pWebView)
: CCWebViewImpl(pWebView)
, m_pSysWebView(NULL)
{
    
}

CCWebViewImplIOS::~CCWebViewImplIOS()
{
    [GET_IMPL release];
}

bool CCWebViewImplIOS::initWithSize(const CCSize& size)
{
    do 
    {
        CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();

        CGRect rect;
        if (eglView->isRetinaEnabled())
        {
            rect = CGRectMake(0, 0, size.width,size.height);
        }
        else
        {
            rect = CGRectMake(0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY());
        }
        
        m_pSysWebView = [[WebViewImplIOS alloc] initWithFrame:rect];
        if (!m_pSysWebView) break;
        
        return true;
    }while (0);
    
    return false;
}

void CCWebViewImplIOS::loadURL(std::string url)
{
    NSURL *_url = [NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]];
//    UIImage *image = [UIImage imageWithData:[NSData dataWithContentsOfURL:imageUrl]];
//    GET_IMPL.imageView.image = image;
    
    [GET_IMPL loadURL:_url];
}

static CGPoint convertDesignCoordToScreenCoord(const CCPoint& designCoord)
{
    float viewH = (float)[[EAGLView sharedEGLView] getHeight];
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
    CCPoint visiblePos;
    if (eglView->isRetinaEnabled())
    {
        visiblePos = ccp(designCoord.x, designCoord.y);
    }
    else
    {
        visiblePos = ccp(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    }
    
    CCPoint screenGLPos = ccpAdd(visiblePos, eglView->getViewPortRect().origin);
    CGPoint screenPos = CGPointMake(screenGLPos.x, viewH - screenGLPos.y);
    return screenPos;
}

void CCWebViewImplIOS::setPosition(const CCPoint& pos)
{
    CCPoint ap = m_pWebView->getAnchorPoint();
    //TODO should consider anchor point, the default value is (0.5, 0,5)
    [GET_IMPL setPosition:convertDesignCoordToScreenCoord(ccp(pos.x-m_tContentSize.width/2, pos.y+m_tContentSize.height/2))];
    NSLog(@"pos = %f, %f", pos.x, pos.y);
    NSLog(@"contentSize = %f, %f", m_tContentSize.width, m_tContentSize.height);
    
//    [GET_IMPL setPosition:convertDesignCoordToScreenCoord(ccp(pos.x, pos.y))];
}

void CCWebViewImplIOS::setContentSize(const CCSize& size)
{
    m_tContentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
}

void CCWebViewImplIOS::visit(void)
{
    [GET_IMPL visit];
}

void CCWebViewImplIOS::removeWebView(void)
{
    [GET_IMPL removeWebView];
}

NS_CC_EXT_END

