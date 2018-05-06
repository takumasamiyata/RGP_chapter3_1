//
//	フレームワーク（DC ラッパ）
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include "Window.h"
#include "Misc.h"
#include "dc.h"

//
// CDCデストラクタ
//
CDC::~CDC()
{
}

//
// CClientDCコンストラクタ
//
CClientDC::CClientDC(CWindow *win)
{
	hWnd = *win;
	hDC = ::GetDC(hWnd);
}

//
// CClientDCデストラクタ
//
CClientDC::~CClientDC()
{
	::ReleaseDC(hWnd, hDC);
}

//
// CPaintDCコンストラクタ
//
CPaintDC::CPaintDC(CWindow *win)
{
	hWnd = *win;
	hDC = ::BeginPaint(hWnd, &ps);
}

//
// CPaintDCデストラクタ
//
CPaintDC::~CPaintDC()
{
	::EndPaint(hWnd, &ps);
}

//
// CMemoryDCコンストラクタ
//
CMemoryDC::CMemoryDC(HDC hdc)
{
	hDC = ::CreateCompatibleDC(hdc);
}

//
// CMemoryDCデストラクタ
//
CMemoryDC::~CMemoryDC()
{
	::DeleteDC(hDC);
}

//
// CScreenDCコンストラクタ
//
CScreenDC::CScreenDC()
{
	hDC = ::GetDC(0);
}

//
// CScreenDCデストラクタ
//
CScreenDC::~CScreenDC()
{
	::ReleaseDC(0, hDC);
}
