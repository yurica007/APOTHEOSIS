#pragma once
#include "EnemyShot.h"

class IceShot :
    public EnemyShot
{
public:
    IceShot() {}
    virtual ~IceShot() {}
    void SetInitializeData();
};

