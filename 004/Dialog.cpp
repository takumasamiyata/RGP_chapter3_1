//
//	フレームワーク（ダイアログ）
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "stdafx.h"
#include "Application.h"
#include "Dialog.h"

//
// (デフォルトの)ダイアログメッセージ処理関数
//
BOOL CDialog::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

//
// 共通のダイアログメッセージ処理関数
//
//	ここから、各クラスのメッセージ処理関数（メンバ関数）を呼び出す
//
BOOL CALLBACK CDialog::_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDialog *pThis = (CDialog *)GetWindowLong(hDlg, DWL_USER);

	if (uMsg == WM_INITDIALOG) {
		pThis = (CDialog *)lParam;
		pThis->hDlg = hDlg;
		SetWindowLong(hDlg, DWL_USER, lParam);
	}
	else if (!pThis) {
		return FALSE;
	}
	return pThis->DlgProc(uMsg, wParam, lParam);
}

//
// モーダルダイアログを開く
//
int CDialog::DoModal(UINT id, HWND hParent)
{
	return ::DialogBoxParam(*Application, MAKEINTRESOURCE(id), hParent, _DlgProc, (LPARAM)this);
}

//
// モードレスダイアログを開く
//
HWND CDialog::DoModeless(UINT id, HWND hParent)
{
	return ::CreateDialogParam(*Application, MAKEINTRESOURCE(id), hParent, _DlgProc, (LPARAM)this);
}

//
// ダイアログを親ウインドウの中央に配置する
//
void CDialog::CenterWindow()
{
	HWND	hParent = ::GetParent(hDlg);
	CRect	rectParent;
	CRect	rectWindow;

	::GetWindowRect(hDlg, &rectWindow);
	::GetClientRect(hParent, &rectParent);

	CPoint	pt(rectParent.Width() / 2, rectParent.Height() / 2);

	::ClientToScreen(hParent, &pt);

	int	width = rectWindow.Width();
	int	height = rectWindow.Height();

	pt.x -= width / 2;
	pt.y -= height / 2;

	::MoveWindow(hDlg, pt.x, pt.y, width, height, FALSE);
}
