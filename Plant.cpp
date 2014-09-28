//
//  Plant.cpp
//  World
//
//  Created by shuhei_komino on 2014/09/18.
//
//

#include "Plant.h"

void Plant::aging(Plant* pL, std::list<Plant *> P)
{
    --life;
    if(life < 0) {
        
        delete pL;
        P.erase(pL);
    }
}

void Plant::createSight()
{
}

