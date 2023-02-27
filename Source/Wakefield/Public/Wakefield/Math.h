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

class FYawAngle
{
public:
	explicit FYawAngle(FVector2D UnitVector)
		: FYawAngle(FMath::RadiansToDegrees(FMath::Atan2(UnitVector.Y, UnitVector.X)))
	{

	}
	
	explicit FYawAngle(double YawIn)
	{
		Yaw = NormalizeYaw(YawIn);
	}

	FYawAngle operator+(double Delta) const
	{
		return FYawAngle(Yaw + Delta);
	}

	FYawAngle& operator+=(double Delta)
	{
		Yaw = NormalizeYaw(Yaw + Delta);
		return *this;
	}

	FYawAngle operator-(double Delta) const
	{
		return FYawAngle(Yaw - Delta);
	}

	FYawAngle& operator-=(double Delta)
	{
		Yaw = NormalizeYaw(Yaw - Delta);
		return *this;
	}

	double Get() const { return Yaw; }

	static double GetDelta(FYawAngle Source, FYawAngle Destination)
	{
		const double A = Source.Yaw;
		const double B = Destination.Yaw;
		double C = NormalizeYaw(B - A);
		if (C > 180)
			C -= 360;
		return C;
	}

	FVector2D Sincos() const
	{
		FVector2D Result;
		FMath::SinCos(&Result.Y, &Result.X, FMath::DegreesToRadians(Yaw));
		return Result;
	}

private:
	static double NormalizeYaw(double Yaw)
	{
		Yaw -= 360 * std::floor(Yaw / 360.0);
		return Yaw;
	}

	double Yaw;
};

WAKEFIELD_API FVector2D NearestPointOnLineSegment(FVector2D Point, FVector2D LineA, FVector2D LineB);

WAKEFIELD_API double DistanceToLineSegment(FVector2D Point, FVector2D LineA, FVector2D LineB);
