#pragma once
#include "MathCore.h"


// A list of static core math functions.
// These functions are universal and work on all platforms.
class TMath :public TMathCore
{
public:
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
	// Will force te value inputted to be between the Min and Max values.
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
	static INLINE double Square(const double Value)
	{
		return Square<double>(Value);
	}


	// Multiplies value by itself.
	static INLINE int32 Square(const int32 Value)
	{
		return Square<int32>(Value);
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
		return NearlyEqual(A, B, Range);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	static INLINE bool NearlyEqual(const int32 A, const int32 B, const float Range)
	{
		return NearlyEqual(A, B, Range);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	static INLINE bool NearlyEqual(const double A, const double B, const float Range)
	{
		return NearlyEqual(A, B, Range);
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
		return Range(Min, Max, Value);
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	static INLINE bool Range(const float& Min, const float& Max, const float& Value)
	{
		return Range(Min, Max, Value);
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	static INLINE bool Range(const double& Min, const double& Max, const double& Value)
	{
		return Range(Min, Max, Value);
	}


	//...


	


	


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