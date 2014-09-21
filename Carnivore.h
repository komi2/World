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
#include "Herbivore.h"

class Carnivore : public LivingThings
{
public:
    void eat(std::list<Herbivore *> &H);
    
    Carnivore() {
        color = cocos2d::Color4F::RED;
        zOrder = zCarnivore;
        vh = 70;
        vw = 20;
    }
};

#endif