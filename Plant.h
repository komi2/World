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
    Plant();
    ~Plant();
    
    bool aging(std::list<LivingThings *>::iterator &itL);
    void createSight();
    void breeding();
    void crossbreeding(LivingThings* L, LivingThings* tL);
};

#endif