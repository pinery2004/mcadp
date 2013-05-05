#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgLine.h
//
//		ê¸(line)Ç∆ê¸ï™(UnboundedLine)ÇÃíËã`ÅAï“èW
//
//		îºíºê¸(lay)ÇÕñ¢ëŒâû
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//
#include "MsDefFunc.h"
#include "MgPoint.h"

//#include "mdPlex.h"

#ifdef DLL_EXPORT_LINE
	#undef DLL_EXPORT_LINE
#endif

#ifdef DLL_EXPORT_LINE_DO
	#pragma message( "<<< MgLineÅEdll_EXport >>>")
	#define DLL_EXPORT_LINE							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode Ç≈ inlineä÷êîÇ™undefÇ…Ç»ÇÈïsãÔçáëŒâû
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_LINE
		#else
//			#pragma message( "=== MgLineÅEdll_IMport ===")
			#define DLL_EXPORT_LINE						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_LINE
	#endif
#endif

namespace MC
{

class	MgULine2D;
class	MgULine3D;
class	MgHLine2D;
class	MgHLine3D;
class	MgLine2D;
class	MgLine3D;
class	MgPlane3D;

//
//==========================================================================================
//
// ---------------------( ÇQéüå≥ )------------------------------
//
//	ÇQéüå≥íºê¸	(UnboundedLine)
//
class DLL_EXPORT_LINE MgULine2D
{
public:
	MgPoint2D	p;																// í âﬂì_
	MgVect2D	v;																// íºê¸ï˚å¸

	MgULine2D()			{}

	MgULine2D( const MgPoint2D& p1, const MgVect2D& v1)
						{ p = p1; v = v1;}										
	bool operator == ( const MgULine2D& ULn1) const;							// b = (uln == ULn1) îªíË

	bool operator != ( const MgULine2D& ULn1) const								// b = (uln != ULn1) îªíË
						{ return !((*this) == ULn1);}
	MgULine2D Set( const MgPoint2D& p1, const MgVect2D& v1)
						{ p = p1; v = v1; return *this;}										
	MgULine2D Set( const MgULine3D& ULn1);										// ÇRéüå≥íºê¸ Å® ÇQéüå≥íºê¸

	void SetRev()																// íºê¸îΩì]
						{ v = - v;}
	void Print(MCHAR* s);
};
//
// ---------------------( ÇQéüå≥ )------------------------------
//
//	ÇQéüå≥îºíºê¸	(HalfUnboundedLine)
//
class DLL_EXPORT_LINE MgHLine2D
{
public:
	MgPoint2D	p;																// énì_
	MgVect2D	v;																// îºíºê¸ï˚å¸

	MgHLine2D()			{}

	MgHLine2D( const MgPoint2D& p1, const MgVect2D& v1)
						{ p = p1; v = v1;}										
	bool operator == ( const MgHLine2D &ULn1) const;							// b = (uln == ULn1) îªíË

	bool operator != ( const MgHLine2D &ULn1) const								// b = (uln != ULn1) îªíË
						{ return !((*this) == ULn1);}
	MgHLine2D Set( const MgPoint2D& p1, const MgVect2D& v1)
						{ p = p1; v = v1; return *this;}										
	MgHLine2D Set( const MgHLine3D &ULn1);										// ÇRéüå≥íºê¸ Å® ÇQéüå≥íºê¸

	void SetRev()																// íºê¸îΩì]
						{ v = - v;}
	void Print(MCHAR* s);
};
//
//  ÇQéüå≥ê¸ï™ 	(Line)
//
class DLL_EXPORT_LINE MgLine2D
{
public:
	MgPoint2D	p[2];															// énì_ÅAèIì_

	MgLine2D()			{}

	MgLine2D( const MgPoint2D& ps, const MgPoint2D& pe)
						{ p[0] = ps; p[1] = pe;}
	MgLine2D( const MgPoint2D *pi)
						{ p[0] = pi[0]; p[1] = pi[1];}

	MgLine2D operator + ( const MgVect2D& v) const;								// Ln1 = Ln2 + V3

	MgLine2D operator - ( const MgVect2D& v) const;								// Ln1 = Ln2 + V3

	MgLine2D operator += ( const MgVect2D& v);									// Ln1 += P2

	MgLine2D operator -= ( const MgVect2D& v);									// Ln1 += P2

	bool operator == ( const MgLine2D& Ln1) const;								// b = (ln == Ln1) îªíË

	bool operator != ( const MgLine2D& Ln1) const								// b = (ln != Ln1) îªíË
						{ return !((*this) == Ln1);}
	MgLine2D Set( const MREAL &psx, const MREAL &psy,
				 const MREAL &pex, const MREAL &pey)
						{ p[0].x = psx; p[0].y = psy; 
						  p[1].x = pex; p[1].y = pey; return *this;}
	MgLine2D Set( const MgPoint2D& ps, const MgPoint2D& pe)
						{ p[0] = ps; p[1] = pe; return *this;}
	MgLine2D Set( const MgPoint2D *pi)
						{ p[0] = pi[0]; p[1] = pi[1]; return *this;}										
	MgLine2D Set( const MgLine3D& Ln1);											// ÇRéüå≥(x,y) Å® ÇQéüå≥

	MgLine2D SetRev()															// ê¸ï™ îΩì]
						{ msSwap( p[0], p[1]); return *this;}
	MgVect2D Vu()
						{ MgVect2D v1 = p[1] - p[0]; return v1.Unitize();}
	void Print(MCHAR* s);
};
//
// ---------------------( ÇRéüå≥ )------------------------------
//
//	ÇRéüå≥íºê¸
//
class DLL_EXPORT_LINE MgULine3D
{
public:
	MgPoint3D	p;																// í âﬂì_
	MgVect3D	v;																// íºê¸ï˚å¸

	MgULine3D()			{}
	
	MgULine3D( const MgPoint3D& p1, const MgVect3D& v1)
						{ p = p1; v = v1;}
	bool operator == ( const MgULine3D& ULn1) const;							// b = (uln == ULn1) îªíË

	bool operator != ( const MgULine3D& ULn1) const								// b = (uln != ULn1) îªíË
						{ return !((*this) == ULn1);}
	MgULine3D Set( const MgPoint3D& p1, const MgVect3D& v1)
						{ p = p1; v = v1; return *this;}
	MgULine3D Set( const MgULine2D& uln1, const MREAL z1 = 0.f, MREAL i_Tol = MGPTOL->D)	// ÇQéüå≥Å®ÇRéüå≥Å@(Zè»ó™0.)
						{ p.x = uln1.p.x; p.y = uln1.p.y; p.z = z1;
						  v = MgVect3DC( uln1.v).Unitize(i_Tol); return *this;} 
	MgULine3D Set( const MgULine2D& ULn1, const MgPlane3D& Pln, MREAL i_Tol = MGPTOL->D);// ÇQéüå≥Å®ÇRéüå≥

	MgULine3D SetRev()	{ v = - v; return *this;}								// íºê¸îΩì]
	void Print(MCHAR* s);
};

//
// ---------------------( ÇRéüå≥ )------------------------------
//
//	ÇRéüå≥îºíºê¸
//
class DLL_EXPORT_LINE MgHLine3D
{
public:
	MgPoint3D	p;																// énì_
	MgVect3D	v;																// îºíºê¸ï˚å¸

	MgHLine3D()			{}

	MgHLine3D( const MgPoint3D& p1, const MgVect3D& v1)
						{ p = p1; v = v1;}

	bool operator == ( const MgHLine3D &ULn1) const;							// b = (uln == ULn1) îªíË

	bool operator != ( const MgHLine3D &ULn1) const								// b = (uln != ULn1) îªíË
						{ return !((*this) == ULn1);}
	MgHLine3D Set( const MgPoint3D& p1, const MgVect3D& v1)
						{ p = p1; v = v1; return *this;}
	MgHLine3D Set( const MgHLine2D &uln1, const MREAL z1 = 0.f)					// ÇQéüå≥Å®ÇRéüå≥Å@(Zè»ó™0.)
						{ p.x = uln1.p.x; p.y = uln1.p.y; p.z = z1;
						  v = MgVect3DC( uln1.v).Unitize(); return *this;} 
	MgHLine3D Set( const MgHLine2D &ULn1, const MgPlane3D& Pln);				// ÇQéüå≥Å®ÇRéüå≥

	MgHLine3D SetRev()	{ v = - v; return *this;}								// îºíºê¸îΩì]
	void Print(MCHAR* s);
};

//
//	ÇRéüå≥ê¸ï™
//
class DLL_EXPORT_LINE MgLine3D
{
public:
	MgPoint3D	p[2];															// énì_ÅAèIì_

	MgLine3D()			{}

	MgLine3D( const MgPoint3D& ps, const MgPoint3D& pe)
						{ p[0] = ps; p[1] = pe;}
	MgLine3D( const MgPoint3D *pi)
						{ p[0] = pi[0]; p[1] = pi[1];}										
	MgLine3D( const MREAL &psx, const MREAL &psy, const MREAL &psz,
			 const MREAL &pex, const MREAL &pey, const MREAL &pez)
						{ p[0].x = psx; p[0].y = psy; p[0].z = psz; 
						  p[1].x = pex; p[1].y = pey; p[1].z = pez;}
	MgLine3D operator + ( const MgVect3D& v) const;								// Ln1 = Ln2 + p3

	MgLine3D operator - ( const MgVect3D& v) const;								// Ln1 = Ln2 + p3

	MgLine3D operator += ( const MgVect3D& v);									// Ln1 += P2

	MgLine3D operator -= ( const MgVect3D& v);									// Ln1 += P2

	bool operator == ( const MgLine3D& Ln1) const;								// b = (ln == Ln1) îªíË

	bool operator != ( const MgLine3D& Ln1) const								// b = (ln != Ln1) îªíË
						{ return !((*this) == Ln1);}
	MgLine3D Set( const MgPoint3D& ps, const MgPoint3D& pe)						// énì_ÅAèIì_
						{ p[0] = ps; p[1] = pe; return *this;}
	MgLine3D Set( const MgPoint3D *pi)											// ÇQì_
						{ p[0] = pi[0]; p[1] = pi[1]; return *this;}										
	MgLine3D Set( const MREAL &psx, const MREAL &psy, const MREAL &psz,			// 2*3é¿êî
				 const MREAL &pex, const MREAL &pey, const MREAL &pez)
						{ p[0].x = psx; p[0].y = psy; p[0].z = psz; 
						  p[1].x = pex; p[1].y = pey; p[1].z = pez;
						  return *this;}
	MgLine3D Set( const MgLine2D& ln1, MREAL z = 0.)							// ÇQéüå≥Å®ÇRéüå≥Å@(Zè»ó™0.)
						{ p[0].x = ln1.p[0].x; p[0].y = ln1.p[0].y; p[0].z = z;
						  p[1].x = ln1.p[1].x; p[1].y = ln1.p[1].y; p[1].z = z;
						  return *this;}
	MgLine3D Set( const MgLine2D& ln1, const MgPlane3D& Pln);					// ÇQéüå≥Å®ÇRéüå≥

	MgLine3D SetRev()
						{ msSwap( p[0], p[1]); return *this;}					// ê¸ï™ îΩì]
	MgVect3D	Vu()
						{ MgVect3D v1 = p[1] - p[0]; return v1.Unitize();}		// ê¸ï™ÇÃï˚å¸(íPà ÉxÉNÉgÉã)
	void Print(MCHAR* s);
};
//
//==========================================================================================
//
// ---------------------( ÇQéüå≥ )------------------------------
//
//	ÇQéüå≥íºê¸
//
inline MgULine2D MgULine2DC( const MgPoint2D& p1, const MgVect2D& v1)						// í âﬂì_Ç∆ï˚å¸íPà ÉxÉNÉgÉãÇÊÇËÇQéüå≥íºê¸ÇãÅÇﬂÇÈ
						{ MgULine2D ULno; ULno.p = p1; ULno.v = v1; return ULno;}										
inline MgULine2D MgULine2DC( const MgULine3D& ULn1)											// ÇRéüå≥(x,y) Å® ÇQéüå≥
						{ MgULine2D ULno; ULno.p.x = ULn1.p.x; ULno.p.y = ULn1.p.y;
						  ULno.v.x = ULn1.v.x, ULno.v.y = ULn1.v.y; return ULno;} 
inline MgULine2D MgULine2D::Set( const MgULine3D& ULn1)										// ÇRéüå≥(x,y) Å® ÇQéüå≥
						{ MgULine2D ULno; ULno.p.x = ULn1.p.x; ULno.p.y = ULn1.p.y;
						  ULno.v.x = ULn1.v.x; ULno.v.y = ULn1.v.y; return ULno;} 
//
//	ÇQéüå≥ê¸ï™
//
inline MgLine2D MgLine2DC( const MgLine3D& Ln1)												// ÇRéüå≥(x,y)Å®ÇQéüå≥
						{ MgLine2D Lno; Lno.p[0].x = Ln1.p[0].x; Lno.p[0].y = Ln1.p[0].y;
						  Lno.p[1].x = Ln1.p[1].x; Lno.p[1].y = Ln1.p[1].y; return Lno;} 
inline MgLine2D MgLine2DC( const MgPoint3D& Ps, const MgPoint3D& Pe)						// ÇRéüå≥(x,y)Å®ÇQéüå≥
						{ MgLine2D Lno; Lno.p[0].x = Ps.x; Lno.p[0].y = Ps.y;
						  Lno.p[1].x = Pe.x; Lno.p[1].y = Pe.y; return Lno;} 
inline MgLine2D MgLine2DC( const MgPoint3D *Pi)												// ÇRéüå≥(x,y)Å®ÇQéüå≥
						{ MgLine2D Lno; Lno.p[0].x = Pi[0].x; Lno.p[0].y = Pi[0].y;
						  Lno.p[1].x = Pi[1].x; Lno.p[1].y = Pi[1].y; return Lno;} 

inline MgVect2D MgVect2DC( const MgLine2D& Ln1)												// Line2 Å® Vect2
						{ return ( Ln1.p[1] - Ln1.p[0]);}
inline MgLine2D MgLine2D::operator + ( const MgVect2D& v) const								// Ln1 = Ln2 + p3
				 		{ return MgLine2D( MgPoint2D( p[0].x + v.x, p[0].y + v.y),
										  MgPoint2D( p[1].x + v.x, p[1].y + v.y));}
inline MgLine2D MgLine2D::operator - ( const MgVect2D& v) const								// Ln1 = Ln2 + p3
				 		{ return MgLine2D( MgPoint2D( p[0].x - v.x, p[0].y - v.y),
										  MgPoint2D( p[1].x - v.x, p[1].y - v.y));}
inline MgLine2D MgLine2D::operator += ( const MgVect2D& v)									// Ln1 += P2
				 		{ return MgLine2D( MgPoint2D( p[0].x += v.x, p[0].y += v.y),
										  MgPoint2D( p[1].x += v.x, p[1].y += v.y));}
inline MgLine2D MgLine2D::operator -= ( const MgVect2D& v)									// Ln1 += P2
				 		{ return MgLine2D( MgPoint2D( p[0].x -= v.x, p[0].y -= v.y),
										  MgPoint2D( p[1].x -= v.x, p[1].y -= v.y));}
inline MgLine2D MgLine2D::Set( const MgLine3D& Ln1)											// ÇRéüå≥(x,y)Å®ÇQéüå≥
						{ MgLine2D Lno; Lno.p[0].x = Ln1.p[0].x; Lno.p[0].y = Ln1.p[0].y;
						  Lno.p[1].x = Ln1.p[1].x; Lno.p[1].y = Ln1.p[1].y;
						  return Lno;} 

// ---------------------( ÇRéüå≥ )------------------------------
//
//	ÇRéüå≥íºê¸
//
inline MgULine3D MgULine3DC( const MgULine2D& uln1, const MREAL z1 = 0.f)						// ÇQéüå≥Å®ÇRéüå≥Å@(Zè»ó™0.)
						{ MgULine3D ULno; ULno.p.x = uln1.p.x; ULno.p.y = uln1.p.y; ULno.p.z = z1;
//KM					  ULno.v = MgPoint3DC( uln1.p).Unitize(); return ULno;} 
						  ULno.v = MgVect3DC( uln1.v).Unitize(); return ULno;} 
inline MgULine3D MgULine3DC( const MgULine2D& ULn1, const MgPlane3D& Pln);						// ÇQéüå≥Å®ÇRéüå≥

inline MgLine3D MgLine3DC( const MgLine2D& ln1, MREAL z = 0.)									// ÇQéüå≥Å®ÇRéüå≥Å@(Zè»ó™0.)
						{ MgLine3D Lno; Lno.p[0].x = ln1.p[0].x; Lno.p[0].y = ln1.p[0].y;
									   Lno.p[0].z = z;
									   Lno.p[1].x = ln1.p[1].x; Lno.p[1].y = ln1.p[1].y;
									   Lno.p[1].z = z; return Lno;}
inline MgLine3D MgLine3DC( const MgLine2D& ln1, const MgPlane3D& Pln);							// ÇQéüå≥Å®ÇRéüå≥

inline MgLine3D MgLine3DC( const MgPoint2D& ps, const MgPoint2D& pe, MREAL z = 0.)				// ÇQéüå≥Å®ÇRéüå≥Å@(Zè»ó™0.)
						{ MgLine3D Lno; Lno.p[0].x = ps.x; Lno.p[0].y = ps.y; Lno.p[0].z = z;
						  Lno.p[1].x = pe.x; Lno.p[1].y = pe.y; Lno.p[1].z = z; return Lno;} 
inline MgLine3D MgLine3DC( const MgPoint2D& ps, const MgPoint2D& pe, const MgPlane3D& Pln)		// ÇQéüå≥Å®ÇRéüå≥
							{ return MgLine3DC( MgLine2D( ps, pe), Pln);} 
inline MgLine3D MgLine3DC( const MgPoint2D *pi, MREAL z = 0.)									// ÇQéüå≥Å®ÇRéüå≥Å@(Zè»ó™0.)
						{ MgLine3D Lno; Lno.p[0].x = pi[0].x; Lno.p[0].y = pi[0].y; Lno.p[0].z = z;
						  Lno.p[1].x = pi[1].x; Lno.p[1].y = pi[1].y; Lno.p[1].z = z; return Lno;} 
inline MgLine3D MgLine3DC( const MgPoint2D *pi, const MgPlane3D& Pln)		// ÇQéüå≥Å®ÇRéüå≥
							{ return MgLine3DC( MgLine2D( pi), Pln);} 
inline MgVect3D MgVect3DC( const MgLine3D& Ln1)												// Line3 Å® Vect3
						{ return ( Ln1.p[1] - Ln1.p[0]);}
inline MgLine3D MgLine3D::operator + ( const MgVect3D& v) const								// Ln1 = Ln2 + p3
				 		{ return MgLine3D( p[0].x + v.x, p[0].y + v.y, p[0].z + v.z,
										  p[1].x + v.x, p[1].y + v.y, p[1].z + v.z);}
inline MgLine3D MgLine3D::operator - ( const MgVect3D& v) const								// Ln1 = Ln2 + p3
				 		{ return MgLine3D( p[0].x - v.x, p[0].y - v.y, p[0].z - v.z,
										  p[1].x - v.x, p[1].y - v.y, p[1].z - v.z);}
inline MgLine3D MgLine3D::operator += ( const MgVect3D& v)									// Ln1 += P2
				 		{ return MgLine3D( p[0].x += v.x, p[0].y += v.y, p[0].z += v.z,
										  p[1].x += v.x, p[1].y += v.y, p[1].z += v.z);}
inline MgLine3D MgLine3D::operator -= ( const MgVect3D& v)									// Ln1 += P2
				 		{ return MgLine3D( p[0].x -= v.x, p[0].y -= v.y, p[0].z -= v.z,
										  p[1].x -= v.x, p[1].y -= v.y, p[1].z -= v.z);}

// ÉTÉCÉY
inline MINT SZMgULine2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgULine2D));}
inline MINT SZMgULine3D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgULine3D));}
inline MINT SZMgHLine2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgHLine2D));}
inline MINT SZMgHLine3D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgHLine3D));}
inline MINT SZMgLine2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgLine2D));}
inline MINT SZMgLine3D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgLine3D));}
inline MINT WSZMgULine2D( MINT i_sz = 1){ return  ( i_sz * (MINT)sizeof( MgULine2D) / SZMINT());}
inline MINT WSZMgULine3D( MINT i_sz = 1){ return  ( i_sz * (MINT)sizeof( MgULine3D) / SZMINT());}
inline MINT WSZMgHLine2D( MINT i_sz = 1){ return  ( i_sz * (MINT)sizeof( MgHLine2D) / SZMINT());}
inline MINT WSZMgHLine3D( MINT i_sz = 1){ return  ( i_sz * (MINT)sizeof( MgHLine3D) / SZMINT());}
inline MINT WSZMgLine2D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgLine2D) / SZMINT());}
inline MINT WSZMgLine3D( MINT i_sz = 1)	{ return  ( i_sz * (MINT)sizeof( MgLine3D) / SZMINT());}

} // namespace MC
