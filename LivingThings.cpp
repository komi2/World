#include "LivingThings.h"
#include "WorldScene.h"

USING_NS_CC;

void LivingThings::eat(std::list<LivingThings*> &tL)
{
    std::list<LivingThings *>::iterator itTL = tL.begin();
    while(itTL != tL.end()) {
        
        float dx = (*itTL)->cx - cx;
        float dy = (*itTL)->cy - cy;
        float distance = sqrt(dx*dx + dy*dy);
        
        // Eat target prey
        if(distance < size * 2) {
            
            // Get nutrition
            nutrition += (*itTL)->nutrition / NUTRITION_DIV_POINT;
            
            // Die
            delete *itTL;
            itTL = tL.erase(itTL);
        }
        
        ++itTL;
    }
}

bool LivingThings::hunger(std::list<LivingThings *>::iterator &itL, std::list<LivingThings *> &L)
{
    // Starvation
    if(nutrition < 0) {
        delete *itL;
        itL = L.erase(itL);
        ++itL;
        CCLOG("Starvation");
        return true;
    }
    
    --nutrition;
    return false;
}

bool LivingThings::aging(std::list<LivingThings *>::iterator &itL, std::list<LivingThings*> &L)
{
    // Die a Natural death
    if(life < 0) {
        delete *itL;
        itL = L.erase(itL);
        ++itL;
        CCLOG("Natural death");
        return true;
    } else if ( life == OLD_POINT ) {
        color = cOld;
        speed = speed - speed / 3;
    }

    --life;
    return false;
}

void LivingThings::randomWalk()
{
    if(moves > 0) {
        moves--;
        cx += ux;
        cy += uy;
    } else {
        this->createDistination();
    }
    
    drawNode->clear();
    
    // Hunting mode
    if(hunting) drawNode->drawDot(Vec2(cx, cy), size + 1, Color4F::WHITE);
    drawNode->drawDot(Vec2(cx, cy), size, color);

    if( G->isVisualList[type] ) {
        this->createSight();
    }
}

void LivingThings::createDistination()
{
    float radius = size / 2;
    
    // Get goal point
    sx = (arc4random() + (int)radius) % (int)(G->winSize.width - radius);
    sy = (arc4random() + (int)radius) % (int)(G->winSize.height - radius);
    
    double dx = sx - cx;
    double dy = sy - cy;
    double distance = sqrt(dx * dx + dy * dy);
    moves = distance / speed;
    ux = dx / moves;
    uy = dy / moves;
}

void LivingThings::createSight()
{
    double h = sqrt(vh*vh + vw*vw);

    double rad1 = atan2((sy-cy), (sx-cx));
    double rad2 = atan2(vw, vh);
    double rad = rad1 + rad2;
    
    double LX = (cos(rad) * h) + cx;
    double LY = (sin(rad) * h) + cy;
    
    rad = rad1 - rad2;
    double RX = (cos(rad) * h) + cx;
    double RY = (sin(rad) * h) + cy;

    drawNode->drawTriangle(Vec2(cx, cy), Vec2(LX, LY), Vec2(RX, RY), Color4F(1,1,1,0.2));
}