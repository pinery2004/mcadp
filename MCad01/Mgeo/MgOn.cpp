//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"

namespace MC
{

////
////===========================================================================
////		�_�@�`�󉉎Z
////
//// ---------------------( �Q���� )------------------------------
////
////	�_���_��ɂ��邩�𒲂ׂ�B
////
//bool MGeo::On(									// (  O) �X�e�C�^�X
//												//			true:	�_��ɂ���
//												//			false:	�_��ɂȂ�
//				const	MgPoint2&	p1,			// (I  ) �_1
//				const	MgPoint2&	p2,			// (I  ) �_2
//						MREAL		rTol		// (I  ) �g�������X
//				)
//{
////	return (p1 == p2);
//	MgVect2	V1 = p2 - p1;
//	return (MgAbs_2( V1) <= rTol * rTol);
//}

//// ---------------------( �R���� )------------------------------
////
////	�_���_��ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkPt3OnPt3(							// (  O) �X�e�C�^�X
//												//			true:	�_��ɂ���
//												//			false:	�_��ɂȂ�
//				const	MgPoint3&	p1,			// (I  ) �_1
//				const	MgPoint3&	p2,			// (I  ) �_2
//						MREAL		rTol		// (I  ) �g�������X
//				)
//{
////	return (p1 == p2);
//	MgVect3	V1 = p2 - p1;
//	return (MgAbs_2( V1) <= rTol * rTol);
//}

////===========================================================================
////		�����@�`�󉉎Z
////
//// ---------------------( �Q���� )------------------------------
////
////	�_��������ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkPt2OnULn2WS(						// (  O) �X�e�C�^�X
//												//		 	true:	������ɂ���
//												//		 	false:	������ɂȂ�
//				const	MgPoint2&	p1,			// (I  ) �_1
//				const	MgULine2&	ULn2,		// (I  ) ����2
//						MINT*		ist,		// (  O) �⏕�X�e�C�^�X
//												//			MC_RIGHT			(010): �_�������̉E��
//												//			MC_ON_LINE			(020): �_��������
//												//			MC_LEFT				(040): �_�������̍���
//						MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	bool		bst;							// �X�e�C�^�X
//	MgVect2		v2s1;							// ����2�̎n�_����_1�܂ł̃x�N�g��
//	MREAL		pa1;							// ����2����_1�܂ł̉�������
////
//// ����2�̕����i�P�ʃx�N�g���j�ƒ���2�̎n�_����_1�܂ł̃x�N�g���̊O�ς�艔�����������߂�
//	v2s1 = p1 - ULn2.p;					
//	pa1 = ULn2.v ^ v2s1;						// ����2�̕����i�P�ʃx�N�g���j�ƒ���2�̎n�_����_1�܂ł̃x�N�g���̊O��
////
//// �����������덷���Ȃ璼����Ƃ݂Ȃ�
//	if (MgZero(pa1, rTol)) {
//		*ist = MC_ON_LINE;
//		bst = true;
////
//// �������������Ȃ璼���̍��Ƃ݂Ȃ�
//	} else if (pa1 > 0) {
//		*ist = MC_LEFT;
//		bst = false;
////
//// �������������Ȃ璼���̉E�Ƃ݂Ȃ�
//	} else {
//		*ist = MC_RIGHT;
//		bst = false;
//	}
//	return bst;
//}

//// ---------------------( �Q���� )------------------------------
////
////	�_����������ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkPt2OnHLn2WS(						// (  O) �X�e�C�^�X
//												//		 	true:	��������ɂ���
//												//		 	false:	��������ɂȂ�
//				const	MgPoint2&	p1,			// (I  ) �_1
//				const	MgHLine2	&HLn2,		// (I  ) ������2
//						MINT*		ist,		// (  O) �⏕�X�e�C�^�X
//												//			MC_RIGHT			(010): �_���������̉E��
//												//			MC_ON_LINE			(020): �_����������
//												//			MC_LEFT				(040): �_���������̍���
//						MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	bool		bst;							// �X�e�C�^�X
//	MgVect2		v2s1;							// ������2�̎n�_����_1�܂ł̃x�N�g��
//	MREAL		pa1;							// ������2����_1�܂ł̉�������
////
//// ������2�̕����i�P�ʃx�N�g���j�Ɣ�����2�̎n�_����_1�܂ł̃x�N�g���̊O�ς�艔�����������߂�
//	v2s1 = p1 - HLn2.p;					
//	pa1 = HLn2.v ^ v2s1;						// ������2�̕����i�P�ʃx�N�g���j�Ɣ�����2�̎n�_����_1�܂ł̃x�N�g���̊O��
////
//// �����������덷���Ȃ璼����Ƃ݂Ȃ�
//	if ( MgZero( pa1, rTol)) {
//		*ist = MC_ON_LINE;
//		bst = true;
////
//// �������������Ȃ璼���̍��Ƃ݂Ȃ�
//	} else if ( pa1 > 0) {
//		*ist = MC_LEFT;
//		bst = false;
////
//// �������������Ȃ璼���̉E�Ƃ݂Ȃ�
//	} else {
//		*ist = MC_RIGHT;
//		bst = false;
//	}
//	return bst;
//}

// ---------------------( �Q���� )------------------------------
//
//	�_��������ɂ��邩�𒲂ׂ�B
//
bool MGeo::ChkPt2OnLn2WS(						// (  O) �X�e�C�^�X
												//			true:	������ɂ���
												//			false:	������ɂȂ�
				const	MgPoint2&	p1,			// (I  ) �_1
				const	MgLine2&	Ln2,		// (I  ) ����2
						MINT*		ist,		// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
												//		 �X�e�C�^�X1
												//			MC_RIGHT			(010): �_�������̉E��
												//			MC_ON_LINE			(020): �_����������������
												//			MC_LEFT				(040): �_�������̍���
												//		 �X�e�C�^�X2
												//			MC_ON_PS			(001): �_�������̎n�_��
												//			MC_INSIDE			(002): �_�������̓�����
												//			MC_ON_PE			(004): �_�������̏I�_��
						MREAL		rTol		// (I  ) �g�������X
		)
{
	bool		bst;
	MgVect2		v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect2		v2e1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect2		v2;								// ����2�̎n�_����I�_�ւ̃x�N�g��
	MREAL		pa1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O��
	MREAL		cs, ce;							// ����2�Ɛ���2�̎n�_�C�I�_����_1�ւ̃x�N�g���̓���
	MREAL		tol_2;							// ����p�덷
	MREAL		v2tol_2;						// ����p�덷
	MREAL		v2tol_2_1;						// ����p�덷 v2tol_2/10000
//
	v2s1 = p1 - Ln2.p[0];
	v2e1 = p1 - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// �_��������܂ł̉�������( abs( pa1)/abs( v2)) <= tol ��蒼����ł��邩�𒲂�
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	// ������Ȃ�A����ɐ�����ł��邩�𒲂ׂ�
	tol_2 = rTol * rTol;
	v2tol_2 = tol_2 * Abs_2( v2);
	v2tol_2_1 = tol_2 * Abs_2( v2) * 0.0001f * 0.0001f;
	*ist = 0;
	if (pa1 * pa1 <= v2tol_2) { 								// �_��������܂ł̉���������rTol�ȓ�
		// ����������
		cs = v2 * v2s1;
		ce = v2 * v2e1;
		if (v2s1 * v2s1 <= tol_2) {
			*ist = MC_ON_PS;									// �_�������̎n�_��
		} else if (v2e1 * v2e1 <= tol_2) {
			*ist = MC_ON_PE;									// �_�������̏I�_��
		} else if (cs > v2tol_2_1 &&  ce < -v2tol_2_1) {
			*ist = MC_INSIDE;									// �_�������̓�����
		} 
		bst = (*ist != 0);
		*ist |= MC_ON_LINE;
	} else {
		// ����������łȂ��Ȃ�A�����̍��E�ǂ���ɂ��邩�𒲂ׂ�
		if (pa1 > 0) {
			*ist |= MC_LEFT;									// ����
		} else {
			*ist |= MC_RIGHT;									// �E��
		}
		bst = false;
	}
	return bst;
}
//// ---------------------( �Q���� )------------------------------
////
////	�����̒��S�_��������ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkLn2OnULn2WS(						// (  O) �X�e�C�^�X
//												//			true:	������ɂ���
//												//			false:	������ɂȂ�
//				const	MgLine2&	Ln1,		// (I  ) ����1
//				const	MgULine2&	ULn2,		// (I  ) ����2
//						MINT*		ist,		// (  O) �X�e�C�^�X
//												//			MC_RIGHT			(010): �_�������̉E��
//												//			MC_ON_LINE			(020): �_��������
//												//			MC_LEFT				(040): �_�������̍���
//						MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	MgPoint2 Pt1;
//	Pt1 = ( Ln1.p[0] + Ln1.p[1]) * 0.5;
//	return MgChkPt2OnULn2WS( Pt1, ULn2, ist);
//}

// ---------------------( �Q���� )------------------------------
//
//	�����Ɛ������d�Ȃ��Ă��邩�𒲂ׂ�B
//
bool MGeo::ChkLn2OnLn2(							// (  O) �X�e�C�^�X
												//			true:	�d�Ȃ��Ă���
												//			false:	�d�Ȃ��Ă��Ȃ�
				const	MgLine2&	Ln1,		// (I  ) ����1
				const	MgLine2&	Ln2,		// (I  ) ����2
						MREAL		rTol		// (I  ) �g�������X
		)
{
	bool		bst = false;
	MgVect2		v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
//	MgVect2		v2e1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect2		v2;								// ����2�̎n�_����I�_�ւ̃x�N�g��
	MREAL		pa1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O��
	MREAL		v2tol_2;						// ����p�덷
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;
//
	if (!MGeo::Parallel( Ln1, Ln2))									// ���s�łȂ��ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	v2s1 = Ln1.p[0] - Ln2.p[0];
//	v2e1 = Ln1.p[0] - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// ����1�̎n�_�������2�܂ł̉�������( abs( pa1)/abs( v2)) <= tol ��蒼����ł��邩�𒲂ׂ�
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	cs22 = v2 * v2;
	v2tol_2 = rTol * rTol * cs22;
	if (pa1 * pa1 > v2tol_2) 									// �_��������܂ł̉���������rTol���̏ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	cs21 = 0;
	cs11 = (Ln1.p[0] - Ln2.p[0]) * v2;
	cs12 = (Ln1.p[1] - Ln2.p[0]) * v2;
	if (cs11 < cs12) {
		d1 = MGMAX( cs11, cs21);
		d2 = MGMIN( cs12, cs22);
	} else {
		d1 = MGMAX( cs12, cs21);
		d2 = MGMIN( cs11, cs22);
	}
	dd = d2 - d1;
	// �d�Ȃ�̎n�_����I�_�܂ł̋���( dd/abs( v2)) <= tol ���d�Ȃ��Ă��Ȃ����𒲂ׂ�
	//						 ( dd * dd <= tol * tol * (v2 * v2))
	if (dd < 0. || (dd * dd) <= v2tol_2)						// �d�Ȃ肪rTol�ȉ��̏ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���

	bst = true;
exit:
	return bst;
}

//// ---------------------( �R���� )------------------------------
////
////	�_��������ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkPt3OnULn3(							// (  O) �X�e�C�^�X
//												//			true:	������ɂ���
//												//			false:	������ɂȂ�
//				const	MgPoint3&	p1,			// (I  ) �_1
//				const	MgULine3&	ULn2,		// (I  ) ����2
//						MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	MgVect3		v21, va1;
////	MREAL		pa_2;							//	����2����_1�܂ł̉�������**2
////
//	v21 = p1 - ULn2.p;
//	va1 = v21 ^ ULn2.v;
////	pa_2 = MgAbs_2(va1);
////	return (pa_2 <= rTol * rTol);
//	return (MgAbs_2(va1) <= rTol * rTol);
//}

//// ---------------------( �R���� )------------------------------
////
////	�_����������ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkPt3OnHLn3(							// (  O) �X�e�C�^�X
//												//			true:	������ɂ���
//												//			false:	������ɂȂ�
//				const	MgPoint3&	p1,			// (I  ) �_1
//				const	MgHLine3	&HLn2,		// (I  ) ������2
//						MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	MgVect3		v21, va1;
//	MREAL		c1;
////	MREAL		pa_2;							//	����2����_1�܂ł̉�������**2
////
//	v21 = p1 - HLn2.p;
//	va1 = v21 ^ HLn2.v;
//	c1 = v21 * HLn2.v;
////	pa_2 = MgAbs_2(va1);
////	return (pa_2 <= rTol * rTol);
//	return (MgAbs_2(va1) <= rTol * rTol && c1 > -rTol);
//}

// ---------------------( �R���� )------------------------------
//
//	�_��������ɂ��邩�𒲂ׂ�B
//
bool MGeo::ChkPt3OnLn3WS(						// (  O) �X�e�C�^�X
												//			true:	������ɂ���
												//			false:	������ɂȂ�
				const	MgPoint3&	p1,			// (I  ) �_1
				const	MgLine3		&Ln2,		// (I  ) ����2
						MINT*		ist,		// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
												//		 �X�e�C�^�X1
												//			MC_ON_LINE			(020): �_����������������
												//		 �X�e�C�^�X2
												//			MC_ON_PS			(001): �_�������̎n�_��
												//			MC_INSIDE			(002): �_�������̓�����
												//			MC_ON_PE			(004): �_�������̏I�_��
						MREAL		rTol		// (I  ) �g�������X
		)
{
	bool		bst;
	MgVect3		v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect3		v2e1;							// ����2�̏I�_����_1�ւ̃x�N�g��
	MgVect3		v2;								// ����2�̎n�_����I�_�ւ̃x�N�g��
	MgVect3		va1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O�� 
	MREAL		cs, ce;
	MREAL		tol_2;							// ����p�덷
	MREAL		v2tol_2;						// ����p�덷
	MREAL		v2tol_2_1;						// ����p�덷 v2tol_2/10000
//
	v2s1 = p1 - Ln2.p[0];
	v2e1 = p1 - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	va1 = v2 ^ v2s1;
	//
	// �_��������܂ł̉�������( abs( va1)/abs( v2)) <= tol ��蒼����ł��邩�𒲂�
	//						 ( (va1 * va1) <= tol * tol * (v2 * v2))
	// ������Ȃ�A����ɐ�����ł��邩�𒲂ׂ�
	tol_2 = rTol * rTol;
	v2tol_2 = tol_2 * Abs_2( v2);
	v2tol_2_1 = tol_2 * Abs_2( v2) * 0.0001f * 0.0001f;
	*ist = 0;
	if ( Abs_2( va1) <= v2tol_2) { 							// �_��������܂ł̉���������rTol�ȓ�
		cs = v2 * v2s1;
		ce = v2 * v2e1;
		if (v2s1 * v2s1 <= tol_2) {
			*ist = MC_ON_PS;									// �_�������̎n�_��
		} else if ( v2e1 * v2e1 <= v2tol_2) {
			*ist = MC_ON_PE;									// �_�������̏I�_��
//		} else if ( cs * ce <= 0) {
		} else if ( cs > v2tol_2_1 &&  ce < -v2tol_2_1) {
			*ist = MC_INSIDE;									// �_�������̓�����
		} 
		bst = ( *ist != 0);
		*ist |= MC_ON_LINE;
	} else {
		bst = false;
	}
	return bst;
}
// ---------------------( �R���� )------------------------------
//
//	�����Ɛ������d�Ȃ��Ă��邩�𒲂ׂ�B
//
bool MGeo::ChkLn3OnLn3(							// (  O) �X�e�C�^�X
												//			true:	�d�Ȃ��Ă���
												//			false:	�d�Ȃ��Ă��Ȃ�
				const	MgLine3		&Ln1,		// (I  ) ����1
				const	MgLine3		&Ln2,		// (I  ) ����2
						MREAL		rTol		// (I  ) �g�������X
		)
{
	bool		bst = false;
	MgVect3		v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
//	MgVect3		v2e1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect3		v2;								// ����2�̎n�_����I�_�ւ̃x�N�g��
	MgVect3		pa1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O��
	MREAL		v2tol_2;						// ����p�덷
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;
//
	if (!MGeo::Parallel( Ln1, Ln2))									// ���s�łȂ��ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	v2s1 = Ln1.p[0] - Ln2.p[0];
//	v2e1 = Ln1.p[0] - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// ����1�̎n�_�������2�܂ł̉�������( abs( pa1)/abs( v2)) <= tol ��蒼����ł��邩�𒲂ׂ�
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	cs22 = v2 * v2;
	v2tol_2 = rTol * rTol * cs22;
	if ((pa1 * pa1) > v2tol_2) 									// �_��������܂ł̉���������rTol���̏ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	cs21 = 0;
	cs11 = v2s1 * v2;
	cs12 = (Ln1.p[1] - Ln2.p[0]) * v2;
	if (cs11 < cs12) {
		d1 = MGMAX( cs11, cs21);
		d2 = MGMIN( cs12, cs22);
	} else {
		d1 = MGMAX( cs12, cs21);
		d2 = MGMIN( cs11, cs22);
	}
	dd = d2 - d1;
	// �d�Ȃ�̎n�_����I�_�܂ł̋���( dd/abs( v2)) <= tol ���d�Ȃ��Ă��Ȃ����𒲂ׂ�
	//						 ( dd * dd <= tol * tol * (v2 * v2))
	if (dd < 0. || (dd * dd) <= v2tol_2)						// �d�Ȃ肪rTol�ȉ��̏ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���

	bst = true;
exit:
	return bst;
}
// ---------------------( �R���� )------------------------------
//
//	�����Ɛ������d�Ȃ��Ă��邩�𒲂ׂ�B
//
bool MGeo::ChkLn3OnLn3WS(						// (  O) �X�e�C�^�X
												//			true:	�d�Ȃ��Ă���
												//			false:	�d�Ȃ��Ă��Ȃ�
				const	MgLine3		&Ln1,		// (I  ) ����1
				const	MgLine3		&Ln2,		// (I  ) ����2
						MINT*		ist,		// (  O) �⏕�X�e�C�^�X�@�d�Ȃ肠��̏ꍇ�͎��̒ʂ�
												//        -4    -3   -2   -1    0     1    2    3    4 		   	
												//		|--   |--  |--- | -- | --- |----| ---|  --|   --|           	  	
												//		|   --|  --| ---|----| --- | -- |--- |--  |--   |                �@	
						MREAL		rTol		// (I  ) �g�������X
				)
{
	bool		bst = false;
	MgVect3		v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
//	MgVect3		v2e1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect3		v2, vu2;						// ����2�̎n�_����I�_�ւ̃x�N�g���A���P�ʃx�N�g��
	MgVect3		pa1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O��
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;
	MREAL		d11, d12, d21, d22;
//
	*ist = 0;
	if (!MGeo::Parallel( Ln1, Ln2))									// ���s�łȂ��ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	v2s1 = Ln1.p[0] - Ln2.p[0];
//	v2e1 = Ln1.p[0] - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	vu2 = v2.Unitize();
	pa1 = vu2 ^ v2s1;
	//
	// ����1�̎n�_�������2�܂ł̉������� abs( pa1) <= tol ��蒼����ł��邩�𒲂ׂ�
	//						 ( pa1 * pa1 <= tol * tol)
	if ( Abs_2( pa1) > rTol * rTol) 							// �_��������܂ł̉���������rTol���̏ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	cs21 = 0;
	cs22 = v2 * vu2;
	cs11 = v2s1 * vu2;
	cs12 = (Ln1.p[1] - Ln2.p[0]) * vu2;
	if (cs11 < cs12) {
		d1 = MGMAX( cs11, cs21);
		d2 = MGMIN( cs12, cs22);

		d11 = cs11;
		d12 = cs12;
		d21 = cs21;
		d22 = cs22;

	} else {
		d1 = MGMAX( cs12, cs21);
		d2 = MGMIN( cs11, cs22);

		d11 = cs12;
		d12 = cs11;
		d21 = cs22;
		d22 = cs21;
	}
	// �⏕�X�e�C�^�X�����߂�
	if (d12 > d22 + rTol) {
		if (d11 > d22 - rTol) {
			if (d11 > d22 + rTol)
				*ist = 4;
			else
				*ist = 3;
		} else {
			if (d11 > d21 + rTol)
				*ist = 2;
			else
				*ist = 1;
		}
	} else if (d11 < d21 - rTol) {
		if (d12 < d21 + rTol) {
			if (d12 < d21 - rTol)
				*ist = -4;
			else
				*ist = -3;
		} else {
			if (d12 < d22 - rTol)
				*ist = -2;
			else
				*ist = 1;
		}
	} else if (d12 > d22 - rTol && d11 < d21 + rTol)
		*ist = 0;
	else
		*ist = -1;

	dd = d2 - d1;
	// �d�Ȃ�̎n�_����I�_�܂ł̋���( dd/abs( v2)) <= tol ���d�Ȃ��Ă��Ȃ����𒲂ׂ�
	//						 ( dd * dd <= tol * tol * (v2 * v2))
	if (dd < 0. || (dd * dd) <= rTol * rTol)					// �d�Ȃ肪rTol�ȉ��̏ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���

	bst = true;
exit:
	return bst;
}

//
// ---------------------( �Q���� )------------------------------
//	�_�ƌ��t�����p�`�̈ʒu�֌W�����߂�
//
bool MGeo::ChkPt2OnGPg2WS(						// (  O) �X�e�C�^�X
												//			true:	���t�����p�`�̓����܂��͕ӏ�
												//			false:	���t�����p�`�̊O��
				const	MgPoint2&	i_pt,		// (I  ) �_
				const	MgGPolyg2&	i_Gpg,		// (I  ) ���t�����p�`
						MINT*		o_piSt,		// (  O) �X�e�C�^�X
												//			MC_IN_BORDER		(001): �_�����t�����p�`�̓���
												//			MC_ON_BORDER		(002): �_�����t�����p�`�̕ӏ�(�܂��͒��_��)
												//			MC_OUT_BORDER		(004): �_�����t�����p�`�̊O��
						MREAL		i_rTol		// (I  ) �g�������X
		)
{
	bool		bst;
	MINT		ist1;
	MINT		ic1;
	MINT		ict, ictSum = 0;									// ���O����p�J�E���^
	MgPolyg2*	pPg;
	
	for ( ic1=0; ic1<i_Gpg.m_n; ic1++) {
		pPg = &(i_Gpg.m_pg[ic1]);

		
		ist1 = CountPg2AroundPt2( i_pt, NULL, *pPg, &ict, i_rTol);
		if ( ist1) {
			*o_piSt = MC_ON_BORDER;
			bst = true;												// ���t�����p�`�̕ӏ�(�܂��͒��_��)
			MQUIT;
		}
		ictSum += ict;
	}

	if ( ictSum > 0) {
		*o_piSt = MC_IN_BORDER;										// ���t�����p�`�̓���
		bst = true;
	} else {
		*o_piSt = MC_OUT_BORDER;										// ���t�����p�`�̊O��
		bst = false;
	}
exit:
	return bst;
}

//
// ---------------------( �Q���� )------------------------------
//	�����̒��S�_�ƌ��t�����p�`�̈ʒu�֌W�����߂�
//
bool MGeo::ChkLn2OnGPg2WS(						// (  O) �X�e�C�^�X
												//			true:	���t�����p�`�̓����܂��͕ӏ�
												//			false:	���t�����p�`�̊O��
				const	MgLine2&	Ln1,		// (I  ) ����
				const	MgGPolyg2&	GPg2,		// (I  ) ���t�����p�`
						MINT*		isth,		// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
												// 		 �e�C�^�X1
												//			MC_IN_BORDER		(001): �_�����t�����p�`�̓���
												//			MC_ON_BORDER		(002): �_�����t�����p�`�̕ӏ�(�܂��͒��_��)
												//			MC_OUT_BORDER		(004): �_�����t�����p�`�̊O��
												// 		 �e�C�^�X2
												//			MC_ON_SIDE_SAME		(010): �ӏ�(�������)	(MC_ON_BORDER�Ƌ��ɐݒ�)
												//			MC_ON_SIDE_REV		(020): �ӏ�(�t����)		(MC_ON_BORDER�Ƌ��ɐݒ�)
												//			MC_ON_TOP			(040): ���_��			(MC_ON_BORDER�Ƌ��ɐݒ�)
						MREAL		rTol		// (I  ) �g�������X
				)
{
	bool		bst;
	MgPoint2	pt1;
	MgVect2		vt1;
	MINT		ist1;
	MINT		ic1;
	MINT		ict, ictSum = 0;									// ���O����p�J�E���^
	MgPolyg2*	pPg;
	
	pt1 = ( Ln1.p[0] + Ln1.p[1]) * 0.5;
	vt1 = Ln1.p[1] - Ln1.p[0];
	
	for ( ic1=0; ic1<GPg2.m_n; ic1++) {
		pPg = &(GPg2.m_pg[ic1]);
		
		ist1 = CountPg2AroundPt2( pt1, &vt1, *pPg, &ict, rTol);
		if ( ist1) {
			*isth = MC_ON_BORDER | ist1;
			bst = true;												// ���t�����p�`�̕ӏ�(�܂��͒��_��)
			MQUIT;
		}
		ictSum += ict;
	}

	if ( ictSum > 0) {
		*isth = MC_IN_BORDER;										// ���t�����p�`�̓���
		bst = true;
	} else {
		*isth = MC_OUT_BORDER;										// ���t�����p�`�̊O��
		bst = false;
	}
exit:
	return bst;
}
//
// ---------------------( �Q���� )------------------------------
// �_�Ƒ��p�`�̈ʒu�֌W�����߂�
// ���p�`�̕ӂ��_�̎���������񐔂����߂�i���̈��:1�@�����:-1�j
MINT MGeo::CountPg2AroundPt2(				// (  O) �X�e�C�^�X
												//								(000): ���p�`�̒��܂��͊O	
												//			MC_ON_SIDE_SAME		(010): �ӏ�(�������)
												//			MC_ON_SIDE_REV		(020): �ӏ�(�t����)
												//			MC_ON_SIDE			(030): �ӏ�(��������=NULL: ���������w�薳��)
												//			MC_ON_TOP			(040): ���_��
				const	MgPoint2&	Pt,			// (I  ) �_
				const	MgVect2		*vst,		// (I  ) �������� �܂��� NULL
												//		 ������NULL�Ŗ�����Γ_���ӏ�̏ꍇ�A
												//		 �ӂ̐��������Ɣ�r����
				const	MgPolyg2&	Pg,			// (I  ) ���p�`
						MINT*		ict,		// (  O) ����J�E���g
												//			>0: ���p�`�����̂̏ꍇ�̎���	(1:1��)
												//			=0: ���_�A�ӏ�A���p�`�̊O
												//			<0: ���p�`�����̏ꍇ�̎���	(-1:1��)	
						MREAL		rTol		// (I  ) �g�������X
				)
{
	MINT		ist;
	MINT		ic;
	MgPoint2	Ps, Pe;
	MgVect2		Vs, Ve;
	MgVect2		Vl;
	MINT		iQs, iQe;						// �n�_�A�I�_�̏ی�
	MINT 		iQse;							// �n�_����I�_�ւ̏ی��ړ���
	MINT 		iQSum = 0;						// �ی��ړ����̍��v
	
	*ict = 0;
	Ps = Pg.m_p[Pg.m_n-1];
	if (Pt == Ps) {								// �_���n�_��
		ist = MC_ON_TOP;
		MQUIT;
	}
	iQs = Quadrant( Pt, Ps);
	Vs = Pt - Ps;
	for ( ic=0; ic<Pg.m_n; ic++) {
		Pe = Pg.m_p[ic];
		Ve = Pt - Pe;
		if ( Abs_2(Ve) <= rTol * rTol) {						// �_���I�_��(Pt == Pe)
			ist = MC_ON_TOP;
			MQUIT;
		}
		Vl = Pe - Ps;
		MREAL Ss = Vl ^ Vs;
		if ( ( Ss * Ss) <= (rTol * rTol * Abs_2(Vl))) {			// �_����ӂ܂ł̋�����rTol�ȓ�
			MREAL Cs = Vs * Vl;
			MREAL Ce = Ve * Vl;
			if (Cs >= 0.0f && Ce <= 0.0f) {						// �ӏ�
				if (vst) {
					if (*vst * Vl > 0.f) 
						ist = MC_ON_SIDE_SAME;					// �_���ӏ�(�������)
					else
						ist = MC_ON_SIDE_REV;					// �_���ӏ�(�t����)
				} else {
					ist = MC_ON_SIDE;							// �_���ӏ�(��������=NULL: ���������w�薳��)
				}
				MQUIT;
			}
		}
		
		iQe = Quadrant( Pt, Pe);
		iQse = iQe - iQs;

		if (Ss > 0.0f) {										// �_�������̍���
			if ( iQse < 0) iQse += 4;
		} else {												// �_�������̉E��
			if ( iQse > 0) iQse -= 4;
		}
		iQSum += iQse;
		
		Ps = Pe;
		iQs = iQe;
		Vs = Ve;
	}
	*ict = iQSum / 4;
	ist = 0;
exit:
	return ist;
}
//
// ---------------------( �R���� )------------------------------
//	�_�Ƒ��p�`�̈ʒu�֌W�����߂� �R�c
//
/*
bool MGeo::ChkPt3OnPg3WS(						// (  O) �X�e�C�^�X
												//			true:	���p�`�̓����܂��͕ӏ�
												//			false:	���p�`�̊O��
				const	MgPoint3&	Pt,			// (I  ) �_
				const	MgPolyg3&	Pg,			// (I  ) ���p�`
						MINT*		ist,		// (  O) �X�e�C�^�X
							  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
												//			MC_UPPER			(010): �_�����ʂ̏㑤	
												//			MC_ON_PLANE			(020): �_�����ʏ�
												//			MC_LOWER			(040): �_�����ʂ̉���
												//		 ���p�`�Ɠ_�̈ʒu�֌W
												//			MC_IN_BORDER		(001): �_�����p�`�̓���
												//			MC_ON_BORDER		(002): �_�����p�`�̕ӏ�
												//			MC_OUT_BORDER		(004): �_�����p�`�̊O��
						MREAL		rTol		// (I  ) �g�������X
				)
{
	MgPoint2 wPt;												// �_�̂Q�c��Ɨp
	MINT work[sizeof(MgPolyg2)+MX_LIN2*(sizeof(MgPoint2)-1)];	// �ő�\��������MX_LIN2��
	MgPolyg2 *wPg = (MgPolyg2*)work;							// ���p�`�p�Q�c��Ɨp�G���A���m��

	*ist = 0;
	
	MgPlane3 Pln = MgPgtoPln( Pg);								// ���p�`����镽��
	MREAL pa1 = (Pln.v * Pt) + Pln.d;							// �_���畽�ʂ܂ł̋���
	
	if (!(MgAbs_2( pa1) <= rTol * rTol)) {						// ���p�`�̕��ʏ�Ŗ����ꍇ�ɁA���p�`�̏㉺�𔻒肷��
		if (pa1 > 0) *ist = MC_UPPER;							// ���p�`�̍\���_���E�˂���]�Ƃ݂Ȃ��i�ޕ������㑤�Ƃ���
		else *ist = MC_LOWER;
		return	false;
	}
	MgMat3E mat = MgMat3EDto2D( Pln);
	Mg3Dto2D( Pt, mat, &wPt);
	Mg3Dto2D( Pg, mat, wPg);
	MgPolyg2 wPg1;
	bool bst = MgOnPtPg3( wPt, wPg1, ist);
	bst = MgOnPtPg3( wPt, *wPg, ist);
	*ist |= MC_ON_PLANE;
	return bst;
}
*/
//
// ---------------------( �R���� )------------------------------
//	�����̒��S�_�Ƒ��p�`�̈ʒu�֌W�����߂�
//
/*
bool MGeo::ChkLn3OnPg3WS(						// (  O) �X�e�C�^�X
												//			true:	���p�`��
												//			false:	���p�`�O
				const	MgLine3		&Ln1,		// (I  ) ����
				const	MgPolyg3&	Pg2,		// (I  ) ���p�`
						MINT*		ist,		// (  O) �⏕�X�e�C�^�X
							  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
												//			MC_UPPER			(010): �_�����ʂ̏㑤	
												//			MC_ON_PLANE			(020): �_�����ʏ�
												//			MC_LOWER			(040): �_�����ʂ̉���
												//       ���p�`�Ɠ_�̈ʒu�֌W
												//			MC_IN_BORDER		(001): �_�����p�`�̓���
												//			MC_ON_BORDER		(002): �_�����p�`�̕ӏ�
												//			MC_OUT_BORDER		(004): �_�����p�`�̊O��
						MREAL		rTol		// (I  ) �g�������X
		)
{
	MgPoint3	Pt1;
	Pt1 = ( Ln1.p[0] + Ln1.p[1]) * 0.5;
	return MgOnPtPg3( Pt1, Pg2, ist);
}
*/

////		���ʁ@�`�󉉎Z
////
//// ---------------------( �R���� )------------------------------
////
////	�_�����ʏ�ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkPt3OnPln3WS(						// (  O) �X�e�C�^�X
//												//			true:  ���ʏ�
//												//			false: ���ʊO
//				const	MgPoint3&	p1,			// (I  ) �_1
//				const	MgPlane3	&Pln2,		// (I  ) ����2
//						MINT*		ist,		// (  O) �⑫�X�e�C�^�X
//												//			MC_UPPER			(010): �_�����ʂ̏㑤	
//												//			MC_ON_PLANE			(020): �_�����ʏ�
//												//			MC_LOWER			(040): �_�����ʂ̉���
//						MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	bool	bst;
//	MREAL	pa1;								//	�_���畽�ʂ܂ł̋���
////
//	pa1 = (Pln2.v * p1) + Pln2.d;
//	if (pa1 > rTol) {
//		*ist = MC_UPPER;
//		bst = false;
//	} else if (pa1 < -rTol) {
//		*ist = MC_LOWER;
//		bst = false;
//	} else {
//		*ist = MC_ON_PLANE;
//		bst = true;
//	}
//	return bst;
//}

////
//// ---------------------( �R���� )------------------------------
////	���������ʏ�ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkULn3OnPln3(						// (  O) �X�e�C�^�X
//												//			true:  ���ʏ�
//												//			false: ���ʊO
//				const	MgULine3&	ULn1,		// (I  ) ����1
//				const	MgPlane3	&Pln2,		// (I  ) ����2
//						MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	int		ist;
//	if (MgChkPt3OnPln3WS(ULn1.p, Pln2, &ist)) {
////
////	���s�̃`�F�b�N
////
//		if (MgChkPerp2V3(ULn1.v, Pln2.v)) return true;	//	���ʏ�
//	}
//	return false;
//}

////
//// ---------------------( �R���� )------------------------------
////	���������ʏ�ɂ��邩�𒲂ׂ�B
////
//bool MGeo::ChkLn3OnPln3WS(						// (  O) �X�e�C�^�X
//												//			true:  ���ʏ�
//												//			false: ���ʊO
//				const	MgLine3		&Ln1,		// (I  ) ����1
//				const	MgPlane3	&Pln2,		// (I  ) ����2
//						MINT*		ist,		// (  O) �⑫�X�e�C�^�X
//							  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
//												//			MC_PS_UPPER			(001): �n�_�����ʂ̏㑤	
//												//			MC_PS_ON_PLANE		(002): �n�_�����ʏ�
//												//			MC_PS_LOWER			(004): �n�_�����ʂ̉���
//												//       ���p�`�Ɠ_�̈ʒu�֌W
//												//			MC_PE_UPPER			(010): �I�_�����ʂ̏㑤	
//												//			MC_PE_ON_PLANE		(020): �I�_�����ʏ�
//												//			MC_PE_LOWER			(040): �I�_�����ʂ̉���
//						MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	bool	bs, be;
//	MINT	ists, iste;
//
//	bs = MgChkPt3OnPln3WS(Ln1.p[0], Pln2, &ists);
//	be = MgChkPt3OnPln3WS(Ln1.p[1], Pln2, &iste);
//	*ist = (ists * MC_PS_UPPER + iste * MC_PE_UPPER)/ MC_UPPER;
//	return (bs && be);
//}

////
//// ---------------------( �Q���� )------------------------------
//// P1�����_�Ƃ���P2�̈ʒu�̏ی������߂�
////
//static MINT MGeo::Quadrant	(						// (  O) 1�`4: �ی�
//				const	MgPoint2&	p1,			// (I  ) P1
//				const	MgPoint2&	p2			// (I  ) P2
//		)
//{
//	return ((p2.x > p1.x) ? ((p2.y > p1.y) ? 1 : 4) : ((p2.y > p1.y) ? 2 : 3));
//}

} // namespace MC