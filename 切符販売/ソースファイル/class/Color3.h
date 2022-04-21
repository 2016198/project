#pragma once
#include <DxLib.h>

struct Color3
{
	int red = 0;
	int green = 0;
	int blue = 0;

	bool operator==(Color3 c)const
	{
		return (c.red == red && c.blue == blue && c.green == green);
	};

	bool operator!=(Color3 c)const
	{
		return (c.red != red || c.blue != blue || c.green != green);
	};

	Color3 operator+=(int c)
	{
		red += c;
		green += c;
		blue += c;
		return *this;
	}

	Color3 operator+=(Color3 c)
	{
		red += c.red;
		green += c.green;
		blue += c.blue;
		return *this;
	}

	Color3 operator-=(int c)
	{
		red -= c;
		green -= c;
		blue -= c;
		return *this;
	}

	Color3 operator-=(Color3 c)
	{
		red -= c.red;
		green -= c.green;
		blue -= c.blue;
		return *this;
	}

	Color3 operator++(void)
	{
		red++;
		green++;
		blue++;
		return *this;
	}

	Color3 operator--(void)
	{
		red--;
		green--;
		blue--;
		return *this;
	}

	Color3 operator+(Color3 c)
	{
		return Color3{ red + c.red, green + c.green, blue + c.blue };
	}

	Color3 operator-(Color3 c)
	{
		return Color3{ red - c.red, green - c.green, blue - c.blue };
	}

	Color3 operator*(Color3 c)
	{
		return Color3{ red * c.red, green * c.green, blue * c.blue };
	}

	Color3 operator/(Color3 c)
	{
		return Color3{ red / c.red, green / c.green, blue / c.blue };
	}

	const unsigned int GetColorCode(void)
	{
		return GetColor(red, green, blue);
	}

	void Color3Code(unsigned int color)	//GetColorをColor3に変換
	{
		red = color / 0x010000 % 0x000100;
		green = color / 0x000100 % 0x000100;
		blue = color % 0x000100;
	}

	void Color3Code(int color)	//色コードをColor3に変換
	{
		red = color / 0x010000;
		green = color / 0x000100 % 0x000100;
		blue = color % 0x000100;
	}

};

static Color3 RED = { 255, 0, 0 };
static Color3 BLUE = { 0, 0, 255 };
static Color3 GREEN = { 0, 255, 0 };
static Color3 MAGENTA = { 255, 0, 255 };
static Color3 YELLOW = { 255, 255, 0 };
static Color3 CYAN = { 0, 255, 255 };
static Color3 BLACK = { 0, 0, 0 };
static Color3 WHITE = { 255, 255, 255 };
static Color3 BROWN = { 101, 67, 33 };
static Color3 ORENGE = { 255, 125, 0 };
static Color3 GRAY = { 125, 125, 125 };