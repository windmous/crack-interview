#include "BallGameLayer.h"


bool BallGameLayer::init()
{
	Layer::init();

	auto winSize = Director::getInstance()->getWinSize();
	setTouchEnabled(true);

	// Set the background
	auto ui_background = Sprite::create("BallGameScene/ui_background.png");
	ui_background->setAnchorPoint(Point(0.0f, 0.0f));
	ui_background->setPosition(Point(0.0f, 0.0f));
	addChild(ui_background, 0);
	
	// Set the candidate ball
	//auto ballCandidate_01 = BallCandidate::createWithType(BallCandidate::BallActorType::BType1);
	//ballCandidate_01->setAnchorPoint(Point(0.0f, 1.0f));
	//ballCandidate_01->setPosition(Point(0.0f, winSize.height));
	//((Type01_BallCandidate*)ballCandidate_01)->addEvents();
	//addChild(ballCandidate_01, 10);

	// Set the message hub above the scene
	auto messageHUD = MessageHUD::create();
	messageHUD->setAnchorPoint(Point(0.0f, 0.0f));
	messageHUD->setPosition(Point(0.0f, winSize.height - 106 - 20));
	log("Set message HUB position : %f, %f", messageHUD->getPosition().x, messageHUD->getPosition().y );
	addChild(messageHUD, 10);

	// Add candidate ball
	messageHUD->addCandidateBall("BallGameScene/ball_01.png", "BallGameScene/ball_01_chosen.png");
	messageHUD->addCandidateBall("BallGameScene/ball_02.png", "BallGameScene/ball_02_chosen.png");

	return true;
}