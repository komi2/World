//
//  Carnivore.h
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//

#ifndef __CARNIVORE_H__
#define __CARNIVORE_H__

#include "LivingThings.h"

class Carnivore : public LivingThings
{
public:
    Carnivore() {
        cNormal = CL_NORAML_C;
        cOld = CL_OLD_C;
        cBreeding = CL_BREEDING_C;
        zOrder = zCarnivore;
        vh = 70;
        vw = 20;
        life = arc4random() % (C_MAX_LIFE-C_MIN_LIFE) + C_MIN_LIFE;
        type = lTypeC;
        color = cNormal;
    }
    
    ~Carnivore() {
        drawNode->clear();
        CCLOG("Carnivore is dead.");
    }
    
    void eat(std::list<LivingThings *> &H);
};

#endif