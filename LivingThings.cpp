#include "LivingThings.h"
#include "WorldScene.h"

USING_NS_CC;

void LivingThings::breeding()
{
    // Check condition
    bool isOK = false;
    if(eatingAmount >= GOAL_EATING_AMOUNT) {
        int season1 = endLife / 4;
        int season2 = season1 * 3;
        bool condition1 = (season1 < life && life < season1 + F_BREEDING);
        bool condition2 = (season2 < life && life < season2 + F_BREEDING);
        
        isOK = (condition1 || condition2);
        
        // End one season breeding (female)
        if(breededAmount >= BREEDABLE_MAX_AMOUNT && color == cBreeding) {
            color = cNormal;
            this->createDistination(true);
            activity = true;
            G->eraseTarget(this, G->breedingFemaleMap[type]);
            return;
        } else if(breededAmount >= BREEDABLE_MAX_AMOUNT && isOK) {
            return;
        }
    }
    
    // Out of breeding season
    if( ! isOK) {
        if(color == cBreeding) {
            breededAmount = 0;
            color = cNormal;
            speed = normalSpeed;
            activity = true;
            if(sex == female) G->eraseTarget(this, G->breedingFemaleMap[type]);
            this->createDistination(true);
        }
        return;
    }
    
    // Change status
    if(color != cBreeding) color = cBreeding;
    
    if(sex == male) {
        if(breedingTarget == NULL) {
            breedingTarget = G->nearestSearch(this, G->breedingFemaleMap[type]);
        }
        
        // No females..
        if(breedingTarget == NULL) return;
        
        // Check female whether alive
        if( ! G->checkAlive(breedingTarget, G->breedingFemaleMap[type]) ) {
            breedingTarget = NULL;
            this->createDistination(true);
            return;
        }
        
        // Change Speed
        speed = runningSpeed;
        
        sx = breedingTarget->cx;
        sy = breedingTarget->cy;
        this->createDistination(false);
        this->crossbreeding(this, breedingTarget);
        
    } else if(sex == female) {
        if( ! activity) return;
        
        activity = false;
        G->breedingFemaleMap[type].push_back(this);
        
        drawNode->clear();
        drawNode->drawDot(Vec2(cx, cy), size, color);
    }
}

void LivingThings::crossbreeding(LivingThings* L, LivingThings* tL)
{
    float distance = pythagoras(L->cx, L->cy, tL->cx, tL->cy);
    if(distance < size * 2) {
        // Reset male data
        L->eatingAmount = 0;
        L->speed = normalSpeed;
        L->createDistination(true);
        
        for(int i = 0; i < tL->breedableAmount; ++i) {
            tL->born();
        }
        
        ++tL->breededAmount;
    }
}

void LivingThings::born()
{
    // New object
    LivingThings* newL = this->getInstance();
    
    newL->drawNode = DrawNode::create();
    newL->drawNode->setPosition(Vec2(0, 0));
    G->world->addChild(newL->drawNode, newL->zOrder);
    
    // Point of my parent
    newL->cx = cx;
    newL->cy = cy;
    newL->drawNode->drawDot(Vec2(newL->cx, newL->cy), newL->size, newL->color);
    
    newL->createDistination(true);
    
    // Push data
    G->L[newL->type].push_back(newL);
}

void LivingThings::eat()
{
    std::list<LivingThings *>::iterator itTL = G->L[targetType].begin();
    while(itTL != G->L[targetType].end()) {
        
        float dx = (*itTL)->cx - cx;
        float dy = (*itTL)->cy - cy;
        float distance = sqrt(dx*dx + dy*dy);
        
        // Eat target prey
        if(distance < size * 2) {
            
            // Get nutrition
            nutrition += (*itTL)->nutrition / NUTRITION_DIV_POINT;
            ++eatingAmount;
            
            // Die
            delete *itTL;
            itTL = G->L[targetType].erase(itTL);
        }
        
        ++itTL;
    }
}

bool LivingThings::hunger(std::list<LivingThings *>::iterator &itL)
{
    // Starvation
    if(nutrition < 0) {
        delete *itL;
        itL = G->L[type].erase(itL);
        ++itL;
        CCLOG("Starvation");
        return true;
    }
    
    --nutrition;
    return false;
}

bool LivingThings::aging(std::list<LivingThings *>::iterator &itL)
{
    // Die a Natural death
    if(life > endLife) {
        // Carcass become a plant
        this->decomposition( (*itL) );

        delete *itL;
        itL = G->L[type].erase(itL);
        ++itL;
        CCLOG("Natural death");
        return true;
        
    } else if ( life == endLife - OLD_POINT ) {
        color = cOld;
        speed = speed - speed / 3;
    }

    ++life;
    return false;
}

void LivingThings::randomWalk()
{
    if( ! activity) return;
    
    if(moves > 0) {
        moves--;
        cx += ux;
        cy += uy;
    } else {
        this->createDistination(true);
    }
    
    drawNode->clear();
    
    // Hunting mode
    if(hunting) drawNode->drawDot(Vec2(cx, cy), size + 1, Color4F::WHITE);
    drawNode->drawDot(Vec2(cx, cy), size, color);

    if( G->isVisualList[type] ) {
        this->createSight();
    }
}

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

void LivingThings::createSight()
{
    double h = sqrt(vh*vh + vw*vw);

    double rad1 = atan2((sy-cy), (sx-cx));
    double rad2 = atan2(vw, vh);
    double rad = rad1 + rad2;
    
    double LX = (cos(rad) * h) + cx;
    double LY = (sin(rad) * h) + cy;
    
    rad = rad1 - rad2;
    double RX = (cos(rad) * h) + cx;
    double RY = (sin(rad) * h) + cy;

    drawNode->drawTriangle(Vec2(cx, cy), Vec2(LX, LY), Vec2(RX, RY), Color4F(1,1,1,0.2));
}

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
        plant->drawNode = DrawNode::create();
        plant->drawNode->setPosition(Vec2(0, 0));
        G->world->addChild(plant->drawNode, plant->zOrder);
    

        plant->cx = bornX;
        plant->cy = bornY;
        plant->drawNode->drawDot(Vec2(plant->cx, plant->cy), plant->size, plant->color);
        G->L[lTypeP].push_back(plant);
    }
}

LivingThings* LivingThings::getInstance()
{
    return new LivingThings;
}