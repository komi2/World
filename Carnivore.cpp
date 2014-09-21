//
//  Carnivore.cpp
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//
#include "Carnivore.h"

USING_NS_CC;

void Carnivore::eat(std::list<Herbivore*> &H)
{
    std::list<Herbivore *>::iterator itH = H.begin();
    while(itH != H.end()) {
        
        float dx = (*itH)->cx - cx;
        float dy = (*itH)->cy - cy;
        float distance = sqrt(dx*dx + dy*dy);
       
        // Eat target prey
        if(distance < size * 2) {
            
            // Die
            delete *itH;
            itH = H.erase(itH);
        }
        
        ++itH;
    }
}