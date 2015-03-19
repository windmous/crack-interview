#include "CandidateBall.h"

bool CandidateBallList::init()
{
	auto winSize = Director::getInstance()->getWinSize();
	setTouchEnabled(true);

	setTotalAmountCandidateBall(3);

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
				if (candidateBall->getBallState() == CandidateBall::Available)
					candidateBall->setToChosen();

				log("MessageHUD: %d th candidate contain %f, %f", ballIdx, p.x, p.y);

				// TODO: CHANGE THE STATE

			}
			else  // Untouched
			{
				// Recover to normal resource
				if (candidateBall->getBallState() == CandidateBall::Available)
					candidateBall->setToNormal();
				log("MessageHUD: %d th candidate NOT contain %f, %f", ballIdx, p.x, p.y);
			}

		}
		return touchFlag;
	};

	//Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
	this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
	return true;
}

bool CandidateBallList::addCandidateBall(const std::string normalFilePath, 
	const std::string chosenFilePath, 
	const std::string unavailFilePath)
{
	// Should not exceed the number of total ball
	if (getUsedCandidateBall() + 1 >= getTotalAmountCandidateBall())
		return false;

	auto winSize = Director::getInstance()->getWinSize();

	// Add the ball resource to the path 
	auto candidateBall = CandidateBall::create(normalFilePath, chosenFilePath, unavailFilePath);

	// Set the position of candidate ball
	candidateBall->setAnchorPoint(Point(0.0f, 0.0f));
	candidateBall->setPosition(Point(nextXPos, winSize.height - candidateBall->getSize().height));
	candidateBallList.pushBack(candidateBall);
	addChild(candidateBall, 30);
	log("MessageHUD: set candidate ball at position: %f, %f", candidateBall->getPosition().x, candidateBall->getPosition().y);

	// Update the nextXPos
	nextXPos += candidateBall->getSize().width + gap;

	// Update the usedCandidateBall
	++usedCandidateBall;

	return true;
}

void CandidateBallList::clearCandidateBall()
{
	for (auto candidateBall : candidateBallList)
		candidateBall->release();
	candidateBallList.clear();
	usedCandidateBall = 0;
}