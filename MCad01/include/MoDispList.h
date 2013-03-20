#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MoDispList.h
//
//		�l�b�`�c���f��
//						�f�B�X�v���C���X�g
//
//
//==========================================================================================

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_DISPLIST_DO
	#pragma message( "<<< DispList�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_SUB_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== MgPlane�Edll_IMport ===")
			#define DLL_EXPORT					__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

class DLL_EXPORT DispList
{
public:

	/////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�S�\���G���e�B�e�B�̃f�B�X�v���C���X�g���쐬����
	//
	static MINT DrawAllEnt(							//
					const	MgPoint3&	PtCtr,		// �\���ƃ��f���̒��S
							MREAL		rB			// �R�����\���{��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�}�`�̃f�B�X�v���C���X�g���쐬����
	static MINT	DrawFig(
					class	MDFIG&		Fig,		// �}�`
					const	MgPoint3	&PtCtr,		// �\���ƃ��f���̒��S
							MREAL		rB			// �R�����\���{��
					);

	
	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�_�̃f�B�X�v���C���X�g���쐬����		(�����W)
	//			
	static void DrawPoint(
					const	MgPoint3	&i_Pt,		// �_						(�����W)
					const	MgPoint3	&i_PtCtr,	// �\���ƃ��f���̒��S
							MREAL		i_rB		// �R�����\���{��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�����̃f�B�X�v���C���X�g���쐬����		(�����W)
	//			
	static void DrawLine( 
					const	MgLine3		&Ln,		// �O�p�`					(�����W)
					const	MgPoint3	&PtCtr,		// �\���ƃ��f���̒��S
							MREAL		rB			// �R�����\���{��
					);


	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�R�p�`�̃f�B�X�v���C���X�g���쐬����	(�_�����W)
	//				(���Ԃ𖄂߂�ׂɎ኱�傫�߂ɍ쐬����j�i�v�����j
	//			
	static void DspTriangles( 
					const	MgPolyg3	&PGTri,			// �O�p�`				(�_�����W)
					const	MgVect3		&VuUp			// �R�p�`���ʂ̖@���x�N�g��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�S�p�`�̃f�B�X�v���C���X�g���쐬����	(�_�����W)
	//				(��ӂƏ�ӂ��쐬)
	//			
	static void DspQuads( 
					const	MgLine3		&LnLf,			// ��Ӂi�E�Ӂj			(�_�����W)
					const	MgLine3		&LnRt			// ��Ӂi���Ӂj			(�_�����W)
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z���t�����p�`�̃f�B�X�v���C���X�g���쐬����	(�����W)
	//			
	static void DrawPolygon(
					const	MgGPolyg3	&GPgR,			// ���t�����p�`			(�����W)
					const	MgPoint3	&PtCtr,			// �\���ƃ��f���̒��S	(�����W)
							MREAL		rB				// �R�����\���{��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�����̂̃f�B�X�v���C���X�g���쐬����	(�_�����W)
	//			
	static void DspRectangular( 
							MgPoint3	PT[2][2][2],	// �����̂̒��_���W		(�_�����W)
					const	MgVect3		&VuLng,			// �n�_����I�_�����̒P�ʃx�N�g��
					const	MgVect3		&VuRt,			// �E�����̒P�ʃx�N�g��
					const	MgVect3		&VuUp			// ������̒P�ʃx�N�g��
					);

	////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�����A���̃p�����[�^�̐ݒ� 1
	static void MsSetLight_MaterialParameter1( void);

	static void SetLightModel1( void);

	////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�����̐ݒ�
	//
	static void SetLight( void);

	////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�����A���̃p�����[�^�̐ݒ� 1
	static void MsGlInitialize( void);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z���ޕ\������(Material)��ݒ肷��
	//			
	static void SetMaterial(
							MINT		i_iT,			// �\���^�C�v	{ 0:���́A1:������}�A
							MINT		i_iB			// ����			{ 0:�����A1:��؁A2:�ǁA3:���ށA4:��b�A5:�p�l��_�����A6:�p�l��_�g}
					);

	////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�r���[�|�[�g�T�C�Y�̕ύX
	static void MsOnSize(UINT nType, int cx, int cy);

};

////#ifdef DLL_EXPORT
////	#undef DLL_EXPORT
////#endif
////
////#ifdef DLL_EXPORT_GEOMETRY_DO
////	#pragma message( "<<< DispList�Edll_EXport >>>")
////	#define DLL_EXPORT							__declspec( dllexport)
////#else
////	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
////		#ifdef DLL_NO_IMPORT_SUB_DO
////			#define DLL_EXPORT
////		#else
//////			#pragma message( "=== MgPlane�Edll_IMport ===")
////			#define DLL_EXPORT					__declspec( dllimport)
////		#endif
////	#else
////		#define DLL_EXPORT
////	#endif
////#endif

////class DLL_EXPORT Geometry
////{
////public:

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�����W�n�̓_���W���R�����\�����W(�_�����W)�ɕϊ�����

inline MgPoint3 DPtoDSP(						//							(�_�����W)
				const	MgPoint3	&i_Pt,		// ���Ύ����W�n�̓_���W		(�����W)
				const	MREAL		&i_rZ,		// �����					(�����W)
				const	MgPoint3	&i_PtCtr,	// �����W�̒��S���W			(�����W)
						MREAL		i_rB		// �����W����R�����\�����W�ɕϊ��̔{��
				)
{
	return MgPoint3( ( i_Pt.x - i_PtCtr.x) * i_rB, 
					 ( i_Pt.y - i_PtCtr.y) * i_rB,
					 ( i_Pt.z + i_rZ - i_PtCtr.z) * i_rB
				);
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�����W�n�̐������W���R�����\�����W(�_�����W)�ɕϊ�����

inline MgLine3 DPtoDSP(							//											(�_�����W)
				const	MgLine3		&i_Ln,		// ���Ύ����W�n�̐������W					(�����W)
				const	MREAL		&i_rZ,		// �����									(�����W)
				const	MgPoint3	&i_PtCtr,	// �����W�̒��S���W							(�����W)
						MREAL		i_rB		// �����W����R�����\�����W�ɕϊ��̔{��
				)
{
	return MgLine3( 
			MgPoint3( ( i_Ln.p[0].x - i_PtCtr.x) * i_rB, ( i_Ln.p[0].y - i_PtCtr.y) * i_rB,
					  ( i_Ln.p[0].z + i_rZ - i_PtCtr.z) * i_rB),
			MgPoint3( ( i_Ln.p[1].x - i_PtCtr.x) * i_rB, ( i_Ln.p[1].y - i_PtCtr.y) * i_rB,
					  ( i_Ln.p[1].z + i_rZ - i_PtCtr.z) * i_rB) 
				);
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�����W�n�̉����ʂR�p�`���W���R�����\�����W�ɕϊ�����
//
inline void DPtoDSP3(
				const	MgPolyg3	&i_PgI,		// �����ʂR�p�`�i���������̑��΍����j	(�����W)
				const	MREAL		&i_rZ,		// �����									(�����W)
				const	MgVect3		&i_VtR,		// ������ʂ��牮���ʂւ̈ړ��x�N�g��		(�����W)
				const	MgPoint3	&i_PtCtr,	// �����W�̒��S���W							(�����W)
						MREAL		i_rB,		// �����W����R�����\�����W�ɕϊ��̔{��
						MgPolyg3*	o_pPgO		// �R�����\�����							(�_�����W)
				)
{
	MINT	ic0;
	o_pPgO->m_n = 3;
	for ( ic0=0; ic0<3; ic0++) {
		o_pPgO->m_P[ic0].x = ( i_PgI.m_P[ic0].x + i_VtR.x - i_PtCtr.x) * i_rB;
		o_pPgO->m_P[ic0].y = ( i_PgI.m_P[ic0].y + i_VtR.y - i_PtCtr.y) * i_rB;
		o_pPgO->m_P[ic0].z = ( i_PgI.m_P[ic0].z + i_VtR.z + i_rZ - i_PtCtr.z) * i_rB;
	}
}

inline void DPtoDSP3R(
				const	MgPolyg3	&i_PgI,		// �����ʂR�p�`�i���������̑��΍����j	(�����W)
				const	MREAL		&i_rZ,		// �����									(�����W)
				const	MgVect3		&i_VtR,		// ������ʂ��牮���ʂւ̈ړ��x�N�g��		(�����W)
				const	MgPoint3	&i_PtCtr,		// �����W�̒��S���W							(�����W)
						MREAL		i_rB,			// �����W����R�����\�����W�ɕϊ��̔{��
						MgPolyg3*	o_pPgO		// �R�����\������(������)					(�_�����W)
				)
{
	MINT	ic0, ic1;
	o_pPgO->m_n = 3;
	for ( ic0=0,ic1=2; ic0<3; ic0++,ic1--) {
		o_pPgO->m_P[ic1].x = (i_PgI.m_P[ic0].x + i_VtR.x - i_PtCtr.x) * i_rB;
		o_pPgO->m_P[ic1].y = (i_PgI.m_P[ic0].y + i_VtR.y - i_PtCtr.y) * i_rB;
		o_pPgO->m_P[ic1].z = (i_PgI.m_P[ic0].z + i_VtR.z + i_rZ - i_PtCtr.z) * i_rB;
	}
}


} // namespace MC
