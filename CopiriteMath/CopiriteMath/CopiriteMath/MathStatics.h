#pragma once
#include "GlobalValues.h"

#include <float.h>
#include <math.h>


#define TO_RADIAN(Value) { (float) ((Value) * (TMath::PI / 180.0f)) }
#define RADIAN { (float) (TMath::PI * 2.0f) }
#define TO_DEGREES(Value) { (float) ((Value) * (180.0f / TMath::PI)) }
#define DEGREES { (float) (TMath::PI / 180.0f) }



class TMath
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
		const float AbsX{ TMath::Abs(X) };
		const float AbsY{ TMath::Abs(Y) };
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


	// Clamps the value to be between the Min and Max.
	template <typename Type>
	static INLINE Type Clamp(const Type Min, const Type Max, const Type Value)
	{
		return (Value > Max) ? Max : (Value < Min) ? Min : Value;
	}


	// Clamps the value to be between the Min and Max.
	static INLINE float Clamp(const float Min, const float Max, const float Value)
	{
		return Clamp<float>(Min, Max, Value);
	}

	// Clamps the value to be between the Min and Max.
	static INLINE double Clamp(const double Min, const double Max, const double Value)
	{
		return Clamp<double>(Min, Max, Value);
	}


	// Clamps the value to be between the Min and Max.
	static INLINE int32 Clamp(const int32 Min, const int32 Max, const int32 Value)
	{
		return Clamp<int32>(Min, Max, Value);
	}


	// Clamps the value between the Min and Max.
	// Will force the value inputted to be between the Min and Max values.
	template <typename Type>
	static INLINE Type ForceClamp(const Type Min, const Type Max, Type& Value)
	{
		Value = Clamp<Type>(Min, Max, Value);
		return Value;
	}


	// Clamps the value between the Min and Max.
	// Will force the value inputted to be between the Min and Max values.
	static INLINE float ForceClamp(const float Min, const float Max, float& Value)
	{
		return ForceClamp<float>(Min, Max, Value);
	}


	// Clamps the value between the Min and Max.
	// Will force the value inputted to be between the Min and Max values.
	static INLINE double ForceClamp(const double Min, const double Max, double& Value)
	{
		return ForceClamp<double>(Min, Max, Value);
	}


	// Clamps the value between the Min and Max.
	// Will force the value inputted to be between the Min and Max values.
	static INLINE int32 ForceClamp(const int32 Min, const int32 Max, int32& Value)
	{
		return ForceClamp<int32>(Min, Max, Value);
	}


	// Shorthand of doing Clamp(0,1). 
	// Clamps the value to be between 0 and 1.
	template <typename Type>
	static INLINE Type Clamp01(const Type Value)
	{
		return Clamp<Type>((Type)0, (Type)1, Value);
	}


	// Shorthand of doing Clamp(0,1).
	// Clamps the value to be between 0 and 1.
	static INLINE float Clamp01(const float Value)
	{
		return Clamp01<float>(Value);
	}


	// Shorthand of doing Clamp(0,1).
	// Clamps the value to be between 0 and 1.
	static INLINE double Clamp01(const double Value)
	{
		return Clamp01<double>(Value);
	}


	// Shorthand of doing ForceClamp(0,1).
	// Clamps the value to be between 0 and 1.
	// WIll force te value inputted to be between the Min and Max values.
	template <typename Type>
	static INLINE Type ForceClamp01(Type& Value)
	{
		return ForceClamp<Type>((Type)0, (Type)1, Value);
	}


	// Shorthand of doing ForceClamp(0,1).
	// Clamps the value to be between 0 and 1.
	// WIll force te value inputted to be between the Min and Max values.
	static INLINE float ForceClamp01(float& Value)
	{
		return ForceClamp01<float>(Value);
	}


	// Shorthand of doing ForceClamp(0,1).
	// Clamps the value to be between 0 and 1.
	// WIll force te value inputted to be between the Min and Max values.
	static INLINE double ForceClamp01(double& Value)
	{
		return ForceClamp01<double>(Value);
	}


	// Multiplies value by itself.
	template <typename Type>
	static INLINE Type Square(const Type Value)
	{
		return Value * Value;
	}


	// Multiplies value by itself.
	static INLINE float Square(const float Value)
	{
		return Square<float>(Value);
	}


	// Multiplies value by itself.
	static INLINE int32 Square(const int32 Value)
	{
		return Square<int32>(Value);
	}


	// Multiplies value by itself.
	static INLINE double Square(const double Value)
	{
		return Square<double>(Value);
	}


	// Locks a value between a minimum and a maximum value.
	// @param Min - The lowest value the inputted value can be.
	// @param Max - The largest value the inputted value can be.
	// @param Percent - The variable being clamped.
	template <typename Type>
	static INLINE Type Lerp(const Type Min, const Type Max, const float Percent)
	{
		return (Type)((Max - Min) * Percent) + Min;
	}


	// Locks a value between a minimum and a maximum value.
	// @param Min - The lowest value the inputted value can be.
	// @param Max - The largest value the inputted value can be.
	// @param Percent - The variable being clamped.
	static INLINE float Lerp(const float Min, const float Max, const float Percent)
	{
		return Lerp<float>(Min, Max, Percent);
	}


	// Locks a value between a minimum and a maximum value.
	// @param Min - The lowest value the inputted value can be.
	// @param Max - The largest value the inputted value can be.
	// @param Percent - The variable being clamped.
	static INLINE double Lerp(const double Min, const double Max, const float Percent)
	{
		return Lerp<double>(Min, Max, Percent);
	}


	// Locks a value between a minimum and a maximum value.
	// @param Min - The lowest value the inputted value can be.
	// @param Max - The largest value the inputted value can be.
	// @param Percent - The variable being clamped.
	static INLINE int32 Lerp(const int32 Min, const int32 Max, const float Percent)
	{
		return Lerp<int32>(Min, Max, Percent);
	}


	// Gets a value betwee.
	// @param Percent - The variable being clamped.
	static INLINE float Lerp01(const float Percent)
	{
		return Lerp<float>(0.0f, 0.1f, Percent);
	}


	// Returns the percentage between two values.
	// @param Min - The minimum value.
	// @param Max - The maximum value.
	// @param Percent - The value (between 0 and 1) to retreive the percentage.
	// @Return - The value between the minimum and maximum based off the percentage.
	static INLINE const float Percent(const float Min, const float Max, const float Value)
	{
		return (Value - Min) / (Max - Min);
	}


	// Returns the percentage between two values.
	// @param Min - The minimum value.
	// @param Max - The maximum value.
	// @param Percent - The value (between 0 and 1) to retreive the percentage.
	// @Return - The percentage between the minimum and maximum based off the percentage.
	static INLINE const double Percent(const double Min, const double Max, const double Value)
	{
		return (Value - Min) / (Max - Min);
	}


	// Returns the percentage between two values.
	// @param Min - The minimum value.
	// @param Max - The maximum value.
	// @param Percent - The value (between 0 and 1) to retreive the percentage.
	// @Return - The percentage between the minimum and maximum based off the percentage.
	static INLINE const float Percent(const int32 Min, const int32 Max, const int32 Value)
	{
		return float(Value - Min) / float(Max - Min);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	template <typename Type>
	static INLINE bool NearlyEqual(const Type A, const Type B, const float Range)
	{
		return ((A >= B - Range) && A <= B + Range);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	static INLINE bool NearlyEqual(const float A, const float B, const float Range)
	{
		return NearlyEqual<float>(A, B, Range);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	static INLINE bool NearlyEqual(const int32 A, const int32 B, const float Range)
	{
		return NearlyEqual<int32>(A, B, Range);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	static INLINE bool NearlyEqual(const double A, const double B, const float Range)
	{
		return NearlyEqual<double>(A, B, Range);
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	template <typename Type>
	static INLINE bool Range(const Type& Min, const Type& Max, const Type& Value)
	{
		return ((Value >= Min) && (Value <= Max));
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	static INLINE bool Range(const int32& Min, const int32& Max, const int32& Value)
	{
		return Range<int32>(Min, Max, Value);
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	static INLINE bool Range(const float& Min, const float& Max, const float& Value)
	{
		return Range<float>(Min, Max, Value);
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	static INLINE bool Range(const double& Min, const double& Max, const double& Value)
	{
		return Range<double>(Min, Max, Value);
	}


	//...

	// Returns true if the inputted value is NaN.
	static INLINE bool IsNaN(float Value)
	{
		return _isnan(Value) != 0;
	}


	// Returns true if the inputted value is a finite number.
	static INLINE bool IsFinite(float Value)
	{
		return _finite(Value) != 0;
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


	// 
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


	// Returns signed fractional part of a float.
	// @param Value - The value to be converted.
	// @return - A value between >= 0 and < 1 for non-negative input. A value between >= -1 and  < 0 for negative input.
	static INLINE float Fractional(float Value)
	{
		return Value - TruncateFloat(Value);
	}


	// 
	template <typename Type, typename FuncType>
	static Type Derivative(const Type X, const Type DX, FuncType Func)
	{
		const Type DX1{ DX };
		const Type DX2{ DX1 * 2 };
		const Type DX3{ DX1 * 3 };

		const Type M1{ (Func(X + DX1) - Func(X - DX1)) / 2.0f };
		const Type M2{ (Func(X + DX2) - Func(X - DX2)) / 4.0f };
		const Type M3{ (Func(X + DX3) - Func(X - DX3)) / 6.0f };

		const Type FifteenM1{ 15.0f * M1 };
		const Type SixM2{ 6.0f * M2 };
		const Type TenDX1{ 10.0f * DX1 };

		return ((FifteenM1 - SixM2) + M3) / TenDX1;
	}
};