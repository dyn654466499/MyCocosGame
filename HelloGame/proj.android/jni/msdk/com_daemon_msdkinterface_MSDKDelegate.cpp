//#include "com_daemon_msdkinterface_MSDKDelegate.h"
#include "CommonFiles/WGPlatform.h"
#include "CommonFiles/WGPlatformObserver.h"
#include <string>
#include <vector>

#include <android/log.h>   
#include "com_daemon_msdkinterface_MSDKDelegate.h"

//#define LOGD(fmt, ...)   __android_log_print(ANDROID_LOG_INFO, "WeGame  ~!!@", fmt, __VA_ARGS__)
static jobject gActivity;
static JNIEnv * mEnv;
static JavaVM* g_jvm;

class GlobalCallback: public WGPlatformObserver {
public:
	virtual void OnLoginNotify(LoginRet& loginRet) {
		LOGD("OnLoginNotify: flag:%d platform:%d OpenId:%s, Token Size: %d",
				loginRet.flag, loginRet.platform, loginRet.open_id.c_str(), loginRet.token.size());

		if (loginRet.platform == ePlatform_QQ) {
			// 读取QQ的登陆票据
			switch (loginRet.flag) {
			case eFlag_Succ: {
				std::string accessToken = "";
				std::string payToken = "";
				for (int i = 0; i < loginRet.token.size(); i++) {
					if (loginRet.token.at(i).type == eToken_QQ_Access) {
						accessToken.assign(loginRet.token.at(i).value);
					} else if (loginRet.token.at(i).type == eToken_QQ_Pay) {
						payToken.assign(loginRet.token.at(i).value);
					}
				}
				LOGD("accessToken : %s", accessToken.c_str());
				LOGD("payToken : %s", payToken.c_str());

				// 下面是MSDKSample使用的逻辑, 游戏忽略此部分内容
//				jclass cls = mEnv->GetObjectClass(gActivity);
//				jmethodID method = mEnv->GetMethodID(cls, "showDialog", "()V");
//				mEnv->CallVoidMethod(gActivity, method);

				jclass TestProvider = mEnv->FindClass("com/daemon/nativecallback/MSDKCallBack");
				jmethodID changeToWelcomeScene_mID = mEnv->GetStaticMethodID(TestProvider, "changeToWelcomeScene","()V");
//			    JavaVMAttachArgs thread_args;
//			    thread_args.name = "test";
//			    thread_args.version = JNI_VERSION_1_4;
//			    thread_args.group = NULL;
//			    g_jvm->AttachCurrentThread(&mEnv, &thread_args);
				mEnv->CallStaticVoidMethod(TestProvider, changeToWelcomeScene_mID);
				//g_jvm->DetachCurrentThread();
				LOGD("OnLoginNotify call changeToWelcomeScene end%s", "");
				break;
			}
			case eFlag_QQ_NotInstall:
			case eFlag_QQ_NotSupportApi:
				break;
			case eFlag_QQ_UserCancel:
				break;
			case eFlag_QQ_NoAcessToken:
			case eFlag_QQ_LoginFail:
			case eFlag_QQ_NetworkErr:
				break;
			}
		} else if (loginRet.platform == ePlatform_Weixin) {
			switch (loginRet.flag) {
			case eFlag_Succ: {
				std::string accessToken = "";
				std::string refreshToken = "";
				for (int i = 0; i < loginRet.token.size(); i++) {
					if (loginRet.token.at(i).type == eToken_WX_Access) {
						accessToken.assign(loginRet.token.at(i).value);
					} else if (loginRet.token.at(i).type == eToken_WX_Refresh) {
						refreshToken.assign(loginRet.token.at(i).value);
					}
				}
				LOGD("accessToken : %s", accessToken.c_str());
				LOGD("payToken : %s", refreshToken.c_str());

				// 下面是MSDKSample使用的逻辑, 游戏忽略此部分内容
//				jclass cls = mEnv->GetObjectClass(gActivity);
//				jmethodID method = mEnv->GetMethodID(cls, "letUserLogin", "()V");
//				mEnv->CallVoidMethod(gActivity, method);
				LOGD("OnLoginNotify call letUserLogin end%s", "");

				break;
			}
			case eFlag_WX_NotSupportApi:
				break;

			case eFlag_WX_UserCancel:
			case eFlag_WX_UserDeny:
				break;
			case eFlag_WX_AccessTokenExpired:
				// 调用WGRefreshWxToken, 刷新accessToken
				break;
			case eFlag_WX_RefreshTokenExpired:
				// refreshToken过期, 提示用户重新授权
				break;
			case eFlag_WX_LoginFail:
			case eFlag_Error:
				break;
			case eFlag_WX_RefreshTokenSucc: {
				// WGRefreshWXToken调用成功, 成功用当前的refreshToken换到新的accessToken
				std::string accessToken = "";
				std::string refreshToken = "";
				for (int i = 0; i < loginRet.token.size(); i++) {
					if (loginRet.token.at(i).type == eToken_WX_Access) {
						accessToken.assign(loginRet.token.at(i).value);
					} else if (loginRet.token.at(i).type == eToken_WX_Refresh) {
						refreshToken.assign(loginRet.token.at(i).value);
					}
				}
				LOGD("accessToken : %s", accessToken.c_str());
				LOGD("payToken : %s", refreshToken.c_str());

				// 下面是MSDKSample使用的逻辑, 游戏忽略此部分内容
//				jclass cls = mEnv->GetObjectClass(gActivity);
//				jmethodID method = mEnv->GetMethodID(cls, "letUserLogin", "()V");
//				mEnv->CallVoidMethod(gActivity, method);
				LOGD("OnLoginNotify call letUserLogin end%s", "");
				break;
			}
			case eFlag_WX_RefreshTokenFail:
				// WGRefreshWXToken调用失败, 游戏自己决定是否需要重试 WGRefreshWXToken
				break;
			}
		}

	}

	virtual void OnShareNotify(ShareRet& shareRet) {
		LOGD("OnShareNotify: platform:%d flag:%d",
				shareRet.platform, shareRet.flag);
		// 处理分享回调
		if (shareRet.platform == ePlatform_QQ) {
			switch (shareRet.flag) {
			case eFlag_Succ:
				// 分享成功
				break;
			case eFlag_Error:
				// 分享失败
				break;
			}
		} else if (shareRet.platform == ePlatform_Weixin) {
			switch (shareRet.flag) {
			case eFlag_Succ:
				// 分享成功
				break;
			case eFlag_Error:
				// 分享失败
				break;
			}
		}
	}

	virtual void OnWakeupNotify(WakeupRet& wakeupRet) {
		LOGD("OnWakeupNotify: platform:%d flag:%d openid:%s",
				wakeupRet.platform, wakeupRet.flag, wakeupRet.open_id.c_str());
		// TODO GAME 这里要处理异账号的逻辑
		switch(wakeupRet.flag){
			case eFlag_Succ:
			case eFlag_UrlLogin:
			case eFlag_AccountRefresh:{
				// 下面是MSDKSample使用的逻辑, 游戏忽略此部分内容
//				jclass cls = mEnv->GetObjectClass(gActivity);
//				jmethodID methodletUserLogin = mEnv->GetMethodID(cls, "letUserLogin", "()V");
//				mEnv->CallVoidMethod(gActivity, methodletUserLogin);
				LOGD("OnWakeupNotify call letUserLogin end%s", "");
				break;
			}
			case eFlag_NeedSelectAccount:{
				LOGD("diff account%s", "");
//				jclass cls = mEnv->GetObjectClass(gActivity);
//				jmethodID methodshowDiffLogin = mEnv->GetMethodID(cls, "showDiffLogin", "()V");
//				mEnv->CallVoidMethod(gActivity, methodshowDiffLogin);
				LOGD("OnWakeupNotify call showDiffLogin end%s", "");
				break;
			}
			case eFlag_NeedLogin:{
				LOGD("login%s", "");
//				jclass cls = mEnv->GetObjectClass(gActivity);
//				jmethodID methodletUserLogout = mEnv->GetMethodID(cls, "letUserLogout", "()V");
//				mEnv->CallVoidMethod(gActivity, methodletUserLogout);
				LOGD("OnWakeupNotify call letUserLogout end%s", "");
				break;
			}
			default :{
				LOGD("login%s", "");
//				jclass cls = mEnv->GetObjectClass(gActivity);
//				jmethodID methodletUserLogout = mEnv->GetMethodID(cls, "letUserLogout", "()V");
//				mEnv->CallVoidMethod(gActivity, methodletUserLogout);
				LOGD("OnWakeupNotify call letUserLogout end%s", "");
				break;
			}
		}
	}

	virtual void OnRelationNotify(RelationRet& relationRet) {
		LOGD("OnRelationCallBack flag:%d ", relationRet.flag);
		LOGD("OnRelationCallBack desc:%s ", relationRet.desc.c_str());
		LOGD("OnRelationCallBack friends total:%d ", relationRet.persons.size());
		// TODO GAME 这里应该也要返回平台
		switch (relationRet.flag) {
		case eFlag_Succ: {
			// relationRet.persons.at(0) 中保存的即是个人信息
			for (int i = 0; i < relationRet.persons.size(); i++) {
				std::string city = relationRet.persons.at(i).city;
				std::string gender = relationRet.persons.at(i).gender;
				std::string nickName = relationRet.persons.at(i).nickName;
				std::string openId = relationRet.persons.at(i).openId;
				std::string pictureLarge =
						relationRet.persons.at(i).pictureLarge;
				std::string pictureMiddle =
						relationRet.persons.at(i).pictureMiddle;
				std::string pictureSmall =
						relationRet.persons.at(i).pictureSmall;
				std::string provice = relationRet.persons.at(i).provice;
			}
			break;
		}
		default:
			break;
		}
	}

    virtual void OnLocationNotify(RelationRet& relationRet) {
    	LOGD("OnLocationNotify %d", relationRet.persons.size());
    }

    virtual void OnLocationGotNotify(LocationRet& locationRet) {
    	LOGD("OnLocationNotify longitude %f", locationRet.longitude);
    	LOGD("OnLocationNotify latitude %f", locationRet.latitude);
    }

    virtual void OnFeedbackNotify(int flag, std::string desc) {
    	LOGD("OnFeedbackNotify %d; %s", flag, desc.c_str());
    }

    virtual std::string OnCrashExtMessageNotify() {
    	// 此处游戏补充crash时上报的额外信息
    	std::string str = "new jni update extra jni crash log now!";
    	LOGD("OnCrashExtMessageNotify %s", str.c_str());
    	return str;
    }

	virtual ~GlobalCallback() {
	}
};

GlobalCallback g_Test;

// 广告的回调
class ADCAllback: public WGADObserver {

    virtual void OnADNotify(ADRet& adRet) {
    	// 游戏在此处添加显示广告点击button的处理逻辑
		LOGD("ADCAllback OnADNotify Tag:%s ", adRet.viewTag.c_str());
		if(adRet.scene == Type_Pause) {
			LOGD("ADCAllback OnADNotify scene:Type_Pause%s", "");
		} else if(adRet.scene == Type_Stop) {
			LOGD("ADCAllback OnADNotify scene:Type_Stop%s", "");
		}
    }

    virtual void OnADBackPressedNotify(ADRet& adRet) {
    	 // 游戏在此处添加显示广告后按返回键的处理逻辑
		LOGD("ADCAllback OnADBackPressedNotify Tag:%s ", adRet.viewTag.c_str());
		if(adRet.scene == Type_Pause) {
			LOGD("ADCAllback OnADBackPressedNotify scene:Type_Pause%s", "");
			// 游戏注意关闭广告对话框
			WGPlatform::GetInstance()->WGCloseAD(adRet.scene);
		} else if(adRet.scene == Type_Stop) {
			LOGD("ADCAllback OnADBackPressedNotify scene:Type_Stop%s", "");
			// 游戏注意关闭广告对话框
			WGPlatform::GetInstance()->WGCloseAD(adRet.scene);
		}
    }
};

ADCAllback ad_callback;

class SaveUpdateCallback: public WGSaveUpdateObserver {
	virtual void OnCheckNeedUpdateInfo(long newApkSize, std::string newFeature, long patchSize,
			int status, std::string updateDownloadUrl, int updateMethod) {
		LOGD("SaveUpdateCallback  OnCheckNeedUpdateInfo  "
				"newApkSize: %ld; newFeature: %s; patchSize: %ld; status: %d; updateDownloadUrl: %s; updateMethod: %d",
				newApkSize, newFeature.c_str(), patchSize,
				status, updateDownloadUrl.c_str(),  updateMethod);
	}

	virtual void OnDownloadAppProgressChanged(long receiveDataLen, long totalDataLen) {
		LOGD("SaveUpdateCallback  OnDownloadAppProgressChanged  receiveDataLen: %ld; totalDataLen: %ld;",
				receiveDataLen, totalDataLen);
	}

	virtual void OnDownloadAppStateChanged(int state, int errorCode, std::string errorMsg) {
		LOGD("SaveUpdateCallback  OnDownloadAppStateChanged state: %d; errorCode: %d; errorMsg: %s",
				state, errorCode, errorMsg.c_str());
	}

	virtual void OnDownloadYYBProgressChanged(std::string url, long receiveDataLen, long totalDataLen) {
		LOGD("SaveUpdateCallback  OnDownloadYYBProgressChanged url: %s; receiveDataLen: %ld; totalDataLen: %ld",
				url.c_str(), receiveDataLen, totalDataLen);
	}

	virtual void OnDownloadYYBStateChanged(std::string url, int state, int errorCode, std::string errorMsg) {
		LOGD("SaveUpdateCallback  OnDownloadYYBStateChanged  url: %s, state: %d, errorCode: %d, errorMsg: %s",
				url.c_str(), state, errorCode, errorMsg.c_str());
	}
};
SaveUpdateCallback callback;

// 广告的回调
class QQGroupCallback: public WGQQGroupObserver {

	virtual void OnQueryGroupInfoNotify(QQGroupRet& groupRet){
		// 游戏在此处添加查询群信息返回以后的逻辑
		LOGD("QQGroupCallback OnQueryGroupInfoNotify;flag:%d;errorCode:%d;desc:%s",groupRet.flag,groupRet.errorCode,groupRet.desc.c_str());
	}
	virtual void OnBindGroupNotify(QQGroupRet& groupRet){
		//游戏在此处添加绑定群以后的逻辑,目前openSDK不支持，MSDK只能返回接口调用成功
		LOGD("QQGroupCallback OnQueryGroupInfoNotify;flag:%d;errorCode:%d;desc:%s",groupRet.flag,groupRet.errorCode,groupRet.desc.c_str());
	}
	virtual void OnUnbindGroupNotify(QQGroupRet& groupRet){
		// 游戏在此处添加调用解绑接口以后的返回结果
		LOGD("QQGroupCallback OnQueryGroupInfoNotify;flag:%d;errorCode:%d;desc:%s",groupRet.flag,groupRet.errorCode,groupRet.desc.c_str());
	}
};
QQGroupCallback qqGroup_callback;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
	//TODO GAME C++层初始化, 必须在游戏主Activity的onCreate之前被调用

	WGPlatform::GetInstance()->init(vm);
	WGPlatform::GetInstance()->WGSetObserver(&g_Test);
	WGPlatform::GetInstance()->WGSetADObserver(&ad_callback);
	WGPlatform::GetInstance()->WGSetQQGroupObserver(&qqGroup_callback);
	
	WGPlatform::GetInstance()->WGSetSaveUpdateObserver(&callback);
	g_jvm = vm;
	return JNI_VERSION_1_4;
}
static std::string j2c(JNIEnv* env, jstring str) {
	LOGD("WGPlatform::java2c %s", "");

	jclass clsstring = env->FindClass("java/lang/String");
	jmethodID length = env->GetMethodID(clsstring, "length", "()I");
	if (str == NULL) {
		std::string stemp("");
		return stemp;
	}
	jint len = (jint) env->CallIntMethod(str, length);

	if (len > 0) {
		LOGD("WGPlatform::java2c %s", "");

		jstring strencode = env->NewStringUTF("utf-8");
		jmethodID mid = env->GetMethodID(clsstring, "getBytes",
				"(Ljava/lang/String;)[B");
		jbyteArray barr = (jbyteArray) env->CallObjectMethod(str, mid,
				strencode);
		jsize alen = env->GetArrayLength(barr);
		jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);

		char* rtn = (char*) malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
		env->ReleaseByteArrayElements(barr, ba, 0);

		std::string stemp(rtn);
		free(rtn);
		return stemp;
	} else {
		std::string stemp("");
		return stemp;
	}
}

static jstring c2j(JNIEnv *env, unsigned char* buf, unsigned int size) {
	jclass strClass = env->FindClass("java/lang/String");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>",
			"([BLjava/lang/String;)V");

	jbyteArray bytes = env->NewByteArray(size);
	env->SetByteArrayRegion(bytes, 0, size, (jbyte*) buf);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring) env->NewObject(strClass, ctorID, bytes, encoding);
}
//jint, jstring, jstring, jstring, jstring, jint
//jint scene, jstring title, jstring desc, jstring url, jstring imgUrl, jint imgUrlLen
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQ(
		JNIEnv * env, jclass, jobject jScene, jstring j_title, jstring j_desc,
		jstring j_url, jstring j_imgUrl, jint imgUrlLen) {
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQ %s", "");

	// 把参数中的jstring全部转为 unsigned char *
	std::string s_title = j2c(env, j_title);
	unsigned char * title = (unsigned char *) s_title.c_str();

	std::string s_desc = j2c(env, j_desc);
	unsigned char * desc = (unsigned char *) s_desc.c_str();

	std::string s_url = j2c(env, j_url);
	unsigned char * url = (unsigned char *) s_url.c_str();

	std::string s_imgUrl = j2c(env, j_imgUrl);
	unsigned char * imgUrl = (unsigned char *) s_imgUrl.c_str();

	jclass jSceneClass = env->GetObjectClass(jScene);
	jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
	int cScene = env->GetIntField(jScene, jSceneField);
	env->DeleteLocalRef(jSceneClass);
	WGPlatform::GetInstance()->WGSendToQQ((eQQScene)cScene, title, desc, url, imgUrl,
			imgUrlLen);
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToQQWithPhoto
 * Signature: (ILjava/lang/String;)V
 */JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQWithPhoto(
		JNIEnv * env, jclass, jobject jScene, jstring jImageFilePath) {
	jboolean jIsCopy;
	const char * cImageFilePath = env->GetStringUTFChars(jImageFilePath,
			&jIsCopy);
	jclass jSceneClass = env->GetObjectClass(jScene);
	jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
	int cScene = env->GetIntField(jScene, jSceneField);
	env->DeleteLocalRef(jSceneClass);

	WGPlatform::GetInstance()->WGSendToQQWithPhoto((eQQScene)cScene,
			(unsigned char*) cImageFilePath);
	env->ReleaseStringUTFChars(jImageFilePath, cImageFilePath);
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixin(
		JNIEnv * pEnv, jclass, jstring j_title, jstring j_desc,
		jstring j_mediaTagName, jbyteArray j_imgData, jint j_imgDataLen,
		jstring j_messageExt) {
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixin + messageExt%s",
			"");

	// 把参数中的jstring全部转为 unsigned char *
	std::string s_title = j2c(pEnv, j_title);
	unsigned char * title = (unsigned char *) s_title.c_str();

	std::string s_desc = j2c(pEnv, j_desc);
	unsigned char * desc = (unsigned char *) s_desc.c_str();

	std::string s_mediaTagName = j2c(pEnv, j_mediaTagName);
	unsigned char * mediaTagName = (unsigned char *) s_mediaTagName.c_str();

	std::string s_messageExt = j2c(pEnv, j_messageExt);
	unsigned char * messageExt = (unsigned char *) s_messageExt.c_str();

	// 把jByteArray中的数据转为unsigned char array
	jboolean isCopy;
	jbyte * imgDataJb = pEnv->GetByteArrayElements(j_imgData, &isCopy);
	int imgDataLen = (int) j_imgDataLen;
	unsigned char * imgData = new unsigned char[imgDataLen];
	memcpy(imgData, (unsigned char *) imgDataJb, imgDataLen);

	WGPlatform::GetInstance()->WGSendToWeixin(title, desc, mediaTagName, imgData, imgDataLen, messageExt);

	if (isCopy) {
		pEnv->ReleaseByteArrayElements(j_imgData, imgDataJb, 0);
	}
}

/**
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToQQWithMusic
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQWithMusic
  (JNIEnv *env, jclass, jobject jScene, jstring jTitle, jstring jDesc, jstring jMusicUrl, jstring jMusicDataUrl, jstring jImgUrl){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQWithMusic%s", "");
	jclass jSceneClass = env->GetObjectClass(jScene);
	jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
	int cScene = env->GetIntField(jScene, jSceneField);

	std::string cTitle = j2c(env, jTitle);
	std::string cDesc = j2c(env, jDesc);
	std::string cMusicUrl = j2c(env, jMusicUrl);
	std::string cMusicDataUrl = j2c(env, jMusicDataUrl);
	std::string cImgUrl = j2c(env, jImgUrl);

	WGPlatform::GetInstance()->WGSendToQQWithMusic((eQQScene)cScene, (unsigned char *)cTitle.c_str(),
			 (unsigned char *)cDesc.c_str(), (unsigned char *)cMusicUrl.c_str(),
			 (unsigned char *)cMusicDataUrl.c_str(), (unsigned char *)cImgUrl.c_str());
	env->DeleteLocalRef(jSceneClass);
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQWithMusic%s", "");
}

/**
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGBindQQGroup
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGBindQQGroup
  (JNIEnv *env, jclass, jstring jUnionid, jstring jUnion_name, jstring jZoneid, jstring jSignature){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGBindQQGroup%s", "");

	std::string cUnionid = j2c(env, jUnionid);
	std::string cUnion_name = j2c(env, jUnion_name);
	std::string cZoneid = j2c(env, jZoneid);
	std::string cSignature = j2c(env, jSignature);

	WGPlatform::GetInstance()->WGBindQQGroup((unsigned char *)cUnionid.c_str(),
			 (unsigned char *)cUnion_name.c_str(), (unsigned char *)cZoneid.c_str(),
			 (unsigned char *)cSignature.c_str());

	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGBindQQGroup%s", "");
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWeixinWithUrl
 * Signature: (Lcom/tencent/msdk/api/eWechatScene;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[BILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithUrl
  (JNIEnv *env, jclass, jobject jScene, jstring jTitle, jstring jDesc, jstring jUrl, jstring jMediaTagName, jbyteArray jImgData, jint jLength, jstring jMessageExt){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithUrl%s", "");
		jclass jSceneClass = env->GetObjectClass(jScene);
		jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
		int cScene = env->GetIntField(jScene, jSceneField);
		std::string cTitle = j2c(env, jTitle);
		std::string cDesc = j2c(env, jDesc);
		std::string cUrl = j2c(env, jUrl);
		std::string cMediaTagName = j2c(env, jMediaTagName);
		jboolean jIsCopy;
		jbyte * jImgDataByte = env->GetByteArrayElements(jImgData, &jIsCopy);
		int cImgDataLen = (int) jLength;
		unsigned char * cImgData = new unsigned char[cImgDataLen];
		memcpy(cImgData, (unsigned char *) jImgDataByte, cImgDataLen);
		std::string cMessageExt = j2c(env, jMessageExt);
		WGPlatform::GetInstance()->WGSendToWeixinWithUrl((eWechatScene)cScene, (unsigned char *)cTitle.c_str(),
				(unsigned char *)cDesc.c_str(), (unsigned char *)cUrl.c_str(), (unsigned char *)cMediaTagName.c_str(),
				(unsigned char*)cImgData, cImgDataLen, (unsigned char *)cMessageExt.c_str());

		LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithUrl%s", "");
}

/**
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGBindQQGroup
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGAddGameFriendToQQ
  (JNIEnv *env, jclass, jstring jFopenid, jstring jDesc, jstring jMessage){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGAddGameFriendToQQ%s", "");

	std::string cFopenid = j2c(env, jFopenid);
	std::string cDesc = j2c(env, jDesc);
	std::string cMessage = j2c(env, jMessage);

	WGPlatform::GetInstance()->WGAddGameFriendToQQ((unsigned char *)cFopenid.c_str(),
			 (unsigned char *)cDesc.c_str(), (unsigned char *)cMessage.c_str());

	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGAddGameFriendToQQ%s", "");
}

/**
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGBindQQGroup
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGJoinQQGroup
  (JNIEnv *env, jclass, jstring jQqGroupKey){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGBindQQGroup%s", "");

	std::string cQqGroupKey = j2c(env, jQqGroupKey);

	WGPlatform::GetInstance()->WGJoinQQGroup((unsigned char *)cQqGroupKey.c_str());

	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGJoinQQGroup%s", "");
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWeixinWithMusic
 * Signature: (Lcom/tencent/msdk/api/eWechatScene;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[BILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithMusic
  (JNIEnv *env, jclass, jobject jScene, jstring jTitle, jstring jDesc,
		  jstring jMusicUrl, jstring jMusicDataUrl, jstring jMediaTagName,
		  jbyteArray jImageDataArray, jint jImgDataLen, jstring jMessageExt, jstring jMessageAction){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithMusic%s", "");
	jclass jSceneClass = env->GetObjectClass(jScene);
	jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
	int cScene = env->GetIntField(jScene, jSceneField);
	env->DeleteLocalRef(jSceneClass);
	std::string cTitle = j2c(env, jTitle);
	std::string cDesc = j2c(env, jDesc);
	std::string cMusicUrl = j2c(env, jMusicUrl);
	std::string cMusicDataUrl = j2c(env, jMusicDataUrl);
	std::string cMediaTagName = j2c(env, jMediaTagName);
	// 把jByteArray中的数据转为unsigned char array
	jboolean jIsCopy;
	jbyte * jImgDataByte = env->GetByteArrayElements(jImageDataArray, &jIsCopy);
	int cImgDataLen = (int) jImgDataLen;
	unsigned char * cImgData = new unsigned char[cImgDataLen];
	memcpy(cImgData, (unsigned char *) jImgDataByte, cImgDataLen);
	std::string cMessageExt = j2c(env, jMessageExt);
	std::string cMessageAction = j2c(env, jMessageAction);

	WGPlatform::GetInstance()->WGSendToWeixinWithMusic((eWechatScene)cScene, (unsigned char *)cTitle.c_str(),
			(unsigned char *)cDesc.c_str(), (unsigned char *)cMusicUrl.c_str(), (unsigned char *)cMusicDataUrl.c_str(),
			(unsigned char *)cMediaTagName.c_str(), (unsigned char*)cImgData, cImgDataLen,
	        (unsigned char *)cMessageExt.c_str(), (unsigned char *)cMessageAction.c_str());

	if (jIsCopy) {
		env->ReleaseByteArrayElements(jImageDataArray, jImgDataByte, 0);
	}
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithPhoto__Lcom_tencent_msdk_api_eWechatScene_2Ljava_lang_String_2_3BI(
		JNIEnv * env, jclass, jobject jScene, jstring j_mediaTagName,
		jbyteArray j_imgData, jint j_imgDataLen) {
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithPhoto%s", "");

	jclass jSceneClass = env->GetObjectClass(jScene);
	jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
	int cScene = env->GetIntField(jScene, jSceneField);
	env->DeleteLocalRef(jSceneClass);

	// 把jByteArray中的数据转为unsigned char array
	jboolean isCopy;
	jbyte * imgDataJb = env->GetByteArrayElements(j_imgData, &isCopy);
	int imgDataLen = (int) j_imgDataLen;
	unsigned char * imgData = new unsigned char[imgDataLen];
	memcpy(imgData, (unsigned char *) imgDataJb, imgDataLen);

	std::string s_mediaTagName = j2c(env, j_mediaTagName);
	unsigned char * mediaTagName = (unsigned char *) s_mediaTagName.c_str();

	WGPlatform::GetInstance()->WGSendToWeixinWithPhoto((eWechatScene)cScene, mediaTagName,
			(unsigned char*) imgData, imgDataLen);

	if (isCopy) {
		env->ReleaseByteArrayElements(j_imgData, imgDataJb, 0);
	}
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithPhoto__Lcom_tencent_msdk_api_eWechatScene_2Ljava_lang_String_2_3BILjava_lang_String_2Ljava_lang_String_2(
		JNIEnv * env, jclass, jobject jScene, jstring j_mediaTagName,
		jbyteArray j_imgData, jint j_imgDataLen, jstring j_messageExt,
		jstring j_messageAction) {
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWeixinWithPhoto  + messageExt %s", "");

	jclass jSceneClass = env->GetObjectClass(jScene);
	jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
	int cScene = env->GetIntField(jScene, jSceneField);
	env->DeleteLocalRef(jSceneClass);

	// 把jByteArray中的数据转为unsigned char array
	jboolean isCopy;
	jbyte * imgDataJb = env->GetByteArrayElements(j_imgData, &isCopy);
	int imgDataLen = (int) j_imgDataLen;
	unsigned char * imgData = new unsigned char[imgDataLen];
	memcpy(imgData, (unsigned char *) imgDataJb, imgDataLen);

	std::string s_mediaTagName = j2c(env, j_mediaTagName);
	unsigned char * mediaTagName = (unsigned char *) s_mediaTagName.c_str();

	std::string s_messageExt = j2c(env, j_messageExt);
	unsigned char * messageExt = (unsigned char *) s_messageExt.c_str();

	std::string s_messageAction = j2c(env, j_messageAction);
	unsigned char * messageAction = (unsigned char *) s_messageAction.c_str();

	WGPlatform::GetInstance()->WGSendToWeixinWithPhoto((eWechatScene)cScene, mediaTagName,
			(unsigned char*) imgData, imgDataLen, messageExt, messageAction);

	if (isCopy) {
		env->ReleaseByteArrayElements(j_imgData, imgDataJb, 0);
	}
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGLogin(
		JNIEnv *pEnv, jclass, jint Platform) {
	int p = (int) Platform;
	WGPlatform::GetInstance()->WGLogin((ePlatform) Platform);
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_login: %d", Platform);
}

JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSwitchUser(
		JNIEnv *, jclass, jboolean switchToLaunchUser) {

	bool flag = WGPlatform::GetInstance()->WGSwitchUser(switchToLaunchUser);
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGLoginWithUrlInfo: %d", flag);
	return flag;
}

JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGLogout(
		JNIEnv *, jclass) {
	bool bOk = WGPlatform::GetInstance()->WGLogout();
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_logout clear:%s",
			bOk ? "true" : "false");
	return bOk;
}
JNIEXPORT jint JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetLoginRecord(
		JNIEnv * env, jclass, jobject jLr) {
	LoginRet lr;
	LOGD(
			"Java_com_daemon_msdkinterface_MSDKDelegate_WGGetLoginRecord start: desc: %s",
			lr.desc.c_str());
	int platform = WGPlatform::GetInstance()->WGGetLoginRecord(lr);
	LOGD("call WGGetLoginRecord end:%s", "");

	jclass cls = env->GetObjectClass(jLr);
	jfieldID flagFieldId = env->GetFieldID(cls, "flag", "I");
	env->SetIntField(jLr, flagFieldId, lr.flag);

	jfieldID descFieldId = env->GetFieldID(cls, "desc", "Ljava/lang/String;");
	env->SetObjectField(jLr, descFieldId,
			c2j(env, (unsigned char *) lr.desc.c_str(),
					strlen((char *) lr.desc.c_str())));

	jfieldID openIdFieldId = env->GetFieldID(cls, "open_id",
			"Ljava/lang/String;");
	env->SetObjectField(jLr, openIdFieldId,
			c2j(env, (unsigned char *) lr.open_id.c_str(),
					strlen((char *) lr.open_id.c_str())));

	jfieldID pfFieldId = env->GetFieldID(cls, "pf", "Ljava/lang/String;");
	env->SetObjectField(jLr, pfFieldId,
			c2j(env, (unsigned char *) lr.pf.c_str(),
					strlen((char *) lr.pf.c_str())));

	jfieldID pfKeyFieldId = env->GetFieldID(cls, "pf_key",
			"Ljava/lang/String;");
	env->SetObjectField(jLr, pfKeyFieldId,
			c2j(env, (unsigned char *) lr.pf_key.c_str(),
					strlen((char *) lr.pf_key.c_str())));

	jfieldID platformFieldId = env->GetFieldID(cls, "platform", "I");
	env->SetIntField(jLr, platformFieldId, (jint) lr.platform);

	jfieldID userIdFieldId = env->GetFieldID(cls, "user_id",
			"Ljava/lang/String;");
	env->SetObjectField(jLr, userIdFieldId,
			c2j(env, (unsigned char *) lr.user_id.c_str(),
					strlen((char *) lr.user_id.c_str())));

	// Vector<TokenRet>
	jfieldID tokenFieldId = env->GetFieldID(cls, "token", "Ljava/util/Vector;");
	jobject tokenVector = env->GetObjectField(jLr, tokenFieldId);
	jclass tokenVctCls = env->GetObjectClass(tokenVector);
	jmethodID jmVectorAdd = env->GetMethodID(tokenVctCls, "add",
			"(Ljava/lang/Object;)Z");

	// TokenRet
	jclass tokenRetCls = env->FindClass("com/tencent/msdk/api/TokenRet");
	jmethodID trConstructor = env->GetMethodID(tokenRetCls, "<init>", "()V");
	jfieldID trTypeFieldId = env->GetFieldID(tokenRetCls, "type", "I");
	jfieldID trValueFieldId = env->GetFieldID(tokenRetCls, "value",
			"Ljava/lang/String;");
	jfieldID trExpFieldId = env->GetFieldID(tokenRetCls, "expiration", "J");

	for (int i = 0; i < lr.token.size(); i++) {
		jobject loginRet = env->NewObject(tokenRetCls, trConstructor);
		env->SetIntField(loginRet, trTypeFieldId, lr.token.at(i).type);
		jstring jValue = c2j(env, (unsigned char*) lr.token.at(i).value.c_str(),
				strlen((char *) lr.token.at(i).value.c_str()));
		env->SetObjectField(loginRet, trValueFieldId, jValue);
		env->SetLongField(loginRet, trExpFieldId, lr.token.at(i).expiration);
		env->CallBooleanMethod(tokenVector, jmVectorAdd, loginRet);
		env->DeleteLocalRef(loginRet);
		env->DeleteLocalRef(jValue);
		LOGD("call WGGetLoginRecord end:2%s", "");
	}
	env->SetObjectField(jLr, tokenFieldId, tokenVector);
	LOGD("call Java_com_daemon_msdkinterface_MSDKDelegate_WGGetLoginRecord end:%s",
			"");
	env->DeleteLocalRef(cls);
	env->DeleteLocalRef(tokenVector);
	env->DeleteLocalRef(tokenVctCls);
	env->DeleteLocalRef(tokenRetCls);

	return platform;
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGFeedBack
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGFeedBack__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *env, jclass, jstring game, jstring txt) {
	std::string cgame = j2c(env, game);
	std::string ctxt = j2c(env, txt);
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGFeedBack: game:%s, txt:%s",
			cgame.c_str(), ctxt.c_str());
	return WGPlatform::GetInstance()->WGFeedback((unsigned char*) cgame.c_str(),
			(unsigned char*) ctxt.c_str());
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGFeedBack
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGFeedBack__Ljava_lang_String_2
  (JNIEnv * env, jclass, jstring body) {
	std::string cBody = j2c(env, body);
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGFeedBack: body:%s", cBody.c_str());
	return WGPlatform::GetInstance()->WGFeedback((unsigned char*) cBody.c_str());
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_throwExp(JNIEnv *,
		jclass) {
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_throwExp%s", "");
	WGPlatform* tmp = NULL;
	LoginRet lr;
	printf("%d", tmp->WGGetLoginRecord(lr));
}
//-----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_setObserver(
		JNIEnv *, jclass, jboolean flag) {
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_setObserver%s", "");
	if (flag == JNI_TRUE) {
		WGPlatform::GetInstance()->WGSetObserver(&g_Test);
	} else {
		WGPlatform::GetInstance()->WGSetObserver(NULL);
	}
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGEnableCrashReport(
		JNIEnv * env, jclass, jboolean isRdmEnable, jboolean isMtaEnable) {
	WGPlatform::GetInstance()->WGEnableCrashReport(isRdmEnable, isMtaEnable);
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGReportEvent
 * Signature: (Ljava/lang/String;Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGReportEvent__Ljava_lang_String_2Ljava_lang_String_2Z
  (JNIEnv * env, jclass, jstring jName, jstring jBody, jboolean jIsRealTime) {
	std::string sName = j2c(env, jName);
	std::string sBody = j2c(env, jBody);
	WGPlatform::GetInstance()->WGReportEvent((unsigned char *) sName.c_str(),
			(unsigned char *) sBody.c_str(), (bool) jIsRealTime);
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGReportEvent
 * Signature: (Ljava/lang/String;Ljava/util/HashMap;Z)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGReportEvent__Ljava_lang_String_2Ljava_util_HashMap_2Z
  (JNIEnv * env, jclass, jstring jName, jobject jparams, jboolean jIsRealTime){
	std::string sName = j2c(env, jName);
	jclass clsHashMap = env->FindClass("java/util/HashMap");
//  	Set<Entry<String,String>> keySet = params.entrySet();

	jmethodID jEntrySetMethod = env->GetMethodID(clsHashMap, "entrySet", "()Ljava/util/Set;");
	jobject jEntrySet = env->CallObjectMethod(jparams, jEntrySetMethod);
	//    	Iterator iter = keySet.iterator();
	jclass jEntrySetClass = env->GetObjectClass(jEntrySet);
	jmethodID jIteratorMethod = env->GetMethodID(jEntrySetClass, "iterator", "()Ljava/util/Iterator;");
	jobject jIterator = env->CallObjectMethod(jEntrySet, jIteratorMethod);

	jclass jIteratorClass = env->GetObjectClass(jIterator);
	//jclass jIteratorClass = env->FindClass("java/util/Iterator");
	jmethodID jHasNextMethod = env->GetMethodID(jIteratorClass, "hasNext", "()Z");
	jmethodID jNextMethod = env->GetMethodID(jIteratorClass, "next", "()Ljava/lang/Object;");

	std::vector<KVPair> cEventList;

	while(env->CallBooleanMethod(jIterator, jHasNextMethod)){
		//    	while (iter.hasNext()) {
		//    	    Map.Entry<String,String> entry = (Map.Entry<String,String>) iter.next();
		jobject jMap = env->CallObjectMethod(jIterator, jNextMethod);
		jclass jMapClass = env->GetObjectClass(jMap);
		jmethodID jGetKeyMethod = env->GetMethodID(jMapClass, "getKey", "()Ljava/lang/Object;");
		jmethodID jGetValueMethod = env->GetMethodID(jMapClass, "getValue", "()Ljava/lang/Object;");
		std::string cKeysInfo = j2c(env,(jstring) env->CallObjectMethod(jMap, jGetKeyMethod));
		std::string cValuesInfo = j2c(env,(jstring) env->CallObjectMethod(jMap, jGetValueMethod));

		KVPair cKVPair = {cKeysInfo,cValuesInfo};
		cEventList.push_back(cKVPair);
	}
	WGPlatform::GetInstance()->WGReportEvent((unsigned char*) sName.c_str(),
				cEventList, (bool) jIsRealTime);
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGTestSpeed(
		JNIEnv * env, jclass, jobject jAddrList) {
	jclass cls = env->GetObjectClass(jAddrList);
	jmethodID jmSize = env->GetMethodID(cls, "size", "()I");
	jmethodID jmGet = env->GetMethodID(cls, "get", "(I)Ljava/lang/Object;");
	jint len = env->CallIntMethod(jAddrList, jmSize);

	std::vector<std::string> addrVector;
	for (int i = 0; i < len; i++) {
		jstring addr = (jstring) env->CallObjectMethod(jAddrList, jmGet, i);
		addrVector.push_back(j2c(env, addr));
	}

	WGPlatform::GetInstance()->WGTestSpeed(addrVector);
}
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetChannelId(
		JNIEnv * env, jclass) {
	const std::string channelId = WGPlatform::GetInstance()->WGGetChannelId();
	LOGD("channelId: %s", channelId.c_str());
	jstring js;
	js = env->NewStringUTF(channelId.c_str());
	return js;
}

JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetVersion(
		JNIEnv * env, jclass) {
	const std::string version = WGPlatform::GetInstance()->WGGetVersion();
	return env->NewStringUTF(version.c_str());
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSetPermission(
		JNIEnv *, jclass, jint permissions) {
	int pms = (unsigned int) permissions;
	LOGD("permissions: %d", permissions);
	WGPlatform::GetInstance()->WGSetPermission(pms);
}
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGIsPlatformInstalled(
		JNIEnv * env, jclass, jint platform) {
	return WGPlatform::GetInstance()->WGIsPlatformInstalled(
			(ePlatform) platform);
}

JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGIsPlatformSupportApi(
		JNIEnv * env, jclass, jint platform) {
	return WGPlatform::GetInstance()->WGIsPlatformSupportApi(
			(ePlatform) platform);
}

JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetRegisterChannelId(
		JNIEnv * env, jclass) {
	const std::string channelId =
			WGPlatform::GetInstance()->WGGetRegisterChannelId();
	LOGD("channelId: %s", channelId.c_str());
	jstring js;
	js = env->NewStringUTF(channelId.c_str());
	return js;
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGRefreshWXToken(
		JNIEnv * env, jclass) {
	WGPlatform::GetInstance()->WGRefreshWXToken();
}
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetPf(
		JNIEnv * env, jclass, jstring jGameCustomInfo) {
	jstring js;
	jboolean jIsCopy;
	unsigned char * cGameCustomInfo = (unsigned char*)env->GetStringUTFChars(jGameCustomInfo, &jIsCopy);
	const std::string pf = WGPlatform::GetInstance()->WGGetPf(cGameCustomInfo);
	js = env->NewStringUTF(pf.c_str());
	return js;
}
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetPfKey(
		JNIEnv * env, jclass) {
	jstring js;
	const std::string pfKey = WGPlatform::GetInstance()->WGGetPfKey();
	js = env->NewStringUTF(pfKey.c_str());
	return js;
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToQQGameFriend
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQGameFriend(
		JNIEnv * env, jclass, jint jAct, jstring jFriendOpendId, jstring jTitle,
		jstring jSummary, jstring jTargetUrl, jstring jImageUrl,
		jstring jPreviewText, jstring jGameTag) {
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQGameFriend%d", jAct);
	int cAct = (int) jAct;
	std::string cFriendOpenId = j2c(env, jFriendOpendId);
	std::string cTitle = j2c(env, jTitle);
	std::string cSummary = j2c(env, jSummary);
	std::string cTargetUrl = j2c(env, jTargetUrl);
	std::string cImageUrl = j2c(env, jImageUrl);
	std::string cPreviewText = j2c(env, jPreviewText);
	std::string cGameTag = j2c(env, jGameTag);
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToQQGameFriend%s", "");

	LOGD("WGSendToQQGameFriend cAct : %d ", cAct);
	LOGD("WGSendToQQGameFriend cFriendOpenid %s : ", cFriendOpenId.c_str());
	LOGD("WGSendToQQGameFriend cTitle  : %s", cTitle.c_str());
	LOGD("WGSendToQQGameFriend cSummary : %s ", cSummary.c_str());
	LOGD("WGSendToQQGameFriend cTargetUrl : %s ", cTargetUrl.c_str());
	LOGD("WGSendToQQGameFriend cImgUrl : %s ", cImageUrl.c_str());
	LOGD("WGSendToQQGameFriend cPreviewText : %s ", cPreviewText.c_str());
	LOGD("WGSendToQQGameFriend cGameTag : %s ", cGameTag.c_str());

	return WGPlatform::GetInstance()->WGSendToQQGameFriend(cAct,
			(unsigned char *) cFriendOpenId.c_str(),
			(unsigned char *) cTitle.c_str(),
			(unsigned char *) cSummary.c_str(),
			(unsigned char *) cTargetUrl.c_str(),
			(unsigned char *) cImageUrl.c_str(),
			(unsigned char *) cPreviewText.c_str(),
			(unsigned char *) cGameTag.c_str());
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendToWXGameFriend
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendToWXGameFriend(
		JNIEnv * env,
		jclass,
		jstring jFriendOpenId,
		jstring jTitle,
		jstring jDescription,
		jstring jThumbMediaId,
		jstring jMessageExt,
		jstring jMediaTagName) {
	/**
	std::string friendOpenId = "oGRTijrV0l67hDGN7dstOl8Cp***";
	std::string title = " title ";
	std::string description = " description ";
	std::string thumbMediaId = " thumbMediaId ";
	std::string extinfo = " extinfo ";
	std::string mediaTagName = " mediaTagName ";

	return WGPlatform::GetInstance()->WGSendToWXGameFriend(
		(unsigned char *) friendOpenId.c_str(),
		(unsigned char *) title.c_str(),
		(unsigned char *) description.c_str(),
		(unsigned char *) thumbMediaId.c_str(),
		(unsigned char *) extinfo.c_str(),
		(unsigned char *) mediaTagName.c_str());
	 */

	 std::string cFriendOpenId = j2c(env, jFriendOpenId);
	 std::string cTitle = j2c(env, jTitle);
	 std::string cDescription = j2c(env, jDescription);
	 std::string cThumbMediaId = j2c(env, jThumbMediaId);
	 std::string cMessageExt = j2c(env, jMessageExt);
	 std::string cMediaTagName = j2c(env, jMediaTagName);

	 return WGPlatform::GetInstance()->WGSendToWXGameFriend(
	 (unsigned char *) cFriendOpenId.c_str(),
	 (unsigned char *) cTitle.c_str(),
	 (unsigned char *) cDescription.c_str(),
	 (unsigned char *) cThumbMediaId.c_str(),
	 (unsigned char *) cMessageExt.c_str(),
	 (unsigned char *) cMediaTagName.c_str());
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryQQMyInfo
 * Signature: ()Z
 */JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryQQMyInfo(
		JNIEnv * env, jclass) {
	return WGPlatform::GetInstance()->WGQueryQQMyInfo();
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryQQGameFriendsInfo
 * Signature: ()Z
 */JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryQQGameFriendsInfo(
		JNIEnv * env, jclass) {
	return WGPlatform::GetInstance()->WGQueryQQGameFriendsInfo();
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryWXMyInfo
 * Signature: ()Z
 */JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryWXMyInfo(
		JNIEnv * env, jclass) {
	return WGPlatform::GetInstance()->WGQueryWXMyInfo();
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryWXGameFriendsInfo
 * Signature: ()Z
 */JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryWXGameFriendsInfo(
		JNIEnv * env, jclass) {
	return WGPlatform::GetInstance()->WGQueryWXGameFriendsInfo();
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCheckApiSupport
 * Signature: (I)Z
 */JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCheckApiSupport(
		JNIEnv * env, jclass, jint jApiName) {
	return WGPlatform::GetInstance()->WGCheckApiSupport((eApiName) jApiName);
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGLogPlatformSDKVersion(
		JNIEnv *, jclass) {
	WGPlatform::GetInstance()->WGLogPlatformSDKVersion();
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_SetActivity(
		JNIEnv * env, jclass, jobject activity) {
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_SetActivity call end%s", "");
	mEnv = env;
	gActivity = env->NewGlobalRef(activity);
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetNoticeData
 * Signature: (Ljava/lang/String;)Ljava/util/Vector;
 */
JNIEXPORT jobject JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetNoticeData
  (JNIEnv * env, jclass, jstring jScene){
	LOGD("PlatformTest_WGGetNoticeData %s", "");
	jclass jMsgTypeClass = env->FindClass("com/tencent/msdk/notice/eMSG_NOTICETYPE");
	jmethodID jGetMsgTypeEnumMethod = env->GetStaticMethodID(jMsgTypeClass, "getEnum",
			"(I)Lcom/tencent/msdk/notice/eMSG_NOTICETYPE;");

	jclass jContentTypeClass = env->FindClass("com/tencent/msdk/notice/eMSG_CONTENTTYPE");
	jmethodID jGetContentTypeEnumMethod = env->GetStaticMethodID(jContentTypeClass, "getEnum",
			"(I)Lcom/tencent/msdk/notice/eMSG_CONTENTTYPE;");
	jmethodID jGetContentTypeValueMethod = env->GetMethodID(jContentTypeClass, "val","()I");

	jclass jScreenDirClass = env->FindClass("com/tencent/msdk/notice/eMSDK_SCREENDIR");
	jmethodID jGetScreenDirEnumMethod = env->GetStaticMethodID(jScreenDirClass, "getEnum",
			"(I)Lcom/tencent/msdk/notice/eMSDK_SCREENDIR;");
	jmethodID jGetScreenDirValueMethod = env->GetMethodID(jScreenDirClass, "val","()I");

	//调用接口，获取结果的vector
	std::string cScene = j2c(env,jScene);
	LOGD("PlatformTest_WGGetNoticeData call scene:%s", cScene.c_str());
	std::vector<NoticeInfo> noticeVector = WGPlatform::GetInstance()->WGGetNoticeData((unsigned char *) cScene.c_str());
	LOGD("PlatformTest_WGGetNoticeData noticeVector.size:%d",noticeVector.size());
	//初始化Vector相关操作
	jclass jVectorClass = env->FindClass("java/util/Vector");
	jmethodID jVectorInitMethod = env->GetMethodID(jVectorClass, "<init>", "()V");
	jmethodID jVectorSizeMethod = env->GetMethodID(jVectorClass, "size", "()I");
	jmethodID jVectorAddMethod = env->GetMethodID(jVectorClass, "add","(Ljava/lang/Object;)Z");
	//Vector 对象
	jobject jNoticeVectorObj = env->NewObject(jVectorClass, jVectorInitMethod);
	//初始化noticeinfo 对象
	jclass jNoticeInfoClass = env->FindClass("com/tencent/msdk/notice/NoticeInfo");
	jmethodID jNoticeInfoInitMethod = env->GetMethodID(jNoticeInfoClass, "<init>", "()V");
	//初始化NoticePic 对象
	jclass jNoticePicClass = env->FindClass("com/tencent/msdk/notice/NoticePic");
	jmethodID jNoticePicInitMethod = env->GetMethodID(jNoticePicClass, "<init>", "()V");
	//noticeinfo 对应字段
	jfieldID jmsg_id = env->GetFieldID(jNoticeInfoClass,"mNoticeId","Ljava/lang/String;");
	jfieldID jopen_id = env->GetFieldID(jNoticeInfoClass,"mOpenId","Ljava/lang/String;");
	jfieldID jmsg_url = env->GetFieldID(jNoticeInfoClass,"mNoticeUrl","Ljava/lang/String;");
	jfieldID jmsg_type = env->GetFieldID(jNoticeInfoClass,"mNoticeType","Lcom/tencent/msdk/notice/eMSG_NOTICETYPE;");
	jfieldID jmsg_scene = env->GetFieldID(jNoticeInfoClass,"mNoticeScene","Ljava/lang/String;");
	jfieldID jstart_time = env->GetFieldID(jNoticeInfoClass,"mNoticeStartTime","Ljava/lang/String;");
	jfieldID jend_time = env->GetFieldID(jNoticeInfoClass,"mNoticeEndTime","Ljava/lang/String;");
	jfieldID jcontent_type = env->GetFieldID(jNoticeInfoClass,"mNoticeContentType","Lcom/tencent/msdk/notice/eMSG_CONTENTTYPE;");
	jfieldID jmsg_title = env->GetFieldID(jNoticeInfoClass,"mNoticeTitle","Ljava/lang/String;");
	jfieldID jmsg_content = env->GetFieldID(jNoticeInfoClass,"mNoticeContent","Ljava/lang/String;");
	jfieldID jcontent_url = env->GetFieldID(jNoticeInfoClass,"mNoticeContentWebUrl","Ljava/lang/String;");
	jfieldID jnoticePics = env->GetFieldID(jNoticeInfoClass,"mNoticePics","Ljava/util/Vector;");

	jfieldID jScreenDir = env->GetFieldID(jNoticePicClass,"mScreenDir","Lcom/tencent/msdk/notice/eMSDK_SCREENDIR;");
	jfieldID jPicUrl = env->GetFieldID(jNoticePicClass,"mPicUrl","Ljava/lang/String;");
	jfieldID jPicHash = env->GetFieldID(jNoticePicClass,"mPicHash","Ljava/lang/String;");

	//遍历vector,转化结构体为jobject
	for(int i = 0 ; i < noticeVector.size() ; i++ ){
		jobject jNoticeInfoObj = env->NewObject(jNoticeInfoClass, jNoticeInfoInitMethod);
		env->SetObjectField(jNoticeInfoObj, jmsg_id,
				c2j(env, (unsigned char *) noticeVector[i].msg_id.c_str(),strlen((char *) noticeVector[i].msg_id.c_str())));
		env->SetObjectField(jNoticeInfoObj, jopen_id,
				c2j(env, (unsigned char *) noticeVector[i].open_id.c_str(),strlen((char *) noticeVector[i].open_id.c_str())));
		env->SetObjectField(jNoticeInfoObj, jmsg_url,
						c2j(env, (unsigned char *) noticeVector[i].msg_url.c_str(),strlen((char *) noticeVector[i].msg_url.c_str())));
		jobject jMsgTypeEnumObj = env->CallStaticObjectMethod(jMsgTypeClass, jGetMsgTypeEnumMethod, (int) noticeVector[i].msg_type);
		env->SetObjectField(jNoticeInfoObj,jmsg_type,jMsgTypeEnumObj);
		env->SetObjectField(jNoticeInfoObj, jmsg_scene,
				c2j(env, (unsigned char *) noticeVector[i].msg_scene.c_str(),strlen((char *) noticeVector[i].msg_scene.c_str())));
		env->SetObjectField(jNoticeInfoObj, jstart_time,
				c2j(env, (unsigned char *) noticeVector[i].start_time.c_str(),strlen((char *) noticeVector[i].start_time.c_str())));
		env->SetObjectField(jNoticeInfoObj, jend_time,
				c2j(env, (unsigned char *) noticeVector[i].end_time.c_str(),strlen((char *) noticeVector[i].end_time.c_str())));
		jobject jContentTypeEnumObj = env->CallStaticObjectMethod(jContentTypeClass, jGetContentTypeEnumMethod, (int) noticeVector[i].content_type);
		env->SetObjectField(jNoticeInfoObj,jcontent_type,jContentTypeEnumObj);
		env->SetObjectField(jNoticeInfoObj, jmsg_title,
				c2j(env, (unsigned char *) noticeVector[i].msg_title.c_str(),strlen((char *) noticeVector[i].msg_title.c_str())));
		env->SetObjectField(jNoticeInfoObj, jmsg_content,
				c2j(env, (unsigned char *) noticeVector[i].msg_content.c_str(),strlen((char *) noticeVector[i].msg_content.c_str())));
		env->SetObjectField(jNoticeInfoObj, jcontent_url,
						c2j(env, (unsigned char *) noticeVector[i].content_url.c_str(),strlen((char *) noticeVector[i].content_url.c_str())));
		std::vector<PicInfo> noticePicVector = noticeVector[i].picArray;
		jobject jNoticePicVectorObj = env->NewObject(jVectorClass, jVectorInitMethod);
		for(int j = 0 ; j < noticePicVector.size() ; j++ ){
			jobject jNoticePicInfoObj = env->NewObject(jNoticePicClass, jNoticePicInitMethod);
			jobject jScreenDirEnumObj = env->CallStaticObjectMethod(jScreenDirClass, jGetScreenDirEnumMethod, (int) noticePicVector[j].screenDir);
			env->SetObjectField(jNoticePicInfoObj,jScreenDir,jScreenDirEnumObj);
			env->SetObjectField(jNoticePicInfoObj, jPicUrl,
					c2j(env, (unsigned char *) noticePicVector[j].picPath.c_str(),strlen((char *) noticePicVector[j].picPath.c_str())));
			env->SetObjectField(jNoticePicInfoObj, jPicHash,
					c2j(env, (unsigned char *) noticePicVector[j].hashValue.c_str(),strlen((char *) noticePicVector[j].hashValue.c_str())));
			env->CallBooleanMethod(jNoticePicVectorObj,jVectorAddMethod,jNoticePicInfoObj);
			env->DeleteLocalRef(jNoticePicInfoObj);
			env->DeleteLocalRef(jScreenDirEnumObj);
		}
		env->SetObjectField(jNoticeInfoObj,jnoticePics,jNoticePicVectorObj);
		env->CallBooleanMethod(jNoticeVectorObj,jVectorAddMethod,jNoticeInfoObj);
		env->DeleteLocalRef(jMsgTypeEnumObj);
		env->DeleteLocalRef(jContentTypeEnumObj);
		env->DeleteLocalRef(jNoticePicVectorObj);
		env->DeleteLocalRef(jNoticeInfoObj);
	}
	LOGD("PlatformTest_WGGetNoticeData call Finished:%d",noticeVector.size());
	env->DeleteLocalRef(jMsgTypeClass);
	env->DeleteLocalRef(jContentTypeClass);
	env->DeleteLocalRef(jScreenDirClass);
	env->DeleteLocalRef(jVectorClass);
	env->DeleteLocalRef(jNoticeInfoClass);
	env->DeleteLocalRef(jNoticePicClass);
	return jNoticeVectorObj;
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGShowNotice
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGShowNotice
  (JNIEnv * env, jclass, jstring jscene){
	std::string msg_scene = j2c(env,jscene);
	WGPlatform::GetInstance()->WGShowNotice((unsigned char *) msg_scene.c_str());
 }

 /*
  * Class:     com_daemon_msdkinterface_MSDKDelegate
  * Method:    WGHideBarNotice
  * Signature: (I)
  */
 JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGHideScrollNotice
   (JNIEnv * env, jclass){
	 WGPlatform::GetInstance()->WGHideScrollNotice();
 }

 /*
  * Class:     com_daemon_msdkinterface_MSDKDelegate
  * Method:    WGOpenUrl
  * Signature: (v)
  */
 JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGOpenUrl
   (JNIEnv *env, jclass,jstring openUrl){
	 std::string s_openUrl = j2c(env, openUrl);
	 unsigned char * cOpenUrl = (unsigned char *) s_openUrl.c_str();
	 WGPlatform::GetInstance()->WGOpenUrl(cOpenUrl);
 }

 /*
  * Class:     com_daemon_msdkinterface_MSDKDelegate
  * Method:    WGOpenAmsCenter
  * Signature: (Ljava/lang/String;)V
  */
 JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGOpenAmsCenter
   (JNIEnv * env, jclass, jstring jUrl) {
	 jboolean jIsCopy;
	 unsigned char * cUrl = (unsigned char *)j2c(env, jUrl).c_str();
	 WGPlatform::GetInstance()->WGOpenAmsCenter(cUrl);
 }

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGLoginWithLocalInfo
  (JNIEnv *, jclass) {
	WGPlatform::GetInstance()->WGLoginWithLocalInfo();
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetNearbyPersonInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetNearbyPersonInfo
  (JNIEnv *, jclass) {
	LOGD("WGGetNearbyPersonInfo %s", "");
	WGPlatform::GetInstance()->WGGetNearbyPersonInfo();
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCleanLocation
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCleanLocation
  (JNIEnv *, jclass) {
	LOGD("WGCleanLocation %s", "");
	return WGPlatform::GetInstance()->WGCleanLocation();
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCleanLocation
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetLocationInfo
  (JNIEnv *, jclass) {
	LOGD("WGGetLocationInfo %s", "");
	return WGPlatform::GetInstance()->WGGetLocationInfo();
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGSendMessageToWechatGameCenter
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSendMessageToWechatGameCenter
  (JNIEnv *, jclass) {

	// 要分享的好友ID
	std::string fOpenId = "oGRTijiaT-XrbyXKozckdNHFgPyc";     // erichua23
	std::string title = "分享消息title";
	std::string content = "分享消息 content";
	std::string extMsdkInfo = "extMsdkInfo";

	LOGD("%s", "WGSendMessageToWechatGameCenter");
	// 消息类型: 链接; 按钮: 拉起游戏
	ButtonApp * btnApp = new ButtonApp("BtnName", "MessageExt");
	TypeInfoLink * link = new TypeInfoLink("typeinfo picurl", "typeinfo targetUrl");
	WGPlatform::GetInstance()->WGSendMessageToWechatGameCenter(
			(unsigned char*) fOpenId.c_str(),
			(unsigned char*) title.c_str(),
			(unsigned char*) content.c_str(),
			link,
			btnApp,
			(unsigned char*) extMsdkInfo.c_str()
			);

    // 消息类型: 图片; 按钮: 拉起游戏排行榜
    ButtonRankView * btnRankView = new ButtonRankView("BtnName1", "title", "ButtonName2",  "MessageExt");
    TypeInfoImage * img = new TypeInfoImage("http://upload.wikimedia.org/wikipedia/en/9/9c/Tencent_QQ.png", 100, 100);
    WGPlatform::GetInstance()->WGSendMessageToWechatGameCenter(
		    (unsigned char*) fOpenId.c_str(),
		    (unsigned char*) title.c_str(),
		    (unsigned char*) content.c_str(),
		    img,
		    btnRankView,
		    (unsigned char*) extMsdkInfo.c_str()
		    );

    // 消息类型: 视频; 按钮: 拉起指定页面
    ButtonWebview * btnWebview = new ButtonWebview("ButtonName", "http://www.qq.com");
    TypeInfoVideo * video = new TypeInfoVideo("http://upload.wikimedia.org/wikipedia/en/9/9c/Tencent_QQ.png",
		    100, 100, "http://121.14.123.28/vkp.tc.qq.com/x0014xix6om.p203.1.mp4?vkey=AA2DD98F586D5026B98DF7DAF3AD914D9537F8CCA1536DE461FBD3408CE784BB32D8BF18F04A8687&sha=&level=3&br=200&fmt=sd&sdtfrom=v3000&platform=10403&locid=ed4f4884-4c3b-401b-ac67-6205e363f1d5&size=10938135&ocid=186392492");
    WGPlatform::GetInstance()->WGSendMessageToWechatGameCenter(
		    (unsigned char*) fOpenId.c_str(),
		    (unsigned char*) title.c_str(),
		    (unsigned char*) content.c_str(),
		    video,
		    btnWebview,
		    (unsigned char*) extMsdkInfo.c_str()
		    );

    // 消息类型: 文本; 按钮: 拉起游戏
    TypeInfoText * text = new TypeInfoText();
    bool rtn = WGPlatform::GetInstance()->WGSendMessageToWechatGameCenter(
		    (unsigned char*) fOpenId.c_str(),
		    (unsigned char*) title.c_str(),
		    (unsigned char*) content.c_str(),
		    text,
		    btnApp,
		    (unsigned char*) extMsdkInfo.c_str()
		    );
	return rtn;
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGStartSaveUpdate
  (JNIEnv * env, jclass, jboolean isUseYYB) {
	LOGD("%s", "Java_com_daemon_msdkinterface_MSDKDelegate_WGStartCommonUpdate");
	WGPlatform::GetInstance()->WGStartSaveUpdate(isUseYYB);
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSetSaveUpdateObserver
  (JNIEnv * env, jclass) {
	LOGD("%s", "Java_com_daemon_msdkinterface_MSDKDelegate_WGSetSaveUpdateObserver");
	WGPlatform::GetInstance()->WGSetSaveUpdateObserver(&callback);
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCheckNeedUpdate
  (JNIEnv *, jclass) {
	LOGD("%s", "Java_com_daemon_msdkinterface_MSDKDelegate_WGCheckNeedUpdate");
	WGPlatform::GetInstance()->WGCheckNeedUpdate();
}

JNIEXPORT int JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCheckYYBInstalled
  (JNIEnv *, jclass) {
	LOGD("%s", "Java_com_daemon_msdkinterface_MSDKDelegate_WGCheckYYBInstalled");
	return WGPlatform::GetInstance()->WGCheckYYBInstalled();
}

JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGSetADObserver
  (JNIEnv *, jclass){
	LOGD("%s", "Java_com_daemon_msdkinterface_MSDKDelegate_WGSetADObserver");
	WGPlatform::GetInstance()->WGSetADObserver(&ad_callback);
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGShowAD
 * Signature: (Lcom/tencent/msdk/api/eADType)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGShowAD
  (JNIEnv *env, jclass, jobject jScene) {
    LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGShowAD%s", "");
	jclass jSceneClass = env->GetObjectClass(jScene);
	jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
	int cScene = env->GetIntField(jScene, jSceneField);
	env->DeleteLocalRef(jSceneClass);
	WGPlatform::GetInstance()->WGShowAD((eADType)cScene);
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGCloseAD
 * Signature: (Lcom/tencent/msdk/api/eADType)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGCloseAD
  (JNIEnv *env, jclass, jobject jScene) {
    LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGCloseAD%s", "");
	jclass jSceneClass = env->GetObjectClass(jScene);
	jfieldID jSceneField = env->GetFieldID(jSceneClass, "value", "I");
	int cScene = env->GetIntField(jScene, jSceneField);
	env->DeleteLocalRef(jSceneClass);
	WGPlatform::GetInstance()->WGCloseAD((eADType)cScene);
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGGetPlatformAPPVersion
 * Signature: (Lcom/tencent/msdk/consts/EPlatform;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGGetPlatformAPPVersion
  (JNIEnv *env, jclass, jint Platform){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGGetPlatformAPPVersion%s", "");
	const std::string version = WGPlatform::GetInstance()->WGGetPlatformAPPVersion((ePlatform) Platform);
	jstring js;
	js = env->NewStringUTF(version.c_str());
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGGetPlatformAPPVersion: %d", Platform);
	return js;
}


/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGQueryQQGroupInfo
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryQQGroupInfo
  (JNIEnv *env, jclass, jstring jUnionid, jstring jZoneid){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryQQGroupInfo%s", "");

	std::string cUnionid = j2c(env, jUnionid);
	std::string cZoneid = j2c(env, jZoneid);

	WGPlatform::GetInstance()->WGQueryQQGroupInfo((unsigned char *)cUnionid.c_str(),(unsigned char *)cZoneid.c_str());

	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGQueryQQGroupInfo%s", "");
}

/*
 * Class:     com_daemon_msdkinterface_MSDKDelegate
 * Method:    WGUnbindQQGroup
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_daemon_msdkinterface_MSDKDelegate_WGUnbindQQGroup
  (JNIEnv *env, jclass,jstring jGroupOpenid,jstring jUnionid){
	LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGUnbindQQGroup%s", "");

		std::string cGroupOpenid = j2c(env, jGroupOpenid);
		std::string cUnionid = j2c(env, jUnionid);

		WGPlatform::GetInstance()->WGUnbindQQGroup((unsigned char *)cGroupOpenid.c_str(),(unsigned char *)cUnionid.c_str());

		LOGD("Java_com_daemon_msdkinterface_MSDKDelegate_WGUnbindQQGroup%s", "");
}
