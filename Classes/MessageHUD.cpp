#include "MessageHUD.h"

bool MessageHUD::init()
{
	auto winSize = Director::getInstance()->getWinSize();

	// Set background
	auto background = Sprite::create("BallGameScene/hubBackground.png");
	background->setAnchorPoint(Point(0.0f, 0.0f));
	background->setPosition(Point(0.0f, 0.0f));
	log("Set message HUB background position : %f, %f", background->getPosition().x, background->getPosition().y);
	addChild(background, 0);

	// Set default number of candidate ball
	setNumCandidateBall(3);

	// Set the gap of two candidate ball
	gap = 20.0;

	// Set the next x position to place candidate ball
	nextXPos = gap;

	// Add touch listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		Vec2 p = touch->getLocation();
		bool touchFlag = false;

		// Traverse all candidate ball, check if touched
		for (auto candidateBall : candidateBallList) {
			Rect rect = candidateBall->getBoundingBox();
			log("RECT %f, %f", rect.getMidX(), rect.getMidY());
			if (rect.containsPoint(p))
			{
				touchFlag = true;
				// Change the state and resource
				candidateBall->loadTexture("BallGameScene/ball_02_chosen.png");
				log("CONTAIN %f, %f", p.x, p.y);
				
			}
			else 
			{
				// Recover the resource
				candidateBall->loadTexture("BallGameScene/ball_02.png");

				log("NOT CONTAIN %f, %f", p.x, p.y);
			}
			
		}
		return touchFlag;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);

	return true;
}

bool MessageHUD::addCandidateBall(std::string normalFilePath, std::string chosenFilePath)
{
	// Should not exceed the number of total ball
	if (getUsedCandidateBall() + 1 >= getNumCandidateBall())
		return false;

	auto winSize = Director::getInstance()->getWinSize();

	// Add the ball resource to the path 
	// TODO: how to load these resource only once?
	//normalBallPathList.pushBack(normalFilePath);
	//chosenBallPathList.pushBack(chosenFilePath);

	// Add the candidate ball (normal) to the HUD layer
	auto candidateBall = ui::ImageView::create();
	candidateBall->loadTexture(normalFilePath);

	// Set the position
	candidateBall->setAnchorPoint(Point(0.0f, 0.0f));
	candidateBall->setPosition(Point(nextXPos, 0));
	log("Set candidate ball position : %f, %f", candidateBall->getPosition().x, candidateBall->getPosition().y);
	candidateBallList.pushBack(candidateBall);
	addChild(candidateBall, 10);

	// Update the nextXPos
	nextXPos += candidateBall->getSize().width + gap;

	return true;
}

void MessageHUD::clearCandidateBall()
{

}