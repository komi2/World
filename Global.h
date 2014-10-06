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
#include "LivingThings.h"

class Global
{
public:
    // World scene
    cocos2d::Scene* world;
    
    // Living Things
    std::map<livingThingsType, std::list<LivingThings*>> L;
    
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
};

inline double pythagoras(double mx, double my, double sx, double sy) {
    int dx = mx - sx;
    int dy = my - sy;
    return sqrt(dx*dx + dy*dy);
}

extern Global* G;

#endif


