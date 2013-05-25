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

#include "MgMatD.h"
/*
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
*/
namespace MC
{
/*
class DLL_EXPORT_GEO MGeo
{
public:
	//
	//======================( ２次元、３次元 )==============================
	//	２次元、３次元座標変換マトリックス
	//
	//======================( ２次元 )==============================
	//		原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat2E Mat2ERot( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2ERotV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ２次元 )==============================
	//		原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat2E Mat2ERotRev( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2ERotRevV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＸＹ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3E Mat3ERotZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＸＹ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat3E Mat3ERotRevZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotRevZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＹＺ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3E Mat3ERotTX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return  Mat3ERotTXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＹＺ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat3E Mat3ERotRevX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotRevXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3E Mat3ERotY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3E Mat3ERotRevY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotRevYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}
*/

//======================( ２次元、３次元 )==============================
//	２次元、３次元座標変換マトリックス
//
//===========================================================================
//	処理内容
//	    座標変換マトリックスの加算
//
//	使用法
//		MgMat2E = MgMat2E1 + MgMat2E2;
//
//	| m11 m12 0 |     | n11 n12 0 |
//	| m21 m22 0 |  +  | n21 n22 0 |
//	| m31 m32 1 |     | n31 n32 1 |
//
inline MgMat2E operator + ( const MgMat2E& i_mt, const MgMat2E& i_mt2)			// +
{
	return MGeo::Mat2EPlus( i_mt, i_mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat2E1 += MgMat2E2;
//
//	| m11 m12 0 |     | m11 m12 0 |     | n11 n12 0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  +  | n21 n22 0 |
//	| m31 m32 1 |     | m31 m32 1 |     | n31 n32 1 |
//
inline	MgMat2E operator += ( MgMat2E& io_mt, const MgMat2E& i_mt2)				// +=
{
	return MGeo::Mat2EPlusEqual( io_mt, i_mt2);
}

//===========================================================================
//	処理内容
//		負の座標変換マトリックスを作成
//
//	使用法
//		MgMat2E2 = - MgMat2E1;
//
//	  | m11 m12 0 |
//	- | m21 m22 0 |
//	  | m31 m32 1 |
//
inline	MgMat2E operator - ( const MgMat2E& i_mt)								// -
{
	return MGeo::Mat2ESingleMinus( i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat2E = MgMat2E1 - MgMat2E2;
//
//	  | m11 m12 0 |     | n11 n12 0 |
//	  | m21 m22 0 |  -  | n21 n22 0 |
//	  | m31 m32 1 |     | n31 n32 1 |
//
inline	MgMat2E operator - ( const MgMat2E& i_mt, const MgMat2E& i_mt2)			// -
{
	return MGeo::Mat2EMinus( i_mt, i_mt2);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの引算
//
//	使用法
//		MgMat2E1 -= MgMat2E2;
//
//	| m11 m12 0 |    | m11 m12 0 |     | n11 n12 0 |
//	| m21 m22 0 |  = | m21 m22 0 |  -  | n21 n22 0 |
//	| m31 m32 1 |    | m31 m32 1 |     | n31 n32 1 |
//
inline	MgMat2E operator -= ( MgMat2E& io_mt, const MgMat2E& i_mt2)				// -=
{
	return MGeo::Mat2EMinusEqual( io_mt, i_mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
//
//	使用法
//		MgMat2E = MgMat2E1 * MgMat2E2;
//
//	| m11 m12 0 |     | n11 n12 0 |
//	| m21 m22 0 |  X  | n21 n22 0 |
//	| m31 m32 1 |     | n31 n32 1 |
//
inline	MgMat2E operator * ( const MgMat2E& i_mt, const MgMat2E& i_mt2)			// *
{
	return MGeo::Mat2EMult( i_mt, i_mt2);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスのかけ算
//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
//
//	使用法
//		MgMat2E2 *= MgMat2E1;
//
//	| m11 m12 0 |     | m11 m12 0 |     | n11 n12 0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  | n21 n22 0 |
//	| m31 m32 1 |     | m31 m32 1 |     | n31 n32 1 |
//
inline	MgMat2E operator *= ( MgMat2E& io_mt, const MgMat2E& i_mt2)				// *=
{
	return MGeo::Mat2EMultEqual( io_mt, i_mt2);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat2E = MgMat2E1 + MgVect2D1;
//
//	| m11 m12 0 |     |  1  0  0 |
//	| m21 m22 0 |  X  |  0  1  0 |
//	| m31 m32 1 |     |  vx vy 1 |
//
inline	MgMat2E operator + ( const MgMat2E& i_m1, const MgVect2D& i_v)			// +	平行移動
{
	MgMat2E mw;
	mw = i_m1;
	mw += i_v;
	return mw;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat2E = MgMat2E1 + MgPoint2D1;
//
//	| m11 m12 0 |     |  1  0  0 |
//	| m21 m22 0 |  X  |  0  1  0 |
//	| m31 m32 1 |     |  px py 1 |
//
inline	MgMat2E operator + ( const MgMat2E& i_m1, const MgPoint2D& i_pt)		// +	平行移動
{ 
	return i_m1 + (MgVect2D&)i_pt;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat2E1 += MgVect2D1;
//
//	| m11 m12 0 |     | m11 m12 0 |     |  1  0  0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0  1  0 |
//	| m31 m32 1 |     | m31 m32 1 |     |  vx vy 1 |
//
inline	MgMat2E operator += ( MgMat2E& io_m1, const MgVect2D& i_v)				// +=	平行移動
{
	io_m1.m[2][0] += i_v.x;
	io_m1.m[2][1] += i_v.y;
	return io_m1;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat2E1 += MgPoint2D1;
//
//	| m11 m12 0 |     | m11 m12 0 |     |  1  0  0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0  1  0 |
//	| m31 m32 1 |     | m31 m32 1 |     |  px py 1 |
//
inline	MgMat2E operator += ( MgMat2E& io_m1, const MgPoint2D& i_pt)			// +=	平行移動
{
	return io_m1 += (MgVect2D&)i_pt;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに逆方向に移動するマトリックスを作成
//
//	使用法
//		MgMat2E = MgMat2E1 - MgVect2D1;
//
//	| m11 m12 0 |     |  1   0  0 |
//	| m21 m22 0 |  X  |  0   1  0 |
//	| m31 m32 1 |     | -vx -vy 1 |
//
inline	MgMat2E operator - ( const MgMat2E& i_m1, const MgVect2D& i_pt)			// -	平行移動
{ 
	MgMat2E mw;
	mw = i_m1;
	mw -= i_pt;
	return mw;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに逆方向に移動するマトリックスを作成
//
//	使用法
//		MgMat2E = MgMat2E1 - MgPoint2D1;
//
//	| m11 m12 0 |     |  1   0  0 |
//	| m21 m22 0 |  X  |  0   1  0 |
//	| m31 m32 1 |     | -px -py 1 |
//
inline	MgMat2E operator - ( const MgMat2E& i_m1, const MgPoint2D& i_pt)		// -	平行移動
{ 
	return i_m1 - (MgVect2D&)i_pt;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに逆方向に移動するマトリックスを作成
//
//	使用法
//		MgMat2E1 -= MgVect2D1;
//
//	| m11 m12 0 |     | m11 m12 0 |     |  1   0  0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0   1  0 |
//	| m31 m32 1 |     | m31 m32 1 |     | -vx -vy 1 |
//
inline	MgMat2E operator -= ( MgMat2E& i_m1, const MgVect2D& i_v)				// -=	平行移動
{
	i_m1.m[2][0] -= i_v.x;
	i_m1.m[2][1] -= i_v.y;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに逆方向に移動するマトリックスを作成
//
//	使用法
//		MgMat2E1 -= MgPoint2D1;
//
//	| m11 m12 0 |     | m11 m12 0 |     |  1   0  0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0   1  0 |
//	| m31 m32 1 |     | m31 m32 1 |     | -px -py 1 |
//
inline	MgMat2E operator -= ( MgMat2E& i_m1, const MgPoint2D& i_pt)				// -=	平行移動
{ 
	return i_m1 -= (MgVect2D&)i_pt;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgPoint2D = MgPoint2D * MgMat2E;
//
//					   | m11 m12 0 |
//	| px  py  1  |  X  | m21 m22 0 |
//					   | m31 m32 1 |     
//
inline	MgPoint2D operator * ( const MgPoint2D& i_pt, const MgMat2E& i_mt)		// *	座標変換
{
	return MGeo::Mat2EMultPoint2D( i_pt, i_mt);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D = MgVect2D * MgMat2E;
//
//					   | m11 m12 0 |
//	| vx  vy  0  |  X  | m21 m22 0 |
//					   | m31 m32 1 |     
//
inline	MgVect2D operator * ( const MgVect2D& i_pt, const MgMat2E& i_mt)		// *	座標変換
{
	return MGeo::Mat2EMultVect2D( i_pt, i_mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgLine2D = MgLine2D * MgMat2E;
//
//	| px  py  1   |     | m11 m12 0 |
//	| px  py  1   |  X  | m21 m22 0 |
//						| m31 m32 1 |
//
inline	MgLine2D operator * ( const MgLine2D& i_ln, const MgMat2E& i_mt)		// *	座標変換
{ 
//S	MgLine2D ln;
//	ln.p[0] = i_ln.p[0] * i_mt;
//	ln.p[1] = i_ln.p[1] * i_mt;
//	return ln;
	return MGeo::Mat2EMultLine2D( i_ln, i_mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgSLine2D = MgSLine2D * MgMat2E;
//
//	| px  py  1   |     | m11 m12 0 |
//	| vx  vy  0   |  X  | m21 m22 0 |
//						| m31 m32 1 |
//
inline	MgSLine2D operator * ( const MgSLine2D& i_sln, const MgMat2E& i_mt)		// *	座標変換
{ 
//S	MgSLine2D sln;
//	sln.p = i_sln.p * i_mt;
//	sln.v = i_sln.v * i_mt;
//	return i_sln;
	return MGeo::Mat2EMultSLine2D( i_sln, i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D *= MgMat2E;
//
//										  | m11 m12 0 |
//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 0 |
//				   						  | m31 m32 1 |
//
inline	MgPoint2D operator *= ( MgPoint2D& io_pt, const MgMat2E& i_mt)			// *=	座標変換
{
	return MGeo::Mat2EMultEqualPoint2D( io_pt, i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D *= MgMat2E;
//
//										  | m11 m12 0 |
//	| vx  vy  0  |  =  | vx  vy  0  |  X  | m21 m22 0 |
//				   						  | m31 m32 1 |
//
inline	MgVect2D operator *= ( MgVect2D& io_pt, const MgMat2E& i_mt)			// *=	座標変換
{
	return MGeo::Mat2EMultEqualVect2D( io_pt, i_mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgLine2D *= MgMat2E;
//
//	| px  py  1   |     | px  py  1   |     | m11 m12 0 |
//	| px  py  1   |  =  | px  py  1   |  X  | m21 m22 0 |
//											| m31 m32 1 |
//
inline	MgLine2D operator *= ( MgLine2D& io_ln, const MgMat2E& i_mt)				// *=	座標変換
{ 
//S	io_ln.p[0] *= i_mt;
//	io_ln.p[1] *= i_mt;
//	return io_ln;
	return MGeo::Mat2EMultEqualLine2D( io_ln, i_mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgSLine2D *= MgMat2E;
//
//	| px  py  1   |     | px  py  1   |     | m11 m12 0 |
//	| vx  vy  0   |  =  | vx  vy  0   |  X  | m21 m22 0 |
//											| m31 m32 1 |
//
inline	MgSLine2D operator *= ( MgSLine2D& io_sln, const MgMat2E& i_mt)			// *=	座標変換
{ 
//S	io_sln.p *= i_mt;
//	io_sln.v *= i_mt;
//	return io_sln;
	return MGeo::Mat2EMultEqualSLine2D( io_sln, i_mt);
}

//===============( ２次元座標変換マトリックスで３次元座標処理 )==============
//
//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgPoint3D = MgPoint3D1 * MgMat2E1;
//
//						  | m11 m12 0 0 |     
//	| px  py  pz  1 |  X  | m21 m22 0 0 |
//						  |  0   0  1 0 |
//						  | m31 m32 0 1 |
//
inline	MgPoint3D operator * ( const MgPoint3D& i_Pt, const MgMat2E& i_mt)		// *	座標変換
{
	return MGeo::Mat2EMultPoint3D( i_Pt, i_mt);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect3D2 = MgVect3D1 * MgMat2E1;
//
//						  | m11 m12 0 0 |     
//	| vx  vy  vz  0 |  X  | m21 m22 0 0 |
//						  |  0   0  1 0 |
//						  | m31 m32 0 1 |
//
inline	MgVect3D operator * ( const MgVect3D& i_Vt, const MgMat2E& i_mt)		// *	座標変換
{
	return MGeo::Mat2EMultVect3D( i_Vt, i_mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgLine3D = MgLine3D1 * MgMat3E;
//
//	| px  py  pz  1   |     | m11 m12  0  0 |
//	| px  py  pz  1   |  X  | m21 m22  0  0 |
//							|  0   0   1  0 |
//							| m31 m32  0  1 |
//
inline	MgLine3D operator * ( const MgLine3D& i_Ln, const MgMat2E& i_mt)		// *	座標変換
{
//S	MgLine3D Ln;
//	Ln.p[0] = i_Ln.p[0] * i_mt;
//	Ln.p[1] = i_Ln.p[1] * i_mt;
//	return Ln;
	return MGeo::Mat2EMultLine3D( i_Ln, i_mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgSLine3D = MgSLine3D1 * MgMat3E;
//
//	| px  py  pz  1   |     | m11 m12  0  0 |
//	| vx  vy  vz  0   |  X  | m21 m22  0  0 |
//							|  0   0   1  0 |
//							| m31 m32  0  1 |
//
inline	MgSLine3D operator * ( const MgSLine3D& i_SLn, const MgMat2E& i_mt)		// *	座標変換
{
//S	MgSLine3D SLn;
//	SLn.p = i_SLn.p * i_mt;
//	SLn.v = i_SLn.v * i_mt;
//	return SLn;
	return MGeo::Mat2EMultSLine3D( i_SLn, i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgPoint3D *= MgMat2E;
//
//						 						| m11 m12 0 0 |
//	| px  py  pz  1 |  =  | px  py  pz  1 |  X  | m21 m22 0 0 |
//			   									|  0   0  1 0 |
//			   									| m31 m32 0 1 |
//
inline	MgPoint3D operator *= ( MgPoint3D& io_Pt, const MgMat2E& i_mt)			// *=	座標変換

{
	return MGeo::Mat2EMultEqualPoint3D( io_Pt, i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect3D *= MgMat2E;
//
//						 						| m11 m12 0 0 |
//	| vx  vy  vz  0 |  =  | vx  vy  vz  0 |  X  | m21 m22 0 0 |
//			   									|  0   0  1 0 |
//			   									| m31 m32 0 1 |
//
inline	MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat2E& i_mt)			// *=	座標変換

{
	return MGeo::Mat2EMultEqualVect3D( io_Pt, i_mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgLine3D *= MgMat3E;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12  0  0 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22  0  0 |
//													|  0   0   1  0 |
//													| m31 m32  0  1 |
//
inline	MgLine3D operator *= ( MgLine3D& io_Ln, const MgMat2E& i_mt)			// *=	座標変換
{
//S	io_Ln.p[0] *= i_mt;
//	io_Ln.p[1] *= i_mt;
//	return io_Ln;
	return MGeo::Mat2EMultLine3D( io_Ln, i_mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgSLine3D *= MgMat3E;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12  0  0 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22  0  0 |
//													|  0   0   1  0 |
//													| m31 m32  0  1 |
//
inline	MgSLine3D operator *= ( MgSLine3D& io_SLn, const MgMat2E& i_mt)			// *=	座標変換
{ 
//S	io_SLn.p *= i_mt;
//	io_SLn.v *= i_mt;
//	return io_SLn;
	return MGeo::Mat2EMultEqualLine3D( io_SLn, i_mt);
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
//		MgMat3E_3 = MgMat3E_1 + MgMat3E_2;
//
//	| m11 m12 m13 0 |     | n11 n12 n13 0 |
//	| m21 m22 m23 0 |  +  | n21 n22 n23 0 |
//	| m31 m32 m33 0 |     | n31 n32 n33 0 |
//	| m41 m42 m43 1 |     | n41 n42 n43 1 |    
//
inline	MgMat3E operator + ( const MgMat3E& i_Mt, const MgMat3E& i_Mt2)			// +
{
	return MGeo::Mat3EPlus( i_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat3E += MgMat3E;
//
//	| m11 m12 m13 0 |	  | m11 m12 m13 0 |     | n11 n12 n13 0 |
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  +  | n21 n22 n23 0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     | n31 n32 n33 0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | n41 n42 n43 1 |     
//
inline	MgMat3E operator += ( MgMat3E& io_Mt, const MgMat3E& i_Mt2)				// +=
{
	return MGeo::Mat3EPlusEqual( io_Mt, i_Mt2);
}	

//===========================================================================
//	処理内容
//		負の座標変換マトリックスを作成
//
//	使用法
//		MgMat3E_2 = - MgMat3E_1;
//
//	  | m11 m12 m13 0 |
//	- | m21 m22 m23 0 |
//	  | m31 m32 m33 0 |
//	  | m41 m42 m43 1 |     
//
inline	MgMat3E operator - ( const MgMat3E& i_Mt)								// -
{
	return MGeo::Mat3ESingleMinus( i_Mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat3E_3 = MgMat3E_1 - MgMat3E_2;
//
//	  | m11 m12 m13 0 |     | n11 n12 n13 0 |
//	  | m21 m22 m23 0 |  -  | n21 n22 n23 0 |
//	  | m31 m32 m33 0 |     | n31 n32 n33 0 |
//	  | m41 m42 m43 1 |     | n41 n42 n43 1 |    
//
inline	MgMat3E operator - ( const MgMat3E& i_Mt, const MgMat3E& i_Mt2)			// -
{
	return MGeo::Mat3EMinus( i_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat3E -= MgMat3E;
//
//	| m11 m12 m13 0 |	  | m11 m12 m13 0 |     | n11 n12 n13 0 |
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  -  | n21 n22 n23 0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     | n31 n32 n33 0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | n41 n42 n43 1 |     
//
inline MgMat3E operator -= ( MgMat3E& io_Mt, const MgMat3E& i_Mt2)				// -=
{
	return MGeo::Mat3EMinusEqual( io_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//
//	使用法
//		MgMat3E_3 = MgMat3E_1 * MgMat3E_2;
//
//	| m11 m12 m13 0 |     | n11 n12 n13 0 |
//	| m21 m22 m23 0 |  X  | n21 n22 n23 0 |
//	| m31 m32 m33 0 |     | n31 n32 n33 0 |
//	| m41 m42 m43 1 |     | n41 n42 n43 1 |    
//
inline MgMat3E operator * ( const MgMat3E& i_Mt, const MgMat3E& i_Mt2)			// *
{
	return MGeo::Mat3EMult( i_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//
//	使用法
//		MgMat3E *= MgMat3E;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     | n11 n12 n13 0 |
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  | n21 n22 n23 0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     | n31 n32 n33 0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | n41 n42 n43 1 |     
//
inline MgMat3E operator *= ( MgMat3E& io_Mt, const MgMat3E& i_Mt2)
{
	return MGeo::Mat3EMultEqual( io_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat3E = MgMat3E1 + Vect3D1;
//
//	| m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | vx vy vz 1 |
//
inline MgMat3E operator + ( const MgMat3E& i_M1, const MgVect3D& i_Pt)			// +	平行移動
{
	MgMat3E Mw;
	Mw = i_M1;
	Mw += i_Pt;
	return Mw;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat3E = MgMat3E1 + Point3D1;
//
//	| m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | px py pz 1 |
//
inline MgMat3E operator + ( const MgMat3E& i_M1, const MgPoint3D& i_Pt)			// +	平行移動
{
	return i_M1 + (MgVect3D&)i_Pt;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat3E1 += Vect3D1;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | vx vy vz 1 |
//
inline MgMat3E operator += ( MgMat3E& io_M1, const MgVect3D& i_Vt)				// +=	平行移動
{
	io_M1.m[3][0] += i_Vt.x;
	io_M1.m[3][1] += i_Vt.y;
	io_M1.m[3][2] += i_Vt.z;
	return io_M1;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat3E1 += Point3D1;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | px py pz 1 |
//
inline MgMat3E operator += ( MgMat3E& io_M1, const MgPoint3D& i_Pt)				// +=	平行移動
{
	return io_M1 += (MgVect3D&)i_Pt;
} 

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat3E = MgMat3E1 + Vect3D1;
//
//	| m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | vx vy vz 1 |
//
inline MgMat3E operator - ( const MgMat3E& i_M1, const MgVect3D& i_Vt)				// -	平行移動
{
	MgMat3E Mw = i_M1;
	Mw -= i_Vt;
	return Mw;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat3E = MgMat3E1 + Point3D1;
//
//	| m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | px py pz 1 |
//
inline MgMat3E operator - ( const MgMat3E& i_M1, const MgPoint3D& i_Pt)				// -	平行移動
{
	return i_M1 - (MgVect3D&)i_Pt;
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat3E1 += Vect3D1;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     |  1   0   0  0 |		
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  |  0   1   0  0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     |  0   0   1  0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | -vx -vy -vz 1 |
//
inline MgMat3E operator -= ( MgMat3E& io_M1, const MgVect3D& i_Vt)					// -=	平行移動
{
	io_M1.m[3][0] -= i_Vt.x;
	io_M1.m[3][1] -= i_Vt.y;
	io_M1.m[3][2] -= i_Vt.z;
	return io_M1;
} 
//===========================================================================
//	処理内容
//	    座標変換マトリックスの平行移動
//	    座標変換マトリックスによる変換後に、さらに移動するマトリックスを作成
//
//	使用法
//		MgMat3E1 += Point3D1;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     |  1   0   0  0 |		
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  |  0   1   0  0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     |  0   0   1  0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | -px -py -pz 1 |
//
inline MgMat3E operator -= ( MgMat3E& io_M1, const MgPoint3D& i_Pt)					// -=	平行移動
{
	return io_M1 -= (MgVect3D&)i_Pt;
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgPoint2D = MgPoint2D * MgMat3E_1;
//
//						    | m11 m12 m13 0 |
//	| px  py  0   1   |  X  | m21 m22 m23 0 |
//						    | m31 m32 m33 0 |
//						    | m41 m42 m43 1 |
//
inline MgPoint2D operator * ( const MgPoint2D& i_Pt, const MgMat3E& i_Mt)		// 座標変換
{
	return MGeo::Mat3EMultPoint2D( i_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgVect2D = MgVect2D * MgMat3E_1;
//
//						    | m11 m12 m13 0 |
//	| vx  vy  0   0   |  X  | m21 m22 m23 0 |
//						    | m31 m32 m33 0 |
//						    | m41 m42 m43 1 |
//
inline MgVect2D operator * ( const MgVect2D& i_Pt, const MgMat3E& i_Mt)		// 座標変換
{
	return MGeo::Mat3EMultVect2D( i_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgLine2D = MgLine2D1 * MgMat3E1;
//
//	| px  py  0   1   |     | m11 m12 m13 0 |
//	| px  py  0   1   |  X  | m21 m22 m23 0 |
//							| m31 m32 m33 0 |
//							| m41 m42 m43 1 |
//
inline MgLine2D operator * ( const MgLine2D& i_ln, const MgMat3E &i_Mt)			// 座標変換
{
//S	MgLine2D ln;
//	ln.p[0] = i_ln.p[0] * i_Mt;
//	ln.p[1] = i_ln.p[1] * i_Mt;
//	return ln;
	return MGeo::Mat3EMultLine2D( i_ln, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgSLine2D = MgSLine2D1 * MgMat3E1;
//
//	| px  py  0   1   |     | m11 m12 m13 0 |
//	| vx  vy  0   0   |  X  | m21 m22 m23 0 |
//							| m31 m32 m33 0 |
//							| m41 m42 m43 1 |
//
inline MgSLine2D operator * ( const MgSLine2D& i_sln, const MgMat3E& i_Mt)		// 座標変換
{
	return MGeo::Mat3EMultSLine2D( i_sln, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgPoint2D *= MgMat3E;
//
//						     					    | m11 m12 m13 0 |
//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 0 |
//	           									    | m31 m32 m33 0 |
//	           									    | m41 m42 m43 1 |
//
inline MgPoint2D operator *= ( MgPoint2D& io_Pt, const MgMat3E& i_Mt)			// 座標変換
{
	return MGeo::Mat3EMultEqualPoint2D( io_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgVect2D *= MgMat3E;
//
//						     					    | m11 m12 m13 0 |
//	| vx  vy  0   0   |  =  | vx  vy  0   0   |  X  | m21 m22 m23 0 |
//	           									    | m31 m32 m33 0 |
//	           									    | m41 m42 m43 1 |
//
inline MgVect2D operator *= ( MgVect2D& io_Pt, const MgMat3E& i_Mt)			// 座標変換
{
	return MGeo::Mat3EMultEqualVect2D( io_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgLine3D1 *= MgMat3E1;
//
//	| px  py  0   1   |     | px  py  0   1   |     | m11 m12 m13 0 |
//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 0 |
//													| m31 m32 m33 0 |
//													| m41 m42 m43 1 |
//
inline MgLine2D operator *= ( MgLine2D& io_ln, const MgMat3E &i_Mt)					// 座標変換
{
//S	io_ln.p[0] *= i_Mt;
//	io_ln.p[1] *= i_Mt;
//	return io_ln;
	return MGeo::Mat3EMultEqualLine2D( io_ln, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgSLine2D *= MgMat3E;
//
//	| px  py  0   1   |     | px  py  0   1   |     | m11 m12 m13 0 |
//	| vx  vy  0   0   |  =  | vx  vy  0   0   |  X  | m21 m22 m23 0 |
//													| m31 m32 m33 0 |
//													| m41 m42 m43 1 |
//
inline MgSLine2D operator *= ( MgSLine2D& io_sln, const MgMat3E& i_Mt)			// 座標変換
{
//S	io_sln.p *= i_Mt;
//	io_sln.v *= i_Mt;
//	return io_sln;
	return MGeo::Mat3EMultEqualSLine2D( io_sln, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgPoint3D_2 = MgPoint3D_1 * MgMat3E;
//
//	 					    | m11 m12 m13 0 |
//	| px  py  pz  1   |  X  | m21 m22 m23 0 |
//						    | m31 m32 m33 0 |
//						    | m41 m42 m43 1 |
//
inline MgPoint3D operator * ( const MgPoint3D& i_Pt, const MgMat3E& i_Mt)		// 座標変換
{
	return MGeo::Mat3EMultPoint3D( i_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D_2 = MgVect3D_1 * MgMat3E;
//
//	 					    | m11 m12 m13 0 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 0 |
//						    | m31 m32 m33 0 |
//						    | m41 m42 m43 1 |
//
inline MgVect3D operator * ( const MgVect3D& i_Pt, const MgMat3E& i_Mt)		// 座標変換
{
	return MGeo::Mat3EMultVect3D( i_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgLine3D = MgLine3D1 * MgMat3E1;
//
//	| px  py  pz  1   |     | m11 m12 m13 0 |
//	| px  py  pz  1   |  X  | m21 m22 m23 0 |
//							| m31 m32 m33 0 |
//							| m41 m42 m43 1 |
//
inline MgLine3D operator * ( const MgLine3D& i_Ln, const MgMat3E &i_Mt)			// 座標変換
{
//S	MgLine3D Ln;
//	Ln.p[0] = i_Ln.p[0] * i_Mt;
//	Ln.p[1] = i_Ln.p[1] * i_Mt;
//	return Ln;
	return MGeo::Mat3EMultLine3D( i_Ln, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgSLine3D = MgSLine3D1 * MgMat3E1;
//
//	| px  py  pz  1   |     | m11 m12 m13 0 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 0 |
//							| m31 m32 m33 0 |
//							| m41 m42 m43 1 |
//
inline MgSLine3D operator * ( const MgSLine3D& i_SLn, const MgMat3E& i_Mt)		// 座標変換
{
//S	MgSLine3D SLn;
//	SLn.p = i_SLn.p * i_Mt;
//	SLn.v = i_SLn.v * i_Mt;
//	return SLn;
	return MGeo::Mat3EMultSLine3D( i_SLn, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgPoint3D *= MgMat3E;
//
//							 					    | m11 m12 m13 0 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 0 |
//												    | m31 m32 m33 0 |
//												    | m41 m42 m43 1 |
//
inline MgPoint3D operator *= ( MgPoint3D& io_Pt, const MgMat3E& i_Mt)			// 座標変換
{
	return MGeo::Mat3EMultEqualPoint3D( io_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D *= MgMat3E;
//
//							 					    | m11 m12 m13 0 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 0 |
//												    | m31 m32 m33 0 |
//												    | m41 m42 m43 1 |
//
inline MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat3E& i_Mt)			// 座標変換
{
	return MGeo::Mat3EMultEqualVect3D( io_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgLine3D1 *= MgMat3E1;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 0 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 0 |
//													| m31 m32 m33 0 |
//													| m41 m42 m43 1 |
//
inline MgLine3D operator *= ( MgLine3D& io_Ln, const MgMat3E &i_Mt)					// 座標変換
{
//S	io_Ln.p[0] *= i_Mt;
//	io_Ln.p[1] *= i_Mt;
//	return io_Ln;
	return MGeo::Mat3EMultEqualLine3D( io_Ln, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgSLine3D *= MgMat3E;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 0 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 0 |
//													| m31 m32 m33 0 |
//													| m41 m42 m43 1 |
//
inline MgSLine3D operator *= ( MgSLine3D& io_SLn, const MgMat3E& i_Mt)			// 座標変換
{
//S	io_SLn.p *= i_Mt;
//	io_SLn.v *= i_Mt;
//	return io_SLn;
	return MGeo::Mat3EMultEqualSLine3D( io_SLn, i_Mt);
}

inline	void MgMat2E::Print( MCHAR* s)											// print
{
#ifdef LOGOUT
	MgMatPrint2( s);
#endif
}

} // namespace MC
