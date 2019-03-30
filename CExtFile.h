//////////////////////////////////////////////////////////////////////////
// CExtFile.h
// Goal  : ��չFile�࣬ʵ��ֻд�����һ����С�����ݣ��������г���¼�ǵĹ��ܡ�
// Author: Bob
// Create: 2018-03-30
// Modify: 2018-04-03
// Modify: 2019-03-29  ���Դ������ע�ͣ�����ӻ������Լ��ٴ���д���Ƶ�ʡ���
//////////////////////////////////////////////////////////////////////////
#pragma once

class CExtFile
{
public:
	CExtFile();
	~CExtFile();

	/*
	[����] �����ļ������
	[����] lpszFileName	�ļ�����·��
		   nOpenFlags	�ļ�������ʶ
	[���] BOOL true:�ļ��򿪳ɹ���false:�ļ���ʧ�ܡ�
	*/
	BOOL		Open(LPCTSTR lpszFileName, UINT nOpenFlags);

	/*
	[����] д�ļ���
	[����] lpBuf	������ָ��
		   nCount	�������ַ���С
	*/
	void		Write(const void* lpBuf, UINT nCount);

	/*
	[����] д�ļ�ͷ��
	[����] lpBuf	������ָ��
		   nCount	�������ַ���С
	*/
	void		WriteHeader(const void* lpBuf, UINT nCount);
	
	/*
	[����] �ر��ļ������
	*/
	void		Close();
	
	/*
	[����] �����ļ���С��
		   CExtFile�������г���¼�ǵĹ��ܣ�ֻ�ܱ���һ���ļ���С���ļ���
	[����] size: �ļ���Ԥ���ܴ�С��ʵ���ļ���m_dwTotalSize+m_dwBlockSize��
	*/
	void		SetFileSize(DWORD size);

	/*
	[����] ���û����С��
		   ���û���֮�󣬻��Ƚ������ݷŵ������С�����������д�뵽�����ļ��С�������Ϊ�˼��ٴ��̵�д��Ƶ�ʣ�����ÿ�����ݽ�����Ҫִ��һ��IOд�������
		   ��Ҫʹ����Ա�Լ����գ����ú���Ļ����С��
	[����] size:	
	*/
	void		SetBufferSize(DWORD size);

private:
	/*
	[����]
	[����]
	[���] CString �������ļ�·��
	*/
	CString		GetSubFilePath();

	/*
	[����] ������ļ���С��m_dwBlockSize����رո����ļ����������µ����ļ���
	*/
	void		ChargeFileSize();

private:
	//�ļ�����·��
	CString		m_csFilePath;
	
	//���ļ�·������
	CString*	m_csSubFile;
	
	//�ļ�������ʶ
	UINT		m_nOpenFlags;
	
	//���ļ�����
	UINT		m_nSubCNT;
	
	//���ļ�·�����������ܳ���m_nSubCNT��һ�����������ִ�0��ʼ����ȷ�����ļ�·��ʼ�ն�ֻ������m_csSubFile�С�
	UINT		m_nSubIndex;
	
	//���ļ��ܹ������ĸ�������1��ʼ���������ε�����
	UINT		m_nSubNo;		
	
	//���С�������ļ��Ĵ�С
	DWORD		m_dwBlockSize;	
	
	//���ļ�ʵ��д���С
	DWORD		m_dwActSize;	
	
	//�Ƿ�д��һ��ѭ��
	BOOL		m_bCycle;		
	
	CFile		m_File;			
	
	//�ļ��Ƿ�򿪱�ʶ
	BOOL		m_bFileOpened;
	
	//Ԥ�ڵĻط��ļ��ߴ�
	DWORD		m_dwTotalSize;
	
	//��¼�ļ���д�����
	DWORD		m_dwNo;	
	
	//ͷ�ļ�
	char*		m_szHeader;

	//����
	char*		m_szBuffer;
	
	//�����С
	DWORD		m_dwBufferLen;
};

