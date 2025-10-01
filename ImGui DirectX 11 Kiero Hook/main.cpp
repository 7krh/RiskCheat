#include "includes.h"
#include "Rendering.hpp"
#include "Font.h"
#include "sdk.h"
#include "Menu.h"
#include "Functions.h"
#include "kiero/minhook/include/MinHook.h"
#include "il2cpp_resolver.hpp"
#include "Lists.hpp"
#include "Callback.hpp"
#include <Utils/VFunc.hpp>
#include <iostream>
#include <PaternScan.hpp>
#include <intrin.h>
#include "il2cpp.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

//void CreateConsole() {
//	AllocConsole();
//	AttachConsole(GetCurrentProcessId());
//	SetConsoleTitle("IL2CPP");
//	FILE* f;
//	freopen_s(&f, "CONOUT$", "w", stdout);
//}

void initvars() {
	if (IL2CPP::Initialize(true)) {
		printf("[ DEBUG ] Il2Cpp initialized\n");
	}
	else {
		printf("[ DEBUG ] Il2Cpp initialize failed, quitting...");
		Sleep(300);
		exit(0);
	}
	sdk::Base = (uintptr_t)GetModuleHandleA(NULL);
	sdk::GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
}

void Log(uintptr_t address, const char* name) {
	printf("[ LOG ] %s: 0x%llX\n", name, address);
}
#define DEBUG 


bool find_sigs() {
	Unity::il2cppClass* RiskInventory = IL2CPP::Class::Find("RiskInventory");
	Unity::il2cppClass* Territory = IL2CPP::Class::Find("Territory");

	Unity::il2cppClass* Network = IL2CPP::Class::Find("Network");
	Unity::il2cppClass* ObscuredInt = IL2CPP::Class::Find("CodeStage.AntiCheat.ObscuredTypes.ObscuredInt");

	Offsets::HasItem = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RiskInventory, "HasItem");

	Offsets::IsVisible = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Territory, "IsVisible");

	Offsets::GetPlayer = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Network, "GetPlayer");

	Offsets::Encrypt = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ObscuredInt, "Encrypt");
	Offsets::GetDecrypted = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ObscuredInt, "GetDecrypted");

	return true;
}





void EnableHooks() {
	

if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::HasItem), &Functions::RiskInventory__HasItem_hk, (LPVOID*)&Functions::RiskInventory__HasItem_org) == MH_OK)
{
	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::HasItem));
}

if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::IsVisible), &Functions::Territory__IsVisible_hk, (LPVOID*)&Functions::Territory__IsVisible) == MH_OK)
{
	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::IsVisible));
}

//"Signature": "void DServerApi__Call (DServerApi_o* __this, DServerApi_delegateLoaded_o* OnLoadedCall, System_Collections_Generic_Dictionary_string__object__o* parameters, const MethodInfo* method);",

if (MH_CreateHook(reinterpret_cast<LPVOID*>(sdk::GameAssembly + 0x133C2C0), &Functions::DServerApi__Call__hk, (LPVOID*)&Functions::DServerApi__Call__org) == MH_OK)
{

	MH_EnableHook(reinterpret_cast<LPVOID*>(sdk::GameAssembly + 0x133C2C0));
}

}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	ImGuiIO& io = ImGui::GetIO();

	// Let ImGui handle inputs first
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	// Allow clicking in-game EXCEPT when hovering the ImGui window
	if (uMsg >= WM_MOUSEFIRST && uMsg <= WM_MOUSELAST)
	{
		if (ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
			return true; // eat mouse clicks ONLY when menu is hovered
	}

	return CallWindowProcA(oWndProc, hWnd, uMsg, wParam, lParam);

}

bool init = false;



HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			ImGui::GetIO().Fonts->AddFontDefault();
			ImFontConfig font_cfg;
			font_cfg.GlyphExtraSpacing.x = 1.2;
			gameFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(TTSquaresCondensedBold, 14, 14, &font_cfg);
			ImGui::GetIO().Fonts->AddFontDefault();
			// Grab A shader Here If You want
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	pContext->RSGetViewports(&vars::vps, &vars::viewport);
	vars::screen_size = { vars::viewport.Width, vars::viewport.Height };
	vars::screen_center = { vars::viewport.Width / 2.0f, vars::viewport.Height / 2.0f };

	auto begin_scene = [&]() {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	};

	auto end_scene = [&]() {
		ImGui::Render();
	};

	begin_scene();

	auto isFrames = ImGui::GetFrameCount();
	static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;
	if (isFrames % 1 == 0)
	{
		if (isGreen == 0.01f && isBlue == 0.0f)
		{
			isRed += 0.01f;

		}
		if (isRed > 0.99f && isBlue == 0.0f)
		{
			isRed = 1.0f;

			isGreen += 0.01f;

		}
		if (isGreen > 0.99f && isBlue == 0.0f)
		{
			isGreen = 1.0f;

			isRed -= 0.01f;

		}
		if (isRed < 0.01f && isGreen == 1.0f)
		{
			isRed = 0.0f;

			isBlue += 0.01f;

		}
		if (isBlue > 0.99f && isRed == 0.0f)
		{
			isBlue = 1.0f;

			isGreen -= 0.01f;

		}
		if (isGreen < 0.01f && isBlue == 1.0f)
		{
			isGreen = 0.0f;

			isRed += 0.01f;

		}
		if (isRed > 0.99f && isGreen == 0.0f)
		{
			isRed = 1.0f;

			isBlue -= 0.01f;

		}
		if (isBlue < 0.01f && isGreen == 0.0f)
		{
			isBlue = 0.0f;

			isRed -= 0.01f;

			if (isRed < 0.01f)
				isGreen = 0.01f;

		}
	}
	vars::Rainbow = ImVec4(isRed, isGreen, isBlue, 1.0f);

	

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(window, &mousePos);

	if (show_menu)
	{
		DrawMenu();
	}
	

	end_scene();

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show_menu = !show_menu;
		ImGui::GetIO().MouseDrawCursor = show_menu;
	}

	if (GetKeyState(VK_END) & 1)
	{
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
		show_menu = false;
	}

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	IL2CPP::Thread::Detach(m_pThisThread);

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void initchair()
{
#ifdef DEBUG
	/*CreateConsole();
	system("cls");*/
#endif // DEBUG
	initvars();
	find_sigs();
	IL2CPP::Callback::Initialize();
	EnableHooks();
	kiero::bind(8, (void**)&oPresent, hkPresent);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			initchair();
			init_hook = true;
			vars::initil2cpp = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(mod);
		CreateThread(nullptr, 0, MainThread, mod, 0, nullptr);
	}
	return TRUE;
}