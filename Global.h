#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//
//  Global.h
//  World
//
//  Created by shuhei_komino on 2014/10/03.
//
//

#include <stdio.h>
#include "cocos2d.h"
#include "Config.h"

class LivingThings;

class Global
{
public:
    Global();
    
    // World scene
    cocos2d::Scene* world;

    // Living Things
    std::map<livingThingsType, std::list<LivingThings*>> L;
    
    std::map<livingThingsType, cocos2d::DrawNode*> mainDrawNode;
    
//    std::map<livingThingsType, cocos2d::DrawNode*> visionDrawNode;
    cocos2d::DrawNode* visionDrawNode;
    
    // Living Things visual flag
    bool isVisualList[2];
    
    // Window size
    cocos2d::Size winSize;
    
    std::map<livingThingsType, std::list<LivingThings*>> breedingFemaleMap;
    
    void switchVisual(int lType);
    
    // Nearest search
    LivingThings* nearestSearch(LivingThings* L, std::list<LivingThings*> tL);
    
    // Check whether alive
    bool checkAlive(LivingThings* L, std::list<LivingThings*> tL);
    
    void eraseTarget(LivingThings* L, std::list<LivingThings *> &tL);
    
    double pythagoras(double mx, double my, double sx, double sy);
    
    cocos2d::Vec2 sub_vector(cocos2d::Vec2 a, cocos2d::Vec2 b);
    
    bool hitCheckPointPolygon2d(cocos2d::Vec2 A, cocos2d::Vec2 B, cocos2d::Vec2 C, cocos2d::Vec2 P);
};


extern Global* G;

#endif


