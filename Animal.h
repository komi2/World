//
//  Animal.h
//  World
//
//  Created by shuhei_komino on 2014/10/10.
//
//

#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "LivingThings.h"

class Animal : public LivingThings
{
public:
    Animal();
    ~Animal();
    
    // Status color
    cocos2d::Color4F cBreeding;
    
    // Vector of sight
    cocos2d::Vec2 VL, VR;
    
    LivingThings* breedingTarget;
    LivingThings* huntingTarget;
    
    // Viewing angle
    double vh, vw, vhNormal, vwNormal, vhHunting, vwHunting;
    
    int fatigue = 0;
    int breakSpan = arc4random() % (3000) + 500;
    
    void fatigueManage();
    bool aging(std::list<LivingThings *>::iterator &itL);
    void breeding();
    void crossbreeding(LivingThings* L, LivingThings* tL);
    void eat();
    void defecate();
    bool hunger(std::list<LivingThings *>::iterator &itL);
    void randomWalk();
    void createSight();
    LivingThings* searchOperation();
};

#endif