#include <windows.h>
#include <dwmapi.h>
#include "spoofer.h"
#include "SkCrypt.h"
#include "lazy.h"

enum InjectedInputMouseOptions
{
	move = 1,
	left_up = 4,
	left_down = 2,
	right_up = 8,
	right_down = 16
};

struct InjectedInputMouseInfo
{
	int move_direction_x;
	int move_direction_y;
	unsigned int mouse_data;
	InjectedInputMouseOptions mouse_options;
	unsigned int time_offset_in_miliseconds;
	void* extra_info;
};

inline bool(*_NtUserInjectMouseInput)(InjectedInputMouseInfo*, int) = nullptr;
inline  int screen_width;
inline int screen_height;

bool IsInScreen(fvector pos, int over = 30)
{
	SPOOF_FUNC;

	if (pos.x > -over && pos.x < screen_width + over && pos.y > -over && pos.y < screen_height + over)
		return true;
	return false;
}

BOOL(*_GetCursorPos)(LPPOINT lpPoint) = nullptr;
BOOL(*_SetLayeredWindowAttributes)(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags) = nullptr;
HRESULT(*_DwmExtendFrameIntoClientArea)(HWND hwnd, const MARGINS* pMarInset) = nullptr;
LRESULT(*_DefWindowProc)(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) = nullptr;
HWND(*_CreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) = nullptr;
LONG(*_SetWindowLongA)(HWND hwnd, int nIndex, LONG dwNewLong) = nullptr;
LONG(*_GetWindowLongA)(HWND hwnd, int nIndex) = nullptr;
ATOM(*_RegisterClassExA)(const WNDCLASSEXA*) = nullptr;
int(*_GetSystemMetrics)(int nIndex) = nullptr;
HWND(*_FindWindowA)(LPCSTR lpClassName, LPCSTR lpWindowName) = nullptr;

SHORT(*_GetAsyncKeyState)(int vKey) = nullptr;
HWND(*_GetForegroundWindow)() = nullptr;
BOOL(*_MoveWindow)(HWND hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint) = nullptr;
BOOL(*_PeekMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) = nullptr;
BOOL(*_TranslateMessage)(const MSG* lpMsg) = nullptr;
LRESULT(*_DispatchMessageA)(const MSG* lpMsg) = nullptr;
HANDLE(*_CreateThread)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE     lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) = nullptr;
BOOL(*_CloseHandle)(HANDLE hObject) = nullptr;
BOOL(*_SetWindowPos)(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) = nullptr;
BOOL(*_ShowWindow)(HWND hWnd, int nCmdShow) = nullptr;
BOOL(*_SetWindowDisplayAffinity)(HWND hWnd, DWORD dwAffinity) = nullptr;
BOOL(*_mouse_event)(DWORD, DWORD, DWORD, DWORD, ULONG_PTR) = nullptr;
BOOL(*_UpdateWindow)(HWND) = nullptr;
BOOL(*_GetClientRect)(HWND, LPRECT) = nullptr;
BOOL(*_ClientToScreen)(HWND, LPPOINT) = nullptr;

void mouse_interface()
{
	SPOOF_FUNC;

	HMODULE user32 = LI_FN(LoadLibraryA).get()(skCrypt("user32.dll"));
	HMODULE kernel32 = LI_FN(LoadLibraryA).get()(skCrypt("Kernel32.dll"));
	HMODULE win32u = LI_FN(LoadLibraryA).get()(skCrypt("win32u.dll"));
	HMODULE dwmapi = LI_FN(LoadLibraryA).get()(skCrypt("dwmapi.dll"));

	if (!win32u) {
		return;
	}

	if (!user32) {
		return;
	}

	if (!dwmapi) {
		return;
	}

	if (!kernel32) {
		return;
	}


	void* NtUserInjectMouseInputAddress = (void*)LI_FN(GetProcAddress).get()(win32u, skCrypt("NtUserInjectMouseInput"));
	void* GetCursorPos = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetCursorPos"));
	void* SetLayeredWindowAttributes = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("SetLayeredWindowAttributes"));
	void* DwmExtendFrameIntoClientArea = (void*)LI_FN(GetProcAddress).get()(dwmapi, skCrypt("DwmExtendFrameIntoClientArea"));
	void* DefWindowProcA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("DefWindowProcA"));
	void* CreateWindowExA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("CreateWindowExA"));
	void* SetWindowLongA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("SetWindowLongA"));
	void* GetWindowLongA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetWindowLongA"));
	void* RegisterClassExA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("RegisterClassExA"));
	void* GetSystemMetrics = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetSystemMetrics"));
	void* FindWindowA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("FindWindowA"));
	void* GetAsyncKeyState = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetAsyncKeyState"));
	void* GetForegroundWindow = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetForegroundWindow"));
	void* MoveWindow = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("MoveWindow"));
	void* PeekMessageA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("PeekMessageA"));
	void* TranslateMessage = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("TranslateMessage"));
	void* DispatchMessageA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("DispatchMessageA"));
	void* CreateThread = (void*)LI_FN(GetProcAddress).get()(kernel32, skCrypt("CreateThread"));
	void* SetWindowPos = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("SetWindowPos"));
	void* CloseHandle = (void*)LI_FN(GetProcAddress).get()(kernel32, skCrypt("CloseHandle"));
	void* ShowWindow = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("ShowWindow"));
	void* SetWindowDisplayAffinity = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("SetWindowDisplayAffinity"));
	void* mouzeevent = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("mouse_event"));
	void* updetewindow = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("UpdateWindow"));
	void* clientrect = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetClientRect"));
	void* clienttoscreen = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("ClientToScreen"));

	if (!NtUserInjectMouseInputAddress) {
		return;
	}

	if (!GetCursorPos) {
		return;
	}

	if (!SetLayeredWindowAttributes) {
		return;
	}

	if (!DwmExtendFrameIntoClientArea) {
		return;
	}

	if (!DefWindowProcA) {
		return;
	}

	if (!CreateWindowExA) {
		return;
	}

	if (!SetWindowLongA) {
		return;
	}

	if (!GetWindowLongA) {
		return;
	}

	if (!RegisterClassExA) {
		return;
	}

	if (!GetSystemMetrics) {
		return;
	}

	if (!FindWindowA) {
		return;
	}

	if (!GetAsyncKeyState) {
		return;
	}

	if (!GetForegroundWindow) {
		return;
	}

	if (!MoveWindow) {
		return;
	}

	if (!PeekMessageA) {
		return;
	}

	if (!TranslateMessage) {
		return;
	}

	if (!DispatchMessageA) {
		return;
	}

	if (!CreateThread) {
		return;
	}

	if (!CloseHandle) {
		return;
	}

	if (!SetWindowPos) {
		return;
	}

	if (!ShowWindow) {
		return;
	}

	if (!SetWindowDisplayAffinity) {
		return;
	}

	if (!mouzeevent) {
		return;
	}

	if (!updetewindow) {
		return;
	}

	if (!clientrect) {
		return;
	}

	if (!clienttoscreen) {
		return;
	}


	*(void**)&_GetCursorPos = GetCursorPos;
	*(void**)&_SetLayeredWindowAttributes = SetLayeredWindowAttributes;
	*(void**)&_DwmExtendFrameIntoClientArea = DwmExtendFrameIntoClientArea;
	*(void**)&_DefWindowProc = DefWindowProcA;
	*(void**)&_CreateWindowExA = CreateWindowExA;
	*(void**)&_SetWindowLongA = SetWindowLongA;
	*(void**)&_GetWindowLongA = GetWindowLongA;
	*(void**)&_RegisterClassExA = RegisterClassExA;
	*(void**)&_GetSystemMetrics = GetSystemMetrics;
	*(void**)&_FindWindowA = FindWindowA;
	*(void**)&_GetAsyncKeyState = GetAsyncKeyState;
	*(void**)&_GetForegroundWindow = GetForegroundWindow;
	*(void**)&_MoveWindow = MoveWindow;
	*(void**)&_PeekMessageA = PeekMessageA;
	*(void**)&_TranslateMessage = TranslateMessage;
	*(void**)&_DispatchMessageA = DispatchMessageA;
	*(void**)&_CreateThread = CreateThread;
	*(void**)&_CloseHandle = CloseHandle;
	*(void**)&_SetWindowPos = SetWindowPos;
	*(void**)&_ShowWindow = ShowWindow;
	*(void**)&_SetWindowDisplayAffinity = SetWindowDisplayAffinity;
	*(void**)&_mouse_event = mouzeevent;
	*(void**)&_UpdateWindow = updetewindow;
	*(void**)&_GetClientRect = clientrect;
	*(void**)&_ClientToScreen = clienttoscreen;


	LI_FN(FreeLibrary).get()(kernel32);
	LI_FN(FreeLibrary).get()(user32);
	LI_FN(FreeLibrary).get()(win32u);
	LI_FN(FreeLibrary).get()(dwmapi);

}

BOOL GetCursorPosA_Spoofed(LPPOINT lpPoint)
{
	SPOOF_FUNC;

	return _GetCursorPos(lpPoint);
}

BOOL SetLayeredWindowAttributes_Spoofed(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	SPOOF_FUNC;

	return _SetLayeredWindowAttributes(hwnd, crKey, bAlpha, dwFlags);
}

HRESULT __stdcall DwmExtendFrameIntoClientArea_Spoofed(HWND hwnd, const MARGINS* pMarInset)
{
	SPOOF_FUNC;

	return _DwmExtendFrameIntoClientArea(hwnd, pMarInset);
}

LRESULT __stdcall DefWindowProcA_Spoofed(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	SPOOF_FUNC;

	return _DefWindowProc(hwnd, Msg, wParam, lParam);
}

HWND __stdcall CreateWindowExA_Spoofed(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	SPOOF_FUNC;

	return _CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

LONG __stdcall SetWindowLongA_Spoofed(HWND hwnd, int nIndex, LONG dwNewLong)
{
	SPOOF_FUNC;

	return _SetWindowLongA(hwnd, nIndex, dwNewLong);
}

LONG __stdcall GetWindowLongA_Spoofed(HWND hwnd, int nIndex)
{
	SPOOF_FUNC;

	return _GetWindowLongA(hwnd, nIndex);
}

ATOM __stdcall RegisterClassExA_Spoofed(const WNDCLASSEXA* softaim) {
	SPOOF_FUNC;

	return _RegisterClassExA(softaim);
}

int __stdcall GetSystemMetrics_Spoofed(int nIndex) {
	SPOOF_FUNC;

	return _GetSystemMetrics(nIndex);
}

HWND __stdcall FindWindowA_Spoofed(LPCSTR lpClassName, LPCSTR lpWindowName) {
	SPOOF_FUNC;

	return _FindWindowA(lpClassName, lpWindowName);
}

HWND __stdcall GetForegroundWindow_Spoofed() {
	SPOOF_FUNC;

	return _GetForegroundWindow();
}

SHORT GetAsyncKeyState_Spoofed(int vKey) {
	SPOOF_FUNC;

	return _GetAsyncKeyState(vKey);
}

SHORT MoveWindow_Spoofed(HWND hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint) {
	SPOOF_FUNC;

	return _MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
}

BOOL __stdcall PeekMessageA_Spoofed(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
	SPOOF_FUNC;

	return _PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

BOOL __stdcall TranslateMessage_Spoofed(const MSG* lpMsg) {
	SPOOF_FUNC;

	return _TranslateMessage(lpMsg);
}

LRESULT __stdcall DispatchMessageA_Spoofed(const MSG* lpMsg) {
	SPOOF_FUNC;

	return _DispatchMessageA(lpMsg);
}

HANDLE __stdcall CreateThread_Spoofed(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
	SPOOF_FUNC;

	return _CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

BOOL __stdcall CloseHandle_Spoofed(HANDLE hObject) {
	SPOOF_FUNC;

	return _CloseHandle(hObject);
}

BOOL __stdcall SetWindowPos_Spoofed(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {
	SPOOF_FUNC;

	return _SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

BOOL __stdcall ShowWindow_Spoofed(HWND hWnd, int nCmdShow) {
	SPOOF_FUNC;

	return _ShowWindow(hWnd, nCmdShow);
}

BOOL __stdcall SetWindowDisplayAffinity_Spoofed(HWND hWnd, DWORD dwAffinity) {
	SPOOF_FUNC;

	return _SetWindowDisplayAffinity(hWnd, dwAffinity);
}

BOOL __stdcall mouse_event_Spoofed(DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo) {
	SPOOF_FUNC;

	return _mouse_event(dwFlags, dx, dy, dwData, dwExtraInfo);
}

BOOL __stdcall UpdateWindow_Spoofed(HWND hWnd) {
	SPOOF_FUNC;

	return _UpdateWindow(hWnd);
}

BOOL __stdcall GetClientRect_Spoofed(HWND hWnd, LPRECT lpRect) {
	SPOOF_FUNC;

	return _GetClientRect(hWnd, lpRect);
}

BOOL __stdcall ClientToScreen_Spoofed(HWND hWnd, LPPOINT lpRect) {
	SPOOF_FUNC;

	return _ClientToScreen(hWnd, lpRect);
}













