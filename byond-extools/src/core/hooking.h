#pragma once

#include "byond_functions.h"
#include "core.h"
#include "proc_management.h"
#include "../third_party/subhook/subhook.h"

namespace Core
{
	struct Proc;
}

struct QueuedCall
{
	Core::Proc& proc;
	Value src;
	Value usr;
	std::vector<Value> args;
};

namespace Core
{
	void* untyped_install_hook(void* original, void* hook);

	// Used to ensure everything is the same function pointer type.
	template<typename FnPtr>
	FnPtr install_hook(FnPtr original, FnPtr hook)
	{
		return (FnPtr) untyped_install_hook((void*) original, (void*) hook);
	}

	void remove_hook(void* func);
	void remove_all_hooks();
	bool hook_custom_opcodes();
	//void schedule_call(Proc proc, std::vector<Value> args, Value src = Value::Null(), Value usr = Value::Null());
}