#pragma once

// template <class T> class テンプレートクラス名

template <class T> class Vector2Temple
{
public:
	Vector2Temple();
	Vector2Temple(T x,T y);
	~Vector2Temple();
	T x_;
	T y_;

	//代入演算子
	Vector2Temple& operator = (const Vector2Temple& vec);
	//↑返り値	         		//↑式の右辺
	//添え字演算子
	int& operator[] (int j);

	//単項演算子
	Vector2Temple& operator+=(const Vector2Temple& vec);
	Vector2Temple& operator-=(const Vector2Temple& vec);
	Vector2Temple& operator*=(const Vector2Temple& vec);
	Vector2Temple& operator/=(const Vector2Temple& vec);
	Vector2Temple& operator%=(const Vector2Temple& vec);
	Vector2Temple operator+()const;//関数内において(x_,y_)が変更できなくなる*Vector2
	Vector2Temple operator-()const;

	//二項演算子
	Vector2Temple operator+(Vector2Temple vec);
	Vector2Temple operator-(Vector2Temple vec);
	Vector2Temple operator*(Vector2Temple vec);
	Vector2Temple operator/(Vector2Temple vec);
	Vector2Temple operator%(Vector2Temple vec);

	//比較演算子
	bool operator==(const Vector2Temple&vec)const;
	bool operator!=(const Vector2Temple& vec)const;
	bool operator<=(const Vector2Temple& vec)const;
	bool operator>=(const Vector2Temple& vec)const;
	bool operator<(const Vector2Temple& vec)const;
	bool operator>(const Vector2Temple& vec)const;

};

template <class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& u, T e);
template <class T>
Vector2Temple<T> operator*(T e, const Vector2Temple<T>& u);

using Vector2 = Vector2Temple<int>;
using Vector2Flt = Vector2Temple<float>;
using Vector2Dbl = Vector2Temple<double>;

#include "datails/Vector2.h"

