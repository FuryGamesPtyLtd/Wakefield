// © 2022 Fury Games Pty Ltd.  All rights reserved.

#pragma once

#include "Containers/UnrealString.h"
#include <string>

// ToStd(s) Converts an FString s to a UTF-8 std::string
inline std::string ToStd(const FString& String)
{
	return TCHAR_TO_UTF8(*String);
}

// FromStd(s) Converts a UTF-8 std::string s to an FString
inline FString FromStd(const std::string& String)
{
	return UTF8_TO_TCHAR(String.c_str());
}

// Enstring(a1,a2,...,an) will convert its arguments to strings, concatenate
// them, and return them as an FString.
//
// eg
//    Enstring(42) returns FString("42")
//    Enstring("a", "bc", 3) returns FString("abc3")
//
inline FString Enstring()
{
	return {};
}
inline FString Enstring(FString Str)
{
	return Str;
}
inline FString Enstring(const ANSICHAR* Str)
{
	return FString(Str);
}
inline FString Enstring(const WIDECHAR* Str)
{
	return FString(Str);
}
inline FString Enstring(const UTF8CHAR* Str)
{
	return FString(Str);
}
inline FString Enstring(const UCS2CHAR* Str)
{
	return FString(Str);
}
inline FString Enstring(int32 i)
{
	return FString::Printf(TEXT("%d"), i);
}
inline FString Enstring(int64 i)
{
	return FString::Printf(TEXT("%lld"), i);
}
inline FString Enstring(uint32 i)
{
	return FString::Printf(TEXT("%u"), i);
}
inline FString Enstring(uint64 i)
{
	return FString::Printf(TEXT("%llu"), i);
}
inline FString Enstring(const void* p)
{
	return Enstring(reinterpret_cast<uint64>(p));
}
inline FString Enstring(int8 i)
{
	return Enstring(int32(i));
}
inline FString Enstring(int16 i)
{
	return Enstring(int32(i));
}
inline FString Enstring(uint8 i)
{
	return Enstring(uint32(i));
}
inline FString Enstring(uint16 i)
{
	return Enstring(uint32(i));
}
inline FString Enstring(bool b)
{
	return Enstring(int32(b));
}
inline FString Enstring(double f)
{
	return FString::Printf(TEXT("%g"), f);
}
inline FString Enstring(float f)
{
	return Enstring((double)f);
}
inline FString Enstring(void* p)
{
	return FString::FromHexBlob((uint8*)&p, sizeof(void*));
}
template <typename T>
FString Enstring(T&& t)
{
	return std::forward<T>(t).ToString();
}

template <typename Arg0, typename... Args>
FString Enstring(Arg0&& arg0, Args&&... args)
{
	FString String = Enstring(std::forward<Arg0>(arg0));
	(String += ... += Enstring(std::forward<Args>(args)));
	return String;
}
