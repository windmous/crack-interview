#ifndef __MESSAGEHUD_H__
#define __MESSAGEHUD_H__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include <string>

USING_NS_CC;

class MessageHUD : public Layer
{
public:

	bool init();
	CREATE_FUNC(MessageHUD);


	Vector<ui::ImageView *> candidateBallList;

	// Add candidate ball 
	bool addCandidateBall(std::string normalFilePath, std::string chosenFilePath);

	// Clear candidate ball 
	void clearCandidateBall();

	// Get total available candidate ball
	inline int getNumCandidateBall(){ return numCandidateBall; }

	// Set total available candidate ball 
	inline void setNumCandidateBall(int n){ numCandidateBall = n; }

	// Get used candidate ball
	inline int getUsedCandidateBall() { return usedCandidateBall; }

private:

	// Total health point
	int totalHP;

	// Total number of candidate ball
	int numCandidateBall;

	// Used number of candidate ball
	int usedCandidateBall;

	// Next x position to place candidate ball
	float nextXPos;

	// Gap between two candidate ball
	float gap;

	// Normal candidate ball path
	//Vector<std::string> normalBallPathList;

	// Chosen candidate ball path
	//Vector<std::string> chosenBallPathList;

};

#endif