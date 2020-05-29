#pragma once
#include "../MathGlobals.h"
#include "../Statics/MathStatics.h"

#include <iostream>


// Other libraries (if included)

#ifdef INCLUDE_DIRECTX_MATH
#include <DirectXMath.h>
#endif // INCLUDE_DIRECTX_MATH

#ifdef INCLUDE_SDL
#include<SDL.h>
#endif


#pragma warning(disable : 26812)
// Stores the different types of axis'.
// Used to easily access values in a vector.
enum EAxis : uint32
{
	X = 0x0,		// The X axis.
	Y = 0x1,		// The Y axis.
	Z = 0x2,		// The Z axis.
	W = 0x3			// The W axis.
};
//DEFINE_ENUM_FLAG_OPERATORS(EAxis);


// Represents a point in space in a specifid amount of dimensions.
// @template Size - How many dimensions this vector should have.
// @template Type - The datatype this vector should use.
template <uint Size, typename Type>
struct STVector
{
private:
	/// Properties

	// Stores all elements of this vector.
	Type Data[Size]{ 0 };


public:
	/// Constructors

	// Constructor, Default. Creates an empty vector.
	INLINE STVector<Size, Type>();

	// Constructor, Initializes all vector components with the inputted value.
	// @param Value - The value used to initialize all components with.
	INLINE STVector<Size, Type>(Type Value);

	// Constructor, Initiates a vector2 using 2 values.
	// @param InX - The value used to initialize this vector's X component.
	// @param InY - The value used to initialize this vector's Y component.
	INLINE STVector<Size, Type>(Type InX, Type InY);

	// Constructor, Initiates a vector3 using 3 values.
	// @param InX - The value used to initialize this vector's X component.
	// @param InY - The value used to initialize this vector's Y component.
	// @param InZ - The value used to initialize this vector's Z component.
	INLINE STVector<Size, Type>(Type InX, Type InY, Type InZ);

	// Constructor, Initiates a vector3 using a 2D vector and a value.
	// @param InV - The vector2 used to initiate this vector's X and Y components.
	// @param InZ - The value used to initialize this vector's Z component.
	INLINE STVector<Size, Type>(STVector<2, Type> InV, Type InZ);

	// Constructor, Initiates a vector4 using 4 values.
	// @param InX - The value used to initialize this vector's X component.
	// @param InY - The value used to initialize this vector's Y component.
	// @param InZ - The value used to initialize this vector's Z component.
	// @param InW - The value used to initialize this vector's W component.
	INLINE STVector<Size, Type>(Type InX, Type InY, Type InZ, Type InW);

	// Constructor, Initiates a vector4 using 2 vector2s.
	// @param V1 - The vector2 used to initialize this vector's X and Y components.
	// @param V2 - The vector2 used to initialize this vector's Z and W components.
	INLINE STVector<Size, Type>(STVector<2, Type> V1, STVector<2, Type> V2);

	// Constructor, Initiates a vector4 using a vector2 and 2 values.
	// @param V - The vector2 used to initialize this vector's X and Y components.
	// @param InZ - The value used to initialize this vector's Z component.
	// @param InW - The value used to initialize this vector's W component.
	INLINE STVector<Size, Type>(STVector<2, Type> V, Type InZ, Type InW);

	// Constructor, Initiates a vector4 using a vector3 and a value.
	// @param V - The vector3 used to initialize this vector's X, Y and Z components.
	// @param InW - The value used to initialize this vector's W component.
	INLINE STVector<Size, Type>(STVector<3, Type> V, Type InW);

	// Constructor, Initializes this vector with an array of values.
	// @note - The array size must be the same size as this vector.
	// @param Values - The array to initialize all components of this vector.
	INLINE STVector<Size, Type>(Type Values[Size]);

	// Constructor, Initializes this vector with the components of another vector.
	// @template Size2 - The size of the other vector.
	// @template Type2 - The datatype the other vector uses.
	// @param Other - The other vector to copy the values from.
	// @param Flood - The value to give this vector to empty components if the other vector is smaller than this one.
	template <uint Size2, typename Type2>
	STVector<Size, Type>(STVector<Size2, Type2> Other, Type Flood = (Type)0.0f);



	/// Operators

	// Operator, Returns teh result of an addition between this vector and another vector.
	template <uint Size2, typename Type2>
	INLINE STVector<Size, Type> operator+(const STVector<Size2, Type2>& Other) const;

	// Operator, Returns the result of an addition between this vector and a value.
	INLINE STVector<Size, Type> operator+(const Type& Value) const;

	// Operator, Returns the result of an addition between a value and this vector.
	INLINE friend STVector<Size, Type> operator+(const Type& Value, const STVector<Size, Type>& Other)
	{
		STVector<Size, Type> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = Value + Other[i];
		}
		Result.CheckNaN();
		return Result;
	}

	// Operator, Sets this vector's values with the result of an addition between this vector and another vector.
	template <uint Size2, typename Type2>
	INLINE STVector<Size, Type> operator+=(const STVector<Size2, Type2>& Other);

	//Operator, Sets this vector's values with the result of an addition between this vector and a value.
	INLINE STVector<Size, Type> operator+=(const Type& Value);

	// Operator, Returns the result of a subtraction between this vector and another vector.
	template <uint Size2, typename Type2>
	INLINE STVector<Size, Type> operator-(const STVector<Size2, Type2>& Other) const;

	// Operator, Returns the result of a subtraction between this vector and a value.
	INLINE STVector<Size, Type> operator-(const Type& Value) const;

	// Operator, Returns the result of a subtraction between a value and this vector.
	INLINE friend STVector<Size, Type> operator-(const Type& Value, const STVector<Size, Type>& Other)
	{
		STVector<Size, Type> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = Value - Other[i];
		}
		Result.CheckNaN();
		return Result;
	}

	// Operator, Returns the contents of this vector but negative.
	INLINE STVector<Size, Type> operator-() const;

	// Operator, Sets this vector's values with the result of a subtraction between this vector and another vector.
	template <uint Size2, typename Type2>
	INLINE STVector<Size, Type> operator-=(const STVector<Size2, Type2>& Other);

	// Operator, Sets this vector's values with the result of a subtraction between this vector and a value.
	INLINE STVector<Size, Type> operator-=(const Type& Value);

	// Operator, Returns the result of a multiplication between this vector and another vector.
	template <uint Size2, typename Type2>
	INLINE STVector<Size, Type> operator*(const STVector<Size2, Type2>& Other) const;

	// Operator, Returns the result of a multiplication between this vector and a value.
	INLINE STVector<Size, Type> operator*(const Type& Value) const;

	// Operator, Returns the result of a multiplication between a value and this vector.
	INLINE friend STVector<Size, Type> operator*(const Type& Value, const STVector<Size, Type>& Other)
	{
		STVector<Size, Type> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = Value * Other[i];
		}
		Result.CheckNaN();
		return Result;
	}

	// Operator, Sets this vector's values with the result of a multiplication between this vector and another vector.
	template <uint Size2, typename Type2>
	INLINE STVector<Size, Type> operator*=(const STVector<Size2, Type2>& Other);

	// Operator, Sets this vector's values with the result of a multiplication between this vector and a value.
	INLINE STVector<Size, Type> operator*=(const Type& Value);

	// Operator, Returns the result of a division between this vector and another vector.
	template <uint Size2, typename Type2>
	INLINE STVector<Size, Type> operator/(const STVector<Size2, Type2>& Other) const;

	// Operator, Returns the result of a division between this vector and a value.
	INLINE STVector<Size, Type> operator/(const Type& Value) const;

	// Operator, Returns the result of a division between a value and this vector.
	INLINE friend STVector<Size, Type> operator/(const Type& Value, const STVector<Size, Type>& Other)
	{
		STVector<Size, Type> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = Value / Other[i];
		}
		Result.CheckNaN();
		return Result;
	}

	// Operator, Sets this vector's values with the result of a division between this vector and another vector.
	template <uint Size2, typename Type2>
	INLINE STVector<Size, Type> operator/=(const STVector<Size2, Type2>& Other);

	// Operator, Sets this vector's values with the result of a division between this vector and a value.
	INLINE STVector<Size, Type> operator/=(const Type& Value);

	// Operator, Increments all the components of this vector by 1.
	INLINE STVector<Size, Type> operator++();

	// Operator, Decrements all the components of this vector by 1.
	INLINE STVector<Size, Type> operator--();

	// Operator, Assigns all components to a value.
	INLINE STVector<Size, Type> operator=(const Type& Value);

	// Operator, Calculates the cross product between this vector and another vector.
	INLINE STVector<Size, Type> operator|(const STVector<Size, Type>& Other) const;

	// Operator, Calculates the dot product between this vector and another vector.
	INLINE Type operator^(const STVector<Size, Type>& Other) const;

	// Operator, Tests if each component in this vector is greater than the corosponding component in another vector.
	INLINE bool operator>(const STVector<Size, Type>& Other) const;

	// Operator, Tests if all components in this vector is greater than a value.
	INLINE bool operator>(const Type& Value) const;

	// Operator, Tests if each component in this vector is greater than or equal to the corosponding component in another vector.
	INLINE bool operator>=(const STVector<Size, Type>& Other) const;

	// Operator, Tests if all components in this vector is greater than or equal to a value.
	INLINE bool operator>=(const Type& Value) const;

	// Operator, Tests if each component in this vector is less than the corosponding component in another vector.
	INLINE bool operator<(const STVector<Size, Type>& Other) const;

	// Operator, Tests if all components in this vector is less than a vlue.
	INLINE bool operator<(const Type& Value) const;

	// Operator, Tests if each component in this vector is less than or equal to the corosponding component in another vector.
	INLINE bool operator<=(const STVector<Size, Type>& Other) const;

	// Operator, Tests if all components in this vector is less than or equal to a value.
	INLINE bool operator<=(const Type& Value) const;

	// Operator, Tests if each component in this vector is equal to the corosponding component in another vector.
	INLINE bool operator==(const STVector<Size, Type>& Other) const;

	// Operator, Tests if all the components of this vector is equal to a value.
	INLINE bool operator==(const Type& Value) const;

	// Operator, Tests if each component in this vector is not equal to the corosponding component in another vector.
	INLINE bool operator!=(const STVector<Size, Type>& Other) const;

	// Operator, Tests if all the components of this vector is not equal to a value.
	INLINE bool operator!=(const Type& Value) const;

	// Operator, Returns the vector component value at the given index.
	INLINE Type& operator[](const uint& Index);

	// Operator, Returns the vector component value at the given index.
	INLINE Type operator[](const uint& Index) const;

	// Operator, Returns the vector component value at the given axis.
	INLINE Type& operator[](const EAxis& Axis);

	// Operator, Returns the vector component value at the given axis.
	INLINE Type operator[](const EAxis& Axis) const;



	/// Debug

	// Debug diagnostics handle for when a vector contains NaN in any component.
	// @note - This will set this vector to a vector0 if it contains NaN.
	INLINE void CheckNaN();

	// Check if this vector's components contains NaN.
	// @return - True if a component contains NaN.
	INLINE bool ContainsNaN() const;

	// Prints out the contents of this vector to the console.
	INLINE void Print() const;



	/// Conversions

#ifdef INCLUDE_DIRECTX_MATH

	// Converts a DirectX::XMVECTOR to this type of vector.
	// @param V - The XMVECTOR to convert.
	// @return - The converted vector.
	static INLINE STVector<Size, Type> FromXMVector(DirectX::XMVECTOR Vector);

	// Converts this vector to a DirectX::XMVECTOR.
	INLINE DirectX::XMVECTOR ToXMVector() const;

#endif // INCLUDE_DIRECTX_MATH


#ifdef INCLUDE_SDL
	// Converts a SDL_Rect to this type of vector.
	// @param Rect - The SDL_Rect to convert.
	// @return = The converted vector.
	static INLINE STVector<Size, Type> FromSDL_Rect(SDL_Rect Rect);

	// Converts a SDL_FRect to this type of vector.
	// @param Rect - The SDL_FRect to convert.
	// @return = The converted vector.
	static INLINE STVector<Size, Type> FromSDL_FRect(SDL_FRect Rect);

	// Converts a SDL_FPoint to this type of vector.
	// @param Point - The SDL_FPoint to convert.
	// @return = The converted vector.
	static INLINE STVector<Size, Type> FromSDL_Point(SDL_Point Point);

	// Converts a SDL_FPoint to this type of vector.
	// @param Point - The SDL_FPoint to convert.
	// @return = The converted vector.
	static INLINE STVector<Size, Type> FromSDL_FPoint(SDL_FPoint Point);

	// Converts this vector to a SDL_Rect.
	INLINE SDL_Rect ToRect() const;

	// Converts this vector to a SDL_FRect.
	INLINE SDL_FRect ToFRect() const;

	// Converts this vector to a SDL_FPoint.
	INLINE SDL_Point ToPoint() const;

	// Converts this vector to a SDL_FPoint.
	INLINE SDL_FPoint ToFPoint() const;

#endif // INCLUDE_SDL


	// Converts this vector to represent a rotation of unit length.
	INLINE STVector<3, float> Rotation() const;

	// Converts this vector to a specified type.
	// @template NewType - The new datatype this vector should be.
	template <typename NewType>
	INLINE STVector<Size, NewType> ToType();

	// Converts this vector to a specified type.
	// @template NewType - The new datatype this vector should be.
	template <typename NewType>
	INLINE STVector<Size, NewType> ToType() const;

	// Converts this vector to a floating point vector.
	INLINE STVector<Size, float> ToFloat();

	// Converts this vector to a floating point vector.
	INLINE STVector<Size, float> ToFloat() const;

	// Converts this vector to a double type vector.
	INLINE STVector<Size, double> ToDouble();

	// Converts this vector to a double type vector.
	INLINE STVector<Size, double> ToDouble() const;

	// Converts this vector to an integer vector.
	INLINE STVector<Size, int32> ToInt();

	// Converts this vector to an integer vector.
	INLINE STVector<Size, int32> ToInt() const;



	/// Functions

	// Calculates the cross product between this vector and another vector.
	// @param Other - The inputted vector to calculate against.
	// @return - The resulting vector.
	INLINE STVector<Size, Type> CrossProduct(const STVector<Size, Type>& Other) const;

	// Calculates the dot product between thsi vector an another vector.
	// @param Other - The inputted vector to calculate against.
	// @return - The resulting vector.
	INLINE float DotProduct(const STVector<Size, Type>& Other) const;

	// Creates a vector with the highest values in each dimension between this vector and an inputted vector.
	// @param Other - The inputted vector to calculate against.
	// @return - The resulting vector.
	INLINE STVector<Size, Type> Max(const STVector<Size, Type>& Other) const;

	// Creates a vector with the lowest values in each dimension between this vector and an inputted vector.
	// @param Other - The inputted vector to calculate against.
	// @return - The resulting vector.
	INLINE STVector<Size, Type> Min(const STVector<Size, Type>& Other) const;

	// Normalize the vector.
	// @param Tolerance - Minimum square vector length.
	INLINE void Normalize(float Tolerance = MICRO_NUMBER);

	// Returns true if this vector is almost equal to another vector.
	// @param Other - The vector to compare with.
	// @param Threshold - The range in which the other vector can be in.
	// @return - Returns true if the other vector is within range of this vector.
	INLINE bool NearlyEqual(const STVector<Size, Type>& Other, const Type& Threshold = MICRO_NUMBER) const;

	// Checks to see if this vector is a zero vector.
	// @param Threshold - The range in which this vector can be in.
	// @return - True if all components in this vector are equal to 0.
	INLINE bool IsZero(float Threshold = MICRO_NUMBER) const;

	// Powers every component of this vector.
	// @param Exponent - The amount of times the component will be multiplied.
	// @return - A copy of this vector after being powered.
	INLINE STVector<Size, Type> Power(uint Exponent) const;

	// Multiplies this vector by itself.
	// @return - A copy of this vector doubled.
	INLINE STVector<Size, Type> Square() const;

	// Adds all of this vector's components together.
	// @return - The sum of this vector's components.
	INLINE float GetSize() const;

	// Squares all of this vector's components then adds them together.
	// @return - The sum of this vector's components multiplied by itself.
	INLINE float SizeSquared() const;

	// Creates a copy of this vector resized to a different size.
	// @template NewSize - The size of the new vector to be created.
	// @param Value - The value to add to the end of the vector (if the new size is larger than the current size).
	// @return - A copy of this vector resized.
	template <uint NewSize>
	INLINE STVector<NewSize, Type> Resize(const Type& Value = 0.0f) const;

	// Rotates around an axis.
	// @note - Assumes the axis size is equal to 1.
	// @param AngleDegrees - Angle to rotate (in degrees).
	// @param Axis - Axis to rotate around.
	// @return - The rotated vector.
	inline STVector<3, float> RotateAxis(const float AngleDegrees, const STVector<3, float>& Axis) const;

	// Gets a normalized copy of the vector.
	// @param Tolerance - Minimum square vector length.
	// @return - A normalized copy if safe, returns a zero vector otherwise.
	INLINE STVector<Size, Type> SafeNormal(float Tolerance = MICRO_NUMBER) const;



	/// Setters

	// Sets all components of this vector2.
	// @param X - The value to put into the X component.
	// @param Y - The value to put into the Y component.
	INLINE void Set(const Type& X, const Type& Y);

	// Sets all components of this vector3.
	// @param X - The value to put into the X component.
	// @param Y - The value to put into the Y component.
	// @param Z - The value to put into the Z component.
	INLINE void Set(const Type& X, const Type& Y, const Type& Z);

	// Sets all components of this vector4.
	// @param X - The value to put into the X component.
	// @param Y - The value to put into the Y component.
	// @param Z - The value to put into the Z component.
	// @param W - The value to put into the W component.
	INLINE void Set(const Type& X, const Type& Y, const Type& Z, const Type& W);

	// Sets the X component to the inputted value.
	// @param Value - The value to set the X component.
	INLINE void SetX(const Type& Value);

	// Sets the Y component to the inputted value.
	// @param Value - The value to set the Y component.
	INLINE void SetY(const Type& Value);

	// Sets the Z component to the inputted value.
	// @param Value - The value to set the Z component.
	INLINE void SetZ(const Type& Value);

	// Sets the W component to the inputted value.
	// @param Value - The value to set the W component.
	INLINE void SetW(const Type& Value);



	/// Getters

	// Returns the highest component in this vector.
	INLINE Type MaxComp() const;

	// Returns the absolute component with the highest value in this vector.
	INLINE Type AbsMaxComp() const;
	
	// Returns the lowest component in this vector.
	INLINE Type MinComp() const;

	// Returns the absolute component with the lowest value in this vector.
	INLINE Type AbsMinComp() const;

	// Returns a copy of this vector with absolute values in each component.
	INLINE STVector<Size, Type> Abs() const;

	// Returns the amount of dimensions this vector has.
	INLINE uint GetVectorSize() const { return Size; }

	// Returns the inputted component of this vector.
	INLINE Type& GetComponent(const uint& Index);

	// Returns the inputted component of this vector.
	INLINE Type GetComponent(const uint& Index) const;

	// Returns the inputted component of this vector.
	INLINE Type& GetComponent(const EAxis& Axis);

	// Returns the inputted component of this vector.
	INLINE Type GetComponent(const EAxis& Axis) const;

	// Returns a normalized copy of this vector.
	INLINE STVector<Size, Type> GetNormal(float Tolerance = MICRO_NUMBER) const;

	// Returns the X component of this vector.
	INLINE Type& X();

	// Returns the X component of this vector.
	INLINE Type X() const;

	// Returns the X component of this vector.
	INLINE Type& GetX();

	// Returns the X component of this vector.
	INLINE Type GetX() const;

	// Returns the Y component of this vector.
	INLINE Type& Y();

	// REturns the Y component of this vector.
	INLINE Type Y() const;

	// Returns the Y component of this vector.
	INLINE Type& GetY();

	// Returns the Y component of this vector.
	INLINE Type GetY() const;

	// Returns the Z component of this vector.
	INLINE Type& Z();

	// Returns the Z component of this vector.
	INLINE Type Z() const;

	// Returns the Z component of this vector.
	INLINE Type& GetZ();

	// Returns the Z component of this vector.
	INLINE Type GetZ() const;

	// Returns the W Component of this vector.
	INLINE Type& W();

	// Returns the W component of this vector.
	INLINE Type W() const;

	// Returns the W component of this vector.
	INLINE Type& GetW();

	// Returns the W component of this vector.
	INLINE Type GetW() const;



	/// Statics

	// Returns the dot product between two vectors.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - The result of the dot product between the two vectors.
	static INLINE float DotProduct(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2);

	// Calculates the cross product between two vectors.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - The result of the cross product between the two vectors.
	static INLINE STVector<Size, Type> CrossProduct(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2);

	// Gets the value between two vectors based on a percentage value.
	// @param Min - The minimum value of the lerp.
	// @param Max - The maximum value of the lerp.
	// @param Value - The percentage the lerp should calculate at (between 0 - 1).
	// @return - The vector at the inputted percentage position between the two inputted vectors.
	static INLINE STVector<Size, Type> Lerp(const STVector<Size, Type>& Min, const STVector<Size, Type>& Max, float Value);

	// Powers every component of this vector.
	// @param Vector - The vector to power.
	// @param Exponent - The amount of times the component will be multiplied.
	// @return - A copy of this vector after being powered.
	static INLINE STVector<Size, Type> Power(const STVector<Size, Type>& Vector, uint Exponent);

	// Shorthand of typing Vector{1, 0, 0}.
	// @note - Vector size must have the X component.
	static INLINE STVector<Size, Type> Right();

	// Shorthand of typing Vector{-1, 0, 0}.
	// @note - Vector size must have the X component.
	static INLINE STVector<Size, Type> Left();

	// Shorthand of typing Vector{0, 1, 0}.
	// @note - Vector size must have the Y component.
	static INLINE STVector<Size, Type> Up();

	// Shorthand of typing Vector{0, -1, 0}.
	// @note - Vector size must have the Y component.
	static INLINE STVector<Size, Type> Down();

	// Shorthand of typing Vector{0, 0, 1}.
	// @note - Vector size must have the Z component.
	static INLINE STVector<Size, Type> Forward();

	// Shorthand of typing Vector{0, 0, -1}.
	// @note - Vector size must have the Z component.
	static INLINE STVector<Size, Type> Backward();

	// Returns true if this vector is almost equal to another vector.
	// @param V1 - The initial vector.
	// @param V2 - The vector to compare with.
	// @param Threshold - The range in which the other vector can be in.
	// @return - Returns true if the other vector is within range of this vector.
	static INLINE bool NearlyEqual(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2, const Type& Threshold);

	// Creates a vector with the highest values in each dimension between this vector and an inputted vector.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - The resulting vector.
	static INLINE STVector<Size, Type> Max(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2);

	// Returns the highest component in this vector.
	// @param Vector - The vector to search.
	// @return - The highest component in the inputted vector.
	static INLINE Type MaxComp(const STVector<Size, Type>& Vector);

	// Returns the absolute component with the highest value in this vector.
	// @param Vector - The vector to search.
	// @return - The highest component in the inputted vector.
	static INLINE Type AbsMaxComp(const STVector<Size, Type>& Vector);

	// Creates a vector with the lowest values in each dimension between this vector and an inputted vector.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - The resulting vector.
	static INLINE STVector<Size, Type> Min(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2);

	// Returns the lowest component in this vector.
	// @param Vector - The vector to search.
	// @return - The lowest component in the inputted vector.
	static INLINE Type MinComp(const STVector<Size, Type>& Vector);

	// Returns the absolute component with the lowest value in this vector.
	// @param Vector - The vector to search.
	// @return - The lowest component in the inputted vector.
	static INLINE Type AbsMinComp(const STVector<Size, Type>& Vector);

	// Calculates the distance between two vectors.
	// @param Start - The vector representing the starting position.
	// @param End - The vector representing the end position.
	// @return - The distance between the two vectors.
	static INLINE float Distance(const STVector<Size, Type>& Start, const STVector<Size, Type>& End);

	// Calculates the squared distance between two vectors.
	// @note - This is faster than Vector::Distance().
	// @param Start - The vector representing the starting position.
	// @param End - The vector representing the end position.
	// @return - The distance between the two vectors.
	static INLINE float DistanceSquared(const STVector<Size, Type>& Start, const STVector<Size, Type>& End);

	// Creates a new vector by selecting values in the two inputted vectors using a bool value.
	// @note - true = the value V1, false = the value in V2.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @param Control - A vector of bools which determines which vector component to use in each axis.
	// @return - Returns a new vector with the selected values.
	static INLINE STVector<Size, Type> Select(STVector<Size, Type> V1, STVector<Size, Type> V2, STVector<Size, bool> Control);

	// Merges two vectors together based on the inputted axis.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @param A - The axis to initiate the new vector's X and Z components (from the first vector).
	// @param B - The axis to initiate the new vector's Y and W components (from the second vector).
	// @return - A new vector4 with the merged values.
	static INLINE STVector<4, Type> Merge(STVector<4, Type> V1, STVector<4, Type> V2, EAxis A, EAxis B);
};



// A floating point vector with 2 dimensions.
typedef STVector<2, float> SVector2;

// A floating point vector with 3 dimensions.
typedef STVector<3, float> SVector3;

// A floating point vector with 3 dimensions.
typedef STVector<3, float> SVector;

// A floating point vector with 4 dimensions.
typedef STVector<4, float> SVector4;

// A double type vector with 2 dimensions.
typedef STVector<2, double> SVector2d;

// A double type vector with 3 dimensions.
typedef STVector<3, double> SVector3d;

// A double type vector with 3 dimensions.
typedef STVector<3, double> SVectord;

// A double type vector with 4 dimensions.
typedef STVector<4, double> SVector4d;

// An integer vector with 2 dimensions.
typedef STVector<2, int> SVector2i;

// An integer vector with 3 dimensions.
typedef STVector<3, int> SVector3i;

// An integer vector with 3 dimensions.
typedef STVector<3, int> SVectori;

// An integer vector with 4 dimensions.
typedef STVector<4, int> SVector4i;

// A bool vector with 2 dimensions, used for STVector::Select().
typedef STVector<2, bool> SVector2Control;

// A bool vector with 3 dimensions, used for STVector::Select().
typedef STVector<3, bool> SVector3Control;

// A bool vector with 3 dimensions, used for STVector::Select().
typedef STVector<3, bool> SVectorControl;

// A bool vector with 4 dimensions, used for STVector::Select().
typedef STVector<4, bool> SVector4Control;



template <uint Size, typename Type>
STVector<Size, Type>::STVector()
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] = (Type)0.0f;
	}
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(Type Value)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] = Value;
	}
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(Type InX, Type InY)
{
	ASSERT(Size == 2, "Error: Illigal use of constructor. Is the vector the correct size?");
	Data[0] = InX;
	Data[1] = InY;
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(Type InX, Type InY, Type InZ)
{
	ASSERT(Size == 3, "Error: Illigal use of constructor. Is the vector the correct size?");
	Data[0] = InX;
	Data[1] = InY;
	Data[2] = InZ;
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(STVector<2, Type> V, Type InZ)
{
	ASSERT(Size == 3, "Error: Illigal use of constructor. Is the vector the correct size?");
	Data[0] = V[0];
	Data[1] = V[1];
	Data[2] = InZ;
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(Type InX, Type InY, Type InZ, Type InW)
{
	ASSERT(Size == 4, "Error: Illigal use of constructor. Is the vector the correct size?");
	Data[0] = InX;
	Data[1] = InY;
	Data[2] = InZ;
	Data[3] = InW;
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(STVector<2, Type> V1, STVector<2, Type> V2)
{
	ASSERT(Size == 4, "Error: Illigal use of constructor. Is the vector the correct size?");
	Data[0] = V1[0];
	Data[1] = V1[1];
	Data[2] = V2[0];
	Data[3] = V2[1];
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(STVector<2, Type> V, Type InZ, Type InW)
{
	ASSERT(Size == 4, "Error: Illigal use of constructor. Is the vector the correct size?");
	Data[0] = V[0];
	Data[1] = V[1];
	Data[2] = InZ;
	Data[3] = InW;
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(STVector<3, Type> V, Type InW)
{
	ASSERT(Size == 4, "Error: Illigal use of constructor. Is the vector the correct size?");
	Data[0] = V[0];
	Data[1] = V[1];
	Data[2] = V[2];
	Data[3] = InW;
}


template <uint Size, typename Type>
STVector<Size, Type>::STVector(Type Values[Size])
	:Data{ Values }
{}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
STVector<Size, Type>::STVector(STVector<Size2, Type2> Other, Type Flood)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] = Type((i < Size2) ? Other[i] : Flood);
	}
}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
INLINE STVector<Size, Type> STVector<Size, Type>::operator+(const STVector<Size2, Type2>& Other) const
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	STVector<Size, Type> Result;
	for (uint i = 0; i < Count; ++i)
	{
		Result[i] = Data[i] + (Type)Other[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator+(const Type& Value) const
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = Data[i] + Value;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
INLINE STVector<Size, Type> STVector<Size, Type>::operator+=(const STVector<Size2, Type2>& Other)
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	for (uint i = 0; i < Count; ++i)
	{
		Data[i] += (Type)Other[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator+=(const Type& Value)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] += Value;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
INLINE STVector<Size, Type> STVector<Size, Type>::operator-(const STVector<Size2, Type2>& Other) const
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	STVector<Size, Type> Result;
	for (uint i = 0; i < Count; ++i)
	{
		Result[i] = Data[i] - (Type)Other[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator-(const Type& Value) const
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = Data[i] - Value;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator-() const
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = -Data[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
INLINE STVector<Size, Type> STVector<Size, Type>::operator-=(const STVector<Size2, Type2>& Other)
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	for (uint i = 0; i < Count; ++i)
	{
		Data[i] -= (Type)Other[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator-=(const Type& Value)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] -= Value;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
INLINE STVector<Size, Type> STVector<Size, Type>::operator*(const STVector<Size2, Type2>& Other) const
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	STVector<Size, Type> Result;
	for (uint i = 0; i < Count; ++i)
	{
		Result[i] = Data[i] * (Type)Other[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator*(const Type& Value) const
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = Data[i] * Value;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
INLINE STVector<Size, Type> STVector<Size, Type>::operator*=(const STVector<Size2, Type2>& Other)
{
	uint Count{ (Size < Size2) ? Size : Size };
	for (uint i = 0; i < Count; ++i)
	{
		Data[i] *= (Type)Other[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator*=(const Type& Value)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] *= Value;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
INLINE STVector<Size, Type> STVector<Size, Type>::operator/(const STVector<Size2, Type2>& Other) const
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	STVector<Size, Type> Result;
	for (uint i = 0; i < Count; ++i)
	{
		Result[i] = Data[i] / (Type)Other[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator/(const Type& Value) const
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = Data[i] / Value;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
template <uint Size2, typename Type2>
INLINE STVector<Size, Type> STVector<Size, Type>::operator/=(const STVector<Size2, Type2>& Other)
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	for (uint i = 0; i < Count; ++i)
	{
		Data[i] /= (Type)Other[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator/=(const Type& Value)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] /= Value;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator++()
{
	for (uint i = 0; i < Size; ++i)
	{
		++Data[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator--()
{
	for (uint i = 0; i < Size; ++i)
	{
		--Data[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator=(const Type& Value)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] = Value;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::operator|(const STVector<Size, Type>& Other) const
{
	STVector<Size, Type> Result{ 0.0f };
	Result[0] = (Data[1] * Other[2]) - (Data[2] * Other[1]);
	Result[1] = (Data[2] * Other[0]) - (Data[0] * Other[2]);
	Result[2] = (Data[0] * Other[1]) - (Data[1] * Other[0]);
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::operator^(const STVector<Size, Type>& Other) const
{
	Type Result{ 0.0f };
	for (uint i = 0; i < Size; ++i)
	{
		Result += Data[i] * Other[i];
	}
	if (!TMath::IsFinite(Result)) Result = 0.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator>(const STVector<Size, Type>& Other) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] <= Other[i]) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator>(const Type& Value) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] <= Value) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator>=(const STVector<Size, Type>& Other) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] < Other[i]) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator>=(const Type& Value) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] < Value) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator<(const STVector<Size, Type>& Other) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] >= Other[i]) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator<(const Type& Value) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] >= Value) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator<=(const STVector<Size, Type>& Other) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] > Other[i]) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator<=(const Type& Value) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] > Value) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator==(const STVector<Size, Type>& Other) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] != Other[i]) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator==(const Type& Value) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] != Value) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator!=(const STVector<Size, Type>& Other) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] == Other[i]) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::operator!=(const Type& Value) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] == Value) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::operator[](const uint& Index)
{
	return Data[Index];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::operator[](const uint& Index) const
{
	return Data[Index];
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::operator[](const EAxis& Axis)
{
	return Data[Axis];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::operator[](const EAxis& Axis) const
{
	return Data[Axis];
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::CheckNaN()
{
	if (ContainsNaN())
	{
		printf("Vector contains NaN\n");
		*this = (Type)0.0f;
	}
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::ContainsNaN() const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (!TMath::IsFinite((float)Data[i])) return true;
	}
	return false;
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::Print() const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (i + 1 == Size) printf("%f\n", Data[i]);
		else printf("%f, ", Data[i]);
	}
}


#ifdef INCLUDE_DIRECTX_MATH
template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::FromXMVector(DirectX::XMVECTOR Vector)
{
	STVector<Size, Element> Result;
	switch (Size)
	{
	default:
	case 4:
		Result[3] = (Type)DirectX::XMVectorGetW(Vector);

	case 3:
		Result[2] = (Type)DirectX::XMVectorGetZ(Vector);

	case 2:
		Result[1] = (Type)DirectX::XMVectorGetY(Vector);

	case 1:
		Result[0] = (Type)DirectX::XMVectorGetX(Vector);
	}
	return Result;
}


template <uint Size, typename Type>
INLINE DirectX::XMVECTOR STVector<Size, Type>::ToXMVector() const
{
	switch (Size)
	{
	case 0:
		return DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	case 1:
		return DirectX::XMVectorSet((float)Data[0], 0.0f, 0.0f, 0.0f);

	case 2:
		return DirectX::XMVectorSet((float)Data[0], (float)Data[1], 0.0f, 0.0f);

	case 3:
		return DirectX::XMVectorSet((float)Data[0], (float)Data[1], (float)Data[2], 0.0f);

	case 4:
	default:
		return DirectX::XMVectorSet((float)Data[0], (float)Data[1], (float)Data[2], (float)Data[3]);
	}
}
#endif // INCLUDE_DIRECTX_MATH


#ifdef INCLUDE_SDL
template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::FromSDL_Rect(SDL_Rect Rect)
{
	STVector<Size, Type> Result;
	switch (Size)
	{
	default:
	case 4:
		Result[3] = (Type)Rect.h;

	case 3:
		Result[2] = (Type)Rect.w;

	case 2:
		Result[1] = (Type)Rect.y;

	case 1:
		Result[0] = (Type)Rect.x;
	}
	return Result;
}


template <uint Size, typename Type>
static INLINE STVector<Size, Type> STVector<Size, Type>::FromSDL_FRect(SDL_FRect Rect)
{
	STVector<Size, Type> Result;
	switch (Size)
	{
	default:
	case 4:
		Result[3] = (Type)Rect.h;

	case 3:
		Result[2] = (Type)Rect.w;

	case 2:
		Result[1] = (Type)Rect.y;

	case 1:
		Result[0] = (Type)Rect.x;
	}
	return Result;
}


template <uint Size, typename Type>
static INLINE STVector<Size, Type> STVector<Size, Type>::FromSDL_Point(SDL_Point Point)
{
	STVector<Size, Type> Result;
	switch (Size)
	{
	default:
	case 2:
		Result[1] = (Type)Point.y;

	case 1:
		Result[0] = (Type)Point.x;
	}
	return Result;
}


template <uint Size, typename Type>
static INLINE STVector<Size, Type> STVector<Size, Type>::FromSDL_FPoint(SDL_FPoint Point)
{
	STVector<Size, Type> Result;
	switch (Size)
	{
	default:
	case 2:
		Result[1] = (Type)Point.y;

	case 1:
		Result[0] = (Type)Point.x;
	}
	return Result;
}


template <uint Size, typename Type>
INLINE SDL_Rect STVector<Size, Type>::ToRect() const
{
	switch (Size)
	{
	case 0:
		return SDL_Rect{ 0, 0, 0, 0 };

	case 1:
		return SDL_Rect{ (int32)Data[0], 0, 0, 0 };

	case 2:
		return SDL_Rect{ (int32)Data[0], (int32)Data[1], 0, 0 };

	case 3:
		return SDL_Rect{ (int32)Data[0], (int32)Data[1], (int32)Data[2], 0 };

	case 4:
	default:
		return SDL_Rect{ (int32)Data[0], (int32)Data[1], (int32)Data[2], (int32)Data[3] };
	}
}


template <uint Size, typename Type>
INLINE SDL_FRect STVector<Size, Type>::ToFRect() const
{
	switch (Size)
	{
	case 0:
		return SDL_FRect{ 0, 0, 0, 0 };

	case 1:
		return SDL_FRect{ (float)Data[0], 0, 0, 0 };

	case 2:
		return SDL_FRect{ (float)Data[0], (float)Data[1], 0, 0 };

	case 3:
		return SDL_FRect{ (float)Data[0], (float)Data[1], (float)Data[2], 0 };

	case 4:
	default:
		return SDL_FRect{ (float)Data[0], (float)Data[1], (float)Data[2], (float)Data[3] };
	}
}


template <uint Size, typename Type>
INLINE SDL_Point STVector<Size, Type>::ToPoint() const
{
	switch (Size)
	{
	case 0:
		return SDL_Point{ 0, 0 };

	case 1:
		return SDL_Point{ (int32)Data[0], 0 };

	case 2:
	default:
		return SDL_Point{ (int32)Data[0], (int32)Data[1] };
	}
}


template <uint Size, typename Type>
INLINE SDL_FPoint STVector<Size, Type>::ToFPoint() const
{
	switch (Size)
	{
	case 0:
		return SDL_FPoint{ 0.0f, 0.0f };

	case 1:
		return SDL_FPoint{ (float)Data[0], 0.0f };

	case 2:
	default:
		return SDL_FPoint{ (float)Data[0], (float)Data[1] };
	}
}
#endif // INCLUDE_SDL


template <uint Size, typename Type>
INLINE STVector<3, float> STVector<Size, Type>::Rotation() const
{
	ASSERT(Size >= 3, "Vector must have 3 or more dimenions to do this conversion.");

	STVector<3, float> Result;
	Result[EAxis::Y] = TO_DEGREES(TMath::ATan2(Data[EAxis::Y], Data[EAxis::X]));
	Result[EAxis::X] = TO_DEGREES(TMath::ATan2(Data[EAxis::Z], TMath::Sqrt((Data[EAxis::X] * Data[EAxis::X]) + (Data[EAxis::Y] * Data[EAxis::Y]))));
	Result[EAxis::Z] = 0.0f;
	return Result;
}


template <uint Size, typename Type>
template <typename NewType>
INLINE STVector<Size, NewType> STVector<Size, Type>::ToType()
{
	STVector<Size, NewType> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = (NewType)Data[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
template <typename NewType>
INLINE STVector<Size, NewType> STVector< Size, Type>::ToType() const
{
	STVector<Size, NewType> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = (NewType)Data[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, float> STVector<Size, Type>::ToFloat()
{
	return ToType<float>();
}


template <uint Size, typename Type>
INLINE STVector<Size, float> STVector<Size, Type>::ToFloat() const
{
	return ToType<float>();
}


template <uint Size, typename Type>
INLINE STVector<Size, double> STVector<Size, Type>::ToDouble()
{
	return ToType<double>();
}


template <uint Size, typename Type>
INLINE STVector<Size, double> STVector<Size, Type>::ToDouble() const
{
	return ToType<double>();
}


template <uint Size, typename Type>
INLINE STVector<Size, int32> STVector<Size, Type>::ToInt()
{
	return ToType<int32>();
}


template <uint Size, typename Type>
INLINE STVector<Size, int32> STVector<Size, Type>::ToInt() const
{
	return ToType<int32>();
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::CrossProduct(const STVector<Size, Type>& Other) const
{
	return *this | Other;
}


template <uint Size, typename Type>
INLINE float STVector<Size, Type>::DotProduct(const STVector<Size, Type>& Other) const
{
	return *this ^ Other;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Max(const STVector<Size, Type>& Other) const
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = (Data[i] > Other[i]) ? Data[i] : Other[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Min(const STVector<Size, Type>& Other) const
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = (Data[i] < Other[i]) ? Data[i] : Other[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::Normalize(float Tolerance)
{
	const float SquareSum{ DotProduct(*this) };
	if (SquareSum > Tolerance)
	{
		const float Scale{ TMath::InvSqrt(SquareSum) };
		for (uint i = 0; i < Size; ++i)
		{
			Data[i] *= Scale;
		}
	}
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::NearlyEqual(const STVector<Size, Type>& Other, const Type& Threshold) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if ((Data[i] < Other[i] - Threshold) || (Data[i] > Other[i] + Threshold)) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::IsZero(float Threshold) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (TMath::Abs(Data[i]) > Threshold) return false;
	}
	return true;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Power(uint Exponent) const
{
	STVector<Size, Type> Result{ Data };
	for (uint i = 0; i < Exponent; ++i)
	{
		Result *= Data;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Square() const
{
	return *this * *this;
}


template <uint Size, typename Type>
INLINE float STVector<Size, Type>::GetSize() const
{
	float Result{ 0.0f };
	for (uint i = 0; i < Size; ++i)
	{
		Result += Data[i];
	}
	if (!TMath::IsFinite(Result)) Result = 0.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE float STVector<Size, Type>::SizeSquared() const
{
	float Result{ 0.0f };
	for (uint i = 0; i < Size; ++i)
	{
		Result += Data[i] * Data[i];
	}
	if (!TMath::IsFinite(Result)) Result = 0.0f;
	return Result;
}


template <uint Size, typename Type>
template <uint NewSize>
INLINE STVector<NewSize, Type> STVector<Size, Type>::Resize(const Type& Value) const
{
	STVector<NewSize, Type> Result;
	for (uint i = 0; i < NewSize; ++i)
	{
		Result[i] = (i < Size) ? Data[i] : Value;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
inline STVector<3, float> STVector<Size, Type>::RotateAxis(const float AngleDegrees, const STVector<3, float>& Axis) const
{
	ASSERT(Size == 3, "Vector size must be 3 in order to use this function.");

	float S;
	float C;
	TMath::SinCos(&S, &C, TMath::ToRadians(AngleDegrees));

	const float XX{ Axis[EAxis::X] * Axis[EAxis::X] };
	const float YY{ Axis[EAxis::Y] * Axis[EAxis::Y] };
	const float ZZ{ Axis[EAxis::Z] * Axis[EAxis::Z] };

	const float XY{ Axis[EAxis::X] * Axis[EAxis::Y] };
	const float YZ{ Axis[EAxis::Y] * Axis[EAxis::Z] };
	const float ZX{ Axis[EAxis::Z] * Axis[EAxis::X] };

	const float XS{ Axis[EAxis::X] * S };
	const float YS{ Axis[EAxis::X] * S };
	const float ZS{ Axis[EAxis::X] * S };

	const float OMC{ 1.0f - C };

	return STVector<3, float>
	{
		(OMC* XX + C)  * Data[EAxis::X] + (OMC * XY - ZS) * Data[EAxis::Y] + (OMC * ZX + YS) * Data[EAxis::Z],
		(OMC* XY + ZS) * Data[EAxis::X] + (OMC * YY + C)  * Data[EAxis::Y] + (OMC * YZ - XS) * Data[EAxis::Z],
		(OMC* ZX - YS) * Data[EAxis::X] + (OMC * YZ + XS) * Data[EAxis::Y] + (OMC * ZZ + C)  * Data[EAxis::Z]
	};
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::SafeNormal(float Tolerance) const
{
	const float SquareSum{ SizeSquared() };
	if (SquareSum == 1.0f)
	{
		return *this;
	}
	else if (SquareSum < Tolerance)
	{
		return 0.0f;
	}

	const float Scale{ TMath::InvSqrt(SquareSum) };
	return *this * Scale;
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::Set(const Type& X, const Type& Y)
{
	Data[0] = X;
	Data[1] = Y;
	CheckNaN();
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::Set(const Type& X, const Type& Y, const Type& Z)
{
	Data[0] = X;
	Data[1] = Y;
	Data[3] = Z;
	CheckNaN();
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::Set(const Type& X, const Type& Y, const Type& Z, const Type& W)
{
	Data[0] = X;
	Data[1] = Y;
	Data[2] = Z;
	Data[3] = W;
	CheckNaN();
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::SetX(const Type& Value)
{
	Data[EAxis::X] = Value;
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::SetY(const Type& Value)
{
	Data[EAxis::Y] = Value;
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::SetZ(const Type& Value)
{
	Data[EAxis::Z] = Value;
}


template <uint Size, typename Type>
INLINE void STVector<Size, Type>::SetW(const Type& Value)
{
	Data[EAxis::W] = Value;
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::MaxComp() const
{
	Type Result{ Data[0] };
	for (uint i = 1; i < Size; ++i)
	{
		if (Data[i] > Result) Result = Data[i];
	}
	if (!TMath::IsFinite(Result)) Result = 0.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::AbsMaxComp() const
{
	return Abs().MaxComp();
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::MinComp() const
{
	Type Result{ Data[0] };
	for (uint i = 1; i < Size; ++i)
	{
		if (Data[i] < Result) Result = Data[i];
	}
	if (!TMath::IsFinite(Result)) Result = 0.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::AbsMinComp() const
{
	return Abs().MinComp();
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Abs() const
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = TMath::Abs(Data[i]);
	}
	return Result;
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::GetComponent(const uint& Index)
{
	return Data[Index];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::GetComponent(const uint& Index) const
{
	return Data[Index];
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::GetComponent(const EAxis& Axis)
{
	return Data[Axis];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::GetComponent(const EAxis& Axis) const
{
	return Data[Axis];
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::GetNormal(float Tolerance) const
{
	const float SquareSum{ SizeSquared() };
	if (SquareSum > Tolerance)
	{
		const float Scale{ TMath::InvSqrt(SquareSum) };
		STVector<Size, Type> Result{ *this * Scale };
		return Result;
	}
	return 0.0f;
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::X()
{
	return Data[EAxis::X];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::X() const
{
	return Data[EAxis::X];
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::GetX()
{
	return Data[EAxis::X];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::GetX() const
{
	return Data[EAxis::X];
}

template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::Y()
{
	return Data[EAxis::Y];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::Y() const
{
	return Data[EAxis::Y];
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::GetY()
{
	return Data[EAxis::Y];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::GetY() const
{
	return Data[EAxis::Y];
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::Z()
{
	return Data[EAxis::Z];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::Z() const
{
	return Data[EAxis::Z];
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::GetZ()
{
	return Data[EAxis::Z];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::GetZ() const
{
	return Data[EAxis::Z];
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::W()
{
	return Data[EAxis::W];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::W() const
{
	return Data[EAxis::W];
}


template <uint Size, typename Type>
INLINE Type& STVector<Size, Type>::GetW()
{
	return Data[EAxis::W];
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::GetW() const
{
	return Data[EAxis::W];
}


template <uint Size, typename Type>
INLINE float STVector<Size, Type>::DotProduct(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2)
{
	return V1 ^ V2;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::CrossProduct(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2)
{
	return V1 | V2;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Lerp(const STVector<Size, Type>& Min, const STVector<Size, Type>& Max, float Value)
{
	return ((Max - Min) * Value) + Min;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Power(const STVector<Size, Type>& Vector, uint Exponent)
{
	return Vector.Power(Exponent);
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Right()
{
	STVector<Size, Type> Result{ (Type)0.0f };
	Result[EAxis::X] = (Type)1.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Left()
{
	STVector<Size, Type> Result{ (Type)0.0f };
	Result[EAxis::X] = (Type)-1.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Up()
{
	STVector<Size, Type> Result{ (Type)0.0f };
	Result[EAxis::Y] = (Type)1.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Down()
{
	STVector<Size, Type> Result{ (Type)0.0f };
	Result[EAxis::Y] = (Type)-1.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Forward()
{
	STVector<Size, Type> Result{ (Type)0.0f };
	Result[EAxis::Z] = (Type)1.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Backward()
{
	STVector<Size, Type> Result{ (Type)0.0f };
	Result[EAxis::Z] = (Type)-1.0f;
	return Result;
}


template <uint Size, typename Type>
INLINE bool STVector<Size, Type>::NearlyEqual(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2, const Type& Threshold)
{
	return V1.NearlyEqual(V2, Threshold);
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Max(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2)
{
	return V1.Max(V2);
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::MaxComp(const STVector<Size, Type>& Vector)
{
	return Vector.MaxComp();
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::AbsMaxComp(const STVector<Size, Type>& Vector)
{
	return Vector.AbsMaxComp();
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Min(const STVector<Size, Type>& V1, const STVector<Size, Type>& V2)
{
	return V1.Min(V2);
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::MinComp(const STVector<Size, Type>& Vector)
{
	return Vector.MinComp();
}


template <uint Size, typename Type>
INLINE Type STVector<Size, Type>::AbsMinComp(const STVector<Size, Type>& Vector)
{
	return Vector.AbsMinComp();
}


template <uint Size, typename Type>
INLINE float STVector<Size, Type>::Distance(const STVector<Size, Type>& Start, const STVector<Size, Type>& End)
{
	STVector<Size, Type> Delta{ Start - End };
	return TMath::Sqrt(Delta ^ Delta);
}


template <uint Size, typename Type>
INLINE float STVector<Size, Type>::DistanceSquared(const STVector<Size, Type>& Start, const STVector<Size, Type>& End)
{
	STVector<Size, Type> Delta{ Start - End };
	return Delta ^ Delta;
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> STVector<Size, Type>::Select(STVector<Size, Type> V1, STVector<Size, Type> V2, STVector<Size, bool> Control)
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = ((Control[i]) ? V1[i] : V2[i]);
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Type>
INLINE STVector<4, Type> STVector<Size, Type>::Merge(STVector<4, Type> V1, STVector<4, Type> V2, EAxis A, EAxis B)
{
	STVector<4, Type> Result{ V1[A], V2[B], V1[A], V2[B] };
	Result.CheckNaN();
	return Result;
}