#include "GameScene.h"

#include "VisibleRect.h"

#include "TextUnit.h"

int Pos_tag_L = 1001;
int Pos_tag_R = 1002;
int Position_M = 1003;

int Position_L1 = 2001;
int Position_L2 = 2002;
int Position_R1 = 2003;
int Position_R2 = 2004;

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

	schedule(schedule_selector(GameScene::printText),0.1f);

	this->setTouchEnabled(true);

	isActing = true;
	isShowingText = false;
	curIndex = 0;

	text_str = NULL;
	text_index = -1;
	text_size = 0;

    emptySprite = CCSprite::create();
	this->addChild(emptySprite);


	textBoxSp = CCSprite::create("textbox_bg.png");
	textBoxSp->setPosition( ccpAdd( VisibleRect::bottom(), ccp(0,textBoxSp->getContentSize().height/2 + 5 )));
	this->addChild(textBoxSp,3);

	textLabel = CCLabelTTF::create("", "Arial", SCALE_FACTOR * 28 );

	textLabel->setPosition(ccp(textBoxSp->getPositionX(),textBoxSp->getPositionY()));
	textLabel->setDimensions(CCSizeMake(textBoxSp->getContentSize().width - 40 , textBoxSp->getContentSize().height - 40));
	textLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
	this->addChild(textLabel, 3);

	actorNameSp = CCSprite::create("actor_name_bg.png");
	actorNameSp->setPosition( ccpAdd( VisibleRect::leftBottom(), ccp( actorNameSp->getContentSize().width , textBoxSp->getContentSize().height + 5 + actorNameSp->getContentSize().height/2 +5)));
	this->addChild(actorNameSp,3);

	actorNameLabel = CCLabelTTF::create("", "Arial", SCALE_FACTOR * 28 );
	actorNameLabel->setPosition(ccp(actorNameSp->getContentSize().width/2 , actorNameSp->getContentSize().height/2));
	actorNameSp->addChild(actorNameLabel,3);

	//load the story date as Json 
	unsigned long size;
	char* date = (char*)CCFileUtils::sharedFileUtils()->getFileData("scripts/chapter1_1.json","r", &size);

	rootJson = cocos2d::extension::Json_create(date);
	storyJson = cocos2d::extension::Json_getItem (rootJson, "story");
	totalSize = cocos2d::extension::Json_getSize(storyJson);

	CheckDelayBeforeReadStroy(curIndex);

	return true;

}

void GameScene::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
	CCLayer::onEnter();
}


void GameScene::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


bool GameScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(isShowingText)
	{
		text_index = text_size-1;
		return true;
	}

	if(!isActing)
	{
		curIndex++;
		CheckDelayBeforeReadStroy(curIndex);
		/*CCLOG(" ccTouchBegan ---> %d" , curIndex);*/
	}

	return true;
}

void GameScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void GameScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void GameScene::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

GameScene::~GameScene()
{
	//stop all schedule first 
	this->unscheduleUpdate();
	this->unscheduleAllSelectors();

	removeAllChildren();

	CC_SAFE_DELETE(rootJson);
	CC_SAFE_DELETE(storyJson);

}

void GameScene::menuCallback( CCObject* pSender )
{

}

void GameScene::CheckDelayBeforeReadStroy( int index )
{
	isActing = true;

	cocos2d::extension::Json* story_item = cocos2d::extension::Json_getItemAt(storyJson,index);
	cocos2d::extension::Json* delay_json =  cocos2d::extension::Json_getItem(story_item, "delay");

	if(!delay_json) 
	{
		readStory(index);

	}else
	{
		float delay_time = delay_json->valuefloat;

		if(delay_time>0)
		{
			CCLOG( "delay_time ---> %f " , delay_time);
			CCAction* action = CCSequence::create(CCDelayTime::create(delay_time), CCCallFunc::create(this,callfunc_selector(GameScene::readNext)) , NULL);
			emptySprite->runAction(action);
		/*	scheduleOnce(schedule_selector(GameScene::readNext),delay_time);*/
		}else{
			readStory(index);
		}
	}
}

void GameScene::readStory( int index )
{
	isActing = true;

	cocos2d::extension::Json* story_item = cocos2d::extension::Json_getItemAt(storyJson,index);

	int type =  cocos2d::extension::Json_getItem(story_item, "type")->valueint;
	CCLOG("story_item  No.%d  , type is %d ",index,type);

	switch(type)
	{
	case 1:
		{
			actBg(story_item);
		}
		break;

	case 2:
		{
			actFg(story_item);
		}
		break;

	case 3:
		{
			actText(story_item);
		}
		break;

	case 4:
		{

		}
		break;

	case 5:
		{

		}
		break;

	default:
		break;
	}

	/*CC_SAFE_DELETE(story_item);*/

}

void GameScene::actBg( cocos2d::extension::Json* json )
{
	
	if(bgSp)
	{
		this->removeChild(bgSp);
	}

	std::string img = cocos2d::extension::Json_getItem(json, "img")->valuestring;

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	  std::string img_src = std::string(img);
	#else
	  std::string img_src = std::string("bgs/").append(img);
    #endif

	cocos2d::extension::Json* anim_json = cocos2d::extension::Json_getItem(json, "anim");

	bgSp = CCSprite::create(img_src.c_str());
	bgSp->setPosition(VisibleRect::center());
	
	bool isHaveAnima = false;

	if(anim_json)
	{
		std::string anim = anim_json->valuestring;
		/*CCLOG(" anim value is ---> %s" , anim.c_str());*/

		if(!strcmp(anim.c_str(),"fade_in"))
		{
			/*CCLOG(" anim is fade_in");*/
			bgSp->setOpacity(0);
			CCAction* action = CCSequence::create(CCFadeIn::create(1.0f), CCCallFunc::create(this,callfunc_selector(GameScene::cancleIsActing)) , NULL);
			bgSp->runAction(action);

			isHaveAnima = true;
		}

	}

	if(!isHaveAnima)
	{
		isActing = false;
	}


	this->addChild(bgSp,0);

	cocos2d::extension::Json* auto_json = cocos2d::extension::Json_getItem(json, "auto_next");

	if(auto_json)
	{
		std::string auto_str = auto_json->valuestring;
		CCLOG(" anim value is ---> %s" , auto_str.c_str());

		if(!strcmp(auto_str.c_str(),"true")) //设置了"auto_next"属性,并且值为true
		{
			curIndex++;
			CheckDelayBeforeReadStroy(curIndex);
		}

	}else if(!auto_json) //没有设置"auto_next"属性，背景元素默认自动跳转至下一节
	{
		curIndex++;
		CheckDelayBeforeReadStroy(curIndex);
	}

}


void GameScene::actText( cocos2d::extension::Json* json )
{
	isShowingText = true;

	if(text_str)
	{
		CC_SAFE_DELETE(text_str);
	}

	text_index = 0;

	std::string txt = cocos2d::extension::Json_getItem(json, "txt") -> valuestring;
	text_str = new std::string(txt);

	std::vector<std::string>  data = TextUnit::toVectorCharacters(txt,3);
	/*CCLOG(" data size is ---> %d" ,data.size());*/

	// 	for(int j = 0 ;j< data.size() ; j++)
	// 	{
	// 		std::string s = data[j];
	// 		CCLOG(" data str --->%s" , s.c_str());
	// 	}

	/*std::wstring w_str = TextUnit::UTF8ToUnicode(std::string(txt).c_str());*/
	/*std::wstring w_str = TextUnit::s2ws(std::string(txt));*/
	/*std::wstring w_str(txt.begin(),txt.end());*/

	/*text_size = text_str->size();*/
	text_size = data.size();

	/*schedule(schedule_selector(GameScene::printText),0.1f,text_size - 1,0);*/

	cocos2d::extension::Json* actor_name_json = cocos2d::extension::Json_getItem(json, "actor_name");

	if(actor_name_json)
	{
		std::string auto_str = actor_name_json->valuestring;

		actorNameLabel->setString(auto_str.c_str());
	}

// 	cocos2d::extension::Json* auto_json = cocos2d::extension::Json_getItem(json, "anim");
// 
// 	if(auto_json)
// 	{
// 		std::string auto_str = auto_json->valuestring;
// 		if(!strcmp(auto_str.c_str(),"true"))
// 		{
// 
// 		}
// 	}

}

void GameScene::actFg( cocos2d::extension::Json* json )
{

	cocos2d::extension::Json* img_json = cocos2d::extension::Json_getItem(json, "img");

	if(img_json)
	{
		std::string img = cocos2d::extension::Json_getItem(json, "img")->valuestring;

        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string img_src = std::string(img);
        #else
		std::string img_src = std::string("actors/").append(img);
        #endif

		std::string pos_code = cocos2d::extension::Json_getItem(json, "position")->valuestring;

		CCPoint pos = getActorPositon(pos_code);
		int pos_tag = getActorPositionTag(pos_code);

		this->removeChildByTag(pos_tag);

		CCSprite* actorSp = CCSprite::create(img_src.c_str());
		actorSp->setTag(pos_tag);
		actorSp->setPosition(ccp(pos.x , pos.y - (pos.y - actorSp->getContentSize().height/2)));

		this->addChild(actorSp,2);

        /*CCLOG(" position is [ %f,%f ] ,  tag --> %d " , pos.x , pos.y  , pos_tag);*/

	}

	cocos2d::extension::Json* dis_json = cocos2d::extension::Json_getItem(json, "dis");

	if(dis_json)
	{
		std::string dis_str = cocos2d::extension::Json_getItem(json, "dis")->valuestring;
		int dis_tag = getActorPositionTag(dis_str);

		CCLOG(" dis_tag ---> %d" , dis_tag);
		this->removeChildByTag(dis_tag);
	}

	

	curIndex++;
	CheckDelayBeforeReadStroy(curIndex);

}



void GameScene::cancleIsActing()
{
	isActing = false;
}

void GameScene::readNext()
{
	readStory(curIndex);
}

void GameScene::printText( float dt )
{
	if(text_index<0)
	{
		return;
	}

	text_index++;
	/*std::wstring w_str = TextUnit::UTF8ToUnicode(text_str->c_str());*/
	/*std::wstring w_str = TextUnit::str2wstr(*text_str);*/
	/*std::wstring w =  w_str.substr(0,text_index);*/

	/*std::string str = TextUnit::UnicodeToUTF8(w.c_str());*/
	/*std::string str = TextUnit::wstr2str(w);*/

	/*CCLOG(" text_index : % d  , str : %s" , text_index , str.c_str() );*/

	std::vector<std::string>  data = TextUnit::toVectorCharacters(*text_str,3);

	std::string str = data[0];

	for(int i = 1 ; i<text_index ; i++)
	{
		str.append(data[i]);
	}

	textLabel->setString(str.c_str());

	if(text_index==text_size)
	{
		/*unschedule(schedule_selector(GameScene::printText));*/

		CCLOG(" --- end print next ---");
		isActing = false;
		isShowingText = false;
		text_index = -1;
	}

}

void GameScene::update( float dt )
{

}

CCPoint GameScene::getActorPositon( std::string code)
{
	CCRect s_visibleRect;
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	s_visibleRect.origin = pEGLView->getVisibleOrigin();
	s_visibleRect.size = pEGLView->getVisibleSize();

	if(!strcmp(code.c_str(),"L"))
	{
		return  ccp(s_visibleRect.origin.x + s_visibleRect.size.width/4, s_visibleRect.origin.y + s_visibleRect.size.height/2);
	}else if (!strcmp(code.c_str(),"R"))
	{
		return   ccp(s_visibleRect.origin.x + s_visibleRect.size.width/4 * 3, s_visibleRect.origin.y + s_visibleRect.size.height/2);
	}else if (!strcmp(code.c_str(),"M"))
	{
		return   ccp(s_visibleRect.origin.x + s_visibleRect.size.width/2 , s_visibleRect.origin.y + s_visibleRect.size.height/2);
	}else if (!strcmp(code.c_str(),"L1"))
	{
		return    ccp(s_visibleRect.origin.x + s_visibleRect.size.width/5 , s_visibleRect.origin.y + s_visibleRect.size.height/2);
	}else if (!strcmp(code.c_str(),"L2"))
	{
		return   ccp(s_visibleRect.origin.x + s_visibleRect.size.width/5*2 , s_visibleRect.origin.y + s_visibleRect.size.height/2);
	}else if (!strcmp(code.c_str(),"R2"))
	{
		return    ccp(s_visibleRect.origin.x + s_visibleRect.size.width/5*3 , s_visibleRect.origin.y + s_visibleRect.size.height/2);
	}else if (!strcmp(code.c_str(),"R1"))
	{
		return    ccp(s_visibleRect.origin.x + s_visibleRect.size.width/5*4 , s_visibleRect.origin.y + s_visibleRect.size.height/2);
	}
}

int GameScene::getActorPositionTag( std::string pos_code )
{
	int pos_tag;
	if(!strcmp(pos_code.c_str(),"L"))
	{
		pos_tag = Pos_tag_L;
	}else if (!strcmp(pos_code.c_str(),"R"))
	{
		pos_tag = Pos_tag_R;
	}else if (!strcmp(pos_code.c_str(),"M"))
	{
		pos_tag = Position_M;
	}else if (!strcmp(pos_code.c_str(),"L1"))
	{
		pos_tag = Position_L1;
	}else if (!strcmp(pos_code.c_str(),"L2"))
	{
		pos_tag = Position_L2;
	}else if (!strcmp(pos_code.c_str(),"R2"))
	{
		pos_tag = Position_R2;
	}else if (!strcmp(pos_code.c_str(),"R1"))
	{
		pos_tag = Position_R1;
	}
	return pos_tag;
}


