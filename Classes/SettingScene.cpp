#include "SettingScene.h"

#include "VisibleRect.h"

cocos2d::CCScene* SettingScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	SettingScene *layer = SettingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool SettingScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCLabelTTF* pLabel = CCLabelTTF::create("I am setting page", "Arial", SCALE_FACTOR * 36 );
	pLabel->setPosition(ccpAdd(VisibleRect::top(),ccp(0, -pLabel->getContentSize().height)));
	this->addChild(pLabel, 1);

	return true;
}

