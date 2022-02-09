#include <iostream>
#include "Math.hpp"

int main()
{
	Vector2Int v0( 1, 2 );
	Vector2 v1( 2, 3 );
	auto v2 = v0 * v1;
	Vector< int, 5 > v12;

	auto one = Vector< int, 6 >::One;
	auto zer = Vector< float, 3 >::Zero;

	auto v3 = v0.swizzle.xx.ToVector();

	Matrix< int, 2, 3 > mat;
	
	for ( int i = 0; i < 6; ++i )
	{
		mat.Data[ i ] = i;
	}

	auto v4 = mat.GetCol( 2 ) * v1;
	auto v5 = mat.ToVector4();

	auto mat1 = mat.ToMatrixMN< 1, 2 >( 1, 1 );

	auto mat2 = Matrix< int, 3, 3 >::One;

	auto mat5 = Matrix< int, 2, 2 >::Identity;
}