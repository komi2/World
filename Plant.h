//
//  Plant.h
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//

#ifndef __PLANT_H__
#define __PLANT_H__

#include "LivingThings.h"

class Plant : public LivingThings
{
public:
    Plant() {
        cNormal = CL_NORAML_P;
        cOld = CL_OLD_P;
        zOrder = zPlant;
        size = 4;
        endLife = arc4random() % (MAX_LIFE_P-MIN_LIFE_P) + MIN_LIFE_P;
        type = lTypeP;
        color = cNormal;
    }
    
    ~Plant() {
        drawNode->clear();
        G->eraseTarget(this, G->breedingFemaleMap[type]);
        CCLOG("Plant is dead.");
    }
    
    void createSight();
    
    // Get instance
    LivingThings* getInstance();
};

#endif