#pragma once
#include "Vector2.h"
#include "Collision.h"

class Raycast
{
public:
	Raycast();
	~Raycast();
	struct Ray
	{
		Vector2 point;	//始点
		Vector2 vec;	//方向ベクトル
	};
	struct Line
	{
		Vector2 point;	//始点
		Vector2 end;	//終点
		Vector2 vec() {return end - point; }
	};
	bool CheckCollision(Ray ray, Collision collision);//Collision = std::pair<Vector2, Vector2>;
	bool CheckRay(Ray ray, Line line);

private:

};