//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdlDispList.h
//
//		�ƃ��f���̃f�B�X�v���C���X�g�쐬
//
//
//  K.Matsu           08/06/01    Created.
//==========================================================================================

#define		MP_PANEL_LINE			1
#define		MP_PANEL_RECTANGULAR	2

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MDLDISPLIST_DO
	#pragma message( "<<< MdlDispList�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MN_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== MdlDispList�Edll_IMport ===")
			#define DLL_EXPORT					__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

class DLL_EXPORT MdlDispList
{
public:	
	////////////////////////////////////////////////////////////////////////////
	//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	���ށA��b	����
	//	
	static int DrawIeMdl(
							MREAL		rB,				// �\���{��
					const	MgPoint3D	&PtCtr			// ���S���W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	���ށA��b	����
	//	
	static int DrawIeMdl1(
							MREAL		rB,				// �\���{��
					const	MgPoint3D	&PtCtr			// ���S���W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�ǁA��؁@�}�e���A���Ȃ�
	//
	static int DrawIeMdl2(
							MREAL		rB,				// �\���{��
					const	MgPoint3D	&PtCtr			// ���S���W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�����@�}�e���A���Ȃ�
	//
	static int DrawIeMdl3(
							MREAL		rB,				// �\���{��
					const	MgPoint3D	&PtCtr			// ���S���W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�����̃f�B�X�v���C���X�g���쐬����@���̗p
	//			
	static void DrawYane1(
							MhRoofInfo	*pRoofEn,		// ���u����
					const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
							MREAL		rB				// �R�����\���{��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�����̃f�B�X�v���C���X�g���쐬����@������
	//			
	static void DrawYane2(
							MhRoofInfo	*pRoofEn,		// ���u����
					const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
							MREAL		rB				// �R�����\���{��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z��؂̃f�B�X�v���C���X�g���쐬����@���̗p
	//			
	static void DrawYagiri(
							MhRoofInfo	*pRoofEn,		// ���u����
					const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
							MREAL		rB				// �R�����\���{��
					);
			
	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�ǂ̃f�B�X�v���C���X�g���쐬���� ���ԁA������
	//			
	static void DrawKabe(
							mhPlcParts	*i_pPlcEn,		// ��
					const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
							MREAL		rB				// �R�����\���{��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�f�B�X�v���C���X�g���쐬����
	static MINT OpenDL( 
							MINT		inmDispList		// DisplayList�ԍ�
					);

	////////////////////////////////////////////////////////////////////////////
	//	�f�B�X�v���C���X�g�̍쐬���I������
	static void CloseDL();

	////////////////////////////////////////////////////////////////////////////
	//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�����A������
	//
	static MINT MakeDispListMat0(
							MREAL		rB,				// �\���{��
					const	MgPoint3D	&PtCtr			// ���S���W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�ǁA��؁@
	//
	static MINT MakeDispListMat1(
							MREAL		rB,				// �\���{��
					const	MgPoint3D	&PtCtr			// ���S���W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�\���ƃ��f���̂R�����f�B�X�v���C���X�g���쐬����	�ǁA��؁A�����@������
	//
	static MINT MakeDispListMat2(
							MREAL		rB,				// �\���{��
					const	MgPoint3D	&PtCtr			// ���S���W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z����̊J���g�̃f�B�X�v���C���X�g���쐬����
	//			
	static void DrawTategu(
							mhPlcParts	*i_pPlcEn,		// �ǂ܂���NULL
							mhPlcParts	*pPlcTEn,		// ����
					const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
							MREAL		rB				// �R�����\���{��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z���Ęg�A���̃f�B�X�v���C���X�g���쐬����
	//			
	static void DrawTatewaku( 
							mhPlcParts	*i_pPlcEn,
					const	MgPoint3D	&PtCtr,
							MREAL		rB
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z���A�V��A�����̊J���̃f�B�X�v���C���X�g���쐬����
	//			
	static void DrawKaiko( 
							mhPlcParts *i_pPlcEn,
					const	MgPoint3D	&PtCtr,
							MREAL		rB
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z���u���ނ̃f�B�X�v���C���X�g���쐬����
	//			
	static void DrawOukaZai( 
							mhPlcParts	*i_pPlcEn,
					const	MgPoint3D	&PtCtr,
							MREAL		rB
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�p�l���̃f�B�X�v���C���X�g���쐬����
	//			
	static void DrawPanel( 
							mhPlcParts *i_pPlcEn,
					const	MgPoint3D	&PtCtr,
							MREAL		rB,
							MINT		iMode			// �\�����[�h 1:�p�l���㕔���� 2:�p�l���`�󒼕��� 3:����+�p�l���`��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z��b�̃f�B�X�v���C���X�g���쐬����
	//			
	static void DrawKiso(
							mhPlcParts	*i_pPlcEn,		// ��b
					const	MgPoint3D	&PtCtr,			// �\���ƃ��f���̒��S
							MREAL		rB				// �R�����\���{��
					);

	////////////////////////////////////////////////////////////////////////////
	//	�\���ƃ��f���̃f�[�^��S�ēǂݍ��݂R�����f�B�X�v���C���X�g�쐬�p��
	//  �\���{���ƒ��S���W�����߂�
	//
	static void MhGetBCtr(
							MREAL		*rB,			// �\���{��
							MgPoint3D	*PtCtr			// ���S���W
					);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z�ƃ��f����MINMAX���擾����
	//
	static void MhGetMinMaxMdl( MgMinMaxR3D	*prMmMdl);

	////////////////////////////////////////////////////////////////////////////
	//	�y�@�\�z����̌��̑��p�`�����߂�
	//			
	static void TateguHole(
							mhPlcParts	*i_pPlcEn,		// �ǂ܂���NULL
							mhPlcParts	*pPlcTEn,		// ����
							MgPolyg3D	*PgR,			// �ǉE�ʊJ��
							MgPolyg3D	*PgL			// �Ǎ��ʊJ��
					);
};

} // namespace MC
