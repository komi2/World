//
//  Herbivore.cpp
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//
#include "Herbivore.h"

USING_NS_CC;

void Herbivore::eat(std::list<LivingThings*> &P)
{
    std::list<LivingThings *>::iterator itP = P.begin();
    while(itP != P.end()) {
        
        float dx = (*itP)->cx - cx;
        float dy = (*itP)->cy - cy;
        float distance = sqrt(dx*dx + dy*dy);
        
        // Eat target prey
        if(distance < size * 2) {
            
            // Die
            delete *itP;
            itP = P.erase(itP);
            CCLOG("%lu", P.size());
        }
        
        ++itP;
    }
}