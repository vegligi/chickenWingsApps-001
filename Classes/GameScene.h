#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Json.h"

USING_NS_CC;

class GameScene : public CCLayer 
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

	virtual ~GameScene();

	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void onEnter();
    virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void update(float dt);
private:

	bool isActing;

	CCSprite* emptySprite;

	CCSprite* bgSp;//背景

	CCSprite* textBoxSp; //文字的背景
	CCLabelTTF* textLabel; //文字

	CCSprite* actorNameSp; //主角名字背景
    CCLabelTTF* actorNameLabel; //角名字

	cocos2d::extension::Json* rootJson;
	cocos2d::extension::Json* storyJson;

	int cur_chapter; //第几章
	int cur_act;//第几幕
	int totalSize;// 当前幕一共有多少小节
	int curIndex;//当前到第几小节
	bool isShowingText;

	void CheckDelayBeforeReadStroy(int index);
	void readStory(int index);
	void readNext();
	void actBg(cocos2d::extension::Json* json);
	void actText(cocos2d::extension::Json* json);
	void actFg(cocos2d::extension::Json* json);

	std::string* text_str;
	int text_size;
	int text_index;
	void printText(float dt);

	void cancleIsActing();

	void menuCallback(CCObject* pSender);

	CCPoint getActorPositon( std::string code);
	int getActorPositionTag(std::string code);
	CREATE_FUNC(GameScene);

};

#endif 
