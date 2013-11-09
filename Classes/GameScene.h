#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Json.h"
#else
#include "Spine/Json.h";
#endif



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
	bool isShowingText;

	CCSprite* bgSp;//����

	CCSprite* textBoxSp; //���ֵı���
	CCLabelTTF* textLabel; //����

	CCSprite* actorNameSp; //�������ֱ���
    CCLabelTTF* actorNameLabel; //������

	cocos2d::extension::Json* rootJson;
	cocos2d::extension::Json* storyJson;

	int cur_chapter; //�ڼ���
	int cur_act;//�ڼ�Ļ
	int totalSize;// ��ǰĻһ���ж���С��
	int curIndex;//��ǰ���ڼ�С��
	

	void CheckDelayBeforeReadStroy(int index);
	void readStory(int index);
	void readNext();
	void actBg(cocos2d::extension::Json* json);
	void actText(cocos2d::extension::Json* json);
	void actFg(cocos2d::extension::Json* json);
	void actBgMusic( cocos2d::extension::Json* story_item );

	void actAction(cocos2d::extension::Json* json);

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