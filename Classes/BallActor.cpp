#include "BallActor.h"

BallCandidate* BallCandidate::createWithType(BallActorType ballType)
{
	BallCandidate* ballC;

	switch (ballType) 
	{
	case BallActorType::BType1:

		ballC = (Type01_BallCandidate*)Type01_BallCandidate::create("BallGameScene/ball_01.png");
		//ballC->addEvents();
		break;

	case BallActorType::BType2:

		ballC = (Type02_BallCandidate*)Type02_BallCandidate::create("BallGameScene/ball_02.png");
		//ballC->addEvents();
		break;

	default:
		break;
	}

	return ballC;
}

bool Type01_BallCandidate::init()
{
	//setTexture("ball_01.png");
	return true;
}

void Type01_BallCandidate::addEvents()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		Vec2 p = touch->getLocation();
		Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{
			this->setTexture("BallGameScene/ball_01_chosen.png");
			log("TOUCHED!!!");
			return true;
		}
		return false;
	};

	listener->onTouchEnded = [](Touch* touch, Event* event)
	{
		
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

bool Type02_BallCandidate::init()
{
	//setTexture("ball_02.png");
	return true;
}

void Type02_BallCandidate::addEvents()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		Vec2 p = touch->getLocation();
		Rect rect = this->getBoundingBox();
		log("touch began");

		if (rect.containsPoint(p))
		{
			this->setTexture("BallGameScene/ball_02_chosen.png");

			return true;
		}
		return false;
	};

	listener->onTouchEnded = [](Touch* touch, Event* event)
	{

	};
}