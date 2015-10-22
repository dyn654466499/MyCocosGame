/*
 * LoginScene.h
 *
 *  Created on: 2015-10-12
 *      Author: Administrator
 */

#ifndef LOGINSCENE_H_
#define LOGINSCENE_H_

#include "cocos2d.h"
#include "WelcomeScene.h"

using namespace cocos2d;

class LoginScene : public WelcomeScene
{
public:
    static Scene* scene();
};

class LoginLayer : public WelcomeLayer
{
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LoginLayer);

    //RepeatForever* buildParticleMovePath(float controlX, float controlY, float w, bool isClockwise);

};

#endif /* LOGINSCENE_H_ */
