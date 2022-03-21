#pragma once
#include "TransitionScene.h"
class CrossOver :
    public TransitionScene
{
public:
    CrossOver(double limtTime, uniqueScene beforScene, uniqueScene afterScene);
    ~CrossOver();
private:
    double limtTime_;

    bool UpDateTransition(double delta) override;
    void DrawOwnScreen(double delta) override;
};

