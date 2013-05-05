#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPointDf.h
//
//		�_�ƃx�N�g���̕ҏW	inline�֐�
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
//
#include "MsDefConst.h"
#include "MgAngle.h"
#include "MgPoint2D.h"
#include "MgPoint3D.h"
//#include "mdPlex.h"

namespace MC
{

//
//======================( �Q���� )==============================
//		�Q�����_	�x�N�g�����Z
//
// �R�s�[�R���X�g���N�^
inline MgPoint2D::MgPoint2D( const MgPoint3D& pt)
						{ x = pt.x; y = pt.y;}
//inline MgPoint2D::MgPoint2D( const MgVect2D& pt)
//						{ x = pt.x; y = pt.y;}

// ���Z
inline MgPoint2D MgPoint2DC( const MgPoint3D& v)								// �R����(x,y)���Q����
						{ MgPoint2D vto; vto.x=v.x; vto.y=v.y; return vto;}
inline MgPoint2D MgPoint2DC( const CPoint &cp)									// CPoint���Q����
						{ MgPoint2D vto; vto.x = MREAL( cp.x);
						  vto.y = MREAL( cp.y); return vto;}
inline CPoint MgCPointC(MgPoint2D& p)
						{ CPoint cp; cp.x = MINT( p.x + 0.5);
						  cp.y = MINT( p.y + 0.5); return cp;}
inline MgPoint2D MgPoint2DAngR( MREAL rad)
						{ return MgPoint2D( cos( rad), sin( rad));}
inline MgPoint2D MgPoint2DAngD( MREAL deg)
						{ MREAL rad = deg * MC_DTR; return MgPoint2D( cos( rad), sin( rad));}
inline MgPoint2D MgPoint2D::Rot( const MgVect2D& v) const						// ���_�𒆐S�ɒP�ʃx�N�g�������ɉ�]�����_�̈ʒu�����߂�
						{ return MgPoint2D( x * v.x -  y * v.y,
		 			               		   x * v.y +  y * v.x);}
inline MgPoint2D	MgPoint2D::Rot( MREAL ang)									// ���_�𒆐S�Ɏw��p�x�ō���]�����_�̈ʒu�����߂�
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
						  MgPoint2D pt;
						  pt.x = x * v.x -  y * v.y;
						  pt.y = x * v.y +  y * v.x;
						  return pt;}

// �ϊ�
inline MgPoint2D MgPoint2D::SetRot( const MgVect2D& v)							// ���_�𒆐S�ɒP�ʃx�N�g�������ɉ�]����
						{ *this = Rot( v);
						  return *this;}
inline MgPoint2D MgPoint2D::SetRot( MREAL ang)									// ���_�𒆐S�Ɏw��p�x�ō���]����
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
						  *this = Rot( v);
						  return *this;}
// ���Z�I�y���[�^
inline MgPoint2D MgPoint2D::operator + ( const MgPoint2D& p) const				// p3 = p1 + p2
				 		{ return MgPoint2D( x + p.x, y + p.y);}
inline MgPoint2D MgPoint2D::operator + ( const MgVect2D& v) const				// p3 = p1 + v2
				 		{ return MgPoint2D( x + v.x, y + v.y);}
inline MgVect2D MgPoint2D::operator - ( const MgPoint2D& p) const				// p3 = p1 - p2
				 		{ return MgVect2D( x - p.x, y - p.y);}
inline MgPoint2D MgPoint2D::operator - ( const MgVect2D& v) const				// P3 = p1 - v2
				 		{ return MgPoint2D( x - v.x, y - v.y);}
inline MgPoint2D MgPoint2D::operator += ( const MgPoint2D& p)					// p1 += p2
				 		{ return MgPoint2D( x += p.x, y += p.y);}
inline MgPoint2D MgPoint2D::operator += ( const MgVect2D& v)					// p1 += v2
				 		{ return MgPoint2D( x += v.x, y += v.y);}
inline MgPoint2D MgPoint2D::operator -= ( const MgPoint2D& p)					// p1 -= p2
				 		{ return MgPoint2D( x -= p.x, y -= p.y);}
inline MgPoint2D MgPoint2D::operator -= ( const MgVect2D& v)					// p1 -= v2
				 		{ return MgPoint2D( x -= v.x, y -= v.y);}
inline MgPoint2D MgPoint2D::operator * ( MREAL r) const							// p2 = p1 * r
				 		{ return MgPoint2D( x * r, y * r);}
inline MgPoint2D MgPoint2D::operator / ( MREAL r) const							// p2 = p1 / r
				 		{ return MgPoint2D( x / r, y / r);}
inline MgPoint2D MgPoint2D::operator *= ( MREAL r)								// p1 *= r
				 		{ return MgPoint2D( x *= r, y *= r);}
inline MgPoint2D MgPoint2D::operator /= ( MREAL r)								// p1 /= r
				 		{ return MgPoint2D( x /= r, y /= r);}
inline MREAL MgPoint2D::operator * ( const MgPoint2D& p) const					// r = p1 * p2 (���� cos)
				 		{ return ( x * p.x + y * p.y);}
inline MREAL MgPoint2D::operator * ( const MgVect2D& v) const					// r = p1 * v2 (���� cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgPoint2D::operator ^ ( const MgPoint2D& p) const					// r = p1 ^ p2 (�O�� sin)
				 		{ return ( x * p.y -  y * p.x);}
inline MgPoint2D MgPoint2D::operator & ( const MgPoint2D& p) const				// p3 = p1 & p2 (rotation)
				 		{ return MgPoint2D( x * p.x -  y * p.y,
		 			               		    x * p.y +  y * p.x);}
inline bool MgPoint2D::operator == (const MgPoint2D& p) const					// b = (p1 == p2) ����
				 		{ MgVect2D v1 = p - *this;
						  return (v1 * v1) <= MGPTOL->D_2;}
inline bool MgPoint2D::operator != (const MgPoint2D& p) const					// b = (p1 != p2) ����
				 		{ return !((*this) == p);}
//
//======================( �Q���� )==============================
//		�Q�����x�N�g���@�x�N�g�����Z
//
// �R�s�[�R���X�g���N�^
inline MgVect2D::MgVect2D( const MgVect3D& V)
						{ x = V.x; y = V.y;}
//inline MgVect2D::MgVect2D( const MgPoint2D& p)
//						{ x = p.x; y = p.y;}

// ���Z

inline MgVect2D MgVect2DC( const MgVect3D& v)									// �R����(x,y)���Q����
						{ MgVect2D vto; vto.x=v.x; vto.y=v.y; return vto;}

inline MgVect2D MgVect2DC( const CPoint &cp)									// CPoint���Q����
						{ MgVect2D vto; vto.x = MREAL( cp.x);
						  vto.y = MREAL( cp.y); return vto;}

inline CPoint MgCPointC(MgVect2D& v)
						{ CPoint cp; cp.x = MINT( v.x + 0.5);
						  cp.y = MINT( v.y + 0.5); return cp;}

inline MgVect2D MgVect2DAngR( MREAL rad)
						{ return MgVect2D( cos( rad), sin( rad));}

inline MgVect2D MgVect2DAngD( MREAL deg)
						{ MREAL rad = deg * MC_DTR;
						  return MgVect2D( cos( rad), sin( rad));}

// ���Z�I�y���[�^
inline MgVect2D MgVect2D::operator + ( const MgVect2D& v) const					// v3 = v1 + v2
				 		{ return MgVect2D( x + v.x, y + v.y);}
inline MgVect2D MgVect2D::operator - ( const MgVect2D& v) const					// v3 = v1 - v2
				 		{ return MgVect2D( x - v.x, y - v.y);}
inline MgVect2D MgVect2D::operator += ( const MgVect2D& v)						// v1 += v2
				 		{ return MgVect2D( x += v.x, y += v.y);}
inline MgVect2D MgVect2D::operator -= ( const MgVect2D& v)						// v1 -= v2
				 		{ return MgVect2D( x -= v.x, y -= v.y);}
inline MgVect2D MgVect2D::operator * ( MREAL r) const							// v2 = v1 * r
				 		{ return MgVect2D( x * r, y * r);}
inline MgVect2D MgVect2D::operator / ( MREAL r) const							// v2 = v1 / r
				 		{ return MgVect2D( x / r, y / r);}
inline MgVect2D MgVect2D::operator *= ( MREAL r)								// v1 *= r
				 		{ return MgVect2D( x *= r, y *= r);}
inline MgVect2D MgVect2D::operator /= ( MREAL r)								// v1 /= r
				 		{ return MgVect2D( x /= r, y /= r);}
inline MREAL MgVect2D::operator * ( const MgVect2D& v) const					// r = v1 * v2 (���� cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgVect2D::operator * ( const MgPoint2D& v) const					// r = v1 * p2 (���� cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgVect2D::operator ^ ( const MgVect2D& v) const					// r = v1 ^ v2 (�O�� sin)
				 		{ return ( x * v.y -  y * v.x);}
inline MgVect2D MgVect2D::operator & ( const MgVect2D& v) const					// v3 = v1 & v2 (rotation)
				 		{ return MgVect2D( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}
inline bool MgVect2D::operator == (const MgVect2D& v) const						// b = (v1 == v2) ����
				 		{ MgVect2D v1 = v - *this;
						  return (v1 * v1) <= MGPTOL->D_2;}
inline bool MgVect2D::operator != (const MgVect2D& v) const						// b = (v1 != v2) ����
				 		{ return !((*this) == v);}
//
//======================( �R���� )==============================
//		�R�����_	�x�N�g�����Z
//
// �R�s�[�R���X�g���N�^
//inline MgPoint3D::MgPoint3D( const MgPoint2D& v1, const MgPlane3D& Pln3)		// �Q�������R����
//inline MgPoint3D::MgPoint3D( const MgVect3D& v1)
//						{x = v1.x; y = v1.y; z = v1.z;}

// ���Z
inline MgPoint3D MgPoint3D::Rot( const MgVect2D& v) const						// Z���𒆐S���Ƃ��ĒP�ʃx�N�g�������ɉ�]�����_�̈ʒu�����߂�
						{ return MgPoint3D( x * v.x -  y * v.y,
		 			               		   x * v.y +  y * v.x, z);}
inline MgPoint3D MgPoint3D::Rot( MREAL ang) const								// Z���𒆐S���Ƃ��Ďw��p�x�ō���]�����_�̈ʒu�����߂�
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
						  return Rot( v);}

// �ϊ�
inline MgPoint3D MgPoint3D::SetRot( const MgVect2D& v)							// Z���𒆐S���Ƃ��ĒP�ʃx�N�g�������ɉ�]����
						{ *this = Rot( v);
						  return *this;}
inline MgPoint3D MgPoint3D::SetRot( MREAL ang)									// Z���𒆐S���Ƃ��Ďw��p�x�ō���]����
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
						  *this = Rot( v);
						  return *this;}

// ���Z�I�y���[�^
inline MgPoint3D MgPoint3DC( const MgPoint2D& v1, MREAL z2 = 0.)				// �Q�������R�����@(Z�ȗ�0.)
						{ MgPoint3D Pto; Pto.x = v1.x; Pto.y = v1.y;
						  Pto.z = z2; return Pto;} 
inline MgPoint3D MgPoint3DC( const MgPoint2D& v1, const MgPlane3D& Pln3);		// �Q�������R����

inline MgPoint3D MgPoint3D::operator + ( const MgPoint3D& P) const				// P3 = P1 + p2
				 		{ return MgPoint3D( x + P.x, y + P.y, z + P.z);}
inline MgPoint3D MgPoint3D::operator + ( const MgVect3D& V) const				// P3 = P1 + p2
				 		{ return MgPoint3D( x + V.x, y + V.y, z + V.z);}
inline MgVect3D MgPoint3D::operator - ( const MgPoint3D& P) const				// P3 = P1 - P2
						{ return MgVect3D(x - P.x, y - P.y, z - P.z);}
inline MgPoint3D MgPoint3D::operator - ( const MgVect3D& P) const				// P3 = P1 - P2
				 		{ return MgPoint3D(x - P.x, y - P.y, z - P.z);}
inline MgPoint3D MgPoint3D::operator += ( const MgPoint3D& P)					// P1 += P2
				 		{ return MgPoint3D( x += P.x, y += P.y, z += P.z);}
inline MgPoint3D MgPoint3D::operator += ( const MgVect3D& V)					// P1 += P2
				 		{ return MgPoint3D( x += V.x, y += V.y, z += V.z);}
inline MgPoint3D MgPoint3D::operator -= ( const MgPoint3D& P)					// P1 -= P2
				 		{ return MgPoint3D( x -= P.x, y -= P.y, z -= P.z);}
inline MgPoint3D MgPoint3D::operator -= ( const MgVect3D& V)					// P1 -= P2
				 		{ return MgPoint3D( x -= V.x, y -= V.y, z -= V.z);}
inline MgPoint3D MgPoint3D::operator * (  MREAL r)	const						// P2 = P1 * r
				 		{ return MgPoint3D( x * r, y * r, z * r);}
inline MgPoint3D MgPoint3D::operator / (  MREAL r) const						// P2 = P1 / r
				 		{ return MgPoint3D( x / r, y / r, z / r);}
inline MgPoint3D MgPoint3D::operator *= ( MREAL r)								// P1 *= r
				 		{ return MgPoint3D( x *= r, y *= r, z *= r);}
inline MgPoint3D MgPoint3D::operator /= ( MREAL r)								// P1 /= r
				 		{ return MgPoint3D( x /= r, y /= r, z /= r);}
inline MREAL MgPoint3D::operator * ( const MgPoint3D& P) const					// r = P1 * P2 (���� cos)
				 		{ return ( x * P.x + y * P.y + z * P.z);}
inline MREAL MgPoint3D::operator * ( const MgVect3D& V) const					// r = P1 * V2 (���� cos)
				 		{ return ( x * V.x + y * V.y + z * V.z);}
inline MgVect3D MgPoint3D::operator ^ ( const MgPoint3D& P) const				// P3 = P1 ^ P2 (�O�� sin)
				 		{ return MgVect3D( y * P.z - z * P.y,
						                   z * P.x - x * P.z,
								           x * P.y - y * P.x);}
inline bool MgPoint3D::operator == ( const MgPoint3D& P) const					// b = (P1 == P2) ����
				 		{ MgVect3D v1 = P - *this;
						  return ((v1 * v1) <= MGPTOL->D_2);}
inline bool MgPoint3D::operator != ( const MgPoint3D& P) const					// b = (P1 != P2) ����
				 		{ return !((*this) == P);}
//
//======================( �R���� )==============================
//		�R�����x�N�g��	�x�N�g�����Z
//
// �R�s�[�R���X�g���N�^
//inline MgVect3D::MgVect3D( const MgPoint3D& v1)
//						{ x = v1.x; y = v1.y; z = v1.z;}

// ���Z
inline MgVect3D MgVect3D::Rot( const MgVect2D& v) const							// Z���𒆐S���Ƃ��ĒP�ʃx�N�g�������ɉ�]�����x�N�g�������߂�
						{ return MgVect3D( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x, z);}
inline MgVect3D MgVect3D::Rot( MREAL ang) const									// Z���𒆐S���Ƃ��Ďw��p�x�ō���]�����_�̈ʒu�����߂�
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
						  return Rot( v);}
// �ϊ�
inline MgVect3D MgVect3D::SetRot( const MgVect2D& v)							// Z���𒆐S���Ƃ��ĒP�ʃx�N�g�������ɉ�]����
						{ *this = Rot( v);
						  return *this;}
inline MgVect3D MgVect3D::SetRot( MREAL ang)									// Z���𒆐S���Ƃ��Ďw��p�x�ō���]����
						{ MgVect2D v = MgVect2D( cos( ang), sin( ang));
						  *this = Rot( v);
						  return *this;}


// ���Z�I�y���[�^
inline MgVect3D MgVect3DC( const MgVect2D& v1, MREAL z2 = 0.)					// �Q�������R�����@(Z�ȗ�0.)
						{ MgVect3D vto; vto.x = v1.x; vto.y = v1.y;
						  vto.z = z2; return vto;} 
inline MgVect3D MgVect3DC( const MgVect2D& v1, const MgPlane3D& Pln3);			// �Q�������R����

inline MgVect3D MgVect3D::operator + ( const MgVect3D& V) const					// V3 = V1 + V2
				 		{ return MgVect3D( x + V.x, y + V.y, z + V.z);}
inline MgVect3D MgVect3D::operator - ( const MgVect3D& P) const					// V3 = V1 - V2
				 		{ return MgVect3D(x - P.x, y - P.y, z - P.z);}
inline MgVect3D MgVect3D::operator += ( const MgVect3D& V)						// V1 += V2
				 		{ return MgVect3D( x += V.x, y += V.y, z += V.z);}
inline MgVect3D MgVect3D::operator -= ( const MgVect3D& V)						// V1 -= V2
				 		{ return MgVect3D( x -= V.x, y -= V.y, z -= V.z);}
inline MgVect3D MgVect3D::operator * (  MREAL r)	const						// V2 = V1 * r
				 		{ return MgVect3D( x * r, y * r, z * r);}
inline MgVect3D MgVect3D::operator / (  MREAL r) const							// V2 = V1 / r
				 		{ return MgVect3D( x / r, y / r, z / r);}
inline MgVect3D MgVect3D::operator *= ( MREAL r)								// V1 *= r
				 		{ return MgVect3D( x *= r, y *= r, z *= r);}
inline MgVect3D MgVect3D::operator /= ( MREAL r)								// V1 /= r
				 		{ return MgVect3D( x /= r, y /= r, z /= r);}
inline MREAL MgVect3D::operator * ( const MgVect3D& V) const					// r = V1 * V2 (���� cos)
				 		{ return ( x * V.x + y * V.y + z * V.z);}
inline MREAL MgVect3D::operator * ( const MgPoint3D& P) const					// r = V1 * P2 (���� cos)
				 		{ return ( x * P.x + y * P.y + z * P.z);}
inline MgVect3D MgVect3D::operator ^ ( const MgVect3D& V) const					// V3 = V1 ^ V2 (�O�� sin)
				 		{ return MgVect3D( y * V.z - z * V.y,
						                  z * V.x - x * V.z,
								          x * V.y - y * V.x);}
inline bool MgVect3D::operator == ( const MgVect3D& V) const					// b = (V1 == V2) ����
				 		{ MgVect3D V1 = V - *this;
						  return ((V1 * V1) <= MGPTOL->D_2);}
inline bool MgVect3D::operator != ( const MgVect3D& V) const					// b = (V1 != V2) ����
				 		{ return !((*this) == V);}

} // namespace MC
