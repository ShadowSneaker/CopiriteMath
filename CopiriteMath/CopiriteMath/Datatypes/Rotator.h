#pragma once

// This is a temporary class to get a better understanding of Quaternions
// and to hopefully find a way to use them correctly.
// At the moment when I convert values I always recieve a different value when
// converting back. I hope this interface will solve that issue.

// This entire file was referenced from the Unreal Engine 4.
// I do intend on removing this file after testing the functionality of
// the quaternion through this as an interface.

// A few changes from the Unreal Engine 4 has been made, as the axis' are
// different. X is right, Y is up and Z is forward whereas in Unreal,
// X is forward, Y is right, and Z is up.


#include "Quaternion.h"


struct SRotator
{
public:

	float Pitch{ 0.0f };
	float Yaw{ 0.0f };
	float Roll{ 0.0f };

public:


	INLINE SRotator() {}

	explicit INLINE SRotator(float Value);

	INLINE SRotator(float InPitch, float InYaw, float InRoll);

	explicit SRotator(const SQuaternion& Quat);

	INLINE SRotator(SVector Vec);

public:

	INLINE SRotator operator+(const SRotator& Rotation) const;
	INLINE SRotator operator+=(const SRotator& Rotation);
	INLINE SRotator operator-(const SRotator& Rotation) const;
	INLINE SRotator operator-=(const SRotator& Rotation);
	INLINE SRotator operator*(const float& Value) const;
	INLINE SRotator operator*=(const float& Value);
	INLINE bool operator==(const SRotator& Rotation) const;
	INLINE bool operator!=(const SRotator& Rotation) const;


public:
	INLINE bool IsNearlyZero(float Tolerance = SMALL_NUMBER) const;
	INLINE bool IsZero() const;

	INLINE bool Equals(const SRotator& Rotator, float Tolerance = SMALL_NUMBER) const;
	INLINE SRotator Add(float DeltaPitch, float DeltaYaw, float DeltaRoll);
	SRotator GetInverse() const;
	SVector Vector() const;
	SQuaternion Quaternion() const;
	SVector Euler() const;
	SVector RotateVector(const SVector& Vector) const;
	SVector UnrotateVector(const SVector& Vector) const;
	INLINE SRotator Clamp() const;
	SRotator GetNormalized() const;
	SRotator GetDenormalized() const;
	float GetComponentForAxis(EAxis Axis) const;
	void SetComponentForAxis(EAxis Axis, float Component);
	void Normalize();
	void GetWindingAndRemainder(SRotator& Winding, SRotator& Remainder) const;
	float GetManhattanDistance(const SRotator& Rotator) const;
	SRotator GetEquivalentRotator() const;
	void SetCloseToMe(SRotator& MakeClosest) const;
	
	INLINE static float ClampAxis(float Angle);
	INLINE static float NormalizeAxis(float Angle);
	INLINE static uint8 CompressAxisToByte(float Angle);
	INLINE static float DecompressAxisFromByte(uint8 Angle);
	INLINE static uint16 CompressAxisToShort(float Angle);
	INLINE static float DecompressAxisFromShort(uint16 Angle);
	SRotator MakeFromEuler(const SVector& Euler);
};


INLINE SRotator::SRotator(float Value)
	: Pitch{ Value }, Yaw{ Value }, Roll{ Value }
{}


INLINE SRotator::SRotator(float InPitch, float InYaw, float InRoll)
	: Pitch{ InPitch }, Yaw{ InYaw }, Roll{ InRoll }
{}


INLINE SRotator::SRotator(SVector Vec)
	: Pitch{ Vec[X] }, Yaw{ Vec[Y] }, Roll{ Vec[Z] }
{}


INLINE SRotator SRotator::operator+(const SRotator& Rotation) const
{
	return SRotator{ Pitch + Rotation.Pitch, Yaw + Rotation.Yaw, Roll + Rotation.Roll };
}


INLINE SRotator SRotator::operator+=(const SRotator& Rotation)
{
	Pitch += Rotation.Pitch;
	Yaw += Rotation.Yaw;
	Roll += Rotation.Roll;
	return *this;
}


INLINE SRotator SRotator::operator-(const SRotator& R) const
{
	return SRotator{ Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll };
}


INLINE SRotator SRotator::operator-=(const SRotator& R)
{
	Pitch -= R.Pitch;
	Yaw -= R.Yaw;
	Roll -= R.Roll;
	return *this;
}


INLINE SRotator SRotator::operator*(const float& Scale) const
{
	return SRotator{ Pitch * Scale, Yaw * Scale, Roll * Scale };
}


INLINE SRotator SRotator::operator*=(const float& Scale)
{
	Pitch *= Scale;
	Yaw *= Scale;
	Roll *= Scale;
	return *this;
}


INLINE bool SRotator::operator==(const SRotator& R) const
{
	return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll;
}


INLINE bool SRotator::operator!=(const SRotator& R) const
{
	return Pitch != R.Pitch || Yaw != R.Yaw || Roll != R.Roll;
}


INLINE bool SRotator::IsNearlyZero(float Tolerance) const
{
	return TMath::Abs(NormalizeAxis(Pitch)) <= Tolerance
		&& TMath::Abs(NormalizeAxis(Yaw)) <= Tolerance
		&& TMath::Abs(NormalizeAxis(Roll)) <= Tolerance;
}


INLINE bool SRotator::IsZero() const
{
	return ClampAxis(Pitch) == 0.0f
		&& ClampAxis(Yaw) == 0.0f
		&& ClampAxis(Roll) == 0.0f;
}


INLINE bool SRotator::Equals(const SRotator& R, float Tolerance) const
{
	return TMath::Abs(NormalizeAxis(Pitch - R.Pitch)) <= Tolerance
		&& TMath::Abs(NormalizeAxis(Yaw - R.Yaw)) <= Tolerance
		&& TMath::Abs(NormalizeAxis(Roll - R.Roll)) <= Tolerance;
}


INLINE SRotator SRotator::Add(float DeltaPitch, float DeltaYaw, float DeltaRoll)
{
	Yaw += DeltaYaw;
	Pitch += DeltaPitch;
	Roll += DeltaRoll;
	return *this;
}


INLINE SRotator SRotator::Clamp() const
{
	return SRotator(ClampAxis(Pitch), ClampAxis(Yaw), ClampAxis(Roll));
}


INLINE float SRotator::ClampAxis(float Angle)
{
	Angle = TMath::FMod(Angle, 360.0f);
	if (Angle < 0.0f)
	{
		Angle += 360.0f;
	}
	return Angle;
}


INLINE float SRotator::NormalizeAxis(float Angle)
{
	Angle = ClampAxis(Angle);
	if (Angle > 180.0f)
	{
		Angle -= 360.0f;
	}
	return Angle;
}


INLINE uint8 SRotator::CompressAxisToByte(float Angle)
{
	return TMath::RoundInt(Angle * 256.0f / 360.0f) & 0xFF;
}


INLINE float SRotator::DecompressAxisFromByte(uint8 Angle)
{
	return (Angle * 360.0f / 256.0f);
}


INLINE uint16 SRotator::CompressAxisToShort(float Angle)
{
	return TMath::RoundInt(Angle * 65536.0f / 360.0f) & 0xFFFF;
}


INLINE float SRotator::DecompressAxisFromShort(uint16 Angle)
{
	return (Angle * 360.0f / 65536.0f);
}


INLINE SRotator SRotator::GetNormalized() const
{
	SRotator Rot{ *this };
	Rot.Normalize();
	return Rot;
}


INLINE SRotator SRotator::GetDenormalized() const
{
	SRotator Rot{ *this };
	Rot.Pitch = ClampAxis(Rot.Pitch);
	Rot.Yaw = ClampAxis(Rot.Yaw);
	Rot.Roll = ClampAxis(Rot.Roll);
	return Rot;
}


INLINE void SRotator::Normalize()
{
	Pitch = NormalizeAxis(Pitch);
	Yaw = NormalizeAxis(Yaw);
	Roll = NormalizeAxis(Roll);
}


INLINE float SRotator::GetComponentForAxis(EAxis Axis) const
{
	switch (Axis)
	{
	case EAxis::X:
		return Pitch;


	case EAxis::Y:
		return Yaw;


	case EAxis::Z:
		return Roll;


	default:
		return 0.0f;
	}
}


INLINE void SRotator::SetComponentForAxis(EAxis Axis, float Component)
{
	switch (Axis)
	{
	case X:
		Pitch = Component;
		break;


	case Y:
		Yaw = Component;
		break;


	case Z:
		Roll = Component;
		break;
	}
}


INLINE float SRotator::GetManhattanDistance(const SRotator& Rotator) const
{
	return TMath::Abs(Yaw - Rotator.Yaw)
		+ TMath::Abs(Pitch - Rotator.Pitch)
		+ TMath::Abs(Roll - Rotator.Roll);
}


INLINE SRotator SRotator::GetEquivalentRotator() const
{
	return SRotator{ 180.0f - Pitch, Yaw + 180.0f, Roll + 180.0f };
}


INLINE void SRotator::SetCloseToMe(SRotator& MakeClosest) const
{
	SRotator OtherChoice{ MakeClosest.GetEquivalentRotator() };
	float FirstDiff{ GetManhattanDistance(MakeClosest) };
	float SecondDiff{ GetManhattanDistance(OtherChoice) };
	if (SecondDiff < FirstDiff)
		MakeClosest = OtherChoice;
}