package com.daemon.nativecallback;

import android.app.Activity;


public class MSDKCallBack {
	 private static Activity mActivity;
	 public static void setActivity(Activity activity){
		 mActivity = activity;
	 }
     public static void changeToWelcomeScene(){MSDKNativeCallBack.changeToWelcomeScene();}
     public static void changeToLoginScene(){MSDKNativeCallBack.changeToLoginScene();}
}
