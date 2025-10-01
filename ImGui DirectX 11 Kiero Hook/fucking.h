#include "vec.h"
#include "vec2.h"
#include <string>
#include "il2cpp_resolver.hpp"
#include "Lists.hpp"
#include <intrin.h>
#include <iostream>
#include "il2cppRisk.h";
#include <locale>
#include <codecvt>
#include <Windows.h>
namespace fucking {

	
	MethodInfo* method = new MethodInfo();

	uintptr_t GameAssembly1 = (uintptr_t)GetModuleHandleA("GameAssembly.dll");






	Player_o* GetPlayer1(int32_t index, MethodInfo* method) {
		Player_o* (UNITY_CALLING_CONVENTION ta)(int32_t, MethodInfo*);
		return reinterpret_cast<decltype(ta)>(GameAssembly1 + 0x17C7A90)(index, method);
	}











}