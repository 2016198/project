#include "Raycast.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

Raycast::Raycast()
{

}

Raycast::~Raycast()
{

}

bool Raycast::CheckCollision(Ray ray, Collision col)//Collision = std::pair<Vector2, Vector2>;
{
	bool resalt = false;
	Line point[4] =
	{
		col.first, Vector2{col.first.x_ + col.second.x_, col.first.y_ },					//���ォ��E��
		Vector2{col.first.x_ + col.second.x_, col.first.y_ }, col.first + col.second,		//�E�ォ��E��
		col.first + col.second, Vector2{col.first.x_, col.first.y_ + col.second.y_ },		//�E�����獶��
		Vector2{col.first.x_, col.first.y_ + col.second.y_ }, col.first						//�������獶��
	};
	for (auto line : point)
	{
		resalt |= CheckRay(ray, line);
		//_dbgDrawLine(line.point.x_, line.point.y_, line.end.x_, line.end.y_, 0xff0000);
	}
	/*if (collision.first <= ray.point + ray.vec && collision.first + collision.second >= ray.point + ray.vec)
	{
		resalt != ;
	}*/
	return resalt;//�������Ă����true��Ԃ��B
}

bool Raycast::CheckRay(Ray ray, Line line)
{
	//line(x,y) ray(X,Y) -> xY-Xy
	//�O�όv�Z����񂾂悠������
	auto CheckCross = [](Vector2& vec1, Vector2& vec2)
	{
		return ((vec1.x_ * vec2.y_) - (vec1.y_ * vec2.x_));
	};
	Vector2& vecRay = ray.vec;
	Vector2&& vecLine = line.vec();

	int crossRayLine = CheckCross(vecRay, vecLine);
	if (crossRayLine == 0)
	{
		return false;
	}

	Vector2 v = Vector2{ line.point.x_ - ray.point.x_, line.point.y_ - ray.point.y_ };
	int cross_vRay = CheckCross(v, vecRay);
	int cross_vLine = CheckCross(v, vecLine);

	double ans[2];
	ans[0] = (double)cross_vRay / (double)crossRayLine;
	ans[1] = (double)cross_vLine / (double)crossRayLine;
	
	if (ans[0] > 0.0f && ans[0] <= 1.0f &&
		ans[1] > 0.0f && ans[1] <= 1.0f)
	{
		return true;
	}

	return false;
}


