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
    type = lTypeC;
    targetType = lTypeH;
    color = cNormal;
    normalSpeed = NORMAL_SPPED_C;
    runningSpeed = RUNNING_SPEED_C;
}

Carnivore::~Carnivore() {
    drawNode->clear();
    CCLOG("Carnivore is dead.");
}

LivingThings* Carnivore::getInstance()
{
    return new Carnivore;
}