//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MCmdSekkei.cpp
//
//		
//
//
//  K.Matsu           09/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "MrAPI.h"

#include "MgPoint.h"

#include "MdModel.h"
#include "MdmDB.h"
#include "MdmEnt.h"
#include "Mdm.h"
#include "MdmSet.h"
#include "MdZukei.h"
#include "MdmFig.h"
#include "MsLib.h"
#include "MgGeo.h"
#include "MlLog.h"
#include "MdmDB.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//	Geoテスト
//
void BrkPoint()
{
	_asm int 3;
}
void Test000_Geo()
{
	{
	//=======================
	//	ウィンドウオープン

	CPoint iRect[2] = { CPoint( 100, 100), CPoint( 1000, 800)};;

	DWin::MdwOpen( 1, iRect,	1.0f, 1);

	//=======================
	//	直線上の点

						//#define		MC_ON_PS			0x001			// 点が線分の始点上
						//#define		MC_INSIDE			0x002			// 点が線分の内側上
						//#define		MC_ON_PE			0x004			// 点が線分の終点上
						//#define		MC_OUT_PS			0x010			// 点が線分の始点側延長線上
						//#define		MC_OUT_PE			0x040			// 点が線分の終点側延長線上
						//
						//#define		MC_LEFT				0x100			// 点が線分の左側
						//#define		MC_ON_SLINE			0x200			// 点が線分または延長直線上
						//#define		MC_RIGHT			0x400			// 点が線分の右側
	{
	MgLine2D ln01( 0.f, 10.f, 10.f, 0.f);
	MgSLine2D ln02( 0.f, 10.f, 1.f, -1.f);
	MgHLine2D ln03( 0.f, 10.f, 1.f, -1.f);
	ln03.v.Unitize();
	MgPoint2D pn01[] = { MgPoint2D( 5.001f, 5.001f), MgPoint2D( 5.001f, 6.001f), MgPoint2D( 5.001f, 4.001f), MgPoint2D( 0.001f, 10.001f), MgPoint2D( 10.001f, 0.001f),
						 MgPoint2D( 15.001f, -5.001f), MgPoint2D( -5.001f, 15.001f)};
	int npn01 = sizeof( pn01) / sizeof(MgPoint2D);

	int ist01;
	bool bC01;
	CString sMsg;
	for( int iCl=0; iCl<3; iCl++) {
		switch (iCl)
		{
		case 0: ln01.Print( Mstr(" 線分")); break;
		case 1: ln02.Print( Mstr(" 直線")); break;
		case 2: ln03.Print( Mstr(" 半直線")); break;
		}
		for ( int iC=0; iC<npn01; iC++) {
			pn01[iC].Print( Mstr( "点"));
			switch (iCl)
			{
			case 0:
			bC01 = MGeo::CheckPointOnLine2D( pn01[iC], ln01, &ist01);
				break;
			case 1:
			bC01 = MGeo::CheckPointOnSLine2D( pn01[iC], ln02, &ist01);
				break;
			case 2:
			bC01 = MGeo::CheckPointOnHLine2D( pn01[iC], ln03, &ist01);
				break;
			}
			mlLog::LogOut( Mstr( " 直線上の点 %d, %x : "), bC01, ist01);
			sMsg = "";
			if ( bC01) {
				sMsg += "線分上の点 | ";
			} else {
				sMsg += "線分外の点 | ";
			}
			if ( ist01 & MC_ON_PS)		sMsg += "線分の始点上 | ";
			if ( ist01 & MC_INSIDE)		sMsg += "線分の内側上 | ";
			if ( ist01 & MC_ON_PE)		sMsg += "線分の終点上 | ";
			if ( ist01 & MC_OUT_PS)		sMsg += "線分の始点側延長線上 | ";
			if ( ist01 & MC_OUT_PE)		sMsg += "線分の終点側延長線上 | ";

			if ( ist01 & MC_LEFT)		sMsg += "線分の左側 | ";
			if ( ist01 & MC_ON_SLINE)	sMsg += "線分または延長直線上 | ";
			if ( ist01 & MC_RIGHT)		sMsg += "線分の右側 | ";
			mlLog::LogOut( Mstr( "%s\n"), sMsg);
		}
		mlLog::Print( "");
	}
	}
	MgLine3D ln01( 0.f, 0.f, 10.f, 0.f, 10.f, 0.f);
	MgSLine3D ln02( 0.f, 0.f, 10.f, 0.f, 1.f, -1.f);
	MgHLine3D ln03( 0.f, 0.f, 10.f, 0.f, 1.f, -1.f);
	ln03.v.Unitize();
	MgPoint3D pn01[] = { MgPoint3D( 0.f, 5.001f, 5.001f), MgPoint3D( 0.f, 5.001f, 6.001f), MgPoint3D( 0.f, 5.001f, 4.001f),
						 MgPoint3D( 0.f, 0.001f, 10.001f), MgPoint3D( 0.f, 10.001f, 0.001f),
						 MgPoint3D( 0.f, 15.001f, -5.001f), MgPoint3D( 0.f, -5.001f, 15.001f)};
	int npn01 = sizeof( pn01) / sizeof(MgPoint3D);

	int ist01;
	bool bC01;
	CString sMsg;
	for( int iCl=0; iCl<3; iCl++) {
		switch (iCl)
		{
		case 0: ln01.Print( Mstr(" 線分")); break;
		case 1: ln02.Print( Mstr(" 直線")); break;
		case 2: ln03.Print( Mstr(" 半直線")); break;
		}
		for ( int iC=0; iC<npn01; iC++) {
			pn01[iC].Print( Mstr( "点"));
			switch (iCl)
			{
			case 0:
			bC01 = MGeo::CheckPointOnLine3D( pn01[iC], ln01, &ist01);
				break;
			case 1:
			bC01 = MGeo::CheckPointOnSLine3D( pn01[iC], ln02);
				break;
			case 2:
			bC01 = MGeo::CheckPointOnHLine3D( pn01[iC], ln03, &ist01);
				break;
			}
			mlLog::LogOut( Mstr( " 直線上の点 %d, %x : "), bC01, ist01);
			sMsg = "";
			if ( bC01) {
				sMsg += "線分上の点 | ";
			} else {
				sMsg += "線分外の点 | ";
			}
			if ( ist01 & MC_ON_PS)		sMsg += "線分の始点上 | ";
			if ( ist01 & MC_INSIDE)		sMsg += "線分の内側上 | ";
			if ( ist01 & MC_ON_PE)		sMsg += "線分の終点上 | ";
			if ( ist01 & MC_OUT_PS)		sMsg += "線分の始点側延長線上 | ";
			if ( ist01 & MC_OUT_PE)		sMsg += "線分の終点側延長線上 | ";

			if ( ist01 & MC_LEFT)		sMsg += "線分の左側 | ";
			if ( ist01 & MC_ON_SLINE)	sMsg += "線分または延長直線上 | ";
			if ( ist01 & MC_RIGHT)		sMsg += "線分の右側 | ";
			mlLog::LogOut( Mstr( "%s\n"), sMsg);
		}
		mlLog::Print( "");
	}

	//=======================
	//	２ベクトルの角度乗数
//	MgVect2D v1( 10.f, 0.f), v2( 12.f, 12.f);
//	MgVect3D V1( 0., 10.f, 0.f), V2( 0., 12.f, 12.f), Vp( 1., 0., 0.);
	MgVect2D v1( 10.f, -5.f), v2( -12.f, 12.f);
	MgVect3D V1( 0., 10.f, -5.f), V2( 0., -12.f, 12.f), Vp( 1., 0., 0.);
	MREAL a211 = MGeo::AngSSa2Vect2D( v1, v2);
	MREAL a212 = MGeo::AngSSa2Vect2D( v2, v1);
	MREAL a221 = MGeo::AngSSb2Vect2D( v1, v2);
	MREAL a222 = MGeo::AngSSb2Vect2D( v2, v1);
	MREAL a311 = MGeo::AngSSa2Vect3D( V1, V2, Vp);
	MREAL a312 = MGeo::AngSSa2Vect3D( V2, V1, Vp);
	MREAL a321 = MGeo::AngSSb2Vect3D( V1, V2, Vp);
	MREAL a322 = MGeo::AngSSb2Vect3D( V2, V1, Vp);
	MREAL a411 = MGeo::AngSSa2Vect3D( V1, V2, -Vp);
	MREAL a412 = MGeo::AngSSa2Vect3D( V2, V1, -Vp);
	MREAL a421 = MGeo::AngSSb2Vect3D( V1, V2, -Vp);
	MREAL a422 = MGeo::AngSSb2Vect3D( V2, V1, -Vp);
	mlLog::LogOut( Mstr( "２ベクトルの角度乗数 2D +: %6.3f, -: %6.3f, +-(+): %6.3f, +-(-): %6.3f\n"),
				   a211, a212, a221, a222);
	mlLog::LogOut( Mstr( "２ベクトルの角度乗数 3D +: %6.3f, -: %6.3f, +-(+): %6.3f, +-(-): %6.3f\n"),
				   a311, a312, a321, a322);
	mlLog::LogOut( Mstr( "２ベクトルの角度乗数 3D(法線ベクトル反転) +: %6.3f, -: %6.3f, +-(+): %6.3f, +-(-): %6.3f\n"),
				   a411, a412, a421, a422);

	//=======================
	//	点の重なり
	MgPoint2D p1(0, 1), p2(0, 1);
	if ( p1 == p2) {
		p1.Print( Mstr( "p1 == p2"));
	}
	//=======================
	//	軸回転マトリックス
	MgSLine3D Uln( 0, 1, 2, 1, 1, 1);
	Uln.v.SetUnitize();
	MgMat3E Mr;
	Mr = MGeo::Mat3ERot( Uln, MGRADIAN( 90));
	Mr.Print( Mstr("軸回転マトリックス"));
	}
	{
	//=======================
	//	軸回転マトリックス
	MgSLine3D Uln( 0, 1, 2, 1, 1, 1);
	Uln.v.SetUnitize();
	MgMat3D Mrd;
	Mrd = MGeo::Mat3DRot( Uln, MGRADIAN( 90));
	Mrd.Print( Mstr("軸回転マトリックス"));
	}
	{
	//=======================
	//	鏡像マトリックス
	MgMat2E m1, m2, m3, m4;
	MgSLine2D sln1( 1., 2., 1., 1.);
	sln1.v.SetUnitize();
	sln1.Print( Mstr("鏡像直線"));
	m1 = MGeo::Mat2EMirror(sln1);
	m1.Print( Mstr("鏡像マトリックス m1"));
	MgPoint2D p01( 1., 0.);
	MgPoint2D p02;
	p02 = p01 * m1;
	p01.Print( Mstr("鏡像前の点"));
	p02.Print( Mstr("鏡像後の点"));

	MgMat2E m01, m02, m03;
	m01.SetUnit();
	m01.Print( Mstr("初期マトリックス m01"));
	m03 = m01 * m1;
	p02 = p01 * m03;
	m03.Print( Mstr("鏡像マトリックス m03 = m01 * m1"));
//S	m02 = MGeo::Mat2EMirror( m01, sln1);
//	p02 = p01 * m02;
//	m02.Print( Mstr("鏡像マトリックス 関数 m02"));
	p02.Print( Mstr("鏡像後の点"));

	MgPlane3D pln1( 1, 2, 3, 1);
	pln1.v.SetUnitize();
	pln1.Print( Mstr("鏡映平面"));
	MgPoint3D P1( 2, 0, 0);
	MgMat3E M1;
	M1.SetUnit();
	M1.Print( Mstr("初期マトリックス M1"));

//S	MgMat3E M2;
//	M2 = MGeo::Mat3EMirror( M1, pln1);
//	M2.Print( Mstr("鏡像マトリックス M2"));
//	MgPoint3D P2;
//	P2 = P1 * M2;
//	P1.Print( Mstr("鏡像前の点"));
//	P2.Print( Mstr("鏡像後の点"));
	
	MgMat3E M3;
	M3 = MGeo::Mat3EMirror( pln1);
	MgPoint3D P3;
	P3 = P1 * M3;
	M3.Print( Mstr("鏡像マトリックス M3"));
	P3.Print( Mstr("鏡像後の点"));
	}
	{
	//=======================
	//	鏡像マトリックス
	MgMat2D m1, m2, m3, m4;
	MgSLine2D sln1( 1., 2., 1., 1.);
	sln1.v.SetUnitize();
	sln1.Print( Mstr("鏡像直線"));
	m1 = MGeo::Mat2DMirror(sln1);
	m1.Print( Mstr("鏡像マトリックス m1"));
	MgPoint2D p01( 1., 0.);
	MgPoint2D p02;
	p02 = p01 * m1;
	p01.Print( Mstr("鏡像前の点"));
	p02.Print( Mstr("鏡像後の点"));

	MgMat2D m01, m02, m03;
	m01.SetUnit();
	m01.Print( Mstr("初期マトリックス m01"));
	m03 = m01 * m1;
	p02 = p01 * m03;
	m03.Print( Mstr("鏡像マトリックス m03 = m01 * m1"));
//S	m02 = MGeo::Mat2DMirror( m01, sln1);
//	p02 = p01 * m02;
//	m02.Print( Mstr("鏡像マトリックス 関数 m02"));
	p02.Print( Mstr("鏡像後の点"));

	MgPlane3D pln1( 1, 2, 3, 1);
	pln1.v.SetUnitize();
	pln1.Print( Mstr("鏡映平面"));
	MgPoint3D P1( 2, 0, 0);
	MgMat3D M1;
	M1.SetUnit();
	M1.Print( Mstr("初期マトリックス M1"));

//S	MgMat3D M2;
//	M2 = MGeo::Mat3DMirror( M1, pln1);
//	M2.Print( Mstr("鏡像マトリックス M2"));
//	MgPoint3D P2;
//	P2 = P1 * M2;
//	P1.Print( Mstr("鏡像前の点"));
//	P2.Print( Mstr("鏡像後の点"));
	
	MgMat3D M3;
	M3 = MGeo::Mat3DMirror( pln1);
	MgPoint3D P3;
	P3 = P1 * M3;
	M3.Print( Mstr("鏡像マトリックス M3"));
	P3.Print( Mstr("鏡像後の点"));
	}

	//=======================
	//	角度
	{
		MgVect2D	v1( 1.f, 0.f);
		MgVect2D	v2( 1.f, 1.f);
		MgVect2D	v3( 0.f, 1.f);
		MgVect2D	v4( -1.f, 1.f);
		MgVect2D	v5( -1.f, 0.f);
		MgVect2D	v6( -1.f, -1.f);
		MgVect2D	v7( 0.f, -1.f);
		MgVect2D	v8( 1.f, -1.f);
		mlLog::Print( "v1", MGDEGREE( MGeo::AngleXVect2D( v1)));
		mlLog::Print( "v2", MGDEGREE( MGeo::AngleXVect2D( v2)));
		mlLog::Print( "v3", MGDEGREE( MGeo::AngleXVect2D( v3)));
		mlLog::Print( "v4", MGDEGREE( MGeo::AngleXVect2D( v4)));
		mlLog::Print( "v5", MGDEGREE( MGeo::AngleXVect2D( v5)));
		mlLog::Print( "v6", MGDEGREE( MGeo::AngleXVect2D( v6)));
		mlLog::Print( "v7", MGDEGREE( MGeo::AngleXVect2D( v7)));
		mlLog::Print( "v8", MGDEGREE( MGeo::AngleXVect2D( v8)));

		MgVect3D	V1( 0.5f, 0.3f, 1.f);
		mlLog::Print( "V1", MGDEGREE( MGeo::AngleVectXYPln3D( V1)));
		MgVect3D	V2( 0.f, 1.f, 1.f);
		mlLog::Print( "V2", MGDEGREE( MGeo::AngleVectYZPln3D( V2)));
		MgVect3D	V3( 0.f, 1.f, 1.f);
		mlLog::Print( "V3", MGDEGREE( MGeo::AngleVectZXPln3D( V3)));
		MgVect3D	V4( 0.5f, 0.3f, 1.f);
		MgPlane3D	pln1( 1., 1., 1., 0.);
		mlLog::Print( "V4", MGDEGREE( MGeo::AngleVectPln3D( V4, pln1)));
		MgVect3D	V5( 1.f, 1.f, 1.f);
		mlLog::Print( "V5", MGDEGREE( MGeo::AngleVectPln3D( V5, pln1)));
		MgVect3D V6,V7,V8;
		V6 = V5;
		memcpy( &V7, &V5, SZMgPoint3D());
		memcpy( &V8, &V5, 3*sizeof(float));
		V8.x = V5.x;
		V8.y = V5.y;
		V8.z = V5.z;
		mlLog::Print( "V6", MGDEGREE( MGeo::AngleVectPln3D( V6, pln1)));
		mlLog::Print( "V7", MGDEGREE( MGeo::AngleVectPln3D( V7, pln1)));
		mlLog::Print( "V8", MGDEGREE( MGeo::AngleVectPln3D( V8, pln1)));
	}

	//=======================
	//	Lambda式
	std::vector<int> v;
	for( int i=1; i<10; i++)
		v.push_back(i);
	int x = 3;
	int y = 6;
	v.erase( std::remove_if(v.begin(), v.end(), [x, y](int n) { return x < n && n < y; }), v.end());

	//=======================
	//	strcpy_s
	char* c1 = "1234567890";
	char c21[] = "1111111111111111111111111111111111111111";
	strcpy_s( c21, 15, c1);

	MCHAR* cw1 = Mstr("1234567890");
	MCHAR cw21[] = Mstr("1111111111111111111111111111111111111111");
	Mstrcpy_s( cw21, 30, cw1);

	//=======================
	//	Point2D
	MgVect2D v1( 1., 2.);
	MgVect2D v2( 2., -1.);
	MgVect2D v3( 2., 1.);
	MgVect2D v4( 0., 0.);
	MgVect2D v5( 1., 0.);
	MgVect2D v6( 0., 1.);
	MgPoint2D p1[3];
	p1[0] = MgPoint2D( 1., 2.);
	p1[1] = MgPoint2D( 0., 0.);
	p1[2] = p1[1] + v2;
	MREAL rAngd[10];
	//rAngd[0] = MGeo::AngleXVect2D( v1);
	//rAngd[1] = MGeo::AngleYVect2D( v1);
	//rAngd[2] = MGeo::Angle2Vect2D( v1, v2);
	//rAngd[3] = MGeo::Angle2Vect2D( v1, v3);
	//rAngd[4] = MGeo::Angle2Vect2D( v2, v1);
	//rAngd[5] = MGeo::Angle2Vect2D( v3, v1);
	//rAngd[6] = MGeo::Angle3Point2D( p1[0], p1[1], p1[2]);
	//rAngd[7] = MGeo::AngleXVect2D( v5);
	//rAngd[8] = MGeo::AngleYVect2D( v6);
	//mlLog::Print( Mstr("回転角"), rAngd, 9);
#ifdef BRKPT_TEST2
	rAngd[9] = MGeo::AngleXVect2D( v4);
#endif
	mlLog::Print( Mstr("回転角"), rAngd, 10);

	//=======================
	//	MatD

	MgPoint2D ptd1 = MgPoint2D( 1., 2.);
//	MgMat2D matd1 = MgMat2D( 1., 0., 0., 0., 1., 0., 10., 10., 1.);
	MgMat2D matd1 = MgMat2D( 0.2f, .5f, 0.f, 0.8f, 0.2f, 0.f, 10.f, 10.f, 1.f);
	matd1.Print( Mstr("matd1"));
	MgPoint2D ptd2 = ptd1 * matd1;
	ptd2.Print( Mstr("Ptd2"));

	MgMat2D matd2;
	matd2 = MGeo::Mat2DInv( matd1);
	matd2.Print( Mstr("matd2 = Inv( matd1) "));

	MgMat2D matd3;
	matd3 = matd1 * matd2;
	matd3.Print( Mstr("matd3 = mate1 * matd2"));

	MgPoint3D Ptd1 = MgPoint3D( 1., 2., 3.);
//	MgMat3D Matd1 = MgMat3D( 1., 0., 0.,  0.,  0., 1., 0., 0.,  0., 0., 1., 0.,  10., 10., 10., 1.);
	MgMat3D Matd1 = MgMat3D( 0.2f, .5f, 0.7f, 0.f,  0.8f, 0.2f, 0.3f, 0.f,  0.2f, 0.3f, 0.9f, 0.f,  10.f, 10.f, 10.f, 1.f);
	Matd1.Print( Mstr("Matd1"));
	MgPoint3D Ptd2 = Ptd1 * Matd1;
	Ptd2.Print( Mstr("Ptd2"));

	MgMat3D Matd2;
	Matd2 = MGeo::Mat3DInv( Matd1);
	Matd2.Print( Mstr("Matd2 = Inv( Matd1) "));

	MgMat3D Matd3;
	Matd3 = Matd1 * Matd2;
	Matd3.Print( Mstr("Matd3 = Matd1 * Matd2"));
//#define BRKPT_TEST2
#ifdef BRKPT_TEST2
	RETURN_FILEOPEN_ERR_S( "CHECK");
#endif
	//=======================
	//	MatE

	MgPoint2D pt1 = MgPoint2D( 1., 2.);
//	MgMat2E mate1 = MgMat2E( 1., 0., 0., 1., 10., 10.);
	MgMat2E mate1 = MgMat2E( 0.2f, .5f, 0.8f, 0.2f, 10.f, 10.f);
	mate1.Print( Mstr("mate1"));
	MgPoint2D pt2 = pt1 * mate1;
	pt2.Print( Mstr("Pt2"));

	MgMat2E mate2;
	mate2 = MGeo::Mat2EInv( mate1);
	mate2.Print( Mstr("mate2 = Inv( mate1) "));

	MgMat2E mate3;
	mate3 = mate1 * mate2;
	mate3.Print( Mstr("mate3 = mate1 * mate2"));

	MgPoint3D Pt1 = MgPoint3D( 1., 2., 3.);
//	MgMat3E Mate1 = MgMat3E( 1., 0., 0.,  0., 1., 0.,  0., 0., 1.,  10., 10., 10.);
	MgMat3E Mate1 = MgMat3E( 0.2f, .5f, 0.7f,  0.8f, 0.2f, 0.3f,  0.2f, 0.3f, 0.9f,  10.f, 10.f, 10.f);
	Mate1.Print( Mstr("Mate1"));
	MgPoint3D Pt2 = Pt1 * Mate1;
	Pt2.Print( Mstr("Pt2"));

	MgMat3E Mate2;
	Mate2 = MGeo::Mat3EInv( Mate1);
	Mate2.Print( Mstr("Mate2 = Inv( Mate1) "));

	MgMat3E Mate3;
	Mate3 = Mate1 * Mate2;
	Mate3.Print( Mstr("Mate3 = Mate1 * Mate2"));

	MgVect2D v22 = MgVect2D( 1., 2.);
	MgVect2D v23 = v22.RotR90();
	v22.Print( Mstr("v22"));
	v23.Print( Mstr("v23"));
	v22 = v22.RotR90();
	v22.Print( Mstr("v22"));
	v23.SetRotR90();
	v23.Print( Mstr("v23"));
	MgVect2D v24;
	v24 = v22.Rot( MgVect2D( 1., 1.).Unitize());
	v24.Print( Mstr("v24(v22.Rot(1.,1.))"));
	v22.SetRot( (MREAL)MC_PIE/4);
	v22.Print( Mstr("v22.SetRot(MC_PIE/4)"));
	MREAL ri = v22 * v23;
	mlLog::Print( Mstr("v22 * v23"), ri);
	MREAL ro = v22 ^ v23;
	mlLog::Print( Mstr("v22 ^ v23"), ro);
//	MREAL ang = v24.ang();
//	MGeo::arc3di

	MgPoint2D pt22 = MgPoint2D( 1., 2.);
	MgPoint2D pt23 = pt22.RotR90();
	pt22.Print( Mstr("pt22"));
	pt23.Print( Mstr("pt23"));
	pt22 = pt22.RotR90();
	pt22.Print( Mstr("pt22"));
	pt23.SetRotR90();
	pt23.Print( Mstr("pt23"));
	MgPoint2D pt24;
	pt24 = pt22.Rot( (MREAL)MC_PIE/4);
	pt24.Print( Mstr("pt24(pt22.Rot(MC_PIE/4))"));
	pt22.SetRot( (MREAL)MC_PIE/4);
	pt22.Print( Mstr("pt22.SetRot(MC_PIE/4)"));

	MgVect3D v32 = MgVect3D( 1., 2., 3.);
	MgVect3D v33 = v32.RotR90();
	v32.Print( Mstr("v32"));
	v33.Print( Mstr("v33"));
	v32 = v32.RotR90();
	v32.Print( Mstr("v32"));
	v33.SetRotR90();
	v33.Print( Mstr("v33"));
	MgVect3D v34;
	v34 = v32.Rot( MgVect2D( 1., 1.).Unitize());
	v34.Print( Mstr("v34(v32.Rot(1.,1.))"));
	v32.SetRot( (MREAL)MC_PIE/4);
	v32.Print( Mstr("v22.SetRot(MC_PIE/4)"));

	MgPoint3D pt32 = MgPoint3D( 1., 2., 3.);
	MgPoint3D pt33 = pt32.RotR90();
	pt32.Print( Mstr("pt32"));
	pt33.Print( Mstr("pt33"));
	pt32 = pt32.RotR90();
	pt32.Print( Mstr("pt32"));
	pt33.SetRotR90();
	pt33.Print( Mstr("pt33"));
	MgPoint3D pt34;
	pt34 = pt32.Rot( (MREAL)MC_PIE/4);
	pt34.Print( Mstr("pt34(pt32.Rot(MC_PIE/4))"));
	pt32.SetRot( (MREAL)MC_PIE/4);
	pt32.Print( Mstr("pt32.SetRot(MC_PIE/4)"));
	
//U	AfxDebugBreak( );
//U	BrkPoint();
}

////////////////////////////////////////////////////////////////////////////
//	ファイル・フォルダ選択テスト
//
void Test001_SelectFile()
{
	MCHAR FilePathI[] = Mstr( "D:\\temp\\*.txt");
	MCHAR FilePathO[MAX_PATH];

	MmWndInfo* pWndInfo = WindowCtrl::MmWndKGetCurWnd();					// カレントウィンドウを取得する
	CWnd* pWnd = pWndInfo->m_pWnd;

	HWND hWnd;
	if ( pWnd != NULL ) hWnd = pWnd->GetSafeHwnd();
	else hWnd = NULL;

	//	読み込み用ファイル選択ダイアログを表示する
	//
	ms::LoadFileDlg( pWnd, FilePathI, FilePathO, MAX_PATH, NULL);

	pWnd->MessageBox( FilePathO, Mstr( "Load File Name"), MB_OK | MB_TOPMOST);
	MessageBox( hWnd, FilePathO, Mstr( "Load File Name"), MB_OK | MB_TOPMOST);

	//	保存用ファイル選択ダイアログを表示する
	//
	ms::SaveFileDlg( pWnd, FilePathI, FilePathO, MAX_PATH, NULL);
	MessageBox( hWnd, FilePathO, Mstr( "Save File Name"), MB_OK | MB_TOPMOST);


	//	フォルダ選択ダイアログを表示する
	//
	MCHAR FolderPath[MAX_PATH] = Mstr( "D:\\Temp");
	ms::ForFolderDlg( hWnd, Mstr( "テスト用フォルダの選択"), Mstr( "D:\\Temp"), FolderPath, MAX_PATH);
	MessageBox( hWnd, FolderPath, Mstr( "Folder Name"), MB_OK | MB_TOPMOST);
	BrkPoint();
}

////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールグループ生成テスト
//
void Test002_DBModule()
{
	MINT	iSt;

	MDID	idGrp[5];							// グループId
	MINT	isz = 20;							// 初期グループIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "グループ１"), 3000., 201., &idGrp[0], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ２"), 3000., 202., &idGrp[1], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ２"));
	iSt = DGrp::DeleteGrp( idGrp[0]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬグループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ３"), 3000., 203., &idGrp[2], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ３"));
	//iSt = DGrp::CreateGrp( Mstr( "グループ４"), 3000., 250., &idGrp[3], isz);
	//pIeModel->Print( Mstr( "●家モデル　グループ４"));
	//iSt = DGrp::DeleteGrp( idGrp[2]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬグループ３"));
	//iSt = DGrp::DeleteGrp( idGrp[3]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬグループ４"));
	//iSt = DGrp::CreateGrp( Mstr( "グループ５"), 3000., 250., &idGrp[4], isz);
	//pIeModel->Print( Mstr( "●家モデル　グループ５"));
	//iSt = DGrp::DeleteGrp( idGrp[4]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬグループ５"));
}

////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールスキーマ生成テスト
//
void Test003_DBModule()
{
	MINT	iSt;

	MDID	idScm[5];							// レイヤーId
	MINT	isz = 20;							// 初期レイヤーIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateScm( Mstr( "スキーマ１"), &idScm[0], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ１"));
	iSt = DGrp::CreateScm( Mstr( "スキーマ２"), &idScm[1], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ２"));
	iSt = DGrp::DeleteScm( idScm[0]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬスキーマ１"));
	iSt = DGrp::CreateScm( Mstr( "スキーマ３"), &idScm[2], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ３"));
	//iSt = DGrp::CreateScm( Mstr( "スキーマ４"), &idScm[3], isz);
	//pIeModel->Print( Mstr( "●家モデル　スキーマ４"));
	//iSt = DGrp::DeleteScm( idScm[2]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬスキーマ３"));
	//iSt = DGrp::DeleteScm( idScm[3]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬスキーマ４"));
	//iSt = DGrp::CreateScm( Mstr( "スキーマ５"), &idScm[4], isz);
	//pIeModel->Print( Mstr( "●家モデル　スキーマ５"));
	//iSt = DGrp::DeleteScm( idScm[4]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬスキーマ５"));
}

////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールレイヤー生成テスト
//
void Test004_DBModule()
{
	MINT	iSt;

	MDID	idGrp[2];							// グループId
	MDID	idScm[2];							// レイヤーId

	MDID	idLyr[5];							// レイヤーId

	MINT	isz = 20;							// 初期グループIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "グループ１"), 3000., 204., &idGrp[0], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ２"), 3000., 205., &idGrp[1], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ２"));

	iSt = DGrp::CreateScm( Mstr( "スキーマ１"), &idScm[0], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ１"));
	iSt = DGrp::CreateScm( Mstr( "スキーマ２"), &idScm[1], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ２"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー１"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー２"));
	iSt = DLyr::DeleteLyr( idLyr[0]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬレイヤー１"));
	iSt = DLyr::CreateLyr( idScm[1], idGrp[0], &idLyr[2], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー３"));
	iSt = DLyr::CreateLyr( idScm[1], idGrp[1], &idLyr[3], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー４"));
	iSt = DLyr::DeleteLyr( idLyr[2]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬレイヤー３"));
	iSt = DLyr::DeleteLyr( idLyr[3]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬレイヤー４"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[4], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー５"));
	iSt = DLyr::DeleteLyr( idLyr[4]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬレイヤー５"));
}

////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールエンティティ生成テスト
//
void Test005_DBModule()
{
	MINT	iSt;

	MDID	idGrp[4];							// グループId
	MDID	idScm[2];							// レイヤーId

	MDID	idLyr[4];							// レイヤーId

	MDID	idEnt[10];							// エンティティId
	MINT	isz = 20;							// 初期エンティティIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "グループ１"), 3000., 206., &idGrp[0], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ２"), 3000., 207., &idGrp[1], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ２"));

	iSt = DGrp::CreateScm( Mstr( "スキーマ１"), &idScm[0], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ１"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー１"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー２"));

	iSt = mdmDEnt::CreateEnt( 01, &idEnt[0], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１"));
	iSt = mdmDEnt::CreateEnt( 02, &idEnt[1], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ２"));
	//iSt = mdmDEnt::DeleteEnt( idEnt[0]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ１"));
	iSt = mdmDEnt::DeleteEnt( idEnt[1]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ２"));



	iSt = mdmDEnt::CreateEnt( 02, &idEnt[2], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ３"));

	iSt = mdmDEnt::CreateEnt( 01, &idEnt[3], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ４"));

	//iSt = mdmDEnt::DeleteEnt( idEnt[2]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ３"));
	iSt = mdmDEnt::DeleteEnt( idEnt[3]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ４"));
	iSt = mdmDEnt::CreateEnt( 01, &idEnt[4], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ５"));
	//iSt = mdmDEnt::DeleteEnt( idEnt[4]);
	//pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ５"));
}
////////////////////////////////////////////////////////////////////////////
//	ＤＢモジュールエンティティ図形生成テスト
//
void Test006_DBModule()
{
	MINT	iSt;

	MDID	idGrp[4];							// グループId
	MDID	idScm[2];							// レイヤーId

	MDID	idLyr[4];							// レイヤーId

	MDID	idEnt[20];							// エンティティId
	MINT	isz = 40;							// 初期エンティティIdバッファサイズ

	MdModel* pIeModel = Mdm::GetCurModel();

	iSt = DGrp::CreateGrp( Mstr( "グループ１"), 3000., 208., &idGrp[0], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ１"));
	iSt = DGrp::CreateGrp( Mstr( "グループ２"), 3000., 209., &idGrp[1], isz);
	pIeModel->Print( Mstr( "●家モデル　グループ２"));

	iSt = DGrp::CreateScm( Mstr( "スキーマ１"), &idScm[0], isz);
	pIeModel->Print( Mstr( "●家モデル　スキーマ１"));

	iSt = DLyr::CreateLyr( idScm[0], idGrp[0], &idLyr[0], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー１"));
	iSt = DLyr::CreateLyr( idScm[0], idGrp[1], &idLyr[1], isz);
	pIeModel->Print( Mstr( "●家モデル　レイヤー２"));

	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[0], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[1], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ２"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[2], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ３"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[3], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ４"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[4], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ５"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[5], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ６"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[6], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ７"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[7], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ８"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[8], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ９"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[9], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１０"));
	iSt = mdmDEnt::CreateEnt( idLyr[0], &idEnt[10], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１１"));

	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[11], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１２"));
	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[12], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１３"));
	iSt = mdmDEnt::CreateEnt( idLyr[1], &idEnt[13], isz);
	pIeModel->Print( Mstr( "●家モデル　エンティティ１４"));

	iSt = mdmDEnt::DeleteEnt( idEnt[1]);
	pIeModel->Print( Mstr( "●家モデル　ＤＥＬエンティティ２"));


	// 表示モードを設定する
	DLyr::SetLyrDispMode( 1, idLyr[0], 3);
	DLyr::SetLyrDispMode( 1, idLyr[1], 3);

	// エンティティに図形を設定する
	MgPoint3D Pt0( 0., 0., 0.);
	MgPoint3D Pt1( 1000., 0., 0.);
	MgPoint3D Pt2( 1000., 1000., 0.);

	
	//// テクスチャ
	//MINT iP;
	//iP = 0;
	//MDFIG stFig13( 100);
	//stFig13.Push();							// push プリミティブを追加
	//stFig13.SetN( WSZMgPush() + 1);			
	//;
	
	
	// 線分１
	MDFIG stFig1( 10);
	stFig1.Line3D( MgLine3D( Pt0, Pt1));
	mdmDEnt::SetFig( idEnt[0], stFig1); 

	// 線分２
	MDFIG stFig2( 12);
	stFig2.Line3D( MgLine3D( Pt0, Pt1));
	mdmDEnt::SetFig( idEnt[2], stFig2); 

	// ポリゴン
	MgPolyg3D Pg1(10);

	Pg1 += MgPoint3D( 0., 0., -1000.);
	Pg1 += MgPoint3D( 0., 2000., -1000.);
	Pg1 += MgPoint3D( 2000., 2000., -1000.);
	Pg1 += MgPoint3D( 2000., 0., -1000.);

	MDFIG stFig3( 20);
	stFig3.Polyg3( Pg1);
	mdmDEnt::SetFig( idEnt[3], stFig3); 
	
	// 点
	MDFIG stFig4( 10);
	stFig4.Point3( MgPoint3D( 1000., 1000., -1000.));
	mdmDEnt::SetFig( idEnt[4], stFig4);

	// 直線
	MDFIG stFig5( 10);
	stFig5.SLine3D( MgSLine3D( MgPoint3D( 3000., 3000., -2000.), MgVect3D( 1., 0., 0.)));
	mdmDEnt::SetFig( idEnt[5], stFig5);

	// 半直線
	MDFIG stFig6( 10);
	stFig6.HLine3D( MgHLine3D( MgPoint3D( 2000., 2000., -1500.), MgVect3D( 0., 1., 0.)));
	mdmDEnt::SetFig( idEnt[6], stFig6);

	// ポリライン
	MgPolyl3D Pl1(10);

	Pl1 += MgPoint3D( 0., 0., -2000.);
	Pl1 += MgPoint3D( 0., 2000., -2000.);
	Pl1 += MgPoint3D( 2000., 2000., -2000.);
	Pl1 += MgPoint3D( 2000., 0., -2000.);

	MDFIG stFig7( 20);
	stFig7.Polyl3( Pl1);
	mdmDEnt::SetFig( idEnt[7], stFig7); 

	// 平面
	MDFIG stFig8( 10);
	stFig8.Plane3( MgPlane3D( MgVect3D( 0., 1., 0.), -6000.));
	mdmDEnt::SetFig( idEnt[8], stFig8);

	// ポリゴン
	MgPolyg3D Pg2(10);

	Pg2 += MgPoint3D( 0., 0., -3000.);
	Pg2 += MgPoint3D( 0., 2000., -3000.);
	Pg2 += MgPoint3D( 2000., 2000., -3000.);
	Pg2 += MgPoint3D( 2000., 0., -3000.);

	MDFIG stFig9( 20);
	stFig9.Polyg3( Pg1);
	mdmDEnt::SetFig( idEnt[9], stFig9); 

	// 円
	MDFIG stFig10( 10);
	stFig10.Cir3( MgCir3D( MgPoint3D( 5000., 5000., -1000.), MgVect3D( 0., 1., 0.), 2000.));
	mdmDEnt::SetFig( idEnt[10], stFig10);

	// 円弧
	MDFIG stFig11( 15);
	stFig11.Arc3( MgArc3D( MgPoint3D( 2000., 0., -1500.), MgPoint3D( 0., 2000., -1500.),
						  MgPoint3D( 0., 0., -1500.), MgVect3D( 0., 1., 0.), 1500.));
	mdmDEnt::SetFig( idEnt[11], stFig11);

	// 無限平面
	MDFIG stFig12( 10);
	stFig12.IPlane3( MgPlane3D( MgVect3D( 0., 1., 0.), -6000.));
	mdmDEnt::SetFig( idEnt[12], stFig12);

	//// テクスチャ
	MDFIG stFig13( 100);
	stFig13.zPush();							// push プリミティブを追加

	stFig13.zMarker( 1, 2.);
	stFig13.zPaint( 2, 3, 4);
	stFig13.zLineTp( 5);

	stFig13.zColorRGB( MUQUARTER( 100, 200, 255, 100));			// RGB	{byte} ( 0, r, g, b)
	stFig13.zColorRGB( FLOAT3( 0.3f, 0.4f, 0.5f));				// RGB	{float} ( 1., 1., 1.) (1.)
	stFig13.zColorPlt( 2);										// 色(パレット)
	stFig13.zTransmissivity( 0.7f);								// 透過率 ( 0. ～ 1.)
	stFig13.zLineWd( 0.1f);										// 線幅
	stFig13.zMaterialRGBA( MC_AMBIENT, MUQUARTER( 100, 255, 200, 150));		// RGB	( A{透過率}, R, G, B)
	stFig13.zMaterialRGBA( MC_DIFFUSE, FLOAT3( 1.f, 0.5f, 0.3f), 0.7f);	// A 透過率	( 0. ～ 1.)
	stFig13.zMaterialShininess( 100.0f);						// 鏡面光係数 ( 0. ～ 128.)
	stFig13.zTexture( 5);										// テクスチャＩＤ
//S	MgMat3E mat3( 1., 0., 0., 1.,
//				  0., 1., 0., 1.,
//				  0., 1., 1., 1.,
//				  100., 200., 300., 1.);
	MgMat3E mat3( 1., 0., 0.,
				  0., 1., 0.,
				  0., 0., 1.,
				  100., 200., 300.);
	stFig13.zTextureCoordinate( 0, 1, &MgVect2D( 1., 0.), &mat3);// 配置マトリックス
	stFig13.zTextureParam( 1, 1, 2, 3, 4,						// 拡大／縮小フィルタ
		MREAL3( 1., 0.5, 0.3f), MREAL3( 0.2f, 0.3f, 0.4f));		// 境界線色2		
	stFig13.zShininess( 101.);									// 鏡面反射率 ( 0. ～ 1.)
	stFig13.zPovRay( Mstr( "TEST"));							// 文字列


	stFig13.zPull();

	mdmDEnt::SetFig( idEnt[13], stFig13);

	pIeModel->Print( Mstr( "●家モデル　３図形追加"));
}

////////////////////////////////////////////////////////////////////////////
//	テスト用００１
//
void MCmdTest001()
{
	////	ファイル・フォルダ選択テスト
	//Test001_SelectFile();

	//	ＤＢモジュールテスト
	Test000_Geo();
	Test002_DBModule();
	Test003_DBModule();
	Test004_DBModule();
	Test005_DBModule();
	Test006_DBModule();
}

} // namespace MC
