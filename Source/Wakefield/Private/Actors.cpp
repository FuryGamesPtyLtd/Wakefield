// Copyright Fury Games Pty Ltd. All rights reserved.

#include "Wakefield/Actors.h"

FActorSpawnSpecification::FActorSpawnSpecification(UClass* ClassIn,
	FTransform TransformIn)
	: FActorSpawnParameters(), Class(ClassIn), Transform(TransformIn) {}

FActorSpawnSpecification::FActorSpawnSpecification()
	: FActorSpawnSpecification(nullptr, FTransform::Identity) {}

FActorSpawnSpecification::FActorSpawnSpecification(FTransform TransformIn)
	: FActorSpawnSpecification(nullptr, TransformIn) {}

FActorSpawnSpecification::FActorSpawnSpecification(UClass* ClassIn)
	: FActorSpawnSpecification(ClassIn, FTransform::Identity) {}
