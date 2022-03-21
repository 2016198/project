#pragma once
#include "Shape.h"
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480
#define PAI 3.1415f
class Circle :
    public Shape
{
public:
    Circle(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color);
    bool UpDate(float delta, Shape& ShapeVec) override;
    void Draw(void) override;
    void Draw(float exp) override;
    void Draw(float exp, Vector2Flt offset) override;
    bool IsAlive(void) override;
    ShapeType GetType(void) override;
    Vector2Flt GetPos(void) override;
    Vector2Flt GetSize(void) override;
    ShapeType Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type) override;

private:
    bool alive_;
    Vector2Flt vec_;
    float stop_t_ = 0.0f;
    Vector2Flt add_speed_ = { 5.0f,5.0f };
    int def_color_;
};

