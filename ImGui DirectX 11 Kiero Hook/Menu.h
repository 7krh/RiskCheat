#pragma once
#include "imgui/imgui.h"
#include "sdk.h"
#include "functions.h"
#include "Dumper.hpp"
#include "Lists.hpp"
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace ImGui;

void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("[?]");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ImGuiTheme2()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.WindowRounding = 4;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
}

// Helper function to handle card changes  
void HandleCardChange(int playerIndex, int cardIndex, int cardType)
{
	Functions::ChangePlayerCard(playerIndex, cardIndex, cardType);
	vars::selectedCards[playerIndex][cardIndex] = Functions::ReturnPlayerCard(playerIndex, cardIndex);
}

//  Helper function to render troop controls for a player
void RenderTroopControls(int playerIndex)
{
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 160, 255));
	ImGui::Text("Troops");
	ImGui::PopStyleColor();

	// Create unique checkbox ID
	char checkboxLabel[64];
	snprintf(checkboxLabel, sizeof(checkboxLabel), "Change Troop Count##%d", playerIndex + 1);

	ImGui::Checkbox(checkboxLabel, &vars::showTroopCount[playerIndex]);

	if (vars::showTroopCount[playerIndex]) {
		ImGui::SameLine();
		ImGui::PushItemWidth(100);

		// Create unique input ID
		char inputLabel[32];
		snprintf(inputLabel, sizeof(inputLabel), "##%d", playerIndex + 1);
		ImGui::InputInt(inputLabel, &vars::troopCount[playerIndex]);

		ImGui::SameLine();

		// Create unique button ID
		char buttonLabel[32];
		snprintf(buttonLabel, sizeof(buttonLabel), "Set##%d", playerIndex + 1);
		if (ImGui::Button(buttonLabel)) {
			Functions::changePlayerTroops(playerIndex, vars::troopCount[playerIndex]);
			vars::troopCount[playerIndex] = Functions::getPlayerTroopAmount(playerIndex);
		}

		ImGui::Text("Troop Count is: %d", Functions::getPlayerTroopAmount(playerIndex));
	}
}

//  Helper function to render card controls for a player
void RenderCardControls(int playerIndex)
{
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 149, 255, 255));
	ImGui::Text("Cards");
	ImGui::PopStyleColor();

	// Create unique checkbox ID
	char checkboxLabel[64];
	snprintf(checkboxLabel, sizeof(checkboxLabel), "Change Cards Type##%d", playerIndex + 1);

	ImGui::Checkbox(checkboxLabel, &vars::ChangeCardsType[playerIndex]);

	if (vars::ChangeCardsType[playerIndex]) {
		const char* cardTypes[] = { "Wild", "Infantry", "Cavalry", "Artillery" };

		// Loop through all 5 cards
		for (int cardIndex = 0; cardIndex < vars::MAX_CARDS; cardIndex++) {
			ImGui::Text("Card %d Type :", cardIndex + 1);
			ImGui::SameLine(110);
			ImGui::SetNextItemWidth(100);

			// Create unique combo ID
			char comboLabel[64];
			snprintf(comboLabel, sizeof(comboLabel), "##CardType%d##%d", cardIndex + 1, playerIndex + 1);
			ImGui::Combo(comboLabel, &vars::selectedCards[playerIndex][cardIndex], cardTypes, IM_ARRAYSIZE(cardTypes));

			ImGui::SameLine(220);

			// Create unique button ID
			char buttonLabel[64];
			snprintf(buttonLabel, sizeof(buttonLabel), "Set##%d%d", cardIndex + 1, playerIndex + 1);
			if (ImGui::Button(buttonLabel)) {
				HandleCardChange(playerIndex, cardIndex, vars::selectedCards[playerIndex][cardIndex]);
			}
		}

		//  Handle player card validation in loop
		auto player = Functions::GetPlayer(playerIndex, vars::method);
		if (player != nullptr) {
			for (int cardIndex = 0; cardIndex < vars::MAX_CARDS; cardIndex++) {
				auto playerCard = Functions::GetPlayer(playerIndex, vars::method)->fields.cards->fields._items->m_Items[cardIndex];

				if (playerCard == nullptr) {
					vars::selectedCards[playerIndex][cardIndex] = Functions::ReturnPlayerCard(playerIndex, cardIndex);
				}
				else if (cardIndex == 2) { 
					if (playerCard->fields.type != 0 && playerCard->fields.type != 1 &&
						playerCard->fields.type != 2 && playerCard->fields.type != 3) {
						vars::selectedCards[playerIndex][cardIndex] = Functions::ReturnPlayerCard(playerIndex, cardIndex);
					}
				}
			}
		}
	}
}



inline void DrawSectionHeader(const char* text) {
	ImVec2 textSize = CalcTextSize(text);
	float posX = (GetWindowSize().x - textSize.x) * 0.5f;

	Separator();
	SetCursorPosX(posX);
	TextColored({ 0.2f, 1.0f, 0.2f, 1.0f }, text);
	Separator();
}

 void DrawTerritoriesTab() {
	using namespace vars;
	static char searchBuf[128] = "";
	static Territory_o* giveToPlayerExpanded = nullptr;
	static Territory_o* expanded = nullptr;
	static std::unordered_map<std::string, int> troopInputs;
	static bool giveAllExpanded = false;

	InputTextWithHint("##search", "Search territories...", searchBuf, IM_ARRAYSIZE(searchBuf));
	SameLine(); Text("Total: %d", (int)Functions::g_Territories.size());
	Separator();

	if (Button("Give All Territories (instant win)")) giveAllExpanded = !giveAllExpanded;
	if (giveAllExpanded) {
		Indent();
		TextColored({ 1,0,0,1 }, "Choose a player:");
		for (int i = 0; i < 6; i++) {
			if (auto* p = Functions::GetPlayer(i, method)) {
				PushStyleColor(ImGuiCol_Button, Functions::GetColorFromColorID(p->fields.colorID));
				if (Button(Functions::getplayername(i), { -1,0 }))
					for (auto& t : Functions::g_Territories) if (t) t->fields._player = p;
				PopStyleColor();
			}
		}
		if (Functions::GetPlayer(0, method)) {
			PushStyleColor(ImGuiCol_Button, { 0.3f,0.3f,0.3f,1 });
			if (Button("No One", { -1,0 }))
				for (auto& t : Functions::g_Territories) if (t) t->fields._player = nullptr;
			PopStyleColor();
		}
		Unindent(); Separator();
	}

	BeginChild("TerritoryList", { 0,350 }, true, ImGuiWindowFlags_HorizontalScrollbar);
	Columns(2, nullptr, false);

	std::set<std::string> shown;
	std::string search = searchBuf;
	std::transform(search.begin(), search.end(), search.begin(), ::tolower);

	for (auto& t : Functions::g_Territories) {
		if (!t || !t->fields.name) continue;
		std::string name = Functions::il2cppStringToStdString(t->fields.name);
		std::string cmp = name; std::transform(cmp.begin(), cmp.end(), cmp.begin(), ::tolower);
		if (!search.empty() && cmp.find(search) == std::string::npos) continue;
		if (!shown.insert(name).second) continue;

		ImVec4 color = t->fields._player ? Functions::GetColorFromColorID(t->fields._player->fields.colorID) : ImVec4(0.4f, 0.4f, 0.4f, 1);
		std::string id = std::to_string((uintptr_t)t);

		PushStyleColor(ImGuiCol_Button, color);
		Button((name + "##name" + id).c_str(), { -1,0 });
		PopStyleColor(); NextColumn();

		if (Button(("Properties##" + id).c_str(), { -1,0 }))
			expanded = (expanded == t) ? nullptr : t;
		NextColumn();

		if (expanded == t) {
			Columns(1); Indent(); Separator();
			if (Button(("Toggle Capital##" + id).c_str())) t->fields._isCapital = !t->fields._isCapital;

			Separator();
			int& local = troopInputs[id];
			InputInt(("##TroopInput" + id).c_str(), &local);
			SameLine();
			if (Button(("Set Troops##" + id).c_str())) {
				t->fields._units.fields.hiddenValue = Functions::Encrypt(local, t->fields._units.fields.currentCryptoKey, method);
				local = 0;
			}

			Separator();
			if (Button(("Give Territory##" + id).c_str()))
				giveToPlayerExpanded = (giveToPlayerExpanded == t) ? nullptr : t;

			if (giveToPlayerExpanded == t) {
				Indent(); Separator(); TextColored({ 1,0,0,1 }, "Give this territory to:");
				for (int i = 0; i < 6; i++) {
					if (auto* p = Functions::GetPlayer(i, method)) {
						PushStyleColor(ImGuiCol_Button, Functions::GetColorFromColorID(p->fields.colorID));
						if (Button(Functions::getplayername(i), { -1,0 })) { t->fields._player = p; giveToPlayerExpanded = nullptr; }
						PopStyleColor();
					}
				}
				PushStyleColor(ImGuiCol_Button, { 0.3f,0.3f,0.3f,1 });
				if (Button(("No One##" + id).c_str(), { -1,0 })) { t->fields._player = nullptr; giveToPlayerExpanded = nullptr; }
				PopStyleColor();
				Unindent(); Separator();
			}
			Unindent(); Columns(2, nullptr, false);
		}
	}

	Columns(1); EndChild();
}

 void DrawUnlockAllTab() {
	using namespace vars;
	DrawSectionHeader("UnlockAll");
	Checkbox("UnlockAll##12", &unlockall);
}


void DrawMenu()
{
	using namespace vars;
	ImGuiTheme2();
	static int page = 0;

	if (ImGui::Begin(" 7krh ", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::GetIO().MouseDrawCursor = true;
		ImGui::GetIO().WantCaptureMouse = true;
		ImGui::GetIO().WantCaptureKeyboard = true;

		ImGui::SetWindowPos(ImVec2(500, 500), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(375, 400), ImGuiCond_Once);

		static int tabb = 0;
		const char* tabNames[] = { "game", "Territories", "UnlockAll##22" };
		int numTabs = IM_ARRAYSIZE(tabNames);
		float fullWidth = ImGui::GetContentRegionAvail().x;
		float tabWidth = fullWidth / numTabs;

		for (int i = 0; i < numTabs; ++i)
		{
			if (tabb == i)
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 0.25f));
			else
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.25f));

			if (ImGui::Button(tabNames[i], ImVec2(tabWidth, 0))) {
				tabb = i;
			}

			ImGui::PopStyleColor();

			if (i < numTabs - 1)
				ImGui::SameLine();
		}

		ImGui::Separator();
		ImGui::Separator();

		switch (tabb) {
		case 0: {
			// FogOfWar Section
			const char* header1 = "FogOfWar";
			ImVec2 textSize1 = ImGui::CalcTextSize(header1);
			float windowWidth1 = ImGui::GetWindowSize().x;
			float textPosX1 = (windowWidth1 - textSize1.x) * 0.5f;
			ImGui::Separator();
			ImGui::SetCursorPosX(textPosX1);
			ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), header1);
			ImGui::Separator();

			ImGui::Checkbox("FogOfWar", &FogOfWar);

			if (FogOfWar) {
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.4f, 1.0f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.5f, 1.0f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.3f, 0.9f, 1.0f));

				if (ImGui::Button("Enable FogOfWar ")) {
					Functions::ModifyFogOfWar(1);
				}
				ImGui::PopStyleColor(3);
				ImGui::SameLine(135);

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.4f, 1.0f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.5f, 1.0f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.3f, 0.9f, 1.0f));

				if (ImGui::Button("Disable FogOfWar ")) {
					Functions::ModifyFogOfWar(0);
				}
				ImGui::PopStyleColor(3);

				bool FogOfWar1 = Functions::GetFogOfWar();
				if (FogOfWar1) {
					ImGui::Text("FogOfWar is: Enabled ");
				}
				else {
					ImGui::Text("FogOfWar is: Disabled ");
				}
			}

			// Troops & Cards Section
			const char* header = "Troops & Cards";
			ImVec2 textSize = ImGui::CalcTextSize(header);
			float windowWidth = ImGui::GetWindowSize().x;
			float textPosX = (windowWidth - textSize.x) * 0.5f;

			ImGui::Separator();
			ImGui::SetCursorPosX(textPosX);
			ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), header);
			ImGui::Separator();

			// Enhanced: Loop through all players instead of duplicating code
			for (int playerIndex = 0; playerIndex < MAX_PLAYERS; playerIndex++) {
				if (Functions::GetPlayer(playerIndex, vars::method)) {
					if (ImGui::CollapsingHeader(Functions::getplayername(playerIndex))) {
						RenderTroopControls(playerIndex);
						RenderCardControls(playerIndex);
					}
				}
			}
			break;
		}
		case 1: {
			DrawTerritoriesTab();
			break;
		}
		case 2: {
			DrawUnlockAllTab();
			break;
		}
		}
	}
	ImGui::End();
}