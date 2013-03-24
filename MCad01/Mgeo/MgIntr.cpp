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

//
//===========================================================================
//		�����ƒ����̌�_�@�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//�@�Q�{�̒����̌�_�����߂�B
//
MINT MGeo::Intr2ULn2(							// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MgULine2&	ULn1,		// (I  ) ����1
				const	MgULine2&	ULn2,		// (I  ) ����2
						MgPoint2*	po			// (  O) �Q������_
				)
{
	MINT	ist;
	MREAL	so;									// �P�ʃx�N�g���̊O��
	MREAL	pa1;								// ����1�̎n�_�����_�܂ł̋���
//
//	���s�̃`�F�b�N
//
	so = ULn1.v ^ ULn2.v;										// sin��v1v2
	if ( Zero( so, g_gTol.A)) {
		ist = MC_PARALLEL;										// ���s
	} else {
		pa1 = (ULn2.p - ULn1.p) ^ ULn2.v / so;					// sin��v12v2 / sin��v1v2
		*po = ULn1.p + pa1 * ULn1.v;
		ist = MC_INT;
	}
	return ist;
}

// ---------------------( �Q���� )------------------------------
//�@�����Ɛ����̌�_�����߂�B
//�@�d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�Ƃ݂Ȃ��B
//
MINT MGeo::IntrULnLn2(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MgULine2&	ULn1,		// (I  ) ����1
				const	MgLine2&	Ln2,		// (I  ) ����2
						MgPoint2*	po			// (  O) �Q������_
				)
{
	MINT	ist;
	MgVect2	vd2;
	MREAL	ss, se;
//
//�@���s�̃`�F�b�N
//
	vd2 = Ln2.p[1] - Ln2.p[0];
	if (MGeo::Parallel(ULn1.v, vd2)) {
		ist = MC_PARALLEL;										// ���s
	} else {
//
		SVal(Ln2.p[0], Ln2.p[1], ULn1.p, ULn1.v, &ss, &se);
//
		*po = Ln2.p[0] + (vd2 * (ss / (ss - se)));				// ��_
//
		if (ss * se < 0 || *po == Ln2.p[0]						// ������
						|| *po == Ln2.p[1]) {
			ist = MC_INT;
		} else {
			ist = MC_NINT;										// �����̊O
		}
	}
	return ist;
}

// ---------------------( �Q���� )------------------------------
//�@�����ƒ����̌�_�����߂�B
//�@�d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�Ƃ݂Ȃ��B
//
//					<< �R�[�f�B���O���̂�MgLib.h�ɂ��� >>
//
// MINT	MgIntrLnULn2(							// (  O) �X�e�C�^�X
//												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
//												//	MC_NINT	    (0)	�����Ȃ�
//												//	MC_INT      (1)	��������
//				const	MgLine2&	Ln1,		// (I  ) ����1
//				const	MgULine2&	ULn2,		// (I  ) ����2
//						MgPoint2*	po			// (  O) �Q������_
//				)
//{
//	return MgIntr(ULn2, Ln1, po);
// }
// ---------------------( �Q���� )------------------------------
//�@�����Ɛ����̌�_�����߂�B
//�@�Q�������d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�Ƃ݂Ȃ��B
//  �Q�������d�Ȃ�Ȃ������I�ɒ[���Őڍ����Ă���ꍇ�͂��̐ڍ��_����_�Ƃ݂Ȃ��B
MINT MGeo::Intr2Ln2(							// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//  MC_CONNECTION(4) �ڑ�	 �i���s�j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MgLine2&	Ln1,		// (I  ) ����1
				const	MgLine2&	Ln2,		// (I  ) ����2
				MgPoint2			*po			// (  O) �Q������_
				)
{
	MINT		ist;
	MREAL		so, si;
	MgVect2		vd1, vd2;
	MREAL		ss1, se1;
	MREAL		ss2, se2;
//
//	���s�̃`�F�b�N
//
	vd1 = Ln1.p[1] - Ln1.p[0];
	vd2 = Ln2.p[1] - Ln2.p[0];
	if (MGeo::Parallel(vd1, vd2, &so, &si)) {
		if (Ln1.p[0] == Ln2.p[0] && si < 0 ||
			Ln1.p[0] == Ln2.p[1] && si > 0) {
			*po = Ln1.p[0];
			ist = MC_CONNECTION;								// ���s�@����1�̎n�_�Ɛ���2�̒[�_���ߓ_
		} else if (Ln1.p[1] == Ln2.p[0] && si > 0 ||
				   Ln1.p[1] == Ln2.p[1] && si < 0) {
			*po = Ln1.p[1];
			ist = MC_CONNECTION;								// ���s�@����1�̏I�_�Ɛ���2�̒[�_���ߓ_
		} else {
			ist = MC_PARALLEL;									// ���s
		}
	} else {
		SVal(Ln1.p[0], Ln1.p[1], Ln2.p[0], vd2, &ss1, &se1);
		SVal(Ln2.p[0], Ln2.p[1], Ln1.p[0], vd1, &ss2, &se2);
//
		*po = Ln1.p[0] + (vd1 * (ss1 / (ss1 - se1)));			// ��_
//
		if ((ss1 * se1 < 0 ||									// ������
			 *po == Ln1.p[0] || *po == Ln1.p[1]) &&
			(ss2 * se2 < 0 ||
			 *po == Ln2.p[0] || *po == Ln2.p[1])) {
			ist = MC_INT;
		} else {
			ist = MC_NINT;										// �����̊O
		}
	}
	return ist;
}

// ---------------------( �Q���� )------------------------------
//	�����P�ƒ����Q�Ƃ̌�_�����߁A�_�Q�ɒǉ�����B
//�@�d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�Ƃ݂Ȃ��B
//
MINT MGeo::IntrAddLnULn2(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MgLine2&	Ln1,		// (I  ) ����1
				const	MgULine2&	ULn2,		// (I  ) ����2
						MgGPoint2	*GPt3		// (I O) ��_��ǉ�����_�Q
												//		 �ǉ���_��(0:�����Ȃ��A�����̒[���Ō����A�܂��͏d�Ȃ�
												//					1:��������i�����̒[���ł̌����͊܂܂�))
				)
{
	MINT		ist;
	MgVect2		vd1, vd2;
	MgPoint2	po;
	MREAL		ss, se;
//
//	���s�̃`�F�b�N
//
	vd1 = Ln1.p[1] - Ln1.p[0];
	if (MGeo::Parallel(vd1, ULn2.v)) {								// ���s
		ist = MC_PARALLEL;
	} else {
		SVal(Ln1.p[0], Ln1.p[1], ULn2.p, ULn2.v, &ss, &se);
		if (ss * se < 0) {										// ��_�͐����P�̓���
			po = Ln1.p[0] + (vd1 * (ss / (ss - se)));			// ��_
			if (po != Ln1.p[0] && po != Ln1.p[1]) {				// �����P�̒[���͌����_�ƌ��Ȃ��Ȃ�
				(*GPt3) += po;									// ��_����
				ist = MC_INT;
				MQUIT;
			}
		}
		ist = MC_NINT;											// ��_�Ȃ�
	}
exit:
	return ist;
}

// ---------------------( �Q���� )------------------------------
//	�����P�Ɛ����Q�Ƃ̌�_�Əd�Ȃ蕔���̒[�_�����߁A�_�Q�ɒǉ�����B
//  ��_�܂��͏d�Ȃ蕔���̒[�_�������P�̒[�_�ł���ꍇ�́A���̓_��ΏۊO�Ƃ���B
//
MINT MGeo::IntrAdd2Ln2(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
												//  MC_REP	    (2)	��������i�d�Ȃ�j
				const	MgLine2&	Ln1,		// (I  ) ����1
				const	MgLine2&	Ln2,		// (I  ) ����2
						MgGPoint2	*GPt3		// (I O) ��_��ǉ���������Q
												// 		 �ǉ���_��(0:���������܂��͐���1������2�̓����ɂ���d�Ȃ�(�[�����m�̏d�Ȃ�܂�) |
												//					1:����2�ƌ����i����2�̒[���ł̌������܂ށj�܂��͈ꕔ�d�Ȃ�(�В[�d�Ȃ�܂�) |
												//					2:����2������1�̓����ɂ���d�Ȃ�(�[�����m�̏d�Ȃ�Ȃ�)) 
				)
{
	MINT		ist;
	MINT		ist1;
	MgVect2		vd1, vd2;
	MgPoint2	po;
	MREAL		ss1, se1;
	MREAL		ss2, se2;
//	MINT		ist = 0;
//
//	���s�̃`�F�b�N
//
	vd1 = Ln1.p[1] - Ln1.p[0];
	vd2 = Ln2.p[1] - Ln2.p[0];
	if (MGeo::Parallel(vd1, vd2)) {

		MINT	nb = GPt3->m_n;
		ChkPt2OnLn2WS( Ln2.p[0], Ln1, &ist1);
		if ( MF_CHECK_OR(ist1, MC_INSIDE)) (*GPt3) += Ln2.p[0];		// �����Q�̎n�_�������P��
		ChkPt2OnLn2WS( Ln2.p[1], Ln1, &ist1);
		if ( MF_CHECK_OR(ist1, MC_INSIDE)) (*GPt3) += Ln2.p[1];		// �����Q�̏I�_�������P��
		if ( GPt3->m_n == nb) {
			ist = MC_PARALLEL;
		} else {
			ist = MC_REP;
		}
	} else {
//
		SVal(Ln1.p[0], Ln1.p[1], Ln2.p[0], vd2, &ss1, &se1);
		SVal(Ln2.p[0], Ln2.p[1], Ln1.p[0], vd1, &ss2, &se2);
//
		po = Ln1.p[0] + (vd1 * (ss1 / (ss1 - se1)));			// ��_
//
		if ((ss2 * se2 < 0 || po == Ln2.p[0] || po == Ln2.p[1]) &&
			 ss1 * se1 < 0 && po != Ln1.p[0] && po != Ln1.p[1]) {
			(*GPt3) += po;										// ��_�������P����ѐ����Q��Ő���1�̒[�_�łȂ�
			ist = MC_INT;
		} else {
			ist = MC_NINT;										// �����P�܂��͐����Q�̊O�܂��͐���1�̒[�_
		}
	}
	return ist;
}

// ---------------------( �Q���� )------------------------------
//	�����P�Ɛ����Q�Ƃ̌�_�܂��͏d�Ȃ蕔���̒[�_�����߁A�_�Q�ɒǉ�����B
//
MINT MGeo::IntrAddULnLn2(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
												//  MC_REP	    (2)	��������i�d�Ȃ�j
				const	MgULine2&	ULn1,		// (I  ) ����1
				const	MgLine2&	Ln2,		// (I  ) ����2
						MgGPoint2	*GPt3		// (I O) ��_��ǉ���������Q
												// 		 �ǉ���_��(0:�������� |
												//					1:����1�Ɛ���2�������i����2�̒[���ł̌������܂ށj|
												//					2:����1�Ɛ���2���d�Ȃ� 
				)
{
	MINT		ist;
	MINT		ist1;
	MgVect2		vd1, vd2;
	MgPoint2	po;
	MREAL		ss, se;
//	MINT	ist = 0;
//
//	���s�̃`�F�b�N
//
	vd2 = Ln2.p[1] - Ln2.p[0];
	if (MGeo::Parallel(ULn1.v, vd2)) {

		if ( ChkPt2OnULn2WS( Ln2.p[0], ULn1, &ist1)) {
			(*GPt3) += Ln2.p[0];								// �����Q�̎n�_�������P��
			(*GPt3) += Ln2.p[1];								// (�����Q�̏I�_�������P��)
			ist = MC_REP;
		} else {
			ist = MC_PARALLEL;
		}
	} else {
//
		SVal(Ln2.p[0], Ln2.p[1], ULn1.p, ULn1.v, &ss, &se);
//
		po = Ln2.p[0] + (vd2 * (ss / (ss - se)));				// ��_
//
		if (ss * se < 0 || po == Ln2.p[0]						// �����Q��
						|| po == Ln2.p[1]) {
			(*GPt3) += po;
			ist = MC_INT;
		} else {
			ist = MC_NINT;										// �����Q�̊O
		}
	}
	return ist;
}

// ---------------------( �R���� )------------------------------
//	�Q�{�̒����̌�_�����߂�B
//
MINT MGeo::Intr2ULn3(							// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_TWIST	(-2) �����Ȃ��i�˂���j
												//	MC_INT      (1)	��������
				const	MgULine3&	ULn1,		// (I  ) ����1
				const	MgULine3&	ULn2,		// (I  ) ����2
						MgPoint3	*po			// (  O) �R������_
				)
{
	MINT	ist;
	MgVect3	sp;									//	�P�ʃx�N�g���̊O��
	MgVect3	V12;								//	����1�̎n�_���璼��2�̎n�_�ւ̃x�N�g��
	MREAL	s12_2;								//	�P�ʃx�N�g���̊O��**2
	MREAL	pa1;								//	����1�̎n�_�����_�܂ł̋���
	MREAL	Hab12;								//	�P�ʃx�N�g��2�{����Ȃ镽�s�U�ʑ̂̑̐�
//	MREAL	L12_2;								//	�������̎n�_�Ԃ̋����̂Q��
//
//	���s�̃`�F�b�N
//
	sp = ULn1.v ^ ULn2.v;										// Vect(sin��v1v2)
	s12_2 = sp * sp;											// (sin��v1v2)**2
	if (s12_2 < g_gTol.A_2) {
		ist = MC_PARALLEL;										// ���s
	} else {
		V12 = ULn2.p - ULn1.p;									// ����1�̎n�_���璼��2�̎n�_�ւ̃x�N�g��	
//
		Hab12 = SVal2ULn3(ULn1, ULn2);								// ���s�S���ʑ̂̑̐�
		if ( Hab12*Hab12 > g_gTol.S_2*s12_2) {
			ist = MC_TWIST;										// �����Ȃ��i�˂����ԁj 
		} else {
			pa1 = ((V12 ^ ULn2.v) * sp) / s12_2;				// sin��v12v2 / sin��v1v2
			*po = ULn1.p + pa1 * ULn1.v;
			ist = MC_INT;
		}
	}
	return ist;
}

// ---------------------( �R���� )------------------------------
//�@�����Ɛ����̌�_�����߂�B
//
MINT MGeo::IntrULnLn3(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_TWIST    (-2) �����Ȃ��i�˂���j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MgULine3&	ULn1,		// (I  ) ����1
				const	MgLine3		&Ln2,		// (I  ) ����2
						MgPoint3	*po			// (  O) �R������_
				)
{
	MINT	ist;
	MgVect3	vd2;								//	�����Q�̎n�_����I�_�ւ̃x�N�g��
	MgVect3	vso;								//	�����Ɛ����̕����x�N�g���̊O��
	MREAL	si;									//	�����Ɛ����̕����x�N�g���̓���
//
	MgVect3	V12;								//	����1�̎n�_���璼��2�̎n�_�ւ̃x�N�g��
	MREAL	s12_2;								//	�����Ɛ����̕����x�N�g���̊O��**2
	MREAL	Hab12;								//	�P�ʃx�N�g��2�{����Ȃ镽�s�U�ʑ̂̑̐�
//
//	���s�̃`�F�b�N
//
	vd2 = Ln2.p[1] - Ln2.p[0];
//
	if (MGeo::Parallel(ULn1.v, vd2, &vso, &si)) {
		ist = MC_PARALLEL;										//	���s
	} else {
//
		V12 = Ln2.p[0] - ULn1.p;								// ����1�̎n�_�������2�̎n�_�ւ̃x�N�g��	
//
		s12_2 = vso * vso;
		Hab12 = SValULnLn3(ULn1, Ln2);							// ���s�S���ʑ̂̑̐�
		if (Hab12*Hab12 > g_gTol.S_2*s12_2) {
			ist = MC_TWIST;		//	�����Ȃ��i�˂����ԁj 
		} else {
//
			MREAL		ss;										// �����Q�̎n�_���r�o�����[
			MREAL		se;										// �����Q�̏I�_���r�o�����[
//
			SValLnULnS3(Ln2, ULn1, vso, &ss, &se);
//
			*po = Ln2.p[0] + (vd2 * (ss / (ss - se)));			// ��_
//
			if (ss * se < 0 || *po == Ln2.p[0]					// ������
							|| *po == Ln2.p[1]) {
				ist = MC_INT;
			} else {
				ist = MC_NINT;									// �����O
			}
		}
	}
	return ist;
}

// ---------------------( �R���� )------------------------------
//�@�����ƒ����̌�_�����߂�B
//
//
//					<< �R�[�f�B���O���̂�MgLib.h�ɂ��� >>
//
// MINT	MGeo::IntrLnULn3(							// (  O) �X�e�C�^�X
//												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
//												//	MC_TWIST    (-2) �����Ȃ��i�˂���j
//												//	MC_NINT	    (0)	�����Ȃ�
//												//	MC_INT      (1)	��������
//				const	MgLine3		&Ln1,		// (I  ) ����1
//				const	MgULine3&	ULn2,		// (I  ) ����2
//						MgPoint3	*po			// (  O) �R������_
//				)
// {
//	return MgIntrULnLn3(ULn2, Ln1, po);
// }
// ---------------------( �R���� )------------------------------
//�@�����Ɛ����̌�_�����߂�B
//�@�Q�������d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�Ƃ݂Ȃ��B
//  �Q�������d�Ȃ�Ȃ������I�ɒ[���Őڍ����Ă���ꍇ�͂��̐ڍ��_����_�Ƃ݂Ȃ��B
//
MINT MGeo::Intr2Ln3(							// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//  MC_CONNECTION(4) �ڑ�	 �i���s�j
												//	MC_TWIST    (-2) �����Ȃ��i�˂���j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MgLine3		&Ln1,		// (I  ) ����1
				const	MgLine3		&Ln2,		// (I  ) ����2
						MgPoint3	*po			// (  O) �R������_
				)
{
	MINT	ist;
	MgVect3	vso;
	MREAL	si;
	MgVect3	vd1,vd2;
	MREAL	s12_2;								//	�����Ɛ����̕����x�N�g���̊O��**2
	MREAL	Hab12;								//	�P�ʃx�N�g��2�{����Ȃ镽�s�U�ʑ̂̑̐�
	MREAL	ss1, se1;
	MREAL	ss2, se2;
//
//	���s�̃`�F�b�N
//
	vd1 = Ln1.p[1] - Ln1.p[0];
	vd2 = Ln2.p[1] - Ln2.p[0];
	if (MGeo::Parallel(vd1, vd2, &vso, &si)) {
		if (Ln1.p[0] == Ln2.p[0] && si < 0 ||
			Ln1.p[0] == Ln2.p[1] && si > 0) {
			*po = Ln1.p[0];
			ist = MC_CONNECTION;								// ���s�@����1�̎n�_�Ɛ���2�̒[�_���ߓ_
		} else if (Ln1.p[1] == Ln2.p[0] && si > 0 ||
				   Ln1.p[1] == Ln2.p[1] && si < 0) {
			*po = Ln1.p[1];
			ist = MC_CONNECTION;								// ���s�@����1�̏I�_�Ɛ���2�̒[�_���ߓ_
		} else {
			ist = MC_PARALLEL;									// ���s
		}
	} else {
//
		s12_2 = vso * vso;
		Hab12 = SVal2Ln3(Ln1, Ln2);								// ���s�S���ʑ̂̑̐�
		if ( Hab12*Hab12 > g_gTol.S_2*s12_2) {
			ist = MC_TWIST;		//	�����Ȃ��i�˂����ԁj 
		} else {
//
			SVal2LnS3(Ln1, Ln2, vso, &ss1, &se1);
			SVal2LnS3(Ln2, Ln1, vso, &ss2, &se2);
//
			*po = Ln1.p[0] + (vd1 * (ss1 / (ss1 - se1)));		// ��_
//
			if ((ss1 * se1 < 0 ||			//	������
				 *po == Ln1.p[0] || *po == Ln1.p[1]) &&
				(ss2 * se2 < 0 ||
				 *po == Ln2.p[0] || *po == Ln2.p[1])) {
				ist = MC_INT;
			} else {
				ist = MC_NINT;									// �����O
			}
		}
	}
	return ist;
}

//===========================================================================
//		���ʂƒ����̌�_�@�`�󉉎Z
//
// ---------------------( �R���� )------------------------------
//
//	���ʂƒ����̌�_�����߂�B
//
MINT MGeo::IntrPlnULn3(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_INT      (1)	��������
				const	MgPlane3	&Pln1,		// (I  ) ����1
				const	MgULine3&	ULn2,		// (I  ) ����2
						MgPoint3	*po			// (  O) �R������_(�_�̕W���`��)
				)
{
	MINT	ist;
	MREAL	c12;								//	�P�ʃx�N�g���̓���
	MREAL	ss;									//	����2�̎n�_���r�o�����[
	MREAL	pa1;								//	����2�̎n�_�����_�܂ł̋���
//
//	���s�̃`�F�b�N
//
	c12 = Pln1.v * ULn2.v;										// (cos��v1v2)
	if ( Zero( c12, g_gTol.A)) {
		ist = MC_PARALLEL;										// ���s
	} else {
//
		ss = (Pln1.v * ULn2.p) + Pln1.d;
		pa1 = - ss / c12;										// ss / (ss - se) [se = ss + c12]
		*po = ULn2.p + ULn2.v * pa1;
//
		ist = MC_INT;
	}
	return ist;
}

// ---------------------( �R���� )------------------------------
//	���ʂƐ����̌�_�����߂�B
//
MINT MGeo::IntrPlnLn3(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MgPlane3	&Pln1,		// (I  ) ����1
				const	MgLine3		&Ln2,		// (I  ) ����2
						MgPoint3	*po			// (  O) �R������_(�_�̕W���`��)
				)
{
	MINT	ist;
	MgVect3	vso;
	MREAL	si;
	MgVect3	vd2;								//	����2�̃x�N�g��
	MREAL	ss;									//	�����Q�̎n�_���r�o�����[
	MREAL	se;									//	�����Q�̏I�_���r�o�����[
//
	MREAL	pa1;								//	����2�̎n�_�����_�܂ł̋���
//
//	���s�̃`�F�b�N
//
	vd2 = Ln2.p[1] - Ln2.p[0];
	if (MGeo::Parallel(Pln1.v, vd2, &vso, &si)) {
		ist = MC_PARALLEL;	//	���s
	} else {
//
		ss = (Pln1.v * Ln2.p[0]) + Pln1.d;
		se = (Pln1.v * Ln2.p[1]) + Pln1.d;
		pa1 = ss / (ss - se);
		*po = Ln2.p[0] + vd2 * pa1;
//
		if (ss * se < 0 || *po == Ln2.p[0]			 			// ������
						|| *po == Ln2.p[1]) {
			ist = MC_INT;
		} else {
			ist = MC_NINT;										// �����O
		}
	}
	return ist;
}

// ---------------------( �R���� )------------------------------
//	�����ƕ��ʂ̌�_�����߂�B
/*
MINT MGeo::IntrULnPln3(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_INT      (1)	��������
				const	MgULine3&	ULn1,		// (I  ) ����1
				const	MgPlane3	&Pln2,		// (I  ) ����2
						MgPoint3	*po			// (  O) �R������_(�_�̕W���`��)
				)
{
	return MgIntrPlnULn3(Pln2, ULn1, po);
}
*/
// ---------------------( �R���� )------------------------------
//	�����ƕ��ʂ̌�_�����߂�B
/*
MINT MGeo::IntrLnPln3(						// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_NINT	    (0)	�����Ȃ�
												//	MC_INT      (1)	��������
				const	MgLine3		&Ln1,		// (I  ) ����1
				const	MgPlane3	&Pln2,		// (I  ) ����2
						MgPoint3	*po			// (  O) �R������_(�_�̕W���`��)
				)
{
	return MgIntrPlnLn3(Pln2, Ln1, po);
}
*/
//===========================================================================
//		���ʂƕ��ʂ̌���@�`�󉉎Z
//
// ---------------------( �R���� )------------------------------
//
//	���ʂƕ��ʂ̌�������߂�B
//
MINT MGeo::Intr2Pln3(							// (  O) �X�e�C�^�X
												//	MC_PARALLEL (-1) �����Ȃ��i���s�j
												//	MC_INT      (1)	��������
				const	MgPlane3	&Pln1,		// (I  ) ����1
				const	MgPlane3	&Pln2,		// (I  ) ����2
						MgULine3	*ULn3		// (  O) ����2
				)
{
	MINT	ist;
	MgVect3 vso;
	MREAL	s12;								//	�P�ʃx�N�g���̓���
//
//	���s�̃`�F�b�N
//
	vso = Pln1.v ^ Pln2.v;										// (sin��v1v2)
	s12 = Abs_2(vso);
	if ( Zero(s12, g_gTol.A_2)) {
		ist = MC_NINT;											// ���s
	} else {
//
		if ( !Zero( vso.z, 0.5)) {
			ULn3->p.x = ( Pln2.d * Pln1.v.y - Pln1.d * Pln2.v.y) / vso.z;
			ULn3->p.y = ( Pln1.d * Pln2.v.x - Pln2.d * Pln1.v.x) / vso.z;
			ULn3->p.z = 0.0f;
		} else if ( !Zero(vso.y, 0.5)) {
			ULn3->p.x = ( Pln1.d * Pln2.v.z - Pln2.d * Pln1.v.z) / vso.y;
			ULn3->p.y = 0.0f;
			ULn3->p.z = ( Pln2.d * Pln1.v.x - Pln1.d * Pln2.v.x) / vso.y;
		} else {
			ULn3->p.x = 0.0f;
			ULn3->p.y = ( Pln2.d * Pln1.v.z - Pln1.d * Pln2.v.z) / vso.x;
			ULn3->p.z = ( Pln1.d * Pln2.v.y - Pln2.d * Pln1.v.y) / vso.x;
		}
		ULn3->v = vso.Unitize();
		ist = MC_INT;
	}
	return ist;
}

} // namespace MC