#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgDefine.h 
//	CPR
// 
//	����
//
//	MCAD�Ŏg�p����p��̒�`
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <TCHAR.h>
#include <float.h>
#include <limits.h>
#define		_USE_MATH_DEFINES 
#include <math.h>
#include <time.h>

#ifndef	WINVER
#define		WINVER		 0x0501
#endif

#define	MGPTOL (&g_gTol)

//===========================================================================
//		�}�`���Z �I�������^�X�e�[�^�X
#define		MC_UNDEF			010000000000	// ���ݒ���
//
//#define		MC_PARALLEL			-1			// �X�e�C�^�X�F���s
//#define		MC_TWIST			-2			// �˂���
#define		MC_PARALLEL			010000000000	// �X�e�C�^�X�F���s
#define		MC_TWIST			004000000000	// �˂���
#define		MC_NINT				1				// �����Ȃ�
#define		MC_INT				2				// ��������
#define		MC_REP				4				// �d�Ȃ�
#define		MC_CONNECTION		8				// �ڑ��F���s
#define		MC_MATCH			16				// �I�������ɍ�����������
//
#define		MC_SAME_DIR			0100			// �ӏ㓯�����
#define		MC_REV_DIR			0200			// �ӏ�t����
//
#define		MC_ON_PS			001				// �_�������̎n�_��
#define		MC_INSIDE			002				// �_�������̓�����
#define		MC_ON_PE			004				// �_�������̏I�_��
//
#define		MC_LEFT				010				// �_�������̍���
#define		MC_ON_LINE			020				// �_�������܂��͉���������
#define		MC_RIGHT			040				// �_�������̉E��
#define		MC_CLOSS			100				// �����������̌���
//
#define		MC_PS_NEAR			001				// �n�_���I�_���߂�
#define		MC_PE_NEAR			002				// �I�_���n�_���߂�
//
#define		MC_PS_FAR			002				// �n�_���I�_��藣��Ă���
#define		MC_PE_FAR			001				// �I�_���n�_��藣��Ă���
//
#define		MC_LEFT_ROT			010				// ����]
#define		MC_RIGHT_ROT		040				// �E��]
#define		MC_REAL				010				// ���|���S��
#define		MC_HOLE				040				// ���|���S��
//
#define		MC_OR				001				// �a
#define		MC_DIFF				002				// ��
#define		MC_AND				004				// ��
//
#define		MC_IN_BORDER		001				// �_�����p�`�̓���
#define		MC_ON_BORDER		002				// �_�����p�`�̕ӏ�
#define		MC_OUT_BORDER		004				// �_�����p�`�̊O��
//
#define		MC_ON_SIDE_SAME		010				// ���������Ɠ�������̕ӏ�
#define		MC_ON_SIDE_REV		020				// ���������Ƌt�����̕ӏ�
#define		MC_ON_SIDE			030				// �ӏ�i���������w�薳���j
#define		MC_ON_TOP			040				// ���_��
//
#define		MC_UPPER			010				// �_�����ʂ̕\���i�@���x�N�g�������j
#define		MC_ON_PLANE			020				// �_�����ʏ�
#define		MC_LOWER			040				// �_�����ʂ̗����i�@���x�N�g���t�����j
//
#define		MC_PS_UPPER			001				// �n�_�����ʂ̕\���i�@���x�N�g�������j
#define		MC_PS_ON_PLANE		002				// �n�_�����ʏ�
#define		MC_PS_LOWER			004				// �n�_�����ʂ̗����i�@���x�N�g���t�����j
//
#define		MC_PE_UPPER			010				// �I�_�����ʂ̕\���i�@���x�N�g�������j
#define		MC_PE_ON_PLANE		020				// �I�_�����ʏ�
#define		MC_PE_LOWER			040				// �I�_�����ʂ̗����i�@���x�N�g���t�����j

//===========================================================================
//	�}�`���Z�X�e�[�^�X	(�V�X�e���G���[)

#define		MC_ERR_INPUT	   1100				// ���̓G���[
#define		MC_ERR_NUM_OVER	   1101				// �����\�������G���[
//#define	MC_ERR_BAD_SPLINE  1102				// 
#define		MC_ERR_VECT_ZERO   1103				// �[���x�N�g���ŏ����s�G���[
#define		MC_ERR_INPUT_ZERO  1104				// ���l�[���ŏ����s�G���[
#define		MC_ERR_OFFSET	   1105				// �I�t�Z�b�g���G���[


//===========================================================================
//		�}�`���Z ��Ɨ̈�T�C�Y
#define		MX_PNT0				 20				// �_�o�b�t�@�T�C�Y�O
#define		MX_PNT1				 40				// �_�o�b�t�@�T�C�Y�P
#define		MX_PNT2				130				// �_�o�b�t�@�T�C�Y�Q
#define		MX_PNT3				400				// �_�o�b�t�@�T�C�Y�R
#define		MX_PNT4			   1300				// �_�o�b�t�@�T�C�Y�S
#define		MX_PNT5			   4000				// �_�o�b�t�@�T�C�Y�T
#define		MX_LIN0				 20				// �����o�b�t�@�T�C�Y�O
#define		MX_LIN1				 40				// �����o�b�t�@�T�C�Y�P
#define		MX_LIN2				130				// �����o�b�t�@�T�C�Y�Q
#define		MX_LIN3				400				// �����o�b�t�@�T�C�Y�R
#define		MX_LIN4			   1300				// �����o�b�t�@�T�C�Y�S
#define		MX_LIN5			   4000				// �����o�b�t�@�T�C�Y�T

//===========================================================================
//
//	�}�N����`
//

#define		MGABS(X) 			(((X) > 0)		? (X)  : -(X))
#define		MGMAX(X1, X2) 		(((X1) > (X2))	? (X1) : (X2))
#define		MGMIN(X1, X2) 		(((X1) < (X2))	? (X1) : (X2))
#define		MGSIGN(X) 			(((X) > 0)		?  1   : -1)
#define		MGLEFT(X)			((X) > 0)
#define		MGRIGHT(X)			((X) < 0)
#define		MGDEGREE(X) 		((X) * MC_RTD)					//	* 180.0f / MC_PIE
#define		MGRADIAN(X) 		((X) * MC_DTR)					//	* MC_PIE / 180.0f

template<class T>
inline T MAX( T& t1, T& t2)
{
	return (((t1) > (t2)) ? (t1) : (t2));
}

//===========================================================================
//
//	�T�C�Y��`
//
//#define		MSZ_INT				sizeof( MINT)
//#define		MSZ_REAL			sizeof( MREAL)
//#define		MSZ_CHAR			sizeof( MCHAR)
//#define		MSZ_POINT2			sizeof( MPOINT2)
//#define		MSZ_POINT3			sizeof( MPOINT3)
//#define		MSZ_LINE2			sizeof( MLINE2)
//#define		MSZ_LINE3			sizeof( MLINE3)

////
////	MGCHECK_ZEROVECTOR( �[���`�F�b�N�̃x�N�g����, "�v���O������");
//#define		MGCHECK_ZEROVECTOR(X,Z)\
//								{if (X < MGPTOL->DN)  msSysError( Z, MC_ERR_VECT_ZERO);}
////
////	MGCHECK__DM_MEM( �A���P�[�V�����`�F�b�N�̃������A�h���X�ݒ�|�C���^, �G���[�\���p�v���O������);
//#define		MBCHECK_POINTER(P)	{if (P == NULL)  msSysError( MBCstr( __FILE__ + __LINE__), MC_ERR_POINTER);}

//
//	�萔�Ŏw�肵���T�C�Y�̓_�f�[�^�z��������p�`���쐬����
//
//	MGPOLYG( ���p�`��, �z��T�C�Y(�萔)); 
//
//	��	MGPOLYG( dd, MX_PNT1);
//			��
//		MgPoint2D	MPB_dd[MX_PNT1];
//		MgPolyg2D	dd;
//		dd.sz = MX_PNT1;
//		dd.p = MPB_dd;
//
#define		MGPOLYG2( P, M)	MgPoint2D MPB_ ## P[M]; MgPolyg2D P; P.m_isz = M; P.m_p = MPB_ ## P;
//
//	�萔�Ŏw�肵���T�C�Y�̓_�f�[�^�z��������p�`���쐬����
//
//	MGPOLYG3( ���p�`��, �z��T�C�Y(�萔)); 
//
//	��	MGPOLYG3( dd, MX_PNT1);
//			��
//		MgPoint3D	MPB_dd[MX_PNT1];
//		MgPolyg3D	dd;
//		dd.sz = MX_PNT1;
//		dd.p = MPB_dd;
//
#define		MGPOLYG3( P, M)	MgPoint3D MPB_ ## P[M]; MgPolyg3D P; P.m_isz = M; P.m_P = MPB_ ## P;
//
//	�萔�Ŏw�肵���T�C�Y�̓_�f�[�^�z��������p�`�̔z��������p�`�Q���쐬����
//
//	MGGPOLYG2( ���p�`��, �_�z��T�C�Y�P(�萔),  �_�z��T�C�Y�Q(�萔),  �_�z��T�C�Y�R(�萔)); 
//
//	��	MGGPOLYG2( dd, MX_PNT1, 20, 10);
//			��
//		MgPolyg2D	MPGB_dd[3];
//		MgPoint2D	MPB1_dd[MX_PNT1];
//		MgPoint2D	MPB2_dd[20];
//		MgPoint2D	MPB3_dd[10];
//		MgGPolyg2D	dd;
//		dd.sz = 3;
//		dd.pg = MPGB_dd;
//		dd.pg[0].sz = MX_PNT1;
//		dd.pg[0].p = MPB1_dd;
//		dd.pg[1].sz = 20;
//		dd.pg[1].p = MPB2_dd;
//		dd.pg[2].sz = 10;
//		dd.pg[2].p = MPB3_dd;
//
#define		MGGPOLYG2( P, M1, M2, M3)\
								MgPolyg2D MPGB_ ## P[3]; MgPoint2D MPB1_ ## P[M1];\
								MgPoint2D MPB2_ ## P[M2]; MgPoint2D MPB3_ ## P[M3];\
								MgGPolyg2D P; P.m_isz = 3; P.m_pg = MPGB_ ## P;\
								P.m_pg[0].m_isz = M1; P.m_pg[0].m_p = MPB1_ ## P;\
								P.m_pg[1].m_isz = M2; P.m_pg[1].m_p = MPB2_ ## P;\
								P.m_pg[2].m_isz = M3; P.m_pg[2].m_p = MPB3_ ## P;
//
//	MBMALCPOLYG( �����Q��, �m�ۗv���T�C�Y(�ϐ�), �����z��T�C�Y(�萔)); 
//
//	��	MBMALCPOLYG( dd, GPt2->n, MX_PNT1);
//			��
//		MgPoint2D	MPB_dd[MX_PNT1];
//		MgPolyg2D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.p = (MgPoint2D *)new char[sizeof( MgPoint2D) * GPt2->n];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.p = MLB_dd;
//		}
//
#define		MBMALCPOLYG2( P, S, M)\
								 MgPoint2D MLB_ ## P[M]; MgPolyg2D P;\
								 if (S > M) {P.m_isz = S; P.m_p = (MgPoint2D *)new char[S * sizeof(MgPoint2D)]; MBCHECK_POINTER( P.m_p);}\
								 else {P.sz = M; P.m_p = MLB_ ## P;}
//
//	MBMALCPOLYG3( �����Q��, �m�ۗv���T�C�Y(�ϐ�), �����z��T�C�Y(�萔)); 
//
//	��	MBMALCPOLYG3( dd, GPt2->n, MX_PNT1);
//			��
//		MgPoint3D	MPB_dd[MX_PNT1];
//		MgPolyg3D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.p = (MgPoint3D *)new char[GPt2->n * sizeof( MgPoint3D)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.p = MLB_dd;
//		}
//
#define		MBMALCPOLYG3( P, S, M)\
								MgPoint3D MLB_ ## P[M]; MgPolyg3D P;\
								if (S > M) {P.m_isz = S; P.m_p = (MgPoint3D *)new char[S * sizeof(MgPoint3D)]; MBCHECK_POINTER( P.m_p);}\
								else {P.m_isz = M; P.m_p = MLB_ ## P;}
//
//	�萔�Ŏw�肵���T�C�Y�̓_�f�[�^�z��������p�`�̔z��������p�`�Q���쐬����
//
//	MGPOLYG( ���p�`��, �_�z��T�C�Y�P(�萔),  �_�z��T�C�Y�Q(�萔),  �_�z��T�C�Y�R(�萔)); 
//
//	��	MGGPOLYG3( dd, MX_PNT1, 20, 10);
//			��
//		MgPolyg3D	MPGB_dd[3];
//		MgPoint3D	MPB1_dd[MX_PNT1];
//		MgPoint3D	MPB2_dd[20];
//		MgPoint3D	MPB3_dd[10];
//		MgGPolyg3D	dd;
//		dd.sz = 3;
//		dd.pg = MPGB_dd;
//		dd.pg[0].sz = MX_PNT1;
//		dd.pg[0].p = MPB1_dd;
//		dd.pg[1].sz = 20;
//		dd.pg[1].p = MPB2_dd;
//		dd.pg[2].sz = 10;
//		dd.pg[2].p = MPB3_dd;
//
#define		MGGPOLYG3( P, M1, M2, M3)\
								MgPolyg3D MPGB_ ## P[3]; MgPoint3D MPB1_ ## P[M1];\
								MgPoint3D MPB2_ ## P[M2]; MgPoint3D MPB3_ ## P[M3];\
								MgGPolyg2D P; P.m_isz = 3; P.m_pg = MPGB_ ## P;\
								P.m_pg[0].m_isz = M1; P.m_pg[0].p = MPB1_ ## P;\
								P.m_pg[1].m_isz = M2; P.m_pg[1].p = MPB2_ ## P;\
								P.m_pg[2].m_isz = M3; P.m_pg[2].p = MPB3_ ## P;
//
//	�萔�Ŏw�肵���T�C�Y�̐����f�[�^�z����������Q���쐬����
//
//	MGGLINE( �����Q��, �z��T�C�Y(�萔)); 
//
//	��	MGGLINE2( dd, MX_PNT1);
//			��
//		MgLine2D		MLB_dd[MX_PNT1];
//		MgGLine2D		dd;
//		dd.sz = MX_PNT1;
//		dd.ln = MLB_dd;
//
#define		MGGLINE2( P, M)	MgLine2D MLB_ ## P[M]; MgGLine2D P; P.m_isz = M; P.m_ln = MLB_ ## P;
//
//
//	�萔�Ŏw�肵���T�C�Y�̐����f�[�^�z����������Q���쐬����
//
//	MgGLine3D( �����Q��, �z��T�C�Y(�萔)); 
//
//	��	MgGLine3D( dd, MX_PNT1);
//			��
//		MgLine3D		MLB_dd[MX_PNT1];
//		MgGLine3D	dd;
//		dd.sz = MX_PNT1;
//		dd.ln = MLB_dd;
//
#define		MGGLINE3( P, M)	MgLine3D MLB_ ## P[M]; MgGLine3D P; P.m_isz = M; P.m_ln = MLB_ ## P;
//
//	�萔�Ŏw�肵���T�C�Y�̐����f�[�^�z�������Q���쐬����
//		�����ɒ萔�Ŏw�肵���T�C�Y�̔z����`���Ă��邪�ϐ��Ŏw�肵���T�C�Y�̕����傫���ꍇ��malloc�ō쐬����B
//		malloc�Ŋm�ۂ��ꂽ�̈��Prog�̃��^�[�����Ɏ����I�ɍ폜�����
//
//	MBMALCGLINE2( �����Q��, �m�ۗv���T�C�Y(�ϐ�), �����z��T�C�Y(�萔)); 
//
//	��	MBMALCGLINE2( dd, GPt2->n, MX_PNT1);
//			��
//		MgLine2D		MLB_dd[MX_PNT1];
//		MgGLine2D		dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.ln = (MgLine2D *)new char[GPt2->n * sizeof( MgLine2D)];
//					MBCHECK_POINTER( dd.ln);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.ln = MLB_dd;
//		}
//
#define		MBMALCGLINE2( P, S, M)\
								 MgLine2D MLB_ ## P[M]; MgGLine2D P;\
								 if (S > M) {P.m_isz = S; P.m_ln = (MgLine2D *)new char[S * sizeof(MgLine2D)]; MBCHECK_POINTER( P.m_ln);}\
								 else {P.m_isz = M; P.m_ln = MLB_ ## P;}
//
//	�萔�Ŏw�肵���T�C�Y�̐����f�[�^�z�������Q���쐬����
//		�����ɒ萔�Ŏw�肵���T�C�Y�̔z����`���Ă��邪�ϐ��Ŏw�肵���T�C�Y�̕����傫���ꍇ��malloc�ō쐬����B
//		malloc�Ŋm�ۂ��ꂽ�̈��Prog�̃��^�[�����Ɏ����I�ɍ폜�����
//
//	MBMALCGLINE3( �����Q��, �m�ۗv���T�C�Y(�ϐ�), �����z��T�C�Y(�萔)); 
//
//	��	MBMALCGLINE3( dd, GPt2->n, MX_PNT1);
//			��
//		MgLine3D		MLB_dd[MX_PNT1];
//		MgGLine3D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.ln = (MgLine3D *)new char[GPt2->n * sizeof( MgLine3D)];
//					MBCHECK_POINTER( dd.ln);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.ln = MLB_dd;
//		}
//
#define		MBMALCGLINE3( P, S, M)\
								 MgLine3D MLB_ ## P[M]; MgGLine3D P;\
								 if (S > M) {P.m_isz = S; P.m_ln = (MgLine3D *)new char[S * sizeof(MgLine3D)]; MBCHECK_POINTER( P.m_ln);}\
								 else {P.m_isz = M; P.m_ln = MLB_ ## P;}
//
//
//	�萔�Ŏw�肵���T�C�Y�̐����f�[�^�z����������Q���쐬����
//
//	MGGINT( �����Q��, �z��T�C�Y(�萔)); 
//
//	��	MGGINT( dd, MX_INT1);
//			��
//		MINT		MIB_dd[MX_INT1];
//		MgGInt		dd;
//		dd.sz = MX_INT1;
//		dd.i = MIB_dd;
//
#define		MGGINT( P, M)	MINT MIB_ ## P[M]; MgGInt P; P.m_isz = M; P.m_i = MIB_ ## P;
//
//	�萔�Ŏw�肵���T�C�Y�̎����f�[�^�z����������Q���쐬����
//
//	MGGFLOAT( �����Q��, �z��T�C�Y(�萔)); 
//
//	��	MGGFLOAT( dd, MX_FLT1);
//			��
//		MREAL		MFB_dd[MX_FLT1];
//		MgGReal	dd;
//		dd.sz = MX_FLT1;
//		dd.r = MFB_dd;
//
#define		MGGFLOAT( P, M)	MREAL MFB_ ## P[M]; MgGReal P; P.m_isz = M; P.m_r = MFB_ ## P;
//
//	�萔�Ŏw�肵���T�C�Y�̐����f�[�^�z����������Q���쐬����
//		�����ɒ萔�Ŏw�肵���T�C�Y�̔z����`���Ă��邪�ϐ��Ŏw�肵���T�C�Y�̕����傫���ꍇ��malloc�ō쐬����B
//		malloc�Ŋm�ۂ��ꂽ�̈��Prog�̃��^�[�����Ɏ����I�ɍ폜�����
//
//	MBMALCGINT( �����Q��, �m�ۗv���T�C�Y(�ϐ�), �����z��T�C�Y(�萔)); 
//
//	��	MBMALCGINT( dd, GInt->n, MX_INT1);
//			��
//		MINT		MIB_dd[MX_INT1];
//		MgGInt		dd;
//		if (GInt->n > MX_INT1) {
//			dd.sz = GInt->n;
//			dd.i = (MINT *)new char[GInt->n * sizeof( MINT)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_INT1;
//			dd.i = MIB_dd;
//		}
//
#define		MBMALCGINT( P, S, M)\
								 MINT MIB_ ## P[M]; MgGInt P;\
								 if (S > M) {P.sz = S; P.m_i = (MgPoint2D *)new char[S * sizeof(MgPoint2D)]; MBCHECK_POINTER( P.m_i);}\
								 else {P.m_isz = M; P.m_i = MIB_ ## P;}
//
//
//	�萔�Ŏw�肵���T�C�Y�̎����f�[�^�z����������Q���쐬����
//		�����ɒ萔�Ŏw�肵���T�C�Y�̔z����`���Ă��邪�ϐ��Ŏw�肵���T�C�Y�̕����傫���ꍇ��malloc�ō쐬����B
//		malloc�Ŋm�ۂ��ꂽ�̈��Prog�̃��^�[�����Ɏ����I�ɍ폜�����
//
//	MBMALCGFLOAT( �����Q��, �m�ۗv���T�C�Y(�ϐ�), �����z��T�C�Y(�萔)); 
//
//	��	MBMALCGFLOAT( dd, GFlt->n, MX_FLT1);
//			��
//		MREAL		MFB_dd[MX_FLT1];
//		MgGReal	dd;
//		if (GFlt->n > MX_FLT1) {
//			dd.sz = GFlt->n;
//			dd.p = (MgPoint3D *)new char[GPt2->n * sizeof( MgPoint3D)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_FLT1;
//			dd.p = MFB_dd;
//		}
//
#define		MBMALCGFLOAT( P, S, M)\
								 MREAL MFB_ ## P[M]; MgGReal P;\
								 if (S > M) {P.m_isz = S; P.m_r = (MREAL* )new char[S * sizeof(MREAL)]; MBCHECK_POINTER( P.m_r);}\
								 else {P.m_isz = M; P.m_r = MLB_ ## P;}
//
//
//
//	�萔�Ŏw�肵���T�C�Y�̓_�f�[�^�z������_�Q���쐬����
//
//	MGGPOINT2( �_�Q��, �z��T�C�Y(�萔)); 
//
//	��	MGGPOINT2( dd, MX_PNT1);
//			��
//		MgPoint2D	MPB_dd[MX_PNT1];
//		MgGPoint2D	dd;
//		dd.sz = MX_PNT1;
//		dd.p = MPB_dd;
//
#define		MGGPOINT2( P, M)	MgPoint2D MPB_ ## P[M]; MgGPoint2D P; P.m_isz = M; P.m_p = MPB_ ## P;
//
//	�萔�Ŏw�肵���T�C�Y�̓_�f�[�^�z������_�Q���쐬����
//
//	MgGPoint3D( �_�Q��, �z��T�C�Y(�萔)); 
//
//	��	MgGPoint3D( dd, MX_PNT1);
//			��
//		MgPoint3D	MPB_dd[MX_PNT1];
//		MgGPoint3D	dd;
//		dd.sz = MX_PNT1;
//		dd.p = MPB_dd;
//
#define		MGGPOINT3( P, M)	MgPoint3D MPB_ ## P[M]; MgGPoint3D P; P.m_isz = M; P.m_p = MPB_ ## P;
//
//	�萔�Ŏw�肵���T�C�Y�̓_�f�[�^�z������_�Q���쐬����
//		�����ɒ萔�Ŏw�肵���T�C�Y�̔z����`���Ă��邪�ϐ��Ŏw�肵���T�C�Y�̕����傫���ꍇ��malloc�ō쐬����B
//		malloc�Ŋm�ۂ��ꂽ�̈��Prog�̃��^�[�����Ɏ����I�ɍ폜�����
//
//	MBMALCGPOINT2( �����Q��, �m�ۗv���T�C�Y(�ϐ�), �����z��T�C�Y(�萔)); 
//
//	��	MBMALCGPOINT2( dd, GPt2->n, MX_PNT1);
//			��
//		MgPoint2D	MPB_dd[MX_PNT1];
//		MgGPoint2D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.p = (MgPoint2D *)new char[GPt2->n * sizeof( MgPoint2D)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.p = MPB_dd;
//		}
//
#define		MBMALCGPOINT2( P, S, M)\
								 MgPoint2D MLB_ ## P[M]; MgGPoint2D P;\
								 if (S > M) {P.m_isz = S; P.m_p = (MgPoint2D *)new char[S * sizeof(MgPoint2D)]; MBCHECK_POINTER( P.m_p);}\
								 else {P.m_isz = M; P.m_p = MLB_ ## P;}
//
//
//	�萔�Ŏw�肵���T�C�Y�̓_�f�[�^�z������_�Q���쐬����
//		�����ɒ萔�Ŏw�肵���T�C�Y�̔z����`���Ă��邪�ϐ��Ŏw�肵���T�C�Y�̕����傫���ꍇ��malloc�ō쐬����B
//		malloc�Ŋm�ۂ��ꂽ�̈��Prog�̃��^�[�����Ɏ����I�ɍ폜�����
//
//	MBMALCGPOINT3( �����Q��, �m�ۗv���T�C�Y(�ϐ�), �����z��T�C�Y(�萔)); 
//
//	��	MBMALCGPOINT3( dd, GPt2->n, MX_PNT1);
//			��
//		MgPoint3D	MPB_dd[MX_PNT1];
//		MgGPoint3D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.p = (MgPoint3D *)new char[GPt2->n * sizeof( MgPoint3D)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.p = MPB_dd;
//		}
//
#define		MBMALCGPOINT3( P, S, M)\
								 MgPoint3D MLB_ ## P[M]; MgGPoint3D P;\
								 if (S > M) {P.m_isz = S; P.m_p = (MgPoint3D *)new char[S * sizeof(MgPoint3D)]; MBCHECK_POINTER( P.m_p);}\
								 else {P.m_isz = M; P.m_p = MLB_ ## P;}

/////////////////////////////////////////////////////////////////////////////
//	�}�`�f�[�^�^�C�v
#define		MGTP_POINT			1								// �_
#define		MGTP_LINE			2								// ����
#define		MGTP_ILINE			3								// ����
#define		MGTP_POLYLN			4								// �܂��
#define		MGTP_CIR			5								// �~
#define		MGTP_ARC			6								// �~��
#define		MGTP_POLYGN			7								// ���p�`(��)
#define		MGTP_TXT			8								// ������
#define		MGTP_MSH			9								// ү��
#define		MGTP_GINT			10								// �����Q
#define		MGTP_GREAL			11								// �����Q
#define		MGTP_GPOINT2		22								// �Q�����_�Q
#define		MGTP_GPOINT3		23								// �R�����_�Q
#define		MGTP_GLINE			32								// �Q���������Q
#define		MGTP_GLINE3			33								// �R���������Q
#define		MGTP_POLYG			42								// �Q�������p�`
#define		MGTP_POLYG3			43								// �R�������p�`
#define		MGTP_GPOLYG			52								// �Q�������p�`�Q
#define		MGTP_GPOLYG3		53								// �R�������p�`�Q
