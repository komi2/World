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
        life = arc4random() % (H_MAX_LIFE-H_MIN_LIFE) + H_MIN_LIFE;
        type = lTypeH;
        color = cNormal;
    }
    
    ~Herbivore() {
        drawNode->clear();
        CCLOG("Herbivore is dead.");
    }
};

#endif