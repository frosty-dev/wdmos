#include "core.h"

extern "C" EXPORT const char* core_initialize(int n_args, const char** args)
{
	if (!Core::initialize())
	{
		Core::Alert("Core init failed!");
		return Core::FAIL;
	}
	return Core::SUCCESS;
}

extern "C" EXPORT const char* cleanup(int n_args, const char** args)
{
	Core::cleanup();
	return Core::SUCCESS;
}
