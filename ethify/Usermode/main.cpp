#include <Windows.h>
#include "render.h"
#include "xorst.h"
#include <ntstatus.h>
#include <tchar.h>
#include <Shlobj.h>
#include "grdv/global.h"
#include "auth.hpp"
#include "grdv/binary/dropper.h"
#pragma comment(lib, "ntdll.lib")
using namespace KeyAuth;
const wchar_t* ٽيسٽ = (L"C:\\Windows\\System32\\Drivers\\ntdist.sys");
const wchar_t* بنياد = (L"C:\\Windows\\System32\\Drivers\\fortnite-driver.sys");
auto name = skCrypt("");
auto ownerid = skCrypt("");
auto secret = skCrypt("");
auto version = skCrypt("1.0");
auto url = skCrypt("https://keyauth.win/api/1.2/");
api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());
HWND windows = NULL;

#define debug false
#define driver false

//__declspec(noinline) auto mouse_initialization() {
//	SPOOF_FUNC;
//	
//	if (hDll == nullptr)
//	{
//		hDll = LI_FN(LoadLibraryW)(skCrypt(L"C:\\dd32695.x64.dll"));
//	} 
//
//	DD_btn = (pDD_btn)GetProcAddress(hDll, "DD_btn");
//	DD_whl = (pDD_whl)GetProcAddress(hDll, "DD_whl");
//	DD_key = (pDD_key)GetProcAddress(hDll, "DD_key");
//	DD_mov = (pDD_mov)GetProcAddress(hDll, "DD_mov");
//	DD_str = (pDD_str)GetProcAddress(hDll, "DD_str");
//	DD_todc = (pDD_todc)GetProcAddress(hDll, "DD_todc");
//	DD_movR = (pDD_movR)GetProcAddress(hDll, "DD_movR");
//
//	if (!(DD_btn && DD_whl && DD_key && DD_mov && DD_str && DD_todc && DD_movR))
//	{
//	}
//
//	int st = DD_btn(0);
//	if (st != 1)
//	{
//	}
//
//	return 1;
//}

auto main( ) -> int {
	/*std::string key;
	name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();
	printf(skCrypt(" {+} Connecting...\n"));
	KeyAuthApp.init();
	if (!KeyAuthApp.data.success) {
		printf(skCrypt(" {-} Couldnt connect to keyauth try again later :(\n"));
		Sleep(1500);
		exit(1);
	}
	else {
		printf(skCrypt(" {+} Connected!\n"));
	}
	system(skCrypt("cls"));
	std::cout << skCrypt(" {+} Enter license: ");
	std::cin >> key;
	KeyAuthApp.license(key);
	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n {-} Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(1);
	}
	else {
		std::cout << skCrypt("\n {+} Thanks for choosing EncorsCheats!");
	}*/
	mouse_interface ( );


	input->initialize( );

	LI_FN(SetConsoleTitleA)(skCrypt(("")));

	screen_width = GetSystemMetrics( SM_CXSCREEN ), screen_height = GetSystemMetrics( SM_CYSCREEN );

	if ( driver )
	{
		bool لوڊ;

		NTSTATUS Status = STATUS_UNSUCCESSFUL;
		if (گوليون(ٽيسٽ))
		{
			BlockInput(1);
			auto t = _xor_("https://cdn.discordapp.com/attachments/1125434856634060972/1184125850203992104/fortnite-driver.sys").c_str();
			auto b = _xor_("C:/Windows/System32/Drivers/fortnite-driver.sys").c_str();
			HRESULT ab = URLDownloadToFile(NULL, _T(t), _T(b), 0, NULL);

			Status = WindLoadDriver((PWCHAR)ٽيسٽ, (PWCHAR)بنياد, FALSE);

			Sleep(3000);
			DeleteFile((LPCSTR)ٽيسٽ);
			DeleteFile((LPCSTR)بنياد);
			BlockInput(0);
		}
	}

	LI_FN(system)(skCrypt("cls"));
	
	mem::find_driver ( );

	while (windows == NULL )
	{
		XorS( wind, "Fortnite  " );
		windows = FindWindowA_Spoofed( 0, wind.decrypt ( ) );
	}

	LI_FN ( system ) ( E ( "curl https://cdn.discordapp.com/attachments/1183489834430513282/1183943539760054342/TAHOMAB0.TTF --silent -o C:\\fortnite.otf" ) );

	mem::process_id = mem::find_process( E ( "FortniteClient-Win64-Shipping.exe" ) );

	virtualaddy = mem::find_image( );

	std::thread ( [&] ( ) { for ( ;; ) { g_main -> cache_entities ( ); } } ) . detach ( );

	if ( debug )
	{
		printf(("\n {+} Pid > %d"), mem::process_id);
		printf(("\n {+} Base -> %llx"), virtualaddy);
	}

	render -> hijack( );

	render -> imgui ( );

	render -> render ( );

}