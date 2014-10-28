//
//  Herbivore.cpp
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//
#include "Herbivore.h"

USING_NS_CC;

Herbivore::Herbivore() {
    cNormal = CL_NORAML_H;
    cOld = CL_OLD_H;
    cBreeding = CL_BREEDING_H;
    zOrder = zHerbivore;
    vh = VISUAL_DISTANCE_H;
    vw = VISUAL_WIDTH_H;
    vhNormal =VISUAL_DISTANCE_H;
    vwNormal =VISUAL_WIDTH_H;
    vhHunting = VISUAL_DISTANCE_HUNTING_H;
    vwHunting = VISUAL_WIDTH_HUNTING_H;
    endLife = arc4random() % (MAX_LIFE_H-MIN_LIFE_H) + MIN_LIFE_H;
    breedableAmount = arc4random() % (BREEDING_MAX_AMOUNT_H-BREEDING_MIN_AMOUNT_H) + BREEDING_MIN_AMOUNT_H;
    nutrition = arc4random() % (MAX_NUTRITION_H-MIN_NUTRITION_H) + MIN_NUTRITION_H;
    type = lTypeH;
    targetType = lTypeP;
    color = cNormal;
    normalSpeed = NORMAL_SPPED_H;
    runningSpeed = RUNNING_SPEED_H;
}

Herbivore::~Herbivore() {
    G->eraseTarget(this, G->breedingFemaleMap[type]);
    G->eraseTarget(this, G->group[type]);
    CCLOG("Herbivore is dead.");
}

LivingThings* Herbivore::getInstance()
{
    return new Herbivore;
}

void Herbivore::hunting()
{
    if( ! isHunting) {
        vh = vhNormal;
        vw = vwNormal;
        speed = normalSpeed;
        return;
    }
    
    // statisfied stomach
    if( nutrition > HUNTING_POINT ) {
        isHunting = false;
        return;
    }
    
    // long range
    vh = vhHunting;
    vw = vwHunting;
    speed = runningSpeed;
    
    if(huntingTarget == NULL) {
        huntingTarget = this->searchOperation();
    }
    
    // Not found target
    if(huntingTarget == NULL) return;
    
    if( ! G->checkAlive(huntingTarget, G->L[targetType]) ) {
        this->createDistination(true);
        huntingTarget = NULL;
        return;
    }
    
    // Lock on
    sx = huntingTarget->cx;
    sy = huntingTarget->cy;
    this->createDistination(false);
}