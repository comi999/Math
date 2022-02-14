#include <iostream>
#include "Math.hpp"

using namespace std;

int main()
{
	auto lookat = Matrix4::LookAt( Vector3::Zero, Vector3::One, Vector3::Up );
}