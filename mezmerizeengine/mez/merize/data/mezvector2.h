#pragma once

//2 dimensional vector

struct Vector2
{
	float x;
	float y;
	Vector2 operator-(Vector2 i) { return Vector2(x - i.x, y - i.y); }
	Vector2 operator+(Vector2 i) { return Vector2(x + i.x, y + i.y); }
	Vector2 operator*(Vector2 i) { return Vector2(x * i.x, y * i.y); }
	Vector2 operator/(Vector2 i) { return Vector2(x / i.x, y / i.y); }
	Vector2 operator*(float i) { return Vector2(x * i, y * i); }
	Vector2 operator/(float i) { return Vector2(x / i, y / i); }
	Vector2 operator-() { return *this * -1; }
	Vector2 operator-=(Vector2 i) { return *this = *this - i; }
	Vector2 operator+=(Vector2 i) { return *this = *this + i; }
	Vector2 operator*=(Vector2 i) { return *this = *this * i; }
	Vector2 operator/=(Vector2 i) { return *this = *this / i; }
	Vector2 operator*=(float i) { return *this = *this * i; }
	Vector2 operator/=(float i) { return *this = *this / i; }
};