#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgArc.h
//
//		â~å (Arc)ÇÃíËã`ÅAï“èW
//
//  K.Matsu           09/20/07    Created.
//==========================================================================================
//
#include "MgPoint.h"

#include "mdPlex.h"

#ifdef DLL_EXPORT_ARC
	#undef DLL_EXPORT_ARC
#endif

#ifdef DLL_EXPORT_ARC_DO
	#pragma message( "<<< MgArcÅEdll_EXport >>>")
	#define DLL_EXPORT_ARC							 __declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode Ç≈ inlineä÷êîÇ™undefÇ…Ç»ÇÈïsãÔçáëŒâû
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_ARC
		#else
//			#pragma message( "=== MgArcÅEdll_IMport ===")
			#define DLL_EXPORT_ARC						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_ARC
	#endif
#endif

namespace MC
{

class	MgArc2D;
class	MgArc3D;
class	MgPlane3D;

// ---------------------( ÇQéüå≥ )------------------------------
//
//  ÇQéüå≥â~å  	(Arc)
//
class DLL_EXPORT_ARC MgArc2D
{
public:
	MgPoint2D	pt[2];						// énì_ÅAèIì_íl	( x, y )
	MgPoint2D	pc;							// íÜêSì_
	MREAL		r;							// îºåa
	
	MgArc2D()			{}

	MgArc2D( const MgPoint2D pt1[2], const MgPoint2D& pc1, MREAL r1)
						{ pt[0] = pt1[0]; pt[1] = pt1[1]; pc = pc1; r = r1;}

	MgArc2D( const MgPoint2D pt1, const MgPoint2D pt2, const MgPoint2D& pc1, MREAL r1)
						{ pt[0] = pt1; pt[1] = pt2; pc = pc1; r = r1;}

	bool operator == ( const MgArc2D &arc1) const								// b = (arc == arc1) îªíË
						{ return ( pc == arc1.pc && 
						  ( ( MgTol::MgEQ( r, arc1.r) && (pt[0] == arc1.pt[0]) && (pt[1] == arc1.pt[1])) ||
						    ( MgTol::MgEQ( r, - arc1.r) && (pt[0] == arc1.pt[1]) && (pt[1] == arc1.pt[0]))));}

	bool operator != ( const MgArc2D &arc1) const								// b = (arc != arc1) îªíË
						{ return !((*this) == arc1);}

	MgArc2D Set( const MgPoint2D pt1[2], const MgPoint2D& pc1, MREAL r1)
						{ pt[0] = pt1[0]; pt[1] = pt1[1]; pc = pc1; r = r1; return *this;}
							
	MgArc2D Set( const MgPoint2D pt1, const MgPoint2D pt2, const MgPoint2D& pc1, MREAL r1)
						{ pt[0] = pt1; pt[1] = pt2; pc = pc1; r = r1; return *this;}
							
	MgArc2D Set( const MgArc3D &Arc1);											// ÇRéüå≥(x,y) Å® ÇQéüå≥
	
	void Print(MCHAR* s);
};

//
// ---------------------( ÇRéüå≥ )------------------------------
//
//	ÇRéüå≥â~å 
//
class DLL_EXPORT_ARC MgArc3D
{
public:
	MgPoint3D	Pt[2];						// énì_ÅAèIì_íl	( x, y, z )
	MgPoint3D	Pc;							// íÜêSì_ç¿ïWíl	( x, y, z )
	MgVect3D	V;							// ñ@ê¸íPà ÉxÉNÉgÉã	( x, y, z )
	MREAL		r;							// îºåa

	MgArc3D()			{}

	MgArc3D( const MgPoint3D Pt1[2], const MgPoint3D& Pc1,
			const MgVect3D& V1, const MREAL r1)
						{ Pt[0] = Pt1[0]; Pt[1] = Pt1[1]; Pc = Pc1; V = V1; r = r1;}

	MgArc3D( const MgPoint3D& Pt1, const MgPoint3D& Pt2, const MgPoint3D& Pc1,
			const MgVect3D& V1, const MREAL r1)
						{ Pt[0] = Pt1; Pt[1] = Pt2; Pc = Pc1; V = V1; r = r1;}

	bool operator == ( const MgArc3D &Arc1) const								// b = (arc == arc1) îªíË
							{ MINT iFR; MINT iFV;
								if ( Pc != Arc1.Pc ) return false;
								if ( MgTol::MgEQ( r, Arc1.r)) iFR = 1;  
								else if ( MgTol::MgEQ( r, -Arc1.r)) iFR = -1;
								else return false;
								if ( V == Arc1.V ) iFV = 1;
								else if ( V == -Arc1.V ) iFV = -1;
								else return false;
								if ( iFR * iFV > 0 ) return ( Pt[0] == Arc1.Pt[0] && Pt[1] == Arc1.Pt[1]);
						  		else return ( Pt[0] == Arc1.Pt[1] && Pt[1] == Arc1.Pt[0]);}

	bool operator != ( const MgArc3D &Arc1) const								// b = (arc != arc1) îªíË
						{ return !((*this) == Arc1);}

	MgArc3D Set( const MgPoint3D Pt1[2], const MgPoint3D& Pc1, const MgVect3D V1, MREAL r1)
						{ Pt[0] = Pt1[0]; Pt[1] = Pt1[1]; Pc = Pc1;
						  V = V1; r = r1; return *this;}

	MgArc3D Set( const MgPoint3D Pt1, const MgPoint3D Pt2, const MgPoint3D& Pc1,
				const MgVect3D V1, const MREAL r1)
						{ Pt[0] = Pt1; Pt[1] = Pt2; Pc = Pc1;
						  V = V1; r = r1; return *this;}

	MgArc3D Set( const MgArc2D &arc1, MREAL z = 0.)								// ÇQéüå≥Å®ÇRéüå≥	(Zè»ó™0.)
//						{ Pt[0].Set( arc1.pt[0], z); Pt[1].Set( arc1.pt[1], z);
//						  Pc.Set( arc1.pc, z); V = MgPoint3D( 0., 0., 1.);
						{ Pt[0] = MgPoint3D( arc1.pt[0], z); Pt[1] = MgPoint3D( arc1.pt[1], z);
						  Pc = MgPoint3D( arc1.pc, z); V = MgVect3D( 0., 0., 1.);
						  r = arc1.r; return *this;}

//	MgArc3D Set( const MgArc2D &arc1, const MgPlane3D& Pln)						// ÇQéüå≥Å®ÇRéüå≥	(ïΩñ è„)
////						{ Pt[0].Set( arc1.pt[0], Pln); Pt[1].Set( arc1.pt[1], Pln);
////						  Pc.Set( arc1.pc, Pln);
//						{ Pt[0] = MgPoint3D( arc1.pt[0], Pln); Pt[1] = MgPoint3D( arc1.pt[1], Pln);
//						  Pc = MgPoint3D( arc1.pc, Pln);
//						  V = Pln.v; r = arc1.r; return *this;}

	void Print(MCHAR* s);
};

// ---------------------( ÇQéüå≥ )------------------------------
//
//	ÇQéüå≥â~å 
//
inline MgArc2D MgArc2DC( const MgArc3D &Arc1)									// ÇRéüå≥(x,y)Å®ÇQéüå≥
//						{ MgArc2D arco; arco.pt[0].Set( Arc1.Pt[0]);
//						  arco.pt[1].Set( Arc1.Pt[1]); arco.pc.Set( Arc1.Pc);
						{ MgArc2D arco; arco.pt[0] = Arc1.Pt[0].To2D();
						  arco.pt[1] = Arc1.Pt[1].To2D(); arco.pc = Arc1.Pc.To2D();
						  arco.r = ( ( Arc1.V.z > 0) ? Arc1.r: -Arc1.r);
						  return arco;} 

inline MgArc2D MgArc2DC( const MgPoint3D Pt[2], const MgPoint3D& Pc,
					   const MREAL r1)											// ÇRéüå≥(x,y)Å®ÇQéüå≥
//						{ MgArc2D arco; arco.pt[0].Set( Pt[0]);
//						  arco.pt[1].Set( Pt[1]); arco.pc.Set( Pc);
						{ MgArc2D arco; arco.pt[0] = Pt[0].To2D();
						  arco.pt[1] = Pt[1].To2D(); arco.pc = Pc.To2D();
						  arco.r = r1; return arco;} 

inline MgArc2D MgArc2DC( const MgPoint3D Pt1, const MgPoint3D Pt2,
					   const MgPoint3D& Pc, const MREAL r1)						// ÇRéüå≥(x,y)Å®ÇQéüå≥
//						{ MgArc2D arco; arco.pt[0].Set( Pt1);
//						  arco.pt[1].Set( Pt2); arco.pc.Set( Pc);
						{ MgArc2D arco; arco.pt[0] = Pt1.To2D();
						  arco.pt[1] = Pt2.To2D(); arco.pc = Pc.To2D();
						  arco.r = r1; return arco;} 

inline MgArc2D MgArc2D::Set( const MgArc3D &Arc1)								// ÇRéüå≥(x,y)Å®ÇQéüå≥
//						{ MgArc2D arco; arco.pt[0].Set( Arc1.Pt[0]);
//						  arco.pt[1].Set( Arc1.Pt[1]);
						{ MgArc2D arco; arco.pt[0] = Arc1.Pt[0].To2D();
						  arco.pt[1] = Arc1.Pt[1].To2D();
						  arco.pc.x = Arc1.Pc.x; arco.pc.y = Arc1.Pc.y;
						  arco.r = Arc1.r; return arco;} 

// ---------------------( ÇRéüå≥ )------------------------------
//
//	ÇRéüå≥â~
//
inline MgArc3D MgArc3DC( const MgArc2D &arc1, MREAL z = 0.)						// ÇQéüå≥Å®ÇRéüå≥	(Zè»ó™0.)
//						{ MgArc3D Arco; Arco.Pc.Set( arc1.pc, z);
						{ MgArc3D Arco; Arco.Pc = MgPoint3D( arc1.pc, z);
						  Arco.V = MgVect3D( 0., 0., 1.);
						  Arco.r = arc1.r; return Arco;}

inline MgArc3D MgArc3DC( const MgArc2D &arc1, const MgPlane3D& Pln)				// ÇQéüå≥Å®ÇRéüå≥	(ïΩñ è„)
//						{ MgArc3D Arco; Arco.Pc.Set( arc1.pc, Pln);
						{ MgArc3D Arco; Arco.Pc = MgPoint3D( arc1.pc, Pln);
						  Arco.V = Pln.v;
						  Arco.r = arc1.r; return Arco;}

inline MgArc3D MgArc3DC( const MgPoint2D pt[2], const MgPoint2D& pc,
					   MREAL r, MREAL z = 0.)									// ÇQéüå≥Å®ÇRéüå≥	(Zè»ó™0.)
//						{ MgArc3D Arco; Arco.Pt[0].Set( pt[0], z);
//						  Arco.Pt[1].Set( pt[1], z); Arco.Pc.Set( pc, z);
						{ MgArc3D Arco; Arco.Pt[0] = MgPoint3D( pt[0], z);
						  Arco.Pt[1] = MgPoint3D( pt[1], z); Arco.Pc = MgPoint3D( pc, z);
						  Arco.V = MgVect3D( 0., 0., 1.);
						  Arco.r = r; return Arco;}

inline MgArc3D MgArc3DC( const MgPoint2D pt1, const MgPoint2D pt2,
					   const MgPoint2D& pc, MREAL r, MREAL z = 0.)				// ÇQéüå≥Å®ÇRéüå≥	(Zè»ó™0.)
//						{ MgArc3D Arco; Arco.Pt[0].Set( pt1, z);
//						  Arco.Pt[1].Set( pt2, z); Arco.Pc.Set( pc, z);
						{ MgArc3D Arco; Arco.Pt[0] = MgPoint3D( pt1, z);
						  Arco.Pt[1] = MgPoint3D( pt2, z); Arco.Pc = MgPoint3D( pc, z);
						  Arco.V = MgVect3D( 0., 0., 1.);
						  Arco.r = r; return Arco;}

inline MgArc3D MgArc3DC( const MgPoint2D pt[2], const MgPoint2D& pc,
					   const MREAL r, const MgPlane3D& Pln)						// ÇQéüå≥Å®ÇRéüå≥	(ïΩñ è„)
//						{ MgArc3D Arco; Arco.Pt[0].Set( pt[0], Pln);
//						  Arco.Pt[1].Set( pt[1], Pln); Arco.Pc.Set( pc, Pln);
						{ MgArc3D Arco; Arco.Pt[0] = MgPoint3D( pt[0], Pln);
						  Arco.Pt[1] = MgPoint3D( pt[1], Pln); Arco.Pc = MgPoint3D( pc, Pln);
						  Arco.V = Pln.v; Arco.r = r; return Arco;}

inline MgArc3D MgArc3DC( const MgPoint2D pt1, const MgPoint2D pt2,
					   const MgPoint2D& pc,
					   const MREAL r, const MgPlane3D& Pln)						// ÇQéüå≥Å®ÇRéüå≥	(ïΩñ è„)
//						{ MgArc3D Arco; Arco.Pt[0].Set( pt1, Pln);
//						  Arco.Pt[1].Set( pt2, Pln); Arco.Pc.Set( pc, Pln);
						{ MgArc3D Arco; Arco.Pt[0] = MgPoint3D( pt1, Pln);
						  Arco.Pt[1] = MgPoint3D( pt2, Pln); Arco.Pc = MgPoint3D( pc, Pln);
						  Arco.V = Pln.v; Arco.r = r; return Arco;}

// ÉTÉCÉY
inline int SZMgArc2D( int i_sz)		{ return ( i_sz * (int)sizeof( MgArc2D));}
inline int SZMgArc2D()				{ return (int)sizeof( MgArc2D);}
inline int SZMgArc3D( int i_sz)		{ return ( i_sz * (int)sizeof( MgArc3D));}
inline int SZMgArc3D()				{ return (int)sizeof( MgArc3D);}
inline int WSZMgArc2D( int i_sz)	{ return ( i_sz * (int)sizeof( MgArc2D) / SZMINT());}
inline int WSZMgArc2D()				{ return (int)sizeof( MgArc2D) / SZMINT();}
inline int WSZMgArc3D( int i_sz)	{ return ( i_sz * (int)sizeof( MgArc3D) / SZMINT());}
inline int WSZMgArc3D()				{ return (int)sizeof( MgArc3D) / SZMINT();}

} // namespace MC
