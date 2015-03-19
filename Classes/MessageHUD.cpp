#include "MessageHUD.h"

bool MessageHUD::init()
{
	auto winSize = Director::getInstance()->getWinSize();

	// Set background
	auto background = Sprite::create("BallGameScene/hudBackground.png");
	background->setAnchorPoint(Point(0.0f, 1.0f));
	background->setPosition(Point(0.0f, winSize.height));
	addChild(background, 0);
	log("MessageHUD: set background, anchor point: %f, %f, position: %f, %f", 
		background->getAnchorPoint().x, background->getAnchorPoint().y, 
		background->getPosition().x, background->getPosition().y);

	// Set default maximum number of candidate ball
	setNumCandidateBall(3);

	// Set the distance gap between two candidate balls
	gap = 20.0;

	// Set the next x position to place candidate ball
	nextXPos = gap;

	// Add touch listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		Vec2 p = touch->getLocation();
		bool touchFlag = false;	// Set to true if any ball is touched, false if no ball is touched

		// Traverse all candidate ball, check if touched
		for (int ballIdx = 0; ballIdx < candidateBallList.size(); ++ballIdx)
		{
			// Fetch the bounding box of each candidate ball
			auto candidateBall = candidateBallList.at(ballIdx);
			Rect rect = candidateBall->getBoundingBox();
			log("MessageHUD: touch event check for candidate ball with rect center: %f, %f", rect.getMidX(), rect.getMidY());

			if (rect.containsPoint(p))	// Touched
			{
				touchFlag = true;
				// Change to chosen resource
				candidateBall->loadTexture(chosenBallPathList.at(ballIdx));
				log("MessageHUD: %d th candidate contain %f, %f", ballIdx, p.x, p.y);
				
				// TODO: CHANGE THE STATE

			}
			else  // Untouched
			{
				// Recover to normal resource
				candidateBall->loadTexture(normalBallPathList.at(ballIdx));
				log("MessageHUD: %d th candidate NOT contain %f, %f", ballIdx, p.x, p.y);
			}
			
		}
		return touchFlag;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);

	return true;
}

bool MessageHUD::addCandidateBall(const std::string normalFilePath, const std::string chosenFilePath)
{
	// Should not exceed the number of total ball
	if (getUsedCandidateBall() + 1 >= getNumCandidateBall())
		return false;

	auto winSize = Director::getInstance()->getWinSize();

	// Add the ball resource to the path 
	// TODO: how to load these resource only once?
	normalBallPathList.push_back(normalFilePath);
	chosenBallPathList.push_back(chosenFilePath);

	// Add the candidate ball (normal) to the HUD layer
	auto candidateBall = ui::ImageView::create();
	candidateBall->loadTexture(normalFilePath);

	// Set the position
	candidateBall->setAnchorPoint(Point(0.0f, 1.0f));
	candidateBall->setPosition(Point(nextXPos, winSize.height));
	candidateBallList.pushBack(candidateBall);
	addChild(candidateBall, 10);
	log("MessageHUD: set candidate ball at position: %f, %f", candidateBall->getPosition().x, candidateBall->getPosition().y);

	// Update the nextXPos
	nextXPos += candidateBall->getSize().width + gap;

	// Update the usedCandidateBall
	++usedCandidateBall;

	return true;
}

void MessageHUD::clearCandidateBall()
{
	normalBallPathList.clear();
	chosenBallPathList.clear();
	candidateBallList.clear();
	usedCandidateBall = 0;

}