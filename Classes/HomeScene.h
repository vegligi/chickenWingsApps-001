#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HomeScene : public CCLayer 
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

	virtual bool init();  
	static cocos2d::CCScene* scene();

private:

	CCSprite* pS_bg;
	CCSprite* pS_butterfly;

	void menuCallback(CCObject* pSender);

	void onFinishButterflyAnimation(CCNode* sender);
	void onFinishButterfly(CCNode* sender);

	void getButterflyAnimation(int i);

	void getButterflyAnimation2(int i);
	

	CREATE_FUNC(HomeScene);
};

#endif 
