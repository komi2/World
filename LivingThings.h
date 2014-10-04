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
    LivingThings() {
        color = cocos2d::Color4F::WHITE;
        
        size = 6;
        speed = 1.0f;
        sex = (arc4random() % 2) ? male : female ;
        hunting = false;
        nutrition = 2000;
    }
    
    virtual ~LivingThings() {}
    
    // Status color
    cocos2d::Color4F cNormal;
    cocos2d::Color4F cOld;
    cocos2d::Color4F cBreeding;
    
    // Point
    double moves, cx, cy, ux, uy, sx, sy;
    
    // Viewing angle
    double vh, vw;
    
    float speed;
    
    int size, zOrder, life, sex, type, nutrition;
    
    bool hunting;
    
    cocos2d::Color4F color;

    // Node
    cocos2d::DrawNode* drawNode;
    
    // Draw
    void born();
    
    // Aging
    bool aging(std::list<LivingThings *>::iterator &itL, std::list<LivingThings *> &L);
    
    // Check nutrition
    bool hunger(std::list<LivingThings *>::iterator &itL, std::list<LivingThings *> &L);
    
    /**
    @param Target Liging Things
    */
    void eat(std::list<LivingThings*> &tL);
    
    void createDistination();
    
    // Moves
    void randomWalk();
    
    // Create sight
    void createSight();
};


#endif