
#include "loop.h"

#include "icons.h"
#include <D3D11.h>
#include "ImGui/imgui_impl_dx11.h"
#include "icon.h"
#include "ImGui/imgui_internal.h"
#include "imgui_notify.h"
#include "animation.h"
#include <D3DX11core.h>
#include "fonts.h"
#include "image.h"
#include <D3DX11.h>
#include <D3DX11tex.h>
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);
HWND window_handle;

ID3D11Device* d3d_device;
ID3D11DeviceContext* d3d_device_ctx;
IDXGISwapChain* d3d_swap_chain;
ID3D11RenderTargetView* d3d_render_target;
D3DPRESENT_PARAMETERS d3d_present_params;


ID3D11ShaderResourceView* Logo = nullptr;

ImVec2 pos;
static int tabs = 1;
static int closeaimbotsubs = 0;
static int weaponconfigsubs = 0;
static int visualsubs = 0;

static int meng_slide = 0;
static int meng_animation = 0;
static int border_animation = 0;
ImFont* icons;
ImFont* colorpicker;
ImFont* tabfont;
ImFont* MenuFont1;

namespace n_render {
    class c_render {
    public:

        auto imgui( ) -> bool {
            SPOOF_FUNC

            DXGI_SWAP_CHAIN_DESC swap_chain_description;
            ZeroMemory(&swap_chain_description, sizeof(swap_chain_description));
            swap_chain_description.BufferCount = 2;
            swap_chain_description.BufferDesc.Width = 0;
            swap_chain_description.BufferDesc.Height = 0;
            swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swap_chain_description.BufferDesc.RefreshRate.Numerator = 60;
            swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
            swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
            swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swap_chain_description.OutputWindow = window_handle;
            swap_chain_description.SampleDesc.Count = 1;
            swap_chain_description.SampleDesc.Quality = 0;
            swap_chain_description.Windowed = 1;
            swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            D3D_FEATURE_LEVEL d3d_feature_lvl;

            const D3D_FEATURE_LEVEL d3d_feature_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

            D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, d3d_feature_array, 2, D3D11_SDK_VERSION, &swap_chain_description, &d3d_swap_chain, &d3d_device, &d3d_feature_lvl, &d3d_device_ctx);

            ID3D11Texture2D* pBackBuffer;
            D3DX11_IMAGE_LOAD_INFO info;
            ID3DX11ThreadPump* pump{ nullptr };
            //D3DX11CreateShaderResourceViewFromMemory(d3d_device, rawData, sizeof(rawData), &info,
            //    pump, &Logo, 0);
            d3d_swap_chain->GetBuffer( 0, IID_PPV_ARGS (&pBackBuffer ) );

            d3d_device->CreateRenderTargetView(pBackBuffer, NULL, &d3d_render_target );

            pBackBuffer->Release( );

            IMGUI_CHECKVERSION( );
            ImGui::CreateContext( );
            ImGuiIO& io = ImGui::GetIO( ); ( void )io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

            static const ImWchar icons_ranges[ ] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;

            ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;

            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;

            ImGui_ImplWin32_Init( window_handle );
            ImGui_ImplDX11_Init( d3d_device, d3d_device_ctx );


            ImFontConfig font_config;
            font_config.OversampleH = 1; 
            font_config.OversampleV = 1;
            font_config.PixelSnapH = 1;


            static const ImWchar ranges[] =
            {
                0x0020, 0x00FF,
                0x0400, 0x044F, 
                0,
            };

            MenuFont = io.Fonts->AddFontFromFileTTF(E("C:\\Windows\\Fonts\\Verdana.ttf"), 18.f);
            IconsFont = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 22.0f, &icons_config, icons_ranges);

            GameFont = io.Fonts->AddFontFromFileTTF(E("C:\\fortnite.otf"), 15.f);

            MenuFont1 = io.Fonts->AddFontFromFileTTF(E("C:\\fortnite.otf"), 18.f);

            tabfont = io.Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 16, NULL, io.Fonts->GetGlyphRangesCyrillic());
            icons = io.Fonts->AddFontFromMemoryTTF(iconshxd, sizeof(iconshxd), 14.0f, &font_config, ranges);
            colorpicker = io.Fonts->AddFontFromMemoryTTF(iconshxd, sizeof(iconshxd), 28.0f, &font_config, ranges);

            ImGui_ImplWin32_Init(window_handle);

            ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);

            d3d_device->Release();

            return true;

        }

        auto hijack( ) -> bool {

            window_handle = FindWindowA_Spoofed ( E ("MedalOverlayClass" ), E ( "MedalOverlay" ) ); //CiceroUIWndFrame

            if ( !window_handle )
            {
                MessageBoxA(0, skCrypt("{!} Overlay Failed. Contact Support with error {3}"), skCrypt(""), MB_ICONINFORMATION);
            }

            int WindowWidth = GetSystemMetrics(SM_CXSCREEN);
            int WindowHeight = GetSystemMetrics(SM_CYSCREEN);

            if (!SetWindowPos_Spoofed(window_handle, HWND_TOPMOST, 0, 0, WindowWidth, WindowHeight, SWP_SHOWWINDOW))
            {
                return false;
            }

            if (!SetLayeredWindowAttributes_Spoofed(window_handle, RGB(0, 0, 0), 255, LWA_ALPHA))
            {
                return false;
            }

            if (!SetWindowLongA_Spoofed(window_handle, GWL_EXSTYLE, GetWindowLong(window_handle, GWL_EXSTYLE) | WS_EX_TRANSPARENT))
            {
                return false;
            }

            MARGINS Margin = { -1 };
            if (FAILED(DwmExtendFrameIntoClientArea(window_handle, &Margin)))
            {
                return false;
            }

            ShowWindow_Spoofed(window_handle, SW_SHOW);

            UpdateWindow_Spoofed(window_handle);

            ShowWindow_Spoofed(window_handle, SW_HIDE);

            return true;
        }

        int tab = 0;
        ImVec2 MPos;

        bool a1 = 1, b1 = 1, c1 = 0, d1 = 1, e1 = 0;
        bool a2 = 1, b2 = 0, c2 = 1, d2 = 0, e2 = 1;
        bool a3 = 0, b3 = 0, c3 = 1, d3 = 1, e3 = 1;
        bool a4 = 0, b4 = 0, c4 = 0, d4 = 0, e4 = 0;
        float fv1 = 30, sm1 = 6;
        float fv2 = 20, sm2 = 0;
        float fv3 = 25, sm3 = 4;
        float fv4 = 0, sm4 = 0;

        float in = 10;

        int selectedWeapon = 0;
        const char* weapons[4]{ "Rifle", "Shotgun", "Smg", "Sniper" };
       

        auto menu() -> void {

            if (GetAsyncKeyState_Spoofed(VK_INSERT) & 1)
                globals::g_render_menu = !globals::g_render_menu;



            if (globals::g_render_menu) {

                if (globals::g_render_menu) {
                    ImGui::PushFont(MenuFont);
                    ImGui::PushFont(IconsFont);
                    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImColor();
                    ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImColor(19, 18, 19);
                    ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor();
                    ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor();
                    ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor();
                    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImColor(150, 150, 150);
                    ImGui::GetStyle().Colors[ImGuiCol_Header] = ImColor(25, 25, 25);
                    ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered] = ImColor(25, 25, 25);
                    ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = ImColor(25, 25, 25);
                    ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImColor(25, 25, 25);
                    ImGui::GetStyle().WindowBorderSize = 0;
                    ImGui::GetStyle().PopupBorderSize = 0;
                    ImGui::GetStyle().PopupRounding = 3.0f;
                    ImGui::GetStyle().FrameRounding = 3.0f;
                    ImGui::SetNextWindowSize({ 450, 320 });
                    ImGui::Begin(("##fortnite"), 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
                    MPos = ImGui::GetWindowPos();
                    ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(ImVec2(MPos.x, MPos.y), ImVec2(MPos.x + 450, MPos.y + 320), ImColor(20, 20, 20), ImColor(15, 15, 15), ImColor(20, 20, 20), ImColor(15, 15, 15));
                    ImGui::SetWindowFontScale(1.5f);
                    ImGui::SetCursorPos({ 11, 15 });  ImGui::TextColored(ImColor(255, 255, 255), ICON_FA_BOMB);
                    ImGui::SetWindowFontScale(1.0f);
                    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(MPos.x + 15, MPos.y + 55), ImVec2(MPos.x + 47, MPos.y + 55), ImColor(100, 100, 100, 100), 1);
                    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(MPos.x + 60, MPos.y), ImVec2(MPos.x + 60, MPos.y + 320), ImColor(100, 100, 100, 100), 1);

                    ImGui::PushStyleColor(ImGuiCol_Button, tab == 0 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, tab == 0 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, tab == 0 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::SetCursorPos({ 5, 65 }); if (ImGui::Button(ICON_FA_SHIELD, ImVec2(50, 50))) tab = 0;

                    ImGui::PushStyleColor(ImGuiCol_Button, tab == 1 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, tab == 1 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, tab == 1 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::SetCursorPos({ 5, 115 }); if (ImGui::Button(ICON_FA_EYE, ImVec2(50, 50))) tab = 1;

                    ImGui::PushStyleColor(ImGuiCol_Button, tab == 2 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, tab == 2 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, tab == 2 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::SetCursorPos({ 5, 165 }); if (ImGui::Button(ICON_FA_PLUS, ImVec2(50, 50))) tab = 2;

                    ImGui::PushStyleColor(ImGuiCol_Button, tab == 3 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, tab == 3 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, tab == 3 ? ImVec4(25.f / 255.f, 25.f / 255.f, 25.f / 255.f, 1.0f) : ImVec4());
                    ImGui::SetCursorPos({ 5, 215 }); if (ImGui::Button(ICON_FA_SLIDERS_H, ImVec2(50, 50))) tab = 3;

                    ImGui::PopStyleColor(12);

                    switch (tab)
                    {
                    case 0:
                        switch (selectedWeapon)
                        {
                        case 0:
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 15), ImVec2(MPos.x + 250, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 34), ImVec2(MPos.x + 250, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 130, MPos.y + 15), ImColor(255, 255, 255), skCrypt("General"));
                            ImGui::SetCursorPos({ 75, 40 }); ImGui::Text(skCrypt("Aimbot")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Aimbot"), &rifle::aimbot);
                            ImGui::SetCursorPos({ 75, 65 }); ImGui::Text(skCrypt("Ignore Downed")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##IgnoreDowned"), &rifle::ignore_downed);
                            ImGui::SetCursorPos({ 75, 90 }); ImGui::Text(skCrypt("Visible Check")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##VisibleCheck"), &rifle::visible_check);
                            ImGui::SetCursorPos({ 75, 115 }); ImGui::Text(skCrypt("Target Line")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##TargetLine"), &rifle::target_line);

                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 15), ImVec2(MPos.x + 440, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 34), ImVec2(MPos.x + 440, MPos.y + 180), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 320, MPos.y + 15), ImColor(255, 255, 255), skCrypt("Settings"));
                            ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 41 }); ImGui::Text(skCrypt("Gun:")); ImGui::SameLine(290); ImGui::Combo(skCrypt("WeaponType"), &selectedWeapon, weapons, IM_ARRAYSIZE(weapons), 5); ImGui::PopItemWidth();
                            ImGui::SetCursorPos({ 265, 70 }); ImGui::Text(skCrypt("Fov")); ImGui::SameLine(); ImGui::SliderFloat(skCrypt("##FOV"), &rifle::aim_fov, 0, 180, skCrypt("%.f"));
                            ImGui::SetCursorPos({ 265, 95 }); ImGui::Text(skCrypt("Smooth")); ImGui::SameLine(); ImGui::SliderFloat(skCrypt("##smooth"), &rifle::smooth, 5, 20, skCrypt("%.f"));
                            ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 122 }); ImGui::Text(skCrypt("Bone:")); ImGui::SameLine(295);   ImGui::Combo(E("Rifle Bone"), &rifle::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 190), ImVec2(MPos.x + 440, MPos.y + 210), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 209), ImVec2(MPos.x + 440, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 333, MPos.y + 190), ImColor(255, 255, 255), skCrypt("Other"));
                            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(25, 25, 25);
                            ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25);
                            ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 25, 25);
                            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
                            ImGui::SetCursorPos({ 265, 215 }); HotkeyButton(rifle::aimkey, ChangeKey1, keystatus1);
                            ImGui::PopStyleVar(2);
                            break;
                        case 1:
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 15), ImVec2(MPos.x + 250, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 34), ImVec2(MPos.x + 250, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 130, MPos.y + 15), ImColor(255, 255, 255), skCrypt("General"));
                            ImGui::SetCursorPos({ 75, 40 }); ImGui::Text(skCrypt("Aimbot")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Aimbot"), &shotgun::aimbot);
                            ImGui::SetCursorPos({ 75, 65 }); ImGui::Text(skCrypt("Ignore Downed")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##IgnoreDowned"), &shotgun::ignore_downed);
                            ImGui::SetCursorPos({ 75, 90 }); ImGui::Text(skCrypt("Visible Check")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##VisibleCheck"), &shotgun::visible_check);
                            ImGui::SetCursorPos({ 75, 115 }); ImGui::Text(skCrypt("Target Line")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##TargetLine"), &shotgun::target_line);


                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 15), ImVec2(MPos.x + 440, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 34), ImVec2(MPos.x + 440, MPos.y + 180), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 320, MPos.y + 15), ImColor(255, 255, 255), "Settings");
                            ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 41 }); ImGui::Text("Gun:"); ImGui::SameLine(290); ImGui::Combo("WeaponType", &selectedWeapon, weapons, IM_ARRAYSIZE(weapons), 5); ImGui::PopItemWidth();
                            ImGui::SetCursorPos({ 265, 70 }); ImGui::Text("Fov"); ImGui::SameLine(); ImGui::SliderFloat("##FOV", &shotgun::aim_fov, 0, 180, "%.f");
                            ImGui::SetCursorPos({ 265, 95 }); ImGui::Text("Smooth"); ImGui::SameLine(); ImGui::SliderFloat("##smooth", &shotgun::smooth, 5, 20, "%.f");
                            ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 122 }); ImGui::Text("Bone:"); ImGui::SameLine(295);   ImGui::Combo(E("Bone"), &shotgun::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 190), ImVec2(MPos.x + 440, MPos.y + 210), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 209), ImVec2(MPos.x + 440, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 333, MPos.y + 190), ImColor(255, 255, 255), "Other");
                            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(25, 25, 25);
                            ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25);
                            ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 25, 25);
                            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
                            ImGui::SetCursorPos({ 265, 215 }); HotkeyButton(shotgun::aimkey, ChangeKey2, keystatus2);
                            ImGui::PopStyleVar(2);
                            break;
                        case 2:
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 15), ImVec2(MPos.x + 250, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 34), ImVec2(MPos.x + 250, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 130, MPos.y + 15), ImColor(255, 255, 255), "General");
                            ImGui::SetCursorPos({ 75, 40 }); ImGui::Text(skCrypt("Aimbot")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Aimbot"), &smg::aimbot);
                            ImGui::SetCursorPos({ 75, 65 }); ImGui::Text(skCrypt("Ignore Downed")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##IgnoreDowned"), &smg::ignore_downed);
                            ImGui::SetCursorPos({ 75, 90 }); ImGui::Text("Visible Check"); ImGui::SameLine(205); ImGui::Checkbox("##VisibleCheck", &smg::visible_check);
                            ImGui::SetCursorPos({ 75, 115 }); ImGui::Text("Target Line"); ImGui::SameLine(205); ImGui::Checkbox("##TargetLine", &smg::target_line);

                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 15), ImVec2(MPos.x + 440, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 34), ImVec2(MPos.x + 440, MPos.y + 180), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 320, MPos.y + 15), ImColor(255, 255, 255), "Settings");
                            ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 41 }); ImGui::Text("Gun:"); ImGui::SameLine(290); ImGui::Combo("WeaponType", &selectedWeapon, weapons, IM_ARRAYSIZE(weapons), 5); ImGui::PopItemWidth();
                            ImGui::SetCursorPos({ 265, 70 }); ImGui::Text("Fov"); ImGui::SameLine(); ImGui::SliderFloat("##FOV", &smg::aim_fov, 0, 180, "%.f");
                            ImGui::SetCursorPos({ 265, 95 }); ImGui::Text("Smooth"); ImGui::SameLine(); ImGui::SliderFloat("##smooth", &smg::smooth, 5, 20, "%.f");
                            ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 122 }); ImGui::Text("Bone:"); ImGui::SameLine(295);   ImGui::Combo(E("Bone"), &smg::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 190), ImVec2(MPos.x + 440, MPos.y + 210), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 209), ImVec2(MPos.x + 440, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 333, MPos.y + 190), ImColor(255, 255, 255), "Other");
                            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(25, 25, 25);
                            ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25);
                            ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 25, 25);
                            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
                            ImGui::SetCursorPos({ 265, 215 }); HotkeyButton(smg::aimkey, ChangeKey3, keystatus3);
                            ImGui::PopStyleVar(2);
                            break;
                        case 3:
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 15), ImVec2(MPos.x + 250, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 34), ImVec2(MPos.x + 250, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 130, MPos.y + 15), ImColor(255, 255, 255), "General");
                            ImGui::SetCursorPos({ 75, 40 }); ImGui::Text(skCrypt("Aimbot")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Aimbot"), &sniper::aimbot);
                            ImGui::SetCursorPos({ 75, 65 }); ImGui::Text("Target Line"); ImGui::SameLine(205); ImGui::Checkbox("##TargetLine", &sniper::target_line);
                            ImGui::SetCursorPos({ 75, 90 }); ImGui::Text(skCrypt("Ignore Downed")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##IgnoreDowned"), &rifle::ignore_downed);

                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 15), ImVec2(MPos.x + 440, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 34), ImVec2(MPos.x + 440, MPos.y + 180), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 320, MPos.y + 15), ImColor(255, 255, 255), "Settings");
                            ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 41 }); ImGui::Text("Gun:"); ImGui::SameLine(290); ImGui::Combo("WeaponType", &selectedWeapon, weapons, IM_ARRAYSIZE(weapons), 5); ImGui::PopItemWidth();
                            ImGui::SetCursorPos({ 265, 70 }); ImGui::Text("Fov"); ImGui::SameLine(); ImGui::SliderFloat("##FOV", &sniper::aim_fov, 0, 180, "%.f");
                            ImGui::SetCursorPos({ 265, 95 }); ImGui::Text("Smooth"); ImGui::SameLine(); ImGui::SliderFloat("##smooth", &sniper::smooth, 5, 20, "%.f");
                            ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 122 }); ImGui::Text("Bone:"); ImGui::SameLine(295);  ImGui::Combo(E("Bone"), &rifle::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 190), ImVec2(MPos.x + 440, MPos.y + 210), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 209), ImVec2(MPos.x + 440, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 333, MPos.y + 190), ImColor(255, 255, 255), "Other");
                            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(25, 25, 25);
                            ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25);
                            ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 25, 25);
                            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
                            ImGui::SetCursorPos({ 265, 215 });  HotkeyButton(sniper::aimkey, ChangeKey4, keystatus4);
                            ImGui::PopStyleVar(2);
                            break;
                        }
                        break;
                    case 1:
                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 15), ImVec2(MPos.x + 250, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 34), ImVec2(MPos.x + 250, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 130, MPos.y + 15), ImColor(255, 255, 255), skCrypt("General"));
                        ImGui::SetCursorPos({ 75, 40 }); ImGui::Text(skCrypt("Enable")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Enable"), &globals::g_enable_esp);
                        ImGui::SetCursorPos({ 75, 65 }); ImGui::Text(skCrypt("Skeleton")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Skeleton"), &globals::g_skeleton);
                        ImGui::SetCursorPos({ 75, 90 }); ImGui::Text(skCrypt("Snapline")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Snapline"), &globals::g_line);
                        ImGui::SetCursorPos({ 75, 115 }); ImGui::Text(skCrypt("Username")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Username"), &globals::g_username);
                        ImGui::SetCursorPos({ 75, 140 }); ImGui::Text(skCrypt("Distance")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Distance_"), &globals::g_distance);
                        ImGui::SetCursorPos({ 75, 165 }); ImGui::Text(skCrypt("Weapon")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Weapon"), &globals::g_weapon_esp);
                        ImGui::SetCursorPos({ 75, 190 }); ImGui::Text(skCrypt("Weapon Rarity")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Weapon Rarity"), &globals::g_weapon_rarity);

                        ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 60 }); ImGui::Text("Box:"); ImGui::SameLine(295); ImGui::Combo(E("Box"), &globals::g_box_type, E("2D \0\Rounded\0\Cornered\0"));
                        ImGui::PushItemWidth(210);  ImGui::SetCursorPos({ 265, 90 }); ImGui::Text("Line:"); ImGui::SameLine(295);  ImGui::Combo(E("Line"), &globals::g_line_type, E("Top\0\Middle\0\Bottom\0"));


                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 15), ImVec2(MPos.x + 440, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 34), ImVec2(MPos.x + 440, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 320, MPos.y + 15), ImColor(255, 255, 255), skCrypt("Settings"));
                        ImGui::SetCursorPos({ 265, 40 }); ImGui::Text(skCrypt("Distance")); ImGui::SameLine(); ImGui::SliderFloat(skCrypt("##Distance"), &globals::g_render_distance, 50, 275, skCrypt("%.f"), 0, 70.0f);
                        break;
                    case 2:
                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 15), ImVec2(MPos.x + 250, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 34), ImVec2(MPos.x + 250, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 130, MPos.y + 15), ImColor(255, 255, 255), skCrypt("General"));
                        ImGui::SetCursorPos({ 75, 40 }); ImGui::Text(skCrypt("Triggerbot")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##2DBox"), &globals::g_triggerbot);
                        ImGui::SetCursorPos({ 75, 65 }); ImGui::Text(skCrypt("Shotguns Only")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Skeleton"), &globals::g_shotguns_only);
                        ImGui::SetCursorPos({ 75, 90 }); ImGui::Text(skCrypt("Ignore Keybind")); ImGui::SameLine(205); ImGui::Checkbox(skCrypt("##Snapline"), &globals::g_ignore_keybind);

                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 15), ImVec2(MPos.x + 440, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 260, MPos.y + 34), ImVec2(MPos.x + 440, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 320, MPos.y + 15), ImColor(255, 255, 255), skCrypt("Settings"));
                        ImGui::SetCursorPos({ 265, 40 }); ImGui::Text(skCrypt("Delay(ms)")); ImGui::SameLine(); ImGui::SliderFloat(skCrypt("##Delay"), &globals::g_custom_delay, 50, 300, skCrypt("%.f"), 0, 64.0f);
                        ImGui::SetCursorPos({ 265, 65 }); ImGui::Text(skCrypt("Distance")); ImGui::SameLine(); ImGui::SliderFloat(skCrypt("##Distance"), &globals::g_maximum_distance, 5, 100, skCrypt("%.f"), 0, 70.0f);
                        ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(25, 25, 25);
                        ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25);
                        ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 25, 25);
                        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
                        /*          ImGui::SetCursorPos({ 265, 90 }); ImGui::Text(_("Keybind:"));  ImGui::SetCursorPos({ 435 - (tbKeySize.x), 92 }); if (ImGui::Button(tbKeyStr.c_str())) tbSelectKey = 1;*/
                        ImGui::PopStyleVar(2);
                        break;
                    case 3:
                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 15), ImVec2(MPos.x + 440, MPos.y + 35), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(MPos.x + 70, MPos.y + 34), ImVec2(MPos.x + 440, MPos.y + 305), ImColor(100, 100, 100, 100), 1);
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(MPos.x + 226, MPos.y + 15), ImColor(255, 255, 255), skCrypt("General"));
                        ImGui::SetCursorPos({ 75, 40 }); ImGui::Text(skCrypt("Render Framerate")); ImGui::SameLine(390); ImGui::Checkbox(skCrypt("##RenderFramerate"), &globals::g_fps);

                        break;
                    }

                    ImGui::End();
                    ImGui::PopFont();
                    ImGui::PopFont();
                }
            }
        }


        auto draw( ) -> void {

            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);

            ImGui::StyleColorsDark();


            ImGui_ImplDX11_NewFrame( );
            ImGui_ImplWin32_NewFrame( );
            ImGui::NewFrame( );

            g_main -> actor_loop( );

            menu( );

           ImGui::Render( );
            const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
            d3d_device_ctx->OMSetRenderTargets(1, &d3d_render_target, nullptr);
            d3d_device_ctx->ClearRenderTargetView(d3d_render_target, clear_color_with_alpha);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            d3d_swap_chain->Present(1, 0);

        }

        auto render( ) -> bool {
            SPOOF_FUNC

            static RECT rect_og;
            MSG msg = { NULL };
            ZeroMemory(&msg, sizeof(MSG));

            while (msg.message != WM_QUIT)
            {

                UpdateWindow_Spoofed(window_handle);
                ShowWindow_Spoofed(window_handle, SW_SHOW);

                if (PeekMessageA_Spoofed(&msg, window_handle, 0, 0, PM_REMOVE))
                {
                    TranslateMessage_Spoofed(&msg);
                    DispatchMessage(&msg);
                }

                ImGuiIO& io = ImGui::GetIO();
                io.ImeWindowHandle = window_handle;
                io.DeltaTime = 1.0f / 60.0f;


                POINT p_cursor;
                GetCursorPos(&p_cursor);
                io.MousePos.x = p_cursor.x;
                io.MousePos.y = p_cursor.y;

                if (GetAsyncKeyState_Spoofed(VK_LBUTTON)) {
                    io.MouseDown[0] = true;
                    io.MouseClicked[0] = true;
                    io.MouseClickedPos[0].x = io.MousePos.x;
                    io.MouseClickedPos[0].x = io.MousePos.y;
                }
                else
                    io.MouseDown[0] = false;

                draw();

            }
            ImGui_ImplDX11_Shutdown( );
            ImGui_ImplWin32_Shutdown( );
            ImGui::DestroyContext( );

            DestroyWindow(window_handle);

            return true;

        }

    };
} static n_render::c_render* render = new n_render::c_render();