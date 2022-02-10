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

	auto& submat0 = mat.GetSubMatrix< 1, 1 >();

	for ( int m = 0; m < submat0.SizeM; ++m )
	{
		auto& row = submat0.GetRow( m );

		for ( int n = 0; n < submat0.SizeN; ++n )
		{
			std::cout << row[ n ] << std::endl;
		}
	}

	auto& submat = submat0.GetSubMatrix< 1, 1 >();
	
	for ( int m = 0; m < submat.SizeM; ++m )
	{
		auto& row = submat.GetRow( m );

		for ( int n = 0; n < submat.SizeN; ++n )
		{
			std::cout << row[ n ] << std::endl;
		}
	}

}