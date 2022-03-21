#include "BaseScene.h"
#include "../Input/P1Input.h"
#include "../Input/P2Input.h"

BaseScene::BaseScene(INPUT_TYPE type)
{
	ptr_[0] = std::make_unique<P1Input>();
	ptr_[1] = std::make_unique<P2Input>();
	font_ = -1;
	selectNum_ = SCENE_ID::CONTINUE;
	image_ = -1;
	inputType_ = type;
}
