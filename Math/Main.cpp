#include <iostream>
#include "Math.hpp"

int main()
{
	auto diag = Matrix< int, 4>();
	auto mat = Matrix< int, 4 >{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	diag = mat;
	auto tra = mat.transverse.ToMatrixMN< 4, 4 >();

	auto mat0 = Matrix2::Identity;
	auto mat1 = Matrix2( 2, 1, 2, 1 );
	auto mat2 = Math::Multiply( mat0, mat1 );

	mat1 *= 2;
}