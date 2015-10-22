#ifndef SUPER_BULLET_H_
#define SUPER_BULLET_H_

#include <cocos2d.h>
using namespace cocos2d;
typedef enum
{
	DIR_UP = 0,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
}BULLET_DIR;

class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();

	virtual bool init();

	CC_SYNTHESIZE_READONLY(int, _speed_x, _speed_x);
	CC_SYNTHESIZE_READONLY(int, _speed_y, _speed_y);

	CC_SYNTHESIZE(bool, _is_live, _is_live);

	CREATE_FUNC(Bullet);

};

#endif
