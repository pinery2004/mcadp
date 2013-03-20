#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgEnt.h
//
//		�}�`�v�f�̒�`
//
//		������(lay)�͖��Ή�
//
//  K.Matsu           09/12/07    Created.
//==========================================================================================
//
#define		MPRM_SZPT	10					// �f�o�b�O���̕\���p�_�T�C�Y
//
// �}�`�v�f
//
typedef struct	_mgeprm2	{
	MSHORT		Type;						// �^�C�v
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	p[MPRM_SZPT];				// ���W�l	( x, y )
}	MgePrm2;

typedef struct	_mgeprm3	{
	MSHORT		Type;						// �^�C�v
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	P[MPRM_SZPT];				// ���W�l	( x, y )
}	MgePrm3;

//
// �_	(�Q����)
//
typedef struct	_mgepnt2	{
	MSHORT		Type;						// �^�C�v	( = MPT_DOT )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	p;							// ���W�l	( x, y )
}	MgePnt2;

//
// �_	(�R����)
//
typedef struct	_mgepnt3	{
	MSHORT		Type;						// �^�C�v	( = MPT_DOT )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	P;							// ���W�l	( x, y, z )
}	MgePnt3;

//
// ����	(�Q����)
//
typedef struct	_mgeuline2	{
	MSHORT		Type;						// �^�C�v	( = MPT_ULINE )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	p;							// �_				( x, y )
	MgVect2		v;							// �����x�N�g��	( x, y )
}	MgeULine2;

//
// ����	(�R����)
//
typedef struct	_mgeuline3	{
	MSHORT		Type;						// �^�C�v	( = MPT_ULINE )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	P;							// �_				( x, y, z )
	MgVect3		V;							// �����x�N�g��	( x, y, z )
}	MgeULine3;

//
// ����	(�Q����)
//
typedef struct	_mgeline2	{
	MSHORT		Type;						// �^�C�v	( = MPT_LINE )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	p[2];						// �n�_�A�I�_���W�l	( x, y )
}	MgeLine2;

//
// ����	(�R����)
//
typedef struct	_mgeline3	{
	MSHORT		Type;						// �^�C�v	( = MPT_LINE )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	P[2];						// �n�_�A�I�_���W�l	( x, y, z )
}	MgeLine3;

//
// �|�����C��	(�Q����)
//
typedef struct	_mgepolyline2	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLYL )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	p[MPRM_SZPT];				// �\���_���W�l	( x, y )
}	MgePlyLine2;

//
// �|�����C��	(�R����)
//
typedef struct	_mgepolyline3	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLYL )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	P[MPRM_SZPT];				// �\���_���W�l	( x, y, z )
}	MgePlyLine3;

//
// �|���S��	(�Q����)
//
typedef struct	_mgepolygon2	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLYG )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	p[MPRM_SZPT];				// �\���_���W�l	( x, y )
}	MgePlygon2;

//
// �|���S��	(�R����)
//
typedef struct	_mgepolygon3	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLYG )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	P[MPRM_SZPT];				// �\���_���W�l	( x, y, z )
}	MgePlygon3;

//
// ���t���|���S��	(�Q����)
//
typedef struct	_mgegpolygon2	{
	MSHORT		Type;						// �^�C�v	( = MPT_GPLYG )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePolygon2	*pg[MPRM_SZPT];				// �|���S���ւ̃|�C���^	( x, y )
}	MgeGPlygon2;

//
// ���t���|���S��	(�R����)
//
typedef struct	_mgegpolygon3	{
	MSHORT		Type;						// �^�C�v	( = MPT_GPLYG )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePolygon3	*Pg[MPRM_SZPT];				// �|���S���ւ̃|�C���^	( x, y, z )
}	MgeGPlygon3;

//
// �~	(�Q����)
//
typedef struct	_mgecircle2	{
	MSHORT		Type;						// �^�C�v	( = MPT_CIR )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	pc;							// ���S�_���W�l	( x, y )
	MREAL		r;							// ���a
}	MgeCircle2;

//
// �~	(�R����)
//
typedef struct	_mgecircle2	{
	MSHORT		Type;						// �^�C�v	( = MPT_CIR )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	Pc;							// ���S�_���W�l	( x, y, z )
	MgVect3		V;							// �@���P�ʃx�N�g��	( x, y, z )
	MREAL		R;							// ���a
}	MgeCircle2;

//
// �~��	(�Q����)
//
typedef struct	_mgearc2	{
	MSHORT		Type;						// �^�C�v	( = MPT_ARC )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	pt[2];						// �n�_�A�I�_�l	( x, y )
	MgPoint2	pc;							// ���S�_���W�l	( x, y )
	MREAL		r;							// ���a
}	MgeArc2;

//
// �~��	(�R����)
//
typedef struct	_mgearc3	{
	MSHORT		Type;						// �^�C�v	( = MPT_ARC )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	Pt[2];						// �n�_�A�I�_�l	( x, y, z )
	MgPoint3	Pc;							// ���S�_���W�l	( x, y, z )
	MgVect3		V;							// �@���P�ʃx�N�g��	( x, y, z )
	MREAL		r;							// ���a
}	MgeArc3;

//
// �ȉ~	(�Q����)
//
typedef struct	_mgeeps2	{
	MSHORT		Type;						// �^�C�v	( = MPT_EPS )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	pc;							// ���S�_���W�l	( x, y )
	MgPoint2	pf;							// �œ_���W�l		( x, y )
	MREAL		rl;							// ���a
}	MgeEps2;

//
// �ȉ~	(�R����)
//
typedef struct	_mgeeps3	{
	MSHORT		Type;						// �^�C�v	( = MPT_EPS )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	Pc;							// ���S�_���W�l	( x, y, z )
	MgPoint3	Pf;							// �œ_���W�l		( x, y, z )
	MgVect3		V;							// �@���P�ʃx�N�g��	( x, y, z )
	MREAL		rl;							// ���a
}	MgeEps3;

//
// �ȉ~��	(�Q����)
//
typedef struct	_mgeeps2	{
	MSHORT		Type;						// �^�C�v	( = MPT_EPS )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint2	pt[2];						// �n�_�A�I�_�l	( x, y )
	MgPoint2	pc;							// ���S�_���W�l	( x, y )
	MgPoint2	pf;							// �œ_���W�l		( x, y )
	MREAL		rl;							// ���a
}	MgeEps2;

//
// �ȉ~��	(�R����)
//
typedef struct	_mgeeps3	{
	MSHORT		Type;						// �^�C�v	( = MPT_EPS )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	Pt[2];						// �n�_�A�I�_�l	( x, y, z )
	MgPoint3	Pc;							// ���S�_���W�l	( x, y, z )
	MgPoint3	Pf;							// �œ_���W�l		( x, y, z )
	MgVect3		V;							// �@���P�ʃx�N�g��	( x, y, z )
	MREAL		rl;							// ���a
}	MgeEps3;

//
// ����	( ax + by + cz + d = 0 )
//
typedef struct	_mgepln3	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgVect3		V;							// �@���x�N�g��	( a, b, c )
	MREAL		d;							// d = - (���S���畽�ʂ܂ł̕��ʕ\�����̋���)
}	MgePln3;

//
// ����	( ax + by + cz + d = 0 )
//
typedef struct	_mgeplna3	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLNA )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgPoint3	P;							// ���S�_���W�l	( x, y, z )
	MREAL		d;							// - (���S���畽�ʂ܂ł̕��ʕ\�����̋���)
	MgePrm3		Prm;						// �}�`�v�f
}	MgePlna3;

//
// �����Ȑ� (�J)	(�Q����)
//
typedef struct	_mgecmpo2	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm2		prm;						// �}�`�v�f
}	MgeCmpo2

//
// �����Ȑ� (�J)	 (�R����)
//
typedef struct	_mgecmpo3	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm3		Prm;						// �}�`�v�f
}	MgeCmpo3

//
// �����Ȑ� (��)	(�Q����)
//
typedef struct	_mgecmpc2	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm2		prm;						// �}�`�v�f
}	MgeCmpc2

//
// �����Ȑ� (��)	 (�R����)
//
typedef struct	_mgecmpc3	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm3		Prm;						// �}�`�v�f
}	MgeCmpc3

//
// ����	(�Q����)
//
	typedef struct	_mgemanys2	{			// (many sides)
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm3		prm;						// �}�`�v�f
}	MgeManys2

//
// ����	 (�R����)
//
typedef struct	_mgemanys3	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm3		Prm;						// �}�`�v�f
}	MgeManys3

//
// ���ʑ�	 (�R����)
//
typedef struct	_mgepolyh	{				// (polyhedron)
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm3		Prm;						// �}�`�v�f
}	MgePolyh3

//
// �W��	(�Q����)
//
typedef struct	_mgeset2	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm3		prm;						// �}�`�v�f
}	MgeSet2

//
// �W��	 (�R����)
//
typedef struct	_mgeset3	{
	MSHORT		Type;						// �^�C�v	( = MPT_PLN )
	MSHORT		Size;						// �T�C�Y	( byte )
	MgePrm3		Prm;						// �}�`�v�f
}	MgeSet3

