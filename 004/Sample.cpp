//
//	�T���v���A�v���P�[�V����
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#include "StdAfx.h"
#include "Sample.h"
#include "resource.h"

//
// �A�v���P�[�V�����̃C���X�^���X
//
CSampleApp	theApp;

//
// �A�v���P�[�V����������
//
BOOL CSampleApp::InitInstance()
{
	// ���C���E�C���h�E�̍쐬
	if (!MainWin.Create(this, "Sample", LoadMenu(IDC_APPMENU)))
		return FALSE;

	MainWnd = &MainWin;

	return TRUE;
}
