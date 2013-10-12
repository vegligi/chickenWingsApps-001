#include "HomeScene.h"
#include "GameScene.h"
#include "SettingScene.h"

#include "VisibleRect.h"

#include "TextUnit.h"

cocos2d::CCScene* HomeScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HomeScene *layer = HomeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool HomeScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCLabelTTF* pLabel = CCLabelTTF::create("I am Home page", "Arial", SCALE_FACTOR * 36 );
	pLabel->setPosition(ccpAdd(VisibleRect::top(),ccp(0, -pLabel->getContentSize().height)));
	this->addChild(pLabel, 1);


	//start game meun  
	CCMenuItemImage *pStartGameItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",this,
		menu_selector(HomeScene::menuCallback));

	pStartGameItem->setTag(1);

	// create menu, it's an autorelease object
	CCMenu* pStartGameMenu = CCMenu::create(pStartGameItem, NULL);
	pStartGameMenu->setPosition(VisibleRect::center());
	this->addChild(pStartGameMenu, 1);


	//setting menu
	CCMenuItemImage *pSettingItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",this,
		menu_selector(HomeScene::menuCallback));

	pSettingItem->setTag(2);

	// create menu, it's an autorelease object
	CCMenu* pSettingMenu = CCMenu::create(pSettingItem, NULL);
	pSettingMenu->setPosition(ccpSub(pStartGameMenu->getPosition(),ccp(0,pSettingItem->getContentSize().height + 20)));
	this->addChild(pSettingMenu, 1);

	return true;

}

void HomeScene::menuCallback( CCObject* pSender )
{
	int tag = ((CCNode*)pSender)->getTag();

	switch(tag)
	{

	case 1:
		{

			//Çå¿Õ»º´æ
			CCDirector::sharedDirector()->purgeCachedData();
			CCScene *game = GameScene::scene();
			CCDirector::sharedDirector()->replaceScene(game);

		}
		break;

	case 2:
		{
			//Çå¿Õ»º´æ
			CCDirector::sharedDirector()->purgeCachedData();
			CCScene *setting = SettingScene::scene();
			CCDirector::sharedDirector()->replaceScene(setting);

		}
		break;

		default:
			break;
	}
}
