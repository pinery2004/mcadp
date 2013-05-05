//==========================================================================================
//	Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//	MODULE: MgMat.cpp
//
//	�}�g���b�N�X�̌v�Z
//
//�@�{�֐����g�p����v���O�����́A�}�g���b�N�X�ϊ��̑O�����͍����Ɍ㏈���͉E���ɋL�q����B
//
//	K.Matsu           08/01/04    Created.
//==========================================================================================
//
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#define	DLL_EXPORT_MAT_DO

#include "MgMat.h"

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"

namespace MC
{

static MgMat2E McMatN  = MgMat2E ( 1.0f, 0.0f,
						 		 0.0f, 1.0f,
								 0.0f, 0.0f);
static MgMat3E McMat3N = MgMat3E( 1.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, 1.0f,
								0.0f, 0.0f, 0.0f);

//
void MgMat2E::SetUnit() {*this = McMatN;}
void MgMat3E::SetUnit() {*this = McMat3N;}

//// �w�莲�𒆐S�ɉ�]����
//MgRot( MgULine3D& i_UL, MgVect3D& i_VR)
//{
//	MREAL	Vx2 = i_UL.v.x * i_UL.v.x;
//	MREAL	Vy2 = i_UL.v.y * i_UL.v.y;
//	MREAL	Vz2 = i_UL.v.z * i_UL.v.z;
//	MREAL	Vxy = i_UL.v.x * i_UL.v.y;
//	MREAL	Vyz = i_UL.v.y * i_UL.v.z;
//	MREAL	Vzx = i_UL.v.z * i_UL.v.x;
//	MREAL	VRmc = 1 - i_VR.x;
//	MgMat3E	M1;
//	M1.m[0][0]
//}

//===========================================================================
//
//	�Q�c���W�ϊ��}�g���b�N�X�̌v�Z
//
//	| m11 m12 m13 |
//	| m21 m22 m23 |
//	| m31 m32 m33 |
//
//	| ���@���@�� |     | ���@���@�� |
//	| ���@���@�� |  X  | ���@���@�� |
//	| dx�@dy�@�� |     | dx  dy  �� |
//
//
//	|  x�@ y�@�� |     | ���@���@�� |
//				�@  X  | ���@���@�� |
//					   | dx  dy�@�� |
//
//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̉��Z
//
//	�g�p�@
//		MgMat3E = MgMat2E1 + MgMat2E2;
//
//	| m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  +  | n21 n22 n23 |
//	| m31 m32 m33 |     | n31 n32 n33 |
//
//MgMat2E operator + (const MgMat2E &tm, const MgMat2E &tn)
MgMat2E MGeo::Mat2EPlus( const MgMat2E& i_tm, const MgMat2E& i_tn)
{
	MgMat2E	to;
	int		ic;
	for ( ic=0; ic<3; ic++) {
		to.m[ic][0] = i_tm.m[ic][0] + i_tn.m[ic][0];
		to.m[ic][1] = i_tm.m[ic][1] + i_tn.m[ic][1];
		to.m[ic][2] = i_tm.m[ic][2] + i_tn.m[ic][2];
	}
	return to;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̉��Z
//
//	�g�p�@
//		MgMat2E1 += MgMat2E2;
//
//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  =  | m21 m22 m23 |  +  | n21 n22 n23 |
//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
//
//MgMat2E operator += (MgMat2E &tm, const MgMat2E &tn)
MgMat2E MGeo::Mat2EPlusEqual( MgMat2E& io_tm, const MgMat2E& i_tn)
{
	int		ic;
	for ( ic=0; ic<3; ic++) {
		io_tm.m[ic][0] += i_tn.m[ic][0];
		io_tm.m[ic][1] += i_tn.m[ic][1];
		io_tm.m[ic][2] += i_tn.m[ic][2];
	}
	return io_tm;
}
//
//===========================================================================
//	�������e
//		���̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E2 = - MgMat2E1;
//
//	  | -m11 -m12 0 |
//	  | -m21 -m22 0 |
//	  | -m31 -m32 1 |
//
//MgMat2E operator - (const MgMat2E &tm)
MgMat2E MGeo::Mat2EMinusSingle( const MgMat2E& i_tm)
{
	return MgMat2E( -i_tm.m[0][0], -i_tm.m[0][1],
		            -i_tm.m[1][0], -i_tm.m[1][1],
				    -i_tm.m[2][0], -i_tm.m[2][1]);
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̈��Z
//
//	�g�p�@
//		MgMat2E = MgMat2E1 - MgMat2E2;
//
//	  | m11 m12 m13 |     | n11 n12 n13 |
//	  | m21 m22 m23 |  -  | n21 n22 n23 |
//	  | m31 m32 m33 |     | n31 n32 n33 |
//
//MgMat2E operator - (const MgMat2E &M1, const MgMat2E &M2)
MgMat2E MGeo::Mat2EMinus( const MgMat2E& i_tm, const MgMat2E& i_tn)
{
	MgMat2E	to;
	int		ic;
	for ( ic=0; ic<3; ic++) {
		to.m[ic][0] = i_tm.m[ic][0] - i_tn.m[ic][0];
		to.m[ic][1] = i_tm.m[ic][1] - i_tn.m[ic][1];
		to.m[ic][2] = i_tm.m[ic][2] - i_tn.m[ic][2];
	}
	return to;
}
//
//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̈��Z
//
//	�g�p�@
//		MgMat2E1 -= MgMat2E2;
//
//	| m11 m12 m13 |    | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  = | m21 m22 m23 |  -  | n21 n22 n23 |
//	| m31 m32 m33 |    | m31 m32 m33 |     | n31 n32 n33 |
//
//MgMat2E operator -= (MgMat2E &tm, const MgMat2E &tn)
MgMat2E MGeo::Mat2EMinusEqual( MgMat2E& io_tm, const MgMat2E& i_tn)
{
	int		ic;
	for ( ic=0; ic<3; ic++) {
		io_tm.m[ic][0] -= i_tn.m[ic][0];
		io_tm.m[ic][1] -= i_tn.m[ic][1];
		io_tm.m[ic][2] -= i_tn.m[ic][2];
	}
	return io_tm;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̂����Z
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɍ��W�ϊ��}�g���b�N�X�ɂ��ϊ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E = MgMat2E1 * MgMat2E2;
//
//	| m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  X  | n21 n22 n23 |
//	| m31 m32 m33 |     | n31 n32 n33 |
//
//MgMat2E operator * (const MgMat2E &tm, const MgMat2E &tn)
MgMat2E MGeo::Mat2EMult( const MgMat2E& i_tm, const MgMat2E& i_tn)
{
	MgMat2E	to;
	int		i1, i2;
	for (i1=0; i1<3; i1++) 
		for (i2=0; i2<3; i2++) 
			to.m[i1][i2] = i_tm.m[i1][0] * i_tn.m[0][i2] +
						   i_tm.m[i1][1] * i_tn.m[1][i2] +
						   i_tm.m[i1][2] * i_tn.m[2][i2]	;
	return to;
}
//
//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�̂����Z
//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɍ��W�ϊ��}�g���b�N�X�ɂ��ϊ�����}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E2 *= MgMat2E1;
//
//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  =  | m21 m22 m23 |  X  | n21 n22 n23 |
//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
//
//MgMat2E operator *= (MgMat2E &tm, const MgMat2E &tn)
MgMat2E MGeo::Mat2EMultEqual( MgMat2E& io_tm, const MgMat2E& i_tn)
{
	MgMat2E	tw;
	int		i1, i2;
	for (i1=0; i1<3; i2++) 
		for (i2=0; i2<3; i1++) 
			tw.m[i1][i2] = io_tm.m[i1][0] * i_tn.m[0][i2] +
						   io_tm.m[i1][1] * i_tn.m[1][i2] +
						   io_tm.m[i1][2] * i_tn.m[2][i2]	;
	io_tm = tw;
	return io_tm;
}
//
//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgPoint2Dpo = MgPoint2Dp * MgMat2Etm;
//
//					   | m11 m12 m13 |
//	| px  py  1  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |     
//
//MgPoint2D operator * (const MgPoint2D& pi, const MgMat2E &tm)
MgVect2D MGeo::Mat2EMultPoint2D( const MgVect2D& i_pt, const MgMat2E& i_tm)
{
	MgVect2D	po;
	po.x = i_tm.m[0][0] * i_pt.x + i_tm.m[1][0] * i_pt.y + i_tm.m[2][0];
	po.y = i_tm.m[0][1] * i_pt.x + i_tm.m[1][1] * i_pt.y + i_tm.m[2][1];
	return po;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgVect2D *= MgMat2E;
//
//										  | m11 m12 m13 |
//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 m23 |
//				   						  | m31 m32 m33 |
//
//MgVect2D operator *= (MgVect2D& pi, const MgMat2E& tm)
MgVect2D MGeo::Mat2EMultEqualPoint2D( MgVect2D& io_pt, const MgMat2E& i_tm)
{
	MREAL	rwx;
	rwx	    = i_tm.m[0][0] * io_pt.x + i_tm.m[1][0] * io_pt.y + i_tm.m[2][0];
	io_pt.y = i_tm.m[0][1] * io_pt.x + i_tm.m[1][1] * io_pt.y + i_tm.m[2][1];
	io_pt.x = rwx;
	return io_pt;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgULine2D = MgULine2D*  MgMat2E;
//
//	| px  py  1  |     | m11 m12 m13 |
//	| vx  vy  0  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |
//
//MgULine2D operator * (const MgULine2D& uln1, const MgMat2E &m2)
MgULine2D MGeo::Mat2EMultULine2D( const MgULine2D& i_uln, const MgMat2E& i_tm)
{
	MgULine2D	ulno;
	ulno.p.x = i_tm.m[0][0] * i_uln.p.x + i_tm.m[1][0] * i_uln.p.y + i_tm.m[2][0];
	ulno.p.y = i_tm.m[0][1] * i_uln.p.x + i_tm.m[1][1] * i_uln.p.y + i_tm.m[2][1];

	ulno.v.x = i_tm.m[0][0] * i_uln.v.x + i_tm.m[1][0] * i_uln.v.y;
	ulno.v.y = i_tm.m[0][1] * i_uln.v.x + i_tm.m[1][1] * i_uln.v.y;
	return ulno;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgULine2D* = MgMat2E;
//
//	| px  py  1  |     | px  py  1  |     | m11 m12 m13 |
//	| vx  vy  0  |  =  | vx  vy  1  |  X  | m21 m22 m23 |
//			             				  | m31 m32 m33 |
//
//MgULine2D operator *= (MgULine2D& ili, const MgMat2E &m2)
MgULine2D MGeo::Mat2EMultEqualULine2D( MgULine2D& io_uln, const MgMat2E& i_tm)
{
	MREAL	rwx;
	rwx		   = i_tm.m[0][0] * io_uln.p.x + i_tm.m[1][0] * io_uln.p.y + i_tm.m[2][0];
	io_uln.p.y = i_tm.m[0][1] * io_uln.p.x + i_tm.m[1][1] * io_uln.p.y + i_tm.m[2][1];
	io_uln.p.x = rwx;

	rwx		   = i_tm.m[0][0] * io_uln.v.x + i_tm.m[1][0] * io_uln.v.y;
	io_uln.v.y = i_tm.m[0][1] * io_uln.v.x + i_tm.m[1][1] * io_uln.v.y;
	io_uln.v.x = rwx;

	return io_uln;
}
//===============( �Q�������W�ϊ��}�g���b�N�X�łR�������W���� )==============
//
//===========================================================================
//	�������e
//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgVect3D2 = MgVect3D1 * MgMat2E1;
//
//						  | m11 m12 0 m13 |     
//	| px  py  pz  1 |  X  | m21 m22 0 m23 |
//						  |  0   0  1  0  |
//						  | m31 m32 0 m33 |
//
//MgVect3D operator * (const MgVect3D& Pt1, const MgMat2E &m2)
MgVect3D MGeo::Mat2EMultPoint3D( const MgVect3D& i_Pt, const MgMat2E& i_tm)
{
	MgVect3D	Po;
	Po.x = i_tm.m[0][0] * i_Pt.x + i_tm.m[1][0] * i_Pt.y + i_tm.m[2][0];
	Po.y = i_tm.m[0][1] * i_Pt.x + i_tm.m[1][1] * i_Pt.y + i_tm.m[2][1];
	Po.z = i_Pt.z;
	return Po;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgVect3D *= MgMat2E;
//
//						 						| m11 m12 0 m13 |
//	| px  py  pz  1 |  =  | px  py  pz  1 |  X  | m21 m22 0 m23 |
//			   									|  0   0  1  0  |
//			   									| m31 m32 0 m33 |


//MgVect3D operator *= (MgVect3D& Pt1, const MgMat2E &m2)
MgVect3D MGeo::Mat2EMultEqualVect3D( MgVect3D& io_Pt, const MgMat2E& i_tm)
{
	MREAL	rwx;
	rwx		= i_tm.m[0][0] * io_Pt.x + i_tm.m[1][0] * io_Pt.y + i_tm.m[2][0];
	io_Pt.y = i_tm.m[0][1] * io_Pt.x + i_tm.m[1][1] * io_Pt.y + i_tm.m[2][1];
	io_Pt.x = rwx;
	return io_Pt;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgULine2D = MgULine2D*  MgMat2E;
//
//	| px  py  pz  1 |	  | m11 m12 0 m13 |
//	| vx  vy  vz  1 |  X  | m21 m22 0 m23 |
//						  |  0   0  1  0  |
//			   			  | m31 m32 0 m33 |
//
//MgULine3D operator * (const MgULine3D& uln1, const MgMat2E &m2)
MgULine3D MGeo::Mat2EMultULine3D( const MgULine3D& i_ULn, const MgMat2E& i_tm)
{
	MgULine3D ULno;
	ULno.p.x = i_tm.m[0][0] * i_ULn.p.x + i_tm.m[1][0] * i_ULn.p.y + i_tm.m[2][0];
	ULno.p.y = i_tm.m[0][1] * i_ULn.p.x + i_tm.m[1][1] * i_ULn.p.y + i_tm.m[2][1];
	ULno.p.z = i_ULn.p.z;

	ULno.v.x = i_tm.m[0][0] * i_ULn.v.x + i_tm.m[1][0] * i_ULn.v.y;
	ULno.v.y = i_tm.m[0][1] * i_ULn.v.x + i_tm.m[1][1] * i_ULn.v.y;
	ULno.v.z = i_ULn.v.z;
	return ULno;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//
//	�g�p�@
//		MgULine2D* = MgMat2E;
//
//	| px  py  pz  1 |     | px  py  pz  1 |		| m11 m12 0 m13 |
//	| vx  vy  vz  1 |  =  | vx  vy  vz  1 |  X  | m21 m22 0 m23 |
//												|  0   0  1  0  |
//				 				   				| m31 m32 0 m33 |
//
//MgULine3D operator *= (MgULine3D& ULn1, const MgMat2E &m2)
MgULine3D MGeo::Mat2EMultEqualULine3D( MgULine3D& io_ULn, const MgMat2E& i_tm)
{
	MREAL	rwx;
	rwx		   = i_tm.m[0][0] * io_ULn.p.x + i_tm.m[1][0] * io_ULn.p.y + i_tm.m[2][0];
	io_ULn.p.y = i_tm.m[0][1] * io_ULn.p.x + i_tm.m[1][1] * io_ULn.p.y + i_tm.m[2][1];
	io_ULn.p.x = rwx;

	rwx		   = i_tm.m[0][0] * io_ULn.v.x + i_tm.m[1][0] * io_ULn.v.y;
	io_ULn.v.y = i_tm.m[0][1] * io_ULn.v.x + i_tm.m[1][1] * io_ULn.v.y;
	io_ULn.v.x = rwx;
	return io_ULn;
}
//
//======================( �Q���� )==============================
//		�}�g���b�N�X���g���[�X����
//
void MgMat2E::MgMatPrint2( MCHAR* s)														// print
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgMat2E	=	%f, %f, %f\n")
			        Mstr( "					%f, %f, %f\n")
					Mstr( "					%f, %f, %f\n"),
							s, m[0][0], m[0][1], m[0][2],
							   m[1][0], m[1][1], m[1][2],
							   m[2][0], m[2][1], m[2][2]);
	MBLOGPRBF;
#endif
};
//
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
//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
//MgMat3E operator + (const MgMat3E &M1, const MgMat3E &M2)
MgMat3E MGeo::Mat3EPlus(const MgMat3E &i_Tm, const MgMat3E &i_Tn)
{
	MgMat3E	To;
	int		ic;
	for ( ic=0; ic<4; ic++) {
		To.m[ic][0] = i_Tm.m[ic][0] + i_Tn.m[ic][0];
		To.m[ic][1] = i_Tm.m[ic][1] + i_Tn.m[ic][1];
		To.m[ic][2] = i_Tm.m[ic][2] + i_Tn.m[ic][2];
		To.m[ic][3] = i_Tm.m[ic][3] + i_Tn.m[ic][3];
	}
	return To;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̉��Z
//
//	�g�p�@
//		MgMat3E += MgMat3E;
//
//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
//MgMat3E operator += (MgMat3E &M1, const MgMat3E &M2)
MgMat3E MGeo::Mat3EPlusEqual( MgMat3E &io_Tm, const MgMat3E &i_Tn)
{
	int		ic;
	for ( ic=0; ic<4; ic++) {
		io_Tm.m[ic][0] += i_Tn.m[ic][0];
		io_Tm.m[ic][1] += i_Tn.m[ic][1];
		io_Tm.m[ic][2] += i_Tn.m[ic][2];
		io_Tm.m[ic][3] += i_Tn.m[ic][3];
	}
	return io_Tm;
}
//
//===========================================================================
//	�������e
//		���̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E_2 = - MgMat3E_1;
//
//	  | m11 m12 m13 m14 |
//	- | m21 m22 m23 m24 |
//	  | m31 m32 m33 m34 |
//	  | m41 m42 m43 m44 |     
//
//MgMat3E operator - (const MgMat3E &M1)
MgMat3E MGeo::Mat3ESingleMinus( const MgMat3E& i_Tm)
{
	MgMat3E	To;
	int		ic;
	for ( ic=0; ic<4; ic++) {
		To.m[ic][0] = - i_Tm.m[ic][0];
		To.m[ic][1] = - i_Tm.m[ic][1];
		To.m[ic][2] = - i_Tm.m[ic][2];
		To.m[ic][3] = - i_Tm.m[ic][3];
	}
	return To;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̈��Z
//
//	�g�p�@
//		MgMat3E_3 = MgMat3E_1 - MgMat3E_2;
//
//	  | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
//	  | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	  | m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
//MgMat3E operator - (const MgMat3E &M1, const MgMat3E &M2)
MgMat3E MGeo::Mat3EMinus( const MgMat3E& i_Tm, const MgMat3E& i_Tn)
{
	MgMat3E	To;
	int		ic;
	for ( ic=0; ic<4; ic++) {
		To.m[ic][0] = i_Tm.m[ic][0] - i_Tn.m[ic][0];
		To.m[ic][1] = i_Tm.m[ic][1] - i_Tn.m[ic][1];
		To.m[ic][2] = i_Tm.m[ic][2] - i_Tn.m[ic][2];
		To.m[ic][3] = i_Tm.m[ic][3] - i_Tn.m[ic][3];
	}
	return To;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̈��Z
//
//	�g�p�@
//		MgMat3E -= MgMat3E;
//
//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
//MgMat3E operator -= (MgMat3E &M1, const MgMat3E &M2)
MgMat3E MGeo::Mat3EMinusEqual( MgMat3E& io_Tm, const MgMat3E& i_Tn)
{
	int		ic;
	for ( ic=0; ic<4; ic++) {
		io_Tm.m[ic][0] -= i_Tn.m[ic][0];
		io_Tm.m[ic][1] -= i_Tn.m[ic][1];
		io_Tm.m[ic][2] -= i_Tn.m[ic][2];
		io_Tm.m[ic][3] -= i_Tn.m[ic][3];
	}
	return io_Tm;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̂����Z
//
//	�g�p�@
//		MgMat3E_3 = MgMat3E_1 * MgMat3E_2;
//
//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
//MgMat3E operator * (const MgMat3E &M1, const MgMat3E &M2)
MgMat3E MGeo::Mat3EMult( const MgMat3E& i_Tm, const MgMat3E& i_Tn)
{
	MgMat3E	To;
	int		i1, i2;
	for (i1=0; i1<4; i1++) 
		for (i2=0; i2<4; i2++) 
			To.m[i1][i2] = i_Tm.m[i1][0] * i_Tn.m[0][i2] +
						   i_Tm.m[i1][1] * i_Tn.m[1][i2] +
						   i_Tm.m[i1][2] * i_Tn.m[2][i2] +
						   i_Tm.m[i1][3] * i_Tn.m[3][i2];
	return To;
}
//
//===========================================================================
//	�������e
//		���W�ϊ��}�g���b�N�X�̂����Z
//
//	�g�p�@
//		MgMat3E *= MgMat3E;
//
//	| m11 m12 m13 m14 |     | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
//MgMat3E operator *= (MgMat3E &M1, const MgMat3E &M2)
MgMat3E MGeo::Mat3EMultEqual( MgMat3E& io_Tm, const MgMat3E& i_Tn)
{
	MgMat3E	To;
	int		i1, i2;
	for (i1=0; i1<4; i1++) 
		for (i2=0; i2<4; i2++) 
			To.m[i1][i2] = io_Tm.m[i1][0] * i_Tn.m[0][i2] +
						   io_Tm.m[i1][1] * i_Tn.m[1][i2] +
						   io_Tm.m[i1][2] * i_Tn.m[2][i2] +
						   io_Tm.m[i1][3] * i_Tn.m[3][i2];
	io_Tm = To;
	return io_Tm;
}
//
//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgMat3E_2 = MgVect2D * MgMat3E_1;
//
//						    | m11 m12 m13 m14 |
//	| px  py  0   1   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
//MgVect2D operator * (const MgVect2D& Pt1, const MgMat3E &M1)
MgVect2D MGeo::Mat3EMultVect2D( const MgVect2D& i_Pt, const MgMat3E& i_Tm)
{
	MgVect2D	Po;
	Po.x = i_Tm.m[0][0] * i_Pt.x + i_Tm.m[1][0] * i_Pt.y + i_Tm.m[3][0];
	Po.y = i_Tm.m[0][1] * i_Pt.x + i_Tm.m[1][1] * i_Pt.y + i_Tm.m[3][1];
	return Po;
}
//
//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgVect2D *= MgMat3E;
//
//						     					    | m11 m12 m13 m14 |
//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 m24 |
//	           									    | m31 m32 m33 m34 |
//	           									    | m41 m42 m43 m44 |
//
//MgVect2D operator *= (MgVect2D& Pt1o, const MgMat3E &M1)
MgVect2D MGeo::Mat3EMultEqualVect2D( MgVect2D& io_Pt, const MgMat3E& i_Tm)
{
	MREAL	rwx;
	rwx		= i_Tm.m[0][0] * io_Pt.x + i_Tm.m[1][0] * io_Pt.y + i_Tm.m[3][0];
	io_Pt.y = i_Tm.m[0][1] * io_Pt.x + i_Tm.m[1][1] * io_Pt.y + i_Tm.m[3][1];
	io_Pt.x = rwx;
	return io_Pt;
}
//
//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgVect3D_2 = MgVect3D_1 * MgMat3E;
//
//	 					    | m11 m12 m13 m14 |
//	| px  py  pz  1   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
//MgVect3D operator * (const MgVect3D& Pt1, const MgMat3E &M1)
MgVect3D MGeo::Mat3EMultVect3D( const MgVect3D& i_Pt, const MgMat3E& i_Tm)
{
	MgVect3D	Pto;
	Pto.x = i_Tm.m[0][0] * i_Pt.x + i_Tm.m[1][0] * i_Pt.y +	i_Tm.m[2][0] * i_Pt.z + i_Tm.m[3][0];
	Pto.y = i_Tm.m[0][1] * i_Pt.x + i_Tm.m[1][1] * i_Pt.y + i_Tm.m[2][1] * i_Pt.z + i_Tm.m[3][1];
	Pto.z = i_Tm.m[0][2] * i_Pt.x + i_Tm.m[1][2] * i_Pt.y +	i_Tm.m[2][2] * i_Pt.z + i_Tm.m[3][2];
#ifdef	MGDOUJIZAHYOU
	MREAL		dd;
	dd 	  = i_Tm.m[0][3] * i_Pt.x + i_Tm.m[1][3] * i_Pt.y + i_Tm.m[2][3] * i_Pt.z + i_Tm.m[3][3];
//	_ASSERT(dd>MCTOLDN);
	if (dd > MGPTOL->DN) {
		MREAL	dd1 = 1. / dd;
		po.x *= dd1;
		po.y *= dd1;
		po.z *= dd1;
	}
#endif
	return Pto;
}
//
//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgVect3D *= MgMat3E;
//
//							 					    | m11 m12 m13 m14 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
//												    | m31 m32 m33 m34 |
//												    | m41 m42 m43 m44 |
//
//MgVect3D operator *= (MgVect3D& Pt1o, const MgMat3E &M1)
MgVect3D MGeo::Mat3EMultEqualVect3D( MgVect3D& io_Pt, const MgMat3E& i_Tm)
{
	MgVect3D	Pto;
	Pto.x = i_Tm.m[0][0] * io_Pt.x + i_Tm.m[1][0] * io_Pt.y + i_Tm.m[2][0] * io_Pt.z + i_Tm.m[3][0];
	Pto.y = i_Tm.m[0][1] * io_Pt.x + i_Tm.m[1][1] * io_Pt.y + i_Tm.m[2][1] * io_Pt.z + i_Tm.m[3][1];
	Pto.z = i_Tm.m[0][2] * io_Pt.x + i_Tm.m[1][2] * io_Pt.y + i_Tm.m[2][2] * io_Pt.z + i_Tm.m[3][2];
#ifdef	MGDOUJIZAHYOU
	MREAL		dd;
	dd 	  = i_Tm.m[0][3] * io_Pt.x + i_Tm.m[1][3] * io_Pt.y + i_Tm.m[2][3] * io_Pt.z + i_Tm.m[3][3];
//	_ASSERT(dd>MCTOLDN);
	if (dd > MGPTOL->DN) {
		MREAL	dd1 = 1. / dd;
		po.x *= dd1;
		po.y *= dd1;
		po.z *= dd1;
	}
#endif
	io_Pt = Pto;
	return io_Pt;
}
//
//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgULine3D_2 = MgULine3D_1 * MgMat3E;
//
//	| px  py  pz  1   |     | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//							| m31 m32 m33 m34 |
//							| m41 m42 m43 m44 |
//
//MgULine3D operator * (const MgULine3D& ULn1, const MgMat3E &M1)
MgULine3D MGeo::Mat3EMultULine3D( const MgULine3D& i_ULn, const MgMat3E& i_Tm)
{
	MgULine3D	ULno;
	ULno.p.x = i_Tm.m[0][0] * i_ULn.p.x + i_Tm.m[1][0] * i_ULn.p.y + i_Tm.m[2][0] * i_ULn.p.z + i_Tm.m[3][0];
	ULno.p.y = i_Tm.m[0][1] * i_ULn.p.x + i_Tm.m[1][1] * i_ULn.p.y + i_Tm.m[2][1] * i_ULn.p.z + i_Tm.m[3][1];
	ULno.p.z = i_Tm.m[0][2] * i_ULn.p.x + i_Tm.m[1][2] * i_ULn.p.y + i_Tm.m[2][2] * i_ULn.p.z + i_Tm.m[3][2];
																		   
	ULno.v.x = i_Tm.m[0][0] * i_ULn.v.x + i_Tm.m[1][0] * i_ULn.v.y + i_Tm.m[2][0] * i_ULn.v.z;
	ULno.v.y = i_Tm.m[0][1] * i_ULn.v.x + i_Tm.m[1][1] * i_ULn.v.y + i_Tm.m[2][1] * i_ULn.v.z;
	ULno.v.z = i_Tm.m[0][2] * i_ULn.v.x + i_Tm.m[1][2] * i_ULn.v.y + i_Tm.m[2][2] * i_ULn.v.z;

	return ULno;
}
//
//===========================================================================
//	�������e
//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
//
//	�g�p�@
//		MgVect3D *= MgMat3E;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//													| m31 m32 m33 m34 |
//													| m41 m42 m43 m44 |
//
//MgULine3D operator *= (MgULine3D& ULn1, const MgMat3E &M1)
MgULine3D MGeo::Mat3EMultEqualULine3D( MgULine3D& io_ULn, const MgMat3E& i_Tm)
{
	MgULine3D	ULno;
	ULno.p.x = i_Tm.m[0][0] * io_ULn.p.x + i_Tm.m[1][0] * io_ULn.p.y + i_Tm.m[2][0] * io_ULn.p.z + i_Tm.m[3][0];
	ULno.p.y = i_Tm.m[0][1] * io_ULn.p.x + i_Tm.m[1][1] * io_ULn.p.y + i_Tm.m[2][1] * io_ULn.p.z + i_Tm.m[3][1];
	ULno.p.z = i_Tm.m[0][2] * io_ULn.p.x + i_Tm.m[1][2] * io_ULn.p.y + i_Tm.m[2][2] * io_ULn.p.z + i_Tm.m[3][2];
																		   
	ULno.v.x = i_Tm.m[0][0] * io_ULn.v.x + i_Tm.m[1][0] * io_ULn.v.y + i_Tm.m[2][0] * io_ULn.v.z;
	ULno.v.y = i_Tm.m[0][1] * io_ULn.v.x + i_Tm.m[1][1] * io_ULn.v.y + i_Tm.m[2][1] * io_ULn.v.z;
	ULno.v.z = i_Tm.m[0][2] * io_ULn.v.x + i_Tm.m[1][2] * io_ULn.v.y + i_Tm.m[2][2] * io_ULn.v.z;
	io_ULn = ULno;
	return io_ULn;
}
//
//======================( �R���� )==============================
//		�}�g���b�N�X���g���[�X����
//
void MgMat3E::MgMatPrint3(MCHAR* s)													// print
{
#ifdef _DEBUG
	Msprintf_s( mlLog::m_Str, Mstr( "%s	MgMat2E	=	%f, %f, %f, %f\n")
			        Mstr( "					%f, %f, %f, %f\n")
			        Mstr( "					%f, %f, %f, %f\n")
					Mstr( "					%f, %f, %f, %f\n"),
							s, m[0][0], m[0][1], m[0][2],m[0][3],
							   m[1][0], m[1][1], m[1][2],m[1][3],
							   m[2][0], m[2][1], m[2][2],m[2][3],
							   m[3][0], m[3][1], m[3][2],m[3][3]);
	MBLOGPRBF;
#endif
}

//
//======================( �Q�����A�R���� )==============================
//	�Q�����A�R�������W�ϊ��}�g���b�N�X
//
//
//======================( �Q���� )==============================
//	�������e
//		���_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E = MgMat2ERotV(MgVect2D);
//
//		( MgVect2D: �P�ʃx�N�g��)
//
//	|  cos  sin  0. |
//	| -sin  cos  0. |
//	|   0.   0.  1. |
//
MgMat2E MGeo::Mat2ERotV(const MgVect2D& v)
{
	return MgMat2E( v.x,  v.y, 
				   -v.y,  v.x, 
				    0.0f, 0.0f);
}
//
//======================( �Q���� )==============================
//	�������e
//		���_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E = MgMat2ERotRevV(MgVect2D);
//
//		( MgVect2D: �P�ʃx�N�g��)
//
//	| cos -sin  0. |
//	| sin  cos  0. |
//	|  0.   0.  1. |
//
MgMat2E MGeo::Mat2ERotRevV(const MgVect2D& v)
{
	return MgMat2E( v.x, -v.y, 
				    v.y,  v.x,
				    0.0f, 0.0f);
}
//
//======================( �R���� )==============================
//	�������e
//		�w�x���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3ERotZV(MgVect2D);
//
//		( MgVect2D: �P�ʃx�N�g��)
//
//	|  cos  sin  0.  0. |
//	| -sin  cos  0.  0. |
//	|   0.   0.  1.  0. |
//	|   0.   0.  0.  1. |
//
MgMat3E MGeo::Mat3ERotZV(const MgVect2D& v)
{
	return MgMat3E( v.x,  v.y,  0.0f,
				   -v.y,  v.x,  0.0f,
				    0.0f, 0.0f, 1.0f,
				    0.0f, 0.0f, 0.0f);
}
//
//======================( �R���� )==============================
//	�������e
//		�w�x���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3ERotRevZV(MgVect2D);
//
//		( MgVect2D: �P�ʃx�N�g��)
//
//	|  cos -sin  0.  0. |
//	|  sin  cos  0.  0. |
//	|   0.   0.  1.  0. |
//	|   0.   0.  0.  1. |
//
MgMat3E MGeo::Mat3ERotRevZV(const MgVect2D& v)
{
	return MgMat3E( v.x, -v.y,  0.0f,
				    v.y,  v.x,  0.0f,
				    0.0f, 0.0f, 1.0f,
				    0.0f, 0.0f, 0.0f);
}
//
//======================( �R���� )==============================
//	�������e
//		�x�y���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3ERotTXV(MgVect2D);
//
//		( MgVect2D: �P�ʃx�N�g��)
//
//	|  1.   0.   0.  0. |
//	|  0.  cos  sin  0. |
//	|  0. -sin  cos  0. |
//	|  0.   0.   0.  1. |
//
MgMat3E MGeo::Mat3ERotTXV(const MgVect2D& v)
{
	return MgMat3E( 1.0f,  0.0f, 0.0f,
				    0.0f,  v.x,  v.y,
				    0.0f, -v.y,  v.x,
				    0.0f,  0.0f, 0.0f);
}
//
//======================( �R���� )==============================
//	�������e
//		�x�y���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3ERotRevXV(MgVect2D);
//
//		( MgVect2D: �P�ʃx�N�g��)
//
//	|  1.   0.   0.  0. |
//	|  0.  cos -sin  0. |
//	|  0.  sin  cos  0. |
//	|  0.   0.   0.  1. |
//
MgMat3E MGeo::Mat3ERotRevXV(const MgVect2D& v)
{
	return MgMat3E( 1.0f,  0.0f, 0.0f,
				    0.0f,  v.x, -v.y,
				    0.0f,  v.y,  v.x,
				    0.0f,  0.0f, 0.0f);
}
//
//======================( �R���� )==============================
//	�������e
//		�y�w���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3ERotYV(MgVect2D);
//
//		( MgVect2D: �P�ʃx�N�g��)
//
//	|  cos   0. -sin   0. |
//	|   0.   1.   0.   0. |
//	|  sin   0.  cos   0. |
//	|   0.   0.   0.   1. |
//
MgMat3E MGeo::Mat3ERotYV(const MgVect2D& v)
{
	return MgMat3E( v.x,   0.0f, -v.y,
				    0.0f,  1.0f,  0.0f,
				    v.y,   0.0f,  v.x,
				    0.0f,  0.0f,  0.0f);
}
//
//======================( �R���� )==============================
//	�������e
//		�y�w���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat3E = MgMat3ERotRevYV(MgVect2D);
//
//		( MgVect2D: �P�ʃx�N�g��)
//
//	|  cos   0.  sin   0. |
//	|   0.   1.   0.   0. |
//	| -sin   0.  cos   0. |
//	|   0.   0.   0.   1. |
//
MgMat3E MGeo::Mat3ERotRevYV(const MgVect2D& v)
{
	return MgMat3E( v.x,   0.0f,  v.y,
				    0.0f,  1.0f,  0.0f,
				   -v.y,   0.0f,  v.x,
				    0.0f,  0.0f,  0.0f);
}
//
//======================( �Q���� )==============================
//	�������e
//	    �w�C�x�����Ɋg��^�k������}�g���b�N�X���쐬
//
//	�g�p�@
//		Mgmat_2 = MgMat2EScl(MgVect2D_1);
//
//	| sx  0   0  |
//	| 0   xy  0  |
//	| 0   0   1  |
//
MgMat2E MGeo::Mat2EScl(const MgVect2D& vs)
{
	return MgMat2E(vs.x, 0.0f, 
			       0.0f, vs.y,
				   0.0f, 0.0f);
}
//
//======================( �R���� )==============================
//	�������e
//	    �w�C�x�C�y�����Ɋg��^�k������}�g���b�N�X���쐬����
//
//	�g�p�@
//		Mgmat3_2 = MgMat3EScl(MgMat3E_1);
//
//	| sx  0   0   0  |
//	| 0   xy  0   0  |
//	| 0   0   sz  0  |
//	| 0   0   0   1  |
//
MgMat3E MGeo::Mat3EScl(const MgVect3D& vs)
{
	return MgMat3E(vs.x, 0.0f, 0.0f, 
				   0.0f, vs.y, 0.0f,
				   0.0f, 0.0f, vs.z, 
				   0.0f, 0.0f, 0.0f);
}
//
//======================( �Q���� )==============================
//	�������e
//		���s�ړ��̕ϊ��}�g���b�N�X���쐬����
//
//	�g�p�@
//		MgMat2E = MgMat2EMov(MgVect2D)
//
//	|  1.  0.  0. |
//	|  0.  1.  0. |
//	|  v.x v.y 1. |
//
MgMat2E MGeo::Mat2EMov(const MgVect2D& v)
{
	return MgMat2E(1.0f, 0.0f,
				   0.0f, 1.0f,
				   v.x,  v.y);
}

//
//======================( �R���� )==============================
//	�������e
//		���s�ړ��̕ϊ��}�g���b�N�X���쐬����
//
//	�g�p�@
//		Mgmat3 = MgMat3EMov(MgVect3D)
//
//	| 1.  0.  0.  0. |
//	| 0.  1.  0.  0. |
//	| 0.  0.  1.  0. |
//	| v.x v.y v.z 1. |
//
MgMat3E MGeo::Mat3EMov(const MgVect3D& v)
{
	return MgMat3E(1.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f,
				   0.0f, 0.0f, 1.0f,
				   v.x,  v.y,  v.z);
}
//
//======================( �Q���� )==============================
//	�������e
//		�ϊ��}�g���b�N�X�̋t�ϊ��}�g���b�N�X���쐬
//
//	�g�p�@
//		MgMat2E = MgMat2EInv(MgMat2E);
//
//	| m11 m21 m31 |
//	| m12 m22 m32 |			�i���͍s��͒P�ʍs��ł��鎖 ???�j
//	| m13 m23 m33 |
//
MgMat2E MGeo::Mat2EInv( const MgMat2E& i_tm)
{
	MgMat2E	tmlu = i_tm;
	MgMat2E	tmo;
	int		i, j, k;
	
    // LU����	
    for (i=0; i<3; i++){
        for (j=i+1; j<3; j++){
            tmlu.m[j][i] /= tmlu.m[i][i];
            for (k=i+1; k<3; k++)
                tmlu.m[j][k] -= tmlu.m[i][k] * tmlu.m[j][i];
        }
    }

    // �t�s������߂�
    for (k=0; k<3; k++){
        // ������
        for (i=0; i<3; i++){
            if( i == k){ tmo.m[i][k] = 1; }
            else{ tmo.m[i][k] = 0; }
        }
        // �������߂�
        for (i=0; i<3; i++){
            for (j=i+1; j<3; j++)
                tmo.m[j][k] -= tmo.m[i][k] * tmlu.m[j][i];
        }
        for (i=3-1; i>=0; i--){
            for (j=i+1; j<3; j++)
                tmo.m[i][k] -= tmlu.m[i][j] * tmo.m[j][k];
            tmo.m[i][k] /= tmlu.m[i][i];
        }
    }
    return tmo;
}
//
//======================( �R���� )==============================
//	�������e
//	    �ϊ��}�g���b�N�X�̋t�ϊ��}�g���b�N�X���쐬����
//
//	�g�p�@
//		Mgmat3_2 = MgMat3EInv(MgMat3E_1);
//
//	| m11 m21 m31 m41 |
//	| m12 m22 m32 m42 |     �i���͍s��͒P�ʍs��ł��鎖 ???�j
//	| m13 m23 m33 m43 |
//	| M14 m24 m34 m44 |
//
MgMat3E MGeo::Mat3EInv( const MgMat3E& i_Tm)
{
	MgMat3E	Tmlu = i_Tm;
	MgMat3E	Tmo;
	int		i, j, k;
	
    // LU���� 
    for (i=0; i<4; i++){
        for (j=i+1; j<4; j++){
            Tmlu.m[j][i] /= Tmlu.m[i][i];
            for (k=i+1; k<4; k++)
                Tmlu.m[j][k] -= Tmlu.m[i][k] * Tmlu.m[j][i];
        }
    }

    // �t�s������߂�
    for (k=0; k<4; k++){
        // ������
        for (i=0; i<4; i++){
            if( i == k)
				Tmo.m[i][k] = 1;
            else{ Tmo.m[i][k] = 0; }
        }
        // �������߂�
        for (i=0; i<4; i++){
            for (j=i+1; j<4; j++)
                Tmo.m[j][k] -= Tmo.m[i][k] * Tmlu.m[j][i];
        }
        for (i=4-1; i>=0; i--){
            for (j=i+1; j<4; j++)
                Tmo.m[i][k] -= Tmlu.m[i][j] * Tmo.m[j][k];
            Tmo.m[i][k] /= Tmlu.m[i][i];
        }
    }
    return Tmo;
}
//
//===========================================================================
//		�����ɑ΂��鋾���ϊ��s����쐬
//
// ---------------------( �Q���� )------------------------------
//
MgMat2E MGeo::Mat2EMirror(							// (  O) �����ϊ��s��
				const MgMat2E&	i_tm, 				// (I  ) �ϊ��s��
				const MgULine2D& i_uln				// (I  ) ���f�̎��Ƃ��钼��
		)
{
	MgMat2E	tmo;
//
	tmo = i_tm;
	tmo *= Mat2EMov( - i_uln.p);
	tmo *= Mat2ERotRevV( i_uln.v);
//
	tmo *= Mat2EScl( MgVect2D( 1.0f, -1.0f));
//
	tmo *= Mat2ERotV( i_uln.v);
    tmo *= Mat2EMov( i_uln.p);
	return tmo;
}
//===========================================================================
//		���ʂɑ΂��鋾���ϊ��s����쐬
//
// ---------------------( �R���� )------------------------------
//
MgMat3E MGeo::Mat3EMirror(							// (  O) �����ϊ��s��
				const	MgMat3E&  i_Tm,			// (I  ) �ϊ��s��
				const	MgPlane3D& i_Pln			// (I  ) ���f�̖ʂƂ��镽��
		)
{
	MgVect3D V0, V1, V2;
	MgMat3E	Tmo;
//
	Tmo = i_Tm;
//
	V0 = i_Pln.d * i_Pln.v;
	V1 = TaniVect3D( i_Pln.v);
	V2 = i_Pln.v ^ V1;
	MgMat3E rm1( V2, i_Pln.v, V1);
//
	Tmo *= Mat3EMov( -V0);
	Tmo *= rm1;
//
	Tmo *= Mat3EScl( MgVect3D( 1.0f, -1.0f, 1.0f));
//
	Tmo *= Mat3EInv( rm1);
	Tmo *= Mat3EMov( V0);
	return Tmo;
}
//
////===========================================================================
////		���S�_�Ɖ�]�p���ϊ��s����쐬
////
//// ---------------------( �Q���� )------------------------------
////
//MgMat2E MGeo::Mat2ERot(							// (  O) �ϊ��s��
//				const	MgPoint2D&	i_ptc, 			// (I  ) ��]�̒��S�ƂȂ�_
//				const	MREAL&		i_ar			// (I  ) ��]�p Degree
//		)
//{
//
//	MgMat2E    tmw, tmo;
//	MgAngleR  ra;
//	MgVect2D   v1;
////
//	ra.a  = MGRADIAN( i_ar);
//	v1 = MgVect2DC( ra);
////
//	tmw = Mat2ERotV( v1);
////
//    tmo = Mat2EMov( -i_ptc) * tmw;
////
//	tmo *= Mat2EMov( i_ptc);
//	return tmo;
//}
////===========================================================================
////		��]���ƂȂ钼���Ɖ�]�p���ϊ��s����쐬
////
//// ---------------------( �R���� )------------------------------
////
//MgMat3E MGeo::Mat3ERot(							// (  O) �ϊ��s��
//				const	MgULine3D&	i_ULn, 			// (I  ) ��]���ƂȂ钼��
//				const	MREAL		&i_ar			// (I  ) ��]�p(Degree)
//		)
//{
//	MgMat3E		Tmw, Tmo;
//	MgAngleR	ra;
//	MgVect2D		va;
//	MREAL		rmcos;
////
//	ra.a  = MGRADIAN( i_ar);
//	va = MgVect2DC( ra);
//	rmcos = 1 - va.x;
//
////
//	Tmw.m[0][0] = i_ULn.v.x * i_ULn.v.x * rmcos + va.x;
//	Tmw.m[1][0] = i_ULn.v.x * i_ULn.v.y * rmcos - i_ULn.v.z * va.y;
//	Tmw.m[2][0] = i_ULn.v.x * i_ULn.v.z * rmcos - i_ULn.v.y * va.y;
//		 
//	Tmw.m[0][1] = i_ULn.v.x * i_ULn.v.y * rmcos + i_ULn.v.z * va.y;
//	Tmw.m[1][1] = i_ULn.v.y * i_ULn.v.y * rmcos + va.x;
//	Tmw.m[2][1] = i_ULn.v.y * i_ULn.v.z * rmcos - i_ULn.v.x * va.y;
//		 
//	Tmw.m[0][2] = i_ULn.v.x * i_ULn.v.z * rmcos - i_ULn.v.y * va.y;
//	Tmw.m[1][2] = i_ULn.v.y * i_ULn.v.z * rmcos + i_ULn.v.x * va.y;
//	Tmw.m[2][2] = i_ULn.v.z * i_ULn.v.z * rmcos + va.x;
//
//	Tmw.m[3][0] = Tmw.m[3][1] = Tmw.m[3][2] = 
//	Tmw.m[0][3] = Tmw.m[1][3] = Tmw.m[2][3] = 0.0f;
//	Tmw.m[3][3] = 1.0f;
////
//    Tmo = Mat3EMov( -i_ULn.p) * Tmw;
////
//	//MgPoint3D a;
//	//a = i_ULn.p;
//	Tmo *= Mat3EMov( i_ULn.p);
//	return Tmo;
//}
//===========================================================================
//		�����ەϊ��s����v�Z����
//
// ---------------------( �R���� )------------------------------
//
MgMat3E MGeo::Mat3ENProj(							// (  O) �����ەϊ��s��
				const	MgMat3E	&i_Tm,			// (I  ) ���͍��W�ϊ��s��
				const	MgPlane3D	&i_Pln			// (I  ) ���ۖ�
		)
{
	MgVect3D V1, V2;
	MgMat3E	Tmw, Tmo;
	int		ic, jc;
//
	V1 = TaniVect3D( i_Pln.v);
	V2 = i_Pln.v ^ V1;
	MgMat3E Tm1(V1, V2, i_Pln.v);
//
	Tmw = Tm1 * i_Tm;
//
	Tmw.m[0][2] = Tmw.m[0][3] * i_Pln.d;	
	Tmw.m[1][2] = Tmw.m[1][3] * i_Pln.d;	
	Tmw.m[2][2] = Tmw.m[2][3] * i_Pln.d;	
	Tmw.m[3][2] = Tmw.m[3][3] * i_Pln.d;
//
	for ( ic=0; ic<4; ic++) {
		for (jc=0; jc<4; jc++) {
			Tmo.m[jc][ic] = Tmw.m[ic][0] * Tm1.m[jc][0] + Tmw.m[ic][1] * Tm1.m[jc][1]
						  + Tmw.m[ic][2] * Tm1.m[jc][2] + Tmw.m[ic][3] * Tm1.m[jc][3];
		}
	}
	return	Tmo;
}
//===========================================================================
//		�Γ��ەϊ��s����v�Z����
//
// ---------------------( �R���� )------------------------------
//
MgMat3E MGeo::Mat3ESProj(							// (  O) �Γ��ەύ��W�ϊ��s��
				const	MgMat3E	&i_Tm,			// (I  ) ���͍��W�ϊ��s��
				const	MgPlane3D	&i_Pln,			// (I  ) ���ۖ�
				const	MgVect3D&	i_V				// (I  ) ���ە����������P�ʃx�N�g��
		)
{
	MgVect3D V1, V2, V3;
	MgMat3E	Tm2, Tm3, Tmo;
	int		ic, jc;
//
	V1 = TaniVect3D( i_Pln.v);
	V2 = i_Pln.v ^ V1;
	MgMat3E Tm1(V1, V2, i_Pln.v);
//
	Tm2 = Tm1 * i_Tm;
	V3	= i_V * Tm2;
//
//	MULTIPLY TMO BY (OBLIQUE PROJECTION MATRIX).

	for ( ic=0; ic<4; ic++) {
		Tm3.m[ic][0] = Tmo.m[ic][0] - ( Tmo.m[ic][2] - Tmo.m[ic][3] * i_Pln.d) * V1.x / V1.z;
		Tm3.m[ic][1] = Tmo.m[ic][1] - ( Tmo.m[ic][2] - Tmo.m[ic][3] * i_Pln.d) * V1.y / V1.z;
		Tm3.m[ic][2] = Tmo.m[ic][3] * i_Pln.d;
		Tm3.m[ic][3] = 0.0f;
	}
//
	for ( ic=0; ic<4; ic++) {
		for (jc=0; jc<4; jc++) {
			Tmo.m[ic][jc] = Tm3.m[ic][0] * Tm1.m[jc][0] + Tm3.m[ic][1] * Tm1.m[jc][1]
						  + Tm3.m[ic][2] * Tm1.m[jc][2] + Tm3.m[ic][3] * Tm1.m[jc][3];
		}
	}
	return	Tmo;
}
/*
//===========================================================================
//		�R�c���ʏ�̓_����Q�c���W�ւ̕ϊ��s����v�Z����
//
// ---------------------( �R���� )------------------------------
//
MgMat3E MGeo::Mat3E3Dto2D(							// (  O) ���W�ϊ��s��
				const	MgPlane3D&	pln,			// (I  ) ���ʂ̖@���������P�ʃx�N�g��
				const	MgVect3D&	vi				// (I  ) ���ʂ̖@���������P�ʃx�N�g��
				)
{
	MgMat3E	M1o;
	M1o.SetUnit();
//
	MREAL ra = MgAbs( *(MgVect2D*)&pln.v);
	if (ra > MGPTOL->S)
		MgVect2D Vh = *(MgVect2D*)&pln.v;
	
	MgVect2D	vt;
	ra = MgAbs(vi);
	
	M1o.m[0][0] = vi.x;
	M1o.m[0][1] = vi.y;
	M1o.m[0][2] = vi.z;
	
	if (ra < MCTOLD) {
					// �x����]
		M1o.m[1][0] = vi.z;
		M1o.m[1][1] = 0.f;
		M1o.m[1][2] = - ra;
		M1o.m[2][0] = 0.f;
		M1o.m[2][1] = 1.f;
		M1o.m[2][2] = 0.f;

	} else {
		 			// �x����] �~ �y����]
		vt.x = vi.x / ra;
		vt.y = vi.y / ra;
		
		M1o.m[1][0] = vi.z * vt.x;
		M1o.m[1][1] = vi.z * vt.y;
		M1o.m[1][2] = - ra;
		M1o.m[2][0] = - vt.y;
		M1o.m[2][1] = vt.x;
		M1o.m[2][2] = 0.f;
	}
	M1o.m[0][3] = M1o.m[1][3] = M1o.m[2][3] =
	M1o.m[3][0] = M1o.m[3][1] = M1o.m[3][2] = 0.f;
	M1o.m[3][3] = 1.f;

	return M1o;
}
*/
//===========================================================================
//		�R�c���ʏ�̓_����Q�c���W�ւ̕ϊ��s����v�Z����
//
// ---------------------( �R���� )------------------------------
//		��ӂ�X���ɕ��s�ɂȂ�悤XY���ʂɓ��e����}�g���b�N�X�����߂�
//
//
//	���ʎ�	ax + by + cz + d = 0
//
//
//	����
//
//	(|Pln.v.z|<0.6)
//
//		Z�����̃x�N�g�����@�w,�@Z�̏��ŉ�]����Ǝ��̎��ƂȂ�A
//		���͕��ʂɑ�������												�i�Q�c���R�c�j
//		�t�ɓ��͕��ʂ��@�y�C �w�̏��ŉ�]�����Z�����̃x�N�g���ƂȂ�	�i�R�c���Q�c�j�A
//
//		sx: sin(x), cx: cos(x), sz: sin(z), cz: cos(z), (ab): sqrt(a*a+b*b)
//
//		cz = -b/(ab)	sz = a/(ab)
//		cx = c			sx = (ab)
//
//	================================================
//	�R�c���Q�c
//
//					|	1			0			0		|
//	X���t��]	A	|	0			cx			-sx		|
//					|	0			sx			cx		|
//
//					|	cz			-sz			0		|
//	Z���t��]	B	|	sz			cz			0		|
//					|	0			0			1		|
//
//	Z���t��]���X���t��]����
//					|	cz			-cxsz		sxsz	|
//		A x B	=	|	sz			cxcz		-sxcz	|
//					|	0			sx			cx		|
//
//					|	-b/(ab)		-ac/(ab)	a		|
//					|	a/(ab)		-bc/(ab)	b		|
//					|	0			(ab)		c		|
//
//	================================================
//	�Q�c���R�c
//
//	Z���t��]��(2)�ɋt�ړ�(1)�����̉�]���s��
//
//					|	cz			sz			0		|
//	Z����]		A	|	-sz			cz			0		|
//					|	0			0			1		|
//
//					|	1			0			0		|
//	X����]		B	|	0			cx			sx		|
//					|	0			-sx			cx		|
//
//	X����]��ɂy����]����
//					|	cz			sz			0		|
//		A x B		|	-szcx		czcx		sx		|
//					|	szsx		-czsx		cx		|
//
//					|	-b/(ab)		a/(ab)		0		|
//					|	-ac/(ab)	-bc/(ab)	(ab)	|
//					|	a			b			c		|
//
//	================================================
//
//	|pln.v.y|<0.6	
//
//	X����]				-sx		cx
//	Y����]		sy�cx	-sx		cy�cx
//				a		b		c
//
//	================================================
//	�R�c���Q�c
//
//					|	1			0			0			|
//	�w���t��]	B	|	0			cx			-sx			|
//					|	0			sx			cx			|
//
//					|	cy			0			sy			|
//	�x���t��]	A	|	0			1			0			|
//					|	-sy			0			cy			|
//
//	�x���t��]���X���t��]����
//					|	cy			sysx		sycx		|
//		A x B		|	0			cx			-sx			|
//					|	-sy			cysx		cycx		|
//
//					|	c/(ca)		-ab/(ca)	a			|
//		-			|	0			(ca)		b			|
//					|	-a/(ca)		-bc/(ca)	c			|
//
//	================================================
//
//	�Q�c���R�c
//					
//	Z���t��]��ɋt�ړ�����
//
//					|	cy			0			-sy			|
//	�x����]	A	|	0			1			0			|
//					|	sy			0			cy			|
//
//					|	1			0			0			|
//	X����]		B	|	0			cx			sx			|
//					|	0			-sx			cx			|
//
//	X����]���Y����]����
//					|	cy			0			-sy			|
//			A x B	|	sxsy		cx			sxcy		|
//					|	cxsy		-sx			cxcy		|
//
//					|	c/(ca)		0			-a/(ca)		|
//					|	-ab/(ca)	(ca)		-bc/(ca)	|
//					|	a			b			c			|

void MGeo::Mat3EPlntoXY(
				const	MgPlane3D	&i_Pln,		// (I  ) �ϊ��Ώە���
				const	MgPoint3D&	i_PtOrg,	// (I  ) ���_���W			
						MgMat3E*	o_MatXY,	// (  O) Pln to XY���� �R�c�}�g���b�N�X
						MgMat3E*	o_MatPln	// (  O) XY���� to Pln �R�c�}�g���b�N�X
				)
{
	MREAL		A = i_Pln.v.x, B = i_Pln.v.y, C = i_Pln.v.z;
	MgPoint3D	PtOrgD;

	// ���e�}�g���b�N�X
//	MgMat3E(MREAL m11, MREAL m12, MREAL m13, MREAL m14,
//		    MREAL m21, MREAL m22, MREAL m23, MREAL m24,
//		    MREAL m31, MREAL m32, MREAL m33, MREAL m34,
//		    MREAL m41, MREAL m42, MREAL m43, MREAL m44)

//	�R�c���Q�c�̃}�g���b�N�X�쐬
//	Z���t��]���X���t��]����

	if ( Abs( C) < 0.98) {
		MREAL	Lab = sqrt( A * A + B * B);
		
		*o_MatXY  = MgMat3E(	-B / Lab,		-A * C / Lab,	A,
								A / Lab,		-B * C / Lab,	B,
								0.,				Lab,			C,
								0.,				0.,				0.);
		PtOrgD = i_PtOrg * *o_MatXY;
		*o_MatXY -= PtOrgD;

		// �t�ϊ��}�g���b�N�X
		*o_MatPln = MgMat3E(	-B / Lab,		A / Lab,		0.,
								-A * C / Lab,	-B * C / Lab,	Lab,
								A,				B,				C,
								0.,				0.,				0.);
		*o_MatPln += i_PtOrg;
	} else {
		MREAL	Lca = sqrt( C * C + A * A);

		*o_MatXY  = MgMat3E(	C / Lca,		-A * B / Lca,	A,
								0.,				Lca,			B,
								-A / Lca,		-B * C / Lca,	C,
								0.,				0.,				0.);
		PtOrgD = i_PtOrg * *o_MatXY;
		*o_MatXY -= PtOrgD;
							
		// �t�ϊ��}�g���b�N�X
		*o_MatPln	= MgMat3E( 	C / Lca,		0.,				-A / Lca,
								-A * B / Lca,	Lca,			-B * C / Lca,
								A,				B,				C,
								0.,				0.,				0.);
		*o_MatPln += i_PtOrg;
	}
}

//
//===================(�R���� �� �Q����)=========================
//		�R�c���W���Q�c���W�֕ϊ�����
//
void MGeo::Point3Dto2D(
				const	MgPoint3D&	i_P,			// (I  ) �R�c���W
				const	MgMat3E	&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
						MgPoint2D*	o_P				// (  O) �Q�c���W
				)
{
	o_P->v[0] = i_Tm.m[0][0] * i_P.x + i_Tm.m[1][0] * i_P.y + i_Tm.m[2][0] * i_P.z + i_Tm.m[3][0];
	o_P->v[1] = i_Tm.m[0][1] * i_P.x + i_Tm.m[1][1] * i_P.y + i_Tm.m[2][1] * i_P.z + i_Tm.m[3][1];
}
/*
//
//===================(�R���� �� �Q����)=========================
//		�R�c�������Q�c�����֍��W�ϊ�����
//
inline void MGeo::Line3Dto2D(
				const MgLine3D		&i_Ln,			// (I  ) �R�c����
				const MgMat3E		&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
					  MgLine2D		*o_ln			// (  O) �Q�c����
				)
						{ Mg3Dto2D( i_Ln.p[0], Mat, &o_ln->p[0]); 
						  Mg3Dto2D( i_Ln.p[1], Mat, &o_ln->p[1]);}  
*/
//
//===================(�R���� �� �Q����)=========================
//		�R�c�������Q�c�����֍��W�ϊ�����
//
void MGeo::ULine3Dto2D(
				const MgULine3D		&i_ULn,			// (I  ) �R�c����
				const MgMat3E		&i_Mt,			// (I  ) ���W�ϊ��}�g���b�N�X
					  MgULine2D		*o_uln			// (  O) �Q�c����
				)
{
	Point3Dto2D( i_ULn.p, i_Mt, &o_uln->p); 

	o_uln->v.x = i_Mt.m[0][0] * i_ULn.v.x + i_Mt.m[1][0] * i_ULn.v.y + i_Mt.m[2][0] * i_ULn.v.z;		 
	o_uln->v.y = i_Mt.m[0][1] * i_ULn.v.x + i_Mt.m[1][1] * i_ULn.v.y + i_Mt.m[2][1] * i_ULn.v.z;
	o_uln->v.SetUnitize();
}
//
//===================(�R���� �� �Q����)=========================
//		�R�c���W���Q�c���W�֕ϊ�����
//
MgPoint2D MGeo::Point3Dto2D2(						// (  O) �Q�c���W
				const	MgPoint3D&	i_P,			// (I  ) �R�c���W
				const	MgMat3E	&i_Tm			// (I  ) ���W�ϊ��}�g���b�N�X
				)
{
	MgPoint2D	Po;

	Po.x = i_Tm.m[0][0] * i_P.x + i_Tm.m[1][0] * i_P.y + i_Tm.m[2][0] * i_P.z + i_Tm.m[3][0];
	Po.y = i_Tm.m[0][1] * i_P.x + i_Tm.m[1][1] * i_P.y + i_Tm.m[2][1] * i_P.z + i_Tm.m[3][1];
	return Po;
}
/*
//
//===================(�R���� �� �Q����)=========================
//		�R�c�������Q�c�����֍��W�ϊ�����
//
inline MgLine2D MgLine3DDto2D2(						// (  O) �Q�c����
				const MgLine3D		&i_Ln,			// (I  ) �R�c����
				const MgMat3E		&i_Tm			// (I  ) ���W�ϊ��}�g���b�N�X
				)
						{ return MgLine2D( 
						  Point3Dto2D2( i_Ln.p[0], i_Tm), 
						  Point3Dto2D2( i_Ln.p[1], i_Tm));}  
*/
//
//===================(�R���� �� �Q����)=========================
//		�R�c�������Q�c�����֍��W�ϊ�����
//
MgULine2D MGeo::ULine3Dto2D2(						// (  O) �Q�c����
				const MgULine3D		&i_ULn,			// (I  ) �R�c����
				const MgMat3E		&i_Tm			// (I  ) ���W�ϊ��}�g���b�N�X
				)
{
	MgULine2D	ulno;
	Point3Dto2D( i_ULn.p, i_Tm, &ulno.p); 

	ulno.v.x = i_Tm.m[0][0] * i_ULn.v.x + i_Tm.m[1][0] * i_ULn.v.y + i_Tm.m[2][0] * i_ULn.v.z;		
	ulno.v.y = i_Tm.m[0][1] * i_ULn.v.x + i_Tm.m[1][1] * i_ULn.v.y + i_Tm.m[2][1] * i_ULn.v.z;
	ulno.v.SetUnitize();
	return ulno;
}
//
//===================(�R���� �� �Q����)=========================
//		�R�c���W�Q���Q�c���W�Q�֕ϊ�����
//
void MGeo::GPoint3Dto2D(
				const	MgGPoint3D	&i_GP,			// (I  ) �R�c���W�Q
				const	MgMat3E	&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
						MgGPoint2D	*o_GP			// (  O) �Q�c���W�Q
				)
{
	int	ic;
	o_GP->m_n = 0;
	for ( ic=0; ic<i_GP.m_n; ic++)
		*o_GP += Point3Dto2D2( i_GP.m_p[ic], i_Tm);
}

//
//===================(�R���� �� �Q����)=========================
//		�R�c���W�Q�i�|�����C���j���Q�c���W�Q�֕ϊ�����
//
void MGeo::Polyg3Dto2D(
				const	MgPolyg3D&	i_Pg,			// (I  ) �R�c���W�Q
				const	MgMat3E	&iTm,			// (I  ) ���W�ϊ��}�g���b�N�X
						MgPolyg2D*	o_Pg			// (  O) �Q�c���W�Q
				)
{
	int		ic;
	o_Pg->m_n = 0;
	for ( ic=0; ic<i_Pg.m_n; ic++)
		*o_Pg += Point3Dto2D2( i_Pg.m_P[ic], iTm);
}

//
//===================(�R���� �� �Q����)=========================
//		�R�c�����Q���Q�c�����Q�֕ϊ�����
//
void MGeo::GLine3Dto2D(
				const	MgGLine3D	&i_GLn,			// (I  ) �R�c�����Q
				const	MgMat3E	&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
						MgGLine2D*	o_gln			// (  O) �Q�c�����Q
				)
{
	int		ic;
	o_gln->m_n = 0;
	for ( ic=0; ic<i_GLn.m_n; ic++)
		*o_gln += Line3Dto2D2( i_GLn.m_ln[ic], i_Tm);
}

//
//===================(�R���� �� �Q����)=========================
//		�R�c���p�`�Q�i�|�����C���Q�j���Q�c���p�`�Q�֕ϊ�����
//
void MGeo::GPolyg3Dto2D(
				const MgGPolyg3D	&i_gPg,			// (I  ) �R�c���p�`�Q
				const MgMat3E		&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
					  MgGPolyg2D	*o_gpg			// (  O) �Q�c���p�`�Q
				)
{
	int	ic;
	MGPOLYG2( pgw, MX_PNT0);

	o_gpg->SetCount0();
	for ( ic=0; ic<i_gPg.m_n; ic++) {
		Polyg3Dto2D( i_gPg.m_Pg[ic], i_Tm, &pgw);
		(*o_gpg) += pgw;
	}
}
//
//===================(�Q���� �� �R����)=========================
//		�Q�c���W���R�c���W�֕ϊ�����
//
void MGeo::Point2Dto3D(
				const	MgPoint2D&	i_pt,			// (I  ) �Q�c���W
				const	MgMat3E	&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
						MgPoint3D	*o_Pt			// (  O) �R�c���W
				)
{
	o_Pt->v[0] = i_Tm.m[0][0] * i_pt.x + i_Tm.m[1][0] * i_pt.y + i_Tm.m[3][0];
	o_Pt->v[1] = i_Tm.m[0][1] * i_pt.x + i_Tm.m[1][1] * i_pt.y + i_Tm.m[3][1];
	o_Pt->v[2] = i_Tm.m[0][2] * i_pt.x + i_Tm.m[1][2] * i_pt.y + i_Tm.m[3][2];
}
/*
//
//===================(�Q���� �� �R����)=========================
//		�Q�c�������R�c�����֍��W�ϊ�����
//
inline void MgLine2DDto3D(
				const MgLine2D&		i_ln,			// (I  ) �Q�c����
				const MgMat3E		&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
					  MgLine3D		*o_Ln			// (  O) �R�c����
				)
						{ Mg2Dto3D( i_ln.p[0], i_Tm, &o_Ln->p[0]);
						  Mg2Dto3D( i_ln.p[1], i_Tm, &o_Ln->p[1]);}  
*/
//
//===================(�Q���� �� �R����)=========================
//		�Q�c�������R�c�����֍��W�ϊ�����
//
void MGeo::ULine2Dto3D(
				const MgULine2D		&i_uln,			// (I  ) �Q�c����
				const MgMat3E		&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
					  MgULine3D		*o_ULn			// (  O) �R�c����
				)
{
	Point2Dto3D( i_uln.p, i_Tm, &o_ULn->p); 

	o_ULn->v.x = i_Tm.m[0][0] * i_uln.v.x + i_Tm.m[1][0] * i_uln.v.y + i_Tm.m[3][0];
	o_ULn->v.y = i_Tm.m[0][1] * i_uln.v.x + i_Tm.m[1][1] * i_uln.v.y + i_Tm.m[3][1];
	o_ULn->v.z = i_Tm.m[0][2] * i_uln.v.x + i_Tm.m[1][2] * i_uln.v.y + i_Tm.m[3][2];
	o_ULn->v.SetUnitize();
}
//
//===================(�Q���� �� �R����)=========================
//		�Q�c���W���R�c���W�֕ϊ�����
//
MgPoint3D MGeo::Point2Dto3D3(						// (  O) �R�c���W
				const	MgPoint2D&	i_Pt,			// (I  ) �Q�c���W
				const	MgMat3E	&i_Tm			// (I  ) ���W�ϊ��}�g���b�N�X
				)
{
	MgPoint3D	Pto;
	Pto.x = i_Tm.m[0][0] * i_Pt.x + i_Tm.m[1][0] * i_Pt.y + i_Tm.m[3][0];
	Pto.y = i_Tm.m[0][1] * i_Pt.x + i_Tm.m[1][1] * i_Pt.y + i_Tm.m[3][1];
	Pto.z = i_Tm.m[0][2] * i_Pt.x + i_Tm.m[1][2] * i_Pt.y + i_Tm.m[3][2];
	return Pto;
}
/*
//===================(�Q���� �� �R����)=========================
//		�Q�c�������R�c�����֍��W�ϊ�����
//
inline MgLine3D MgLine2DDto3D3(						// (  O) �R�c����
				const MgLine2D&		i_ln,			// (I  ) �Q�c����
				const MgMat3E		&i_Tm			// (I  ) ���W�ϊ��}�g���b�N�X
				)
						{ return MgLine3D(
						  Mg2Dto3D( i_ln.p[0], i_Tm), 
						  Mg2Dto3D( i_ln.p[1], i_Tm))}  
*/
//
//===================(�Q���� �� �R����)=========================
//		�Q�c�������R�c�����֍��W�ϊ�����
//
MgULine3D MGeo::ULine2Dto3D3(						// (  O) �R�c����
				const MgULine2D		&i_uln,			// (I  ) �Q�c����
				const MgMat3E		&i_Tm			// (I  ) ���W�ϊ��}�g���b�N�X
				)
{
	MgULine3D	ULno;
	Point2Dto3D( i_uln.p, i_Tm, &ULno.p); 

	ULno.v.x = i_Tm.m[0][0] * i_uln.v.x + i_Tm.m[1][0] * i_uln.v.y;
	ULno.v.y = i_Tm.m[0][1] * i_uln.v.x + i_Tm.m[1][1] * i_uln.v.y;
	ULno.v.z = i_Tm.m[0][2] * i_uln.v.x + i_Tm.m[1][2] * i_uln.v.y;
	ULno.v.SetUnitize();
	return ULno;
}
//
//===================(�Q���� �� �R����)=========================
//		�Q�c���W�Q���R�c���W�Q�֕ϊ�����
//
void MGeo::GPoint2Dto3D(
				const	MgGPoint2D	&i_GPt,			// (I  ) �Q�c���W�Q
				const	MgMat3E	&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
						MgGPoint3D	*o_GPt			// (  O) �R�c���W�Q
				)
{
	int	ic;
	o_GPt->m_n = 0;
	for ( ic=0; ic<i_GPt.m_n; ic++)
		*o_GPt += Point2Dto3D3( i_GPt.m_p[ic], i_Tm);
}

//
//===================(�Q���� �� �R����)=========================
//		�Q�c���W�Q�i�|�����C���j���R�c���W�Q�֕ϊ�����
//
void MGeo::Polyg2Dto3D(
				const	MgPolyg2D&	i_Pg,			// (I  ) �Q�c���W�Q
				const	MgMat3E	&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
						MgPolyg3D*	o_Pg			// (  O) �R�c���W�Q
				)
{
	int ic;
	o_Pg->m_n = 0;
	for ( ic=0; ic<i_Pg.m_n; ic++)
		*o_Pg += Point2Dto3D3( i_Pg.m_p[ic], i_Tm);
}

//
//===================(�Q���� �� �R����)=========================
//		�Q�c�����Q���R�c�����Q�֕ϊ�����
//
void MGeo::GLine2Dto3D(
				const	MgGLine2D&	i_gln,			// (I  ) �Q�c�����Q
				const	MgMat3E	&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
						MgGLine3D	*o_GLn			// (  O) �R�c�����Q
				)
{
	int ic;
	o_GLn->m_n = 0;
	for ( ic=0; ic<i_gln.m_n; ic++)
		*o_GLn += Line2Dto3D3( i_gln.m_ln[ic], i_Tm);
}
//
//===================(�Q���� �� �R����)=========================
//		�Q�c���p�`�Q�i�|�����C���Q�j���R�c���p�`�Q�֕ϊ�����
//
void MGeo::GPolyg2Dto3D(
				const MgGPolyg2D	&i_GPg,			// (I  ) �Q�c���p�`�Q
				const MgMat3E		&i_Tm,			// (I  ) ���W�ϊ��}�g���b�N�X
					  MgGPolyg3D	*o_GPg			// (  O) �R�c���p�`�Q
				)
{
	int	ic;
	MGPOLYG3( Pgw, MX_PNT0);
	
	o_GPg->SetCount0();
	for ( ic=0; ic<i_GPg.m_n; ic++) {
		Polyg2Dto3D( i_GPg.m_pg[ic], i_Tm, &Pgw);
		(*o_GPg) += Pgw;
	}
}

/*
//
//===========================================================================
//		�s�񎮊֐�
//
void madd(double a[], double b[], double c[], int la, int lb, int lc, int m, int n)
{
	int i, j, ka, kb, kc;
	double *p, *q, *r;

	if(m <= 0 || n <= 0 || la < n || lb < n || lc < n)
	{
		fprintf(stderr, "Error : Illegal parameter  in madd()\n");
		return;
	}
	for (i=0, ka=kb=kc=0; i<m; i++, ka+=la, kb+=lb, kc+=lc)
		for (j=0, p=a+ka, q=b+kb, r=c+kc; j<n; j++)
			*r++ = *p++ + *q++;
	return;
}

void msub(double a[], double b[], double c[], int la, int lb, int lc, int m, int n)
{
	int i, j, ka, kb, kc;
	double *p, *q, *r;

	if(m <= 0 || n <= 0 || la < n || lb < n || lc < n)
	{
		fprintf(stderr, "Error : Illegal parameter  in msub()\n");
		return;
	}
	for (i=0, ka=kb=kc=0; i<m; i++, ka+=la, kb+=lb, kc+=lc)
		for (j=0, p=a+ka, q=b+kb, r=c+kc; j<n; j++)
			*r++ = *p++ - *q++;
	return;
}

void mmuLn1(double a[], double b[], int la, int lb, int m)
{
	int i, j, ka, l;
	double *p, *q, *r, w, *work;

	if(m <= 0 || la < m || lb < m)
	{
		fprintf(stderr, "Error : Illegal parameter  in mmuLn1()\n");
		return;
	}
	work = (double *)new char[m * m * sizeof(double)];
	if(work == NULL)
	{
		fprintf(stderr, "Error : Out of memory  in mmuLn1()\n");
		return;
	}
	for (i=0, ka=0, r=work; i<m; i++, ka+=la)
	{
		for (l=0; l<m; l++)
		{
			w = 0.;
			for (j=0, p=a+ka, q=b+l; j<m; j++)
			{
				w += *p++ * *q;
				q += lb;
			}
			*r++ = w;
		}
	}
	mmove(work, a, m, la, m, m);
	free((MCHAR* )work);
	return;
}

void mmuLine2D(double a[], double b[], double c[], int la, int lb, int lc, int m, int n, int k)
{
	int i, j, ka, kc, l;
	double *p, *q, *r, w;

	if(m <= 0 || n <= 0 || k <= 0 || la < n || lb < k || lc < k)
	{
		fprintf(stderr, "Error : Illegal parameter  in mmuLine2D()\n");
		return;
	}
	for (i=0, ka=kc=0; i<m; i++, ka+=la, kc+=lc)
	{
		for (l=0, r=c+kc; l<k; l++)
		{
			w = 0.;
			for (j=0, p=a+ka, q=b+l; j<n; j++)
			{
				w += *p++ * *q;
				q += lb;
			}
			*r++ = w;
		}
	}
}

void mtra1(double a[], int l, int m, int n)
{
	int i, j, ka, mn;
	double *p, *q;

	if(m <= 0 || n <= 0 || l < m || l < n || m < n)
	{
		fprintf(stderr, "Error : Illegal parameter  in mtra1()\n");
		return;
	}
	mn = m;
	if(mn < n)	mn = n;
	for (i=0, ka=0; i<mn-1; i++, ka+=l)
		for (j=i+1, p=a+ka+j, q=p+l-1; j<mn; j++, q+=l)
			swapd(p++, q);
}

void mtra2(double a[], double b[], int la, int lb, int m, int n)
{
	int i, j, ka;
	double *p, *q;

	if(m <= 0 || n <= 0 || la < n || lb < m)
	{
		fprintf(stderr, "Error : Illegal parameter  in mtra2()\n");
		return;
	}
	for (i=0, ka=0; i<m; i++, ka+=la)
		for (j=0, p=a+ka, q=b+i; j<n; j++, q+=lb) *q = *p++;
}

double minver(double a[], int l, int m, double eps)
{
	int i, j, k, *p, r, s, u, v, *work;
	double api, pivot, *q, *q1, w, w1, wmax;

	if(m < 2 || l < m || eps <= 0.)
	{
		fprintf(stderr, "Error : Illegal parameter  in minver()\n");
		return 0.;
	}
	work = (int *)new char[m * sizeof(int)];
	if(work == NULL)
	{
		fprintf(stderr, "Error : Out of memory  in minver()\n");
		return 0.;
	}
	w1 = 1.;
	for (i=0, p=work; i<m; i++)	*p++ = i;
	for (k=0, u=0; k<m; k++, u+=l)
	{
		wmax = 0.;
		for (i=k; i<m; i++)
		{
			w = fabs(*(a + i * l + k));
			if(w > wmax)
			{
				wmax = w;
				r = i;
			}
		}
		api = fabs(pivot = *(a + r * l + k));
		if(api < eps)
		{
			fprintf(stderr, "Error : api < eps  in minver()\n");
			free((MCHAR* )work);
			return w1;
		}
		w1 *= pivot;
		v = r * l;
		if(r != k)
		{
			w1 = -w1;
			swapi(work + k, work + r);
			for (j=0, q=a+u, q1=a+v; j<m; j++)	swapd(q++, q1++);
		}
		for (i=0, q=a+u; i<m; i++)	*q++ /= pivot;
		for (i=0, v=0; i<m; i++, v+=l)
		{
			if(i != k)
			{
				s = v + k;
				w = *(a + s);
				if(w != 0.)
				{
					for (j=0, q=a+u, q1=a+v; j<m; j++, q++, q1++)
						if (j != k)	*q1 -= w * *q;
					*(a + s) = - w / pivot;
				}
			}
		}
		*(a + u + k) = 1. / pivot;
	}
	for (i=0; i<m; i++)
	{
		for (;;)
		{
			k = *(work + i);
			if(k == i)	break;
			swapi(work + k, work + i);
			for (j=0, u=0; j<m; j++, u+=l)	swapd(a + u + i, a + u + k);
		}
	}
	free((MCHAR* )work);
	return w1;
}

void mmove(double a[], double b[], int la, int lb, int m, int n)
{
	int i, j, ka, kb;
	double *p, *q;

	if(m <= 0 || n <= 0 || la < n || lb < n)
	{
		fprintf(stderr, "Error : Illegal parameter  in mmove()\n");
		return;
	}
	for (i=ka=kb=0; i<m; i++, ka+=la, kb+=lb)
		for (j=0, p=a+ka, q=b+kb; j<n; j++)	*q++ = *p++;
	return;
}

void mswap(double a[], double b[], int la, int lb, int m, int n)
{
	int i, j, ka, kb;
	double *p, *q;

	if(m <= 0 || n <= 0 || la < n || lb < n)
	{
		fprintf(stderr, "Error : Illegal parameter  in mswap()\n");
		return;
	}
	for (i=ka=kb=0; i<m; i++, ka+=la, kb+=lb)
		for (j=0, p=a+ka, q=b+kb; j<n; j++)	swapd(p++, q++);
	return;
}

int jacobi(double a[], double v[], int l, int m, int *nr, double eps)
{
	int n, i, j, r, c, k1, k2, s1, s2, s3, s5, s6;
	double wmax, w, a1, a2, a3, t1, ta, si, co;

	if(m < 2 || *nr < 1 || eps <= 0.0)	return 999;
	n = 0;
	for (i=0; i<m - 1; i++)
	{
		k1 = i * l;
		for (j=i+1; j<m; j++)	if(a[k1 + j] != a[j * l + i])	return 999;
	}
	for (i=0; i<m; i++)
	{
		k1 = i * l;
		for (j=0; j<m; j++)	if(i != j)	v[k1 + j] = 0.0;
		v[k1 + i] = 1.0;
	}
	while(1)
	{
		wmax = 0.0;
		for (i=0; i<m; i++)
		{
			k1 = i * l;
			for (j=i+1; j<m; j++)
			{
				w = fabs(a[k1 + j]);
				if(w > wmax)
				{
					wmax = w;
					r = i;
					c = j;
				}
			}
		}
		if(wmax <= eps)
		{
			*nr = n;
			return 0;
		}
		if(n >= *nr)
		{
			*nr = n;
			return 1;
		}
		k1 = r * l;
		k2 = c * l;
		s1 = k1 + r;
		s2 = k2 + c;
		s3 = k1 + c;
		n++;
		a1 = a[s1];
		a2 = a[s2];
		a3 = a[s3];
		t1 = fabs(a1 - a2);
		ta = 2.0 * a3 / (t1 + sqrt(t1 * t1 + 4.0 * a3 * a3));
		if(a1 < a2)	ta = - ta;
		co = sqrt(1.0 / (ta * ta + 1.0));
		si = ta * co;
		for (i=0; i<m; i++)
		{
			s5 = i * l + r;
			s6 = i * l + c;
			w = v[s5];
			v[s5] = w * co + v[s6] * si;
			v[s6] = - w * si + v[s6] * co;
			if(i != r && i != c)
			{
				w = a[s5];
				a[s5] = w * co + a[s6] *si;
				a[s6] = - w * si + a[s6] * co;
				a[k1 + i] = a[s5];
				a[k2 + i] = a[s6];
			}
		}
		a[s1] = a1 * co * co + a2 * si * si + 2.0 * a3 * co * si;
		a[s2] = a1 + a2 - a[s1];
		a[s3] = 0.0;
		a[k2 + r] = 0.0;
	}
}

void swapi(int *a, int *b)
{
	int w;

	w = *a;
	*a = *b;
	*b = w;
	return;
}

void swapd(double *a, double *b)
{
	double w;

	w = *a;
	*a = *b;
	*b = w;
	return;
}
*/

} // namespace MC
