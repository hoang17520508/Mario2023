#pragma once
#include "GameObject.h"
#define LEAF_GRAVITY 0.0016f

#define LEAF_WIDTH  16
#define LEAF_HEIGHT  14

#define LEAF_SPEED_IDLE    0.2f

#define LEAF_STATE_IDLE 1
#define LEAF_STATE_FALLING 2

#define ID_ANI_LEAF_FALLING_RIGHT   303001
#define ID_ANI_LEAF_FALLING_LEFT   303002

#define LEAF_VX_SPEED 0.05f
class CLeaf :
    public CGameObject
{
protected:
    float original_y;
    ULONGLONG fallingInWindTime;
public:
    CLeaf(float x, float y) :CGameObject(x, y) {
        vx = LEAF_VX_SPEED;
        original_y = y;
        fallingInWindTime = 0;
        state = LEAF_SPEED_IDLE;
    };
    void Render();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int IsBlocking() { return 0; }
    int IsCollidable() { return 1; }
    void SetState(int state);
    void OnNoCollision(DWORD dt);
};

