#pragma once

/*******************************************************************************
										Created on 06/15/02 By K.Matsubayashi
										Copyright 2002 K.Matsubayashi
	�f�[�^�x�[�X���W���[��

	MDB.h

*******************************************************************************/
//
/*
#define	MaxSzMdbBuf		2000000				// �l�c�a�o�b�t�@�T�C�Y
#define MaxMdbRecId		30000				// �G���e�B�e�B���R�[�h�̂h�c�ő�l
#define	MaxSzMdbRec		62383				// �G���e�B�e�B���R�[�h�ő�T�C�Y
#define MinszMdbRec		10					// �G���e�B�e�B���R�[�h�ŏ��T�C�Y
*/
// �����l
#define	MaxSzMdbBuf		2000000				// �l�c�a�o�b�t�@�T�C�Y
#define MaxMdbRecId		30					// �G���e�B�e�B���R�[�h�̂h�c�ő�l
#define	MaxSzMdbRec		21					// �G���e�B�e�B���R�[�h�ő�T�C�Y
#define MinSzMdbRec		8					// �G���e�B�e�B���R�[�h�ŏ��T�C�Y
// �X�e�C�^�X
#define	FEMPTY			0					// ��
#define F_OVERFLOW		-101				// �I�[�o�[�t���[�G���[�X�e�C�^�X
#define F_NOERROR		0					// ����
#define F_NOITEM		-1					// �����Ȃ��@���[�j���O
#define F_IDERROR		-201				// �G���e�B�e�B���R�[�h�h�c�G���[
#define F_POSERROR		-202				// �G���e�B�e�B���R�[�h�ʒu�G���[
#define F_HDRERROR		-203				// �G���e�B�e�B���R�[�h�w�b�_�`���G���[
// �t���O
#define F_NOLINKP		-1					// ���R�[�h�ʒu�̃����N�Ȃ�(�擪�܂��͍ŏI�����N)
#define F_NOLINKI		0					// �h�c�̃����N�Ȃ�(�擪�܂��͍ŏI�����N)

typedef	unsigned short	MRINT;				// ���R�[�h�h�c�^
typedef			 int	MRID;				// ���R�[�h�h�c�^

namespace MC
{

/*******************************************************************************
// 
//	�G���e�B�e�B�E���R�[�h
//
*******************************************************************************/
typedef struct {
	union {
		int		iRec0[1];					// �G���e�B�e�B���R�[�h�N���A�p
		struct {
			MRID	idRec;					// �G���e�B�e�B���R�[�h�h�c(0:��)
			MRINT	iSzBuf;					// �G���e�B�e�B�o�b�t�@�T�C�Y(�w�b�_�����݃T�C�Y)
			MRINT	iSzRec;					// �G���e�B�e�B���R�[�h�T�C�Y(�w�b�_�����݃T�C�Y)
		};
	};
	union {
		int		iRec1[1];
		//	���e���f�[�^���R�[�h�̏ꍇ
		struct {
			MRINT	iType;					// �G���e�B�e�B���R�[�h�^�C�v
			MRINT	iSzUsed;				// �G���e�B�e�B���R�[�h�g�p�σT�C�Y(�w�b�_�����݃T�C�Y)
			int		iRec[1];
		};									// �G���e�B�e�B���R�[�h�E�o�b�t�@
		//	���e���󂫃G���A�̏ꍇ
		struct	{
			int		nBefore;				// �O�̋󂫃G���e�B�e�B���R�[�h�ւ̃|�C���^
											//  (��0:�擪�j
			int		nNext;					// ���̋󂫃G���e�B�e�B���R�[�h�ւ̃|�C���^
											//  (��0:�ŏI�j
		};
	};
} MDBR;

/*******************************************************************************

	�G���e�B�e�B�E���R�[�h

	���ڏ���

*******************************************************************************/
class CMDBR
{
public:
	MDBR*	m_pMdbr;						// �l�c�a���R�[�h
public:
	CMDBR( int iSzRec);
	CMDBR()							{};
	~CMDBR();
	void	AsgBuf( int iSzRec);
	void	FreeBuf();
	int		GetSzRec()				{return m_pMdbr->iSzRec;}
	int		GetSzUsed()				{return m_pMdbr->iSzUsed;}
	int		GetType()				{return m_pMdbr->iType;}
	int		GetId()					{return m_pMdbr->idRec;}
	int		GetBefore()				{return m_pMdbr->nBefore;}
	int		GetNext()				{return m_pMdbr->nNext;}
	int*	GetBufP()				{return m_pMdbr->iRec;}

	void	PutSzRec( int iSz)		{m_pMdbr->iSzRec = iSz;}
	void	PutSzUsed( int iSz)		{m_pMdbr->iSzUsed = iSz;}
	void	PutType( int it)			{m_pMdbr->iType = it;}
	void	PutId( int id)			{m_pMdbr->idRec = id;}
	void	PutBefore( int n)		{m_pMdbr->nBefore = n;}
	void	PutNext( int n)			{m_pMdbr->nNext = n;}

	int		InsertItem( int idItem, int* pItem, int iSzItem);
	int		DeleteItem( int idItem);
	int		GetItem   ( int idItem, int* pItem, int iSzItem);
	void	PrintRec();
};// CMDBR
/*******************************************************************************

	�G���e�B�e�B�E���R�[�h�h�c���R�[�h

*******************************************************************************/
typedef struct {
	int	Model;								// �G���e�B�e�B���R�[�h�̌^
											//	(��0:�󂫃��R�[�h�A��0:�g�p�ς݃��R�[�h)
	union { 
											// �g�p�ς݃��R�[�h�̏ꍇ
		int	nRec;							// �@�G���e�B�e�B���R�[�h�̈ʒu
//
		struct {							// �󂫃��R�[�h�̏ꍇ
			MRID idBefore;					// �@�O�̋󂫃G���e�B�e�B���R�[�h�h�c
											//  (��0:�擪�j
			MRID idNext;					// �@���̋󂫃G���e�B�e�B���R�[�h�h�c
											//  (��0:�ŏI�j
		};
	};
} MDBRID;
/*******************************************************************************

	�����i�w�b�_+���e�j

*******************************************************************************/
typedef struct {
	MRINT	idItem;							// �A�C�e���h�c
	MRINT	iSzItem;						// �A�C�e���T�C�Y
	int		iItem[1];						// �A�C�e�����e
} MDBRI;
/*******************************************************************************

	�l�c�a�@���R�[�h����

*******************************************************************************/
class CMDB
{
	MCHAR*	m_sFileName;					// �l�c�a�̃t�@�C����
	int		*m_pMdbBuf;						// �l�c�a�o�b�t�@[MaxSzMdbBuf]
	int		m_iSzMdbBuf;					// �l�c�a�̃T�C�Y
	int		m_update;						// �l�c�a�̏C���t���O

	MDBRID	*m_pMdbRId;						// �G���e�B�e�B���R�[�h�h�c���R�[�h�|�C���^
	MRID	m_id1stEmptyR;					// �擪�󂫃G���e�B�e�B���R�[�h�h�c
	int		m_n1stEmptyR;					// �擪�󂫃G���e�B�e�B���R�[�h�ʒu
//
	int		m_MaxSzMdbBuf;					// �l�c�a�o�b�t�@�T�C�Y
	int		m_MaxMdbRId;					// �G���e�B�e�B���R�[�h�h�c�ő�l
	int		m_MaxSzMdbR;					// �G���e�B�e�B�E���R�[�h�ő�T�C�Y
	int		m_MinSzMdbR;					// �G���e�B�e�B�E���R�[�h�ŏ��T�C�Y
//	int		m_iSzEmptyRec;					// �_�~�[�󂫃G���e�B�e�B���R�[�h�T�C�Y
public:
	CMDB	( int iMaxSzMdbBuf, int iMaxMdbRId, int iMaxSzMdbR,
			 int iMinSzMdbR);
//			 , int iiSzEmptyRec);
	~CMDB();
//	Bool	OpenDB(HMDB hMdb, LPCSTR pszFileName, UINT nOpenFlags, 
//                                  CFileException *pError = NULL);
//	void	Close(HMDB hMdb, UINT nCloseFlags);
	int		InsertRec(CMDBR *pMdbR, int iType);
	int		GetRec   ( int idR, CMDBR *pMdbR);
	int		ModifyRec( int idR, CMDBR *pMdbR, int iType);
	int		DeleteRec( int idR);

	int		GetEmptyArea ( int iSzRec);
	int		GetEmptyRecID();
	void	PutEmptyArea ( int nRec);
	void	PutEmptyRecID( int idRec);
	void	PrintRec(MCHAR* head, int nRec, int num);
	void	PrintID (MCHAR* head);
	void	PrintMdb();
};// CMDB

} // namespace MC