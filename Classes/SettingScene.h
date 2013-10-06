#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class SettingScene : public CCLayer 
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

	virtual bool init();  
	static cocos2d::CCScene* scene();

private:
	void menuCallback(CCObject* pSender);

	CREATE_FUNC(SettingScene);
};

#endif 
