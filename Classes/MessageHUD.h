#ifndef __MESSAGEHUD_H__
#define __MESSAGEHUD_H__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include "CandidateBall.h"
#include <string>
#include <vector>

USING_NS_CC;

class MessageHUD : public Layer
{
public:

	bool init();
	CREATE_FUNC(MessageHUD);

	CandidateBallList* candidateBallList;

	// Add new candidate ball, fail if number of balls exceeds the threshold
	bool addCandidateBall(const std::string normalFilePath,
		const std::string chosenFilePath,
		const std::string unavailFilePath);

private:

	// Total health point
	int totalHP;

};

#endif