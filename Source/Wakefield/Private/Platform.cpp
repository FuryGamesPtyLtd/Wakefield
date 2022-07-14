#include "Wakefield/Platform.h"

void ExitFailure()
{
	FPlatformMisc::RequestExitWithStatus(false, EXIT_FAILURE);
}
