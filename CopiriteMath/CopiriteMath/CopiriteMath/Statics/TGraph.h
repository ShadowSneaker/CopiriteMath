#pragma once
#include "MathCore.h"


class TGraph :public TMathCore
{



	// @return - The area of the curve.
	template <typename Type>
	static Type Integration(Type Start, Type End, uint StepCount, Type(*Function)(Type))
	{
		const Type Step{ (End - Start) / StepCount };
		Type Result;
		for (uint i = 0; i < StepCount; ++i)
		{
			Area += Function(Start + (i + (Type)0.5f) * Step) * Step;
		}
		return Result;
	}
};