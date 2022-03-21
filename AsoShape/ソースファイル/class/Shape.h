#pragma once
#include "Vector2.h"

enum class ShapeType
{
	SQUARE,
	CIRCLE,
	TRIANGLE,
	STAR,
	TREFOIL,
	CROSS,
	MAX
};

class Shape
{
public:
	Vector2Flt pos_;
	Vector2Flt size_;
	Vector2Flt speed_;
	int color_;

	Shape(Vector2Flt& pos, Vector2Flt& sizs, Vector2Flt& speed, unsigned int color);
	virtual void Draw(void) = 0;
	virtual void Draw(float exp) = 0;
	virtual void Draw(float exp, Vector2Flt offset) = 0;
	virtual bool UpDate(float delta, Shape& ShapeVec) = 0;
	virtual bool IsAlive(void) = 0;
	virtual ShapeType GetType(void) = 0;
	virtual Vector2Flt GetPos(void) = 0;
	virtual Vector2Flt GetSize(void) = 0;
	virtual ShapeType Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type) = 0;
};

