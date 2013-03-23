//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MmWnd.cpp
//
//		�E�B���h�E�Ǘ�
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MmSystem.h"
#include "MgLib.h"
#include "MgMat.h"
#include "MsDefine.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"
#define DLL_EXPORT_WNDINFO_DO
#define DLL_EXPORT_MC_WINDOWCTRL_DO
#include "MmWnd.h"
#include "McSystemProperty.h"

#include "resource.h"
#include "..\\MCAD\\resource.h"

//S #include "MgMapMode.h"
#include "MdList.h"
#include "MainFrm.h"

#define		AKIG		600.f

namespace MC
{

static	MbListE		z_lWnd( 10, sizeof( MmWndInfo)+10);			// �E�B���h�E�Ǘ����
static	MmWndInfo	z_wWndC;									// �J�����g�E�B���h�E�Ǘ����
static	MPOSITION	z_WndPos;

/////////////////////////////////////////////////////////////////////////////
//	�擪�̃E�B���h�E���擾����
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�ʒu
MmWndInfo* WindowCtrl::MmGetHeadWnd( MPOSITION *pWndPos)
{
	if ( pWndPos)
		return (MmWndInfo*)z_lWnd.GetHead( pWndPos);
	else
		return (MmWndInfo*)z_lWnd.GetHead( &z_WndPos);
}

/////////////////////////////////////////////////////////////////////////////
//	���̃E�B���h�E���擾����
//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�ʒu
MmWndInfo* WindowCtrl::MmGetNextWnd( MPOSITION *pWndPos)
{
	if ( pWndPos)
		return (MmWndInfo*)z_lWnd.GetNext( pWndPos);
	else
		return (MmWndInfo*)z_lWnd.GetNext( &z_WndPos);
}


/////////////////////////////////////////////////////////////////////////////
//	�J�����g�̃E�B���h�E��ʂ�ݒ�
//						(1st �E�B���h�E�쐬�J�n���ɐݒ�)

void	WindowCtrl::MmWndSetSyubetsuC(
						MINT		iWndSyu,		// (I  ) �E�B���h�E���
						MINT		iZuSyu,			// (I  ) �}���
						MINT		iKai,			// (I  ) �K
						MINT		iZuNum			// (I  ) �}�ԍ�
				) 
{
	z_wWndC.SetWndSyu( iWndSyu);
	z_wWndC.SetZuSyu( iZuSyu);
	z_wWndC.SetKai( iKai);
	z_wWndC.SetZuNum( iZuNum);
}

/////////////////////////////////////////////////////////////////////////////
//	�J�����g�̃t���[���̃C���X�^���X��ݒ�
//						(2nd �q�t���[���쐬�J�n���ɐݒ�)

void	WindowCtrl::MmWndSetFrameC(
						MINT		iWndSyu,		// (I  ) �E�B���h�E���
						CMDIChildWnd* pChildFrm		// (I  ) �t���[���̃C���X�^���X
				)
{
	_ASSERTE( iWndSyu == z_wWndC.m_iWndSyu);
	z_wWndC.m_pChildFrm = pChildFrm;
}

/////////////////////////////////////////////////////////////////////////////
//	�J�����g�̃E�B���h�E�̃C���X�^���X��ݒ�
//						(3rd �q�r���[�쐬�J�n���ɐݒ�)

void	WindowCtrl::MmWndSetWndC(
						MINT		iWndSyu,		// (I  ) �E�B���h�E���
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	_ASSERTE( iWndSyu == z_wWndC.m_iWndSyu);
	z_wWndC.m_pWnd = pWnd;
}

/////////////////////////////////////////////////////////////////////////////
//	�E�B���h�E�Ǘ����̍쐬

MmWndInfo::MmWndInfo(
						MINT		iWndSyu,		// (I  ) �E�B���h�E���
						MINT		iZuSyu,			// (I  ) �}���
						MINT		iKai,			// (I  ) �K
						MINT		iZuNum			// (I  ) �}�ԍ�
				)
{
	m_iWndSyu		= iWndSyu;									// �E�B���h�E���
	m_iZuSyu		= iZuSyu;									// �}���
	m_iKai			= iKai,										// �K
	m_iZuNum		= iZuNum;									// �}�ԍ�
	m_iHoko			= 0;										// ����
	m_pWnd			= NULL;										// �E�B���h�E�̃C���X�^���X
	m_pDrag			= NULL;										// �h���b�O������
	m_pMemBmp		= NULL;										// �J�����g�E�B���h�E�C���[�W�r�b�g�}�b�v
	m_pOldMemBmp	= NULL;										// �ۑ��p�E�B���h�E�C���[�W�r�b�g�}�b�v
	m_pMemDC		= NULL;										// �E�B���h�E�C���[�W�������c�b

	SetMinMaxD( MgMinMaxI2( 0, 0, 100, 100));					//	�\�����W(Min/Max)

	SetMinMaxRS( MgMinMaxR2( 0, 0, 100., 100.));				//	�����W(Min/Max)�X�^�b�N
	SetMat();
}

MmWndInfo::~MmWndInfo      ()
{
//	DeleteWnd();
//	MBDELETE( m_pMemBmp);
//	MBDELETE( m_pMemDC);
}

/////////////////////////////////////////////////////////////////////////////
//	�h���b�O������̍폜

void MmWndInfo::DeleteDrag()
{ 
	if ( m_pDrag) {
//	    KillTimer(RealTimeTimer_id);
	    delete m_pDrag;
		m_pDrag = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�E�B���h�E�C���[�W�������c�b�̍쐬
//
//	���̎菇�Ŏg�p
//
//		CreateMDC		(AsignMDC���܂�)
//			FreeMDC		(�J��Ԃ�)
//			AsignMDC	(�J��Ԃ�)
//		DeleteMDC		(FreeMDC���܂�)
//

void MmWndInfo::CreateMDC()
{
	m_pMemBmp		= new CBitmap;
	m_pMemDC		= new CDC;
	SetDC( m_pMemDC);
}

/////////////////////////////////////////////////////////////////////////////
//	�E�B���h�E�C���[�W�������c�b�̍폜

void MmWndInfo::DeleteMDC()
{
	FreeMDC();
	MBDELETE( m_pMemBmp);
	MBDELETE( m_pMemDC);
}

/////////////////////////////////////////////////////////////////////////////
//	�E�B���h�E�C���[�W�������c�b�̊��蓖��

void MmWndInfo::AsignMDC()
{
	if ( m_pMemDC->m_hDC == NULL) {
		CClientDC		dc( m_pWnd);
	
		m_pMemDC->CreateCompatibleDC( &dc);													// �E�B���h�E�c�b�̑����ݒ�
		m_pMemBmp->CreateCompatibleBitmap( &dc, m_iMinMaxD.max.x, -m_iMinMaxD.min.y);		// �E�B���h�E�C���[�W�r�b�g�}�b�v�̍쐬
		m_pOldMemBmp = m_pMemDC->SelectObject( m_pMemBmp);									// �E�B���h�E�C���[�W�r�b�g�}�b�v������t��
	}
}

/////////////////////////////////////////////////////////////////////////////
//	�E�B���h�E�C���[�W�������c�b�̊J��

void MmWndInfo::FreeMDC()
{
	if ( m_pOldMemBmp)
		m_pMemDC->SelectObject( m_pOldMemBmp);
	if ( m_pMemDC)
		m_pMemDC->DeleteDC();
	if ( m_pMemBmp)
		m_pMemBmp->DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
//	�������c�b�̃E�B���h�E���N���A����

void MmWndInfo::ClearMDC()
{
	CBrush	brushBG = mcs::GetColor( MM_COLOR_BACKGROUND);
	CBrush* pOldBrush = m_pMemDC->SelectObject( &brushBG);

	MINT iOldMM = SetMapMode( MMAPMODE);						// �}�b�v���[�h�������ݒ肷��

	m_pMemDC->PatBlt( 0, 0, m_iMinMaxL.max.x, m_iMinMaxL.min.y * GetUpL(), PATCOPY);	// �w�i�F�ݒ�

	m_pMemDC->SetMapMode( iOldMM);
	m_pMemDC->SelectObject( pOldBrush);
}
/////////////////////////////////////////////////////////////////////////////
//	�E�B���h�E�Ǘ�
/*
/////////////////////////////////////////////////////////////////////////////
//	������

MINT WindowCtrl::MmWndKInit        ()				// (  O) 0 : ����  1 : �װ
{
	MmWndKDeleteAll();								// ؽĂ�j������

	return(0);
}

/////////////////////////////////////////////////////////////////////////////
//	�I��

MINT WindowCtrl::MmWndKTerm        ()				// (  O) 0 : ����  1 : �װ
{
	MmWndKDeleteAll();								// ؽĂ�j������

	return(0);
}
*/
/////////////////////////////////////////////////////////////////////////////
//  �J�����g�E�B���h�E��ǉ�����
//						(4th �q�r���[�쐬�J�n����MmWndSetWndC���s��ɐݒ�)

MINT WindowCtrl::MmWndKAddC()						// (  O) 0 : ����  1 : �װ
{
	MINT		ist = 1;
	MmWndInfo	WndInfo(z_wWndC.m_iWndSyu, z_wWndC.m_iZuSyu, z_wWndC.m_iKai, z_wWndC.m_iZuNum);

	WndInfo.SetCursor( IDC_CROSS1);

	WndInfo.SetWnd( z_wWndC.m_pWnd);
	WndInfo.SetFrame( z_wWndC.m_pChildFrm);

	if ( WindowCtrl::MmWndKFindSyu( z_wWndC.m_iWndSyu, z_wWndC.m_iZuSyu, z_wWndC.m_iKai, z_wWndC.m_iZuNum) == NULL) {
		WndInfo.CreateMDC();
		z_lWnd.Inject( &WndInfo);
		ist = 0;
	}
	return( ist);
}

/////////////////////////////////////////////////////////////////////////////
//  �E�B���h�E��ǉ�����

MINT WindowCtrl::MmWndKAdd(							// (  O) 0 : ����  1 : �װ
						MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
						MINT		iZuSyu,			// (I  ) �}���
						MINT		iKai,			// (I  ) �K
						MINT		iZuNum			// (I  ) �E�B���h�E���}�ԍ�
				)
{
	MINT		ist = 1;
	MmWndInfo	*pWndInfo = new MmWndInfo( iWndSyu, iZuSyu, iKai, iZuNum);

	if ( WindowCtrl::MmWndKFindSyu( iWndSyu, iZuSyu, iKai, iZuNum) == NULL) {
		z_lWnd.Inject( pWndInfo);
		ist = 0;
	}
	return( ist);
}

/////////////////////////////////////////////////////////////////////////////
//  �E�B���h�E���폜����

MINT WindowCtrl::MmWndKDelete(						// (  O) �ð��  0 : ����  1 : �װ
						MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
				)
{
	MINT		ist = 1;
	MPOSITION	nPos;

	if ( pWndInfo) {
		pWndInfo->DeleteDrag();
		pWndInfo->DeleteMDC();

		nPos = z_lWnd.Find( pWndInfo, 0);
		if ( nPos) {
			z_lWnd.RemoveAt( &nPos);
			ist = 0;
		}
	}
	return( ist);
}

/////////////////////////////////////////////////////////////////////////////
//  �E�B���h�E����������

MmWndInfo* WindowCtrl::MmWndKFindSyu(				// (  O) �E�B���h�E���ւ��߲��
						MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
						MINT		iZuSyu,			// (I  ) �}���
						MINT		iKai,			// (I  ) �K
						MINT		iZuNum			// (I  ) �E�B���h�E���}�ԍ�
				)
{
	MPOSITION			Pos;
	MmWndInfo*			pWndInfo;

	for (pWndInfo = (MmWndInfo*)z_lWnd.GetHead( &Pos);
			pWndInfo != 0; 
				pWndInfo = (MmWndInfo*)z_lWnd.GetNext( &Pos)) {
		if ( (pWndInfo->m_iWndSyu == 0 || iWndSyu == 0 || pWndInfo->m_iWndSyu == iWndSyu) &&
			 (pWndInfo->m_iZuSyu  == 0 || iZuSyu  == 0 || pWndInfo->m_iZuSyu  == iZuSyu) &&
			 (pWndInfo->m_iKai    == 0 || iKai    == 0 || pWndInfo->m_iKai    == iKai) &&
			 (pWndInfo->m_iZuNum  == 0 || iZuNum  == 0 || pWndInfo->m_iZuNum  == iZuNum))
			return pWndInfo;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//  �E�B���h�E����������

MmWndInfo* WindowCtrl::MmWndKFindWnd(							// (  O) �E�B���h�E���ւ��߲��
						CWnd*		pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
				)
{
	MPOSITION			Pos;
	MmWndInfo*			pWndInfo2;

	for (pWndInfo2=(MmWndInfo*)z_lWnd.GetHead( &Pos); pWndInfo2!=0; pWndInfo2=(MmWndInfo*)z_lWnd.GetNext( &Pos)) {
		if ( pWndInfo2->GetWnd() == pWnd)
			return pWndInfo2;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//  �E�B���h�E����������

MmWndInfo* WindowCtrl::MmWndKFindFrm(							// (  O) �E�B���h�E���ւ��߲��
						CMDIChildWnd* pChildFrm		// (I  ) �t���[���̃C���X�^���X
				)
{
	MPOSITION			Pos;
	MmWndInfo*			pWndInfo2;

	for (pWndInfo2=(MmWndInfo*)z_lWnd.GetHead( &Pos); pWndInfo2!=0; pWndInfo2=(MmWndInfo*)z_lWnd.GetNext( &Pos)) {
		if ( pWndInfo2->GetFrame() == pChildFrm)
			return pWndInfo2;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//	�S�E�B���h�E���폜����

MINT WindowCtrl::MmWndKDeleteAll()								// (  O) �X�e�C�^�X 0 : ����  1 : �G���[
{
	MINT				ist;
	MPOSITION			Pos;
	MmWndInfo*			pWndInfo2;

	for (pWndInfo2=(MmWndInfo*)z_lWnd.GetHead( &Pos); pWndInfo2!=0; pWndInfo2=(MmWndInfo*)z_lWnd.GetHead( &Pos)) {
		ist = MmWndKDelete( pWndInfo2);
		if ( ist) return ist;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//	�J�����g�̃E�B���h�E���擾����

MmWndInfo* WindowCtrl::MmWndKGetCurWnd()						// (  O) �X�e�C�^�X  NULL : �G���[ 
{
	CMainFrame*			pMainFrm;					// ���C���t���[��
	CMDIChildWnd*		pChildFrm;					// �q�t���[��
	MmWndInfo*			pWndInfo = NULL;

//	pMainFrm = (CMDIFrameWnd *)AfxGetMainWnd();					// ���C���t���[���擾
//	if ( pMainFrm == NULL) MQUIT;

	pMainFrm = System::GetpMainFrame();

//	pChildFrm = pMainFrm->MDIGetActive();						// �A�N�e�B�u�Ȏq�t���[�������
//	if ( pChildFrm == NULL) MQUIT;

	pChildFrm = pMainFrm->m_pCurFrame;

	pWndInfo = MmWndKFindFrm( pChildFrm);

//exit:

	return( pWndInfo);
}

} // namespace MC