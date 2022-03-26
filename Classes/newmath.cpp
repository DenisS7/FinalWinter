#include "newmath.h"



bool newmath::inRange(int n, int min, int max)
{
    if (n < min || n > max)
        return false;
    return true;
}

bool newmath::inRangef(float n, float min, float max)
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

int newmath::clamp(int n, int min, int max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

float newmath::clampf(float n, float min, float max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

int newmath::getIndex(int n, int v[], int vsize)
{
    for (int i = 0; i < vsize; i++)
        if (v[i] == n)
            return i;
    return -1;
}
