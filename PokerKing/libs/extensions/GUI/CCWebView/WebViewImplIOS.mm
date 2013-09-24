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

#import "WebViewImplIOS.h"
#import "EAGLView.h"
#import "CCWebViewImplIOS.h"

#define getWebViewImplIOS() ((cocos2d::extension::CCWebViewImplIOS*)webView_)

@implementation CustomUIWebView
@end


@implementation WebViewImplIOS

@synthesize webView = webView_;

- (void)dealloc
{
    [webView_ resignFirstResponder];
    [webView_ removeFromSuperview];
    NSLog(@"Webview has been removed! - dealloc");
    
    [webView_ release];
    [super dealloc];
}

-(id) initWithFrame: (CGRect) frameRect
{
    self = [super init];

    do 
    {
        if (self == nil) break;
        webView_ = [[CustomUIWebView alloc] initWithFrame: frameRect];
        if (!webView_) break;
        
        [[EAGLView sharedEGLView] addSubview:webView_];
        
        return self;
    }while(0);
    
    [webView_ release];

    
    return nil;
}

-(void) loadURL:(NSURL *)url
{
    NSLog(@"%@", [url absoluteString]);
    
    NSURLRequest *request =[NSURLRequest requestWithURL:url];
    [webView_ loadRequest:request];
}

-(void) setPosition:(CGPoint) pos
{
    CGRect frame = [webView_ frame];
    frame.origin = pos;
    [webView_ setFrame:frame];
}

-(void) setContentSize:(CGSize) size
{
    
}

-(void) visit
{
    [webView_ becomeFirstResponder];
}

-(void) removeWebView
{
    [webView_ setHidden:YES];
    [webView_ resignFirstResponder];
    [webView_ removeFromSuperview];
    NSLog(@"Webview has been removed! - removeWebView");
}

@end
