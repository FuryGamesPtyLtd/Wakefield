// Copyright Fury Games Pty Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"

constexpr FORCEINLINE int32 SignedDiv(int32 A, int32 B)
{
	return A / B - (A % B < 0);
}
constexpr FORCEINLINE int64 SignedDiv(int64 A, int64 B)
{
	return A / B - (A % B < 0);
}
constexpr FORCEINLINE int32 SignedMod(int32 A, int32 B)
{
	return A - B * SignedDiv(A, B);
}
constexpr FORCEINLINE int64 SignedMod(int64 A, int64 B)
{
	return A - B * SignedDiv(A, B);
}

constexpr double operator"" _m(unsigned long long int M)
{
	return M * 100.0;
}

constexpr double operator"" _m(long double M)
{
	return M * 100.0;
}

constexpr double operator"" _km(unsigned long long int Km)
{
	return Km * 100000.0;
}

constexpr double operator"" _km(long double Km)
{
	return Km * 100000.0;
}
