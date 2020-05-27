#include "ProcMem.h"
#include "csgo.hpp"
#include "iostream"

ProcMem Pamiec;
ProcMem* wsk = &Pamiec;

void BunnyHop()
{
	char NazwaProgramu[11]{ "csgo.exe" };
	char DLL[20]{ "client_panorama.dll" };

	wsk->Process(NazwaProgramu);
	DWORD PamiecModul{ wsk->Module(DLL) };

	while (true)
	{
		if (GetAsyncKeyState(0x20))
		{
			DWORD jednostka1{ wsk->Read<DWORD>(DWORD(PamiecModul) + DWORD(hazedumper::signatures::dwLocalPlayer)) };
			DWORD FLAGA{ wsk->Read<DWORD>(jednostka1 + hazedumper::netvars::m_fFlags) };

			if (static_cast<int>(FLAGA) == 257)
			{
				wsk->Write(PamiecModul + hazedumper::signatures::dwForceJump, 6);
			}
		}
		Sleep(5);
	}
}