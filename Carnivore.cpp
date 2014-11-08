//
//  Carnivore.cpp
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//
#include "Carnivore.h"

USING_NS_CC;

Carnivore::Carnivore() {
    cNormal = CL_NORAML_C;
    cOld = CL_OLD_C;
    cBreeding = CL_BREEDING_C;
    zOrder = zCarnivore;
    vh = VISUAL_DISTANCE_C;
    vw = VISUAL_WIDTH_C;
    vhNormal =VISUAL_DISTANCE_C;
    vwNormal =VISUAL_WIDTH_C;
    vhHunting = VISUAL_DISTANCE_HUNTING_C;
    vwHunting = VISUAL_WIDTH_HUNTING_C;
    endLife = arc4random() % (MAX_LIFE_C-MIN_LIFE_C) + MIN_LIFE_C;
    breedableAmount = arc4random() % (BREEDING_MAX_AMOUNT_C-BREEDING_MIN_AMOUNT_C) + BREEDING_MIN_AMOUNT_C;
    nutrition = arc4random() % (MAX_NUTRITION_C-MIN_NUTRITION_C) + MIN_NUTRITION_C;
    type = lTypeC;
    targetType = lTypeH;
    color = cNormal;
    normalSpeed = NORMAL_SPPED_C;
    runningSpeed = RUNNING_SPEED_C;
}

Carnivore::~Carnivore() {
    CCLOG("Carnivore is dead.");
    G->eraseTarget(this, G->breedingFemaleMap[type]);
    G->eraseTarget(this, G->group[type]);
}

void Carnivore::hunting()
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
    G->mainDrawNode[type]->drawDot(Vec2(cx, cy), size + 1, Color4F::WHITE);
    
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