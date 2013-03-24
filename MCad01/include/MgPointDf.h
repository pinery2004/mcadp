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
inline MgPoint2::MgPoint2( const MgPoint3& pt)
						{ x = pt.x; y = pt.y;}
//inline MgPoint2::MgPoint2( const MgVect2& pt)
//						{ x = pt.x; y = pt.y;}

// ���Z�I�y���[�^
inline MgPoint2 MgPoint2::operator + ( const MgPoint2& v) const					// P1 = P2 + p3
				 		{ return MgPoint2( x + v.x, y + v.y);}
inline MgPoint2 MgPoint2::operator + ( const MgVect2& v) const					// P1 = P2 + p3
				 		{ return MgPoint2( x + v.x, y + v.y);}
inline MgVect2 MgPoint2::operator - ( const MgPoint2& v) const					// P1 = P2 - P3
				 		{ return MgVect2( x - v.x, y - v.y);}
inline MgPoint2 MgPoint2::operator - ( const MgVect2& v) const					// P1 = P2 - P3
				 		{ return MgPoint2( x - v.x, y - v.y);}
inline MgPoint2 MgPoint2::operator += ( const MgPoint2& v)						// P1 += P2
				 		{ return MgPoint2( x += v.x, y += v.y);}
inline MgPoint2 MgPoint2::operator += ( const MgVect2& v)						// P1 += P2
				 		{ return MgPoint2( x += v.x, y += v.y);}
inline MgPoint2 MgPoint2::operator -= ( const MgPoint2& v)						// P1 -= P2
				 		{ return MgPoint2( x -= v.x, y -= v.y);}
inline MgPoint2 MgPoint2::operator -= ( const MgVect2& v)						// P1 -= P2
				 		{ return MgPoint2( x -= v.x, y -= v.y);}
inline MgPoint2 MgPoint2::operator * ( MREAL r) const							// P1 = P2 * r
				 		{ return MgPoint2( x * r, y * r);}
inline MgPoint2 MgPoint2::operator / ( MREAL r) const							// P1 = P2 / r
				 		{ return MgPoint2( x / r, y / r);}
inline MgPoint2 MgPoint2::operator *= ( MREAL r)								// P1 *= r
				 		{ return MgPoint2( x *= r, y *= r);}
inline MgPoint2 MgPoint2::operator /= ( MREAL r)								// P1 /= r
				 		{ return MgPoint2( x /= r, y /= r);}
inline MREAL MgPoint2::operator * ( const MgPoint2& v) const					// r = P1 * P2 (���� cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgPoint2::operator * ( const MgVect2& v) const						// r = P1 * P2 (���� cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgPoint2::operator ^ ( const MgPoint2& v) const					// r = P2 ^ P3 (�O�� sin)
				 		{ return ( x * v.y -  y * v.x);}
inline MgPoint2 MgPoint2::operator & ( const MgPoint2& v) const					// P1 = P2 & P3 (rotation)
				 		{ return MgPoint2( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}
inline bool MgPoint2::operator == (const MgPoint2& v) const						// b = (P1 == P2) ����
				 		{ MgVect2 v1 = v - *this; return (v1 * v1) <= g_gTol.D_2;}
inline bool MgPoint2::operator != (const MgPoint2& v) const						// b = (P1 != P2) ����
				 		{ return !((*this) == v);}

inline MgPoint2 MgPoint2::RotR90() const										// �E�ɂX�O�x��]�����x�N�g�������߂�
						{ return MgPoint2( y, -x);}
inline MgPoint2 MgPoint2::RotL90() const										// ���ɂX�O�x��]�����x�N�g�������߂�
						{ return MgPoint2( -y, x);}
inline MgPoint2 MgPoint2::Rot180() const										// �P�W�O�x��]�����x�N�g�������߂�
						{ return MgPoint2( -x, -y);}
inline MgPoint2 MgPoint2::Rot( const MgPoint2& v) const							// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�
						{ return MgPoint2( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}

inline MgPoint2 MgPoint2C( const MgPoint3& v)									// �R����(x,y)���Q����
						{ MgPoint2 vto; vto.x=v.x; vto.y=v.y; return vto;}

inline MgPoint2 MgPoint2C( const CPoint &cp)									// CPoint���Q����
						{ MgPoint2 vto; vto.x = MREAL( cp.x);
						  vto.y = MREAL( cp.y); return vto;}

inline CPoint MgCPointC(MgPoint2& v)
						{ CPoint cp; cp.x = MINT( v.x + 0.5);
						  cp.y = MINT( v.y + 0.5); return cp;}

inline MgPoint2 MgPoint2AngR( MREAL rad)
						{ return MgPoint2( cos( rad), sin( rad));}

inline MgPoint2 MgPoint2AngD( MREAL deg)
						{ MREAL rad = deg * MC_DTR; return MgPoint2( cos( rad), sin( rad));}
//
//======================( �Q���� )==============================
//		�Q�����x�N�g���@�x�N�g�����Z
//
// �R�s�[�R���X�g���N�^
inline MgVect2::MgVect2( const MgVect3& pt)
						{ x = pt.x; y = pt.y;}
//inline MgVect2::MgVect2( const MgPoint2& pt)
//						{ x = pt.x; y = pt.y;}

// ���Z�I�y���[�^
inline MgVect2 MgVect2::operator + ( const MgVect2& v) const					// P1 = P2 + p3
				 		{ return MgVect2( x + v.x, y + v.y);}
inline MgVect2 MgVect2::operator - ( const MgVect2& v) const					// P1 = P2 - P3
				 		{ return MgVect2( x - v.x, y - v.y);}
inline MgVect2 MgVect2::operator += ( const MgVect2& v)							// P1 += P2
				 		{ return MgVect2( x += v.x, y += v.y);}
inline MgVect2 MgVect2::operator -= ( const MgVect2& v)							// P1 -= P2
				 		{ return MgVect2( x -= v.x, y -= v.y);}
inline MgVect2 MgVect2::operator * ( MREAL r) const								// P1 = P2 * r
				 		{ return MgVect2( x * r, y * r);}
inline MgVect2 MgVect2::operator / ( MREAL r) const								// P1 = P2 / r
				 		{ return MgVect2( x / r, y / r);}
inline MgVect2 MgVect2::operator *= ( MREAL r)									// P1 *= r
				 		{ return MgVect2( x *= r, y *= r);}
inline MgVect2 MgVect2::operator /= ( MREAL r)									// P1 /= r
				 		{ return MgVect2( x /= r, y /= r);}
inline MREAL MgVect2::operator * ( const MgVect2& v) const						// r = P1 * P2 (���� cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgVect2::operator * ( const MgPoint2& v) const						// r = P1 * P2 (���� cos)
				 		{ return ( x * v.x + y * v.y);}
inline MREAL MgVect2::operator ^ ( const MgVect2& v) const						// r = P2 ^ P3 (�O�� sin)
				 		{ return ( x * v.y -  y * v.x);}
inline MgVect2 MgVect2::operator & ( const MgVect2& v) const					// P1 = P2 & P3 (rotation)
				 		{ return MgVect2( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}
inline bool MgVect2::operator == (const MgVect2& v) const						// b = (P1 == P2) ����
				 		{ MgVect2 v1 = v - *this; return (v1 * v1) <= g_gTol.D_2;}
inline bool MgVect2::operator != (const MgVect2& v) const						// b = (P1 != P2) ����
				 		{ return !((*this) == v);}

inline MgVect2 MgVect2::RotR90() const											// �E�ɂX�O�x��]�����x�N�g�������߂�
						{ return MgVect2( y, -x);}
inline MgVect2 MgVect2::RotL90() const											// ���ɂX�O�x��]�����x�N�g�������߂�
						{ return MgVect2( -y, x);}
inline MgVect2 MgVect2::Rot180() const											// �P�W�O�x��]�����x�N�g�������߂�
						{ return MgVect2( -x, -y);}
inline MgVect2 MgVect2::Rot( const MgVect2& v) const							// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�
						{ return MgVect2( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x);}

inline MgVect2 MgVect2C( const MgVect3& v)										// �R����(x,y)���Q����
						{ MgVect2 vto; vto.x=v.x; vto.y=v.y; return vto;}

inline MgVect2 MgVect2C( const CPoint &cp)										// CPoint���Q����
						{ MgVect2 vto; vto.x = MREAL( cp.x);
						  vto.y = MREAL( cp.y); return vto;}

inline CPoint MgCPointC(MgVect2& v)
						{ CPoint cp; cp.x = MINT( v.x + 0.5);
						  cp.y = MINT( v.y + 0.5); return cp;}

inline MgVect2 MgVect2AngR( MREAL rad)
						{ return MgVect2( cos( rad), sin( rad));}

inline MgVect2 MgVect2AngD( MREAL deg)
						{ MREAL rad = deg * MC_DTR; return MgVect2( cos( rad), sin( rad));}
//
//======================( �R���� )==============================
//		�R�����_	�x�N�g�����Z
//
// �R�s�[�R���X�g���N�^
//inline MgPoint3::MgPoint3( const MgPoint2& v1, const MgPlane3& Pln3)			// �Q�������R����
//inline MgPoint3::MgPoint3( const MgVect3& v1)
//						{x = v1.x; y = v1.y; z = v1.z;}

// ���Z�I�y���[�^
inline MgPoint3 MgPoint3C( const MgPoint2& v1, MREAL z2 = 0.)					// �Q�������R�����@(Z�ȗ�0.)
						{ MgPoint3 vto; vto.x = v1.x; vto.y = v1.y;
						  vto.z = z2; return vto;} 
inline MgPoint3 MgPoint3C( const MgPoint2& v1, const MgPlane3& Pln3);			// �Q�������R����

inline MgPoint3 MgPoint3::operator + ( const MgPoint3& v) const					// P1 = P2 + p3
				 		{ return MgPoint3( x + v.x, y + v.y, z + v.z);}
inline MgPoint3 MgPoint3::operator + ( const MgVect3& v) const					// P1 = P2 + p3
				 		{ return MgPoint3( x + v.x, y + v.y, z + v.z);}
inline MgVect3 MgPoint3::operator - ( const MgPoint3& p) const					// P1 = P2 - P3
						{ return MgVect3(x - p.x, y - p.y, z - p.z);}
inline MgPoint3 MgPoint3::operator - ( const MgVect3& p) const					// P1 = P2 - P3
				 		{ return MgPoint3(x - p.x, y - p.y, z - p.z);}
inline MgPoint3 MgPoint3::operator += ( const MgPoint3& v)						// P1 += P2
				 		{ return MgPoint3( x += v.x, y += v.y, z += v.z);}
inline MgPoint3 MgPoint3::operator += ( const MgVect3& v)						// P1 += P2
				 		{ return MgPoint3( x += v.x, y += v.y, z += v.z);}
inline MgPoint3 MgPoint3::operator -= ( const MgPoint3& v)						// P1 -= P2
				 		{ return MgPoint3( x -= v.x, y -= v.y, z -= v.z);}
inline MgPoint3 MgPoint3::operator -= ( const MgVect3& v)						// P1 -= P2
				 		{ return MgPoint3( x -= v.x, y -= v.y, z -= v.z);}
inline MgPoint3 MgPoint3::operator * (  MREAL r)	const						// P1 = P2 * r
				 		{ return MgPoint3( x * r, y * r, z * r);}
inline MgPoint3 MgPoint3::operator / (  MREAL r) const							// P1 = P2 / r
				 		{ return MgPoint3( x / r, y / r, z / r);}
inline MgPoint3 MgPoint3::operator *= ( MREAL r)								// P1 *= r
				 		{ return MgPoint3( x *= r, y *= r, z *= r);}
inline MgPoint3 MgPoint3::operator /= ( MREAL r)								// P1 /= r
				 		{ return MgPoint3( x /= r, y /= r, z /= r);}
inline MREAL MgPoint3::operator * ( const MgPoint3& v) const					// r = P1 * P2 (���� cos)
				 		{ return ( x * v.x + y * v.y + z * v.z);}
inline MREAL MgPoint3::operator * ( const MgVect3& v) const						// r = P1 * P2 (���� cos)
				 		{ return ( x * v.x + y * v.y + z * v.z);}
inline MgVect3 MgPoint3::operator ^ ( const MgPoint3& v) const					// P1 = P2 ^ P3 (�O�� sin)
				 		{ return MgVect3( y * v.z - z * v.y,
						                  z * v.x - x * v.z,
								          x * v.y - y * v.x);}
inline bool MgPoint3::operator == ( const MgPoint3& v) const					// b = (P1 == P2) ����
				 		{ MgVect3 v1 = v - *this; return ((v1 * v1) <= g_gTol.D_2);}
inline bool MgPoint3::operator != ( const MgPoint3& v) const					// b = (P1 != P2) ����
				 		{ return !((*this) == v);}

inline MgPoint3 MgPoint3::RotR90() const										// Z���𒆐S���Ƃ��ĉE�ɂX�O�x��]�����x�N�g�������߂�
						{ return MgPoint3( y, -x, z);}
inline MgPoint3 MgPoint3::RotL90() const										// Z���𒆐S���Ƃ��č��ɂX�O�x��]�����x�N�g�������߂�
						{ return MgPoint3( -y, x, z);}
inline MgPoint3 MgPoint3::Rot180() const										// Z���𒆐S���Ƃ��ĂP�W�O�x��]�����x�N�g�������߂�
						{ return MgPoint3( -x, -y, z);}
inline MgPoint3 MgPoint3::Rot( const MgVect2& v) const							// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�
						{ return MgPoint3( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x, z);}
//
//======================( �R���� )==============================
//		�R�����x�N�g��	�x�N�g�����Z
//
// �R�s�[�R���X�g���N�^
//inline MgVect3::MgVect3( const MgPoint3& v1)
//						{ x = v1.x; y = v1.y; z = v1.z;}

// ���Z�I�y���[�^
inline MgVect3 MgVect3C( const MgVect2& v1, MREAL z2 = 0.)						// �Q�������R�����@(Z�ȗ�0.)
						{ MgVect3 vto; vto.x = v1.x; vto.y = v1.y;
						  vto.z = z2; return vto;} 
inline MgVect3 MgVect3C( const MgVect2& v1, const MgPlane3& Pln3);				// �Q�������R����

inline MgVect3 MgVect3::operator + ( const MgVect3& v) const					// P1 = P2 + p3
				 		{ return MgVect3( x + v.x, y + v.y, z + v.z);}
inline MgVect3 MgVect3::operator - ( const MgVect3& p) const					// P1 = P2 - P3
				 		{ return MgVect3(x - p.x, y - p.y, z - p.z);}
inline MgVect3 MgVect3::operator += ( const MgVect3& v)							// P1 += P2
				 		{ return MgVect3( x += v.x, y += v.y, z += v.z);}
inline MgVect3 MgVect3::operator -= ( const MgVect3& v)							// P1 -= P2
				 		{ return MgVect3( x -= v.x, y -= v.y, z -= v.z);}
inline MgVect3 MgVect3::operator * (  MREAL r)	const							// P1 = P2 * r
				 		{ return MgVect3( x * r, y * r, z * r);}
inline MgVect3 MgVect3::operator / (  MREAL r) const							// P1 = P2 / r
				 		{ return MgVect3( x / r, y / r, z / r);}
inline MgVect3 MgVect3::operator *= ( MREAL r)									// P1 *= r
				 		{ return MgVect3( x *= r, y *= r, z *= r);}
inline MgVect3 MgVect3::operator /= ( MREAL r)									// P1 /= r
				 		{ return MgVect3( x /= r, y /= r, z /= r);}
inline MREAL MgVect3::operator * ( const MgVect3& v) const						// r = P1 * P2 (���� cos)
				 		{ return ( x * v.x + y * v.y + z * v.z);}
inline MREAL MgVect3::operator * ( const MgPoint3& v) const						// r = P1 * P2 (���� cos)
				 		{ return ( x * v.x + y * v.y + z * v.z);}
inline MgVect3 MgVect3::operator ^ ( const MgVect3& v) const					// P1 = P2 ^ P3 (�O�� sin)
				 		{ return MgVect3( y * v.z - z * v.y,
						                  z * v.x - x * v.z,
								          x * v.y - y * v.x);}
inline bool MgVect3::operator == ( const MgVect3& v) const						// b = (P1 == P2) ����
				 		{ MgVect3 v1 = v - *this; return ((v1 * v1) <= g_gTol.D_2);}
inline bool MgVect3::operator != ( const MgVect3& v) const						// b = (P1 != P2) ����
				 		{ return !((*this) == v);}

inline MgVect3 MgVect3::RotR90() const											// Z���𒆐S���Ƃ��ĉE�ɂX�O�x��]�����x�N�g�������߂�
						{ return MgVect3( y, -x, z);}
inline MgVect3 MgVect3::RotL90() const											// Z���𒆐S���Ƃ��č��ɂX�O�x��]�����x�N�g�������߂�
						{ return MgVect3( -y, x, z);}
inline MgVect3 MgVect3::Rot180() const											// Z���𒆐S���Ƃ��ĂP�W�O�x��]�����x�N�g�������߂�
						{ return MgVect3( -x, -y, z);}
inline MgVect3 MgVect3::Rot( const MgVect2& v) const							// �P�ʃx�N�g�������ɉ�]�����x�N�g�������߂�
						{ return MgVect3( x * v.x -  y * v.y,
		 			               		  x * v.y +  y * v.x, z);}
} // namespace MC