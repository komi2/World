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

void Plant::createSight() {}

LivingThings* Plant::getInstance()
{
    return new LivingThings;
}