#include <DxLib.h>
#include "BaseInput.h"

void BaseInput::CheckInputList(void)
{
	for (auto id : INPUT_LIST())
	{
		input_[id][KEY::OLD] = input_[id][KEY::NOW];
	}

	input_[INPUT_LIST::MOUSE_LEFT][KEY::NOW] = GetMouseInput() & MOUSE_INPUT_LEFT;
	input_[INPUT_LIST::MOUSE_RIGHT][KEY::NOW] = GetMouseInput() & MOUSE_INPUT_RIGHT;
	input_[INPUT_LIST::MOUSE_MIDDLE][KEY::NOW] = GetMouseInput() & MOUSE_INPUT_MIDDLE;
}

void BaseInput::CheckTrgList(void)
{
	for (auto id : INPUT_LIST())
	{
		input_[id][KEY::TRG_UP] = input_[id][KEY::OLD] && !input_[id][KEY::NOW];
		input_[id][KEY::TRG_DOWN] = !input_[id][KEY::OLD] && input_[id][KEY::NOW];
	}
}
