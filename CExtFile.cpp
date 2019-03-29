#include "StdAfx.h"
#include "CExtFile.h"
#include <math.h>

/*
[功能] 删除后缀
[输入] csIn		文件完整路径
	   csSuffix	文件后缀名，如：'.dat'
[输出] CString	返回去掉后缀后的字符串
*/
CString RemoveSuffix(const CString csIn, const CString csSuffix){
	CString csOut;

	int nEnd = csIn.Find(csSuffix);
	for(int i=0; i<nEnd; i++){
		csOut += csIn.GetAt(i);
	}

	return csOut;
}

CExtFile::CExtFile(){
	m_csFilePath.Empty();
	m_nOpenFlags = NULL;
	m_csSubFile = NULL;
	m_nSubCNT = 0;
	m_nSubIndex = -1;
	m_nSubNo = 0;
	m_dwTotalSize = 2*1024;
	m_dwBlockSize = 1024;
	m_dwActSize = 0;
	m_bCycle = FALSE;
	m_bFileOpened = FALSE;
	m_dwNo = 0;
	m_szHeader = NULL;
}

/*
析构函数：
	1. 如果子文件没有关闭，则进行关闭。
	2. 删除素有临时子文件。
	3. 释放内存。
*/
CExtFile::~CExtFile(){
	for(UINT i=0; i<m_nSubCNT; i++){
		if(m_bFileOpened){
			m_File.Flush();
			m_File.Close();
			m_bFileOpened = FALSE;
		}
		if(m_csSubFile != NULL){
			if(m_csSubFile[i] != ""){
				CFile::Remove(m_csSubFile[i]);
				m_csSubFile[i].Empty();
			}
		}
		delete []m_csSubFile;
	}

	if(m_szHeader != NULL){
		delete[] m_szHeader;
		m_szHeader = NULL;
	}
}

BOOL CExtFile::Open(LPCTSTR lpszFileName, UINT nOpenFlags){
	if(m_dwBlockSize<=0 || m_dwTotalSize <= 0){
		return FALSE;
	}

	//计算需要的子文件个数
	m_nSubCNT = (UINT)ceil(1.0 * m_dwTotalSize / m_dwBlockSize);
	
	//保存文件完整路径
	m_csFilePath = lpszFileName;

	//保存文件创建标识
	m_nOpenFlags = nOpenFlags;

	//new 子文件路径数组
	m_csSubFile = new CString[m_nSubCNT];

	m_nSubIndex = 0;
	m_nSubNo = 0;
	m_bCycle = FALSE;
	m_dwActSize = 0;
	
	//获取子文件路径，并创建相应的文件打开句柄
	CString csFilePath = GetSubFilePath();
	if(!m_File.Open(csFilePath, CFile::modeWrite | CFile::modeCreate)){
		return FALSE;
	}

	//设置文件打开标识
	m_bFileOpened = TRUE;

	//隐藏子文件
	SetFileAttributes(csFilePath, FILE_ATTRIBUTE_HIDDEN);
	m_dwNo = 0;

	return TRUE;
}

void CExtFile::Write(const void* lpBuf, UINT nCount){
	CString csTime;
	CTime time = CTime::GetCurrentTime();
	csTime.Format("%04d%02d%02d_%02d:%02d:%02d", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	
	char szBuf[256];
	sprintf(szBuf, "%lu,%s,%s", ++m_dwNo, csTime.GetBuffer(csTime.GetLength()), (char*)lpBuf);
	nCount = strlen(szBuf);
	m_File.Write(szBuf, nCount);
	m_dwActSize += nCount;
	
	ChargeFileSize();
}

void CExtFile::WriteHeader(const void* lpBuf, UINT nCount){
	m_szHeader = new char[nCount];
	sprintf(m_szHeader, "%s", (char*)lpBuf);
}

void CExtFile::Close(){
	m_File.Close();
	m_bFileOpened = FALSE;

	CFile outFile;
	outFile.Open(m_csFilePath, m_nOpenFlags);

	CFile tempFile;
	CString csTempPath;
	if(m_bCycle){
		for(UINT i=0; i<m_nSubCNT; i++){
			m_nSubIndex++;
			if(m_nSubIndex == m_nSubCNT){
				m_nSubIndex = 0;
			}

			csTempPath = m_csSubFile[m_nSubIndex];
			tempFile.Open(csTempPath, CFile::modeRead);

			DWORD tempLen = (DWORD)tempFile.GetLength();
			BYTE *tempBuf = new BYTE[tempLen];
			tempFile.Read(tempBuf, tempLen);

			tempFile.Close();
			CFile::Remove(csTempPath);
			m_csSubFile[m_nSubIndex].Empty();

			if(i == 0){
				outFile.Write(m_szHeader, strlen(m_szHeader));
				outFile.Write("\r\n------\r\n", strlen("\r\n------\r\n"));
			}

			outFile.Write(tempBuf, tempLen);
			delete []tempBuf;
		}
	} else {
		for(UINT i=0; i<=m_nSubIndex; i++){
			csTempPath = m_csSubFile[i];
			tempFile.Open(csTempPath, CFile::modeRead);

			DWORD tempLen = (DWORD)tempFile.GetLength();
			BYTE* tempBuf = new BYTE[tempLen];
			tempFile.Read(tempBuf, tempLen);

			tempFile.Close();
			CFile::Remove(csTempPath);
			m_csSubFile[i].Empty();

			if(i == 0){
				outFile.Write(m_szHeader, strlen(m_szHeader));
				outFile.Write("\r\n------\r\n", strlen("\r\n------\r\n"));
			}

			outFile.Write(tempBuf, tempLen);
			delete []tempBuf;
		}
	}

	outFile.Close();
	if(m_csSubFile != NULL){
		delete[] m_csSubFile;
		m_csSubFile = NULL;
	}
}

CString CExtFile::GetSubFilePath(){
	CString csFilePath;
	csFilePath = RemoveSuffix(m_csFilePath, ".dat");
	
	CString csNo;
	csNo.Format("_%d", ++m_nSubNo);
	csFilePath += csNo;
	
	csFilePath += ".dat";
	
	//如果写满一个循环，则删除现存所有子文件中最早的那一个，因为其已经没用了。
	if(m_bCycle)
	{
		CFile::Remove(m_csSubFile[m_nSubIndex]);
	}
	
	m_csSubFile[m_nSubIndex] = csFilePath;
	
	return csFilePath;
}

void CExtFile::ChargeFileSize(){
	//如果块文件写满，则关闭该块文件句柄，并创建并打开新的块文件。
	if(m_dwActSize >= m_dwBlockSize)
	{
		m_File.Close();
		m_bFileOpened = FALSE;
		m_dwActSize = 0;
		
		m_nSubIndex++;
		if(m_nSubIndex == m_nSubCNT)
		{
			m_nSubIndex = 0;
			m_bCycle = TRUE;
		}
		
		CString csFilePath = GetSubFilePath();
		m_File.Open(csFilePath, CFile::modeWrite | CFile::modeCreate);
		m_bFileOpened = TRUE;
		SetFileAttributes(csFilePath, FILE_ATTRIBUTE_HIDDEN);
	}
}

void CExtFile::SetFileSize(DWORD size){
	m_dwTotalSize = size;	
}
