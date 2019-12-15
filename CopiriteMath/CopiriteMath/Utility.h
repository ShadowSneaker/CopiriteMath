#pragma once


#ifndef COPIRITE_UTILITY
#define COPIRITE_UTILITY

#define ASSERT static_assert
#define INLINE __forceinline
#define VECTORCALL __vectorcall
#define FASTCALL __fastcall

#define DEPRECATED(Message) [[deprecated(Message)]]




#endif // !COPIRITE_UTILITY