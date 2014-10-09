//
//  Herbivore.h
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//

#ifndef __HERBIVORE_H__
#define __HERBIVORE_H__

#include "Animal.h"

class Herbivore : public Animal
{
public:    
    Herbivore() {
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
        type = lTypeH;
        targetType = lTypeP;
        color = cNormal;
        normalSpeed = NORMAL_SPPED_H;
        runningSpeed = RUNNING_SPEED_H;
    }
    
    ~Herbivore() {
        drawNode->clear();
        G->eraseTarget(this, G->breedingFemaleMap[type]);
        CCLOG("Herbivore is dead.");
    }
    
    // Get instance
    LivingThings* getInstance();
};

#endif