/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_daemon_msdkinterface_MSDKDelegate */

#ifndef _Included_com_daemon_msdkinterface_MSDKDelegate
#define _Included_com_daemon_msdkinterface_MSDKDelegate
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWeixin
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[BILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixin
  (JNIEnv *, jclass, jstring, jstring, jstring, jbyteArray, jint, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWeixinWithPhoto
 * Signature: (Lcom/tencent/msdk/api/eWechatScene;Ljava/lang/String;[BI)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithPhoto__Lcom_tencent_msdk_api_eWechatScene_2Ljava_lang_String_2_3BI
  (JNIEnv *, jclass, jobject, jstring, jbyteArray, jint);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWeixinWithPhoto
 * Signature: (Lcom/tencent/msdk/api/eWechatScene;Ljava/lang/String;[BILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithPhoto__Lcom_tencent_msdk_api_eWechatScene_2Ljava_lang_String_2_3BILjava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jclass, jobject, jstring, jbyteArray, jint, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWeixinWithMusic
 * Signature: (Lcom/tencent/msdk/api/eWechatScene;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[BILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithMusic
  (JNIEnv *, jclass, jobject, jstring, jstring, jstring, jstring, jstring, jbyteArray, jint, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToQQ
 * Signature: (Lcom/tencent/msdk/api/eQQScene;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQ
  (JNIEnv *, jclass, jobject, jstring, jstring, jstring, jstring, jint);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToQQWithPhoto
 * Signature: (Lcom/tencent/msdk/api/eQQScene;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQWithPhoto
  (JNIEnv *, jclass, jobject, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToQQWithMusic
 * Signature: (Lcom/tencent/msdk/api/eQQScene;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQWithMusic
  (JNIEnv *, jclass, jobject, jstring, jstring, jstring, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGLogin
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGLogin
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSwitchUser
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSwitchUser
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGLogout
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGLogout
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetLoginRecord
 * Signature: (Lcom/tencent/msdk/api/LoginRet;)I
 */
JNIEXPORT jint JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetLoginRecord
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGFeedBack
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGFeedBack__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGFeedBack
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGFeedBack__Ljava_lang_String_2
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    throwExp
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_throwExp
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    setObserver
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_setObserver
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGEnableCrashReport
 * Signature: (ZZ)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGEnableCrashReport
  (JNIEnv *, jclass, jboolean, jboolean);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGReportEvent
 * Signature: (Ljava/lang/String;Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGReportEvent__Ljava_lang_String_2Ljava_lang_String_2Z
  (JNIEnv *, jclass, jstring, jstring, jboolean);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGReportEvent
 * Signature: (Ljava/lang/String;Ljava/util/HashMap;Z)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGReportEvent__Ljava_lang_String_2Ljava_util_HashMap_2Z
  (JNIEnv *, jclass, jstring, jobject, jboolean);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGTestSpeed
 * Signature: (Ljava/util/ArrayList;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGTestSpeed
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetChannelId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetChannelId
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetVersion
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSetPermission
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSetPermission
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGIsPlatformInstalled
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGIsPlatformInstalled
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGIsPlatformSupportApi
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGIsPlatformSupportApi
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetRegisterChannelId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetRegisterChannelId
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGRefreshWXToken
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGRefreshWXToken
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetPf
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetPf
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetPfKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetPfKey
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGLogPlatformSDKVersion
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGLogPlatformSDKVersion
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToQQGameFriend
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQGameFriend
  (JNIEnv *, jclass, jint, jstring, jstring, jstring, jstring, jstring, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWXGameFriend
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWXGameFriend
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryQQMyInfo
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryQQMyInfo
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryQQGameFriendsInfo
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryQQGameFriendsInfo
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryWXMyInfo
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryWXMyInfo
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryWXGameFriendsInfo
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryWXGameFriendsInfo
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCheckApiSupport
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCheckApiSupport
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    SetActivity
 * Signature: (Landroid/app/Activity;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_SetActivity
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetNoticeData
 * Signature: (Ljava/lang/String;)Ljava/util/Vector;
 */
JNIEXPORT jobject JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetNoticeData
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGShowNotice
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGShowNotice
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGHideScrollNotice
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGHideScrollNotice
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGOpenUrl
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGOpenUrl
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGOpenAmsCenter
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGOpenAmsCenter
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGLoginWithLocalInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGLoginWithLocalInfo
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetNearbyPersonInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetNearbyPersonInfo
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCleanLocation
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCleanLocation
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetLocationInfo
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetLocationInfo
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendMessageToWechatGameCenter
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendMessageToWechatGameCenter
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGStartSaveUpdate
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGStartSaveUpdate
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSetSaveUpdateObserver
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSetSaveUpdateObserver
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCheckNeedUpdate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCheckNeedUpdate
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCheckYYBInstalled
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCheckYYBInstalled
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSetGameEngineType
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSetGameEngineType
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSetADObserver
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSetADObserver
  (JNIEnv *, jclass);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGShowAD
 * Signature: (Lcom/tencent/msdk/api/eADType;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGShowAD
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCloseAD
 * Signature: (Lcom/tencent/msdk/api/eADType;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCloseAD
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGJoinQQGroup
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGJoinQQGroup
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGBindQQGroup
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGBindQQGroup
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGAddGameFriendToQQ
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGAddGameFriendToQQ
  (JNIEnv *, jclass, jstring, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWeixinWithUrl
 * Signature: (Lcom/tencent/msdk/api/eWechatScene;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[BILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithUrl
  (JNIEnv *, jclass, jobject, jstring, jstring, jstring, jstring, jbyteArray, jint, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetPlatformAPPVersion
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetPlatformAPPVersion
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryQQGroupInfo
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryQQGroupInfo
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGUnbindQQGroup
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGUnbindQQGroup
  (JNIEnv *, jclass, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
