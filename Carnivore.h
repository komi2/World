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
    // Status: normal
    const cocos2d::Color4F NORMAL = CL_NORAML_C;
    // Status: Old
    const cocos2d::Color4F OLD = CL_OLD_C;
    // Status: Breeding
    const cocos2d::Color4F BREEDING = CL_BREEDING_C;
    
    Carnivore() {
        color = NORMAL;
        zOrder = zCarnivore;
        vh = 70;
        vw = 20;
        life = arc4random() % (C_MAX_LIFE-C_MIN_LIFE) + C_MIN_LIFE;
        type = lTypeC;
    }
    
    ~Carnivore() {
        drawNode->clear();
        CCLOG("Carnivore is dead.");
    }
    
    void eat(std::list<LivingThings *> &H);
};

#endif