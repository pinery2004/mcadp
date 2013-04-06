#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdModel.h
//
//		�l�b�`�c���f��
//
//

namespace MC
{

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MDM_DO
	#pragma message( "<<< Mdm�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== Mdm�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT Mdm
{
//private:
public:
	static CArray<MdModel*>	ms_pMdl;			// ���f�����X�g
	static MDID				ms_idCurMdl;		// �J�����g���f��ID
	static MdModel*			ms_pCurMdl;			// �J�����g���f��


public:
	//===========================================================================
	//�y�@�\�z���f��������������
	//�y�Ԓl�z�Ȃ�
	static MINT MdmInitialize( void);

	//===========================================================================
	//�y�@�\�z���f���̎g�p���I������
	//�y�Ԓl�z�Ȃ�
	static MINT Mdm::MdmTerminate( void);

	//===========================================================================
	//�y�@�\�z���f����ǉ����A���f��ID���擾
	//�y�Ԓl�z���f��ID
	static MDID AddModel(
						MCHAR*	i_cMdlNm		// ���f����
						);
//S	{
//		// s
//	}

	//===========================================================================
	//�y�@�\�z���f�������擾����
	//�y�Ԓl�z���f����
	static MINT GetModelCount()
	{
		return (MINT)ms_pMdl.GetCount();
	}

	//===========================================================================
	//�y�@�\�z���f�������烂�f��ID���擾����
	//�y�Ԓl�z���f��ID
	static MDID GetModelId(
						MCHAR*	i_cMdlNm		// ���f����
						);
//S	{
//		MDID idMdl = 0;
//		for ( int iC=0; iC<ms_pMdl.GetCount(); iC++) {
//			if ( Mstrcmp( ms_pMdl[iC]->m_cMdlNm, i_cMdlNm)) {
//				idMdl = MHNtoID( iC);
//				break;
//			}
//		}
//		return idMdl; 
//	}

	//===========================================================================
	//�y�@�\�z���f��ID���烂�f�������擾����
	//�y�Ԓl�z���f��ID
	static MDID GetModelName(
						MDID	i_idMdl,		// ���f��ID
						MCHAR*	o_cMdlNm		// ���f����
						);

	//===========================================================================
	//�y�@�\�z�J�����g���f����ݒ肷��
	//�y�Ԓl�z���f��
	static MdModel* SetCurModel(
						MDID	i_idnModel		// ���f��ID
						)
	{
		ms_idCurMdl = i_idnModel;
		ms_pCurMdl = ms_pMdl[MIDtoHN(i_idnModel)];
		return ms_pCurMdl;
	}

	//===========================================================================
	//�y�@�\�z�J�����g���f��ID���擾����
	//�y�Ԓl�z���f��ID
	static MDID	GetCurModelId()
	{
		return ms_idCurMdl;
	}

	//===========================================================================
	//�y�@�\�z�J�����g���f�����擾����
	//�y�Ԓl�z���f��
	static MdModel* GetCurModel()
	{
		return ms_pCurMdl;
	}

	//===========================================================================
	//�y�@�\�z���f��ID���烂�f�����擾����
	//�y�Ԓl�z���f��
	static MdModel* GetModel( MDID i_idnModel = 1)
	{
		return ms_pMdl[MIDtoHN(i_idnModel)];
	}

};

} // namespace MC
