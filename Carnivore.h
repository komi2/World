//
//  Carnivore.h
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//

#ifndef __CARNIVORE_H__
#define __CARNIVORE_H__

#include "Animal.h"

class Carnivore : public Animal
{
public:
    Carnivore();
    ~Carnivore();
    
    // Get instance
    LivingThings* getInstance();
    void hunting();
};

#endif