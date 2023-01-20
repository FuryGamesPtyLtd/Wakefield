#include "Wakefield/Math.h"

FVector2D NearestPointOnLineSegment(FVector2D Point, FVector2D LineA, FVector2D LineB)
{
	const FVector2D LineOffset = LineB - LineA;
	const double LineLength = LineOffset.Length();
	if (LineLength < KINDA_SMALL_NUMBER)
		return LineA;
	const FVector2D LineDirection = LineOffset.GetSafeNormal();

	const FVector2D OffsetFromA = Point - LineA;

	const double ProjPoint = OffsetFromA.Dot(LineDirection);
	if (ProjPoint < 0)
		return LineA;
	else if (ProjPoint > LineLength)
		return LineB;
	else
		return LineA + ProjPoint * LineDirection;
}

double DistanceToLineSegment(FVector2D Point, FVector2D LineA, FVector2D LineB)
{
	return (Point - NearestPointOnLineSegment(Point, LineA, LineB)).Length();
}
