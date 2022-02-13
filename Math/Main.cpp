#include <iostream>
#include "Math.hpp"

using namespace std;

int main()
{
	int mini = 0;
	int maxi = 10;
	
	int res0 = Math::Clamp( -10, mini, maxi );
	int res1 = Math::Clamp( 20, mini, maxi );
	int res2 = Math::Clamp( 5, mini, maxi );
	float val = 0.0f;
	bool res = Math::IsInf( 1.0f / val );
}