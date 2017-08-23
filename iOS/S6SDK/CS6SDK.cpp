//
//  CS6SDK.cpp
//  S6SDK
//
//  Created by pp on 2017/8/29.
//  Copyright © 2017年 pp. All rights reserved.
//

#include "CS6SDK.h"
#include "CS6UMMobClickPlugin.h"

IS6Plugin * CS6SDK::queryPlugin(S6PluginName pulginName) {
    IS6Plugin *pPlugin = NULL;
    if (pulginName == S6_PLUGIN_UMMobClick) {
        pPlugin = new CS6UMMobClickPlugin();
    }
    return pPlugin;
}

void CS6SDK::init() {
    
}

void CS6SDK::uninit() {
    
}

void CS6SDK::onFirstConnectedNetwork() {
    
}

void CS6SDK::onCreateGame() {
    
}

void CS6SDK::setWebViewStyle(int style) {
    
}
