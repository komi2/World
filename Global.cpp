//
//  Global.cpp
//  World
//
//  Created by shuhei_komino on 2014/10/03.
//
//

#include "Global.h"

Global* G = new Global;

USING_NS_CC;

double Global::pythagoras(double mx, double my, double sx, double sy)
{
    int dx = mx - sx;
    int dy = my - sy;
    return sqrt(dx*dx + dy*dy);
}

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

Vec2 Global::sub_vector(cocos2d::Vec2 a, cocos2d::Vec2 b)
{
    cocos2d::Vec2 ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

bool Global::hitCheckPointPolygon2d(cocos2d::Vec2 A, cocos2d::Vec2 B, cocos2d::Vec2 C, cocos2d::Vec2 P)
{
    cocos2d::Vec2 AB = this->sub_vector(B, A);
    cocos2d::Vec2 BP = this->sub_vector(P, B);
    
    cocos2d::Vec2 BC = this->sub_vector(C, B);
    cocos2d::Vec2 CP = this->sub_vector(P, C);
    
    cocos2d::Vec2 CA = this->sub_vector(A, C);
    cocos2d::Vec2 AP = this->sub_vector(P, A);
    
    // cross product
    double c1 = AB.x*BP.y - AB.y*BP.x;
    double c2 = BC.x*CP.y - BC.y*CP.x;
    double c3 = CA.x*AP.y - CA.y*AP.x;
    
    if( ( c1 > 0 && c2 > 0 && c3 > 0 ) || ( c1 < 0 && c2 < 0 && c3 < 0 ) ) {
        // inside
        return true;
    }
    
    // outside
    return false;
}