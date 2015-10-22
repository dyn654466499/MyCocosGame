#include <jni.h>
#include "com_tencent_msdk_api_WGQQGroupObserverForSO.h"
#include "CommonFiles/WGPlatform.h"
#include "CommonFiles/WGCommon.h"

#include <android/log.h>

/*
 * Class:     com_tencent_msdk_api_WGQQGroupObserverForSO
 * Method:    OnQueryGroupInfoNotify
 * Signature: (Lcom/tencent/msdk/api/QQGroupRet;)V
 */
JNIEXPORT void JNICALL Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnQueryGroupInfoNotify
  (JNIEnv *env, jclass, jobject jQQGroupRet){
	 LOGD("Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnQueryGroupInfoNotify start%s", "");
	 jclass jQQGroupRetClz = env->GetObjectClass(jQQGroupRet);
	 QQGroupRet cQQGroupRet;

	 JniGetAndSetIntField(flag, "flag", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);
	 JniGetAndSetIntField(errorCode, "errorCode", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);
	 JniGetAndSetStringField(desc, "desc", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);
	 //QQGroupInfo 对象
	 QQGroupInfo tempGroupInfo;
	 jclass jQQGroupInfoClass = env->FindClass("com/tencent/msdk/qq/group/QQGroupInfo");
	 jmethodID jQQGroupInfoInitMethod = env->GetMethodID(jQQGroupInfoClass, "<init>", "()V");
	 jmethodID jGetGroupInfoMethod = env->GetMethodID(jQQGroupRetClz, "getGroupInfo", "()Lcom/tencent/msdk/qq/group/QQGroupInfo;");
	 jobject jQQGroupInfoObj = env->NewObject(jQQGroupInfoClass, jQQGroupInfoInitMethod);
	 jQQGroupInfoObj = env->CallObjectMethod(jQQGroupRet,jGetGroupInfoMethod);
	 JniGetAndSetStringField(groupName,"groupName",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(fingerMemo,"fingerMemo",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(memberNum,"memberNum",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(maxNum,"maxNum",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(ownerOpenid,"ownerOpenid",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(unionid,"unionid",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(zoneid,"zoneid",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(adminOpenids,"adminOpenids",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(groupOpenid,"groupOpenid",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 JniGetAndSetStringField(groupKey,"groupKey",jQQGroupInfoClass, jQQGroupInfoObj,tempGroupInfo);
	 cQQGroupRet.mGroupInfo = tempGroupInfo;
	 if (WGPlatform::GetInstance()->GetQQGroupObserver() != NULL) {
		 WGPlatform::GetInstance()->GetQQGroupObserver()->OnQueryGroupInfoNotify(cQQGroupRet);
	 }
	 env->DeleteLocalRef(jQQGroupRetClz);
	 env->DeleteLocalRef(jQQGroupInfoClass);
	 env->DeleteLocalRef(jQQGroupInfoObj);
	 LOGD("Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnQueryGroupInfoNotify end%s", "");
}

/*
 * Class:     com_tencent_msdk_api_WGQQGroupObserverForSO
 * Method:    OnBindGroupNotify
 * Signature: (Lcom/tencent/msdk/api/QQGroupRet;)V
 */
JNIEXPORT void JNICALL Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnBindGroupNotify
(JNIEnv *env, jclass, jobject jQQGroupRet){

	LOGD("Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnBindGroupNotify start%s", "");
	 jclass jQQGroupRetClz = env->GetObjectClass(jQQGroupRet);
	 QQGroupRet cQQGroupRet;

	 JniGetAndSetIntField(flag, "flag", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);
	 JniGetAndSetIntField(errorCode, "errorCode", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);
	 JniGetAndSetStringField(desc, "desc", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);

	 if (WGPlatform::GetInstance()->GetQQGroupObserver() != NULL) {
		 WGPlatform::GetInstance()->GetQQGroupObserver()->OnBindGroupNotify(cQQGroupRet);
	 }
	 env->DeleteLocalRef(jQQGroupRetClz);
	 LOGD("Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnBindGroupNotify end%s", "");
}

/*
 * Class:     com_tencent_msdk_api_WGQQGroupObserverForSO
 * Method:    OnUnbindGroupNotify
 * Signature: (Lcom/tencent/msdk/api/QQGroupRet;)V
 */
JNIEXPORT void JNICALL Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnUnbindGroupNotify
(JNIEnv *env, jclass, jobject jQQGroupRet){
	 LOGD("Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnUnbindGroupNotify start%s", "");
	 jclass jQQGroupRetClz = env->GetObjectClass(jQQGroupRet);
	 QQGroupRet cQQGroupRet;

	 JniGetAndSetIntField(flag, "flag", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);
	 JniGetAndSetIntField(errorCode, "errorCode", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);
	 JniGetAndSetStringField(desc, "desc", jQQGroupRetClz, jQQGroupRet, cQQGroupRet);

	 if (WGPlatform::GetInstance()->GetQQGroupObserver() != NULL) {
		 WGPlatform::GetInstance()->GetQQGroupObserver()->OnUnbindGroupNotify(cQQGroupRet);
	 }
	 env->DeleteLocalRef(jQQGroupRetClz);
	 LOGD("Java_com_tencent_msdk_api_WGQQGroupObserverForSO_OnUnbindGroupNotify end%s", "");
}

