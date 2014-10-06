//
//  Herbivore.h
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//

#ifndef __HERBIVORE_H__
#define __HERBIVORE_H__

#include "LivingThings.h"

class Herbivore : public LivingThings
{
public:    
    Herbivore() {
        cNormal = CL_NORAML_H;
        cOld = CL_OLD_H;
        cBreeding = CL_BREEDING_H;
        zOrder = zHerbivore;
        vh = 70;
        vw = 50;
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