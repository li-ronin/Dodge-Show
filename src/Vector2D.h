#pragma once
#include <iostream>

class Vector2D
{
public:
	float x;
	float y;
	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);
	//operator+= 通常被设计为成员函数而不是友元函数，以便对当前对象进行修改，
	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator/=(const Vector2D& v);

	Vector2D& operator*(const int& i);
	Vector2D& Zero();

	// 示例：输出操作符重载
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);

};