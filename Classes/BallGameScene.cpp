#include "BallGameScene.h"

bool BallGameScene::init()
{
	// Init the BallGameLayer
	auto ballGameLayer = BallGameLayer::create();

	// Add to the child
	addChild(ballGameLayer, 0);

	return true;
}