#include "Rotator.h"


SRotator::SRotator(const SQuaternion& Quat)
{
	*this = Quat.ToEuler();
}


SRotator SRotator::GetInverse() const
{
	return Quaternion().Inverse().ToEuler();
}


SVector SRotator::Vector() const
{
	float CP, SP, CY, SY;
	TMath::SinCos(&SP, &CP, TO_RADIAN(Pitch));
	TMath::SinCos(&SY, &CY, TO_RADIAN(Yaw));
	return SVector{ CP * CY, CP * SY, SP };
}


SQuaternion SRotator::Quaternion() const
{
	const float DEG_TO_RAD = TMath::PI / (180.f);
	const float DIVIDE_BY_2 = DEG_TO_RAD / 2.f;
	float SP, SY, SR;
	float CP, CY, CR;

	TMath::SinCos(&SP, &CP, Pitch * DIVIDE_BY_2);
	TMath::SinCos(&SY, &CY, Yaw * DIVIDE_BY_2);
	TMath::SinCos(&SR, &CR, Roll * DIVIDE_BY_2);

	SQuaternion RotationQuat;
	RotationQuat.X = CR * SP * SY - SR * CP * CY;
	RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
	RotationQuat.Z = CR * CP * SY - SR * SP * CY;
	RotationQuat.W = CR * CP * CY + SR * SP * SY;
	return RotationQuat;
}


SVector SRotator::Euler() const
{
	return SVector{ Pitch, Yaw, Roll };
}


SRotator SRotator::MakeFromEuler(const SVector& Euler)
{
	return SRotator{ Euler[X], Euler[Y], Euler[Z] };
}


SVector SRotator::RotateVector(const SVector& V) const
{
	return 0.0f;
}


SVector SRotator::UnrotateVector(const SVector& V) const
{
	return 0.0f;
}


void SRotator::GetWindingAndRemainder(SRotator& Winding, SRotator& Remainder) const
{
	Remainder.Pitch = NormalizeAxis(Pitch);
	Winding.Pitch = Pitch - Remainder.Pitch;

	Remainder.Yaw = NormalizeAxis(Yaw);
	Winding.Yaw = Yaw - Remainder.Yaw;

	Remainder.Roll = NormalizeAxis(Roll);
	Winding.Roll = Roll - Remainder.Roll;
}