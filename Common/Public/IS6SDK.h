//
//  IS6SDK.h
//  S6SDK
//
//  Created by pp on 2017/8/29.
//  Copyright © 2017年 pp. All rights reserved.
//

#ifndef IS6SDK_h
#define IS6SDK_h

#include "S6SDKDefine.h"
#include "IPlugin.h"
#include "IUMMobClickPlugin.h"

S6NAMESPACE_BEGIN

void initializeSDK(const char * cfg);

IUMMobClickPlugin *UMMobClickPlugin();

//
////
////class IS6SDK
////{
////public:
////    
////    
////    virtual void init() = 0;
////    virtual void uninit() = 0;
////    
////    // 启动时验证是否有网络 有的话调用这个方法
////    virtual void onFirstConnectedNetwork() = 0;
////    // 初始化游戏 OpenGL Context等结束调用
////    virtual void onCreateGame() = 0;
////    // 设置网页样式 预留
////    virtual void setWebViewStyle(int style) = 0;
////};

S6NAMESPACE_END

#endif /* IS6SDK_h */
