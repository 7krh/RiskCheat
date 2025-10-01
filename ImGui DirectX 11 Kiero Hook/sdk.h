#pragma once
#include "il2cpp.h"
#include "vec.h"
#include "vec2.h"
#include <vector>
#include <utility> // for std::pair
#include <imgui/imgui.h>

bool show_menu = true;

// read write 
namespace mem
{
	template<typename T> T read(uintptr_t address) {
		try { return *(T*)address; }
		catch (...) { return T(); }
	}

	template<typename T> void write(uintptr_t address, T value) {
		try { *(T*)address = value; }
		catch (...) { return; }
	}
}

namespace sdk
{
	uint32_t* g_TroopLoss = nullptr;
	uintptr_t Base;
	uintptr_t GameAssembly;
	uintptr_t UnityPlayer;

	uintptr_t g_injectionPoint = 0;
	uintptr_t g_returnAddress = 0;
	BYTE originalBytes[6];
	uintptr_t g_patchAddress = 0;
}

namespace Offsets
{
	uintptr_t HasItem = 0x0;
	uintptr_t IsVisible = 0x0;
	uintptr_t GetPlayer = 0x0;
	uintptr_t Encrypt = 0x0;
	uintptr_t GetDecrypted = 0x0;
	uintptr_t fogOfWarOffset = 0x0;
	uintptr_t GameManager = 0x0;

}

namespace vars
{
	static Territory_o* selectedTerritory = nullptr;
	static bool openProperties = false;
	static Territory_o* expandedTerritory = nullptr;

	MethodInfo* method = new MethodInfo();

	constexpr int MAX_PLAYERS = 6;
	constexpr int MAX_CARDS = 5;

	bool showTroopCount[MAX_PLAYERS] = { false };
	bool ChangeCardsType[MAX_PLAYERS] = { false };
	int troopCount[MAX_PLAYERS] = { 0 };

	int selectedCards[MAX_PLAYERS][MAX_CARDS] = { {0} };

	bool unlockall = false;
	bool FogOfWar = false;

	static Territory_o* giveToPlayerExpanded = nullptr;
	static bool giveAllExpanded = false;
	static int troopAmount = 0;

	inline static UINT vps = 1;
	Vector2 screen_size = { 0, 0 };
	Vector2 screen_center = { 0, 0 };
	D3D11_VIEWPORT viewport;
	bool initil2cpp = false;

	bool crosshairRainbow = false;
	bool watermark = true;

	// Colors
	ImColor CrossColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor PlayerNameColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor skeletonESPCol = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor PlayerSnaplineColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor PlayerHealthbarColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor SelfChamsColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor ChamsColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor ItemNameColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor ItemSnaplineColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor boxESPCol = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor hitdebugcol = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImVec4 Rainbow = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	Vector3 PlayerPos = { 0, 0, 0 };
}