// Copyright Fury Games Pty Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector2D.h"
#include "HexVector.generated.h"

USTRUCT(BlueprintType)
struct WAKEFIELD_API FHexVectorU
{
	GENERATED_BODY()

	UPROPERTY()
	int32 X = 0;

	UPROPERTY()
	int32 Y = 0;
};

// +UnitR() right
// +UnitQ() Upleft
// +UnitS() Downleft
// +X right +Y down
//
//  -------------> +X
//  |
//  |    +Q    -S
//  |        A
//  |  -R  |  |  +R
//  |       V
//  |    +S    -Q
//  |
//  v
//  +Y
//
USTRUCT(BlueprintType)
struct WAKEFIELD_API FHexVector
{
	GENERATED_BODY();

public:
	// W = sqrt(3)
	static constexpr double Sqrt3 = 1.7320508075688772;
	static_assert(0x1.BB67AE8584CAAP+0 == 1.7320508075688772);
	static_assert(Sqrt3 * Sqrt3 == 2.9999999999999996);

	static constexpr double Ux = 0.5 * Sqrt3; // W/2
	static constexpr double Uy = 0.5;		  // H/4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Q = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 R = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 S = 0;

	constexpr bool IsValid() const { return (static_cast<uint32>(Q + R + S) & 1) == 0; }

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("Q=%d R=%d S=%d"), Q, R, S);
	}
};

static_assert(sizeof(FHexVector) == 12);

FORCEINLINE constexpr bool operator==(const FHexVector A, FHexVector B)
{
	return A.Q == B.Q && A.R == B.R && A.S == B.S;
}

FORCEINLINE constexpr bool operator!=(const FHexVector A, const FHexVector B)
{
	return !(A == B);
}

FORCEINLINE uint32 GetTypeHash(const FHexVector V)
{
	static constexpr size_t NumBytes = sizeof(FHexVector);
	static_assert(NumBytes == 12);
	return FCrc::MemCrc_DEPRECATED(&V, NumBytes);
}

FORCEINLINE constexpr FHexVector operator+(const FHexVector V)
{
	return V;
}

FORCEINLINE constexpr FHexVector operator+(const FHexVector A, const FHexVector B)
{
	return { A.Q + B.Q, A.R + B.R, A.S + B.S };
}

FORCEINLINE constexpr FHexVector operator-(const FHexVector V)
{
	return { -V.Q, -V.R, -V.S };
}

FORCEINLINE constexpr FHexVector operator-(const FHexVector A, const FHexVector B)
{
	return { A.Q - B.Q, A.R - B.R, A.S - B.S };
}

FORCEINLINE constexpr FHexVector operator*(const int32 K, const FHexVector V)
{
	return { K * V.Q, K * V.R, K * V.S };
}

FORCEINLINE constexpr FHexVector operator*(const FHexVector V, const int32 K)
{
	return K * V;
}

FORCEINLINE constexpr FHexVector& operator+=(FHexVector& A, const FHexVector B)
{
	A.Q += B.Q;
	A.R += B.R;
	A.S += B.S;
	return A;
}

FORCEINLINE constexpr FHexVector& operator-=(FHexVector& A, const FHexVector B)
{
	A.Q -= B.Q;
	A.R -= B.R;
	A.S -= B.S;
	return A;
}

FORCEINLINE constexpr FHexVector& operator*=(FHexVector& V, const int32 K)
{
	V.Q *= K;
	V.R *= K;
	V.S *= K;
	return V;
}

WAKEFIELD_API FVector2D HexVectorVertex(const FHexVector V, int i);

constexpr int32 ManhattanLength(const FHexVector V)
{
	const int64 Q64 = V.Q;
	const int64 R64 = V.R;
	const int64 S64 = V.S;
	const int64 T = ((Q64 >= 0 ? Q64 : -Q64) + (R64 >= 0 ? R64 : -R64) + (S64 >= 0 ? S64 : -S64));
	return T / static_cast<int64>(2);
}

constexpr FHexVectorU EuclideanPositionU(const FHexVector V)
{
	return { 2 * V.Q + V.R, 3 * V.R };
}

constexpr FHexVector FromEuclideanPositionU(FHexVectorU Position)
{
	FHexVector Result;
	Result.R = Position.Y / 3;
	Result.Q = (Position.X - Result.R) / 2;
	Result.S = 0 - Result.R - Result.Q;
	return Result;
}

FORCEINLINE FVector2D HexVectorUToVector2D(const FHexVectorU U)
{
	return { FHexVector::Ux * static_cast<double>(U.X), FHexVector::Uy * static_cast<double>(U.Y) };
}

FORCEINLINE FVector2D EuclideanPosition(const FHexVector V)
{
	return HexVectorUToVector2D(EuclideanPositionU(V));
}

FORCEINLINE double EuclideanLength(const FHexVector V)
{
	return EuclideanPosition(V).Length();
}

constexpr FHexVector ZeroHexVector = { 0, 0, 0 };
constexpr FHexVector UnitQHexVector = { 0, -1, +1 };
constexpr FHexVector UnitRHexVector = { +1, 0, -1 };
constexpr FHexVector UnitSHexVector = { -1, +1, 0 };

static_assert(UnitQHexVector + UnitRHexVector == -UnitSHexVector);
static_assert(UnitRHexVector + UnitSHexVector == -UnitQHexVector);
static_assert(UnitSHexVector + UnitQHexVector == -UnitRHexVector);

static constexpr FHexVector UnitHexVectors[6] = {
	UnitRHexVector,
	-UnitQHexVector,
	UnitSHexVector,
	-UnitRHexVector,
	UnitQHexVector,
	-UnitSHexVector,
};

WAKEFIELD_API FHexVector Vector2DToHexVector(FVector2D Point);
