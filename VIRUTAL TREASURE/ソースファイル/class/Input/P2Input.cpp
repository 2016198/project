#include <DxLib.h>
#include "P2Input.h"

void P2Input::SetKeyList(INPUT_TYPE type)
{
	BaseInput::CheckInputList();

	switch (type)
	{
	case INPUT_TYPE::KEY:
		input_[INPUT_LIST::START][KEY::NOW] = CheckHitKey(KEY_INPUT_SPACE);
		input_[INPUT_LIST::SELECT][KEY::NOW] = CheckHitKey(KEY_INPUT_RETURN);

		input_[INPUT_LIST::LEFT][KEY::NOW] = CheckHitKey(KEY_INPUT_LEFT);
		input_[INPUT_LIST::RIGHT][KEY::NOW] = CheckHitKey(KEY_INPUT_RIGHT);
		input_[INPUT_LIST::UP][KEY::NOW] = CheckHitKey(KEY_INPUT_UP);
		input_[INPUT_LIST::DOWN][KEY::NOW] = CheckHitKey(KEY_INPUT_DOWN);

		input_[INPUT_LIST::A][KEY::NOW] = CheckHitKey(KEY_INPUT_BACKSLASH);
		input_[INPUT_LIST::B][KEY::NOW] = CheckHitKey(KEY_INPUT_SLASH);
		break;
	case INPUT_TYPE::PAD:
		input_[INPUT_LIST::START][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_R;
		input_[INPUT_LIST::SELECT][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_L;

		input_[INPUT_LIST::LEFT][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_LEFT;
		input_[INPUT_LIST::RIGHT][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_RIGHT;
		input_[INPUT_LIST::UP][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_UP;
		input_[INPUT_LIST::DOWN][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_DOWN;

		input_[INPUT_LIST::A][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A;
		input_[INPUT_LIST::B][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_B;
		break;
	}

	BaseInput::CheckTrgList();
}
