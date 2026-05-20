#pragma once
#include "sdk_types.h"
#include "sdk_accessors.h"

bool show_menu = true;

namespace Offsets
{
	uintptr_t HasItem = 0x0;
	uintptr_t IsVisible = 0x0;
	uintptr_t GetPlayer = 0x0;
	uintptr_t Encrypt = 0x0;
	uintptr_t GetDecrypted = 0x0;
	uintptr_t DServerApi_Call = 0x0;
	void*     isFogOfWar_Field = nullptr;
}

namespace vars
{
	MethodInfo* method = new MethodInfo();

	constexpr int MAX_PLAYERS = 6;
	constexpr int MAX_CARDS = 5;

	bool showTroopCount[MAX_PLAYERS] = { false };
	bool ChangeCardsType[MAX_PLAYERS] = { false };
	int troopCount[MAX_PLAYERS] = { 0 };
	int selectedCards[MAX_PLAYERS][MAX_CARDS] = { {0} };

	bool unlockall = false;
	bool FogOfWar = false;
}
