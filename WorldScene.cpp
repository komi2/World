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
    
    // Create Background
    LayerColor* layer = LayerColor::create(Color4B(60, 60, 60, 255), G->winSize.width, G->winSize.height);
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
    
    // Born Plant
    for(int i=0; i<initNumP; i++)
        P.push_back(new Plant);

    // Born Carnivore
    for(int i=0; i<initNumC; i++)
        C.push_back(new Carnivore);
    
    // Born Herbivore
    for(int i=0; i<initNumH; i++)
        H.push_back(new Herbivore);
    
    
    std::list<LivingThings *>::iterator itP = P.begin();
    while(itP != P.end()) {
        this->createNode((*itP));
        ++itP;
    }

    std::list<LivingThings *>::iterator itC = C.begin();
    while(itC != C.end()) {
        this->createNode((*itC));
        ++itC;
    }

    std::list<LivingThings *>::iterator itH = H.begin();
    while(itH != H.end()) {
        this->createNode((*itH));
        ++itH;
    }
    
    // update
    this->scheduleUpdate();
    
    return true;
}

// Game Loop
void World::update(float delta)
{
    std::list<LivingThings *>::iterator itC = C.begin();
    while(itC != C.end()) {
        (*itC)->randomWalk();
        (*itC)->eat(H);
        
        itC = (*itC)->aging(itC, C);
        ++itC;
    }
    
    std::list<LivingThings *>::iterator itH = H.begin();
    while(itH != H.end()) {
        (*itH)->randomWalk();
        (*itH)->eat(P);
        
        itH = (*itH)->aging(itH, H);
        ++itH;
    }
    
    std::list<LivingThings *>::iterator itP = P.begin();
    while(itP != P.end()) {
        
        itP = (*itP)->aging(itP, P);
        ++itP;
    }
    
    this->checkGameOver();
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

void World::createNode(LivingThings* L)
{
//    int i = L->index;

    L->drawNode = DrawNode::create();
    L->drawNode->setPosition(Vec2(0, 0));
//    L->drawNode->setTag(i);
    this->addChild(L->drawNode, L->zOrder);
        
    float radius = L->size / 2;
    L->cx = (rand() + (int)radius) % (int) (G->winSize.width - radius);
    L->cy = (rand() + (int)radius) % (int) (G->winSize.height - radius);
    L->drawNode->drawDot(Vec2(L->cx, L->cy), L->size, L->color);
        
    L->createDistination();
}

void World::checkGameOver()
{
    unsigned long numP = P.size();
    unsigned long numH = H.size();
    unsigned long numC = C.size();
    
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