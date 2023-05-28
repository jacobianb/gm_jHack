#include <Windows.h>
#include "icvar.h"
#include "CLuaShared.h"
#include "CLuaConVars.h"
#include "CLuaInterface.h"

template <class T>
T* GetInterface(const char *pModule, const char *pInterface)
{
	typedef void*(CreateInterface)(const char*, int*);
	CreateInterface *pCreateInterface = (CreateInterface*)GetProcAddress(GetModuleHandleA(pModule), "CreateInterface");

	return (T*)pCreateInterface(pInterface, nullptr);
}

void Main(HMODULE hModule)
{
	ICvar *pCvar = GetInterface<ICvar>("vstdlib.dll", "VEngineCvar007");
	CLuaShared* LuaShared = GetInterface<CLuaShared>("lua_shared.dll", "LUASHARED003");
	CLuaInterface* LuaInterface = nullptr;

	while (!LuaInterface)
	{
		LuaInterface = LuaShared->GetLuaInterface(LuaInterfaceType::LUA_CLIENT);
		Sleep(10);
	}
	LuaInterface->RunStringEx("", "", "print('WELCOME FAGGOT')", true, true, true, true);
	Sleep(10); // without this sleep it crashes
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, nullptr);
	case DLL_PROCESS_DETACH:
	break;
	}
	return TRUE;
}

