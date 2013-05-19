//==========================================================================================
//	Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//	MODULE: .cpp
//
//		
//
//
//	K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"
#include "MgMatD.h"

namespace MC
{

////
//// ---------------------( �Q���� )------------------------------
////		�w��������n�܂�����Q�̐������������čŏ��̑��p�`���쐬����
////	
//bool MGeo::MakeGPolygonFromLineInGLine2D(				// (  O) �X�e�C�^�X�@true: ����쐬�@false: �쐬�s��
//				const	MgLine2D&	ln1,		// (I  ) �w�����
//						MgGLine2D*	Gln2,		// (I  ) ������������Q
//						MINT*		nHk,		// (I O) ������������̒��̐��������������������i�擪�������\���j
//						MgPolyg2D*	pg3			// (  O) �̈�
//				);

//
// ---------------------( �Q���� )------------------------------
//		���p�`�𒼐��Ő؂�A�����̎w�葤�̗̈�𓾂�			<���p�`�����̏ꍇ�̍l���s��?>
//
MINT MGeo::DividePolygonULine2D(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_LEFT			(010): �����̗̈�
												//			MC_RIGHT		(040): �E���̗̈�
				const	MgPolyg2D&	i_pg1,		// (I  ) ���p�`
				const	MgULine2D&	i_uln2,		// (I  ) ����
						MgGPolyg2D*	o_pGpg3		// (  O) ���t�����p�`�Q
				)
{
	MINT		ist = MC_NINT;
	MINT		ist1;
	MINT		ic1, icb;
	MgLine2D		lnw1;
	MgULine2D	uln2;
	MINT		sels;
	MgVect2D		vULn2;
	
	MINT		icls;							// 1: ���p�`�������ƌ������邩�A�����̔�I�𑤂ɂ���ŁA���p�`�̕ӂɍ폜����������

	MGGPOINT2( GPt, MX_PNT1);					// �����Ɛ����̕�����Ɨp�_�G���A
	MGGLINE2( GLn1, MX_PNT1);					// �������ꂽ�|���S���̍\�������̐����Q
	MGGLINE2( GLn2, MX_PNT2);					// �����̕�����Ɨp�����G���A
	MGGPOLYG2( GPgW1, MX_LIN1, MX_LIN0, MX_LIN0); // �����̑I�𑤂̃|���S���Q

	uln2.p  = i_uln2.p;
	if ( i_Sel == MC_LEFT)
		uln2.v = i_uln2.v;
	else
		uln2.v = - i_uln2.v;

	//	���p�`�̕���
	sels = MC_LEFT | MC_ON_LINE | MC_SAME_DIR;
	icls = 0;													// ���p�`�ƒ����Ƃ̌����L�� (0:�����A1:�L��)

	GLn1.m_n = 0;
	for ( icb=i_pg1.m_n-1,ic1=0; ic1<i_pg1.m_n; icb=ic1,icb=ic1,ic1++) {
		lnw1 = MgLine2D( i_pg1.m_p[icb], i_pg1.m_p[ic1]);
		ist1 = DivideAddLineULine2D( sels, lnw1, uln2, &GLn1);
		if ( ist1 != (MC_NINT | MC_MATCH))						// ���p�`�̕ӂɍ폜��������
			 icls = 1;
	}

	if (GLn1.m_n > 0) {											// �����̎w�葤�ɑ��p�`�̕ӂ�����
		if ( icls == 0) {
			GPgW1 += i_pg1;										// ���������Ȃ炻�̂܂܎c��
		} else {
			GLn2 += GLn1;										// ��������Ȃ璼���̎w�葤�̐����̂݁A�V�K�̈�쐬�p�����Q�ɒǉ�����
			MF_SET_ON( ist, MC_INT);
		}
		MF_SET_ON( ist, MC_MATCH);
	}
//
//	�����̕���

	ist1 = DivideAddULinePolygon2D( MC_IN_BORDER, uln2, i_pg1, &GLn2);
	
	ist |= ist1;
//
	MakeGPolygonInGLine2D( GLn2, o_pGpg3);								// GLine2D(�����������������Ă�������Q)���̈�Q���쐬����
	
	*o_pGpg3 += GPgW1;											// �̈�Q��Ԃ�

	if ( MF_CHECK_ON( ist, MC_INT))
		MF_SET_OFF( ist, MC_NINT);								// ��������Ȃ�����Ȃ��̃t���O������

	return ist;
}
//
// ---------------------( �Q���� )------------------------------
//		���t�����p�`�𒼐��Ő؂�A�����̎w�葤�̗̈�𓾂�
//
MINT MGeo::DivideGPolygonULine2D(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_LEFT			(010): �����̗̈�
												//			MC_RIGHT		(040): �E���̗̈�
				const	MgGPolyg2D&	i_Gpg1,		// (I  ) ���t�����p�`
				const	MgULine2D&	i_uln2,		// (I  ) ����
						MgGPolyg2D*	o_pGpg3		// (  O) ���t�����p�`�Q
				)
{
	MINT		ist = MC_NINT;
	MINT		ist1;
	MINT		ic1, ic2, icb;
	MgLine2D		lnw1;
	MINT		sels;
	MgULine2D	uln2;
	
	MgPolyg2D*	pg1;
	MINT		icls;

	MGGPOINT2( GPt, MX_PNT1);					// �����Ɛ����̕�����Ɨp�_�G���A
	MGGLINE2( GLn1, MX_PNT1);					// �������ꂽ�|���S���̍\�������̐����Q
	MGGLINE2( GLn2, MX_PNT2);					// �����̕�����Ɨp�����G���A
	MGGPOLYG2( GPgW1, MX_LIN1, MX_LIN0, MX_LIN0); // �����̑I�𑤂̃|���S���Q

	uln2.p  = i_uln2.p;
	if ( i_Sel == MC_LEFT)
		uln2.v = i_uln2.v;
	else
		uln2.v = - i_uln2.v;

	//	���t�����p�`�̕���
																// �����ƌ��t�����p�`�̑S�Ẵ|���S���Ƃ̌�_�����߂�
	for ( ic1=0; ic1<i_Gpg1.m_n; ic1++) {
		pg1 = &(i_Gpg1.m_pg[ic1]);
		
		sels = MC_LEFT | MC_ON_BORDER | MC_SAME_DIR;
		icls = 0;												// �|���S���ƒ����Ƃ̌����L�� (0:�����A1:�L��)

		//	���p�`�̕���
		GLn1.m_n = 0;
		for ( icb=pg1->m_n-1,ic2=0; ic2<pg1->m_n; icb=ic2,ic2++) {
			lnw1 = MgLine2D( pg1->m_p[icb], pg1->m_p[ic2]);
			ist1 = DivideAddLineULine2D( sels, lnw1, uln2, &GLn1);
			if ( ist1 != (MC_NINT | MC_MATCH))					// ���p�`�̕ӂɍ폜��������
				 icls = 1;
		}

		if (GLn1.m_n > 0) {										// �����̎w�葤�ɂ���
			if ( icls == 0) {
				GPgW1 += *pg1;									// ���������Ȃ炻�̂܂܎c��
			} else {
				GLn2 += GLn1;									// ��������Ȃ璼���̎w�葤�̐����̂݁A�V�K�̈�쐬�p�����Q�ɒǉ�����
				MF_SET_ON( ist, MC_INT);
			}
			MF_SET_ON( ist, MC_MATCH);
		}
	}
//
//	�����̕���

	ist1 = DivideAddULineGPolygon2D( MC_IN_BORDER, uln2, i_Gpg1, &GLn2);
	
	MF_SET_ON( ist, ist1);
//
	MakeGPolygonInGLine2D( GLn2, o_pGpg3);								// GLine2D(�����������������Ă�������Q)���̈�Q���쐬����
	
	*o_pGpg3 += GPgW1;											// �̈�Q��Ԃ�

	if ( MF_CHECK_ON( ist, MC_INT))
		MF_SET_OFF( ist, MC_NINT);								// ��������Ȃ�����Ȃ��̃t���O������

	return ist;
}
//
// ---------------------( �Q���� )------------------------------
//		���p�`1�𑽊p�`2�ŕ������A���p�`2�̎w�葤�i�����܂��͊O���j�̗̈�𓾂�
//
MINT MGeo::Divide2Polygon2D(							// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_OUT_BORDER	(004): �O��
												//									
				const	MgPolyg2D&	i_pg1,		// (I  ) ���p�`1
				const	MgPolyg2D&	i_pg2,		// (I  ) ���p�`2
						MgGPolyg2D*	o_pGpgo		// (  O) ���t�����p�`3
				)
{
	MINT	Selc;

	if ( i_Sel == MC_IN_BORDER)
		Selc = MC_AND;
	else if ( i_Sel == MC_OUT_BORDER)
		Selc = MC_DIFF;

	return Merge2PgtoGPolygon2D( Selc, i_pg1, i_pg2, o_pGpgo);
}

//
// ---------------------( �Q���� )------------------------------
//		���t�����p�`�����t�����p�`�ŕ������A�I�������ɍ����̈�𓾂�
//
MINT MGeo::Divide2GPolygon2D(							// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_OUT_BORDER	(004): �O��
				const	MgGPolyg2D&	i_Gpg1,		// (I  ) ���t�����p�`1
				const	MgGPolyg2D&	i_Gpg2,		// (I  ) ���t�����p�`2
						MgGPolyg2D*	o_pGpgo		// (  O) ���t�����p�`3
				)
{
	MINT	Selc;

	if ( i_Sel == MC_IN_BORDER)
		Selc = MC_AND;
	else if ( i_Sel == MC_OUT_BORDER)
		Selc = MC_DIFF;

	return Merge2GPgtoGPolygon2D( Selc, i_Gpg1, i_Gpg2, o_pGpgo);
}

//
// ---------------------( �R���� )------------------------------
//		���p�`1�𑽊p�`2�ŕ������A���p�`2�̎w�葤�i�����܂��͊O���j�̗̈�𓾂�
//
MINT MGeo::Divide2Polygon3D(							// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_OUT_BORDER	(004): �O��
												//									
				const	MgPolyg3D&	i_Pg1,		// (I  ) ���p�`1
				const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`2
						MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
				)
{
	MINT	Selc;

	if ( i_Sel == MC_IN_BORDER)
		Selc = MC_AND;
	else if ( i_Sel == MC_OUT_BORDER)
		Selc = MC_DIFF;

	return Merge2PgtoGPolygon3D( Selc, i_Pg1, i_Pg2, o_pGPgo);
}

//
// ---------------------( �R���� )------------------------------
//		���t�����p�`�����t�����p�`�ŕ������A�I�������ɍ����̈�𓾂�
//
MINT MGeo::Divide2GPolygon3D(							// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_IN_BORDER	(001): ����
												//			MC_OUT_BORDER	(004): �O��
				const	MgGPolyg3D&	i_GPg1,		// (I  ) ���t�����p�`1
				const	MgGPolyg3D&	i_GPg2,		// (I  ) ���t�����p�`2
						MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
				)
{
	MINT	Selc;

	if ( i_Sel == MC_IN_BORDER)
		Selc = MC_AND;
	else if ( i_Sel == MC_OUT_BORDER)
		Selc = MC_DIFF;

	return Merge2GPgtoGPolygon3D( Selc, i_GPg1, i_GPg2, o_pGPgo);
}

//
// ---------------------( �Q���� )------------------------------
//		���p�`�Ƒ��p�`�̘a�A���A�ς̌��t�����p�`�����߂�
//
MINT MGeo::Merge2PgtoGPolygon2D(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_OR			(1): �a
												//			MC_DIFF			(2): ��
												//			MC_AND			(4): ��
				const	MgPolyg2D&	i_pg1,		// (I  ) ���p�`1
				const	MgPolyg2D&	i_pg2,		// (I  ) ���p�`2
						MgGPolyg2D*	o_pGpgo		// (  O) ���t�����p�`3
				)
{
	MINT		ist, ist2;
	MINT		sel1, sel2;
	bool		fRev;

	MGGLINE2( GLnw, MX_PNT1);						// �������ꂽ�|���S���̍\�������̐����Q
	MGGPOLYG2( GPgw, MX_LIN1, MX_PNT0, MX_PNT0);	// �I�𑤂̃|���S���Q
//
	// ���������Ŏc�������w��
	switch ( i_Sel)
	{
	case MC_OR:
		sel1 = MC_OUT_BORDER | MC_ON_BORDER | MC_SAME_DIR;
		sel2 = MC_OUT_BORDER;
		break;
	case MC_DIFF:
		sel1 = MC_OUT_BORDER | MC_ON_BORDER | MC_REV_DIR;
		sel2 = MC_IN_BORDER;
		break;
	case MC_AND:
		sel1 = MC_IN_BORDER | MC_ON_BORDER | MC_SAME_DIR;
		sel2 = MC_IN_BORDER;
		break;
	}
	fRev = ( i_Sel == MC_DIFF);
	//	���p�`1�̐����𑽊p�`2�ŕ������w�葤���c��
	o_pGpgo->SetCount0();
	ist  = DivideAdd2Polygon2D( sel1, false, i_pg1, i_pg2, &GLnw, o_pGpgo);
	ist2 = DivideAdd2Polygon2D( sel2, fRev, i_pg2, i_pg1, &GLnw, o_pGpgo);
	if (GLnw.m_n > 2) {
		MakeGPolygonInGLine2D( GLnw, &GPgw);							// �����������������������Q���̈�Q���쐬����
		*o_pGpgo += GPgw;										// �̈�Q��ǉ�����
	}
//	
	MF_SET_ON( ist, ist2);
	if ( MF_CHECK_ON( ist, MC_INT))
		MF_SET_OFF( ist, MC_NINT);								// ��������Ȃ�����Ȃ��̃t���O������

	return ist;
}

//
// ---------------------( �Q���� )------------------------------
//		���p�`�ƌ��t�����p�`�̘a�A���A�ς̌��t�����p�`�����߂�
//
MINT MGeo::MergePgGPgtoGPolygon2D(					// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_OR			(1): �a
												//			MC_DIFF			(2): ��
												//			MC_AND			(4): ��
				const	MgPolyg2D&	i_pg1,		// (I  ) ���p�`1
				const	MgGPolyg2D&	i_Gpg2,		// (I  ) ���t�����p�`2
						MgGPolyg2D*	o_pGpgo		// (  O) ���t�����p�`3
				)
{
	MINT		ist;
	MINT		ist2;
	MINT		ic2;
	MINT		sel1, sel2;
	bool		fRev;
	MgPolyg2D*	ppg2;

	MGGLINE2( GLnw, MX_PNT1);						// �������ꂽ�|���S���̍\�������̐����Q
	MGGPOLYG2( GPgw, MX_LIN1, MX_PNT0, MX_PNT0);	// �I�𑤂̃|���S���Q
//
	// ���������Ŏc�������w��
	switch ( i_Sel)
	{
	case MC_OR:
		sel1 = MC_OUT_BORDER | MC_ON_BORDER | MC_SAME_DIR;
		sel2 = MC_OUT_BORDER;
		break;
	case MC_DIFF:
		sel1 = MC_OUT_BORDER | MC_ON_BORDER | MC_REV_DIR;
		sel2 = MC_IN_BORDER;
		break;
	case MC_AND:
		sel1 = MC_IN_BORDER | MC_ON_BORDER | MC_SAME_DIR;
		sel2 = MC_IN_BORDER;
		break;
	}
	fRev = ( i_Sel == MC_DIFF);

	o_pGpgo->SetCount0();
	//	���p�`1�̐��������t�����p�`2�ŕ������w�葤���c��
	ist = DivideAddPolygonGPolygon2D( sel1, false, i_pg1, i_Gpg2, &GLnw, o_pGpgo);

	//	���t�����p�`2�̐����𑽊p�`1�ŕ������w�葤���c��
	for ( ic2=0; ic2<i_Gpg2.m_n; ic2++) {
		ppg2 = &i_Gpg2.m_pg[ic2];
		ist2 = DivideAdd2Polygon2D( sel2, fRev, *ppg2, i_pg1, &GLnw, o_pGpgo);
		MF_SET_ON( ist, ist2);
	}
	if (GLnw.m_n > 2) {
		MakeGPolygonInGLine2D( GLnw, &GPgw);									// �����������������������Q���̈�Q���쐬����
		*o_pGpgo += GPgw;											// �̈�Q��ǉ�����
	}

	if ( MF_CHECK_ON( ist, MC_INT))
		MF_SET_OFF( ist, MC_NINT);								// ��������Ȃ�����Ȃ��̃t���O������

	return ist;
}

//
// ---------------------( �Q���� )------------------------------
//		���t�����p�`�Ƒ��p�`�̘a�A���A�ς̌��t�����p�`�����߂�
//
MINT MGeo::MergeGPgPgtoGPolygon2D(					// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_OR			(1): �a
												//			MC_DIFF			(2): ��
												//			MC_AND			(4): ��
				const	MgGPolyg2D&	i_Gpg1,		// (I  ) ���t�����p�`1
				const	MgPolyg2D&	i_pg2,		// (I  ) ���p�`2
						MgGPolyg2D*	o_pGpgo		// (  O) ���t�����p�`3
				)
{
	MINT		ist = MC_NINT;
	MINT		ist1, ist2;
	MINT		ic1;
	MINT		sel1, sel2;
	bool		fRev;
	MgPolyg2D*	ppg1;

	MGGLINE2( GLnw, MX_PNT1);						// �������ꂽ�|���S���̍\�������̐����Q
	MGGPOLYG2( GPgw, MX_LIN1, MX_PNT0, MX_PNT0);	// �I�𑤂̃|���S���Q
//
	// ���������Ŏc�������w��
	switch ( i_Sel)
	{
	case MC_OR:
		sel1 = MC_OUT_BORDER | MC_ON_BORDER | MC_SAME_DIR;
		sel2 = MC_OUT_BORDER;
		break;
	case MC_DIFF:
		sel1 = MC_OUT_BORDER | MC_ON_BORDER | MC_REV_DIR;
		sel2 = MC_IN_BORDER;
		break;
	case MC_AND:
		sel1 = MC_IN_BORDER | MC_ON_BORDER | MC_SAME_DIR;
		sel2 = MC_IN_BORDER;
		break;
	}
	fRev = ( i_Sel == MC_DIFF);

	o_pGpgo->SetCount0();
	//	���t�����p�`1�̐����𑽊p�`2�ŕ������w�葤���c��
	for ( ic1=0; ic1<i_Gpg1.m_n; ic1++) {
		ppg1 = &i_Gpg1.m_pg[ic1];
		//	���p�`1�̐��������t�����p�`2�ŕ������w�葤���c��
		ist1 = DivideAdd2Polygon2D( sel1, false, *ppg1, i_pg2, &GLnw, o_pGpgo);
		MF_SET_ON( ist, ist1);
	}
	//	���p�`2�̐��������t�����p�`1�ŕ������w�葤���c��
	ist2 = DivideAddPolygonGPolygon2D( sel2, fRev, i_pg2, i_Gpg1, &GLnw, o_pGpgo);
	MF_SET_ON( ist, ist2);

	if (GLnw.m_n > 2) {
		MakeGPolygonInGLine2D( GLnw, &GPgw);							// �����������������������Q���̈�Q���쐬����
		*o_pGpgo += GPgw;										// �̈�Q��ǉ�����
	}

	if ( MF_CHECK_ON( ist, MC_INT))
		MF_SET_OFF( ist, MC_NINT);								// ��������Ȃ�����Ȃ��̃t���O������

	return ist;
}

//
// ---------------------( �Q���� )------------------------------
//		���t�����p�`�ƌ��t�����p�`�̘a�A���A�ς̌��t�����p�`�����߂�
//
MINT MGeo::Merge2GPgtoGPolygon2D(						// (  O) �X�e�C�^�X
												//			MC_NINT			(x01): �����Ȃ�
												//			MC_INT			(x02): ��������
												//			MC_MATCH		(x10): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_OR			(1): �a
												//			MC_DIFF			(2): ��
												//			MC_AND			(4): ��
				const	MgGPolyg2D&	i_Gpg1,		// (I  ) ���t�����p�`1
				const	MgGPolyg2D&	i_Gpg2,		// (I  ) ���t�����p�`2
						MgGPolyg2D*	o_pGpgo		// (  O) ���t�����p�`3
				)
{
	MINT		ist = MC_NINT;
	MINT		ic1, ic2;
	MINT		ist1, ist2;
	MINT		sel1, sel2;
	bool		fRev;
	MgPolyg2D*	ppg1;
	MgPolyg2D*	ppg2;

	MGGLINE2( GLnw, MX_PNT1);					// �������ꂽ�|���S���̍\�������̐����Q
	MGGPOLYG2( GPgw, MX_LIN1, MX_PNT0, MX_PNT0);// �I�𑤂̃|���S���Q
//
	// ���������Ŏc�������w��
	switch ( i_Sel)
	{
	case MC_OR:
		sel1 = MC_OUT_BORDER | MC_ON_BORDER | MC_SAME_DIR;
		sel2 = MC_OUT_BORDER;
		break;
	case MC_DIFF:
		sel1 = MC_OUT_BORDER | MC_ON_BORDER | MC_REV_DIR;
		sel2 = MC_IN_BORDER;
		break;
	case MC_AND:
		sel1 = MC_IN_BORDER | MC_ON_BORDER | MC_SAME_DIR;
		sel2 = MC_IN_BORDER;
		break;
	}
	fRev = ( i_Sel == MC_DIFF);
	o_pGpgo->SetCount0();
	//	���t�����p�`1�̐��������t�����p�`2�ŕ������w�葤���c��
	for ( ic1=0; ic1<i_Gpg1.m_n; ic1++) {
		ppg1 = &i_Gpg1.m_pg[ic1];
		//	���p�`1�̐��������t�����p�`2�ŕ������w�葤���c��
		ist1 = DivideAddPolygonGPolygon2D( sel1, false, *ppg1, i_Gpg2, &GLnw, o_pGpgo);
		MF_SET_ON( ist, ist1);
	}
	//	���t�����p�`2�̐��������t�����p�`1�ŕ������w�葤���c��
	for ( ic2=0; ic2<i_Gpg2.m_n; ic2++) {
		ppg2 = &i_Gpg2.m_pg[ic2];
		//	���p�`2�̐��������t�����p�`1�ŕ������w�葤���c��
		ist2 = DivideAddPolygonGPolygon2D( sel2, fRev, *ppg2, i_Gpg1, &GLnw, o_pGpgo);
		MF_SET_ON( ist, ist2);
	}
	if (GLnw.m_n > 2) {
		MakeGPolygonInGLine2D( GLnw, &GPgw);							// �����������������������Q���̈�Q���쐬����
		*o_pGpgo += GPgw;										// �̈�Q��Ԃ�
	}

	if ( MF_CHECK_ON( ist, MC_INT))
		MF_SET_OFF( ist, MC_NINT);								// ��������Ȃ�����Ȃ��̃t���O������

	return ist;
}
//
// ---------------------( �R���� )------------------------------
//		���p�`�Ƒ��p�`�̘a�A���A�ς̌��t�����p�`�����߂�
//
MINT MGeo::Merge2PgtoGPolygon3D(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_OR			(1): �a
												//			MC_DIFF			(2): ��
												//			MC_AND			(4): ��
				const	MgPolyg3D&	i_Pg1,		// (I  ) ���p�`1
				const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`2
						MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
				)
{
	MINT		ist = MC_NINT;
	MgPlane3D	Pln1, Pln2;
	MgMat3E		MatXY;							// Pln to XY���� �R�c�}�g���b�N�X
	MgMat3E		MatPln;							// XY���� to Pln �R�c�}�g���b�N�X

	MGPOLYG2( pg1, MX_PNT0);
	MGPOLYG2( pg2, MX_PNT0);
	MGGPOLYG2( gpg3, MX_LIN1, MX_PNT0, MX_PNT0);

	Pln1 = MgPlanePolygon3D( i_Pg1);							// ���p�`1�̕��ʌW�������o��
	Pln2 = MgPlanePolygon3D( i_Pg2);									// ���p�`2�̕��ʌW�������o��
	if (Pln1 != Pln2)
		MQUIT;													// ���ꕽ�ʏ�ɖ���

	Mat3EPlntoXY( Pln1, i_Pg1.m_P[0], &MatXY, &MatPln);			// �R�c���Q�c�p�ϊ��}�g���b�N�X�Ƌt�ϊ��}�g���b�N�X�����߂�
	Polyg3Dto2D( i_Pg1, MatXY, &pg1);							// ���p�`1���Q�����ɕϊ�����
	Polyg3Dto2D( i_Pg2, MatXY, &pg2);							// ���p�`2���Q�����ɕϊ�����

	ist = Merge2PgtoGPolygon2D( i_Sel, pg1, pg2, &gpg3);
	GPolyg2Dto3D( gpg3, MatPln, o_pGPgo);
exit:
	return ist;
}

//
// ---------------------( �R���� )------------------------------
//		���p�`�ƌ��t�����p�`�̘a�A���A�ς̌��t�����p�`�����߂�
//
MINT MGeo::MergePgGPgtoGPolygon3D(					// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_OR			(1): �a
												//			MC_DIFF			(2): ��
												//			MC_AND			(4): ��
				const	MgPolyg3D&	i_Pg1,		// (I  ) ���p�`1
				const	MgGPolyg3D&	i_GPg2,		// (I  ) ���t�����p�`2
						MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
				)
{
	MINT		ist = MC_NINT;
	MgPlane3D	Pln1, Pln2;
	MgMat3E		MatXY;							// Pln to XY���� �R�c�}�g���b�N�X
	MgMat3E		MatPln;							// XY���� to Pln �R�c�}�g���b�N�X

	MGPOLYG2( pg1, MX_PNT0);
	MGGPOLYG2( gpg2, MX_LIN1, MX_PNT0, MX_PNT0);
	MGGPOLYG2( gpg3, MX_LIN1, MX_PNT0, MX_PNT0);
//

	Pln1 = MgPlanePolygon3D( i_Pg1);										// ���p�`1�̕��ʌW�������o��
	Pln2 = MgPlanePolygon3D( i_GPg2.m_Pg[0]);								// ���t�����p�`2�̕��ʌW�������o��
	if (Pln1 != Pln2)
		MQUIT;													// ���ꕽ�ʏ�ɖ���

	Mat3EPlntoXY( Pln1, i_Pg1.m_P[0], &MatXY, &MatPln);			// �R�c���Q�c�p�ϊ��}�g���b�N�X�Ƌt�ϊ��}�g���b�N�X�����߂�
	Polyg3Dto2D( i_Pg1, MatXY, &pg1);							// ���t�����p�`1���Q�����ɕϊ�����
	GPolyg3Dto2D( i_GPg2, MatXY, &gpg2);						// ���t�����p�`2���Q�����ɕϊ�����

	ist = MergePgGPgtoGPolygon2D( i_Sel, pg1, gpg2, &gpg3);
	GPolyg2Dto3D( gpg3, MatPln, o_pGPgo);
exit:
	return ist;
}

//
// ---------------------( �R���� )------------------------------
//		���t�����p�`�Ƒ��p�`�̘a�A���A�ς̌��t�����p�`�����߂�
//
MINT MGeo::MergeGPgPgtoGPolygon3D(					// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_OR			(1): �a
												//			MC_DIFF			(2): ��
												//			MC_AND			(4): ��
				const	MgGPolyg3D&	i_GPg1,		// (I  ) ���t�����p�`1
				const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`2
						MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
				)
{
	MINT		ist = MC_NINT;
	MgPlane3D	Pln1, Pln2;
	MgMat3E		MatXY;							// Pln to XY���� �R�c�}�g���b�N�X
	MgMat3E		MatPln;							// XY���� to Pln �R�c�}�g���b�N�X
	MgMat3E		Dbg1;
	MgMat3E		Dbg2;
	MGGPOLYG2( gpg1, MX_LIN1, MX_PNT0, MX_PNT0);
	MGPOLYG2( pg2, MX_PNT0);
	MGGPOLYG2( gpg3, MX_LIN1, MX_PNT0, MX_PNT0);
//
	Pln1 = MgPlanePolygon3D( i_GPg1.m_Pg[0]);							// ���t�����p�`1�̕��ʌW�������o��
	Pln2 = MgPlanePolygon3D( i_Pg2);									// ���p�`2�̕��ʌW�������o��
	if (Pln1 != Pln2)
		MQUIT;													// ���ꕽ�ʏ�ɖ���

	Mat3EPlntoXY( Pln1, i_GPg1.m_Pg[0].m_P[0], &MatXY, &MatPln);	// �R�c���Q�c�p�ϊ��}�g���b�N�X�Ƌt�ϊ��}�g���b�N�X�����߂�
	Dbg1 = MatXY * MatPln;
	Dbg2 = MatPln * MatXY;
	GPolyg3Dto2D( i_GPg1, MatXY, &gpg1);						// ���t�����p�`1���Q�����ɕϊ�����
	Polyg3Dto2D( i_Pg2, MatXY, &pg2);							// ���t�����p�`2���Q�����ɕϊ�����

	ist = MergeGPgPgtoGPolygon2D( i_Sel, gpg1, pg2, &gpg3);
	GPolyg2Dto3D( gpg3, MatPln, o_pGPgo);
exit:
	return ist;
}

//
// ---------------------( �R���� )------------------------------
//		���t�����p�`�ƌ��t�����p�`�̘a�A���A�ς̌��t�����p�`�����߂�
//
MINT MGeo::Merge2GPgtoGPolygon3D(						// (  O) �X�e�C�^�X
												//			MC_NINT			(0): �����Ȃ�
												//			MC_INT			(1): ��������
												//			MC_MATCH		(4): �I�������ɍ�����������
												//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
												//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
												//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel,		// (I  ) �I������
												//			MC_OR			(1): �a
												//			MC_DIFF			(2): ��
												//			MC_AND			(4): ��
				const	MgGPolyg3D&	i_GPg1,		// (I  ) ���t�����p�`1
				const	MgGPolyg3D&	i_GPg2,		// (I  ) ���t�����p�`2
						MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
				)
{
	MINT		ist = MC_NINT;
	MgPlane3D	Pln1, Pln2;
	MgMat3E		MatXY;								// Pln to XY���� �R�c�}�g���b�N�X
	MgMat3E		MatPln;								// XY���� to Pln �R�c�}�g���b�N�X

	MGGPOLYG2( gpg1, MX_LIN1, MX_PNT0, MX_PNT0);
	MGGPOLYG2( gpg2, MX_LIN1, MX_PNT0, MX_PNT0);
	MGGPOLYG2( gpg3, MX_LIN1, MX_PNT0, MX_PNT0);
//

	Pln1 = MgPlanePolygon3D( i_GPg1.m_Pg[0]);							// ���t�����p�`1�̕��ʌW�������o��
	Pln2 = MgPlanePolygon3D( i_GPg2.m_Pg[0]);							// ���t�����p�`2�̕��ʌW�������o��
	if (Pln1 != Pln2)
		MQUIT;													// ���ꕽ�ʏ�ɖ���

	Mat3EPlntoXY( Pln1, i_GPg1.m_Pg[0].m_P[0], &MatXY, &MatPln);		// �R�c���Q�c�p�ϊ��}�g���b�N�X�Ƌt�ϊ��}�g���b�N�X�����߂�
	GPolyg3Dto2D( i_GPg1, MatXY, &gpg1);							// ���t�����p�`1���Q�����ɕϊ�����
	GPolyg3Dto2D( i_GPg2, MatXY, &gpg2);							// ���t�����p�`2���Q�����ɕϊ�����

	ist = Merge2GPgtoGPolygon2D( i_Sel, gpg1, gpg2, &gpg3);
	GPolyg2Dto3D( gpg3, MatPln, o_pGPgo);
exit:
	return ist;
}

//
// ---------------------( �Q���� )------------------------------
//		���p�`�̕Ӂi�����j�𑼂̑��p�`�ŕ������A�w�肵�����̐������c��
//								���������p�`�̕ӏ�ɂ���ꍇ�́A
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
//				(3) ���̑��̏ꍇ�͎̂Ă�
//
MINT MGeo::DivideAdd2Polygon2D(							// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel1,			// (I  ) �I������1�@���p�`1�̐������c������
													//			MC_IN_BORDER	(001):	���p�`2�̗̈�̓���
													//			MC_ON_BORDER	(002):  ���p�`2�̕ӏ�
													//			MC_OUT_BORDER	(004):	���p�`2�̗̈�̊O��
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
													//			MC_REV_DIR		(0200):	�ӏ�t����
				const	bool		i_fRev,			// (I  ) ���]�t���O	
													//		 true: �����̕����𔽓]����
				const	MgPolyg2D&	i_pg1,			// (I  ) ���p�`1
				const	MgPolyg2D&	i_pg2,			// (I  ) ���p�`2
						MgGLine2D*	io_pGlno,		// (I O) �����Q
						MgGPolyg2D*	io_pGpgo		// (I O) ���t�����p�`
				)
{
	MINT		ist = MC_NINT;
	MINT		ist1;
	MINT		icb, ic1;
	MgLine2D		lnw1;

	bool		fcls;								// �|���S���ƒ����Ƃ̌����L�� (0:�����A1:�L��)
	
	MGGLINE2( GLnw, MX_PNT1);						// �������ꂽ�|���S���̍\�������̐����Q
//
	//	���p�`1�̐����𑽊p�`2�ŕ������w�葤���c��
	fcls = false;												// ���p�`1�̐����Ƒ��p�`2�Ƃ̌����L�� (0:�����A1:�L��)
	for ( icb=i_pg1.m_n-1,ic1=0; ic1<i_pg1.m_n; icb=ic1,ic1++) {
		lnw1 = MgLine2D( i_pg1.m_p[icb], i_pg1.m_p[ic1]);		// �����𑽊p�`�Ő؂�
		ist1 = DivideAddLinePolygon2D( i_Sel1, lnw1, i_pg2, &GLnw);
		if (!MF_CHECK_AND( ist1, (MC_NINT | MC_MATCH)))			// ���p�`�̕ӂɍ폜��������(�����܂��͑I��͈͊O��)
			 fcls = true;
	}

	if (GLnw.m_n > 0) {											// ���p�`2�̎w�葤�ɑ��p�`1�̕ӂ�����
		if (fcls) {
			if ( i_fRev) GLnw.Rev();
			*io_pGlno += GLnw;									// ��������Ȃ�����̎w�葤�̐����̂݁A�V�K�̈�쐬�p�����Q�ɒǉ�����
			ist = MC_INT;
		} else {
			*io_pGpgo += i_pg1;									// ���������Ȃ炻�̑��p�`�̂܂܎c��
			if ( i_fRev) io_pGpgo->m_pg[io_pGpgo->m_n - 1].Rev();
		}
		MF_SET_ON( ist, MC_MATCH);
	}


	return ist;
}

//
// ---------------------( �Q���� )------------------------------
//		���p�`�̕Ӂi�����j�����t�����p�`�ŕ������A�w�肵�����̐������c��
//								���������p�`�̕ӏ�ɂ���ꍇ�́A
//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
//				(3) ���̑��̏ꍇ�͎̂Ă�
//

MINT MGeo::DivideAddPolygonGPolygon2D(							// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
						MINT		i_Sel1,			// (I  ) �I������1�@���p�`1�̐������c������
													//			MC_IN_BORDER	(001): ���p�`2�̗̈�̓���
													//			MC_ON_BORDER	(002): ���p�`2�̕ӏ�
													//			MC_OUT_BORDER	(004): ���p�`2�̗̈�̊O��
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
													//			MC_REV_DIR		(0200):	�ӏ�t����
				const	bool		i_fRev,			// (I  ) ���]�t���O	
													//		 true: �����̕����𔽓]����
				const	MgPolyg2D&	i_pg1,			// (I  ) ���p�`1
				const	MgGPolyg2D&	i_Gpg2,			// (I  ) ���t�����p�`2
						MgGLine2D*	io_pGlno,		// (I O) �����Q
						MgGPolyg2D*	io_pGpgo		// (I O) ���t�����p�`
				)
{
	MINT		ist = MC_NINT;
	MINT		ist1;
	MINT		icb, ic1;
	MgLine2D		lnw1;

	bool		fcls;								// �|���S���ƒ����Ƃ̌����L�� (0:�����A1:�L��)
	
	MGGLINE2( GLnw, MX_PNT1);						// �������ꂽ�|���S���̍\�������̐����Q
//
	//	���p�`1�̐��������t�����p�`2�ŕ������w�葤���c��
	fcls = false;												// ���p�`1�̐����ƌ��t�����p�`2�Ƃ̌����L�� (0:�����A1:�L��)
	for ( icb=i_pg1.m_n-1,ic1=0; ic1<i_pg1.m_n; icb=ic1,ic1++) {
		lnw1 = MgLine2D( i_pg1.m_p[icb], i_pg1.m_p[ic1]);		// ���������t�����p�`�Ő؂�
		ist1 = DivideAddLineGPolygon2D( i_Sel1, lnw1, i_Gpg2, &GLnw);
		if (!MF_CHECK_AND( ist1, (MC_NINT | MC_MATCH)))			// ���p�`1�̕ӂɍ폜��������(�����܂��͑I��͈͊O��)
			 fcls = true;
	}

	if (GLnw.m_n > 0) {											// ���t�����p�`2�̎w�葤�ɑ��p�`1�̕ӂ�����
		if (fcls) {
			if ( i_fRev) GLnw.Rev();
			*io_pGlno += GLnw;									// ��������Ȃ�����̎w�葤�̐����̂݁A�V�K�̈�쐬�p�����Q�ɒǉ�����
			ist = MC_INT;
		} else {
			*io_pGpgo += i_pg1;									// ���������Ȃ炻�̑��p�`�̂܂܎c��
			if ( i_fRev) io_pGpgo->m_pg[io_pGpgo->m_n - 1].Rev();
		}
		MF_SET_ON( ist, MC_MATCH);
	}
	return ist;
}

//
// ---------------------( �Q���� )------------------------------
//		GLn1�̕������l�����Đڑ����̈�Q���쐬����
//

#define	MX_AREA_BY_PT	20						// �P�_�̎���̍ő�̈搔

void MGeo::MakeGPolygonInGLine2D(
				const	MgGLine2D&	i_Gln1,		// (I  ) �������������������Q
						MgGPolyg2D*	o_pGpg3		// (  O) �̈�Q
				)
{
	bool		bst1;
	MINT		ic1;
	MgLine2D		Lnh1;
	MINT		nHk;								// ��������������������

	MBMALCGLINE2(	gLnW1,	i_Gln1.m_n,		MX_PNT2);			// ������Ɨ̈�
	MGPOLYG2(		pgW1,	MX_PNT1);							// ���p�`���_

	o_pGpg3->SetCount0();
	gLnW1 = i_Gln1;

	for (;gLnW1.m_n > 0;)	{
		MgLine2D	Lnh1 = gLnW1.m_ln[0];						// ������Ɨ̈���ŏ��̂P�{�����o��
		for ( ic1=1; ic1<gLnW1.m_n; ic1++)						// ������Ɨ̈悩�炻�̐������Ԉ���
			gLnW1.m_ln[ic1-1] = gLnW1.m_ln[ic1];
		gLnW1.m_n--;
		nHk = gLnW1.m_n;
		bst1 = MakeGPolygonFromLineInGLine2D( Lnh1, &gLnW1, &nHk, &pgW1);
		if (bst1)
			(*o_pGpg3) += pgW1;
	}
}

//
// ---------------------( �Q���� )------------------------------
//		GLn1�̕������l�����Ē�����������GLn2��ǉ����̈�Q���쐬����
//
void MGeo::MakeGPolygonIn2GLine2D(
				const	MgGLine2D&	i_Gln1,		// (I  ) �������������������Q
				const	MgGLine2D&	i_Gln2,		// (I  ) �s���m�ȕ����̐����Q
						MgGPolyg2D*	o_Gpg3		// (  O) �̈�Q
				)
{
	bool		bst;
	MINT		ic1;
	MgLine2D		Lnh1;
	MINT		nHk;								// ��������������������

	MBMALCGLINE2( GLnW1, i_Gln1.m_n+i_Gln2.m_n, MX_PNT2);		// ������Ɨ̈�
	MGPOLYG2( PgW1,	MX_PNT1);									// ���p�`���_

	o_Gpg3->SetCount0();
	GLnW1 = i_Gln1;
	GLnW1 += i_Gln2;
	nHk = i_Gln1.m_n;

	MINT	ifstart = 1;
	for (;!ifstart || nHk>0;)	{
		MgLine2D Lnh1 = GLnW1.m_ln[0];							// ������Ɨ̈���ŏ��̂P�{�����o��
		for ( ic1=1; ic1<GLnW1.m_n; ic1++)						// ������Ɨ̈悩�炻�̐������Ԉ���
			GLnW1.m_ln[ic1-1] = GLnW1.m_ln[ic1];
		GLnW1.m_n--;
		nHk--;
		bst = MakeGPolygonFromLineInGLine2D( Lnh1, &GLnW1, &nHk, &PgW1);
		if (bst)
			(*o_Gpg3) += PgW1;
	}
}

//
// ---------------------( �Q���� )------------------------------
//		�w��������n�܂�����Q�̐�������_�ŕ�����Ɍ������čŏ��̑��p�`���쐬����
//
bool MGeo::MakeGPolygonFromLineInGLine2D(				// (  O) �X�e�C�^�X�@true: ����쐬�@false: �쐬�s��
				const	MgLine2D&	i_ln1,		// (I  ) �w�����
				const	MgGLine2D&	i_Gln2,		// (I  ) ������������Q
						MgPolyg2D*	o_ppg3		// (  O) �̈�
				)
{
	bool		bst;
	MINT		nHk;
	MgGLine2D	GLn2t;

	MBMALCGLINE2( GLnW1, i_Gln2.m_n * 2, MX_PNT2);				// ������Ɨ̈�
	MGPOLYG2( PgW1,	MX_PNT1);									// ���p�`���_

	o_ppg3->m_n = 0;
	DivideGLine2D( i_Gln2, &GLnW1);
	nHk = 0;
	GLn2t = i_Gln2;

	bst = MakeGPolygonFromLineInGLine2D( i_ln1, &GLnW1, &nHk, &PgW1);
	if (bst)
		*o_ppg3 = PgW1;
	return bst;
}

//
// ---------------------( �Q���� )------------------------------
//		�w��������n�܂�����Q�̐������������čŏ��̑��p�`���쐬����
//
bool MGeo::MakeGPolygonFromLineInGLine2D(				// (  O) �X�e�C�^�X�@true: ����쐬�@false: �쐬�s��
				const	MgLine2D&	i_ln1,		// (I  ) �w�����
						MgGLine2D*	io_Gln2,	// (I O) ������������Q
						MINT*		io_nHk,		// (I O) ������������̒��̐��������������������i�擪�������\���j
						MgPolyg2D*	o_pg3		// (  O) �̈�
				)
{
	bool		bst;
	MINT		ic1, ic2;
	MINT		nc1;
	MgPoint2D	PtF, PtS, PtE;
	MINT		nPtW1;
	MINT		mxic;
	MREAL		mxcc;

	MgVect2D		V1;
	MgVect2D		V2;
	MREAL		ss;
	MREAL		cc;

	MGPOLYG2( PgW1,		MX_PNT1);

	MBBUFF(			PtW1,	MgPoint2D,	MX_PNT0); 
	MBBUFF(			iPtW1,	MINT,		MX_PNT0); 

	o_pg3->m_n = 0;

	PtS = i_ln1.p[0];
	PtF = PtS;
	PtE = i_ln1.p[1];

	PgW1 += PtS;
	PgW1 += PtE;

	for (;;) {
		nPtW1 = 0;
		for ( ic1=0; ic1<io_Gln2->m_n; ic1++) {						// �I�_�ɐڑ��������������
			if (PtE == io_Gln2->m_ln[ic1].p[0]) {
				PtW1[nPtW1] = io_Gln2->m_ln[ic1].p[1];
				iPtW1[nPtW1++] = ic1;
			}
		}
		for ( ic1=*io_nHk; ic1<io_Gln2->m_n; ic1++) {
			if (PtE == io_Gln2->m_ln[ic1].p[1]) {
				PtW1[nPtW1] = io_Gln2->m_ln[ic1].p[0];
				iPtW1[nPtW1++] = ic1;
			}
		}
		if ( nPtW1 == 0) {										// �����Ȃ��A�I�_��O�̐������폜
			PgW1.m_n--;
			if (PgW1.m_n < 2) {
				bst = false;
				break;
			} else {
				PtE = PtS;
				PtS = PgW1.m_p[PgW1.m_n - 2];
			}
		} else {
			if ( nPtW1 == 1) {									// ������1���������ꍇ�͂��̐�����ڑ�
				mxic = 0;
			} else {
				V1 = (PtS - PtE).Unitize();						// �������������������ꍇ�͂����Ƃ������̐�����ڑ�
				mxcc = -9.0f;
				for ( ic2=0; ic2<nPtW1; ic2++) {
					V2 = (PtW1[ic2] - PtE).Unitize();
					ss = V1 ^ V2;
					cc = V1 * V2;
					if (ss > 0) cc = -cc - 2.0f;
					if (cc > mxcc) {
						mxcc = cc;
						mxic = ic2;
					}
				}
			}
			if (PtW1[mxic] == PtF) {
				*o_pg3 = PgW1;									// �I�_�Ƒ��p�`�̊J�n�_������ʒu�̏ꍇ�́A�P�̑��p�`
				bst = true;
				break;
			} else {
				PtS = PtE;
				PtE = PtW1[mxic];
				PgW1 += PtE;									// ��������������ڑ�
			}
			nc1 = iPtW1[mxic];									// ������Ɨ̈悩��ڑ��ς݂̐������Ԉ���
			for ( ic1=1; ic1<io_Gln2->m_n; ic1++) {
				if ( ic1 > nc1)
					io_Gln2->m_ln[ic1-1] = io_Gln2->m_ln[ic1];
			}
			io_Gln2->m_n--;
			if ( nc1 < *io_nHk) (*io_nHk)--;
		}
	}
	return	bst;
}

//
// ---------------------( �Q���� )------------------------------
//		���t�����p�`�𑽊p�`�Ɍ�������
//
void MGeo::ConnectGPolygontoPolygon2D(						//
				const	MgGPolyg2D&	i_GpgI,		// (I  ) ���t�����p�`
						MgPolyg2D*	o_pgO		// (  O) ������̑��p�`
				)
{
	MINT			ic0, ic1, ic1a, ic2, ic2a;
	MINT			ic1amin, ic2min, ic2amin;
	MgGPolyg2D		GpgW;
	MGPOLYG2( pgW, 100);
	MgPoint2D		pt1;
	MgVect2D			v12;
	MREAL			rL2, rMinL2;

	GpgW = i_GpgI;
	for ( ic1=GpgW.m_n-1; ic1>0; ic1--) {
		rMinL2 = MREALMAX;
		for ( ic1a=0; ic1a<GpgW.m_pg[ic1].m_n; ic1a++) {
			pt1 = GpgW.m_pg[ic1].m_p[ic1a];
			for ( ic2=0; ic2<ic1; ic2++) {
				for ( ic2a=0; ic2a<GpgW.m_pg[ic2].m_n; ic2a++) {
					v12 = GpgW.m_pg[ic2].m_p[ic2a] - pt1;
					rL2 = v12.x * v12.x + v12.y * v12.y;
					if (rL2 < rMinL2) {
						ic1amin = ic1a;
						ic2min = ic2;
						ic2amin = ic2a;
						rMinL2 = rL2;
					}
				}
			}
		}
		pgW.m_n = 0;
		for ( ic0=0; ic0<=ic2a; ic0++)
			pgW += GpgW.m_pg[ic2].m_p[ic0];
		for ( ic0=ic1a; ic0<GpgW.m_pg[ic1].m_n; ic0++)
			pgW += GpgW.m_pg[ic1].m_p[ic0];
		for ( ic0=0; ic0<=ic1a; ic0++)
			pgW += GpgW.m_pg[ic1].m_p[ic0];
		for ( ic0=ic2a; ic0<GpgW.m_pg[ic2].m_n; ic0++)
			pgW += GpgW.m_pg[ic2].m_p[ic0];
		GpgW.m_pg[ic2] = pgW;
	}
	*o_pgO = GpgW.m_pg[0];
}

//
// ---------------------( �R���� )------------------------------
//		���t�����p�`�𑽊p�`�Ɍ�������
//
void MGeo::ConnectGPolygontoPolygon3D(						//
				const	MgGPolyg3D&	i_GPgI,		// (I  ) ���t�����p�`
				const	MgVect3D&	i_VuH,		// (I  ) �@������
						MgPolyg3D*	o_pPgO		// (  O) ������̑��p�`
				)
{
	MINT			ic0, ic1, ic1a, ic2, ic2a;
	MINT			ic2a1, ic2a2;
	MINT			ic1b1, ic1b2;
	MINT			ic1amin, ic2min, ic2amin;
	MgGPolyg3D		gPgW;
	MGPOLYG3( PgW, 100);
	MgPoint3D		Pt1;
	MgVect3D			V12;
	MREAL			rL2, rMinL2;
	MgVect3D			V1, V1p, V2, V2p;

//								gPgI.Print( Mstr( "051127 ���t�����p�`�𑽊p�`�Ɍ��� gPgI"));

	gPgW = i_GPgI;
	for ( ic1=gPgW.m_n-1; ic1>0; ic1--) {
		rMinL2 = MREALMAX;

		for ( ic1a=0; ic1a<gPgW.m_Pg[ic1].m_n; ic1a++) {
			Pt1 = gPgW.m_Pg[ic1].m_P[ic1a];
			for ( ic2=0; ic2<ic1; ic2++) {
				ic2a2 = gPgW.m_Pg[ic2].m_n - 2;
				ic2a1 = ic2a2 + 1;

				for ( ic2a=0; ic2a<gPgW.m_Pg[ic2].m_n; ic2a2=ic2a1,ic2a1=ic2a,ic2a++) {
					V12 = gPgW.m_Pg[ic2].m_P[ic2a1] - Pt1;
					rL2 = V12 * V12;											// �����̓��

					if ((rL2 - rMinL2) * (rL2 - rMinL2) < MGPTOL->D_2 * 4 * rL2) {
						V1 = gPgW.m_Pg[ic2min].m_P[ic2a1] - gPgW.m_Pg[ic2min].m_P[ic2a2];
						V1p = Pt1 - gPgW.m_Pg[ic2min].m_P[ic2a2];
						V2 = gPgW.m_Pg[ic2min].m_P[ic2a] - gPgW.m_Pg[ic2min].m_P[ic2a1];
						V2p = Pt1 - gPgW.m_Pg[ic2min].m_P[ic2a1];
						if ((V1 ^ V1p) * i_VuH < 0 || (V2 ^ V2p) * i_VuH < 0)
							continue;											// �ŏ��Ɠ��ꋗ���̓_�ł��邪����
					} else if (rL2 > rMinL2) {
						continue;												// �ŏ��Ŗ���
					}

					ic1amin	= ic1a;												// �ŏ�
					ic2min = ic2;
					ic2amin = ic2a1;
					rMinL2 = rL2;
				}
			}
		}
		// �Ō�̃|���S���Ƌ�������ԋ߂��|���S�������̂��A�Ō�̃|���S������菜��
		PgW.m_n = 0;
		for ( ic0=0; ic0<=ic2amin; ic0++)
			PgW += gPgW.m_Pg[ic2min].m_P[ic0];
		for ( ic0=ic1amin; ic0<gPgW.m_Pg[ic1].m_n; ic0++)
			PgW += gPgW.m_Pg[ic1].m_P[ic0];
		for ( ic0=0; ic0<=ic1amin; ic0++)
			PgW += gPgW.m_Pg[ic1].m_P[ic0];
		for ( ic0=ic2amin; ic0<gPgW.m_Pg[ic2min].m_n; ic0++)
			PgW += gPgW.m_Pg[ic2min].m_P[ic0];
		gPgW.m_Pg[ic2min] = PgW;
	}
//								PgW.Print( L"PgW");
//								gPgW.pg[0].Print( Mstr( "gPgW.pg[0]"));
	*o_pPgO = gPgW.m_Pg[0];
//								PgO->Print( L"PgO");
	o_pPgO->m_n = 0;
//								PgO->Print( L"PgO_0");
	ic1b2 = gPgW.m_Pg[0].m_n -2;
	ic1b1 = ic1b2 + 1;
	for ( ic1=0; ic1<gPgW.m_Pg[0].m_n; ic1b2=ic1b1, ic1b1=ic1,ic1++) {
		V1 = gPgW.m_Pg[0].m_P[ic1b1] - gPgW.m_Pg[0].m_P[ic1b2];
		V2 = gPgW.m_Pg[0].m_P[ic1] - gPgW.m_Pg[0].m_P[ic1b2];

//								MBLOGPRINTI( L"Count", ic1);
//								V1.Print( L"V1");
//								V2.Print( L"V2");
//								MREAL V22 = V2 * V2;			MBLOGPRINTF( L"V22", V22);
		// �R�_�������ɕ���ł���ꍇ�͒����̓_���Ԉ�������
		MREAL D12 = (V1 ^ V2) * i_VuH;
			MBLOGPRINTF( L"D12", D12);
			MBLOGPRINTF( L"MGPTOL->D_2", MGPTOL->D_2);
		if (D12 * D12 > V2 * V2 * MGPTOL->D_2)
			(*o_pPgO) += gPgW.m_Pg[0].m_P[ic1b1];
	}
//								PgO->Print( Mstr( "051127 ���t�����p�`�𑽊p�`�Ɍ��� PgO"));
//								MBLOGFLUSH;
}

} // namespace MC
