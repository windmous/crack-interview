#ifndef __MESSAGEHUD_H__
#define __MESSAGEHUD_H__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include "CandidateBall.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>

USING_NS_CC;

class MessageHUD : public Layer
{
public:

	bool init();
	CREATE_FUNC(MessageHUD);

	CandidateBallList* candidateBallList;

	// Add new candidate ball, return NULL if number of balls exceeds the threshold
	CandidateBall* addCandidateBall(const std::string normalFilePath,
		const std::string chosenFilePath,
		const std::string unavailFilePath);

	// 
	ui::TextAtlas* hpLabel;

	//void updateHP();

private:

	// Total health point
	int totalHP;

};

#endif