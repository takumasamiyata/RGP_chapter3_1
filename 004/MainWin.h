//
//	�T���v�����C���E�C���h�E
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#ifndef __MainWin_h__
#define __MainWin_h__

#include "Window.h"
#include "dib.h"
#include "dc.h"

//
//	���C���E�C���h�E�N���X
//
class CMainWin: public CWindow {
  public:
	LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void OnCommand(UINT notifyCode, UINT id, HWND ctrl);

  protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);

	BOOL OnCreate(CREATESTRUCT *cs);
	void OnPaint();

  protected:
	CDib ViewImage;				// �\��
} ;

#endif
