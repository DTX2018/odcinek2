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

	
	DWORD SwiecacyGracz{ wsk2->Read<DWORD>(PamiecModul + hazedumper::signatures::dwGlowObjectManager) };
	DWORD ObiektGracza{ wsk2->Read<DWORD>(DWORD(PamiecModul) + DWORD(hazedumper::signatures::dwLocalPlayer)) };

	while (true)
	{
		ObiektGracza = wsk2->Read<DWORD>(DWORD(PamiecModul) + DWORD(hazedumper::signatures::dwLocalPlayer)) ;
		int MojZespol{ wsk2->Read<int>(ObiektGracza + hazedumper::netvars::m_iTeamNum) };

		for (int i = 0; i < 10; i++)
		{
			DWORD ObiektPrzeciwnegoGracza{ wsk2->Read<DWORD>(PamiecModul + hazedumper::signatures::dwEntityList + i * VK_SHIFT) };

			DWORD Swiecenie_Dyn{ wsk2->Read<DWORD>(ObiektPrzeciwnegoGracza + hazedumper::netvars::m_iGlowIndex) };
			DWORD PrzeciwnyZespol{ wsk2->Read<DWORD>(ObiektPrzeciwnegoGracza + hazedumper::netvars::m_iTeamNum) };
			
			if (static_cast<int>(PrzeciwnyZespol) == static_cast<int>(MojZespol))
			{
				wsk2->Write<float>(SwiecacyGracz + (Swiecenie_Dyn * 0x38) + 0x4, 2);
				wsk2->Write<float>(SwiecacyGracz + (Swiecenie_Dyn * 0x38) + 0x10, 0.5);
			}
			else
			{
				wsk2->Write<float>(SwiecacyGracz + (Swiecenie_Dyn * 0x38) + 0x8, 2);
				wsk2->Write<float>(SwiecacyGracz + (Swiecenie_Dyn * 0x38) + 0x10, 0.5);
			}

			wsk2->Write<bool>(SwiecacyGracz + ((Swiecenie_Dyn * 0x38) + 0x24), true);
			wsk2->Write<bool>(SwiecacyGracz + ((Swiecenie_Dyn * 0x38) + 0x25), false);

		}
	}

}