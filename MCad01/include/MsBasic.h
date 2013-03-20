#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsBasic.h
//
//		��{�@�萔�E�֐�
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================
//#ifndef WINVER				// Windows XP �ȍ~�̃o�[�W�����ɌŗL�̋@�\�̎g�p�������܂��B
//#define WINVER 0x0501		// ����� Windows �̑��̃o�[�W���������ɓK�؂Ȓl�ɕύX���Ă��������B
//#endif
//
//#pragma warning( disable : 4996 )
//
//#include <afxwin.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//===========================================================================
//	�V�X�e���ݒ�

#include	"MsDefMCad.h"
#include	"MsDefConst.h"
#include	"MsDefType.h"
#include	"MsDefFunc.h"
#include	"MsDefArea.h"
#include	"MsDefCheck.h"
#include	"msCode.h"

//===========================================================================
//		�S�I�u�W�F�N�g�̃x�[�X
//
class 		MOBJECT				{};				// �S�I�u�W�F�N�g�̃x�[�X

//===========================================================================
//		abstract iteration position
//
class 		__MPOSITION 		{};
//typedef 	__MPOSITION* 		MPOSITION;
#define		MPOSITION		 	__MPOSITION*

union PZBUF {
	long	lgDt[400];
	int		iDt[200];
	float	fDt[200];
	double	dbDt[200];
};
extern PZBUF* ____pzbuf;
