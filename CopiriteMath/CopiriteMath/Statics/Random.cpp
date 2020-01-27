#include "Random.h"
#include "DataTypes/Matrix.h"


int32 TRandom::Seed{ InitRand() };


float TRandom::SeededRandom()
{
	GenerateSeed();
	union { float F; int32 I; } Result;
	union { float F; int32 I; } Temp;
	Temp.F = 1.0f;
	Result.I = ((Temp.I & 0xff800000) | (Seed & 0x007fffff));
	return TMath::Fractional(Result.F);
}


SVector TRandom::RandomPointInCone(const SVector& Direction, float ConeHalfAngleRadius)
{
	if (ConeHalfAngleRadius > 0.0f)
	{
		const float RandU{ RandomFloat() };
		const float RandV{ RandomFloat() };

		// Get spherical coords that have an even distribution over the unit sphere
		// Method described at http://mathworld.wolfram.com/SpherePointPicking.html	
		float Theta{ 2.0f * TMath::PI * RandU };
		float Phi{ TMath::ACos((2.0f * RandV) - 1.0f) };

		Phi = TMath::FMod(Phi, ConeHalfAngleRadius);

		const SMatrix4 DirectionMatrix{ SMatrix4::MatrixRotate(Direction.Rotation()) };
		const SVector DirectionZ{ DirectionMatrix.GetScaledAxis(EAxis::X) };
		const SVector DirectionY{ DirectionMatrix.GetScaledAxis(EAxis::Y) };

		SVector Result{ Direction.RotateAxis(TO_DEGREES(Phi), DirectionY) };
		Result = Result.RotateAxis(TO_DEGREES(Theta), DirectionZ);

		return Result.SafeNormal();
	}
	return Direction.SafeNormal();
}


SVector TRandom::RandomPointInCone(const SVector& Direction, float HorizontalConeHalfAngleRadius, float VerticalConeHalfAngleRadius)
{
	if ((VerticalConeHalfAngleRadius > 0.0f) && (HorizontalConeHalfAngleRadius > 0.0f))
	{
		const float RandU{ RandomFloat() };
		const float RandV{ RandomFloat() };

		float Theta{ 2.0f * TMath::PI * RandU };
		float Phi{ TMath::ACos((2.0f * RandV) - 1.0f) };

		float ConeHalfAngleRadius{ TMath::Square(TMath::Cos(Theta) / VerticalConeHalfAngleRadius) + TMath::Square(TMath::Sin(Theta) / HorizontalConeHalfAngleRadius) };
		ConeHalfAngleRadius = TMath::Sqrt(1.0f / ConeHalfAngleRadius);

		Phi = TMath::FMod(Phi, ConeHalfAngleRadius);

		const SMatrix4 DirectionMatrix{ SMatrix4::MatrixRotate(Direction.Rotation()) };
		const SVector DirectionZ{ DirectionMatrix.GetScaledAxis(EAxis::X) };
		const SVector DirectionY{ DirectionMatrix.GetScaledAxis(EAxis::Y) };

		SVector Result{ Direction.RotateAxis(TO_DEGREES(Phi), DirectionY) };
		Result = Result.RotateAxis(TO_DEGREES(Theta), DirectionZ);

		return Result.SafeNormal();
	}
	return Direction.SafeNormal();
}


SVector TRandom::RandomPointInSphere(float Radius)
{
	SVector Result;
	float Length;

	do
	{
		for (uint i = 0; i < Result.GetSize(); ++i)
		{
			Result[i] = RandomFloat() * 2.0f - 1.0f;
		}
		Length = Result.SizeSquared();
	} while (Length > 1.0f);

	return Result * Radius;
}


SVector2 TRandom::RandomPointInCircle(float Radius)
{
	SVector2 Result;
	float Length;

	do
	{
		for (uint i = 0; i < Result.GetSize(); ++i)
		{
			Result[i] = RandomFloat() * 2.0f - 1.0f;
		}
		Length = Result.SizeSquared();
	} while (Length > 1.0f);

	return Result * Radius;
}


SVector TRandom::RandomPointInBox(const SVector& MinExtents, const SVector& MaxExtents)
{
	return Range(MinExtents, MaxExtents);
}


SVector TRandom::RandomPointInBox(const SVector& ExtentSquared)
{
	return Range(-ExtentSquared / 2.0f, ExtentSquared / 2.0f);
}