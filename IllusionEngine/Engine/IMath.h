#pragma once
#include <cmath>
#include <random>
#include <iostream>
#include <cstdio>
#include <unordered_set>

#ifndef Math_PI
#define Math_PI 3.14159265358979323846
#endif
struct Vector2
{
	float x;
	float y;
	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	bool operator==(const Vector2& other) const
	{
		return (x == other.x) && (y == other.y);
	}
	// 長さ
	float length() const
	{
		return std::sqrt(x * x + y * y);
	}

	// 単位ベクトル
	Vector2 normalized() const {
		float len = length();
		if (len < std::numeric_limits<float>::epsilon()) return Vector2(0, 0);
		float invLen = 1.0f / len;
		return Vector2(x * invLen, y * invLen);
	}

	// char に変換 decは小数点以下の桁数
	const char* toString(unsigned int dec = 2)
	{
		static char buffer[50];
		static char format[20];

		if (dec > 10) dec = 10;// 最大10桁まで制限

		// フォーマット文字列を作成
		std::snprintf(format, sizeof(format), "(%%.%df, %%.%df)", dec, dec);

		std::snprintf(buffer, sizeof(buffer), format, x, y);
		return buffer;
	}
	// 0ベクトル
	static const Vector2 Zero;
};
class IMath {
public:
	
	double static ToDegrees(double radian);
};