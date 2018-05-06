//
//	フレームワーク（メイン）
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include "Application.h"
#include "Misc.h"

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR CmdLine, int CmdShow)
{
#if defined(_MSC_VER) && defined(_DEBUG)
	// メモリリークのチェック
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	if (Application == 0) {
		TRACE("CWinApp が登録されていない。\n");
		return -1;
	}

	Application->SetWinMainArgs(hInstance, CmdLine, CmdShow);

	if (!Application->InitInstance())
		return -1;

	return Application->Run();
}
