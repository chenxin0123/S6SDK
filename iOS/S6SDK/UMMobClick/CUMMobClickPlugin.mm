//
//  S6UMMobClick.m
//  S6SDK
//
//  Created by pp on 2017/8/22.
//  Copyright © 2017年 pp. All rights reserved.
//

#import "CUMMobClickPlugin.h"
#import "S6SDKDefine.h"
#import <UMMobClick/MobClick.h>
#import <UMMobClick/MobClickGameAnalytics.h>
#import <UMMobClick/MobClickSocialAnalytics.h>
#import "iOSMacro.h"
#import "S6Utils.h"
S6NAMESPACE_BEGIN
const char * CUMMobClickPlugin::getName() {
    return S6_PLUGIN_UMMobClick;
}

const char * CUMMobClickPlugin::getVersion() {
    return S6SDKVersion;
}

void CUMMobClickPlugin::setLogEnabled(bool flag) {
    [MobClick setLogEnabled:flag?YES:NO];
}

void CUMMobClickPlugin::setCrashReportEnabled(bool flag) {
    [MobClick setCrashReportEnabled:flag?YES:NO];
}
void CUMMobClickPlugin::setAppVersion(const char *appVersion) {
    [MobClick setAppVersion:S6Char2NSString(appVersion)];
}

void CUMMobClickPlugin::event(const char * key, const char *attributes) {
    NSDictionary *info = [S6Utils dictFromChar:attributes];
    NSString *sKey = S6Char2NSString(key);
    if (sKey && info) {
        [MobClick event:sKey attributes:info];
    } else if (sKey) {
        [MobClick event:sKey];
    }
}

void CUMMobClickPlugin::setUserLevel(int level) {
    
}

void CUMMobClickPlugin::pay(double cash, int source, int coins) {
    
}

void CUMMobClickPlugin::beginPayment(const char * usreId, const char * orderId, const char *desc, double amount) {
    
}

void CUMMobClickPlugin::finishPayment(const char * usreId, const char * orderId, const char *desc, double amount) {
    
}

void CUMMobClickPlugin::profileSignIn(const char * userId) {
    
}

void CUMMobClickPlugin::profileSignOff() {
    
}

void CUMMobClickPlugin::login(const char *extraData) {
    
}

void CUMMobClickPlugin::registerAccount(const char *extraData) {
    
}

void CUMMobClickPlugin::createRole(const char *roleId) {
    
}
S6NAMESPACE_END
