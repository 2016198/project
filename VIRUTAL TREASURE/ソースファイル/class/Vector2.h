#pragma once

struct Vector2
{
	int x = 0;
	int y = 0;
	int num = 0;

	bool operator==(Vector2 v)const
	{
		return (v.x == x && y == v.y);
	};

	bool operator!=(Vector2 v)const
	{
		return (v.x != x || y != v.y);
	};

	Vector2 operator+=(Vector2 v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2 operator-=(Vector2 v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2 operator--(void)
	{
		x--;
		y--;
		return *this;
	}

	Vector2 operator++(void)
	{
		x++;
		y++;
		return *this;
	}

	Vector2 operator+(Vector2 v)
	{
		return Vector2{ x + v.x, y + v.y };
	}

	Vector2 operator-(Vector2 v)
	{
		return Vector2{ x - v.x, y - v.y };
	}

	Vector2 operator*(Vector2 v)
	{
		return Vector2{ x * v.x, y * v.y };
	}

	Vector2 operator/(Vector2 v)
	{
		return Vector2{ x / v.x, y / v.y };
	}
};


