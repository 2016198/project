#include <DxLib.h>
#include "P1Input.h"

void P1Input::SetKeyList(INPUT_TYPE type)
{
	BaseInput::CheckInputList();

	switch (type)
	{
	case INPUT_TYPE::KEY:
		input_[INPUT_LIST::START][KEY::NOW] = CheckHitKey(KEY_INPUT_SPACE);
		input_[INPUT_LIST::SELECT][KEY::NOW] = CheckHitKey(KEY_INPUT_RETURN);

		input_[INPUT_LIST::LEFT][KEY::NOW] = CheckHitKey(KEY_INPUT_A);
		input_[INPUT_LIST::RIGHT][KEY::NOW] = CheckHitKey(KEY_INPUT_D);
		input_[INPUT_LIST::UP][KEY::NOW] = CheckHitKey(KEY_INPUT_W);
		input_[INPUT_LIST::DOWN][KEY::NOW] = CheckHitKey(KEY_INPUT_S);

		input_[INPUT_LIST::A][KEY::NOW] = CheckHitKey(KEY_INPUT_T);
		input_[INPUT_LIST::B][KEY::NOW] = CheckHitKey(KEY_INPUT_R);
		break;

	case INPUT_TYPE::PAD:
		input_[INPUT_LIST::START][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_R;
		input_[INPUT_LIST::SELECT][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_L;

		input_[INPUT_LIST::LEFT][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT;
		input_[INPUT_LIST::RIGHT][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT;
		input_[INPUT_LIST::UP][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP;
		input_[INPUT_LIST::DOWN][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN;

		input_[INPUT_LIST::A][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A;
		input_[INPUT_LIST::B][KEY::NOW] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B;
		break;
	}

	BaseInput::CheckTrgList();
}
