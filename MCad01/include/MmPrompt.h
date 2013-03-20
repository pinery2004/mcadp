#pragma once
// MmPrompt.h
// Copyright (C) 2005-2008 kenMatsu. All rights reserved.
// 
//===========================================================================
//	�X�e�C�^�X�o�[�\���̈�ԍ�

#define		MC_STSBAR_GUIDANCE				0
#define		MC_STSBAR_ERROR					1
#define		MC_STSBAR_COORDINATE			2
#define		MC_STSBAR_OPERATION				3//

//===========================================================================
//	���͑��상�b�Z�[�W�\���pID
// 
// 

//===========================================================================
//		�K�C�_���X���b�Z�[�W
//

#define		MC_GUID_BASE					10000
#define		MC_GUID_SITEN					MC_GUID_BASE+1
#define		MC_GUID_HAITITEN				MC_GUID_BASE+2
#define		MC_GUID_SYUUTEN					MC_GUID_BASE+3
#define		MC_GUID_HOUKOUTEN				MC_GUID_BASE+4
#define		MC_GUID_AREA_SITEN				MC_GUID_BASE+5
#define		MC_GUID_AREA_TUUKATEN			MC_GUID_BASE+6
#define		MC_GUID_AREA_TAIKAKUTEN			MC_GUID_BASE+7
#define		MC_GUID_AREA_HOUKOUTEN			MC_GUID_BASE+8
#define		MC_GUID_JIM_SITEN				MC_GUID_BASE+9
#define		MC_GUID_JIM_TUUKATEN			MC_GUID_BASE+10
#define		MC_GUID_JIM_HOUKOUTEN			MC_GUID_BASE+11
#define		MC_GUID_DEL_PARTS				MC_GUID_BASE+12
#define		MC_GUID_DEL_ROOF				MC_GUID_BASE+13
#define		MC_GUID_MOD_PANELNO				MC_GUID_BASE+14
#define		MC_GUID_MOD_BUZAILENGTH1		MC_GUID_BASE+15
#define		MC_GUID_MOD_BUZAILENGTH2		MC_GUID_BASE+16
#define		MC_GUID_MULTI_BUZAIAREA			MC_GUID_BASE+17


//===========================================================================
//		����\��
//

#define		MC_OPRT_BASE					20000
#define		MC_OPRT_WAIT					MC_OPRT_BASE+1
#define		MC_OPRT_PARTS					MC_OPRT_BASE+2
#define		MC_OPRT_ROOF					MC_OPRT_BASE+3
#define		MC_OPRT_DEL_PARTS				MC_OPRT_BASE+4
#define		MC_OPRT_DEL_ROOF				MC_OPRT_BASE+5
#define		MC_OPRT_MOD_PANEL				MC_OPRT_BASE+6
#define		MC_OPRT_MOD_BUZAI				MC_OPRT_BASE+7

//===========================================================================
//		�G���[���b�Z�[�W
//

#define		MC_ERR_BASE						20000
#define		MC_ERR_IMPOS_MAKE_ROOF			MC_ERR_BASE+1
#define		MC_ERR_NOTSET_TABLE				MC_ERR_BASE+2
#define		MC_ERR_NOTSET_PARTS_TABLE		MC_ERR_BASE+3
#define		MC_ERR_NOTSET_MEMBER_TABLE		MC_ERR_BASE+4
