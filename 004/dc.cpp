//
//	�t���[�����[�N�iDC ���b�p�j
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include "Window.h"
#include "Misc.h"
#include "dc.h"

//
// CDC�f�X�g���N�^
//
CDC::~CDC()
{
}

//
// CClientDC�R���X�g���N�^
//
CClientDC::CClientDC(CWindow *win)
{
	hWnd = *win;
	hDC = ::GetDC(hWnd);
}

//
// CClientDC�f�X�g���N�^
//
CClientDC::~CClientDC()
{
	::ReleaseDC(hWnd, hDC);
}

//
// CPaintDC�R���X�g���N�^
//
CPaintDC::CPaintDC(CWindow *win)
{
	hWnd = *win;
	hDC = ::BeginPaint(hWnd, &ps);
}

//
// CPaintDC�f�X�g���N�^
//
CPaintDC::~CPaintDC()
{
	::EndPaint(hWnd, &ps);
}

//
// CMemoryDC�R���X�g���N�^
//
CMemoryDC::CMemoryDC(HDC hdc)
{
	hDC = ::CreateCompatibleDC(hdc);
}

//
// CMemoryDC�f�X�g���N�^
//
CMemoryDC::~CMemoryDC()
{
	::DeleteDC(hDC);
}

//
// CScreenDC�R���X�g���N�^
//
CScreenDC::CScreenDC()
{
	hDC = ::GetDC(0);
}

//
// CScreenDC�f�X�g���N�^
//
CScreenDC::~CScreenDC()
{
	::ReleaseDC(0, hDC);
}
