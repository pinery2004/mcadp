//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgConnect.cpp
//
//		
//
//
//  K.Matsu           09/20/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_CONNECT_DO

#include "MgLib.h"
#include "MgConnect.h"	

#define PROG_NAME MBCstr( "MgConnect")
//
//======================( �R���� )==============================
//		�E�B���O�h�G�b�W�f�[�^�\��
//
MgNode::MgNode(
						MINT	iSzNode		// (I  ) �m�[�h��
				)
{
	MINT	iN1;

	m_Node = (MINT *)new char[iSzNode * 12 * sizeof(MINT)];
	
	for ( iN1=0; iN1<iSzNode; iN1++ ) {
		EMPT( iN1)->nlnk = iN1 + 1;
		EMPT( iN1)->plnk = iN1 - 1;
	}
	EMPT( 0)->plnk = iSzNode - 1;
	EMPT( iSzNode - 1)->nlnk = 0;
}

void MgNode::wing(
						MINT	iE1,
						MINT	iE2
				)
{
	MgEdgeNode *pE1 = EDGE( iE1);
	MgEdgeNode *pE2 = EDGE( iE2);
	
	if ( pE1->PVT == pE2->PVT ) {
		if ( pE1->PFACE == pE2->NFACE ) {
			pE1->PCW = iE2;
			pE2->NCCW = iE1;
		} else if ( pE1->NFACE == pE2->PFACE ) {
			pE1->NCCW = iE2;
			pE2->PCW = iE1;
		}
	} else if ( pE1->PVT == pE2->NVT ) {
		if ( pE1->PFACE == pE2->PFACE ) {
			pE1->PCW = iE2;
			pE2->PCCW = iE1;
		} else if ( pE1->NFACE == pE2->NFACE ) {
			pE1->NCCW = iE2;
			pE2->NCW = iE1;
		}
	} else if ( pE1->NVT == pE2->PVT ) {
		if ( pE1->PFACE == pE2->PFACE ) {
			pE1->PCCW = iE2;
			pE2->PCW = iE1;
		} else if ( pE1->NFACE == pE2->NFACE ) {
			pE1->NCW = iE2;
			pE2->NCCW = iE1;
		}
	} else if ( pE1->NVT == pE2->NVT ) {
		if ( pE1->PFACE == pE2->NFACE ) {
			pE1->PCCW = iE2;
			pE2->NCW = iE1;
		} else if ( pE1->NFACE == pE2->PFACE ) {
			pE1->NCW = iE2;
			pE2->PCCW = iE1;
		}
	}
}

//	��̃\���b�hSn�A��̖ʕ�Fn�A��̒��_Vn���Ȃ�k�ނ����_������킷���ʑ̂����
MINT MgNode::mvsf(							// (  O) �\���b�h�m�[�h�h�c
						MINT	*piFn,		// (  O) �ʕ��m�[�h�h�c
						MINT	*piVn		// (  O) ���_�m�[�h�h�c
				 )
{
	MINT iSn = mks();						// �\���b�h
	*piFn = mkf( iSn);						// �ʕ�
	*piVn = mkv( iSn);						// ���_

	SOLD( iSn)->NFACE = SOLD( iSn)->PFACE = *piFn;
	FACE( *piFn)->NFACE = FACE( *piFn)->PFACE = iSn;
	SOLD( iSn)->NVT = SOLD( iSn)->PVT = *piVn;
	VRTX( *piVn)->NVT = VRTX( *piVn)->PVT = iSn;
	return iSn;
}

//	�\���b�hS1�̖ʕ�F1��ɁA���̍\�����_V1�ɐڑ����āA�V�����Ő�En�ƐV�������_Vn�����
MINT MgNode::mev(							// (  O) ���_�m�[�h�h�c
						MINT	iS1,		// (I  ) �\���b�h�m�[�h�h�c
						MINT	iF1,		// (I  ) �ʕ��m�[�h�h�c
						MINT	iV1,		// (I  ) ���_�m�[�h�h�c
						MINT*	piEn		// (  O) �Ő��m�[�h�h�c
				)
{
	MINT iVn = mkv( iS1);					// ���_
	*piEn = mke( iS1);						// �Ő�
	
	VRTX( iVn)->PED = *piEn;

	EDGE( *piEn)->NFACE = EDGE( *piEn)->PFACE = iF1;
	EDGE( *piEn)->NVT = iVn;
	EDGE( *piEn)->PVT = iV1;
	return iVn;
}

//	�Ő�E1�ƒ��_V1���폜����
MINT MgNode::kev(
						MINT	iE1			// (I  ) �Ő��m�[�h�h�c
				)
{
	MINT iVd = EDGE( iE1)->PVT;
	klv( EDGE( iE1)->NVT);
	kle( iE1);								// �c���->���̗Ő��Ƀ����N���Ă��镽�ʂƒ��_�̃����N��̕ύX
	return iVd;
}

//	split edge, make vertex
//	�\���b�hS1�̖ʕ�F1��ɁA�V�����Ő�En�ƐV�������_Vn����邱�Ƃɂ��Ő��𕪊�����
MINT MgNode::semv(							// (  O) ���_�m�[�h�h�c
						MINT	iS1,		// (I  ) �\���b�h�m�[�h�h�c
						MINT	iE1,		// (I  ) �ʕ��m�[�h�h�c
						MINT*	piEn		// (  O) �Ő��m�[�h�h�c
				)
{
	MINT iVn = mkv( iS1);					// ���_
	*piEn = mke( iS1);						// �Ő�

	EDGE( *piEn)->PFACE = EDGE( iE1)->PFACE;
	EDGE( *piEn)->NFACE = EDGE( iE1)->NFACE;
	EDGE( *piEn)->PVT = EDGE( iE1)->PVT;
	EDGE( *piEn)->NVT = iVn;
	EDGE( *piEn)->PED = *piEn;

	EDGE( iE1)->PVT = iVn;
	return iVn;
}

//	join edges, kill vertex
//	���_V1�Ƒ����Ő�Ed���폜���邱�Ƃɂ�蒸�_V1���܂����Q�̗Ő�����������
MINT MgNode::jekv(							// (  O) �Ő��m�[�h�h�c
						MINT	iVd			// (I  ) ���_�m�[�h�h�c
				)
{
	MINT iCW;
	MINT iCCW;
	MINT iV1;
	MINT iE1;
	MINT iEd = VRTX( iVd)->PED;

	if ( EDGE( iEd)->NVT == iVd) {
		if (EDGE( iEd)->NCW != EDGE( iEd)->NCCW)
			msSysError( PROG_NAME, 999);
		iE1 = EDGE( iEd)->NCW;
		iCW = EDGE( iEd)->PCW;
		iCCW = EDGE( iEd)->PCCW;
		iV1 = EDGE( iEd)->PVT;
	} else {
		if (EDGE( iEd)->PCW != EDGE( iEd)->PCCW)
			msSysError( PROG_NAME, 999);
		iE1 = EDGE( iEd)->PCW;
		iCW = EDGE( iEd)->NCW;
		iCCW = EDGE( iEd)->NCCW;
		iV1 = EDGE( iEd)->NVT;
	}

	if ( EDGE( iE1)->PVT == iVd) {
		EDGE( iE1)->PCW = iCW;
		EDGE( iE1)->PCCW = iCCW;
		EDGE( iE1)->PVT = iV1;
	} else {
		EDGE( iE1)->NCW = iCW;
		EDGE( iE1)->NCCW = iCCW; 
		EDGE( iE1)->NVT = iV1;
	}

	klv( iV1);
	kle( iEd);
	return iE1;
}

//	�\���b�hS1�̖ʕ�F1��ɁA�V�����Ő�En�ƐV�����ʕ�Fn����邱�Ƃɂ��ʕ��𕪊�����
MINT MgNode::mef(							// (  O) �Ő��m�[�h�h�c
						MINT	iS1,		// (I  ) �\���b�h�m�[�h�h�c
						MINT	iV1,		// (I  ) ���_�m�[�h�h�c�P
						MINT	iF1,		// (I  ) �ʕ��m�[�h�h�c
						MINT	iV2,		// (I  ) ���_�m�[�h�h�c�Q
						MINT*	piFn		// (  O) �ʕ��m�[�h�h�c
				)
{
	MINT iEn = mke( iS1);					// �Ő�
	*piFn = mkf( iS1);						// ���_

	EDGE( iEn)->PFACE = iF1;
	EDGE( iEn)->NFACE = *piFn;
	EDGE( iEn)->PVT = iV1;
	EDGE( iEn)->NVT = iV2;

	FACE( *piFn)->PED = iEn;
	return iEn;
}

//	�Ő�En����іʕ�Fn���폜���AEn.PFACE���o�͂���
MINT MgNode::kef(							// (  O) �ʕ��m�[�h�h�c
						MINT	iEd			// (I  ) �Ő��m�[�h�h�c
				)
{
	MINT iFd = EDGE( iEd)->NFACE;
	MINT iF1 = EDGE( iEd)->PFACE;


	kle( iEd);
	klf( iFd);
	return iF1;
}

//	�����O��̂P�_�ƊO�����[�v��̂P�_���w�肵�āA���������ԗŐ�����邱�Ƃɂ��A�����O����������
MINT MgNode::mekr(							// (  O) 
						MINT	iS1,		// (I  ) �\���b�h�m�[�h�h�c
						MINT	iV1,		// (I  ) ���_�m�[�h�h�c�P
						MINT	iV2			// (I  ) ���_�m�[�h�h�c�Q
				)
{
	MINT iEn = mke( iS1);
	EDGE( iEn)->PVT = iV2;
	EDGE( iEn)->NVT = iV1;
	return iEn;
}

//	�����O��̂P�_�ƊO�����[�v��̂P�_���w�肵�āA���������ԗŐ�����邱�Ƃɂ��A�����O����������
MINT MgNode::kekr(							// (  O) 
						MINT	iEd			// (I  ) �Ő��m�[�h�h�c
				)
{
	kle(iEd);
	return iEn;
}


