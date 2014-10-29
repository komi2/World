//
//  Animal.cpp
//  World
//
//  Created by shuhei_komino on 2014/10/10.
//
//

#include "Animal.h"
#include "Plant.h"

USING_NS_CC;

Animal::Animal()
{
    speed = 1.0;
}

Animal::~Animal() {}

void Animal::behavior()
{
    switch (chromosome[dBehavior]) {
        case loneWolf:
            this->randomWalk();
            break;
            
        case collective:
            // TODO
            this->groupMove();
            break;
            
        case laziness:
            this->laze();
            break;
            
        default:
            CCLOG("ERROR");
            exit(1);
            break;
    }
}

void Animal::fatigueManage()
{
    // Exceptions
    if(isHunting
       || color == cBreeding) {
        isBreakTime = false;
        return;
    }
    
    if(isBreakTime) {
        fatigue -= 2;
        isBreakTime = (fatigue > 0);
        
        // return original speed
        if(speed != normalSpeed)
            speed = normalSpeed;
    } else {
        fatigue++;
        isBreakTime = (fatigue > breakSpan);
        
        // Get tired
//        float a = -1500/normalSpeed;
//        speed = ((breakSpan-fatigue) - 1500) / a;
    }
}

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
            // Bear a child and genetic
            tL->born(false)->chromosome = this->genetic(L, tL);
        }
        
        ++tL->breededAmount;
    }
}

std::map<DNAType, int> Animal::genetic(LivingThings* L, LivingThings* tL)
{
    int P = arc4random() % 1;
    std::map<DNAType, int> nChromosome;
    
    int i = 1;
    for (int DNATypeIt=0; DNATypeIt<sizeof(DNAType); DNATypeIt++) {
        DNAType dnaType = static_cast<DNAType>(DNATypeIt);
        nChromosome[dnaType] = (i%2 == P) ? L->chromosome[dnaType] : tL->chromosome[dnaType];
        i++;
    }
    
    return nChromosome;
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
            
            // Defecate
            if(eatingAmount % 2 == 0)
                this->defecate();
            
            // Die
            G->deathCounter[(*itTL)->type][prey]++;
            delete *itTL;
            itTL = G->L[targetType].erase(itTL);
        }
        
        ++itTL;
    }
}

void Animal::defecate()
{
    LivingThings* plant = new Plant;

    plant->cx = cx;
    plant->cy = cy;
    G->mainDrawNode[lTypeP]->drawDot(Vec2(plant->cx, plant->cy), plant->size, plant->color);
    G->L[lTypeP].push_back(plant);
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
    if(activity && ! isBreakTime) {
        if(moves > 0) {
            moves--;
            cx += ux;
            cy += uy;
        } else {
            this->createDistination(true);
        }
    }
    
    // Hunting mode
    this->hunting();
    
    G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size, color);
    
    this->createSight();
}

void Animal::laze()
{
    if(activity && isHunting) {
        if(moves > 0) {
            moves--;
            cx += ux;
            cy += uy;
        } else {
            this->createDistination(true);
        }
    }
    
    // Hunting mode
    this->hunting();
    
    G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size, color);
    
    this->createSight();
}

void Animal::groupMove()
{
    std::list<LivingThings *>::iterator it = G->group[type].begin();
    
    // If pointer is group leader, random walk
    if(this == (*it)) {
        G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size+4, Color4F::YELLOW);
        if(activity){// && ! isBreakTime) {
            if(moves > 0) {
                moves--;
                cx += ux;
                cy += uy;
            } else {
                this->createDistination(true);
                
                // Initialize other animal
                while(it != G->group[type].end()) {
                    if(this != (*it)) {
                        (*it)->groupX = 0;
                        (*it)->groupY = 0;
                    }
                    ++it;
                }
            }
        }
        
        // Hunting mode
        this->hunting();
        
        G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size, color);
        
        this->createSight();
    } else {
        if(groupX == 0 && groupY == 0) {
            groupX = arc4random() % 200 + ((*it)->cx-100);
            groupY = arc4random() % 200 + ((*it)->cy-100);
            sx = groupX + ((*it)->sx - (*it)->cx);
            sy = groupY + ((*it)->sy - (*it)->cy);
            double dx = sx-cx;
            double dy = sy-cy;
            double distance = sqrt(dx * dx + dy * dy);
            moves = distance / speed;
            ux = dx / moves;
            uy = dy / moves;
        }
    
        if(activity && moves > 0) {
            moves--;
            cx += ux;
            cy += uy;
        }
        
        // Hunting mode
        this->hunting();
        
        G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size+2, Color4F::YELLOW);
        G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size, color);
        
        this->createSight();
    }
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