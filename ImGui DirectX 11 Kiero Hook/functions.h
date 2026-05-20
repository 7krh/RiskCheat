#pragma once
#include <string>
#include <unordered_set>
#include <algorithm>
#include "il2cpp_resolver.hpp"
#include "sdk.h"
#include "il2cpp_exports.h"
#include "sdk_accessors.h"
#include <imgui/imgui.h>

namespace Functions
{

#pragma region Hooks

    int32_t Encrypt(int32_t value, int32_t key, MethodInfo* method);
    Player_o* GetPlayer(int32_t index, MethodInfo* method);

    inline std::string il2cppStringToStdString(System_String_o* str) {
        return sdk::string_to_std(str);
    }

    inline ImVec4 GetColorFromColorID(System_String_o* colorStr) {
        if (!colorStr) return ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        std::string color = sdk::string_to_std(colorStr);
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

        return ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
    }

    inline std::unordered_set<Territory_o*> g_Territories;

    inline bool(__fastcall* Territory__IsVisible)(Territory_o*, MethodInfo*);
    inline bool Territory__IsVisible_hk(Territory_o* __this, MethodInfo* method) {
        if (GetPlayer(0, vars::method)) {
            if (__this) g_Territories.insert(__this);
        } else {
            g_Territories.clear();
        }
        return Territory__IsVisible(__this, method);
    }

    inline void(__fastcall* DServerApi__Call__org)(DServerApi_o*, DServerApi_delegateLoaded_o*, void*, MethodInfo*);
    inline void __fastcall DServerApi__Call__hk(DServerApi_o* __this, DServerApi_delegateLoaded_o* OnLoadedCall, void* parameters, MethodInfo* method) {

        if (!vars::unlockall || !parameters || !sdk::resolve_dict_entry_layout(parameters)) {
            DServerApi__Call__org(__this, OnLoadedCall, parameters, method);
            return;
        }

        void* entries = sdk::field_get<void*>(parameters, Offsets::Game.Dict_entries);
        if (!entries) {
            DServerApi__Call__org(__this, OnLoadedCall, parameters, method);
            return;
        }

        const uint32_t n = sdk::array_length(entries);
        char* data = reinterpret_cast<char*>(sdk::array_data(entries));
        const int es = Offsets::Game.DictEntry_size;

        std::string typeVal;
        for (uint32_t i = 0; i < n; ++i) {
            char* entry = data + i * es;

            int hash = sdk::field_get<int>(entry, Offsets::Game.DictEntry_hashCode);
            if (hash < 0) continue;

            auto* keyStr = sdk::field_get<System_String_o*>(entry, Offsets::Game.DictEntry_key);
            void* v      = sdk::field_get<void*>(entry, Offsets::Game.DictEntry_value);
            if (!keyStr || !v) continue;

            int32_t klen = sdk::field_get<int32_t>(keyStr, Offsets::Game.String_length);
            if (klen < 2 || klen > 20) continue;

            const uint16_t* kch = reinterpret_cast<const uint16_t*>(
                reinterpret_cast<char*>(keyStr) + Offsets::Game.String_firstChar);

            auto eq = [&](const char* s, int len) {
                if (klen != len) return false;
                for (int i = 0; i < len; ++i) if (kch[i] != (uint16_t)s[i]) return false;
                return true;
            };

            const bool isType       = eq("type", 4);
            const bool isId         = eq("id", 2);
            const bool isGameConfig = eq("gameConfig", 10);
            const bool isFog        = eq("fogOfWar", 8);
            const bool isBlockers   = eq("blockers", 8);
            const bool isPortals    = eq("portalsMode", 11);
            if (!(isType || isId || isGameConfig || isFog || isBlockers || isPortals))
                continue;

            const char* tn = sdk::object_class_name(v);
            if (!tn) continue;
            const bool isStr = strcmp(tn, "String") == 0;
            const bool isI32 = strcmp(tn, "Int32") == 0;

            if (isType && isStr) {
                typeVal = sdk::string_to_std(reinterpret_cast<System_String_o*>(v));
            } else if (isId && isStr) {
                const char* spoofed = nullptr;
                if      (typeVal == "troop")  spoofed = "troop_classic_stance_idle";
                else if (typeVal == "dice")   spoofed = "dice_classicDefault_base_red";
                else if (typeVal == "colour") spoofed = "color_red";
                else if (typeVal == "frame")  spoofed = "frame_classic";
                else if (typeVal == "avatar") spoofed = "AVATAR 1-M-FR";
                if (spoofed)
                    sdk::field_set<void*>(entry, Offsets::Game.DictEntry_value, sdk::string_new(spoofed));
            } else if (isGameConfig && isStr) {
                sdk::field_set<void*>(entry, Offsets::Game.DictEntry_value, sdk::string_new("custom_classic"));
            } else if ((isFog || isBlockers || isPortals) && isI32) {
                const size_t header = sizeof(void*) * 2;
                *reinterpret_cast<int32_t*>(reinterpret_cast<char*>(v) + header) = 0;
            }
        }

        DServerApi__Call__org(__this, OnLoadedCall, parameters, method);
    }

    inline bool (__fastcall* RiskInventory__HasItem_org)(RiskInventory_o*, System_String_o*, MethodInfo*);
    inline bool RiskInventory__HasItem_hk(RiskInventory_o* __this, System_String_o* id, MethodInfo* method) {
        if (vars::unlockall) return true;
        return RiskInventory__HasItem_org(__this, id, method);
    }

#pragma endregion

#pragma region Game Functions

    inline Player_o* GetPlayer(int32_t index, MethodInfo* method) {
        if (!Offsets::GetPlayer) return nullptr;
        Player_o* (UNITY_CALLING_CONVENTION t)(int32_t, MethodInfo*);
        return reinterpret_cast<decltype(t)>(Offsets::GetPlayer)(index, method);
    }

    inline int32_t Encrypt(int32_t value, int32_t key, MethodInfo* method) {
        if (!Offsets::Encrypt) return value ^ key;
        int32_t(UNITY_CALLING_CONVENTION t)(int32_t, int32_t, MethodInfo*);
        return reinterpret_cast<decltype(t)>(Offsets::Encrypt)(value, key, method);
    }

    inline int32_t GetDecrypted(void* obscuredInt_ptr, MethodInfo* method) {
        if (!obscuredInt_ptr || !Offsets::GetDecrypted) return 0;
        int32_t(UNITY_CALLING_CONVENTION t)(void*, MethodInfo*);
        return reinterpret_cast<decltype(t)>(Offsets::GetDecrypted)(obscuredInt_ptr, method);
    }

    inline void ModifyFogOfWar(bool enable) {
        if (!Offsets::isFogOfWar_Field || !il2cpp_exp::field_static_set_value) return;
        uint8_t v = enable ? 1 : 0;
        il2cpp_exp::field_static_set_value(Offsets::isFogOfWar_Field, &v);
    }

    inline bool GetFogOfWar() {
        if (!Offsets::isFogOfWar_Field || !il2cpp_exp::field_static_get_value) return false;
        uint8_t v = 0;
        il2cpp_exp::field_static_get_value(Offsets::isFogOfWar_Field, &v);
        return v != 0;
    }

    inline void changePlayerTroops(int playerIndex, int amountOfTroops) {
        auto player = GetPlayer(playerIndex, vars::method);
        if (!player) return;
        int key = sdk::Player_currentCryptoKey(player);
        sdk::Player_set_hiddenValue(player, Encrypt(amountOfTroops, key, vars::method));
    }

    inline int getPlayerTroopAmount(int playerIndex) {
        auto player = GetPlayer(playerIndex, vars::method);
        if (!player || Offsets::Game.Player_units < 0 || !Offsets::GetDecrypted) return 0;
        void* unitsPtr = reinterpret_cast<char*>(player) + Offsets::Game.Player_units;
        return GetDecrypted(unitsPtr, vars::method);
    }

    inline const char* getplayername(int index) {
        static thread_local std::string buf;
        auto player = GetPlayer(index, vars::method);
        if (player) {
            buf = "Player " + std::to_string(index + 1) + " : " + sdk::string_to_std(sdk::Player_name(player));
        } else {
            buf = "Player " + std::to_string(index + 1) + " : ?????? ";
        }
        return buf.c_str();
    }

    inline void ChangePlayerCard(int PlayerIndex, int CardIndex, int CardType) {
        auto player = GetPlayer(PlayerIndex, vars::method);
        if (!player) return;
        auto card = sdk::Player_card_at(player, CardIndex);
        if (card) sdk::RiskCard_set_Type(card, CardType);
    }

    inline int ReturnPlayerCard(int PlayerIndex, int CardIndex) {
        auto player = GetPlayer(PlayerIndex, vars::method);
        if (!player) return 0;
        auto card = sdk::Player_card_at(player, CardIndex);
        return card ? sdk::RiskCard_Type(card) : 0;
    }

#pragma endregion

}
