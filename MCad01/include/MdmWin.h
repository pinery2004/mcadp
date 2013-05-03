#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdModel.h
//
//		�l�b�`�c���f��
//
//

//==========================================================================================
//	�E�B���h�E���
namespace MC
{

class MdmWin
{
public:
	MINT		m_itpWin;						// �E�B���h�E�^�C�v ( 0:�R�c�A1�F�}��)�@�@// ����
	MINT		m_iProj;						// �������@			�������e�ƕ��s���e
	MDID		m_idFn;							// �@�\�ԍ�
	MgPoint3D	m_ViewPt;						// ���_�^�����_�i�܂ޗ����j
	MREAL		m_rZClip[2];					// Z�N���b�s���O�l
	MgPoint2D	m_Size[2];						// �T�C�Y
	MREAL		m_Scale;						// �k��etc
	// ���̕\���^��\���@����

	// �E�B���h�E�ɕ���\�����鎞�ɂ́A
	//   �E�B���h�E�̋@�\�ԍ��ɑΉ�����֌W���Ő}�`�����o���B
	//   �����ꍇ�ɂ́A�R�����̐}�`�����o���ĕ\�����s���B
public:
	void	Init()		{}
	void	Free()		{}
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* i_s, MINT i_i);
};

//	�g���[�X
inline void MdmWin::Print( MCHAR* i_s, MINT i_i)
{
#ifdef LOGOUT
	//Msprintf_s( mlLog::m_Str, Mstr( "%s < MdmSetP > ID = %d\n"), i_s, i_i);
	//MBLOGPRBF;
	//MBLOGPRINTI( Mstr( "		�E�B���h�E�^�C�v ( 0:�R�c�A1�F�}��)", m_itpWin);
	//MBLOGPRINTI( Mstr( "		�������@			�������e�ƕ��s���e"), m_iProj);
	//MBLOGPRINTI( Mstr( "		�@�\�ԍ�"), m_idFn);
	//MBLOGPRINTIN( Mstr( "		���_�^�����_�i�܂ޗ����j", m_ViewPt, 3);
	//MBLOGPRINTFN( Mstr( "		Z�N���b�s���O�l"), m_rZClip, 2);
	//MBLOGPRINTFN( Mstr( "		�T�C�Y"), m_Size, 2);
	//MBLOGPRINTFN( Mstr( "		�k��etc", m_Scale);
#endif
}

//==========================================================================================
class MdmCordinate
{
public:	
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* i_s, MINT i_i);
};
//	�g���[�X
inline void MdmCordinate::Print( MCHAR* i_s, MINT i_i)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "%s	< MdmCordinate > ID = %d\n"), i_s, i_i);
	MBLOGPRBF;
#endif
}

} // namespace MC
