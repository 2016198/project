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
		Vector2 point;	//�n�_
		Vector2 vec;	//�����x�N�g��
	};
	struct Line
	{
		Vector2 point;	//�n�_
		Vector2 end;	//�I�_
		Vector2 vec() {return end - point; }
	};
	bool CheckCollision(Ray ray, Collision collision);//Collision = std::pair<Vector2, Vector2>;
	bool CheckRay(Ray ray, Line line);

private:

};