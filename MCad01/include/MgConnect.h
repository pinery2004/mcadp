#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPoint.h
//
//		�����̌���
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//

#ifdef DLL_EXPORT_CNCT
	#undef DLL_EXPORT_CNCT
#endif

#ifdef DLL_EXPORT_CONECT_DO
	#pragma message( "<<< MgConnect�Edll_EXport >>>")
	#define DLL_EXPORT_CNCT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_CNCT
		#else
//			#pragma message( "=== MgConnect�Edll_IMport ===")
			#define DLL_EXPORT_CNCT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_CNCT
	#endif
#endif

#define		MSZNODEBF	10000
#define		MSZNODE		12

#define		MASK8		0x80
#define		MASK7		0x40
#define		MASK6		0x20
#define		MASK5		0x10
#define		MASK4		0x08
#define		MASK3		0x04
#define		MASK2		0x02
#define		MASK1		0x01

namespace MC
{

//
//======================( �R���� )==============================
//		�E�B���O�h�G�b�W�f�[�^�\��
//
class DLL_EXPORT_CNCT MgNode
{
public:
//	MINT m_Node[MSZNODEBF][MSZNODE];
	MINT*		m_Node;
	
	MgNode( MINT iSzNode);
	
	void wing( MINT iE1, MINT iE2);
	class MgWorldNode* WRLD();
	class MgEmptyNode* EMPT( MINT iM1);
	class MgSolidNode* SOLD( MINT iB1);
	class MgEdgeNode* EDGE( MINT iE1);
	class MgFaceNode* FACE( MINT iF1);
	class MgVertexNode* VRTX( MINT iV1);
	void CLR( MINT iN1);
	void CLR( void* pN1);

	//	�ʕ��A�Ő��A���_�̊e���O�͋�̏�ԂŃ\���b�h�̃m�[�h�𐸐����A
	//	���[���h�u���b�N�̃\���b�h�̃����O�Ɋ܂߂�
	MINT mks();
	//	�V�����g�p�\�ȃm�[�h�𐶐�����
	MINT mkm();
	//	�V�����ʕ��̃m�[�h�𐶐����A�ʕ��̃����O���Ɋ܂߂�(�����N�̍ŏI�ɕt����)
	MINT mkf( MINT iS1);
	//	�V�����Ő��̃m�[�h�𐶐����A�Ő��̃����O���Ɋ܂߂�(�����N�̍ŏI�ɕt����)
	MINT mke( MINT iS1);
	//	�V�������_�̃m�[�h�𐶐����A���_�̃����O���Ɋ܂߂�(�����N�̍ŏI�ɕt����)
	MINT mkv( MINT iS1);
	// �m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
	void klm( MINT iM1);
	// �\���b�h�̃m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
	void kls( MINT iS1);
	// �ʕ��̃m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
	void  klf( MINT iF1);
	// �Ő��̃m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
	void  kle( MINT iE1);
	// ���_�̃m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
	void  klv( MINT iV1);
	//	��̃\���b�hSn�A��̖ʕ�Fn�A��̒��_Vn���Ȃ�k�ނ����_������킷���ʑ̂����
	MINT mvsf( MINT	*piFn, MINT *piVn);
	//	�\���b�hS1�̖ʕ�F1��ɁA���̍\�����_V1�ɐڑ����āA�V�����Ő�En�ƐV�������_Vn�����
	MINT mev( MINT iS1, MINT iF1, MINT iV1, MINT* piEn);
	//	�Ő�E1�ƒ��_V1���폜����
	MINT kev( MINT iE1);
	//	�\���b�hS1�̖ʕ�F1��ɁA�V�����Ő�En�ƐV�������_Vn����邱�Ƃɂ��Ő��𕪊�����
	MINT semv( MINT iS1, INT iE1, MINT* piEn);
	//	join edges, kill vertex
	//	���_V1�Ƒ����Ő�Ed���폜���邱�Ƃɂ�蒸�_V1���܂����Q�̗Ő�����������
	MINT jekv( MINT	iVd);
	//	�\���b�hS1�̖ʕ�F1��ɁA�V�����Ő�En�ƐV�����ʕ�Fn����邱�Ƃɂ��ʕ��𕪊�����
	MINT mef( MINT iS1, MINT iV1, MINT iF1, MINT iV2, MINT*	piFn);
	//	�Ő�En����іʕ�Fn���폜���AEn.PFACE���o�͂���
	MINT kef( MINT iEd);
};

class DLL_EXPORT_CNCT MgWorldNode
{
public:
	MUINT		TMP1[3];
	MINT		St;							// ���	
	MUSHORT		NSOLD;						// Body ring
	MUSHORT		PSOLD;
	MINT		TMP3[6];
	MUSHORT		nlnk;						// �󂫃G���A �����N
	MUSHORT		plnk;
};

class DLL_EXPORT_CNCT MgEmptyNode
{
public:
	MUINT		TMP1[3];
	MINT		St;							// ���	
	MUINT		TMP2[2];
	MUSHORT		NEMPT;						// Empty ring
	MUSHORT		PEMPT;
	MINT		TMP3[4];
	MUSHORT		nlnk;						// User links
	MUSHORT		plnk;
};

class DLL_EXPORT_CNCT MgSolidNode
{
public:
	MUINT		TMP;
	MUINT		PNAME1;
	MUINT		PNAME2;
	MINT		St;							// ���	
	MUSHORT		NFACE;						// Fase ring
	MUSHORT		PFACE;
	MUSHORT		NED;						// Edge ring
	MUSHORT		PED;
	MUSHORT		NVT;						// Vertex ring
	MUSHORT		PVT;
	MUSHORT		DAD;						// Pts Tree
	MUSHORT		SON;
	MUSHORT		BRO;						// Pts Tree
	MUSHORT		SIS;
	MUSHORT		alt;						// Body TRAM
	MUSHORT		TRAM;
	MUSHORT		CW;							// Body ring
	MUSHORT		CCW;
	MUSHORT		nlnk;						// User links
	MUSHORT		plnk;
};

class DLL_EXPORT_CNCT MgFaceNode
{
public:	
	MBYTE		Tp;							// ����	( 1:���A2:����������� )
// ��
	MINT		AA;							// FacePlane
	MINT		BB;							// normal
	MINT		CC;							// vector
	MINT		St;							// ���	
											// 		MASK8:	�L���t���O
											// 
	MUSHORT		NFACE;						// Face ring
	MUSHORT		PFACE;
//
	MUSHORT		Ncnt;						// First edge
	MUSHORT		PED;
	MREAL		KK;							// Distance to origin
	MUINT		rgb;						// red, grn, blue, wht Reflectivities(���˗�)
	MUINT		lrgb;						// Lr, Lg, Lb, Lw, Sm, Sn Lumns & Spec Coef(�X�y�b�N�W��) 
	MUSHORT		alt;						// Temporaries
	MUSHORT		slt2;
	MINT		OO;							// Video Intensity
	MUSHORT		nlnk;						// User links
	MUSHORT		plnk;
};

class DLL_EXPORT_CNCT MgEdgeNode
{
public:
//	MBYTE		Tp;							// ����	( 1:�����A2:�~�ʁA3:�~ )
// ��
	MINT		AA;							// display Coord( x1dc, y1dc) or
	MINT		BB;							// 2-D Edge Coet or
	MINT		CC;							// 3-D line Cosines
	MINT		St;							// ���	
											// 		MASK8:	�L���t���O
											// 		MASK7:	�n�_���I�_�����̗̈��`�ς�
											// 		MASK6:	�I�_���n�_�����̗̈��`�ς�
											// 
	
//	MINT		idLine;						// ����ID
	MUSHORT		NFACE;						// Two Faces
	MUSHORT		PFACE;
	MUSHORT		NED;						// Edge ring
	MUSHORT		PED;
	MUSHORT		NVT;						// Two Vertices
	MUSHORT		PVT;
	MUSHORT		NCW;						// Clockwise Wing Edges
	MUSHORT		PCW;
	MUSHORT		NCCW;						// CCW Wing Edges
	MUSHORT		PCCW;
	MUSHORT		alt;						// Temporaries
	MUSHORT		slt2;
	MUSHORT		CW;							// Temporaries
	MUSHORT		CCW;
	MUSHORT		nlnk;						// User links
	MUSHORT		plnk;
//	union _z{
//		MgLine2	Ln;							// ����
//		MgArc	Arc;						// �~��
//		MgCir	Cir;						// �~
//	} Z;
//	MgMinMax Mm;							// MinMax

	MUSHORT fcwv( MUSHORT v0);				// ���_V0�̎���ɁA���v��]�����ɉ�]�����ꍇ�̎��̖ʕ������߂�
	MUSHORT fccwv( MUSHORT v0);				// ���_V0�̎���ɁA�����v��]�����ɉ�]�����ꍇ�̎��̖ʕ������߂�
	MUSHORT ecwv( MUSHORT v0);				// ���_V0�̎���ɁA���v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
	MUSHORT eccwv( MUSHORT v0);				// ���_V0�̎���ɁA�����v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
	MUSHORT ecwf( MUSHORT f0);				// �ʕ�f0�̎���ɁA���v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
	MUSHORT eccwf( MUSHORT f0);				// �ʕ�f0�̎���ɁA�����v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
	MUSHORT vcwf( MUSHORT f0);				// �ʕ�f0�̎���ɁA���v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
	MUSHORT vccwf( MUSHORT f0);				// �ʕ�f0�̎���ɁA�����v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
};

class DLL_EXPORT_CNCT MgVertexNode
{
public:
	MgPoint3	Pt;							// �_
// ��
	MREAL		XWC;						// World Locus
	MREAL		YWC;						// 
	MREAL		ZWC;						// 
	MINT		St;							// ���	
											// 		MASK8:	�L���t���O
											// 
	MUSHORT		XDC;						// Display Locus
	MUSHORT		YDC;
	MUSHORT		Tjoint;						// First Edge
	MUSHORT		PED;
	MUSHORT		NVT;						// Vertex ring
	MUSHORT		PVT;
	MREAL		XPP;						// Perspective
	MREAL		YPP;						// Projected Locus
	MREAL		ZPP;						//	alt alt2
	MUSHORT		cw;							// Temporaries
	MUSHORT		ccw;
	MUSHORT		nlnk;						// User links
	MUSHORT		plnk;
};


#include "MgConnect1.h"

} // namespace MC