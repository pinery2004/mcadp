#pragma once
#include	"McSystemProperty.h"
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhTpPts.h
//
//		���ގ�ރ��R�[�h
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#define	MHPTSZ_NMGENERAL	23							// ���̍ő啶����
#define	MHPTSZ_NMPARTS1		23							// ����p���ޖ��ő啶����
#define	MHPTSZ_NMPARTS2		23							// �ώZ�p���ޖ��ő啶����
#define	MHPTSZ_TPMEMBER		1							// ���@�^���I��p��ރR�[�h�ő啶����
#define	MHPTSZ_CDMEMBER		15							// ���@�^���ő啶����

//	���i���

#define		MP_BZICD_NOSELECT		-1
#define		MP_BZICD_TYPE			10000
#define		MP_BZICD_KIND			1000
#define		MP_BZICD_BUZAI			10000
#define		MP_BZICD_PANEL			30000
#define		MP_BZICD_YUKAPANEL		32010
#define		MP_BZICD_KABEPANEL		35010
#define		MP_BZICD_TENJOPANEL		33010
#define		MP_BZICD_YANEPANEL		34010
#define		MP_BZICD_YANEBUZAI		14000
#define		MP_BZICD_KABEBUZAI		15000
#define		MP_BZICD_TATEGU			65000
#define		MP_BZICD_TAIKABEAREA	45010
#define		MP_BZICD_TAIKABELINE	45020
#define		MP_BZICD_SIJIKABELINE	45030
#define		MP_BZICD_TENKAI			45110

namespace MC
{

class	mhTpPts									// ���ގ�ރ��R�[�h
{
	friend	class	mhPlcInfo;

//public:
//G	MINT	m_iPTId;
	MhGp*	m_pPTGp;							// �\��(�g)�R�[�h( �����A�����A�V��A�ϗ͕ǁA�ǁA���A��b)
	MINT	m_iPTBr;							// ���ރR�[�h("����", "����", "�p�l��", "����", "��", "��b", "����", "���", "���L", "���̑�")
	MCHAR	m_sPTNmGeneral[MHPTSZ_NMGENERAL+1];	// ����
	MCHAR	m_sPTNmPts1[MHPTSZ_NMPARTS1+1];		// ����p���ޖ�1
	MCHAR	m_sPTNmPts2[MHPTSZ_NMPARTS2+1];		// �ώZ�p���ޖ�2
	DWORD	m_dPTColor;							// �F
	MINT	m_iPTCdBuzaiR;						// ���ރR�[�h	�Ǎ��ݗp
	MINT	m_iPTCdBuzaiW;						// ���ރR�[�h	�������ݗp(���ގ�ރe�[�u��VerUp���C���e�i���X�p)
	MCHAR	m_sPTTpMbr[MHPTSZ_TPMEMBER+1];		// ���@�^���I��p��ރR�[�h
	MCHAR	m_sPTCdMbr[MHPTSZ_CDMEMBER+1];		// ���@�^��
	MINT	m_iPTKbInp;							// ���̓R�[�h
	MSTNDH	m_iPTCdHgt;							// ���t��������R�[�h
	MINT	m_iPTCdPlc;							// �z�u�R�[�h
	MINT	m_iPTCdIzon;						// �ˑ��R�[�h
	MINT	m_iPTCdMarume;						// �ۂ߃R�[�h
	MINT	m_iPTCdToritk;						// ���t���R�[�h�@�㉺�t���R�[�h (0:���t��, 1:��t��)
public:
//G	void	SetPTId( MINT iPTId)	{
//G									m_iPTId = iPTId;}
	void	SetPTGp( MhGp* pPTGp)	{													// �\��(�g)�R�[�h( �����A�����A�V��A�ϗ͕ǁA�ǁA���A��b)
									m_pPTGp = pPTGp;}
	void	SetPTBr( MINT iPTBr)	{													// ���ރR�[�h("����", "����", "�p�l��", "����", "��", "��b", "����", "���", "���L", "���̑�")
									m_iPTBr = iPTBr;}
	void	SetPTNmGeneral( MCHAR* cPTNmGeneral)	{									// ����
									Mstrncpy_s( m_sPTNmGeneral, cPTNmGeneral, MHPTSZ_NMGENERAL+1);}
	void	SetPTNmPts1( MCHAR* cPTNmPts1)	{											// ����p���ޖ�1
									Mstrncpy_s( m_sPTNmPts1, cPTNmPts1, MHPTSZ_NMPARTS1+1);}
	void	SetPTNmPts2( MCHAR* cPTNmPts2)	{											// �ώZ�p���ޖ�2
									Mstrncpy_s( m_sPTNmPts2, cPTNmPts2, MHPTSZ_NMPARTS2+1);}
	void	SetPTColor( DWORD dPTColor)	{												// �F
									m_dPTColor = dPTColor;}
	void	SetPTCdBuzaiR( MINT iPTCdBuzaiR)	{										// ���ރR�[�h	�Ǎ��ݗp
									m_iPTCdBuzaiR = iPTCdBuzaiR;}
	void	SetPTCdBuzaiW( MINT iPTCdBuzaiW)	{										// ���ރR�[�h	�������ݗp(���ގ�ރe�[�u��VerUp���C���e�i���X�p)
									m_iPTCdBuzaiW = iPTCdBuzaiW;}
	void	SetPTTpMbr( MCHAR* sPTTpMbr)	{											// ���@�^���I��p��ރR�[�h
									Mstrncpy_s( m_sPTTpMbr, sPTTpMbr, MHPTSZ_TPMEMBER+1);}
	void	SetPTCdMbr( MCHAR* sPTCdMbr)	{											// ���@�^��
									Mstrncpy_s( m_sPTCdMbr, sPTCdMbr, MHPTSZ_CDMEMBER+1);}
	void	SetPTInpKb( MINT iPTInpKb)	{												// ���̓R�[�h
									m_iPTKbInp = iPTInpKb;}
	void	SetPTCdHgt( MSTNDH iPTCdHgt)	{											// ���t��������R�[�h
									m_iPTCdHgt = iPTCdHgt;}
	void	SetPTCdPlc( MINT iPTCdPlc)	{												// �z�u�R�[�h
									m_iPTCdPlc = iPTCdPlc;}
	void	SetPTCdIzon( MINT iPTCdIzon)	{											// �ˑ��R�[�h
									m_iPTCdIzon = iPTCdIzon;}
	void	SetPTCdMarume( MINT iPTCdMarume)	{										// �ۂ߃R�[�h
									m_iPTCdMarume = iPTCdMarume;}
	void	SetPTCdToritk( MINT iPTCdToritk)	{										// ���t���R�[�h�@�㉺�t���R�[�h (0:���t��, 1:��t��)
									m_iPTCdToritk = iPTCdToritk;}

	MINT	GetPTCdGp()	{			
									return m_pPTGp->m_iCdGp;}
	MINT	GetPTBr()	{			
									return m_iPTBr;}
	MCHAR*	GetPTNmGeneral()	{	
									return m_sPTNmGeneral;}
	MCHAR*	GetPTNmPts1()	{		
									return m_sPTNmPts1;}
	MCHAR*	GetPTNmPts2()	{		
									return m_sPTNmPts2;}
	DWORD	GetPTColor()	{		
									return m_dPTColor;}
	MINT	GetPTCdBuzai()	{		
									return m_iPTCdBuzaiR;}
	MINT	GetPTCdBuzaiW()	{		
									return m_iPTCdBuzaiW;}
	MCHAR*	GetPTTpMbr()	{		
									return m_sPTTpMbr;}									// ���@�^���I��p��ރR�[�h
	MCHAR*	GetPTCdMbr()	{		
									return m_sPTCdMbr;}									// ���@�^��
	MINT	GetPTInpKb()	{		
									return m_iPTKbInp;}									// ���̓R�[�h
	MINT	GetPTCdHgt()	{		
									return m_iPTCdHgt;}									// ���t��������R�[�h
	MINT	GetPTCdPlc()	{		
									return m_iPTCdPlc;}									// �z�u�R�[�h
	MINT	GetPTCdIzon()	{		
									return m_iPTCdIzon;}								// �ˑ��R�[�h
	MINT	GetPTCdMarume()	{		
									return m_iPTCdMarume;}								// �ۂ߃R�[�h
	MINT	GetPTCdToritk()	{		
									return m_iPTCdToritk;}								// ���t���R�[�h�@�㉺�t���R�[�h (0:���t��, 1:��t��)

	bool	IsYane()	{			
									return m_pPTGp->IsYane();}							// ����
	bool	IsTenjo()	{			
									return m_pPTGp->IsTenjo();}							// �V��
	bool	IsYuka()	{			
									return m_pPTGp->IsYuka();}							// ��
	bool	IsKiso()	{			
									return m_pPTGp->IsKiso();}							// ��b
 
	bool	IsTategu()	{			
									return MINT(m_iPTCdBuzaiR / MP_BZICD_KIND) * MP_BZICD_KIND == MP_BZICD_TATEGU;}	// ����
	bool	IsTenkai()	{			
									return (m_iPTCdBuzaiR == MP_BZICD_TENKAI);}			// �Z���W�J
	bool	IsFrame()	{			
									return m_iPTCdIzon == MP_IZNCD_SUICYOKU;}			// ����( ���Ęg| ��)
//	bool	IsPanel()	{			
//									return m_iPTCdBuzaiR / MP_BZICD_TYPE == MP_BZICD_PANEL / MP_BZICD_TYPE;}	// �p�l��
	bool	IsPanel()	{			
									return m_iPTBr == MP_BR_PANEL;}						// �p�l��
	bool	IsKaiko()	{			
									return m_iPTBr == MP_BR_KAIKO;}						// �J��
	bool	IsKabe()	{			
									return m_iPTBr == MP_BR_KABE;}						// ��
	bool	IsTaiKabeArea()	{		
									return m_iPTCdBuzaiR == MP_BZICD_TAIKABEAREA;}		// �ϗ͕ǋ��
	bool	IsTaiKabeLine()	{		
									return m_iPTCdBuzaiR == MP_BZICD_TAIKABELINE;}		// �ϗ͕ǐ�
	bool	IsSijiKabeLine()	{	
									return m_iPTCdBuzaiR == MP_BZICD_SIJIKABELINE;}		// �x���ǐ�
	bool	IsOukaZai()	{			
									return m_iPTBr == MP_BR_BUZAI && 
											!( IsFrame() || IsPanel() || IsKaiko());}	// ���U��
	bool	IsYukaPanel()	{		
									return m_iPTCdBuzaiR == MP_BZICD_YUKAPANEL;}		// ���p�l��
	bool	IsKabePanel()	{		
									return m_iPTCdBuzaiR == MP_BZICD_KABEPANEL;}		// �ǃp�l��
	bool	IsTenjoPanel()	{		
									return m_iPTCdBuzaiR == MP_BZICD_TENJOPANEL;}		// �V��p�l��
	bool	IsYanePanel()	{		
									return m_iPTCdBuzaiR == MP_BZICD_YANEPANEL;}		// �����p�l��
};

} // namespace MC