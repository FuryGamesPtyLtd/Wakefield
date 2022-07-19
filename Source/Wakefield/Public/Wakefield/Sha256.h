// Copyright Fury Games Pty Ltd. All rights reserved.

#pragma once

#include <array>

#include "CoreMinimal.h"

#define SHA256_BYTES_SIZE 32

class WAKEFIELD_API FSha256
{
public:
	FSha256();

	void Append(const void* data, size_t n_bytes);

	std::array<uint64, 4> Finalize();

	uint32_t State[8];
	uint8_t Buffer[64];
	uint64_t NBits;
	uint8_t BufferCounter;
};
