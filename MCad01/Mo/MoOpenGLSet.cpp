//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdDsipModel.cpp
//
//		�ƃ��f���̃f�B�X�v���C���X�g�쐬
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MgLib.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "MoOpengl.h"
#include "MoMaterial.h"

#define	DLL_EXPORT_DISPLIST_DO
#include "MoDispList.h"

#define		MP_PANEL_LINE			1
#define		MP_PANEL_RECTANGULAR	2

#pragma warning( disable : 4305 )

namespace MC
{

void Cube( GLfloat lenght);

// �}�e���A���R�[�h

enum MPMATERIAL1 {
	MTR_JITTAI = 0,
	MTR_TOUMEI
};

enum MPMATERIAL2 {
	MTR_YANE = 0,								// �\������
	MTR_YAGIRI,									// �����A�ǁ@������
	MTR_KABE,									// ��؁A�ǁ@����
	MTR_BUZAI,									// �����@����
	MTR_KISO,									// ��b�@����
	MTR_PANEL									// �p�l���@����
};

static	MINT	z_iMaterialC1;					// �J�����g�̃}�e���A�� GL_FRONT
static	MATERIAL_LIST	z_Material[8];			// { 0:�����A1:��؁A2:�ǁA3:���ށA4:��b�A5:�p�l��_�����A6:�p�l��_�g�A7:�ǁE����������}
static	MINT	z_iMtrNo[2][7] = { { 0, 1, 2, 3, 4, 5, 6}, { 7, 7, 7, 7, 7, 7}};
												// ���ޕ\�������ԍ�
												//		{ 0:���́A1:������}�A
												//		{ 0:�����A1:��؁A2:�ǁA3:���ށA4:��b�A5:�p�l��_�����A6:�p�l��_�g}
static	LIGHT_MODEL		z_Lmodel;
static	LIGHT			z_Light[5];
void	MsSetLight_MaterialParameter1( void);

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�����A���̃p�����[�^�̐ݒ� 1
void DispList::MsGlInitialize( void)
{
	// Initialize
	// 3D�V�[���̔w�i��Z���O���[�ɂ���B
	// (Color �o�b�t�@���N���A����Ƃ��ɂ͔Z���O���[�ɐݒ肷�邱�Ƃ̎w��)
	glClearColor( 0.2f, 0.2f, 0.2f, 0.0f);

	// Depth �o�b�t�@�̎w�� (�����l��1.0�ł���ȗ��\)
	glClearDepth( 1.0f);

	// ��̂Q���߂�::glClear(GL_COLOR_BUFFER_BIT | BL_DEPTH_BUFFER_BIT)�ɂėL���ƂȂ邪
	// glClear�͉�ʂ̏��������̂��тɎ��s��v����̂�OnPaint�Ŏ��s����

//	glDepthFunc(GL_LEQUAL);
	// Depth �o�b�t�@��L����
	glEnable( GL_DEPTH_TEST);

//�y�@�\�z�����A���̃p�����[�^�̐ݒ� 1
	MsSetLight_MaterialParameter1();
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�r���[�|�[�g�T�C�Y�̕ύX
void DispList::MsOnSize(UINT nType, int cx, int cy)
{

	if( 0>= cx || 0>=cy) return;

	glViewport( 0, 0, cx, cy );
//
	glMatrixMode( GL_PROJECTION );								// <PROJECTION MATRIX SETUP>
	glLoadIdentity();											// Reset Projection matrix
/*
	if ( cx <= cy)
		glOrtho(  -2., 2., -2.*(GLfloat)(cy/cx),				// ���ˉe
				  2.*(GLfloat)(cy/cx), -10.,10.);
	else
		glOrtho( -2.*(GLfloat)(cy/cx),							// ���ˉe
				 2.*(GLfloat)(cy/cx),  -2., 2., -10.,10.);
*/
//	glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 7.0);					// �����@�ˉe�@���̐� �c�����W�A�c����iaspect�j�A�O��(front)�ƌ��(back)�̈ʒu��
	gluPerspective( 50.0f, (GLfloat)(cx/cy), 0.5f, 25.0f );		// �����@�ˉe�@���̐� ���p�x�A�c����iaspect�j�A�O��(front)�ƌ��(back)�̈ʒu

	glMatrixMode( GL_MODELVIEW );								// <MODEL VIEW MATRIX SETUP>
	glLoadIdentity();											// Reset Model view matrix
	
//DD	glTranslatef (0.0f, 0.0f, -5.0f);						// ���̐ς̒��ɓ���悤�ړ�����
	glTranslated (0.0f, 0.0f, -5.0f);							// ���̐ς̒��ɓ���悤�ړ�����
	
	DispList::SetLightModel1();									// �����̃p�����[�^�̐ݒ�1
	DispList::SetLight();										// �����̐ݒ�1
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�����A���̃p�����[�^�̐ݒ� 1
void DispList::MsSetLight_MaterialParameter1( void)
{
	// LIGHT MODEL
	GLSet4f( z_Lmodel.ambient, 0.2, 0.2, 0.2, 1.0);
	z_Lmodel.local_view = 0.0;
	z_Lmodel.two_size   = 0.0;

	// ���� LIGHT AMBIENT
	// ���̕\�ʏ�ɋψ�Ȍ��𓖂āA���̖̂��Â�e�͏o���Ȃ��D�܂�̓��̌��Ɠ��l�D 

	// �g�U�� LIGHT DIFFUSE
	// ���͕��̕\�ʂőS�����ɓ������g�U����D�����̈ʒu�Ɩ@���x�N�g�������Ŗ��Â͌���D

	// ���ʌ�(�n�C���C�g) LIGHT SPECULAR
	// ��������ɂ݂̂ɗ����˂��邽�߁C�����̈ʒu�C�@���x�N�g���C�����Ď��_�̈ʒu�Ɉˑ����Čv�Z�D

	// �����̈ʒu�C���� LIGHT POSITION
	// �����̈ʒu��3������Ԃň�ӂɎw��D���̂��ߋ����̌����́C�ʒu�����̂̏ƌ��ɋy�ڂ��e����D
	// �܂��C���z�̂悤�ɋɂ߂ĉ��������́A���������s�ɂȂ邽�߁C�����̕������d�v�D
	// �ʒu���d�v�ȈӖ�����������positional�Ȍ����C�������d�v�Ȍ�����directional�Ȍ����Ƃ����D 

	// �X�|�b�g���C�g LIGHT SPOTLIGHT
	// �X�|�b�g���C�g�Ƃ́C��������˂���͈͂��~���̂悤�Ȍ`��ɂȂ���̂ł���D
	// �X�|�b�g�̑傫�����p�x�Ŏw��D�Ȃ��X�|�b�g���C�g���g�p����ꍇ�́C
	// �~���̎��������w�肵�āC�����̌������w�肷��D

	// �����̌��� LIGHT ATTENUATION
	// �����̌��͌������牓������ƌ��ʂ��������܂��D�����W���ɂ���Č����ʂ��w�肵�܂��D
	// �������Cdirectional�Ȍ����͖������ɑ��݂���̂ŁC�����W���̎w��͈Ӗ����Ȃ��܂���D 

	GLSet4f(	z_Light[0].ambient,		0.0,  0.0,  0.0,  1.0);	// ����
	GLSet4f(	z_Light[0].diffuse,		0.3,  0.3,  1.3,  1.0);	// �g�U��
	GLSet4f(	z_Light[0].specular,	0.1,  0.1,  0.1,  1.0);	// ���ʌ�(�n�C���C�g)
	GLSet4f(	z_Light[0].position,	0.0,  0.0,  1.0,  0.0);	// �����̈ʒu�C����
	GLSet3f(	z_Light[0].spot_direction,   0.0,  0.0, -1.0);	// �X�|�b�g���C�g

	z_Light[0].spot_exponet	= 0.0;
	z_Light[0].spot_cutoff	= 180.0;
	z_Light[0].KC = 1.0;										// �����̌���
	z_Light[0].KL = 0.0;
	z_Light[0].KQ = 0.0;

	// ��
	GLSet4f(	z_Light[1].ambient,		0.0,  0.0,  0.0,  1.0);	// ����
	GLSet4f(	z_Light[1].diffuse,		0.5,  0.2,  0.2,  1.0);	// �g�U��
	GLSet4f(	z_Light[1].specular,	0.2,  0.1,  0.1,  1.0);	// ���ʌ�(�n�C���C�g)
	GLSet4f(	z_Light[1].position,	2.0,  1.0, -0.5,  1.0);	// �����̈ʒu�C����

	GLSet4f(	z_Light[2].ambient,		0.0,  0.0,  0.0,  1.0);	// ����
	GLSet4f(	z_Light[2].diffuse,		0.3,  0.3,  0.3,  1.0);	// �g�U��
	GLSet4f(	z_Light[2].specular,	0.2,  0.1,  0.1,  1.0);	// ���ʌ�(�n�C���C�g)
	GLSet4f(	z_Light[2].position,	2.0,  1.0, -1.0,  1.0);	// �����̈ʒu�C����

	// ��
	GLSet4f(	z_Light[3].ambient,		0.0,  0.0,  0.0,  1.0);	// ����
	GLSet4f(	z_Light[3].diffuse,		0.3,  0.3,  0.6,  1.0);	// �g�U��
	GLSet4f(	z_Light[3].specular,	0.05, 0.05, 0.1,  1.0);	// ���ʌ�(�n�C���C�g)
	GLSet4f(	z_Light[3].position,   -0.5, -1.5, -1.0,  1.0);	// �����̈ʒu�C����

	GLSet4f(	z_Light[4].ambient,		0.0,  0.0,  0.0,  1.0);	// ����
	GLSet4f(	z_Light[4].diffuse,		0.2,  0.3,  0.3,  1.0);	// �g�U��
	GLSet4f(	z_Light[4].specular,	0.0,  0.1,  0.1,  1.0);	// ���ʌ�(�n�C���C�g)
	GLSet4f(	z_Light[4].position,	2.0,  0.5,  0.5,  0.0);	// �����̈ʒu�C����

	// �����̊g�U�F MATERIAL AMBIENT
	// �����ɑ΂��Ă��̕��̂��ǂ�ȐF�������g�U���邩��\���D
	// �Ⴆ�ΐԐF���w�肷��ƁC	���Ƃ����F�����ł����̂͑S�̓I�ɐԐF��тт�D

	// �g�U���̊g�U�F MATERIAL DIFFUSE
	// �g�U���ɑ΂��Ă��̕��̂��ǂ�ȐF�������g�U���邩��\���D
	// �Ⴆ�Η΂��w�肷��ƁC���Ƃ����F�����ł����̖̂��Â͗΂̃O���f�[�V�����ŕ\�������D

	// ���ʌ��̔��ːF MATERIAL SPECULAR
	// ���ʌ��ɑ΂��Ă��̕��̂��ǂ�ȐF�������g�U���邩��\���D
	// �Ⴆ�ΐF���w�肷��ƁC���Ƃ����F�����ł����̂͐F�̃n�C���C�g���o���D

	// ���� MATERIAL SHININESS
	// ���ʌ��ł͕��̂Ƀn�C���C�g���o�邪�C���̂̎����ɂ���Ă̓n�C���C�g���������Ȃ�����
	// �傫���Ȃ����肵�܂��D���򂪍����قǁC�n�C���C�g�����������邢���(�œ_�������Ă���)�ɂȂ�D
	// ���̌���x�����̑����L�̃p�����[�^�ł���D

	// ���ːF MATERIAL EMISSION
	// ���̂����甭���Ă���F�ł���D���̐F�����͌����ɂ͖��֌W�ɂȂ邽�߁C�����̂���󋵉���
	// �����̉e�����󂯂Ȃ�����(�V�[�����̃����v��)�Ɏg��ꂽ�肵�܂��D

	// ����	����
	GLSet4f(	z_Material[0].ambient,	0.12, 0.23, 0.23, 1.0);	// �����̊g�U�F
	GLSet4f(	z_Material[0].diffuse,	0.12, 0.23, 0.23, 1.0);	// �g�U���̊g�U�F
	GLSet4f(	z_Material[0].specular,	0.12, 0.23, 0.23, 1.0);	// ���ʌ��̔��ːF
	z_Material[0].shininess[0] = 10.0;							// ����
	GLSet4f(	z_Material[0].emission,	0.12, 0.23, 0.34, 1.0);	// ���ːF
	
	// ���	����
	GLSet4f(	z_Material[1].ambient,	0.45, 0.5, 0.35, 1.0);	// �����̊g�U�F
	GLSet4f(	z_Material[1].diffuse,	0.56, 0.6, 0.35, 1.0);	// �g�U���̊g�U�F
	GLSet4f(	z_Material[1].specular,	0.45, 0.5, 0.35, 1.0);	// ���ʌ��̔��ːF
	z_Material[1].shininess[0] = 10.0;							// ����
	GLSet4f(	z_Material[1].emission,	0.6, 0.5, 0.4, 1.0);	// ���ːF

	// ��	����
	memcpy( &z_Material[2], &z_Material[1], sizeof( MATERIAL_LIST));

	// ����
	GLSet4f(	z_Material[3].ambient,	0.6, 0.6, 0.2, 1.0);	// �����̊g�U�F
	GLSet4f(	z_Material[3].diffuse,	0.8, 0.8, 0.2, 1.0);	// �g�U���̊g�U�F
	GLSet4f(	z_Material[3].specular,	0.5, 0.5, 0.2, 1.0);	// ���ʌ��̔��ːF
	z_Material[3].shininess[0] = 0.0;							// ����
	GLSet4f(	z_Material[3].emission,	0.2, 0.2, 0.1, 1.0);	// ���ːF

	// ��b	����
	GLSet4f(	z_Material[4].ambient,	0.40, 0.45, 0.38, 1.0);	// �����̊g�U�F
	GLSet4f(	z_Material[4].diffuse,	0.45, 0.45, 0.37, 1.0);	// �g�U���̊g�U�F
	GLSet4f(	z_Material[4].specular,	0.1, 0.1, 0.1, 1.0);	// ���ʌ��̔��ːF
	z_Material[4].shininess[0] = 10.0;							// ����
	GLSet4f(	z_Material[4].emission,	0.43, 0.43, 0.37, 1.0);	// ���ːF
	
	// �p�l�� ����
	GLSet4f(	z_Material[5].ambient,	0.90, 0.25, 0.18, 1.0);	// �����̊g�U�F
	GLSet4f(	z_Material[5].diffuse,	0.95, 0.25, 0.17, 1.0);	// �g�U���̊g�U�F
	GLSet4f(	z_Material[5].specular,	0.1, 0.1, 0.1, 1.0);	// ���ʌ��̔��ːF
	z_Material[5].shininess[0] = 10.0;							// ����
	GLSet4f(	z_Material[5].emission,	0.93, 0.23, 0.17, 1.0);	// ���ːF

	// �p�l�� �g
	memcpy( &z_Material[6], &z_Material[1], sizeof( MATERIAL_LIST));

	// �ǁA����	������
	GLSet4f(	z_Material[7].ambient,	0.1, 0.1, 0.1, 1.0);	// �����̊g�U�F
	GLSet4f(	z_Material[7].diffuse,	0.2, 0.2, 0.2, 1.0);	// �g�U���̊g�U�F
	GLSet4f(	z_Material[7].specular,	0.1, 0.2, 0.1, 1.0);	// ���ʌ��̔��ːF
	z_Material[7].shininess[0] = 100.0;							// ����
}

void DispList::SetLightModel1( void)
{
	// LIGHT MODEL
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, z_Lmodel.ambient);
	glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, z_Lmodel.local_view);
	glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, z_Lmodel.two_size);
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�����̐ݒ�
//
void DispList::SetLight( void)
{
	// LIGHT 0
	glEnable( GL_LIGHT0 );
	glLightfv(	GL_LIGHT0, GL_AMBIENT, 				z_Light[0].ambient);
	glLightfv(	GL_LIGHT0, GL_DIFFUSE, 				z_Light[0].diffuse);
	glLightfv(	GL_LIGHT0, GL_SPECULAR, 			z_Light[0].specular);
	glLightfv(	GL_LIGHT0, GL_POSITION, 			z_Light[0].position);

	glLightfv(	GL_LIGHT0, GL_SPOT_DIRECTION, 		z_Light[0].spot_direction);
	glLightf(	GL_LIGHT0, GL_SPOT_EXPONENT, 		z_Light[0].spot_exponet);
	glLightf(	GL_LIGHT0, GL_SPOT_CUTOFF, 			z_Light[0].spot_cutoff);

	glLightf(	GL_LIGHT0, GL_CONSTANT_ATTENUATION, z_Light[0].KC);
	glLightf(	GL_LIGHT0, GL_LINEAR_ATTENUATION, 	z_Light[0].KL);
	glLightf(	GL_LIGHT0, GL_QUADRATIC_ATTENUATION,z_Light[0].KQ);

	// LIGHT 1
	glEnable( GL_LIGHT1 );
	glLightfv(	GL_LIGHT1, GL_AMBIENT,				z_Light[1].ambient);
	glLightfv(	GL_LIGHT1, GL_DIFFUSE,				z_Light[1].diffuse);
	glLightfv(	GL_LIGHT1, GL_SPECULAR,				z_Light[1].specular);
	glLightfv(	GL_LIGHT1, GL_POSITION,				z_Light[1].position);

	// LIGHT 2
	glEnable( GL_LIGHT2 );
	glLightfv(	GL_LIGHT2, GL_AMBIENT,				z_Light[2].ambient);
	glLightfv(	GL_LIGHT2, GL_DIFFUSE,				z_Light[2].diffuse);
	glLightfv(	GL_LIGHT2, GL_SPECULAR,				z_Light[2].specular);
	glLightfv(	GL_LIGHT2, GL_POSITION,				z_Light[2].position);

	// LIGHT 3
	glEnable( GL_LIGHT3 );
	glLightfv(	GL_LIGHT3, GL_AMBIENT,				z_Light[3].ambient);
	glLightfv(	GL_LIGHT3, GL_DIFFUSE,				z_Light[3].diffuse);
	glLightfv(	GL_LIGHT3, GL_SPECULAR,				z_Light[3].specular);
	glLightfv(	GL_LIGHT3, GL_POSITION,				z_Light[3].position);

	// LIGHT 4
	glEnable( GL_LIGHT4 );
	glLightfv(	GL_LIGHT4, GL_AMBIENT,				z_Light[4].ambient);
	glLightfv(	GL_LIGHT4, GL_DIFFUSE,				z_Light[4].diffuse);
	glLightfv(	GL_LIGHT4, GL_SPECULAR,				z_Light[4].specular);
	glLightfv(	GL_LIGHT4, GL_POSITION,				z_Light[4].position);
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z���ޕ\������(Material)��ݒ肷��
//			
void DispList::SetMaterial(
						MINT		i_iT,			// �\���^�C�v
						MINT		i_iB			// ����
				)
{
	MINT	iMtrNo = z_iMtrNo[i_iT][i_iB];
	if ( iMtrNo != z_iMaterialC1) {
		z_iMaterialC1 = iMtrNo;

		// MATERIAL
		glMaterialfv( GL_FRONT, GL_AMBIENT,		z_Material[iMtrNo].ambient);
	    glMaterialfv( GL_FRONT, GL_DIFFUSE,		z_Material[iMtrNo].diffuse);
		glMaterialfv( GL_FRONT, GL_SPECULAR,	z_Material[iMtrNo].specular);
	    glMaterialfv( GL_FRONT, GL_SHININESS,	z_Material[iMtrNo].shininess);
		glMaterialfv( GL_FRONT, GL_EMISSION,	z_Material[iMtrNo].emission);
	}
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�����̂̃f�B�X�v���C���X�g���쐬���� (MakeDisplaylist)
//			
void DispList::DspRectangular( 
						MgPoint3D	PT[2][2][2],	// �����̂̒��_���W		(�_�����W)
				const	MgVect3D	&VuLng,			// �n�_����I�_�����̒P�ʃx�N�g��
				const	MgVect3D	&VuRt,			// �E�����̒P�ʃx�N�g��
				const	MgVect3D	&VuUp			// ������̒P�ʃx�N�g��
				)
{
	glBegin( GL_QUADS);
		glNormal3r( -VuUp.x, -VuUp.y, -VuUp.z);					// �ʂ̖@���x�N�g�� ������
		glVertex3r( PT[1][0][0].x, PT[1][0][0].y, PT[1][0][0].z);
		glVertex3r( PT[0][0][0].x, PT[0][0][0].y, PT[0][0][0].z);
		glVertex3r( PT[0][1][0].x, PT[0][1][0].y, PT[0][1][0].z);
		glVertex3r( PT[1][1][0].x, PT[1][1][0].y, PT[1][1][0].z);
	glEnd();

	glBegin( GL_QUADS);
		glNormal3r( VuUp.x, VuUp.y, VuUp.z);					// �ʂ̖@���x�N�g�� �����
		glVertex3r( PT[0][0][1].x, PT[0][0][1].y, PT[0][0][1].z);
		glVertex3r( PT[1][0][1].x, PT[1][0][1].y, PT[1][0][1].z);
		glVertex3r( PT[1][1][1].x, PT[1][1][1].y, PT[1][1][1].z);
		glVertex3r( PT[0][1][1].x, PT[0][1][1].y, PT[0][1][1].z);
	glEnd();

	glBegin( GL_QUADS);
		glNormal3r( VuLng.x, VuLng.y, VuLng.z);					// �ʂ̖@���x�N�g�� �O����
		glVertex3r( PT[1][0][1].x, PT[1][0][1].y, PT[1][0][1].z);
		glVertex3r( PT[1][0][0].x, PT[1][0][0].y, PT[1][0][0].z);
		glVertex3r( PT[1][1][0].x, PT[1][1][0].y, PT[1][1][0].z);
		glVertex3r( PT[1][1][1].x, PT[1][1][1].y, PT[1][1][1].z);
	glEnd();

	glBegin( GL_QUADS);
		glNormal3r( -VuLng.x, -VuLng.y, -VuLng.z);				// �ʂ̖@���x�N�g�� �����
		glVertex3r( PT[0][0][0].x, PT[0][0][0].y, PT[0][0][0].z);
		glVertex3r( PT[0][0][1].x, PT[0][0][1].y, PT[0][0][1].z);
		glVertex3r( PT[0][1][1].x, PT[0][1][1].y, PT[0][1][1].z);
		glVertex3r( PT[0][1][0].x, PT[0][1][0].y, PT[0][1][0].z);
	glEnd();

	glBegin( GL_QUADS);
		glNormal3r( -VuRt.x, -VuRt.y, -VuRt.z);					// �ʂ̖@���x�N�g�� ������
		glVertex3r( PT[0][1][1].x, PT[0][1][1].y, PT[0][1][1].z);
		glVertex3r( PT[1][1][1].x, PT[1][1][1].y, PT[1][1][1].z);
		glVertex3r( PT[1][1][0].x, PT[1][1][0].y, PT[1][1][0].z);
		glVertex3r( PT[0][1][0].x, PT[0][1][0].y, PT[0][1][0].z);
	glEnd();

	glBegin( GL_QUADS);
		glNormal3r( VuRt.x, VuRt.y, VuRt.z);					// �ʂ̖@���x�N�g�� �E����
		glVertex3r( PT[0][0][0].x, PT[0][0][0].y, PT[0][0][0].z);
		glVertex3r( PT[1][0][0].x, PT[1][0][0].y, PT[1][0][0].z);
		glVertex3r( PT[1][0][1].x, PT[1][0][1].y, PT[1][0][1].z);
		glVertex3r( PT[0][0][1].x, PT[0][0][1].y, PT[0][0][1].z);
	glEnd();
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�R�p�`�̃f�B�X�v���C���X�g���쐬����
//				(���Ԃ𖄂߂�ׂɎ኱�傫�߂ɍ쐬����j�i�v�����j
//			
void DispList::DspTriangles( 
				const	MgPolyg3D	&PGTri,			// �O�p�`		(�_�����W)
				const	MgVect3D	&VuUp			// �R�p�`���ʂ̖@���x�N�g��
				)
{
//#define TRIANGLE_HOSEI 1
#ifdef TRIANGLE_HOSEI
	MgPoint3D	Pc;
	MgPoint3D	Pc0, Pc1, Pc2;

	Pc = (PGTri.p[0] + PGTri.p[1] + PGTri.p[2]) / 3.;
	Pc0 = (PGTri.p[0] - Pc) * 0.0005;
	Pc1 = (PGTri.p[1] - Pc) * 0.0005;
	Pc2 = (PGTri.p[2] - Pc) * 0.0005;
	PGTri.p[0] += Pc0;
	PGTri.p[1] += Pc1;
	PGTri.p[2] += Pc2;
#endif
	glBegin( GL_TRIANGLES);
		glNormal3r( VuUp.x, VuUp.y, VuUp.z);			// �ʂ̖@���x�N�g��
		glVertex3r( PGTri.m_P[0].x, PGTri.m_P[0].y, PGTri.m_P[0].z);
		glVertex3r( PGTri.m_P[1].x, PGTri.m_P[1].y, PGTri.m_P[1].z);
		glVertex3r( PGTri.m_P[2].x, PGTri.m_P[2].y, PGTri.m_P[2].z);
	glEnd();
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�_�̃f�B�X�v���C���X�g���쐬����
//			
void DispList::DrawPoint(
				const	MgPoint3D	&i_Pt,				// �_		(�����W)
				const	MgPoint3D	&i_PtCtr,			// �\���ƃ��f���̒��S
						MREAL		i_rB				// �R�����\���{��
				)
{
	MgPoint3D	Pt;

	Pt = DPtoDSP( i_Pt, 0., i_PtCtr, i_rB);

	glDisable( GL_LIGHTING);
	glColor4f( 1.0, 0.0, 1.0, 1.0);
	glPointSize( 2.0);
	glBegin( GL_POINTS);
		glVertex3rv( (GLfloat *)Pt.v);
	glEnd();
	glEnable( GL_LIGHTING);
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�����̃f�B�X�v���C���X�g���쐬����
//			
void DispList::DrawLine(
				const	MgLine3D	&i_Ln,				// ����		(�����W)
				const	MgPoint3D	&i_PtCtr,			// �\���ƃ��f���̒��S
						MREAL		i_rB				// �R�����\���{��
				)
{
	MgLine3D	Ln;

	Ln = DPtoDSP( i_Ln, 0., i_PtCtr, i_rB);

	glDisable( GL_LIGHTING);
	glColor4f( 1.0, 0.0, 0.0, 1.0);
	glBegin( GL_LINES);
		glVertex3rv( Ln.p[0].v);
		glVertex3rv( Ln.p[1].v);
	glEnd();
	glEnable( GL_LIGHTING);
}


////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�S�p�`�̃f�B�X�v���C���X�g���쐬����
//				(��ӂƏ�ӂ��쐬)
//			
void DispList::DspQuads( 
				const	MgLine3D		&LnLf,			// ��Ӂi�E�Ӂj(�_�����W)
				const	MgLine3D		&LnRt			// ��Ӂi���Ӂj(�_�����W)
				)
{
	MgVect3D		VtLng, VtLf;						// ���ނ̒��������x�N�g���A�������x�N�g��
	MgVect3D		VuLng, VuUp;						// ���ނ̒��������P�ʃx�N�g���A����P�ʃx�N�g��
	
	VtLng = LnLf.p[1] - LnLf.p[0];
	VtLf = LnRt.p[0] - LnLf.p[0];
	VuUp = VtLng ^ VtLf;
	VuUp.SetUnitize( g_gTol.L);									// �_�����W

	glBegin( GL_QUADS);
		glNormal3r( VuUp.x, VuUp.y, VuUp.z);					// �ʂ̖@���x�N�g��
		glVertex3r( LnLf.p[0].x, LnLf.p[0].y, LnLf.p[0].z);
		glVertex3r( LnLf.p[1].x, LnLf.p[1].y, LnLf.p[1].z);
		glVertex3r( LnRt.p[1].x, LnRt.p[1].y, LnRt.p[1].z);
		glVertex3r( LnRt.p[0].x, LnRt.p[0].y, LnRt.p[0].z);
	glEnd();
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z���t�����p�`�̃f�B�X�v���C���X�g���쐬����
//			
void DispList::DrawPolygon(
				const	MgGPolyg3D	&GPgR,			// ���t�����p�`	(�����W)
				const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
						MREAL		rB				// �R�����\���{��
				)
{
	MINT			ist1;
	MINT			ic2;
	MgVect3D			V1, V2;
	MgVect3D			VuRt;
	MGPOLYG3( PgW, 100);
	MgGPolyg3D		GPgW(30);
	MGPOLYG3( zPg3, 3);

	V1 = GPgR.m_Pg[0].m_P[1] - GPgR.m_Pg[0].m_P[0];
	V2 = GPgR.m_Pg[0].m_P[2] - GPgR.m_Pg[0].m_P[0];
	VuRt = V1 ^ V2;
	VuRt.SetUnitize();

	MGeo::ConnectGPgtoPg3( GPgR, VuRt, &PgW);

	GPgR.Print( Mstr( "GPgR"));
	VuRt.Print( Mstr( "VuRt"));
	PgW.Print( Mstr( "PgW"));

	ist1 = MGeo::DivideTriPg3( PgW, VuRt, &GPgW);

	GPgW.Print( Mstr( "GPgW"));

	for ( ic2=0; ic2<GPgW.m_n; ic2++) {
		DPtoDSP3( GPgW.m_Pg[ic2], 0., MgVect3D( 0., 0., 0.), PtCtr, rB, &zPg3);		// �{�֐��̈����̐��͗v����	
		DspTriangles( zPg3, VuRt);
	}
}

} // namespace MC