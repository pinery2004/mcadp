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
namespace MC
{

	class MdmAtr
{
	MUBYTESET	m_at;

public:
	void Init()	{}
	void Free()	{}

	void Alloc( MINT i_szAt)
						{ m_at.Alloc( i_szAt);}
	// �f�o�b�O�p�g���[�X�o��
	void Print( MCHAR* s, MINT i_i);
};
//	�g���[�X
inline void MdmAtr::Print( MCHAR* s, MINT i_i)
{
#ifdef LOGOUT
	Msprintf_s( mlLog::m_Str, Mstr( "		%s < MdmAtr > ID = %d\n"), s, i_i);
	MBLOGPRBF;
#endif
}

} // namespace MC
