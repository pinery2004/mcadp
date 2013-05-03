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
#include "MlLog.h"

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"

namespace MC
{

// ---------------------( �Q���� )------------------------------
//		����������ŕ�������
//		(�����P�̒[���ł̌����͌��������Ƃ���������)
//
MINT MGeo::Divide2Ln2(							// (  O) �X�e�C�^�X
												//			MC_NINT			(0): ��������
												//			MC_INT			(1): ��������
				const	MgLine2D&	Ln1, 		// (I  ) �����Ώې���
				const	MgLine2D&	Ln2, 		// (I  ) ��������
						MgGLine2D*	GLn3		// (  O) ������̐����Q
				)
{
	MINT		ist;
	MgVect2D		vd1, vd2;
	MgPoint2D 	po;
	MREAL		ss1, se1;
	MREAL		ss2, se2;

	_ASSERTE(Ln1.p[0] != Ln1.p[1]);								// debug --> check same point
//
	GLn3->m_n = 0;
//
//	���s�̃`�F�b�N
//
	vd1 = Ln1.p[1] - Ln1.p[0];
	vd2 = Ln2.p[1] - Ln2.p[0];
	if (!MGeo::Parallel( vd1, vd2)) {							// ����
		SVal( Ln1.p[0], Ln1.p[1], Ln2.p[0], vd2, &ss1, &se1);
		SVal( Ln2.p[0], Ln2.p[1], Ln1.p[0], vd1, &ss2, &se2);
		if (ss1 * se1 < 0) {									// ��_�͐����P�̓���
			po = Ln1.p[0] + (vd1 * (ss1 / (ss1 - se1)));		// ��_
			if (ss2 * se2 < 0 || po == Ln2.p[0] || po == Ln2.p[1]) { // ��_�͐����Q��
				if ( po != Ln1.p[0] && po != Ln1.p[1]) {		// �����P�̒[���͌�_�ƌ��Ȃ��Ȃ�
					(*GLn3) += MgLine2D(Ln1.p[0], po);			// ��������
					(*GLn3) += MgLine2D(po, Ln1.p[1]);
					ist = MC_INT;
					MQUIT;
				}
			}
		}
	}
	(*GLn3) += Ln1;												//	��������
	ist = MC_NINT;
exit:
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		�����𒼐��ŕ�������
//		(�����P�̒[���ł̌����͌��������Ƃ���������)
//
MINT MGeo::DivideLnULn2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
				const	MgLine2D&	Ln1, 		// (I  ) �����Ώې���
				const	MgULine2D&	ULn2, 		// (I  ) ��������
						MgGLine2D*	GLn3		// (  O) ������̐����Q
				)
{
	MINT		ist;
	MgVect2D		vd1;
	MgPoint2D	po;
	MREAL		ss, se;
//
	_ASSERTE(Ln1.p[0] != Ln1.p[1]);								// debug --> check same point

	GLn3->m_n = 0;
//
//�@���s�̃`�F�b�N
//
	vd1 = Ln1.p[1] - Ln1.p[0];
	if (!MGeo::Parallel( vd1, ULn2.v)) {
		SVal( Ln1.p[0], Ln1.p[1], ULn2.p, ULn2.v, &ss, &se);
		if (ss * se < 0) {										//	��_�͐����P�̓���
			po = Ln1.p[0] + (vd1 * (ss / (ss - se)));			//	��_
			if ( po != Ln1.p[0] && po != Ln1.p[1]) {			//	�����P�̒[���͌�_�ƌ��Ȃ��Ȃ�
				(*GLn3) += MgLine2D( Ln1.p[0], po);				// ��������
				(*GLn3) += MgLine2D( po, Ln1.p[1]);
				ist = MC_INT;
				MQUIT;
			}
		}
	}
	(*GLn3) += Ln1;												//	��������
	ist = MC_NINT;
exit:
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		�����𒼐��ŕ����������̑I�𑤂̐����𕪊���̐����Q�ɒǉ�����
//		(�����̒[���ł̌����͌����Ȃ��Ƃ���)
//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
//			���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
//				(3) ���̑��̏ꍇ�͎̂Ă�
//		//			(1) �I�������������̍���|������̏ꍇ�́A��������̎��c��
//		//			(2) �I�������������̉E��|������̏ꍇ�́A�t�����̎��c��
//		//			(3) ���̑��̏ꍇ�͎̂Ă�
//
// 		sels = MC_LEFT | MC_ON_BORDER | MC_SAME_DIR;

//
MINT MGeo::DivideAddLnULn2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_LEFT			(010): �����̍���
												//			MC_ON_LINE		(020): ������
												//			MC_RIGHT		(040): �����̉E��
												//			MC_SAME_DIR		(0100):	�ӏ㓯�����
												//			MC_REV_DIR		(0200):	�ӏ�t����
				const	MgLine2D&	Ln1, 		// (I  ) �����Ώې���
				const	MgULine2D&	ULn2, 		// (I  ) ��������
						MgGLine2D*	GLn3		// (I O) ������̐����Q
				)
{
	MINT		ist;
	MINT		ist1;
	MgVect2D		vd1;
	MgPoint2D 	po;
	MREAL		ss, se;
	MREAL		selr;
//
	_ASSERTE(Ln1.p[0] != Ln1.p[1]);								// debug --> check same point
//
	if (MF_CHECK_OR( Sel, MC_LEFT)) selr = 1.;
	else selr = -1.;
//
	vd1 = Ln1.p[1] - Ln1.p[0];
	// �����ƒ��������s�Ő����̒[���łȂ��ʒu�Ō�������ꍇ�́A
	// �����𕪊����I�������ɍ������𕪊���̐����Q�ɒǉ�����
	if (!MGeo::Parallel( vd1, ULn2.v)) {
		SVal( Ln1.p[0], Ln1.p[1], ULn2.p, ULn2.v, &ss, &se);
		if (ss * se < 0) {										// ��_�͐����P�̓����ɂ���
			po = Ln1.p[0] + (vd1 * (ss / (ss - se)));			// ��_�����߂�
			if ( po != Ln1.p[0] && po != Ln1.p[1]) {			// ��_�������P�̒[���Ŗ����Ȃ��
				if (ss * selr > 0) {							// �����𕪊����I�������ɍ������𕪊���̐����Q�ɒǉ�����
					(*GLn3) += MgLine2D( Ln1.p[0], po);
				} else {
					(*GLn3) += MgLine2D( po, Ln1.p[1]);
				}
				ist = MC_INT | MC_MATCH;
				MQUIT;
			}
		}
	}
	// ���s�܂��͕��������̏ꍇ�I�������ɍ����ꍇ�͕�����̐����Q�ɒǉ�����
	ist = MC_NINT;
	MGeo::ChkLn2OnULn2WS( Ln1, ULn2, &ist1);					// �����̒��S�_�������ƑI�������ɍ��������ׂ�
	if (MF_CHECK_OR( Sel, MC_SAME_DIR | MC_REV_DIR) &&			// �I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���ꍇ�́A
		MF_CHECK_OR( ist1, MC_ON_LINE)) {						// ������̐�����������ɂ���Ǝ��̂悤�ɑI������
		MREAL	cvd1 = vd1 * ULn2.v;
		if ((MF_CHECK_OR( Sel, MC_SAME_DIR) && cvd1 > 0. ||		//	(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��𕪊���̐����Q�ɒǉ�����
			 MF_CHECK_OR( Sel, MC_REV_DIR) && cvd1 < 0. )) {	//	(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��𕪊���̐����Q�ɒǉ�����
			(*GLn3) += Ln1;
			ist |= MC_MATCH;
		}														//	(3) ���̑��̏ꍇ�͎̂Ă�
	} else if (MF_CHECK_OR( ist1, Sel & (MC_LEFT | MC_ON_LINE | MC_RIGHT))) {
																// ���̑��A�������I�������ɍ����ꍇ�͕�����̐����Q�ɒǉ�����
		(*GLn3) += Ln1;
		ist |= MC_MATCH;
	}
exit:
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		����������Q�Ƃ̌�_�ŕ�������
//		(�����̒[���ł̌����͌����Ȃ��Ƃ���)
//
MINT MGeo::DivideLnGLn2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
				const	MgLine2D&	Ln1, 		// (I  ) �����Ώې���
				const	MgGLine2D&	GLn2, 		// (I  ) ���������Q
						MgGLine2D*	GLn3		// (  O) ������̐����Q
				)
{
	MINT		ist;
	MINT		ic2, ic3;
	MINT		ULn1 = 0;
	MGGPOINT2( GPt, MX_PNT1);						// �_�W���̍�ƃG���A

		_ASSERTE(Ln1.p[0] != Ln1.p[1]);							// debug --> check same point
	GLn3->m_n = 0;
	
	GPt += Ln1.p[0];											// �n�_�ƏI�_��_�W���̍�ƃG���A�ɃZ�b�g����
	GPt += Ln1.p[1];
	for ( ic2=0; ic2<GLn2.m_n; ic2++) {
																// �����Ɛ����̌�_�����߂�
		IntrAdd2Ln2( Ln1, GLn2.m_ln[ic2], &GPt);				// ��_�i�Q�������d�Ȃ莞�ɂ͂Q�_������j
	}
//
	SortLnGPt2( Ln1, &GPt);										// ���߂���_�̓���_���Ԉ����āALn1�̕����Ɉ��ɕ��ׂ�
//
	if (GLn3->m_isz < GPt.m_n - 1)
		GLn3->Resize( GPt.m_n - 1);
	for ( ic3=1; ic3<GPt.m_n; ic3++) {							// �������ꂽ���������߂�
		(*GLn3) += MgLine2D( GPt.m_p[ic3-1], GPt.m_p[ic3]);
	}
//
	if (GPt.m_n > 2)
		ist = MC_INT;
	else
		ist = MC_NINT;
//
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		�����Q����_�ŕ�������������͏�����{�ɂ���i�t�����������j
//		��������łQ�������d�Ȃ�ꍇ�͒[�_�ŕ�������
//
MINT MGeo::DivideGLn2(							// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
				const	MgGLine2D&	GLn1, 		// (I  ) �����Q
						MgGLine2D*	GLn2		// (  O) ������̐����Q
				)
{
	MINT		ist = MC_NINT;
	MINT		ic1, ic2, ic3;
	MINT		ULn1 = 0;
	MGGPOINT2( GPt, MX_PNT1);						// �_�Q�̍�ƃG���A
	
	GLn2->m_n = 0;

	for ( ic1=0; ic1<GLn1.m_n; ic1++) {
		MgLine2D Ln1 = GLn1.m_ln[ic1];							// ��{�̐��������o��

		GPt.m_n = 0;
		GPt += Ln1.p[0];										// �n�_�ƏI�_��_�W����ƃG���A�ɃZ�b�g����
		GPt += Ln1.p[1];
		for ( ic2=0; ic2<GLn1.m_n; ic2++) {
			if ( ic1 == ic2) continue;
																// �����Ɛ����̌�_�����߂�
			IntrAdd2Ln2( Ln1, GLn1.m_ln[ic2], &GPt);			// ��_�i�Q�������d�Ȃ莞�ɂ͂Q�_������j
		}
//
		SortLnGPt2( Ln1, &GPt);									// ���߂���_�̓���_���Ԉ����āALn1�̕����Ɉ��ɕ��ׂ�
//
		for ( ic3=1; ic3<GPt.m_n; ic3++) {						// �������ꂽ���������߂�
			(*GLn2) += MgLine2D( GPt.m_p[ic3-1], GPt.m_p[ic3]);
		}
		if (GPt.m_n > 2)
			ist = MC_INT;
	}
	MergeGLn2( GLn2);											// �d�Ȃ��Ă���������폜����
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		�����𑽊p�`�ŕ������A�I�������ɍ��������Q�����o��
//			�I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
//			���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideULnPg2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
												//			MC_SAME_DIR		(0100):	�ӏ㓯�����
				const	MgULine2D&	ULn1,		// (I  ) ����
				const	MgPolyg2D&	Pg2,		// (I  ) ���p�`
						MgGLine2D*	GLn3		// (  O) ������̐����Q
				)
{
	GLn3->m_n = 0;
	return DivideAddULnPg2( Sel, ULn1, Pg2, GLn3);
}

// ---------------------( �Q���� )------------------------------
//		�����𑽊p�`�ŕ������A�I�������ɍ��������𕪊���̐����Q�ɒǉ�����
//			�I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
//			���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideAddULnPg2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
												//			MC_SAME_DIR		(0100):	�ӏ㓯�����
				const	MgULine2D&	ULn1,		// (I  ) ����
				const	MgPolyg2D&	Pg2,		// (I  ) ���p�`
						MgGLine2D*	GLn3		// (I O) ������̐����Q
				)
{
	MINT		ist;
	MINT		ist1;
	MINT		ic1, icb;
	MgLine2D		lnw1;
	MGGPOINT2( GPt, MX_PNT1);						// �_�Q�̍�ƃG���A

	// ���p�`�̑S�Ă̕Ӂi�����j�Ƃ̌�_�����ߒ����̕����ɂ��킹�ĕ��ׂ�
	for ( icb=Pg2.m_n-1,ic1=0; ic1<Pg2.m_n; icb=ic1,ic1++) {
		lnw1 = MgLine2D( Pg2.m_p[icb], Pg2.m_p[ic1]);
		IntrAddULnLn2( ULn1, lnw1, &GPt);							// �����Ɛ����̌�_�i�Q�������d�Ȃ莞�ɂ͂Q�_������j
	}

	MGeo::SortVGPt2( ULn1.v, &GPt);									// ���߂���_�̓���_���Ԉ����Ĉ��ɕ��ׂ�

	if (GPt.m_n >= 2)
		ist = MC_INT;
	else
		ist = MC_NINT;
	// ������̐��������p�`�ƑI�������ɍ������̂̂ݎc��
	for ( ic1=1; ic1<GPt.m_n; ic1++) {
		lnw1 = MgLine2D( GPt.m_p[ic1-1], GPt.m_p[ic1]);
		ChkLn2OnPg2WS( lnw1, Pg2, &ist1);							// �����̒��S�_�����p�`�ƑI�������̊֌W�����ׂ�
		if (MF_CHECK_OR( Sel, MC_SAME_DIR) &&						// �I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���ꍇ�́A
			MF_CHECK_OR( ist1, MC_ON_SIDE)) {						// ������̐��������p�`�̕ӏ�ɂ���Ǝ��̂悤�ɑI������
			if (MF_CHECK_OR( ist1, MC_ON_SIDE_SAME)) {				// (1) ��������̎��c��
				(*GLn3) += lnw1;
				ist |= MC_MATCH;
			}													//  (2) ���̑��̏ꍇ�͎̂Ă�
		} else if (MF_CHECK_OR( ist1, Sel & (MC_IN_BORDER | MC_ON_BORDER))) {
																// ���̑��A�������I�������ɍ����ꍇ�͕�����̐����Q�ɒǉ�����
			(*GLn3) += lnw1;
			ist |= MC_MATCH;
		}
	}
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		�����𑽊p�`�ŕ������A�I�������ɍ��������Q�𓾂�
//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
//			���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
//				(3) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideLnPg2(							// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
												//			MC_OUT_BORDER	(004): �O��
												//			MC_FOR_POLYGON	(0100): ���p�`�쐬�p
				const	MgLine2D&	Ln1,		// (I  ) ����
				const	MgPolyg2D&	Pg2,		// (I  ) ���p�`
						MgGLine2D*	GLn3		// (  O) ������̐����Q
				)
{
	GLn3->m_n = 0;
	return DivideAddLnPg2( Sel, Ln1, Pg2, GLn3);
}

// ---------------------( �Q���� )------------------------------
//		�����𑽊p�`�ŕ������A�I�������ɍ��������𕪊���̐����Q�ɒǉ�����
//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
//			���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
//				(3) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideAddLnPg2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
												//			MC_OUT_BORDER	(004): �O��
												//			MC_SAME_DIR		(0100):	�ӏ㓯�����
												//			MC_REV_DIR		(0200):	�ӏ�t����
				const	MgLine2D&	Ln1,		// (I  ) ����
				const	MgPolyg2D&	Pg2,		// (I  ) ���p�`
						MgGLine2D*	GLn3		// (I O) ������̐����Q
				)
{
	MINT		ist;
	MINT		ist1;
	MINT		ic1, icb;
	MgLine2D		lnw1;
	MGGPOINT2( GPt, MX_PNT1);						// �_�Q�̍�ƃG���A
	
	// ���p�`�̑S�Ă̕Ӂi�����j�̌�_�����ߐ����̎n�_����I�_�̕����ɂ��킹�ĕ��ׂ�
	GPt += Ln1.p[0];
	GPt += Ln1.p[1];
																// ���p�`�̑S�Ă̕Ӂi�����j�Ƃ̌�_�����߂�
	for ( icb=Pg2.m_n-1,ic1=0; ic1<Pg2.m_n; icb=ic1,ic1++) {
		lnw1 = MgLine2D( Pg2.m_p[icb], Pg2.m_p[ic1]);
		IntrAdd2Ln2( Ln1, lnw1, &GPt);							// �����Ɛ����̌�_�i�Q�������d�Ȃ莞�ɂ͂Q�_������j
	}

	SortLnGPt2( Ln1, &GPt);										// ���߂���_�̓���_���Ԉ����Ĉ��ɕ��ׂ�

	if (GPt.m_n > 2)
		ist = MC_INT;
	else
		ist = MC_NINT;
	// ������̐��������p�`�ƑI�������ɍ������̂̂ݎc��
	for ( ic1=1; ic1<GPt.m_n; ic1++) {
		lnw1 = MgLine2D( GPt.m_p[ic1-1], GPt.m_p[ic1]);
		ChkLn2OnPg2WS( lnw1, Pg2, &ist1);						// �����̒��S�_�����p�`�ƑI�������̊֌W�����ׂ�
		if (MF_CHECK_OR( Sel, MC_SAME_DIR | MC_REV_DIR) &&		// �I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���ꍇ�́A
			MF_CHECK_OR( ist1, MC_ON_SIDE)) {					// ������̐��������p�`�̕ӏ�ɂ���Ǝ��̂悤�ɑI������
			if ((MF_CHECK_OR( Sel, MC_SAME_DIR) && MF_CHECK_OR( ist1, MC_ON_SIDE_SAME)) ||
																//	(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
				(MF_CHECK_OR( Sel, MC_REV_DIR) && MF_CHECK_OR( ist1, MC_ON_SIDE_REV))) {
																//	(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
				(*GLn3) += lnw1;
				ist |= MC_MATCH;
			}													//	(3) ���̑��̏ꍇ�͎̂Ă�
		} else if (MF_CHECK_OR( ist1, Sel & (MC_IN_BORDER | MC_ON_BORDER | MC_OUT_BORDER))) {
																// ���̑��A�������I�������ɍ����ꍇ�͕�����̐����Q�ɒǉ�����
			(*GLn3) += lnw1;
			ist |= MC_MATCH;
		}
	}
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		���������t�����p�`�ŕ������A�I�������ɍ��������Q�𓾂�
//			�I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
//			���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideULnGPg2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �I�������ɍ��������Ȃ�
												//			MC_INT			(1): �I�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
												//			MC_SAME_DIR		(0100):	�ӏ㓯�����
				const	MgULine2D&	ULn1,		// (I  ) ����
				const	MgGPolyg2D&	gPg2,		// (I  ) ���t�����p�`
						MgGLine2D*	GLn3		// (  O) ������̐����Q
				)
{
	GLn3->m_n = 0;
	return DivideAddULnGPg2( Sel, ULn1, gPg2, GLn3);
}

// ---------------------( �Q���� )------------------------------
//		���������t�����p�`�ŕ������A�I�������ɍ��������𕪊���̐����Q�ɒǉ�����
//			�I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideAddULnGPg2(						// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �I�������ɍ��������Ȃ�
													//			MC_INT			(1): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,			// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
				const	MgULine2D&	ULn1,			// (I  ) ����
				const	MgGPolyg2D&	gpg2,			// (I  ) ���t�����p�`
						MgGLine2D*	gLn3			// (I O) ������̐����Q
				)
{
	MINT		ist;
	MINT		ist1;
	MINT		ic1, ic2, icb;
	MgLine2D		lnw1;
	MGGPOINT2( GPt, MX_PNT1);									// �_�Q�̍�ƃG���A
	
	// ���t�����p�`�̑S�Ă̕Ӂi�����j�Ƃ̌�_�����ߒ����̕����ɂ��킹�ĕ��ׂ�
	for ( ic1=0; ic1<gpg2.m_n; ic1++) {
		MgPolyg2D*	pg2 = &(gpg2.m_pg[ic1]);
																// �|���S���̑S�ĕӂƂ̌�_�����߂�
		for ( icb=pg2->m_n-1,ic2=0; ic2<pg2->m_n; icb=ic2,ic2++) {
			lnw1 = MgLine2D( pg2->m_p[icb], pg2->m_p[ic2]);
			IntrAddULnLn2( ULn1, lnw1, &GPt);					// �����Ɛ����̌�_�i�Q�������d�Ȃ莞�ɂ͂Q�_������j
		}
	}

	MGeo::SortVGPt2( ULn1.v, &GPt);								// ���߂���_�̓���_���Ԉ����Ĉ��ɕ��ׂ�

	if (GPt.m_n >= 2)
		ist = MC_INT;
	else
		ist = MC_NINT;
	// ������̐��������t�����p�`�ƑI�������ɍ������̂̂ݎc��
	for ( ic1=1; ic1<GPt.m_n; ic1++) {
		lnw1 = MgLine2D(GPt.m_p[ic1-1], GPt.m_p[ic1]);
		ChkLn2OnGPg2WS( lnw1, gpg2, &ist1);						// �����̒��S�_�����t�����p�`�ƑI�������̊֌W�����ׂ�
		if (MF_CHECK_OR( Sel, MC_SAME_DIR) &&					// �I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���ꍇ�́A
			MF_CHECK_OR( ist1, MC_ON_SIDE)) {					// ������̐��������t�����p�`�̕ӏ�ɂ���ƁA���̂悤�ɑI������
			if (MF_CHECK_OR( ist1, MC_ON_SIDE_SAME)) {			//	(1) ��������̎��c��
				(*gLn3) += lnw1;
				ist |= MC_MATCH;
			}													//	(2) ���̑��̏ꍇ�͎̂Ă�
		} else if (MF_CHECK_OR( ist1, Sel & (MC_IN_BORDER | MC_ON_BORDER))) {
																// ���̑��A�������I�������ɍ����ꍇ�͕�����̐����Q�ɒǉ�����
				(*gLn3) += lnw1;
				ist |= MC_MATCH;
		}
	}
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		���������t�����p�`�ŕ������A�I�������ɍ��������Q�𓾂�
//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
//			���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
//				(3) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideLnGPg2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
												//			MC_OUT_BORDER	(004): �O��
												//			MC_SAME_DIR		(0100):	�ӏ㓯�����
												//			MC_REV_DIR		(0200):	�ӏ�t����
				const	MgLine2D&	Ln1,		// (I  ) ����
				const	MgGPolyg2D&	GPg2,		// (I  ) ���t�����p�`
						MgGLine2D*	GLn3		// (  O) ������̐����Q
				)
{
	GLn3->m_n = 0;
	return DivideAddLnGPg2( Sel, Ln1, GPg2, GLn3);
}

// ---------------------( �Q���� )------------------------------
//		���������t�����p�`�ŕ������A�I�������ɍ��������𕪊���̐����Q�ɒǉ�����
//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
//			���̂悤�ɑI������
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
//				(3) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideAddLnGPg2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
												//			MC_OUT_BORDER	(004): �O��
												//			MC_SAME_DIR		(0100):	�ӏ㓯�����
												//			MC_REV_DIR		(0200):	�ӏ�t����
				const	MgLine2D&	Ln1,		// (I  ) ����
				const	MgGPolyg2D&	GPg2,		// (I  ) ���t�����p�`
						MgGLine2D*	GLn3		// (I O) ������̐����Q
				)
{
	MINT		ist;
	MINT		ist1;
	MINT		ic1, ic2, icb;
	MgLine2D		lnw1;
	MGGPOINT2(GPt, MX_PNT1);									// �_�Q�̍�ƃG���A
	
	// ���t�����p�`�̑S�Ă̕Ӂi�����j�̌�_�����ߐ����̎n�_����I�_�̕����ɂ��킹�ĕ��ׂ�
	GPt += Ln1.p[0];
	GPt += Ln1.p[1];

	for ( ic1=0; ic1<GPg2.m_n; ic1++) {
		MgPolyg2D*	pg2 = &(GPg2.m_pg[ic1]);
																// ���p�`�̑S�ĕӂƂ̌�_�����߂�
		for ( icb=pg2->m_n-1,ic2=0; ic2<pg2->m_n; icb=ic2,ic2++) {
																// �����Ɛ����̌�_�����߂�
			lnw1 = MgLine2D( pg2->m_p[icb], pg2->m_p[ic2]);
			IntrAdd2Ln2( Ln1, lnw1, &GPt);						// ��_�i�Q�������d�Ȃ莞�ɂ͂Q�_������j
		}
	}

	SortLnGPt2( Ln1, &GPt);										// ���߂���_�̓���_���Ԉ����Ĉ��ɕ��ׂ�

	if (GPt.m_n > 2)
		ist = MC_INT;
	else
		ist = MC_NINT;
	// ������̐��������t�����p�`�ƑI�������ɍ��v������̂̂ݎc��
	for ( ic1=1; ic1<GPt.m_n; ic1++) {
		lnw1 = MgLine2D( GPt.m_p[ic1-1], GPt.m_p[ic1]);
		ChkLn2OnGPg2WS( lnw1, GPg2, &ist1);						// �����̒��S�_�����t�����p�`�ƑI�������̊֌W�����ׂ�
		if (MF_CHECK_OR( Sel, MC_SAME_DIR | MC_REV_DIR) &&		// �I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���ꍇ�́A
			MF_CHECK_OR( ist1, MC_ON_SIDE)) {					// ������̐��������t�����p�`�̕ӏ�ɂ���Ǝ��̂悤�ɑI������
			if (MF_CHECK_OR( Sel, MC_ON_BORDER) &&
				((MF_CHECK_OR( Sel, MC_SAME_DIR) && MF_CHECK_OR( ist1, MC_ON_SIDE_SAME)) ||
																//	(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
				 (MF_CHECK_OR( Sel, MC_REV_DIR) && MF_CHECK_OR( ist1, MC_ON_SIDE_REV)))) {
																//	(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
				(*GLn3) += lnw1;
				ist |= MC_MATCH;
			}													//	(3) ���̑��̏ꍇ�͎̂Ă�
		} else if (MF_CHECK_OR( ist1, Sel & (MC_IN_BORDER | MC_ON_BORDER | MC_OUT_BORDER))) {
																// ���̑��A�������I�������ɍ����ꍇ�͕�����̐����Q�ɒǉ�����
			(*GLn3) += lnw1;
			ist |= MC_MATCH;
		}
	}
	return ist;
}

// ---------------------( �Q���� )------------------------------
//		�d�Ȃ��Ă���������폜����{�ɂ��� (�t�������܂�)				<�v����UP?>
//
void MGeo::MergeGLn2(
						MgGLine2D*	Gln			// (I O) �����Q
				)
{
	MINT	ic0, ic1, ic2;
	bool	fEq;
	MINT	nGln = Gln->m_n;

	for ( ic1=0; ic1<nGln; ic1++) {
		fEq = false;
		ic0 = ic1 + 1;
		for ( ic2=ic0; ic2<nGln; ic2++) {
			if (Gln->m_ln[ic1] == Gln->m_ln[ic2]) {
				fEq = true;										// �d�Ȃ����(����������)������
			} else {
				if (fEq) Gln->m_ln[ic0] = Gln->m_ln[ic2];		// �r���ɏd�Ȃ����������΋l�߂�
				ic0++;
			}
		}
		nGln = ic0;
	}
	Gln->m_n = nGln;
}

//===========================================================================
// ---------------------( �R���� )------------------------------
//		�����𑽊p�`�ŕ������A�I�������ɍ��������Q�����o��
//
MINT MGeo::DivideULnPg3(						// (  O) �X�e�C�^�X
												//		 MC_NINT		(0): �����Ȃ�
												//		 MC_INT			(1): ��������
						MINT		Sel,		// (I  ) �I������
												//		 MC_IN_BORDER	(001): ����
												//		 MC_ON_BORDER	(002): �ӏ�
				const	MgULine3D&	ULn1,		// (I  ) ����
				const	MgPolyg3D&	Pg2,		// (I  ) ���p�`
						MgGLine3D	*GLn3		// (  O) ������̐����Q
				)
{
	GLn3->m_n = 0;
	return DivideAddULnPg3( Sel, ULn1, Pg2, GLn3);
}

/*MINT MGeo::DivideULnPg3(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
				const	MgULine3D&	ULn1,		// (I  ) ����
				const	MgPolyg3D&	Pg2,		// (I  ) ���p�`
						MgGLine3D	*GLn3		// (I O) ������̐����Q
				)
{
	GLn3->m_n = 0;
	return DivideAddULnPg3( Sel, ULn1, Pg2, GLn3);
}
*/

// ---------------------( �R���� )------------------------------
//		�����𑽊p�`�ŕ������A���������ɍ��������𕪊���̐����Q�ɒǉ�����
//
MINT MGeo::DivideAddULnPg3(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_ON_BORDER	(002): �ӏ�
				const	MgULine3D&	ULn1,		// (I  ) ����
				const	MgPolyg3D&	Pg2,		// (I  ) ���p�`
						MgGLine3D	*GLn3		// (I O) ������̐����Q
				)
{
	MINT		ist;
	MINT		ic1;
	MgPlane3D	Pln2;
	MgLine3D	Ln3;
	MgMat3DE	MatXY;							// Pln to XY���� �R�c�}�g���b�N�X
	MgMat3DE	MatPln;							// XY���� to Pln �R�c�}�g���b�N�X
	MgULine2D	uln1;
	MgPolyg2D	pg2;
	MgGLine2D	Gln3;

	Pln2 = MgPlane3DC( Pg2);

	// ��ӂ�X���ɕ��s�ɂȂ�悤XY���ʂɓ��e�}�g���b�N�X�����߂�
	Mat3PlntoXY( Pln2, Pg2.m_P[0], &MatXY, &MatPln);
	ULine3Dto2D( ULn1, MatXY, &uln1);
	Polyg3Dto2D( Pg2, MatXY, &pg2);
	ist = DivideULnPg2( Sel, uln1, pg2, &Gln3);

	if ( ist == (MC_INT | MC_MATCH)) {
		for ( ic1=0; ic1<Gln3.m_n; ic1++) {
			Line2Dto3D( Gln3.m_ln[ic1], MatPln, &Ln3);
			*GLn3 += Ln3;
		}
	}
	return ist;
}

//S //
//// ---------------------( �Q���� )------------------------------
////	�Q�̐����Ԃ̊p�x�̑召�ɏ]�����lCC�����߂�
////	[p0����p1�Ɍ���������]����[p1����p2�Ɍ���������]�ւ̊p�x�ɂ��
////		0.: -0�K, 0.5: 90�K, 1.: 180�K, 1.5: -90�K, <2.: <360(-)�K
////
//MREAL MGeo::AngSSa3Pt2( 
//				const	MgPoint2D&	p0,
//				const	MgPoint2D&	p1,
//				const	MgPoint2D&	p2
//				)
//{
//	MgVect2D	v1, v2;
//	MREAL	sp;
//	MREAL	ss, cc;
//	MREAL	sse, cce;
//
//	v1 = p1 - p0;
//	v2 = p2 - p1;
//	sp = MREAL( sqrt( (v1 * v1) * (v2 * v2)));					// MgAbs( v1) * MgAbs( v2)
//	ss = v1 ^ v2;												// sin( v1 v2) * sp
//	cc = v1 * v2 / sp;											// cos( v1 v2)
//
//	sse = ( ( cc > 0) ? ( ( ss > 0) ? sse = ss : sse = ss + 4) : sse = 2 - ss);
//	cce = ( ( ss > 0) ? cce = 1 - cc : cce = cc + 3);
//	return  ( sse + cce) / 4.f;
//}
////
//// ---------------------( �R���� )------------------------------
////	�Q�̐����Ԃ̊p�x�̑召�ɏ]�����lCC�����߂�
////	����pln3���[p0����p1�Ɍ���������]����[p1����p2�Ɍ���������]�ւ̊p�x�ɂ��
////		0.: -0�K, 0.5: 90�K, 1.: 180�K, 1.5: -90�K, <2.: <360(-)�K
////
//MREAL MGeo::AngSSa3Pt3( 
//				const	MgPoint3D&	P0,
//				const	MgPoint3D&	P1,
//				const	MgPoint3D&	P2,
//				const	MgPlane3D	&Pln3
//				)
//{
//	MgVect3D	V1, V2;
//	MREAL	sp;
//	MREAL	ss, cc;
//	MREAL	sse, cce;
//
//	V1 = P1 - P0;
//	V2 = P2 - P1;
//	sp = MREAL( sqrt( (V1 * V1) * (V2 * V2)));					// MgAbs( v1) * MgAbs( v2)
//	ss = (V1 ^ V2) * Pln3.v;									// sin( v1 v2) * sp
//	cc = V1 * V2 / sp;											// cos( v1 v2)
//
//	sse = ( ( cc > 0) ? ( ( ss > 0) ? sse = ss : sse = ss + 4) : sse = 2 - ss);
//	cce = ( ( ss > 0) ? cce = 1 - cc : cce = cc + 3);
//	return  ( sse + cce) / 4.f;
//}
////
//// ---------------------( �Q���� )------------------------------
////	�Q�̐����Ԃ̊p�x�̑召�ɏ]�����lCC�����߂�
////	[p0����p1�Ɍ���������]����[p1����p2�Ɍ���������]�ւ̊p�x�ɂ��
////		>-1.: >-180�K, -0.5: -90�K, 0.: -0�K, 0.5: 90�K, 1.: 180�K
////
//MREAL MGeo::AngSSb3Pt2( 
//				const	MgPoint2D&	p0,
//				const	MgPoint2D&	p1,
//				const	MgPoint2D&	p2
//				)
//{
//	MgVect2D	v1, v2;
//	MREAL	sp;
//	MREAL	ss, cc;
//	MREAL	sse, cce;
//
//	v1 = p1 - p0;
//	v2 = p2 - p1;
//	sp = MREAL( sqrt( (v1 * v1) * (v2 * v2)));					// MgAbs( v1) * MgAbs( v2)
//	ss = v1 ^ v2;												// sin( v1 v2) * sp
//	cc = v1 * v2 / sp;											// cos( v1 v2)
//
//	sse = ( ( cc < 0) ? ( ( ss > 0) ? sse = 2 - ss : sse = -2 - ss) : sse = ss);
//	cce = ( ( ss > 0) ? cc = 1 - cc : cc = -1 + cc);
//	return  ( sse + cce) / 4.f;
//}
////
//// ---------------------( �R���� )------------------------------
////	�Q�̐����Ԃ̊p�x�̑召�ɏ]�����lCC�����߂�
////	����pln3���[p0����p1�Ɍ���������]����[p1����p2�Ɍ���������]�ւ̊p�x�ɂ��
////		>-1.: >-180�K, -0.5: -90�K, 0.: -0�K, 0.5: 90�K, 1.: 180�K
////
//MREAL MGeo::AngSSb3Pt3( 
//				const	MgPoint3D&	P0,
//				const	MgPoint3D&	P1,
//				const	MgPoint3D&	P2,
//				const	MgPlane3D	&Pln3
//				)
//{
//	MgVect3D	V1, V2;
//	MREAL	sp;
//	MREAL	ss, cc;
//	MREAL	sse, cce;
//
//	V1 = P1 - P0;
//	V2 = P2 - P1;
//	sp = MREAL( sqrt( (V1 * V1) * (V2 * V2)));					// MgAbs( v1) * MgAbs( v2)
//	ss = (V1 ^ V2) * Pln3.v;									// sin( v1 v2) * sp
//	cc = V1 * V2 / sp;											// cos( v1 v2)
//
//	sse = ( ( cc < 0) ? ( ( ss > 0) ? sse = 2 - ss : sse = -2 - ss) : sse = ss);
//	cce = ( ( ss > 0) ? cc = 1 - cc : cc = -1 + cc);
//	return  ( sse + cce) / 4.f;
//}
//
// ---------------------( �Q���� )------------------------------
//	�I���R�p�`�������\�����ׂ�
//			 0: �ʐς�0
//			 1: �����\
//			-1: �O�p�`���ɑ��̓����_�����蕪���s��(�R�p�`�̕ӏ�͑ΏۊO)
//
MINT MGeo::ChkDivTriPtPg2( 
						MgPoint2D*	p3,			// �I���R�p�`
				const	MgPolyg2D&	Pgw,		// �������p�`
				const	MgGInt		&iGIrisumi	// �����_���X�g
				)
{
	MgVect2D		v12, v23, v31;
	MgVect2D		v10, v20, v30;
	MREAL		ss10, ss20, ss30;
	MREAL		ss, cc;
	MINT		ic0;
	MgPoint2D	p0;

	v12 = *(p3 + 1) - *p3;
	v23 = *(p3 + 2) - *(p3 + 1);
	ss = v12 ^ v23;												// sin( v12 v23) * |v12| * |v23|
	cc = v12 * v23;												// cos( v12 v23) + |v12| * |v23|
	if (ss * ss < g_gTol.A_2 * cc * cc)							// if (|sin( v12 v23)| < g_gTol.A)
		return 0;
	else {
		for ( ic0=0; ic0<iGIrisumi.m_n; ic0++) {
			v31 = *p3 - *(p3 + 2);
			p0 = Pgw.m_p[iGIrisumi[ic0]];
			v10 = p0 - *p3;
			v20 = p0 - *(p3 + 1);
			v30 = p0 - *(p3 + 2);
			if ((ss10 = (v12 ^ v10)) > 0 && (ss20 = (v23 ^ v20)) > 0 && (ss30 = (v31 ^ v30)) > 0)
				if (ss10 * ss10 > g_gTol.D_2 * (v10 * v10) &&
					ss20 * ss20 > g_gTol.D_2 * (v20 * v20) &&
					ss30 * ss30 > g_gTol.D_2 * (v30 * v30))
					return -1;
		}
	}
	return 1;
}

// ---------------------( �R���� )------------------------------
//	�I���R�p�`�������\�����ׂ�
//			 0: �ʐς�0
//			 1: �����\
//			-1: �O�p�`��܂��͓��ɑ��̓����_�����蕪���s��(�R�p�`�̕ӏ�͑ΏۊO)
//
MINT MGeo::ChkDivTriPtPg3( 
						MgPoint3D	*p3,		// �I���R�p�`
				const	MgPolyg3D&	Pgw,		// �������p�`
				const	MgGInt		&iGIrisumi,	// �����_���X�g
				const	MgVect3D&	VuPg1		// ���p�`�̖@������
				)
{
	MgVect3D		v12, v23, v31;
	MgVect3D		v10, v20, v30;
	MREAL		ss10, ss20, ss30;
	MREAL		ss, cc;
	MINT		ic0;
	MgPoint3D	p0;

	v12 = *(p3 + 1) - *p3;
	v23 = *(p3 + 2) - *(p3 + 1);
	ss = (v12 ^ v23) * VuPg1;									// sin( v12 v23) * |v12| * |v23|
	cc = v12 * v23;												// cos( v12 v23) + |v12| * |v23|
	if ( ss * ss < g_gTol.D_2 * Abs(cc))
		return 0;
	else if (ss < 0)
		return -1;
	else {
		for ( ic0=0; ic0<iGIrisumi.m_n; ic0++) {
			p0 = Pgw.m_P[iGIrisumi[ic0]];
			v31 = *p3 - *(p3 + 2);
			v10 = p0 - *p3;
			v20 = p0 - *(p3 + 1);
			v30 = p0 - *(p3 + 2);
			if ((ss10 = MREAL((v12 ^ v10) * VuPg1)) > 0 &&
				(ss20 = MREAL((v23 ^ v20) * VuPg1)) > 0 &&
				(ss30 = MREAL((v31 ^ v30) * VuPg1)) > 0)
				if (ss10 * ss10 > g_gTol.D_2 * (v10 * v10) &&
					ss20 * ss20 > g_gTol.D_2 * (v20 * v20) &&
					ss30 * ss30 > g_gTol.D_2 * (v30 * v30))
					return -1;
		}
	}
	return 1;
}

// ---------------------( �Q���� )------------------------------
//		���p�`���R�p�`�ɕ�������
//
MINT MGeo::DivideTriPg2(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
				const	MgPolyg2D&	Pg1,		// (I  ) ���p�`
						MgGPolyg2D*	GPg2		// (  O) ������̂R�p�`�Q
				)
{
	MINT		ist = 0;
	MINT		ist1;
	MINT		ic0, ic1;
	MINT		icm;
	MgVect2D		v0, v1;
	MREAL		ss;
	MGPOLYG2( Pgw, MX_PNT1);					// ��Ɨp���p�`
	MINT		Pgwn;
	MGGINT( iGIrisumi, MX_PNT0);				// �����_���X�g
	MGPOLYG2( Pg3, 3);							// �O�p�`
	Pg3.m_n = 0;

	GPg2->SetCount0();

	if (Pg1.m_n < 3)
		MQUIT;
	if (Pg1.m_n == 3) {
		(*GPg2) += Pg1;
		MQUIT;
	}
	// �����_�����ߓ����_���X�g�ɒǉ�����
	Pgw = Pg1;
	Pgw += Pg1[0];
	Pgw += Pg1[1];

	Pgwn = Pg1.m_n;
	for ( ic0=0; ic0<Pgwn; ic0++) {
		v0 = Pgw.m_p[ic0 + 1] - Pgw.m_p[ic0];
		v1 = Pgw.m_p[ic0 + 2] - Pgw.m_p[ic0 + 1];
		ss = v0 ^ v1;
		if (ss < 0)
			iGIrisumi += (ic0 + 1);								// �����_���X�g�ɒǉ� (1 �` n)
	}
//							Pg1.Print( L"Pg1");
//							iGIrisumi.Print( L"iGIrisumi");

	// �����_���X�g�̐擪�̓����_�𕪊��Ώے��_�Ƃ���
	for (; iGIrisumi.m_n > 0; ) {
		// �����v��]�����̘A������R�_�łR�p�`����茟��
		ic0 = iGIrisumi.m_i[0];									// ic0: (1 �` n)�A(0 �` n-1)
		if ( ic0 >= Pgwn)
			ic0 = 0;											// ic0: (1 �` n-1 | 0)�A(0 �` n-1)
		ist1 = ChkDivTriPtPg2( &Pgw.m_p[ic0], Pgw, iGIrisumi);
		if ( ist1 == 0)											// �O�p�`�̖ʐς��O
			goto skip1;
		else if ( ist1 == -1) {									// �O�p�`���ɑ��̓����_����
			// ���v��]�����̘A������R�_�łR�p�`����茟��
			ic0 = iGIrisumi.m_i[0] - 2;							// ic0: (-1 �` n-2)�A(-2 �` n-3)
			if ( ic0 < 0)
				ic0 += Pgwn;									// ic0: (n-1 | 0 �` n-2)�A(n-2 | n-1 | 0 �` n-2)
			ist1 = ChkDivTriPtPg2( &Pgw.m_p[ic0], Pgw, iGIrisumi);
			if ( ist1 == 0)										// �O�p�`�̖ʐς��O
				goto skip1;
			else if ( ist1 == -1) {								// �O�p�`���ɑ��̓����_����
				// �擪�����_������_���X�g�̖����Ɋi�[
				ic0 = iGIrisumi.m_i[0];
				for ( ic1=0; ic1<iGIrisumi.m_n; ic1++)
					iGIrisumi.m_i[ic1] = iGIrisumi.m_i[ic1 + 1];
				iGIrisumi.m_i[iGIrisumi.m_n - 1] = ic0;
				continue;
			}
		}
		// �����R�p�`�𕪊���̂R�p�`�Q�ɒǉ�
		Pg3.m_p[0] = Pgw.m_p[ic0];
		Pg3.m_p[1] = Pgw.m_p[ic0 + 1];
		Pg3.m_p[2] = Pgw.m_p[ic0 + 2];
		(*GPg2) += Pg3;
skip1:
		// �R�p�`�����ɂ�钸�_���Ԉ���
		ic1 = ic0 + 1;											// ic0: (1 �` n)
		if ( ic1 >= Pgwn)
			ic1 -= Pgwn;										// ic1: (1 �`  n-1 | 0)
		icm = ic1;
		Pgwn --;
		Pgw.m_n = Pgwn;
		for ( ; ic1<Pgwn; ic1++)
			Pgw.m_p[ic1] = Pgw.m_p[ic1 + 1];
		Pgw += Pgw.m_p[0];
		Pgw += Pgw.m_p[1];
		for ( ic0=0; ic0<iGIrisumi.m_n; ic0++) {
			if ( iGIrisumi.m_i[ic0] > icm)
				iGIrisumi.m_i[ic0] --;
			if ( iGIrisumi.m_i[ic0] == 0)
				iGIrisumi.m_i[ic0] = Pgwn;
		}
		// �����Ώے��_���o���ɂȂ����Ȃ�����_���X�g����폜
		ic0 = iGIrisumi.m_i[0];
		v0 = Pgw.m_p[ic0] - Pgw.m_p[ic0 - 1];
		v1 = Pgw.m_p[ic0 + 1] - Pgw.m_p[ic0];
		ss = v0 ^ v1;
		if (ss > 0) {
			iGIrisumi.m_n --;
			for ( ic1=0; ic1<iGIrisumi.m_n; ic1++)
				iGIrisumi.m_i[ic1] = iGIrisumi.m_i[ic1 + 1];
		}
	}
	// �����Ȃ��Ȃ̂ŔC�ӂ̂P�_(�擪�̓_)�łR�p�`����
	Pg3[0] = Pgw.m_p[ic1];
	for ( ic1=1; ic1<Pgw.m_n-1; ic1++) {
		Pg3[1] = Pgw.m_p[ic1];
		Pg3[2] = Pgw.m_p[ic1 + 1];
		ist1 = ChkDivTriPtPg2( Pg3.m_p, Pgw, iGIrisumi);
		if ( ist != 0)											// �O�p�`�̖ʐς��O�łȂ�
			(*GPg2) += Pg3;
	}
	ist = 1;
exit:
	return ist;
}

// ---------------------( �R���� )------------------------------
//		���p�`���R�p�`�ɕ�������
//
MINT MGeo::DivideTriPg3(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
				const	MgPolyg3D&	Pg1,		// (I  ) ���p�`
				const	MgVect3D&	VuPg1,		// (I  ) ���p�`�̖@������
						MgGPolyg3D*	gPg2		// (  O) ������̂R�p�`�Q
				)
{
	MINT		ist = 0;
	MINT		ist1;
	MINT		ic0, ic1;
	MINT		icm;
	MgVect3D		v0, v1;
	MREAL		ss;
	MGPOLYG3( Pgw, MX_PNT1);						// ��Ɨp���p�`
	MINT		Pgwn;
	MGGINT( iGIrisumi, MX_PNT0);					// �����_���X�g
	MINT		iIrisumi;
	MGPOLYG3( Pg3, 3);								// �O�p�`
	Pg3.m_n = 3;
	MINT		iDel;

	gPg2->SetCount0();

	if (Pg1.m_n < 3)
		MQUIT;
	if (Pg1.m_n == 3) {
		(*gPg2) += Pg1;
		MQUIT;
	}
	// �����_�����ߓ����_���X�g�ɒǉ�����
	Pgw = Pg1;
	Pgw += Pg1[0];												
	Pgw += Pg1[1];

	Pgwn = Pg1.m_n;
	for ( ic0=0; ic0<Pgwn; ic0++) {
		v0 = Pgw.m_P[ic0 + 1] - Pgw.m_P[ic0];
		v1 = Pgw.m_P[ic0 + 2] - Pgw.m_P[ic0 + 1];
		ss = (v0 ^ v1) * VuPg1;
		if (ss < 0)
			iGIrisumi += (ic0 + 1);								// �����_���X�g�ɒǉ� (n-1 | 0 �` n-2)
	}
//								Pg1.Print( L"Pg1");
//								iGIrisumi.Print( L"first�����__iGIrisumi");

	// �����_���X�g�̐擪�̓����_�𕪊��Ώے��_�Ƃ���
	for ( ; iGIrisumi.m_n > 0; ) {
		// �����R�_�i�����v��]�����̘A������R�_�j�łR�p�`����茟��
		ic0 = iGIrisumi.m_i[0];									// �擪�����_
		if ( ic0 >= Pgwn)
			ic0 = 0;											// ic0: �O�p�`�̊J�n�ʒu�i�擪�����_�j
		ist1 = ChkDivTriPtPg3( &Pgw.m_P[ic0], Pgw, iGIrisumi, VuPg1);
		if ( ist1 == 0)											// �O�p�`�̖ʐς��O�̏ꍇ�͊Ԉ���
		{
//								MBLOGPRINTI( L"�O�p�`�̖ʐς�0��skip_ic0", ic0);
			goto skip1;
			}
		else if ( ist1 == -1) {									// �O�p�`���ɑ��̓����_����
			// ��O�̂R�_�i���v��]�����̘A������R�_�j�łR�p�`����茟��
			ic0 = iGIrisumi.m_i[0] - 2;							// ic0: �O�p�`�̊J�n�ʒu�i�擪�����_���R�_�ڂƂ����J�n�ʒu�j
			if ( ic0 < 0)
				ic0 += Pgwn;									//
			ist1 = ChkDivTriPtPg3( &Pgw.m_P[ic0], Pgw, iGIrisumi, VuPg1);
			if ( ist1 == 0)										// �O�p�`�̖ʐς��O�̏ꍇ�͊Ԉ���
			{
//										MBLOGPRINTI( L"�O�p�`�̖ʐς�0��skip_ic0", ic0);
				goto skip1;
			}
			else if ( ist1 == -1) {								// �O�p�`���ɑ��̓����_����
				// �擪�����_������_���X�g�̖����Ɋi�[
				iIrisumi = iGIrisumi.m_i[0];
				for ( ic1=0; ic1<iGIrisumi.m_n-1; ic1++)
					iGIrisumi.m_i[ic1] = iGIrisumi.m_i[ic1 + 1];
				iGIrisumi.m_i[iGIrisumi.m_n - 1] = iIrisumi;
				continue;
			}
		}
		// �����R�p�`�𕪊���̂R�p�`�Q�ɒǉ�
		Pg3.m_P[0] = Pgw.m_P[ic0];
		Pg3.m_P[1] = Pgw.m_P[ic0 + 1];
		Pg3.m_P[2] = Pgw.m_P[ic0 + 2];
		(*gPg2) += Pg3;
//										MBLOGPRINTI( Mstr( "�����J�n�__ic0"), ic0);
//										Pg3.Print( Mstr( "�����R�p�`_Pg3"));
skip1:
		// �R�p�`�����ɂ�钸�_���Ԉ���
		ic1 = ic0 + 1;											// ic1: �Ԉ����_�@ic0: (1 �` n)
		if ( ic1 >= Pgwn)
			ic1 -= Pgwn;										// ic1: (1 �`  n-1 | 0)
		icm = ic1;
//										MBLOGPRINTI( Mstr( "�Ԉ����__icm"), icm);
		Pgwn --;
		Pgw.m_n = Pgwn;
		for ( ; ic1<Pgwn; ic1++)
			Pgw.m_P[ic1] = Pgw.m_P[ic1 + 1];
		Pgw += Pgw.m_P[0];
		Pgw += Pgw.m_P[1];

		iDel = 0;
		for ( ic0=0; ic0<iGIrisumi.m_n; ic0++) {
			if ( iGIrisumi.m_i[ic0] == icm) {
				iDel = 1;
			} else if ( iGIrisumi.m_i[ic0] > icm) {
				iGIrisumi.m_i[ic0 - iDel] = iGIrisumi.m_i[ic0] - 1;
			} else {
				iGIrisumi.m_i[ic0 - iDel] = iGIrisumi.m_i[ic0];
			}
//			if ( iGIrisumi.i[ic0] == 0)
//				iGIrisumi.i[ic0] = Pgwn;
		}
		iGIrisumi.m_n -= iDel;

		// �����Ώے��_���o���ɂȂ����Ȃ�����_���X�g����폜
		ic0 = iGIrisumi.m_i[0];
		v0 = Pgw.m_P[ic0] - Pgw.m_P[ic0 - 1];
		v1 = Pgw.m_P[ic0 + 1] - Pgw.m_P[ic0];
		ss = (v0 ^ v1) * VuPg1;
		if (ss > 0) {
			iGIrisumi.m_n --;
			for ( ic1=0; ic1<iGIrisumi.m_n; ic1++)
				iGIrisumi.m_i[ic1] = iGIrisumi.m_i[ic1 + 1];
		}
//										Pgw.Print( Mstr( "�������p�`_Pgw"));
//										iGIrisumi.Print( Mstr( "�����__iGIrisumi"));
//										MBLOGFLUSH;
	}
	// �����Ȃ��Ȃ̂ŔC�ӂ̂P�_(�擪�̓_)�łR�p�`����
	Pg3[0] = Pgw.m_P[0];
	Pgw.m_n = Pgwn;
	for ( ic1=1; ic1<Pgw.m_n-1; ic1++) {
		Pg3[1] = Pgw.m_P[ic1];
		Pg3[2] = Pgw.m_P[ic1 + 1];
		ist1 = ChkDivTriPtPg3( Pg3.m_P, Pgw, iGIrisumi, VuPg1);
		if ( ist1 != 0)										// �O�p�`�̖ʐς��O�łȂ�
			(*gPg2) += Pg3;
	}
	ist = 1;
exit:
	return ist;
}

} // namespace MC
