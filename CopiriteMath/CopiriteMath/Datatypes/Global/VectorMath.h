#pragma once
#include "../Vector.h"
#include <DirectXMath.h>
template <uint Size, typename Type>
STVector<Size, Type> VectorMultiplyAdd(STVector<Size, Type> V1, STVector<Size, Type> V2, STVector<Size, Type> V3) { return (V1 * V2) + V3; }
