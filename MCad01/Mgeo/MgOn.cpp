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
#include "MgGeo.h"

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"

namespace MC
{

//===========================================================================
//		�����@�`�󉉎Z

// ---------------------( �Q���� )------------------------------
//
//	�_��������ɂ��邩�𒲂ׂ�B
//
bool MGeo::CheckPointOnSLine2D(					// (  O) �X�e�C�^�X
												//		 	true:	������ɂ���
												//		 	false:	������ɂȂ�
				const	MgPoint2D&	i_p1,		// (I  ) �_1
				const	MgSLine2D&	i_SLn2,		// (I  ) ����2
						int*		o_pist		// (  O) �⏕�X�e�C�^�X
												//			MC_RIGHT			: �_�������̉E��
												//			MC_ON_SLINE			: �_��������
												//			MC_LEFT				: �_�������̍���
				)
{
	bool		bst;							// �X�e�C�^�X
	int			ist;							// �⏕�X�e�C�^�X
	MgVect2D	v2s1;							// ����2�̎n�_����_1�܂ł̃x�N�g��
	MREAL		pa1;							// ����2����_1�܂ł̉�������

	// ����2�̕����i�P�ʃx�N�g���j�ƒ���2�̎n�_����_1�܂ł̃x�N�g���̊O�ς�艔�����������߂�
	v2s1 = i_p1 - i_SLn2.p;					
	pa1 = i_SLn2.v ^ v2s1;						// ����2�̕����i�P�ʃx�N�g���j�ƒ���2�̎n�_����_1�܂ł̃x�N�g���̊O��

	// �����������덷���Ȃ璼����
	if ( CheckZero(pa1)) {
		ist = MC_ON_SLINE;
		bst = true;

	// �������������Ȃ璼���̍���
	} else if ( pa1 > 0) {
		ist = MC_LEFT;
		bst = false;

	// �������������Ȃ璼���̉E��
	} else {
		ist = MC_RIGHT;
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}
	
// ---------------------( �Q���� )------------------------------
//
//	�_����������ɂ��邩�𒲂ׂ�B
//
bool  MGeo::CheckPointOnHLine2D(				// (  O) �X�e�C�^�X
												//		 	true:	��������ɂ���
												//		 	false:	��������ɂȂ�
				const	MgPoint2D&	i_p1,		// (I  ) �_1
				const	MgHLine2D&	i_HLn2,		// (I  ) ������2
						MINT*		o_pist		// (  O) �⏕�X�e�C�^�X
												//		 �X�e�C�^�X1
												//			MC_RIGHT			: �_���������̉E��
												//			MC_ON_SLINE			: �_���������̉���������
												//			MC_LEFT				: �_���������̍���
												//		 �X�e�C�^�X2
												//			MC_INSIDE			: �_���������̓���(�n�_����������)
												//			MC_ON_PS			: �_���������̎n�_��
												//			MC_OUT_PS			: �_���������̎n�_����������
				)
{
	bool		bst;							// �X�e�C�^�X
	int			ist;							// �⏕�X�e�C�^�X
	MgVect2D	v2s1;							// ������2�̎n�_����_1�܂ł̃x�N�g��
	MREAL		rl21;							// ������2����_1�܂ł̉�������

	// ������2�̕����i�P�ʃx�N�g���j�Ɣ�����2�̎n�_����_1�܂ł̃x�N�g���̊O�ς�艔�����������߂�
	v2s1 = i_p1 - i_HLn2.p;					
	rl21 = i_HLn2.v ^ v2s1;						// ������2�̕����i�P�ʃx�N�g���j�Ɣ�����2�̎n�_����_1�܂ł̃x�N�g���̊O��

	// �����������덷���Ȃ璼����
	if ( CheckZero( rl21)) {
		if ( v2s1 * v2s1 <= MGPTOL->D_2) {
			ist = MC_ON_PS;
			bst = true;
		} else if ( v2s1 * i_HLn2.v > 0) {
			ist = MC_INSIDE;
			bst = true;
		} else {
			ist = MC_OUT_PS;
			bst = false;
		}
		ist |= MC_ON_SLINE;

	// �������������Ȃ璼���̍���
	} else if ( rl21 > 0) {
		ist = MC_LEFT;
		bst = false;

	// �������������Ȃ璼���̉E��
	} else {
		ist = MC_RIGHT;
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

// ---------------------( �Q���� )------------------------------
//
//	�_��������ɂ��邩�𒲂ׂ�B
//
bool MGeo::CheckPointOnLine2D(					// (  O) �X�e�C�^�X
												//			true:	������ɂ���
												//			false:	������ɂȂ�
				const	MgPoint2D&	p1,			// (I  ) �_1
				const	MgLine2D&	Ln2,		// (I  ) ����2
						MINT*		o_pist		// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
												//		 �X�e�C�^�X1
												//			MC_RIGHT			: �_�������̉E��
												//			MC_ON_SLINE			: �_����������������
												//			MC_LEFT				: �_�������̍���
												//		 �X�e�C�^�X2
												//			MC_ON_PS			: �_�������̎n�_��
												//			MC_INSIDE			: �_�������̓�����
												//			MC_ON_PE			: �_�������̏I�_��
												//			MC_OUT_PS			: �_�������̎n�_����������
												//			MC_OUT_PE			: �_�������̏I�_����������
		)
{
	bool		bst;
	int			ist;							// �⏕�X�e�C�^�X
	MgVect2D	v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect2D	v2e1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect2D	v2;								// ����2�̎n�_����I�_�ւ̃x�N�g��
	MREAL		pa1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O��
	MREAL		cs, ce;							// ����2�Ɛ���2�̎n�_�C�I�_����_1�ւ̃x�N�g���̓���
	MREAL		tol_2;							// ����p�덷
	MREAL		v2tol_2;						// ����p�덷

	v2s1 = p1 - Ln2.p[0];
	v2e1 = p1 - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// �_��������܂ł̉�������( abs( pa1)/abs( v2)) <= tol ��蒼����ł��邩�𒲂�
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	// ������Ȃ�A����ɐ�����ł��邩�𒲂ׂ�
	tol_2 = MGPTOL->D_2;
	v2tol_2 = tol_2 * SqLenVect2D( v2);
	if ( pa1 * pa1 <= v2tol_2) { 								// �_��������܂ł̉���������rTol�ȓ�
		// ����������
		cs = v2 * v2s1;
		ce = v2 * v2e1;
		ist = 0;
		bst = true;
		if (v2s1 * v2s1 <= tol_2) {
			ist = MC_ON_PS;										// �_�������̎n�_��
		} else if ( v2e1 * v2e1 <= tol_2) {
			ist = MC_ON_PE;										// �_�������̏I�_��
		} else if ( cs > 0 &&  ce < 0) {
			ist = MC_INSIDE;									// �_�������̓�����
		} else {
			if ( cs > 0) {
				ist = MC_OUT_PE;
			} else {
				ist = MC_OUT_PS;
			}
			bst = false;
		}
		ist |= MC_ON_SLINE;
	} else {
		// ����������łȂ��Ȃ�A�����̍��E�ǂ���ɂ��邩�𒲂ׂ�
		if ( pa1 > 0) {
			ist = MC_LEFT;										// ����
		} else {
			ist = MC_RIGHT;										// �E��
		}
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

// ---------------------( �Q���� )------------------------------
//
//	�����Ɛ������d�Ȃ��Ă��邩�𒲂ׂ�B
//
bool MGeo::CheckLineOnLine2D(					// (  O) �X�e�C�^�X
												//			true:	�d�Ȃ��Ă���
												//			false:	�d�Ȃ��Ă��Ȃ�
				const	MgLine2D&	Ln1,		// (I  ) ����1
				const	MgLine2D&	Ln2			// (I  ) ����2
		)
{
	bool		bst = false;
	MgVect2D	v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
//	MgVect2D	v2e1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect2D	v2;								// ����2�̎n�_����I�_�ւ̃x�N�g��
	MREAL		pa1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O��
	MREAL		v2tol_2;						// ����p�덷
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;

	if (!MGeo::ParallelLine2D( Ln1, Ln2))						// ���s�łȂ��ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	v2s1 = Ln1.p[0] - Ln2.p[0];
//	v2e1 = Ln1.p[0] - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// ����1�̎n�_�������2�܂ł̉�������( abs( pa1)/abs( v2)) <= tol ��蒼����ł��邩�𒲂ׂ�
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	cs22 = v2 * v2;
	v2tol_2 = MGPTOL->D_2 * cs22;
	if ( pa1 * pa1 > v2tol_2) 									// �_��������܂ł̉���������rTol���̏ꍇ��
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

// ---------------------( �R���� )------------------------------
//
//	�_����������ɂ��邩�𒲂ׂ�B
//
bool MGeo::CheckPointOnHLine3D(					// (  O) �X�e�C�^�X
												//			true:	������ɂ���
												//			false:	������ɂȂ�
				const	MgPoint3D&	i_p1,		// (I  ) �_1
				const	MgHLine3D&	i_HLn2,		// (I  ) ������2
						int*		o_pist		// (  O) �⏕�X�e�C�^�X
												//		 �X�e�C�^�X1
												//			MC_ON_SLINE			: �_���������̉���������
												//		 �X�e�C�^�X2
												//			MC_INSIDE			: �_���������̓���(�n�_����������)
												//			MC_ON_PS			: �_���������̎n�_��
												//			MC_OUT_PS			: �_���������̎n�_����������
				)
{
	bool		bst;							// �X�e�C�^�X
	int			ist;							// �⏕�X�e�C�^�X
	MgVect3D	v2s1;							// ������2�̎n�_����_1�܂ł̃x�N�g��
	MgVect3D	v21;							// ������2�̎n�_����_1�܂ł̐����x�N�g��
	MREAL		rl21_2;							// ������2����_1�܂ł̉��������̂Q��

	// ������2�̕����i�P�ʃx�N�g���j�Ɣ�����2�̎n�_����_1�܂ł̃x�N�g���̊O�ς�艔�����������߂�
	v2s1 = i_p1 - i_HLn2.p;					
	v21 = i_HLn2.v ^ v2s1;						// ������2�̕����i�P�ʃx�N�g���j�Ɣ�����2�̎n�_����_1�܂ł̃x�N�g���̊O��
	rl21_2 = v21 * v21;

	if ( rl21_2 <= MGPTOL->D_2) {
		if ( v2s1 * v2s1 <= MGPTOL->D_2) {
			ist = MC_ON_PS;
			bst = true;
		} else if ( v2s1 * i_HLn2.v > 0) {
			ist = MC_INSIDE;
			bst = true;
		} else {
			ist = MC_OUT_PS;
			bst = false;
		}
		ist |= MC_ON_SLINE;

	} else {
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

// ---------------------( �R���� )------------------------------
//
//	�_��������ɂ��邩�𒲂ׂ�B
//
bool MGeo::CheckPointOnLine3D(					// (  O) �X�e�C�^�X
												//			true:	������ɂ���
												//			false:	������ɂȂ�
				const	MgPoint3D&	p1,			// (I  ) �_1
				const	MgLine3D	&Ln2,		// (I  ) ����2
						int*		o_pist		// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
												//		 �X�e�C�^�X1
												//			MC_ON_SLINE			: �_����������������
												//		 �X�e�C�^�X2
												//			MC_ON_PS			: �_�������̎n�_��
												//			MC_INSIDE			: �_�������̓�����
												//			MC_ON_PE			: �_�������̏I�_��
												//			MC_OUT_PS			: �_�������̎n�_����������
												//			MC_OUT_PE			: �_�������̏I�_����������
		)
{
	bool		bst;
	int			ist;							// �⏕�X�e�C�^�X
	MgVect3D	v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect3D	v2e1;							// ����2�̏I�_����_1�ւ̃x�N�g��
	MgVect3D	v2;								// ����2�̎n�_����I�_�ւ̃x�N�g��
	MgVect3D	va1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O�� 
	MREAL		cs, ce;
	MREAL		tol_2;							// ����p�덷
	MREAL		v2tol_2;						// ����p�덷
	MREAL		v2tol_2_1;						// ����p�덷 v2tol_2/10000

	v2s1 = p1 - Ln2.p[0];
	v2e1 = p1 - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	va1 = v2 ^ v2s1;
	//
	// �_��������܂ł̉�������( abs( va1)/abs( v2)) <= tol ��蒼����ł��邩�𒲂�
	//						 ( (va1 * va1) <= tol * tol * (v2 * v2))
	// ������Ȃ�A����ɐ�����ł��邩�𒲂ׂ�
	tol_2 = MGPTOL->D_2;
	v2tol_2 = tol_2 * SqLenVect3D( v2);
	v2tol_2_1 = tol_2 * SqLenVect3D( v2) * 0.0001f * 0.0001f;
	ist = 0;
	if ( SqLenVect3D( va1) <= v2tol_2) { 						// �_��������܂ł̉���������rTol�ȓ�
		cs = v2 * v2s1;
		ce = v2 * v2e1;
		bst = true;
		if (v2s1 * v2s1 <= tol_2) {
			ist = MC_ON_PS;										// �_�������̎n�_��
		} else if ( v2e1 * v2e1 <= v2tol_2) {
			ist = MC_ON_PE;										// �_�������̏I�_��
		} else if ( cs > 0 &&  ce < 0) {
			ist = MC_INSIDE;									// �_�������̓�����
		} else {
			if ( cs > 0) {
				ist = MC_OUT_PE;
			} else {
				ist = MC_OUT_PS;
			}
			bst = false;
		}
		ist |= MC_ON_SLINE;
	} else {
		bst = false;
	}
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

// ---------------------( �R���� )------------------------------
//
//	�����Ɛ������d�Ȃ��Ă��邩�𒲂ׂ�B
//
bool MGeo::CheckLineOnLine3D(					// (  O) �X�e�C�^�X
												//			true:	�d�Ȃ��Ă���
												//			false:	�d�Ȃ��Ă��Ȃ�
				const	MgLine3D		&Ln1,	// (I  ) ����1
				const	MgLine3D		&Ln2	// (I  ) ����2
		)
{
	bool		bst = false;
	MgVect3D	v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
//	MgVect3D	v2e1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect3D	v2;								// ����2�̎n�_����I�_�ւ̃x�N�g��
	MgVect3D	pa1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O��
	MREAL		v2tol_2;						// ����p�덷
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;

	if (!MGeo::ParallelLine3D( Ln1, Ln2))						// ���s�łȂ��ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	v2s1 = Ln1.p[0] - Ln2.p[0];
//	v2e1 = Ln1.p[0] - Ln2.p[1];
	v2 = Ln2.p[1] - Ln2.p[0];
	pa1 = v2 ^ v2s1;
	//
	// ����1�̎n�_�������2�܂ł̉�������( abs( pa1)/abs( v2)) <= tol ��蒼����ł��邩�𒲂ׂ�
	//						 ( pa1 * pa1 <= tol * tol * (v2 * v2))
	cs22 = v2 * v2;
	v2tol_2 = MGPTOL->D_2 * cs22;
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
bool MGeo::CheckLineOnLine3DWS(					// (  O) �X�e�C�^�X
												//			true:	�d�Ȃ��Ă���
												//			false:	�d�Ȃ��Ă��Ȃ�
				const	MgLine3D	&Ln1,		// (I  ) ����1
				const	MgLine3D	&Ln2,		// (I  ) ����2
						MINT*		o_pist		// (  O) �⏕�X�e�C�^�X�@�d�Ȃ肠��̏ꍇ�͎��̒ʂ�
												//        -4    -3   -2   -1    0     1    2    3    4 		   	
												//		|--   |--  |--- | -- | --- |----| ---|  --|   --|           	  	
												//		|   --|  --| ---|----| --- | -- |--- |--  |--   |                �@	
				)
{
	bool		bst = false;
	int			ist;							// �⏕�X�e�C�^�X
	MREAL		rTol;
	MgVect3D	v2s1;							// ����2�̎n�_����_1�ւ̃x�N�g��
	MgVect3D	v2, vu2;						// ����2�̎n�_����I�_�ւ̃x�N�g���A���P�ʃx�N�g��
	MgVect3D	pa1;							// ����2�Ɛ���2�̎n�_����_1�ւ̃x�N�g���̊O��
	MREAL		cs11, cs12, cs21, cs22;
	MREAL		d1, d2, dd;
	MREAL		d11, d12, d21, d22;

	ist = 0;
	rTol = MGPTOL->D;
	if (!MGeo::ParallelLine3D( Ln1, Ln2))						// ���s�łȂ��ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���
	v2s1 = Ln1.p[0] - Ln2.p[0];
	v2 = Ln2.p[1] - Ln2.p[0];
	vu2 = v2.Unitize();
	pa1 = vu2 ^ v2s1;
	//
	// ����1�̎n�_�������2�܂ł̉������� abs( pa1) <= tol ��蒼����ł��邩�𒲂ׂ�
	//						 ( pa1 * pa1 <= tol * tol)
	if ( SqLenVect3D( pa1) > MGPTOL->D_2)						// �_��������܂ł̉���������rTol���̏ꍇ��
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
				ist = 4;
			else
				ist = 3;
		} else {
			if (d11 > d21 + rTol)
				ist = 2;
			else
				ist = 1;
		}
	} else if (d11 < d21 - rTol) {
		if (d12 < d21 + rTol) {
			if (d12 < d21 - rTol)
				ist = -4;
			else
				ist = -3;
		} else {
			if (d12 < d22 - rTol)
				ist = -2;
			else
				ist = 1;
		}
	} else if (d12 > d22 - rTol && d11 < d21 + rTol)
		ist = 0;
	else
		ist = -1;

	dd = d2 - d1;
	// �d�Ȃ�̎n�_����I�_�܂ł̋���( dd/abs( v2)) <= tol ���d�Ȃ��Ă��Ȃ����𒲂ׂ�
	//						 ( dd * dd <= tol * tol * (v2 * v2))
	if (dd < 0. || (dd * dd) <= MGPTOL->D_2)					// �d�Ȃ肪rTol�ȉ��̏ꍇ��
		MQUIT;													// �d�Ȃ��Ă��Ȃ��Ƃ���

	bst = true;
exit:
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

//
// ---------------------( �Q���� )------------------------------
//	�_�ƌ��t�����p�`�̈ʒu�֌W�����߂�
//
bool MGeo::CheckPointOnGPolygon2DWS(			// (  O) �X�e�C�^�X
												//			true:	���t�����p�`�̓����܂��͕ӏ�
												//			false:	���t�����p�`�̊O��
				const	MgPoint2D&	i_pt,		// (I  ) �_
				const	MgGPolyg2D&	i_Gpg,		// (I  ) ���t�����p�`
						int*		o_pist		// (  O) �X�e�C�^�X
												//			MC_IN_BORDER		: �_�����t�����p�`�̓���
												//			MC_ON_BORDER		: �_�����t�����p�`�̕ӏ�(�܂��͒��_��)
												//			MC_OUT_BORDER		: �_�����t�����p�`�̊O��
		)
{
	bool		bst;
	int			ist;							// �⏕�X�e�C�^�X
	MINT		ist1;
	MINT		ic1;
	MINT		ict, ictSum;
	MgPolyg2D*	pPg;
	
	ictSum = 0;													// ���O����p�J�E���^
	for ( ic1=0; ic1<i_Gpg.m_n; ic1++) {
		pPg = &(i_Gpg.m_pg[ic1]);

		
		ist1 = CountPolygonAroundPoint2D( i_pt, NULL, *pPg, &ict);
		if ( ist1) {
			ist = MC_ON_BORDER;
			bst = true;											// ���t�����p�`�̕ӏ�(�܂��͒��_��)
			MQUIT;
		}
		ictSum += ict;
	}

	if ( ictSum > 0) {
		ist = MC_IN_BORDER;										// ���t�����p�`�̓���
		bst = true;
	} else {
		ist = MC_OUT_BORDER;									// ���t�����p�`�̊O��
		bst = false;
	}
exit:
	if ( o_pist)
		*o_pist = ist;
	return bst;
}

//
// ---------------------( �Q���� )------------------------------
//	�����̒��S�_�ƌ��t�����p�`�̈ʒu�֌W�����߂�
//
bool MGeo::CheckLineOnGPolygon2DWS(				// (  O) �X�e�C�^�X
												//			true:	���t�����p�`�̓����܂��͕ӏ�
												//			false:	���t�����p�`�̊O��
				const	MgLine2D&	Ln1,		// (I  ) ����
				const	MgGPolyg2D&	GPg2,		// (I  ) ���t�����p�`
						int*		o_pist		// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
												// 		 �e�C�^�X1
												//			MC_IN_BORDER		: �_�����t�����p�`�̓���
												//			MC_ON_BORDER		: �_�����t�����p�`�̕ӏ�(�܂��͒��_��)
												//			MC_OUT_BORDER		: �_�����t�����p�`�̊O��
												// 		 �e�C�^�X2
												//			MC_ON_SIDE_SAME		: �ӏ�(�������)	(MC_ON_BORDER�Ƌ��ɐݒ�)
												//			MC_ON_SIDE_REV		: �ӏ�(�t����)		(MC_ON_BORDER�Ƌ��ɐݒ�)
												//			MC_ON_TOP			: ���_��			(MC_ON_BORDER�Ƌ��ɐݒ�)
				)
{
	bool		bst;
	int			ist;							// �⏕�X�e�C�^�X
	MgPoint2D	pt1;
	MgVect2D	vt1;
	MINT		ist1;
	MINT		ic1;
	MINT		ict, ictSum = 0;								// ���O����p�J�E���^
	MgPolyg2D*	pPg;
	
	pt1 = ( Ln1.p[0] + Ln1.p[1]) * 0.5;
	vt1 = Ln1.p[1] - Ln1.p[0];
	
	for ( ic1=0; ic1<GPg2.m_n; ic1++) {
		pPg = &(GPg2.m_pg[ic1]);
		
		ist1 = CountPolygonAroundPoint2D( pt1, &vt1, *pPg, &ict);
		if ( ist1) {
			ist = MC_ON_BORDER | ist1;
			bst = true;											// ���t�����p�`�̕ӏ�(�܂��͒��_��)
			MQUIT;
		}
		ictSum += ict;
	}

	if ( ictSum > 0) {
		ist = MC_IN_BORDER;										// ���t�����p�`�̓���
		bst = true;
	} else {
		ist = MC_OUT_BORDER;									// ���t�����p�`�̊O��
		bst = false;
	}
exit:
	if ( o_pist)
		*o_pist = ist;
	return bst;
}
//
// ---------------------( �Q���� )------------------------------
// �_�Ƒ��p�`�̈ʒu�֌W�����߂�
// ���p�`�̕ӂ��_�̎���������񐔂����߂�i���̈��:1�@�����:-1�j
MINT MGeo::CountPolygonAroundPoint2D(			// (  O) �X�e�C�^�X
												//			(000)				: ���p�`�̒��܂��͊O	
												//			MC_ON_SIDE_SAME		: �ӏ�(�������)
												//			MC_ON_SIDE_REV		: �ӏ�(�t����)
												//			MC_ON_SIDE			: �ӏ�(��������=NULL: ���������w�薳��)
												//			MC_ON_TOP			: ���_��
				const	MgPoint2D&	Pt,			// (I  ) �_
				const	MgVect2D	*vst,		// (I  ) �������� �܂��� NULL
												//		 ������NULL�Ŗ�����Γ_���ӏ�̏ꍇ�A
												//		 �ӂ̐��������Ɣ�r����
				const	MgPolyg2D&	Pg,			// (I  ) ���p�`
						MINT*		ict			// (  O) ����J�E���g
												//			>0: ���p�`�����̂̏ꍇ�̎���	(1:1��)
												//			=0: ���_�A�ӏ�A���p�`�̊O
												//			<0: ���p�`�����̏ꍇ�̎���	(-1:1��)	
				)
{
	MINT		ist;
	MINT		ic;
	MgPoint2D	Ps, Pe;
	MgVect2D		Vs, Ve;
	MgVect2D		Vl;
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
		if ( SqLenVect2D( Ve) <= MGPTOL->D_2) {					// �_���I�_��(Pt == Pe)
			ist = MC_ON_TOP;
			MQUIT;
		}
		Vl = Pe - Ps;
		MREAL Ss = Vl ^ Vs;
		if ( ( Ss * Ss) <= ( MGPTOL->D_2 * SqLenVect2D( Vl))) {	// �_����ӂ܂ł̋�����rTol�ȓ�
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
bool MGeo::CheckPt3OnPg3WS(						// (  O) �X�e�C�^�X
												//			true:	���p�`�̓����܂��͕ӏ�
												//			false:	���p�`�̊O��
				const	MgPoint3D&	Pt,			// (I  ) �_
				const	MgPolyg3D&	Pg,			// (I  ) ���p�`
						MINT*		ist,		// (  O) �X�e�C�^�X
							  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
												//			MC_UPPER			: �_�����ʂ̏㑤	
												//			MC_ON_PLANE			: �_�����ʏ�
												//			MC_LOWER			: �_�����ʂ̉���
												//		 ���p�`�Ɠ_�̈ʒu�֌W
												//			MC_IN_BORDER		: �_�����p�`�̓���
												//			MC_ON_BORDER		: �_�����p�`�̕ӏ�
												//			MC_OUT_BORDER		: �_�����p�`�̊O��
//SS					MREAL		rTol		// (I  ) �g�������X
				)
{
	MgPoint2D wPt;												// �_�̂Q�c��Ɨp
	MINT work[sizeof(MgPolyg2D)+MX_LIN2*(sizeof(MgPoint2D)-1)];	// �ő�\��������MX_LIN2��
	MgPolyg2D *wPg = (MgPolyg2D*)work;							// ���p�`�p�Q�c��Ɨp�G���A���m��

	*ist = 0;
	
	MgPlane3D Pln = MgPgtoPln( Pg);								// ���p�`����镽��
	MREAL pa1 = (Pln.v * Pt) + Pln.d;							// �_���畽�ʂ܂ł̋���
	
	if (!(MgAbs_2( pa1) <= Geo::D_2)) {							// ���p�`�̕��ʏ�Ŗ����ꍇ�ɁA���p�`�̏㉺�𔻒肷��
		if ( pa1 > 0) *ist = MC_UPPER;							// ���p�`�̍\���_���E�˂���]�Ƃ݂Ȃ��i�ޕ������㑤�Ƃ���
		else *ist = MC_LOWER;
		return	false;
	}
	MgMat3E mat = MgMat3EDto2D( Pln);
	Mg3Dto2D( Pt, mat, &wPt);
	Mg3Dto2D( Pg, mat, wPg);
	MgPolyg2D wPg1;
	bool bst = MgOnPtPolygon3D( wPt, wPg1, ist);
	bst = MgOnPtPolygon3D( wPt, *wPg, ist);
	*ist |= MC_ON_PLANE;
	return bst;
}
*/
//
// ---------------------( �R���� )------------------------------
//	�����̒��S�_�Ƒ��p�`�̈ʒu�֌W�����߂�
//
/*
bool MGeo::CheckLn3OnPg3WS(						// (  O) �X�e�C�^�X
												//			true:	���p�`��
												//			false:	���p�`�O
				const	MgLine3D	&Ln1,		// (I  ) ����
				const	MgPolyg3D&	Pg2,		// (I  ) ���p�`
						MINT*		ist			// (  O) �⏕�X�e�C�^�X
							  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
												//			MC_UPPER			: �_�����ʂ̏㑤	
												//			MC_ON_PLANE			: �_�����ʏ�
												//			MC_LOWER			: �_�����ʂ̉���
												//       ���p�`�Ɠ_�̈ʒu�֌W
												//			MC_IN_BORDER		: �_�����p�`�̓���
												//			MC_ON_BORDER		: �_�����p�`�̕ӏ�
												//			MC_OUT_BORDER		: �_�����p�`�̊O��
		)
{
	MgPoint3D	Pt1;
	Pt1 = ( Ln1.p[0] + Ln1.p[1]) * 0.5;
	return MgOnPtPolygon3D( Pt1, Pg2, ist);
}
*/

////		���ʁ@�`�󉉎Z
////
//// ---------------------( �R���� )------------------------------
////
////	�_�����ʏ�ɂ��邩�𒲂ׂ�B
////
//bool MGeo::CheckPt3OnPln3WS(					// (  O) �X�e�C�^�X
//												//			true:  ���ʏ�
//												//			false: ���ʊO
//				const	MgPoint3D&	p1,			// (I  ) �_1
//				const	MgPlane3D	&Pln2,		// (I  ) ����2
//						MINT*		ist			// (  O) �⑫�X�e�C�^�X
//												//			MC_UPPER			: �_�����ʂ̏㑤	
//												//			MC_ON_PLANE			: �_�����ʏ�
//												//			MC_LOWER			: �_�����ʂ̉���
//SS //					MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	bool	bst;
//	MREAL	pa1;								//	�_���畽�ʂ܂ł̋���
////
//	pa1 = (Pln2.v * p1) + Pln2.d;
//	if ( pa1 > rTol) {
//		*ist = MC_UPPER;
//		bst = false;
//	} else if ( pa1 < -rTol) {
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
//bool MGeo::CheckSLn3OnPln3D(					// (  O) �X�e�C�^�X
//												//			true:  ���ʏ�
//												//			false: ���ʊO
//				const	MgSLine3D&	SLn1,		// (I  ) ����1
//				const	MgPlane3D	&Pln2		// (I  ) ����2
//SS //					MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	int		ist;
//	if (MgCheckPt3OnPln3WS(SLn1.p, Pln2, &ist)) {
////
////	���s�̃`�F�b�N
////
//		if (MgCheckPerp2V3(SLn1.v, Pln2.v)) return true;	//	���ʏ�
//	}
//	return false;
//}

////
//// ---------------------( �R���� )------------------------------
////	���������ʏ�ɂ��邩�𒲂ׂ�B
////
//bool MGeo::CheckLn3OnPln3WS(					// (  O) �X�e�C�^�X
//												//			true:  ���ʏ�
//												//			false: ���ʊO
//				const	MgLine3D	&Ln1,		// (I  ) ����1
//				const	MgPlane3D	&Pln2,		// (I  ) ����2
//						MINT*		ist			// (  O) �⑫�X�e�C�^�X
//							  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
//												//			MC_PS_UPPER			: �n�_�����ʂ̏㑤	
//												//			MC_PS_ON_PLANE		: �n�_�����ʏ�
//												//			MC_PS_LOWER			: �n�_�����ʂ̉���
//												//       ���p�`�Ɠ_�̈ʒu�֌W
//												//			MC_PE_UPPER			: �I�_�����ʂ̏㑤	
//												//			MC_PE_ON_PLANE		: �I�_�����ʏ�
//												//			MC_PE_LOWER			: �I�_�����ʂ̉���
//SS //					MREAL		rTol		// (I  ) �g�������X
//		)
//{
//	bool	bs, be;
//	MINT	ists, iste;
//
//	bs = MgCheckPt3OnPln3WS(Ln1.p[0], Pln2, &ists);
//	be = MgCheckPt3OnPln3WS(Ln1.p[1], Pln2, &iste);
//	*ist = (ists * MC_PS_UPPER + iste * MC_PE_UPPER)/ MC_UPPER;
//	return (bs && be);
//}

////
//// ---------------------( �Q���� )------------------------------
//// P1�����_�Ƃ���P2�̈ʒu�̏ی������߂�
////
//static MINT MGeo::Quadrant	(				// (  O) 1�`4: �ی�
//				const	MgPoint2D&	p1,			// (I  ) P1
//				const	MgPoint2D&	p2			// (I  ) P2
//		)
//{
//	return ((p2.x > p1.x) ? ((p2.y > p1.y) ? 1 : 4) : ((p2.y > p1.y) ? 2 : 3));
//}

} // namespace MC
