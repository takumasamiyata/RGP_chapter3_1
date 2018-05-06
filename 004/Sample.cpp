//
//	サンプルアプリケーション
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include "Sample.h"
#include "resource.h"

//
// アプリケーションのインスタンス
//
CSampleApp	theApp;

//
// アプリケーション初期化
//
BOOL CSampleApp::InitInstance()
{
	// メインウインドウの作成
	if (!MainWin.Create(this, "Sample", LoadMenu(IDC_APPMENU)))
		return FALSE;

	MainWnd = &MainWin;

	return TRUE;
}
