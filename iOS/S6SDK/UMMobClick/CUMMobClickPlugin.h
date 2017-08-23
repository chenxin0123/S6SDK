//
//  CS6UMMobClickPlugin.h
//  S6SDK
//
//  Created by pp on 2017/8/29.
//  Copyright © 2017年 pp. All rights reserved.
//

#ifndef CUMMobClickPlugin_h
#define CUMMobClickPlugin_h

#include "IUMMobClickPlugin.h"

S6NAMESPACE_BEGIN

class CUMMobClickPlugin : public IUMMobClickPlugin {
public:
    virtual const char * getName();
    virtual const char * getVersion();
    /**
     * appKey 初始化appKey
     * channelId iOS默认App Store
     * seType 0普通统计 1游戏统计
     **/
    //void init(const char *appKey, const char * channelId = NULL, int seType = 1);
    
    // 是否在控制台打印log
    void setLogEnabled(bool flag);
    // 是否进行崩溃统计
    void setCrashReportEnabled(bool flag);
    // 设置app版本
    void setAppVersion(const char *appVersion);
    // 自定义事件
    void event(const char * key, const char *attributes = NULL);
    // 设置玩家等级
    void setUserLevel(int level);
    
    /** 玩家支付货币兑换虚拟币.
     * cash 真实货币数量
     * source 支付渠道
     * coin 虚拟币数量
     */
    void pay(double cash, int source, int coins);
    
    // 支付统计 创建订单后调用amount 单位:元
    void beginPayment(const char * usreId, const char * orderId, const char *desc, double amount);
    // 支付统计 订单支付完成后调用amount 单位:元
    void finishPayment(const char * usreId, const char * orderId, const char *desc, double amount);
    
    // 统计用户登录时间 登录时调用
    void profileSignIn(const char * userId);
    // 统计用户登录时间 登出时调用
    void profileSignOff();
    
    // 登录事件
    void login(const char *extraData);
    // 注册账号事件
    void registerAccount(const char *extraData);
    // 创建角色
    void createRole(const char *roleId);
};

S6NAMESPACE_END

#endif /* CS6UMMobClickPlugin_h */
