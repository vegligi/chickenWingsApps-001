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

	pS_bg = CCSprite::create("bg.jpg");
	pS_bg->setPosition(VisibleRect::center());
	this->addChild(pS_bg);

// 	CCLabelTTF* pLabel = CCLabelTTF::create("I am Home page", "Arial", SCALE_FACTOR * 36 );
// 
// 	pLabel->setPosition(ccpAdd(VisibleRect::top(),ccp(0, -pLabel->getContentSize().height)));
// 	this->addChild(pLabel, 1);


	//setting menu
	CCMenuItemImage *pSettingItem = CCMenuItemImage::create(
		"setting_menu.png",
		"setting_menu_pressed.png",this,
		menu_selector(HomeScene::menuCallback));

	pSettingItem->setTag(2);

	CCMenu* pSettingMenu = CCMenu::create(pSettingItem, NULL);
	pSettingMenu->setPosition( ccpAdd(VisibleRect::leftBottom() , ccp( 50 +  pSettingItem->getContentSize().width/2 , pSettingItem->getContentSize().height/2 + 50 ) ) );
	this->addChild(pSettingMenu, 1);

	//start game meun  
	CCMenuItemImage *pStartGameItem = CCMenuItemImage::create(
		"start_menu.png",
		"start_menu_pressed.png",this,
		menu_selector(HomeScene::menuCallback));

	pStartGameItem->setTag(1);

	CCMenu* pStartGameMenu = CCMenu::create(pStartGameItem, NULL);
	pStartGameMenu->setPosition( ccpAdd(pSettingMenu->getPosition() , ccp(0 , 40 + pSettingItem->getContentSize().height/2 + pStartGameItem->getContentSize().height/2)) );
	this->addChild(pStartGameMenu, 1);


	//粒子系统
	CCParticleSystem *system = CCParticleSystemQuad::create("particle/gameBackground.plist");
	system->setPosition(VisibleRect::center());
	this->addChild(system);


	CCArray* plistArray=CCArray::createWithCapacity(2);
	char name[100];

	std::string type = std::string("butterfly/");

	std::string sub = "%d.png";
	std::string patten = type.append(sub);

	for(int i=0;i<=29;i++){
		sprintf(name,patten.c_str(),i);

		CCTexture2D *pTexture=CCTextureCache::sharedTextureCache()->addImage(name);
		float width = pTexture->getContentSize().width;
		float height = pTexture->getContentSize().height;
		CCSpriteFrame *frame=CCSpriteFrame::createWithTexture(pTexture,CCRectMake(0,0,width,height));

		/*CCLog(" name ---> %s" ,name);*/
		plistArray->addObject(frame);
	}

	CCAnimation *plitAnimation=CCAnimation::createWithSpriteFrames(plistArray,0.1f);
	CCActionInterval* fly = CCAnimate::create(plitAnimation);

	CCActionInterval* butterfly_action = CCSequence::create(fly,CCCallFuncN::create(this,callfuncN_selector(HomeScene::onFinishButterflyAnimation)),NULL);

	pS_butterfly = CCSprite::create("butterfly/0.png");
	pS_butterfly->setPosition(VisibleRect::center());
	this->addChild(pS_butterfly,2);
	pS_butterfly->runAction(butterfly_action);

	//持续时间 ,网格大小, 位置,半径,速率,振幅
// 	CCActionInterval * ripple3D=  CCRepeatForever::create(CCRipple3D::create( 10 , CCSizeMake(100,80) , VisibleRect::center() , 1200 , 10 , 100 )); 
// 	pS_bg->runAction( ripple3D);
	
	return true;

}

void HomeScene::menuCallback( CCObject* pSender )
{
	int tag = ((CCNode*)pSender)->getTag();

	switch(tag)
	{

	case 1:
		{

			//清空缓存
			CCDirector::sharedDirector()->purgeCachedData();
			CCScene *game = GameScene::scene();
			CCDirector::sharedDirector()->replaceScene(game);

		}
		break;

	case 2:
		{
			//清空缓存
			CCDirector::sharedDirector()->purgeCachedData();
			CCScene *setting = SettingScene::scene();
			CCDirector::sharedDirector()->replaceScene(setting);

		}
		break;

		default:
			break;
	}
}

void HomeScene::onFinishButterflyAnimation( CCNode* sender )
{

	CCTexture2D *pTexture=CCTextureCache::sharedTextureCache()->textureForKey("butterfly/0.png");
	float width = pTexture->getContentSize().width;
	float height = pTexture->getContentSize().height;
	CCSpriteFrame *frame=CCSpriteFrame::createWithTexture(pTexture,CCRectMake(0,0,width,height));
	pS_butterfly->setDisplayFrame(frame);

	pS_butterfly->runAction(CCFadeIn::create(5.0f));

	CCActionInterval * ripple3D=  CCRepeatForever::create(CCRipple3D::create( 10 , CCSizeMake(100,80) , VisibleRect::center() , 1200 , 8 , 100 ));
	pS_bg->runAction( ripple3D);
}
