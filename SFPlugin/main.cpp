#include "main.h"

SAMPFUNCS *SF = new SAMPFUNCS();

void send_death(uint16_t player_id, uint8_t weapon)
{
	BitStream bsDeath;
	bsDeath.Write(weapon);
	bsDeath.Write(player_id);
	SF->getRakNet()->SendRPC(RPC_Death, &bsDeath);
}

void __stdcall mainloop()
{
	static bool initialized = false;
	if (!initialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			initialized = true;
			SF->getGame()->registerGameDestructorCallback(DestructorPlugin);
			SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Present);
			SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_RESET, Reset);
			SF->getGame()->registerWndProcCallback(SFGame::MEDIUM_CB_PRIORITY, WndProcHandler);
			ImGui::CreateContext();
			/*
			SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_INCOMING_PACKET, OnRecvPacket);
			SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_INCOMING_RPC, OnRecvRPC);
			SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_OUTCOMING_PACKET, onSendPacket);
			SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_OUTCOMING_RPC, onSendRPC);
			*/
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui_ImplWin32_Init(GetActiveWindow());
			ImGui_ImplDX9_Init(SF->getRender()->getD3DDevice());
			ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16.5f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			SF->getSAMP()->registerChatCommand("razdw", [](std::string argument) {
				activew = !activew;
			});
		}
	}
	else {
		if (menustate != activew) {
			SF->getSAMP()->getMisc()->ToggleCursor(activew);
			menustate = activew;
		}
		if (skip && ticktime > 0 && GetTickCount() > ticktime)
		{
			SF->getSAMP()->sendTakeDamage(id_p, 100, 24, 3);
			send_death(id_p, 24);
			ticktime = GetTickCount() + 200;
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
		SF->initPlugin(mainloop, hModule);
	return TRUE;
}
