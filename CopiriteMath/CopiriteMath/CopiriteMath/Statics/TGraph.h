#pragma once
#include "MathCore.h"


class TGraph :public TMathCore
{


	// Finds the area beneath a curve.
	// @note - Increasing the StepCount increases accuracy but slows the calculation down.
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