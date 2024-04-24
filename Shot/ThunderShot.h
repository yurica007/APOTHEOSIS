#pragma once
#include "EnemyShot.h"

class ThunderShot :
    public EnemyShot
{
public:
    ThunderShot() {}
    virtual ~ThunderShot() {}
    void SetInitializeData();
};

