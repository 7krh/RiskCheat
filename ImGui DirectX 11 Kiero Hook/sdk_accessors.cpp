#include "sdk_accessors.h"
#include <cstdio>
#include <cstdint>

namespace sdk {

std::string string_to_std(System_String_o* s) {
    if (!s || Offsets::Game.String_length < 0 || Offsets::Game.String_firstChar < 0)
        return {};

    int32_t len = field_get<int32_t>(s, Offsets::Game.String_length);
    if (len <= 0) return {};

    const uint16_t* chars = reinterpret_cast<const uint16_t*>(
        reinterpret_cast<char*>(s) + Offsets::Game.String_firstChar);

    std::string out;
    out.reserve(len);
    for (int i = 0; i < len; ++i) {
        uint16_t ch = chars[i];
        if (ch < 0x80) {
            out += (char)ch;
        } else if (ch < 0x800) {
            out += (char)(0xC0 | (ch >> 6));
            out += (char)(0x80 | (ch & 0x3F));
        } else {
            out += (char)(0xE0 | (ch >> 12));
            out += (char)(0x80 | ((ch >> 6) & 0x3F));
            out += (char)(0x80 | (ch & 0x3F));
        }
    }
    return out;
}

static constexpr int kIl2CppObjectHeader = 0x10;

static int unbox_field(void* klass, const char* name) {
    int off = il2cpp_exp::find_field_offset(klass, name);
    if (off < 0) return -1;
    if (il2cpp_exp::class_is_valuetype(klass) && off >= kIl2CppObjectHeader)
        off -= kIl2CppObjectHeader;
    return off;
}

bool resolve_dict_entry_layout(void* dict_obj) {
    if (!dict_obj) return false;
    if (Offsets::Game.Dict_entries >= 0 && Offsets::Game.DictEntry_size > 0)
        return true;

    void* dict_klass = il2cpp_exp::object_get_class(dict_obj);
    if (!dict_klass) return false;

    Offsets::Game.Dict_entries = il2cpp_exp::find_field_offset(dict_klass, "_entries");
    if (Offsets::Game.Dict_entries < 0)
        Offsets::Game.Dict_entries = il2cpp_exp::find_field_offset(dict_klass, "entries");

    Offsets::Game.Dict_count = il2cpp_exp::find_field_offset(dict_klass, "_count");
    if (Offsets::Game.Dict_count < 0)
        Offsets::Game.Dict_count = il2cpp_exp::find_field_offset(dict_klass, "count");

    if (Offsets::Game.Dict_entries < 0) return false;

    void* entries = field_get<void*>(dict_obj, Offsets::Game.Dict_entries);
    if (!entries) return false;

    void* entries_klass = il2cpp_exp::object_get_class(entries);
    void* entry_klass = entries_klass ? il2cpp_exp::class_get_element_class(entries_klass) : nullptr;
    if (!entry_klass) return false;

    Offsets::Game.DictEntry_key      = unbox_field(entry_klass, "key");
    Offsets::Game.DictEntry_value    = unbox_field(entry_klass, "value");
    Offsets::Game.DictEntry_hashCode = unbox_field(entry_klass, "hashCode");

    uint32_t align = 0;
    Offsets::Game.DictEntry_size = il2cpp_exp::class_value_size(entry_klass, &align);

    return Offsets::Game.DictEntry_key >= 0 &&
           Offsets::Game.DictEntry_value >= 0 &&
           Offsets::Game.DictEntry_hashCode >= 0 &&
           Offsets::Game.DictEntry_size > 0;
}

static int log_off(int v, const char* name) {
    printf("[ OFF ] %-32s = %d (0x%X)\n", name, v, v);
    return v;
}

void resolve_game_offsets() {
    void* sysString = il2cpp_exp::find_class("String", "System");
    void* obsInt    = il2cpp_exp::find_class("ObscuredInt", "CodeStage.AntiCheat.ObscuredTypes");
    void* playerKl  = il2cpp_exp::find_class("Player");
    void* territKl  = il2cpp_exp::find_class("Territory");
    void* cardKl    = il2cpp_exp::find_class("TerritoryCard");
    if (!cardKl) cardKl = il2cpp_exp::find_class("RiskCard");

    if (sysString) {
        Offsets::Game.String_length    = log_off(il2cpp_exp::find_field_offset(sysString, "_stringLength"), "String._stringLength");
        Offsets::Game.String_firstChar = log_off(il2cpp_exp::find_field_offset(sysString, "_firstChar"),    "String._firstChar");
        if (Offsets::Game.String_length    < 0) Offsets::Game.String_length    = log_off(il2cpp_exp::find_field_offset(sysString, "m_stringLength"), "String.m_stringLength");
        if (Offsets::Game.String_firstChar < 0) Offsets::Game.String_firstChar = log_off(il2cpp_exp::find_field_offset(sysString, "m_firstChar"),    "String.m_firstChar");
    }

    if (obsInt) {
        Offsets::Game.Obscured_hiddenValue      = log_off(unbox_field(obsInt, "hiddenValue"),      "ObscuredInt.hiddenValue");
        Offsets::Game.Obscured_currentCryptoKey = log_off(unbox_field(obsInt, "currentCryptoKey"), "ObscuredInt.currentCryptoKey");
    }

    if (playerKl) {
        Offsets::Game.Player_name    = log_off(il2cpp_exp::find_field_offset(playerKl, "_name"),    "Player._name");
        Offsets::Game.Player_units   = log_off(il2cpp_exp::find_field_offset(playerKl, "_units"),   "Player._units");
        Offsets::Game.Player_colorID = log_off(il2cpp_exp::find_field_offset(playerKl, "colorID"),  "Player.colorID");
        Offsets::Game.Player_cards   = log_off(il2cpp_exp::find_field_offset(playerKl, "cards"),    "Player.cards");
    }

    if (territKl) {
        Offsets::Game.Territory_name      = log_off(il2cpp_exp::find_field_offset(territKl, "name"),       "Territory.name");
        Offsets::Game.Territory_player    = log_off(il2cpp_exp::find_field_offset(territKl, "_player"),    "Territory._player");
        Offsets::Game.Territory_isCapital = log_off(il2cpp_exp::find_field_offset(territKl, "_isCapital"), "Territory._isCapital");
        Offsets::Game.Territory_units     = log_off(il2cpp_exp::find_field_offset(territKl, "_units"),     "Territory._units");
    }

    if (cardKl) {
        Offsets::Game.RiskCard_Type = log_off(il2cpp_exp::find_field_offset(cardKl, "Type"), "RiskCard.Type");
        if (Offsets::Game.RiskCard_Type < 0)
            Offsets::Game.RiskCard_Type = log_off(il2cpp_exp::find_field_offset(cardKl, "type"), "RiskCard.type");
    }
}

}
