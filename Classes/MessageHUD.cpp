#include "MessageHUD.h"

bool MessageHUD::init()
{
	auto winSize = Director::getInstance()->getWinSize();

	// Set background
	//auto background = Sprite::create("BallGameScene/hudBackground.png");
	//background->setAnchorPoint(Point(0.0f, 1.0f));
	//background->setPosition(Point(0.0f, winSize.height));
	//addChild(background, 0);
	//log("MessageHUD: set background, anchor point: %f, %f, position: %f, %f", 
	//	background->getAnchorPoint().x, background->getAnchorPoint().y, 
	//	background->getPosition().x, background->getPosition().y);

	// Set candidateBallList
	candidateBallList = CandidateBallList::create();
	candidateBallList->setAnchorPoint(Point(0.0f, 0.0f));
	candidateBallList->setPosition(Point(0.0f, winSize.height));
	addChild(candidateBallList, 10);

	return true;
}

bool MessageHUD::addCandidateBall(const std::string normalFilePath,
	const std::string chosenFilePath,
	const std::string unavailFilePath)
{
	return candidateBallList->addCandidateBall(normalFilePath, chosenFilePath, unavailFilePath);
}