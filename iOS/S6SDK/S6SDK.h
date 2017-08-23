//
//  S6SDK.h
//  S6SDK
//
//  Created by pp on 2017/8/22.
//  Copyright © 2017年 pp. All rights reserved.
//
//#if defined __ANDROID__ || defined __APPLE__
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

//! Project version number for S6SDK.
FOUNDATION_EXPORT double S6SDKVersionNumber;

//! Project version string for S6SDK.
FOUNDATION_EXPORT const unsigned char S6SDKVersionString[];

#import <S6SDK/S6AppDelegate.h>

#import <S6SDK/S6SDKDefine.h>
#import <S6SDK/IS6SDK.h>
#import <S6SDK/IPlugin.h>

#import <S6SDK/IUMMobClickPlugin.h>



///-----------------------------------------------
/// Dolphin 更新 保留当前大部分逻辑 包括弹窗
///-----------------------------------------------
class IS6UpdatePlugin;
class IS6DolphinPlugin;
@interface IS6UpdateiOS : NSObject
+ (instancetype)sharedInstance;
// 以下两个方法按顺序调用
- (void)setUpdatePlugin:(IS6UpdatePlugin *)plugin;
// 提供一个父控制器来显示更新界面并开始更新 内部自动调用IS6UpdatePlugin::start()方法
- (void)startWithViewController:(UIViewController *)parentVc;
@end


S6NAMESPACE_BEGIN

class IS6UpdateCallback : public IPlugin {
public:
    // 这里写自己的更新业务 比如请求接口判断是否走gcloud
    // 返回0结束更新 返回1首包解压 返回2检查app更新
    virtual int onWillStartUpdate() = 0;
    virtual void onFinishUpdate() = 0;
    virtual void onFirstExtractSuccess();
    virtual void onError(int stage, int errorCode);
    virtual void onVersionInfo(bool isAppUpdating,
                               bool isNeedUpdating,
                               bool isForcedUpdating,
                               const char *versionNumber,
                               double downloadSize,
                               const char *versionDescrition,
                               const char *userDefine);
};

class IS6UpdatePlugin : public IPlugin {
public:
    // 设置更新界面的背景图
    virtual void setBackgroundImageName(const char *imageName) = 0;
    virtual void setUpdateProgressBarImageName(const char *imageName) = 0;
    virtual void start() = 0;
    // virtual bool isFirstExtractNeed() = 0;
    // virtual void checkFirstExtract() = 0;
    // virtual void checkVersionWithAppStore() = 0;
    
};

class IS6DolphinPlugin : public IS6UpdatePlugin {
public:
    // 可选 可以不调用
    virtual void setCallback(IS6UpdateCallback *callback) = 0;
    
    virtual void setFirstExtractSoucrePath(const char *path) = 0;
    virtual void setFirstExtractDestPath(const char *path) = 0;
    // 更新环境地址，对应渠道页面下的正式环境地址或预发布环境地址
    virtual void setChannelId(int channelId) = 0;
    virtual void setUpdateUrl(const char *path) = 0;
    //virtual void start(bool needFirstExtract, bool isAppUpdate) = 0;
};

///-----------------------------------------------
/// 热云
///-----------------------------------------------
class IS6TrackingIOPlugin : public IPlugin {
public:
    // 自定义事件
    virtual void event(const char * key, const char *attributes = NULL) = 0;
    // 是否在控制台打印log
    virtual void setPrintLog(bool flag) = 0;
    // 注册
    virtual void setRegisterWithAccountId(const char * accountId) = 0;
    // 登录
    virtual void setLoginWithAccountId(const char *accountId) = 0;
    /***
     * 支付统计 创建订单后调用
     * transactionId 支付订单号
     * ryzfType 支付类型 如:"app Store"
     * currencyType 货币类型 如:"CNY"
     * amount 金额 单位:元
     */
    virtual void beginPayment(const char * transactionId, const char * ryzfType, const char *currencyType, double amount) = 0;
    // 支付统计 订单支付完成后调用
    virtual void finishPayment(const char * transactionId, const char * ryzfType, const char *currencyType, double amount) = 0;
};

///-----------------------------------------------
/// Bugly
///-----------------------------------------------
class IS6BuglyPlugin : public IPlugin {
public:
    // 设置用户标识
    virtual void setUserIdentifier(const char *accountId) = 0;
    // 设置关键数据，随崩溃信息上报
    virtual void setUserKeyValue(const char *key, const char *value) = 0;
    // 设置标签 可在网站生成
    virtual void setTag(const char *tagName) = 0;
    /***
     * 上报自定义的异常
     * name 名称
     * reason 原因
     * callstack 堆栈
     */
    virtual void reportLuaException(const char *name, const char *reason, const char *callstack) = 0;
};

///-----------------------------------------------
/// CrashEye
///-----------------------------------------------
class IS6CrashEyePlugin : public IPlugin {
public:
    // 设置用户标识
    virtual void setUserIdentifier(const char *accountId) = 0;
    // 设置关键数据，随崩溃信息上报 userinfo: json字符串
    virtual void setUserInfo(const char *userinfo) = 0;
    // 设置标签 可在网站生成
    virtual void setTag(const char *tagName) = 0;
    /***
     * 上报自定义的异常
     * name 名称
     * reason 原因
     * callstack 堆栈
     */
    virtual void reportLuaException(const char *name, const char *reason, const char *callstack) = 0;
    // 获取设备crashEye的设备Id
    virtual const char * getDeviceId() = 0;
    // 上一次启动是否有崩溃 如果有可以进行上传日志等操作
    virtual bool hasCrashLastLaunch() = 0;
};

///-----------------------------------------------
/// ShareSDK 分享
///-----------------------------------------------

class IS6ShareSDKCallback {
    virtual void onShareReturn(int shareResult) = 0;
};

class IS6ShareSDKPlugin : public IPlugin {
public:
    virtual void setCallback(IS6ShareSDKCallback *Callback) = 0;
    /**
     * platType 1微信好友 2微信朋友圈 3QQ好友 4QQ空间
     * shareType 0图片 1自动根据传入的参判断类型
     * title 标题
     * content 分享的文本
     * url 网页路径
     * imgUrl 图片地址
     */
    virtual void share(int platType,
                       int shareType,
                       const char * title,
                       const char * content,
                       const char * url,
                       const char * imgUrl) = 0;
};


///-----------------------------------------------
/// 个推 推送
///-----------------------------------------------
class IS6GeTuiPlugin : public IPlugin {
public:
    virtual void setChannelId(const char *channelId) = 0;
    virtual void bindAlias(const char *alias) = 0;
    virtual void unbindAlias(const char *alias) = 0;
};

///-----------------------------------------------
/// 新游手柄
///-----------------------------------------------
class IS6GamePadCallback {
    enum GamepadEvent
    {
        CONNECTED_EVENT,
        DISCONNECTED_EVENT,
        PRESS_EVENT,
        RELEASE_EVENT,
        MOTION_EVENT
    };
    
    enum ButtonMapping
    {
        THUMBSTICK_LEFT_X = 1000,
        THUMBSTICK_LEFT_Y,
        THUMBSTICK_RIGHT_X,
        THUMBSTICK_RIGHT_Y,
        BUTTON_A,
        BUTTON_B,
        BUTTON_C,
        BUTTON_X,
        BUTTON_Y,
        BUTTON_Z,
        BUTTON_DPAD_UP,
        BUTTON_DPAD_DOWN,
        BUTTON_DPAD_LEFT,
        BUTTON_DPAD_RIGHT,
        BUTTON_DPAD_CENTER,
        BUTTON_LEFT_SHOULDER,
        BUTTON_RIGHT_SHOULDER,
        BUTTON_LEFT_TRIGGER,
        BUTTON_RIGHT_TRIGGER,
        BUTTON_LEFT_THUMBSTICK,
        BUTTON_RIGHT_THUMBSTICK,
        BUTTON_START,
        BUTTON_SELECT,
        BUTTON_BACK,
        BUTTON_HELP
    };
    virtual void gamepadEvent(GamepadEvent evt, int controller) = 0;
    virtual void gamepadButtonEvent(GamepadEvent evt, int controller, ButtonMapping button) = 0;
    virtual void gamepadMotionEvent(GamepadEvent evt, int controller, ButtonMapping axisID, float xvalue, float yvalue) = 0;
};

class IS6XinYouGamePadPlugin : public IPlugin {
public:
    virtual void setCallback(IS6GamePadCallback *Callback) = 0;
    /**
     *  设置手柄震动强度, 0为关闭震动
     *  @param leftMotorSpeed  左马达转速，0.0f~1.0f
     *  @param rightMoterSpeed 右马达转速, 0.0f~1.0f
     */
    virtual void vibrate(float leftMotorSpeed, float rightMoterSpeed) = 0;
    // 停止震动
    virtual void stopVibrating() = 0;
};

///-----------------------------------------------
/// GcloudVoice
///-----------------------------------------------
class IS6GcloudVoiceCallback {
public:
    /**
     * Callback when JoinXxxRoom successful or failed.
     *
     * @param code : a GCloudVoiceCompleteCode code . You should check this first.
     * @param roomName : name of your joining, should be 0-9A-Za-Z._- and less than 127 bytes
     * @param memberID : if success, return the memberID
     */
    virtual void OnJoinRoom(int code, const char *roomName, int memberID) = 0;
    /**
     * Callback when QuitRoom successful or failed.
     *
     * @param code : a GCloudVoiceCompleteCode code . You should check this first.
     * @param roomName : name of your joining, should be 0-9A-Za-Z._- and less than 127 bytes
     */
    virtual void OnQuitRoom(int code, const char *roomName) = 0;
    /**
     * Callback when someone saied or silence in the same room.
     *
     * @param count count of members who's status has changed.
     * @param members a int array composed of [memberid_0, status,memberid_1, status ... memberid_2*count, status]
     * here, status could be 0, 1, 2. 0 meets silence and 1/2 means saying
     */
    virtual void OnMemberVoice(const unsigned int *members, int count) = 0;
    /**
     * Callback when upload voice file successful or failed.
     *
     * @param code a GCloudVoiceCompleteCode code . You should check this first.
     * @param filePath file to upload
     * @param fileID if success ,get back the id for the file.
     */
    virtual void OnUploadFile(int code, const char *filePath, const char *fileID) = 0;
    /**
     * Callback when download voice file successful or failed.
     *
     * @param code a GCloudVoiceCompleteCode code . You should check this first.
     * @param filePath file to download to .
     * @param fileID if success ,get back the id for the file.
     */
    virtual void OnDownloadFile(int code, const char *filePath, const char *fileID) = 0;
    /**
     * Callback when finish a voice file play end.
     *
     * @param code a GCloudVoiceCompleteCode code . You should check this first.
     * @param filePath file had been plaied.
     */
    virtual void OnPlayRecordedFile(int code,const char *filePath) = 0;
    /**
     * Callback when query message key successful or failed.
     *
     * @param code a GCloudVoiceCompleteCode code . You should check this first.
     */
    virtual void OnApplyMessageKey(int code) = 0;
    /**
     * Callback when translate voice to text successful or failed.
     *
     * @param code a GCloudVoiceCompleteCode code . You should check this first.
     * @param fileID : file to translate
     * @param result : the destination text of the destination language.
     */
    virtual void OnSpeechToText(int code, const char *fileID, const char *result) = 0;
};

class IS6GcloudVoicePlugin : public IPlugin {
public:
    virtual bool setCallback(IS6GcloudVoiceCallback * cb) = 0;
    // @param openID : player's openID from QQ or Wechat. or a unit role ID.
    virtual bool setOpenId(const char * openId) = 0;
    /**
     * Join in team room.
     *
     * @param roomName the room to join, should be less than 127byte, composed by alpha.
     * @param msTimeout time for join, it is micro second. value range[5000, 60000]
     * @return : if success return GCLOUD_VOICE_SUCC, failed return other errno @see GCloudVoiceErrno
     */
    virtual bool JoinRoom(const char *roomName, int msTimeout = 10000) = 0;
    /**
     * Quit the voice room.
     *
     * @param roomName the room to join, should be less than 127byte, composed by alpha.
     * @param msTimeout time for quit, it is micro second.value range[5000, 60000]
     * @return : if success return GCLOUD_VOICE_SUCC, failed return other errno @see GCloudVoiceErrno
     */
    virtual bool QuitRoom(const char * roomName,int msTimeout) = 0;
    /**
     * Trigger engine's Callback.
     *
     * You should invoke poll on your loop. such as onUpdate() in cocos2dx
     */
    virtual void Process() = 0;
    /**
     * The Application's Pause.
     *
     * When your app pause such as goto backend you should invoke this
     * @return : if success return GCLOUD_VOICE_SUCC, failed return other errno @see GCloudVoiceErrno
     */
    virtual bool Pause() = 0;
    /**
     * The Application's Resume.
     *
     * When your app reuse such as come back from  backend you should invoke this
     * @return : if success return GCLOUD_VOICE_SUCC, failed return other errno @see GCloudVoiceErrno
     */
    virtual bool Resume() = 0;
    /**
     * Open player's micro phone  and begin to send player's voice data.
     *
     * @return : if success return GCLOUD_VOICE_SUCC, failed return other errno @see GCloudVoiceErrno
     * @see : GCloudVoiceErrno
     */
    virtual bool OpenMic() = 0;
    /**
     * Close players's micro phone and stop to send player's voice data.
     *
     * @return : if success return GCLOUD_VOICE_SUCC, failed return other errno @see GCloudVoiceErrno
     * @see : GCloudVoiceErrno
     */
    virtual bool CloseMic() = 0;
    /**
     * Open player's speaker and begin recvie voice data from the net .
     *
     * @return : if success return GCLOUD_VOICE_SUCC, failed return other errno @see GCloudVoiceErrno
     * @see : GCloudVoiceErrno
     */
    virtual bool OpenSpeaker() = 0;
    /**
     * Close player's speaker and stop to recive voice data from the net.
     *
     * @return : if success return GCLOUD_VOICE_SUCC, failed return other errno @see GCloudVoiceErrno
     * @see : GCloudVoiceErrno
     */
    virtual bool CloseSpeaker() = 0;
};

///-----------------------------------------------
/// 魔窗
///-----------------------------------------------
class IS6MagicWindowCallback {
    // 搜到深度链接的用户信息后会调用
    virtual void onGetMWUserData(const char *json) = 0;
};

class IS6MagicWindowPlugin : public IPlugin {
public:
    virtual bool setCallback(IS6MagicWindowCallback * cb) = 0;
    /**
     * 获取深度链接的json字符串
     */
    virtual const char * getUserData() = 0;
    virtual const char * deleteUserData() = 0;
    // http://www.magicwindow.cn/doc/mlink-js-api.html u_id是唯一支持的options.tparams
    virtual const char * getUid() = 0;
    virtual const char * deleteUid() = 0;
};

///-----------------------------------------------
/// 高德
///-----------------------------------------------
class IS6MapCallback {
    virtual void onLocation(double longitude, double latitude) = 0;
    virtual void onSearchLocationWithKeyword(const char * json, const char * userinfo) = 0;
    virtual void onSearchPoiWithPoiId(const char * json, const char * userinfo) = 0;
};
class IS6AMapPlugin : public IPlugin {
public:
    virtual bool setCallback(IS6MapCallback * cb) = 0;
    // 获取当前位置
    virtual void startLocationOnce() = 0;
    /**
     * keywork 关键字
     * 当前页数 [1-100]
     * pagesize 每页记录数[1-50]
     * 搜索半径 单位:米
     */
    virtual void searchLocationDetail(const char *keywork, int page, int pagesize, int radius) = 0;
    virtual void searchPoi(const char *poiId) = 0;
};

///-----------------------------------------------
/// 网宿定向流量
///-----------------------------------------------
class IS6WSPXPlugin : public IPlugin {
public:
    // 当前免流状态
    virtual int getWspxStatus() = 0;
    // 网页订购
    virtual void wspxStatus() = 0;
    // SDK定时查询流量，超过预警值 or 已经消耗完之后的回调
    virtual const char * wsRealtimeTrafficAlert() = 0;
    // 实时流量接口回调 返回json字符串
    virtual const char * wsQueryRealTimeTraffic() = 0;
};

///-----------------------------------------------
/// 触手TV
///-----------------------------------------------
class IS6ChuShouPlugin : public IPlugin {
public:
    // 打开直播页面
    virtual void openTv(const char* url) = 0;
    virtual void submitTvInfo(const char* accountId, const char* token) = 0;
};


// ??? 这块不熟悉 也比较乱
///-----------------------------------------------
/// NDSDK
///-----------------------------------------------
class IS6NDSDKCallback {
    virtual void onNDLogin() = 0;
    virtual void onNDLeavePlatform() = 0;
    virtual void onNDUserPortraitDidChange() = 0;
    virtual void onNDUserInfoDidChange() = 0;
    
    virtual void onGetUserInfo(int errorCode, const char *json) = 0;
};

class IS6NDSDKPlugin : public IPlugin {
public:
    virtual void setCallback(IS6NDSDKCallback *callback) = 0;
    virtual void login() = 0;
    virtual void login(int type) = 0;
    virtual void switchLogin() = 0;
    virtual void logout() = 0;
    virtual void logout(int type) = 0;
    virtual void realNameBinderState() = 0;
    virtual int realNameBinder() = 0;
    // flag 获取标识，按位组合（0:无效；1:基本信息；2:积分；4:心情;7: 所有
    // uin 要获取的对象uin
    virtual void getUserInfo(int flag, const char * uin) = 0;
};

///-----------------------------------------------
/// 录屏
///-----------------------------------------------
class IS6ReplaykitCallback {
    // 录屏状态回调
    virtual void  onScreenRecord(int sig, const char* msg) = 0;
    
};

class IS6ReplaykitPlugin : public IPlugin {
public:
    virtual void setCallback(IS6ReplaykitCallback *callback) = 0;
    virtual bool isSupportReplaykit() = 0;
    virtual bool isRecording() = 0;
    virtual void startScreenRecord(bool useMicroPhone) = 0;
    virtual void stopScreenRecord() = 0;
    // 抛弃已录的
    virtual void startLive() = 0;
    virtual void stopLive() = 0;
    virtual void pauseLive() = 0;
    virtual void resumeLive() = 0;
    virtual void isLiving() = 0;
    virtual void isPause() = 0;
    virtual void showLive(float x, float y) = 0;
    virtual void hideLive() = 0;
};

///-----------------------------------------------
/// 内购
///-----------------------------------------------
class IS6InAppPurchaseCallback {
    // 录屏状态回调
    virtual void onFinishReportToServer(const char* orderId,
                                   int productId,
                                   const char* productDesc,
                                   int price,
                                   int buyNum,
                                   int coinNum,
                                   const char* roleId,
                                   const char* roleName,
                                   int roleLev,
                                   const char* extension) = 0;
    
};

class IS6InAppPurchasePlugin : public IPlugin {
public:
    virtual void setCallback(IS6InAppPurchaseCallback *callback) = 0;
    virtual void pay(const char* orderId,
                     int productId,
                     const char* productDesc,
                     int price,
                     int buyNum,
                     int coinNum,
                     const char* roleId,
                     const char* roleName,
                     int roleLev,
                     const char* extension) = 0;
    // 支付完成后上报的url
    virtual void setPayReportURL(const char * url) = 0;
};

///-----------------------------------------------
/// 二维码
///-----------------------------------------------
class IS6QRCodePlugin : public IPlugin {
public:
    virtual const char * generalQRCode(const char *nickName, const char *headImgPath, const char* qrPicName = "") = 0;
    // 弹出扫描二维码界面
    virtual void captureQrCode(int captureType) = 0;
};

///-----------------------------------------------
/// 设备相关
///-----------------------------------------------
class IS6DeviceCallback {
    // 电池电量变化
    virtual void onBatteryLevelChange(int level) = 0;
    // 录屏状态回调
    virtual void onScreenRecord(int sig, const char* msg) = 0;

    virtual void onShake() = 0;
    virtual void onMotionUpdate(double roll, double pitch, double yaw) = 0;
    virtual void onChangeVolume(int volume) = 0;
    
};

class IS6DevicePlugin : public IPlugin {
public:
    virtual void setCallback(IS6DeviceCallback *callback) = 0;
    ///-----------------------------------------------
    /// 电池
    ///-----------------------------------------------
    // 监听电池电量
    virtual void startMonitorBattery() = 0;
    virtual void stopMonitorBattery() = 0;
    // 0 UIDeviceBatteryStateUnknown 1 on battery, discharging 2 plugged in, less than 100% 3 plugged in, at 100%
    virtual void getBatteryState() = 0;
    // 摇一摇
    virtual void startShake() = 0;
    virtual void stopShake() = 0;
    // 陀螺仪
    virtual void startMotionSensor() = 0;
    virtual void stopMotionSensor() = 0;

    // 外网IP
    virtual const char * getLocalIpAddress() = 0;
    // 局域网IP
    virtual const char * getLocalHostIp() = 0;
    // mac地址 iOS平台返回空字符串
    virtual const char * getLocalMacAddress() = 0;
    // 全部内存
    virtual float getMemorySize() = 0;
    // 剩余可用内存
    virtual float getAvailMemorySize() = 0;
    // 震动
    virtual void vibrate() = 0;
    
    virtual int getDeviceVolume() = 0;
    virtual int getEffectLevel() = 0;
    
    // 是否越狱/root
    virtual bool is_root() = 0;
    // 系统版本
    virtual const char * systemVersion() = 0;
    
    // 例: "iPhone5,3"
    virtual const char * machineModel() = 0;
    // 例: "iPhone 5c"
    virtual const char * machineModelName() = 0;
    
};

///-----------------------------------------------
/// 设备相关
///-----------------------------------------------
class IS6UtilityCallback {
    virtual void onTakeClipPhoto(const char* path) = 0;
    virtual void onSavePhotosAlbumEvent(int sig, const char* msg) = 0;
};

class IS6UtilityPlugin : public IPlugin {
public:
    virtual void setCallback(IS6UtilityCallback *callback) = 0;
    virtual void addImageToAlbum(const char* imgPath) = 0;
    // 获取并裁剪图片
    virtual void takeClipPhoto(int takeType, const char* clipName) = 0;
    virtual void clipboard(const char * pStr) = 0;
    virtual const char* paste() = 0;
    virtual void checkPermission(const int type) = 0;
    
    virtual void exitGame() = 0;
    virtual const char* getAppVersionName() = 0;
    virtual const char* getResVersionName() = 0;
    virtual double getDistance(double lat1, double lng1, double lat2, double lng2) = 0;
    // 设置appStore的appid
    virtual void setAppId(const char *appId);
    // 以下两个方法调用前需先调用setAppId
    virtual void jumpToCommentApp() = 0;
    virtual void jumpToAppStore() = 0;
    // iOS上返回doucument目录
    virtual const char * getWorkDir();
    // iOS上返回doucument下cache目录
    virtual const char * getCacheDir();
};

///-----------------------------------------------
/// 日志
///-----------------------------------------------
class IS6LogCallback {
    enum LOG_TYPE
    {
        LOG_ERR,
        LOG_WARN,
        LOG_DEBUG,
        LOG_INFO,
    };
    virtual void onLog(LOG_TYPE type,const char* log) = 0;
};

class IS6LogPlugin : public IPlugin {
public:
    // 其他的SDK打印的日志在调用本方法前都会保存在队列内 这样日志不至于丢失
    virtual void setCallback(IS6LogCallback *callback) = 0;
};


S6NAMESPACE_END
