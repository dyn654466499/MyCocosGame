 /*
 * com_daemon_nativecallback_MSDKCallBack.cpp
 *
 *  Created on: 2015-10-13
 *      Author: Administrator
 */
#include "com_daemon_nativecallback_MSDKNativeCallBack.h"
USING_NS_CC;

JNIEXPORT void JNICALL Java_com_daemon_nativecallback_MSDKNativeCallBack_changeToWelcomeScene
  (JNIEnv *, jclass){
	 Director::getInstance()->getScheduler()->performFunctionInCocosThread([&]()
	    {
		    Scene* scene = WelcomeScene::scene();
		    Director::getInstance()->replaceScene(scene);
	    });
}
