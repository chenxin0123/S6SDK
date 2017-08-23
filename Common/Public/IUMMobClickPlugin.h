//
//  IS6UMMobClickPlugin.h
//  S6SDK
//
//  Created by pp on 2017/8/22.
//  Copyright © 2017年 pp. All rights reserved.
//

#ifndef IS6UMMobClickPlugin_h
#define IS6UMMobClickPlugin_h

#include "IPlugin.h"
S6NAMESPACE_BEGIN
///-----------------------------------------------
/// 友盟
///-----------------------------------------------
class IUMMobClickPlugin : public IPlugin {
public:
    /**
     * appKey 初始化appKey
     * channelId iOS默认App Store
     * seType 0普通统计 1游戏统计
     **/
    //virtual void init(const char *appKey, const char * channelId = NULL, int seType = 1) = 0;
    
    // 是否在控制台打印log
    virtual void setLogEnabled(bool flag) = 0;
    // 是否进行崩溃统计
    virtual void setCrashReportEnabled(bool flag) = 0;
    // 设置app版本
    virtual void setAppVersion(const char *appVersion) = 0;
    // 自定义事件
    virtual void event(const char * key, const char *attributes = NULL) = 0;
    // 设置玩家等级
    virtual void setUserLevel(int level) = 0;
    
    /** 玩家支付货币兑换虚拟币.
     * cash 真实货币数量
     * source 支付渠道
     * coin 虚拟币数量
     */
    virtual void pay(double cash, int source, int coins) = 0;
    
    // 支付统计 创建订单后调用amount 单位:元
    virtual void beginPayment(const char * usreId, const char * orderId, const char *desc, double amount) = 0;
    // 支付统计 订单支付完成后调用amount 单位:元
    virtual void finishPayment(const char * usreId, const char * orderId, const char *desc, double amount) = 0;
    
    // 统计用户登录时间 登录时调用
    virtual void profileSignIn(const char * userId) = 0;
    // 统计用户登录时间 登出时调用
    virtual void profileSignOff() = 0;
    
    // 登录事件
    virtual void login(const char *extraData) = 0;
    // 注册账号事件
    virtual void registerAccount(const char *extraData) = 0;
    // 创建角色
    virtual void createRole(const char *roleId) = 0;
};
S6NAMESPACE_END


#endif /* IS6UMMobClickPlugin_h */
