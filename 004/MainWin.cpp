//
//	サンプルメインウインドウ
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include "file.h"
#include "Sample.h"
#include "Window.h"
#include "MainWin.h"
#include "resource.h"

//
// ウインドウ作成前処理
//
//	スタイルとサイズを指定する
//
BOOL CMainWin::PreCreateWindow(CREATESTRUCT &cs)
{
	cs.dwExStyle = WS_EX_CLIENTEDGE;
	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	// クライアントエリアから、ウインドウサイズを求める
	CRect	rect(0, 0, 640, 480);
	::AdjustWindowRectEx(&rect, cs.style, TRUE, cs.dwExStyle);

	int width = rect.Width();
	int height = rect.Height();

	// ワークエリアのサイズを求める。
	// ワークエリアとは、画面から「タスクバー」などの
	// 領域を取り除いたもの
	CRect rcArea;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);

	// ワークエリアの中心に来るように調整
	int	x = rcArea.left + (rcArea.Width() - width) / 2;
	int	y = rcArea.top + (rcArea.Height() - height) / 2;

	cs.x = x;
	cs.y = y;
	cs.cx = width;
	cs.cy = height;
	cs.lpszClass = "MainWindow";

	if (!Application->RegisterWndClass(cs.lpszClass,
		CS_VREDRAW | CS_HREDRAW | CS_OWNDC, LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)::GetStockObject(BLACK_BRUSH), Application->LoadIcon(IDC_APPICON)))
		return FALSE;
	return TRUE;
}

//
// メッセージ処理
//
LRESULT CMainWin::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	  case WM_ERASEBKGND:		// 背景を消去する
		return FALSE;			// 何もしない

	  default:
		return CWindow::WindowProc(uMsg, wParam, lParam);
	}
	return 0L;
}

//
// WM_CREATEの処理
//
BOOL CMainWin::OnCreate(CREATESTRUCT *cs)
{
	LoadAccelTable(IDC_APPACCEL);

	CFile	file("sample.bmp");	// サンプルCGをオープンする
	if (!file || !ViewImage.LoadBMP(file)) {
		MessageBox("CGファイルが読み出せません。");
		return FALSE;
	}
	return TRUE;
}

//
// WM_PAINTの処理（再描画）
//
void CMainWin::OnPaint()
{
	CPaintDC	dc(this);

	// 表示
	::SetDIBitsToDevice(dc, 0, 0,
		ViewImage.Width(), ViewImage.Height(),
		0, 0, 0, ViewImage.Height(),
		ViewImage.GetBits(),
		ViewImage.GetInfo(),
		DIB_RGB_COLORS);
}

//
// WM_COMMANDの処理（メニューの処理）
//
void CMainWin::OnCommand(UINT notifyCode, UINT id, HWND ctrl)
{
	switch (id) {
	  case ID_APP_EXIT:				// 終了
		SendMessage(WM_CLOSE);
		break;

	  default:
		break;
	}
}
