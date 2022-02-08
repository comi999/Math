#include <iostream>
#include "Math.hpp"

int main()
{
	Vector4 v = { 1.0f, 2.2f, 3.1f, 4.8f };
	Vector4Int v1 = v.swizzle.wxyz;

	Vector3 v0 = { 1, 2, 3 };
	auto test0 = v0.ToVector2();

	auto v2 = v.swizzle.wyxz[ 1 ];


	auto a = Vector4::One;
	auto test = a[ 3 ];

	auto test2 = Vector2::One;

	Vector< float, 3 > v5 = Vector3::One;
	Vector< float, 3 > v6 = { 0.0f, 1.0f, 2.0f };
	v5 += v6;

	Matrix< int, 3, 3 > mat3 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto result = mat3.GetCol< 0 >() + v5;
}