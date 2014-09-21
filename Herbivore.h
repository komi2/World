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
#include "Plant.h"

class Herbivore : public LivingThings
{
public:
    void eat(std::list<Plant*> &P);
    
    Herbivore() {
        color = cocos2d::Color4F::BLUE;
        zOrder = zHerbivore;
        vh = 70;
        vw = 50;
    }
    
    ~Herbivore() {
        drawNode->clear();
        CCLOG("Herbivore is dead.");
    }
};

#endif