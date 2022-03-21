#include <DxLib.h>
#include "PadInput.h"
#include "KeyInput.h"


PadInput::PadInput()
{
	inputTbl_ = {
		{InputID::Up,PAD_INPUT_UP},
		{InputID::Down,PAD_INPUT_DOWN},
		{InputID::Left,PAD_INPUT_LEFT},
		{InputID::Right,PAD_INPUT_RIGHT},
		{InputID::ButtonA,PAD_INPUT_A},
		{InputID::ButtonB,PAD_INPUT_B},
		{InputID::ButtonC,PAD_INPUT_X},
		{InputID::ButtonD,PAD_INPUT_Y},
	};
	for (auto id : InputID())
	{
		cntData_.try_emplace(id, TrgBool{ false,false });
	}
}

PadInput::~PadInput()
{

}

uniqueInput PadInput::UpDate(uniqueInput ownInput)
{
	int pad = GetJoypadInputState(DX_INPUT_PAD1);
	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = ((pad & inputTbl_[id]) > 0);
	}
	/*if (cntData_[InputID::ButtonA][1])
	{
		return std::make_unique<KeyInput>();
	}*/
	return std::move(ownInput);
}
