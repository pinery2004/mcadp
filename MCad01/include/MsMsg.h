#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsMsg.h
//
//		メッセージの表示
//		エラーメッセージの表示
//
//
//  K.Matsu           13/05/12    Created.
//==========================================================================================

namespace MC
{

class msmsg
{
public:
	////////////////////////////////////////////////////////////////////////////
	//	メッセージボックスを最前面に表示する
	//
	static void MsgBox(							// ｽﾃｰﾀｽ
						LPCSTR	i_pcText,		// メッセージ
						LPCSTR	i_pcCaption		// 見出し
					);

	static void MsgBox(							// ｽﾃｰﾀｽ
				const	MCHAR*	i_pcText,		// メッセージ
				const	MCHAR*	i_pcCaption		// 見出し
					);

	////////////////////////////////////////////////////////////////////////////
	//	エラーリターンブレークポイント用
	//
	static void	ErrorReturn( void);
	
	static void	SysError( 
							MCHAR*				i_pcProgram,						// エラープログラム名
							int					i_iLineN,							// 行番号
							int					i_iErrorCode,						// エラーコード
							MCHAR*				i_cComment = 0						// コメント
							);
	static void	SysError( 
							MCHAR*				i_pcProgram,						// エラープログラム名
							int					i_iLineN,							// 行番号
							int					i_iErrorCode,						// エラーコード
							char*				i_cComment							// コメント
							);
	static void	SysError( 
							char*				i_pcProgram,						// エラープログラム名
							int					i_iLineN,							// 行番号
							int					i_iErrorCode,						// エラーコード
							MCHAR*				i_cComment = 0						// コメント
							);
	static void	SysError( 
							char*				i_pcProgram,						// エラープログラム名
							int					i_iLineN,							// 行番号
							int					i_iErrorCode,						// エラーコード
							char*				i_cComment							// コメント
							);
	static void	CmdError( 
							char*				i_pcProgram,						// エラープログラム名
							int					i_iLineN,							// 行番号
							int					i_iErrorCode						// エラーコード
							);
	static void	CmdError( 
							MCHAR*				i_pcProgram,						// エラープログラム名
							int					i_iLineN,							// 行番号
							int					i_iErrorCode						// エラーコード
							);

	/////////////////////////////////////////////////////////////////////////////////
	//////		リターンコード
	////
	////static short shortCast( int i)
	////{
	////	ASSERT( -MINSHORT <= i && i <= MAXSHORT);
	////	return (short)i;
	////}

	////struct MbRT
	////{
	////	int	m_iRt;
	////
	////	MbRT()				: m_iRt( 0)		{}
	////	MbRT( int i_iRt)	: m_iRt( i_iRt)	{}
	////	
	////	operator short()			{ return shortCast( m_iRt);}
	////
	////	bool operator &&( bool b)	{ return (*this != 0) && b;}
	////	bool operator ||( bool b)	{ return (*this != 0) || b;}
	////	bool operator ==( int i)	{ return m_iRt == i;}
	////	bool operator !=( int i)	{ return m_iRt != i;}
	////	bool operator < ( int i)	{ return m_iRt <  i;}
	////	bool operator < ( long lg)	{ return m_iRt <  lg;}
	////	bool operator <=( int i)	{ return m_iRt <= i;}
	////	bool operator > ( int i)	{ return m_iRt >  i;}
	////	bool operator >=( int i)	{ return m_iRt >= i;}

};	// msmsg

} // namespace MC


