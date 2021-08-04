#include "hooking.h"
#include <chrono>
#include <fstream>
#include <stack>
#include <mutex>
#include <memory>

CrashProcPtr oCrashProc;
CallGlobalProcPtr oCallGlobalProc;
StartTimingPtr oStartTiming;

std::unordered_map<void*, std::unique_ptr<subhook::Hook>> hooks;

//ExecutionContext* last_suspended_ec;

std::vector<QueuedCall> queued_calls;
bool calling_queue = false;

trvh REGPARM3 hCallGlobalProc(char usr_type, int usr_value, int proc_type, unsigned int proc_id, int const_0, DataType src_type, int src_value, Value *argList, unsigned char argListLen, int const_0_2, int const_0_3)
{
	if (auto ptr = proc_hooks.find((unsigned short)proc_id); ptr != proc_hooks.end())
	{
		trvh result = ptr->second(argListLen, argList, src_type ? Value(src_type, src_value) : static_cast<Value>(Value::Null()));
		for (int i = 0; i < argListLen; i++)
		{
			DecRefCount(argList[i].type, argList[i].value);
		}
		return result;
	}
	trvh result = oCallGlobalProc(usr_type, usr_value, proc_type, proc_id, const_0, src_type, src_value, argList, argListLen, const_0_2, const_0_3);
	return result;
}

void hCrashProc(char *error, variadic_arg_hack hack) //this is a hack to pass variadic arguments to the original function, the struct contains a 1024 byte array
{
	int argument = *(int*)hack.data;
	if (auto ptr = Core::opcode_handlers.find(argument); ptr != Core::opcode_handlers.end())
	{
		ptr->second(*Core::current_execution_context_ptr);
		return;
	}
	oCrashProc(error, hack);
}

std::recursive_mutex timing_mutex;

#ifndef _WIN32
REGPARM3
#endif
void hStartTiming(SuspendedProc* sp)
{
	std::lock_guard<std::recursive_mutex> lk(timing_mutex);
	oStartTiming(sp);
}

void* Core::untyped_install_hook(void* original, void* hook)
{
	std::unique_ptr<subhook::Hook> /*I am*/ shook = std::make_unique<subhook::Hook>();
	shook->Install(original, hook);
	auto trampoline = shook->GetTrampoline();
	hooks[original] = std::move(shook);
	return trampoline;
}

void Core::remove_hook(void* func)
{
	hooks[func]->Remove();
	hooks.erase(func);
}

void Core::remove_all_hooks()
{
	for (auto iter = hooks.begin(); iter != hooks.end(); )
	{
		iter->second->Remove();
		iter = hooks.erase(iter);
	}
}

bool Core::hook_custom_opcodes() {
	oCrashProc = install_hook(CrashProc, hCrashProc);
	oCallGlobalProc = install_hook(CallGlobalProc, hCallGlobalProc);
	oStartTiming = install_hook(StartTiming, hStartTiming);
	if (!(oCrashProc && oCallGlobalProc && oStartTiming)) {
		Core::Alert("Failed to install hooks!");
		return false;
	}
	return true;
}
