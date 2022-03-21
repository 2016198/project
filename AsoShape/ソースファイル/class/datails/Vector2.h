#pragma once

#include "../class/Vector2.h"

template <class T>
Vector2Temple<T>::Vector2Temple()
{
	x_ = 0;
	y_ = 0;
}

template <class T>
Vector2Temple<T>::~Vector2Temple()
{

}

template <class T>
Vector2Temple<T>::Vector2Temple(T x, T y)
{
	x_ = x;
	y_ = y;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator = (const Vector2Temple<T>& vec)
{
	// TODO: return ステートメントをここに挿入します
	x_ = vec.x_;
	y_ = vec.y_;

	//実態で返す。
	return *this;
}

template <class T>
int& Vector2Temple<T>::operator[](int j)
{
	// TODO: return ステートメントをここに挿入します

	switch (j)
	{
	case 0:
		return x_;
		//break;
	case 1:
		return y_;
		//break;
	default:
		return x_;
		break;
	}
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(const Vector2Temple<T>& vec)
{
	// TODO: return ステートメントをここに挿入します
	x_ += vec.x_;
	y_ += vec.y_;
	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(const Vector2Temple<T>& vec)
{
	// TODO: return ステートメントをここに挿入します
	x_ -= vec.x_;
	y_ -= vec.y_;
	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(const Vector2Temple<T>& vec)
{
	// TODO: return ステートメントをここに挿入します
	x_ *= vec.x_;
	y_ *= vec.y_;
	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator/=(const Vector2Temple<T>& vec)
{
	// TODO: return ステートメントをここに挿入します
	if (vec.x_ != 0)
	{
		x_ /= vec.x_;
	}
	else
	{
		x_ = 0;
	}
	if (vec.y_ != 0)
	{
		y_ /= vec.y_;
	}
	else
	{
		y_ = 0;
	}
	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator%=(const Vector2Temple<T>& vec)
{
	// TODO: return ステートメントをここに挿入します
	if (vec.x_ != 0)
	{
		x_ %= vec.x_;
	}
	else
	{
		x_ = 0;
	}
	if (vec.y_ != 0)
	{
		y_ %= vec.y_;
	}
	else
	{
		y_ = 0;
	}
	return *this;
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator+() const
{
	// TODO: return ステートメントをここに挿入します
	return *this;
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator-() const
{
	// TODO: return ステートメントをここに挿入します
	return { -x_,-y_ };
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator+(Vector2Temple<T> vec)
{
	return { x_ + vec.x_ ,y_ + vec.y_ };
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator-(Vector2Temple<T> vec)
{
	return { x_ - vec.x_ ,y_ - vec.y_ };
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator*(Vector2Temple<T> vec)
{
	return { x_ * vec.x_ ,y_ * vec.y_ };
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator/(Vector2Temple<T> vec)
{
	return { x_ / vec.x_ ,y_ / vec.y_ };
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator%(Vector2Temple<T> vec)
{
	return { x_ % (int)(vec.x_) ,y_ % (int)(vec.y_) };
}

template <class T>
bool Vector2Temple<T>::operator==(const Vector2Temple<T>& vec) const
{
	// TODO: return ステートメントをここに挿入します
	return (x_ == vec.x_ && y_ == vec.y_);
}

template <class T>
bool Vector2Temple<T>::operator!=(const Vector2Temple<T>& vec) const
{
	// TODO: return ステートメントをここに挿入します
	return !(x_ == vec.x_ && y_ == vec.y_);
}

template <class T>
bool Vector2Temple<T>::operator>=(const Vector2Temple<T>& vec) const
{
	// TODO: return ステートメントをここに挿入します
	return (x_ >= vec.x_ && y_ >= vec.y_);
}

template <class T>
bool Vector2Temple<T>::operator<=(const Vector2Temple<T>& vec) const
{
	// TODO: return ステートメントをここに挿入します
	return (x_ <= vec.x_ && y_ <= vec.y_);
}

template <class T>
bool Vector2Temple<T>::operator<(const Vector2Temple<T>& vec) const
{
	// TODO: return ステートメントをここに挿入します
	return (x_ < vec.x_&& y_ < vec.y_);
}

template <class T>
bool Vector2Temple<T>::operator>(const Vector2Temple<T>& vec) const
{
	// TODO: return ステートメントをここに挿入します
	return (x_ > vec.x_ && y_ > vec.y_);
}

template <class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& u, T e)
{
	return { u.x_ * e,u.y_ * e };
}

template <class T>
Vector2Temple<T> operator*(T e, const Vector2Temple<T>& u)
{
	return { u.x_ * e,u.y_ * e };
}
