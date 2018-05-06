//
//	miscellaneous
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include <stdarg.h>
#include <stdio.h>
#include "Misc.h"
#include "dc.h"

//
// 与えたパス名のフルパスを得る
//
BOOL FullPath(char *path, const char *file)
{
	char *part;
	if (!GetFullPathName(file, _MAX_PATH, path, &part)) {
		strncpy(path, file, _MAX_PATH);
		return FALSE;
	}
	return TRUE;
}

#ifdef	_DEBUG

//
// デバッグメッセージ表示
//
void __cdecl DebugPrintf(const char *fmt, ...)
{
	char	tmp[4096];
	va_list	ap;

	va_start(ap, fmt);

	vsprintf(tmp, fmt, ap);
	OutputDebugString(tmp);

	va_end(ap);
}

//
// アサーション（ASSERTの補助関数）
//
bool AssertFailed(const char *exp, const char *file, unsigned line)
{
	DebugPrintf("Assertion failed: %s, file %s, line %d", exp, file, line);

	char	tmp[1024];
	sprintf(tmp, "%s, file %s, line %d", exp, file, line);

	HWND hWnd = ::GetActiveWindow();
	if (hWnd != NULL)
		hWnd = ::GetLastActivePopup(hWnd);

	MSG msg;
	BOOL bPostQuitNeed = ::PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
	int result = ::MessageBox(hWnd, tmp, "Assertion Failed",
		MB_TASKMODAL|MB_ICONHAND|MB_ABORTRETRYIGNORE|MB_SETFOREGROUND);
	if (bPostQuitNeed)
		PostQuitMessage(msg.wParam);

	switch (result) {
	  case IDIGNORE:
		return false;

	  case IDRETRY:
		return true;

	  default:
		abort();
	}
	return false;
}

#endif
