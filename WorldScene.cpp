#include "WorldScene.h"


USING_NS_CC;

Scene* World::createScene()
{
    if(DEBUG_MODE) {
        CCLOG("Create World.");
    }
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = World::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    G->world = scene;
    
    World::theCreation();

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool World::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Get window size
    G->winSize = Director::getInstance()->getWinSize();
    
    // Create main draw node
    G->mainDrawNode[lTypeC] = DrawNode::create();
    G->mainDrawNode[lTypeH] = DrawNode::create();
    G->mainDrawNode[lTypeP] = DrawNode::create();
    
    // Create vision draw node
    G->visionDrawNode = DrawNode::create();
    
    // Create Background
    LayerColor* layer = LayerColor::create(WORLD_COLOR, G->winSize.width, G->winSize.height);
    Size layerSize = layer->getContentSize();
    layer->setPosition(Vec2((G->winSize.width-layerSize.width)*.5, (G->winSize.height-layerSize.height)*.5));
    this->addChild(layer, zBackground);
    
    // Create menu button
    Label* labelMenu = Label::createWithSystemFont("Menu", GAME_FONT, 50);
    MenuItemLabel* menu = MenuItemLabel::create(labelMenu, CC_CALLBACK_1(World::onMenuPressed,this));
    _menuBtn = Menu::create(menu, NULL);
    _menuBtn->setPosition(Vec2(
        G->winSize.width - labelMenu->getContentSize().width,
        G->winSize.height - labelMenu->getContentSize().height
    ));
    this->addChild(_menuBtn, zButton);
    
    // Create menu layer
    _layerMenu = LayerColor::create(Color4B(0, 0, 0, 60), G->winSize.width/3, G->winSize.height);
    _layerMenu->setPosition(Vec2(
        G->winSize.width,
        G->winSize.height - _layerMenu->getContentSize().height
    ));
    this->addChild(_layerMenu, zMenuLayer);
    
    // Create menu items
    this->createMenuItems();
    
    // update
    this->scheduleUpdate();
    
    return true;
}


void World::theCreation()
{
    // Born Plant
    LivingThings* originP = new Plant;
    for(int i=0; i<INIT_AMOUNT_P; i++)
        originP->born(true);
    
    // Born Carnivore
    LivingThings* originC = new Carnivore;
    for(int i=0; i<INIT_AMOUNT_C; i++)
        originC->born(true);
    
    // Born Herbivore
    LivingThings* originH = new Herbivore;
    for(int i=0; i<INIT_AMOUNT_H; i++)
        originH->born(true);
    
    G->world->addChild(G->mainDrawNode[lTypeP], zPlant);
    G->world->addChild(G->mainDrawNode[lTypeC], zCarnivore);
    G->world->addChild(G->mainDrawNode[lTypeH], zHerbivore);
    
    G->world->addChild(G->visionDrawNode, zVision);
    
    delete originP;
    delete originC;
    delete originH;
}

// Game Loop
void World::update(float delta)
{
    G->mainDrawNode[lTypeC]->clear();
    G->mainDrawNode[lTypeH]->clear();
    G->mainDrawNode[lTypeP]->clear();
    G->visionDrawNode->clear();
    
    this->checkGameOver();
    
    std::list<LivingThings *>::iterator itC = G->L[lTypeC].begin();
    while(itC != G->L[lTypeC].end()) {
        (*itC)->breeding();
        (*itC)->randomWalk();
        (*itC)->eat();
        
        if( (*itC)->hunger(itC) ) continue;
        if( (*itC)->aging(itC) ) continue;
        ++itC;
    }
    
    std::list<LivingThings *>::iterator itH = G->L[lTypeH].begin();
    while(itH != G->L[lTypeH].end()) {
        (*itH)->breeding();
        (*itH)->randomWalk();
        (*itH)->eat();
        
        if( (*itH)->hunger(itH) ) continue;
        if( (*itH)->aging(itH) ) continue;
        ++itH;
    }
    
    std::list<LivingThings *>::iterator itP = G->L[lTypeP].begin();
    while(itP != G->L[lTypeP].end()) {
        
        if( (*itP)->aging(itP) ) continue;
        ++itP;
    }
}

void World::createMenuItems(void)
{
    std::vector<Label *> label;
    std::vector<MenuItemLabel *> menuItem;
    
    label.push_back( Label::createWithSystemFont("Visual: C", GAME_FONT, 50) );
    label.push_back( Label::createWithSystemFont("Visual: H", GAME_FONT, 50) );
    label.push_back( Label::createWithSystemFont("Retry", GAME_FONT, 50) );
    label.push_back( Label::createWithSystemFont("Close", GAME_FONT, 50) );
    
    menuItem.push_back( MenuItemLabel::create(label.at(0), CC_CALLBACK_1(World::onVisualPressed,this, lTypeC)) );
    menuItem.push_back( MenuItemLabel::create(label.at(1), CC_CALLBACK_1(World::onVisualPressed,this, lTypeH)) );
    menuItem.push_back( MenuItemLabel::create(label.at(2), CC_CALLBACK_1(World::onRetryPressed,this)) );
    menuItem.push_back( MenuItemLabel::create(label.at(3), CC_CALLBACK_1(World::onMenuClosePressed,this)) );
    
    Menu* menuItems = Menu::create(
        menuItem.at(0),
        menuItem.at(1),
        menuItem.at(2),
        menuItem.at(3),
        NULL
    );

    menuItems->alignItemsVerticallyWithPadding(50);
    menuItems->setPosition(Vec2(_layerMenu->getContentSize().width/2, G->winSize.height - 230));
    _layerMenu->addChild(menuItems, zMenuItems);
    
}

void World::checkGameOver()
{
    unsigned long numP = G->L[lTypeP].size();
    unsigned long numH = G->L[lTypeH].size();
    unsigned long numC = G->L[lTypeC].size();
    
    if( numP <= 0 || numH <= 0 || numC <= 0) {
        Label* gameOver = Label::createWithSystemFont("Game Over", GAME_FONT, 60);
        gameOver->setPosition(Vec2(G->winSize.width/2, G->winSize.height/2));
        this->addChild(gameOver, zButton);
        
        Label* labelRetry = Label::createWithSystemFont("Retry?", GAME_FONT, 60);
        MenuItemLabel* retry = MenuItemLabel::create(labelRetry, CC_CALLBACK_1(World::onRetryPressed,this));
        Menu* menu = Menu::create(retry, NULL);
        menu->setPosition(Vec2(G->winSize.width/2, G->winSize.height/2 - (gameOver->getContentSize().height+50)));
        this->addChild(menu, zButton);
        
        this->pause();
    }
}

void World::onMenuPressed(Ref* sender)
{
    // Blinded menu button.
    _menuBtn->setVisible(false);
    
    MoveTo* action = MoveTo::create(0.3f, Vec2(
        G->winSize.width - _layerMenu->getContentSize().width,
        G->winSize.height - _layerMenu->getContentSize().height
    ));
    _layerMenu->runAction(EaseIn::create(action, 2.0f));
}

void World::onRetryPressed(Ref* sender)
{
    // Reset global data
    delete G;
    G = new Global;
    
    Director* director = Director::getInstance();
    Scene* world = (Scene*) World::createScene();
    director->replaceScene(world);
}

void World::onMenuClosePressed(Ref* sender)
{
    // Make visible menu button.
    _menuBtn->setVisible(true);
    
    MoveTo* action = MoveTo::create(0.3f, Vec2(
        G->winSize.width,
        G->winSize.height - _layerMenu->getContentSize().height
    ));
    _layerMenu->runAction(EaseIn::create(action, 2.0f));
}

void World::onVisualPressed(Ref* sender, int lType)
{
    G->switchVisual(lType);
}