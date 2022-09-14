// Copyright Fury Games Pty Ltd. All rights reserved.

#include "Wakefield/Print.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPrint, All, All);

DEFINE_LOG_CATEGORY(LogPrint);

void PrintImpl(const FString& Message)
{
	UE_LOG(LogPrint, Display, TEXT("%s"), *Message);
}
