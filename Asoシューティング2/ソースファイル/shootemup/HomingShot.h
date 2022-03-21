#pragma once
#include "Trail.h"
#include "Bullet.h"

struct HomingShot : public Bullet
{
	Trail trail;
	HomingShot();
};