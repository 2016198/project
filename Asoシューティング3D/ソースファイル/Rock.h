#pragma once
#include "Transform.h"

class Rock
{
public:

	Rock(void);
	void Init(int modelId, VECTOR pos, VECTOR angles, VECTOR scale);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	//モデル制御の基本情報
	Transform mTransform;
	
};

