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
    
    // Vector of sight
    cocos2d::Vec2 VL, VR;
    
    sexType sex;
    livingThingsType type, targetType;
    
    LivingThings* breedingTarget;
    LivingThings* huntingTarget;
    
    // Point
    double moves, cx, cy, ux, uy, sx, sy;
    
    // Viewing angle
    double vh, vw, vhNormal, vwNormal, vhHunting, vwHunting;
    
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
    bool aging(std::list<LivingThings *>::iterator &itL);
    
    // Check nutrition
    bool hunger(std::list<LivingThings *>::iterator &itL);
    
    void breeding();
    
    void crossbreeding(LivingThings* L, LivingThings* tL);
    
    // Born plants
    void decomposition(LivingThings* L);
    
    void eat();
    
    void hunting();
    
    LivingThings* searchOperation();
    
    void createDistination(bool isRandom);
    
    // Moves
    void randomWalk();
    
    // Create sight
    void createSight();
};


#endif