//
//  Plant.cpp
//  World
//
//  Created by shuhei_komino on 2014/09/18.
//
//

#include "Plant.h"

USING_NS_CC;

Plant::Plant() {
    cNormal = CL_NORAML_P;
    cOld = CL_OLD_P;
    cBreeding = CL_BREEDING_P;
    zOrder = zPlant;
    size = 4;
    endLife = arc4random() % (MAX_LIFE_P-MIN_LIFE_P) + MIN_LIFE_P;
    nutrition = arc4random() % (MAX_NUTRITION_P-MIN_NUTRITION_P) + MIN_NUTRITION_P;
    type = lTypeP;
    color = cNormal;
}

Plant::~Plant() {
    CCLOG("Plant is dead.");
    G->eraseTarget(this, G->breedingFemaleMap[type]);
}

bool Plant::aging(std::list<LivingThings *>::iterator &itL)
{
    G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size, color);
    
    // Die a Natural death
    if(life > endLife) {
        delete *itL;
        itL = G->L[type].erase(itL);
        ++itL;
        CCLOG("Natural death");
        G->deathCounter[type][naturalDeath]++;
        return true;
        
    } else if ( life == endLife - OLD_POINT ) {
        color = cOld;
    }
    
    ++life;
    return false;
}

void Plant::breeding()
{
    // Breeding season flag
    if(G->time % 3000 == 0) {
        activity = false;
        color = cBreeding;
    } else if(G->time % 3300 == 0) {
        activity = true;
        color = cNormal;
        breededAmount = 0;
        if(sex == female)
            G->eraseTarget(this, G->breedingFemaleMap[type]);
    }
    
    // Out of breeding season
    if(activity)
        return;
    
    // Change status
    //if(color != cBreeding)
    //    color = cBreeding;
    
    if(sex == male) {
        
        // limied
        if(breededAmount >= 1) return;
        
        std::list<LivingThings*>::iterator it = G->breedingFemaleMap[type].begin();
        while (it != G->breedingFemaleMap[type].end()) {
            if( pow((cx - (*it)->cx), 2.0) + pow((cy - (*it)->cy), 2.0) <= pow(250, 2.0) ) {
                this->crossbreeding(this, (*it));
                break;
            }
            ++it;
        }
        
    } else if(sex == female) {
        
        activity = true;
        G->breedingFemaleMap[type].push_back(this);
        G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size, color);
    }
}

void Plant::crossbreeding(LivingThings* L, LivingThings* tL)
{
    int tmp = 250;
    
    // Reset male data
    L->activity = true;
    L->color = cNormal;
    
    LivingThings* child = tL->born(false);
    
    // Bear a child and genetic
    child->chromosome = this->genetic(L, tL);

    child->cx = arc4random() % (int) (tL->cx+(tmp*2)) + (tL->cx-tmp);
    child->cy = arc4random() % (int) (tL->cy+(tmp*2)) + (tL->cy-tmp);
    
    // Check over window
    while(   child->cx <= size
          || child->cy <= size
          || G->winSize.width-size <= child->cx
          || G->winSize.height-size <= child->cy ) {
        
        child->cx = arc4random() % (int) (tL->cx+(tmp*2)) + (tL->cx-tmp);
        child->cy = arc4random() % (int) (tL->cy+(tmp*2)) + (tL->cy-tmp);
    }

    G->mainDrawNode[type]->drawDot(Vec2(child->cx, child->cy), child->size, child->color);
    
    L->breededAmount++;
}

std::map<DNAType, int> Plant::genetic(LivingThings* L, LivingThings* tL)
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

void Plant::createSight() {}

LivingThings* Plant::getInstance()
{
    return new Plant;
}