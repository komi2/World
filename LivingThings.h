#ifndef __LIVING_THINGS_H__
#define __LIVING_THINGS_H__
//
//  LivingThings.h
//  World
//
//  Created by shuhei_komino on 2014/09/14.
//
//

#include <stdio.h>
#include "cocos2d.h"
#include "Config.h"
#include "Global.h"

class LivingThings
{
public:
    LivingThings();
    virtual ~LivingThings();
    
    // Status color
    cocos2d::Color4F cNormal;
    cocos2d::Color4F cOld;
    cocos2d::Color4F cBreeding;
    
    sexType sex;
    livingThingsType type, targetType;
    
    std::map<DNAType, int> chromosome;
    
    LivingThings* breedingTarget;
    
    // Point
    double moves, cx, cy, ux, uy, sx, sy;
    double groupX = 0, groupY = 0;
    
    float speed, normalSpeed, runningSpeed;
    
    int generation = 0;
    int size, zOrder, life = 0, endLife, nutrition, eatingAmount, breededAmount, breedableAmount;
    
    bool isHunting = false,
         activity = true,
         isBreakTime = false;
    
    cocos2d::Color4F color;

    // Node
    cocos2d::DrawNode* drawNode;
    
    // Draw
    LivingThings* born(bool isBeginning);
    
    void genetic(LivingThings* L, LivingThings* tL, LivingThings* &C);
    
    virtual void fatigueManage();
    
    virtual void behavior();
    
    virtual void search();
    
    // Aging
    virtual bool aging(std::list<LivingThings *>::iterator &itL);
    
    // Check nutrition
    virtual bool hunger(std::list<LivingThings *>::iterator &itL);
    
    virtual void breeding();
    
    virtual void crossbreeding(LivingThings* L, LivingThings* tL);
    
    // Born plants
    void decomposition(LivingThings* L);
    
    virtual bool eat(std::list<LivingThings *>::iterator &itL);
    
    virtual void hunting();
    
    virtual LivingThings* searchOperation();
    
    void createDistination(bool isRandom);
    
    // Moves
    virtual void randomWalk();
    virtual void groupMove();
    virtual void laze();
    
    // Create sight
    virtual void createSight();
};


#endif