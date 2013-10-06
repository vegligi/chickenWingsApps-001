#include "GameScene.h"

#include "cocos-ext.h"
#include "spine\Json.h"

#include "VisibleRect.h"


cocos2d::CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameScene *layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool GameScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCLabelTTF* pLabel = CCLabelTTF::create("I am game page", "Arial", SCALE_FACTOR * 36 );
	pLabel->setPosition(ccpAdd(VisibleRect::top(),ccp(0, -pLabel->getContentSize().height)));
	this->addChild(pLabel, 1);


	unsigned long size;
	char* date = (char*)CCFileUtils::sharedFileUtils()->getFileData("scripts/chapter1_1.json","r", &size);

	cocos2d::extension::Json* root= cocos2d::extension::Json_create(date);
	cocos2d::extension::Json* storiese = cocos2d::extension::Json_getItem (root, "stories");
	int stories_size = cocos2d::extension::Json_getSize(storiese);

	for(int i = 0; i<stories_size-1 ;i++)
	{
       cocos2d::extension::Json* story_item = cocos2d::extension::Json_getItemAt(storiese,i);

	   int type =  cocos2d::extension::Json_getItem(story_item, "type")->valueint;

	   CCLOG("story_item  No.%d  , type is %d ",i,type);
	}

	return true;
}