#include "MainMenuLayer.h"

bool MainMenuLayer::init()
{
	// Get the windows size
	auto winSize = Director::getInstance()->getWinSize();

	// Set the background
	auto ui_background = Sprite::create("MainMenu/ui_background.png");
	ui_background->setAnchorPoint(Point(0.0f, 0.0f));
	ui_background->setPosition(Point(0.0f, 0.0f));
	addChild(ui_background, 0);

	// Set game logo
	auto ui_logo = Sprite::create("MainMenu/ui_logo.png");
	ui_logo->setPosition(Point(winSize.width / 2.0f, winSize.height / 1.35f));
	addChild(ui_logo, 2);

	// Create the start button of the game
	auto ui_startGameBtn = Sprite::create("MainMenu/ui_startGameBtn.png");
	auto ui_startGameBtnPush = Sprite::create("MainMenu/ui_startGameBtnPush.png");

	// Create the exit button of the game
	auto ui_exitGameBtn = Sprite::create("MainMenu/ui_exitGameBtn.png");
	auto ui_exitGameBtnPush = Sprite::create("MainMenu/ui_exitGameBtnPush.png");

	// Create the menu
	auto startGameMenuItem = MenuItemSprite::create(ui_startGameBtn, ui_startGameBtnPush, CC_CALLBACK_1(MainMenuLayer::startGameEvent, this));
	auto exitGameMenuItem = MenuItemSprite::create(ui_exitGameBtn, ui_exitGameBtnPush, CC_CALLBACK_1(MainMenuLayer::exitGameEvent, this));
	exitGameMenuItem->setPosition(Point(startGameMenuItem->getPosition().x, startGameMenuItem->getPosition().y - 140));
	auto mainMenu = Menu::create(startGameMenuItem, exitGameMenuItem, NULL);
	addChild(mainMenu, 2);

	// Play the music
	//TODO

	return true;
}

void MainMenuLayer::startGameEvent(Ref* sender)
{
	// Create the scene of BallGameScene with a transition effect
	auto replaceScene = TransitionCrossFade::create(1, BallGameScene::create());

	// Replace the scene with the transition effect 
	Director::getInstance()->replaceScene(replaceScene);
}

void MainMenuLayer::exitGameEvent(Ref* sender)
{
	// Exit game 
	Director::getInstance()->end();

	exit(0);
}