#include <iostream>
#include "Easing.h"
#include "myglobal.h"


namespace Ease{
	double sinOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < allFrame){
			return start + (end - start) * sin(PI / 2 * nowFrame / allFrame);
		}
		else if(nowFrame < 0){
			return start;
		}
		else{
			return end;
		}
	}
};