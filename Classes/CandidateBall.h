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
		const std::string unavailFilePath);

	bool init(const std::string normalFilePath,
		const std::string chosenFilePath,
		const std::string unavailFilePath);

	enum BallState {
		Available,
		Unavailable,
	};

	// Get ball state
	BallState getBallState();
	
	// Set ball to normal state
	bool setToNormal();
	bool setToChosen();
	bool setToUnavail();

private:

	BallState state;
	std::string normalBallPath;
	std::string chosenBallPath;
	std::string unavailBallPath;

	// Set ball state, called from setToXX functions
	void setBallState(BallState s);
};

class CandidateBallList : public Layer
{
public:

	bool init();
	CREATE_FUNC(CandidateBallList);

	Vector<CandidateBall*> candidateBallList;

	// Add candidate ball 
	CandidateBall* addCandidateBall(const std::string normalFilePath, 
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