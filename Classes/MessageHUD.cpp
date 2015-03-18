#include "MessageHUD.h"

MessageHUD::MessageHUD() {}

MessageHUD::~MessageHUD() {}

MessageHUD* MessageHUD::createLayer(const std::string& _message)
{
	MessageHUD* a = new MessageHUD();
	a->create();
	a->setColor(cocos2d::Color3B(0, 0, 0));

	a->setContentSize(cocos2d::Size::Size(1, 1));
	a->setAnchorPoint(cocos2d::Vec2(0, 0));

	a->initOptions(_message);

	return a;
}

void MessageHUD::initOptions(const std::string& _message)
{
	//_messageLabel = cocos2d::LabelBMFont::create(_message.c_str(), "arial16.fnt");

	//_messageLabel->setColor(cocos2d::Color3B(255, 215, 0));

	//addChild(_messageLabel, 1);

	//_messageLabel->setPosition(cocos2d::Vec2(Director::getInstance()->getVisibleSize().width,
	//	Director::getInstance()->getVisibleSize().height));

	auto msg = Label::create(_message.c_str());

}

void MessageHUD::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
	bool transformUpdated) {}