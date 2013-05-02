//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsDispModel.cpp
//
//		�ƃ��f���̃f�B�X�v���C���X�g�쐬
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#include "MgLib.h"
#include "McSystemProperty.h"

#include "MhInpPlcParts.h"
#define DLL_EXPORT_MDLDISPLIST_DO
#include "MoMdlDispList.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "MoGlLib.h"

#include "MoOpengl.h"
#include "MoDispList.h"

#define		MP_PANEL_LINE			1
#define		MP_PANEL_RECTANGULAR	2

namespace MC
{

void Cube( GLfloat lenght);

static	GLuint	z_DispListFig[4];			// �}�`�f�B�X�v���C���X�g
											//	0: ����		�}�e���A���t��
											//	1: �ǁE���	�}�e���A���Ȃ�
											//	2: ����		�}�e���A���Ȃ�
static	GLuint	z_DispListMat[10];			// �}�e���A���f�B�X�v���C���X�g
											//	0: ����
											//	1: �ǁE���
											//	2: ������

//											//	2: �p�l��
//											//	3: �p�l���g
//											//	4: ����
//											//	5: ��b
//											//	6: ������

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�p�l���̌`������߂�
//			
void Panelfig( 
						mhPlcParts	*i_pPlcEn,		// �p�l��
				const	MgPoint3	&PtCtr,
						MREAL		rB,
						MgPoint3	PT[2][2][2],	// ���_���W
						MgVect3		*VuW,			// �Е���
						MgVect3		*VuF,			// ��O����
						MgVect3		*VuU			// �����
				)
{
	MSTNDH		iCdHgt;								// ���t�������R�[�h
	MINT		iULCd;								// �㉺�t���R�[�h (0:���t��, 1:��t��)
	MREAL		rZ;
	MgLine3		LnPlc;
	MgLine3		LnBz;
	MREAL		rH1, rH2, rTH, rOY;

	MgVect3		VtLng, VtRt, VtUp, VtUph;			// ���ނ̒��������x�N�g���A�E�����x�N�g���A������x�N�g���A�p�l���͂ݏo����
	MgVect3		VuLng, VuRt, VuUp;					// ���ނ̒��������P�ʃx�N�g���A�E�����P�ʃx�N�g���A������P�ʃx�N�g��
	MgVect3		VtTkH;								// ���t������
	MgVect3		VtTH, VtOY;							// ��O���␳�l�A���s��
	MgVect2		vuRt;								// �����p�l���p���s�������Q�����x�N�g��
	MREAL		rlXY;								// �����p�l���p���s�������Q�����x�N�g����XY���ʏ㒷��
	
	iCdHgt = i_pPlcEn->GetPTCdHgt();
	iULCd = i_pPlcEn->GetPTCdToritk();

	rZ = mcs::GetStnd( i_pPlcEn->GetPIKai(), iCdHgt);
	LnPlc = i_pPlcEn->GetPIPlcIti();

	VuLng = LnPlc.Vu();
	if ( MGeo::Zero( VuLng.z))
		VuRt = VuLng.RotR90();
	else {
		MREAL r1_D = 1.f / sqrt( VuLng.x * VuLng.x + VuLng.y * VuLng.y);
//		VuRt.Set( VuLng.y * r1_D, - VuLng.x * r1_D, 0.f);
		VuRt = MgVect3( VuLng.y * r1_D, - VuLng.x * r1_D, 0.f);
	}
	VuUp = i_pPlcEn->GetPIUpPlc();
	VuRt = VuLng ^ VuUp;
	
	VtTkH = i_pPlcEn->GetPIHgt( 0)  * VuUp;											// ���t������
	LnPlc.p[0] = LnPlc.p[0] - i_pPlcEn->GetPILenHosei( 0) * VuLng + VtTkH;
	LnPlc.p[1] = LnPlc.p[1] + i_pPlcEn->GetPILenHosei( 1) * VuLng + VtTkH;

	// �\�����W�n
	LnBz = DPtoDSP( LnPlc, rZ, PtCtr, rB);
	rH1 = i_pPlcEn->GetMbHeight() * rB;
	rH2 = 15.f * rB;
	rTH = i_pPlcEn->GetPIMaeHosei() * rB;						// �p�l����O���␳�l
	rOY = ( i_pPlcEn->GetPIMaeHosei() + i_pPlcEn->GetPIOku() +
		   i_pPlcEn->GetPIOkuHosei()) * rB;						// �p�l����O���␳�l + ���s�� + �����␳�l
	if ( i_pPlcEn->IsYanePanel()) {
		vuRt = MgVect2C( VuRt);
		rlXY = MGeo::Abs( vuRt);
		if ( !MGeo::Zero( rlXY)) {
			rTH /= rlXY;
			rOY /= rlXY;
		}
	}

	VtLng = LnBz.p[1] - LnBz.p[0];
	VtTH = VuRt * rTH;
	VtOY = VuRt * rOY;
	VtUp = VuUp * rH1;
	VtUph = VuUp * rH2;

	//if ( iULCd == 0)
	//	PT[0][0][0].Set( LnBz.p[0] + VtTH);						// ���t����
	//else
	//	PT[0][0][0].Set( LnBz.p[0] + VtTH - VtUp);				// ��t����
	//PT[0][0][1].Set( PT[0][0][0] + VtUp + VtUph);				//
	//PT[0][1][0].Set( PT[0][0][0] - VtOY);						//
	//PT[0][1][1].Set( PT[0][0][1] - VtOY);						//
	//PT[1][0][0].Set( PT[0][0][0] + VtLng);						//
	//PT[1][0][1].Set( PT[0][0][1] + VtLng);						//
	//PT[1][1][0].Set( PT[0][1][0] + VtLng);						//
	//PT[1][1][1].Set( PT[0][1][1] + VtLng);						//
	if ( iULCd == 0) {
		PT[0][0][0] = LnBz.p[0] + VtTH;						// ���t����
	} else {
		PT[0][0][0] = LnBz.p[0] + VtTH - VtUp;				// ��t����
	}
	PT[0][0][1] = PT[0][0][0] + VtUp + VtUph;				//
	PT[0][1][0] = PT[0][0][0] - VtOY;						//
	PT[0][1][1] = PT[0][0][1] - VtOY;						//
	PT[1][0][0] = PT[0][0][0] + VtLng;						//
	PT[1][0][1] = PT[0][0][1] + VtLng;						//
	PT[1][1][0] = PT[0][1][0] + VtLng;						//
	PT[1][1][1] = PT[0][1][1] + VtLng;						//

//	DispList::Rectangular( PT, VuLng, VuRt, VuUp);
	*VuW = VuLng;
	*VuF = VuRt;
	*VuU = VuUp;
}

////////////////////////////////////////////////////////////////////////////
//	�y�@�\�z�p�l���̃f�B�X�v���C���X�g���쐬����
//			
void MdlDispList::DrawPanel( 
						mhPlcParts*	i_pPlcEn,	// �p�l���z�u���
				const	MgPoint3	&i_PtCtr,	//
						MREAL		i_rB,		//
						MINT		i_iMode		// �\�����[�h 1:�p�l���㕔���� 2:�p�l���`�󒼕��� 3:����+�p�l���`��
				)
{

	MgPoint3	PT[2][2][2];					// ���_���W
	MgVect2		vuRt;							// �����p�l���p���s�������Q�����x�N�g��
	MgVect3		VuW, VuF, VuU;					// ���ނ̒��������P�ʃx�N�g���A�E�����P�ʃx�N�g���A������P�ʃx�N�g��

	Panelfig( i_pPlcEn, i_PtCtr, i_rB, PT, &VuW, &VuF, &VuU);
	if ( i_iMode & MP_PANEL_RECTANGULAR) {
		DispList::SetMaterial( 0, 1);
		DispList::DspRectangular( PT, VuF, VuW, VuU);
		DispList::SetMaterial( 0, 5);
//		DispList::Quads( MgLine3( PT[0][1]), MgLine3( PT[0][0]));			
//		DispList::Quads( MgLine3( PT[1][1]), MgLine3( PT[0][1]));			
//		DispList::Quads( MgLine3( PT[1][0]), MgLine3( PT[1][1]));			
//		DispList::Quads( MgLine3( PT[0][0]), MgLine3( PT[1][0]));
	}
	if ( i_iMode & MP_PANEL_LINE) {
//		glColor3f(1.0,0.,0.);
		DispList::SetMaterial( 0, 5);
		glBegin(GL_LINE_STRIP);
			glVertex3r( PT[0][1][1].x, PT[0][1][1].y, PT[0][1][1].z);			
			glVertex3r( PT[1][1][1].x, PT[1][1][1].y, PT[1][1][1].z);			
			glVertex3r( PT[1][0][1].x, PT[1][0][1].y, PT[1][0][1].z);			
			glVertex3r( PT[0][0][1].x, PT[0][0][1].y, PT[0][0][1].z);	
			glVertex3r( PT[0][1][1].x, PT[0][1][1].y, PT[0][1][1].z);	
		glEnd();
	}
}


////////////////////////////////////////////////////////////////////////////
//	�f�B�X�v���C���X�g���쐬����
MINT MdlDispList::OpenDL( 
						MINT		inmDispList		// DisplayList�ԍ�
				)
{
	// make display list number
	if ( ( z_DispListFig[inmDispList] = glGenLists( 1)) == 0)
		return 1;

	// �f�B�X�v���C���X�g���쐬����
	glNewList( z_DispListFig[inmDispList], GL_COMPILE);

//	glPushMatrix();
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	�f�B�X�v���C���X�g�̍쐬���I������
void MdlDispList::CloseDL()
{
//	glPopMatrix();
	glEndList();
}

////////////////////////////////////////////////////////////////////////////
//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�����A������
//
MINT MdlDispList::MakeDispListMat0(
						MREAL		rB,				// �\���{��
				const	MgPoint3	&PtCtr			// ���S���W
				)
{
	if ( ( z_DispListMat[0] = glGenLists( 1)) == 0)
		return 1;
	// �f�B�X�v���C���X�g���쐬����
	glNewList( z_DispListMat[0], GL_COMPILE);

	DispList::SetMaterial( 0, 0);									// ����

	MdlDispList::CloseDL();
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�ǁA��؁@
//
MINT MdlDispList::MakeDispListMat1(
						MREAL		rB,				// �\���{��
				const	MgPoint3	&PtCtr			// ���S���W
				)
{
	if ( ( z_DispListMat[1] = glGenLists( 1)) == 0)
		return 1;
	// �f�B�X�v���C���X�g���쐬����
	glNewList( z_DispListMat[1], GL_COMPILE);

	DispList::SetMaterial( 0, 1);									// �ǁA���

	MdlDispList::CloseDL();
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�ǁA��؁A�����@������
//
MINT MdlDispList::MakeDispListMat2(
						MREAL		rB,				// �\���{��
				const	MgPoint3	&PtCtr			// ���S���W
				)
{
	if ( ( z_DispListMat[2] = glGenLists( 1)) == 0)
		return 1;
	// �f�B�X�v���C���X�g���쐬����
	glNewList( z_DispListMat[2], GL_COMPILE);

	DispList::SetMaterial( 1, 0);									// �����A�ǁ@������

	MdlDispList::CloseDL();
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�ʕ\���@�܂��́@���C���t���[���\�� �I��
//
void MsViewSWMode(
						MINT		imdWS			// �\���I��		1: �ʕ\���A2: ���C���t���[���\��
				)
{
	switch ( imdWS)
	{
	case 1:														// �ʕ\��
		// SetColor for Wireframe mode
		glEnable(GL_BLEND);

		glEnable( GL_LIGHTING);
		glEnable( GL_DEPTH_TEST);								// �O��֌W�𖾊m�ɂ���ׂɃf�v�X�e�X�g��L���ɂ���
//		glEnable( GL_NORMALIZE);								// glScalef���g���ꍇ�͖@���̒������ω�����̂�
																// GL_NORMALIZE��Enable�ŒP�ʃx�N�g��������
		glDisable( GL_NORMALIZE);

		// Front face Fill
		glPolygonMode( GL_FRONT, GL_FILL);

		//// Back face Line (Only wireframe mode)
		// glPolygonMode( GL_BACK, GL_LINE);

		// BackFace Culling
		glCullFace( GL_BACK);

		// Culling mode set
		glEnable( GL_CULL_FACE);

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;

	case 11:													// �ʕ\��
		// SetColor for Wireframe mode
//		glEnable(GL_BLEND);

		glEnable( GL_LIGHTING);
		glEnable( GL_DEPTH_TEST);								// �O��֌W�𖾊m�ɂ���ׂɃf�v�X�e�X�g��L���ɂ���
//		glEnable( GL_NORMALIZE);								// glScalef���g���ꍇ�͖@���̒������ω�����̂�
//																// GL_NORMALIZE��Enable�ŒP�ʃx�N�g��������
		glDisable( GL_NORMALIZE);
																// �ʂ�h��ׂ��ŕ`��
		// Front face Fill
		glPolygonMode( GL_FRONT, GL_FILL);

		// BackFace Culling
		glCullFace( GL_BACK);

//		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

		// Culling mode set
		glEnable( GL_CULL_FACE);

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;

	case 12:													// �|���S���I�t�Z�b�g�@�\��L���ɂ���
																// �ʂ̋��E����`�����[�h�ɂ��čēx�ʂ�`�悷��B
////U		glColor4f( 0., 0., 0., 0.);
////
////		glDisable( GL_LIGHTING);
////		glDisable( GL_DEPTH_TEST);
////		glDisable( GL_NORMALIZE);

		glEnable( GL_POLYGON_OFFSET_LINE);
		glPolygonOffset( 1.0, 1.0);
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
//		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
//		glCullFace( GL_BACK);
//		glEnable( GL_CULL_FACE);
		break;

	case 2:														// ���C���[�t���[��
		// SetColor for Wireframe mode
		glColor4f( 1., 1., 1., 1.);

		glDisable( GL_LIGHTING);
		glDisable( GL_DEPTH_TEST);
		glDisable( GL_NORMALIZE);

		// Front Line
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

		// Culling mode set
		glDisable( GL_CULL_FACE);
		break;

	case 3:														// ���C���[�t���[��
		// SetColor for Wireframe mode
		glColor4f( 1., 1., 1., 1.);

		glDisable( GL_LIGHTING);
		glDisable( GL_DEPTH_TEST);
		glDisable( GL_NORMALIZE);

		// Polygon Offset Mode
		glEnable( GL_POLYGON_OFFSET_LINE);
//		glPolygonOffset( 1.0, 1.0);
		glPolygonOffset( 5.0, 5.0);

		// Front Line
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

		// Culling mode set
		glDisable( GL_CULL_FACE);
		break;
	}
}

GLint MsDrawPlane( GLdouble w, GLdouble d ,GLdouble h);		//ADD
GLint MsDrawBox(GLdouble d, GLdouble w, GLdouble h);		//ADD

//N #define __ORIGINAL__
////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���C���t���[���\���@�܂��́@�ʕ\������
//
void MsDrawDisplayList(
						int			iFWire		// �\���^�C�v�@0: �ʕ\���A1:�������A2:���ނ̂݁A3:���C���t���[���\��
				)
{
	switch( iFWire)
	{
	case 0:
#ifdef __ORIGINAL__		
		MsViewSWMode( 1);										// �ʕ\��

	glEnable(GL_DEPTH_TEST);									// �O��e�X�g
	glBlendFunc(GL_ONE, GL_ZERO);								// ���ԕ\���ݒ�(�O1.0,��0.0: ��̐}�`���\��)�@

		glCallList( z_DispListFig[1]);							// �}�e���A���t���@����+��b

		glCallList( z_DispListMat[1]);							// �}�e���A��(��+���)	����
		glCallList( z_DispListFig[2]);							// ��+���

		glCallList( z_DispListMat[0]);							// �}�e���A��(����)		����
		glCallList( z_DispListFig[3]);							// ����
		break;
		
#else
		MsViewSWMode( 11);										// �ʕ\��
 
		glCallList( z_DispListFig[1]);							// �}�e���A���t���@����+��b

		MsViewSWMode( 12);										// �ʕ\��

		glCallList( z_DispListFig[1]);							// �}�e���A���t���@����+��b

		break;
#endif
	case 1:
		MsViewSWMode( 1);										// �ʕ\��

	glEnable(GL_DEPTH_TEST);									// �O��e�X�g
	glBlendFunc(GL_ONE, GL_ZERO);								// ���ԕ\���ݒ�(�O1.0,��0.0: ��̐}�`���\��)�@

		glCallList( z_DispListFig[1]);
		glCallList( z_DispListMat[2]);

		glDepthMask(GL_FALSE);									// �����A�ǁ@������
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);				// �������ݒ�

		glCallList( z_DispListFig[2]);							// ��+��؁@������
		glCallList( z_DispListFig[3]);							// ����		������
		break;
		
	case 2:
		MsViewSWMode( 1);										// �ʕ\��

	glEnable(GL_DEPTH_TEST);									// �O��e�X�g
	glBlendFunc(GL_ONE, GL_ZERO);								// ���ԕ\���ݒ�(�O1.0,��0.0: ��̐}�`���\��)�@

		glCallList( z_DispListFig[1]);							// �}�e���A���t���@����+��b
		break;
		
	case 3:
		MsViewSWMode( 2);										// ���C���t���[���\��

	glEnable(GL_DEPTH_TEST);									// �O��e�X�g
	glBlendFunc(GL_ONE, GL_ZERO);								// ���ԕ\���ݒ�(�O1.0,��0.0: ��̐}�`���\��)�@

		glCallList( z_DispListFig[1]);							// ����+��b
		glCallList( z_DispListFig[2]);							// ��+����
		glCallList( z_DispListFig[3]);							// ����
//		glCallList( z_DispListFig[1]);							// ����+��b
		break;

	case 4:
		MsViewSWMode( 1);										// �ʕ\��

	glEnable(GL_DEPTH_TEST);									// �O��e�X�g
	glBlendFunc(GL_ONE, GL_ZERO);								// ���ԕ\���ݒ�(�O1.0,��0.0: ��̐}�`���\��)�@

		glCallList( z_DispListFig[1]);							// �}�e���A���t���@����+��b

		glCallList( z_DispListMat[1]);							// �}�e���A��(��+���)	����
		glCallList( z_DispListFig[2]);							// ��+���

		glCallList( z_DispListMat[0]);							// �}�e���A��(����)		����
		glCallList( z_DispListFig[3]);							// ����

		MsViewSWMode( 3);										// �I�t�Z�b�g���C���[�t���[���\��

	glEnable(GL_DEPTH_TEST);									// �O��e�X�g
	glBlendFunc(GL_ONE, GL_ZERO);								// ���ԕ\���ݒ�(�O1.0,��0.0: ��̐}�`���\��)�@

		glCallList( z_DispListFig[1]);							// �}�e���A���t���@����+��b
	}

	glFlush();
	glDepthMask(GL_TRUE);										// �������e�X�g

	//glDisable(GL_LIGHTING);									// �������e�X�g		NU?
	//glDisable(GL_DEPTH_TEST);									// �������e�X�g		NU?
	//glDisable(GL_BLEND);										// �������e�X�g		NU?

//	auxSwapBuffers();
//DEL	glutSwapBuffers();

}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�`��
BOOL MsRenderScene1(
						int			i_iFWire,	// �\���^�C�v�@0: �ʕ\���A1:�������A2:���ނ̂݁A3:���C���t���[���\��
						MREAL		i_rScl,		// �g�嗦
						MREAL		i_rRotX,	// ��]�p	V3( ���C���C��)
						MREAL		i_rRotY,	// ��]�p	V3( ���C���C��)
						MREAL		i_rRotZ,	// ��]�p	V3( ���C���C��)
						MREAL		i_rMovX,	// �ړ���	V3( ���C���C��)
						MREAL		i_rMovY,	// �ړ���	V3( ���C���C��)
						MREAL		i_rMovZ		// �ړ���	V3( ���C���C��)
				)
{
	// �w�i�F�̏���
//Org	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT) ;

	//======
		//�I�u�W�F�N�g�`�惂�[�h�ɂ���B
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;
	//////////////////////////////////////////////
	//�K�v�ȋ@�\�̗L����
	//
	glEnable(GL_NORMALIZE) ;
	glEnable(GL_AUTO_NORMAL) ;
	glShadeModel (GL_SMOOTH);
	glEnable( GL_DEPTH_TEST ); //Z�o�b�t�@���g�p����
	//----

	// �}�g���b�N�X�̃X�^�b�N
	glPushMatrix();


	// 11/10/25
	gluLookAt(0., 0., 5.,   0.,0.,0.,    0.,1.,0.);


	// ��] X��Y��Z�̏��ɉ�]
    glRotatef( i_rRotZ, 0.0f, 0.0f, 1.0f );
    glRotatef( i_rRotY, 0.0f, 1.0f, 0.0f );
	glRotatef( i_rRotX, 1.0f, 0.0f, 0.0f );

	// �g��k��
	glScalef( i_rScl, i_rScl, i_rScl); 

	// �ړ�
	glTranslatef( i_rMovX, i_rMovY, i_rMovZ);

#if(1)
	// �f�B�X�v���C���X�g�`��
	MsDrawDisplayList( i_iFWire);

	// �}�g���b�N�X�̃X�^�b�N
    glPopMatrix();
#else

	MsDrawBox(2.0, 3.0, 1.0);
	MsDrawPlane( 5.0, 5.0 , 0.0);

	//���W�n��߂��Ă���
	glPopMatrix();

#endif
//===
	glDisable(GL_AUTO_NORMAL) ;
	glDisable(GL_NORMALIZE) ;
//---
	// �_�u���o�b�t�@�؂�ւ�
    glFinish();
    return TRUE;
}

} // namespace MC
