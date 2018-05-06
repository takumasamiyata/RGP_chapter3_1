//
//	�t�@�C�����o��
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#ifndef __FILE_H__
#define __FILE_H__

#include <io.h>
#include <stdio.h>
#include <share.h>

//
//	CFile�N���X
//
class CFile {
  public:
	enum	{
		read,
		write,
	} ;
	enum	{
		begin = SEEK_SET,
		current = SEEK_CUR,
		end = SEEK_END,
	} ;

  public:
	CFile(): fp(0) {}
	CFile(const char *file, int mode=read);
	~CFile();

	bool Open(const char *file, int mode=read);
	bool Close();

	int Read(void *buffer, int length);
	int Write(const void *buffer, int length);
	long Seek(long offset, int from);
#ifdef _MSC_VER
	long GetFileSize() { return _filelength(_fileno(fp)); }
#else
  #ifdef __BORLANDC__
	long GetFileSize() { return filelength(_fileno(fp)); }
  #endif
#endif

	bool IsOk() const { return fp != 0; }
	bool Error() { return ferror(fp) != 0; }

	bool operator !() { return fp == 0 || ferror(fp) != 0; }

  protected:
	FILE *fp;
} ;

// �C�����C�������o�֐�

// �R���X�g���N�^
//
//	�t�@�C���̃I�[�v���𔺂��\�z
//
inline CFile::CFile(const char *file, int mode)
{
	Open(file, mode);
}

//
// �f�X�g���N�^
//
//	�N���[�Y����Ă��Ȃ��ꍇ�A�N���[�Y����
//
inline CFile::~CFile()
{
	Close();
}

//
// �t�@�C���̃I�[�v��
//
//	mode �� �ǂݏo��:CFile::read, ��������:CFile::write �ƁA�w�肷��
//
inline bool CFile::Open(const char *file, int mode)
{
#ifdef _MSC_VER
	fp = _fsopen(file, mode == read? "rb": "wb", _SH_DENYWR);
#else
	fp = fopen(file, mode == read? "rb": "wb");
#endif
	return fp != 0;
}

//
// �N���[�Y
//
inline bool CFile::Close()
{
	if (fp != 0) {
		fclose(fp);
		fp = 0;
	}
	return TRUE;
}

//
// �ǂݏo��
//
inline int CFile::Read(void *buffer, int length)
{
	return fread(buffer, 1, length, fp);
}

//
// ��������
//
inline int CFile::Write(const void *buffer, int length)
{
	return fwrite(buffer, 1, length, fp);
}

//
// �t�@�C���A�N�Z�X�ʒu�̕ύX
//
inline long CFile::Seek(long offset, int from)
{
	return fseek(fp, offset, from);
}

#endif
