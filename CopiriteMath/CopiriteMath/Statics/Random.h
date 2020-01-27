#include "../DataTypes/Vector.h"
#include "../Statics/MathStatics.h"

#include <random>
#include <time.h>


// A static class used to generate random values for various things.
// All functions and components in this are static so to access them
// use "TRandom::".
class TRandom
{
public:
	/// Properties

	// The seed currently used to generate the random numbers.
	static int32 Seed;



public:
	/// Functions

	// Initiates the random seed based off the current time.
	// @return - The new seed generated.
	static INLINE int32 InitRand();

	// Initiates the random seed with an inputted value.
	// @param Seed - The seed value to initiate the random with.
	// @return - The new seed generated.
	static INLINE int32 InitRand(int32 Seed);

	// Generates a new seed.
	static INLINE void GenerateSeed();

	// A helper function to help getting a random integer.
	// Since there are some platforms where RAND_MAX is a large number,
	// we don't want to include the upper bound results.
	static INLINE int32 RandomHelper(int32 Value);

	// Generates a random integer between 0 and RAND_MAX.
	static INLINE int32 Random();

	// Generates a seeded random float in the range (0, 1).
	// @return - The new seed generated.
	static float SeededRandom();

	// Returns a randomized value between an inputted range.
	// @param Min - The minimum value the random can be.
	// @param Max - The maximum value the random can be.
	// @return - The randomized value.
	static INLINE int32 Range(int32 Min, int32 Max);

	// Returns a randomized value between an inputted range.
	// @param Min - The minimum value the random can be.
	// @param Max - The maximum value the random can be.
	// @return - The randomized value.
	static INLINE float Range(float Min, float Max);

	// Returns a randomized value between an inputted range.
	// @param Min - The minimum value the random can be.
	// @param Max - The maximum value the random can be.
	// @return - The randomized value.
	static INLINE double Range(double Min, double Max);

	// Returns a randomized vector between an inputted range.
	// @template Size - The size of the vector.
	// @template Type - The datatype of the vector components.
	// @param Min - The minimum value the random can be.
	// @param Max - The maximum value the random can be.
	// @return - The randomized vector.
	template <uint Size, typename Type>
	static INLINE STVector<Size, Type> Range(STVector<Size, Type> Min, STVector<Size, Type> Max);

	// Returns a random float between 0 and 1.
	static INLINE float RandomFloat();

	// Returns a random double between 0 and 1.
	static INLINE double RandomDouble();

	// Returns a random int between 0 and RAND_MAX.
	static INLINE int32 RandomInt();

	// Returns a random bool value (Either true or false).
	static INLINE bool RandomBool();

	// Returns a uniformly distributed random unit length vector.
	// @note - The returned vector is a point on a unit sphere surface.
	// @template Size - The size of the vector.
	// @template Type - The datatype the vector should have.
	// @return - The randomized vector.
	template <uint Size, typename Type>
	static STVector<Size, Type> RandomVector();

	// Calculates a random vector within a cone.
	// @param Direction - The direction the cone is facing.
	// @param ConeHalfAngleRadius - Half of the cone radius.
	// @return - Returns a vector at a random point within a cone.
	static SVector RandomPointInCone(const SVector& Direction, float ConeHalfAngleRadius);

	// Calculates a random vector within a cone.
	// @param Direction - The direction the cone is facing.
	// @param HorizontalConeHalfAngleRadius - Half of the cone radius along the X axis.
	// @param VerticalConeHalfAngleRadius - Half of the cone radidus along the Y axis.
	// @return - Returns a vector at a random point within a cone.
	static SVector RandomPointInCone(const SVector& Direction, float HorizontalConeHalfAngleRadius, float VerticalConeHalfAngleRadius);

	// Calculates a random vector in a sphere.
	// @param Radius - The radius of the sphere.
	// @return - A vector at a random point within a sphere.
	static SVector RandomPointInSphere(float Radius);

	// Calculates a random vector in a 2D circle.
	// @param Radius - The radius of the circle.
	// @return - A vector at a random point within a circle.
	static SVector2 RandomPointInCircle(float Radius);

	// Calculates a random vector in a bounding box.
	// @param MinExtents - The minimum extents of the box.
	// @param MaxExtents - The maximum extents of the box.
	// @return - A vector at a random point within a bounding box.
	static SVector RandomPointInBox(const SVector& MinExtents, const SVector& MaxExtents);

	// Calcualtes a random vector in a bounding box.
	// @note - This creates a box using half of the ExtentSquared.
	// @param ExtentSquared - The Extent of the bounding box (squared).
	// @return - A vector at a random point within a bounding box.
	static SVector RandomPointInBox(const SVector& ExtentSquared);
};


INLINE int32 TRandom::InitRand()
{
	srand(time(NULL));
	return RandomInt();
}


INLINE int32 TRandom::InitRand(int32 Seed)
{
	srand(Seed);
	return RandomInt();
}


INLINE void TRandom::GenerateSeed()
{
	Seed = (Seed * 196314165) + 907633515;
}


INLINE int32 TRandom::RandomHelper(int32 Value)
{
	return (Value > 0) ? TMath::Min(TMath::TruncateInt(RandomFloat() * Value), Value - 1) : 0;
}


INLINE int32 TRandom::Random()
{
	return rand();
}


INLINE int32 TRandom::Range(int32 Min, int32 Max)
{
	const int32 Range{ (Max - Min) + 1 };
	return Min + RandomHelper(Range);
}


INLINE float TRandom::Range(float Min, float Max)
{
	return (Min + (Max - Min) * RandomFloat());
}


INLINE double TRandom::Range(double Min, double Max)
{
	return (Min + (Max - Min) * RandomDouble());
}


template <uint Size, typename Type>
INLINE STVector<Size, Type> TRandom::Range(STVector<Size, Type> Min, STVector<Size, Type> Max)
{
	STVector<Size, Type> Result;
	for (uint i = 0; i < Result.GetSize(); ++i)
	{
		Result[i] = Range(Min[i], Max[i]);
	}
	return Result;
}


INLINE float TRandom::RandomFloat()
{
	return (Random() / (float)RAND_MAX);
}


INLINE double TRandom::RandomDouble()
{
	return (Random() / (double)RAND_MAX);
}


INLINE int32 TRandom::RandomInt()
{
	return Random();
}


INLINE bool TRandom::RandomBool()
{
	return (Range(0, 1) == 1);
}


template <uint Size, typename Type>
STVector<Size, Type> TRandom::RandomVector()
{
	STVector<Size, Type> Result;
	float Length;

	do
	{
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = ((Type)RandomFloat() * 2.0f) - 1.0f;
		}
		Length = Result.SizeSquared();
	} while (Length > 1.0f || Length < SMALL_NUMBER);

	return Result * (1.0f / TMath::Sqrt(Length));
}