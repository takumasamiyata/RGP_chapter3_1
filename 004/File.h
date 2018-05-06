//
//	ファイル入出力
//
//		Copyright (c) 2000-2001 Chihiro.SAKAMOTO (HyperWorks)
//
#ifndef __FILE_H__
#define __FILE_H__

#include <io.h>
#include <stdio.h>
#include <share.h>

//
//	CFileクラス
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

// インラインメンバ関数

// コンストラクタ
//
//	ファイルのオープンを伴う構築
//
inline CFile::CFile(const char *file, int mode)
{
	Open(file, mode);
}

//
// デストラクタ
//
//	クローズされていない場合、クローズする
//
inline CFile::~CFile()
{
	Close();
}

//
// ファイルのオープン
//
//	mode は 読み出し:CFile::read, 書き込み:CFile::write と、指定する
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
// クローズ
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
// 読み出し
//
inline int CFile::Read(void *buffer, int length)
{
	return fread(buffer, 1, length, fp);
}

//
// 書き込み
//
inline int CFile::Write(const void *buffer, int length)
{
	return fwrite(buffer, 1, length, fp);
}

//
// ファイルアクセス位置の変更
//
inline long CFile::Seek(long offset, int from)
{
	return fseek(fp, offset, from);
}

#endif
