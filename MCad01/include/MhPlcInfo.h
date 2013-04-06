#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhPlcInfo.h
//
//		�z�u�����R�[�h
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "MhIeModel.h"
#include "MhGp.h"
#include "MhMbr.h"

#include "MhTategu.h"
#include "MhZukei.h"
#include "MhPartsSpec.h"

#include "MhLib.h"

#include "MgPolygon.h"

namespace MC
{

// �z�u�^
class	mhPlcInfo: public MOBJECT
{
	friend	class	MdPartsQueue;
	friend	void	MdPartsModify( mhPlcInfo *pPlcEnR, mhPlcInfo* *ppPlcEnM);
	friend	void	MdPartsDelete( MPOSITION pPosition);
	friend	void	MmPartsPlc( const MgPoint3 *Pt, const MgVect3 vUpPlc, const MgPolyg2 *pPg);
	friend	void	MmWndKDrawParts( class MmWndInfo* pWndInfo);
	friend	void	IeModel::MhNormKabe( MINT nProc);
	friend	void	MhNormKiso( MINT nProc);
	//friend	MINT	MhMdlLoad( MCHAR* PathI);
	friend	MINT	MhBziHaitiLoad(
						MhMdlIO*	i_phMdl		// �ǂݍ��݃t�@�C���@�n���h��
						//void**	io_ppEnt,	// �G���e�B�e�B
						//MINT		i_iSize		// ���ڃT�C�Y
				);
public:
	MsBitSet*			m_pVer;					// �o�[�W�������� (NULL: �S�o�[�W�����ŕ\��)
	MsBitSet*			m_pOpt1;				// �\���I��OPT�Q�Z�b�g (NULL: �I�v�V�����ݒ薳���ł��\��)
	MsBitSet*			m_pOpt2;				// �\���I�tOPT�Q�Z�b�g (NULL: ����)
	MUINT				m_iTenkai;				// �Z���W�J���� (NULL: ����)
	MUBYTE				m_ibKai;				// �K( 1, 2, 3)
	MUBYTE				m_ibCdHgt;				// ���t�������R�[�h
	MUBYTE				m_ibCdInpKbCd;			// ���͓_�敪�R�[�h
	MUBYTE				m_ibDisplayFlg;			// �\���t���O(�}�`,���L1,���L2)
	MSHORT				m_isPanelNo;			// �p�l���ԍ�
	MSHORT				m_isKaikoNo;			// �J���ԍ�
	MSHORT				m_isIdPartsTp;			// ���iID
	MSHORT				m_isMbrId;				// ���@�^��ID
	mhPartsTp*			m_pPartsTp;				// ���i���
	MhMbr*				m_pMbr;					// ���@�^��
	MgLine3				m_lnPlc;				// p[0]: �n�_ | �z�u�_
												// p[1]: �I�_ | �z�u�����_
	MgVect3				m_vUpPlc;				// �z�u�����(�z�u�_�̏㑤����)
	MREAL				m_rSinZure;				// �ގ��c�����		>0:�E���A<0:����
	MREAL				m_rPlcZure;				// �z�u�_�����		>0:�O�A�@<0:��
	MREAL				m_rLngHosei[2];			// �����␳�l�i�n�_���A�I�_���j
	MREAL				m_rHgt[2];				// �����i���t�������A�����j
	MgPoint2			m_ptCmnt1;				// ���L�\���ʒu
	union	{									// �⏕����
		class MhAuxAttr*	m_pAuxAttr;			// �⏕��������
		class MhTateguInfo*	m_pAuxTategu;		// ����
		class JTTenkaiPr*	m_pAuxTenkai;		// �Z���W�J
	};
	MhZukei*			m_pZukei;				// �}�`

public:
	mhPlcInfo()	{
				InitPtrTypeAtr();}
	void Copy( const mhPlcInfo &Ent);
	~mhPlcInfo()	{
				FreeAllAtr();}

	void	FreeAllAtr()	{									// �����p�Ɋm�ۂ����̈���J������
					MBFREE( m_pVer);
					MBFREE( m_pOpt1);
					MBFREE( m_pOpt2);
					MBFREE( m_pAuxAttr);
					if ( m_pZukei) 
						{ MBFREE( m_pZukei->m_pNext);
						delete (char*)m_pZukei;
						m_pZukei = 0;
					}
				}
	MINT	Load(												// �c�a���P���R�[�h�ǂݍ���
						MhMdlIO*	i_phMdl						// �ǂݍ��݃t�@�C���@�n���h��
				);
	MINT	Save(												// �c�a�ւP���R�[�h��������
						MhMdlIO*	i_phMdl						// �������݃t�@�C���@�n���h��
				);

	void	InitPtrTypeAtr()	{								// �����̈�t���̑������C�j�V�����C�Y�A�̈�ւ̃|�C���^���N���A
								m_pVer = 0; m_pOpt1 = 0; m_pOpt2 = 0;
								m_pAuxAttr = 0; m_pZukei = 0;}
	void	SetPIVer( MsBitSet* pVer)	{						// �o�[�W��������
								m_pVer = pVer;}
	void	FreePIVer()		{									// �o�[�W��������𖳂��ɐݒ�
								MBFREE( m_pVer);}
	void	SetPIOpt1( MsBitSet* pOptv)	{						// �\���I��OPT�Q�Z�b�g
								m_pOpt1 = pOptv;}				
	void	FreePIOpt1()	{									// �\���I��OPT�Q�Z�b�g�𖳂��ɐݒ�
								MBFREE( m_pOpt1);}			
	void	SetPIOpt2( MsBitSet* pOptv)	{						// �\���I�tOPT�Q�Z�b�g
								m_pOpt2 = pOptv;}				
	void	FreePIOpt2()	{									// �n�o�s�Q�\���n�e�e�𖳂��ɐݒ�
								MBFREE( m_pOpt1);}			
	void	SetPITenkai( MUINT iTenkai)	{						// �Z���W�J����
								m_iTenkai = iTenkai;}				
	void	SetPIKai( MINT iKai)	{							// �K
								m_ibKai = iKai;}				
	void	SetPICdHgt( MINT iCdCdHgt)	{						// ���t�������R�[�h
								m_ibCdHgt = iCdCdHgt;}			
	void	SetPICdInpKbCd( MINT iCdInpKbCd)	{				// ���͓X�敪�R�[�h
								m_ibCdInpKbCd = iCdInpKbCd;}		
	void	SetPIDisplayFlg( MINT iDisplayFlg)	{				// �\���t���O(�}�`,���L1,���L2)
								m_ibDisplayFlg = iDisplayFlg;}	
	void	SetPIPanelNo( MINT iPanelNo)	{					// �p�l���ԍ�
								m_isPanelNo = iPanelNo;}		
	void	SetPIKaikoNo( MINT iKaikoNo)	{					// �J���ԍ�
								m_isKaikoNo = iKaikoNo;}		
	void	SetPIIdPartsTp( MINT iIdPartsTp)	{					// ���iID
								m_isIdPartsTp = iIdPartsTp;}		
	void 	SetPIIdMbr( MINT iMbrId)	{						// ���@�^��ID
								m_isMbrId = iMbrId;}		
	void	SetPIPartsTp( mhPartsTp* pPartsTp)	{					// ���i���
								m_pPartsTp = pPartsTp;}			
	void	SetPIMbr( MhMbr* pMbr)	{							// ���@�^��							
								m_pMbr = pMbr;}				
	void 	SetPIPlcIti( MgLine3 lnPlc)	{						// �z�u�ʒu�i�n�_�E�I�_�j
								m_lnPlc = lnPlc;}				// p[0]: �n�_ | �z�u�_
																// p[1]: �I�_ | �z�u�����_
	void 	SetPIPlcIti( MINT iti, MgPoint3 ptPlc)	{			// �z�u�ʒu�i�n�_�E�I�_�j 
								m_lnPlc.p[iti] = ptPlc;}		// p[0]: �n�_ | �z�u�_
																// p[1]: �I�_ | �z�u�����_
	void 	SetPIUpPlc( MgVect3 vUpPlc)	{						// �z�u�����
								m_vUpPlc = vUpPlc;}			
	void	SetPISinZure ( MREAL rSinZure)	{					// �ގ��c����ʁ@	>0:�E���A<0:����
								m_rSinZure = rSinZure;}		
	void 	SetPIPlcZure( MREAL rPlcZure)	{					// �z�u�_�����		>0:�O�A�@<0:��
								m_rPlcZure = rPlcZure;}		
	void	SetPILenHosei( MINT iti, MREAL rLngHosei)	{		// �����␳�l�i�n�_��(0)�A�I�_��(1)�j
								m_rLngHosei[iti] = rLngHosei;}
	void	SetPIHgt( MINT iti, MREAL rHgt)	{					// �����i���t������(0)�A����(1)�j
								m_rHgt[iti] = rHgt;}			
	void	SetPICmntPt( MgPoint2	ptCmnt)	{					// ���L�\���ʒu
								m_ptCmnt1 = ptCmnt;}			
	void	SetPIAuxAttr( class MhAuxAttr* pAuxAttr)	{		// �⏕�����@����
								m_pAuxAttr = pAuxAttr;}		
	void	SetPIAuxTategu( MhTateguInfo* pAuxTategu)	{		// �⏕�����@����
								m_pAuxTategu = pAuxTategu;}	
	void	SetPIAuxTenkai( JTTenkaiPr* pAuxTenkai)	{			// �⏕�����@�Z���W�J
								m_pAuxTenkai = pAuxTenkai;}		
	void 	SetPIZukei( MhZukei* pZukei)	{					// �}�`								
								m_pZukei = pZukei;}				

	void	SetPIMaeHosei( MREAL rMaeHosei)	{					// ��O���␳
								m_rSinZure = rMaeHosei;}
	void	SetPIOku( MREAL rOku)	{							// ���s
								m_rPlcZure = rOku;}
	void	SetPIOkuHosei( MREAL rOkuHosei)	{					// �����␳
								m_rHgt[1] = rOkuHosei;}

	MsBitSet*	GetPIVer()	{	
								return m_pVer;}					// �o�[�W��������
	MsBitSet*	GetPIOpt1()	{	
								return m_pOpt1;}				// �\���I��OPT�Q�Z�b�g
	MsBitSet*	GetPIOpt2()	{	
								return m_pOpt2;}				// �\���I�tOPT�Q�Z�b�g
	MUINT		GetPITenkai()	{
								return m_iTenkai;}				// �Z���W�J����
	MINT		GetPIKai()	{
								return m_ibKai;}				// �K
	MINT		GetPICdHgt()	{
								return m_ibCdHgt;}				// ���t�������R�[�h
	MINT		GetPICdInpKbCd()	{
								return m_ibCdInpKbCd;}			// ���͓_�敪�R�[�h
	MINT		GetPIDisplayFlg()	{
								return m_ibDisplayFlg;}			// �\���t���O(�}�`,���L1,���L2)
	MINT		GetPIPanelNo()	{
								return m_isPanelNo;}			// �p�l���ԍ�
	MINT		GetPIKaikoNo()	{
								return m_isKaikoNo;}			// �J���ԍ�
	MINT		GetPIIdPartsTp()	{
								return m_isIdPartsTp;}			// ���iID
	MINT 		GetPIIdMbr()	{
								return m_isMbrId;}				// ���@�^��ID
	mhPartsTp*	GetPIPartsTp()	{
								return m_pPartsTp;}				// ���i���
	MhMbr*		GetPIMbr()		{	
								return m_pMbr;}					// ���@�^��
	MgLine3 	GetPIPlcIti()	{
								return m_lnPlc;}				// p[0]: �n�_ | �z�u�_
																// p[1]: �I�_ | �z�u�����_
	MgPoint3 	GetPIPlcIti( MINT iti)	{ 
								return m_lnPlc.p[iti];}			// p[0]: �n�_ | �z�u�_
																// p[1]: �I�_ | �z�u�����_
	MgVect3 	GetPIUpPlc()	{
								return m_vUpPlc;}				// �z�u�����
	MREAL		GetPISinZure ()	{
								return m_rSinZure;}				// �ގ��c����ʁ@	>0:�E���A<0:����
	MREAL 		GetPIPlcZure()	{
								return m_rPlcZure;}				// �z�u�_�����		>0:�O�A�@<0:��
	MREAL*		GetPILenHosei()	{
								return m_rLngHosei;}			// �����␳�l�i�n�_��(0)�A�I�_��(1)�j
	MREAL		GetPILenHosei( MINT iti)	{
								return m_rLngHosei[iti];}		// �����␳�l�i�n�_��(0)�A�I�_��(1)�j
	MREAL*		GetPIHgt()		{	
								return m_rHgt;}					// �����i���t������(0)�A����(1)�j
	MREAL		GetPIHgt( MINT iti)	{
								return m_rHgt[iti];}			// �����i���t������(0)�A����(1)�j
	MgPoint2	GetPICmntPt()	{
								return m_ptCmnt1;}				// ���L�\���ʒu
	class MhAuxAttr*	GetPIAuxAttr()	{
								return m_pAuxAttr;}				// �⏕�����@����
	MhTateguInfo*	GetPIAuxTategu()	{
								return m_pAuxTategu;}			// �⏕�����@����
	JTTenkaiPr* GetPIAuxTenkai()	{
								return m_pAuxTenkai;}			// �⏕�����@�Z���W�J
	MhZukei*	GetPIZukei()	{
								return m_pZukei;}				// �}�`
	MREAL		GetPIMaeHosei()	{
								return m_rSinZure;}				// �p�l����O���␳�l
	MREAL		GetPIOku()	{	
								return m_rPlcZure;}				// �p�l�����s��
	MREAL		GetPIOkuHosei()	{
								return m_rHgt[1];}				// �p�l�������␳�l

//G	MINT	GetPTId()		{		
//								return m_pPartsTp->m_iPTId;}
	MINT	GetPTCdGp()		{		
								return m_pPartsTp->m_pPTGp->m_iCdGp;}	// �\��(�g)�R�[�h( �����A�����A�V��A�ϗ͕ǁA�ǁA���A��b)
	MINT	GetPTCdBr()		{		
								return m_pPartsTp->m_iPTCdBr;}		// ���ރR�[�h("����", "����", "�p�l��", "����", "��", "��b", "����", "���", "���L", "���̑�")
	MCHAR*	GetPTNmGeneral(){
								return m_pPartsTp->m_sPTNmGeneral;}	// ����
	MCHAR*	GetPTNmParts1()	{	
								return m_pPartsTp->m_sPTNmParts1;}		// ����p���ޖ�1
	MCHAR*	GetPTNmParts2()	{	
								return m_pPartsTp->m_sPTNmParts2;}		// �ώZ�p���ޖ�2
	DWORD	GetPTColor()	{	
								return m_pPartsTp->m_dPTColor;}		// �F
	MINT	GetPTCdBuzai()	{	
								return m_pPartsTp->m_iPTCdBuzaiR;}	// ���ރR�[�h	�Ǎ��ݗp
	MINT	GetPTCdBuzaiW()	{	
								return m_pPartsTp->m_iPTCdBuzaiW;}	// ���ރR�[�h	�������ݗp(���i�d�l�e�[�u��VerUp���C���e�i���X�p)
	MCHAR*	GetPTTpMbr()	{	
								return m_pPartsTp->m_sPTTpMbr;}		// ���@�^���I��p��ރR�[�h
	MCHAR*	GetPTCdMbr()	{
								return m_pPartsTp->m_sPTCdMbr;}		// ��\���@�^��
	MINT	GetPTCdInpKb()	{	
								return m_pPartsTp->m_iPTCdInpKb;}		// ���͓_�敪�R�[�h
	MSTNDH	GetPTCdHgt()	{	
								return m_pPartsTp->m_iPTCdHgt;}		// ���t��������R�[�h
	MINT	GetPTCdPlc()	{	
								return m_pPartsTp->m_iPTCdPlc;}		// �z�u�R�[�h
	MINT	GetPTCdIzon()	{	
								return m_pPartsTp->m_iPTCdIzon;}		// �ˑ��R�[�h
	MINT	GetPTCdMarume()	{	
								return m_pPartsTp->m_iPTCdMarume;}	// �ۂ߃R�[�h
	MINT	GetPTCdToritk()	{	
								return m_pPartsTp->m_iPTCdToritk;}	// ���t���R�[�h�@�㉺�t���R�[�h (0:���t��, 1:��t��)

	MCHAR*	GetMbCdMbr()	{	
								return m_pMbr->m_cMbrCode;}			// ���@�^��
	MCHAR*	GetMbCdMbrW()	{	
								return m_pMbr->m_cMbrCodeW;}		// ���@�^�� (�������ݗp�@�ʏ�m_cCode�Ɠ��� VerUp���ɕύX�������e������)
	MREAL	GetMbHeight()	{	
								return m_pMbr->m_rBziHeight;}		// ���ލ���
	MREAL	GetMbWidth()	{	
								return m_pMbr->m_rBziWidth;}		// ���ޕ�
	MREAL	GetMbWidthR()	{	
								return m_pMbr->m_rBziWidth * 0.5f + m_pMbr->m_rBziSZure;}	// ���މE����
	MREAL	GetMbWidthL()	{	
								return m_pMbr->m_rBziWidth * 0.5f - m_pMbr->m_rBziSZure;}	// ���ލ�����
	MREAL	GetMbTWidth()	{	
								return m_pMbr->m_rBziHeight;}		// ���Ęg�p��
	MREAL	GetMbTWidthR()	{	
								return m_pMbr->m_rBziHeight * 0.5f;}	// ���Ęg�p�E����
	MREAL	GetMbTWidthL()	{	
								return m_pMbr->m_rBziHeight * 0.5f;}	// ���Ęg�p������
	MREAL	GetMbTHeight()	{	
								return m_pMbr->m_rBziWidth;}			// ���Ęg�p����
	MREAL	GetMbTHeightF()	{	
								return m_pMbr->m_rBziWidth * 0.5f;}	// ���Ęg�p����/2.
	MREAL	GetMbTHeightB()	{	
								return m_pMbr->m_rBziWidth * 0.5f;}	// ���Ęg�p����/2.
	MCHAR*	GetMbType()		{		
								return m_pMbr->m_cMbrType;}			// ���@�^���I��p��ރR�[�h

	bool	IsYane()		{		
								return m_pPartsTp->IsYane();}			// ����
	bool	IsTenjo()		{		
								return m_pPartsTp->IsTenjo();}		// �V��
	bool	IsYuka()		{		
								return m_pPartsTp->IsYuka();}			// ��
	bool	IsKiso()		{		
								return m_pPartsTp->IsKiso();}			// ��b
 
	bool	IsTategu()		{		
								return m_pPartsTp->IsTategu();}		// ����
	bool	IsTenkai()		{		
								return m_pPartsTp->IsTenkai();}		// �Z���W�J
	bool	IsFrame()		{		
								return m_pPartsTp->IsFrame();}		// ����( ���Ęg| ��)
	bool	IsPanel()		{		
								return m_pPartsTp->IsPanel();}		// �p�l��
	bool	IsKaiko()		{		
								return m_pPartsTp->IsKaiko();}		// �J��
	bool	IsKabe()		{		
								return m_pPartsTp->IsKabe();}			// ��
	bool	IsTaiKabeArea()	{	
								return m_pPartsTp->IsTaiKabeArea();}	// �ϗ͕ǋ��
	bool	IsTaiKabeLine()	{	
								return m_pPartsTp->IsTaiKabeLine();}	// �ϗ͕ǐ�
	bool	IsSijiKabeLine()	{
								return m_pPartsTp->IsSijiKabeLine();}	// �x���ǐ�
	bool	IsOukaZai()		{		
								return m_pPartsTp->IsOukaZai();}		// ���U��
	bool	IsYukaPanel()	{	
								return m_pPartsTp->IsYukaPanel();}	// ���p�l��
	bool	IsKabePanel()	{	
								return m_pPartsTp->IsKabePanel();}	// �ǃp�l��
	bool	IsTenjoPanel()	{	
								return m_pPartsTp->IsTenjoPanel();}	// �V��p�l��
	bool	IsYanePanel()	{	
								return m_pPartsTp->IsYanePanel();}	// �����p�l��
	
	void	Print(MCHAR *s);
};

} // namespace MC