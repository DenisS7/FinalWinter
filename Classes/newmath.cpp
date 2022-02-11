#include "newmath.h"
#include <iostream>


bool newmath::inRange(int n, int min, int max)
{
	if (n < min || n > max)
		return false;
	return true;
}

bool newmath::isIncluded(int n, int v[], int vsize)
{
	for (int i = 0; i < vsize; i++)
		if (n == v[i])
			return true;
	return false;
}

void newmath::clamp(int& n, int min, int max)
{
	if (n < min)
		n = min;
	else if (n > max)
		n = max;
}

int newmath::getIndex(int n, int v[], int vsize)
{
	for (int i = 0; i < vsize; i++)
		if (v[i] == n)
			return i;
	return -1;
}


