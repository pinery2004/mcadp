#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgLine.h
//
//		��(line)�Ɛ���(UnboundedLine)�̒�`�A�ҏW
//
//		������(lay)�͖��Ή�
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
	#pragma message( "<<< MgLine�Edll_EXport >>>")
	#define DLL_EXPORT_LINE							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_LINE
		#else
//			#pragma message( "=== MgLine�Edll_IMport ===")
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
// ---------------------( �Q���� )------------------------------
//
//	�Q��������	(UnboundedLine)
//
class DLL_EXPORT_LINE MgULine2D
{
public:
	MgPoint2D	p;																// �ʉߓ_
	MgVect2D	v;																// ��������

	// �R���X�g���N�^
	MgULine2D()			{}

	MgULine2D( MREAL x, MREAL y, MREAL vx, MREAL vy)
						{ p.x = x; p.y = y; v.x = vx; v.y = vy;}
	MgULine2D( const MgPoint2D& p1, const MgVect2D& v1)
						{ p = p1; v = v1;}										
	bool operator == ( const MgULine2D& ULn1) const;							// b = (uln == ULn1) ����

	bool operator != ( const MgULine2D& ULn1) const								// b = (uln != ULn1) ����
						{ return !((*this) == ULn1);}
	MgULine2D Set( const MgPoint2D& p1, const MgVect2D& v1)
						{ p = p1; v = v1; return *this;}										
	MgULine2D Set( const MgULine3D& ULn1);										// �R�������� �� �Q��������

	void SetRev()																// �������]
						{ v = - v;}
	void Print(MCHAR* s);
};
//
// ---------------------( �Q���� )------------------------------
//
//	�Q����������	(HalfUnboundedLine)
//
class DLL_EXPORT_LINE MgHLine2D
{
public:
	MgPoint2D	p;																// �n�_
	MgVect2D	v;																// ����������

	// �R���X�g���N�^
	MgHLine2D()			{}

	MgHLine2D( MREAL x, MREAL y, MREAL vx, MREAL vy)
						{ p.x = x; p.y = y; v.x = vx; v.y = vy;}
	MgHLine2D( const MgPoint2D& p1, const MgVect2D& v1)
						{ p = p1; v = v1;}										
	bool operator == ( const MgHLine2D &ULn1) const;							// b = (uln == ULn1) ����

	bool operator != ( const MgHLine2D &ULn1) const								// b = (uln != ULn1) ����
						{ return !((*this) == ULn1);}
	MgHLine2D Set( const MgPoint2D& p1, const MgVect2D& v1)
						{ p = p1; v = v1; return *this;}										
	MgHLine2D Set( const MgHLine3D &ULn1);										// �R�������� �� �Q��������

	void SetRev()																// �������]
						{ v = - v;}
	void Print(MCHAR* s);
};
//
//  �Q�������� 	(Line)
//
class DLL_EXPORT_LINE MgLine2D
{
public:
	MgPoint2D	p[2];															// �n�_�A�I�_

	// �R���X�g���N�^
	MgLine2D()			{}

	MgLine2D( MREAL x, MREAL y, MREAL vx, MREAL vy)
						{ p[0].x = x; p[0].y = y; p[1].x = vx; p[1].y = vy;}
	MgLine2D( const MgPoint2D& ps, const MgPoint2D& pe)
						{ p[0] = ps; p[1] = pe;}
	MgLine2D( const MgPoint2D *pi)
						{ p[0] = pi[0]; p[1] = pi[1];}

	MgLine2D operator + ( const MgVect2D& v) const;								// Ln1 = Ln2 + V3

	MgLine2D operator - ( const MgVect2D& v) const;								// Ln1 = Ln2 + V3

	MgLine2D operator += ( const MgVect2D& v);									// Ln1 += P2

	MgLine2D operator -= ( const MgVect2D& v);									// Ln1 += P2

	bool operator == ( const MgLine2D& Ln1) const;								// b = (ln == Ln1) ����

	bool operator != ( const MgLine2D& Ln1) const								// b = (ln != Ln1) ����
						{ return !((*this) == Ln1);}
	MgLine2D Set( MREAL psx, MREAL psy,
				  MREAL pex, MREAL pey)
						{ p[0].x = psx; p[0].y = psy; 
						  p[1].x = pex; p[1].y = pey; return *this;}
	MgLine2D Set( const MgPoint2D& ps, const MgPoint2D& pe)
						{ p[0] = ps; p[1] = pe; return *this;}
	MgLine2D Set( const MgPoint2D *pi)
						{ p[0] = pi[0]; p[1] = pi[1]; return *this;}										
	MgLine2D Set( const MgLine3D& Ln1);											// �R����(x,y) �� �Q����

	MgLine2D SetRev()															// ���� ���]
						{ msSwap( p[0], p[1]); return *this;}
	MgVect2D Vu()
						{ MgVect2D v1 = p[1] - p[0]; return v1.Unitize();}
	void Print(MCHAR* s);
};
//
// ---------------------( �R���� )------------------------------
//
//	�R��������
//
class DLL_EXPORT_LINE MgULine3D
{
public:
	MgPoint3D	p;																// �ʉߓ_
	MgVect3D	v;																// ��������

	// �R���X�g���N�^
	MgULine3D()			{}
	
	MgULine3D( MREAL x, MREAL y, MREAL z, MREAL vx, MREAL vy, MREAL vz)
						{ p.x = x; p.y = y; p.z = z; v.x = vx; v.y = vy; v.z = vz;}
	MgULine3D( const MgPoint3D& p1, const MgVect3D& v1)
						{ p = p1; v = v1;}
	bool operator == ( const MgULine3D& ULn1) const;							// b = (uln == ULn1) ����

	bool operator != ( const MgULine3D& ULn1) const								// b = (uln != ULn1) ����
						{ return !((*this) == ULn1);}
	MgULine3D Set( const MgPoint3D& p1, const MgVect3D& v1)
						{ p = p1; v = v1; return *this;}
	MgULine3D Set( const MgULine2D& uln1, MREAL z1 = 0.f)						// �Q�������R�����@(Z�ȗ�0.)
						{ p.x = uln1.p.x; p.y = uln1.p.y; p.z = z1;
						  v = MgVect3DC( uln1.v).Unitize(); return *this;} 
	MgULine3D Set( const MgULine2D& ULn1, const MgPlane3D& Pln);				// �Q�������R����

	MgULine3D SetRev()	{ v = - v; return *this;}								// �������]
	void Print(MCHAR* s);
};

//
// ---------------------( �R���� )------------------------------
//
//	�R����������
//
class DLL_EXPORT_LINE MgHLine3D
{
public:
	MgPoint3D	p;																// �n�_
	MgVect3D	v;																// ����������

	// �R���X�g���N�^
	MgHLine3D()			{}

	MgHLine3D( MREAL x, MREAL y, MREAL z, MREAL vx, MREAL vy, MREAL vz)
						{ p.x = x; p.y = y; p.z = z; v.x = vx; v.y = vy; v.z = vz;}
	MgHLine3D( const MgPoint3D& p1, const MgVect3D& v1)
						{ p = p1; v = v1;}

	bool operator == ( const MgHLine3D &ULn1) const;							// b = (uln == ULn1) ����

	bool operator != ( const MgHLine3D &ULn1) const								// b = (uln != ULn1) ����
						{ return !((*this) == ULn1);}
	MgHLine3D Set( const MgPoint3D& p1, const MgVect3D& v1)
						{ p = p1; v = v1; return *this;}
	MgHLine3D Set( const MgHLine2D &uln1, MREAL z1 = 0.f)					// �Q�������R�����@(Z�ȗ�0.)
						{ p.x = uln1.p.x; p.y = uln1.p.y; p.z = z1;
						  v = MgVect3DC( uln1.v).Unitize(); return *this;} 
	MgHLine3D Set( const MgHLine2D &ULn1, const MgPlane3D& Pln);				// �Q�������R����

	MgHLine3D SetRev()	{ v = - v; return *this;}								// ���������]
	void Print(MCHAR* s);
};

//
//	�R��������
//
class DLL_EXPORT_LINE MgLine3D
{
public:
	MgPoint3D	p[2];															// �n�_�A�I�_

	// �R���X�g���N�^
	MgLine3D()	{}

	MgLine3D( const MgPoint3D& ps, const MgPoint3D& pe)
						{ p[0] = ps; p[1] = pe;}
	MgLine3D( const MgPoint3D *pi)
						{ p[0] = pi[0]; p[1] = pi[1];}										
	MgLine3D( MREAL psx, MREAL psy, MREAL psz,
			  MREAL pex, MREAL pey, MREAL pez)
						{ p[0].x = psx; p[0].y = psy; p[0].z = psz; 
						  p[1].x = pex; p[1].y = pey; p[1].z = pez;}
	MgLine3D operator + ( const MgVect3D& v) const;								// Ln1 = Ln2 + p3

	MgLine3D operator - ( const MgVect3D& v) const;								// Ln1 = Ln2 + p3

	MgLine3D operator += ( const MgVect3D& v);									// Ln1 += P2

	MgLine3D operator -= ( const MgVect3D& v);									// Ln1 += P2

	bool operator == ( const MgLine3D& Ln1) const;								// b = (ln == Ln1) ����

	bool operator != ( const MgLine3D& Ln1) const								// b = (ln != Ln1) ����
						{ return !((*this) == Ln1);}
	MgLine3D Set( const MgPoint3D& ps, const MgPoint3D& pe)						// �n�_�A�I�_
						{ p[0] = ps; p[1] = pe; return *this;}
	MgLine3D Set( const MgPoint3D *pi)											// �Q�_
						{ p[0] = pi[0]; p[1] = pi[1]; return *this;}										
	MgLine3D Set( MREAL psx, MREAL psy, MREAL psz,			// 2*3����
				  MREAL pex, MREAL pey, MREAL pez)
						{ p[0].x = psx; p[0].y = psy; p[0].z = psz; 
						  p[1].x = pex; p[1].y = pey; p[1].z = pez;
						  return *this;}
	MgLine3D Set( const MgLine2D& ln1, MREAL z = 0.)							// �Q�������R�����@(Z�ȗ�0.)
						{ p[0].x = ln1.p[0].x; p[0].y = ln1.p[0].y; p[0].z = z;
						  p[1].x = ln1.p[1].x; p[1].y = ln1.p[1].y; p[1].z = z;
						  return *this;}
	MgLine3D Set( const MgLine2D& ln1, const MgPlane3D& Pln);					// �Q�������R����

	MgLine3D SetRev()
						{ msSwap( p[0], p[1]); return *this;}					// ���� ���]
	MgVect3D Vu()
						{ MgVect3D v1 = p[1] - p[0]; return v1.Unitize();}		// �����̕���(�P�ʃx�N�g��)
	void Print(MCHAR* s);
};

// ---------------------( �Q���� )------------------------------

//==========================================================================================
//	�Q��������
//
inline MgULine2D MgULine2DC( const MgPoint2D& p1, const MgVect2D& v1)						// �ʉߓ_�ƕ����P�ʃx�N�g�����Q�������������߂�
{
	MgULine2D ULno;
	ULno.p = p1;
	ULno.v = v1;
	return ULno;
}										
inline MgULine2D MgULine2DC( const MgULine3D& ULn1)											// �R����(x,y) �� �Q����
{
	MgULine2D ULno;
	ULno.p.x = ULn1.p.x;
	ULno.p.y = ULn1.p.y;
	ULno.v.x = ULn1.v.x,
	ULno.v.y = ULn1.v.y;
	return ULno;
} 
inline MgULine2D MgULine2D::Set( const MgULine3D& ULn1)										// �R����(x,y) �� �Q����
{
	MgULine2D ULno;
	ULno.p.x = ULn1.p.x;
	ULno.p.y = ULn1.p.y;
	ULno.v.x = ULn1.v.x;
	ULno.v.y = ULn1.v.y;
	return ULno;
} 

//==========================================================================================
//	�Q��������
//
inline MgLine2D MgLine2DC( const MgLine3D& Ln1)												// �R����(x,y)���Q����
{
	MgLine2D Lno;
	Lno.p[0].x = Ln1.p[0].x;
	Lno.p[0].y = Ln1.p[0].y;
	Lno.p[1].x = Ln1.p[1].x;
	Lno.p[1].y = Ln1.p[1].y;
	return Lno;
} 
inline MgLine2D MgLine2DC( const MgPoint3D& Ps, const MgPoint3D& Pe)						// �R����(x,y)���Q����
{
	MgLine2D Lno;
	Lno.p[0].x = Ps.x;
	Lno.p[0].y = Ps.y;
	Lno.p[1].x = Pe.x;
	Lno.p[1].y = Pe.y;
	return Lno;
} 
inline MgLine2D MgLine2DC( const MgPoint3D *Pi)												// �R����(x,y)���Q����
{
	MgLine2D Lno;
	Lno.p[0].x = Pi[0].x;
	Lno.p[0].y = Pi[0].y;
	Lno.p[1].x = Pi[1].x;
	Lno.p[1].y = Pi[1].y;
	return Lno;
} 

inline MgVect2D MgVect2DC( const MgLine2D& Ln1)												// Line2 �� Vect2
{
	return ( Ln1.p[1] - Ln1.p[0]);
}
inline MgLine2D MgLine2D::operator + ( const MgVect2D& v) const								// Ln1 = Ln2 + p3
{
	return MgLine2D( MgPoint2D( p[0].x + v.x, p[0].y + v.y),
					 MgPoint2D( p[1].x + v.x, p[1].y + v.y));
}
inline MgLine2D MgLine2D::operator - ( const MgVect2D& v) const								// Ln1 = Ln2 + p3
{
	return MgLine2D( MgPoint2D( p[0].x - v.x, p[0].y - v.y),
					 MgPoint2D( p[1].x - v.x, p[1].y - v.y));
}
inline MgLine2D MgLine2D::operator += ( const MgVect2D& v)									// Ln1 += P2
{
	return MgLine2D( MgPoint2D( p[0].x += v.x, p[0].y += v.y),
					 MgPoint2D( p[1].x += v.x, p[1].y += v.y));
}
inline MgLine2D MgLine2D::operator -= ( const MgVect2D& v)									// Ln1 += P2
{
	return MgLine2D( MgPoint2D( p[0].x -= v.x, p[0].y -= v.y),
					 MgPoint2D( p[1].x -= v.x, p[1].y -= v.y));
}
inline MgLine2D MgLine2D::Set( const MgLine3D& Ln1)											// �R����(x,y)���Q����
{
	MgLine2D Lno;
	Lno.p[0].x = Ln1.p[0].x;
	Lno.p[0].y = Ln1.p[0].y;
	Lno.p[1].x = Ln1.p[1].x;
	Lno.p[1].y = Ln1.p[1].y;
	return Lno;
} 

//==========================================================================================
//	�Q�����x�N�g���@�R���X�g���N�^
//
inline MgVect2D::MgVect2D( const MgULine2D& uln)											// 2D�����̕�����\��2D�x�N�g�������߂�
{
	*this = uln.v;
}
inline MgVect2D::MgVect2D( const MgLine2D& ln)												// 2D�����̕�����\��2D�x�N�g�������߂�
{
	*this = ln.p[1] - ln.p[0];
}

// ---------------------( �R���� )------------------------------

//==========================================================================================
//	�R��������
//
inline MgULine3D MgULine3DC( const MgULine2D& uln1, MREAL z1 = 0.f)					// �Q�������R�����@(Z�ȗ�0.)
{
	MgULine3D ULno;
	ULno.p.x = uln1.p.x;
	ULno.p.y = uln1.p.y;
	ULno.p.z = z1;
	ULno.v = MgVect3DC( uln1.v).Unitize();
	return ULno;
} 
inline MgULine3D MgULine3DC( const MgULine2D& ULn1, const MgPlane3D& Pln);					// �Q�������R����

//==========================================================================================
//	�R��������
//

inline MgLine3D MgLine3DC( const MgLine2D& ln1, MREAL z = 0.)								// �Q�������R�����@(Z�ȗ�0.)
{
	MgLine3D Lno;
	Lno.p[0].x = ln1.p[0].x;
	Lno.p[0].y = ln1.p[0].y;
	Lno.p[0].z = z;
	Lno.p[1].x = ln1.p[1].x; Lno.p[1].y = ln1.p[1].y;
	Lno.p[1].z = z;
	return Lno;
}
inline MgLine3D MgLine3DC( const MgLine2D& ln1, const MgPlane3D& Pln);							// �Q�������R����

inline MgLine3D MgLine3DC( const MgPoint2D& ps, const MgPoint2D& pe, MREAL z = 0.)				// �Q�������R�����@(Z�ȗ�0.)
{
	MgLine3D Lno;
	Lno.p[0].x = ps.x;
	Lno.p[0].y = ps.y;
	Lno.p[0].z = z;
	Lno.p[1].x = pe.x;
	Lno.p[1].y = pe.y;
	Lno.p[1].z = z;
	return Lno;
} 
inline MgLine3D MgLine3DC( const MgPoint2D& ps, const MgPoint2D& pe, const MgPlane3D& Pln)		// �Q�������R����
{
	return MgLine3DC( MgLine2D( ps, pe), Pln);
} 
inline MgLine3D MgLine3DC( const MgPoint2D *pi, MREAL z = 0.)									// �Q�������R�����@(Z�ȗ�0.)
{
	MgLine3D Lno;
	Lno.p[0].x = pi[0].x;
	Lno.p[0].y = pi[0].y;
	Lno.p[0].z = z;
	Lno.p[1].x = pi[1].x;
	Lno.p[1].y = pi[1].y;
	Lno.p[1].z = z;
	return Lno;
} 
inline MgLine3D MgLine3DC( const MgPoint2D *pi, const MgPlane3D& Pln)		// �Q�������R����
{
	return MgLine3DC( MgLine2D( pi), Pln);
} 
inline MgVect3D MgVect3DC( const MgLine3D& Ln1)												// Line3 �� Vect3
{
	return ( Ln1.p[1] - Ln1.p[0]);
}
inline MgLine3D MgLine3D::operator + ( const MgVect3D& v) const								// Ln1 = Ln2 + p3
{
	return MgLine3D( p[0].x + v.x, p[0].y + v.y, p[0].z + v.z,
					 p[1].x + v.x, p[1].y + v.y, p[1].z + v.z);
}
inline MgLine3D MgLine3D::operator - ( const MgVect3D& v) const								// Ln1 = Ln2 + p3
{
	return MgLine3D( p[0].x - v.x, p[0].y - v.y, p[0].z - v.z,
					 p[1].x - v.x, p[1].y - v.y, p[1].z - v.z);
}
inline MgLine3D MgLine3D::operator += ( const MgVect3D& v)									// Ln1 += P2
{
	return MgLine3D( p[0].x += v.x, p[0].y += v.y, p[0].z += v.z,
					 p[1].x += v.x, p[1].y += v.y, p[1].z += v.z);
}
inline MgLine3D MgLine3D::operator -= ( const MgVect3D& v)									// Ln1 += P2
{
	return MgLine3D( p[0].x -= v.x, p[0].y -= v.y, p[0].z -= v.z,
					 p[1].x -= v.x, p[1].y -= v.y, p[1].z -= v.z);
}

//==========================================================================================
//	�R�����x�N�g���@�R���X�g���N�^
//
inline MgVect3D::MgVect3D( const MgULine3D& uln)											// 3D�����̕�����\��3D�x�N�g�������߂�
{
	*this = uln.v;
}
inline MgVect3D::MgVect3D( const MgLine3D& ln)												// 3D�����̕�����\��3D�x�N�g�������߂�
{
	*this = ln.p[1] - ln.p[0];
}

// �T�C�Y
inline int SZMgULine2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgULine2D));}
inline int SZMgULine2D()			{ return  (int)sizeof( MgULine2D);}
inline int SZMgULine3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgULine3D));}
inline int SZMgULine3D()			{ return  (int)sizeof( MgULine3D);}
inline int SZMgHLine2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgHLine2D));}
inline int SZMgHLine2D()			{ return  (int)sizeof( MgHLine2D);}
inline int SZMgHLine3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgHLine3D));}
inline int SZMgHLine3D()			{ return  (int)sizeof( MgHLine3D);}
inline int SZMgLine2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgLine2D));}
inline int SZMgLine2D()				{ return  (int)sizeof( MgLine2D);}
inline int SZMgLine3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgLine3D));}
inline int SZMgLine3D()				{ return  (int)sizeof( MgLine3D);}
inline int WSZMgULine2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgULine2D) / SZMINT());}
inline int WSZMgULine2D()			{ return  (int)sizeof( MgULine2D) / SZMINT();}
inline int WSZMgULine3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgULine3D) / SZMINT());}
inline int WSZMgULine3D()			{ return  (int)sizeof( MgULine3D) / SZMINT();}
inline int WSZMgHLine2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgHLine2D) / SZMINT());}
inline int WSZMgHLine2D()			{ return  (int)sizeof( MgHLine2D) / SZMINT();}
inline int WSZMgHLine3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgHLine3D) / SZMINT());}
inline int WSZMgHLine3D()			{ return  (int)sizeof( MgHLine3D) / SZMINT();}
inline int WSZMgLine2D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgLine2D) / SZMINT());}
inline int WSZMgLine2D()			{ return  (int)sizeof( MgLine2D) / SZMINT();}
inline int WSZMgLine3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgLine3D) / SZMINT());}
inline int WSZMgLine3D()			{ return  (int)sizeof( MgLine3D) / SZMINT();}

} // namespace MC
