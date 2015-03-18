#ifndef __BALLGAMESCENE_H__
#define __BALLGAMESCENE_H__

#include "cocos2d.h"
#include "BallGameLayer.h"

USING_NS_CC;

class BallGameScene : public Scene
{
public:
	
	bool init();

	CREATE_FUNC(BallGameScene);
};

#endif