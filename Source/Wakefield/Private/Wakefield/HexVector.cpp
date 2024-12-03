// Copyright Fury Games Pty Ltd. All rights reserved.

#include "Wakefield/HexVector.h"
#include "Wakefield/Math.h"

FVector2D HexVectorVertex(const FHexVector V, int i)
{
	auto CalcVertex = [&](int32 X, int32 Y) -> FVector2D {
		FHexVectorU U = EuclideanPositionU(V);
		return HexVectorUToVector2D({ U.X + X, U.Y + Y });
	};

	switch (i)
	{
		case 0:
			return CalcVertex(0, -2);
		case 1:
			return CalcVertex(1, -1);
		case 2:
			return CalcVertex(1, 1);
		case 3:
			return CalcVertex(0, 2);
		case 4:
			return CalcVertex(-1, 1);
		case 5:
			return CalcVertex(-1, -1);
		default:
			check(false);
			return EuclideanPosition(V);
	}
}

FHexVector Vector2DToHexVector(FVector2D Point)
{
	const double Xu = Point.X / FHexVector::Ux;
	const double Yu = Point.Y / FHexVector::Uy;
	const double BlockX = 2.0 * FMath::Floor(Xu / 2.0);
	const double BlockY = 6.0 * FMath::Floor(Yu / 6.0);
	const FHexVectorU U0{ static_cast<int32>(BlockX), static_cast<int32>(BlockY) };
	const FHexVector V0 = FromEuclideanPositionU(U0);

	const double BlockOffsetY = Yu - BlockY;
	const int Interval = static_cast<int>(FMath::Floor(BlockOffsetY));
	if (Interval == 2 || Interval == 3)
	{
		return V0 - UnitQHexVector;
	}
	else
	{
		const double BlockOffsetX = Xu - BlockX;
		const bool LeftSide = (BlockOffsetX < 1.0);

		if (Interval == 0)
			return LeftSide ? V0 : V0 + UnitRHexVector;
		else if (Interval == 5)
		{
			const FHexVector B = V0 + UnitSHexVector - UnitQHexVector;
			return LeftSide ? B : B + UnitRHexVector;
		}
		else
		{
			auto CalcSlope = [&](const FHexVector& A, const FHexVector& B, double X, double Y) {
				if (X <= 1.0 - Y)
					return A;
				else
					return B;
			};

			double RectOffX = BlockOffsetX - (LeftSide ? 0.0 : 1.0);
			double RectOffY = BlockOffsetY - static_cast<double>(Interval);

			if (LeftSide && Interval == 1)
			{
				const FHexVector A = V0;
				const FHexVector B = V0 - UnitQHexVector;
				if (RectOffX <= 1.0 - RectOffY)
					return A;
				else
					return B;
			}
			else if (!LeftSide && Interval == 1)
			{
				const FHexVector A = V0 - UnitQHexVector;
				const FHexVector B = V0 + UnitRHexVector;
				if (RectOffY >= RectOffX)
					return A;
				else
					return B;
			}
			else if (LeftSide && Interval == 4)
			{
				const FHexVector A = V0 + UnitSHexVector - UnitQHexVector;
				const FHexVector B = V0 - UnitQHexVector;
				if (RectOffY >= RectOffX)
					return A;
				else
					return B;
			}
			else
			{
				check(!LeftSide && Interval == 4);

				const FHexVector A = V0 - UnitQHexVector;
				const FHexVector B = V0 - 2 * UnitQHexVector;
				if (RectOffX <= 1.0 - RectOffY)
					return A;
				else
					return B;
			}
		}
	}
}
