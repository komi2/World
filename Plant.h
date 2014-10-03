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
        color = cocos2d::Color4F::GREEN;
        zOrder = zPlant;
        size = 4;
        life = arc4random() % (P_MAX_LIFE-P_MIN_LIFE) + P_MIN_LIFE;
        type = lTypeP;
    }
    
    ~Plant() {
        drawNode->clear();
        CCLOG("Plant is dead.");
    }
    
    void createSight();
};

#endif