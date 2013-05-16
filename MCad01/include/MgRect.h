#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgRect2D.h
//
//		��`
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

#include "MgPoint.h"
#include "MgLine.h"

class MgPolyg2D;
class MgPolyg3D;

#include "mdPlex.h"

#ifdef DLL_EXPORT_RECT
	#undef DLL_EXPORT_RECT
#endif

#ifdef DLL_EXPORT_RECT_DO
	#pragma message( "<<< MgRect�Edll_EXport >>>")
	#define DLL_EXPORT_RECT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_RECT
		#else
//			#pragma message( "=== MgRect�Edll_IMport ===")
			#define DLL_EXPORT_RECT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_RECT
	#endif
#endif

namespace MC
{

//
//===========================================================================
//		�l�h���^�l����
//
//======================( �Q���� )==============================
//	�����^
class DLL_EXPORT_RECT MgMinMaxI2D
{
public:
	CPoint			min;											// �ŏ����W�̓_			
	CPoint			max;											// �ő���W�̓_
//
public:
	MgMinMaxI2D() {};
	MgMinMaxI2D(MINT i1x, MINT i1y, MINT i2x, MINT i2y) {
						min.x = i1x; min.y = i1y;
						max.x = i2x; max.y = i2y;}
	MgMinMaxI2D(const CPoint &cp1, const CPoint &cp2) {
						min.x = min( cp1.x, cp2.x);
						min.y = min( cp1.y, cp2.y);
						max.x = max( cp1.x, cp2.x);
						max.y = max( cp1.y, cp2.y);}
	void SetUnit();
	void SetInit();
	void Ins2(const CPoint &pt) {
						if (min.x > pt.x) min.x = pt.x;	if (max.x < pt.x) max.x = pt.x;
						if (min.y > pt.y) min.y = pt.y;	if (max.y < pt.y) max.y = pt.y;}				
	void Ins2(const MgMinMaxI2D &imm1) {
						if (min.x > imm1.min.x) min.x = imm1.min.x;
						if (max.x < imm1.max.x) max.x = imm1.max.x;
						if (min.y > imm1.min.y) min.y = imm1.min.y;
						if (max.y < imm1.max.y) max.y = imm1.max.y;}				
	CPoint GetCenter()
						{ return CPoint( (min.x + max.x) / 2, (min.y + max.y) / 2);}
	MINT GetWidth()
						{ return (max.x - min.x);}
	MINT GetHgt()
						{ return (max.y - min.y);}

	MgMinMaxI2D operator | ( const MgMinMaxI2D &imm1) const							// mm1 = mm2 | mm3
						{ return MgMinMaxI2D( MGMIN( min.x, imm1.min.x),
											  MGMIN( min.y, imm1.min.y),
											  MGMAX( max.x, imm1.max.x),
											  MGMAX( max.y, imm1.max.y));}
	MgMinMaxI2D operator + ( const CPoint &pt) const								// mm1 = mm2 + pt
						{ return MgMinMaxI2D( min + pt, max + pt);}
	MgMinMaxI2D operator - ( const CPoint &pt) const								// mm1 = mm2 - pt
						{ return MgMinMaxI2D( min - pt, max - pt);}
	MgMinMaxI2D operator += ( const CPoint &pt)										// mm1 += pt
						{ min += pt; max += pt; return *this;}
	MgMinMaxI2D operator -= ( const CPoint &pt)										// mm1 -= pt
						{ min -= pt; max -= pt; return *this;}
	friend MgMinMaxI2D operator * ( MINT isc, const MgMinMaxI2D &mm)				// mm1 = isc * mm2
						{ return MgMinMaxI2D( mm.min.x * isc, mm.min.y * isc, 
										      mm.max.x * isc, mm.max.y * isc);}
	friend MgMinMaxI2D operator * ( MREAL rsc, const MgMinMaxI2D &mm)				// mm1 = rsc * mm2
						{ return MgMinMaxI2D( MINT(mm.min.x * rsc),
										      MINT(mm.min.y * rsc), 
										      MINT(mm.max.x * rsc), 
										      MINT(mm.max.y * rsc));}
	MgMinMaxI2D operator * ( MINT isc) const										// mm1 = mm2 * isc
						{ return MgMinMaxI2D( min.x * isc, min.y * isc, 
										     max.x * isc, max.y * isc);}
	MgMinMaxI2D operator * ( MREAL rsc) const										// mm1 = mm2 * rsc
						{ return MgMinMaxI2D( MINT(min.x * rsc),
										      MINT(min.y * rsc), 
										      MINT(max.x * rsc),
										      MINT(max.y * rsc));}
	MgMinMaxI2D operator / ( MINT isc) const										// mm1 = mm2 / isc
						{ return MgMinMaxI2D( min.x / isc, min.y / isc, 
										      max.x / isc, max.y / isc);}
	MgMinMaxI2D operator / ( MREAL rsc) const										// mm1 = mm2 / rsc
						{ return MgMinMaxI2D( MINT(min.x / rsc),
										      MINT(min.y / rsc), 
										      MINT(max.x / rsc),
										      MINT(max.y / rsc));}
	MgMinMaxI2D operator *= ( MINT isc)												// mm1 *= isc
						{ return MgMinMaxI2D( min.x *= isc, min.y *= isc, 
										      max.x *= isc, max.y *= isc);}
	MgMinMaxI2D operator *= ( MREAL rsc)											// mm1 *= rsc
						{ return MgMinMaxI2D( min.x = MINT(min.x * rsc),
										      min.y = MINT(min.y * rsc), 
										      max.x = MINT(max.x * rsc),
										      max.y = MINT(max.y * rsc));}
	MgMinMaxI2D operator /= ( MINT isc)												// mm1 /= isc
						{ return MgMinMaxI2D( min.x /= isc, min.y /= isc, 
										      max.x /= isc, max.y /= isc);}
	MgMinMaxI2D operator /= ( MREAL rsc)											// mm1 /= rsc
						{ return MgMinMaxI2D( min.x = MINT(min.x / rsc),
										      min.y = MINT(min.y / rsc), 
										      max.x = MINT(max.x / rsc),
										      max.y = MINT(max.y / rsc));}

	void Print(MCHAR* s);															// print
};
//======================( �Q���� )==============================
//	�����^
class DLL_EXPORT_RECT MgMinMaxR2D
{
public:
	MgPoint2D			min;											// �ŏ����W�̓_			
	MgPoint2D			max;											// �ő���W�̓_
//
public:
	MgMinMaxR2D() {};
	MgMinMaxR2D(MREAL r1x, MREAL r1y, MREAL r2x, MREAL r2y) {
						min.x = r1x; min.y = r1y; 
						max.x = r2x; max.y = r2y;}
	MgMinMaxR2D(const MgPoint2D& p1, const MgPoint2D& p2) {
						min.x = min( p1.x, p2.x);
						min.y = min( p1.y, p2.y);
						max.x = max( p1.x, p2.x);
						max.y = max( p1.y, p2.y);}
	MgMinMaxR2D(const MgLine2D& Ln1) {
						min.x = min( Ln1.p[0].x, Ln1.p[1].x);
						min.y = min( Ln1.p[0].y, Ln1.p[1].y);
						max.x = max( Ln1.p[0].x, Ln1.p[1].x);
						max.y = max( Ln1.p[0].y, Ln1.p[1].y);}
	void SetUnit();
	void SetInit();
	void Ins2(const MgPoint2D& pt) {
						if (min.x > pt.x) min.x = pt.x;	if (max.x < pt.x) max.x = pt.x;
						if (min.y > pt.y) min.y = pt.y;	if (max.y < pt.y) max.y = pt.y;}				
	void Ins2(const MgLine2D& ln) {
						if (min.x > ln.p[0].x) min.x = ln.p[0].x; if (max.x < ln.p[0].x) max.x = ln.p[0].x;
						if (min.y > ln.p[0].y) min.y = ln.p[0].y; if (max.y < ln.p[0].y) max.y = ln.p[0].y;
						if (min.x > ln.p[1].x) min.x = ln.p[1].x; if (max.x < ln.p[1].x) max.x = ln.p[1].x;
						if (min.y > ln.p[1].y) min.y = ln.p[1].y; if (max.y < ln.p[1].y) max.y = ln.p[1].y;}				
	void Ins2(const MgPolyg2D &pg);

	void Ins2(const MgMinMaxR2D &mm1) {
						if (min.x > mm1.min.x) min.x = mm1.min.x;
						if (max.x < mm1.max.x) max.x = mm1.max.x;
						if (min.y > mm1.min.y) min.y = mm1.min.y;
						if (max.y < mm1.max.y) max.y = mm1.max.y;}				
	MgPoint2D GetCenter()
						{ return MgPoint2D( (min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f);}
	MREAL GetWidth()
						{ return (max.x - min.x);}
	MREAL GetHgt()
						{ return (max.y - min.y);}

	MgMinMaxR2D operator | ( const MgMinMaxR2D &mm1) const							// mm1 = mm2 | mm3
						{ return MgMinMaxR2D( MGMIN( min.x, mm1.min.x),
											  MGMIN( min.y, mm1.min.y),
											  MGMAX( max.x, mm1.max.x),
											  MGMAX( max.y, mm1.max.y));}
	MgMinMaxR2D operator + ( const MgVect2D& pt) const								// mm1 = mm2 + pt
						{ return MgMinMaxR2D( min + pt, max + pt);}
	MgMinMaxR2D operator - ( const MgVect2D& pt) const								// mm1 = mm2 - pt
						{ return MgMinMaxR2D( min - pt, max - pt);}
	MgMinMaxR2D operator += ( const MgVect2D& pt)									// mm1 += pt
						{ min += pt; max += pt; return *this;}
	MgMinMaxR2D operator -= ( const MgVect2D& pt)									// mm1 -= pt
						{ min -= pt; max -= pt; return *this;}
	friend MgMinMaxR2D operator * ( MREAL rsc, const MgMinMaxR2D &mm)				// mm1 = rsc * mm2
						{ return MgMinMaxR2D( mm.min.x * rsc, mm.min.y * rsc, 
										      mm.max.x * rsc, mm.max.y * rsc);}
	MgMinMaxR2D operator * ( MREAL rsc) const										// mm1 = mm2 * rsc
						{ return MgMinMaxR2D( min.x * rsc, min.y * rsc, 
										      max.x * rsc, max.y * rsc);}
	MgMinMaxR2D operator / ( MREAL rsc) const										// mm1 = mm2 / rsc
						{ return MgMinMaxR2D( min.x / rsc, min.y / rsc, 
										      max.x / rsc, max.y / rsc);}
	MgMinMaxR2D operator *= ( MREAL rsc)											// mm1 *= rsc
						{ return MgMinMaxR2D( min.x *= rsc, min.y *= rsc, 
										      max.x *= rsc, max.y *= rsc);}
	MgMinMaxR2D operator /= ( MREAL rsc)											// mm1 /= rsc
						{ return MgMinMaxR2D( min.x /= rsc, min.y /= rsc, 
										      max.x /= rsc, max.y /= rsc);}

	void Print(MCHAR* s);															// print
};
//======================( �R���� )==============================
//	�����^
class DLL_EXPORT_RECT MgMinMaxR3D
{
public:
	MgPoint3D		min;											// �ŏ����W�̓_
	MgPoint3D		max;											// �ő���W�̓_
//
public:
	MgMinMaxR3D() {};
	MgMinMaxR3D( MREAL minx, MREAL miny, MREAL minz,
			    MREAL maxx, MREAL maxy, MREAL maxz) {
						min.x = minx; min.y = miny; min.z = minz;
						max.x = maxx; max.y = maxy; max.z = maxz;}
	MgMinMaxR3D( const MgPoint3D& min1, const MgPoint3D& max1) {
						min.x = min1.x; min.y = min1.y; min.z = min1.z;
						max.x = max1.x; max.y = max1.y; max.z = max1.z;}
	MgMinMaxR3D( const MgLine3D& Ln1) {
						min.x = min( Ln1.p[0].x, Ln1.p[1].x);
						min.y = min( Ln1.p[0].y, Ln1.p[1].y);
						min.z = min( Ln1.p[0].z, Ln1.p[1].z);
						max.x = max( Ln1.p[0].x, Ln1.p[1].x);
						max.y = max( Ln1.p[0].y, Ln1.p[1].y);
						max.z = max( Ln1.p[0].z, Ln1.p[1].z);}
	void SetUnit();
	void SetInit();
	// �_�̍��W��ǉ�����MinMax��
	void Ins3( const MgPoint3D& Pt) {
						if (min.x > Pt.x) min.x = Pt.x;	if (max.x < Pt.x) max.x = Pt.x;
						if (min.y > Pt.y) min.y = Pt.y;	if (max.y < Pt.y) max.y = Pt.y;				
						if (min.z > Pt.z) min.z = Pt.z;	if (max.z < Pt.z) max.z = Pt.z;}				
	void Ins3( const MgLine3D& Ln) {
						if (min.x > Ln.p[0].x) min.x = Ln.p[0].x; if (max.x < Ln.p[0].x) max.x = Ln.p[0].x;
						if (min.y > Ln.p[0].y) min.y = Ln.p[0].y; if (max.y < Ln.p[0].y) max.y = Ln.p[0].y;
						if (min.z > Ln.p[0].z) min.z = Ln.p[0].z; if (max.z < Ln.p[0].z) max.z = Ln.p[0].z;
						if (min.x > Ln.p[1].x) min.x = Ln.p[1].x; if (max.x < Ln.p[1].x) max.x = Ln.p[1].x;
						if (min.y > Ln.p[1].y) min.y = Ln.p[1].y; if (max.y < Ln.p[1].y) max.y = Ln.p[1].y;
						if (min.z > Ln.p[1].z) min.z = Ln.p[1].z; if (max.z < Ln.p[1].z) max.y = Ln.p[1].z;}				
	void Ins3( const MgPolyg3D &Ln);

	void Ins3( const MgMinMaxR3D &mm1) {
						if (min.x > mm1.min.x) min.x = mm1.min.x;
						if (max.x < mm1.max.x) max.x = mm1.max.x;
						if (min.y > mm1.min.y) min.y = mm1.min.y;
						if (max.y < mm1.max.y) max.y = mm1.max.y;}				

	MgPoint3D GetCenter()
						{ return MgPoint3D( (min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f, (min.z + max.z) * 0.5f);}
	MREAL GetWidth()
						{ return (max.x - min.x);}
	MREAL GetHgt()
						{ return (max.y - min.y);}
	MREAL GetDepth()
						{ return (max.z - min.z);}

	MgMinMaxR3D operator | ( const MgMinMaxR3D &mm1) const							// mm1 = mm2 | mm3
						{ return MgMinMaxR3D( MGMIN( min.x, mm1.min.x),
											 MGMIN( min.y, mm1.min.y),
											 MGMIN( min.z, mm1.min.z),
											 MGMAX( max.x, mm1.max.x),
											 MGMAX( max.y, mm1.max.y),
											 MGMAX( max.z, mm1.max.z));}
	MgMinMaxR3D operator + ( const MgVect3D& pt) const								// mm1 = mm2 + pt
						{ return MgMinMaxR3D( min + pt,
											  max + pt);}
	MgMinMaxR3D operator - ( const MgVect3D& pt) const								// mm1 = mm2 - pt
						{ return MgMinMaxR3D( min - pt,
											  max - pt);}
	MgMinMaxR3D operator += ( const MgVect3D& pt)									// mm1 += pt
						{ min += pt; max += pt; return *this;}
	MgMinMaxR3D operator -= ( const MgVect3D& pt)									// mm1 -= pt
						{ min -= pt; max -= pt; return *this;}
	friend MgMinMaxR3D operator * ( MREAL rsc, const MgMinMaxR3D &mm)				// mm1 = rsc * mm2
						{ return MgMinMaxR3D( mm.min.x * rsc, mm.min.y * rsc, mm.min.z * rsc, 
											  mm.max.x * rsc, mm.max.y * rsc, mm.max.z * rsc);}
	MgMinMaxR3D operator * ( MREAL rsc) const										// mm1 = mm2 * rsc
						{ return MgMinMaxR3D( min.x * rsc, min.y * rsc, min.z * rsc,
											  max.x * rsc, max.y * rsc, max.z * rsc);}
	MgMinMaxR3D operator / ( MREAL rsc) const										// mm1 = mm2 / rsc
						{ return MgMinMaxR3D( min.x / rsc, min.y / rsc, min.z / rsc,
											  max.x / rsc, max.y / rsc, max.z / rsc);}
	MgMinMaxR3D operator *= ( MREAL rsc)											// mm1 *= rsc
						{ return MgMinMaxR3D( min.x *= rsc, min.y *= rsc, min.z *= rsc,
											  max.x *= rsc, max.y *= rsc, max.z *= rsc);}
	MgMinMaxR3D operator /= ( MREAL rsc)											// mm1 /= rsc
						{ return MgMinMaxR3D( min.x /= rsc, min.y /= rsc, min.z /= rsc,
											  max.x /= rsc, max.y /= rsc, max.z /= rsc);}

	void Print(MCHAR* s);														// print
};
//
//======================( �Q���� )==============================
//	�����`
class DLL_EXPORT_RECT MgRect2D
{
public:
	MgPoint2D p[2];
//
public:
	MgRect2D() {};
	MgRect2D(MREAL r1x, MREAL r1y, MREAL r2x, MREAL r2y) {
		p[0].x = r1x; p[0].y = r1y; p[1].x = r2x; p[1].y = r2y;}
	MgRect2D(const MgPoint2D& min, const MgPoint2D& max) {
		p[0].x = min.x; p[0].y = min.y; p[1].x = max.x; p[1].y = max.y;}
	void SetUnit();
	MgPoint2D GetCenter()
						{ return MgPoint2D( (p[0].x + p[1].x) * 0.5f, (p[0].y + p[1].y) * 0.5f);}
	MREAL GetWidth()
						{ return (p[1].x - p[0].x);}
	MREAL GetHgt()
						{ return (p[1].y - p[0].y);}
	bool Overlap(const MgRect2D&, const MgRect2D);

	MgRect2D operator + ( const MgVect2D& pt) const									// rc1 = rc2 + pt
						{ return MgRect2D( p[0] + pt,
										   p[1] + pt);}
	MgRect2D operator - ( const MgVect2D& pt) const									// rc1 = rc2 - pt
						{ return MgRect2D( p[0] - pt,
										   p[1] - pt);}
	MgRect2D operator += ( const MgVect2D& pt)										// rc1 += pt
						{ p[0] += pt; p[1] += pt; return *this;}
	MgRect2D operator -= ( const MgVect2D& pt)										// rc1 -= pt
						{ p[0] -= pt; p[1] -= pt; return *this;}
	friend MgRect2D operator * ( MREAL rsc, const MgRect2D &rc)						// rc1 = rsc * rc2
						{ return MgRect2D( rc.p[0].x * rsc, rc.p[0].y * rsc, 
										   rc.p[1].x * rsc, rc.p[1].y * rsc);}
	MgRect2D operator * ( MREAL rsc) const											// rc1 = rc2 * rsc
						{ return MgRect2D( p[0].x * rsc, p[0].y * rsc, 
										   p[1].x * rsc, p[1].y * rsc);}
	MgRect2D operator / ( MREAL rsc) const											// rc1 = rc2 / rsc
						{ return MgRect2D( p[0].x / rsc, p[0].y / rsc, 
										   p[1].x / rsc, p[1].y / rsc);}
	MgRect2D operator *= ( MREAL rsc)												// rc1 *= rsc
						{ return MgRect2D( p[0].x *= rsc, p[0].y *= rsc, 
										   p[1].x *= rsc, p[1].y *= rsc);}
	MgRect2D operator /= ( MREAL rsc)												// rc1 /= rsc
						{ return MgRect2D( p[0].x /= rsc, p[0].y /= rsc, 
										   p[1].x /= rsc, p[1].y /= rsc);}

	void Print(MCHAR* s);															// print
};
//
//======================( �R���� )==============================
//	������
class DLL_EXPORT_RECT MgRect3D
{
public:
	MgPoint3D p[2];
//
public:
	MgRect3D() {};
	MgRect3D(MREAL r1x, MREAL r1y, MREAL r1z, 
		    MREAL r2x, MREAL r2y, MREAL r2z) {
			p[0].x = r1x; p[0].y = r1y; p[0].z = r1z;
			p[1].x = r2x; p[1].y = r2y; p[1].z = r2z;}
	MgRect3D(const MgPoint3D& min, const MgPoint3D& max) {
			p[0].x = min.x; p[0].y = min.y; p[0].z = min.z;
			p[1].x = max.x; p[1].y = max.y; p[1].z = max.z;}
	void SetUnit();
	MgPoint3D GetCenter()
						{ return MgPoint3D( (p[0].x + p[1].x) * 0.5f,
										   (p[0].y + p[1].y) * 0.5f,
										   (p[0].z + p[1].z) * 0.5f);}
	MREAL GetWidth()
						{ return (p[1].x - p[0].x);}
	MREAL GetHgt()
						{ return (p[1].y - p[0].y);}
	MREAL GetDepth()
						{ return (p[1].z - p[0].z);}
	bool Overlap(const MgRect3D&, const MgRect3D);

	MgRect3D operator + ( const MgVect3D& pt) const									// rc1 = rc2 + pt
						{ return MgRect3D( p[0] + pt,
										   p[1] + pt);}
	MgRect3D operator - ( const MgVect3D& pt) const									// rc1 = rc2 - pt
						{ return MgRect3D( p[0] - pt,
										   p[1] - pt);}
	MgRect3D operator += ( const MgVect3D& pt)										// rc1 += pt
						{ p[0] += pt; p[1] += pt; return *this;}
	MgRect3D operator -= ( const MgPoint3D& pt)										// rc1 -= pt
						{ p[0] -= pt; p[1] -= pt; return *this;}

	friend MgRect3D operator * ( MREAL rsc, const MgRect3D &rc)						// rc1 = rsc * rc2
						{ return MgRect3D( rc.p[0].x * rsc, rc.p[0].y * rsc, rc.p[0].z * rsc,
										   rc.p[1].x * rsc, rc.p[1].y * rsc, rc.p[1].z * rsc);}
	MgRect3D operator * ( MREAL rsc) const											// rc1 = rc2 * rsc
						{ return MgRect3D( p[0].x * rsc, p[0].y * rsc, p[0].z * rsc,
										   p[1].x * rsc, p[1].y * rsc, p[1].z * rsc);}
	MgRect3D operator / ( MREAL rsc) const											// rc1 = rc2 / rsc
						{ return MgRect3D( p[0].x / rsc, p[0].y / rsc, p[0].z / rsc,
										   p[1].x / rsc, p[1].y / rsc, p[1].z / rsc);}
	MgRect3D operator *= ( MREAL rsc)												// rc1 *= rsc
						{ return MgRect3D( p[0].x *= rsc, p[0].y *= rsc, p[0].z *= rsc,
										   p[1].x *= rsc, p[1].y *= rsc, p[1].z *= rsc);}
	MgRect3D operator /= ( MREAL rsc)												// rc1 /= rsc
						{ return MgRect3D( p[0].x /= rsc, p[0].y /= rsc, p[0].z /= rsc,
										   p[1].x /= rsc, p[1].y /= rsc, p[1].z /= rsc);}

	void Print(MCHAR* s);															// print
};

inline MINT SZMgMinMaxI2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgMinMaxI2D));}
inline MINT SZMgMinMaxR2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgMinMaxR2D));}
inline MINT SZMgMinMaxR3D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgMinMaxR3D));}
inline MINT SZMgRect2D( MINT i_sz = 1)		{ return  ( i_sz * (MINT)sizeof( MgRect2D));}
inline MINT SZMgRect3D( MINT i_sz = 1)		{ return  ( i_sz * (MINT)sizeof( MgRect3D));}

inline MINT WSZMgMinMaxI2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgMinMaxI2D) / SZMINT());}
inline MINT WSZMgMinMaxR2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgMinMaxR2D) / SZMINT());}
inline MINT WSZMgMinMaxR3D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgMinMaxR3D) / SZMINT());}
inline MINT WSZMgRect2D( MINT i_sz = 1)		{ return  ( i_sz * (MINT)sizeof( MgRect2D) / SZMINT());}
inline MINT WSZMgRect3D( MINT i_sz = 1)		{ return  ( i_sz * (MINT)sizeof( MgRect3D) / SZMINT());}

} // namespace MC
