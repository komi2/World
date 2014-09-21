#include "LivingThings.h"
#include "WorldScene.h"

USING_NS_CC;

void LivingThings::randomWalk(Size winSize)
{
    if(moves > 0) {
        moves--;
        cx += ux;
        cy += uy;
    } else {
        this->createDistination(winSize);
    }
    
    drawNode->clear();
    drawNode->drawDot(Vec2(cx, cy), size, color);
    this->createSight();
}

void LivingThings::createDistination(Size winSize)
{
    float radius = size / 2;
    
    // Get goal point
    sx = (arc4random() + (int)radius) % (int)(winSize.width - radius);
    sy = (arc4random() + (int)radius) % (int)(winSize.height - radius);
    
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

    //drawNode->drawTriangle(Vec2(cx, cy), Vec2(LX, LY), Vec2(RX, RY), Color4F(1,1,0,0.3));
}