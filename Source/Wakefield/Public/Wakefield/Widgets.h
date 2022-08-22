#pragma once

#include "CoreMinimal.h"

// WKF_FIND_OBJECT(Class, Variable, Path) uses an FObjectFinder to find
// an object of type Class at Path and assigns it to Variable if successful.
//
#define WKF_FIND_OBJECT(Class, Variable, Path)                             \
	do                                                                     \
	{                                                                      \
		static ConstructorHelpers::FObjectFinder<Class> Variable##_Finder( \
			TEXT(Path));                                                   \
		if (Variable##_Finder.Succeeded())                                 \
			Variable = Variable##_Finder.Object;                           \
	}                                                                      \
	while (0)
