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
    this->_winSize = Director::getInstance()->getWinSize();
    
    // Create Background
    LayerColor* layer = LayerColor::create(Color4B(60, 60, 60, 255), _winSize.width, _winSize.height);
    Size layerSize = layer->getContentSize();
    layer->setPosition(Vec2((_winSize.width-layerSize.width)*.5, (_winSize.height-layerSize.height)*.5));
    this->addChild(layer, zBackground);
    
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
        (*itC)->randomWalk(_winSize);
        (*itC)->eat(H);
        
        itC = (*itC)->aging(itC, C);
        ++itC;
    }
    
    std::list<LivingThings *>::iterator itH = H.begin();
    while(itH != H.end()) {
        (*itH)->randomWalk(_winSize);
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

// Create Node
void World::createNode(LivingThings* L)
{
//    int i = L->index;

    L->drawNode = DrawNode::create();
    L->drawNode->setPosition(Vec2(0, 0));
//    L->drawNode->setTag(i);
    this->addChild(L->drawNode, L->zOrder);
        
    float radius = L->size / 2;
    L->cx = (rand() + (int)radius) % (int) (_winSize.width - radius);
    L->cy = (rand() + (int)radius) % (int) (_winSize.height - radius);
    L->drawNode->drawDot(Vec2(L->cx, L->cy), L->size, L->color);
        
    L->createDistination(_winSize);
}

void World::checkGameOver()
{
    unsigned long numP = P.size();
    unsigned long numH = H.size();
    unsigned long numC = C.size();
    
    if( numP <= 0 || numH <= 0 || numC <= 0) {
        Label* gameOver = Label::createWithSystemFont("Game Over", "HiraKakuProN-W6", 60);
        gameOver->setPosition(Vec2(_winSize.width/2, _winSize.height/2));
        this->addChild(gameOver, 10);
        
        Label* labelRetry = Label::createWithSystemFont("Retry?", "HiraKakuProN-W6", 60);
        MenuItemLabel* retry = MenuItemLabel::create(labelRetry, CC_CALLBACK_1(World::onRetryPressed,this));
        Menu* menu = Menu::create(retry, NULL);
        menu->setPosition(Vec2(_winSize.width/2, _winSize.height/2 - (gameOver->getContentSize().height+50)));
        this->addChild(menu, 10);
        
        this->pause();
    }
}

void World::onRetryPressed(Ref* sender)
{
    Director* director = Director::getInstance();
    Scene* world = (Scene*) World::createScene();
    director->replaceScene(world);
}