/*
	g++ -Wall -Wextra FastInverseSQRT.cpp -o FastInverseSQRT
*/
#include <iostream>

float FastInvSQRT(float x) {
	float xhalf = 0.5f * x;

	int i = *(int *)&x;
	i = 0x5f3759df - (i >> 1);

	x = *(float *)&i;
	x = x * (1.5f - (xhalf * x * x));
	// x = x*(1.5f-(xhalf*x*x));

	return x;
}

int main() {
	std::cout << FastInvSQRT(2) << std::endl;
	return 0;
}
