#pragma once
#include "main.h"
#include "xorstr.h"

bool menustate, activew;
int id_p = 0;
bool skip = false;
DWORD ticktime = 1;

bool CALLBACK Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
    if (SUCCEEDED(SF->getRender()->BeginRender()))
    {

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        if (activew)
        {
            ImGui::Begin(xorstr(u8"РAЗНOC RRP ОТ AKЕGGА"), &activew, ImVec2(450, 200), 0.8f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);
            {
                ImGui::Text(xorstr(u8"Author: https://www.youtube.com/@D.V.AkeGGa"));
                ImGui::InputInt(xorstr(u8"Введите id игрока"), &id_p);
                ImGui::Checkbox(xorstr(u8"Начать давать розыск"), &skip);
                ImGui::End();
            }
        }
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        SF->getRender()->EndRender();
    }
    return true;
}

HRESULT CALLBACK Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    return true;
}

bool CALLBACK WndProcHandler(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    ImGui_ImplWin32_WndProcHandler(hwd, msg, wParam, lParam);
    return true;
}

void CALLBACK DestructorPlugin()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}