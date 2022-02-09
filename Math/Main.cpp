#include <iostream>
#include "Math.hpp"

int main()
{
	Vector4 v = { 1.0f, 2.2f, 3.1f, 4.8f };
	Vector4Int v1 = v.swizzle.wxyz;
	initializer_list< int > list = { 1 };
	Vector< int, 1 > small = list;
	Vector3 v0 = { 1, 2, 3 };
	auto test0 = v0.ToVector2();

	auto v2 = v.swizzle.wyxz[ 1 ];


	auto a = Vector4::One;
	auto test = a[ 3 ];

	auto test2 = Vector2::One;

	Vector< float, 3 > v5 = Vector3::One;
	Vector< float, 3 > v6 = { 0.0f, 1.0f, 2.0f };
	v5 += v6;

	
	//Matrix< int, 2, 3 > m { 1, 2, 3, 4, 5, 6 };

}