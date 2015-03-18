#include "MainMenuScene.h"
#include "MainMenuLayer.h"

bool MainMenuScene::init()
{
	// Init the main menu layer
	auto MainMenuLayer = MainMenuLayer::create();

	// Add the main menu layer to the scene 
	addChild(MainMenuLayer, 10);
	
	return true;
}