#pragma once
#include "../BaseScene.h"

enum class Transition
{
    CrossFade,
    FadeInOut,
    Max
};

class TransitionScene :
    public BaseScene
{
public:
    TransitionScene(uniqueScene beforScene, uniqueScene afterScene);
    ~TransitionScene();

private:

    bool Init(void);
    uniqueScene UpDate(double delta, uniqueScene ownScene) override;
    virtual bool UpDateTransition(double delta) = 0;

protected:
    Scene GetSceneID(void)override final{ return Scene::Transition; };
    uniqueScene beforScene_;
    uniqueScene afterScene_;

    double cnt;
};

