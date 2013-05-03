#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .h
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
namespace MC
{

//===========================================================================
//		�`�󉉎Z
//
// ---------------------( �Q���� )------------------------------
//
//	�������W�ɂ��Q�����_
//
struct MgPoint2DD{
	union{
		MREAL x;
		MREAL v[1];
	};
	MREAL y;
	MREAL w;
public:
	MgPoint2DD(MREAL x, MREAL y, MREAL w)
	{MgPoint2DD::x = x; MgPoint2DD::y = y; MgPoint2DD::w = w;}
};
//
// ---------------------( �R���� )------------------------------
//
//	�������W�ɂ��R�����_
//
struct MgPoint2DD3 {
	union{
		MREAL	x;
		MREAL v[1];
	};
		MREAL y;
		MREAL z;
		MREAL w;
public:
	MgPoint2DD3()			{}
	MgPoint2DD3(MREAL x, MREAL y, MREAL z, MREAL w)
				{MgPoint2DD3::x = x; MgPoint2DD3::y = y;
				 MgPoint2DD3::z = z; MgPoint2DD3::w = w;}
	friend MREAL operator ^ (MgPoint2DD3 p1, MgPoint2DD3 p2)					// ���� cos(191)
				 		{return (p1.x*p2.x + p1.y*p2.y + p1.z*p2.z + p1.w*p2.w);}
	friend MgPoint2DD3 operator * (MgPoint2DD3 p1, MgPoint2DD3 p2)					// �O�� sin(190)
				 		{return MgPoint2DD3(p1.y*p2.z - p1.z*p2.y,
						                  p1.z*p2.x - p1.x*p2.z,
									      p1.x*p2.y - p1.y*p2.x, 
										  p1.w*p2.w);}
};
//
//	�������W�ɂ��R��������
//
struct MgLine2DD3 {
	MgPoint2DD3 p[2];
public:
	MgLine2DD3(const MgPoint2DD3& p1, const MgPoint2DD3& p2)
			{p[0] = p1; p[1] = p2;}
};
//
//	�������W�ɂ��R�����R�p�`
//
struct MgTriangleD3 {
	MgPoint2DD3	p[3];
public:
	MgTriangleD3(const MgPoint2DD3& p1, const MgPoint2DD3& p2, const MgPoint2DD3& p3)
				{p[0] = p1; p[1] = p2; p[2] = p3;}
};
//
//	�������W�ɂ��R�������p�`
//
struct MgPolyg2DonD3 {
	int	n;
	MgPoint2D&	VDT;			//	���_���W
	int	&PN;				//	���̐����̉�]����
	int	&CC;				//	���_�̉���
	int	&TR;				//	�R�p�`��������
};
//
//	�ʕ��Ɋ֘A��������l�Ɗ֌W�f�[�^
//
struct MgPlane3DD3 {
	MREAL	a;				//	���ʌW��	���ʂ̕\�����P�ʃx�N�g��
	MREAL	b;				//				���ʂ̕\�����P�ʃx�N�g��
	MREAL	c;				//				���ʂ̕\�����P�ʃx�N�g��
	MREAL	d;				//				���_����ʕ����ʂɎ���
							//				�����t����������
	MREAL	s;				//	�ʐ�
//	----------------------------------------------------------------
	MREAL	H;				//	����
	MREAL	A;				//�@�ʐ�
//
	MREAL	PVO;			//	���_�Ƃ̊p���̑̐�
	MREAL PVA;			//	
//
	MREAL	NX;				//	�ʃx�N�g��	���ʂ̕\�����x�N�g��
	MREAL	NY;				//				���ʂ̕\�����x�N�g��
	MREAL	NZ;				//				���ʂ̕\�����x�N�g��
	MREAL	D;				//				���_����ʕ����ʂɎ���
							//				�����t����������
//
	MREAL	Ma;				//	�ŋߖT�����Ő��@��
	MREAL	Mb;				//				�@�@��
//	MREAL	c;				//				���ʂ̕\�����P�ʃx�N�g��
//	MREAL	d;				//				���_����ƕ����ʂɎ���
//							//				�����t����������
//	MREAL	a;				//	���ʌW��	���ʂ̕\�����P�ʃx�N�g��
//	MREAL	b;				//				���ʂ̕\�����P�ʃx�N�g��
//
//
	MREAL	I;				//	����
//
	MREAL	RX;				//	�_���W		X
	MREAL	RY;				//				Y
	MREAL	RZ;				//				Z
	MREAL	RW;				//				W
public:
	MgPlane3DD3()				{}
	MgPlane3DD3(const MgPoint2DD3& p0, const MgPoint2DD3& p1, const MgPoint2DD3& p2);
	MgPlane3DD3(const MgMat3DE &m1);

};
//
//	������ԁA�Օ���Ԃ�\���e�[�u��
//
struct MgISD3 {
	int	i;					//	�}�`�P�������O
							//	1:���̓_��花������
							//	0:���̓_�݂̂Ŋ��A���̓_�Ŋ����I��
							//	  �A�܂��͂܂����������Ă��Ȃ�
	int	a;					//	�}�`�P�p�����[�^
							//	��_�̈ʒu�i�}�`�P���_�ԍ����Έʒu�j
	int	b;					//	�}�`�Q�p�����[�^
							//	��_�̈ʒu�i�}�`�Q���_�ԍ����Έʒu�j
							//	�A�܂��͐}�`�P�̒[�_��
							//	-1:�}�`�Q�̓����A-2:�}�`�Q�̊O��
};
//
//
struct MgCVTD3 {
};
//
int MgIntersect(const MgLine2DD3 &Ln1, const MgLine2DD3 &Ln2, int *ist);
//	�Q�����̏d�Ȃ�A�����e�X�g(0,1)
int MgIntersect(const MgPoint2DD3& p1, const MgTriangleD3 &t1, int *ist);
//	�_�ƂR�p�`�̔���ԃe�X�g(2)
int MgInside(const MgTriangleD3 &t1, const MgPoint2DD3& p1, int *ist);
//	�R�p�`�Ɠ_�i���ʁj�̓��O�e�X�g(3)
int MgIntersect(const MgLine2DD3 &Ln1, const MgTriangleD3 &t1);
//	�����ƂR�p�`�̌����e�X�g(4,5,6)
void  MgMkCVT(const MgPolyg2DonD3 &pg1, MgCVTD3 *cvt);
//	�ʕ��̓��������߂�(10,11)
void  MbPartition(const MgPolyg2DonD3 &pg1, MgCVTD3 *cvt);
//	�ʕ��̂R�p�`����(12)
int MgVolume(const MgPoint2DD3& p1, const MgPolyg2DonD3 &pg1, MgCVTD3 *cvt);
//	�_�Ɩʕ��̐��̑̐ς̎Z�o�A����(20)
int MgInside(const MgPolyg2DonD3 &pg1, const MgPoint2DD3& p1, int *ist);
//	�ʕ��ɑ΂���_�i���ʁj�̓��O�e�X�g(21)
int MgShade(const MgPolyg2DonD3 &pg1, const MgPoint2DD3& p1, int *ist);
//	�ʕ��ɑ΂���_�i���ʁj�̎Օ�(22)
int MgIntersect(const MgLine2DD3 &Ln1, const MgPolyg2DonD3 &Ln2, int *ist);
//	�����Ɩʕ��̌����e�X�g(30,31,32)
int MgNearestEdge(const MgLine2DD3 &Ln1, const MgPolyg2DonD3 &Ln2, int *ist);
//	�ŋߖT�����Ő�(33)
int MgInside(const MgPolyg2DonD3 &pg1, const MgLine2DD3 &Ln1, int *ist);
//	�ʕ��ɑ΂�������i���ʁj�̓��O�e�X�g(34)
int MgShade(const MgPolyg2DonD3 &pg1, const MgLine2DD3 &Ln1, int *ist);
//	�ʕ��ɑ΂�������i���ʁj�̎Օ�(35)
MgPoint2DD3 MbRatio(const MgPoint2DD3& p1, const MgPoint2DD3& p2, MREAL r1);
//	�����u���u���Ɠ�����r1���A�����u���u����r1:(1-r1)�ɓ�������_��
//	�������W�l�̎Z�o(192)
void MgSValue(const MgPoint2DD3& p1, int a, int b, MgCVTD3 *cvt);
//	�_p1(Vx)��a,b���ASxijk(i=a..b)��SARY[i]�ɏ�������(200)
//	(j=i+1, k=i+2)
void MgSValue(const MgPoint2DD3& p1, const MgPoint2DD3& p2, int a, int b, MgCVTD3 *cvt);
//	�_p1(Vx)�A�_p2(Vy)��a,b���ASxyij(i=a..b)��SARY[i]�ɏ�������(220)
//	(j=i+1)
void MgSValue(const MgPoint2DD3& p1, const MgPoint2DD3& p2, const MgPoint2D& p3, 
			  int a, int b, MgCVTD3 *cvt);
//	�_p1(Vx)�A�_p2(Vy)�A�_p3(Vz)��a,b���ASxyzi(i=a..b)��SARY[i]�ɏ�������(220)


} // namespace MC
