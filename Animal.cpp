//
//  Animal.cpp
//  World
//
//  Created by shuhei_komino on 2014/10/10.
//
//

#include "Animal.h"

USING_NS_CC;

Animal::Animal()
{
    speed = 1.0;
}

Animal::~Animal() {}

bool Animal::aging(std::list<LivingThings *>::iterator &itL)
{
    // Die a Natural death
    if(life > endLife) {
        // Carcass become a plant
        this->decomposition( (*itL) );
        
        delete *itL;
        itL = G->L[type].erase(itL);
        ++itL;
        CCLOG("Natural death");
        G->deathCounter[type][naturalDeath]++;
        return true;
        
    } else if ( life == endLife - OLD_POINT ) {
        color = cOld;
        speed = speed - speed / 3;
    }
    
    ++life;
    return false;
}

void Animal::breeding()
{
    // Check condition
    bool isOK = false;
    if(eatingAmount >= GOAL_EATING_AMOUNT) {
        
        if(isHunting || color == cOld) return;
        
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
        
        //drawNode->clear();
        G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size, color);
    }
}

void Animal::crossbreeding(LivingThings* L, LivingThings* tL)
{
    float distance = G->pythagoras(L->cx, L->cy, tL->cx, tL->cy);
    if(distance < size * 2) {
        // Reset male data
        L->eatingAmount = 0;
        L->speed = normalSpeed;
        L->createDistination(true);
        
        for(int i = 0; i < tL->breedableAmount; ++i) {
            tL->born(false);
        }
        
        ++tL->breededAmount;
    }
}

void Animal::eat()
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
            G->deathCounter[(*itTL)->type][prey]++;
            delete *itTL;
            itTL = G->L[targetType].erase(itTL);
        }
        
        ++itTL;
    }
}

bool Animal::hunger(std::list<LivingThings *>::iterator &itL)
{
    // Starvation
    if(nutrition < 0) {
        delete *itL;
        itL = G->L[type].erase(itL);
        ++itL;
        CCLOG("Starvation");
        G->deathCounter[type][starvation]++;
        return true;
    } else if( nutrition == HUNTING_POINT ) {
        isHunting = true;
    }
    
    --nutrition;
    return false;
}

void Animal::randomWalk()
{
    if(activity) {
        if(moves > 0) {
            moves--;
            cx += ux;
            cy += uy;
        } else {
            this->createDistination(true);
        }
    }
    
    //drawNode->clear();
    
    // Hunting mode
    this->hunting();
    
    G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size, color);
    
    this->createSight();
}

void Animal::createSight()
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
    
    VR = Vec2(RX, RY);
    VL = Vec2(LX, LY);
    
    Color4F sightColor = (G->isVisualList[type]) ? Color4F(1,1,1,0.2) : Color4F(0,0,0,0) ;
    
    G->visionDrawNode->drawTriangle(Vec2(cx, cy), VL, VR, sightColor);
}

LivingThings* Animal::searchOperation()
{
    std::list<LivingThings *>::iterator itTL = G->L[targetType].begin();
    while(itTL != G->L[targetType].end()) {
        if( G->hitCheckPointPolygon2d(Vec2(cx, cy), VR, VL, Vec2((*itTL)->cx, (*itTL)->cy)) ) {
            return (*itTL);
        }
        ++itTL;
    }
    
    return NULL;
}