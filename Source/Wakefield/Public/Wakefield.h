// Copyright Fury Games Pty Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FWakefieldModule : public IModuleInterface
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};

