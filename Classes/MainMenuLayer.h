#include "MainMenuScene.h"
#include "BallGameScene.h"

#ifndef __MAINMENULAYER_H__
#define __MAINMENULAYER_H__
USING_NS_CC;

class MainMenuLayer : public cocos2d::Layer
{
public:

	/** Init the layer */
	bool init();
	CREATE_FUNC(MainMenuLayer);

protected:

	/** Callback func when touch the start game button */
	void startGameEvent(Ref* sender);

	/** Callback func when touch the exit game button */
	void exitGameEvent(Ref* sender);
};

#endif

