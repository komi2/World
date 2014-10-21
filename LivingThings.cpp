#include "LivingThings.h"
#include "WorldScene.h"

USING_NS_CC;

LivingThings::LivingThings() {
    color = cocos2d::Color4F::WHITE;
    size = 6;
    sex = (arc4random() % 2) ? male : female ;
}

LivingThings::~LivingThings() {}

void LivingThings::fatigueManage() {}

void LivingThings::crossbreeding(LivingThings* L, LivingThings* tL) {}

void LivingThings::breeding() {}

void LivingThings::born(bool isBeginning)
{
    // New object
    LivingThings* newL = this->getInstance();
    
    if(isBeginning) {
        float radius = newL->size / 2;
        newL->cx = (rand() + (int)radius) % (int) (G->winSize.width - radius);
        newL->cy = (rand() + (int)radius) % (int) (G->winSize.height - radius);
    } else {
        // Point of my parent
        newL->cx = cx;
        newL->cy = cy;
    }

    G->mainDrawNode[newL->type]->drawDot(Vec2(newL->cx, newL->cy), newL->size, newL->color);
    
    newL->createDistination(true);
    
    // Push data
    G->L[newL->type].push_back(newL);
}

void LivingThings::eat() {}

bool LivingThings::hunger(std::list<LivingThings *>::iterator &itL) {}

bool LivingThings::aging(std::list<LivingThings *>::iterator &itL) {}

void LivingThings::hunting() {}

LivingThings* LivingThings::searchOperation() {}

void LivingThings::randomWalk() {}

void LivingThings::createDistination(bool isRandom)
{
    // Get new goal point
    if(isRandom) {
        float radius = size / 2;
        sx = (arc4random() + (int)radius) % (int)(G->winSize.width - radius);
        sy = (arc4random() + (int)radius) % (int)(G->winSize.height - radius);
    }
    
    double dx = sx - cx;
    double dy = sy - cy;
    double distance = sqrt(dx * dx + dy * dy);
    moves = distance / speed;
    ux = dx / moves;
    uy = dy / moves;
}

void LivingThings::createSight() {}

void LivingThings::decomposition(LivingThings* L)
{
    // Plant is an exception
    if(L->type == lTypeP) return;
    
    double distance = 25.;
    double bornX, bornY;
    for(int i=0; i < 4; ++i) {
        switch (i) {
            case 0:
                bornX = L->cx;
                bornY = L->cy + distance;
                break;
            case 1:
                bornX = L->cx + distance;
                bornY = L->cy;
                break;
            case 2:
                bornX = L->cx;
                bornY = L->cy - distance;
                break;
            case 3:
                bornX = L->cx - distance;
                bornY = L->cy;
                break;
        }
        
        // Check over window
        if(bornX <= 0 || G->winSize.width <= bornX) continue;
        if(bornY <= 0 || G->winSize.height <= bornY) continue;
        
        LivingThings* plant = new Plant;

        plant->cx = bornX;
        plant->cy = bornY;
        G->mainDrawNode[lTypeP]->drawDot(Vec2(plant->cx, plant->cy), plant->size, plant->color);
        G->L[lTypeP].push_back(plant);
    }
}

LivingThings* LivingThings::getInstance(){}