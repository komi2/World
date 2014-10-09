//
//  Plant.cpp
//  World
//
//  Created by shuhei_komino on 2014/09/18.
//
//

#include "Plant.h"

Plant::Plant() {
    cNormal = CL_NORAML_P;
    cOld = CL_OLD_P;
    zOrder = zPlant;
    size = 4;
    endLife = arc4random() % (MAX_LIFE_P-MIN_LIFE_P) + MIN_LIFE_P;
    type = lTypeP;
    color = cNormal;
}

Plant::~Plant() {
    drawNode->clear();
    G->eraseTarget(this, G->breedingFemaleMap[type]);
    CCLOG("Plant is dead.");
}

bool Plant::aging(std::list<LivingThings *>::iterator &itL)
{
    // Die a Natural death
    if(life > endLife) {
        delete *itL;
        itL = G->L[type].erase(itL);
        ++itL;
        CCLOG("Natural death");
        return true;
        
    } else if ( life == endLife - OLD_POINT ) {
        color = cOld;
    }
    
    ++life;
    return false;
}

void Plant::createSight() {}

LivingThings* Plant::getInstance()
{
    return new LivingThings;
}