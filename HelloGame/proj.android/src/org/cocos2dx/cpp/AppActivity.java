/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.view.KeyEvent;

import com.daemon.msdkinterface.MSDKDelegate;
import com.daemon.nativecallback.MSDKCallBack;
import com.tencent.msdk.api.MsdkBaseInfo;
import com.tencent.msdk.api.WGPlatform;
import com.tencent.msdk.api.WGQZonePermissions;
import com.tencent.msdk.consts.EPlatform;
import com.tencent.msdk.tools.Logger;

public class AppActivity extends Cocos2dxActivity {
	static {
		System.loadLibrary("MSDK"); 
	}
	public static native void changeToWelcomeScene();
	public static void test(){
		changeToWelcomeScene();
    }
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		if (WGPlatform.IsDifferentActivity(this)) {
			Logger.d("Warning!Reduplicate game activity was detected.Activity will finish immediately.");
			this.finish();
			return;
		}
		
		MSDKCallBack.setActivity(this);
		
		
		// TODO GAME 初始化MSDK
		/***********************************************************
		 * TODO GAME 接入必须要看， baseInfo值因游戏而异，填写请注意以下说明: baseInfo值游戏填写错误将导致
		 * QQ、微信的分享，登录失败 ，切记 ！！！ 只接单一平台的游戏请勿随意填写其余平台的信息，否则会导致公告获取失败 offerId
		 * 为必填，一般为手QAppId
		 ***********************************************************/
		MsdkBaseInfo baseInfo = new MsdkBaseInfo();
		baseInfo.qqAppId = "100703379";
		baseInfo.qqAppKey = "4578e54fb3a1bd18e0681bc1c734514e";
		baseInfo.wxAppId = "wxcde873f99466f74a";
		baseInfo.wxAppKey = "bc0994f30c0a12a9908e353cf05d4dea";
		// 订阅型测试用offerId
		baseInfo.offerId = "100703379";
		// TODO GAME 自2.7.1a开始游戏可在初始化msdk时动态设置版本号，灯塔和bugly的版本号由msdk统一设置
		// 1、版本号组成 = versionName + versionCode
		// 2、游戏如果不赋值给appVersionName（或者填为""）和appVersionCode(或者填为-1)，
		// msdk默认读取AndroidManifest.xml中android:versionCode="51"及android:versionName="2.7.1"
		// 3、游戏如果在此传入了appVersionName（非空）和appVersionCode（正整数）如下，则灯塔和bugly上获取的版本号为2.7.1.271
		//baseInfo.appVersionName = "2.7.1";
		//baseInfo.appVersionCode = 271;

		// 注意：传入Initialized的activity即this，在游戏运行期间不能被销毁，否则会产生Crash
		WGPlatform.Initialized(this, baseInfo);
		// TODO GAME 处理游戏被拉起的情况
		// launchActivity的onCreat()和onNewIntent()中必须调用
		// WGPlatform.handleCallback()。否则会造成微信登录无回调
		if (WGPlatform.wakeUpFromHall(this.getIntent())) {
			// 拉起平台为大厅
			Logger.d("LoginPlatform is Hall");
			Logger.d(this.getIntent());
		} else {
			// 拉起平台不是大厅
			Logger.d("LoginPlatform is not Hall");
			Logger.d(this.getIntent());
			WGPlatform.handleCallback(this.getIntent());
		}
		// 设置拉起QQ时候需要用户授权的项
		WGPlatform.WGSetPermission(WGQZonePermissions.eOPEN_ALL);
		// cpp层 回调设置
		MSDKDelegate.setObserver(true);
		MSDKDelegate.WGSetSaveUpdateObserver();
		MSDKDelegate.WGLogPlatformSDKVersion();
		MSDKDelegate.SetActivity(this);
		
		
	}

	private static void msdkQQLogin(){
		WGPlatform.WGLogin(EPlatform.ePlatform_QQ);
	}
	private static void msdkWXLogin(){
		WGPlatform.WGLogin(EPlatform.ePlatform_Weixin);
	}
	private static void msdkLogout(){
		if(WGPlatform.WGLogout()){
			MSDKCallBack.changeToLoginScene();
		}
	}
	
	// TODO GAME 游戏需要集成此方法并调用WGPlatform.onRestart()
	@Override
	protected void onRestart() {
		super.onRestart();
		WGPlatform.onRestart();
	}

	// TODO GAME 游戏需要集成此方法并调用WGPlatform.onResume()
	@Override
	protected void onResume() {
		super.onResume();
		WGPlatform.onResume();

		// TODO GAME 模拟游戏自动登录，这里需要游戏添加加载动画
		// WGLogin是一个异步接口, 传入ePlatform_None则调用本地票据验证票据是否有效
		// 如果从未登录过，则会立即在onLoginNotify中返回flag为eFlag_Local_Invalid，此时应该拉起授权界面
		// 建议在此时机调用WGLogin,它应该在handlecallback之后进行调用。
	}

	// TODO GAME 游戏需要集成此方法并调用WGPlatform.onPause()
	@Override
	protected void onPause() {
		super.onPause();
		WGPlatform.onPause();
	}

	// TODO GAME 游戏需要集成此方法并调用WGPlatform.onStop()
	@Override
	protected void onStop() {
		super.onStop();
		WGPlatform.onStop();
	}

	// TODO GAME 游戏需要集成此方法并调用WGPlatform.onDestory()
	@Override
	protected void onDestroy() {
		super.onDestroy();
		WGPlatform.onDestory(this);
		Logger.d("onDestroy");
	}

	// TODO GAME 在onActivityResult中需要调用WGPlatform.onActivityResult
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		WGPlatform.onActivityResult(requestCode, resultCode, data);
		Logger.d("onActivityResult");
	}

	// TODO GAME 在onNewIntent中需要调用handleCallback将平台带来的数据交给MSDK处理
	@Override
	protected void onNewIntent(Intent intent) {
		Logger.d("onNewIntent");
		super.onNewIntent(intent);

		// TODO GAME 处理游戏被拉起的情况
		// launchActivity的onCreat()和onNewIntent()中必须调用
		// WGPlatform.handleCallback()。否则会造成微信登录无回调
		if (WGPlatform.wakeUpFromHall(intent)) {
			Logger.d("LoginPlatform is Hall");
			Logger.d(intent);
		} else {
			Logger.d("LoginPlatform is not Hall");
			Logger.d(intent);
			WGPlatform.handleCallback(intent);
		}
	}


	@Override
	public boolean onKeyDown(final int pKeyCode, final KeyEvent pKeyEvent) {
		switch (pKeyCode) {
		case KeyEvent.KEYCODE_BACK:
			new AlertDialog.Builder(getContext()).setCancelable(false)
					.setTitle("确定要退出游戏吗？")
					.setPositiveButton("确定", new OnClickListener() {

						@Override
						public void onClick(DialogInterface dialog, int which) {
							// TODO Auto-generated method stub
							dialog.dismiss();
							System.exit(0);
						}
					}).setNegativeButton("取消", new OnClickListener() {

						@Override
						public void onClick(DialogInterface dialog, int which) {
							// TODO Auto-generated method stub
							dialog.dismiss();
						}
					}).create().show();
		case KeyEvent.KEYCODE_MENU:
		case KeyEvent.KEYCODE_DPAD_LEFT:
		case KeyEvent.KEYCODE_DPAD_RIGHT:
		case KeyEvent.KEYCODE_DPAD_UP:
		case KeyEvent.KEYCODE_DPAD_DOWN:
		case KeyEvent.KEYCODE_ENTER:
		case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
		case KeyEvent.KEYCODE_DPAD_CENTER:
		default:
			return super.onKeyDown(pKeyCode, pKeyEvent);
		}
	}

	private void showDialog() {
		new AlertDialog.Builder(getContext()).setCancelable(false)
				.setTitle("QQ登录成功")
				.setPositiveButton("确定", new OnClickListener() {

					@Override
					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub
						dialog.dismiss();
					}
				}).setNegativeButton("取消", new OnClickListener() {

					@Override
					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub
						dialog.dismiss();
					}
				}).create().show();
	}
}
