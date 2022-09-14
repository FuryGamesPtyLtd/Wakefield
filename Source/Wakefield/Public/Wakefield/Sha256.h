// Copyright Fury Games Pty Ltd. All rights reserved.

#pragma once

#include <openssl/sha.h>

#include "CoreMinimal.h"
#include "Sha256.Generated.h"

#define WKF_SHA256_BYTES_SIZE 32

USTRUCT()
struct FWfSha256
{
	GENERATED_BODY()
	
	UPROPERTY()
	uint8 Bytes[WKF_SHA256_BYTES_SIZE] = {};

	FORCEINLINE FString ToString() const
	{
		return FString::FromHexBlob(Bytes, WKF_SHA256_BYTES_SIZE);
	}
};

#define WKF_DEFINE_CMP_SHA256(op) \
	FORCEINLINE bool operator op(const FWfSha256& A, const FWfSha256& B) \
	{ \
		return FMemory::Memcmp(A.Bytes, B.Bytes, WKF_SHA256_BYTES_SIZE) op 0; \
	}
WKF_DEFINE_CMP_SHA256(==)
WKF_DEFINE_CMP_SHA256(!=)
WKF_DEFINE_CMP_SHA256(<)
WKF_DEFINE_CMP_SHA256(>)
WKF_DEFINE_CMP_SHA256(<=)
WKF_DEFINE_CMP_SHA256(>=)

FORCEINLINE uint32 GetTypeHash(const FWfSha256& V)
{
	return (static_cast<uint32>(V.Bytes[0]) << 0)
	| (static_cast<uint32>(V.Bytes[1]) << 8)
	| (static_cast<uint32>(V.Bytes[2]) << 16)
	| (static_cast<uint32>(V.Bytes[3]) << 24);
}

static_assert(sizeof(FWfSha256) == WKF_SHA256_BYTES_SIZE);

class WAKEFIELD_API FWfSha256BuilderHandmade
{
public:
	FWfSha256BuilderHandmade();

	void Append(const void* data, size_t n_bytes);

	FWfSha256 Finalize();

	uint32_t State[8];
	uint8_t Buffer[64];
	uint64_t NBits;
	uint8_t BufferCounter;
};

class WAKEFIELD_API FWfSha256BuilderOpenSSL
{
public:
	FORCEINLINE FWfSha256BuilderOpenSSL()
	{
		SHA256_Init(&Context);
	}
	
	FORCEINLINE void Append(const void* data, size_t n_bytes)
	{
		SHA256_Update(&Context, data, n_bytes);
	}

	FORCEINLINE FWfSha256 Finalize()
	{
		FWfSha256 Result;
		SHA256_Final(Result.Bytes, &Context);
		return Result;
	}

private:
	SHA256_CTX Context;
};