#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhMbr.h
//
//		寸法型式レコード
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

//	寸法型式
#define	MHMBSZ_CODE		15						// 寸法型式最大文字数
#define	MHMBSZ_TYPE		15						// 寸法型式選択用種類コード最大文字数
#define	MHMBSZ_CODEW	15						// 寸法型式 (書き込み用)最大文字数

namespace MC
{

class	MhMbr									// 寸法型式レコード
{
	friend	class	mhPlcInfo;

	friend	void	MhLoadPtsMst();

//public:
	MINT				m_iMbrId;							// 寸法型式ID
	MCHAR				m_cMbrCode[MHMBSZ_CODE+1];			// 寸法型式
	MREAL				m_rBziWidth;						// 部材幅
	MREAL				m_rBziSZure;						// 幅補正用芯ずれ量		右幅 = m_rWidth/2 + m_rSZure
															//						左幅 = m_rWidth/2 - m_rSZure
	MREAL				m_rBziHeight;						// 部材高さ
	MCHAR				m_cMbrType[MHMBSZ_TYPE+1];			// 寸法型式選択用種類コード
	MCHAR				m_cMbrCodeW[MHMBSZ_CODEW+1];		// 寸法型式 (書き込み用　通常m_cCodeと同じ VerUp時に変更した内容が入る)

public:
	void	SetMbrId( MINT iMbrId)	
									{ m_iMbrId = iMbrId;}
	void	SetMbrCode( MCHAR* cMbrCode)
									{ Mstrncpy_s( m_cMbrCode, cMbrCode, MHMBSZ_CODE);}
	void	SetBziWidth( MREAL rBziWidth)
									{ m_rBziWidth = rBziWidth;}
	void	SetBziSZure( MREAL rBziSZure)
									{ m_rBziSZure = rBziSZure;}
	void	SetBziHeight( MREAL rBziHeight)
									{ m_rBziHeight = rBziHeight;}
	void	SetMbrType( MCHAR* cMbrType)
									{ Mstrncpy_s( m_cMbrType, cMbrType, MHMBSZ_TYPE);}
	void	SetMbrCodeW( MCHAR* cMbrCodeW)
									{ Mstrncpy_s( m_cMbrCodeW, cMbrCodeW, MHMBSZ_CODEW);}
	MINT 	GetMbrId()				{ return m_iMbrId;}
	MCHAR*	GetMbrCode()			{ return m_cMbrCode;}
	MREAL 	GetBziWidth()			{ return m_rBziWidth;}
	MREAL	GetBziSZure()			{ return m_rBziSZure;}
	MREAL	GetBziHeight()			{ return m_rBziHeight;}
	MCHAR*	GetMbrType()			{ return m_cMbrType;}
	MCHAR*	GetMbrCodeW()			{ return m_cMbrCodeW;}
};

} // namespace MC