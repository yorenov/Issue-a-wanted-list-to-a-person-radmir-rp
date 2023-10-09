#pragma once

#include <Windows.h>
#include <assert.h>
#include <string>
#include <process.h>
#include <fstream>
#include <dinput.h>
#include <tchar.h>
#include <d3d9.h>
#include <array>
#include <utility>
#include <cstdarg>

#include "SAMPFUNCS_API.h"
#include "game_api.h"

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

extern SAMPFUNCS *SF;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define DIRECTINPUT_VERSION 0x0800
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

#include "menu.h"