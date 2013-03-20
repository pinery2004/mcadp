#pragma once
//
//==========================================================================================
//  Copyright(C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdmDefine.h
//
//		�ƃ��f���E�f�[�^�x�[�X�̒萔
//
//
//  K.Matsu           03/01/09    Created.
//==========================================================================================

#define		MDC_ID_NULL				0							// ����`ID

// �\�����m���[�h
//					An indication detection mode
//
#define		MDD_MD_INDICATION		2							// �\�����[�h
#define		MDD_MD_DETECTION		1							// ���o���[�h

#define		MDC_NONE_ID				-888						// ID�Ȃ�
#define 	MDC_DELETE				0x7DCDCDC					// �폜ID

// �����l
#define		MDMSZ_NMMODEL			40							// ���f�����ő啶����


namespace MC
{

// �l�c�a�̂h�c��z��ԍ��ɕϊ�����
inline MINT MIDtoHN( MINT i_id) { return ( i_id - 1); }
// �l�c�a�̔z��ԍ����h�c�ɕϊ�����
inline MINT MHNtoID( MINT i_idS) { return ( i_idS + 1); }

} // namespace MC