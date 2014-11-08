#include "LivingThings.h"
#include "WorldScene.h"

USING_NS_CC;

LivingThings::LivingThings() {
    color = cocos2d::Color4F::WHITE;
    size = 6;
    sex = (arc4random() % 2) ? male : female ;
}

LivingThings::~LivingThings() {}

void LivingThings::behavior() {}

void LivingThings::search() {}

void LivingThings::fatigueManage() {}

void LivingThings::crossbreeding(LivingThings* L, LivingThings* tL) {}

void LivingThings::breeding() {}

LivingThings* LivingThings::born(bool isBeginning)
{
    // New object
    LivingThings* newL = G->getMyInstance(type);
    
    if(isBeginning) {
        float radius = newL->size / 2;
        newL->cx = (rand() + (int)radius) % (int) (G->winSize.width - radius);
        newL->cy = (rand() + (int)radius) % (int) (G->winSize.height - radius);
        
        // Create chromosome
        // Decide behavior type
        newL->chromosome[dBehavior] = arc4random() % (sizeof(behaviorType)-1);
        // If befavior type is collective, push data
        if(newL->chromosome[dBehavior] == collective) {
            G->group[newL->type].push_back(newL);
        }
        
        // Decide vision type
        newL->chromosome[dVision] = arc4random() % (sizeof(visionType)-1);
        
        // Initialize venom level
        newL->chromosome[dVenom] = venomZero;
    } else {
        // Point of my parent
        newL->cx = cx;
        newL->cy = cy;
    }

    G->mainDrawNode[newL->type]->drawDot(Vec2(newL->cx, newL->cy), newL->size, newL->color);
    
    newL->createDistination(true);
    
    // Push data
    G->L[newL->type].push_back(newL);
    
    return newL;
}

void LivingThings::genetic(LivingThings* L, LivingThings* tL, LivingThings* &C)
{
    G->geneticCounter[type]++;
    
    int P = arc4random() % 1;
    
    int i = 1;
    for (int DNATypeIt=0; DNATypeIt<sizeof(DNAType); DNATypeIt++) {
        DNAType dnaType = static_cast<DNAType>(DNATypeIt);
        C->chromosome[dnaType] = (i%2 == P) ? L->chromosome[dnaType] : tL->chromosome[dnaType];
        i++;
    }
    
    
    if(G->geneticCounter[type] % 10 == 0) {
        int selectedDNA = arc4random() % (sizeof(DNAType)-1);
        
        switch (selectedDNA) {
            case dBehavior:
                C->chromosome[dBehavior] = arc4random() % (sizeof(behaviorType)-1);
                break;
                
            case dVision:
                C->chromosome[dVision] = arc4random() % (sizeof(visionType)-1);
                break;
                
            case dVenom:
                C->chromosome[dVenom] = arc4random() % (sizeof(venomLevel)-1);
                break;
                
            default:
                CCLOG("Exception Error of Genetic: number is %d", selectedDNA);
                exit(1);
                break;
        }
    }
    
    // If befavior type is collective, push data
    if(C->chromosome[dBehavior] == collective) {
        G->group[C->type].push_back(C);
    }
}

bool LivingThings::eat(std::list<LivingThings *>::iterator &itL)
{
    return NULL;
}

bool LivingThings::hunger(std::list<LivingThings *>::iterator &itL)
{
    return NULL;
}

bool LivingThings::aging(std::list<LivingThings *>::iterator &itL)
{
    return NULL;
}

void LivingThings::hunting() {}

LivingThings* LivingThings::searchOperation()
{
    return NULL;
}

void LivingThings::randomWalk() {}
void LivingThings::groupMove() {}
void LivingThings::laze() {}

void LivingThings::createDistination(bool isRandom)
{
    // Get new goal point
    if(isRandom) {
        float radius = size / 2;
        sx = (arc4random() + (int)radius) % (int)(G->winSize.width - radius);
        sy = (arc4random() + (int)radius) % (int)(G->winSize.height - radius);
    }
    
    double dx = sx - cx;
    double dy = sy - cy;
    double distance = sqrt(dx * dx + dy * dy);
    moves = distance / speed;
    ux = dx / moves;
    uy = dy / moves;
}

void LivingThings::createSight() {}

void LivingThings::decomposition(LivingThings* L)
{
    // Plant is an exception
    if(L->type == lTypeP) return;
    
    double distance = 25.;
    double bornX, bornY;
    for(int i=0; i < 4; ++i) {
        switch (i) {
            case 0:
                bornX = L->cx;
                bornY = L->cy + distance;
                break;
            case 1:
                bornX = L->cx + distance;
                bornY = L->cy;
                break;
            case 2:
                bornX = L->cx;
                bornY = L->cy - distance;
                break;
            case 3:
                bornX = L->cx - distance;
                bornY = L->cy;
                break;
        }
        
        // Check over window
        if(bornX <= 0 || G->winSize.width <= bornX) continue;
        if(bornY <= 0 || G->winSize.height <= bornY) continue;
        
        LivingThings* plant = new Plant;

        plant->cx = bornX;
        plant->cy = bornY;
        G->mainDrawNode[lTypeP]->drawDot(Vec2(plant->cx, plant->cy), plant->size, plant->color);
        G->L[lTypeP].push_back(plant);
    }
}