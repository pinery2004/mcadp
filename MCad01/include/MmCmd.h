#pragma once

#include "MgPoint.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_HAITICMD_DO
	#pragma message( "<<< HaitiDb�Edll_EXport >>>")
	#define DLL_EXPORT			__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== HaitiDb�Edll_IMport ===")
			#define DLL_EXPORT	__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class MgPolyg2;
class MgGInt;

class DLL_EXPORT HaitiCmd
{
public:
/////////////////////////////////////////////////////////////////////////////
//	���ޕ\�m�F�ύX����
static void MmPartsEditInp(
				CWnd*		pWnd					// (I  ) �E�B���h�E�̃C���X�^���X
				);

/////////////////////////////////////////////////////////////////////////////
//	���ޕ\�m�F�ύX���s
//ZZ	void MmPartsEditXqt();

/////////////////////////////////////////////////////////////////////////////
//	���ޕ\�m�F�ύX�L�����Z��
//ZZ	void MmPartsEditCancel();

/////////////////////////////////////////////////////////////////////////////
//	���ޕ\�ύX�I��
static void MmPartsEditEnd();

/////////////////////////////////////////////////////////////////////////////
//	���i��z�u����
static void MmPartsPlc(
				const	MgPoint3	*Pt,			// (I  ) �z�u�_�A�z�u�����_
				const	MgVect3		vUp = MgVect3( 0., 0., 1.),	// (I  ) ������
				const	MgPolyg2	*pPg = NULL		// (I  ) �}�`�p�̋��@�܂��� NULL
				);

/////////////////////////////////////////////////////////////////////////////
//	������z�u����
static MINT RoofPlc(										// (  O) �X�e�C�^�X	0: ����A-1: �����쐬�G���[
				const	MgPolyg2	&Pg,			// (I  ) �n�����
				const	MgGInt		&GifInp,		// (I  ) ���̓t���O(1:�� 5:�؍�)
				const	MgPoint2	&Pth			// (I  ) �����_
				);

/////////////////////////////////////////////////////////////////////////////
//	�t�m�c�n
static void MmUndo();
static bool MmUndoIsNotEmpty();

/////////////////////////////////////////////////////////////////////////////
//	�q�d�c�n
static void MmRedo();
static bool MmRedoIsNotEmpty();

/////////////////////////////////////////////////////////////////////////////
//	�C�j�V�����C�Y�t�m�c�n�ۑ��̈�
static void MdClearRedo();

////////////////////////////////////////////////////////////////////////////
//	�R�}���h���s�̎��O����
static void MmPresetCmd();

};

} // namespace MC
