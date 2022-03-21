#include <DxLib.h>
#include "KeyInput.h"
#include "PadInput.h"

KeyInput::KeyInput()
{
	inputTbl_ = {
		{InputID::Up,KEY_INPUT_UP},
		{InputID::Down,KEY_INPUT_DOWN},
		{InputID::Left,KEY_INPUT_LEFT},
		{InputID::Right,KEY_INPUT_RIGHT},
		{InputID::ButtonA,KEY_INPUT_Z},
		{InputID::ButtonB,KEY_INPUT_X},
		{InputID::ButtonC,KEY_INPUT_C},
		{InputID::ButtonD,KEY_INPUT_V},
		{InputID::ButtonE,KEY_INPUT_SPACE},
	};
	for (auto id : InputID())
	{
		cntData_.try_emplace(id, TrgBool{ false,false });
	}
	ringBuf_ = ringBuf_->Create(30);
	LoadCmd("./tmx/command.tmx","player");
	////èâä˙âª
	//int t = 1;
	//for (auto& c : com)
	//{
	//	c.value = t++;
	//}

	//for (size_t q = 1; q < max; q++)//ê∂ê¨
	//{
	//	com.at(q).before = &com.at(q - 1);
	//	com.at(q - 1).next = &com.at(q);
	//}
	//com.at(0).before = &com.at(max - 1);
	//com.at(max - 1).next = &com.at(0);
}

KeyInput::~KeyInput()
{
	
}

uniqueInput KeyInput::UpDate(uniqueInput ownInput)
{
	GetHitKeyStateAll(keyData_.data());
	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[inputTbl_[id]];
	}
	/*if (cntData_[InputID::ButtonA][1])
	{
		return std::make_unique<PadInput>();
	}*/
	/*if (cntData_[InputID::ButtonA][static_cast<int>(Trg::Now)] && !cntData_[InputID::ButtonA][static_cast<int>(Trg::Old)])
	{
		data = data->before;
	}
	if (cntData_[InputID::ButtonB][static_cast<int>(Trg::Now)] && !cntData_[InputID::ButtonB][static_cast<int>(Trg::Old)])
	{
		data = data->next;
	}
	_dbgDrawFormatString(0, 0, 0xffffff, "%d",data->value);*/
	/*for (int r = 0; r < 10; r++)
	{
		_dbgDrawFormatString(30 * r, 0, 0xffffff, "%d", ringBuf_->value);
		ringBuf_ = ringBuf_->before;
	}
	for (int r = 0; r < 10; r++)
	{
		_dbgDrawFormatString(30 * r, 0, 0xffffff, "\n%d", ringBuf_->value);
		ringBuf_ = ringBuf_->next;
	}
	if (cntData_[InputID::ButtonA][static_cast<int>(Trg::Now)] && !cntData_[InputID::ButtonA][static_cast<int>(Trg::Old)])
	{
		ringBuf_->Destroy(ringBuf_);
	}*/
	WriteCmd();
	/*for (int r = 0; r < 20; r++)
	{
		_dbgDrawFormatString(30 * r, 0, 0xffffff, "\n%d", startBuf_->value);
		startBuf_ = startBuf_->next;
	}*/
	return std::move(ownInput);
}
