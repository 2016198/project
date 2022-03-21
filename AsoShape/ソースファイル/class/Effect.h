#pragma once
#include "Shape.h"
class Effect :
    public Shape
{
public:
    Effect(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color);
    void Draw(void) override;
    void Draw(float exp) override;
    void Draw(float exp, Vector2Flt offset) override;
    bool UpDate(float delta, Shape& ShapeVec) override;
    bool IsAlive(void) override;
    ShapeType GetType(void) override;
    Vector2Flt GetPos(void) override;
    Vector2Flt GetSize(void) override;
    ShapeType Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type) override;

private:
    bool alive_;
    int ness_;
    float time_;
    float delta_t_;
};

