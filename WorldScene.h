#ifndef __WORLD_SCENE_H__
#define __WORLD_SCENE_H__

#include "cocos2d.h"
#include "LivingThings.h"
#include "Config.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include "Plant.h"
#include "Global.h"

class LivingThings;

class World : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    static void theCreation();
    
    // Menu layer
    cocos2d::LayerColor* _layerMenu;
    
    // Menu Button
    cocos2d::Menu* _menuBtn;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void update(float delta);
    
    void createMenuItems(void);
    
    void checkGameOver(void);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // Events
    void onRetryPressed(cocos2d::Ref* sender);
    void onMenuPressed(cocos2d::Ref* sender);
    void onMenuClosePressed(cocos2d::Ref* sender);
    void onVisualPressed(cocos2d::Ref* sender, int lType);
    
    // implement the "static create()" method manually
    CREATE_FUNC(World);
};

#endif // __WORLD_SCENE_H__
