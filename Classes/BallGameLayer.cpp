#include "BallGameLayer.h"


bool BallGameLayer::init()
{
	Layer::init();

	auto winSize = Director::getInstance()->getWinSize();

	// Set the background
	auto ui_background = Sprite::create("BallGameScene/ui_background.png");
	ui_background->setAnchorPoint(Point(0.0f, 0.0f));
	ui_background->setPosition(Point(0.0f, 0.0f));
	addChild(ui_background, 0);

	// Set the message hub above the scene
	auto messageHUD = MessageHUD::create();
	messageHUD->setAnchorPoint(Point(0.0f, 0.0f));
	messageHUD->setPosition(Point(0.0f, 0.0f));
	addChild(messageHUD, 10);

	// Add candidate ball
	auto cdBall1 = messageHUD->addCandidateBall("BallGameScene/ball_01.png", "BallGameScene/ball_01_chosen.png", "BallGameScene/ball_unavail.png");
	cdBall1->setToUnavail();
	messageHUD->addCandidateBall("BallGameScene/ball_02.png", "BallGameScene/ball_02_chosen.png", "BallGameScene/ball_unavail.png");
	messageHUD->addCandidateBall("BallGameScene/ball_03.png", "BallGameScene/ball_03_chosen.png", "BallGameScene/ball_unavail.png");


	return true;
}