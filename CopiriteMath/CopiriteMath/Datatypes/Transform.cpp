#include "Transform.h"
#include "Matrix.h"


STransform::STransform(const SVector InLocation, const SQuaternion InRotation, const SVector InScale)
	:Location{ InLocation }, Rotation{ InRotation }, Scale{ InScale }
{}


STransform::~STransform()
{
	for (uint i = 0; i < Children.size(); ++i)
	{
		Children[i]->SetParent(Parent);
	}

	RemoveFromParent();
}


STransform STransform::GetWorldTransform() const
{
	SMatrix4 ParentMat;
	ParentMat.Identity();
	if (Parent) ParentMat = Parent->GetWorldTransform();

	SMatrix4 ScaleMat;
	SMatrix4 RotationMat;
	SMatrix4 LocationMat;

	ScaleMat.ToScale(Scale);
	RotationMat.ToRotation(Rotation);
	LocationMat.ToTranslation(Location);

	SMatrix4 Local{ ScaleMat * RotationMat * LocationMat };
	Local = ParentMat * Local;

	//return Local.GetTransform();
	STransform Result{ Local.GetTransform() };
	Result.Rotation = GetWorldRotation();
	return Result;
}


STransform2::STransform2(const SVector2& InLocation, const float& InRotation, const SVector2& InScale)
	:Location{ InLocation }, Rotation{ InRotation }, Scale{ InScale }
{}


STransform2::~STransform2()
{
	for (uint i = 0; i < Children.size(); ++i)
	{
		Children[i]->SetParent(Parent);
	}

	RemoveFromParent();
}


STransform2 STransform2::GetWorldTransform() const
{
	SMatrix3 ParentMat;
	ParentMat.Identity();
	if (Parent) ParentMat = Parent->GetWorldTransform();

	SMatrix3 ScaleMat;
	SMatrix3 RotationMat;
	SMatrix3 LocationMat;

	ScaleMat.ToScale(Scale);
	RotationMat.ToRotation(Rotation);
	LocationMat.ToTranslation(Location);

	SMatrix3 Local{ ScaleMat * RotationMat * LocationMat };
	SMatrix3 World{ ParentMat * Local };

	STransform2 Transform{ World.GetTransform() };
	Transform.Rotation = GetWorldRotation();
	return Transform;
}