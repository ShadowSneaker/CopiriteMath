#pragma once
#include "../MathGlobals.h"

#include <math.h>
#include <float.h>


#define TO_RADIAN(Value) { ((Value) * (TMathCore::PI / 180.0f)) }
#define RADIAN { (TMathCore::PI * 2.0f) }
#define TO_DEGREES(Value) { ((Value) * (180.0f / TMathCore::PI)) }
#define DEGREES { (TMathCore::PI / 180.0f) }


// The universal platform declaration of math functions.
class TMathCore
{
public:
	/// Properties

	// The value of PI.
	static const float PI;

	// The value of PI.
	static const double PId;

	// The value of PI multiplied by 2.
	static const float PI2;

	// The value of PI multiplied by 2.
	static const double PI2d;

	// The inverse value of PI.
	static const float InversePI;

	// The inverse value of PI.
	static const double InversePId;

	// The value of PI divided by 2.
	static const float HalfPI;

	// The value of PI divided by 2.
	static const double HalfPId;


public:
	/// Statics

	// 
	static INLINE float Exp(float Value) { return expf(Value); }

	// 
	static INLINE double Exp(double Value) { return exp(Value); }

	// 
	static INLINE float Exp2(float Value) { return powf(2.0f, Value); }

	// 
	static INLINE double Exp2(double Value) { return pow(2.0, Value); }
	
	// 
	static INLINE float Log(float Value) { return logf(Value); }

	// 
	static INLINE double Log(double Value) { return log(Value); }

	// 
	static INLINE float LogX(float Base, float Value) { return Log(Value) / Log(Base); }

	// 
	static INLINE double LogX(double Base, double Value) { return Log(Value) / Log(Value); }

	// 
	static INLINE float Log2(float Value) { return Log(Value) * 1.4426950f; }

	// 
	static INLINE double Log2(double Value) { return Log(Value) * 1.4426950; }

	// Calculates the sine of the inputted value.
	static INLINE float Sin(float Value) { return sinf(Value); }

	// Calculates the sine of the inputted value.
	static INLINE double Sin(double Value) { return sin(Value); }

	// Calculates the asine of the inputted value.
	static INLINE float ASin(float Value) { return asinf((Value < -1.0f) ? -1.0f : ((Value < 1.0f) ? Value : 1.0f)); }

	// Calculates the asine of the inputted value.
	static INLINE double ASin(double Value) { return asin((Value < -1.0) ? -1.0 : ((Value < 1.0) ? Value : 1.0)); }

	// Calculates the sineH of the inputted value.
	static INLINE float SinH(float Value) { return sinhf(Value); }

	// Calculates the sineH of the inputted value.
	static INLINE double SinH(double Value) { return sinh(Value); }

	// Calcualtes the sosine of the inputted value.
	static INLINE float Cos(float Value) { return cosf(Value); }

	// Calculates the cosine of the inputted value.
	static INLINE double Cos(double Value) { return cos(Value); }

	// Calculates the acosine of the inputted value.
	static INLINE float ACos(float Value) { return acosf((Value < -1.0f) ? -1.0f : ((Value < 1.0f) ? Value : 1.0f)); }

	// Calculates the acosine of the inputted value.
	static INLINE double ACos(double Value) { return acos((Value < -1.0) ? -1.0 : ((Value < 1.0) ? Value : 1.0)); }

	// Calculates the tan of the inputted value.
	static INLINE float Tan(float Value) { return tanf(Value); }

	// Calculates the tan of the inputted value.
	static INLINE double Tan(double Value) { return tan(Value); }

	// Calculates the atan of the inputted value.
	static INLINE float ATan(float Value) { return atanf(Value); }

	// Calculates the atan of the inputted value.
	static INLINE double ATan(double Value) { return atan(Value); }

	// Calculates the atan of the inputted value.
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

		T0 = 7.2128853633444123e-03f;
		T0 = T0 * T4 + -3.5059680836411644e-02f;
		T0 = T0 * T4 + 8.1675882859940430e-02f;
		T0 = T0 * T4 + -1.3374657325451267e-01f;
		T0 = T0 * T4 + 1.9856563505717162e-01f;
		T0 = T0 * T4 + -3.3324998579202170e-01f;
		T0 = T0 * T4 + 1.0f;
		T3 = T0 * T3;

		T3 = (HighestValue) ? (0.5f * PI) - T3 : T3;
		T3 = (X < 0.0f) ? PI - T3 : T3;
		T3 = (Y < 0.0f) ? -T3 : T3;
		return T3;
	}


	// Calculates the atan of the inputted value
	static INLINE double ATan2(double Y, double X)
	{
		const double AbsX{ Abs(X) };
		const double AbsY{ Abs(Y) };
		const bool HighestValue{ AbsY > AbsX };
		double T0{ (HighestValue) ? AbsY : AbsX };
		double T1{ (HighestValue) ? AbsX : AbsY };

		if (T0 == 0.0) return 0.0;

		double T3{ T1 / T0 };
		double T4{ T3 * T3 };

		T0 = 7.2128853633444123e-03;
		T0 = T0 * T4 + -3.5059680836411644e-02;
		T0 = T0 * T4 + 8.1675882859940430e-02;
		T0 = T0 * T4 + -1.3374657325451267e-01;
		T0 = T0 * T4 + 1.9856563505717162e-01;
		T0 = T0 * T4 + -3.3324998579202170e-01;
		T0 = T0 * T4 + 1.0;
		T3 = T0 * T3;

		T3 = (HighestValue) ? (0.5 * PId) - T3 : T3;
		T3 = (X < 0.0) ? PId - T3 : T3;
		T3 = (Y < 0.0) ? -T3 : T3;
		return T3;
	}


#define FASTASIN_HALF_PI (1.5707963050f)

	// Calculates a fast asine of the inputted value
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


	// Calculates a fast asine of the inputted value.
	static INLINE double FastASin(double Value)
	{
		bool NonNegative{ (Value >= 0.0) };
		double X{ Abs(Value) };
		double OMX{ 1.0 - X };

		if (OMX < 0.0)
		{
			OMX = 0.0;
		}

		double Root{ Sqrt(OMX) };
		double Result{ ((((((-0.0012624911 * X + 0.0066700901) * X - 0.0170881256) * X + 0.0308918810) * X - 0.0501743046) * X + 0.0889789874) * X - 0.2145988016) * X + FASTASIN_HALF_PI };
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
		float Quotient{ (InversePI * 0.5f) * Value };
		Quotient = (float)((int32)(Quotient + (Value >= 0.0f) ? 0.5f : -0.5f));

		float Y{ Value - (2.0f * PI) * Quotient };

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

		float Y2{ Y * Y };
		*ScalarSin = (((((-2.3889859e-08f * Y2 + 2.7525562e-06f) * Y2 - 0.00019840874f) * Y2 + 0.0083333310f) * Y2 - 0.16666667f) * Y2 + 1.0f) * Y;

		float P{ ((((-2.6051615e-07f * Y2 + 2.4760495e-05f) * Y2 - 0.0013888378f) * Y2 + 0.041666638f) * Y2 - 0.5f) * Y2 + 1.0f };
		*ScalarCos = Sign * P;
	}


	// Calculates the Sine and Cosine of a given value.
	// @param ScalarSin - A reference to the value to assign to the sine.
	// @param ScalarCos - A reference to the value to assign to the cosine.
	// @param Value - The value to calculate the sine and cosine.
	static void SinCos(double* ScalarSin, double* ScalarCos, double Value)
	{
		double Quotient = (InversePI * 0.5) * Value;
		Quotient = (double)((int32)(Quotient + (Value >= 0.0) ? 0.5 : -0.5));

		double Y = Value - (2.0 * PId) * Quotient;

		double Sign;
		if (Y > HalfPId)
		{
			Y -= PId;
			Sign = -1.0;
		}
		else if (Y < -HalfPId)
		{
			Y -= -PId;
			Sign = -1.0;
		}
		else
		{
			Sign = 1.0;
		}

		double Y2 = Y * Y;
		*ScalarSin = (((((-2.3889859e-08 * Y2 + 2.7525562e-06) * Y2 - 0.00019840874) * Y2 + 0.0083333310) * Y2 - 0.1666666666666) * Y2 + 1.0) * Y;

		double P = ((((-2.6051615e-07 * Y2 + 2.4760495e-05) * Y2 - 0.0013888378) * Y2 + 0.041666638) * Y2 - 0.5) * Y2 + 1.0;
		*ScalarCos = Sign * P;
	}


	// 
	// @param S1 - 
	// @param S2 - 
	// @param Epsilon - 
	// @return - 
	static INLINE bool ScalarNearEqual(float S1, float S2, float Epsilon)
	{
		float Delta{ S1 - S2 };
		return (fabsf(Delta) <= Epsilon);
	}


	// Converts from radians to degrees.
	// @param - The value to convert to radians.
	// @return - The converted value.
	static float ToRadians(float Degrees)
	{
		return Degrees * (PI / 180.0f);
	}


	// Converts from radians to degrees.
	// @param - The value to convert to radians.
	// @return - The converted value.
	static double ToRadians(double Degrees)
	{
		return Degrees * (PId / 180.0);
	}


	// Converts from degrees to radians.
	// @param - The value to convert to degrees.
	// @return - The converted value.
	static float ToDegrees(float Radians)
	{
		return Radians * (180.0f / PI);
	}


	// Converts from degrees to radians.
	// @param - The value to convert to degrees.
	// @return - The converted value.
	static double ToDegrees(double Radians)
	{
		return Radians * (180.0 / PId);
	}


	// Returns the result of number powered by a value.
	static INLINE float Power(const float Value, const float Exponent)
	{
		return powf(Value, Exponent);
	}


	// Returns the result of a number powered by a value.
	static INLINE double Power(const double Value, const double Exponent)
	{
		return pow(Value, Exponent);
	}


	// Returns the square root of an inputted value.
	static INLINE float Sqrt(const float Value)
	{
		return sqrtf(Value);
	}


	// Returns the square root of an inputted value.
	static INLINE double Sqrt(const double Value)
	{
		return sqrt(Value);
	}


	// Returns the inverted square root of an inputted value.
	static INLINE float InvSqrt(float Value)
	{
		return 1.0f / sqrtf(Value);
	}


	// Returns the inverted square root of an inputted value.
	static INLINE double InvSqrt(double Value)
	{
		return 1.0 / sqrt(Value);
	}


	// Returns the absolute value of the inputted value.
	static INLINE float Abs(const float Value)
	{
		return fabsf(Value);
	}


	// Returns the absolute value of the inputted value.
	static INLINE double Abs(const double Value)
	{
		return fabs(Value);
	}


	// Returns true if the inputted value is NaN.
	template <typename Type>
	static INLINE bool IsNaN(Type Value)
	{
		return isnan(Value);
	}


	// Returns true if the inputted value is NaN.
	static INLINE bool IsNaN(float Value)
	{
		return _isnan(Value) != 0;
	}


	// Returns true if the inputted value is a finite number.
	template <typename Type>
	static INLINE bool IsFinite(Type Value)
	{
		return isfinite(Value);
	}


	// Returns true if the inputted value is a finite number.
	static INLINE bool IsFinite(float Value)
	{
		return _finite(Value) != 0;
	}


	// Returns true if the value is negative.
	static INLINE bool IsNegative(const int32& Value)
	{
		return ((*(uint32*)&Value) >= (uint32)0x80000000);
	}


	// Returns true if the value is negative.
	static INLINE bool IsNegative(const float& Value)
	{
		return ((*(uint32*)&Value) >= (uint32)0x80000000);
	}


	// Returns true if the value is negative.
	static INLINE bool IsNegative(const double& Value)
	{
		return ((*(uint64*)&Value) >= (uint64)0x8000000000000000);
	}


	// Returns the higher value between two inputted values.
	template <class Type>
	static INLINE Type Max(const Type A, const Type B)
	{
		return (A >= B) ? A : B;
	}


	// Returns the lowest value between two inputted value.
	template <class Type>
	static INLINE Type Min(const Type A, const Type B)
	{
		return (A <= B) ? A : B;
	}


	// Returns a value based on comparand.
	static INLINE float FloatSelect(float Comparand, float ValueGEZero, float ValueLTZero)
	{
		return ((Comparand >= 0.0f) ? ValueGEZero : ValueLTZero);
	}


	// Removes the decimal point in a inputted floating point value.
	static INLINE int32 TruncateInt(float Value)
	{
		return (int32)Value;
	}


	// Removes the decimal point in an inputted floating point value.
	static INLINE float TruncateFloat(float Value)
	{
		return (float)TruncateInt(Value);
	}


	// Removes the decimal point in an inputted double value.
	static INLINE double TruncateDouble(float Value)
	{
		return (double)TruncateInt(Value);
	}


	// Rounds the inputted float down to the nearest or equal integer.
	// @param Value - The value to convert.
	// @return - An integer less than or equal to the inputted value.
	static INLINE int32 FloorInt(float Value)
	{
		return TruncateInt(floorf(Value));
	}


	// Rounds the inputted float down to the nearest or equal integer.
	// @param Value - The value to convert.
	// @return - An integer less than or equal to the inputted value.
	static INLINE float FloorFloat(float Value)
	{
		return floorf(Value);
	}


	// Rounds the inputted double down to the nearest or equal integer.
	// @param Value - The value to convert.
	// @return - An integer less than or equal to the inputted value.
	static INLINE double FloorDouble(double Value)
	{
		return floor(Value);
	}


	// Rounds the inputted float up to the nearest or equal integer.
	// @param Value - The value to convert.
	// @return - The rounded up integer.
	static INLINE int32 CeilingInt(float Value)
	{
		return TruncateInt(ceilf(Value));
	}


	// Rounds the inputted float up to the nearest or equal integer.
	// @param Value - The value to convert.
	// @return - The rounded up integer.
	static INLINE float CeilingFloat(float Value)
	{
		return ceilf(Value);
	}


	// Rounds the inputted double up to the nearest or equal integer.
	// @param Value - The value to convert.
	// @return - The rounded up integer.
	static INLINE double CeilingDouble(double Value)
	{
		return ceil(Value);
	}


	// Rounds the inputted value to the nearest integer. Rounds up if the bounds is above 0.5f.
	// @param Value - The value to convert.
	// @return - The nearest integer to the inputted value.
	static INLINE int32 RoundInt(float Value)
	{
		return FloorInt(Value + 0.5f);
	}


	// Rounds the inputted value to the nearest integer. Rounds up if the bounds is above 0.5f.
	// @param Value - The value to convert.
	// @return - The nearest integer to the inputted value.
	static INLINE float RoundFloat(float Value)
	{
		return FloorFloat(Value + 0.5f);
	}


	// Rounds the inputted value to the nearest integer. Rounds up if the bounds is above 0.5.
	// @param Value - The value to convert.
	// @return - The nearest integer to the inputted value.
	static INLINE double RoundDouble(double Value)
	{
		return FloorDouble(Value + 0.5);
	}


	// Returns signed fractional part of a float.
	// @param Value - The value to be converted.
	// @return - A value between >= 0 and < 1 for non-negative input. A value between >= -1 and  < 0 for negative input.
	static INLINE float Fractional(float Value)
	{
		return Value - TruncateFloat(Value);
	}


	// Returns the remainder of X / Y.
	// @warning - Always returns the remainder toward 0, not toward the smaller multiple of Y.
	// @note - Use Floor instead when snapping positions that can ve negative to a grid.
	static INLINE float FMod(float X, float Y)
	{
		if (fabsf(Y) <= 1.e-8f)
		{
			return 0.0f;
		}

		const float Quotient{ TruncateFloat(X / Y) };
		float IntPortion{ Y * Quotient };

		if (fabsf(IntPortion) > fabsf(X))
		{
			IntPortion = X;
		}
		return X - IntPortion;
	}
};
