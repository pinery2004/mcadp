#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdFigPmt.h
//
//		�}�`�v�f
//
//

#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"
#include "MgPoint.h"
#include "MgRect.h"
#include "MgMatD.h"

#define	DLL_EXPORT_MDFIG_DO

#include "MdZukei.h"
#include	"MdmFig.h"
#include "MdModel.h"

#include "MdmDefine.h"
#include "MdAry.h"
#include "MdAryH.h"

#undef	inline_nu
#define inline_nu

namespace MC
{

//==========================================================================================
//	�}�`�v�f�̒ǉ�
//	�E
//
//==========================================================================================

// ==================== �}�`���� ==========================
// �����v�b�V��

inline_nu void	MDPMT::zPush( void)
{ 
	SetHd( MZAT_PUSH, 0, 0);
}

inline_nu void	MDFIG::zPush( void)
{ 
	GetpPmt( m_pPmtl->m_n)->SetHd( MZAT_PUSH, 0, MZWD_PUSH);
	IncrN( MZWD_PUSH + 1);
}

// �����v��

inline_nu void	MDPMT::zPull( void)
{ 
	SetHd( MZAT_PULL, 0, 0);
}

inline_nu void	MDFIG::zPull( void)
{ 
	GetpPmt( m_pPmtl->m_n)->SetHd( MZAT_PULL, 0, MZWD_PULL);
	IncrN( MZWD_PULL + 1);
}

// �}�[�J

inline_nu void	MDPMT::zMarker(
						MINT	i_iTp,			// �}�[�J�^�C�v
						MREAL	i_rSz			// �}�[�J�T�C�Y
				)
{ 
	SetHd( MZAT_MRKR, i_iTp, MZWD_MRKR);
	(MREAL&)m_dt[0] = i_rSz;
}

inline_nu void	MDFIG::zMarker(
						MINT	i_iTp,			// �}�[�J�^�C�v
						MREAL	i_rSz			// �}�[�J�T�C�Y
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zMarker( i_iTp, i_rSz);
	IncrN( MZWD_MRKR + 1);
}

// �h��Ԃ�

inline_nu void	MDPMT::zPaint(
						MINT	i_iTp,			// �h��Ԃ��^�C�v ( 0:�z���[�A1:�\���b�h�A2:�n�b�`���O)
						MINT	i_iId,			// �n�b�`���O�p�^�[��ID
						MINT	i_iEdg			// �G�b�W�t���O		( 0: OFF, 1: ON)
				)
{ 
	SetHd( MZAT_PAINT, i_iTp, MZWD_PAINT);
	(MUHALF&)m_dt[0] = MUHALF( i_iId, i_iEdg);
}

inline_nu void	MDFIG::zPaint(
						MINT	i_iTp,			// �h��Ԃ��^�C�v ( 0:�z���[�A1:�\���b�h�A2:�n�b�`���O)
						MINT	i_iId,			// �n�b�`���O�p�^�[��ID
						MINT	i_iEdg			// �G�b�W�t���O		( 0: OFF, 1: ON)
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zPaint( i_iTp, i_iId, i_iEdg);
	IncrN( MZWD_PAINT + 1);
}

// ����

inline_nu void	MDPMT::zLineTp(
						MINT	i_iTp			// ����
				)
{ 
	SetHd( MZAT_LINETP, i_iTp, 0);
}

inline_nu void	MDFIG::zLineTp(
						MINT	i_iTp			// ����
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zLineTp( i_iTp);
	IncrN( MZWD_LINETP + 1);
}

// �F( RGB) ( byte * 3)

inline_nu void	MDPMT::zColorRGB(
						MUQUARTER i_iRgb			// RGB	( 0, r, g, b)
				)
{ 
	SetHd( MZAT_COLOR, 0, MZWD_COLOR_I);
	(MUQUARTER&)m_dt[0] = i_iRgb;
}

inline_nu void	MDFIG::zColorRGB(
						MUQUARTER i_iRgb			// RGB	( 0, r, g, b)
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zColorRGB( i_iRgb);
	IncrN( MZWD_COLOR_I + 1);
}

// �F( RGB) ( MFLOAT * 3)

inline_nu void	MDPMT::zColorRGB(
						FLOAT3&	i_f3Rgb		// RGB	( 1., 1., 1.)
				)
{ 
	SetHd( MZAT_COLOR, 1, MZWD_COLOR_R);
	(FLOAT3&)m_dt[0] = i_f3Rgb;
}

inline_nu void	MDFIG::zColorRGB(
						FLOAT3&	i_f3Rgb		// RGB	( 1., 1., 1.)
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zColorRGB( i_f3Rgb);
	IncrN( MZWD_COLOR_R + 1);
}

// �F(�p���b�g)

inline_nu void	MDPMT::zColorPlt(
						MINT	i_iPltN			// �p���b�g�m��
				)
{ 
	SetHd( MZAT_COLOR, 2, MZWD_COLOR_P);
	(MINT&)m_dt[0] = i_iPltN;
}

inline_nu void	MDFIG::zColorPlt(
						MINT	i_iPltN			// �p���b�g�m��
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zColorPlt( i_iPltN);
	IncrN( MZWD_COLOR_P + 1);
}

// ���ߗ�

inline_nu void	MDPMT::zTransmissivity(
						MFLOAT	i_fTransm		// ���ߗ� ( 0. �` 1.)
				)
{ 
	SetHd( MZAT_TRANSM, 0, MZWD_TRANSM);
	(MREAL&)m_dt[0] = i_fTransm;
}

inline_nu void	MDFIG::zTransmissivity(
						MFLOAT	i_fTransm		// ���ߗ� ( 0. �` 1.)
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zTransmissivity( i_fTransm);
	IncrN( MZWD_TRANSM + 1);
}

// ����

inline_nu void	MDPMT::zLineWd(
						MFLOAT	i_rLWd			// ����
				)
{ 
	SetHd( MZAT_LINEWD, 0, MZWD_LINEWD);
	(MREAL&)m_dt[0] = i_rLWd;
}

inline_nu void	MDFIG::zLineWd(
						MFLOAT	i_rLWd			// ����
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zLineWd( i_rLWd);
	IncrN( MZWD_LINEWD + 1);
}

// �ގ�( RGB) ( byte * 3)

inline_nu void	MDPMT::zMaterialRGBA(
						MINT	i_iMtN,			// �ގ��ԍ�	( MC_AMBIENT:1		�����̔��ˎw��
												//			  MC_DIFFUSE:2		�g�U���̔��ˎw��
												//			  MC_SPECULAR:3		���ʌ��̔��ˎw��
												//			  MC_EMISSION:4		���ˌ��̕��ˋP�x
												//			  MC_AMBIENT_AND_DIFFUSE:5	�����Ɗg�U��)
						MUQUARTER i_iRgb		// RGB	( A{���ߗ�}, R, G, B)
				)
{ 
	SetHd( MZAT_MTRL, MC_INTRGB | i_iMtN, MZWD_MTRL_I);
	(MUQUARTER&)m_dt[0] = i_iRgb;
}

inline_nu void	MDFIG::zMaterialRGBA(
						MINT	i_iMtN,			// �ގ��ԍ�	( MC_AMBIENT:1		�����̔��ˎw��
												//			  MC_DIFFUSE:2		�g�U���̔��ˎw��
												//			  MC_SPECULAR:3		���ʌ��̔��ˎw��
												//			  MC_EMISSION:4		���ˌ��̕��ˋP�x
												//			  MC_AMBIENT_AND_DIFFUSE:5	�����Ɗg�U��)
						MUQUARTER i_iRgb		// RGB	( A{���ߗ�}, R, G, B)
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zMaterialRGBA( i_iMtN, i_iRgb);
	IncrN( MZWD_MTRL_I + 1);
}

// �ގ�( RGB) ( MFLOAT * 3)

inline_nu void	MDPMT::zMaterialRGBA(
						MINT	i_iMtN,			// �ގ��ԍ�	( MC_AMBIENT:1		�����̔��ˎw��
												//			  MC_DIFFUSE:2		�g�U���̔��ˎw��
												//			  MC_SPECULAR:3		���ʌ��̔��ˎw��
												//			  MC_EMISSION:4		���ˌ��̕��ˋP�x
												//			  MC_AMBIENT_AND_DIFFUSE:5	�����Ɗg�U��)
						FLOAT3& i_f3Rgb,		// RGB		( ( 0.�`1.), ( 0.�`1.), ( 0.�`1.))
						MFLOAT	 i_fAlpha		// A ���ߗ�	( 0. �` 1.)
				)
{ 
	SetHd( MZAT_MTRL, i_iMtN, MZWD_MTRL_R);
	(FLOAT3&)m_dt[0] = i_f3Rgb;
	m_dt[3] = i_fAlpha;
}

inline_nu void	MDFIG::zMaterialRGBA(
						MINT	i_iMtN,			// �ގ��ԍ�	( MC_AMBIENT:1		�����̔��ˎw��
												//			  MC_DIFFUSE:2		�g�U���̔��ˎw��
												//			  MC_SPECULAR:3		���ʌ��̔��ˎw��
												//			  MC_EMISSION:4		���ˌ��̕��ˋP�x
												//			  MC_AMBIENT_AND_DIFFUSE:5	�����Ɗg�U��)
						FLOAT3& i_f3Rgb,		// RGB		( ( 0.�`1.), ( 0.�`1.), ( 0.�`1.))
						MFLOAT	i_fAlpha		// A ���ߗ�	( 0. �` 1.)
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zMaterialRGBA( i_iMtN, i_f3Rgb, i_fAlpha);
	IncrN( MZWD_MTRL_R + 1);
}

// �ގ����ʌ�(����)�W��

inline_nu void	MDPMT::zMaterialShininess(
						MREAL	i_rShns			// ���ʌ��W�� ( 0. �` 128.)
				)
{ 
	SetHd( MZAT_MTRLSHINNS, 0, MZWD_MTRLSHINNS);
	(MREAL&)m_dt[0] = i_rShns;
}

inline_nu void	MDFIG::zMaterialShininess(
						MREAL	i_rShns			// ���ʌ��W�� ( 0. �` 128.)
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zMaterialShininess( i_rShns);
	IncrN( MZWD_MTRLSHINNS + 1);
}

// �e�N�X�`��

inline_nu void	MDPMT::zTexture(
						MINT		i_iTxtrId	// �e�N�X�`���h�c
				)
{ 
	SetHd( MZAT_TXTR, 0, MZWD_TXTR);
	(MINT&)m_dt[0] = i_iTxtrId;
}

inline_nu void	MDFIG::zTexture(
						MINT		i_iTxtrId	// �e�N�X�`���h�c
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zTexture( i_iTxtrId);
	IncrN( MZWD_TXTR + 1);
}

// �e�N�X�`�����W

inline_nu void	MDPMT::zTextureCoordinate(
						MINT		i_iMdCre,	// ���W�������[�hA	( MC_EYE_PLANE:0	EYE_PLANE�A
												//					  MC_OBJECT_PLANE:1	OBJECT_PLANE�A
												//					  MC_2:���}�b�v�p)
						MINT		i_iMdCdn,	// ���W�������[�hB	( MC_PLANE:0		�ʂ���x�N�g���𐶐��A
												//					  MC_1:�w�肵���x�N�g��)
				const	MgVect2D* 	i_pvszimg,	// �C���[�W���@	(mm)( ���A�c) 
				const	MgMat3E*		i_pmatH		// �z�u�}�g���b�N�X
				)
{ 
	SetHd( MZAT_TXTRC, 0, ((i_iMdCdn == 0) ? MZWD_TXTRC_S:MZWD_TXTRC_L) );
	(MHALF&)m_dt[0] = MHALF( i_iMdCre, i_iMdCdn);
	if ( i_pvszimg)
		(MgVect2D&)m_dt[1] = *i_pvszimg;
	if ( i_pmatH)
		(MgMat3E&)m_dt[3] = *i_pmatH;
}

inline_nu void	MDFIG::zTextureCoordinate(
						MINT		i_iMdCre,	// ���W�������[�hA	( 0:EYE_PLANE�A1:OBJECT_PLANE�A2:���}�b�v�p)
						MINT		i_iMdCdn,	// ���W�������[�hB	( 0:�ʂ���x�N�g���𐶐��A1:�w�肵���x�N�g��)
				const	MgVect2D* 	i_pvszimg,	// �C���[�W���@	(mm)( ���A�c) 
				const	MgMat3E*		i_pmatH		// �z�u�}�g���b�N�X
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zTextureCoordinate( i_iMdCre, i_iMdCdn, i_pvszimg, i_pmatH);
	if ( i_iMdCdn = 0) {
		IncrN( MZWD_TXTRC_S + 1);
	} else {
		IncrN( MZWD_TXTRC_L + 1);
	}
}

// �e�N�X�`���p�����[�^

inline_nu void	MDPMT::zTextureParam(
						MINT	i_iTp,			// �֐�				( 0:�X�e�b�J�[�A1:�ϒ��A2:����)
						MINT	i_iPxLap,		// ���b�v�p�����[�^	( ���A�c)	( 0:REPEAT�A1:CLANP)
						MINT	i_iPyLap,		//
						MINT	i_iFltEx,		// �g��^�k���t�B���^
						MINT	i_iFltRd,		//	( 0:��������A1:�ڂ₩���A
												//	  2:�������� - ��������
												//	  3:�������� - �ڂ₩��
												//	  4:�ڂ₩�� - ��������
												//	  5:�ڂ₩�� - �ڂ₩��)
						MREAL3& i_fColBlc1,		// ���E���F1		
						MREAL3& i_fColBlc2		// ���E���F2		
				)
{ 
	SetHd( MZAT_TXTPRM, i_iTp, MZWD_TXTPRM);
	(MQUARTER&)m_dt[0] = MQUARTER( i_iPxLap, i_iPyLap, i_iFltEx, i_iFltRd);
	(MREAL3&)m_dt[1] = i_fColBlc1;
	(MREAL3&)m_dt[4] = i_fColBlc2;
}

inline_nu void	MDFIG::zTextureParam(
						MINT	i_iTp,			// �֐�				( 0:�X�e�b�J�[�A1:�ϒ��A2:����)
						MINT	i_iPxLap,		// ���b�v�p�����[�^	( ���A�c)	( 0:REPEAT�A1:CLANP)
						MINT	i_iPyLap,		//
						MINT	i_iFltEx,		// �g��^�k���t�B���^
						MINT	i_iFltRd,		//	( 0:��������A1:�ڂ₩���A
												//	  2:�������� - ��������
												//	  3:�������� - �ڂ₩��
												//	  4:�ڂ₩�� - ��������
												//	  5:�ڂ₩�� - �ڂ₩��)
						MREAL3& i_fColBlc1,		// ���E���F1		
						MREAL3& i_fColBlc2		// ���E���F2		
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zTextureParam( i_iTp, i_iPxLap, i_iPyLap, i_iFltEx, i_iFltRd,
										   i_fColBlc1,i_fColBlc2);
	IncrN( MZWD_TXTPRM + 1);
}

// ���ʔ��˗�
inline_nu void	MDPMT::zShininess(
						MREAL	i_fShns			// ���ʔ��˗� ( 0. �` 1.)
				)
{ 
	SetHd( MZAT_SHINNS, 0, MZWD_SHINNS);
	(MREAL&)m_dt[0] = i_fShns;
}

inline_nu void	MDFIG::zShininess(
						MREAL	i_fShns			// ���ʔ��˗� ( 0. �` 1.)
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zShininess( i_fShns);
	IncrN( MZWD_SHINNS + 1);
}

// PovRay�o�͑���

inline_nu void	MDPMT::zPovRay(
						MCHAR*	i_sStr			// ������
				)
{ 
	SetHd( MZAT_POVRAY, 0, MNWORD( i_sStr));

#pragma warning(push)
#pragma warning(disable:4996)

	Mstrcpy( (MCHAR*)&m_dt[0], i_sStr);

#pragma warning(pop)

}

inline_nu void	MDFIG::zPovRay(
						MCHAR*	i_sStr			// ������
				)
{ 
	GetpPmt( m_pPmtl->m_n)->zPovRay( i_sStr);
	IncrN( MZWD_POVRAY + MNWORD( i_sStr));
}

// ==================== �}�`�v�f ==========================
// �_
inline_nu void	MDPMT::Point3(
				const	MgPoint3D& i_Pt)			// �_�f�[�^
{
	SetHd( MZCD_PNT, MZTP_3D, WSZMgPoint3D());
	(MgPoint3D&)m_dt[0] = i_Pt;
}

inline_nu void MDFIG::Point3(
				const	MgPoint3D& i_Pt)			// �_�f�[�^
{
	GetpPmt( m_pPmtl->m_n)->Point3( i_Pt);
	IncrN( MZWD_PNT_3D + 1);
}

// �����i3�����j
inline_nu void MDPMT::Line3D(
				const	MgLine3D& i_Ln)			// �����f�[�^
{
	SetHd( MZCD_LINE, MZTP_3D, MZWD_LINE_3D);
	(MgLine3D&)m_dt[0] = i_Ln;
}

inline_nu void MDFIG::Line3D(
				const	MgLine3D& i_Ln)			// �����f�[�^
{
	GetpPmt( m_pPmtl->m_n)->Line3D( i_Ln);
	IncrN( MZWD_LINE_3D + 1);
}

// �����i3�����j
inline_nu void MDPMT::ULine3D(
				const	MgULine3D& i_uLn)		// �����f�[�^
{
	SetHd( MZCD_ULINE, MZTP_3D, MZWD_ULINE_3D);
	(MgULine3D&)m_dt[0] = i_uLn;
}

inline_nu void MDFIG::ULine3D(
				const	MgULine3D& i_uLn)		// �����f�[�^
{
	GetpPmt( m_pPmtl->m_n)->ULine3D( i_uLn);
	IncrN( MZWD_ULINE_3D + 1);
}

// �������i3�����j
inline_nu void MDPMT::HLine3D(
				const	MgHLine3D&	i_hLn)		// �������f�[�^�i3�����j
{
	SetHd( MZCD_HLINE, MZTP_3D, MZWD_HLINE_3D);
	(MgHLine3D&)m_dt[0] = i_hLn;
}

inline_nu void MDFIG::HLine3D(
				const	MgHLine3D&	i_hLn)		// �������f�[�^�i3�����j
{
	GetpPmt( m_pPmtl->m_n)->HLine3D( i_hLn);
	IncrN( MZWD_HLINE_3D + 1);
}

// �܂���i3�����j
inline_nu void MDPMT::Polyl3(
				const	MgPolyl3D& i_Ply)		// �܂���i3�����j
{
	SetHd( MZCD_PLY, MZTP_3D, i_Ply.m_n * 3);
	MgPt3Cpy( (MgPoint3D*)m_dt, i_Ply.m_n, i_Ply.m_p, i_Ply.m_n);
}

inline_nu void MDFIG::Polyl3(
				const	MgPolyl3D& i_Ply)		// �܂���i3�����j
{
	GetpPmt( m_pPmtl->m_n)->Polyl3( i_Ply);
	IncrN( i_Ply.m_n * 3 + 1);
}

// ���p�`�i3�����j
inline_nu void MDPMT::Polyg3(
				const	MgPolyg3D& i_Pgn)		// ���p�`�i3�����j
{
	SetHd( MZCD_PGN, MZTP_3D, i_Pgn.m_n * 3);
	MgPt3Cpy( (MgPoint3D*)m_dt, i_Pgn.m_n, i_Pgn.m_P, i_Pgn.m_n);
}

inline_nu void MDFIG::Polyg3(
				const	MgPolyg3D& i_Pgn)		// ���p�`�i3�����j
{
	GetpPmt( m_pPmtl->m_n)->Polyg3( i_Pgn);
	IncrN( i_Pgn.m_n * 3 + 1);
}

// �~�i3�����j
inline_nu void MDPMT::Cir3(
				const	MgCir3D& i_Cir)			// �~�i3�����j
{
	SetHd( MZCD_CIR, MZTP_3D, MZWD_CIR_3D);
	(MgCir3D&)m_dt = i_Cir;
}

inline_nu void MDFIG::Cir3(
				const	MgCir3D& i_Cir)			// �~�i3�����j
{
	GetpPmt( m_pPmtl->m_n)->Cir3( i_Cir);
	IncrN( MZWD_CIR_3D + 1);
}

// �~�ʁi3�����j
//inline_nu MDZArc3::MDZArc3( MgArc3D& i_Arc)
//{
//	SetHd( MZCD_ARC, MZTP_3D, WSZMgArc3D());
//	m_Arc = i_Arc;
//}
inline_nu void MDPMT::Arc3(
				const	MgArc3D& i_Arc)			// �~�ʁi3�����j
{
	SetHd( MZCD_ARC, MZTP_3D, MZWD_ARC_3D);
	(MgArc3D&)m_dt = i_Arc;
}

inline_nu void MDFIG::Arc3(
				const	MgArc3D& i_Arc)			// �~�ʁi3�����j
{
	GetpPmt( m_pPmtl->m_n)->Arc3( i_Arc);
	IncrN( MZWD_ARC_3D + 1);
}


//// �ȉ~�i3�����j
//inline_nu MDZELPS3::MDZELPS3( MgSLine3 i_sLn)
//{
//	SetHd( MZELN3, MZCD_3D, 6);
//	m_sLn = i_sLn;
//}

//// �ȉ~�ʁi3�����j
//inline_nu MDZELA3::MDZELA3( MgSLine3 i_sLn)
//{
//	SetHd( MZELA3, MZCD_3D, 6);
//	m_sLn = i_sLn;
//}

// �ʕ��i3�����j
inline_nu void MDPMT::Plane3(
				const	MgPlane3D& i_Pln)			// �ʕ��f�[�^
{
	SetHd( MZCD_PLN, MZTP_3D, MZWD_PLN_3D);
	(MgPlane3D&)m_dt[0] = i_Pln;
}

inline_nu void MDFIG::Plane3(
				const	MgPlane3D& i_Pln)			// �ʕ��f�[�^
{
	GetpPmt(  m_pPmtl->m_n)->Plane3( i_Pln);
	IncrN( MZWD_PLN_3D + 1);
}

// �������ʁi3�����j
inline_nu void MDPMT::IPlane3(
				const	MgPlane3D& i_iPln)			// �������ʃf�[�^
{
	SetHd( MZCD_IPLN, MZTP_3D, MZWD_IPLN_3D);
	(MgPlane3D&)m_dt[0] = i_iPln;
}

inline_nu void MDFIG::IPlane3(
				const	MgPlane3D& i_iPln)			// �������ʃf�[�^
{
	GetpPmt( m_pPmtl->m_n)->IPlane3( i_iPln);
	IncrN( MZWD_IPLN_3D + 1);
}

//// �~���ʁi3�����j
//inline_nu MDZCYL3::MDZCYL3( MgSLine3 i_sLn)
//{
//	SetHd( MZSLINE3, MZCD_3D, 6);
//	m_sLn = i_sLn;
//}

//// �R���X�v���C���Ȑ��̍\���_
//inline_nu MDZSPLC3::MDZSPLC3( MgSLine3 i_sLn)
//{
//	SetHd( MZSLINE3, MZCD_3D, 6);
//	m_sLn = i_sLn;
//}
//
//// �R���X�v���C���Ȑ��i3�����j
//inline_nu MDZSPL3::MDZSPL3( MgSLine3 i_sLn)
//{
//	SetHd( MZSLINE3, MZCD_3D, 6);00.
//	m_sLn = i_sLn;
//}
//
//// ���@�\���v�f
//inline_nu MDZMESLC::MDZMESLC( MgSLine3 i_sLn)
//{
//	SetHd( MZSLINE3, MZCD_3D, 6);
//	m_sLn = i_sLn;
//}
//
//// ���@�\��(����)
//inline_nu MDZMESL3::MDZMESL3( MgSLine3 i_sLn)
//{
//	SetHd( MZSLINE3, MZCD_3D, 6);
//	m_sLn = i_sLn;
//}
//
//
//// ���@�\��(�p�x)
//inline_nu MDZMESA3::MDZMESA3( MgSLine3 i_sLn)
//{
//	SetHd( MZSLINE3, MZCD_3D, 6);
//	m_sLn = i_sLn;
//}
//
//// ���@�\��(���a | ���a)
//inline_nu MDZMESR3::MDZMESR3( MgSLine3 i_sLn)
//{
//	SetHd( MZSLINE3, MZCD_3D, 6);
//	m_sLn = i_sLn;
//}

//// �r�b�g�}�b�v�t�@�C���w�b�_

//// �r�b�g�}�b�v���w�b�_

//// �r�b�g�}�b�v�J���[�f�[�^
////	���̍\���́i�傫����4�o�C�g�j�̓r�b�g�}�b�v�̃J���[�f�[�^��\�����̂����A�P�̍\���̂�
////	�P�̃J���[�f�[�^��\���Ă���B�܂�A16�F�Ȃ�16�A256�F�Ȃ�256��RGBQUAD�\���̂�����ł���B
////	BITMAPFILEHEADER�\���̂�bfOffBits�̒l��BITMAPINFOHEADER�\���̂�biBitCount�̒l�ɂ���Č��肳���B
////	�Ⴆ��biBitcount = 8�̏ꍇ�A���̃r�b�g�}�b�v��256�F�ł��邩��RGB�\���̂�256���݂���B
////	�����bfOffBits = 14 + 40 + 4 * 256 = 1078 �ƂȂ�B
////	�A���A16�r�b�g(65536�F)�ȏ�̏ꍇ�̓J���[�p���b�g���s�v�Ȃ��߁A���̍\���͎̂g�p����Ȃ��B
////	���bfOffBits = 54�ł���B
////	�Q�l	http://www.alpha-net.ne.jp/users2/uk413/vc/VCT_DIB.html
////			VC++�e�N�j�b�N : �f�B�X�N���BMP�t�@�C����\��

//// �r�b�g�}�b�v
//
//// �����v�f
//
//// ����

} // namespace MC
