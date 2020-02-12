#pragma once
#include "Quaternion.h"

#include <vector>

struct STransform
{
private:

	// A reference to this object's parent.
	STransform* Parent{ nullptr };

	// A refernce to all the children transforms this object has.
	std::vector<STransform*> Children;


public:
	// This transform's position component.
	SVector Location{ 0.0f };

	// This transform's rotation component.
	SQuaternion Rotation{ 0.0f, 0.0f, 0.0, 1.0f };

	// This transform's scale component.
	SVector Scale{ 1.0f };



public:
	/// Constructors

	// Constructor, Default.
	STransform() {};

	// Constructor, Initiates all components of the transform.
	STransform(const SVector InLocation, const SQuaternion InRotation, const SVector InScale);

	// Destructor.
	~STransform();



	/// Operators



	/// Conversions



private:
	/// Functions

	// Removes this transform from it's parent's children list.
	INLINE void RemoveFromParent();
public:

	// Gets the forward pointing vector relative to this object.
	INLINE SVector Forward() const { return Rotation.GetForwardVector(); }

	// Gets the backward pointing vector relative to this object.
	INLINE SVector Backward() const { return -Rotation.GetForwardVector(); }

	// Gets the right pointing vector relative to this object.
	INLINE SVector Right() const { return Rotation.GetRightVector(); }

	// Gets the left pointing vector relative to this object.
	INLINE SVector Left() const { return -Rotation.GetRightVector(); }

	// Gets the up pointing vector relative to this object.
	INLINE SVector Up() const { return Rotation.GetUpVector(); }

	// Gets the down pointing vector relative to this object.
	INLINE SVector Down() const { return -Rotation.GetUpVector(); }

	// Rotates this transform to look at another transform's position.
	INLINE void LookAt(STransform Other);



	/// Getters

	// Gets the relative location of this object.
	INLINE SVector GetLocation() const { return Location; }

	// Gets the relative rotation of this object.
	INLINE SQuaternion GetRotation() const { return Rotation; }

	// Gets the relative scale of this object.
	INLINE SVector GetScale() const { return Scale; }

	// Gets the location, rotation and scale of this object in worldspace.
	STransform GetWorldTransform() const;

	// Gets the location of this object in worldspace.
	INLINE SVector GetWorldLocation() const { return ((Parent) ? Parent->GetWorldLocation() : SVector{ 0.0f }) + Location; }

	// Gets the rotation of this object in worldspace.
	INLINE SQuaternion GetWorldRotation() const { return ((Parent) ? Parent->GetWorldRotation() : SQuaternion{ 0.0f }) + Rotation; }

	// Gets the scale of this object in worldspace.
	INLINE SVector GetWorldScale() const { return ((Parent) ? Parent->GetWorldScale() : SVector{ 1.0f }) * Scale; }

	// Gets a reference to all this object's children.
	INLINE std::vector<STransform*> GetChildren() const { return Children; }

	// Gets a reference to this object's parent.
	INLINE STransform* GetParent() const { return Parent; }


	/// Setters

	// Sets a parent to this object.
	INLINE void SetParent(STransform* Transform);


	/// Statics

};


INLINE void STransform::RemoveFromParent()
{
	if (Parent)
	{
		for (uint i = 0; i < Parent->GetChildren().size(); ++i)
		{
			if (Parent->GetChildren()[i] == this)
			{
				Parent->GetChildren().erase(Parent->GetChildren().begin() + i);
				return;
			}
		}

		Parent = nullptr;
	}
}


INLINE void STransform::LookAt(STransform Other)
{
	Rotation.Y = TMath::ToDegrees(TMath::ATan2(Other.Location[0] - Location[0], Other.Location[2] - Location[2]));
}


INLINE void STransform::SetParent(STransform* Transform)
{
	// Make sure children don't snap to the local position of their new parent
	// but instead retain the same location in worldspace, but change their local position.

	RemoveFromParent();
	Parent = Transform;

	// Add a reference to the parent of this object.
	if (Parent)
	{
		Parent->GetChildren().push_back(this);
	}
}



// 
struct STransform2
{
private:
	/// Properties

	// A reference to this objects parent.
	STransform2* Parent{ nullptr };

	// A list of all this transform's children.
	std::vector<STransform2*> Children;

public:
	// This transform's position component.
	SVector2 Location{ 0.0f };

	// This transform's rotation component.
	float Rotation{ 0.0f };

	// This transform's scale component.
	SVector2 Scale{ 1.0f };



public:
	/// Constructors

	// Constructor, Default.
	STransform2() {}

	// Constructor, Initiates all components of the transform.
	STransform2(const SVector2& InLocation, const float& InRotation, const SVector2& InScale);

	// Destructor.
	~STransform2();



private:
	/// Functions

	// Removes this transform from it's parent's children list.
	INLINE void RemoveFromParent();

public:
	// Gets the right pointing vector relative to this object.
	INLINE SVector2 Right() const { return SVector2::Right(); }

	// Gets the left pointing vector relative to this object.
	INLINE SVector2 Left() const { return SVector2::Left(); }

	// Gets the up pointing vector relative to this object.
	INLINE SVector2 Up() const { return SVector2::Up(); }

	// Gets the down pointing vector relative to this object.
	INLINE SVector2 Down() const { return SVector2::Down(); }

	// Rotates this transform to look at another transform's position.
	INLINE void LookAt(STransform2 Other);



	/// Getters

	// Gets the relative location of this object.
	INLINE SVector2 GetLocation() const { return Location; }

	// Gets the relative rotation of this object.
	INLINE float GetRotation() const { return Rotation; }

	// Gets the relative scale of this object.
	INLINE SVector2 GetScale() const { return Scale; }

	// Gets the location, rotation and scale of this object in worldspace.
	STransform2 GetWorldTransform() const;

	// Gets the location of this object in worldspace.
	INLINE SVector2 GetWorldLocation() const { return GetWorldTransform().Rotation; }

	// Gets the rotation of this object in worldspace.
	INLINE float GetWorldRotation() const { return ((Parent) ? Parent->GetWorldRotation() : 0.0f) + Rotation; }

	// Gets the scale of this object in worldspace.
	INLINE SVector2 GetWorldScale() const { return GetWorldTransform().Scale; }

	// Gets a reference to all this object's children.
	INLINE std::vector<STransform2*> GetChildren() const { return Children; }

	// Gets a reference to this object's parent.
	INLINE STransform2* GetParent() const { return Parent; }


	/// Setters

	// Sets a parent to this object.
	INLINE void SetParent(STransform2* Transform);


	/// Statics
};



INLINE void STransform2::RemoveFromParent()
{
	if (Parent)
	{
		for (uint i = 0; i < Parent->GetChildren().size(); ++i)
		{
			if (Parent->GetChildren()[i] == this)
			{
				Parent->GetChildren().erase(Parent->GetChildren().begin() + i);
				return;
			}
		}

		Parent = nullptr;
	}
}


INLINE void STransform2::LookAt(STransform2 Other)
{
	Rotation = TMath::ToDegrees(TMath::ATan2(Other.Location[0] - Location[0], Other.Location[2] - Location[2]));
}



INLINE void STransform2::SetParent(STransform2* Transform)
{
	// Make sure children don't snap to the local position of their new parent
	// but instead retain the same location in worldspace, but change their local position.

	RemoveFromParent();
	Parent = Transform;

	// Add a reference to the parent of this object.
	if (Parent)
	{
		Parent->GetChildren().push_back(this);
	}
}