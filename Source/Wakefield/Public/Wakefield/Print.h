// Copyright Fury Games Pty Ltd. All rights reserved.

#pragma once

#include "Wakefield/Enstring.h"

// Print(a1,a2,...,an) will convert its arguments to strings concatenate them
// with a space separator and UE_LOG them at Display level.
//
// eg
//
//   Print("Hello, World!"); // will log "Hello, World!"
//
//   Print("The answer is", 42);  // will log "The answer is 42"
//
//
template <typename Arg0>
void Print(Arg0&& arg0);
template <typename Arg0, typename... Args>
void Print(Arg0&& arg0, Args&&... args);

// WKF_PRINT_EXPR(expr) will stringize its argument expression and its argument
// value and then Print("expr = value")
//
// eg
//
//   int NumCats = 42;
//   WKF_PRINT_EXPR(NumCats); // will log "NumCats = 42"
//
#define WKF_PRINT_EXPR(expr)     \
	do                           \
	{                            \
		Print(#expr, "=", expr); \
	}                            \
	while (0)

void WAKEFIELD_API PrintImpl(const FString& Message);

template <typename Arg0>
void Print(Arg0&& arg0)
{
	PrintImpl(Enstring(std::forward<Arg0>(arg0)));
}

template <typename Arg0, typename... Args>
void Print(Arg0&& arg0, Args&&... args)
{
	FString String = Enstring(std::forward<Arg0>(arg0));

	(((String += " ") += Enstring(std::forward<Args>(args))), ...);
	PrintImpl(String);
}
