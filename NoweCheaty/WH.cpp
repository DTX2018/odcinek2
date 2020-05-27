#include "ProcMem.h"
#include "csgo.hpp"
#include "iostream"

ProcMem Pamiec2;
ProcMem* wsk2 = &Pamiec2;

void WH()
{
	char NazwaProgramu[11]{ "csgo.exe" };
	char DLL[20]{ "client_panorama.dll" };

	wsk2->Process(NazwaProgramu);
	DWORD PamiecModul{ wsk2->Module(DLL) };

	DWORD swiecacyGracz{ wsk2->Read<DWORD>(PamiecModul + hazedumper::signatures::dwGlowObjectManager) };

	while (true)
	{
		DWORD OBIEKTgracza{ wsk2->Read<DWORD>(PamiecModul + hazedumper::signatures::dwLocalPlayer) };
		int MojZespol{ wsk2->Read<int>(OBIEKTgracza + hazedumper::netvars::m_iTeamNum) };


		for (int i = 0; i < 10; i++)
		{
			DWORD ObiektPrzeciwnegoGracza{ wsk2->Read<DWORD>(PamiecModul + hazedumper::signatures::dwEntityList + i *VK_SHIFT) };

			int SwiecenieDyn{ wsk2->Read<int>(ObiektPrzeciwnegoGracza + hazedumper::netvars::m_iGlowIndex) };
			int PrzeciwnyZespol{ wsk2->Read<int>(ObiektPrzeciwnegoGracza + hazedumper::netvars::m_iTeamNum) };

			if (PrzeciwnyZespol != MojZespol)
			{
				wsk2->Write<float>(swiecacyGracz + (SwiecenieDyn * 0x38) + 0x8, 1);
				wsk2->Write<float>(swiecacyGracz + (SwiecenieDyn * 0x38) + 0x10, 0.5);
			}
			else
			{
				wsk2->Write<float>(swiecacyGracz + (SwiecenieDyn * 0x38) + 0x4, 1);
				wsk2->Write<float>(swiecacyGracz + (SwiecenieDyn * 0x38) + 0x10, 0.5);
			}
			wsk2->Write<bool>(swiecacyGracz + (SwiecenieDyn * 0x38) + 0x24, true);
			wsk2->Write<bool>(swiecacyGracz + (SwiecenieDyn * 0x38) + 0x25, false);
		}

	}
}