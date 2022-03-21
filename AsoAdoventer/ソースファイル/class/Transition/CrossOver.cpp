#include <DxLib.h>
#include "CrossOver.h"

CrossOver::CrossOver(double limtTime, uniqueScene beforScene, uniqueScene afterScene) :
	TransitionScene(std::move(beforScene), std::move(afterScene))
{
	limtTime_ = limtTime;
}

CrossOver::~CrossOver()
{

}

bool CrossOver::UpDateTransition(double delta)
{
	cnt += delta * 2.0;
	if (cnt > limtTime_)
	{
		return true;
	}
	return false;
}

void CrossOver::DrawOwnScreen(double delta)
{
	SetDrawScreen(ScreenID_);
	ClsDrawScreen();
	auto alpha = static_cast<int>(255.0 * cnt / limtTime_);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
	beforScene_->Draw(delta);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	afterScene_->Draw(delta);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}
