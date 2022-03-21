#include"Geometry.h"
#include<DxLib.h>
#include<cmath>
#include<algorithm>

void
Rect::Draw() {
	DxLib::DrawBox(Left() * 2, Top() * 2, Right() * 2, Bottom() * 2, 0xffffffff, false);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBox((Left() + offset.x) * 2, (Top() + offset.y) * 2, (Right() + offset.x) * 2, (Bottom() + offset.y) * 2, 0xffffffff, false);
}

Vector2
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
	return *this;
}

Vector2 Vector2::operator/=(float scale)
{
	x /= scale;
	y /= scale;
	return *this;
}

Vector2
Vector2::operator*(float scale) {
	return Vector2(scale * x, scale * y);
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x + vb.x, va.y + vb.y);
}

Vector2 operator-(const Vector2& va, const Vector2 vb){
	return Vector2(va.x - vb.x, va.y - vb.y);
}

bool operator==(const Vector2& va, const Vector2 vb)
{
	return va.x == vb.x && va.y == vb.y;
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
}

float 
Vector2::SQMagnitude() const {
	return x * x + y * y;
}

void 
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}


Vector2
Vector2::Normalized() {
	float mag = Magnitude();
	return Vector2(x / mag,	y /mag);
}

void Vector2::Rotate90(){
	std::swap(x, y);
	x = -x;
}

Vector2 Vector2::Rotated90()const
{
	return Vector2( -y,x );
}


///内積を返す(cosにかかわる。0を中心に線対称)
//A・B
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x * vb.x + va.y * vb.y;
}

///外積を返す(sinにかかわる。0を中心に点対称)
//A×B
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x * vb.y - vb.x * va.y;
}

///内積演算子
float 
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///外積演算子
float 
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}


Vector2
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}
Vector2
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}