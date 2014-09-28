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
    void aging(Plant* pL, std::list<Plant *> P);
    
    Plant() {
        color = cocos2d::Color4F::GREEN;
        zOrder = zPlant;
        size = 4;
    }
    
    ~Plant() {
        drawNode->clear();
        CCLOG("Plant is dead.");
    }
    
    void createSight();
};

#endif