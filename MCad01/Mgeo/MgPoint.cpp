//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPoint.cpp
//
//		
//
//
//  K.Matsu           13/01/23    Created.
//==========================================================================================
//
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#include "MgDefine.h"
#include "MgTol.h"
#include "MgAngle.h"

#define DLL_EXPORT_POINT_DO

#include "MgPoint.h"

#define DLL_EXPORT_GEO_DO

#include "MgGeo.h"

namespace MC
{

//======================( ２次元 )==============================
//		2D点をトレースする
//
void MgPoint2D::Print(MCHAR* s) const				// Print
{
#ifdef LOGOUT
	MBLOGOUT( Mstr( "%s	MgPoint2D	: (%7.1f,%7.1f)\n"), s, x, y);
#endif
}

//======================( ２次元 )==============================
//		2Dベクトルを単位ベクトルに変換する
//
MgVect2D MgVect2D::SetUnitize( MREAL i_Tol)		//	(  O) 単位ベクトル
{
	MREAL	d1 = MGeo::LenVect2D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D Unitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	x *= d2;
	y *= d2;
	return *this;
}

//======================( ２次元 )==============================
// 点列の同一座標をつめる
int MGeo::PackSamePoint2D( MgPoint2D* io_pPt, int* io_pn)
{
	int iC1, iC2;
	int iN;
	bool bPack;
	if( *io_pn != 0) {
		bPack = false;
		iN = *io_pn;
		iC1 = 0;
		for ( iC2=1; iC2<iN; iC2++) {
			if( io_pPt[iC1] == io_pPt[iC2]) {
				bPack = true;
			} else {
				iC1++;
				if( bPack)
					memcpy( &io_pPt[iC1], &io_pPt[iC2], SZMgPoint2D());
			}
		}
		*io_pn = iC1 + 1;
	}
	return 0;
}

// 点列を逆順にする
int MGeo::ReversePoint2D( MgPoint2D* i_pPt, int i_n, MgPoint2D* o_pPt)
{
	int i1, i2;
	if( i_pPt == o_pPt) {
		for( i1=0,i2=i_n-1; i1<i2;i1++,i2--) {
			msSwap( o_pPt[i1], o_pPt[i2]);
		}
	} else {
		for( i1=0,i2=i_n-1; i2>=0; i1++,i2--) {
//E			memcpy( &o_pPt[i2], &i_pPt[i1], SZMgPoint2D());
			o_pPt[i2] = i_pPt[i1];
		}
	}
	return 0;
}

//======================( ２次元 )==============================
//		2Dベクトルの単位ベクトルを求める
//
MgVect2D MgVect2D::Unitize( MREAL i_Tol) const	//	(  O) 単位ベクトル
{
	MREAL	d1 = MGeo::LenVect2D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
    return	MgVect2D(x * d2, y * d2);
}

//======================( ２次元 )==============================
//		2Dベクトルをトレースする
//
void MgVect2D::Print(MCHAR* s) const				// Print
{
#ifdef LOGOUT
	MBLOGOUT( Mstr( "%s	MgVect2D	: (%7.1f,%7.1f)\n"), s, x, y);
#endif
}

//======================( ２次元 )==============================
//		2Dベクトルの単位ベクトルを求める
//
MgVect2D MGeo::UnitizeVect2D( const MgVect2D& i_v, MREAL i_Tol)		//	(  O) 単位ベクトル
{
	MREAL	d1 = MGeo::LenVect2D( i_v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
    return	MgVect2D( i_v.x * d2, i_v.y * d2);
}

//======================( ３次元 )==============================
//
MgVect3D MGeo::TaniVect3D( const MgVect3D& i_v, MREAL i_Tol)
{
	MgVect3D vo;
	MREAL	ax, ay, az;

	ax = MGeo::Abs( i_v.x);
	ay = MGeo::Abs( i_v.y);
	az = MGeo::Abs( i_v.z);
	vo.x = vo.y = vo.z = 1.;

	if (ax > ay && ax > az)	
		vo.x = - ( i_v.y + i_v.z) / i_v.x;
	else if ( ay >= ax && ay >= az)
		vo.y = - ( i_v.x + i_v.z) / i_v.y;
	else					 
		vo.z = - ( i_v.x + i_v.y) / i_v.z;

	return MGeo::UnitizeVect3D( vo, i_Tol);
}

//======================( ３次元 )==============================
//		点列の同一座標をつめる
//
int MGeo::PackSamePoint3D( MgPoint3D* io_pPt, int* io_pn)
{
	int iC1, iC2;
	int iN;
	bool bPack;
	if( *io_pn != 0) {
		bPack = false;
		iN = *io_pn;
		iC1 = 0;
		for ( iC2=1; iC2<iN; iC2++) {
			if( io_pPt[iC1] == io_pPt[iC2]) {
				bPack = true;
			} else {
				iC1++;
				if( bPack)
					memcpy( &io_pPt[iC1], &io_pPt[iC2], SZMgPoint2D());
			}
		}
		*io_pn = iC1 + 1;
	}
	return 0;
}


// 点列を逆順にする
int MGeo::ReversePoint3D( MgPoint3D* i_pPt, int i_n, MgPoint3D* o_pPt)
{
	int i1, i2;
	if( i_pPt == o_pPt) {
		for( i1=0,i2=i_n-1; i1<i2;i1++,i2--) {
			msSwap( o_pPt[i1], o_pPt[i2]);
		}
	} else {
		for( i1=0,i2=i_n-1; i2>=0; i1++,i2--) {
//E			memcpy( &o_pPt[i2], &i_pPt[i1], SZMgPoint3D());
			o_pPt[i2] = i_pPt[i1];
		}
	}
	return 0;
}
	// 点列から直線に対象位置の点列を求める
	static int SymmetryPointULine3D( MgPoint3D* i_pPt, int i_n, MgULine3D& uln, MgPoint3D* o_pPt);

//S //======================( ２次元 )==============================
//#ifdef _MgPoint2DA
//MgPoint2Da Norma( const MgPoint2D& i_p, MREAL i_Tol)
//{
//	MREAL	d1 = MgAbs(p);
////A		MBCHECK_ZEROVECT( d1, MBCstr( "MgPoint2DA Norma"), i_Tol);
//	MREAL	d2 = 1. / d1;
//    return MgPoint2Da( i_p.x * d2, i_p.y * d2, d1);
//}
//#endif

//======================( ３次元 )==============================
//		3D点をトレースする
//
void MgPoint3D::Print(MCHAR* s) const				// Print
{
#ifdef LOGOUT
	MBLOGOUT( Mstr( "%s 	MgPoint3D	: (%7.1f, %7.1f, %7.1f)\n"), s, x, y, z);
#endif
}

//======================( ３次元 )==============================
//		3Dベクトルを単位ベクトルに変換する
//
MgVect3D MgVect3D::SetUnitize( MREAL i_Tol)			//	(  O) 単位ベクトル
{
	MREAL	d1 = MGeo::LenVect3D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect3D Unitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	x *= d2;
	y *= d2;
	z *= d2;
	return *this;
}

//======================( ３次元 )==============================
//		3Dベクトルの単位ベクトルを求める
//
MgVect3D MgVect3D::Unitize( MREAL i_Tol) const		//	(  O) 単位ベクトル
{
	MREAL	d1= MGeo::LenVect3D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	return MgVect3D( x * d2, y * d2, z * d2);
}

//======================( ３次元 )==============================
//		3Dベクトルをトレースする
//
void MgVect3D::Print(MCHAR* s) const				// Print
{
#ifdef LOGOUT
	MBLOGOUT( Mstr( "%s 	MgVect3D	: (%7.1f, %7.1f, %7.1f)\n"), s, x, y, z);
#endif
}

//======================( ３次元 )==============================
//		3Dベクトルの単位ベクトルを求める
//
MgVect3D MGeo::UnitizeVect3D( const MgVect3D& i_v, MREAL i_Tol)	//	(  O) 単位ベクトル
{
	MREAL	d1= MGeo::LenVect3D( i_v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect3D MgUnitize"), i_Tol);
	MREAL	d2 = 1.f / d1;
	return MgVect3D( i_v.x * d2, i_v.y * d2, i_v.z * d2);
}
//S #ifdef _MgPoint3DA
//
//MgPoint3Da Norma( const MgPoint3D& i_p, MREAL i_Tol)
//{
//	MREAL d1;
///*
//	MgPoint3Da p1;
//	if(fabs(p.x < i_Tol)) p1.x = 0;	else p1.x = i_p.x;
//	if(fabs(p.y < i_Tol)) p1.y = 0;	else p1.y = i_p.y;
//	if(fabs(p.z < i_Tol)) p1.z = 0;	else p1.z = i_p.z;
//*/
//	MREAL	d1= MgAbs( p);
//		MBCHECK_ZEROVECT( d1, MBCstr( "MgPoint3Da Norma"), i_Tol);
//	MREAL	d2 = 1.f / d1;
//	return MgPoint3Da( i_p.x * d2, i_p.y * d2, i_p.z * d2, d1);
//}
//#endif

} // namespace MC
