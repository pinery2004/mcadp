// MmCmdMsg.h : GDI���b�Z�[�W �t�@�C��
//
#pragma once

namespace MC
{

enum MTCMDSTR{
	MTCMD_COMMENT = 0,
	MTCMD_YUKANETA,
	MTCMD_YUKAKANAMONO
};

} // namespace MC

#define		IDC_UNDO			IDC_P0010		// �A���h�D
#define		IDC_REDO			IDC_P0020		// ���h�D
#define		IDC_CANCEL1PT		IDC_P0030		// �P�_�L�����Z��
#define		IDC_CANCELALL		IDC_P0040		// �S�_�L�����Z��
#define		IDC_ZOOMINIT		IDC_P0050		// ������ʕ\��
#define		IDC_ZOOMPAN			IDC_P0060		// ��ʈړ�
#define		IDC_ZOOMSIZE		IDC_P0070		// MIN/MAX�w���Y�[��
#define		IDC_InpKai			IDC_P0080		// �K����
#define		IDC_InpALL			IDC_P0090		// �S�K����
#define		IDC_InpEND			IDC_P0100		// ���͏I��
#define		IDC_MODECREATE		IDC_P0110		// �n�����[�h
#define		IDC_MODEDELETE		IDC_P0120		// �폜���[�h
#define		IDC_MODEMOVE		IDC_P0130		// �ړ����[�h
#define		IDC_MODEMODIFY		IDC_P0140		// �C�����[�h
#define		IDC_MODECOPY		IDC_P0150		// ���ʃ��[�h
#define		IDC_MODEPROPERTY	IDC_P0160		// �����\�����[�h
#define		IDC_BASEHIGHT		IDC_P0170		// ���������
#define		IDC_GRIDNUM			IDC_P0180		// �O���b�h���ݒ�
#define		IDC_OPTION			IDC_P0190		// �I�v�V�����ݒ�
#define		IDC_HIST			IDC_P0200		// �����Ǘ�
#define		IDC_TENKAI			IDC_P0210		// 
#define		IDC_PARTSEDIT		IDC_P0220		// �O���b�h�R���g���[���e�X�g
#define		IDC_N11				IDC_P0230		// 
#define		IDC_N15				IDC_P0240		// 
#define		IDC_N16				IDC_P0250		// 
#define		IDC_DISP_3D			IDC_P0260		// �R�����\��
#define		IDC_N18				IDC_P0270		// 
#define		IDC_N19				IDC_P0280		// 
#define		IDC_N1A				IDC_P0290		// 
#define		IDC_LOAD_DXF_FILE	IDC_P0300		// �c�w�e�t�@�C���Ǎ���
#define		IDC_N1C				IDC_P0310		// 
#define		IDC_N1D				IDC_P0320		// 
#define		IDC_N1E				IDC_P0330		// 
#define		IDC_MOD_LINELENGTH	IDC_P0340		// ���ޒ�������
#define		IDC_TEST_001		IDC_P0350		// �e�X�g�p�O�O�P
#define		IDC_MOD_PANELNO		IDC_P0360		// �p�l���ԍ��ύX

#define		IDP_OUTERWALL		IDP_P0010		// �O�Ǔ���
#define		IDP_INNERWALL		IDP_P0020		// ���Ǔ���
#define		IDP_ROOM			IDP_P0030		// ��������
#define		IDP_GAITATESASH		IDP_P0040		// �O���i�T�b�V) ����
#define		IDP_GAITATEDOOR		IDP_P0050		// �O���i�h�A) ����
#define		IDP_NAITATE			IDP_P0060		// �����������
#define		IDP_BAYWINDOW		IDP_P0070		// �o������
#define		IDP_ROOF			IDP_P0080		// ��������
#define		IDP_ROOFSUPPLEMENT	IDP_P0090		// �����t�ѓ���
#define		IDP_OPENING			IDP_P0100		// �J��������
#define		IDP_STAIRS			IDP_P0110		// �K�i����
#define		IDP_BALCONY			IDP_P0120		// �o���R�j�[����
#define		IDP_N21				IDP_P0130		// 
#define		IDP_STRUCTROOF		IDP_P0140		// �\����������
#define		IDP_STRUCTCEILING	IDP_P0150		// �\���V�����
#define		IDP_STRUCTWALL		IDP_P0160		// �\���Ǔ���
#define		IDP_STRUCTFLOOR		IDP_P0170		// �\��������
#define		IDP_STRUCTDODAI		IDP_P0180		// �y�����
#define		IDP_KISO			IDP_P0190		// ��b����
#define		IDP_WASITU			IDP_P0200		// �a������
#define		IDP_N22				IDP_P0210		// 
#define		IDP_KITCHEN			IDP_P0220		// �L�b�`������
#define		IDP_SENMEN			IDP_P0230		// ���ʁE��������
#define		IDP_TOILE			IDP_P0240		// �g�C������
#define		IDP_SETUBI			IDP_P0250		// �ݔ�����
#define		IDP_DENKI			IDP_P0260		// �d�C����
#define		IDP_PIPE			IDP_P0270		// �z�Ǔ���
#define		IDP_N24				IDP_P0280		// 
#define		IDP_N25				IDP_P0290		// 
#define		IDP_N26				IDP_P0300		// 
#define		IDP_SUNPOUSEN		IDP_P0310		// ���@������
#define		IDP_HIKIDASISEN		IDP_P0320		// ���o���L����
#define		IDP_N27				IDP_P0330		// 
#define		IDP_ZUMEN			IDP_P0340		// �}�ʓ���
#define		IDP_N28				IDP_P0350		// 
#define		IDP_N29				IDP_P0360		// 
#define		IDP_N30				IDP_P0370		// 

// USER

#define		IDC_USERDEF			1000000
#define		IDC_PARTSCREATE		IDC_USERDEF
#define		IDC_CANCELCMD		(IDC_USERDEF + 1)

// USER MSG

#define WM_MYMESSAGE_PARTSEDIT				(WM_USER + 100)
#define WM_MYMESSAGE_GRIDNUM				(WM_USER + 101)
#define WM_MYMESSAGE_STATUSBAR				(WM_USER + 102)
#define WM_MYMESSAGE_OPTION					(WM_USER + 103)
#define WM_MYMESSAGE_HIST					(WM_USER + 104)
#define WM_MYMESSAGE_TENKAI					(WM_USER + 105)
#define WM_MYMESSAGE_KATTR					(WM_USER + 106)
#define WM_MYMESSAGE_RIBBONIO				(WM_USER + 107)
#define WM_MYMESSAGE_WINDOW					(WM_USER + 108)
#define WM_MYMESSAGE_RIBBONCATEGORYCHANGED	(WM_USER + 109)
