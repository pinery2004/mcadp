#pragma once

namespace MC
{

// �}�`�^

// �_�^
// MgPoint2	or MgVect2
// MgPoint3 or MgVect3

// �����^
// MgULine2
// MgULine3

// �����^
// MgLine2
// MgLine3

// �~�^
struct	MgCir2 {
	MgPoint2			CPnt;				// ���S�_
	MREAL			Rad;				// ���a
};

struct	MgCir3 {
	MgPoint3		CPnt;				// ���S�_
	MgPoint3		Vect;				// ���ʂ̒P�ʖ@���޸��
	MREAL			Rad;				// ���a
};
/*
struct	MgCirs2 {
	MgPoint2			Pnt1;				// �O�ڂ��鍶��
	MgPoint2			Pnt2;				// �O�ڂ���E��
};

struct	MgCirs3 {
	MgPoint3		Pnt1;				// �O�ڂ��鍶��
	MgPoint3		Pnt2;				// �O�ڂ���E��
};
*/
// �~�ʌ^
struct	MgArc2 {
	MgPoint2			CPnt;				// ���S�_
	MgPoint2			Pnt[2];				// �n�_�A�I�_
};

struct	MgAarc3 {
	MgPoint3		CPnt;				// ���S�_
	MgPoint3		Vect;				// ���ʂ̒P�ʖ@���޸��
 	MgPoint3		Pnt[2];				// �n�_�A�I�_
};
/*
struct	MgArcx2 {
	MgPoint2			CPnt;				// ���S�_�i���S�_���W�l�j
	MREAL 			Rad;				// ���a�i�����j
	MREAL 			Sta;				// �n�_�p�i�p�x�F�P�ʓx�j
	MREAL 			End;				// �I�_�p�i�p�x�F�P�ʓx�j
};

struct	MgArcx3 {
	MgPoint3		CPnt;				// ���S�_�i���S�_���W�l�j
	MREAL 			Rad;				// ���a�i�����j
	MREAL 			Sta;				// �n�_�p�i�p�x�F�P�ʓx�j
	MREAL 			End;				// �I�_�p�i�p�x�F�P�ʓx�j
};

struct	MgArcs2 {
	MgPoint2			Pnt1;				// �O�ڂ��鍶��
	MgPoint2			Pnt2;				// �O�ڂ���E��
	MgPoint2			Pnt3;				// �J�n�_
	MgPoint2			Pnt4;				// �I���_
};

struct	MgArcs3 {
	MgPoint3		Pnt1;				// �O�ڂ��鍶��
	MgPoint3		Pnt2;				// �O�ڂ���E��
	MgPoint3		Pnt3;				// �J�n�_
	MgPoint3		Pnt4;				// �I���_
};
*/
// �ȉ~�^
struct	MgEps2 {
	MgPoint2			CPnt;				// ���S�_( x, y)
	MgPoint2			FPnt;				// �œ_
	MREAL			Lrad;				// ���a
};

struct	MgEps3 {
	MgPoint3		CPnt;				// ���S�_(x, y, z)
	MgPoint3		FPnt;				// �œ_  (x, y, z)
	MgPoint3		Vect;				// ���ʂ̒P�ʖ@���޸��(x, y, z)
	MREAL			Lrad;				// ���a
};

// �ȉ~�ʌ^
struct	MgAel2 {
	MgPoint2			CPnt;				// ���S�_
	MgPoint2			FPnt;				// �œ_
	MREAL			Lrad;				// ���a
	MgPoint2			SPnt;				// �n�_
	MgPoint2			EPnt;				// �I�_
};

struct	MgAeLn3  {
	MgPoint3		CPnt;				// ���S�_
	MgPoint3		FPnt;				// �œ_
	MgPoint3		Vect;				// ���ʂ̒P�ʖ@���޸��
	MREAL			Lrad;				// ���a
	MgPoint3		SPnt;				// �n�_
	MgPoint3		EPnt;				// �I�_
};

// �ʌ^
struct	MgPLn3 {
	MREAL			Dist;				// ���_����̋���
	MgPoint3		Vect;				// �P�ʖ@���޸��
};

// �~���ʌ^
struct	MgCyLn3  {
	MgPoint3		Pnt;				// ����̓_
	MgPoint3		Vect;				// ���S���޸��
	MREAL			Rad;				// ���a
	MREAL			Height;				// ����
};

// �A�������^ *******************
struct MgPLine2 {						// �Q�����A������
	MINT			NumPnt;				// ���_��
	MgPoint2*		Pnt;				// ���_���W�ւ̃|�C���^
};

struct MgPLine3 {						// �R�����A������
	MINT			NumPnt;				// ���_��
	MgPoint2*		Pnt;				// ���_���W�ւ̃|�C���^
};
/*
// ��
struct MgFace3 {
	MINT			CFlag;				// �n�_��I�_   0:���Ȃ�  1:����
	MINT			NumPnt;				// ���_��
	MgPoint3		Pnt[4];				// ���_���W
};
*/
/*
// �̈�
struct	MgArea2 {						// �Q�����̈�
	MINT			NumPnt;				// �_��
	MgPoint2*		Pnt;				// ���W�l�ւ��߲��
	MgArea2*			NxtAra;				// ���̈�ւ��߲��
	MgArea2*			AnaAra;				// ���̈�ւ��߲��
};

struct	MgArea3 {						// �R�����̈�
	MINT			NumPnt;				// �_��
	MgPoint3*		Pnt;				// ���W�l�ւ��߲��
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
	MgPoint3*		Pnt;				// ���_��
};
*/
// �X�v���C���Ȑ��̍\���_����
struct	g_mgCsc2 {
	MgPoint2			Pnt;				// �\���_���W�l
	MgPoint2			Vect;				// �\���_�̕����P�ʃx�N�g��
	MREAL			In;					// ���͕����̑傫��
	MREAL			Out;				// �o�͕����̑傫��
};

struct	g_mgCsc3 {
	MgPoint3		Pnt;				// �\���_���W�l
	MgPoint3		Vect;				// �\���_�̕����P�ʃx�N�g��;
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
	MgPoint2			Vect;				// �P�ʃx�N�g��
	MREAL			Val;				// �傫��
};

struct	MgVec3 {
	MgPoint3		Vect;				// �P�ʃx�N�g��
	MREAL			Val;				// �傫��
};


// �X�v���C���Ȑ���̋�Ԕԍ�����уp�����^�l
struct	MgParm {
	MINT			Kno;				// ��Ԕԍ�
	MREAL			Par;				// �p�����^�l
};

} // namespace MC