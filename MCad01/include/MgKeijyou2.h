#pragma once

namespace MC
{

// �}�`�^

// �_�^
// MgPoint2D	or MgVect2D
// MgPoint3D or MgVect3D

// �����^
// MgULine2D
// MgULine3D

// �����^
// MgLine2D
// MgLine3D

// �~�^
struct	MgCir2D {
	MgPoint2D			CPnt;				// ���S�_
	MREAL			Rad;				// ���a
};

struct	MgCir3D {
	MgPoint3D		CPnt;				// ���S�_
	MgPoint3D		Vect;				// ���ʂ̒P�ʖ@���޸��
	MREAL			Rad;				// ���a
};
/*
struct	MgCirs2 {
	MgPoint2D			Pnt1;				// �O�ڂ��鍶��
	MgPoint2D			Pnt2;				// �O�ڂ���E��
};

struct	MgCirs3 {
	MgPoint3D		Pnt1;				// �O�ڂ��鍶��
	MgPoint3D		Pnt2;				// �O�ڂ���E��
};
*/
// �~�ʌ^
struct	MgArc2D {
	MgPoint2D			CPnt;				// ���S�_
	MgPoint2D			Pnt[2];				// �n�_�A�I�_
};

struct	MgAarc3 {
	MgPoint3D		CPnt;				// ���S�_
	MgPoint3D		Vect;				// ���ʂ̒P�ʖ@���޸��
 	MgPoint3D		Pnt[2];				// �n�_�A�I�_
};
/*
struct	MgArcx2 {
	MgPoint2D			CPnt;				// ���S�_�i���S�_���W�l�j
	MREAL 			Rad;				// ���a�i�����j
	MREAL 			Sta;				// �n�_�p�i�p�x�F�P�ʓx�j
	MREAL 			End;				// �I�_�p�i�p�x�F�P�ʓx�j
};

struct	MgArcx3 {
	MgPoint3D		CPnt;				// ���S�_�i���S�_���W�l�j
	MREAL 			Rad;				// ���a�i�����j
	MREAL 			Sta;				// �n�_�p�i�p�x�F�P�ʓx�j
	MREAL 			End;				// �I�_�p�i�p�x�F�P�ʓx�j
};

struct	MgArcs2 {
	MgPoint2D			Pnt1;				// �O�ڂ��鍶��
	MgPoint2D			Pnt2;				// �O�ڂ���E��
	MgPoint2D			Pnt3;				// �J�n�_
	MgPoint2D			Pnt4;				// �I���_
};

struct	MgArcs3 {
	MgPoint3D		Pnt1;				// �O�ڂ��鍶��
	MgPoint3D		Pnt2;				// �O�ڂ���E��
	MgPoint3D		Pnt3;				// �J�n�_
	MgPoint3D		Pnt4;				// �I���_
};
*/
// �ȉ~�^
struct	MgEps2 {
	MgPoint2D			CPnt;				// ���S�_( x, y)
	MgPoint2D			FPnt;				// �œ_
	MREAL			Lrad;				// ���a
};

struct	MgEps3 {
	MgPoint3D		CPnt;				// ���S�_(x, y, z)
	MgPoint3D		FPnt;				// �œ_  (x, y, z)
	MgPoint3D		Vect;				// ���ʂ̒P�ʖ@���޸��(x, y, z)
	MREAL			Lrad;				// ���a
};

// �ȉ~�ʌ^
struct	MgAel2 {
	MgPoint2D			CPnt;				// ���S�_
	MgPoint2D			FPnt;				// �œ_
	MREAL			Lrad;				// ���a
	MgPoint2D			SPnt;				// �n�_
	MgPoint2D			EPnt;				// �I�_
};

struct	MgAeLn3  {
	MgPoint3D		CPnt;				// ���S�_
	MgPoint3D		FPnt;				// �œ_
	MgPoint3D		Vect;				// ���ʂ̒P�ʖ@���޸��
	MREAL			Lrad;				// ���a
	MgPoint3D		SPnt;				// �n�_
	MgPoint3D		EPnt;				// �I�_
};

// �ʌ^
struct	MgPLn3 {
	MREAL			Dist;				// ���_����̋���
	MgPoint3D		Vect;				// �P�ʖ@���޸��
};

// �~���ʌ^
struct	MgCyLn3  {
	MgPoint3D		Pnt;				// ����̓_
	MgPoint3D		Vect;				// ���S���޸��
	MREAL			Rad;				// ���a
	MREAL			Height;				// ����
};

// �A�������^ *******************
struct MgPLine2 {						// �Q�����A������
	MINT			NumPnt;				// ���_��
	MgPoint2D*		Pnt;				// ���_���W�ւ̃|�C���^
};

struct MgPLine3 {						// �R�����A������
	MINT			NumPnt;				// ���_��
	MgPoint2D*		Pnt;				// ���_���W�ւ̃|�C���^
};
/*
// ��
struct MgFace3 {
	MINT			CFlag;				// �n�_��I�_   0:���Ȃ�  1:����
	MINT			NumPnt;				// ���_��
	MgPoint3D		Pnt[4];				// ���_���W
};
*/
/*
// �̈�
struct	MgArea2 {						// �Q�����̈�
	MINT			NumPnt;				// �_��
	MgPoint2D*		Pnt;				// ���W�l�ւ��߲��
	MgArea2*			NxtAra;				// ���̈�ւ��߲��
	MgArea2*			AnaAra;				// ���̈�ւ��߲��
};

struct	MgArea3 {						// �R�����̈�
	MINT			NumPnt;				// �_��
	MgPoint3D*		Pnt;				// ���W�l�ւ��߲��
	MgArea3*		NxtAra;				// ���̈�ւ��߲��
	MgArea3*		AnArea;				// ���̈�ւ��߲��
};

// ���b�V��
struct	MgMesh3 {
	MINT			Num;				// ү����
	MINT*			VerNumPnt;			// ү�����̒��_����
	MINT			NumPntNo;			// ���_�ԍ���
	MINT*			PntNo;				// ���_�ԍ���
	MINT			NumPnt;				// ���_��
	MgPoint3D*		Pnt;				// ���_��
};
*/
// �X�v���C���Ȑ��̍\���_����
struct	g_mgCsc2 {
	MgPoint2D			Pnt;				// �\���_���W�l
	MgPoint2D			Vect;				// �\���_�̕����P�ʃx�N�g��
	MREAL			In;					// ���͕����̑傫��
	MREAL			Out;				// �o�͕����̑傫��
};

struct	g_mgCsc3 {
	MgPoint3D		Pnt;				// �\���_���W�l
	MgPoint3D		Vect;				// �\���_�̕����P�ʃx�N�g��;
	MREAL			In; 				// ���͕����̑傫��
	MREAL			Out;				// �o�͕����̑傫��
};

// �X�v���C���Ȑ��^
struct	MgSpl2 {
	MINT			Num;				// �_�̐�
	g_mgCsc*			Spl;				// �_��Ɗe�_�ł�1�����W��
};

struct	MgSPln3 {
	MINT			Num;				// �_�̐�
	g_mgCsc3*			Spl;				// �_��Ɗe�_�ł�1�����W��
};

// �x�N�g��
struct	MgVec2 {
	MgPoint2D			Vect;				// �P�ʃx�N�g��
	MREAL			Val;				// �傫��
};

struct	MgVec3 {
	MgPoint3D		Vect;				// �P�ʃx�N�g��
	MREAL			Val;				// �傫��
};


// �X�v���C���Ȑ���̋�Ԕԍ�����уp�����^�l
struct	MgParm {
	MINT			Kno;				// ��Ԕԍ�
	MREAL			Par;				// �p�����^�l
};

} // namespace MC
