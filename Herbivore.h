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
    // Status: normal
    const cocos2d::Color4F NORMAL = CL_NORAML_H;
    // Status: Old
    const cocos2d::Color4F OLD = CL_OLD_H;
    // Status: Breeding
    const cocos2d::Color4F BREEDING = CL_BREEDING_H;
    
    Herbivore() {
        color = NORMAL;
        zOrder = zHerbivore;
        vh = 70;
        vw = 50;
        life = arc4random() % (H_MAX_LIFE-H_MIN_LIFE) + H_MIN_LIFE;
        type = lTypeH;
    }
    
    ~Herbivore() {
        drawNode->clear();
        CCLOG("Herbivore is dead.");
    }
    
    void eat(std::list<LivingThings*> &P);
};

#endif