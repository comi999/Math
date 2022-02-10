#include <iostream>
#include "Math.hpp"

int main()
{
	auto diag = Matrix< int, 3, 3 >{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	auto mat = Matrix< int, 4 >{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	auto tra = mat.transverse.ToMatrixMN< 4, 4 >();

}