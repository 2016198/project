#pragma once
#include "Vector2.h"
#include "Color3.h"

void ChangeNum(bool* num1, bool* num2)
{
	auto index = *num1;
	*num1 = *num2;
	*num2 = index;
};

void ChangeNum(int* num1, int* num2)
{
	int index = *num1;
	*num1 = *num2;
	*num2 = index;
};

void ChangeNum(float* num1, float* num2)
{
	auto index = *num1;
	*num1 = *num2;
	*num2 = index;
};

void ChangeNum(double* num1, double* num2)
{
	auto index = *num1;
	*num1 = *num2;
	*num2 = index;
};

void ChangeNum(Vector2* num1, Vector2* num2)
{
	auto index = *num1;
	*num1 = *num2;
	*num2 = index;
};

void ChangeNum(Color3* num1, Color3* num2)
{
	auto index = *num1;
	*num1 = *num2;
	*num2 = index;
};

int UpDown(int* alpha, int add = 1)
{
	if (add > 0)
	{
		*alpha += add;
	}

	else if (add < 0)
	{
		*alpha -= add;
	}

	if (*alpha > 512)
	{
		*alpha = 0;
	}

	if (*alpha < 256)
	{
		return *alpha;
	}

	return 512 - *alpha;
};
