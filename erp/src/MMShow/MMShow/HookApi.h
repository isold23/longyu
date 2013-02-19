#ifndef __HookApi_h__
#define __HookApi_h__

#ifdef	DLL_EXPORT
#define	DLLAPI	__declspec(dllexport)
#else
#define	DLLAPI	__declspec(dllimport)
#endif

#include <Windows.h>

#ifdef	__cplusplus
extern "C" {
#endif

	BOOL	DLLAPI	set_hook	( HMODULE hMod );
	BOOL	DLLAPI	remove_hook	();

#ifdef	__cplusplus
}
#endif

#endif // __HookApi_h__

#define DLL_EXPORT
#include "HookApi.h"
#include <string.h>
#include <ImageHlp.h>
#include <TlHelp32.h>
#pragma comment( lib, "ImageHlp.lib" )

#pragma data_seg( "share" )
HINSTANCE		g_hInstance	= NULL;
HHOOK			g_hHook		= NULL;
HMODULE			g_hMod		= NULL;
#pragma data_seg()

#pragma comment( linker, "/section:share,RWS" )

//////////////////////////////////////////////////////////////////////////

BOOL	WINAPI		message_box_a	( HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType );
BOOL	WINAPI		message_box_w	( HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType );

BOOL	CALLBACK	hook_api	( const char *lpszModuleName, PROC procOrg, PROC procDst );
BOOL	CALLBACK	unhook_api	( const char *lpszModuleName, PROC procOrg, PROC procDst );

LRESULT CALLBACK	hook_proc	( UINT nCode, WPARAM wParam, LPARAM lParam );

//////////////////////////////////////////////////////////////////////////

int APIENTRY DllMain( HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved )
{
	switch( dwReason ) {
		case DLL_PROCESS_ATTACH:
			g_hInstance = hInst;
			break;
		case DLL_PROCESS_DETACH:
			remove_hook();
			break;
		default:
			break;
	}
	return TRUE;
}

BOOL DLLAPI set_hook( HMODULE hMod )
{
	if( NULL == hMod || NULL != g_hHook )
		return FALSE;

	g_hMod = hMod;
	g_hHook = SetWindowsHookEx( WH_GETMESSAGE, (HOOKPROC)hook_proc, g_hInstance, 0 );
	if( NULL == g_hHook )
		return FALSE;

	hook_api( "User32.dll", GetProcAddress(GetModuleHandle("User32.dll"), "MessageBoxA"),
		(PROC)&message_box_a );
	hook_api( "User32.dll", GetProcAddress(GetModuleHandle("User32.dll"), "MessageBoxW"),
		(PROC)&message_box_w );

	return TRUE;
}

BOOL DLLAPI remove_hook()
{
	if( NULL == g_hMod || NULL == g_hHook )
		return FALSE;

	unhook_api( "User32.dll", GetProcAddress(GetModuleHandle("User32.dll"), "MessageBoxA"),
		(PROC)&message_box_a );
	unhook_api( "User32.dll", GetProcAddress(GetModuleHandle("User32.dll"), "MessageBoxW"),
		(PROC)&message_box_w );

	UnhookWindowsHookEx( g_hHook );
	g_hHook = NULL;
	g_hMod	= NULL;

	return TRUE;
}

LRESULT CALLBACK hook_proc( UINT nCode, WPARAM wParam, LPARAM lParam )
{
	return CallNextHookEx( g_hHook, nCode, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////

BOOL WINAPI message_box_a( HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType )
{
	const char *caption = "hooked caption";
	return MessageBoxA( hWnd, lpText, caption, uType );
}

BOOL WINAPI message_box_w( HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType )
{
	const wchar_t *caption = L"HOOKED CAPTION";
	return MessageBoxW( hWnd, lpText, caption, uType );
}

//////////////////////////////////////////////////////////////////////////

BOOL CALLBACK hook_api( const char *lpszModuleName, PROC procOrg, PROC procDst )
{
	char						*pszDllName		= NULL;
	IMAGE_DOS_HEADER			*pDosHeader		= NULL;
	IMAGE_OPTIONAL_HEADER		*pOptHeader		= NULL;
	IMAGE_IMPORT_DESCRIPTOR		*pImportDesc	= NULL;
	IMAGE_THUNK_DATA			*pThunk			= NULL;
	PROC						*lpAddr			= NULL;
	PROC						*lpNewAddr		= NULL;
	DWORD						dwOldProtect	= 0;
	MEMORY_BASIC_INFORMATION	mbi				= { 0 };

	if( NULL == lpszModuleName || NULL == procOrg || NULL == procDst || NULL == g_hMod )
		return FALSE;

	pDosHeader = (IMAGE_DOS_HEADER*)g_hMod;
	pOptHeader = (IMAGE_OPTIONAL_HEADER*)( (PBYTE)g_hMod + pDosHeader->e_lfanew + 24 );
	pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*)( (PBYTE)g_hMod + pOptHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress );

	while( pImportDesc->FirstThunk ) {
		pszDllName = (char*)( (PBYTE)g_hMod + pImportDesc->Name );
		if( 0 == _stricmp(pszDllName, lpszModuleName) )
			break;
		pImportDesc++;
	}

	if( pImportDesc->FirstThunk ) {
		pThunk = (IMAGE_THUNK_DATA*)( (PBYTE)g_hMod + pImportDesc->FirstThunk );
		while( pThunk->u1.Function ) {
			lpAddr = (PROC*)&(pThunk->u1.Function);
			if( *lpAddr == procOrg ) {
				VirtualQuery( lpAddr, &mbi, sizeof(mbi) );
				VirtualProtect( lpAddr, sizeof(PROC), PAGE_READWRITE, &dwOldProtect );
				lpNewAddr = (PROC*)&procDst;
				WriteProcessMemory( GetCurrentProcess(), lpAddr, lpNewAddr, sizeof(PROC), NULL );
				VirtualProtect( lpAddr, sizeof(PROC), dwOldProtect, 0 );
				return TRUE;
			}
			pThunk++;
		}
	}

	return FALSE;
}

BOOL CALLBACK unhook_api( const char *lpszModuleName, PROC procOrg, PROC procDst )
{
	PROC temp = procOrg;
	procOrg = procDst;
	procDst = temp;
	return hook_api( lpszModuleName, procOrg, procDst );
}

void ToNullFunc(HANDLE hDll,LPCSTR pcszFunc)
{
	FARPROC pFunc = GetProcAddress(hDll,pcszFunc);
	if (pFunc != NULL)
	{
		DWORD flag;
		VirtualProtect(pFunc,3,PAGE_EXECUTE_READWRITE,&flag);
		memcpy(pFunc,(void*)0xC20C00,3);
	}
}

void MuteSound(void)
{
	HANDLE hDSound = LoadLibrary("DSound.dll");
	if (hDSound != NULL)
		ToNullFunc(hDSound,"DirectSoundCreate");		

	HANDLE hWinmm = LoadLibrary("Winmm.dll");
	if (hWinmm != NULL)
	{
		ToNullFunc(hWinmm,"midiStreamOpen");
		ToNullFunc(hWinmm,"waveOutWrite");	
	}
}
