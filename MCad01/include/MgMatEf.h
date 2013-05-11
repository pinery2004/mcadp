#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgGeo.h
//
//		�}�`����
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
	#pragma message( "<<< MgGeo�Edll_EXport >>>")
	#define DLL_EXPORT_GEO							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_GEO_DO
			#define DLL_EXPORT_GEO
		#else
//			#pragma message( "=== MgGeo�Edll_IMport ===")
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
	//======================( �Q�����A�R���� )==============================
	//	�Q�����A�R�������W�ϊ��}�g���b�N�X
	//
	//======================( �Q���� )==============================
	//		���_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat2E Mat2ERot( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2ERotV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �Q���� )==============================
	//		���_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat2E Mat2ERotRev( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2ERotRevV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�w�x���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�w�x���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotRevZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotRevZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�x�y���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotTX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return  Mat3ERotTXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�x�y���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotRevX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotRevXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�y�w���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�y�w���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotRevY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3ERotRevYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}
*/


/*

	inline	MgLine2D operator * ( const MgLine2D& i_ln, const MgMat2E& i_mt)		// *	���W�ϊ�
	{ 
		MgLine2D ln;
		i_ln.p[0] = i_ln.p[0] * i_mt;
		i_ln.p[1] = i_ln.p[1] * i_mt;
		return ln;
	}
	inline	MgULine2D operator * ( const MgULine2D& i_uln, const MgMat2E& i_mt)		// *	���W�ϊ�
	{ 
		MgULine2D uln;
		i_uln.p = i_uln.p * i_mt;
		i_uln.v = i_uln.v * i_mt;
		return uln;
	}
	inline	MgLine2D operator *= ( MgLine2D& i_ln, const MgMat2E& i_mt)					// *=	���W�ϊ�
	{ 
		i_ln.p[0] *= i_mt;
		i_ln.p[1] *= i_mt;
		return Ln;
	}
	inline	MgULine2D operator *= ( MgULine2D& i_uln, const MgMat2E& i_mt)				// *=	���W�ϊ�
	{ 
		i_uln.p *= i_mt;
		i_uln.v *= i_mt;
		return ULn;
	}
	inline	MgLine3D operator * ( const MgLine3D& i_Ln, const MgMat2E& i_mt)			// *	���W�ϊ�
	{
		MgLine3D Ln;
		Ln.p[0] = i_Ln.p[0] * i_mt;
		Ln.p[1] = i_Ln.p[1] * i_mt;
		return Ln;
	}
	inline	MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat2E& i_mt)		// *	���W�ϊ�
	{
		MgULine3D ULn;
		ULn.p = i_ULn.p * i_mt;
		ULn.v = i_ULn.v * i_mt;
		return ULn;
	}
	inline	MgLine3D operator *= ( MgLine3D& i_Ln, const MgMat2E& i_mt)					// *=	���W�ϊ�
	{
		i_Ln.p[0] *= i_mt;
		i_Ln.p[1] *= i_mt;
	}
	inline	MgULine3D operator *= ( MgULine3D& i_ULn, const MgMat2E& i_mt)				// *=	���W�ϊ�
	{
		i_ULn.p *= i_mt;
		i_ULn.v *= i_mt;
	}
*/
//
//======================( �Q�����A�R���� )==============================
//	�Q�����A�R�������W�ϊ��}�g���b�N�X
//
//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̉��Z
//
//	�g�p�@
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
//	�������e
//		���W�ϊ��}�g���b�N�X�̉��Z
//
//	�g�p�@
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
//	�������e
//		���̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
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
//	�������e
//		���W�ϊ��}�g���b�N�X�̈��Z
//
//	�g�p�@
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
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̈��Z
//
//	�g�p�@
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
//	�������e
//		���W�ϊ��}�g���b�N�X�̂����Z
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɍ��W�ϊ��}�g���b�N�X�ɂ��ϊ�����}�g���b�N�X���쐬
//
//	�g�p�@
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
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̂����Z
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɍ��W�ϊ��}�g���b�N�X�ɂ��ϊ�����}�g���b�N�X���쐬
//
//	�g�p�@
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
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E = MgMat2E1 + MgVect2D1;
//
//	| m11 m12 0 |     |  1  0  0 |
//	| m21 m22 0 |  X  |  0  1  0 |
//	| m31 m32 1 |     |  vx vy 1 |
//
inline	MgMat2E operator + ( const MgMat2E& i_m1, const MgVect2D& i_v)			// +	���s�ړ�
{
	MgMat2E mw;
	mw = i_m1;
	mw += i_v;
	return mw;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E = MgMat2E1 + MgPoint2D1;
//
//	| m11 m12 0 |     |  1  0  0 |
//	| m21 m22 0 |  X  |  0  1  0 |
//	| m31 m32 1 |     |  px py 1 |
//
inline	MgMat2E operator + ( const MgMat2E& i_m1, const MgPoint2D& i_pt)		// +	���s�ړ�
{ 
	return i_m1 + (MgVect2D&)i_pt;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E1 += MgVect2D1;
//
//	| m11 m12 0 |     | m11 m12 0 |     |  1  0  0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0  1  0 |
//	| m31 m32 1 |     | m31 m32 1 |     |  vx vy 1 |
//
inline	MgMat2E operator += ( MgMat2E& io_m1, const MgVect2D& i_v)				// +=	���s�ړ�
{
	io_m1.m[2][0] += i_v.x;
	io_m1.m[2][1] += i_v.y;
	return io_m1;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E1 += MgPoint2D1;
//
//	| m11 m12 0 |     | m11 m12 0 |     |  1  0  0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0  1  0 |
//	| m31 m32 1 |     | m31 m32 1 |     |  px py 1 |
//
inline	MgMat2E operator += ( MgMat2E& io_m1, const MgPoint2D& i_pt)			// +=	���s�ړ�
{
	return io_m1 += (MgVect2D&)i_pt;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɋt�����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E = MgMat2E1 - MgVect2D1;
//
//	| m11 m12 0 |     |  1   0  0 |
//	| m21 m22 0 |  X  |  0   1  0 |
//	| m31 m32 1 |     | -vx -vy 1 |
//
inline	MgMat2E operator - ( const MgMat2E& i_m1, const MgVect2D& i_pt)			// -	���s�ړ�
{ 
	MgMat2E mw;
	mw = i_m1;
	mw -= i_pt;
	return mw;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɋt�����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E = MgMat2E1 - MgPoint2D1;
//
//	| m11 m12 0 |     |  1   0  0 |
//	| m21 m22 0 |  X  |  0   1  0 |
//	| m31 m32 1 |     | -px -py 1 |
//
inline	MgMat2E operator - ( const MgMat2E& i_m1, const MgPoint2D& i_pt)		// -	���s�ړ�
{ 
	return i_m1 - (MgVect2D&)i_pt;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɋt�����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E1 -= MgVect2D1;
//
//	| m11 m12 0 |     | m11 m12 0 |     |  1   0  0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0   1  0 |
//	| m31 m32 1 |     | m31 m32 1 |     | -vx -vy 1 |
//
inline	MgMat2E operator -= ( MgMat2E& i_m1, const MgVect2D& i_v)				// -=	���s�ړ�
{
	i_m1.m[2][0] -= i_v.x;
	i_m1.m[2][1] -= i_v.y;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɋt�����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E1 -= MgPoint2D1;
//
//	| m11 m12 0 |     | m11 m12 0 |     |  1   0  0 |
//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0   1  0 |
//	| m31 m32 1 |     | m31 m32 1 |     | -px -py 1 |
//
inline	MgMat2E operator -= ( MgMat2E& i_m1, const MgPoint2D& i_pt)				// -=	���s�ړ�
{ 
	return i_m1 -= (MgVect2D&)i_pt;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgPoint2D = MgPoint2D * MgMat2E;
//
//					   | m11 m12 0 |
//	| px  py  1  |  X  | m21 m22 0 |
//					   | m31 m32 1 |     
//
inline	MgPoint2D operator * ( const MgPoint2D& i_pt, const MgMat2E& i_mt)		// *	���W�ϊ�
{
	return MGeo::Mat2EMultPoint2D( i_pt, i_mt);
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgVect2D = MgVect2D * MgMat2E;
//
//					   | m11 m12 0 |
//	| vx  vy  0  |  X  | m21 m22 0 |
//					   | m31 m32 1 |     
//
inline	MgVect2D operator * ( const MgVect2D& i_pt, const MgMat2E& i_mt)		// *	���W�ϊ�
{
	return MGeo::Mat2EMultVect2D( i_pt, i_mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgLine2D = MgLine2D * MgMat2E;
//
//	| px  py  1   |     | m11 m12 0 |
//	| px  py  1   |  X  | m21 m22 0 |
//						| m31 m32 1 |
//
inline	MgLine2D operator * ( const MgLine2D& i_ln, const MgMat2E& i_mt)		// *	���W�ϊ�
{ 
//S	MgLine2D ln;
//	ln.p[0] = i_ln.p[0] * i_mt;
//	ln.p[1] = i_ln.p[1] * i_mt;
//	return ln;
	return MGeo::Mat2EMultLine2D( i_ln, i_mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine2D = MgULine2D * MgMat2E;
//
//	| px  py  1   |     | m11 m12 0 |
//	| vx  vy  0   |  X  | m21 m22 0 |
//						| m31 m32 1 |
//
inline	MgULine2D operator * ( const MgULine2D& i_uln, const MgMat2E& i_mt)		// *	���W�ϊ�
{ 
//S	MgULine2D uln;
//	uln.p = i_uln.p * i_mt;
//	uln.v = i_uln.v * i_mt;
//	return i_uln;
	return MGeo::Mat2EMultULine2D( i_uln, i_mt);
}

//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgVect2D *= MgMat2E;
//
//										  | m11 m12 0 |
//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 0 |
//				   						  | m31 m32 1 |
//
inline	MgPoint2D operator *= ( MgPoint2D& io_pt, const MgMat2E& i_mt)			// *=	���W�ϊ�
{
	return MGeo::Mat2EMultEqualPoint2D( io_pt, i_mt);
}

//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgVect2D *= MgMat2E;
//
//										  | m11 m12 0 |
//	| vx  vy  0  |  =  | vx  vy  0  |  X  | m21 m22 0 |
//				   						  | m31 m32 1 |
//
inline	MgVect2D operator *= ( MgVect2D& io_pt, const MgMat2E& i_mt)			// *=	���W�ϊ�
{
	return MGeo::Mat2EMultEqualVect2D( io_pt, i_mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgLine2D *= MgMat2E;
//
//	| px  py  1   |     | px  py  1   |     | m11 m12 0 |
//	| px  py  1   |  =  | px  py  1   |  X  | m21 m22 0 |
//											| m31 m32 1 |
//
inline	MgLine2D operator *= ( MgLine2D& io_ln, const MgMat2E& i_mt)				// *=	���W�ϊ�
{ 
//S	io_ln.p[0] *= i_mt;
//	io_ln.p[1] *= i_mt;
//	return io_ln;
	return MGeo::Mat2EMultEqualLine2D( io_ln, i_mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine2D *= MgMat2E;
//
//	| px  py  1   |     | px  py  1   |     | m11 m12 0 |
//	| vx  vy  0   |  =  | vx  vy  0   |  X  | m21 m22 0 |
//											| m31 m32 1 |
//
inline	MgULine2D operator *= ( MgULine2D& io_uln, const MgMat2E& i_mt)			// *=	���W�ϊ�
{ 
//S	io_uln.p *= i_mt;
//	io_uln.v *= i_mt;
//	return io_uln;
	return MGeo::Mat2EMultEqualULine2D( io_uln, i_mt);
}

//===============( �Q�������W�ϊ��}�g���b�N�X�łR�������W���� )==============
//
//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgPoint3D = MgPoint3D1 * MgMat2E1;
//
//						  | m11 m12 0 0 |     
//	| px  py  pz  1 |  X  | m21 m22 0 0 |
//						  |  0   0  1 0 |
//						  | m31 m32 0 1 |
//
inline	MgPoint3D operator * ( const MgPoint3D& i_Pt, const MgMat2E& i_mt)		// *	���W�ϊ�
{
	return MGeo::Mat2EMultPoint3D( i_Pt, i_mt);
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgVect3D2 = MgVect3D1 * MgMat2E1;
//
//						  | m11 m12 0 0 |     
//	| vx  vy  vz  0 |  X  | m21 m22 0 0 |
//						  |  0   0  1 0 |
//						  | m31 m32 0 1 |
//
inline	MgVect3D operator * ( const MgVect3D& i_Vt, const MgMat2E& i_mt)		// *	���W�ϊ�
{
	return MGeo::Mat2EMultVect3D( i_Vt, i_mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgLine3D = MgLine3D1 * MgMat3E;
//
//	| px  py  pz  1   |     | m11 m12  0  0 |
//	| px  py  pz  1   |  X  | m21 m22  0  0 |
//							|  0   0   1  0 |
//							| m31 m32  0  1 |
//
inline	MgLine3D operator * ( const MgLine3D& i_Ln, const MgMat2E& i_mt)		// *	���W�ϊ�
{
//S	MgLine3D Ln;
//	Ln.p[0] = i_Ln.p[0] * i_mt;
//	Ln.p[1] = i_Ln.p[1] * i_mt;
//	return Ln;
	return MGeo::Mat2EMultLine3D( i_Ln, i_mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine3D = MgULine3D1 * MgMat3E;
//
//	| px  py  pz  1   |     | m11 m12  0  0 |
//	| vx  vy  vz  0   |  X  | m21 m22  0  0 |
//							|  0   0   1  0 |
//							| m31 m32  0  1 |
//
inline	MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat2E& i_mt)		// *	���W�ϊ�
{
//S	MgULine3D ULn;
//	ULn.p = i_ULn.p * i_mt;
//	ULn.v = i_ULn.v * i_mt;
//	return ULn;
	return MGeo::Mat2EMultULine3D( i_ULn, i_mt);
}

//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgPoint3D *= MgMat2E;
//
//						 						| m11 m12 0 0 |
//	| px  py  pz  1 |  =  | px  py  pz  1 |  X  | m21 m22 0 0 |
//			   									|  0   0  1 0 |
//			   									| m31 m32 0 1 |
//
inline	MgPoint3D operator *= ( MgPoint3D& io_Pt, const MgMat2E& i_mt)			// *=	���W�ϊ�

{
	return MGeo::Mat2EMultEqualPoint3D( io_Pt, i_mt);
}

//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgVect3D *= MgMat2E;
//
//						 						| m11 m12 0 0 |
//	| vx  vy  vz  0 |  =  | vx  vy  vz  0 |  X  | m21 m22 0 0 |
//			   									|  0   0  1 0 |
//			   									| m31 m32 0 1 |
//
inline	MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat2E& i_mt)			// *=	���W�ϊ�

{
	return MGeo::Mat2EMultEqualVect3D( io_Pt, i_mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgLine3D *= MgMat3E;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12  0  0 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22  0  0 |
//													|  0   0   1  0 |
//													| m31 m32  0  1 |
//
inline	MgLine3D operator *= ( MgLine3D& io_Ln, const MgMat2E& i_mt)			// *=	���W�ϊ�
{
//S	io_Ln.p[0] *= i_mt;
//	io_Ln.p[1] *= i_mt;
//	return io_Ln;
	return MGeo::Mat2EMultLine3D( io_Ln, i_mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine3D *= MgMat3E;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12  0  0 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22  0  0 |
//													|  0   0   1  0 |
//													| m31 m32  0  1 |
//
inline	MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat2E& i_mt)			// *=	���W�ϊ�
{ 
//S	io_ULn.p *= i_mt;
//	io_ULn.v *= i_mt;
//	return io_ULn;
	return MGeo::Mat2EMultEqualLine3D( io_ULn, i_mt);
}

//===========================================================================
//
//	�R�c���W�ϊ��}�g���b�N�X�̌v�Z
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̉��Z
//
//	�g�p�@
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
//	�������e
//		���W�ϊ��}�g���b�N�X�̉��Z
//
//	�g�p�@
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
//	�������e
//		���̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
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
//	�������e
//		���W�ϊ��}�g���b�N�X�̈��Z
//
//	�g�p�@
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
//	�������e
//		���W�ϊ��}�g���b�N�X�̈��Z
//
//	�g�p�@
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
//	�������e
//		���W�ϊ��}�g���b�N�X�̂����Z
//
//	�g�p�@
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
//	�������e
//		���W�ϊ��}�g���b�N�X�̂����Z
//
//	�g�p�@
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
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3E1 + Vect3D1;
//
//	| m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | vx vy vz 1 |
//
inline MgMat3E operator + ( const MgMat3E& i_M1, const MgVect3D& i_Pt)			// +	���s�ړ�
{
	MgMat3E Mw;
	Mw = i_M1;
	Mw += i_Pt;
	return Mw;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3E1 + Point3D1;
//
//	| m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | px py pz 1 |
//
inline MgMat3E operator + ( const MgMat3E& i_M1, const MgPoint3D& i_Pt)			// +	���s�ړ�
{
	return i_M1 + (MgVect3D&)i_Pt;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E1 += Vect3D1;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | vx vy vz 1 |
//
inline MgMat3E operator += ( MgMat3E& io_M1, const MgVect3D& i_Vt)				// +=	���s�ړ�
{
	io_M1.m[3][0] += i_Vt.x;
	io_M1.m[3][1] += i_Vt.y;
	io_M1.m[3][2] += i_Vt.z;
	return io_M1;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E1 += Point3D1;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | px py pz 1 |
//
inline MgMat3E operator += ( MgMat3E& io_M1, const MgPoint3D& i_Pt)				// +=	���s�ړ�
{
	return io_M1 += (MgVect3D&)i_Pt;
} 

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3E1 + Vect3D1;
//
//	| m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | vx vy vz 1 |
//
inline MgMat3E operator - ( const MgMat3E& i_M1, const MgVect3D& i_Vt)				// -	���s�ړ�
{
	MgMat3E Mw = i_M1;
	Mw -= i_Vt;
	return Mw;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3E1 + Point3D1;
//
//	| m11 m12 m13 0 |     | 1  0  0  0 |		
//	| m21 m22 m23 0 |  X  | 0  1  0  0 |
//	| m31 m32 m33 0 |     | 0  0  1  0 |
//	| m41 m42 m43 1 |     | px py pz 1 |
//
inline MgMat3E operator - ( const MgMat3E& i_M1, const MgPoint3D& i_Pt)				// -	���s�ړ�
{
	return i_M1 - (MgVect3D&)i_Pt;
}

//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E1 += Vect3D1;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     |  1   0   0  0 |		
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  |  0   1   0  0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     |  0   0   1  0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | -vx -vy -vz 1 |
//
inline MgMat3E operator -= ( MgMat3E& io_M1, const MgVect3D& i_Vt)					// -=	���s�ړ�
{
	io_M1.m[3][0] -= i_Vt.x;
	io_M1.m[3][1] -= i_Vt.y;
	io_M1.m[3][2] -= i_Vt.z;
	return io_M1;
} 
//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E1 += Point3D1;
//
//	| m11 m12 m13 0 |     | m11 m12 m13 0 |     |  1   0   0  0 |		
//	| m21 m22 m23 0 |  =  | m21 m22 m23 0 |  X  |  0   1   0  0 |
//	| m31 m32 m33 0 |     | m31 m32 m33 0 |     |  0   0   1  0 |
//	| m41 m42 m43 1 |     | m41 m42 m43 1 |     | -px -py -pz 1 |
//
inline MgMat3E operator -= ( MgMat3E& io_M1, const MgPoint3D& i_Pt)					// -=	���s�ړ�
{
	return io_M1 -= (MgVect3D&)i_Pt;
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgPoint2D = MgPoint2D * MgMat3E_1;
//
//						    | m11 m12 m13 0 |
//	| px  py  0   1   |  X  | m21 m22 m23 0 |
//						    | m31 m32 m33 0 |
//						    | m41 m42 m43 1 |
//
inline MgPoint2D operator * ( const MgPoint2D& i_Pt, const MgMat3E& i_Mt)		// ���W�ϊ�
{
	return MGeo::Mat3EMultPoint2D( i_Pt, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgVect2D = MgVect2D * MgMat3E_1;
//
//						    | m11 m12 m13 0 |
//	| vx  vy  0   0   |  X  | m21 m22 m23 0 |
//						    | m31 m32 m33 0 |
//						    | m41 m42 m43 1 |
//
inline MgVect2D operator * ( const MgVect2D& i_Pt, const MgMat3E& i_Mt)		// ���W�ϊ�
{
	return MGeo::Mat3EMultVect2D( i_Pt, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgLine2D = MgLine2D1 * MgMat3E1;
//
//	| px  py  0   1   |     | m11 m12 m13 0 |
//	| px  py  0   1   |  X  | m21 m22 m23 0 |
//							| m31 m32 m33 0 |
//							| m41 m42 m43 1 |
//
inline MgLine2D operator * ( const MgLine2D& i_ln, const MgMat3E &i_Mt)			// ���W�ϊ�
{
//S	MgLine2D ln;
//	ln.p[0] = i_ln.p[0] * i_Mt;
//	ln.p[1] = i_ln.p[1] * i_Mt;
//	return ln;
	return MGeo::Mat3EMultLine2D( i_ln, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine2D = MgULine2D1 * MgMat3E1;
//
//	| px  py  0   1   |     | m11 m12 m13 0 |
//	| vx  vy  0   0   |  X  | m21 m22 m23 0 |
//							| m31 m32 m33 0 |
//							| m41 m42 m43 1 |
//
inline MgULine2D operator * ( const MgULine2D& i_uln, const MgMat3E& i_Mt)		// ���W�ϊ�
{
	return MGeo::Mat3EMultULine2D( i_uln, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgPoint2D *= MgMat3E;
//
//						     					    | m11 m12 m13 0 |
//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 0 |
//	           									    | m31 m32 m33 0 |
//	           									    | m41 m42 m43 1 |
//
inline MgPoint2D operator *= ( MgPoint2D& io_Pt, const MgMat3E& i_Mt)			// ���W�ϊ�
{
	return MGeo::Mat3EMultEqualPoint2D( io_Pt, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgVect2D *= MgMat3E;
//
//						     					    | m11 m12 m13 0 |
//	| vx  vy  0   0   |  =  | vx  vy  0   0   |  X  | m21 m22 m23 0 |
//	           									    | m31 m32 m33 0 |
//	           									    | m41 m42 m43 1 |
//
inline MgVect2D operator *= ( MgVect2D& io_Pt, const MgMat3E& i_Mt)			// ���W�ϊ�
{
	return MGeo::Mat3EMultEqualVect2D( io_Pt, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgLine3D1 *= MgMat3E1;
//
//	| px  py  0   1   |     | px  py  0   1   |     | m11 m12 m13 0 |
//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 0 |
//													| m31 m32 m33 0 |
//													| m41 m42 m43 1 |
//
inline MgLine2D operator *= ( MgLine2D& io_ln, const MgMat3E &i_Mt)					// ���W�ϊ�
{
//S	io_ln.p[0] *= i_Mt;
//	io_ln.p[1] *= i_Mt;
//	return io_ln;
	return MGeo::Mat3EMultEqualLine2D( io_ln, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine2D *= MgMat3E;
//
//	| px  py  0   1   |     | px  py  0   1   |     | m11 m12 m13 0 |
//	| vx  vy  0   0   |  =  | vx  vy  0   0   |  X  | m21 m22 m23 0 |
//													| m31 m32 m33 0 |
//													| m41 m42 m43 1 |
//
inline MgULine2D operator *= ( MgULine2D& io_uln, const MgMat3E& i_Mt)			// ���W�ϊ�
{
//S	io_uln.p *= i_Mt;
//	io_uln.v *= i_Mt;
//	return io_uln;
	return MGeo::Mat3EMultEqualULine2D( io_uln, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgPoint3D_2 = MgPoint3D_1 * MgMat3E;
//
//	 					    | m11 m12 m13 0 |
//	| px  py  pz  1   |  X  | m21 m22 m23 0 |
//						    | m31 m32 m33 0 |
//						    | m41 m42 m43 1 |
//
inline MgPoint3D operator * ( const MgPoint3D& i_Pt, const MgMat3E& i_Mt)		// ���W�ϊ�
{
	return MGeo::Mat3EMultPoint3D( i_Pt, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgVect3D_2 = MgVect3D_1 * MgMat3E;
//
//	 					    | m11 m12 m13 0 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 0 |
//						    | m31 m32 m33 0 |
//						    | m41 m42 m43 1 |
//
inline MgVect3D operator * ( const MgVect3D& i_Pt, const MgMat3E& i_Mt)		// ���W�ϊ�
{
	return MGeo::Mat3EMultVect3D( i_Pt, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgLine3D = MgLine3D1 * MgMat3E1;
//
//	| px  py  pz  1   |     | m11 m12 m13 0 |
//	| px  py  pz  1   |  X  | m21 m22 m23 0 |
//							| m31 m32 m33 0 |
//							| m41 m42 m43 1 |
//
inline MgLine3D operator * ( const MgLine3D& i_Ln, const MgMat3E &i_Mt)			// ���W�ϊ�
{
//S	MgLine3D Ln;
//	Ln.p[0] = i_Ln.p[0] * i_Mt;
//	Ln.p[1] = i_Ln.p[1] * i_Mt;
//	return Ln;
	return MGeo::Mat3EMultLine3D( i_Ln, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine3D = MgULine3D1 * MgMat3E1;
//
//	| px  py  pz  1   |     | m11 m12 m13 0 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 0 |
//							| m31 m32 m33 0 |
//							| m41 m42 m43 1 |
//
inline MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat3E& i_Mt)		// ���W�ϊ�
{
//S	MgULine3D ULn;
//	ULn.p = i_ULn.p * i_Mt;
//	ULn.v = i_ULn.v * i_Mt;
//	return ULn;
	return MGeo::Mat3EMultULine3D( i_ULn, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgPoint3D *= MgMat3E;
//
//							 					    | m11 m12 m13 0 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 0 |
//												    | m31 m32 m33 0 |
//												    | m41 m42 m43 1 |
//
inline MgPoint3D operator *= ( MgPoint3D& io_Pt, const MgMat3E& i_Mt)			// ���W�ϊ�
{
	return MGeo::Mat3EMultEqualPoint3D( io_Pt, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgVect3D *= MgMat3E;
//
//							 					    | m11 m12 m13 0 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 0 |
//												    | m31 m32 m33 0 |
//												    | m41 m42 m43 1 |
//
inline MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat3E& i_Mt)			// ���W�ϊ�
{
	return MGeo::Mat3EMultEqualVect3D( io_Pt, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgLine3D1 *= MgMat3E1;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 0 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 0 |
//													| m31 m32 m33 0 |
//													| m41 m42 m43 1 |
//
inline MgLine3D operator *= ( MgLine3D& io_Ln, const MgMat3E &i_Mt)					// ���W�ϊ�
{
//S	io_Ln.p[0] *= i_Mt;
//	io_Ln.p[1] *= i_Mt;
//	return io_Ln;
	return MGeo::Mat3EMultEqualLine3D( io_Ln, i_Mt);
}

//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine3D *= MgMat3E;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 0 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 0 |
//													| m31 m32 m33 0 |
//													| m41 m42 m43 1 |
//
inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat3E& i_Mt)			// ���W�ϊ�
{
//S	io_ULn.p *= i_Mt;
//	io_ULn.v *= i_Mt;
//	return io_ULn;
	return MGeo::Mat3EMultEqualULine3D( io_ULn, i_Mt);
}

inline	void MgMat2E::Print( MCHAR* s)											// print
{
#ifdef LOGOUT
	MgMatPrint2( s);
#endif
}

} // namespace MC
