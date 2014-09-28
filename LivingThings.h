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

class LivingThings
{
public:
    // Point
    double moves, cx, cy, ux, uy, sx, sy;
    
    // Viewing angle
    double vh, vw;
    
    float speed;
    
    int size, zOrder, life, sex;
    
    cocos2d::Color4F color;

    // Node
    cocos2d::DrawNode* drawNode;
    
    // Draw
    void born();
    
    void aging(LivingThings* pL);
    
    void createDistination(cocos2d::Size winSize);
    
    // Moves
    void randomWalk(cocos2d::Size winSize);
    
    // Create sight
    void createSight();
    
    LivingThings() {
        color = cocos2d::Color4F::WHITE;

        size = 6;
        speed = 1.0f;
        sex = (arc4random() % 2) ? male : female ;
        
        life = arc4random() % 40;
    }
};


#endif