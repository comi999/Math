#include <iostream>
#include "Math.hpp"



int main()
{
	auto diag = Matrix< int, 4>();
	auto mat = Matrix< int, 4 >{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	auto printTerms = []( auto& submat )
	{

		for ( int m = 0; m < submat.SizeM; ++m )
		{
			auto& row = submat.GetRow( m );

			for ( int n = 0; n < submat.SizeN; ++n )
			{
				std::cout << row[ n ] << std::endl;
			}
		}
	};

	//auto det = Math::Determinant( mat );
	//auto& sub = reinterpret_cast< SubMatrix< Indexer< int, 4, 4 >, Indexer< int, 4 >, size_t( -1 ), size_t( -1 ) >& >( mat );
	//sub.Determinant();
	auto& sub = mat.GetSubMatrix< 1, 1 >();
	sub.Determinant();
}