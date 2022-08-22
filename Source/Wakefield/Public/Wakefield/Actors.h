// Copyright Fury Games Pty Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

// FActorSpawnSpecification extends FActorSpawnParameters with an
// optional UClass* Class field, and an FTransform Transform
// field.  The Class field defaults to nullptr (which means take
// the Class from the type template parameter T to SpawnActor).
// The Transform field defaults to the identity transform.
//
struct WAKEFIELD_API FActorSpawnSpecification : FActorSpawnParameters
{
	FActorSpawnSpecification();
	explicit FActorSpawnSpecification(FTransform Transform);
	explicit FActorSpawnSpecification(UClass* Class);
	FActorSpawnSpecification(UClass* Class, FTransform Transform);

	// The class of actor to spawn.  The default nullptr means use the T
	// type template parameter to SpawnActor.
	//
	UClass* Class = nullptr;

	// The initial transform of the spawned actor.
	//
	FTransform Transform = FTransform::Identity;
};

// SpawnActor<T>(World, ActorSpawnSpecification, Arg1, Args2, ..., ArgN)
// spawns an actor of type T according to the given ActorSpawnSpecification
// and calling TheSpawnedActor->Initialize(Arg1, Arg2, ..., ArgN) during
// the spawning process.
//
// Initialize is called in the following order:
//
//    C++ Constructor
//    PostInitProperties
//    PreRegisterComponents
//    PostRegisterComponents
//    PostActorCreated
//    Initialize <-- HERE
//    UserConstructionScript
//    OnConstruction
//    PreInitializeComponents
//    PostInitializeComponents
//    BeginPlay
//
// (This means that Initialize is called prior to replication of the actor,
// and so COND_Initial properties can be set by Initialize.)
//
template <class T, typename... TArgs>
T* SpawnActor(UWorld* World, FActorSpawnSpecification ActorSpawnSpecification,
	TArgs&&... Args)
{
	ActorSpawnSpecification.bDeferConstruction = true;
	if (ActorSpawnSpecification.Class == nullptr)
		ActorSpawnSpecification.Class = T::StaticClass();
	AActor* BaseActor = World->SpawnActor(ActorSpawnSpecification.Class,
		&ActorSpawnSpecification.Transform,
		ActorSpawnSpecification);
	T* Actor = CastChecked<T>(BaseActor);
	if (!IsValid(Actor))
		return nullptr;
	Actor->Initialize(std::forward<TArgs>(Args)...);
	Actor->FinishSpawning(ActorSpawnSpecification.Transform);
	return Actor;
}
