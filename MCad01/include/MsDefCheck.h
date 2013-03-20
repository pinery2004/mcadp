#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsBasic.h
//
//		��{�@�G���[����֐�
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

/////////////////////////////////////////////////////////////////////////////
//		�V�X�e���G���[�X�e�C�^�X

#define	 	MC_ERR_COMMAND		1200			// �R�}���h�G���[
#define	 	MC_ERR_ID			1201			// �h�c���G���[
#define		MC_ERR_POINTER		1202			// �������擾�G���[
#define		MC_ERR_OVERFLOW		1203			// �̈�I�[�o�t���[�G���[
#define		MC_ERR_FILEOPEN		1204			// �t�@�C���I�[�v���G���[
#define		MC_ERR_OTHER	   -999				// ���̑��G���[

//		�������擾�G���[�\��
#define		MB_DM_MEM			{ msSysError( X, MC_ERR_POINTER);}

/////////////////////////////////////////////////////////////////////////////
//		�X�e�C�^�X
#define		MC_SUCCESS			  0
#define		MC_FAILURE			 ~0

#define		MC_E_CANCEL			 13
#define		MC_E_NOMSG			 14
	
#define 	RETURN_ID_ERR( CPROG)\
								ms::SysError( CPROG, MC_ERR_ID)
#define 	RETURN_POINTER_ERR( CPROG)\
								ms::SysError( CPROG, MC_ERR_POINTER)
#define 	RETURN_OVERFLOW_ERR( CPROG)\
								ms::SysError( CPROG, MC_ERR_OVERFLOW)
#define 	RETURN_OTHER_ERR( CPROG)\
								msSysError( CPROG, MC_ERR_OTHER)
#define 	GOTO_ERROR			{ ms::ErrorReturn(); goto ERR_EXIT;}
#define 	GOTO_ERROR_1		{ ms::ErrorReturn(); goto ERR_EXIT_1;}
#define 	GOTO_ERROR1			{ ms::ErrorReturn(); goto ERR_EXIT1;}
#define 	GOTO_ERROR2			{ ms::ErrorReturn(); goto ERR_EXIT2;}
#define 	GOTO_ERROR3			{ ms::ErrorReturn(); goto ERR_EXIT3;}
#define 	GOTO_ERROR4			{ ms::ErrorReturn(); goto ERR_EXIT4;}
#define 	GOTO_ERROR999		{ ms::ErrorReturn(); goto ERR_EXIT999;}



//===========================================================================
//		�|�C���^�`�F�b�N
//
//		�A�N�Z�X�\�ȃ|�C���^�ł��鎖���`�F�b�N����
//
//		CHECKDATA( p, n)	:	( p != 0) && ( p ���� n �o�C�g�̃A�N�Z�X�\)
//		CHECKPTR( p)		:	( p != 0) && ( p ���� 1 �o�C�g�̃A�N�Z�X�\)
//		CHECKFUNCPTR( p) 	:	( p != 0) && ( p �ɃA�N�Z�X�\)
//		CHECKSTR( s)		:	( p != 0) && ( p ���� 30000�����̃A�N�Z�X�\)
//		CHECKSTRUCTPTR( p)	:	( p != 0) && ( p ���� �\���̂̃T�C�Y���̃A�N�Z�X�\)
//  
#define 	CHECKDATA( p, n)		( ( p) && !IsBadReadPtr( ( LPVOID)( p), ( n)))
#define 	CHECKPTR( p)			CHECKDATA( p, 1)
#define 	CHECKFUNCPTR( p) 		( ( p) && !IsBadCodePtr( ( FARPROC) ( p)))
#define 	CHECKSTR( s)			( ( s) && !IsBadStringPtr( ( LPCSTR)( s), 30000))
#define 	CHECKSTRUCTPTR( p)		CHECKDATA( p, sizeof( *p)) 

//===========================================================================
//		�A���P�[�V�������`�F�b�N
//			( out of memory)
//
//	�g�p���@:
//		  rc = MALLOC_FAIL( p = new CMyClass( a, b, c));
//
//	����: rc = DM_MEM: �A���P�[�V�������
//		  rc = SUCCESS: �A���P�[�V��������
//
#define MALLOC_FAIL( object) ( object) ? SUCCESS: DM_MEM

//
//	MGCHECK_ZEROVECT( �[���`�F�b�N�̃x�N�g����, "�v���O������");
//
#define 	MBCHECK_ZEROVECT(X,Z,T)\
								{ if ( ( X) < T)  ms::SysError( Z, MC_ERR_VECT_ZERO);}

#define 	MBCHECK_POINTER(P)	{ if ( P == NULL) ms::SysError( __FILE__ + __LINE__, MC_ERR_POINTER);}


