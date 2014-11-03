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
    
    // Vector of sight
    cocos2d::Vec2 VL, VR;
    
    LivingThings* huntingTarget;
    
    // Viewing angle
    double vh, vw, vhNormal, vwNormal, vhHunting, vwHunting;
    
    int fatigue = 0;
    int breakSpan = arc4random() % (4000) + 1500;
    
    std::map<DNAType, int> genetic(LivingThings* L, LivingThings* tL);
    void behavior();
    void fatigueManage();
    bool aging(std::list<LivingThings *>::iterator &itL);
    void breeding();
    void crossbreeding(LivingThings* L, LivingThings* tL);
    void eat();
    void defecate();
    bool hunger(std::list<LivingThings *>::iterator &itL);
    void randomWalk();
    void groupMove();
    void laze();
    void createSight();
    LivingThings* searchOperation();
};

#endif