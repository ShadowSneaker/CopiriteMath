#pragma once
#include "../MathGlobals.h"



namespace Vector
{

#ifdef SDL
#include <SDL_Image.h>



	template <uint Size, typename Type>
	INLINE STVector<Size, Type> FromSDL_Rect(const SDL_Rect& Rect)
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
	INLINE STVector<Size, Type> FromSDL_FRect(const SDL_FRect& Rect)
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
	INLINE STVector<Size, Type> FromSDL_Point(const SDL_Point& Point)
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
	INLINE STVector<Size, Type> FromSDL_FPoint(const SDL_FPoint& Point)
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
	INLINE SDL_Rect ToSDL_Rect(const STVector<Size, Type>& Vector)
	{
		switch (Size)
		{
		case 0:
			return SDL_Rect{ 0, 0, 0, 0 };

		case 1:
			return SDL_Rect{ (int32)Vector[0], 0, 0, 0 };

		case 2:
			return SDL_Rect{ (int32)Vector[0], (int32)Vector[1], 0, 0 };

		case 3:
			return SDL_Rect{ (int32)Vector[0], (int32)Vector[1], (int32)Vector[2], 0 };

		case 4:
		default:
			return SDL_Rect{ (int32)Vector[0], (int32)Vector[1], (int32)Vector[2], (int32)Vector[3] };
		}
	}


	template <uint Size, typename Type>
	INLINE SDL_FRect ToSDL_FRect(const STVector<Size, Type>& Vector)
	{
		switch (Size)
		{
		case 0:
			return SDL_FRect{ 0, 0, 0, 0 };

		case 1:
			return SDL_FRect{ (float)Vector[0], 0, 0, 0 };

		case 2:
			return SDL_FRect{ (float)Vector[0], (float)Vector[1], 0, 0 };

		case 3:
			return SDL_FRect{ (float)Vector[0], (float)Vector[1], (float)Vector[2], 0 };

		case 4:
		default:
			return SDL_FRect{ (float)Vector[0], (float)Vector[1], (float)Vector[2], (float)Vector[3] };
		}
	}


	template <uint Size, typename Type>
	INLINE SDL_Point ToSDL_Point(const STVector<Size, Type>& Vector)
	{
		switch (Size)
		{
		case 0:
			return SDL_Point{ 0, 0 };

		case 1:
			return SDL_Point{ (int32)Vector[0], 0 };

		case 2:
		default:
			return SDL_Point{ (int32)Vector[0], (int32)Vector[1] };
		}
	}


	// Converts a STVector to a SDL_FPoint.
	// @template Size - The amount of dimensions of the vector.
	// @template Type - The datatype the vector should use.
	// @param Vector - The glm::vec to convert.
	// @return - The created STVector.
	template <uint Size, typename Type>
	INLINE SDL_FPoint ToSDL_FPoint(const STVector<Size, Type>& Vector)
	{
		switch (Size)
		{
		case 0:
			return SDL_FPoint{ 0.0f, 0.0f };

		case 1:
			return SDL_FPoint{ (float)Vector[0], 0.0f };

		case 2:
		default:
			return SDL_FPoint{ (float)Vector[0], (float)Vector[1] };
		}
	}


#endif // SDL



#ifdef DIRECTX_MATH
#include <DirectXMath.h>


#endif // DIRECTX_Math



#ifdef GLM_MATH
#include <glm/glm.hpp>


	// Converts a STVector to a glm::vec of the same size and type.
	// @template Size - The amount of dimensions of the vector.
	// @template Type - The datatype the vector should use.
	// @param Vector - The STVector to convert.
	// @return - The created STVector.
	template <uint Size, typename Type = float>
	INLINE glm::vec<Size, Type> ToGLMVector(const STVector<Size, Type>& Vec)
	{
		glm::vec<Size, Type> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = Vec[i];
		}
		return Result;
	}


	// Converts a glm::vec to a STVector of the same size and type.
	// @template Size - The amount of dimensions of the vector.
	// @template Type - The datatype the vector should use.
	// @param Vector - The glm::vec to convert.
	// @return - The created STVector.
	template <uint Size, typename Type = float>
	INLINE STVector<Size, Type> FromGLMVector(const glm::vec<Size, Type>& Vector)
	{
		STVector<Size, Type> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = Vector[i];
		}
		return Result;
	}

#endif // GLM_MATH
}