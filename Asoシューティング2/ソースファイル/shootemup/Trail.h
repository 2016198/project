#pragma once
#include<list>
#include "Geometry.h"
struct HomingShot;

class Trail
{
private:
	HomingShot& owner_;
	std::list<Position2> history_;
	int handle_;
public:
	Trail(HomingShot& owner);
	void SetHandle(int handle);
	void Update();
	void Draw();
	void Clear();
};

