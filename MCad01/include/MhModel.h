#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdModel.h
//
//		�l�b�`�c�ƃ��f��
//

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MDMODEL_DO
	#pragma message( "<<< MhModel�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MhModel�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

namespace MC
{

//typedef	MINT			MDID;	
//==========================================================================================
//	�ƃ��f��
typedef struct _mhdbie {
	MDID*	pidGrp;								// �O���[�vID
	MINT	nGrp;								// �O���[�vID��
	MDID*	pidScm;								// �X�L�[�}ID
	MINT	nScm;								// �X�L�[�}ID��
	MDID*	pidLyr;								// ���C���[ID
	MINT	nLyr;								// ���C���[ID��

	MINT	nFKai;								// �n��K��
	MINT	nBKai;								// �n���K��
	MINT	nAKai;								// �n���K��
} MhDbIE;

class DLL_EXPORT MhModel
{
public:
	static MhDbIE	m_db;						// DB

public:
	MhModel();
	~MhModel();

	// �g�p�J�n�錾
	static MINT Open( void);
	
	// �f�o�b�O�p�g���[�X�o��
	static void Print( MCHAR* s);
};

//	�g���[�X
inline void MhModel::Print( MCHAR* s)
{
	MBTRCPRINTS( s);
}

extern MhModel	z_DbIE;

inline MINT MhCreateGrp1( MCHAR i_cNmGrp[], MREAL i_rH, MREAL i_rF, MDID i_nhGrp, MINT i_sz)
{
	return DGrp::CreateGrp( i_cNmGrp, i_rH, i_rF,
						 &z_DbIE.m_db.pidGrp[i_nhGrp],
						 i_sz);
}

MINT MhCreateGrp2( MCHAR i_cNmGrp[], MINT i_iKai, MREAL i_rH, MREAL i_rF, MDID i_nhGrp, MINT iKai, MINT i_sz);

inline MINT MhCreateScm1( MCHAR i_cNmScm[], MDID i_nhScm, MINT i_sz)
{
	return DGrp::CreateScm( i_cNmScm,
						 &z_DbIE.m_db.pidScm[i_nhScm],
						 i_sz);
}

MINT MhCreateScm2( MCHAR i_cNmScm[], MINT i_iTp, MINT i_nhScm, MINT iTp, MINT i_sz);

inline MINT MhCreateLyr1( MDID i_nhScm, MDID i_nhGrp, MDID i_nhLyr, MINT i_sz)
{
	return DLyr::CreateLyr(
						z_DbIE.m_db.pidScm[i_nhScm],
						z_DbIE.m_db.pidGrp[i_nhGrp],
						&z_DbIE.m_db.pidLyr[i_nhLyr],
						i_sz);
}

MINT MhCreateLyr2( MDID i_nhScm, MINT i_iTp, MDID i_nhGrp, MINT i_iKai, MINT i_nhLyr, MINT i_sz);

} // namespace MC