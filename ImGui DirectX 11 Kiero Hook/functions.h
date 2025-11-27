#pragma once
#include "vec.h"
#include "vec2.h"
#include <string>
#include "il2cpp_resolver.hpp"
#include "Lists.hpp"
#include <intrin.h>
#include <iostream>
#include "il2cpp.h"
#include "sdk.h"
#include <locale>
#include <codecvt>
#include <Windows.h>
#include <unordered_set>
#include <algorithm>


typedef struct System_String_o System_String_o;

namespace utils {
	std::string ConvertToString (Il2CppObject* obj) {
		if (!obj) return "[null]";

		auto str = reinterpret_cast<System_String_o*>(obj);
		int length = str->fields._stringLength;
		if (length <= 0)
			return "[empty]";

		const wchar_t* wideStr = reinterpret_cast<const wchar_t*>(&str->fields._firstChar);

		int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideStr, length, NULL, 0, NULL, NULL);
		if (utf8Len <= 0) return "[convert error]";

		std::string result(utf8Len, 0);
		WideCharToMultiByte(CP_UTF8, 0, wideStr, length, &result[0], utf8Len, NULL, NULL);

		return result;
	}


}




namespace il2cpp {
	// You must resolve this yourself via symbols or manual scanning
	void* (*gc_alloc)(size_t size);  // Make sure to resolve this
}



namespace Functions
{

#pragma region Hooks



	


	
	int32_t Encrypt(int32_t value, int32_t key, MethodInfo* method);
	Player_o* GetPlayer(int32_t index, MethodInfo* method);
	std::string il2cppStringToStdString(System_String_o* str);


	
	

	ImVec4 GetColorFromColorID(System_String_o* colorStr) {
		if (!colorStr) return ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // fallback gray

		std::string color = il2cppStringToStdString(colorStr);
		std::transform(color.begin(), color.end(), color.begin(), ::tolower); 

		if (color == "color_red")       return ImVec4(0.75f, 0.05f, 0.05f, 1.0f);
		if (color == "color_blue")      return ImVec4(0.0f, 0.45f, 0.80f, 1.0f);
		if (color == "color_green")     return ImVec4(0.35f, 0.70f, 0.30f, 1.0f);
		if (color == "color_yellow")    return ImVec4(0.95f, 0.85f, 0.25f, 1.0f);
		if (color == "color_royale")    return ImVec4(0.50f, 0.25f, 0.80f, 1.0f);
		if (color == "color_pink")      return ImVec4(0.90f, 0.50f, 0.70f, 1.0f);
		if (color == "color_orange")    return ImVec4(0.90f, 0.45f, 0.15f, 1.0f);
		if (color == "color_gray")      return ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
		if (color == "color_white")     return ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
		if (color == "color_black")     return ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
		if (color == "color_brown")     return ImVec4(0.4f, 0.2f, 0.1f, 1.0f);
		if (color == "color_lime")      return ImVec4(0.6f, 0.8f, 0.2f, 1.0f);
		if (color == "color_turquoise") return ImVec4(0.2f, 0.8f, 0.8f, 1.0f);
		if (color == "color_azure")     return ImVec4(0.3f, 0.6f, 1.0f, 1.0f);

		// Fallback
		return ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	}


	

	

	std::unordered_set<Territory_o*> g_Territories;

	bool(__fastcall* Territory__IsVisible)(Territory_o* ,  MethodInfo* );
	bool Territory__IsVisible_hk(Territory_o* __this,  MethodInfo* method) {

		if (GetPlayer(0, vars::method)) {
			if (__this) {
				g_Territories.insert(__this);
			}
		}
		if (!GetPlayer(0, vars::method))
		{
			g_Territories.clear();
		}

		return Territory__IsVisible(__this,method);
	}



	typedef uint16_t Il2CppChar;


	std::string il2cppStringToStdString(System_String_o* str) {
		if (!str || str->fields._stringLength == 0) {
			return "";
		}

		Il2CppChar* chars = &str->fields._firstChar;
		std::string result;

		for (int i = 0; i < str->fields._stringLength; i++) {
			uint16_t ch = chars[i];

			if (ch < 0x80) {
				result += (char)ch;
			}
			else if (ch < 0x800) {
				result += (char)(0xC0 | (ch >> 6));
				result += (char)(0x80 | (ch & 0x3F));
			}
			else {
				result += (char)(0xE0 | (ch >> 12));
				result += (char)(0x80 | ((ch >> 6) & 0x3F));
				result += (char)(0x80 | (ch & 0x3F));
			}
		}

		return result;
	}




	void log_dict(System_Collections_Generic_Dictionary_string__object__o* dict) {

		if (dict) {



			int count = dict->fields._count;
			auto entries = dict->fields._entries;

			for (int i = 0; i < count; ++i) {
				auto& entry = entries->m_Items[i].fields;

				if (entry.hashCode < 0) continue;

				Il2CppObject* keyStr = entry.key;
				Il2CppObject* valueObj = entry.value;

				std::string key = utils::ConvertToString(keyStr);
				std::string value = utils::ConvertToString(valueObj); 
				std::cout << "[loadedData][" << key << "] = " << value << "\n";
			}

		}
	}
	
	void DumpDictionary(System_Collections_Generic_Dictionary_string__object__o* dict) {
		if (!dict || !dict->fields._entries || !dict->fields._entries->m_Items) {
			printf("[DumpDictionary] Dictionary is null or empty.\n");
			return;
		}

		int count = dict->fields._entries->max_length;
		for (int i = 0; i < count; ++i) {
			auto& entry = dict->fields._entries->m_Items[i];
			if (!entry.fields.key || !entry.fields.value || entry.fields.hashCode < 0) continue;

			auto keyStr = reinterpret_cast<System_String_o*>(entry.fields.key);
			std::string key = il2cppStringToStdString(keyStr);

			Il2CppObject* val = entry.fields.value;
			Il2CppClass* klass = val->klass;
			std::string typeName = klass->_1.name;

			printf("[Dump] Key: %s | Type: %s | ", key.c_str(), typeName.c_str());

			if (typeName == "String") {
				auto strVal = reinterpret_cast<System_String_o*>(val);
				std::string value = il2cppStringToStdString(strVal);
				printf("Value: %s\n", value.c_str());
			}
			else if (typeName == "Int64") {
				int64_t longVal = *reinterpret_cast<int64_t*>((uintptr_t)val + sizeof(Il2CppObject));
				printf("Value: %lld\n", longVal);
			}
			else if (typeName == "Int32") {
				int32_t intVal = *reinterpret_cast<int32_t*>((uintptr_t)val + sizeof(Il2CppObject));
				printf("Value: %d\n", intVal);
			}
			else if (typeName.find("Dictionary") != std::string::npos) {
				printf("Value: (Nested Dictionary)\n");
			}
			else {
				printf("Value: (Unknown type or complex object)\n");
			}
		}
	}




	void(__thiscall* DServerApi__Call__org)(DServerApi_o*, DServerApi_delegateLoaded_o*, System_Collections_Generic_Dictionary_string__object__o*, MethodInfo*);
	void  __fastcall DServerApi__Call__hk(DServerApi_o* __this, DServerApi_delegateLoaded_o* OnLoadedCall, System_Collections_Generic_Dictionary_string__object__o* parameters, MethodInfo* method) {

		if (vars::unlockall) {


			if (!parameters || !parameters->fields._entries || !parameters->fields._entries->m_Items) {
				DServerApi__Call__org(__this, OnLoadedCall, parameters, method);
				return;
			}

			int count = parameters->fields._entries->max_length;
			std::string typeVal;

			for (int i = 0; i < count; ++i) {
				auto& entry = parameters->fields._entries->m_Items[i];
				if (!entry.fields.key || !entry.fields.value || entry.fields.hashCode < 0) continue;

				auto keyStr = reinterpret_cast<System_String_o*>(entry.fields.key);
				std::string key = il2cppStringToStdString(keyStr);

				Il2CppObject* val = entry.fields.value;
				Il2CppClass* klass = val->klass;
				std::string typeName = klass->_1.name;

				if (key == "type" && typeName == "String") {
					typeVal = il2cppStringToStdString(reinterpret_cast<System_String_o*>(val));
				}

				if (key == "id" && typeName == "String") {
					const char* spoofed = nullptr;

					if (typeVal == "troop") spoofed = "troop_classic_stance_idle";
					else if (typeVal == "dice") spoofed = "dice_classicDefault_base_red";
					else if (typeVal == "colour") spoofed = "color_red";
					else if (typeVal == "frame") spoofed = "frame_classic";
					else if (typeVal == "avatar") spoofed = "AVATAR 1-M-FR";

					if (spoofed) {
						entry.fields.value = reinterpret_cast<Il2CppObject*>(IL2CPP::String::New(spoofed));
					}
				}

				if (key == "gameConfig" && typeName == "String") {
					std::string valStr = il2cppStringToStdString(reinterpret_cast<System_String_o*>(val));

					const char* fixed = "custom_classic";
					entry.fields.value = reinterpret_cast<Il2CppObject*>(IL2CPP::String::New(fixed));

				}
				if ((key == "fogOfWar" || key == "blockers" || key == "portalsMode") && typeName == "Int32") {
					int32_t* valPtr = reinterpret_cast<int32_t*>((uintptr_t)val + sizeof(Il2CppObject));
					*valPtr = 0;
				}

			}



			DServerApi__Call__org(__this, OnLoadedCall, parameters, method);

		}
		else
		{
			DServerApi__Call__org(__this, OnLoadedCall, parameters, method);

		}

	}


	


	// unlock all
	bool (__thiscall* RiskInventory__HasItem_org) (RiskInventory_o* , System_String_o*,  MethodInfo* );
	bool   RiskInventory__HasItem_hk(RiskInventory_o* __this, System_String_o* id,  MethodInfo* method) {


		if (vars::unlockall) {
						


			return true;

		}
		else return RiskInventory__HasItem_org(__this, id, method);
	}




#pragma endregion

#pragma region Game Functions
	

	Player_o* GetPlayer(int32_t index, MethodInfo* method) {
		Player_o* (UNITY_CALLING_CONVENTION t)(int32_t, MethodInfo*);
		return reinterpret_cast<decltype(t)>(Offsets::GetPlayer)(index, method);
	}

	int32_t Encrypt(int32_t value, int32_t key, MethodInfo* method) {

		int32_t (UNITY_CALLING_CONVENTION t)(int32_t, int32_t, MethodInfo*);
		return reinterpret_cast<decltype(t)>(Offsets::Encrypt)(value,key,method);

	}

	int32_t Getdecrypted(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o __this, MethodInfo* method) {

		int32_t(UNITY_CALLING_CONVENTION t)(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o, MethodInfo*);
		return reinterpret_cast<decltype(t)>(Offsets::GetDecrypted)(__this, method);
	}

	
	uintptr_t GetFogOfWarOffset()
	{
		uintptr_t GameManager_c = *(uintptr_t*)(sdk::GameAssembly + 44218808);	 //GameManager_TypeInfo

		if (!GameManager_c) return 0;

		uintptr_t StaticFields = *(uintptr_t*)(GameManager_c + 0xB8);
		if (!StaticFields) return 0;

		return StaticFields + 0x16;
	}


	void ModifyFogOfWar(bool enable)
	{
		uintptr_t address = GetFogOfWarOffset();
		if (!address) return;

		*(uint8_t*)address = enable ? 1 : 0;
	}


	bool GetFogOfWar()
	{
		uintptr_t address = GetFogOfWarOffset();
		if (!address) return false;

		return *(uint8_t*)address;
	}





	
	

	void changePlayerTroops(int playerIndex, int amountOfTroops) {

		auto player = GetPlayer(playerIndex, vars::method);
		if (player != nullptr) {
			player->fields._units.fields.hiddenValue = Encrypt(amountOfTroops, player->fields._units.fields.currentCryptoKey, vars::method);
		}

	}
	int getPlayerTroopAmount(int playerIndex) {

		auto player = GetPlayer(playerIndex, vars::method);

		if (player != nullptr) {
			return Getdecrypted(player->fields._units, vars::method);
		}
		else return 0; 
	
	}

	const char* getplayername(int index) {

		auto player = Functions::GetPlayer(index, vars::method);
		if (player != nullptr){

		System_String_o* playername = player->fields._name;



		std::string name1 = "Player " + std::to_string(index + 1) + " : " + il2cppStringToStdString(playername);

		return name1.c_str();
		}
		else {
			std::string name1 = "Player " + std::to_string(index + 1) + " : ?????? " ;
			return name1.c_str();


		}

	}

	void ChangePlayerCard(int PlayerIndex, int CardIndex, int CardType) {

		auto player = Functions::GetPlayer(PlayerIndex, vars::method);

		if (player != nullptr) {
			auto playerCard = Functions::GetPlayer(PlayerIndex, vars::method)->fields.cards->fields._items->m_Items[CardIndex];

			if (playerCard != nullptr) {
				playerCard->fields.type = CardType;

			}
		}
		

	}


	 int ReturnPlayerCard(int PlayerIndex, int CardIndex) {

		auto player = Functions::GetPlayer(PlayerIndex, vars::method);

		if (player != nullptr) {
			auto playerCard = Functions::GetPlayer(PlayerIndex, vars::method)->fields.cards->fields._items->m_Items[CardIndex];

			if (playerCard != nullptr) {

				return playerCard->fields.type;
			}
			

		}
		

	}














#pragma endregion

}aaa
