//
//  Global.cpp
//  World
//
//  Created by shuhei_komino on 2014/10/03.
//
//

#include "Global.h"

Global* G = new Global;

void Global::switchVisual(int lType)
{
    isVisualList[lType] = ( isVisualList[lType] ) ? false : true ;
}

void Global::eraseTarget(LivingThings* L, std::list<LivingThings *> &tL)
{
    std::list<LivingThings *>::iterator itTL = tL.begin();
    while(itTL != tL.end()) {
        if( (*itTL) == L ) {
            itTL = tL.erase(itTL);
            return;
        }
        ++itTL;
    }
}

bool Global::checkAlive(LivingThings* L, std::list<LivingThings*> tL)
{
    std::list<LivingThings *>::iterator itTL = tL.begin();
    while(itTL != tL.end()) {
        if( (*itTL) == L ) return true;
        ++itTL;
    }
    
    return false;
}

LivingThings* Global::nearestSearch(LivingThings* L, std::list<LivingThings*> tL)
{
    std::list<LivingThings *>::iterator itTL = tL.begin();
    LivingThings* nearestL = (*itTL);
    
    while(itTL != tL.end()) {
        int dx1 = (*itTL)->cx - L->cx;
        int dy1 = (*itTL)->cy - L->cy;
        float distance1 = sqrt( dx1*dx1 + dy1*dy1 );
        
        int dx2 = nearestL->cx - L->cx;
        int dy2 = nearestL->cy - L->cy;
        float distance2 = sqrt( dx2*dx2 + dy2*dy2 );
        
        if( distance1 <= distance2 ) {
            nearestL = (*itTL);
        }
        
        ++itTL;
    }
    
    return nearestL;
}