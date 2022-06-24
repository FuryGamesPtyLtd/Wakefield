// Copyright Fury Games Pty Ltd. All Rights Reserved.

#include "Wakefield.h"

#include "Wakefield/Print.h"

void FWakefieldModule::StartupModule()
{
    Print("Wakefield module starting up");
}

void FWakefieldModule::ShutdownModule()
{
    Print("TangoCore module shutting down");
}

IMPLEMENT_MODULE(FWakefieldModule, Wakefield)
