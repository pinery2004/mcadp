#pragma once
#include	"McSystemProperty.h"
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhPartsSpec.h
//
//		部品仕様レコード
//
//
//  K.Matsu           13/04/03    Created.
//==========================================================================================
#define	MHPTSZ_NMGENERAL	23							// 総称最大文字数
#define	MHPTSZ_NMPARTS1		23							// 操作用部材名最大文字数
#define	MHPTSZ_NMPARTS2		23							// 積算用部材名最大文字数
#define	MHPTSZ_TPMEMBER		1							// 寸法型式選択用種類コード最大文字数
#define	MHPTSZ_CDMEMBER		15							// 寸法型式最大文字数

//	部品種類

#define		MP_BZICD_NOSELECT		-1
#define		MP_BZICD_TYPE			10000
#define		MP_BZICD_KIND			1000
#define		MP_BZICD_BUZAI			10000
#define		MP_BZICD_PANEL			30000
#define		MP_BZICD_YUKAPANEL		32010
#define		MP_BZICD_KABEPANEL		35010
#define		MP_BZICD_TENJOPANEL		33010
#define		MP_BZICD_YANEPANEL		34010
#define		MP_BZICD_YANEBUZAI		14000
#define		MP_BZICD_KABEBUZAI		15000
#define		MP_BZICD_TATEGU			65000
#define		MP_BZICD_TAIKABEAREA	45010
#define		MP_BZICD_TAIKABELINE	45020
#define		MP_BZICD_SIJIKABELINE	45030
#define		MP_BZICD_TENKAI			45110

namespace MC
{

class	mhPartsTp								// 部品仕様レコード
{
	friend	class	mhPlcInfo;

protected:
	mhGp*	m_pPTGp;							// 構成(組)コード( 屋根、小屋、天井、耐力壁、壁、床、基礎)
	MINT	m_iPTCdBr;							// 分類コード("部材", "金物", "パネル", "屋根", "壁", "基礎", "線分", "区画", "注記", "その他")
	MCHAR	m_sPTNmGeneral[MHPTSZ_NMGENERAL+1];	// 総称
	MCHAR	m_sPTNmParts1[MHPTSZ_NMPARTS1+1];	// 操作用部材名1
	MCHAR	m_sPTNmParts2[MHPTSZ_NMPARTS2+1];	// 積算用部材名2
	DWORD	m_dPTColor;							// 色
	MINT	m_iPTCdBuzaiR;						// 部材コード	読込み用
	MINT	m_iPTCdBuzaiW;						// 部材コード	書き込み用(部品仕様テーブルVerUpメインテナンス用)
	MCHAR	m_sPTTpMbr[MHPTSZ_TPMEMBER+1];		// 寸法型式選択用種類コード
	MCHAR	m_sPTCdMbr[MHPTSZ_CDMEMBER+1];		// 寸法型式
	MINT	m_iPTCdInpKb;						// 入力コード
	MSTNDH	m_iPTCdHgt;							// 取り付け高さ基準コード
	MINT	m_iPTCdPlc;							// 配置コード
	MINT	m_iPTCdIzon;						// 依存コード
	MINT	m_iPTCdMarume;						// 丸めコード
	MINT	m_iPTCdToritk;						// 取り付けコード　上下付けコード (0:下付け, 1:上付け)
public:
	void	SetPTGp( mhGp* pPTGp)	{													// 構成(組)コード( 屋根、小屋、天井、耐力壁、壁、床、基礎)
									m_pPTGp = pPTGp;}
	void	SetPTCdBr( MINT iPTCdBr)	{												// 分類コード("部材", "金物", "パネル", "屋根", "壁", "基礎", "線分", "区画", "注記", "その他")
									m_iPTCdBr = iPTCdBr;}
	void	SetPTNmGeneral( MCHAR* cPTNmGeneral)	{									// 総称
									Mstrncpy_s( m_sPTNmGeneral, cPTNmGeneral, MHPTSZ_NMGENERAL);}
	void	SetPTNmParts1( MCHAR* cPTNmParts1)	{											// 操作用部材名1
									Mstrncpy_s( m_sPTNmParts1, cPTNmParts1, MHPTSZ_NMPARTS1);}
	void	SetPTNmParts2( MCHAR* cPTNmParts2)	{											// 積算用部材名2
									Mstrncpy_s( m_sPTNmParts2, cPTNmParts2, MHPTSZ_NMPARTS2);}
	void	SetPTColor( DWORD dPTColor)	{												// 色
									m_dPTColor = dPTColor;}
	void	SetPTCdBuzaiR( MINT iPTCdBuzaiR)	{										// 部材コード	読込み用
									m_iPTCdBuzaiR = iPTCdBuzaiR;}
	void	SetPTCdBuzaiW( MINT iPTCdBuzaiW)	{										// 部材コード	書き込み用(部品仕様テーブルVerUpメインテナンス用)
									m_iPTCdBuzaiW = iPTCdBuzaiW;}
	void	SetPTTpMbr( MCHAR* sPTTpMbr)	{											// 寸法型式選択用種類コード
									Mstrncpy_s( m_sPTTpMbr, sPTTpMbr, MHPTSZ_TPMEMBER);}
	void	SetPTCdMbr( MCHAR* sPTCdMbr)	{											// 寸法型式
									Mstrncpy_s( m_sPTCdMbr, sPTCdMbr, MHPTSZ_CDMEMBER);}
	void	SetPTCdInpKb( MINT iPTCdInpKb)	{											// 入力点区分コード
									m_iPTCdInpKb = iPTCdInpKb;}
	void	SetPTCdHgt( MSTNDH iPTCdHgt)	{											// 取り付け高さ基準コード
									m_iPTCdHgt = iPTCdHgt;}
	void	SetPTCdPlc( MINT iPTCdPlc)	{												// 配置コード
									m_iPTCdPlc = iPTCdPlc;}
	void	SetPTCdIzon( MINT iPTCdIzon)	{											// 依存コード
									m_iPTCdIzon = iPTCdIzon;}
	void	SetPTCdMarume( MINT iPTCdMarume)	{										// 丸めコード
									m_iPTCdMarume = iPTCdMarume;}
	void	SetPTCdToritk( MINT iPTCdToritk)	{										// 取り付けコード　上下付けコード (0:下付け, 1:上付け)
									m_iPTCdToritk = iPTCdToritk;}

	MINT	GetPTCdGp()	{			
									return m_pPTGp->m_iCdGp;}
	MINT	GetPTCdBr()	{			
									return m_iPTCdBr;}
	MCHAR*	GetPTNmGeneral()	{	
									return m_sPTNmGeneral;}
	MCHAR*	GetPTNmParts1()	{		
									return m_sPTNmParts1;}
	MCHAR*	GetPTNmParts2()	{		
									return m_sPTNmParts2;}
	DWORD	GetPTColor()	{		
									return m_dPTColor;}
	MINT	GetPTCdBuzai()	{		
									return m_iPTCdBuzaiR;}
	MINT	GetPTCdBuzaiW()	{		
									return m_iPTCdBuzaiW;}
	MCHAR*	GetPTTpMbr()	{		
									return m_sPTTpMbr;}									// 寸法型式選択用種類コード
	MCHAR*	GetPTCdMbr()	{		
									return m_sPTCdMbr;}									// 寸法型式
	MINT	GetPTCdInpKb()	{		
									return m_iPTCdInpKb;}								// 入力点区分コード
	MINT	GetPTCdHgt()	{		
									return m_iPTCdHgt;}									// 取り付け高さ基準コード
	MINT	GetPTCdPlc()	{		
									return m_iPTCdPlc;}									// 配置コード
	MINT	GetPTCdIzon()	{		
									return m_iPTCdIzon;}								// 依存コード
	MINT	GetPTCdMarume()	{		
									return m_iPTCdMarume;}								// 丸めコード
	MINT	GetPTCdToritk()	{		
									return m_iPTCdToritk;}								// 取り付けコード　上下付けコード (0:下付け, 1:上付け)

	bool	IsYane()	{			
									return m_pPTGp->IsYane();}							// 屋根
	bool	IsTenjo()	{			
									return m_pPTGp->IsTenjo();}							// 天井
	bool	IsYuka()	{			
									return m_pPTGp->IsYuka();}							// 床
	bool	IsKiso()	{			
									return m_pPTGp->IsKiso();}							// 基礎
 
	bool	IsTategu()	{			
									return MINT(m_iPTCdBuzaiR / MP_BZICD_KIND) * MP_BZICD_KIND == MP_BZICD_TATEGU;}	// 建具
	bool	IsTenkai()	{			
									return (m_iPTCdBuzaiR == MP_BZICD_TENKAI);}			// 住棟展開
	bool	IsFrame()	{			
									return m_iPTCdIzon == MP_IZNCD_SUICYOKU;}			// 垂直( たて枠| 束)
	bool	IsPanel()	{			
									return m_iPTCdBr == MP_BR_PANEL;}					// パネル
	bool	IsKaiko()	{			
									return m_iPTCdBr == MP_BR_KAIKO;}					// 開口
	bool	IsKabe()	{			
									return m_iPTCdBr == MP_BR_KABE;}					// 壁
	bool	IsTaiKabeArea()	{		
									return m_iPTCdBuzaiR == MP_BZICD_TAIKABEAREA;}		// 耐力壁区画
	bool	IsTaiKabeLine()	{		
									return m_iPTCdBuzaiR == MP_BZICD_TAIKABELINE;}		// 耐力壁線
	bool	IsSijiKabeLine()	{	
									return m_iPTCdBuzaiR == MP_BZICD_SIJIKABELINE;}		// 支持壁線
	bool	IsOukaZai()	{			
									return m_iPTCdBr == MP_BR_BUZAI && 
											!( IsFrame() || IsPanel() || IsKaiko());}	// 横袈材
	bool	IsYukaPanel()	{		
									return m_iPTCdBuzaiR == MP_BZICD_YUKAPANEL;}		// 床パネル
	bool	IsKabePanel()	{		
									return m_iPTCdBuzaiR == MP_BZICD_KABEPANEL;}		// 壁パネル
	bool	IsTenjoPanel()	{		
									return m_iPTCdBuzaiR == MP_BZICD_TENJOPANEL;}		// 天井パネル
	bool	IsYanePanel()	{		
									return m_iPTCdBuzaiR == MP_BZICD_YANEPANEL;}		// 屋根パネル
};

} // namespace MC
