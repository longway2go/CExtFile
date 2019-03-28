//////////////////////////////////////////////////////////////////////////
// CExtFile.h
// Goal  : Extend File Class. Enable to write a certain recently records.
// Author: Bob
// Create: 2018-03-30
// Modify: 2018-04-03
//////////////////////////////////////////////////////////////////////////
#pragma once

class CExtFile
{
public:
	CExtFile();
	~CExtFile();

	BOOL		Open(LPCTSTR lpszFileName, UINT nOpenFlags);
	void		Write(const void* lpBuf, UINT nCount);
	void		WriteHeader(const void* lpBuf, UINT nCount);
	void		Close();
	void		SetFileSize(DWORD size);

private:
	CString		GetSubFilePath();
	void		ChargeFileSize();

private:
	CString		m_csFilePath;
	CString*	m_csSubFile;
	UINT		m_nOpenFlags;
	UINT		m_nSubCNT;
	UINT		m_nSubIndex;	
	UINT		m_nSubNo;		
	DWORD		m_dwBlockSize;	
	DWORD		m_dwActSize;	
	BOOL		m_bCycle;		
	CFile		m_File;			
	BOOL		m_bFileOpened;
	DWORD		m_dwTotalSize;
	DWORD		m_dwNo;	
	char*		m_szHeader;
};

