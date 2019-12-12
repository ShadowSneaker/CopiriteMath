#pragma once
#include "../GlobalValues.h"

#include <math.h>



#define TO_RADIAN(Value) { (float) ((Value) * (TMathCore::PI / 180.0f)) }
#define RADIAN { (float) (TMathCore::PI * 2.0f) }
#define TO_DEGREES(Value) { (float) ((Value) * (180.0f / TMathCore::PI)) }
#define DEGREES { (float) (TMathCore::PI / 180.0f) }



class TMathCore
{
public:
	/// Properties

	// The value of PI.
	static const float PI;

	// The value of PI multiplied by 2.
	static const float PI2;

	// The inverse value of PI.
	static const float InversePI;

	// The value of PI divided by 2.
	static const float Divide2PI;

	// 2 divided by the value of PI.
	static const float PIDivide2;

	// 4 divided by the value of PI.
	static const float PIDivide4;

	// The value of half PI.
	static const float HalfPI;


public:
	/// Statics

	// Calculates the Sine of the inputted value.
	static INLINE float Sin(float Value) { return sinf(Value); }

	// Calculates the ASine of the inputted value.
	static INLINE float ASin(float Value) { return asinf((Value < -1.0f) ? -1.0f : ((Value < 1.0f) ? Value : 1.0f)); }

	// Calculates the SineH of the inputted value.
	static INLINE float SinH(float Value) { return sinhf(Value); }

	// Calcualtes the Cosine of the inputted value.
	static INLINE float Cos(float Value) { return cosf(Value); }

	// Calculates the ACosine of the inputted value.
	static INLINE float ACos(float Value) { return acosf((Value < -1.0f) ? -1.0f : ((Value < 1.0f) ? Value : 1.0f)); }

	// Calculates the Tan of the inputted value.
	static INLINE float Tan(float Value) { return tanf(Value); }

	// Calculates the ATan of the inputted value.
	static INLINE float ATan(float Value) { return atanf(Value); }

	// Calculates the ATan of the inputted value.
	static INLINE float ATan2(float Y, float X)
	{
		const float AbsX{ Abs(X) };
		const float AbsY{ Abs(Y) };
		const bool HighestValue{ AbsY > AbsX };
		float T0{ (HighestValue) ? AbsY : AbsX };
		float T1{ (HighestValue) ? AbsX : AbsY };

		if (T0 == 0.0f) return 0.0f;

		float T3{ T1 / T0 };
		float T4{ T3 * T3 };

		static const float C[7] =
		{
			+7.2128853633444123e-03f,
			-3.5059680836411644e-02f,
			+8.1675882859940430e-02f,
			-1.3374657325451267e-01f,
			+1.9856563505717162e-01f,
			-3.3324998579202170e-01f,
			+1.0f
		};

		T0 = C[0];
		T0 = T0 * T4 + C[1];
		T0 = T0 * T4 + C[2];
		T0 = T0 * T4 + C[3];
		T0 = T0 * T4 + C[4];
		T0 = T0 * T4 + C[5];
		T0 = T0 * T4 + C[6];
		T3 = T0 * T3;

		T3 = (HighestValue) ? (0.5f * PI) - T3 : T3;
		T3 = (X < 0.0f) ? PI - T3 : T3;
		T3 = (Y < 0.0f) ? -T3 : T3;
		return T3;
	}


#define FASTASIN_HALF_PI (1.5707963050f)

	// Calculates a fast ASine of the inputted value
	static INLINE float FastASin(float Value)
	{
		bool NonNegative{ (Value >= 0.0f) };
		float X{ Abs(Value) };
		float OMX{ 1.0f - X };

		if (OMX < 0.0f)
		{
			OMX = 0.0f;
		}

		float Root{ Sqrt(OMX) };
		float Result{ ((((((-0.0012624911f * X + 0.0066700901f) * X - 0.0170881256f) * X + 0.0308918810f) * X - 0.0501743046f) * X + 0.0889789874f) * X - 0.2145988016f) * X + FASTASIN_HALF_PI };
		Result *= Root;
		return ((NonNegative) ? FASTASIN_HALF_PI - Result : Result - FASTASIN_HALF_PI);
	}

#undef FASTASIN_HALF_PI


	// Calculates the Sine and Cosine of a given value.
	// @param ScalarSin - A reference to the value to assign to the sine.
	// @param ScalarCos - A reference to the value to assign to the cosine.
	// @param Value - The value to calculate the sine and cosine.
	static void SinCos(float* ScalarSin, float* ScalarCos, float Value)
	{
		float Quotient = (InversePI * 0.5f) * Value;
		Quotient = (float)((int32)(Quotient + (Value >= 0.0f) ? 0.5f : -0.5f));

		float Y = Value - (2.0f * PI) * Quotient;

		float Sign;
		if (Y > HalfPI)
		{
			Y -= PI;
			Sign = -1.0f;
		}
		else if (Y < -HalfPI)
		{
			Y -= -PI;
			Sign = -1.0f;
		}
		else
		{
			Sign = 1.0f;
		}

		float Y2 = Y * Y;
		*ScalarSin = (((((-2.3889859e-08f * Y2 + 2.7525562e-06f) * Y2 - 0.00019840874f) * Y2 + 0.0083333310f) * Y2 - 0.16666667f) * Y2 + 1.0f) * Y;

		float P = ((((-2.6051615e-07f * Y2 + 2.4760495e-05f) * Y2 - 0.0013888378f) * Y2 + 0.041666638f) * Y2 - 0.5f) * Y2 + 1.0f;
		*ScalarCos = Sign * P;
	}


	// 
	// @param S1 - 
	// @param S2 - 
	// @param Epsilon - 
	// @return - 
	static INLINE bool ScalarNearEqual(float S1, float S2, float Epsilon)
	{
		float Delta = S1 - S2;
		return (fabsf(Delta) <= Epsilon);
	}


	// 
	// @param pSin - A reference to 
	// @param pCos - A reference to
	// @param Value - 
	DEPRECATED("This function is deprecated - Use TMath::SinCos() instead.")
		static INLINE void ScalarSinCos(float* pSin, float* pCos, float Value)
	{
		if (!pSin || !pCos)
		{
			return;
		}

		float Quotient = Divide2PI * Value;
		if (Value >= 0.0f)
		{
			Quotient = static_cast<float>(static_cast<int32>(Quotient + 0.5f));
		}
		else
		{
			Quotient = static_cast<float>(static_cast<int32>(Quotient - 0.5f));
		}

		float Y = Value - PI2 * Quotient;

		float Sign;
		if (Y > PIDivide2)
		{
			Y = PI - Y;
			Sign = -1.0f;
		}
		else if (Y < -PIDivide2)
		{
			Y = -PI - Y;
			Sign = -1.0f;
		}
		else
		{
			Sign = 1.0f;
		}

		float Y2 = Y * Y;

		*pSin = (((((-2.3889859e-08f * Y2 + 2.7525562e-06f) * Y2 - 0.00019840874f) * Y2 + 0.0083333310f) * Y2 - 0.16666667f) * Y2 + 1.0f) * Y;
		float P = ((((-2.6051615e-07f * Y2 + 2.4760495e-05f) * Y2 - 0.0013888378f) * Y2 + 0.041666638f) * Y2 - 0.5f) * Y2 + 1.0f;
		*pCos = Sign * P;
	}


	// Converts from Radians to Degrees
	// @param - The value to convert to radians.
	// @return - The converted value.
	static float ToRadians(float Degrees)
	{
		return TO_RADIAN(Degrees);
	}


	// Converts from Degrees to Radians.
	// @param - The value to convert to dagrees.
	// @return - The converted value.
	static float ToDegrees(float Radians)
	{
		return TO_DEGREES(Radians);
	}


	// Returns the result of number powered by a value.
	static INLINE float Power(const float A, const float B)
	{
		return powf(A, B);
	}


	// Returns the square root of an inputted value.
	static INLINE float Sqrt(const float Value)
	{
		return sqrtf(Value);
	}


	// Returns the inverted square root of an inputted value.
	static INLINE float InvSqrt(float F)
	{
		return 1.0f / sqrtf(F);
	}


	// Returns the absolute value of the inputted value.
	static INLINE float Abs(const float Value)
	{
		return fabsf(Value);
	}
};
