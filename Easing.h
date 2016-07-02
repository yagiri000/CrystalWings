#pragma once
#include <iostream>
#include <functional>
#include "Abstract.h"
#include "Vector2.h"

using EaseFuncptr = std::function<Vector2(int, int, Vector2, Vector2)>;

namespace Ease{
	double sinOut(double nowFrame, double allFrame, double startVal, double endVal);


};