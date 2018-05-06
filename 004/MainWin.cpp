//
//	�T���v�����C���E�C���h�E
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
// �E�C���h�E�쐬�O����
//
//	�X�^�C���ƃT�C�Y���w�肷��
//
BOOL CMainWin::PreCreateWindow(CREATESTRUCT &cs)
{
	cs.dwExStyle = WS_EX_CLIENTEDGE;
	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	// �N���C�A���g�G���A����A�E�C���h�E�T�C�Y�����߂�
	CRect	rect(0, 0, 640, 480);
	::AdjustWindowRectEx(&rect, cs.style, TRUE, cs.dwExStyle);

	int width = rect.Width();
	int height = rect.Height();

	// ���[�N�G���A�̃T�C�Y�����߂�B
	// ���[�N�G���A�Ƃ́A��ʂ���u�^�X�N�o�[�v�Ȃǂ�
	// �̈����菜��������
	CRect rcArea;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);

	// ���[�N�G���A�̒��S�ɗ���悤�ɒ���
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
// ���b�Z�[�W����
//
LRESULT CMainWin::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	  case WM_ERASEBKGND:		// �w�i����������
		return FALSE;			// �������Ȃ�

	  default:
		return CWindow::WindowProc(uMsg, wParam, lParam);
	}
	return 0L;
}

//
// WM_CREATE�̏���
//
BOOL CMainWin::OnCreate(CREATESTRUCT *cs)
{
	LoadAccelTable(IDC_APPACCEL);

	CFile	file("sample.bmp");	// �T���v��CG���I�[�v������
	if (!file || !ViewImage.LoadBMP(file)) {
		MessageBox("CG�t�@�C�����ǂݏo���܂���B");
		return FALSE;
	}
	return TRUE;
}

//
// WM_PAINT�̏����i�ĕ`��j
//
void CMainWin::OnPaint()
{
	CPaintDC	dc(this);

	// �\��
	::SetDIBitsToDevice(dc, 0, 0,
		ViewImage.Width(), ViewImage.Height(),
		0, 0, 0, ViewImage.Height(),
		ViewImage.GetBits(),
		ViewImage.GetInfo(),
		DIB_RGB_COLORS);
}

//
// WM_COMMAND�̏����i���j���[�̏����j
//
void CMainWin::OnCommand(UINT notifyCode, UINT id, HWND ctrl)
{
	switch (id) {
	  case ID_APP_EXIT:				// �I��
		SendMessage(WM_CLOSE);
		break;

	  default:
		break;
	}
}
