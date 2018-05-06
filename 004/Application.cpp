//
//	�t���[�����[�N�i�A�v���P�[�V�����j
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include <locale.h>
#include "Application.h"
#include "Misc.h"

#ifdef __BORLANDC__
static int WINAPI (*WinMainPtr)(HINSTANCE, HINSTANCE, LPSTR, int);
#endif

CWinApp *Application;

//
// �R���X�g���N�^
//
CWinApp::CWinApp()
{
#ifdef	_DEBUG
	if (Application != 0) {
		TRACE("CWinApp ���A���d�o�^����Ă��܂��B\n");
	}
#endif
	Instance = 0;
	CmdLine = 0;
	CmdShow = 0;

	Application = this;
	msgCur.message = WM_NULL;
	MainWnd = 0;

#ifdef __BORLANDC__
	// �����J�[�����܂������߁AWinMain���Q�Ƃ��Ă����B
	// ����ɈӖ��͖����B
	WinMainPtr = &WinMain;
#endif
}

//
// �f�X�g���N�^
//
CWinApp::~CWinApp()
{
	Application = 0;
}

//
// �A�v���P�[�V����������
//
BOOL CWinApp::InitInstance()
{
	return TRUE;
}

//
// IDLE����
//
BOOL CWinApp::OnIdle(long count)
{
	return MainWnd && MainWnd->OnIdle(count);
}

//
// ���b�Z�[�W���[�v
//
int CWinApp::Run()
{
	bool idle = true;
	long count = 0;

	if (MainWnd)
		MainWnd->ShowWindow(CmdShow);

	for (;;) {
		if (::PeekMessage(&msgCur, NULL, 0, 0, PM_NOREMOVE)) {
			if (!::GetMessage(&msgCur, NULL, 0, 0))
				return msgCur.wParam;

			if (!PreTranslateMessage(&msgCur)) {
				::TranslateMessage(&msgCur);
				::DispatchMessage(&msgCur);
			}
			idle = true;
			count = 0;
		}
		else if (idle) {
			if (!OnIdle(count++))
				idle = false;
		}
		else {
			::WaitMessage();
		}
	}
}

//
// ���b�Z�[�W�O����
//
BOOL CWinApp::PreTranslateMessage(MSG *msg)
{
	return MainWnd->PreTranslateMessage(msg);
}

//
// �E�C���h�E�N���X�o�^
//
//	�������O�ő��d�o�^�͂��Ȃ�
//
BOOL CWinApp::RegisterWndClass(const char *name, UINT classStyle, HCURSOR hCursor,
	HBRUSH hbrBackground, HICON hIcon)
{
	WNDCLASS	wndclass;

	if (!GetClassInfo(Instance, name, &wndclass)) {		// ���łɓo�^����Ă��邩�H
		wndclass.style = classStyle;
		wndclass.lpfnWndProc = CWindow::_WindowProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = Instance;
		wndclass.hIcon = hIcon;
		wndclass.hCursor = hCursor;
		wndclass.hbrBackground = hbrBackground;
		wndclass.lpszMenuName = 0;
		wndclass.lpszClassName = name;

		if (!::RegisterClass(&wndclass)) {
			TRACE("Can't register window class [%s]\n", name);
			return FALSE;
		}
	}
	return TRUE;
}
