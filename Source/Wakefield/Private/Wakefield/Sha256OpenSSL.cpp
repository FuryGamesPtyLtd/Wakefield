#include "Wakefield/Sha256.h"

#include <openssl/sha.h>

static_assert(sizeof(SHA256_CTX) == sizeof(FWfSha256BuilderOpenSSL::ContextStorage));
static_assert(alignof(SHA256_CTX) == alignof(FWfSha256BuilderOpenSSL::ContextStorage));

FWfSha256BuilderOpenSSL::FWfSha256BuilderOpenSSL()
{
	SHA256_Init((SHA256_CTX*)&Context);
}

void FWfSha256BuilderOpenSSL::Append(const void* data, size_t n_bytes)
{
	SHA256_Update((SHA256_CTX*)&Context, data, n_bytes);
}

FWfSha256 FWfSha256BuilderOpenSSL::Finalize()
{
	FWfSha256 Result;
	SHA256_Final(Result.Bytes, (SHA256_CTX*)&Context);
	return Result;
}
