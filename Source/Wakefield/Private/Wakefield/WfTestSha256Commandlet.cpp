// Copyright Fury Games Pty Ltd. All Rights Reserved.

#include "Wakefield/WfTestSha256Commandlet.h"

#include "Wakefield/Print.h"
#include "Wakefield/Sha256.h"

namespace
{
	class ShaTester
	{
	public:

		void Append(const char* str)
		{
			BuilderHandmade.Append(str, strlen(str));
			BuilderOpenSSL.Append(str, strlen(str));
		}

		void Test(const char* str)
		{
			check(strlen(str) == 64);
			FWfSha256 Sha1, Sha2;
			Sha1 = BuilderHandmade.Finalize();
			Sha2 = BuilderOpenSSL.Finalize();
			check(Sha1 == Sha2);
			FString Observed = Sha1.ToString();
			FString Expected = Enstring(str);
			check(0 == Observed.Compare(Expected, ESearchCase::IgnoreCase));
		}
		
	private:
		FWfSha256BuilderHandmade BuilderHandmade;
		FWfSha256BuilderOpenSSL BuilderOpenSSL;
	};
}

int32 UWfTestSha256Commandlet::Main(const FString& Params)
{
	{
		ShaTester Tester;
		Tester.Append("abc");
		Tester.Test("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
	}

	{
		ShaTester Tester;
		Tester.Test("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
	}

	{
		ShaTester Tester;
		Tester.Append("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
		Tester.Test("248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
	}

	{
		ShaTester Tester;
		for (int i = 0; i < 1000000; i++)
			Tester.Append("a");
		Tester.Test("cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");
	}

	{
		ShaTester Tester;
		for (int i = 0; i < 16777216; i++)
			Tester.Append( "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno");
		Tester.Test("50e72a0e26442fe2552dc3938ac58658228c0cbfb1d2ca872ae435266fcd055e");
	}

	return 0;
}
