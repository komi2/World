//
//  Herbivore.h
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//

#ifndef __HERBIVORE_H__
#define __HERBIVORE_H__

#include "Animal.h"

class Herbivore : public Animal
{
public:    
    Herbivore();
    ~Herbivore();
    
    // Get instance
    LivingThings* getInstance();
    void hunting();
};

#endif