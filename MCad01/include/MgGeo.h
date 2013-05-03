#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgGeo.h
//
//		図形処理
//
//
//  K.Matsu           09/01/18    Created.
//==========================================================================================
//
#include "MgPoint.h"
#include "MgAngle.h"
#include "MgPolygon.h"
#include "MgArc.h"
#include "MgCircle.h"
#include "MgTol.h"

#include "MgMat.h"

#ifdef DLL_EXPORT_GEO
	#undef DLL_EXPORT_GEO
#endif

#ifdef DLL_EXPORT_GEO_DO
	#pragma message( "<<< MgGeo・dll_EXport >>>")
	#define DLL_EXPORT_GEO							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode で inline関数がundefになる不具合対応
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_GEO
		#else
//			#pragma message( "=== MgGeo・dll_IMport ===")
			#define DLL_EXPORT_GEO						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_GEO
	#endif
#endif

namespace MC
{

class DLL_EXPORT_GEO MGeo
{
public:
	//======================( １次元 )==============================
	//
	static MREAL Abs(MREAL x)
						{return ((x > 0) ? x : -x);}
	static MINT Abs(MINT x)
						{return ((x > 0) ? x : -x);}
	static bool Zero(MREAL x, MREAL tol = MGPTOL->D)
						{return (x < tol && x > -tol);}
	static bool Equal(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x - y < tol && y - x < tol);}
	static bool EQ(MREAL x, MREAL y, MREAL tol = MGPTOL->D)							// MgEqualと同じ
						{return (x - y < tol && y - x < tol);}
	static bool LT(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x < y - tol);}
	static bool LE(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x <= y + tol);}
	static bool GT(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x > y + tol);}
	static bool GE(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x >= y - tol);}

	//======================( ２次元 )==============================
	// MgVect2D, MgPoint2D

	static MREAL Abs_2( const MgVect2D& v)											// ベクトルの長さの２乗	Abs**2
				 		{ return ( v.x*v.x+v.y*v.y);}
	static MREAL Abs( const MgVect2D& v)											// ベクトルの長さ		ABS
				 		{ return (MREAL)sqrt( v.x*v.x+v.y*v.y);}
	static MREAL Dist_2( const MgPoint2D& P1, const MgPoint2D& P2)					// ２点間の距離の２乗 MgDist**2
						{ return ( (P2.x-P1.x)*(P2.x-P1.x)+
								   (P2.y-P1.y)*(P2.y-P1.y));}
	static MREAL Dist( const MgPoint2D& P1, const MgPoint2D& P2)					// ２点間の距離
						{ return (MREAL)sqrt( (P2.x-P1.x)*(P2.x-P1.x)+
											   (P2.y-P1.y)*(P2.y-P1.y));}
	static bool Zero( const MgVect2D& v1)											// P1 == (0.,0.)	判定
						{ return Abs_2( v1) <= g_gTol.D_2;}
	static bool Zero( const MgVect2D& v1, MREAL tol)								// P1 == (0.,0.)	誤差指定の判定
						{ return Abs_2( v1) <= tol * tol;}
	static bool Equal( const MgVect2D& v1, const MgVect2D& v2)						// P1 == P2 		判定
				 		{ MgVect2D vt = v2 - v1; return Abs_2( vt) <= g_gTol.D_2;}
	static bool EqualV( const MgVect2D& v1, const MgVect2D& v2)						// V1 == V2 		ベクトル型式の角度の等号判定
				 		{ MgVect2D vt = v2 - v1; return Abs_2( vt) <= g_gTol.A_2;}
	static bool Equal( const MgVect2D& v1, const MgVect2D& v2, MREAL tol)			// P1 == P2			誤差指定の判定
				 		{ MgVect2D vt = v2 - v1; return Abs_2( vt) <= tol * tol;}
	static bool Parallel( const MgVect2D& v1, const MgVect2D& v2)					// V1とV2が平行であるかを確認
				 		{ MREAL ro = v1 ^ v2; MREAL ri = v1 * v2;
						  if( ro < 0) ro = - ro; if(ri < 0) ri = -ri;
						  return (ro <= ri * g_gTol.A);}
	static bool Parallel( const MgVect2D& v1, const MgVect2D& v2, MREAL* so, MREAL* si)	// V1とV2が平行であるかを確認し、外積と内積を出力
				 		{ MREAL ro = v1 ^ v2; MREAL ri = v1 * v2;
				 		  *so = ro; *si = ri;
						  if (ro < 0) ro = - ro; if (ri < 0) ri = -ri;
						  return (ro <= ri * g_gTol.A);}
	static void SVal( const MgPoint2D& ps, const MgPoint2D& pe, const MgPoint2D& p1, const MgVect2D& v1,
						MREAL* ss, MREAL* se)
																					// 直線(p1,v1)と線分(ps, pe)の交点を求めるのに使用可能
																					// ss = 直線(p1,v1)から点psへの垂直距離
																					// se = 直線(p1,v1)から点peへの垂直距離
						{ *ss = (v1 ^ (ps - p1));									// 線分2の始点側S
						  *se = (v1 ^ (pe - p1));}									// 線分2の終点側S
	static MgVect2D UnitizeV2( const MgVect2D& v1, MREAL i_Tol = g_gTol.D	);		// 長さ１に正規化する

	static MgVect2D RotL90( const MgVect2D& v1)										// 左90゜回転
						{ return	MgVect2D( -v1.y, v1.x);}
	static MgVect2D Rot180( const MgVect2D& v1)										// 180゜回転
						{ return	MgVect2D( -v1.x, -v1.y);}
	static MgVect2D RotR90( const MgVect2D& v1)										// 右90゜回転
						{ return	MgVect2D( v1.y, -v1.x);}

	//======================( ３次元 )==============================
	// MgVect3D, MgPoint3D

	static MREAL Abs_2( const MgVect3D& v)											// ベクトルの長さの２乗	MgAbs**2
				 		{ return v.x*v.x+v.y*v.y+v.z*v.z;}
	static MREAL Abs( const MgVect3D& v)											// ベクトルの長さ		MGABS
				 		{ return (MREAL)sqrt(v.x*v.x+v.y*v.y+v.z*v.z);}
	static MREAL Dist_2( const MgPoint3D& P1, const MgPoint3D& P2)					// ２点間の距離の２乗 MgDist**2
						{ return ( (P2.x-P1.x)*(P2.x-P1.x)+
								   (P2.y-P1.y)*(P2.y-P1.y)+
								   (P2.z-P1.z)*(P2.z-P1.z));}
	static MREAL Dist( const MgPoint3D& P1, const MgPoint3D& P2)					// ２点間の距離
						{ return (MREAL)sqrt( (P2.x-P1.x)*(P2.x-P1.x)+
											   (P2.y-P1.y)*(P2.y-P1.y)+
											   (P2.z-P1.z)*(P2.z-P1.z));}
	static bool Zero( const MgVect3D& v1)											// P1 == (0.,0.,0.)	判定
						{ return Abs_2(v1) <= g_gTol.D_2;}
	static bool Zero( const MgVect3D& v1, MREAL tol)								// P1 == (0.,0.,0.)	誤差指定の判定
						{ return Abs_2(v1) <= tol * tol;}
	static bool Equal( const MgVect3D& v1, const MgVect3D& v2)						// P1 == P2 		判定== 判定
				 		{ MgVect3D vt = v2 - v1; return Abs_2(vt) <= g_gTol.D_2;}  
	static bool EqualV( const MgVect3D& v1, const MgVect3D& v2)						// V1 == V2 		ベクトル型式の角度の等号判定
				 		{ MgVect3D vt = v2 - v1; return Abs_2(vt) <= g_gTol.A_2;}  
	static bool Equal( const MgVect3D& v1, const MgVect3D& v2, MREAL tol)			// P1 == P2			誤差指定の判定== 判定
				 		{ MgVect3D vt = v2 - v1; return Abs_2(vt) <= tol * tol;}  
	static bool Parallel( const MgVect3D& v1, const MgVect3D& v2)					// V1とV2が平行であるかを確認
				 		{ MgVect3D vo = v1 ^ v2; MREAL fi = v1 * v2;
						  return ( Abs_2(vo) <= fi * fi * g_gTol.A_2);}
	static bool Parallel( const MgVect3D& v1, const MgVect3D& v2, MgVect3D *pso, MREAL* si)	// V1とV2が平行であるかを確認し、外積と内積を出力
				 		{ MgVect3D vo = v1 ^ v2; MREAL fi = v1 * v2;
				 		  *pso = vo; *si = fi;
						  return ( Abs_2(vo) <= fi * fi * g_gTol.A_2);}
	static MgVect3D UnitizeV3( const MgVect3D& V1, MREAL i_Tol = g_gTol.D);			// 単位ベクトルを求める
	static MgVect3D TaniV3( const MgVect3D& V1, MREAL i_Tol = g_gTol.D);

	static MgVect3D RotL90( const MgVect3D& v1)										// 左90゜回転
						{ return	MgVect3D( -v1.y, v1.x, v1.z);}
	static MgVect3D Rot180( const MgVect3D& v1)										// 180゜回転
						{ return	MgVect3D( -v1.x, -v1.y, v1.z);}
	static MgVect3D RotR90( const MgVect3D& v1)										// 右90゜回転
						{ return	MgVect3D( v1.y, -v1.x, v1.z);}

#ifdef _MgPoint3DA
	//
	//======================( ２次元 )==============================
	static MgPoint2Da Norma( const MgPoint2D& p);
#endif
	
	////
	////======================( ３次元 )==============================
	////		ベクトルの単位ベクトルを求める
	////
	//static MgVect3D MgUnitizeV3( const MgVect3D& v, MREAL i_Tol = g_gTol.D);		//	(  O) 単位ベクトル

#ifdef _MgPoint3DA

	static MgPoint3Da Norma( const MgPoint3D& p);
#endif
	
	// ---------------------( ２次元 )------------------------------
	//
	//	２次元直線
	//
	static MgULine2D Rev( const MgULine2D& ULn1)									// 直線反転
						{ return MgULine2DC( ULn1.p, - ULn1.v);}
	//	２次元線分
	//
	static MgLine2D Rev( const MgLine2D& Ln1)										// 線分 反転
						{ return MgLine2D( Ln1.p[1], Ln1.p[0]);}

	static bool Parallel( const MgLine2D& Ln1, const MgLine2D& Ln2)					// Ln1とLn2が平行であるかを確認
				 		{ MgVect2D v1 = MgVect2DC(Ln1); MgVect2D v2 = MgVect2DC(Ln2);
						  return Parallel( v1, v2);}
	static bool Parallel( const MgLine2D& Ln1, const MgLine2D& Ln2, MREAL* so, MREAL* si)	// Ln1とLn2が平行であるかを確認し、外積と内積を出力
				 		{ MgVect2D v1 = MgVect2DC(Ln1); MgVect2D v2 = MgVect2DC(Ln2);
						  return Parallel( v1, v2, so, si);}

	// ---------------------( ３次元 )------------------------------
	//
	//	３次元直線
	//
	static MgULine3D Rev( const MgULine3D& ULn1)									// 直線反転
						{ return MgULine3D(ULn1.p, - ULn1.v);}

	static MgLine3D Rev( const MgLine3D& Ln1)										// 線分 反転
						{ return MgLine3D( Ln1.p[1], Ln1.p[0]);}

	static bool Parallel( const MgLine3D& Ln1, const MgLine3D& Ln2)					// Ln1とLn2が平行であるかを確認
				 		{ MgVect3D v1 = MgVect3DC(Ln1); MgVect3D v2 = MgVect3DC(Ln2);
						  return Parallel( v1, v2);}
	static bool Parallel( const MgLine3D& Ln1, const MgLine3D& Ln2, MgVect3D *pso, MREAL* si)	// Ln1とLn2が平行であるかを確認し、外積と内積を出力
				 		{ MgVect3D v1 = MgVect3DC(Ln1); MgVect3D v2 = MgVect3DC(Ln2);
						  return Parallel( v1, v2, pso, si);}


	// ---------------------( ２次元 )------------------------------
	//
	//	２次元円弧
	//
	static bool Parallel( const MgArc2D& arc1, const MgArc2D& arc2)					// arc1とarc2が平行であるかを確認
				 		{ return ( arc1.pc == arc2.pc);}

	static MINT Arc2Div( const MgArc2D& arc1, MINT n, const MgGPoint2D *gpto);		// 円弧をn等分する

	// ---------------------( ３次元 )------------------------------
	//
	//	３次元円弧
	//
	static bool Parallel( const MgArc3D& Arc1, const MgArc3D& Arc2)					// Arc1とArc2が平行であるかを確認
				 		{ return ( Arc1.Pc == Arc2.Pc) &&
								   Parallel( Arc1.V, Arc2.V);}

	static MINT Arc3Div( const MgArc3D& arc1, MINT n, const MgGPoint3D *gPto);		// 円弧をn等分する

	// ---------------------( ２次元 )------------------------------
	//
	//	２次元円
	//
	static bool Parallel( const MgCir2D& cir1, const MgCir2D& cir2)					// cir1とcir2が平行であるかを確認
				 		{ return ( cir1.pc == cir2.pc);}

	// ---------------------( ３次元 )------------------------------
	//
	//	３次元円
	//
	static bool Parallel( const MgCir3D& Cir1, const MgCir3D& Cir2)					// Cir1とCir2が平行であるかを確認
				 		{ return ( Cir1.Pc == Cir2.Pc) &&
								   Parallel( Cir1.V, Cir2.V);}

	/////////////////////////////////////////////////////////////////////////////
	//		直線　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//
	//	ベクトルと水平線の角度を求める
	//
	static MREAL GetAngleVH2(						// (  O) 左回転角度　（度）
													//		ベクトルの長さがg_gTol.D未満の場合は0度を返す
					const	MgVect2D&	i_v1		// (I  ) ベクトル
			);

	/////////////////////////////////////////////////////////////////////////////
	//	２点と水平線の角度を求める
	//
	static MREAL GetAngle2PtH2(						// (  O) 左回転角度　（度）
													//		始点、終点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgPoint2D&	i_p1,		// (I  ) 始点
					const	MgPoint2D&	i_p2		// (I  ) 終点
			);

	/////////////////////////////////////////////////////////////////////////////
	//	２ベクトルの角度を求める
	//
	static MREAL GetAngle2V2(						// (  O) 左回転角度　（度）
													//		ベクトルの長さがg_gTol.D未満の場合は0度を返す
					const	MgVect2D&	i_v1,		// (I  ) ベクトル1
					const	MgVect2D&	i_v2		// (I  ) ベクトル2
			);

	/////////////////////////////////////////////////////////////////////////////
	//	３点で作られる２直線の角度を求める
	//
	static MREAL GetAngle3Pt2(						// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgPoint2D&	i_p2,		// (I  ) 点2
					const	MgPoint2D&	i_p3		// (I  ) 点3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	２直線の角度を求める
	//
	static MREAL GetAngle2ULn2(						// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgULine2D&	i_ULn1,		// (I  ) 線分1
					const	MgULine2D&	i_ULn2		// (I  ) 線分2
			);

	/////////////////////////////////////////////////////////////////////////////
	//	直線と線分の角度を求める
	//
	static MREAL GetAngleULnLn2(					// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgULine2D&	i_ULn1,		// (I  ) 直線1
					const	MgLine2D&	i_Ln2		// (I  ) 線分2
			);

	//	-------------------------------------------------------
	static MREAL GetAngleLnULn2(					// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgULine2D&	i_ULn2		// (I  ) 直線2
			);

	/////////////////////////////////////////////////////////////////////////////
	//	２線分の角度を求める
	//
	static MREAL GetAngle2Ln2(						// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgLine2D&	i_Ln2		// (I  ) 線分2
			);

	/////////////////////////////////////////////////////////////////////////////
	//	２ベクトルの角度を求める
	//
	static MREAL GetAngle2V3(						// (  O) 左回転角度　（度）
													//		ベクトルの長さがg_gTol.D未満の場合は0度を返す
					const	MgVect3D&	i_v1,		// (I  ) ベクトル1
					const	MgVect3D&	i_v2,		// (I  ) ベクトル2
					const	MgVect3D&	i_vn		// (I  ) ２ベクトルに直交する単位ベクトル
			);

	/////////////////////////////////////////////////////////////////////////////
	//	３点で作られる２直線の角度を求める
	//
	static MREAL GetAngle3Pt3(						// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgPoint3D&	i_p2,		// (I  ) 点2
					const	MgPoint3D&	i_p3,		// (I  ) 点3
					const	MgVect3D&	i_vn		// (I  ) 点1,点,2点3を通る平面に直交する単位ベクトル
			);

	/////////////////////////////////////////////////////////////////////////////
	//	２直線の角度を求める
	//
	static MREAL GetAngle2ULn3(						// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
					const	MgVect3D&	i_vn		// (I  ) ２直線に直交する単位ベクトル
			);

	/////////////////////////////////////////////////////////////////////////////
	//	直線と線分の角度を求める
	//
	static MREAL GetAngleULnLn3(					// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
					const	MgVect3D&	i_vn		// (I  ) 直線と線分に直交する単位ベクトル
			);

	//	-------------------------------------------------------
	static MREAL GetAngleLnULn3(					// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
					const	MgVect3D&	i_vn		// (I  ) 線分と直線に直交する単位ベクトル
			);

	/////////////////////////////////////////////////////////////////////////////
	//	２線分の角度を求める
	//
	static MREAL GetAngle2Ln3(						// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
					const	MgVect3D&	i_vn		// (I  ) ２線分に直行する単位ベクトル
			);

	/////////////////////////////////////////////////////////////////////////////
	//		直線　平面　形状演算
	//
	// ---------------------( ３次元 )------------------------------
	//
	//	ベクトルと平面の角度を求める
	//
	static MREAL GetAngleVPln3(						// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgVect3D&	i_v1,		// (I  ) ベクトル1
					const	MgPlane3D&	i_Pln2		// (I  ) 平面2
			);

	/////////////////////////////////////////////////////////////////////////////
	//	直線と平面の角度を求める
	//
	static MREAL GetAngleULnPln3(					// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgPlane3D&	i_Pln2		// (I  ) 平面2
			);

	/////////////////////////////////////////////////////////////////////////////
	//	線分と平面の角度を求める
	//
	static MREAL GetAngleLnPln3(					// (  O) 左回転角度　（度）
													//		2点間の距離がg_gTol.D未満の場合は0度を返す
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgPlane3D&	i_Pln2		// (I  ) 平面2
			);

	/////////////////////////////////////////////////////////////////////////////
	//		直線　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//
	//	２直線間の角の2等分線を求める
	//
	static void Bisector2ULn2(						// (  O) ステータス
					const	MgULine2D&	i_ULn1,		// (I  ) 直線1
					const	MgULine2D&	i_ULn2,		// (I  ) 直線2
							MgULine2D*	o_pULn3		// (  O) 直線3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	直線と線分間の角の2等分線を求める
	//
	static void BisectorULnLn2(						// (  O) ステータス
					const	MgULine2D&	i_ULn1,		// (I  ) 直線1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MgULine2D*	o_pULn3		// (  O) 直線3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	線分と直線間の角の2等分線を求める
	//
	static void BisectorLnULn2(						// (  O) ステータス
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgULine2D&	i_ULn2,		// (I  ) 直線2
							MgULine2D*	o_pULn3		// (  O) 直線3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	線分と線分間の角の2等分線を求める
	//
	static void Bisector2Ln2(						// (  O) ステータス
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MgULine2D*	o_pULn3		// (  O) 直線3
			);

	/////////////////////////////////////////////////////////////////////////////
	//
	// ---------------------( ３次元 )------------------------------
	//
	//	２直線間の角の2等分線を求める
	//
	static void Bisector2ULn3(						// (  O) ステータス
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
							MgULine3D*	o_pULn3		// (  O) 直線3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	直線と線分間の角の2等分線を求める
	//
	static void BisectorULnLn3(						// (  O) ステータス
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
							MgULine3D*	o_pULn3		// (  O) 直線3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	線分と直線間の角の2等分線を求める
	//
	static void BisectorLnULn3(						//
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
							MgULine3D*	o_pULn3		// (  O) 直線3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	線分と線分間の角の2等分線を求める
	//
	static void Bisector2Ln3(						//
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
							MgULine3D*	o_pULn3		// (  O) 直線3
			);

	//
	//======================( ２次元、３次元 )==============================
	//	２次元、３次元座標変換マトリックス
	//
	//======================( ２次元 )==============================
	//		原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat2DE Mat2Rot( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2RotV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ２次元 )==============================
	//		原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat2DE Mat2RotRev( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2RotRevV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＸＹ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3DE Mat3RotZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3RotZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＸＹ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat3DE Mat3RotRevZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3RotRevZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＹＺ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3DE Mat3RotTX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return  Mat3RotTXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＹＺ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat3DE Mat3RotRevX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3RotRevXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3DE Mat3RotY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3RotYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3DE Mat3RotRevY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3RotRevYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスの加算
	//
	//	使用法
	//		MgMat3DE = MgMat2DE1 + MgMat2DE2;
	//
	//	| m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  +  | n21 n22 n23 |
	//	| m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2DE MatPlus2( const MgMat2DE& i_tm, const MgMat2DE& i_tn);

	//
	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの加算
	//
	//	使用法
	//		MgMat2DE1 += MgMat2DE2;
	//
	//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  =  | m21 m22 m23 |  +  | n21 n22 n23 |
	//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2DE MatPlusEqual2( MgMat2DE& io_tm, const MgMat2DE& i_tn);

	//===========================================================================
	//	処理内容
	//		負の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat2DE2 = - MgMat2DE1;
	//
	//	  | m11 m12 m13 |
	//	- | m21 m22 m23 |
	//	  | m31 m32 m33 |
	//
	static MgMat2DE MatSingleMinus2( const MgMat2DE& m1);

	//
	//===========================================================================
	//	処理内容
	//		負の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat2DE2 = - MgMat2DE1;
	//
	//	  | m11 m12 m13 |
	//	- | m21 m22 m23 |
	//	  | m31 m32 m33 |
	//
	static MgMat2DE MatMinusSingle2( const MgMat2DE& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの引算
	//
	//	使用法
	//		MgMat3DE = MgMat2DE1 - MgMat2DE2;
	//
	//	  | m11 m12 m13 |     | n11 n12 n13 |
	//	  | m21 m22 m23 |  -  | n21 n22 n23 |
	//	  | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2DE MatMinus2( const MgMat2DE& i_tm, const MgMat2DE& i_tn);

	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスの引算
	//
	//	使用法
	//		MgMat2DE1 -= MgMat2DE2;
	//
	//	| m11 m12 m13 |    | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  = | m21 m22 m23 |  -  | n21 n22 n23 |
	//	| m31 m32 m33 |    | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2DE MatMinusEqual2( MgMat2DE& io_tm, const MgMat2DE& i_tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスのかけ算
	//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
	//
	//	使用法
	//		MgMat3DE = MgMat2DE1 * MgMat2DE2;
	//
	//	| m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  X  | n21 n22 n23 |
	//	| m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2DE MatMult2( const MgMat2DE& i_tm, const MgMat2DE& i_tn);

	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスのかけ算
	//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
	//
	//	使用法
	//		MgMat2DE2 *= MgMat2DE1;
	//
	//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  =  | m21 m22 m23 |  X  | n21 n22 n23 |
	//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2DE MatMultEqual2( MgMat2DE& io_tm, const MgMat2DE& i_tn);

	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgPoint2Dpo = MgPoint2Dp * MgMat2DEtm;
	//
	//					   | m11 m12 m13 |
	//	| px  py  1  |  X  | m21 m22 m23 |
	//					   | m31 m32 m33 |     
	//
	static MgVect2D MatMultPt22( const MgVect2D& i_pt, const MgMat2DE& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgPoint2Dp *= MgMat2DEm;
	//
	//										  | m11 m12 m13 |
	//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 m23 |
	//				   						  | m31 m32 m33 |
	//
	static MgVect2D MatMultEqualPt22( MgVect2D& io_pt, const MgMat2DE& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D = MgULine2D*  MgMat2DE;
	//
	//	| px  py  1  |     | m11 m12 m13 |
	//	| vx  vy  0  |  X  | m21 m22 m23 |
	//					   | m31 m32 m33 |
	//
	static MgULine2D MatMultULn22( const MgULine2D& i_uln, const MgMat2DE& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D *= MgMat2DE;
	//
	//	| px  py  1  |     | px  py  1  |     | m11 m12 m13 |
	//	| vx  vy  0  |  =  | vx  vy  1  |  X  | m21 m22 m23 |
	//			             				  | m31 m32 m33 |
	//
	static MgULine2D MatMultEqualULn22( MgULine2D& io_uln, const MgMat2DE& i_tm);

	//===============( ２次元座標変換マトリックスで３次元座標処理 )==============
	//
	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgVect3D2 = MgVect3D1 * MgMat2DE1;
	//
	//						  | m11 m12 0 m13 |     
	//	| px  py  pz  1 |  X  | m21 m22 0 m23 |
	//						  |  0   0  1  0  |
	//						  | m31 m32 0 m33 |
	//
	static MgVect3D MatMultPt32( const MgVect3D& i_Pt, const MgMat2DE& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgVect3D *= MgMat2DE;
	//
	//						 						| m11 m12 0 m13 |
	//	| px  py  pz  1 |  =  | px  py  pz  1 |  X  | m21 m22 0 m23 |
	//			   									|  0   0  1  0  |
	//			   									| m31 m32 0 m33 |
	
	
	static MgVect3D MatMultEqualPt32( MgVect3D& io_Pt, const MgMat2DE& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D = MgULine2D * MgMat2DE;
	//
	//	| px  py  pz  1 |	  | m11 m12 0 m13 |
	//	| vx  vy  vz  1 |  X  | m21 m22 0 m23 |
	//						  |  0   0  1  0  |
	//			   			  | m31 m32 0 m33 |
	//
	static MgULine3D MultULn32( const MgULine3D& ULn1, const MgMat2DE& m2);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D = MgULine2D * MgMat2DE;
	//
	//	| px  py  pz  1 |	  | m11 m12 0 m13 |
	//	| vx  vy  vz  1 |  X  | m21 m22 0 m23 |
	//						  |  0   0  1  0  |
	//						  | m31 m32 0 m33 |
	//
	static MgULine3D MatMultULn32( const MgULine3D& i_ULn, const MgMat2DE& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D *= MgMat2DE;
	//
	//	| px  py  pz  1 |     | px  py  pz  1 |		| m11 m12 0 m13 |
	//	| vx  vy  vz  1 |  =  | vx  vy  vz  1 |  X  | m21 m22 0 m23 |
	//												|  0   0  1  0  |
	//				 				   				| m31 m32 0 m33 |
	//
	static MgULine3D MatMultEqualULn32( MgULine3D& io_ULn, const MgMat2DE& i_tm);

	//===========================================================================
	//
	//	３Ｄ座標変換マトリックスの計算
	//
	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの加算
	//
	//	使用法
	//		MgMat3DE_3 = MgMat3DE_1 + MgMat3DE_2;
	//
	//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat3DE MatPlus3( const MgMat3DE& i_Tm, const MgMat3DE& i_Tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの加算
	//
	//	使用法
	//		MgMat3DE += MgMat3DE;
	//
	//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat3DE MatPlusEqual3( MgMat3DE& io_Tm, const MgMat3DE& i_Tn);

	//===========================================================================
	//	処理内容
	//		負の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3DE_2 = - MgMat3DE_1;
	//
	//	  | m11 m12 m13 m14 |
	//	- | m21 m22 m23 m24 |
	//	  | m31 m32 m33 m34 |
	//	  | m41 m42 m43 m44 |     
	//
	static MgMat3DE MatSingleMinus3( const MgMat3DE& i_Tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの引算
	//
	//	使用法
	//		MgMat3DE_3 = MgMat3DE_1 - MgMat3DE_2;
	//
	//	  | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
	//	  | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	  | m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat3DE MatMinus3( const MgMat3DE& i_Tm, const MgMat3DE& i_Tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの引算
	//
	//	使用法
	//		MgMat3DE -= MgMat3DE;
	//
	//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat3DE MatMinusEqual3( MgMat3DE& io_Tm, const MgMat3DE& i_Tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスのかけ算
	//
	//	使用法
	//		MgMat3DE_3 = MgMat3DE_1 * MgMat3DE_2;
	//
	//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat3DE MatMult3( const MgMat3DE& i_Tm, const MgMat3DE& i_Tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスのかけ算
	//
	//	使用法
	//		MgMat3DE *= MgMat3DE;
	//
	//	| m11 m12 m13 m14 |     | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat3DE MatMultEqual3( MgMat3DE& io_Tm, const MgMat3DE& i_Tn);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより２次元データを座標変換する
	//
	//	使用法
	//		MgMat3DE_2 = MgVect2D * MgMat3DE_1;
	//
	//						    | m11 m12 m13 m14 |
	//	| px  py  0   1   |  X  | m21 m22 m23 m24 |
	//						    | m31 m32 m33 m34 |
	//						    | m41 m42 m43 m44 |
	//
	static MgVect2D MatMultPt23( const MgVect2D& i_Pt, const MgMat3DE& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより２次元データを座標変換する
	//
	//	使用法
	//		MgVect2D *= MgMat3DE;
	//
	//						     					    | m11 m12 m13 m14 |
	//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 m24 |
	//	           									    | m31 m32 m33 m34 |
	//	           									    | m41 m42 m43 m44 |
	//
	static MgVect2D MatMultEqualPt23( MgVect2D& io_Pt, const MgMat3DE& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより３次元データを座標変換する
	//
	//	使用法
	//		MgVect3D_2 = MgVect3D_1 * MgMat3DE;
	//
	//	 					    | m11 m12 m13 m14 |
	//	| px  py  pz  1   |  X  | m21 m22 m23 m24 |
	//						    | m31 m32 m33 m34 |
	//						    | m41 m42 m43 m44 |
	//
	static MgVect3D MatMultPt33( const MgVect3D& i_Pt, const MgMat3DE& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより３次元データを座標変換する
	//
	//	使用法
	//		MgVect3D *= MgMat3DE;
	//
	//							 					    | m11 m12 m13 m14 |
	//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
	//												    | m31 m32 m33 m34 |
	//												    | m41 m42 m43 m44 |
	//
	static MgVect3D MatMultEqualPt33( MgVect3D& io_Pt, const MgMat3DE& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより３次元データを座標変換する
	//
	//	使用法
	//		MgULine3D_2 = MgULine3D_1 * MgMat3DE;
	//
	//	| px  py  pz  1   |     | m11 m12 m13 m14 |
	//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
	//							| m31 m32 m33 m34 |
	//							| m41 m42 m43 m44 |
	//
	static MgULine3D MatMultULn33( const MgULine3D& i_ULn, const MgMat3DE& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより３次元データを座標変換する
	//
	//	使用法
	//		MgVect3D *= MgMat3DE;
	//
	//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
	//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
	//													| m31 m32 m33 m34 |
	//													| m41 m42 m43 m44 |
	//
	static MgULine3D MatMultEqualULn33( MgULine3D& io_ULn, const MgMat3DE& i_Tm);

	//======================( ２次元 )==============================
	//	処理内容
	//		原点を中心に回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat2DE = MgMat2DERotV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos  sin  0. |
	//	| -sin  cos  0. |
	//	|   0.   0.  1. |
	//
	static MgMat2DE Mat2RotV( const MgVect2D& v);

	//======================( ２次元 )==============================
	//	処理内容
	//		原点を中心に逆回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat2DE = MgMat2DERotRevV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	| cos -sin  0. |
	//	| sin  cos  0. |
	//	|  0.   0.  1. |
	//
	static MgMat2DE Mat2RotRevV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＸＹ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3DE = MgMat3DERotZV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos  sin  0.  0. |
	//	| -sin  cos  0.  0. |
	//	|   0.   0.  1.  0. |
	//	|   0.   0.  0.  1. |
	//
	static MgMat3DE Mat3RotZV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＸＹ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3DE = MgMat3DERotRevZV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos -sin  0.  0. |
	//	|  sin  cos  0.  0. |
	//	|   0.   0.  1.  0. |
	//	|   0.   0.  0.  1. |
	//
	static MgMat3DE Mat3RotRevZV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＹＺ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3DE = MgMat3DERotTXV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  1.   0.   0.  0. |
	//	|  0.  cos  sin  0. |
	//	|  0. -sin  cos  0. |
	//	|  0.   0.   0.  1. |
	//
	static MgMat3DE Mat3RotTXV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＹＺ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3DE = MgMat3DERotRevXV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  1.   0.   0.  0. |
	//	|  0.  cos -sin  0. |
	//	|  0.  sin  cos  0. |
	//	|  0.   0.   0.  1. |
	//
	static MgMat3DE Mat3RotRevXV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3DE = MgMat3DERotYV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos   0. -sin   0. |
	//	|   0.   1.   0.   0. |
	//	|  sin   0.  cos   0. |
	//	|   0.   0.   0.   1. |
	//
	static MgMat3DE Mat3RotYV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＺＸ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3DE = MgMat3DERotRevYV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos   0.  sin   0. |
	//	|   0.   1.   0.   0. |
	//	| -sin   0.  cos   0. |
	//	|   0.   0.   0.   1. |
	//
	static MgMat3DE Mat3RotRevYV( const MgVect2D& v);

	//======================( ２次元 )==============================
	//	処理内容
	//	    Ｘ，Ｙ方向に拡大／縮小するマトリックスを作成
	//
	//	使用法
	//		Mgmat_2 = MgMat2DEScl(MgVect2D_1);
	//
	//	| sx  0   0  |
	//	| 0   xy  0  |
	//	| 0   0   1  |
	//
	static MgMat2DE Mat2Scl( const MgVect2D& vs);

	//======================( ３次元 )==============================
	//	処理内容
	//	    Ｘ，Ｙ，Ｚ方向に拡大／縮小するマトリックスを作成する
	//
	//	使用法
	//		Mgmat3_2 = MgMat3DEScl(MgMat3DE_1);
	//
	//	| sx  0   0   0  |
	//	| 0   xy  0   0  |
	//	| 0   0   sz  0  |
	//	| 0   0   0   1  |
	//
	static MgMat3DE Mat3Scl( const MgVect3D& vs);

	//======================( ２次元 )==============================
	//	処理内容
	//		平行移動の変換マトリックスを作成する
	//
	//	使用法
	//		MgMat2DE = MgMat2DEMov(MgVect2D)
	//
	//	|  1.  0.  0. |
	//	|  0.  1.  0. |
	//	|  v.x v.y 1. |
	//
	static MgMat2DE Mat2Mov( const MgVect2D& v);
	static MgMat2DE Mat2Mov( const MgPoint2D& p)
						{ return Mat2Mov( (MgVect2D&)p);}

	//======================( ３次元 )==============================
	//	処理内容
	//		平行移動の変換マトリックスを作成する
	//
	//	使用法
	//		Mgmat3 = MgMat3DEMov(MgVect3D)
	//
	//	| 1.  0.  0.  0. |
	//	| 0.  1.  0.  0. |
	//	| 0.  0.  1.  0. |
	//	| v.x v.y v.z 1. |
	//
	static MgMat3DE Mat3Mov( const MgVect3D& v);
	static MgMat3DE Mat3Mov( const MgPoint3D& p)
						{ return Mat3Mov( (MgVect3D&)p);}

	//======================( ２次元 )==============================
	//	処理内容
	//		変換マトリックスの逆変換マトリックスを作成
	//
	//	使用法
	//		MgMat2DE = MgMat2DEInv(MgMat2DE);
	//
	//	| m11 m21 m31 |
	//	| m12 m22 m32 |			（入力行列は単位行列である事 ???）
	//	| m13 m23 m33 |
	//
	static MgMat2DE Mat2Inv( const MgMat2DE& i_tm);

	//======================( ３次元 )==============================
	//	処理内容
	//	    変換マトリックスの逆変換マトリックスを作成する
	//
	//	使用法
	//		Mgmat3_2 = MgMat3DEInv(MgMat3DE_1);
	//
	//	| m11 m21 m31 m41 |
	//	| m12 m22 m32 m42 |     （入力行列は単位行列である事 ???）
	//	| m13 m23 m33 m43 |
	//	| M14 m24 m34 m44 |
	//
	static MgMat3DE Mat3Inv( const MgMat3DE& i_Tm);

	//======================( ２次元 )==============================
	//		直線に対する鏡像座標変換マトリックスを作成
	//
	static MgMat2DE Mat2Mirror(						// (  O) 鏡像変換行列
					const	MgMat2DE&	i_tm, 		// (I  ) 変換行列
					const	MgULine2D&	i_uln		// (I  ) 鏡映の軸とする直線
			);

	//======================( ３次元 )==============================
	//		平面に対する鏡像座標変換マトリックスを作成
	//
	static MgMat3DE Mat3Mirror(						// (  O) 鏡像変換行列
					const	MgMat3DE&  i_Tm,	 	// (I  ) 変換行列
					const	MgPlane3D& i_Pln		// (I  ) 鏡映の面とする平面
			);

	//======================( ２次元 )==============================
	//		中心点と回転角より座標変換マトリックスを作成
	//
	static MgMat2DE Mat2Rot(						// (  O) 変換行列
					const	MgPoint2D&	i_ptc, 		// (I  ) 回転の中心となる点
					const	MREAL&		i_ar		// (I  ) 回転角 Degree
			);

	//======================( ３次元 )==============================
	//		回転軸となる直線と回転角より座標変換マトリックスを作成
	//
	static MgMat3DE Mat3Rot(						// (  O) 変換行列
					const	MgULine3D&	i_ULn, 		// (I  ) 回転軸となる直線
					const	MREAL&		i_ar		// (I  ) 回転角(Degree)
			);

	//======================( ３次元 )==============================
	//		正投象座標変換マトリックスを計算する
	//
	static MgMat3DE Mat3NProj(						// (  O) 正投象変換行列
					const	MgMat3DE&	i_Tm,		// (I  ) 入力座標変換行列
					const	MgPlane3D&	i_Pln		// (I  ) 投象面
			);

	//======================( ３次元 )==============================
	//		斜投象座標変換マトリックスを計算する
	//
	static MgMat3DE Mat3SProj(						// (  O) 斜投象変座標変換行列
					const	MgMat3DE&	i_Tm,		// (I  ) 入力座標変換行列
					const	MgPlane3D&	i_Pln,		// (I  ) 投象面
					const	MgVect3D&	i_V			// (I  ) 投象方向を示す単位ベクトル
			);

	//===========================================================================
	//		３Ｄ平面上の点から２Ｄ座標への変換行列を計算する
	//
	// ---------------------( ３次元 )------------------------------
	//		底辺がX軸に平行になるようXY平面に投影するマトリックスを求める
	//
	//
	//	平面式	ax + by + cz + d = 0
	//
	//
	//	屋根
	//
	//	(|Pln.v.z|<0.6)
	//
	//		Z方向のベクトルを　Ｘ,　Zの順で回転すると次の式となり、
	//		入力平面に相当する												（２Ｄ→３Ｄ）
	//		逆に入力平面を　Ｚ， Ｘの順で回転するとZ方向のベクトルとなる	（３Ｄ→２Ｄ）、
	//
	//		sx: sin(x), cx: cos(x), sz: sin(z), cz: cos(z), (ab): sqrt(a*a+b*b)
	//
	//		cz = -b/(ab)	sz = a/(ab)
	//		cx = c			sx = (ab)
	//
	//	================================================
	//	３Ｄ→２Ｄ
	//
	//					|	1			0			0		|
	//	X軸逆回転	A	|	0			cx			-sx		|
	//					|	0			sx			cx		|
	//
	//					|	cz			-sz			0		|
	//	Z軸逆回転	B	|	sz			cz			0		|
	//					|	0			0			1		|
	//
	//	Z軸逆回転後にX軸逆回転する
	//					|	cz			-cxsz		sxsz	|
	//		A x B	=	|	sz			cxcz		-sxcz	|
	//					|	0			sx			cx		|
	//
	//					|	-b/(ab)		-ac/(ab)	a		|
	//					|	a/(ab)		-bc/(ab)	b		|
	//					|	0			(ab)		c		|
	//
	//	================================================
	//	２Ｄ→３Ｄ
	//
	//	Z軸逆回転後(2)に逆移動(1)し次の回転を行う
	//
	//					|	cz			sz			0		|
	//	Z軸回転		A	|	-sz			cz			0		|
	//					|	0			0			1		|
	//
	//					|	1			0			0		|
	//	X軸回転		B	|	0			cx			sx		|
	//					|	0			-sx			cx		|
	//
	//	X軸回転後にＺ軸回転する
	//					|	cz			sz			0		|
	//		A x B		|	-szcx		czcx		sx		|
	//					|	szsx		-czsx		cx		|
	//
	//					|	-b/(ab)		a/(ab)		0		|
	//					|	-ac/(ab)	-bc/(ab)	(ab)	|
	//					|	a			b			c		|
	//
	//	================================================
	//
	//	|pln.v.y|<0.6	
	//
	//	X軸回転				-sx		cx
	//	Y軸回転		sy･cx	-sx		cy･cx
	//				a		b		c
	//
	//	================================================
	//	３Ｄ→２Ｄ
	//
	//					|	1			0			0			|
	//	Ｘ軸逆回転	B	|	0			cx			-sx			|
	//					|	0			sx			cx			|
	//
	//					|	cy			0			sy			|
	//	Ｙ軸逆回転	A	|	0			1			0			|
	//					|	-sy			0			cy			|
	//
	//	Ｙ軸逆回転後にX軸逆回転する
	//					|	cy			sysx		sycx		|
	//		A x B		|	0			cx			-sx			|
	//					|	-sy			cysx		cycx		|
	//
	//					|	c/(ca)		-ab/(ca)	a			|
	//		-			|	0			(ca)		b			|
	//					|	-a/(ca)		-bc/(ca)	c			|
	//
	//	================================================
	//
	//	２Ｄ→３Ｄ
	//					
	//	Z軸逆回転後に逆移動する
	//
	//					|	cy			0			-sy			|
	//	Ｙ軸回転	A	|	0			1			0			|
	//					|	sy			0			cy			|
	//
	//					|	1			0			0			|
	//	X軸回転		B	|	0			cx			sx			|
	//					|	0			-sx			cx			|
	//
	//	X軸回転後にY軸回転する
	//					|	cy			0			-sy			|
	//			A x B	|	sxsy		cx			sxcy		|
	//					|	cxsy		-sx			cxcy		|
	//
	//					|	c/(ca)		0			-a/(ca)		|
	//					|	-ab/(ca)	(ca)		-bc/(ca)	|
	//					|	a			b			c			|
	
	static void Mat3PlntoXY(
					const	MgPlane3D&	i_Pln,		// (I  ) 変換対象平面
					const	MgPoint3D&	i_PtOrg,	// (I  ) 原点座標			
							MgMat3DE*	o_pMatXY,	// (  O) Pln to XY平面 ３Ｄマトリックス
							MgMat3DE*	o_pMatPln	// (  O) XY平面 to Pln ３Ｄマトリックス
					);
	
	//===================(３次元 → ２次元)=========================
	//		３Ｄ座標を２Ｄ座標へ変換する
	//
	static void Point3Dto2D(
					const	MgPoint3D&	i_P,		// (I  ) ３Ｄ座標
					const	MgMat3DE&	i_Tm,		// (I  ) 座標変換マトリックス
							MgPoint2D*	o_pP		// (  O) ２Ｄ座標
					);

	//===================(３次元 → ２次元)=========================
	//		３Ｄ線分を２Ｄ線分へ座標変換する
	//
	static inline void Line3Dto2D(
					const MgLine3D&		i_Lni,		// (I  ) ３Ｄ線分
					const MgMat3DE&		i_Mat,		// (I  ) 座標変換マトリックス
						  MgLine2D*		o_plno		// (  O) ２Ｄ線分
					)
	{
		Point3Dto2D( i_Lni.p[0], i_Mat, &o_plno->p[0]); 
		Point3Dto2D( i_Lni.p[1], i_Mat, &o_plno->p[1]);
	}

	//===================(３次元 → ２次元)=========================
	//		３Ｄ直線を２Ｄ直線へ座標変換する
	//
	static void ULine3Dto2D(
					const	MgULine3D&	i_ULn,		// (I  ) ３Ｄ直線
					const	MgMat3DE&	i_Mt,		// (I  ) 座標変換マトリックス
						 	MgULine2D*	o_puln		// (  O) ２Ｄ直線
					);

	//===================(３次元 → ２次元)=========================
	//		３Ｄ座標を２Ｄ座標へ変換する
	//
	static MgPoint2D Point3Dto2D2(					// (  O) ２Ｄ座標
					const	MgPoint3D&	i_P,		// (I  ) ３Ｄ座標
					const	MgMat3DE&	i_Tm		// (I  ) 座標変換マトリックス
					);

	//===================(３次元 → ２次元)=========================
	//		３Ｄ線分を２Ｄ線分へ座標変換する
	//
	static inline MgLine2D Line3Dto2D2(				// (  O) ２Ｄ線分
					const MgLine3D&		Lni,		// (I  ) ３Ｄ線分
					const MgMat3DE&		Mat			// (I  ) 座標変換マトリックス
					)
	{
		return MgLine2D( 
					  Point3Dto2D2( Lni.p[0], Mat), 
					  Point3Dto2D2( Lni.p[1], Mat));
	}  

	//===================(３次元 → ２次元)=========================
	//		３Ｄ直線を２Ｄ直線へ座標変換する
	//
	static MgULine2D ULine3Dto2D2(					// (  O) ２Ｄ直線
					const	MgULine3D&	i_ULn,		// (I  ) ３Ｄ直線
					const	MgMat3DE&	i_Tm		// (I  ) 座標変換マトリックス
					);

	//===================(３次元 → ２次元)=========================
	//		３Ｄ座標群を２Ｄ座標群へ変換する
	//
	static void	GPoint3Dto2D(
					const	MgGPoint3D&	i_GP,		// (I  ) ３Ｄ座標群
					const	MgMat3DE&	i_Tm,		// (I  ) 座標変換マトリックス
							MgGPoint2D*	o_pGP		// (  O) ２Ｄ座標群
					);
	
	//===================(３次元 → ２次元)=========================
	//		３Ｄ座標群（ポリライン）を２Ｄ座標群へ変換する
	//
	static void	Polyg3Dto2D(
					const	MgPolyg3D&	i_Pg,		// (I  ) ３Ｄ座標群
					const	MgMat3DE&	i_Tm,		// (I  ) 座標変換マトリックス
							MgPolyg2D*	o_pPg		// (  O) ２Ｄ座標群
					);
	
	//===================(３次元 → ２次元)=========================
	//		３Ｄ線分群を２Ｄ線分群へ変換する
	//
	static void	GLine3Dto2D(
					const	MgGLine3D&	i_GLn,		// (I  ) ３Ｄ線分群
					const	MgMat3DE&	i_Tm,		// (I  ) 座標変換マトリックス
							MgGLine2D*	o_pgln		// (  O) ２Ｄ線分群
					);
	
	//===================(３次元 → ２次元)=========================
	//		３Ｄ多角形群（ポリライン群）を２Ｄ多角形群へ変換する
	//
	static void GPolyg3Dto2D(
					const	MgGPolyg3D&	i_GPg,		// (I  ) ３Ｄ多角形群
					const	MgMat3DE&	i_Tm,		// (I  ) 座標変換マトリックス
						 	MgGPolyg2D*	o_pgpg		// (  O) ２Ｄ多角形群
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ座標を３Ｄ座標へ変換する
	//
	static void	Point2Dto3D(
					const	MgPoint2D&	i_pt,		// (I  ) ２Ｄ座標
					const	MgMat3DE&	i_Tm,		// (I  ) 座標変換マトリックス
							MgPoint3D*	o_pPt		// (  O) ３Ｄ座標
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ線分を３Ｄ線分へ座標変換する
	//
	static inline void Line2Dto3D(
					const MgLine2D&		i_lni,		// (I  ) ２Ｄ線分
					const MgMat3DE&		i_Mat,		// (I  ) 座標変換マトリックス
						  MgLine3D*		o_pLno		// (  O) ３Ｄ線分
					)
	{
		Point2Dto3D( i_lni.p[0], i_Mat, &o_pLno->p[0]); 
		Point2Dto3D( i_lni.p[1], i_Mat, &o_pLno->p[1]);
	}  


	//===================(２次元 → ３次元)=========================
	//		２Ｄ直線を３Ｄ直線へ座標変換する
	//
	static void ULine2Dto3D(
					const	MgULine2D	&i_uln,		// (I  ) ２Ｄ直線
					const	MgMat3DE	&i_Tm,		// (I  ) 座標変換マトリックス
						 	MgULine3D	*o_ULn		// (  O) ３Ｄ直線
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ座標を３Ｄ座標へ変換する
	//
	static MgPoint3D Point2Dto3D3(					// (  O) ３Ｄ座標
					const	MgPoint2D&	i_Pt,		// (I  ) ２Ｄ座標
					const	MgMat3DE	&i_Tm		// (I  ) 座標変換マトリックス
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ線分を３Ｄ線分へ座標変換する
	//
	static MgLine3D Line2Dto3D3(					// (  O) ３Ｄ線分
					const MgLine2D&		lni,		// (I  ) ２Ｄ線分
					const MgMat3DE		&Mat		// (I  ) 座標変換マトリックス
					)
	{
		return MgLine3D(
					  Point2Dto3D3( lni.p[0], Mat), 
					  Point2Dto3D3( lni.p[1], Mat));
	}  

	//===================(２次元 → ３次元)=========================
	//		２Ｄ直線を３Ｄ直線へ座標変換する
	//
	static MgULine3D ULine2Dto3D3(					// (  O) ３Ｄ直線
					const	MgULine2D	&i_uln,		// (I  ) ２Ｄ直線
					const	MgMat3DE	&i_Tm		// (I  ) 座標変換マトリックス
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ座標群を３Ｄ座標群へ変換する
	//
	static void	GPoint2Dto3D(
					const	MgGPoint2D	&i_GPt,		// (I  ) ２Ｄ座標群
					const	MgMat3DE	&i_Tm,		// (I  ) 座標変換マトリックス
							MgGPoint3D	*o_GPt		// (  O) ３Ｄ座標群
					);
	
	//===================(２次元 → ３次元)=========================
	//		２Ｄ座標群（ポリライン）を３Ｄ座標群へ変換する
	//
	static void	Polyg2Dto3D(
					const	MgPolyg2D&	i_Pg,		// (I  ) ２Ｄ座標群
					const	MgMat3DE	&i_Tm,		// (I  ) 座標変換マトリックス
							MgPolyg3D*	o_Pg		// (  O) ３Ｄ座標群
					);
	
	//===================(２次元 → ３次元)=========================
	//		２Ｄ直線群を３Ｄ直線群へ変換する
	//
	static void	GLine2Dto3D(
					const	MgGLine2D&	i_gln,		// (I  ) ２Ｄ直線群
					const	MgMat3DE	&i_Tm,		// (I  ) 座標変換マトリックス
							MgGLine3D	*o_GLn		// (  O) ３Ｄ直線群
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ多角形群（ポリライン群）を３Ｄ多角形群へ変換する
	//
	static void GPolyg2Dto3D(
					const	MgGPolyg2D	&i_GPg,		// (I  ) ２Ｄ多角形群
					const	MgMat3DE	&i_Tm,		// (I  ) 座標変換マトリックス
						 	MgGPolyg3D	*o_GPg		// (  O) ３Ｄ多角形群
					);

	//
	//======================( ３Ｄ，４Ｄ )==============================
	//	３Ｄ，４Ｄマトリックス
	//
	//======================( ２次元 )==============================
	//		原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3D Mat3Rot( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3RotV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ２次元 )==============================
	//		原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat3D Mat3RotRev( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3RotRevV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＸＹ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat4D Mat4RotZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat4RotZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＸＹ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat4D Mat4RotRevZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat4RotRevZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＹＺ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat4D Mat4RotTX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return  Mat4RotTXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＹＺ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat4D Mat4RotRevX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat4RotRevXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat4D Mat4RotY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat4RotYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat4D Mat4RotRevY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat4RotRevYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスの加算
	//
	//	使用法
	//		MgMat4D = MgMat3D1 + MgMat3D2;
	//
	//	| m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  +  | n21 n22 n23 |
	//	| m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat3D MatPlus2( const MgMat3D& i_tm, const MgMat3D& i_tn);

	//
	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの加算
	//
	//	使用法
	//		MgMat3D1 += MgMat3D2;
	//
	//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  =  | m21 m22 m23 |  +  | n21 n22 n23 |
	//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat3D MatPlusEqual2( MgMat3D& io_tm, const MgMat3D& i_tn);

	//===========================================================================
	//	処理内容
	//		負の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3D2 = - MgMat3D1;
	//
	//	  | m11 m12 m13 |
	//	- | m21 m22 m23 |
	//	  | m31 m32 m33 |
	//
	static MgMat3D MatSingleMinus2( const MgMat3D& m1);

	//
	//===========================================================================
	//	処理内容
	//		負の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3D2 = - MgMat3D1;
	//
	//	  | m11 m12 m13 |
	//	- | m21 m22 m23 |
	//	  | m31 m32 m33 |
	//
	static MgMat3D MatMinusSingle2( const MgMat3D& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの引算
	//
	//	使用法
	//		MgMat4D = MgMat3D1 - MgMat3D2;
	//
	//	  | m11 m12 m13 |     | n11 n12 n13 |
	//	  | m21 m22 m23 |  -  | n21 n22 n23 |
	//	  | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat3D MatMinus2( const MgMat3D& i_tm, const MgMat3D& i_tn);

	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスの引算
	//
	//	使用法
	//		MgMat3D1 -= MgMat3D2;
	//
	//	| m11 m12 m13 |    | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  = | m21 m22 m23 |  -  | n21 n22 n23 |
	//	| m31 m32 m33 |    | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat3D MatMinusEqual2( MgMat3D& io_tm, const MgMat3D& i_tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスのかけ算
	//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
	//
	//	使用法
	//		MgMat4D = MgMat3D1 * MgMat3D2;
	//
	//	| m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  X  | n21 n22 n23 |
	//	| m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat3D MatMult2( const MgMat3D& i_tm, const MgMat3D& i_tn);

	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスのかけ算
	//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
	//
	//	使用法
	//		MgMat3D2 *= MgMat3D1;
	//
	//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  =  | m21 m22 m23 |  X  | n21 n22 n23 |
	//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat3D MatMultEqual2( MgMat3D& io_tm, const MgMat3D& i_tn);

	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgPoint2Dpo = MgPoint2Dp * MgMat3Dtm;
	//
	//					   | m11 m12 m13 |
	//	| px  py  1  |  X  | m21 m22 m23 |
	//					   | m31 m32 m33 |     
	//
	static MgVect2D MatMultPt22( const MgVect2D& i_pt, const MgMat3D& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgPoint2Dp *= MgMat3Dm;
	//
	//										  | m11 m12 m13 |
	//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 m23 |
	//				   						  | m31 m32 m33 |
	//
	static MgVect2D MatMultEqualPt22( MgVect2D& io_pt, const MgMat3D& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D = MgULine2D*  MgMat3D;
	//
	//	| px  py  1  |     | m11 m12 m13 |
	//	| vx  vy  0  |  X  | m21 m22 m23 |
	//					   | m31 m32 m33 |
	//
	static MgULine2D MatMultULn22( const MgULine2D& i_uln, const MgMat3D& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D *= MgMat3D;
	//
	//	| px  py  1  |     | px  py  1  |     | m11 m12 m13 |
	//	| vx  vy  0  |  =  | vx  vy  1  |  X  | m21 m22 m23 |
	//			             				  | m31 m32 m33 |
	//
	static MgULine2D MatMultEqualULn22( MgULine2D& io_uln, const MgMat3D& i_tm);

	//===============( ２次元座標変換マトリックスで３次元座標処理 )==============
	//
	//===========================================================================
	//	処理内容
	//	    座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgVect3D2 = MgVect3D1 * MgMat3D1;
	//
	//						  | m11 m12 0 m13 |     
	//	| px  py  pz  1 |  X  | m21 m22 0 m23 |
	//						  |  0   0  1  0  |
	//						  | m31 m32 0 m33 |
	//
	static MgVect3D MatMultPt32( const MgVect3D& i_Pt, const MgMat3D& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgVect3D *= MgMat3D;
	//
	//						 						| m11 m12 0 m13 |
	//	| px  py  pz  1 |  =  | px  py  pz  1 |  X  | m21 m22 0 m23 |
	//			   									|  0   0  1  0  |
	//			   									| m31 m32 0 m33 |
	
	
	static MgVect3D MatMultEqualPt32( MgVect3D& io_Pt, const MgMat3D& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D = MgULine2D * MgMat3D;
	//
	//	| px  py  pz  1 |	  | m11 m12 0 m13 |
	//	| vx  vy  vz  1 |  X  | m21 m22 0 m23 |
	//						  |  0   0  1  0  |
	//			   			  | m31 m32 0 m33 |
	//
	static MgULine3D MultULn32( const MgULine3D& ULn1, const MgMat3D& m2);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D = MgULine2D * MgMat3D;
	//
	//	| px  py  pz  1 |	  | m11 m12 0 m13 |
	//	| vx  vy  vz  1 |  X  | m21 m22 0 m23 |
	//						  |  0   0  1  0  |
	//						  | m31 m32 0 m33 |
	//
	static MgULine3D MatMultULn32( const MgULine3D& i_ULn, const MgMat3D& i_tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスにより座標変換する
	//
	//	使用法
	//		MgULine2D *= MgMat3D;
	//
	//	| px  py  pz  1 |     | px  py  pz  1 |		| m11 m12 0 m13 |
	//	| vx  vy  vz  1 |  =  | vx  vy  vz  1 |  X  | m21 m22 0 m23 |
	//												|  0   0  1  0  |
	//				 				   				| m31 m32 0 m33 |
	//
	static MgULine3D MatMultEqualULn32( MgULine3D& io_ULn, const MgMat3D& i_tm);

	//===========================================================================
	//
	//	３Ｄ座標変換マトリックスの計算
	//
	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの加算
	//
	//	使用法
	//		MgMat4D_3 = MgMat4D_1 + MgMat4D_2;
	//
	//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat4D MatPlus3( const MgMat4D& i_Tm, const MgMat4D& i_Tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの加算
	//
	//	使用法
	//		MgMat4D += MgMat4D;
	//
	//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat4D MatPlusEqual3( MgMat4D& io_Tm, const MgMat4D& i_Tn);

	//===========================================================================
	//	処理内容
	//		負の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat4D_2 = - MgMat4D_1;
	//
	//	  | m11 m12 m13 m14 |
	//	- | m21 m22 m23 m24 |
	//	  | m31 m32 m33 m34 |
	//	  | m41 m42 m43 m44 |     
	//
	static MgMat4D MatSingleMinus3( const MgMat4D& i_Tm);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの引算
	//
	//	使用法
	//		MgMat4D_3 = MgMat4D_1 - MgMat4D_2;
	//
	//	  | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
	//	  | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	  | m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat4D MatMinus3( const MgMat4D& i_Tm, const MgMat4D& i_Tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスの引算
	//
	//	使用法
	//		MgMat4D -= MgMat4D;
	//
	//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat4D MatMinusEqual3( MgMat4D& io_Tm, const MgMat4D& i_Tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスのかけ算
	//
	//	使用法
	//		MgMat4D_3 = MgMat4D_1 * MgMat4D_2;
	//
	//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat4D MatMult3( const MgMat4D& i_Tm, const MgMat4D& i_Tn);

	//===========================================================================
	//	処理内容
	//		座標変換マトリックスのかけ算
	//
	//	使用法
	//		MgMat4D *= MgMat4D;
	//
	//	| m11 m12 m13 m14 |     | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat4D MatMultEqual3( MgMat4D& io_Tm, const MgMat4D& i_Tn);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより２次元データを座標変換する
	//
	//	使用法
	//		MgMat4D_2 = MgVect2D * MgMat4D_1;
	//
	//						    | m11 m12 m13 m14 |
	//	| px  py  0   1   |  X  | m21 m22 m23 m24 |
	//						    | m31 m32 m33 m34 |
	//						    | m41 m42 m43 m44 |
	//
	static MgVect2D MatMultPt23( const MgVect2D& i_Pt, const MgMat4D& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより２次元データを座標変換する
	//
	//	使用法
	//		MgVect2D *= MgMat4D;
	//
	//						     					    | m11 m12 m13 m14 |
	//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 m24 |
	//	           									    | m31 m32 m33 m34 |
	//	           									    | m41 m42 m43 m44 |
	//
	static MgVect2D MatMultEqualPt23( MgVect2D& io_Pt, const MgMat4D& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより３次元データを座標変換する
	//
	//	使用法
	//		MgVect3D_2 = MgVect3D_1 * MgMat4D;
	//
	//	 					    | m11 m12 m13 m14 |
	//	| px  py  pz  1   |  X  | m21 m22 m23 m24 |
	//						    | m31 m32 m33 m34 |
	//						    | m41 m42 m43 m44 |
	//
	static MgVect3D MatMultPt33( const MgVect3D& i_Pt, const MgMat4D& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより３次元データを座標変換する
	//
	//	使用法
	//		MgVect3D *= MgMat4D;
	//
	//							 					    | m11 m12 m13 m14 |
	//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
	//												    | m31 m32 m33 m34 |
	//												    | m41 m42 m43 m44 |
	//
	static MgVect3D MatMultEqualPt33( MgVect3D& io_Pt, const MgMat4D& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより３次元データを座標変換する
	//
	//	使用法
	//		MgULine3D_2 = MgULine3D_1 * MgMat4D;
	//
	//	| px  py  pz  1   |     | m11 m12 m13 m14 |
	//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
	//							| m31 m32 m33 m34 |
	//							| m41 m42 m43 m44 |
	//
	static MgULine3D MatMultULn33( const MgULine3D& i_ULn, const MgMat4D& i_Tm);

	//===========================================================================
	//	処理内容
	//		３次元座標変換マトリックスにより３次元データを座標変換する
	//
	//	使用法
	//		MgVect3D *= MgMat4D;
	//
	//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
	//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
	//													| m31 m32 m33 m34 |
	//													| m41 m42 m43 m44 |
	//
	static MgULine3D MatMultEqualULn33( MgULine3D& io_ULn, const MgMat4D& i_Tm);

	//======================( ２次元 )==============================
	//	処理内容
	//		原点を中心に回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3D = MgMat3DRotV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos  sin  0. |
	//	| -sin  cos  0. |
	//	|   0.   0.  1. |
	//
	static MgMat3D Mat3RotV( const MgVect2D& v);

	//======================( ２次元 )==============================
	//	処理内容
	//		原点を中心に逆回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat3D = MgMat3DRotRevV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	| cos -sin  0. |
	//	| sin  cos  0. |
	//	|  0.   0.  1. |
	//
	static MgMat3D Mat3RotRevV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＸＹ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat4D = MgMat4DRotZV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos  sin  0.  0. |
	//	| -sin  cos  0.  0. |
	//	|   0.   0.  1.  0. |
	//	|   0.   0.  0.  1. |
	//
	static MgMat4D Mat4RotZV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＸＹ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat4D = MgMat4DRotRevZV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos -sin  0.  0. |
	//	|  sin  cos  0.  0. |
	//	|   0.   0.  1.  0. |
	//	|   0.   0.  0.  1. |
	//
	static MgMat4D Mat4RotRevZV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＹＺ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat4D = MgMat4DRotTXV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  1.   0.   0.  0. |
	//	|  0.  cos  sin  0. |
	//	|  0. -sin  cos  0. |
	//	|  0.   0.   0.  1. |
	//
	static MgMat4D Mat4RotTXV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＹＺ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat4D = MgMat4DRotRevXV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  1.   0.   0.  0. |
	//	|  0.  cos -sin  0. |
	//	|  0.  sin  cos  0. |
	//	|  0.   0.   0.  1. |
	//
	static MgMat4D Mat4RotRevXV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat4D = MgMat4DRotYV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos   0. -sin   0. |
	//	|   0.   1.   0.   0. |
	//	|  sin   0.  cos   0. |
	//	|   0.   0.   0.   1. |
	//
	static MgMat4D Mat4RotYV( const MgVect2D& v);

	//======================( ３次元 )==============================
	//	処理内容
	//		ＺＸ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	//	使用法
	//		MgMat4D = MgMat4DRotRevYV(MgVect2D);
	//
	//		( MgVect2D: 単位ベクトル)
	//
	//	|  cos   0.  sin   0. |
	//	|   0.   1.   0.   0. |
	//	| -sin   0.  cos   0. |
	//	|   0.   0.   0.   1. |
	//
	static MgMat4D Mat4RotRevYV( const MgVect2D& v);

	//======================( ２次元 )==============================
	//	処理内容
	//	    Ｘ，Ｙ方向に拡大／縮小するマトリックスを作成
	//
	//	使用法
	//		Mgmat_2 = MgMat3DScl(MgVect2D_1);
	//
	//	| sx  0   0  |
	//	| 0   xy  0  |
	//	| 0   0   1  |
	//
	static MgMat3D Mat3Scl( const MgVect2D& vs);

	//======================( ３次元 )==============================
	//	処理内容
	//	    Ｘ，Ｙ，Ｚ方向に拡大／縮小するマトリックスを作成する
	//
	//	使用法
	//		Mgmat3_2 = MgMat4DScl(MgMat4D_1);
	//
	//	| sx  0   0   0  |
	//	| 0   xy  0   0  |
	//	| 0   0   sz  0  |
	//	| 0   0   0   1  |
	//
	static MgMat4D Mat4Scl( const MgVect3D& vs);

	//======================( ２次元 )==============================
	//	処理内容
	//		平行移動の変換マトリックスを作成する
	//
	//	使用法
	//		MgMat3D = MgMat3DMov(MgVect2D)
	//
	//	|  1.  0.  0. |
	//	|  0.  1.  0. |
	//	|  v.x v.y 1. |
	//
	static MgMat3D Mat3Mov( const MgVect2D& v);
	static MgMat3D Mat3Mov( const MgPoint2D& p)
						{ return Mat3Mov( (MgVect2D&)p);}

	//======================( ３次元 )==============================
	//	処理内容
	//		平行移動の変換マトリックスを作成する
	//
	//	使用法
	//		Mgmat3 = MgMat4DMov(MgVect3D)
	//
	//	| 1.  0.  0.  0. |
	//	| 0.  1.  0.  0. |
	//	| 0.  0.  1.  0. |
	//	| v.x v.y v.z 1. |
	//
	static MgMat4D Mat4Mov( const MgVect3D& v);
	static MgMat4D Mat4Mov( const MgPoint3D& p)
						{ return Mat4Mov( (MgVect3D&)p);}

	//======================( ２次元 )==============================
	//	処理内容
	//		変換マトリックスの逆変換マトリックスを作成
	//
	//	使用法
	//		MgMat3D = MgMat3DInv(MgMat3D);
	//
	//	| m11 m21 m31 |
	//	| m12 m22 m32 |			（入力行列は単位行列である事 ???）
	//	| m13 m23 m33 |
	//
	static MgMat3D Mat3Inv( const MgMat3D& i_tm);

	//======================( ３次元 )==============================
	//	処理内容
	//	    変換マトリックスの逆変換マトリックスを作成する
	//
	//	使用法
	//		Mgmat3_2 = MgMat4DInv(MgMat4D_1);
	//
	//	| m11 m21 m31 m41 |
	//	| m12 m22 m32 m42 |     （入力行列は単位行列である事 ???）
	//	| m13 m23 m33 m43 |
	//	| M14 m24 m34 m44 |
	//
	static MgMat4D Mat4Inv( const MgMat4D& i_Tm);

	//======================( ２次元 )==============================
	//		直線に対する鏡像座標変換マトリックスを作成
	//
	static MgMat3D Mat3Mirror(						// (  O) 鏡像変換行列
					const	MgMat3D&	i_tm, 		// (I  ) 変換行列
					const	MgULine2D&	i_uln		// (I  ) 鏡映の軸とする直線
			);

	//======================( ３次元 )==============================
	//		平面に対する鏡像座標変換マトリックスを作成
	//
	static MgMat4D Mat4Mirror(						// (  O) 鏡像変換行列
					const	MgMat4D&	i_Tm,		// (I  ) 変換行列
					const	MgPlane3D&	i_Pln		// (I  ) 鏡映の面とする平面
			);

	//======================( ２次元 )==============================
	//		中心点と回転角より座標変換マトリックスを作成
	//
	static MgMat3D Mat3Rot(							// (  O) 変換行列
					const	MgPoint2D&	i_ptc, 		// (I  ) 回転の中心となる点
					const	MREAL&		i_ar		// (I  ) 回転角 Degree
			);

	//======================( ３次元 )==============================
	//		回転軸となる直線と回転角より座標変換マトリックスを作成
	//
	static MgMat4D Mat4Rot(							// (  O) 変換行列
					const	MgULine3D&	i_ULn, 		// (I  ) 回転軸となる直線
					const	MREAL&		i_ar		// (I  ) 回転角(Degree)
			);

	//======================( ３次元 )==============================
	//		正投象座標変換マトリックスを計算する
	//
	static MgMat4D Mat4NProj(						// (  O) 正投象変換行列
					const	MgMat4D&	i_Tm,		// (I  ) 入力座標変換行列
					const	MgPlane3D&	i_Pln		// (I  ) 投象面
			);

	//======================( ３次元 )==============================
	//		斜投象座標変換マトリックスを計算する
	//
	static MgMat4D Mat4SProj(						// (  O) 斜投象変座標変換行列
					const	MgMat4D&	i_Tm,		// (I  ) 入力座標変換行列
					const	MgPlane3D&	i_Pln,		// (I  ) 投象面
					const	MgVect3D&	i_V			// (I  ) 投象方向を示す単位ベクトル
			);

	//===========================================================================
	//		３Ｄ平面上の点から２Ｄ座標への変換行列を計算する
	//
	// ---------------------( ３次元 )------------------------------
	//		底辺がX軸に平行になるようXY平面に投影するマトリックスを求める
	//
	//
	//	平面式	ax + by + cz + d = 0
	//
	//
	//	屋根
	//
	//	(|Pln.v.z|<0.6)
	//
	//		Z方向のベクトルを　Ｘ,　Zの順で回転すると次の式となり、
	//		入力平面に相当する												（２Ｄ→３Ｄ）
	//		逆に入力平面を　Ｚ， Ｘの順で回転するとZ方向のベクトルとなる	（３Ｄ→２Ｄ）、
	//
	//		sx: sin(x), cx: cos(x), sz: sin(z), cz: cos(z), (ab): sqrt(a*a+b*b)
	//
	//		cz = -b/(ab)	sz = a/(ab)
	//		cx = c			sx = (ab)
	//
	//	================================================
	//	３Ｄ→２Ｄ
	//
	//					|	1			0			0		|
	//	X軸逆回転	A	|	0			cx			-sx		|
	//					|	0			sx			cx		|
	//
	//					|	cz			-sz			0		|
	//	Z軸逆回転	B	|	sz			cz			0		|
	//					|	0			0			1		|
	//
	//	Z軸逆回転後にX軸逆回転する
	//					|	cz			-cxsz		sxsz	|
	//		A x B	=	|	sz			cxcz		-sxcz	|
	//					|	0			sx			cx		|
	//
	//					|	-b/(ab)		-ac/(ab)	a		|
	//					|	a/(ab)		-bc/(ab)	b		|
	//					|	0			(ab)		c		|
	//
	//	================================================
	//	２Ｄ→３Ｄ
	//
	//	Z軸逆回転後(2)に逆移動(1)し次の回転を行う
	//
	//					|	cz			sz			0		|
	//	Z軸回転		A	|	-sz			cz			0		|
	//					|	0			0			1		|
	//
	//					|	1			0			0		|
	//	X軸回転		B	|	0			cx			sx		|
	//					|	0			-sx			cx		|
	//
	//	X軸回転後にＺ軸回転する
	//					|	cz			sz			0		|
	//		A x B		|	-szcx		czcx		sx		|
	//					|	szsx		-czsx		cx		|
	//
	//					|	-b/(ab)		a/(ab)		0		|
	//					|	-ac/(ab)	-bc/(ab)	(ab)	|
	//					|	a			b			c		|
	//
	//	================================================
	//
	//	|pln.v.y|<0.6	
	//
	//	X軸回転				-sx		cx
	//	Y軸回転		sy･cx	-sx		cy･cx
	//				a		b		c
	//
	//	================================================
	//	３Ｄ→２Ｄ
	//
	//					|	1			0			0			|
	//	Ｘ軸逆回転	B	|	0			cx			-sx			|
	//					|	0			sx			cx			|
	//
	//					|	cy			0			sy			|
	//	Ｙ軸逆回転	A	|	0			1			0			|
	//					|	-sy			0			cy			|
	//
	//	Ｙ軸逆回転後にX軸逆回転する
	//					|	cy			sysx		sycx		|
	//		A x B		|	0			cx			-sx			|
	//					|	-sy			cysx		cycx		|
	//
	//					|	c/(ca)		-ab/(ca)	a			|
	//		-			|	0			(ca)		b			|
	//					|	-a/(ca)		-bc/(ca)	c			|
	//
	//	================================================
	//
	//	２Ｄ→３Ｄ
	//					
	//	Z軸逆回転後に逆移動する
	//
	//					|	cy			0			-sy			|
	//	Ｙ軸回転	A	|	0			1			0			|
	//					|	sy			0			cy			|
	//
	//					|	1			0			0			|
	//	X軸回転		B	|	0			cx			sx			|
	//					|	0			-sx			cx			|
	//
	//	X軸回転後にY軸回転する
	//					|	cy			0			-sy			|
	//			A x B	|	sxsy		cx			sxcy		|
	//					|	cxsy		-sx			cxcy		|
	//
	//					|	c/(ca)		0			-a/(ca)		|
	//					|	-ab/(ca)	(ca)		-bc/(ca)	|
	//					|	a			b			c			|
	
	static void Mat4PlntoXY(
					const	MgPlane3D&	i_Pln,		// (I  ) 変換対象平面
					const	MgPoint3D&	i_PtOrg,	// (I  ) 原点座標			
							MgMat4D*	o_MatXY,	// (  O) Pln to XY平面 ３Ｄマトリックス
							MgMat4D*	o_MatPln	// (  O) XY平面 to Pln ３Ｄマトリックス
					);
	
	//===================(３次元 → ２次元)=========================
	//		３Ｄ座標を２Ｄ座標へ変換する
	//
	static void Point3Dto2D(
					const	MgPoint3D&	i_P,		// (I  ) ３Ｄ座標
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
							MgPoint2D*	o_P			// (  O) ２Ｄ座標
					);

	//===================(３次元 → ２次元)=========================
	//		３Ｄ線分を２Ｄ線分へ座標変換する
	//
	static inline void Line3Dto2D(
					const MgLine3D&		i_Lni,		// (I  ) ３Ｄ線分
					const MgMat4D&		i_Mat,		// (I  ) 座標変換マトリックス
						  MgLine2D*		o_plno		// (  O) ２Ｄ線分
					)
	{
		Point3Dto2D( i_Lni.p[0], i_Mat, &o_plno->p[0]); 
		Point3Dto2D( i_Lni.p[1], i_Mat, &o_plno->p[1]);
	}

	//===================(３次元 → ２次元)=========================
	//		３Ｄ直線を２Ｄ直線へ座標変換する
	//
	static void ULine3Dto2D(
					const	MgULine3D&	i_ULn,		// (I  ) ３Ｄ直線
					const	MgMat4D&	i_Mt,		// (I  ) 座標変換マトリックス
						 	MgULine2D*	o_puln		// (  O) ２Ｄ直線
					);

	//===================(３次元 → ２次元)=========================
	//		３Ｄ座標を２Ｄ座標へ変換する
	//
	static MgPoint2D Point3Dto2D2(					// (  O) ２Ｄ座標
					const	MgPoint3D&	i_P,		// (I  ) ３Ｄ座標
					const	MgMat4D&	i_Tm		// (I  ) 座標変換マトリックス
					);

	//===================(３次元 → ２次元)=========================
	//		３Ｄ線分を２Ｄ線分へ座標変換する
	//
	static inline MgLine2D Line3Dto2D2(				// (  O) ２Ｄ線分
					const MgLine3D&		i_Lni,		// (I  ) ３Ｄ線分
					const MgMat4D&		i_Mat		// (I  ) 座標変換マトリックス
					)
	{
		return MgLine2D( 
					  Point3Dto2D2( i_Lni.p[0], i_Mat), 
					  Point3Dto2D2( i_Lni.p[1], i_Mat));
	}  

	//===================(３次元 → ２次元)=========================
	//		３Ｄ直線を２Ｄ直線へ座標変換する
	//
	static MgULine2D ULine3Dto2D2(					// (  O) ２Ｄ直線
					const	MgULine3D&	i_ULn,		// (I  ) ３Ｄ直線
					const	MgMat4D&	i_Tm		// (I  ) 座標変換マトリックス
					);

	//===================(３次元 → ２次元)=========================
	//		３Ｄ座標群を２Ｄ座標群へ変換する
	//
	static void	GPoint3Dto2D(
					const	MgGPoint3D&	i_GP,		// (I  ) ３Ｄ座標群
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
							MgGPoint2D*	o_pGP		// (  O) ２Ｄ座標群
					);
	
	//===================(３次元 → ２次元)=========================
	//		３Ｄ座標群（ポリライン）を２Ｄ座標群へ変換する
	//
	static void	Polyg3Dto2D(
					const	MgPolyg3D&	i_Pg,		// (I  ) ３Ｄ座標群
					const	MgMat4D&	i_iTm,		// (I  ) 座標変換マトリックス
							MgPolyg2D*	o_pPg		// (  O) ２Ｄ座標群
					);
	
	//===================(３次元 → ２次元)=========================
	//		３Ｄ線分群を２Ｄ線分群へ変換する
	//
	static void	GLine3Dto2D(
					const	MgGLine3D&	i_GLn,		// (I  ) ３Ｄ線分群
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
							MgGLine2D*	o_pgln		// (  O) ２Ｄ線分群
					);
	
	//===================(３次元 → ２次元)=========================
	//		３Ｄ多角形群（ポリライン群）を２Ｄ多角形群へ変換する
	//
	static void GPolyg3Dto2D(
					const	MgGPolyg3D&	i_GPg,		// (I  ) ３Ｄ多角形群
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
						 	MgGPolyg2D*	o_pgpg		// (  O) ２Ｄ多角形群
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ座標を３Ｄ座標へ変換する
	//
	static void	Point2Dto3D(
					const	MgPoint2D&	i_pt,		// (I  ) ２Ｄ座標
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
							MgPoint3D*	o_pPt		// (  O) ３Ｄ座標
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ線分を３Ｄ線分へ座標変換する
	//
	static inline void Line2Dto3D(
					const MgLine2D&		i_lni,		// (I  ) ２Ｄ線分
					const MgMat4D&		i_Mat,		// (I  ) 座標変換マトリックス
						  MgLine3D*		o_pLno		// (  O) ３Ｄ線分
					)
	{
		Point2Dto3D( i_lni.p[0], i_Mat, &o_pLno->p[0]); 
		Point2Dto3D( i_lni.p[1], i_Mat, &o_pLno->p[1]);
	}  


	//===================(２次元 → ３次元)=========================
	//		２Ｄ直線を３Ｄ直線へ座標変換する
	//
	static void ULine2Dto3D(
					const	MgULine2D&	i_uln,		// (I  ) ２Ｄ直線
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
						 	MgULine3D*	o_pULn		// (  O) ３Ｄ直線
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ座標を３Ｄ座標へ変換する
	//
	static MgPoint3D Point2Dto3D3(					// (  O) ３Ｄ座標
					const	MgPoint2D&	i_Pt,		// (I  ) ２Ｄ座標
					const	MgMat4D&	i_Tm		// (I  ) 座標変換マトリックス
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ線分を３Ｄ線分へ座標変換する
	//
	static MgLine3D Line2Dto3D3(					// (  O) ３Ｄ線分
					const MgLine2D&		i_lni,		// (I  ) ２Ｄ線分
					const MgMat4D&		i_Mat		// (I  ) 座標変換マトリックス
					)
	{
		return MgLine3D(
					  Point2Dto3D3( i_lni.p[0], i_Mat), 
					  Point2Dto3D3( i_lni.p[1], i_Mat));
	}  

	//===================(２次元 → ３次元)=========================
	//		２Ｄ直線を３Ｄ直線へ座標変換する
	//
	static MgULine3D ULine2Dto3D3(					// (  O) ３Ｄ直線
					const	MgULine2D&	i_uln,		// (I  ) ２Ｄ直線
					const	MgMat4D&	i_Tm		// (I  ) 座標変換マトリックス
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ座標群を３Ｄ座標群へ変換する
	//
	static void	GPoint2Dto3D(
					const	MgGPoint2D&	i_GPt,		// (I  ) ２Ｄ座標群
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
							MgGPoint3D*	o_pGPt		// (  O) ３Ｄ座標群
					);
	
	//===================(２次元 → ３次元)=========================
	//		２Ｄ座標群（ポリライン）を３Ｄ座標群へ変換する
	//
	static void	Polyg2Dto3D(
					const	MgPolyg2D&	i_Pg,		// (I  ) ２Ｄ座標群
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
							MgPolyg3D*	o_pPg		// (  O) ３Ｄ座標群
					);
	
	//===================(２次元 → ３次元)=========================
	//		２Ｄ直線群を３Ｄ直線群へ変換する
	//
	static void	GLine2Dto3D(
					const	MgGLine2D&	i_gln,		// (I  ) ２Ｄ直線群
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
							MgGLine3D*	o_pGLn		// (  O) ３Ｄ直線群
					);

	//===================(２次元 → ３次元)=========================
	//		２Ｄ多角形群（ポリライン群）を３Ｄ多角形群へ変換する
	//
	static void GPolyg2Dto3D(
					const	MgGPolyg2D&	i_GPg,		// (I  ) ２Ｄ多角形群
					const	MgMat4D&	i_Tm,		// (I  ) 座標変換マトリックス
						 	MgGPolyg3D*	o_pGPg		// (  O) ３Ｄ多角形群
					);
	//
	//======================( ２次元，３次元 )==============================
	//		図形処理
	//
	// ---------------------( ２次元 )------------------------------
	//		指定線分より始まり線分群の線分を結合して最小の多角形を作成する
	//
	static bool	MakeGPg2FromLn2InGLn2(				// (  O) ステイタス　true: 正常作成　false: 作成不可
					const	MgLine2D&	i_Ln1,		// (I  ) 指定線分
							MgGLine2D*	io_GLn2,	// (I O) 結合する線分群
							MINT*		io_pnHk,	// (I O) 結合する線分の中の正しい方向を持つ線分数（先頭より幾つかを表す）
							MgPolyg2D*	o_pPg3		// (  O) 領域
					);
	
	// ---------------------( ２次元 )------------------------------
	//		多角形を直線で切り、直線の指定側の領域を得る			<多角形が穴の場合の考慮不足?>
	//
	static MINT DividePgULn2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_LEFT			(010): 左側の領域
													//			MC_RIGHT		(040): 右側の領域
					const	MgPolyg2D&	i_Pg1,		// (I  ) 多角形
					const	MgULine2D&	i_ULn2,		// (I  ) 直線
							MgGPolyg2D*	o_pGPg3		// (  O) 穴付き多角形群
					);
	
	// ---------------------( ２次元 )------------------------------
	//		穴付き多角形を直線で切り、直線の指定側の領域を得る
	//
	static MINT DivideGPgULn2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_LEFT			(010): 左側の領域
													//			MC_RIGHT		(040): 右側の領域
					const	MgGPolyg2D&	i_GPg1,		// (I  ) 穴付き多角形
					const	MgULine2D&	i_ULn2,		// (I  ) 直線
							MgGPolyg2D*	o_pGPg3		// (  O) 穴付き多角形群
					);
	
	// ---------------------( ２次元 )------------------------------
	//		多角形1を多角形2で分割し、多角形2の指定側（内側または外側）の領域を得る
	//
	static MINT Divide2Pg2(							// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_OUT_BORDER	(004): 外側
													//									
					const	MgPolyg2D&	i_Pg1,		// (I  ) 多角形1
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形2
							MgGPolyg2D*	o_ppGPgo	// (  O) 穴付き多角形3
					);
	
	// ---------------------( ２次元 )------------------------------
	//		穴付き多角形を穴付き多角形で分割し、選択条件に合う領域を得る
	//
	static MINT Divide2GPg2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_OUT_BORDER	(004): 外側
					const	MgGPolyg2D&	i_GPg1,		// (I  ) 穴付き多角形1
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形2
							MgGPolyg2D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ３次元 )------------------------------
	//		多角形1を多角形2で分割し、多角形2の指定側（内側または外側）の領域を得る
	//
	static MINT Divide2Pg3(							// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_OUT_BORDER	(004): 外側
													//									
					const	MgPolyg3D&	i_Pg1,		// (I  ) 多角形1
					const	MgPolyg3D&	i_Pg2,		// (I  ) 多角形2
							MgGPolyg3D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ３次元 )------------------------------
	//		穴付き多角形を穴付き多角形で分割し、選択条件に合う領域を得る
	//
	static MINT Divide2GPg3(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_OUT_BORDER	(004): 外側
					const	MgGPolyg3D&	i_GPg1,		// (I  ) 穴付き多角形1
					const	MgGPolyg3D&	i_GPg2,		// (I  ) 穴付き多角形2
							MgGPolyg3D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ２次元 )------------------------------
	//		多角形と多角形の和、差、積の穴付き多角形を求める
	//
	static MINT Merge2PgtoGPg2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_OR			(1): 和
													//			MC_DIFF			(2): 差
													//			MC_AND			(4): 積
					const	MgPolyg2D&	i_Pg1,		// (I  ) 多角形1
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形2
							MgGPolyg2D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ２次元 )------------------------------
	//		多角形と穴付き多角形の和、差、積の穴付き多角形を求める
	//
	static MINT MergePgGPgtoGPg2(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_OR			(1): 和
													//			MC_DIFF			(2): 差
													//			MC_AND			(4): 積
					const	MgPolyg2D&	i_Pg1,		// (I  ) 多角形1
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形2
							MgGPolyg2D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ２次元 )------------------------------
	//		穴付き多角形と多角形の和、差、積の穴付き多角形を求める
	//
	static MINT MergeGPgPgtoGPg2(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_OR			(1): 和
													//			MC_DIFF			(2): 差
													//			MC_AND			(4): 積
					const	MgGPolyg2D&	i_GPg1,		// (I  ) 穴付き多角形1
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形2
							MgGPolyg2D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ２次元 )------------------------------
	//		穴付き多角形と穴付き多角形の和、差、積の穴付き多角形を求める
	//
	static MINT Merge2GPgtoGPg2(					// (  O) ステイタス
													//			MC_NINT			(x01): 交差なし
													//			MC_INT			(x02): 交差あり
													//			MC_MATCH		(x10): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_OR			(1): 和
													//			MC_DIFF			(2): 差
													//			MC_AND			(4): 積
					const	MgGPolyg2D&	i_GPg1,		// (I  ) 穴付き多角形1
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形2
							MgGPolyg2D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ３次元 )------------------------------
	//		多角形と多角形の和、差、積の穴付き多角形を求める
	//
	static MINT Merge2PgtoGPg3(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_OR			(1): 和
													//			MC_DIFF			(2): 差
													//			MC_AND			(4): 積
					const	MgPolyg3D&	i_Pg1,		// (I  ) 多角形1
					const	MgPolyg3D&	i_Pg2,		// (I  ) 多角形2
							MgGPolyg3D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ３次元 )------------------------------
	//		多角形と穴付き多角形の和、差、積の穴付き多角形を求める
	//
	static MINT MergePgGPgtoGPg3(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_OR			(1): 和
													//			MC_DIFF			(2): 差
													//			MC_AND			(4): 積
					const	MgPolyg3D&	i_Pg1,		// (I  ) 多角形1
					const	MgGPolyg3D&	i_GPg2,		// (I  ) 穴付き多角形2
							MgGPolyg3D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ３次元 )------------------------------
	//		穴付き多角形と多角形の和、差、積の穴付き多角形を求める
	//
	static MINT MergeGPgPgtoGPg3(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_OR			(1): 和
													//			MC_DIFF			(2): 差
													//			MC_AND			(4): 積
					const	MgGPolyg3D&	i_GPg1,		// (I  ) 穴付き多角形1
					const	MgPolyg3D&	i_Pg2,		// (I  ) 多角形2
							MgGPolyg3D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ３次元 )------------------------------
	//		穴付き多角形と穴付き多角形の和、差、積の穴付き多角形を求める
	//
	static MINT Merge2GPgtoGPg3(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_OR			(1): 和
													//			MC_DIFF			(2): 差
													//			MC_AND			(4): 積
					const	MgGPolyg3D&	i_GPg1,		// (I  ) 穴付き多角形1
					const	MgGPolyg3D&	i_GPg2,		// (I  ) 穴付き多角形2
							MgGPolyg3D*	o_pGPgo		// (  O) 穴付き多角形3
					);
	
	// ---------------------( ２次元 )------------------------------
	//		多角形の辺（線分）を他の多角形で分割し、指定した側の線分を残す
	//								線分が多角形の辺上にある場合は、
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) 選択条件が辺上逆方向の場合は、逆方向の時残す
	//				(3) その他の場合は捨てる
	//
	static MINT DivideAdd2Pg2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel1,		// (I  ) 選択条件1　多角形1の線分を残す条件
													//			MC_IN_BORDER	(001):	多角形2の領域の内側
													//			MC_ON_BORDER	(002):  多角形2の辺上
													//			MC_OUT_BORDER	(004):	多角形2の領域の外側
													//			MC_SAME_DIR		(0100):	辺上同一方向
													//			MC_REV_DIR		(0200):	辺上逆方向
					const	bool		i_fRev,		// (I  ) 反転フラグ	
													//		 true: 線分の方向を反転する
					const	MgPolyg2D&	i_Pg1,		// (I  ) 多角形1
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形2
							MgGLine2D*	io_pGLno,	// (I O) 直線群
							MgGPolyg2D*	io_pGPgo	// (I O) 穴付き多角形
					);
	
	// ---------------------( ２次元 )------------------------------
	//		多角形の辺（線分）を穴付き多角形で分割し、指定した側の線分を残す
	//								線分が多角形の辺上にある場合は、
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) 選択条件が辺上逆方向の場合は、逆方向の時残す
	//				(3) その他の場合は捨てる
	//
	
	static MINT DivideAddPgGPg2(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel1,		// (I  ) 選択条件1　多角形1の線分を残す条件
													//			MC_IN_BORDER	(001): 多角形2の領域の内側
													//			MC_ON_BORDER	(002): 多角形2の辺上
													//			MC_OUT_BORDER	(004): 多角形2の領域の外側
													//			MC_SAME_DIR		(0100):	辺上同一方向
													//			MC_REV_DIR		(0200):	辺上逆方向
					const	bool		i_fRev,		// (I  ) 反転フラグ	
													//		 true: 線分の方向を反転する
					const	MgPolyg2D&	i_Pg1,		// (I  ) 多角形1
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形2
							MgGLine2D*	io_pGLno,	// (I O) 直線群
							MgGPolyg2D*	io_pGPgo	// (I O) 穴付き多角形
					);
	
	// ---------------------( ２次元 )------------------------------
	//		GLn1の方向を考慮して接続し領域群を作成する
	//
	
	#define	MX_AREA_BY_PT	20						// １点の周りの最大領域数
	
	static void MakeGPg2InGLn2(
					const	MgGLine2D&	i_GLn1,		// (I  ) 正しい方向を持つ線分群
							MgGPolyg2D*	o_GPg3		// (  O) 領域群
					);
	
	// ---------------------( ２次元 )------------------------------
	//		GLn1の方向を考慮して直線分割線分GLn2を追加し領域群を作成する
	//
	static void MakeGPg2In2GLn2(
					const	MgGLine2D&	i_GLn1,		// (I  ) 正しい方向を持つ線分群
					const	MgGLine2D&	i_GLn2,		// (I  ) 不正確な方向の線分群
							MgGPolyg2D*	o_GPg3		// (  O) 領域群
					);
	
	// ---------------------( ２次元 )------------------------------
	//		指定線分より始まり線分群の線分を交点で分割後に結合して最小の多角形を作成する
	//
	static bool MakeGPg2FromLn2InGLn2(				// (  O) ステイタス　true: 正常作成　false: 作成不可
					const	MgLine2D&	i_Ln1,		// (I  ) 指定線分
					const	MgGLine2D&	i_GLn2,		// (I  ) 結合する線分群
							MgPolyg2D*	o_Pg3		// (  O) 領域
					);
	
//	// ---------------------( ２次元 )------------------------------
//	//		指定線分より始まり線分群の線分を結合して最小の多角形を作成する
//	//
//	static bool	MgMakeGPg2FromLn2InGLn2(			// (  O) ステイタス　true: 正常作成　false: 作成不可
//					const	MgLine2D&	i_Ln1,		// (I  ) 指定線分
//							MgGLine2D*	io_pGLn2,	// (I O) 結合する線分群
//							MINT*		io_pnHk,	// (I O) 結合する線分の中の正しい方向を持つ線分数（先頭より幾つかを表す）
//							MgPolyg2D*	o_pPg3		// (  O) 領域
//					);
	
	// ---------------------( ２次元 )------------------------------
	//		穴付き多角形を多角形に結合する
	//
	static void ConnectGPgtoPg2(					//
					const	MgGPolyg2D&	i_GpgI,		// (I  ) 穴付き多角形
							MgPolyg2D*	o_pgO		// (  O) 結合後の多角形
					);
	
	// ---------------------( ３次元 )------------------------------
	//		穴付き多角形を多角形に結合する
	//
	static void ConnectGPgtoPg3(					//
					const	MgGPolyg3D&	i_GPgI,		// (I  ) 穴付き多角形
					const	MgVect3D&	i_VuH,		// (I  ) 法線方向
							MgPolyg3D*	o_pPgO		// (  O) 結合後の多角形
					);

	
	//===========================================================================
	//		点　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//
	//		２点間の距離を求める。
	//
	static MREAL Dist2Pt2(							// (  O) 直線から点までの距離 >0:左側 <0:右側
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgPoint2D&	i_p2		// (I  ) 点2
					);

	//===========================================================================
	//		点　形状演算
	//
	// ---------------------( ３次元 )------------------------------
	//
	//		２点間の距離を求める。
	//
	static MREAL Dist2Pt3(							// (  O) ２点間の距離 >0:左側 <0:右側
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgPoint3D&	i_p2		// (I  ) 点2
					);
	
	//===========================================================================
	//		直線　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//
	//		直線から点までの正負方向付き距離を求める。
	//
	static MREAL DistPtULn2(						// (  O) 直線から点までの距離 >0:左側 <0:右側
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgULine2D&	i_ULn2		// (I  ) 直線2
					);
	
	//	------------------------
	//		線分から点までの正負方向付き距離を求める。	(直線と同様)
	
	//
	static MREAL DistPtLn2(							// (  O) 線分から点までの距離 >0:左側 <0:右側
													//	線分の長さが0の場合は点から線分の始点までの距離
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgLine2D&	i_Ln2		// (I  ) 線分2
					);
	
	// ---------------------( ３次元 )------------------------------
	//		直線から点までの距離を求める。
	//
	static MREAL DistPtULn3(						// (  O) 直線から点までの距離
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgULine3D&	i_ULn2		// (I  ) 直線2
					);

	//
	//		線分から点までの距離を求める。(直線と同様)
	//
	static MREAL DistPtLn3(							// (  O) 線分から点までの距離
													//	線分の長さが0の場合は点から線分の始点までの距離
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgLine3D&	i_Ln2		// (I  ) 線分2
					);
	
	// ---------------------( ３次元 )------------------------------
	//		直線から点までの正負方向付き距離を求める。
	//
	static MREAL DistPtULnV3(						// (  O) 直線から点までの距離 >0:左側 <0:右側
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
					const	MgVect3D&	i_vn		// (I  ) 点と直線に直交する単位ベクトル
					);

	//
	//		線分から点までの正負方向付き距離を求める。(直線と同様)
	//
	static MREAL DistPtLnV3(						// (  O) 線分から点までの距離 >0:左側 <0:右側
													//		 線分の長さが0の場合は点から線分の始点までの距離
													//		 線分の長さが0の場合は点から線分の始点までの距離
				const	MgPoint3D&	i_p1,			// (I  ) 点1
				const	MgLine3D&	i_Ln2,			// (I  ) 線分2
				const	MgVect3D&	i_vn			// (I  ) 点と直線に直交する単位ベクトル
				);
	
	// ---------------------( ３次元 )------------------------------
	//		平面から点までの正負方向付き距離を求める。
	//
	static MREAL DistPtPln3(						// (  O) 点から平面までの距離 >0:表側（平面の単位ベクトル方向側）<0:裏側
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgPlane3D&	i_Pln2		// (I  ) 平面2
					);

	// ---------------------( ２次元 )------------------------------
	//		線分を線分で分割する
	//		(線分１の端部での交差は交差無しとし分割無し)
	//
	static MINT Divide2Ln2(							// (  O) ステイタス
													//			MC_NINT			(0): 分割無し
													//			MC_INT			(1): 分割あり
					const	MgLine2D&	i_Ln1, 		// (I  ) 分割対象線分
					const	MgLine2D&	i_Ln2, 		// (I  ) 分割線分
							MgGLine2D*	o_pGLn3		// (  O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		線分を直線で分割する
	//		(線分１の端部での交差は交差無しとし分割無し)
	//
	static MINT DivideLnULn2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
					const	MgLine2D&	i_Ln1, 		// (I  ) 分割対象線分
					const	MgULine2D&	i_ULn2,		// (I  ) 分割直線
							MgGLine2D*	o_pGLn3		// (  O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		線分を直線で分割し直線の選択側の線分を分割後の線分群に追加する
	//		(線分の端部での交差は交差なしとする)
	//			選択条件に「辺上同一方向または辺上逆方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、
	//			次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) 選択条件が辺上逆方向の場合は、逆方向の時残す
	//				(3) その他の場合は捨てる
	//		//			(1) 選択条件が直線の左側|直線上の場合は、同一方向の時残し
	//		//			(2) 選択条件が直線の右側|直線上の場合は、逆方向の時残す
	//		//			(3) その他の場合は捨てる
	//
	// 		sels = MC_LEFT | MC_ON_BORDER | MC_SAME_DIR;
	
	//
	static MINT DivideAddLnULn2(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_LEFT			(010): 直線の左側
													//			MC_ON_LINE		(020): 直線上
													//			MC_RIGHT		(040): 直線の右側
													//			MC_SAME_DIR		(0100):	辺上同一方向
													//			MC_REV_DIR		(0200):	辺上逆方向
					const	MgLine2D&	i_Ln1, 		// (I  ) 分割対象線分
					const	MgULine2D&	i_ULn2,		// (I  ) 分割直線
							MgGLine2D*	o_pGLn3		// (I O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		線分を線分群との交点で分割する
	//		(線分の端部での交差は交差なしとする)
	//
	static MINT DivideLnGLn2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
					const	MgLine2D&	i_Ln1, 		// (I  ) 分割対象線分
					const	MgGLine2D&	i_GLn2,		// (I  ) 分割線分群
							MgGLine2D*	o_pGLn3		// (  O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		線分群を交点で分割し同一線分は除き一本にする（逆方向も除く）
	//		交差判定で２線分が重なる場合は端点で分割する
	//
	static MINT DivideGLn2(							// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
					const	MgGLine2D&	i_GLn1,		// (I  ) 線分群
							MgGLine2D*	o_pGLn2		// (  O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		直線を多角形で分割し、選択条件に合う線分群を取り出す
	//			選択条件に「辺上同一方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、
	//			次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) その他の場合は捨てる
	//
	static MINT DivideULnPg2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
													//			MC_SAME_DIR		(0100):	辺上同一方向
					const	MgULine2D&	i_ULn1,		// (I  ) 直線
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形
							MgGLine2D*	o_pGLn3		// (  O) 分割後の線分群
					);
	
	// ---------------------( ２次元 )------------------------------
	//		直線を多角形で分割し、選択条件に合う線分を分割後の線分群に追加する
	//			選択条件に「辺上同一方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、
	//			次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) その他の場合は捨てる
	//
	static MINT DivideAddULnPg2(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
													//			MC_SAME_DIR		(0100):	辺上同一方向
					const	MgULine2D&	i_ULn1,		// (I  ) 直線
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形
							MgGLine2D*	io_pGLn3	// (I O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		線分を多角形で分割し、選択条件に合う線分群を得る
	//			選択条件に「辺上同一方向または辺上逆方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、
	//			次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) 選択条件が辺上逆方向の場合は、逆方向の時残す
	//				(3) その他の場合は捨てる
	//
	static MINT DivideLnPg2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
													//			MC_OUT_BORDER	(004): 外側
													//			MC_FOR_POLYGON	(0100): 多角形作成用
					const	MgLine2D&	i_Ln1,		// (I  ) 線分
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形
							MgGLine2D*	o_pGLn3		// (  O) 分割後の線分群
					);
	
	// ---------------------( ２次元 )------------------------------
	//		線分を多角形で分割し、選択条件に合う線分を分割後の線分群に追加する
	//			選択条件に「辺上同一方向または辺上逆方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、
	//			次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) 選択条件が辺上逆方向の場合は、逆方向の時残す
	//				(3) その他の場合は捨てる
	//
	static MINT DivideAddLnPg2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
													//			MC_OUT_BORDER	(004): 外側
													//			MC_SAME_DIR		(0100):	辺上同一方向
													//			MC_REV_DIR		(0200):	辺上逆方向
					const	MgLine2D&	i_Ln1,		// (I  ) 線分
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形
							MgGLine2D*	o_pGLn3		// (I O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		直線を穴付き多角形で分割し、選択条件に合う線分群を得る
	//			選択条件に「辺上同一方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、
	//			次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) その他の場合は捨てる
	//
	static MINT DivideULnGPg2(						// (  O) ステイタス
													//			MC_NINT			(0): 選択条件に合う線分なし
													//			MC_INT			(1): 選択条件に合う線分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
													//			MC_SAME_DIR		(0100):	辺上同一方向
					const	MgULine2D&	i_ULn1,		// (I  ) 直線
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形
							MgGLine2D*	o_pGLn3		// (  O) 分割後の線分群
					);
	
	// ---------------------( ２次元 )------------------------------
	//		直線を穴付き多角形で分割し、選択条件に合う線分を分割後の線分群に追加する
	//			選択条件に「辺上同一方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) その他の場合は捨てる
	//
	static MINT DivideAddULnGPg2(					// (  O) ステイタス
													//			MC_NINT			(0): 選択条件に合う線分なし
													//			MC_INT			(1): 選択条件に合う線分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
													//			MC_SAME_DIR		(0100):	辺上同一方向
					const	MgULine2D&	i_ULn1,		// (I  ) 直線
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形
							MgGLine2D*	o_pGLn3		// (I O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		線分を穴付き多角形で分割し、選択条件に合う線分群を得る
	//			選択条件に「辺上同一方向または辺上逆方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、
	//			次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) 選択条件が辺上逆方向の場合は、逆方向の時残す
	//				(3) その他の場合は捨てる
	//
	static MINT DivideLnGPg2(						// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
													//			MC_OUT_BORDER	(004): 外側
													//			MC_SAME_DIR		(0100):	辺上同一方向
													//			MC_REV_DIR		(0200):	辺上逆方向
					const	MgLine2D&	i_Ln1,		// (I  ) 線分
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形
							MgGLine2D*	o_pGLn3		// (  O) 分割後の線分群
					);
	
	// ---------------------( ２次元 )------------------------------
	//		線分を穴付き多角形で分割し、選択条件に合う線分を分割後の線分群に追加する
	//			選択条件に「辺上同一方向または辺上逆方向」が設定されており、分割後の線分が穴付き多角形の辺上にある場合には、
	//			次のように選択する
	//				(1) 選択条件が辺上同一方向の場合は、同一方向の時残し
	//				(2) 選択条件が辺上逆方向の場合は、逆方向の時残す
	//				(3) その他の場合は捨てる
	//
	static MINT DivideAddLnGPg2(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
													//			MC_OUT_BORDER	(004): 外側
													//			MC_SAME_DIR		(0100):	辺上同一方向
													//			MC_REV_DIR		(0200):	辺上逆方向
					const	MgLine2D&	i_Ln1,		// (I  ) 線分
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形
							MgGLine2D*	io_pGLn3	// (I O) 分割後の線分群
					);

	// ---------------------( ２次元 )------------------------------
	//		重なっている線分を削除し一本にする (逆方向も含む)				<要効率UP?>
	//
	static void MergeGLn2(
							MgGLine2D*	io_pGln		// (I O) 線分群
					);
	
	//===========================================================================
	// ---------------------( ３次元 )------------------------------
	//		直線を多角形で分割し、選択条件に合う線分群を取り出す
	//
	static MINT DivideULnPg3(						// (  O) ステイタス
													//		 MC_NINT		(0): 交差なし
													//		 MC_INT			(1): 交差あり
							MINT		i_Sel,		// (I  ) 選択条件
													//		 MC_IN_BORDER	(001): 内側
													//		 MC_ON_BORDER	(002): 辺上
					const	MgULine3D&	i_ULn1,		// (I  ) 直線
					const	MgPolyg3D&	i_Pg2,		// (I  ) 多角形
							MgGLine3D*	o_pGLn3		// (  O) 分割後の線分群
					);

	//---------------------( ３次元 )------------------------------
	//		直線を多角形で分割し、分割条件に合う線分を分割後の線分群に追加する
	//
	static MINT DivideAddULnPg3(					// (  O) ステイタス
													//			MC_NINT			(0): 交差なし
													//			MC_INT			(1): 交差あり
													//			MC_MATCH		(4): 選択条件に合う部分あり
													//	例	 (STS == MC_NINT):				交差無しで選択条件に合う部分なし 
													//		 (STS == (MC_NINT | MC_MATCH)):	交差無しであるが選択条件に合う
													//		 (STS == (MC_INT | MC_MATCH)):	交差ありで選択条件に合う部分あり
							MINT		i_Sel,		// (I  ) 選択条件
													//			MC_IN_BORDER	(001): 内側
													//			MC_ON_BORDER	(002): 辺上
					const	MgULine3D&	i_ULn1,		// (I  ) 直線
					const	MgPolyg3D&	i_Pg2,		// (I  ) 多角形
							MgGLine3D*	io_pGLn3	// (I O) 分割後の線分群
					);

	//// ---------------------( ２次元 )------------------------------
	////	２つの線分間の角度の大小に従う数値CCを求める
	////	[p0からp1に向かう方向]から[p1からp2に向かう方向]への角度により
	////		0.: -0゜, 0.5: 90゜, 1.: 180゜, 1.5: -90゜, <2.: <360(-)゜
	////
	//static MREAL AngSSa3Pt2( 
	//				const	MgPoint2D&	i_p0,
	//				const	MgPoint2D&	i_p1,
	//				const	MgPoint2D&	i_p2
	//				)
	////
	//// ---------------------( ３次元 )------------------------------
	////	２つの線分間の角度の大小に従う数値CCを求める
	////	平面pln3上で[p0からp1に向かう方向]から[p1からp2に向かう方向]への角度により
	////		0.: -0゜, 0.5: 90゜, 1.: 180゜, 1.5: -90゜, <2.: <360(-)゜
	////
	//static MREAL AngSSa3Pt3( 
	//				const	MgPoint3D&	i_P0,
	//				const	MgPoint3D&	i_P1,
	//				const	MgPoint3D&	i_P2,
	//				const	MgPlane3D&	i_Pln3
	//				)
	////
	//// ---------------------( ２次元 )------------------------------
	////	２つの線分間の角度の大小に従う数値CCを求める
	////	[p0からp1に向かう方向]から[p1からp2に向かう方向]への角度により
	////		>-1.: >-180゜, -0.5: -90゜, 0.: -0゜, 0.5: 90゜, 1.: 180゜
	////
	//static MREAL AngSSb3Pt2( 
	//				const	MgPoint2D&	i_p0,
	//				const	MgPoint2D&	i_p1,
	//				const	MgPoint2D&	i_p2
	//				)
	////
	//// ---------------------( ３次元 )------------------------------
	////	２つの線分間の角度の大小に従う数値CCを求める
	////	平面pln3上で[p0からp1に向かう方向]から[p1からp2に向かう方向]への角度により
	////		>-1.: >-180゜, -0.5: -90゜, 0.: -0゜, 0.5: 90゜, 1.: 180゜
	////
	//static MREAL AngSSb3Pt3( 
	//				const	MgPoint3D&	i_P0,
	//				const	MgPoint3D&	i_P1,
	//				const	MgPoint3D&	i_P2,
	//				const	MgPlane3D&	i_Pln3
	//				)
	//
	// ---------------------( ２次元 )------------------------------
	//	選択３角形が分割可能か調べる
	//			 0: 面積が0
	//			 1: 分割可能
	//			-1: 三角形内に他の入隅点があり分割不可(３角形の辺上は対象外)
	//
	static MINT ChkDivTriPtPg2( 
							MgPoint2D*	i_p3,		// 選択３角形
					const	MgPolyg2D&	i_Pgw,		// 分割多角形
					const	MgGInt&		i_iGIrisumi	// 入隅点リスト
					);
	
	// ---------------------( ３次元 )------------------------------
	//	選択３角形が分割可能か調べる
	//			 0: 面積が0
	//			 1: 分割可能
	//			-1: 三角形上または内に他の入隅点があり分割不可(３角形の辺上は対象外)
	//
	static MINT ChkDivTriPtPg3( 
							MgPoint3D*	i_p3,		// 選択３角形
					const	MgPolyg3D&	i_Pgw,		// 分割多角形
					const	MgGInt&		i_iGIrisumi,// 入隅点リスト
					const	MgVect3D&	i_VuPg1		// 多角形の法線方向
					);
	
	// ---------------------( ２次元 )------------------------------
	//		多角形を３角形に分割する
	//
	static MINT DivideTriPg2(						// (  O) ステイタス
													//			MC_NINT			(0): 分割なし
													//			MC_INT			(1): 分割あり
					const	MgPolyg2D&	i_Pg1,		// (I  ) 多角形
							MgGPolyg2D*	o_pGPg2		// (  O) 分割後の３角形群
					);
	
	//
	// ---------------------( ３次元 )------------------------------
	//		多角形を３角形に分割する
	//
	static MINT DivideTriPg3(						// (  O) ステイタス
													//			MC_NINT			(0): 分割なし
													//			MC_INT			(1): 分割あり
					const	MgPolyg3D&	i_Pg1,		// (I  ) 多角形
					const	MgVect3D&	i_VuPg1,		// (I  ) 多角形の法線方向
							MgGPolyg3D*	o_pGPg2		// (  O) 分割後の３角形群
					);
	
	//===========================================================================
	//		直線と直線の交点　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//　２本の直線の交点を求める。
	//
	static MINT Intr2ULn2(							// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgULine2D&	i_ULn1,		// (I  ) 直線1
					const	MgULine2D&	i_ULn2,		// (I  ) 直線2
							MgPoint2D*	o_ppo		// (  O) ２次元交点
					);
	
	// ---------------------( ２次元 )------------------------------
	//　直線と線分の交点を求める。
	//　重なっている場合は、交差なし（平行）とみなす。
	//
	static MINT IntrULnLn2(							// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgULine2D&	i_ULn1,		// (I  ) 直線1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MgPoint2D*	o_ppo		// (  O) ２次元交点
					);
	
	// ---------------------( ２次元 )------------------------------
	//　線分と直線の交点を求める。
	//　重なっている場合は、交差なし（平行）とみなす。
	//
	static inline MINT IntrLnULn2(					// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgULine2D&	i_ULn2,		// (I  ) 直線2
							MgPoint2D*	o_ppo		// (  O) ２次元交点
					)
	{
		return IntrULnLn2( i_ULn2, i_Ln1, o_ppo);
	}
	
	// ---------------------( ２次元 )------------------------------
	//　線分と線分の交点を求める。
	//　２線分が重なっている場合は、交差なし（平行）とみなす。
	//  ２線分が重なりなく直線的に端部で接合している場合はその接合点を交点とみなす。
	static MINT Intr2Ln2(							// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//  MC_CONNECTION(4) 接続	 （平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MgPoint2D*	o_ppo		// (  O) ２次元交点
					);

	// ---------------------( ２次元 )------------------------------
	//	線分１と直線２との交点を求め、点群に追加する。
	//　重なっている場合は、交差なし（平行）とみなす。
	//
	static MINT IntrAddLnULn2(						// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgULine2D&	i_ULn2,		// (I  ) 直線2
							MgGPoint2D*	io_pGPt3	// (I O) 交点を追加する点群
													//		 追加交点数(0:交差なし、線分の端部で交差、または重なる
													//					1:交差あり（線分の端部での交差は含まず))
					);
	
	// ---------------------( ２次元 )------------------------------
	//	線分１と線分２との交点と重なり部分の端点を求め、点群に追加する。
	//  交点または重なり部分の端点が線分１の端点である場合は、その点を対象外とする。
	//
	static MINT IntrAdd2Ln2(						// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
													//  MC_REP	    (2)	交差あり（重なり）
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MgGPoint2D*	io_pGPt3	// (I O) 交点を追加する線分群
													// 		 追加交点数(0:交差無しまたは線分1が線分2の内側にある重なり(端部同士の重なり含む) |
													//					1:線分2と交差（線分2の端部での交差も含む）または一部重なり(片端重なり含む) |
													//					2:線分2が線分1の内側にある重なり(端部同士の重なりなし)) 
					);

	// ---------------------( ２次元 )------------------------------
	//	直線１と線分２との交点または重なり部分の端点を求め、点群に追加する。
	//
	static MINT IntrAddULnLn2(						// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
													//  MC_REP	    (2)	交差あり（重なり）
					const	MgULine2D&	i_ULn1,		// (I  ) 直線1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MgGPoint2D*	io_pGPt3	// (I O) 交点を追加する線分群
													// 		 追加交点数(0:交差無し |
													//					1:直線1と線分2が交差（線分2の端部での交差も含む）|
													//					2:直線1と線分2が重なる 
					);

	// ---------------------( ３次元 )------------------------------
	//	２本の直線の交点を求める。
	//
	static MINT Intr2ULn3(							// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_TWIST	(-2) 交差なし（ねじれ）
													//	MC_INT      (1)	交差あり
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
							MgPoint3D*	o_ppo			// (  O) ３次元交点
					);

	// ---------------------( ３次元 )------------------------------
	//　直線と線分の交点を求める。
	//
	static MINT IntrULnLn3(							// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_TWIST    (-2) 交差なし（ねじれ）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
							MgPoint3D*	o_ppo		// (  O) ３次元交点
					);
	
	// ---------------------( ３次元 )------------------------------
	//　線分と直線の交点を求める。
	//
	static inline MINT IntrLnULn3(					// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_TWIST    (-2) 交差なし（ねじれ）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
							MgPoint3D*	o_ppo		// (  O) ３次元交点
					)
	{
		return IntrULnLn3( i_ULn2, i_Ln1, o_ppo);
	}
	
	// ---------------------( ３次元 )------------------------------
	//　線分と線分の交点を求める。
	//　２線分が重なっている場合は、交差なし（平行）とみなす。
	//  ２線分が重なりなく直線的に端部で接合している場合はその接合点を交点とみなす。
	//
	static MINT Intr2Ln3(							// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//  MC_CONNECTION(4) 接続	 （平行）
													//	MC_TWIST    (-2) 交差なし（ねじれ）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
							MgPoint3D*	o_ppo		// (  O) ３次元交点
					);
	
	//===========================================================================
	//		平面と直線の交点　形状演算
	//
	// ---------------------( ３次元 )------------------------------
	//
	//	平面と直線の交点を求める。
	//
	static MINT IntrPlnULn3(						// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_INT      (1)	交差あり
					const	MgPlane3D&	i_Pln1,		// (I  ) 平面1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
							MgPoint3D*	o_ppo		// (  O) ３次元交点(点の標準形式)
					);

	// ---------------------( ３次元 )------------------------------
	//	平面と線分の交点を求める。
	//
	static MINT IntrPlnLn3(							// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgPlane3D&	i_Pln1,		// (I  ) 平面1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
							MgPoint3D*	o_ppo		// (  O) ３次元交点(点の標準形式)
					);
	
	// ---------------------( ３次元 )------------------------------
	//	直線と平面の交点を求める。
	//
	static inline MINT IntrULnPln3(					// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_INT      (1)	交差あり
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgPlane3D&	i_Pln2,		// (I  ) 平面2
							MgPoint3D*	o_ppo		// (  O) ３次元交点(点の標準形式)
					)
	{
		return IntrPlnULn3( i_Pln2, i_ULn1, o_ppo);
	}
	
	// ---------------------( ３次元 )------------------------------
	//	線分と平面の交点を求める。
	//
	static inline MINT IntrLnPln3(					// (  O) ステイタス
													//	MC_PARALLEL (-1) 交差なし（平行）
													//	MC_NINT	    (0)	交差なし
													//	MC_INT      (1)	交差あり
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgPlane3D&	i_Pln2,		// (I  ) 平面2
							MgPoint3D*	o_ppo		// (  O) ３次元交点(点の標準形式)
					)
	{
		return IntrPlnLn3( i_Pln2, i_Ln1, o_ppo);
	}
	
	//===========================================================================
	//		平面と平面の交線　形状演算
	//
	// ---------------------( ３次元 )------------------------------
	//
	//	平面と平面の交線を求める。
	//
	static MINT Intr2Pln3(							// (  O) ステイタス
													//	MC_PARALLEL (-1)	交差なし（平行）
													//	MC_INT		(1)		交差あり
					const	MgPlane3D&	i_Pln1,		// (I  ) 平面1
					const	MgPlane3D&	i_Pln2,		// (I  ) 平面2
							MgULine3D*	o_pULn3		// (  O) 直線3
					);


	//===========================================================================
	//		形状演算
	//
	//	-------------------------２ＤＬＩＮＥ・ＰＯＩＮＴ----------------------
	//
	// ---------------------( ２次元 )------------------------------
	//		点から直線への垂線の足位置を求める
	static inline void PerpULnPt2(
					const	MgULine2D&	i_ULn1,		// (I  ) 直線1
					const	MgPoint2D&	i_p2,		// (I  ) 点2
							MgPoint2D*	o_ppo		// (  O) 点から直線への垂線の足
					)
	{
		MREAL		pa1;							//	直線1の始点から垂線の足までの距離
	//
		pa1 = ( i_p2 - i_ULn1.p) * i_ULn1.v;				//	cosΘv12v2
		*o_ppo = i_ULn1.p + i_ULn1.v * pa1;
	}
	
	// ---------------------( ２次元 )------------------------------
	//		点から線分への垂線の足位置を求める
	static inline MINT PerpLnPt2(					// (  O) ステイタス(=MC_ON_LINE	:線分上,
													//					=0			:線分範囲外)
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgPoint2D&	i_p2,		// (I  ) 点2
							MgPoint2D*	o_ppo		// (  O) 点から直線への垂線の足
					)
	{
		MINT		ist;
		MgVect2D	vd1, vd2;
		MREAL		ss, se;
	
		vd1 = i_Ln1.p[1] - i_Ln1.p[0];
		vd2 = RotL90(vd1);
	
		SVal( i_Ln1.p[0], i_Ln1.p[1], i_p2, vd2, &ss, &se);
	
		*o_ppo = i_Ln1.p[0] + (vd1 * (ss / (ss - se)));					//	交点
	
		if (ss * se < 0 ||											//	線分上
			*o_ppo == i_Ln1.p[0] || *o_ppo == i_Ln1.p[1]) ist = MC_ON_LINE;
		else ist =  0;												//	線分の外
		return ist;
	}
	
	// ---------------------( ２次元 )------------------------------
	//		点から直線への垂線の足位置を求める
	static inline void	MgPerpPtULn2(				// (  O) ステイタス
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgULine2D&	i_ULn2,		// (I  ) 直線2
							MgPoint2D*	o_ppo		// (  O) ２次元交点(点の標準形式)
			)
	{
		PerpULnPt2( i_ULn2, i_p1, o_ppo);
	}
	
	// ---------------------( ２次元 )------------------------------
	//		点から線分への垂線の足位置を求める
	static inline MINT PerpPtLn2(					// (  O) ステイタス(=MC_ON_LINE	:線分上,
													//					=0			:線分範囲外)
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MgPoint2D*	o_ppo		// (  O) ２次元交点(点の標準形式)
			)
	{
		return PerpLnPt2( i_Ln2, i_p1, o_ppo);
	}
	
	// ---------------------( ３次元 )------------------------------
	//		点から直線への垂線の足位置を求める
	static inline void PerpULnPt3(
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgPoint3D&	i_p2,		// (I  ) 点2
							MgPoint3D*	o_ppo		// (  O) 点から直線への垂線の足
					)
	{
		MREAL	pa1;								//	直線1の始点から垂線の足までの距離
	//
		pa1 = ( i_p2 - i_ULn1.p) * i_ULn1.v;					//	cosΘv12v2
		*o_ppo = i_ULn1.p + i_ULn1.v * pa1;
	}
	
	// ---------------------( ３次元 )------------------------------
	//		点から線分への垂線の足位置を求める
	static inline MINT	PerpLnPt3(					// (  O) ステイタス(=MC_ON_LINE	:線分上,
													//					=0			:線分範囲外)
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgPoint3D&	i_p2,		// (I  ) 点2
							MgPoint3D*	o_ppo		// (  O) ３次元交点(点の標準形式)
					)
	{
		MINT		ist;
		MgVect3D	vd1, vd2;
		MREAL		ss, se;
		MREAL		d;
	
		vd1 = i_Ln1.p[1] - i_Ln1.p[0];
	
		d  = i_p2 * vd1;
		ss = ( i_Ln1.p[0] * vd1) - d;
		se = ( i_Ln1.p[1] * vd1) - d;
	
		*o_ppo = i_Ln1.p[0] + (vd1 * (ss / (ss - se)));				//	交点
	
		if (ss * se < 0 ||											//	線分上
			*o_ppo == i_Ln1.p[0] || *o_ppo == i_Ln1.p[1])
			ist = MC_ON_LINE;
		else ist = 0;												//	線分の外
	
		return ist;
	}

	// ---------------------( ３次元 )------------------------------
	//		点から線分への垂線の足位置を求める
	static inline MINT	MgPerpPtLn3(				// (  O) ステイタス(=MC_ON_LINE	:線分上,
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgLine3D&	i_Ln2,		// (I  ) 直線2
							MgPoint3D*	o_ppo		// (  O) ３次元交点(点の標準形式)
					)
	{
		return PerpLnPt3( i_Ln2, i_p1, o_ppo);
	}
	
	// ---------------------( ３次元 )------------------------------
	//		点から直線への垂線の足位置を求める
	static inline void	MgPerpPtULn3(
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgULine3D&	i_ULn2,		// (I  ) 線分2
							MgPoint3D*	o_ppo		// (  O) ３次元交点(点の標準形式)
					)
	{
		PerpULnPt3( i_ULn2, i_p1, o_ppo);
	}
	
	//	-------------------------３Ｄ面・ＰＯＩＮＴ----------------------
	//
	// ---------------------( ３次元 )------------------------------
	//		点から面への垂線の足位置を求める
	//
	static inline void PerpPlnPt3(
					const	MgPlane3D&	i_Pln1,		// (I  ) 面1
					const	MgPoint3D&	i_p2,		// (I  ) 点2
							MgPoint3D*	o_ppo		// (  O) 点から直線への垂線の足
					)
	{
		MREAL	pa1;								//	点2から垂線の足までの距離
	//
		pa1 = ( i_p2 * i_Pln1.v) + i_Pln1.d;
		*o_ppo = i_p2 - i_Pln1.v * pa1;
	}
	
	// ---------------------( ３次元 )------------------------------
	//		点から面への垂線の足位置を求める
	//
	static inline void PerpPtPln3(
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgPlane3D&	i_Pln2,		// (I  ) 面2
							MgPoint3D*	o_ppo		// (  O) ３次元交点(点の標準形式)
					)
	{
		PerpPlnPt3( i_Pln2, i_p1, o_ppo);
	}

	//===========================================================================
	//		点の移動　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//
	static inline void MovePt2InDirOfVt2(			//
					const	MgPoint2D&	i_p1,		//  (I  ) 移動点1
					const	MgVect2D&	i_v2,		//	(I  ) 移動方向を示すベクトル
							MREAL		i_dl,		//	(I  ) 移動距離
							MgPoint2D*	o_pp3,		//	(  O) 移動された点3
							MREAL i_Tol = g_gTol.D	//	(I  ) 許容誤差
					)
	{
		*o_pp3 = i_p1 + i_dl * UnitizeV2( i_v2, i_Tol);
	}

	//	------------------------
	static inline void MovePt2AlongULn2(			//
					const	MgPoint2D&	i_p1,		//  (I  ) 移動点1
					const	MgULine2D&	i_ULn2,		//	(I  ) 移動方向を示す直線2
							MREAL		i_dl,		//	(I  ) 移動距離
							MgPoint2D*	o_pp3		//	(  O) 移動された点3
					)
	{
		*o_pp3 = i_p1 + i_dl * i_ULn2.v;
	}

	//	------------------------
	static inline void MovePt2AlongLn2(				//
					const	MgPoint2D&	i_p1,		//  (I  ) 移動点1
					const	MgLine2D&	i_Ln2,		//	(I  ) 移動方向を示す線分2
							MREAL		i_dl,		//	(I  ) 移動距離
							MgPoint2D*	o_pp3,		//	(  O) 移動された点3
							MREAL i_Tol = g_gTol.D	//	(I  ) 許容誤差
					)
	{
		MgVect2D	vd, vn;
	
		vd = i_Ln2.p[1] - i_Ln2.p[0];
		vn = UnitizeV2( vd, i_Tol);
		*o_pp3 = i_p1 + i_dl * vn;
	}

	//
	// ---------------------( ３次元 )------------------------------
	//
	static inline void MovePt3InDirOfVt3(			//
					const	MgPoint3D&	i_p1,		//  (I  ) 移動点1
					const	MgVect3D&	i_v2,		//	(I  ) 移動方向を示すベクトル
							MREAL		i_dl,		//	(I  ) 移動距離
							MgPoint3D	*o_pp3,		//	(  O) 移動された点3
							MREAL i_Tol = g_gTol.D	//	(I  ) 許容誤差
					)
	{
		*o_pp3 = i_p1 + i_dl * UnitizeV3( i_v2, i_Tol);
	}

	//	------------------------
	static inline void MovePt3AlongULn3(			//	(  O) ステイタス
					const	MgPoint3D&	i_p1,		//  (I  ) 移動点1
					const	MgULine3D&	i_ULn2,		//	(I  ) 移動方向を示す直線2
							MREAL		i_dl,		//	(I  ) 移動距離
							MgPoint3D*	o_pp3		//	(  O) 移動された点3
					)
	{
		*o_pp3 = i_p1 + i_dl * i_ULn2.v;
	}

	//	------------------------
	static inline void MovePt3AlongLn3(				//	(  O) ステイタス
					const	MgPoint3D&	i_p1,		//  (I  ) 移動点1
					const	MgLine3D&	i_Ln2,		//	(I  ) 移動方向を示す線分2
							MREAL		i_dl,		//	(I  ) 移動距離
							MgPoint3D*	o_pp3,		//	(  O) 移動された点3
							MREAL i_Tol = g_gTol.D	//	(I  ) 許容誤差
					)
	{
		MgVect3D	vd, vn;
	
		vd = i_Ln2.p[1] - i_Ln2.p[0];
		vn = UnitizeV3(vd, i_Tol);
		*o_pp3 = i_p1 + i_dl * vn;
	}

	//===========================================================================
	//		直線のオフセット　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//
	//	直線をオフセットする。
	//
	static inline void OffsetULn2(					//	(  O) ステイタス (=1)
					const	MgULine2D&	i_ULn1,		//	(I  ) 直線1
							MREAL		i_dl,		//	(I  ) オフセット量
							MgULine2D* 	o_pULn2		//	(  O) オフセットされた直線2
					)
	{
	
		o_pULn2->p = i_ULn1.p + i_dl * RotL90( i_ULn1.v);
		o_pULn2->v = i_ULn1.v;
	}

	//	------------------------
	static inline void OffsetLn2(					//	(  O) ステイタス
					const	MgLine2D&	i_Ln1,		//	(I  ) 線分1
							MREAL		i_dl,		//	(I  ) オフセット量
							MgLine2D*	o_pLn2,		//	(  O) オフセットされた線分2
							MREAL i_Tol = g_gTol.D	//	(I  ) 許容誤差
					)
	{
		MgVect2D	vd, vn;
	
		vd = i_Ln1.p[1] - i_Ln1.p[0];
		vn = UnitizeV2( vd, i_Tol);
		o_pLn2->p[0] = i_Ln1.p[0] + i_dl * RotL90(vn);
		o_pLn2->p[1] = o_pLn2->p[0] + vd;
	}

	//
	// ---------------------( ３次元 )------------------------------
	//
	static inline void OffsetULn3(					//	(  O) ステイタス
					const	MgULine3D&	i_ULn1,		//	(I  ) 直線1
					const	MgPlane3D&	i_Pln2,		//	(I  ) 直線1が乗る平面2
							MREAL		i_dl,		//	(I  ) オフセット量
							MgULine3D*	o_pULn3		//	(  O) オフセットされた直線3
					)
	{
		o_pULn3->p = i_ULn1.p + i_dl * ( i_Pln2.v ^ i_ULn1.v);
		o_pULn3->v = i_ULn1.v;
	}

	//	------------------------
	static inline void OffsetLn3(					//	(  O) ステイタス
					const	MgLine3D&	i_Ln1,		//	(I  ) 線分1
					const	MgPlane3D&	i_Pln2,		//	(I  ) 線分1が乗る平面2
							MREAL		i_dl,		//	(I  ) オフセット量
							MgLine3D*	o_pLn3,		//	(  O) オフセットされた線分3
							MREAL i_Tol = g_gTol.D	//	(I  ) 許容誤差
					)
	{
		MgVect3D	vd, vn;
		//
		vd = i_Ln1.p[1] - i_Ln1.p[0];
		vn = UnitizeV3( vd, i_Tol);
		MgVect3D vv = vn ^ i_Pln2.v;
		o_pLn3->p[0] = i_Ln1.p[0] + i_dl * ( i_Pln2.v ^ vn);
		o_pLn3->p[1] = o_pLn3->p[0] + vd;
	}
	
	//===========================================================================
	//		点　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//
	//	点が点上にあるかを調べる。
	//
	static inline bool On(							// (  O) ステイタス
													//			true:	点上にある
													//			false:	点上にない
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgPoint2D&	i_p2,		// (I  ) 点2
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
	//	return (p1 == p2);
		MgVect2D	V1 = i_p2 - i_p1;
		return ( Abs_2( V1) <= rTol * rTol);
	}
	
	//===========================================================================
	//		点　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//		点が点上にあるかを調べる。
	//
	static bool	MgChkPt2OnPt2(						// (  O) ステイタス
													//		 true:  点上にある
													//		 false: 点上にない
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgPoint2D&	i_p2,		// (I  ) 点2
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);

	// ---------------------( ３次元 )------------------------------
	//
	//	点が点上にあるかを調べる。
	//
	static inline bool ChkPt3OnPt3(					// (  O) ステイタス
													//			true:	点上にある
													//			false:	点上にない
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgPoint3D&	i_p2,		// (I  ) 点2
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
	//	return (p1 == p2);
		MgVect3D	V1 = i_p2 - i_p1;
		return ( Abs_2( V1) <= rTol * rTol);
	}
	
	//===========================================================================
	//		直線　形状演算
	//
	// ---------------------( ２次元 )------------------------------
	//
	//	点が直線上にあるかを調べる。
	//
	static inline bool ChkPt2OnULn2WS(				// (  O) ステイタス
													//		 	true:	直線上にある
													//		 	false:	直線上にない
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgULine2D&	i_ULn2,		// (I  ) 直線2
							MINT*		o_pist,		// (  O) 補助ステイタス
													//			MC_RIGHT			(010): 点が直線の右側
													//			MC_ON_LINE			(020): 点が直線上
													//			MC_LEFT				(040): 点が直線の左側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		bool		bst;							// ステイタス
		MgVect2D	v2s1;							// 直線2の始点から点1までのベクトル
		MREAL		pa1;							// 直線2から点1までの鉛直距離
	//
	// 直線2の方向（単位ベクトル）と直線2の始点から点1までのベクトルの外積より鉛直距離を求める
		v2s1 = i_p1 - i_ULn2.p;					
		pa1 = i_ULn2.v ^ v2s1;						// 直線2の方向（単位ベクトル）と直線2の始点から点1までのベクトルの外積
	//
	// 鉛直距離が誤差内なら直線上とみなす
		if ( Zero(pa1, rTol)) {
			*o_pist = MC_ON_LINE;
			bst = true;
	//
	// 鉛直距離が正なら直線の左とみなす
		} else if ( pa1 > 0) {
			*o_pist = MC_LEFT;
			bst = false;
	//
	// 鉛直距離が負なら直線の右とみなす
		} else {
			*o_pist = MC_RIGHT;
			bst = false;
		}
		return bst;
	}
	
	// ---------------------( ２次元 )------------------------------
	//
	//	点が半直線上にあるかを調べる。
	//
	static inline bool ChkPt2OnHLn2WS(				// (  O) ステイタス
													//		 	true:	半直線上にある
													//		 	false:	半直線上にない
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgHLine2D&	i_HLn2,		// (I  ) 半直線2
							MINT*		o_pist,		// (  O) 補助ステイタス
													//			MC_RIGHT			(010): 点が半直線の右側
													//			MC_ON_LINE			(020): 点が半直線上
													//			MC_LEFT				(040): 点が半直線の左側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		bool		bst;							// ステイタス
		MgVect2D	v2s1;							// 半直線2の始点から点1までのベクトル
		MREAL		pa1;							// 半直線2から点1までの鉛直距離
	//
	// 半直線2の方向（単位ベクトル）と半直線2の始点から点1までのベクトルの外積より鉛直距離を求める
		v2s1 = i_p1 - i_HLn2.p;					
		pa1 = i_HLn2.v ^ v2s1;						// 半直線2の方向（単位ベクトル）と半直線2の始点から点1までのベクトルの外積
	//
	// 鉛直距離が誤差内なら直線上とみなす
		if ( Zero( pa1, rTol)) {
			*o_pist = MC_ON_LINE;
			bst = true;
	//
	// 鉛直距離が正なら直線の左とみなす
		} else if ( pa1 > 0) {
			*o_pist = MC_LEFT;
			bst = false;
	//
	// 鉛直距離が負なら直線の右とみなす
		} else {
			*o_pist = MC_RIGHT;
			bst = false;
		}
		return bst;
	}

	// ---------------------( ２次元 )------------------------------
	//
	//	点が線分上にあるかを調べる。
	//
	static bool ChkPt2OnLn2WS(						// (  O) ステイタス
													//			true:	線分上にある
													//			false:	線分上にない
					const	MgPoint2D&	i_p1,		// (I  ) 点1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MINT*		o_pist,		// (  O) 補助ステイタス	(ステイタス1 | ステイタス2)
													//		 ステイタス1
													//			MC_RIGHT			(010): 点が線分の右側
													//			MC_ON_LINE			(020): 点が線分延長直線上
													//			MC_LEFT				(040): 点が線分の左側
													//		 ステイタス2
													//			MC_ON_PS			(001): 点が線分の始点上
													//			MC_INSIDE			(002): 点が線分の内側上
													//			MC_ON_PE			(004): 点が線分の終点上
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);
	
	// ---------------------( ２次元 )------------------------------
	//
	//	線分の中心点が直線上にあるかを調べる。
	//
	
	static inline bool ChkLn2OnULn2WS(				// (  O) ステイタス
													//			true:	直線上にある
													//			false:	直線上にない
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgULine2D&	i_ULn2,		// (I  ) 直線2
							MINT*		o_pist,		// (  O) ステイタス
													//			MC_RIGHT			(010): 点が線分の右側
													//			MC_ON_LINE			(020): 点が直線上
													//			MC_LEFT				(040): 点が線分の左側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		MgPoint2D Pt1;
		Pt1 = ( i_Ln1.p[0] + i_Ln1.p[1]) * 0.5;
		return ChkPt2OnULn2WS( Pt1, i_ULn2, o_pist);
	}
	
	// ---------------------( ２次元 )------------------------------
	//
	//	線分と線分が重なっているかを調べる。
	//
	static bool	ChkLn2OnLn2(						// (  O) ステイタス
													//			true:	重なっている
													//			false:	重なっていない
					const	MgLine2D&	i_Ln1,		// (I  ) 線分1
					const	MgLine2D&	i_Ln2,		// (I  ) 線分2
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);
	
	// ---------------------( ３次元 )------------------------------
	//
	//	点が直線上にあるかを調べる。
	//
	static inline bool ChkPt3OnULn3(				// (  O) ステイタス
													//			true:	線分上にある
													//			false:	線分上にない
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgULine3D&	i_ULn2,		// (I  ) 直線2
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		MgVect3D		v21, va1;
	//	MREAL		pa_2;							//	直線2から点1までの鉛直距離**2
	//
		v21 = i_p1 - i_ULn2.p;
		va1 = v21 ^ i_ULn2.v;
	//	pa_2 = Abs_2(va1);
	//	return ( pa_2 <= rTol * rTol);
		return ( Abs_2(va1) <= rTol * rTol);
	}
	
	// ---------------------( ３次元 )------------------------------
	//
	//	点が半直線上にあるかを調べる。
	//
	static inline bool ChkPt3OnHLn3(				// (  O) ステイタス
													//			true:	線分上にある
													//			false:	線分上にない
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgHLine3D&	i_HLn2,		// (I  ) 半直線2
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		MgVect3D	v21, va1;
		MREAL		c1;
	//	MREAL		pa_2;							//	直線2から点1までの鉛直距離**2
	//
		v21 = i_p1 - i_HLn2.p;
		va1 = v21 ^ i_HLn2.v;
		c1 = v21 * i_HLn2.v;
	//	pa_2 = Abs_2(va1);
	//	return ( pa_2 <= rTol * rTol);
		return ( Abs_2(va1) <= rTol * rTol && c1 > -rTol);
	}
	
	// ---------------------( ３次元 )------------------------------
	//
	//	点が線分上にあるかを調べる。
	//
	static bool	ChkPt3OnLn3WS(						// (  O) ステイタス
													//			true:	線分上にある
													//			false:	線分上にない
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
							MINT*		o_pist,		// (  O) 補助ステイタス	(ステイタス1 | ステイタス2)
													//		 ステイタス1
													//			MC_ON_LINE			(020): 点が線分延長直線上
													//		 ステイタス2
													//			MC_ON_PS			(001): 点が線分の始点上
													//			MC_INSIDE			(002): 点が線分の内側上
													//			MC_ON_PE			(004): 点が線分の終点上
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);
	
	// ---------------------( ３次元 )------------------------------
	//
	//	線分と線分が重なっているかを調べる。
	//
	static bool	ChkLn3OnLn3(						// (  O) ステイタス
													//			true:	重なっている
													//			false:	重なっていない
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);
	
	// ---------------------( ３次元 )------------------------------
	//
	//	線分と線分が重なっているかを調べる。
	//
	static bool	ChkLn3OnLn3WS(						// (  O) ステイタス
													//			true:	重なっている
													//			false:	重なっていない
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
							MINT*		o_pist,		// (  O) 補助ステイタス　重なりありの場合は次の通り
													//        -4    -3   -2   -1    0     1    2    3    4 		   	
													//		|--   |--  |--- | -- | --- |----| ---|  --|   --|           	  	
													//		|   --|  --| ---|----| --- | -- |--- |--  |--   |                　	
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);

	// ---------------------( ２次元 )------------------------------
	//		ベクトルとベクトルが垂直であるかを確認する
	static inline bool ChkPerp2V2(					// (  O) ステイタス true: 垂直 
					const	MgVect2D&	i_v1,		// (I  ) ベクトル1
					const	MgVect2D&	i_v2		// (I  ) ベクトル2
					)
	{
		MREAL fo = i_v1 ^ i_v2; MREAL fi = i_v1 * i_v2;
		return ( MGABS(fi/fo)  <= MGPTOL->A);
	}

	// ---------------------( ２次元 )------------------------------
	//		ベクトルとベクトルが垂直であるかを確認し、外積と内積を出力する
	static inline bool ChkPerp2VS2(					// (  O) ステイタス true: 垂直
					const	MgVect2D&	i_v1,		// (I  ) ベクトル1
					const	MgVect2D&	i_v2,		// (I  ) ベクトル2
							MREAL*		o_pso,		// (  O) 外積
							MREAL*		o_psi		// (  O) 内積
				)
	{
		*o_pso = i_v1 ^ i_v2;
		*o_psi = i_v1 * i_v2;
		return ( MGABS( *o_psi / *o_pso) <= MGPTOL->A);
	}

	// ---------------------( ３次元 )------------------------------
	//		ベクトルとベクトルが垂直であるかを確認する
	static inline bool ChkPerp2V3(					// (  O) ステイタス true: 垂直
					const	MgVect3D&	i_v1,		// (I  ) ベクトル1
					const	MgVect3D&	i_v2		// (I  ) ベクトル2
					)
	{
		MgVect3D vo = i_v1 ^ i_v2;
		MREAL fi = i_v1 * i_v2;
		return (fi * fi <= Abs_2(vo) * MGPTOL->A_2);
	}

	// ---------------------( ３次元 )------------------------------
	//		ベクトルとベクトルが垂直であるかを確認し、外積と内積を出力する
	static inline bool ChkPerp2VS3(					// (  O) ステイタス true: 垂直
					const	MgVect3D&	i_v1,		// (I  ) ベクトル1
					const	MgVect3D&	i_v2,		// (I  ) ベクトル2
							MgVect3D*	o_ppso,		// (  O) 外積
							MREAL*		o_psi		// (  O) 内積
					)
	{
		MgVect3D vo = i_v1 ^ i_v2;
		MREAL fi = i_v1 * i_v2;
		*o_ppso = vo; *o_psi = fi;
		return (fi * fi <= Abs_2(vo) * MGPTOL->A_2);
	}
	//
	//===========================================================================
	//		点 多角形 演算
	// ---------------------( ２次元 )------------------------------
	//	点と多角形の位置関係を求める
	//
	
	static inline bool ChkPt2OnPg2WS(				// (  O) ステイタス
													//			true:	多角形の内側または辺上
													//			false:	多角形の外側
					const	MgPoint2D&	i_Pt,		// (I  ) 点
					const	MgPolyg2D&	i_Pg,		// (I  ) 多角形
							MINT*		o_pist,		// (  O) ステイタス
													//			MC_IN_BORDER		(001): 点が多角形の内側
													//			MC_ON_BORDER		(002): 点が多角形の辺上(または頂点上)
													//			MC_OUT_BORDER		(004): 点が多角形の外側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		bool	bst;
		MINT	ist1;
		MINT	ict;
		
		ist1 = CountPg2AroundPt2( i_Pt, NULL, i_Pg, &ict, rTol);
		if ( ist1) {
			*o_pist = MC_ON_BORDER;
			bst = true;												// 多角形の辺上(または頂点上)
		} else {
			if ( ict) {
				*o_pist = MC_IN_BORDER;
				bst = true;											// 多角形の内側
			}
			else {
				*o_pist = MC_OUT_BORDER;
				bst = false;										// 多角形の外側
			}
		}
		return bst;
	}
	
	// ---------------------( ２次元 )------------------------------
	//	線分の中心点と多角形の位置関係を求める ２Ｄ
	//
	static inline bool ChkLn2OnPg2WS(				// (  O) ステイタス
													//			true:	多角形の内側または辺上
													//			false:	多角形の外側
					const	MgLine2D&	i_Ln1,		// (I  ) 線分
					const	MgPolyg2D&	i_Pg2,		// (I  ) 多角形
							MINT*		o_pisth,	// (  O) 補助ステイタス	(ステイタス1 | ステイタス2)
													// 		 テイタス1
													//			MC_IN_BORDER		(001):	点が多角形の内側
													//			MC_ON_BORDER		(002):	点が多角形の辺上(または頂点上)
													//			MC_OUT_BORDER		(004):	点が多角形の外側
													//		ステイタス2
													//			MC_ON_SIDE_SAME 	(010):	辺上(同一方向)
													//			MC_ON_SIDE_REV		(020):	辺上(逆方向)
													//			MC_ON_TOP			(040): 頂点上
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		bool		bst;
		MgPoint2D	pt1;
		MgVect2D		vt1;
		MINT		ist1;
		MINT		ict;
		
		pt1 = ( i_Ln1.p[0] + i_Ln1.p[1]) * 0.5;
		vt1 = i_Ln1.p[1] - i_Ln1.p[0];
		
		ist1 = CountPg2AroundPt2( pt1, &vt1, i_Pg2, &ict, rTol);
		if ( ist1) {
			*o_pisth = MC_ON_BORDER | ist1;
			bst = true;												// 多角形の辺上(または頂点上)
		} else {
			if ( ict) {
				*o_pisth = MC_IN_BORDER;
				bst = true;											// 多角形の内側
			}
			else {
				*o_pisth = MC_OUT_BORDER;
				bst = false;										// 多角形の外側
			}
		}
		return bst;
	}
	
	// ---------------------( ２次元 )------------------------------
	//	点と穴付き多角形の位置関係を求める
	//
	static bool ChkPt2OnGPg2WS(						// (  O) ステイタス
													//			true:	穴付き多角形の内側または辺上
													//			false:	穴付き多角形の外側
					const	MgPoint2D&	i_Pt,		// (I  ) 点
					const	MgGPolyg2D&	i_GPg,		// (I  ) 穴付き多角形
							MINT*		o_pist,		// (  O) ステイタス
													//			MC_IN_BORDER		(001): 点が穴付き多角形の内側
													//			MC_ON_BORDER		(002): 点が穴付き多角形の辺上(または頂点上)
													//			MC_OUT_BORDER		(004): 点が穴付き多角形の外側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);

	// ---------------------( ２次元 )------------------------------
	//	線分の中心点と穴付き多角形の位置関係を求める
	//
	static bool ChkLn2OnGPg2WS(						// (  O) ステイタス
													//			true:	穴付き多角形の内側または辺上
													//			false:	穴付き多角形の外側
					const	MgLine2D&	i_Ln1,		// (I  ) 線分
					const	MgGPolyg2D&	i_GPg2,		// (I  ) 穴付き多角形
							MINT*		o_pisth,	// (  O) 補助ステイタス	(ステイタス1 | ステイタス2)
													// 		 テイタス1
													//			MC_IN_BORDER		(001): 点が穴付き多角形の内側
													//			MC_ON_BORDER		(002): 点が穴付き多角形の辺上(または頂点上)
													//			MC_OUT_BORDER		(004): 点が穴付き多角形の外側
													// 		 テイタス2
													//			MC_ON_SIDE_SAME		(010): 辺上(同一方向)	(MC_ON_BORDERと共に設定)
													//			MC_ON_SIDE_REV		(020): 辺上(逆方向)		(MC_ON_BORDERと共に設定)
													//			MC_ON_TOP			(040): 頂点上			(MC_ON_BORDERと共に設定)
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);
	
	// ---------------------( ２次元 )------------------------------
	// 点と多角形の位置関係を求める
	// 多角形の辺が点の周りを回る周回数を求める（実体一周:1　穴一周:-1）
	static MINT	CountPg2AroundPt2(					// (  O) ステイタス
													//								(000): 多角形の中または外	
													//			MC_ON_SIDE_SAME		(010): 辺上(同一方向)
													//			MC_ON_SIDE_REV		(020): 辺上(逆方向)
													//			MC_ON_SIDE			(030): 辺上(線分方向=NULL: 線分方向指定無し)
													//			MC_ON_TOP			(040): 頂点上
					const	MgPoint2D&	i_Pt,		// (I  ) 点
					const	MgVect2D*	i_pvst,		// (I  ) 線分方向 または NULL
													//		 引数がNULLで無ければ点が辺上の場合、
													//		 辺の線分方向と比較する
					const	MgPolyg2D&	i_Pg,		// (I  ) 多角形
							MINT*		o_pict,		// (  O) 周回カウント
													//			>0: 多角形が実体の場合の周回数	(1:1周)
													//			=0: 頂点、辺上、多角形の外
													//			<0: 多角形が穴の場合の周回数	(-1:1周)	
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);
	
	// ---------------------( ３次元 )------------------------------
	//	点と多角形の位置関係を求める ３Ｄ
	//
	/*
	static bool ChkPt3OnPg3WS(						// (  O) ステイタス
													//			true:	多角形の内側または辺上
													//			false:	多角形の外側
					const	MgPoint3D&	i_Pt,		// (I  ) 点
					const	MgPolyg3D&	i_Pg,		// (I  ) 多角形
							MINT*		o_pist,		// (  O) ステイタス
								  					//		 多角形の平面と点の位置関係
													//			MC_UPPER			(010): 点が平面の上側	
													//			MC_ON_PLANE			(020): 点が平面上
													//			MC_LOWER			(040): 点が平面の下側
													//		 多角形と点の位置関係
													//			MC_IN_BORDER		(001): 点が多角形の内側
													//			MC_ON_BORDER		(002): 点が多角形の辺上
													//			MC_OUT_BORDER		(004): 点が多角形の外側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					);
	
	*/
	//
	// ---------------------( ３次元 )------------------------------
	//	線分の中心点と多角形の位置関係を求める
	//
	/*
	static inline bool ChkLn3OnPg3WS(				// (  O) ステイタス
													//			true:	多角形上
													//			false:	多角形外
					const	MgLine3D&	i_Ln1,		// (I  ) 線分
					const	MgPolyg3D&	i_Pg2,		// (I  ) 多角形
							MINT*		o_pist,		// (  O) 補助ステイタス
								  					//		 多角形の平面と点の位置関係
													//			MC_UPPER			(010): 点が平面の上側	
													//			MC_ON_PLANE			(020): 点が平面上
													//			MC_LOWER			(040): 点が平面の下側
													//       多角形と点の位置関係
													//			MC_IN_BORDER		(001): 点が多角形の内側
													//			MC_ON_BORDER		(002): 点が多角形の辺上
													//			MC_OUT_BORDER		(004): 点が多角形の外側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		MgPoint3D	Pt1;
		Pt1 = ( i_Ln1.p[0] + i_Ln1.p[1]) * 0.5;
		return OnPtPg3( Pt1, i_Pg2, o_pist);
	}

	*/
	//		平面　形状演算
	//
	// ---------------------( ３次元 )------------------------------
	//
	//	点が平面上にあるかを調べる。
	//
	static inline bool ChkPt3OnPln3WS(				// (  O) ステイタス
													//			true:  平面上
													//			false: 平面外
					const	MgPoint3D&	i_p1,		// (I  ) 点1
					const	MgPlane3D&	i_Pln2,		// (I  ) 平面2
							MINT*		o_pist,		// (  O) 補足ステイタス
													//			MC_UPPER			(010): 点が平面の上側	
													//			MC_ON_PLANE			(020): 点が平面上
													//			MC_LOWER			(040): 点が平面の下側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		bool	bst;
		MREAL	pa1;								//	点から平面までの距離
	//
		pa1 = ( i_Pln2.v * i_p1) + i_Pln2.d;
		if ( pa1 > rTol) {
			*o_pist = MC_UPPER;
			bst = false;
		} else if ( pa1 < -rTol) {
			*o_pist = MC_LOWER;
			bst = false;
		} else {
			*o_pist = MC_ON_PLANE;
			bst = true;
		}
		return bst;
	}

	// ---------------------( ３次元 )------------------------------
	//	直線が平面上にあるかを調べる。
	//
	static inline bool ChkULn3OnPln3(				// (  O) ステイタス
													//			true:  平面上
													//			false: 平面外
					const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgPlane3D&	i_Pln2,		// (I  ) 平面2
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		int		ist;
		if ( ChkPt3OnPln3WS( i_ULn1.p, i_Pln2, &ist)) {
	//
	//	平行のチェック
	//
			if ( ChkPerp2V3( i_ULn1.v, i_Pln2.v))
				return true;									//	平面上
		}
		return false;
	}
	
	// ---------------------( ３次元 )------------------------------
	//	線分が平面上にあるかを調べる。
	//
	static inline bool ChkLn3OnPln3WS(				// (  O) ステイタス
													//			true:  平面上
													//			false: 平面外
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgPlane3D&	i_Pln2,		// (I  ) 平面2
							MINT*		o_pist,		// (  O) 補足ステイタス
								  					//		 多角形の平面と点の位置関係
													//			MC_PS_UPPER			(001): 始点が平面の上側	
													//			MC_PS_ON_PLANE		(002): 始点が平面上
													//			MC_PS_LOWER			(004): 始点が平面の下側
													//       多角形と点の位置関係
													//			MC_PE_UPPER			(010): 終点が平面の上側	
													//			MC_PE_ON_PLANE		(020): 終点が平面上
													//			MC_PE_LOWER			(040): 終点が平面の下側
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		bool	bs, be;
		MINT	ists, iste;
	
		bs = ChkPt3OnPln3WS( i_Ln1.p[0], i_Pln2, &ists);
		be = ChkPt3OnPln3WS( i_Ln1.p[1], i_Pln2, &iste);
		*o_pist = (ists * MC_PS_UPPER + iste * MC_PE_UPPER)/ MC_UPPER;
		return (bs && be);
	}
	
	// ---------------------( ２次元 )------------------------------
	//
	//		２つの４角形が重なるか否かをチェックする。
	// 
	static inline bool	MgChkRct2OnRct2(			// (  O) ステイタス
													//		 true   交差あり
													//		 false  交差なし
					const	MgRect2D&	i_rct10,		// (I  ) ４角形1 (min,max)
					const	MgRect2D&	i_rct20,		// (I  ) ４角形2 (min,max)
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		return i_rct10.p[0].x < i_rct20.p[1].x + MGPTOL->D &&
			   i_rct20.p[0].x < i_rct10.p[1].x + MGPTOL->D &&
			   i_rct10.p[0].y < i_rct20.p[1].y + MGPTOL->D &&
			   i_rct20.p[0].y < i_rct10.p[1].y + MGPTOL->D;
	}

	// ---------------------( ３次元 )------------------------------
	//
	//		２つの４角形が重なるか否かをチェックする。
	//
	static inline bool	MgChkRct3OnRct3(			// (  O) ステイタス
													//		 true   交差あり
													//		 false  交差なし
					const	MgRect3D&	i_rct10,	// (I  ) ４角形1 (min,max)
					const	MgRect3D&	i_rct20,	// (I  ) ４角形2 (min,max)
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		return i_rct10.p[0].x < i_rct20.p[1].x + MGPTOL->D &&
			   i_rct20.p[0].x < i_rct10.p[1].x + MGPTOL->D &&
			   i_rct10.p[0].y < i_rct20.p[1].y + MGPTOL->D &&
			   i_rct20.p[0].y < i_rct10.p[1].y + MGPTOL->D &&
			   i_rct10.p[0].z < i_rct20.p[1].z + MGPTOL->D &&
			   i_rct20.p[0].z < i_rct10.p[1].z + MGPTOL->D;
	}
	
	// ---------------------( ２次元 )------------------------------
	//
	//		点がＭＩＮ／ＭＡＸ領域が内にあるか否かをチェックする。
	//
	static inline	bool ChkPt2InMMR2(
					const	MgPoint2D&		i_pt1,	// Point
					const	MgMinMaxR2D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		return i_pt1.x < i_mx2.max.x + MGPTOL->D && i_mx2.min.x - MGPTOL->D < i_pt1.x &&
			   i_pt1.y < i_mx2.max.y + MGPTOL->D && i_mx2.min.y - MGPTOL->D < i_pt1.y;
	}
	
	// ---------------------( ３次元 )------------------------------
	//
	//		点がＭＩＮ／ＭＡＸ領域が内にあるか否かをチェックする。
	//
	static inline	bool ChkPt3InMMR3(
					const	MgPoint3D&		i_pt1,	// Point
					const	MgMinMaxR3D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		return i_pt1.x < i_mx2.max.x + MGPTOL->D && i_mx2.min.x - MGPTOL->D < i_pt1.x &&
			   i_pt1.y < i_mx2.max.y + MGPTOL->D && i_mx2.min.y - MGPTOL->D < i_pt1.y &&
			   i_pt1.z < i_mx2.max.z + MGPTOL->D && i_mx2.min.z - MGPTOL->D < i_pt1.z;
	}

	// ---------------------( ２次元 )------------------------------
	//
	//		２つのＭＩＮ／ＭＡＸ領域が重なるか否かをチェックする。
	//
	static inline	bool ChkMMI2OnMMI2(
					const	MgMinMaxI2D&	i_mx1,	// MIN/MAX
					const	MgMinMaxI2D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		return i_mx1.min.x <= i_mx2.max.x && i_mx2.min.x <= i_mx1.max.x &&
			   i_mx1.min.y <= i_mx2.max.y && i_mx2.min.y <= i_mx1.max.y;
	}

	// ---------------------( ２次元 )------------------------------
	//
	//		２つのＭＩＮ／ＭＡＸ領域が重なるか否かをチェックする。
	//
	static inline	bool ChkMMR2OnMMR2(
					const	MgMinMaxR2D&	i_mx1,	// MIN/MAX
					const	MgMinMaxR2D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		return i_mx1.min.x < i_mx2.max.x + MGPTOL->D && i_mx2.min.x < i_mx1.max.x + MGPTOL->D &&
			   i_mx1.min.y < i_mx2.max.y + MGPTOL->D && i_mx2.min.y < i_mx1.max.y + MGPTOL->D;
	}

	// ---------------------( ３次元 )------------------------------
	//
	//		２つのＭＩＮ／ＭＡＸ領域が重なるか否かをチェックする。
	//
	static inline	bool ChkMMR3OnMMR3(
					const	MgMinMaxR3D&	i_mx1,	// MIN/MAX
					const	MgMinMaxR3D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) トレランス
					)
	{
		return i_mx1.min.x < i_mx2.max.x + MGPTOL->D && i_mx2.min.x < i_mx1.max.x + MGPTOL->D &&
			   i_mx1.min.y < i_mx2.max.y + MGPTOL->D && i_mx2.min.y < i_mx1.max.y + MGPTOL->D &&
			   i_mx1.min.z < i_mx2.max.z + MGPTOL->D && i_mx2.min.z < i_mx1.max.z + MGPTOL->D;
	}

	// ---------------------( ２次元 )------------------------------
	// P1を原点としたP2の位置の象限を求める
	//
	static inline MINT Quadrant	(					// (  O) 1～4: 象限
					const	MgPoint2D&	i_p1,		// (I  ) P1
					const	MgPoint2D&	i_p2		// (I  ) P2
					)
	{
		return ( ( i_p2.x > i_p1.x) ? ( ( i_p2.y > i_p1.y) ? 1 : 4) : ( ( i_p2.y > i_p1.y) ? 2 : 3));
	}
		
	// ---------------------( ２次元 )------------------------------
	//		点列を並べ方向に従った座標順に並べる（同一点は間引く）
	//
	static void	SortVGPt2(
					const	MgVect2D&	i_v1,		// (I  ) 点列の並べ方向
							MgGPoint2D*	io_pGPt2	// (I O) 並べる点列
					);

	// ---------------------( ２次元 )------------------------------
	//		点列を線分の始点から終点に向かう方向に従った座標順に並べる（同一点は間引く）
	//
	static inline void	SortLnGPt2(
					const	MgLine2D&	i_Ln1,		// (I  ) 点列の並べ方向を示す線分
							MgGPoint2D*	io_pGPt2	// (I O) 並べる点列
					)
	{
		MgVect2D		v1;
		v1 = i_Ln1.p[1] - i_Ln1.p[0];
		SortVGPt2( v1, io_pGPt2);
	}

	//// ---------------------( ３次元 )------------------------------
	////		点列を並べ方向に従った座標順に並べる（同一点は間引く）
	////
	//static void	MgSortVGPt3(
	//				const	MgVect3D&	i_V1,		// (I  ) 点列の並べ方向
	//						MgGPoint3D*	io_pGPt2	// (I O) 並べる点列
	//				);

	//// ---------------------( ３次元 )------------------------------
	////		点列を線分の始点から終点に向かう方向に従った座標順に並べる（同一点は間引く）
	////
	//static inline void	MgSortLnGPt3(
	//				const	MgLine3D&	i_Ln1,		// (I  ) 点列の並べ方向を示す線分
	//						MgGPoint3D*	io_pGPt2	// (I O) 並べる点列
	//				)
	//	{
	//		MgVect3D		V1;
	//		V1 = i_Ln1.p[1] - i_Ln1.p[0];
	//		MgSortVGPt3( V1, io_pGPt2);
	//	}

	//===========================================================================
	//	線分群を正規化する。（線分の逆方向の重なりを除去する）
	//
	static inline void Norm(						//
					const	MgGLine2D&	i_GLn1,		// (I  ) 線分
							MgGLine2D*	o_pGLn2		// (  O) 重なりを除去後の線分
					)
	{
		MgLine2D	work[MX_LIN1+1];				// 線分の数用のエリアを追加した作業エリアを確保する
		MgGLine2D	*GLn = (MgGLine2D*)work;
		DivideGLn2( i_GLn1, o_pGLn2);				// 線分を交点で分割する
	//	ThinOut( *GLn, GLn2);						// 往復線分と開放端を持つ線分を間引く
	}
	
	//===========================================================================
	//		共通　形状演算
	//
	//	------------- Ｓ値の算出　------------------
	//
	// ---------------------( ３次元 )------------------------------
	//		直線と点の位置関係を表すＳ値
	//
	static inline MREAL SVal2ULn3(					// (  O) Ｓ値(２直線の方向ベクトルからなる平行６面体の体積）
				    const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgULine3D&	i_ULn2		// (I  ) 直線2
					)
	{
	//		( (ULn1.p.x*ULn1.v.y-ULn1.p.y*ULn1.v.x) * (ULn2.p.z*ULn2.v.w-ULn2.p.w*ULn2.v.z)
	//		- (ULn1.p.x*ULn1.v.z-ULn1.p.z*ULn1.v.x) * (ULn2.p.y*ULn2.v.w-ULn2.p.w*ULn2.v.y)
	//		+ (ULn1.p.x*ULn1.v.w-ULn1.p.w*ULn1.v.x) * (ULn2.p.y*ULn2.v.z-ULn2.p.z*ULn2.v.y)
	//		+ (ULn1.p.y*ULn1.v.z-ULn1.p.z*ULn1.v.y) * (ULn2.p.x*ULn2.v.w-ULn2.p.w*ULn2.v.x)
	//		- (ULn1.p.y*ULn1.v.w-ULn1.p.w*ULn1.v.y) * (ULn2.p.x*ULn2.v.z-ULn2.p.z*ULn2.v.x)
	//		+ (ULn1.p.z*ULn1.v.w-ULn1.p.w*ULn1.v.z) * (ULn2.p.x*ULn2.v.y-ULn2.p.y*ULn2.v.x))
	//
		return	( ( i_ULn1.p.x * i_ULn1.v.y - i_ULn1.p.y * i_ULn1.v.x) * ( -i_ULn2.v.z)
				- ( i_ULn1.p.x * i_ULn1.v.z - i_ULn1.p.z * i_ULn1.v.x) * ( -i_ULn2.v.y)
				+ ( -i_ULn1.v.x) * ( i_ULn2.p.y * i_ULn2.v.z - i_ULn2.p.z * i_ULn2.v.y)
				+ ( i_ULn1.p.y * i_ULn1.v.z - i_ULn1.p.z * i_ULn1.v.y) * ( -i_ULn2.v.x)
				- ( -i_ULn1.v.y) * ( i_ULn2.p.x * i_ULn2.v.z - i_ULn2.p.z * i_ULn2.v.x)
				+ ( -i_ULn1.v.z) * ( i_ULn2.p.x * i_ULn2.v.y - i_ULn2.p.y * i_ULn2.v.x));
	}

	// ---------------------( ３次元 )------------------------------
	//		直線と点の位置関係を表すＳ値
	//
	static inline MREAL SValULnLn3(					// (  O) Ｓ値(直線の方向ベクトルと線分からなる平行６面体の体積）
				    const	MgULine3D&	i_ULn1,		// (I  ) 直線1
					const	MgLine3D&	i_Ln2		// (I  ) 線分2
					)
	{
	//		( (ULn1.p.x*ULn1.v.y-ULn1.p.y*ULn1.v.x) * (Ln2.p[0].z*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].z)
	//		- (ULn1.p.x*ULn1.v.z-ULn1.p.z*ULn1.v.x) * (Ln2.p[0].y*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].y)
	//		+ (ULn1.p.x*ULn1.v.w-ULn1.p.w*ULn1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
	//		+ (ULn1.p.y*ULn1.v.z-ULn1.p.z*ULn1.v.y) * (Ln2.p[0].x*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].x)
	//		- (ULn1.p.y*ULn1.v.w-ULn1.p.w*ULn1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
	//		+ (ULn1.p.z*ULn1.v.w-ULn1.p.w*ULn1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x))
	//
		return
		(	  ( i_ULn1.p.x * i_ULn1.v.y - i_ULn1.p.y * i_ULn1.v.x) * ( i_Ln2.p[0].z - i_Ln2.p[1].z)
			- ( i_ULn1.p.x * i_ULn1.v.z - i_ULn1.p.z * i_ULn1.v.x) * ( i_Ln2.p[0].y - i_Ln2.p[1].y)
			+ ( -i_ULn1.v.x) * ( i_Ln2.p[0].y * i_Ln2.p[1].z - i_Ln2.p[0].z * i_Ln2.p[1].y)
			+ ( i_ULn1.p.y * i_ULn1.v.z - i_ULn1.p.z * i_ULn1.v.y) * ( i_Ln2.p[0].x - i_Ln2.p[1].x)
			- ( -i_ULn1.v.y) * ( i_Ln2.p[0].x * i_Ln2.p[1].z - i_Ln2.p[0].z * i_Ln2.p[1].x)
			+ ( -i_ULn1.v.z) * ( i_Ln2.p[0].x * i_Ln2.p[1].y - i_Ln2.p[0].y * i_Ln2.p[1].x));
	}

	// ---------------------( ３次元 )------------------------------
	//		直線と点の位置関係を表すＳ値
	//
	static inline MREAL SVal2Ln3(					// (  O) Ｓ値(2線分からなる平行６面体の体積）
				    const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgLine3D&	i_Ln2		// (I  ) 線分2
					)
	{
	//		( (Ln1.p[0].x*Ln1.v.y-Ln1.p[0].y*Ln1.v.x) * (Ln2.p[0].z*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].z)
	//		- (Ln1.p[0].x*Ln1.v.z-Ln1.p[0].z*Ln1.v.x) * (Ln2.p[0].y*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].y)
	//		+ (Ln1.p[0].x*Ln1.v.w-Ln1.p[0].w*Ln1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
	//		+ (Ln1.p[0].y*Ln1.v.z-Ln1.p[0].z*Ln1.v.y) * (Ln2.p[0].x*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].x)
	//		- (Ln1.p[0].y*Ln1.v.w-Ln1.p[0].w*Ln1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
	//		+ (Ln1.p[0].z*Ln1.v.w-Ln1.p[0].w*Ln1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x))
	//
		return
		(	  ( i_Ln1.p[0].x * i_Ln1.p[1].y - i_Ln1.p[0].y * i_Ln1.p[1].x) * ( i_Ln2.p[0].z - i_Ln2.p[1].z)
			- ( i_Ln1.p[0].x * i_Ln1.p[1].z - i_Ln1.p[0].z * i_Ln1.p[1].x) * ( i_Ln2.p[0].y - i_Ln2.p[1].y)
			+ ( i_Ln1.p[0].x - i_Ln1.p[1].x) * ( i_Ln2.p[0].y * i_Ln2.p[1].z - i_Ln2.p[0].z * i_Ln2.p[1].y)
			+ ( i_Ln1.p[0].y * i_Ln1.p[1].z - i_Ln1.p[0].z * i_Ln1.p[1].y) * ( i_Ln2.p[0].x - i_Ln2.p[1].x)
			- ( i_Ln1.p[0].y - i_Ln1.p[1].y) * ( i_Ln2.p[0].x * i_Ln2.p[1].z - i_Ln2.p[0].z * i_Ln2.p[1].x)
			+ ( i_Ln1.p[0].z - i_Ln1.p[1].z) * ( i_Ln2.p[0].x * i_Ln2.p[1].y - i_Ln2.p[0].y * i_Ln2.p[1].x));
	}

	// ---------------------( ３次元 )------------------------------
	//		直線と点の位置関係を表すＳ値
	//
	static inline void SValLnULnS3(					//
					const	MgLine3D&	i_Ln1,		// (I  ) 線分1
				    const	MgULine3D&	i_ULn2,		// (I  ) 直線2
					const	MgVect3D&	i_vso,		// (I  ) 線分1と直線2がある平面の法線ベクトル
							MREAL*		o_pss,		// (  O) 線分１の始点側Ｓ値
													//		(直線2の方向ベクトルと平面の法線ベクトルと
													//		 線分1の始点で出来る平行６面体の体積)
							MREAL*		o_pse		// (  O) 線分１の終点側Ｓ値
													//		(直線2の方向ベクトルと平面の法線ベクトルと
													//		 線分1の終点で出来る平行６面体の体積)
					)
	{
		MgVect3D	N;								//	直線２と垂直ベクトルからなる平面の係数
		MREAL		d;								//	基準点から直線1の始点までの同平面に垂直距離
	//
		N = i_ULn2.v ^ i_vso;
		d =  i_ULn2.p * N;
		*o_pss = ( i_Ln1.p[0] * N) - d;
		*o_pse = ( i_Ln1.p[1] * N) - d;
	}

	// ---------------------( ３次元 )------------------------------
	//		直線と点の位置関係を表すＳ値
	//
	static inline void SVal2LnS3(					// (  O) ステイタス
				    const	MgLine3D&	i_Ln1,		// (I  ) 線分1
					const	MgLine3D&	i_Ln2,		// (I  ) 線分2
					const	MgVect3D&	i_vso,		// (I  ) 線分1と線分2がある平面の法線ベクトル
							MREAL*		o_pss,		// (  O) 線分１の始点側Ｓ値
													//		(線分2と平面の法線ベクトルと線分1の始点で
													//		 出来る平行６面体の体積)
							MREAL*		o_pse		// (  O) 線分１の終点側Ｓ値
													//		(直線2と平面の法線ベクトルと線分1の終点で
													//		 出来る平行６面体の体積)
			)
	{
		MgVect3D	N;								//	直線２と垂直ベクトルからなる平面の係数
		MREAL		d;								//	基準点から直線1の始点までの同平面に垂直距離
		MgVect3D	vd;								//	線分２のベクトル
	//
		vd = i_Ln2.p[1] - i_Ln2.p[0];
		N = vd ^ i_vso;
		d =  i_Ln2.p[0] * N;
		*o_pss = ( i_Ln1.p[0] * N) - d;
		*o_pse = ( i_Ln1.p[1] * N) - d;
	}

		
		
	//===========================================================================
	//		平面 形状演算
	//

	static MgPlane3D Plane3CPPt( const MgPoint3D *pt);							// ３点より平面の方程式の係数と定数を求める（正規化）

	static MgPlane3D Plane3C3Pt( const MgPoint3D& p0, const MgPoint3D& p1,		// ３点より平面の方程式の係数と定数を求める（正規化）
					   const MgPoint3D& p2);

	static MgPlane3D Plane3CPg( const MgPolyg3D &pg);							// 多角形より平面の方程式の係数と定数を求める（正規化）

	static MgPlane3D Plane3C2Pt2F( const MgPoint2D& p1, const MgPoint2D& p2,	// 始点と終点の２点と勾配より平面の方程式の係数と定数を求める（正規化）
						 MREAL rkb, MREAL z);

	static MgPlane3D Plane3CLn2F( const MgLine2D& ln1,							// 線分と勾配より平面の方程式の係数と定数を求める（正規化）
						MREAL rkb, MREAL z = 0.);

	//===========================================================================
	//		平面の方程式の係数と定数を正規化した平面を求める
	//		ax+by+cz+d=0	(a*a+b*b+c*c=1.0)
	//
	static MgPlane3D NormPln(						// (  O) 正規化後の３次元平面
				const	MgPlane3D&	i_pl,			// (I  ) ３次元平面
						MREAL i_Tol = g_gTol.D);	// (I  ) 許容誤差





	////===========================================================================
	////		３点より平面の方程式の係数と定数を求める（正規化）
	////
	////	ax+by+cz+d=0
	////
	//static inline MgPlane3D Plane3CPPt(			// (  O) 平面式
	//				const	MgPoint3D*	i_pt,		// (I  ) ３点座標
	//						MREAL i_Tol = g_gTol.D	// (I  ) 許容誤差
	//				)
	//{
	//	MgPlane3D	Plno;
	//	MgVect3D	v1, v2;
	//
	//	v1 = i_pt[1] - i_pt[0];
	//	v2 = i_pt[2] - i_pt[0];
	//
	//	Plno.v = UnitizeV3( v1 ^ v2, i_Tol);
	//	Plno.d = -( Plno.v * i_pt[0]);
	//	return Plno;
	//}

	////===========================================================================
	////		３点より平面の方程式の係数と定数を求める（正規化）
	////
	//static inline MgPlane3D Plane3C3Pt(			// (  O) 平面式
	//				const	MgPoint3D&	i_p0,		// (I  ) 点１
	//				const	MgPoint3D&	i_p1,		// (I  ) 点２
	//				const	MgPoint3D&	i_p2,		// (I  ) 点３
	//						MREAL i_Tol = g_gTol.D	// (I  ) 許容誤差
	//				)
	//{
	//	MgPlane3D	Plno;
	//	MgVect3D	v1, v2;
	//
	//	v1 = i_p1 - i_p0;
	//	v2 = i_p2 - i_p0;
	//
	//	Plno.v = UnitizeV3( v1 ^ v2, i_Tol);
	//	Plno.d = -(Plno.v * i_p0);
	//	return Plno;
	//}
	
	////===========================================================================
	////		多角形より平面の方程式の係数と定数を求める（正規化）
	////													pkm	面積の絶対値の合計で求め方向は実面積で求める方が良いか pkm
	//static MgPlane3D Plane3CPg(					// (  O) 平面式
	//				const	MgPolyg3D&	i_pg		// (I  ) 多角形
	//				);
	
	////===========================================================================
	////		２次元始点と２次元終点の２点、勾配とＺ座標より平面の方程式の係数と定数を求める（正規化）
	////
	//static MgPlane3D Plane3C2Pt2F(
	//				const	MgPoint2D&	i_p1,		// (I  ) ２次元始点
	//				const	MgPoint2D&	i_p2,		// (I  ) ２次元終点
	//						MREAL		i_rkb,		// (I  ) 勾配	(始点から終点に向かい左方向=0 tan)
	//						MREAL		i_z			// (I  ) Ｚ座標
	//				);
	
	////===========================================================================
	////		２次元線分、勾配とＺ座標より平面の方程式の係数と定数を求める（正規化）
	////
	//static MgPlane3D Plane3CLn2F(
	//				const	MgLine2D&	i_ln1,		// (I  ) ２次元線分
	//						MREAL		i_rkb,		// (I  ) 勾配	(線分の始点から終点に向かい左方向=0 tan)
	//						MREAL		i_z			// (I  ) Ｚ座標
	//				);
	
	////===========================================================================
	////		平面の方程式の係数と定数を正規化した(係数a,b,cを単位ベクトルに変換した)平面を求める
	////
	//static MgPlane3D NormPln(
	//				const	MgPlane3D&	i_pl,
	//						MREAL		i_Tol
	//				)
	//{
	//	MREAL	d1 = Abs( i_pl.v);
	//		MBCHECK_ZEROVECT( d1, MBCstr( "MgPlane3D Norm"), i_Tol);
	//	MREAL	d2 = 1.f / d1;
	//	return Plane3( i_pl.v.x * d2, i_pl.v.y * d2, i_pl.v.z * d2, i_pl.d * d2);
	//}

};

//	;必要であるが無し　MgChkLn2OnLn2WS

//
//======================( ２次元、３次元 )==============================
//	２次元、３次元座標変換マトリックス
//
//===========================================================================
//	処理内容
//	    座標変換マトリックスの加算
//
//	使用法
//		MgMat3DE = MgMat2DE1 + MgMat2DE2;
//
//	| m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  +  | n21 n22 n23 |
//	| m31 m32 m33 |     | n31 n32 n33 |
//
inline MgMat2DE operator + ( const MgMat2DE& i_tm, const MgMat2DE& i_tn)			// +
{
	return MGeo::MatPlus2( i_tm, i_tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat2DE1 += MgMat2DE2;
//
//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  =  | m21 m22 m23 |  +  | n21 n22 n23 |
//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2DE operator += ( MgMat2DE& io_tm, const MgMat2DE& i_tn)				// +=
{
	return MGeo::MatPlusEqual2( io_tm, i_tn);
}

//===========================================================================
//	処理内容
//		負の座標変換マトリックスを作成
//
//	使用法
//		MgMat2DE2 = - MgMat2DE1;
//
//	  | m11 m12 m13 |
//	- | m21 m22 m23 |
//	  | m31 m32 m33 |
//
inline	MgMat2DE operator - ( const MgMat2DE& i_tm)								// -
{
	return MGeo::MatSingleMinus2( i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat3DE = MgMat2DE1 - MgMat2DE2;
//
//	  | m11 m12 m13 |     | n11 n12 n13 |
//	  | m21 m22 m23 |  -  | n21 n22 n23 |
//	  | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2DE operator - ( const MgMat2DE& i_tm, const MgMat2DE& i_tn)			// -
{
	return MGeo::MatMinus2( i_tm, i_tn);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの引算
//
//	使用法
//		MgMat2DE1 -= MgMat2DE2;
//
//	| m11 m12 m13 |    | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  = | m21 m22 m23 |  -  | n21 n22 n23 |
//	| m31 m32 m33 |    | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2DE operator -= ( MgMat2DE& io_tm, const MgMat2DE& i_tn)				// -=
{
	return MGeo::MatMinusEqual2( io_tm, i_tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
//
//	使用法
//		MgMat3DE = MgMat2DE1 * MgMat2DE2;
//
//	| m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  X  | n21 n22 n23 |
//	| m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2DE operator * ( const MgMat2DE& i_tm, const MgMat2DE& i_tn)			// *
{
	return MGeo::MatMult2( i_tm, i_tn);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスのかけ算
//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
//
//	使用法
//		MgMat2DE2 *= MgMat2DE1;
//
//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  =  | m21 m22 m23 |  X  | n21 n22 n23 |
//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2DE operator *= ( MgMat2DE& io_tm, const MgMat2DE& i_tn)				// *=
{
	return MGeo::MatMultEqual2( io_tm, i_tn);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D = MgVect2D * MgMat2DE;
//
//					   | m11 m12 m13 |
//	| px  py  1  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |     
//
inline	MgVect2D operator * ( const MgVect2D& i_pt, const MgMat2DE& i_tm)		// *	座標変換
{
	return MGeo::MatMultPt22( i_pt, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D *= MgMat2DE;
//
//										  | m11 m12 m13 |
//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 m23 |
//				   						  | m31 m32 m33 |
//
inline	MgVect2D operator *= ( MgVect2D& io_pt, const MgMat2DE& i_tm)			// *=	座標変換
{
	return MGeo::MatMultEqualPt22( io_pt, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D = MgULine2D*  MgMat2DE;
//
//	| px  py  1  |     | m11 m12 m13 |
//	| vx  vy  0  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |
//
inline	MgULine2D operator * ( const MgULine2D& i_uln, const MgMat2DE& i_tm)	// *	座標変換
{
	return MGeo::MatMultULn22( i_uln, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D* = MgMat2DE;
//
//	| px  py  1  |     | px  py  1  |     | m11 m12 m13 |
//	| vx  vy  0  |  =  | vx  vy  1  |  X  | m21 m22 m23 |
//			             				  | m31 m32 m33 |
//
inline	MgULine2D operator *= ( MgULine2D& io_uln, const MgMat2DE& i_tm)		// *=	座標変換
{
	return MGeo::MatMultEqualULn22( io_uln, i_tm);
}

//===============( ２次元座標変換マトリックスで３次元座標処理 )==============
//
//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect3D2 = MgVect3D1 * MgMat2DE1;
//
//						  | m11 m12 0 m13 |     
//	| px  py  pz  1 |  X  | m21 m22 0 m23 |
//						  |  0   0  1  0  |
//						  | m31 m32 0 m33 |
//
inline	MgVect3D operator * ( const MgVect3D& i_Pt, const MgMat2DE& i_tm)		// *	座標変換
{
	return MGeo::MatMultPt32( i_Pt, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect3D *= MgMat2DE;
//
//						 						| m11 m12 0 m13 |
//	| px  py  pz  1 |  =  | px  py  pz  1 |  X  | m21 m22 0 m23 |
//			   									|  0   0  1  0  |
//			   									| m31 m32 0 m33 |
//
inline	MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat2DE& i_tm)			// *=	座標変換

{
	return MGeo::MatMultEqualPt32( io_Pt, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D = MgULine2D*  MgMat2DE;
//
//	| px  py  pz  1 |	  | m11 m12 0 m13 |
//	| vx  vy  vz  1 |  X  | m21 m22 0 m23 |
//						  |  0   0  1  0  |
//			   			  | m31 m32 0 m33 |
//
inline MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat2DE& i_tm)		// *	座標変換
{
	return MGeo::MultULn32( i_ULn, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D* = MgMat2DE;
//
//	| px  py  pz  1 |     | px  py  pz  1 |		| m11 m12 0 m13 |
//	| vx  vy  vz  1 |  =  | vx  vy  vz  1 |  X  | m21 m22 0 m23 |
//												|  0   0  1  0  |
//				 				   				| m31 m32 0 m33 |
//
inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat2DE& i_tm)			// *=	座標変換
{
	return MGeo::MatMultEqualULn32( io_ULn, i_tm);
}

//===========================================================================
//
//	３Ｄ座標変換マトリックスの計算
//
//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat3DE_3 = MgMat3DE_1 + MgMat3DE_2;
//
//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline	MgMat3DE operator + ( const MgMat3DE& i_Tm, const MgMat3DE& i_Tn)			// +
{
	return MGeo::MatPlus3( i_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat3DE += MgMat3DE;
//
//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline	MgMat3DE operator += ( MgMat3DE& io_Tm, const MgMat3DE& i_Tn)				// +=
{
	return MGeo::MatPlusEqual3( io_Tm, i_Tn);
}	

//===========================================================================
//	処理内容
//		負の座標変換マトリックスを作成
//
//	使用法
//		MgMat3DE_2 = - MgMat3DE_1;
//
//	  | m11 m12 m13 m14 |
//	- | m21 m22 m23 m24 |
//	  | m31 m32 m33 m34 |
//	  | m41 m42 m43 m44 |     
//
inline	MgMat3DE operator - ( const MgMat3DE& i_Tm)								// -
{
	return MGeo::MatSingleMinus3( i_Tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat3DE_3 = MgMat3DE_1 - MgMat3DE_2;
//
//	  | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
//	  | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	  | m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline	MgMat3DE operator - ( const MgMat3DE& i_Tm, const MgMat3DE& i_Tn)			// -
{
	return MGeo::MatMinus3( i_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat3DE -= MgMat3DE;
//
//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline MgMat3DE operator -= ( MgMat3DE& io_Tm, const MgMat3DE& i_Tn)				// -=
{
	return MGeo::MatMinusEqual3( io_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//
//	使用法
//		MgMat3DE_3 = MgMat3DE_1 * MgMat3DE_2;
//
//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline MgMat3DE operator * ( const MgMat3DE& i_Tm, const MgMat3DE& i_Tn)			// *
{
	return MGeo::MatMult3( i_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//
//	使用法
//		MgMat3DE *= MgMat3DE;
//
//	| m11 m12 m13 m14 |     | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline MgMat3DE operator *= ( MgMat3DE& io_Tm, const MgMat3DE& i_Tn)
{
	return MGeo::MatMultEqual3( io_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgMat3DE_2 = MgVect2D * MgMat3DE_1;
//
//						    | m11 m12 m13 m14 |
//	| px  py  0   1   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
inline MgVect2D operator * ( const MgVect2D& i_Pt, const MgMat3DE& i_Tm)		// 座標変換
{
	return MGeo::MatMultPt23( i_Pt, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgVect2D *= MgMat3DE;
//
//						     					    | m11 m12 m13 m14 |
//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 m24 |
//	           									    | m31 m32 m33 m34 |
//	           									    | m41 m42 m43 m44 |
//
inline MgVect2D operator *= ( MgVect2D& io_Pt, const MgMat3DE& i_Tm)			// 座標変換
{
	return MGeo::MatMultEqualPt23( io_Pt, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D_2 = MgVect3D_1 * MgMat3DE;
//
//	 					    | m11 m12 m13 m14 |
//	| px  py  pz  1   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
inline MgVect3D operator * ( const MgVect3D& i_Pt, const MgMat3DE& i_Tm)		// 座標変換
{
	return MGeo::MatMultPt33( i_Pt, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D *= MgMat3DE;
//
//							 					    | m11 m12 m13 m14 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
//												    | m31 m32 m33 m34 |
//												    | m41 m42 m43 m44 |
//
inline MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat3DE& i_Tm)			// 座標変換
{
	return MGeo::MatMultEqualPt33( io_Pt, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgULine3D_2 = MgULine3D_1 * MgMat3DE;
//
//	| px  py  pz  1   |     | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//							| m31 m32 m33 m34 |
//							| m41 m42 m43 m44 |
//
inline MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat3DE& i_Tm)		// 座標変換
{
	return MGeo::MatMultULn33( i_ULn, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D *= MgMat3DE;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//													| m31 m32 m33 m34 |
//													| m41 m42 m43 m44 |
//
inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat3DE& i_Tm)			// 座標変換
{
	return MGeo::MatMultEqualULn33( io_ULn, i_Tm);
}

//
//======================( ３Ｄ，４Ｄ )==============================
//	３Ｄ，４Ｄマトリックス
//
//===========================================================================
//	処理内容
//	    座標変換マトリックスの加算
//
//	使用法
//		MgMat4D = MgMat3D1 + MgMat3D2;
//
//	| m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  +  | n21 n22 n23 |
//	| m31 m32 m33 |     | n31 n32 n33 |
//
inline MgMat3D operator + ( const MgMat3D& i_tm, const MgMat3D& i_tn)			// +
{
	return MGeo::MatPlus2( i_tm, i_tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat3D1 += MgMat3D2;
//
//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  =  | m21 m22 m23 |  +  | n21 n22 n23 |
//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat3D operator += ( MgMat3D& io_tm, const MgMat3D& i_tn)				// +=
{
	return MGeo::MatPlusEqual2( io_tm, i_tn);
}

//===========================================================================
//	処理内容
//		負の座標変換マトリックスを作成
//
//	使用法
//		MgMat3D2 = - MgMat3D1;
//
//	  | m11 m12 m13 |
//	- | m21 m22 m23 |
//	  | m31 m32 m33 |
//
inline	MgMat3D operator - ( const MgMat3D& i_tm)								// -
{
	return MGeo::MatSingleMinus2( i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat4D = MgMat3D1 - MgMat3D2;
//
//	  | m11 m12 m13 |     | n11 n12 n13 |
//	  | m21 m22 m23 |  -  | n21 n22 n23 |
//	  | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat3D operator - ( const MgMat3D& i_tm, const MgMat3D& i_tn)			// -
{
	return MGeo::MatMinus2( i_tm, i_tn);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの引算
//
//	使用法
//		MgMat3D1 -= MgMat3D2;
//
//	| m11 m12 m13 |    | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  = | m21 m22 m23 |  -  | n21 n22 n23 |
//	| m31 m32 m33 |    | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat3D operator -= ( MgMat3D& io_tm, const MgMat3D& i_tn)				// -=
{
	return MGeo::MatMinusEqual2( io_tm, i_tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
//
//	使用法
//		MgMat4D = MgMat3D1 * MgMat3D2;
//
//	| m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  X  | n21 n22 n23 |
//	| m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat3D operator * ( const MgMat3D& i_tm, const MgMat3D& i_tn)			// *
{
	return MGeo::MatMult2( i_tm, i_tn);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスのかけ算
//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
//
//	使用法
//		MgMat3D2 *= MgMat3D1;
//
//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  =  | m21 m22 m23 |  X  | n21 n22 n23 |
//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat3D operator *= ( MgMat3D& io_tm, const MgMat3D& i_tn)				// *=
{
	return MGeo::MatMultEqual2( io_tm, i_tn);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D = MgVect2D * MgMat3D;
//
//					   | m11 m12 m13 |
//	| px  py  1  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |     
//
inline	MgVect2D operator * ( const MgVect2D& i_pt, const MgMat3D& i_tm)		// *	座標変換
{
	return MGeo::MatMultPt22( i_pt, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D *= MgMat3D;
//
//										  | m11 m12 m13 |
//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 m23 |
//				   						  | m31 m32 m33 |
//
inline	MgVect2D operator *= ( MgVect2D& io_pt, const MgMat3D& i_tm)			// *=	座標変換
{
	return MGeo::MatMultEqualPt22( io_pt, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D = MgULine2D*  MgMat3D;
//
//	| px  py  1  |     | m11 m12 m13 |
//	| vx  vy  0  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |
//
inline	MgULine2D operator * ( const MgULine2D& i_uln, const MgMat3D& i_tm)	// *	座標変換
{
	return MGeo::MatMultULn22( i_uln, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D* = MgMat3D;
//
//	| px  py  1  |     | px  py  1  |     | m11 m12 m13 |
//	| vx  vy  0  |  =  | vx  vy  1  |  X  | m21 m22 m23 |
//			             				  | m31 m32 m33 |
//
inline	MgULine2D operator *= ( MgULine2D& io_uln, const MgMat3D& i_tm)		// *=	座標変換
{
	return MGeo::MatMultEqualULn22( io_uln, i_tm);
}

//===============( ２次元座標変換マトリックスで３次元座標処理 )==============
//
//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect3D2 = MgVect3D1 * MgMat3D1;
//
//						  | m11 m12 0 m13 |     
//	| px  py  pz  1 |  X  | m21 m22 0 m23 |
//						  |  0   0  1  0  |
//						  | m31 m32 0 m33 |
//
inline	MgVect3D operator * ( const MgVect3D& i_Pt, const MgMat3D& i_tm)		// *	座標変換
{
	return MGeo::MatMultPt32( i_Pt, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect3D *= MgMat3D;
//
//						 						| m11 m12 0 m13 |
//	| px  py  pz  1 |  =  | px  py  pz  1 |  X  | m21 m22 0 m23 |
//			   									|  0   0  1  0  |
//			   									| m31 m32 0 m33 |
//
inline	MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat3D& i_tm)			// *=	座標変換

{
	return MGeo::MatMultEqualPt32( io_Pt, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D = MgULine2D*  MgMat3D;
//
//	| px  py  pz  1 |	  | m11 m12 0 m13 |
//	| vx  vy  vz  1 |  X  | m21 m22 0 m23 |
//						  |  0   0  1  0  |
//			   			  | m31 m32 0 m33 |
//
inline MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat3D& i_tm)		// *	座標変換
{
	return MGeo::MultULn32( i_ULn, i_tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D* = MgMat3D;
//
//	| px  py  pz  1 |     | px  py  pz  1 |		| m11 m12 0 m13 |
//	| vx  vy  vz  1 |  =  | vx  vy  vz  1 |  X  | m21 m22 0 m23 |
//												|  0   0  1  0  |
//				 				   				| m31 m32 0 m33 |
//
inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat3D& i_tm)			// *=	座標変換
{
	return MGeo::MatMultEqualULn32( io_ULn, i_tm);
}

//===========================================================================
//
//	３Ｄ座標変換マトリックスの計算
//
//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat4D_3 = MgMat4D_1 + MgMat4D_2;
//
//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline	MgMat4D operator + ( const MgMat4D& i_Tm, const MgMat4D& i_Tn)			// +
{
	return MGeo::MatPlus3( i_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat4D += MgMat4D;
//
//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline	MgMat4D operator += ( MgMat4D& io_Tm, const MgMat4D& i_Tn)				// +=
{
	return MGeo::MatPlusEqual3( io_Tm, i_Tn);
}	

//===========================================================================
//	処理内容
//		負の座標変換マトリックスを作成
//
//	使用法
//		MgMat4D_2 = - MgMat4D_1;
//
//	  | m11 m12 m13 m14 |
//	- | m21 m22 m23 m24 |
//	  | m31 m32 m33 m34 |
//	  | m41 m42 m43 m44 |     
//
inline	MgMat4D operator - ( const MgMat4D& i_Tm)								// -
{
	return MGeo::MatSingleMinus3( i_Tm);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat4D_3 = MgMat4D_1 - MgMat4D_2;
//
//	  | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
//	  | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	  | m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline	MgMat4D operator - ( const MgMat4D& i_Tm, const MgMat4D& i_Tn)			// -
{
	return MGeo::MatMinus3( i_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat4D -= MgMat4D;
//
//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline MgMat4D operator -= ( MgMat4D& io_Tm, const MgMat4D& i_Tn)				// -=
{
	return MGeo::MatMinusEqual3( io_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//
//	使用法
//		MgMat4D_3 = MgMat4D_1 * MgMat4D_2;
//
//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline MgMat4D operator * ( const MgMat4D& i_Tm, const MgMat4D& i_Tn)			// *
{
	return MGeo::MatMult3( i_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//
//	使用法
//		MgMat4D *= MgMat4D;
//
//	| m11 m12 m13 m14 |     | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline MgMat4D operator *= ( MgMat4D& io_Tm, const MgMat4D& i_Tn)
{
	return MGeo::MatMultEqual3( io_Tm, i_Tn);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgMat4D_2 = MgVect2D * MgMat4D_1;
//
//						    | m11 m12 m13 m14 |
//	| px  py  0   1   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
inline MgVect2D operator * ( const MgVect2D& i_Pt, const MgMat4D& i_Tm)		// 座標変換
{
	return MGeo::MatMultPt23( i_Pt, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgVect2D *= MgMat4D;
//
//						     					    | m11 m12 m13 m14 |
//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 m24 |
//	           									    | m31 m32 m33 m34 |
//	           									    | m41 m42 m43 m44 |
//
inline MgVect2D operator *= ( MgVect2D& io_Pt, const MgMat4D& i_Tm)			// 座標変換
{
	return MGeo::MatMultEqualPt23( io_Pt, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D_2 = MgVect3D_1 * MgMat4D;
//
//	 					    | m11 m12 m13 m14 |
//	| px  py  pz  1   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
inline MgVect3D operator * ( const MgVect3D& i_Pt, const MgMat4D& i_Tm)		// 座標変換
{
	return MGeo::MatMultPt33( i_Pt, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D *= MgMat4D;
//
//							 					    | m11 m12 m13 m14 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
//												    | m31 m32 m33 m34 |
//												    | m41 m42 m43 m44 |
//
inline MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat4D& i_Tm)			// 座標変換
{
	return MGeo::MatMultEqualPt33( io_Pt, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgULine3D_2 = MgULine3D_1 * MgMat4D;
//
//	| px  py  pz  1   |     | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//							| m31 m32 m33 m34 |
//							| m41 m42 m43 m44 |
//
inline MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat4D& i_Tm)		// 座標変換
{
	return MGeo::MatMultULn33( i_ULn, i_Tm);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D *= MgMat4D;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//													| m31 m32 m33 m34 |
//													| m41 m42 m43 m44 |
//
inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat4D& i_Tm)			// 座標変換
{
	return MGeo::MatMultEqualULn33( io_ULn, i_Tm);
}

//===========================================================================
//		平面 形状演算
//
inline MgPlane3D MgPlane3DC(									// ３点より平面の方程式の係数と定数を求める（正規化）
					const	MgPoint3D*	i_ppt)
						{ return MGeo::Plane3CPPt( i_ppt);}

inline MgPlane3D MgPlane3DC(									// ３点より平面の方程式の係数と定数を求める（正規化）
					const	MgPoint3D&	i_p0,
					const	MgPoint3D&	i_p1,
					const	MgPoint3D&	i_p2)
						{ return MGeo::Plane3C3Pt( i_p0, i_p1, i_p2);}

inline MgPlane3D MgPlane3DC(									// 多角形より平面の方程式の係数と定数を求める（正規化）
					const	MgPolyg3D&	i_pg)
						{ return MGeo::Plane3CPg( i_pg);}

inline MgPlane3D MgPlane3DC(									// 始点と終点の２点と勾配より平面の方程式の係数と定数を求める（正規化）
					const	MgPoint2D&	i_p1,
					const	MgPoint2D&	i_p2,
							MREAL		i_rkb,
							MREAL		i_z = 0.)
						{ return MGeo::Plane3C2Pt2F( i_p1, i_p2, i_rkb, i_z);}

inline MgPlane3D MgPlane3DC(									// 線分と勾配より平面の方程式の係数と定数を求める（正規化）
					const	MgLine2D&	i_ln1,
							MREAL		i_rkb,
							MREAL		i_z = 0.)
						{ return MGeo::Plane3CLn2F( i_ln1, i_rkb, i_z);}
//
//===========================================================================
//		平面の方程式の係数と定数を正規化した平面を求める
//		ax+by+cz+d=0	(a*a+b*b+c*c=1.0)
//
inline MgPlane3D	MgNorm(							// (  O) 正規化後の３次元平面
					const	MgPlane3D&	i_pl)		// (I  ) ３次元平面
						{ return MGeo::NormPln( i_pl);}
//
//===========================================================================
//		MgPlane3Dを使用のインライン関数
//	
inline MgPoint3D::MgPoint3D(									// ２次元→３次元
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ x = i_v1.x; y = i_v1.y; z = i_Pln.GetZ( i_v1);} 

//======================( ３次元 )==============================
//		３次元ベクトル演算
inline MgVect3D MgVect3DC(										// ２次元→３次元
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ MgVect3D Vto; Vto.x = i_v1.x; Vto.y = i_v1.y;
									   Vto.z = i_Pln.GetZ( i_v1); return Vto;} 
inline MgPoint3D MgPoint3D::Set(								// ２次元→３次元
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ x = i_v1.x; y = i_v1.y; z = i_Pln.GetZ( i_v1); return *this;} 

inline MgULine3D MgULine3DC(									// ２次元→３次元
					const	MgULine2D&	i_uln,
					const	MgPlane3D&	i_Pln,
							MREAL	i_Tol = g_gTol.D)
						{ MgULine3D ULno; ULno.p.x = i_uln.p.x; ULno.p.y = i_uln.p.y;
										 ULno.p.z = i_Pln.GetZ( i_uln.p);
						  ULno.v = MgVect3DC( i_uln.v, - ( i_Pln.v.x * i_uln.v.x + i_Pln.v.y * i_uln.v.y) / i_Pln.v.z);
						  ULno.v.SetUnitize( i_Tol); return ULno;} 

inline MgULine3D MgULine3D::Set(								// ２次元→３次元
					const	MgULine2D&	i_uln,
					const	MgPlane3D&	i_Pln,
							MREAL	i_Tol)
						{ p.x = i_uln.p.x; p.y = i_uln.p.y; p.z = i_Pln.GetZ( i_uln.p);
						  v = MgVect3DC( i_uln.v, - ( i_Pln.v.x * i_uln.v.x + i_Pln.v.y * i_uln.v.y) / i_Pln.v.z);
						  v.SetUnitize( i_Tol); return *this;} 
	
inline MgLine3D MgLine3DC(										// ２次元→３次元
					const	MgLine2D&	i_ln,
					const	MgPlane3D&	i_Pln)
						{ MgLine3D Lno; Lno.p[0].x = i_ln.p[0].x; Lno.p[0].y = i_ln.p[0].y;
									   Lno.p[0].z = i_Pln.GetZ( i_ln.p[0]);
									   Lno.p[1].x = i_ln.p[1].x; Lno.p[1].y = i_ln.p[1].y;
									   Lno.p[0].z = i_Pln.GetZ( i_ln.p[1]); return Lno;}

inline MgLine3D MgLine3D::Set(									// ２次元→３次元
					const	MgLine2D&	i_ln,
					const	MgPlane3D&	i_Pln)
						{ p[0].x = i_ln.p[0].x; p[0].y = i_ln.p[0].y; p[0].z = i_Pln.GetZ( i_ln.p[0]);
						  p[1].x = i_ln.p[1].x; p[1].y = i_ln.p[1].y; p[0].z = i_Pln.GetZ( i_ln.p[1]);
						  return *this;}

inline MINT SZMgPlane3D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgPlane3D));}

inline MINT WSZMgPlane3D( MINT i_sz = 1) { return  ( i_sz * (MINT)sizeof( MgPlane3D) / SZMINT());}

} // namespace MC
