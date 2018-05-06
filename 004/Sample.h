//
//	サンプルアプリケーション
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#ifndef	__Sample_h__
#define	__Sample_h__

#include "Application.h"
#include "MainWin.h"

//
// アプリケーションクラス
//
class CSampleApp: public CWinApp {
  public:
	BOOL InitInstance();

  protected:
	CMainWin	MainWin;
} ;

#endif
