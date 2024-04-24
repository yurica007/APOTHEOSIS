#pragma once
#include "EnemyShot.h"

class IcicleShot :
    public EnemyShot
{
public:
    IcicleShot() {}
    virtual ~IcicleShot() {}
    void SetInitializeData();
};

