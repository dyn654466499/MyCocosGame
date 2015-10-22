#include "LoginScene.h"
#include "WelcomeScene.h"
#include "plane.h"
#include "platform/android/jni/JniHelper.h"

USING_NS_CC;


Scene* LoginScene::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LoginLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool LoginLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto bgSprite = Sprite::create("index_bg.jpg");
    bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bgSprite, 0);

	auto titleSprite= Sprite::create("LOGO.png");
	titleSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titleSprite->getContentSize().height / 2 - 160));
	this->addChild(titleSprite);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pig.plist");

	auto planeSprite = cocoauto::Plane::create();
	planeSprite->setScale(2.0f);
	planeSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + titleSprite->getPositionY() - titleSprite->getContentSize().height - planeSprite->getContentSize().height / 2 - 100));
	this->addChild(planeSprite);
	//C++11֮lambda���ʽ
	auto qqLoginMenuItem = MenuItemImage::create("","",[](Object *sender) {
				//Scene *scene = WelcomeScene::scene();
				//Director::getInstance()->replaceScene(scene);
		   JniMethodInfo info;
		  //getStaticMethodInfo判断java定义的静态函数是否存在，返回bool
		  bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/AppActivity","msdkQQLogin","()V");
		  if(ret)
		  {
		    log("Call void msdkQQLogin() successfully");
		    //传入类ID和方法ID，小心方法名写错，第一个字母是大写
		    info.env->CallStaticVoidMethod(info.classID,info.methodID);
		  }else{
			  log("Call void msdkQQLogin() fail");
		  }
		});

	auto wxLoginMenuItem = MenuItemImage::create("","",[](Object *sender) {
					//Scene *scene = WelcomeScene::scene();
					//Director::getInstance()->replaceScene(scene);
			   JniMethodInfo info;
			  //getStaticMethodInfo判断java定义的静态函数是否存在，返回bool
			  bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/AppActivity","msdkWXLogin","()V");
			  if(ret)
			  {
			    //传入类ID和方法ID，小心方法名写错，第一个字母是大写
			    info.env->CallStaticVoidMethod(info.classID,info.methodID);
			    log("Call void msdkWXLogin() successfully");
			  }else{
				  log("Call void msdkWXLogin() fail");
			  }
			});

	//---------------------- QQ Login -----------------------------
	//目前不明白，要qqLoginMenuItem->setNormalSpriteFrame(qqLoginSprite->getDisplayFrame())才能起到点击效果;还要注意的是label要最后add才能显示文字（层级问题）
	qqLoginMenuItem->setPosition(Point(origin.x + visibleSize.width * 3 / 4 - 10, origin.y + 230));

	Sprite* qqLoginSprite = Sprite::create("login.png",CCRect(0, 0, 235, 65));
	qqLoginSprite->setPosition(qqLoginMenuItem->getPosition());
	this->addChild(qqLoginSprite);

	qqLoginMenuItem->setNormalSpriteFrame(qqLoginSprite->getDisplayFrame());
	Menu* qqLoginMenu = Menu::create(qqLoginMenuItem, NULL);
	qqLoginMenu->setPosition(Point::ZERO);
	this->addChild(qqLoginMenu);

	LabelTTF *qqLoginLabel = LabelTTF::create("和QQ好友玩", "Marker Felt", 24);
	qqLoginLabel->setPosition(Point(qqLoginSprite->getPositionX() + 8, qqLoginSprite->getPositionY()));
	this->addChild(qqLoginLabel);


	//---------------------- WX Login --------------------------------
	wxLoginMenuItem->setPosition(Point(origin.x + visibleSize.width / 3, origin.y + 230));

	Sprite* wxLoginSprite = Sprite::create("login.png",CCRect(230, 0, 245, 65));
	wxLoginSprite->setPosition(wxLoginMenuItem->getPosition());
	this->addChild(wxLoginSprite);

	wxLoginMenuItem->setNormalSpriteFrame(wxLoginSprite->getDisplayFrame());
	Menu* wxLoginMenu = Menu::create(wxLoginMenuItem, NULL);
	wxLoginMenu->setPosition(Point::ZERO);
	this->addChild(wxLoginMenu);

	LabelTTF *wxLoginLabel = LabelTTF::create("和微信好友玩", "Marker Felt", 23);
	wxLoginLabel->setPosition(Point(wxLoginSprite->getPositionX() + 16, wxLoginSprite->getPositionY()));
	this->addChild(wxLoginLabel);

    return true;
}

//RepeatForever* LoginLayer::buildParticleMovePath(float controlX, float controlY, float w,  bool isClockwise)
//{
//	int flag = isClockwise ? -1 : 1;
//
//	ccBezierConfig bezier1;
//	bezier1.controlPoint_1 = Point(flag * controlX, 0);
//	bezier1.controlPoint_2 = Point(flag * controlX, (-flag) * controlY);
//	bezier1.endPosition = Point(0, (-flag) * controlY);
//
//	auto bezierBy1 = BezierBy::create(0.8f, bezier1);
//
//	float t_w = w;
//	if(!isClockwise) {
//		t_w = -w;
//	}
//	auto move1 = MoveBy::create(1.0f, Point(t_w, 0));
//
//	ccBezierConfig bezier2;
//	bezier2.controlPoint_1 = Point((-flag) * controlX, 0);
//	bezier2.controlPoint_2 = Point((-flag) * controlX, flag * controlY);
//	bezier2.endPosition = Point(0, flag * controlY);
//
//	auto bezierBy2 = BezierBy::create(0.8f, bezier2);
//	auto move2 = MoveBy::create(1.0f, Point(-t_w, 0));
//	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
//	return path;
//}
