#ifndef __CANDIDATE_BALL__
#define __CANDIDATE_BALL__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include <string>
#include <vector>
USING_NS_CC;

class CandidateBall : public ui::ImageView
{
public:

	static CandidateBall* create(const std::string normalFilePath,
		const std::string chosenFilePath,
		const std::string unavailFilePath)
	{
		CandidateBall* widget = new (std::nothrow) CandidateBall();
		if (widget && widget->init(normalFilePath, chosenFilePath, unavailFilePath))
		{
			widget->autorelease();
			return widget;
		}
		CC_SAFE_DELETE(widget);
		return nullptr;
	}

	bool init(const std::string normalFilePath,
		const std::string chosenFilePath,
		const std::string unavailFilePath) 
	{
		if (!Widget::init())
			return false;

		this->normalBallPath = normalFilePath;
		this->chosenBallPath = chosenFilePath;
		this->unavailBallPath = unavailFilePath;
		state = Available;
		this->loadTexture(this->normalBallPath);
		return true;
	}

	enum BallState {
		Available,
		Unavailable,
	};

	// Set/get ball state
	inline BallState getBallState() { return state; }
	inline void setBallState(BallState s) { state = s; }
	
	// Set ball to normal state
	bool setToNormal() { 
		if (getBallState() == BallState::Unavailable)
			return false;
		this->loadTexture(normalBallPath); 
		return true;
	}
	bool setToChosen() {
		if (getBallState() == BallState::Unavailable)
			return false;
		this->loadTexture(chosenBallPath);
		return true;
	}
	bool setToUnavail() {
		this->loadTexture(unavailBallPath);
		setBallState(BallState::Unavailable);
		return true;
	}

private:

	BallState state;
	std::string normalBallPath;
	std::string chosenBallPath;
	std::string unavailBallPath;
};

class CandidateBallList : public Layer
{
public:

	bool init();
	CREATE_FUNC(CandidateBallList);

	Vector<CandidateBall*> candidateBallList;

	// Add candidate ball 
	bool addCandidateBall(const std::string normalFilePath, 
		const std::string chosenFilePath, 
		const std::string unavailFilePath);

	// Clear candidate ball 
	void clearCandidateBall();

	// Get total available candidate ball
	inline int getTotalAmountCandidateBall(){ return totalAmountCandidateBall; }

	// Set total available candidate ball 
	inline void setTotalAmountCandidateBall(int n){ totalAmountCandidateBall = n; }

	// Get used candidate ball
	inline int getUsedCandidateBall() { return usedCandidateBall; }

private:

	// Total number of candidate ball
	int totalAmountCandidateBall;

	// Used number of candidate ball
	int usedCandidateBall;

	// Next x position to place candidate ball
	float nextXPos;

	// Gap between two candidate ball
	float gap;
};

#endif