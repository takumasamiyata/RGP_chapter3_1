//
//	�t���[�����[�N�i�E�C���h�E�j
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include "Application.h"
#include "Window.h"
#include "Misc.h"
#include "dc.h"

//
// �E�C���h�E���X�g�̃��[�g
//
CWindow *CWindow::WindowListTop;

//
// �쐬���̈ꎞ�I�|�C���^
//
CWindow *CWindow::WindowInitPtr;

//
// �R���X�g���N�^
//
CWindow::CWindow()
{
	App = 0;
	hWnd = 0;
	LastMsg = WM_NULL;
	LastWParam = 0;
	LastLParam = 0;

	hAccelTable = 0;

	Next = 0;
}

//
// �f�X�g���N�^
//
CWindow::~CWindow()
{
}

//
// �E�C���h�E���X�g����w���CWindow�I�u�W�F�N�g�𓾂�
//
CWindow *CWindow::GetWindow(HWND hwnd)
{
	for (CWindow *p=WindowListTop; p; p=p->Next) {
		if (p->hWnd == hwnd)
			return p;
	}
	return 0;
}

//
// �E�C���h�E���X�g�ɃE�C���h�E��o�^
//
BOOL CWindow::AddWindowList(HWND hWndNew)
{
	Next = WindowListTop;
	WindowListTop = this;
	hWnd = hWndNew;
	return TRUE;
}

//
// �E�C���h�E���X�g����E�C���h�E���폜
//
HWND CWindow::DeleteWindowList()
{
	for (CWindow **p = &WindowListTop; *p; p = &((*p)->Next)) {
		if (*p == this) {
			*p = Next;
			break;
		}
	}
	return hWnd;
}

//
// ���b�Z�[�W�����֐�(����)
//
//	(�����o�֐���)���b�Z�[�W�����֐����Ăяo��
//
LRESULT CALLBACK CWindow::_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindow *win = GetWindow(hwnd);

	if (win == 0 && WindowInitPtr != 0) {
		win = WindowInitPtr;
		WindowInitPtr->AddWindowList(hwnd);
		WindowInitPtr = 0;
	}
	if (win) {
		win->SetLastParam(uMsg, wParam, lParam);
		return win->WindowProc(uMsg, wParam, lParam);
	}
	return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//
// �L�[�{�[�h�A�N�Z�����[�V�����e�[�u���̓ǂݍ���
//
BOOL CWindow::LoadAccelTable(const char *name)
{
	hAccelTable = Application->LoadAccelerators(name);
	return (hAccelTable != NULL);
}

//
// ���b�Z�[�W�̑O����
//
BOOL CWindow::PreTranslateMessage(MSG *msg)
{
	if (msg->message >= WM_KEYFIRST && msg->message <= WM_KEYLAST) {
		return hAccelTable != NULL && ::TranslateAccelerator(hWnd, hAccelTable, msg);
	}
	return FALSE;
}

//
// �E�C���h�E�̍쐬
//
BOOL CWindow::Create(CWinApp *app, const char *name, HMENU hMenu, CWindow *parent)
{
	App = app;

	CREATESTRUCT cs;
	cs.dwExStyle = WS_EX_CLIENTEDGE;
	cs.lpszClass = NULL;
	cs.lpszName = name;
	cs.style = WS_OVERLAPPEDWINDOW;
	cs.x = CW_USEDEFAULT;
	cs.y = CW_USEDEFAULT;
	cs.cx = CW_USEDEFAULT;
	cs.cy = CW_USEDEFAULT;
	cs.hwndParent = parent? parent->hWnd: 0;
	cs.hMenu = hMenu;
	cs.hInstance = *app;
	cs.lpCreateParams = 0;

	if (!PreCreateWindow(cs))
		return FALSE;

	if (cs.lpszClass == 0) {
		cs.lpszClass = "Window";
		if (!Application->RegisterWndClass(cs.lpszClass, CS_VREDRAW | CS_HREDRAW))
			return FALSE;
	}

	WindowInitPtr = this;
	HWND hWnd = ::CreateWindowEx(cs.dwExStyle, cs.lpszClass,
		cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy,
		cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);

	if (WindowInitPtr != NULL) {
		WindowInitPtr = NULL;
		return FALSE;
	}
	if (hWnd == NULL)
		return FALSE;
	return TRUE;
}

//
// �E�C���h�E�쐬�̑O����
//
BOOL CWindow::PreCreateWindow(CREATESTRUCT &cs)
{
	return TRUE;
}

//
// �����o�֐��̃��b�Z�[�W�����֐�
//
LRESULT CWindow::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	  case WM_CREATE:
		if (!OnCreate((LPCREATESTRUCT)lParam))
			return -1;
		break;

	  case WM_PAINT:
		OnPaint();
		break;

	  case WM_DESTROY:
		OnDestroy();
		break;

	  case WM_COMMAND:
		OnCommand(HIWORD(wParam), LOWORD(wParam), (HWND)lParam);
		break;

	  case WM_INITMENUPOPUP:
		OnInitMenuPopup((HMENU)wParam, LOWORD(lParam), HIWORD(lParam));
		break;

	  case WM_NCDESTROY:
		DeleteWindowList();
		break;

	  default:
		return Default();
	}
	return 0L;
}

//
// IDLE����
//
BOOL CWindow::OnIdle(long count)
{
	return FALSE;
}

//
// WM_CREATE�̏����֐�
//
BOOL CWindow::OnCreate(CREATESTRUCT *cs)
{
	return TRUE;
}

//
// WM_PAINT�̏����֐�
//
void CWindow::OnPaint()
{
	CPaintDC	dc(this);	// OnPaint�̒��ł�CPaintDC�𐶐�����
							// BeginPaint, EndPaint���ĂԂ���
}

//
// WM_DESTROY�̏����֐�
//
void CWindow::OnDestroy()
{
	::PostQuitMessage(0);
}

//
// WM_COMMAND�̏����֐�
//
void CWindow::OnCommand(UINT notifyCode, UINT id, HWND ctrl)
{
}

//
// WM_INITMENUPOPUP�̏����֐�
//
//	���j���[���ڂ��Ƃ�OnInitSubMenu���Ăяo��
//
void CWindow::OnInitMenuPopup(HMENU hMenu, UINT, BOOL sysMenu)
{
	if (sysMenu)
		return;

	int indexMax = ::GetMenuItemCount(hMenu);
	for (int index=0; index < indexMax; index++) {
		OnInitSubMenu(hMenu, ::GetMenuItemID(hMenu, index));
	}
}

void CWindow::OnInitSubMenu(HMENU hMenu, UINT id)
{
}
