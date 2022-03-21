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

	//���f������̊�{���
	Transform mTransform;
	
};

