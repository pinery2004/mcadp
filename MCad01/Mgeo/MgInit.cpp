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

#define DLL_EXPORT_TOLERANCE_DO
#include "MgTol.h"


//
//===========================================================================
//		���e�덷
//
MgTol_Dt	g_gTol;

//	MREAL	MgTol_Dt::DN=0.01f;					//	�[������p	Normarize�p�����ŏ�����
//	MREAL	MgTol_Dt::ZN=0.01f;					//	�[������p	Normarize�p�������ŏ������i���ݕs�g�p�j
	MREAL	MgTol_Dt::D=0.01f;					//	������W����p	��������		���e�덷
	MREAL	MgTol_Dt::L=0.00001f;				//	����_�����W����p	��������	���e�덷
	MREAL	MgTol_Dt::U=0.0001f;				//	����P�ʃx�N�g������p			���e�덷
	MREAL	MgTol_Dt::A=0.0001f;				//	����p�x����p	�p�x(���W�A��)	���e�덷
	MREAL	MgTol_Dt::S=0.01f;					//	���ꕽ�ʔ���p	����			���e�덷
	MREAL	MgTol_Dt::D_2=0.01f;				//	������W����p	��������		���e�덷**2
	MREAL	MgTol_Dt::U_2=0.0001f;				//	����P�ʃx�N�g������p			���e�덷**2
	MREAL	MgTol_Dt::A_2=0.0000001f;			//	����p�x����p	�p�x(���W�A��)	���e�덷**2
	MREAL	MgTol_Dt::S_2=0.0001f;				//	���ꕽ�ʔ���p	����			���e�덷**2
	MREAL	MgTol_Dt::L_2=0.000000001f;			//	����_�����W����p	��������	���e�덷**2
