// Copyright Fury Games Pty Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "WfTestSha256Commandlet.generated.h"

/**
 *
 */
UCLASS()
class WAKEFIELD_API UWfTestSha256Commandlet : public UCommandlet
{
	GENERATED_BODY()

	virtual int32 Main(const FString& Params) override;
};
