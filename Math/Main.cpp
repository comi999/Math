#include <iostream>
#include "Math.hpp"

using namespace std;

int main()
{
	Matrix< float, 3 > mat = { 3, 0, 2, 2, 0, -2, 0, 1, 1 };

	//auto det = Math::Determinant( mat );
	auto cof = Math::Cofactor( mat );
	auto adj = Math::Adjoint( mat );
	auto inv = Math::Inverse( mat );
}