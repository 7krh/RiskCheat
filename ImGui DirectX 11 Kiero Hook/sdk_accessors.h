#pragma once
#include <cstdint>
#include <string>
#include "sdk_types.h"
#include "il2cpp_exports.h"

namespace Offsets {
    struct GameOff {
        int Player_name = -1;
        int Player_units = -1;
        int Player_colorID = -1;
        int Player_cards = -1;

        int Territory_name = -1;
        int Territory_player = -1;
        int Territory_isCapital = -1;
        int Territory_units = -1;

        int RiskCard_Type = -1;

        int Obscured_hiddenValue = -1;
        int Obscured_currentCryptoKey = -1;

        int String_length = -1;
        int String_firstChar = -1;

        int Dict_entries = -1;
        int Dict_count = -1;

        int DictEntry_key = -1;
        int DictEntry_value = -1;
        int DictEntry_hashCode = -1;
        int DictEntry_size = -1;

        int List_items = -1;
        int List_size = -1;
    };
    inline GameOff Game;
}

namespace sdk {

template<typename T>
inline T field_get(void* o, int off) {
    return *reinterpret_cast<T*>(reinterpret_cast<char*>(o) + off);
}

template<typename T>
inline void field_set(void* o, int off, T v) {
    *reinterpret_cast<T*>(reinterpret_cast<char*>(o) + off) = v;
}

template<typename T>
inline T safe_get(void* o, int off, T fallback = T{}) {
    if (!o || off < 0) return fallback;
    return field_get<T>(o, off);
}

template<typename T>
inline bool safe_set(void* o, int off, T v) {
    if (!o || off < 0) return false;
    field_set<T>(o, off, v);
    return true;
}

inline void* object_class(void* obj) {
    if (!obj || !il2cpp_exp::object_get_class) return nullptr;
    return il2cpp_exp::object_get_class(obj);
}

inline const char* object_class_name(void* obj) {
    void* k = object_class(obj);
    if (!k || !il2cpp_exp::class_get_name) return nullptr;
    return il2cpp_exp::class_get_name(k);
}

inline uint32_t array_length(void* arr) {
    if (!arr || !il2cpp_exp::array_length) return 0;
    return il2cpp_exp::array_length(arr);
}

inline void* array_data(void* arr) {
    if (!arr) return nullptr;
    return reinterpret_cast<char*>(arr) + 0x20;
}

template<typename T>
inline T array_get(void* arr, int i) {
    if (!arr || i < 0 || (uint32_t)i >= array_length(arr)) return T{};
    return reinterpret_cast<T*>(array_data(arr))[i];
}

inline System_String_o* string_new(const char* utf8) {
    if (!utf8 || !il2cpp_exp::string_new) return nullptr;
    return reinterpret_cast<System_String_o*>(il2cpp_exp::string_new(utf8));
}

std::string string_to_std(System_String_o* s);

inline System_String_o* Player_name(Player_o* p)         { return safe_get<System_String_o*>(p, Offsets::Game.Player_name, nullptr); }
inline System_String_o* Player_colorID(Player_o* p)      { return safe_get<System_String_o*>(p, Offsets::Game.Player_colorID, nullptr); }
inline void*            Player_cards(Player_o* p)        { return safe_get<void*>(p, Offsets::Game.Player_cards, nullptr); }

inline int  Player_currentCryptoKey(Player_o* p) {
    if (!p || Offsets::Game.Player_units < 0 || Offsets::Game.Obscured_currentCryptoKey < 0) return 0;
    return field_get<int>(p, Offsets::Game.Player_units + Offsets::Game.Obscured_currentCryptoKey);
}
inline bool Player_set_hiddenValue(Player_o* p, int v) {
    if (!p || Offsets::Game.Player_units < 0 || Offsets::Game.Obscured_hiddenValue < 0) return false;
    field_set<int>(p, Offsets::Game.Player_units + Offsets::Game.Obscured_hiddenValue, v);
    return true;
}

inline System_String_o* Territory_name(Territory_o* t)         { return safe_get<System_String_o*>(t, Offsets::Game.Territory_name, nullptr); }
inline Player_o*        Territory_player(Territory_o* t)       { return safe_get<Player_o*>(t, Offsets::Game.Territory_player, nullptr); }
inline bool Territory_set_player(Territory_o* t, Player_o* p)  { return safe_set<Player_o*>(t, Offsets::Game.Territory_player, p); }
inline bool Territory_isCapital(Territory_o* t)                { return safe_get<bool>(t, Offsets::Game.Territory_isCapital, false); }
inline bool Territory_set_isCapital(Territory_o* t, bool v)    { return safe_set<bool>(t, Offsets::Game.Territory_isCapital, v); }

inline int  Territory_currentCryptoKey(Territory_o* t) {
    if (!t || Offsets::Game.Territory_units < 0 || Offsets::Game.Obscured_currentCryptoKey < 0) return 0;
    return field_get<int>(t, Offsets::Game.Territory_units + Offsets::Game.Obscured_currentCryptoKey);
}
inline bool Territory_set_hiddenValue(Territory_o* t, int v) {
    if (!t || Offsets::Game.Territory_units < 0 || Offsets::Game.Obscured_hiddenValue < 0) return false;
    field_set<int>(t, Offsets::Game.Territory_units + Offsets::Game.Obscured_hiddenValue, v);
    return true;
}

inline int32_t RiskCard_Type(RiskCard_o* c)                    { return safe_get<int32_t>(c, Offsets::Game.RiskCard_Type, 0); }
inline bool    RiskCard_set_Type(RiskCard_o* c, int32_t v)     { return safe_set<int32_t>(c, Offsets::Game.RiskCard_Type, v); }

inline RiskCard_o* Player_card_at(Player_o* p, int idx) {
    if (!p || idx < 0 || Offsets::Game.Player_cards < 0) return nullptr;
    void* list = field_get<void*>(p, Offsets::Game.Player_cards);
    if (!list) return nullptr;

    if (Offsets::Game.List_items <= 0) {
        void* listKl = object_class(list);
        if (!listKl) return nullptr;
        Offsets::Game.List_items = il2cpp_exp::find_field_offset(listKl, "_items");
        if (Offsets::Game.List_items <= 0) return nullptr;
    }

    void* items = field_get<void*>(list, Offsets::Game.List_items);
    if (!items) return nullptr;
    if ((uint32_t)idx >= array_length(items)) return nullptr;
    return array_get<RiskCard_o*>(items, idx);
}

bool resolve_dict_entry_layout(void* dict_obj);

void resolve_game_offsets();

}
