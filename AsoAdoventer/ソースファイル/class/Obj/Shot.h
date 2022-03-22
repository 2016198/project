#pragma once
#include "../common/Vector2.h"
class Shot {
public:
	Shot() {};
	~Shot() {};
	virtual bool Init(Vector2 pos, bool isLeft) = 0;
	virtual void UpDate() = 0;
	virtual void Draw() = 0;
protected:
	Vector2Dbl pos_;
	bool moveLeft_;
	double speed_;
	double arive_;
};
