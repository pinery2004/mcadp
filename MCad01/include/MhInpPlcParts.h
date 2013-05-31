//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MhInpPlcParts.cpp
//
//		配置物入力関数
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

////////////////////////////////////////////////////////////////////////////
//	  配置物
////////////////////////////////////////////////////////////////////////////
#pragma once

#include	"MhPlcParts.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MHTATEGUINP_DO
	#pragma message( "<<< MHTATEGUINP・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== MHTATEGUINP・dll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class  DLL_EXPORT mtTateguInp
{
public:
	static MhTateguInfo		m_TateguInp;

public:
	//	配置用建具データ入力バッファに属性を設定
	static void SetKCode( MCHAR* cKCode)	
															{ m_TateguInp.SetKCode( cKCode);}
	static void SetROW( MREAL rROW)
															{ m_TateguInp.SetROW( rROW);}
	static void SetROH( MREAL rROH)
															{ m_TateguInp.SetROH( rROH);}
	static void SetHeight( MREAL rHeight)
															{ m_TateguInp.SetHgt( rHeight);}
	static void SetMU( MREAL rMUSz, MINT ik)
															{ m_TateguInp.SetMUSz( rMUSz, ik);}
	//	配置用建具データ入力バッファから属性を取得
	static MhTateguInfo* GetpTateguInp()
															{ return &m_TateguInp;}
																								//E	static void	 GetKCode( MCHAR* cKCode)
																								//E															{ Mstrcpy_s( cKCode, m_TateguInp.GetKCode());}
	static MREAL GetROW()		
															{ return m_TateguInp.GetROW();}
	static MREAL GetROH()				
															{ return m_TateguInp.GetROH();}
	static MREAL GetHeight()						
															{ return m_TateguInp.GetHeight();}
	static MREAL GetMUSz( MINT ik)					
															{ return m_TateguInp.GetMUSz( ik);}

};


#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MHPLCINP_DO
	#pragma message( "<<< MHPLCINP・dll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== MHPLCINP・dll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif


class DLL_EXPORT mtPlcInp
{
public:
	static mhPlcParts	m_PIInp;

public:
	//	配置データ入力バッファに属性を設定
	static void SetInpKai( MINT iKai)					
															{ m_PIInp.SetPIKai( iKai);}
	static void SetCdHgt( MINT iCdHgt)				
															{ m_PIInp.SetPICdHgt( iCdHgt);}
	static void SetPanelNo( MINT iPanelNo)			
															{ m_PIInp.SetPIPanelNo( iPanelNo);}
	static void SetInpKaikoNo( MINT iKaikoNo)			
															{ m_PIInp.SetPIKaikoNo( iKaikoNo);}
	static void SetIdPartsSpec( MINT iIdPartsSpec)			
															{ m_PIInp.SetPIIdPartsSpec( iIdPartsSpec);}
	static void SetIdMbr( MINT iMbrId)				
															{ m_PIInp.SetPIIdMbr( iMbrId);}
	static void SetpPartsSpec( mhPartsSpec* pPartsSpec)		
															{ m_PIInp.SetPIPartsSpec( pPartsSpec);}
	static void SetpMbr( MhMbr* pMbr)				
															{ m_PIInp.SetPIMbr( pMbr);}

	static void SetLenHosei( MINT ik, MREAL rLngHosei)
															{ m_PIInp.SetPILenHosei( ik, rLngHosei);}
	static void SetSinZure( MREAL rSinZure)		
															{ m_PIInp.SetPISinZure( rSinZure);}
	static void SetPlcZure( MREAL rPlcZure)		
															{ m_PIInp.SetPIPlcZure( rPlcZure);}
	static void SetHgt( MINT ik, MREAL rHgt)
															{ m_PIInp.SetPIHgt( ik, rHgt);}
	static void SetMaeHosei( MREAL rMaeHosei)
															{ m_PIInp.SetPISinZure( rMaeHosei);}
	static void SetOku( MREAL rOku)				
															{ m_PIInp.SetPIPlcZure( rOku);}
	static void SetOkuHosei( MREAL rOkuHosei)
															{ m_PIInp.SetPIHgt( 1, rOkuHosei);}

	static void	SetpAuxAttr( MhAuxAttr* pAuxAttr)
															{ m_PIInp.SetPIAuxAttr( pAuxAttr);}
	static void	SetpAuxTategu( MhTateguInfo* pAuxTategu)
															{ m_PIInp.SetPIAuxTategu( pAuxTategu);}
	static void	SetpAuxTenkai( JTTenkaiPr* pAuxTenkai)
															{ m_PIInp.SetPIAuxTenkai( pAuxTenkai);}
	//	配置データ入力バッファから属性を取得
	static MINT GetInpKai()							
															{ return m_PIInp.GetPIKai();}
	static MINT	GetCdHgt()							
															{ return m_PIInp.GetPICdHgt();}
	static MINT	GetPanelNo()						
															{ return m_PIInp.GetPIPanelNo();}
	static MINT	GetInpKaikoNo()						
															{ return m_PIInp.GetPIKaikoNo();}
	static MINT	GetComboPartsNmId()						
															{ return m_PIInp.GetPIIdPartsSpec();}
	static MINT	GetIdMbr()							
															{ return m_PIInp.GetPIIdMbr();}
	static mhPartsSpec* GetPartsSpec()						
															{ return m_PIInp.GetPIPartsSpec();}
	static MhMbr*  GetMbr()						
															{ return m_PIInp.GetPIMbr();}

	static MREAL GetLenHosei( MINT ik)				
															{ return m_PIInp.GetPILenHosei( ik);}
	static MREAL GetSinZure()						
															{ return m_PIInp.GetPISinZure();}
	static MREAL GetPlcZure()						
															{ return m_PIInp.GetPIPlcZure();}
	static MREAL GetHgt( MINT ik)					
															{ return m_PIInp.GetPIHgt( ik);}
	static MREAL GetMaeHosei()						
															{ return m_PIInp.GetPISinZure();}
	static MREAL GetOku()							
															{ return m_PIInp.GetPIPlcZure();}
	static MREAL GetOkuHosei()						
															{ return m_PIInp.GetPIHgt( 1);}

	static MhAuxAttr* GetpAuxAttr()				
															{ return m_PIInp.GetPIAuxAttr();}
	static MhTateguInfo*  GetpAuxTategu()				
															{ return m_PIInp.GetPIAuxTategu();}
	static JTTenkaiPr*  GetpAuxTenkai()			
															{ return m_PIInp.GetPIAuxTenkai();}
};

} // namespace MC
