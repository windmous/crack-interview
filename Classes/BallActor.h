#ifndef __BALLACTOR_H__
#define __BALLACTOR_H__

#include "cocos2d.h"
#include <string>
USING_NS_CC;

class BallActor : public cocos2d::Sprite
{
public:

	enum class BallActorType
	{
		BType1,
		BType2,
	};

	BallActorType ballType;

};

class BallOnBoard : public BallActor
{
public:

	int HP;

};


// Base class of ball candidate
class BallCandidate : public Sprite
{
public:
	enum class BallActorType
	{
		BType1,
		BType2,
	};

	static BallCandidate* createWithType(BallActorType ballType);
	void addEvents();
};

// Type 01 of ball candidate
class Type01_BallCandidate : public BallCandidate
{
public:
	
	bool init();

	//CREATE_FUNC(Type01_BallCandidate);
	void addEvents();
};

// Type 02 of ball candidate
class Type02_BallCandidate : public BallCandidate
{
public:

	bool init();

	//CREATE_FUNC(Type02_BallCandidate);
	void addEvents();
};

#endif