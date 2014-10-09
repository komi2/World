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
    
    sexType sex;
    livingThingsType type, targetType;
    
    // Point
    double moves, cx, cy, ux, uy, sx, sy;
    
    float speed, normalSpeed, runningSpeed;
    
    int size, zOrder, life, endLife, nutrition, eatingAmount, breededAmount, breedableAmount;
    
    bool isHunting = false,
         activity = true;
    
    cocos2d::Color4F color;

    // Node
    cocos2d::DrawNode* drawNode;
    
    // Get instance
    virtual LivingThings* getInstance();
    
    // Draw
    void born();
    
    // Aging
    virtual bool aging(std::list<LivingThings *>::iterator &itL);
    
    // Check nutrition
    virtual bool hunger(std::list<LivingThings *>::iterator &itL);
    
    virtual void breeding();
    
    virtual void crossbreeding(LivingThings* L, LivingThings* tL);
    
    // Born plants
    void decomposition(LivingThings* L);
    
    virtual void eat();
    
    virtual void hunting();
    
    virtual LivingThings* searchOperation();
    
    void createDistination(bool isRandom);
    
    // Moves
    virtual void randomWalk();
    
    // Create sight
    virtual void createSight();
};


#endif