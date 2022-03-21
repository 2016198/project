#include"Geometry.h"
#include<DxLib.h>
#include<cmath>

void
Rect::Draw() {
	DxLib::DrawBox(Left() * 2, Top() * 2, Right() * 2, Bottom() * 2, 0xffffffff, false);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBox((Left() + offset.x) * 2, (Top() + offset.y) * 2, (Right() + offset.x) * 2, (Bottom() + offset.y) * 2, 0xffffffff, false);
}

void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

Vector2
Vector2::operator*(float scale) {
	return Vector2(x * scale, y * scale);
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x + vb.x, va.y + vb.y);
}

Vector2 operator-(const Vector2& va, const Vector2 vb){
	return Vector2(va.x - vb.x, va.y - vb.y);
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
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


///内積を返す
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x * vb.x + va.y * vb.y;
}

///外積を返す
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


void 
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void 
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}


//-------ここから3Dのターン------
void
Vector3::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

void Vector3::operator*=(const Vector3& v){
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

void Vector3::operator/=(float scale) {
	x /= scale;
	y /= scale;
	z /= scale;
}

Vector3
Vector3::operator*(float scale)const {
	return Vector3(x * scale, y * scale, z * scale);
}

Vector3 operator+(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x + vb.x, va.y + vb.y, va.z + vb.z);
}

Vector3 operator-(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x - vb.x, va.y - vb.y, va.z - vb.z);
}

float
Vector3::Magnitude()const {
	return sqrt(x * x + y * y + z * z);
}


void
Vector3::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}


Vector3
Vector3::Normalized() {
	float mag = Magnitude();
	return Vector3(x / mag, y / mag, z / mag);
}


///内積を返す
float
Dot(const Vector3& va, const Vector3& vb) {
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

///外積を返す
Vector3
Cross(const Vector3& va, const Vector3& vb) {
	return Vector3(va.z * vb.y - va.y * vb.z, va.z * vb.x - va.x * vb.z, va.x * vb.y - vb.x * va.y);
}

///直積演算子
Vector3
operator*(const Vector3& va, const Vector3& vb) {
	return { va.x * vb.x, va.y * vb.y, va.z * vb.z };
}

///外積演算子
Vector3
operator%(const Vector3& va, const Vector3& vb) {
	return Cross(va, vb);
}


void
Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
void
Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

bool Sphere::IshitRay(const Ray& ray, float& t, const Vector3& N)const {
	//レイが正規化済みである前提で…

	//視点から球体中心へのベクトル(視線)を作ります
	auto center = pos - ray.start;
	//中心から視線への内積をとります＝＞ベクトル長
	auto dot = Dot(center, ray.vec);
	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求めます
	auto iray = ray.vec * dot;
	//交点までの距離tを求める手順
	//①垂線の長さを求める
	auto v = iray - center;
	//②垂線の長さが半径を超えているならfalseを返す
	if (Dot(v, v) > radius * radius) return false;
	//③半径と垂線の長さから、垂線をおろしたところから
	// 交点までの距離wを測る(三平行の定理 w^2=r^2-v^2)
	float w = sqrtf(radius * radius - Dot(v, v));
	//④射影距離-wが交点までの距離となるので、それを
	// tに代入する
	t = dot - w;
	//※ヒント　Dot(v,v)のように同一ベクトルを内積すると
	// 大きさの２乗になるゾ
	//return (iray - center).Magnitude() <= sp.radius;
	return true;
}

bool Plane::IshitRay(const Ray& ray, float& t, const Vector3& N)const {
	//ratもplane.Nも正規化されてるとすると…？
	//ヒントは内積
	float dot = Dot(ray.vec, n);
	bool hit = dot < 0.0f;
	if (hit) {
		t = (Dot(ray.start, n) - distance) / Dot(-ray.vec, n);
	}
	return hit;
}