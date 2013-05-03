//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#include "MgLib.h"
#include "MgMat.h"
#include "MgKeijyou.h"

namespace MC
{

//===========================================================================
//		�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
//	�������W�ɂ��R�_���r�`�������߂�
//
MREAL	MgSMatD(const MgPoint2DD3& p0, const MgPoint2DD3& p1,
			   const MgPoint2DD3& p2)
{
	return 
	(	  p0.x * (p1.y*p2.w-p1.w*p2.y)
		- p0.y * (p1.x*p2.w-p1.w*p2.x)
		+ p0.w * (p1.x*p2.y-p1.y*p2.x));
}
//
// ---------------------( �R���� )------------------------------
//
//	�������W�ɂ��S�_���r�`�������߂�
//
MREAL	MgSMatD3(const MgPoint2DD3& p0, const MgPoint2DD3& p1,
				 const MgPoint2DD3& p2, const MgPoint2DD3& p3)
{
	return 
	(	  (p0.x*p1.y-p0.y*p1.x) * (p2.z*p3.w-p2.w*p3.z)
		- (p0.x*p1.z-p0.z*p1.x) * (p2.y*p3.w-p2.w*p3.y)
		+ (p0.x*p1.w-p0.w*p1.x) * (p2.y*p3.z-p2.z*p3.y)
		+ (p0.y*p1.z-p0.z*p1.y) * (p2.x*p3.w-p2.w*p3.x)
		- (p0.y*p1.z-p0.z*p1.y) * (p2.x*p3.z-p2.z*p3.x)
		+ (p0.z*p1.w-p0.w*p1.z) * (p2.x*p3.y-p2.y*p3.x));
}
//
//	�������W�ɂ��R�_��蕽�ʎ������߂�
//
//  ���ʎ� : nx*X + ny*Y + nz*Z + d = 0
//
MgPlane3DD3::MgPlane3DD3(const MgPoint2DD3& p0, const MgPoint2DD3& p1,
						  const MgPoint2DD3& p2)
{
	MREAL xy = p1.x*p2.y - p1.y*p2.x;
	MREAL yz = p1.y*p2.z - p1.z*p2.y;
	MREAL zx = p1.z*p2.x - p1.x*p2.z;
	MREAL xw = p1.x*p2.w - p1.w*p2.x;
	MREAL yw = p1.y*p2.w - p1.w*p2.y;
	MREAL zw = p1.z*p2.w - p1.w*p2.z;
	NX = p0.y*zw - p0.z*yw + p0.w*yz;
	NY = p0.z*xw - p0.x*zw + p0.w*zx;
	NZ = p0.x*yw - p0.y*xw + p0.w*xy;
	d  = - (p0.x*yz + p0.y*zx + p0.z*xy);
}
//
//	�������W�ɂ��S�w�S�s�񎮂�蕽�ʎ������߂�
//
//  ���ʎ� : nx*X + ny*Y + nz*Z + d = 0
//
MgPlane3DD3::MgPlane3DD3(const MgMat3DE &m1)
{
	MREAL xy = m1.m[0][2] * m1.m[1][3] - m1.m[1][2] * m1.m[0][3];
	MREAL yz = m1.m[1][2] * m1.m[2][3] - m1.m[2][2] * m1.m[1][3];
	MREAL zx = m1.m[2][2] * m1.m[0][3] - m1.m[0][2] * m1.m[2][3];
	MREAL xw = m1.m[0][2] * m1.m[3][3] - m1.m[3][2] * m1.m[0][3];
	MREAL yw = m1.m[1][2] * m1.m[3][3] - m1.m[3][2] * m1.m[1][3];
	MREAL zw = m1.m[2][2] * m1.m[3][3] - m1.m[3][2] * m1.m[2][3];
	NX = m1.m[1][1] * zw - m1.m[2][1] * yw + m1.m[3][1] * yz;
	NY = m1.m[2][1] * xw - m1.m[0][1] * zw + m1.m[3][1] * zx;
	NZ = m1.m[0][1] * yw - m1.m[1][1] * xw + m1.m[3][1] * xy;
	d  = - (m1.m[0][1] * yz + m1.m[1][1] * zx + m1.m[2][1] * xy);
}
//
//	���ʂɑ΂���_�̃T�C�h�e�X�g
//
//  return -1:���ʂ̗����@0:���ʏ�@1:�ʂ̕\��
//
int	MgSide(const MgPoint2DD3& p1, const MgPlane3DD3 &Pln1)
{
	MREAL	hb1;
	MREAL	pltol;				// (���ʂ̖@���x�N�g���̐�Βl*�덷�͈�)**2

	hb1 = Pln1.NX * p1.x + Pln1.NY * p1.y +
		  Pln1.NZ * p1.z + Pln1.d * p1.w;

    pltol = g_gTol.A_2 * 
		    (Pln1.NX * Pln1.NX + Pln1.NY * Pln1.NY + Pln1.NZ * Pln1.NZ);
	if (hb1 * hb1 < pltol) return 0;
	if (hb1 > 0) return 1;
	return -1;
}
//
//	�Q�����̏d�Ȃ�A�����e�X�g(0,1)
MINT MgIntersect(const MgLine2DD3 &Ln1, const MgLine2DD3 &Ln2, MINT *ist)
{
/*
	MREAL s1, s2, s3, s4;
	s1 = MgSMatD3(n1, Ln1.p[0], Ln1.p[1], Ln2.p[0]);
	s2 = MgSMatD3(n1, Ln1.p[0], Ln1.p[1], Ln2.p[1]);
	s3 = MgSMatD3(n1, Ln2.p[0], Ln2.p[1], Ln1.p[0]);
	s4 = MgSMatD3(n1, Ln2.p[0], Ln2.p[1], Ln1.p[1]);
*/
	return 1;
}
MREAL	MgSMatD3(const MgPoint2DD3& p0, const MgPoint2DD3& p1,
				 const MgPoint2DD3& p2, const MgPoint2DD3& p3);
MINT MgIntersect(const MgPoint2DD3& p1, const MgTriangleD3 &t1, MINT *ist);
//	�_�ƂR�p�`�̔���ԃe�X�g(2)
MINT MgInside(const MgTriangleD3 &t1, const MgPoint2DD3& p1, MINT *ist);
//	�R�p�`�Ɠ_�i���ʁj�̓��O�e�X�g(3)
MINT MgIntersect(const MgLine2DD3 &Ln1, const MgTriangleD3 &t1);
//	�����ƂR�p�`�̌����e�X�g(4,5,6)
void  MgMkCVT(const MgPolyg2DonD3 &pg1, MgCVTD3 *cvt);
//	�ʕ��̓��������߂�(10,11)
void  MgPartition(const MgPolyg2DonD3 &pg1, MgCVTD3 *cvt);
//	�ʕ��̂R�p�`����(12)
MINT MgVolume(const MgPoint2D& p1, const MgPolyg2DonD3 &pg1, MgCVTD3 *cvt);
//	�_�Ɩʕ��̐��̑̐ς̎Z�o�A����(20)
MINT MgInside(const MgPolyg2DonD3 &pg1, const MgPoint2DD3& p1, MINT *ist);
//	�ʕ��ɑ΂���_�i���ʁj�̓��O�e�X�g(21)
MINT MgShade(const MgPolyg2DonD3 &pg1, const MgPoint2DD3& p1, MINT *ist);
//	�ʕ��ɑ΂���_�i���ʁj�̎Օ�(22)
MINT MgIntersect(const MgLine2DD3 &Ln1, const MgPolyg2DonD3 &Ln2, MINT *ist);
//	�����Ɩʕ��̌����e�X�g(30,31,32)
MINT MgNearestEdge(const MgLine2DD3 &Ln1, const MgPolyg2DonD3 &Ln2, MINT *ist);
//	�ŋߖT�����Ő�(33)
MINT MgInside(const MgPolyg2DonD3 &pg1, const MgLine2DD3 &Ln1, MINT *ist);
//	�ʕ��ɑ΂�������i���ʁj�̓��O�e�X�g(34)
MINT MgShade(const MgPolyg2DonD3 &pg1, const MgLine2DD3 &Ln1, MINT *ist);
//	�ʕ��ɑ΂�������i���ʁj�̎Օ�(35)
MgPoint2DD3 MgRatio(const MgPoint2D& p1, const MgPoint2D& p2, MREAL r1);
//	�����u���u���Ɠ�����r1���A�����u���u����r1:(1-r1)�ɓ�������_��
//	�������W�l�̎Z�o(192)
void MgSValue(const MgPoint2DD3& p1, MINT a, MINT b, MgCVTD3 *cvt);
//	�_p1(Vx)��a,b���ASxijk(i=a..b)��SARY[i]�ɏ�������(200)
//	(j=i+1, k=i+2)
void MgSValue(const MgPoint2DD3& p1, const MgPoint2DD3& p2, MINT a, MINT b, MgCVTD3 *cvt);
//	�_p1(Vx)�A�_p2(Vy)��a,b���ASxyij(i=a..b)��SARY[i]�ɏ�������(220)
//	(j=i+1)
void MgSValue(const MgPoint2DD3& p1, const MgPoint2DD3& p2, const MgPoint2D& p3, 
			  MINT a, MINT b, MgCVTD3 *cvt);
//	�_p1(Vx)�A�_p2(Vy)�A�_p3(Vz)��a,b���ASxyzi(i=a..b)��SARY[i]�ɏ�������(220)
	
} // namespace MC
