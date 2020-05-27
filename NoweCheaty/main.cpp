#include "ProcMem.h"
#include "csgo.hpp"
#include "iostream"
#include "Biblioteki.h"
#include "thread"


int main()
{
	std::thread RADAR(RadarHack);
	std::thread BUNNY(BunnyHop);
	std::thread WH(WH);
	
	RADAR.join();
	BUNNY.join();
	WH.join();
}