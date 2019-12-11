#pragma once
#include "../GlobalValues.h"



// Other libraries (if included)

#ifdef INCLUDE_DIRECTX_MATH
#include <DirectXMath.h>
#endif // INCLUDE_DIRECTX_MATH



// Stores the different types of axis'.
// Used to easily access values in a vector.
enum EAxis
{
	X = 0x1,		// The X axis.
	Y = 0x2,		// The Y axis.
	Z = 0x3,		// The Z axis.
	W = 0x4		// The W axis.
};



// Represents a point in space in a specifid amount of dimensions.
// @template Size - How many dimensions this vector should have.
// @template Type - The datatype this vector should use.
template <uint Size, typename Type>
struct STVector
{
private:
	/// Properties

	// Stores all elements of this vector.
	Type Data[Size];


public:
	/// Constructors

	// Constructor, Default.
	INLINE STVector<Size, Type>();

	// Constructor, Initializes all vector components with the inputted value.
	// @param Value - The value used to initialize all components with.
	INLINE STVector<Size, Type>(Type Value);

	// Constructor, Initiates a vector2 using 2 values.
	// @param InX - The value used to initialize this vector's X component.
	// @param InY - The value used to initialize this vector's Y component.
	INLINE VECTORCALL STVector<Size, Type>(Type InX, Type InY);

	// Constructor, Initiates a vector3 using 3 values.
	// @param InX - The value used to initialize this vector's X component.
	// @param InY - The value used to initialize this vector's Y component.
	// @param InZ - The value used to initialize this vector's Z component.
	INLINE VECTORCALL STVector<Size, Type>(Type InX, Type InY, Type InZ);

	// Constructor, Initiates a vector3 using a 2d vector and a value.
	// @param InV - The vector2 used to initiate this vector's X and Y components.
	// @param InZ - The value used to initialize this Vector's Z component.
	INLINE STVector<Size, Type>(STVector<2, Type> InV, Type InZ);

	// Constructor, Initiates a vector4 using 4 values.
	// @param InX - The value used to initialize this vector's X component.
	// @param InY - The value used to initialize this vector's Y component.
	// @param InZ - The value used to initialize this vector's Z component.
	// @param InW - The value used to initialize this vector's W component.
	INLINE VECTORCALL STVector<Size, Type>(Type InX, Type InY, Type InZ, Type InW);

	// Constructor, Initiates a vector4 using 2 vector2s.
	// @param V1 - The vector2 used to initialize this vector's X and Y components.
	// @param V2 - The vector2 used to initialize this vector's Z and W components.
	INLINE STVector<Size, Type>(STVector<2, Type> V1, STVector<2, Type> V2);

	// Constructor, Initiates a vector4 using a 2D vector and 2 values.
	// @param V - The vector2 used to initialize this vector's X and Y components.
	// @param InZ - The value used to initialize this vector's Z component.
	// @param InW - The value used to initialize this vector's W component.
	INLINE STVector<Size, Type>(STVector<2, Type> V, Type InZ, Type InW);

	// Constructor, Initiates a vector4 using a 3D vector and a value.
	// @param V - The vector3 used to initialize this vector's X, Y and Z components.
	// @param InW - The value used to initialize this vector's W component.
	INLINE VECTORCALL STVector<Size, Type>(STVector<3, Type> V, Type InW);

	// Constructor, Initializes this vector with an array of values.
	// @note - The array size must be the same size as this vector.
	// @param Values - The array to initialize all components.
	INLINE VECTORCALL STVector<Size, Type>(Type Values[Size]);

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
		Vector<Size, Type> Result;
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
	INLINE friend STVector<Size, Type> operator*(const Type& Value, const STVector<Size, Element>& Other)
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
VECTORCALL STVector<Size, Type>::STVector(Type InX, Type InY)
{
	ASSERT(Size == 2, "Error: Illigal use of constructor. Is the vector the correct size?");
	Data[0] = InX;
	Data[1] = InY;
}


template <uint Size, typename Type>
VECTORCALL STVector<Size, Type>::STVector(Type InX, Type InY, Type InZ)
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
VECTORCALL STVector<Size, Type>::STVector(Type InX, Type InY, Type InZ, Type InW)
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
	Data[0] = V1[0];
	Data[1] = V1[1];
	Data[2] = V1[2];
	Data[3] = InW;
}


template <uint Size, typename Type>
VECTORCALL STVector<Size, Type>::STVector(Type Values[Size])
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
		Result[i] = Data[i] - Other[i];
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
		Data[i] -= Other[i];
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
		Result[i] = Data[i] * Other[i];
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