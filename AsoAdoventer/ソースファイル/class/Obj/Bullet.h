#pragma once
#include "Shot.h"
class Bullet :
    public Shot
{
private:
    bool Init(Vector2 pos, bool isLeft)override;
    void UpDate()override;
    void Draw()override;
public:
    Bullet(Vector2 pos, bool isLeft);
    ~Bullet(); 
};

