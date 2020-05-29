#pragma once


#ifndef COPIRITE_UTILITY
#define COPIRITE_UTILITY

#define ASSERT static_assert
#define INLINE __forceinline
#define VECTORCALL __vectorcall

#ifdef _M_IX86
#define FASTCALL __fastcall
#else
#define FASTCALL
#endif

#define DEPRECATED(Message) [[deprecated(Message)]]



#endif // !COPIRITE_UTILITY