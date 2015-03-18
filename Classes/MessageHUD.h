#ifndef __MESSAGEHUD_H__
#define __MESSAGEHUD_H__

#include "cocos2d.h"
#include <string>
USING_NS_CC;

class MessageHUD : public LayerColor
{
public:

	MessageHUD();
	~MessageHUD();

	static MessageHUD* createLayer(const std::string& _message);
	void initOptions(const std::string& _message);

	virtual void draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
		bool transformUpdated);

	inline virtual cocos2d::LabelBMFont* getMessageLabel() { return _messageLabel; };

private:

	cocos2d::LabelBMFont* _messageLabel;
};

#endif