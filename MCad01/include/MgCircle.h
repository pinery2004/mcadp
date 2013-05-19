#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgCir.h
//
//		�~(Cir)�̒�`�A�ҏW
//
//  K.Matsu           09/20/07    Created.
//==========================================================================================
//
#include "MgPoint.h"

#include "mdPlex.h"

#ifdef DLL_EXPORT_CIR
	#undef DLL_EXPORT_CIR
#endif

#ifdef DLL_EXPORT_CIRCLE_DO
	#pragma message( "<<< MgCir�Edll_EXport >>>")
	#define DLL_EXPORT_CIR							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_CIR
		#else
//			#pragma message( "=== MgCir�Edll_IMport ===")
			#define DLL_EXPORT_CIR						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT_CIR
	#endif
#endif

namespace MC
{

class	MgCir2D;
class	MgCir3D;
class	MgPlane3D;

//
// ---------------------( �Q���� )------------------------------
//
//  �Q�����~ 	(Cir)
//
class DLL_EXPORT_CIR MgCir2D
{
public:
	MgPoint2D	pc;							// ���S�_
	MREAL		r;							// ���a
	
	MgCir2D()			{}

	MgCir2D( const MgPoint2D& pc1, MREAL r1)
						{ pc = pc1; r = r1;}

	bool operator == ( const MgCir2D &cir1) const								// b = (cir == cir1) ����
						{ return ( pc == cir1.pc && MgTol::MgEQ( r, cir1.r));}

	bool operator != ( const MgCir2D &cir1) const								// b = (cir != cir1) ����
						{ return !((*this) == cir1);}

	MgCir2D Set( const MgPoint2D& pc1, MREAL r1)
						{ pc = pc1; r = r1; return *this;}
	MgCir2D Set( const MgCir3D &Cir1);											// �R����(x,y) �� �Q����
	
	void Print(MCHAR* s);
};

//
// ---------------------( �R���� )------------------------------
//
//	�R�����~
//
class DLL_EXPORT_CIR MgCir3D
{
public:
	MgPoint3D	Pc;							// ���S�_
	MgVect3D	V;							// �@���P�ʃx�N�g��
	MREAL		r;							// ���a

	MgCir3D()			{}

	MgCir3D( const MgPoint3D& Pc1, const MgVect3D& V1, MREAL r1)
						{ Pc = Pc1; V = V1; r = r1;}

	MgCir3D Set( const MgPoint3D& Pc1, const MgVect3D V1, MREAL r1)
						{ Pc = Pc1; V = V1; r = r1; return *this;}

	MgCir3D Set( const MgCir2D &cir1, MREAL z = 0.)								// �Q�������R����	(Z�ȗ�0.)
//						{ Pc.Set( cir1.pc, z);
						{ Pc = MgPoint3D( cir1.pc, z);
						  V = MgVect3D( 0., 0., 1.);
						  r = cir1.r; return *this;}

	MgCir3D Set( const MgCir2D &cir1, const MgPlane3D& Pln)						// �Q�������R����	(���ʏ�)
						{ Pc.Set( cir1.pc, Pln);
						  V = Pln.v; r = cir1.r; return *this;}

	void Print(MCHAR* s);
};

// ---------------------( �Q���� )------------------------------
//
//	�Q�����~
//
//inline MgCir2D MgCir2DC( const MgCir3D &Cir1)									// �R����(x,y)���Q����
//						{ MgCir2D ciro; ciro.pc.Set( Cir1.Pc);
//						  ciro.r = Cir1.r; return ciro;} 
//
//inline MgCir2D MgCir2DC( const MgPoint3D& Pc, MREAL r1)						// �R����(x,y)���Q����
//						{ MgCir2D ciro; ciro.pc.Set( Pc);
//						  ciro.r = r1; return ciro;} 

inline MgCir2D MgCir2D::Set( const MgCir3D &Cir1)								// �R����(x,y)���Q����
						{ MgCir2D ciro;
						  ciro.pc.x = Cir1.Pc.x; ciro.pc.y = Cir1.Pc.y;
						  ciro.r = Cir1.r; return ciro;} 

MINT DLL_EXPORT_CIR MgCir2DDiv ( const MgCir2D &cir1, MINT n, const MgPoint2D& pts,	// �~��n��������
							MgGPoint2D *gpto);


// ---------------------( �R���� )------------------------------
//
//	�R�����~
//
inline MgCir3D MgCir3DC( const MgCir2D &cir1, MREAL z = 0.)						// �Q�������R����	(Z�ȗ�0.)
//						{ MgCir3D Ciro; Ciro.Pc.Set( cir1.pc, z);
						{ MgCir3D Ciro; Ciro.Pc = MgPoint3D( cir1.pc, z);
						  Ciro.V = MgVect3D( 0., 0., 1.);
						  Ciro.r = cir1.r; return Ciro;}

inline MgCir3D MgCir3DC( const MgCir2D &cir1, const MgPlane3D& Pln)				// �Q�������R����	(���ʏ�)
						{ MgCir3D Ciro; Ciro.Pc.Set( cir1.pc, Pln);
						  Ciro.V = Pln.v;
						  Ciro.r = cir1.r; return Ciro;}

inline MgCir3D MgCir3DC( const MgPoint2D& pc, MREAL r, MREAL z = 0.)			// �Q�������R����	(Z�ȗ�0.)
//						{ MgCir3D Ciro; Ciro.Pc.Set( pc, z);
						{ MgCir3D Ciro; Ciro.Pc = MgPoint3D( pc, z);
						  Ciro.V = MgVect3D( 0., 0., 1.);
						  Ciro.r = r; return Ciro;}

inline MgCir3D MgCir3DC( const MgPoint2D& pc, MREAL r, const MgPlane3D& Pln)	// �Q�������R����	(���ʏ�)
						{ MgCir3D Ciro; Ciro.Pc.Set( pc, Pln);
						  Ciro.V = Pln.v;
						  Ciro.r = r; return Ciro;}

MINT DLL_EXPORT_CIR MgCir3DDiv ( const MgCir3D &Cir1, MINT n, const MgPoint3D& Parts,	// �~��n��������
							MgGPoint3D *gPto);

inline int SZMgCir2D( int i_sz)		{ return  ( i_sz * (int)sizeof( MgCir2D));}
inline int SZMgCir2D()				{ return  (int)sizeof( MgCir2D);}
inline int SZMgCir3D( int i_sz)		{ return  ( i_sz * (int)sizeof( MgCir3D));}
inline int SZMgCir3D()				{ return  (int)sizeof( MgCir3D);}
inline int WSZMgCir2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgCir2D) / SZMINT());}
inline int WSZMgCir2D()				{ return  (int)sizeof( MgCir2D) / SZMINT();}
inline int WSZMgCir3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgCir3D) / SZMINT());}
inline int WSZMgCir3D()				{ return  (int)sizeof( MgCir3D) / SZMINT();}

} // namespace MC
