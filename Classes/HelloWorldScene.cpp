#include "HelloWorldScene.h"

#include "AppMacros.h"

#include "sqlite3.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World Tang!!", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	CCLOG(" i am  ---> %s",smallResource.directory);

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    

	//test sqlite
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值  
	
	//打开一个数据库，如果该数据库不存在，则创建一个数据库文件 
	result = sqlite3_open("save.db", &pDB); 
	if( result != SQLITE_OK )      
		CCLog( "打开数据库失败，错误码:%d ，错误原因:%s\n" , result, errMsg );   
	else
		CCLog(" Open sql  successfully ");

// 	//创建表，设置ID为主键，且自动增加 
// 	result=sqlite3_exec( pDB, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32) ) " , NULL, NULL, &errMsg ); 
// 	if( result != SQLITE_OK )       
// 		CCLog( "创建表失败，错误码:%d ，错误原因:%s\n" , result, errMsg ); 
// 
// 
// 	//插入数据 
// 	sqlstr=" insert into MyTable_1( name ) values ( '克塞' ) "; 
// 	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg ); 
// 	if(result != SQLITE_OK )      
// 		CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );  
// 	
// 
// 	//插入数据 
// 	sqlstr=" insert into MyTable_1( name ) values ( '葫芦娃' ) "; 
// 	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg ); 
// 	if(result != SQLITE_OK )      
// 		CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );  
// 	
// 
// 	//插入数据 
// 	sqlstr=" insert into MyTable_1( name ) values ( '擎天柱' ) "; 
// 	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg ); 
// 	if(result != SQLITE_OK )       
// 		CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );  
// 
// 	//关闭数据库
// 	sqlite3_close(pDB);

	int count;  
	sqlstr="select * from MyTable_1";  
	sqlite3_exec( pDB, sqlstr.c_str() , loadRecordCount, &count, &errMsg ); 

	CCLog(" MyTable_1 have %d  records",count);

    return true;
}


int loadRecordCount( void * para, int n_column, char ** column_value, char ** column_name ) 
{            
	int *count=(int*)para;             
	*count=n_column;             
	return 0;
} 

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
