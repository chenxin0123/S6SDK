//
//  S6SDK.cpp
//  S6SDK
//
//  Created by pp on 2017/8/29.
//  Copyright © 2017年 pp. All rights reserved.
//

#include "IS6SDK.h"
#include "CUMMobClickPlugin.h"

S6NAMESPACE_BEGIN

static IUMMobClickPlugin * s_IS6UMMobClickPlugin = NULL;

void initializeSDK(const char * cfg) {
    s_IS6UMMobClickPlugin = new CUMMobClickPlugin();
}

IUMMobClickPlugin * UMMobClickPlugin() {
    return s_IS6UMMobClickPlugin;
}

S6NAMESPACE_END

