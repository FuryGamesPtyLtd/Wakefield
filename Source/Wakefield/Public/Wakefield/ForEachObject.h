// © 2022 Fury Games Pty Ltd.  All rights reserved.

#pragma once

#include "Templates/Function.h"

// A FObjectVisitor is passed to ForEachObject and will be called with the
// Object as a parameter.
//
using FObjectVisitor = TFunction<void(UObject* Object)>;

// ForEachObject calls ObjectVisitor once for each UObject instance in the
// program, with the instance as parameter.
//
void WAKEFIELD_API ForEachObject(const FObjectVisitor& ObjectVisitor);
