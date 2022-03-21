#pragma once

// template <class T> class �e���v���[�g�N���X��

template <class T> class Vector2Temple
{
public:
	Vector2Temple();
	Vector2Temple(T x,T y);
	~Vector2Temple();
	T x_;
	T y_;

	//������Z�q
	Vector2Temple& operator = (const Vector2Temple& vec);
	//���Ԃ�l	         		//�����̉E��
	//�Y�������Z�q
	int& operator[] (int j);

	//�P�����Z�q
	Vector2Temple& operator+=(const Vector2Temple& vec);
	Vector2Temple& operator-=(const Vector2Temple& vec);
	Vector2Temple& operator*=(const Vector2Temple& vec);
	Vector2Temple& operator/=(const Vector2Temple& vec);
	Vector2Temple& operator%=(const Vector2Temple& vec);
	Vector2Temple operator+()const;//�֐����ɂ�����(x_,y_)���ύX�ł��Ȃ��Ȃ�*Vector2
	Vector2Temple operator-()const;

	//�񍀉��Z�q
	Vector2Temple operator+(Vector2Temple vec);
	Vector2Temple operator-(Vector2Temple vec);
	Vector2Temple operator*(Vector2Temple vec);
	Vector2Temple operator/(Vector2Temple vec);
	Vector2Temple operator%(Vector2Temple vec);

	//��r���Z�q
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

