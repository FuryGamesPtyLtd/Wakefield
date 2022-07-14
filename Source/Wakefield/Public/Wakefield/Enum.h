#pragma once

#include <type_traits>

#include "CoreMinimal.h"
#include "Wakefield/Enstring.h"

template <typename EEnum>
FString EnumToDisplayName(const EEnum Enumerator)
{
	const UEnum* const EnumClass = StaticEnum<EEnum>();

	const auto Value = static_cast<std::underlying_type_t<EEnum>>(Enumerator);

	if (!EnumClass)
		return Enstring(static_cast<int64>(Value));

	FString DisplayName = EnumClass->GetDisplayNameTextByValue(Value).ToString();

	if (!DisplayName.IsEmpty())
		return DisplayName;

	DisplayName = EnumClass->GetNameStringByValue(Value);

	if (!DisplayName.IsEmpty())
		return DisplayName;

	return Enstring(static_cast<int64>(Value));
}
