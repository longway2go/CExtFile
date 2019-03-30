//////////////////////////////////////////////////////////////////////////
// CExtFile.h
// Goal  : 扩展File类，实现只写入最近一定大小的数据，类似于行车记录仪的功能。
// Author: Bob
// Create: 2018-03-30
// Modify: 2018-04-03
// Modify: 2019-03-29  （对代码添加注释，并添加缓存区以减少磁盘写入的频率。）
//////////////////////////////////////////////////////////////////////////
#pragma once

class CExtFile
{
public:
	CExtFile();
	~CExtFile();

	/*
	[功能] 创建文件句柄。
	[输入] lpszFileName	文件保存路径
		   nOpenFlags	文件创建标识
	[输出] BOOL true:文件打开成功；false:文件打开失败。
	*/
	BOOL		Open(LPCTSTR lpszFileName, UINT nOpenFlags);

	/*
	[功能] 写文件。
	[输入] lpBuf	流数据指针
		   nCount	流数据字符大小
	*/
	void		Write(const void* lpBuf, UINT nCount);

	/*
	[功能] 写文件头。
	[输入] lpBuf	流数据指针
		   nCount	流数据字符大小
	*/
	void		WriteHeader(const void* lpBuf, UINT nCount);
	
	/*
	[功能] 关闭文件句柄。
	*/
	void		Close();
	
	/*
	[功能] 设置文件大小。
		   CExtFile类似于行车记录仪的功能，只能保存一定文件大小的文件。
	[输入] size: 文件的预期总大小。实际文件≤m_dwTotalSize+m_dwBlockSize。
	*/
	void		SetFileSize(DWORD size);

	/*
	[功能] 设置缓存大小。
		   设置缓存之后，会先将流数据放到缓存中。缓存满了再写入到磁盘文件中。这样是为了减少磁盘的写入频率，不用每次数据进来都要执行一次IO写入操作。
		   需要使用人员自己把握，设置合理的缓存大小。
	[输入] size:	
	*/
	void		SetBufferSize(DWORD size);

private:
	/*
	[功能]
	[输入]
	[输出] CString 返回子文件路径
	*/
	CString		GetSubFilePath();

	/*
	[功能] 如果子文件大小≥m_dwBlockSize，则关闭该子文件，并创建新的子文件。
	*/
	void		ChargeFileSize();

private:
	//文件保存路径
	CString		m_csFilePath;
	
	//子文件路径数组
	CString*	m_csSubFile;
	
	//文件创建标识
	UINT		m_nOpenFlags;
	
	//子文件个数
	UINT		m_nSubCNT;
	
	//子文件路径索引。不能超过m_nSubCNT。一旦超过，则又从0开始。即确保子文件路径始终都只保存在m_csSubFile中。
	UINT		m_nSubIndex;
	
	//子文件总共创建的个数。从1开始计数，依次递增。
	UINT		m_nSubNo;		
	
	//块大小，即子文件的大小
	DWORD		m_dwBlockSize;	
	
	//块文件实际写入大小
	DWORD		m_dwActSize;	
	
	//是否写满一个循环
	BOOL		m_bCycle;		
	
	CFile		m_File;			
	
	//文件是否打开标识
	BOOL		m_bFileOpened;
	
	//预期的回放文件尺寸
	DWORD		m_dwTotalSize;
	
	//记录文件的写入次数
	DWORD		m_dwNo;	
	
	//头文件
	char*		m_szHeader;

	//缓存
	char*		m_szBuffer;
	
	//缓存大小
	DWORD		m_dwBufferLen;
};

