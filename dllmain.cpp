#include <Windows.h>
#include "icvar.h"
#include "CLuaShared.h"
#include "CLuaConVars.h"
#include "CLuaInterface.h"
#include <fstream>

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
		LuaInterface = LuaShared->GetLuaInterface(LuaInterfaceType::LUA_MENU);
		Sleep(10);
	}
	LuaInterface->RunStringEx("", "", "print('HACK LOADED. WAITING TO LOAD IN GAME...')", true, true, true, true);
	LuaInterface = nullptr;
	while (!LuaInterface)
	{
		LuaInterface = LuaShared->GetLuaInterface(LuaInterfaceType::LUA_CLIENT);
		Sleep(10);
	}
	LuaInterface->RunStringEx("", "", "print('HACK LOADED. LOADED IN GAME.')", true, true, true, true);
	LuaInterface->RunStringEx("", "", "concommand.Add('lo',function(p,c,a)RunString(file.Read(a[1],'LUA'))end)", true, true, true, true);

	Sleep(1000);
/*
	while (1) {
		if (GetAsyncKeyState(VK_END)) {
			LuaInterface->RunStringEx("", "", "print('HOME PRESSED.')", true, true, true, true);
			
			std::ifstream ifs("C:\\myfile.lua");
			std::string content( (std::istreambuf_iterator<char>(ifs) ),(std::istreambuf_iterator<char>()    ) );
			LuaInterface->RunStringEx("", "", content.c_str(), true, true, true, true);
			ifs.close();
			
		}
		Sleep(1000);
	}
*/
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

