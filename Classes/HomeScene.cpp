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

	// background
	pS_bg = CCSprite::create("bg.jpg");
	pS_bg->setPosition(VisibleRect::center());
	this->addChild(pS_bg);


	//ripple effect
	CCRipple3D* ripole = CCRipple3D::create( 10 , CCSizeMake(100,80) , VisibleRect::center() , 1200 , 3 , 100 );
	pS_bg->runAction( CCRepeatForever::create( ripole ));


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

	//bug method create by tang
	getButterflyAnimation(0);
	getButterflyAnimation(1);
	getButterflyAnimation(2);
	getButterflyAnimation(3);

	//zy method
// 	getButterflyAnimation2(0);
// 	getButterflyAnimation2(1);

	//backgroud particle
// 	CCParticleSystem *system = CCParticleSystemQuad::create("particle/gameBackground.plist");
// 	system->setPosition(VisibleRect::center());
// 	this->addChild(system);

	return true;

}

void HomeScene::menuCallback( CCObject* pSender )
{
	int tag = ((CCNode*)pSender)->getTag();

	switch(tag)
	{

	case 1:
		{

			CCDirector::sharedDirector()->purgeCachedData();
			CCScene *game = GameScene::scene();
			CCDirector::sharedDirector()->replaceScene(game);

		}
		break;

	case 2:
		{
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

// 	CCActionInterval * ripple3D=  CCRepeatForever::create(CCRipple3D::create( 10 , CCSizeMake(100,80) , VisibleRect::center() , 1200 , 7 , 100 ));
// 	pS_bg->runAction( ripple3D);
}

void HomeScene::getButterflyAnimation( int i_index )
{
	float time_gap = 1.6f;

	//load the butterfly animation
	CCArray* plistArray=CCArray::createWithCapacity(2);
	char name[100];

	std::string type = std::string("butterfly/");

	std::string sub = "%d.png";
	std::string patten = type.append(sub);

	CCLOG(" ================== i_index =============   : %i" , i_index);

	int i = i_index;
	for(i;i<=29;i+=4){

		sprintf(name,patten.c_str(),i);

		CCTexture2D *pTexture=CCTextureCache::sharedTextureCache()->addImage(name);
		float width = pTexture->getContentSize().width;
		float height = pTexture->getContentSize().height;
		CCSpriteFrame *frame=CCSpriteFrame::createWithTexture(pTexture,CCRectMake(0,0,width,height));

		CCLog(" name ---> %s" ,name);
		plistArray->addObject(frame);

	}

	//second parameter is the speed of each frame
	CCAnimation *plitAnimation = CCAnimation::createWithSpriteFrames(plistArray,time_gap);
	CCActionInterval* fly = CCAnimate::create(plitAnimation);

	float dt = time_gap  * 1.5;

	if(i_index==1)
	{
		dt = time_gap  * 1;
	}else if(i_index==2)
	{
		dt = time_gap * 0.5;
	}else if(i_index==3)
	{
		dt = 0;
	}

	CCDelayTime* delay = CCDelayTime::create(dt);

	CCActionInterval* butterfly_action = NULL;

	if(i_index==1)
	{
       butterfly_action = CCSequence::create(delay,fly,CCCallFuncN::create(this,callfuncN_selector(HomeScene::onFinishButterflyAnimation)),NULL);
	}else{
		butterfly_action = CCSequence::create(delay,fly,CCCallFuncN::create(this,callfuncN_selector(HomeScene::onFinishButterfly)),NULL);
	}
	

	CCFadeOut* f_out = CCFadeOut::create(time_gap);
	CCFadeIn* f_in = CCFadeIn::create(time_gap);

	CCActionInterval* butterfly_alph =NULL;

	butterfly_alph =  CCSequence::create(delay,NULL);

	if(i_index == 1  || i_index == 0 )
	{
		butterfly_alph =  CCSequence::create(delay,f_out,f_in,f_out,f_in,f_out,f_in,f_out,f_in,NULL);
	}else{
		butterfly_alph =  CCSequence::create(delay,f_out,f_in,f_out,f_in,f_out,f_in,f_out,NULL);
	}

	CCSpawn* spawn = CCSpawn::create(butterfly_action,butterfly_alph,NULL);

	if(i_index!=1)
	{
		std::string str_name = std::string("butterfly/").append(TextUnit::int2Str(i_index)).append(".png");
		CCSprite* sprite_butterfly = CCSprite::create(str_name.c_str());
		sprite_butterfly->setPosition(VisibleRect::center());
		this->addChild(sprite_butterfly,2);
		sprite_butterfly->runAction(spawn);

	}else{

		std::string str_name = std::string("butterfly/").append(TextUnit::int2Str(i_index)).append(".png");
		pS_butterfly = CCSprite::create(str_name.c_str());
		pS_butterfly->setPosition(VisibleRect::center());
		this->addChild(pS_butterfly,2);
		pS_butterfly->runAction(spawn);
	}

}

void HomeScene::getButterflyAnimation2( int i_index )
{
	float time_gap = 0.25f;

	//load the butterfly animation
	CCArray* plistArray=CCArray::createWithCapacity(2);
	char name[100];

	std::string type = std::string("butterfly/");

	std::string sub = "%d.png";
	std::string patten = type.append(sub);

	CCLOG(" ================== i_index =============   : %i" , i_index);

	int i = i_index;
	for(i;i<=29;i++){

		sprintf(name,patten.c_str(),i);

		CCTexture2D *pTexture=CCTextureCache::sharedTextureCache()->addImage(name);
		float width = pTexture->getContentSize().width;
		float height = pTexture->getContentSize().height;
		CCSpriteFrame *frame=CCSpriteFrame::createWithTexture(pTexture,CCRectMake(0,0,width,height));

		CCLog(" name ---> %s" ,name);
		plistArray->addObject(frame);

	}

	//second parameter is the speed of each frame
	CCAnimation *plitAnimation = CCAnimation::createWithSpriteFrames(plistArray,time_gap);
	CCActionInterval* fly = CCAnimate::create(plitAnimation);

	CCActionInterval* butterfly_action = NULL;

	if( i_index ==0 )
	{
		butterfly_action = CCSequence::create( fly,CCCallFuncN::create(this,callfuncN_selector(HomeScene::onFinishButterflyAnimation)),NULL);
	}else{
		butterfly_action = CCSequence::create( fly,CCCallFuncN::create(this,callfuncN_selector(HomeScene::onFinishButterfly)),NULL);
	}

	if(i_index==1)
	{
		std::string str_name = std::string("butterfly/").append(TextUnit::int2Str(i_index)).append(".png");
		CCSprite* sprite_butterfly = CCSprite::create(str_name.c_str());
		sprite_butterfly->setPosition(VisibleRect::center());
		this->addChild(sprite_butterfly,2);
		sprite_butterfly->runAction(butterfly_action);
	}else{

		std::string str_name = std::string("butterfly/").append(TextUnit::int2Str(i_index)).append(".png");
		pS_butterfly = CCSprite::create(str_name.c_str());
		pS_butterfly->setPosition(VisibleRect::center());
		this->addChild(pS_butterfly,2);
		pS_butterfly->runAction(butterfly_action);
	}

}

void HomeScene::onFinishButterfly( CCNode* sender )
{
	sender->removeFromParent();
}
