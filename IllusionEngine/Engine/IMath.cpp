#include "IMath.h"

const Vector2 Vector2:: Zero(0.0f, 0.0f);

double IMath::ToDegrees(double radian)
{
	return radian * 180.0 / Math_PI;
}