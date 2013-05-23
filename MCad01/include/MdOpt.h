#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdOpt.h
//
//		�I�v�V�����ݒ�
//						
//
//==========================================================================================

#include "MsBitSet.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MHOPT_DO
	#pragma message( "<<< MHOPT�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== MHOPT�Edll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class mhPlcParts;

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�I���n�o�s�Q �N���X
class DLL_EXPORT MhOpt
{
	MUINT	mb;
public:
	MhOpt()		{}
	MhOpt( MUINT i)
					{ mb = i;}
//	MhOpt & operator	= ( MhOpt &opt)
//					{ *this = opt;}
	MUINT GetOpt()
					{ return mb;}
	bool IsStd()
					{ return (mb <= 1);}
	friend MhOpt operator	~ ( MhOpt &opt)
					{ MhOpt optw; optw.mb = ~opt.mb; return optw;}
	MhOpt operator & ( const MhOpt &opt) const
					{ MhOpt optw; optw.mb = mb & opt.mb; return optw;}
	MhOpt operator | ( const MhOpt &opt) const
					{ MhOpt optw; optw.mb = mb | opt.mb; return optw;}
	MhOpt operator &= ( const MhOpt& opt1)
					{ mb &= opt1.mb; return *this;} 
	MhOpt operator |= ( const MhOpt& opt1)
					{ mb |= opt1.mb; return *this;} 
	bool operator == ( const MhOpt &Opt) const
					{ return (mb == Opt.mb);}

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�����Ǘ��R�[�h�̗̈���J������
	static void MhHistFre(
							MsBitSet*		*pHstv		// (I O) �J�������Ǘ� NULL: �J���s�v
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�V�K���R�[�h�ǉ����ɐݒ肷�闚���Ǘ��R�[�h���擾����
	//		�@�i�����Ǘ��R�[�h������G���A�̊m�ۂ͖{�֐��ōs���j
	static void MhHistAdd(
							MsBitSet*		*ppHstv		// (  O) �ǉ����R�[�h�ɐݒ肷�闚���Ǘ��R�[�h�̃|�C���^ NULL: �S�����Ǘ�
					 );

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z���R�[�h�C�����ɐݒ肷�闚���Ǘ��R�[�h���擾����
	//�y�Ԓl�z�C����̃��R�[�h�\���R�[�h
	//			1 : �C���������Ǘ��̓J�����g�o�[�W�����̂ݐݒ肳��Ă���ꍇ�ŁA
	//				�C�������R�[�h�͗����Ǘ��ύX�Ȃ��ŏC�����e���㏑������B
	//				�ǉ����R�[�h�͂Ȃ��B
	//			3 : �C���������Ǘ��ɃJ�����g�o�[�W�����ȊO�̃o�[�W�������܂ޏꍇ�ŁA
	//				�J�����g�o�[�W�����ȊO�̗��𕔕��́A�C�������R�[�h�����̂܂܎c�������Ǘ��R�[�h�̂ݏC������B
	//				����ɁA�J�����g�o�[�W�����݂̗̂����Ǘ������C����̃��R�[�h��V���ɒǉ�����B
	//				�i�����Ǘ��R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j
	static MINT MhHistMod(
							mhPlcParts	 *pPlcEnR,		// (I O) �C��������
							mhPlcParts* *ppPlcEnM		// (  O) �C���敔��
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z���R�[�h�폜���ɐݒ肷�闚���Ǘ��R�[�h���擾����
	//�y�Ԓl�z�폜��̃��R�[�h�\���R�[�h
	//			1 : �폜�������Ǘ��̓J�����g�o�[�W�����Ɠ���̏ꍇ�ŁA
	//				�폜�����R�[�h�͍폜����B
	//			3 : �폜�������Ǘ��ɃJ�����g�o�[�W�����ȊO�̗����Ǘ����܂ޏꍇ�ŁA
	//				�J�����g�o�[�W�����ȊO�̗����Ǘ������́A�폜�����R�[�h�����̂܂܎c�������Ǘ��R�[�h�̂ݏC������B
	//				�i�����Ǘ��R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j


	static MINT MhHistDel(
	//						MsBitSet		*pHstvR,		// (I O) �폜�����R�[�h�̗����Ǘ��Q
							MsBitSet*		*ppHstvMod		// (I O) �폜��̃��R�[�h�̕\���n�m�����Ǘ��Q
					);

};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MHOPTV_DO
	#pragma message( "<<< MHOPTV�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== MHOPTV�Edll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

/////////////////////////////////////////////////////////////////////////////
//�y�@�\�zOPT�Q�Z�b�g �N���X

#define	MSZ_OPTV	3
#define	MSZ_OPTVB	(3 * 32)

class DLL_EXPORT MhOptV: public MsBitSet
{
public:
												// �n�o�s�Q�Ǘ����
	static	bool		fcDB;					// �J�����g�I���n�o�s�Q��DB�֔��f�t���O
												//		(TRUE:���f�ρAFALSE: �����f)
	static	bool		fcStd;					// �J�����g�I���n�o�s�Q==�W���@�t���O
												//		(TRUE:�W���AFALSE:�W���ȊO�̂n�o�s�Q�L��)
	static	bool		fDispStd;				// �W���I�v�V�����\���t���O
												//		(TRUE:�\���n�m�AFALSE:�\���n�e�e)
	static	MhOpt		bmCurGOpt;				// �J�����g�I���n�o�s�Q
	static	MsBitSet	bmCurRGOptSet;			// �J�����g�I���n�o�s�Q�œǍ��ݑΏۂ�OPT�Q�Z�b�g
	static	MsBitSet	bmCurWGOptSet;			// �J�����g�I���n�o�s�Q�ŏ����ݑΏۂ�OPT�Q�Z�b�g
	static	MsBitSet	bmCurGOptSet;			// �J�����g�I���n�o�s�Q������OPT�Q�Z�b�g
	static	MINT		nbmGOpt;				// �o�^OPT�Q��
	static	MhOpt		bmGOpt[MSZ_OPTVB];		// �o�^OPT�Q

public:
//	MhOptV()			{}

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�J�����g�I���n�o�s�Q�œǍ��ݑΏۂ�OPT�Q�Z�b�g���擾����
	static MsBitSet	MhOptBScRGet();
							
	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�J�����g�I���n�o�s�Q�ŏ����ݑΏۂ�OPT�Q�Z�b�g���擾����
	static MsBitSet	MhOptBScWGet();
							
	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�J�����g�I���n�o�s�Q������OPT�Q�Z�b�g���擾����
	static MsBitSet	MhOptBScGet();

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�n�o�s�Q�Ǘ���������������
	static void MmOptInit();

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�n�o�s�Q�I���`�F�b�N�{�b�N�X�̑I���󋵂��J�����g�I���n�o�s�Q�ɔ��f����
	static void MmOptSet(
							MINT		nOpt,		// (I  ) �`�F�b�N�{�b�N�X�ԍ�
							MINT		iChk		// (I  ) �`�F�b�N�{�b�N�X�I����
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�J�����g�I���n�o�s�Q�擾
	//�y�Ԓl�z�n�o�s�Q�L��
	//			TRUE: �W��
	//			FALSE: �W���ȊO�̃I�v�V�����ݒ肠��
	static bool MmOptGetC(
							MhOpt*	pOpt			// (  O) �J�����g�I���n�o�s�Q
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�c�a���R�[�h��OPT�Q�Z�b�g���J�����g�I���n�o�s�Q���܂ނ����ׂ�
	//�y�Ԓl�z�I���n�o�s�Q�܂݃t���O
	//			TRUE:  �܂�
	//			FALSE: �܂܂Ȃ�
	static bool MmOptCheckC(
							MsBitSet	*pOptv		// (I  ) �c�a���R�[�h��OPT�Q�Z�b�g
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�c�a���R�[�h��OPT�Q�Z�b�g���J�����g�I���n�o�s�Q���܂ނ����ׂ�
	//�y�Ԓl�z�I���n�o�s�Q�܂݃t���O
	//			TRUE : �܂�		�\���n�e�e
	//			FALSE: �܂܂Ȃ�	�\���n�m
	static bool MmOptOffCheckC(
							MsBitSet	*pOptv		// (I  ) �c�a���R�[�h��OPT�Q�Z�b�g
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�c�a���R�[�h�C����̃��R�[�h�\���R�[�h���擾����
	//		�@�i�C�����Ƃ̂n�o�s�Q��OPT�Q�Z�b�g�ƃJ�����g�I���n�o�s�Q�̏����ݑΏ�OPT�Q�Z�b�g��
	//		�@	��r���Ăǂ̂悤�ȏC�������̃��R�[�h�ł��邩���ׂ�j
	//�y�Ԓl�z�C����̃��R�[�h�\���R�[�h
	//			1: �C�������R�[�h��OPT�Q�Z�b�g �� �����ݑΏۂ�OPT�Q�Z�b�g
	//				�n�o�s�Q�̕ύX�͕s�v�ŁA�����C���̂ݕύX����
	//			2: �C�������R�[�h��OPT�Q�Z�b�g �� �����ݑΏۂ�OPT�Q�Z�b�g
	//				�n�o�s�Q�̕ύX�Ƒ����ύX����
	//			3: ���̑� ( �C�������R�[�h��OPT�Q�Z�b�g �� �����ݑΏۂ�OPT�Q�Z�b�g || �����I�ɏd�Ȃ��Ă��� )
	//				�i�C�������R�[�h��OPT�Q�Z�b�g �� �i�����ݑΏۂ�OPT�Q�Z�b�g �� �C�������R�[�h��OPT�Q�Z�b�g)�j
	//				�C�������R�[�h�͂n�o�s�Q�ύX���A�V���������ݑΏۂ�OPT�Q�Z�b�g�̂n�o�s�Q������
	//				�R�s�[���R�[�h���쐻�����̑�����ύX����
	//
	static MINT MmOptModCheck(								// (  O) �C����̃��R�[�h�\���R�[�h
							MsBitSet*	*ppOptvRN,	// (I O) �C���O�ヌ�R�[�h��OPT�Q�Z�b�g�@	(�C����̃��R�[�h�\���R�[�h >= 2 �̎��L��)
							MsBitSet*	*ppOptvWN,	// (  O) �C���p�ɒǉ����R�[�h��OPT�Q�Z�b�g�@(�C����̃��R�[�h�\���R�[�h == 3 �̎��L��)
							MhOptV*	*ppOptv			// (  O) �n�o�s�Q�Ǘ����
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z���R�[�h�폜���ɐݒ肷��n�o�s�Q�R�[�h���擾����
	//�y�Ԓl�z�폜��̃��R�[�h�\���R�[�h
	//			1 : �폜���n�o�s�Q�͏����݂n�o�s�Q�Ɠ���̏ꍇ�ŁA
	//				�폜�����R�[�h�͍폜����B
	//			2 :	�폜���n�o�s�Q�͏����݂n�o�s�Q�ɑS�Ċ܂܂ꂩ�ǉ��n�o�s�Q������ꍇ�ŁA
	//				�폜�����R�[�h�͍폜����B
	//			3 : �폜���n�o�s�Q�ɏ����݂n�o�s�Q�ȊO�̂n�o�s�Q���܂ޏꍇ�ŁA
	//				�����݂n�o�s�Q�ȊO�̂n�o�s�Q�����́A�폜�����R�[�h�����̂܂܎c���n�o�s�Q�R�[�h�̂ݏC������B
	//				�i�n�o�s�Q�R�[�h������G���A�̊J���Ɗm�ۂ͖{�֐��ōs���j
	//
	static MINT MmOptDelCheck(								// (  O) �폜��̃��R�[�h�\���R�[�h
							MsBitSet*	*ppOptvRN,	// (  O) �폜�O��̃��R�[�h�̕\���n�mOPT�Q�Z�b�g
							MsBitSet*	*ppOptvDN	// (  O) �폜�O��̃��R�[�h�̕\���n�e�eOPT�Q�Z�b�g
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�o�^OPT�Q���I���n�o�s�Q��������������Βǉ��o�^����
	//		�@�I���n�o�s�Q��S�Ċ܂ޓo�^OPT�Q�̏W�܂�ɑ�������OPT�Q�Z�b�g��
	//�y�Ԓl�z������
	//			0:�����ł���ǉ�
	//			1:�L��
	//
	static MINT MmOptSrch(
							MhOpt	Opt				// (I  ) �����n�o�s�Q
					);

	/////////////////////////////////////////////////////////////////////////////
	//�y�@�\�z�I���n�o�s�Q�œǍ��ݑΏۂ�OPT�Q�Z�b�g��
	//		  �����ݑΏۂ�OPT�Q�Z�b�g�����߂�
	//�y�Ԓl�z
	//			TRUE: �W��
	//			FALSE: �W���ȊO�̃I�v�V�����ݒ肠��
	//
	static bool MmOptIncSrch(
							MhOpt	Opt				// (I  ) �I���n�o�s�Q
					);

	/////////////////////////////////////////////////////////////////////////////
	// �J�����g�I���n�o�s�Q�ɑ�����OPT�Q�Z�b�g��DB�̎Q�ƑΏۃ��R�[�h�֔��f
	static void MmOptAddDB();

};

} // namespace MC
