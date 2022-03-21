#pragma once
#include <type_traits>

//ボタンの種類
enum class InputID
{
	Up,			//1		:上
	Down,		//2		:下
	Left,		//4		:左
	Right,		//8		:右
	ButtonA,	//16	:Z
	ButtonB,	//32	:X
	ButtonC,	//64	:C
	ButtonD,	//128	:V
	ButtonE,	//256	:SPACE
	New,		//512	:ニュートラル
	Max
};

static InputID begin(InputID) { return InputID::Up; };
static InputID end(InputID) { return InputID::Max; };
static InputID operator++(InputID& state) 
{
	state = static_cast<InputID>(std::underlying_type<InputID>::type(state) + 1);
	return state;
};
static InputID operator*(const InputID& state) { return state; };

