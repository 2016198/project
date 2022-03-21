#pragma once
#include "SceneBase.h"

class ParticleGenerator;
class TextScroll;
class SpaceDome;

class TitleScene : public SceneBase
{

public:

	TitleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawLogo(void);
	void Release(void) override;

private:

	int mImgStartLogo;
	SpaceDome* mSpaceDome;
	ParticleGenerator* mParticleGenerator;
	TextScroll* mTextScroll;

};

