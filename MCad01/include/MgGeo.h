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
#include "MgMatE.h"

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

namespace MC
{

class DLL_EXPORT_GEO MGeo
{
public:
	//======================( �P���� )==============================
	//
	// �����̐�Βl
	static MREAL Abs(MREAL x)
						{return ((x > 0) ? x : -x);}
	// �����̐�Βl
	static MINT Abs(MINT x)
						{return ((x > 0) ? x : -x);}
	// �����̃[������ (�덷�w���)
	static bool Zero(MREAL x, MREAL tol = MGPTOL->D)
						{return (x < tol && x > -tol);}
	// �����̓������� (�덷�w���)
	static bool Equal(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x - y < tol && y - x < tol);}
	// �����̓������� (�덷�w���)
	static bool EQ(MREAL x, MREAL y, MREAL tol = MGPTOL->D)							// MgEqual�Ɠ���
						{return (x - y < tol && y - x < tol);}
	// �����̖������� (�덷�w���)
	static bool LT(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x < y - tol);}
	// �����̖��ȉ����� (�덷�w���)
	static bool LE(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x <= y + tol);}
	// �����̒����� (�덷�w���)
	static bool GT(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x > y + tol);}
	// �����̈ȏ㔻�� (�덷�w���)
	static bool GE(MREAL x, MREAL y, MREAL tol = MGPTOL->D)
						{return (x >= y - tol);}

	//======================( �Q���� )==============================
	// MgVect2D, MgPoint2D

	// �x�N�g���̒����̂Q��	Abs**2
	static MREAL SqLenVect2D( const MgVect2D& v)
				 		{ return ( v * v);}
	// �x�N�g���̒���		ABS
	static MREAL LenVect2D( const MgVect2D& v)
				 		{ return (MREAL)sqrt( v * v);}
	// �Q�_�Ԃ̋����̂Q�� MgDist**2
	static MREAL SqDist2Point2D( const MgPoint2D& P1, const MgPoint2D& P2)
						{ MgVect2D v = P2 - P1;
						  return ( v * v);}
	// �Q�_�Ԃ̋���
	static MREAL Dist2Point2D( const MgPoint2D& P1, const MgPoint2D& P2)
						{ MgVect2D v = P2 - P1;
						  return (MREAL)sqrt( v * v);}
	// P1 == (0.,0.)	����
	static bool ZeroVect2D( const MgVect2D& v1)
						{ return SqLenVect2D( v1) <= MGPTOL->D_2;}
	// P1 == (0.,0.)	�덷�w��̔���
	static bool ZeroVect2D( const MgVect2D& v1, MREAL tol)
						{ return SqLenVect2D( v1) <= tol * tol;}
	// P1 == P2 		����
	static bool EqualPoint2D( const MgPoint2D& p1, const MgPoint2D& p2)
				 		{ MgVect2D pt = p2 - p1; return SqLenVect2D( pt) <= MGPTOL->D_2;}
	// P1 == P2			�덷�w��̔���
	static bool EqualPoint2D( const MgPoint2D& p1, const MgPoint2D& p2, MREAL tol)
				 		{ MgVect2D vt = p2 - p1; return SqLenVect2D( vt) <= tol * tol;}
	// V1 == V2 		�P�ʃx�N�g���^���̓�������
	static bool EqualVect2D( const MgVect2D& v1, const MgVect2D& v2)
				 		{ MgVect2D vt = v2 - v1; return SqLenVect2D( vt) <= MGPTOL->U_2;}
	// V1 == V2			�덷�w��̔���
	static bool EqualVect2D( const MgVect2D& v1, const MgVect2D& v2, MREAL tol)
				 		{ MgVect2D vt = v2 - v1; return SqLenVect2D( vt) <= tol * tol;}
	// V1��V2�����s�ł��邩���m�F
	static bool ParallelVect2D( const MgVect2D& v1, const MgVect2D& v2)
				 		{ MREAL ro = v1 ^ v2; MREAL ri = v1 * v2;
						  if( ro < 0) ro = - ro; if(ri < 0) ri = -ri;
						  return (ro <= ri * MGPTOL->A);}
	// V1��V2�����s�ł��邩���m�F���A�O�ςƓ��ς��o��
	static bool ParallelVect2DWS( const MgVect2D& v1, const MgVect2D& v2, MREAL* so, MREAL* si)
				 		{ MREAL ro = v1 ^ v2; MREAL ri = v1 * v2;
				 		  *so = ro; *si = ri;
						  if (ro < 0) ro = - ro; if (ri < 0) ri = -ri;
						  return (ro <= ri * MGPTOL->A);}
	// ss = ����(p1,v1)����_ps�ւ̐������� �� se = ����(p1,v1)����_pe�ւ̐������������߂�
	// ����(p1,v1)�Ɛ���(ps, pe)�̌�_�����߂�̂Ɏg�p
	static void SVal( const MgPoint2D& ps, const MgPoint2D& pe, const MgPoint2D& p1, const MgVect2D& v1,
						MREAL* ss, MREAL* se)
						{ *ss = (v1 ^ (ps - p1));									// ����2�̎n�_��S
						  *se = (v1 ^ (pe - p1));}									// ����2�̏I�_��S
	// �����P�ɐ��K������
	static MgVect2D UnitizeVect2D( const MgVect2D& v1, MREAL i_Tol = MGPTOL->D	);

	// ��90�K��]
	static MgVect2D RotL90Vect2D( const MgVect2D& v1)
						{ return	MgVect2D( -v1.y, v1.x);}
	// 180�K��]
	static MgVect2D Rot180Vect2D( const MgVect2D& v1)
						{ return	MgVect2D( -v1.x, -v1.y);}
	// �E90�K��]
	static MgVect2D RotR90Vect2D( const MgVect2D& v1)
						{ return	MgVect2D( v1.y, -v1.x);}

	// �_��̓�����W���߂�
	static int PackSamePoint2D( MgPoint2D* io_pPt, int* io_pn);
	static int PackSamePoint2D( MREAL* io_pPt, int* o_pn)
						{ return PackSamePoint2D( (MgPoint2D*)io_pPt, o_pn);}
	// �_����t���ɂ���
	static int ReversePoint2D( MgPoint2D* i_pPt, int i_n, MgPoint2D* o__pPt);
	static int ReversePoint2D( MREAL* i_pPt, int i_n, MREAL* o__pPt)
						{ return ReversePoint2D( (MgPoint2D*)i_pPt, i_n, (MgPoint2D*)o__pPt);}

	// �_�񂩂璼���ɑΏۈʒu�̓_������߂�
	static int SymmetryPointULine2D( MgPoint2D* i_pPt, int i_n, MgULine2D& uln, MgPoint2D* o_pPt);

	//======================( �R���� )==============================
	// MgVect3D, MgPoint3D

	// �x�N�g���̒����̂Q��	MgAbs**2
	static MREAL SqLenVect3D( const MgVect3D& v)
				 		{ return v * v;}
	// �x�N�g���̒���		MGABS
	static MREAL LenVect3D( const MgVect3D& v)
				 		{ return (MREAL)sqrt( v * v);}
	// �Q�_�Ԃ̋����̂Q�� MgDist**2
	static MREAL SqDist2Point3D( const MgPoint3D& P1, const MgPoint3D& P2)
						{ MgVect3D v = P2 - P1;
						  return ( v * v);}
	// �Q�_�Ԃ̋���
	static MREAL Dist2Point3D( const MgPoint3D& P1, const MgPoint3D& P2)
						{ MgVect3D v = P2 - P1;
						  return (MREAL)sqrt( v * v);}
	// P1 == (0.,0.,0.)	����
	static bool ZeroVect3D( const MgVect3D& v1)
						{ return SqLenVect3D(v1) <= MGPTOL->D_2;}
	// P1 == (0.,0.,0.)	�덷�w��̔���
	static bool ZeroVect3D( const MgVect3D& v1, MREAL tol)
						{ return SqLenVect3D(v1) <= tol * tol;}
	// P1 == P2 		����== ����
	static bool EqualVect3D( const MgVect3D& v1, const MgVect3D& v2)
				 		{ MgVect3D vt = v2 - v1; return SqLenVect3D(vt) <= MGPTOL->D_2;}  
	// V1 == V2 		�x�N�g���^���̊p�x�̓�������
	static bool EqualUVect3D( const MgVect3D& v1, const MgVect3D& v2)
				 		{ MgVect3D vt = v2 - v1; return SqLenVect3D(vt) <= MGPTOL->U_2;}  
	// P1 == P2			�덷�w��̔���== ����
	static bool EqualVect3D( const MgVect3D& v1, const MgVect3D& v2, MREAL tol)
				 		{ MgVect3D vt = v2 - v1; return SqLenVect3D(vt) <= tol * tol;}  
	// V1��V2�����s�ł��邩���m�F
	static bool ParallelVect3D( const MgVect3D& v1, const MgVect3D& v2)
				 		{ MgVect3D vo = v1 ^ v2; MREAL fi = v1 * v2;
						  return ( SqLenVect3D(vo) <= fi * fi * MGPTOL->A_2);}
	// V1��V2�����s�ł��邩���m�F���A�O�ςƓ��ς��o��
	static bool ParallelVect3DWP( const MgVect3D& v1, const MgVect3D& v2, MgVect3D *pso, MREAL* si)
				 		{ MgVect3D vo = v1 ^ v2; MREAL fi = v1 * v2;
				 		  *pso = vo; *si = fi;
						  return ( SqLenVect3D(vo) <= fi * fi * MGPTOL->A_2);}
	// �P�ʃx�N�g�������߂�
	static MgVect3D UnitizeVect3D( const MgVect3D& V1, MREAL i_Tol = MGPTOL->D);

	// 
	static MgVect3D TaniVect3D( const MgVect3D& V1, MREAL i_Tol = MGPTOL->D);

	// ��90�K��]�����x�N�g�������߂�
	static MgVect3D RotL90Vect3D( const MgVect3D& v1)
						{ return	MgVect3D( -v1.y, v1.x, v1.z);}
	// 180�K��]�����x�N�g�������߂�
	static MgVect3D Rot180Vect3D( const MgVect3D& v1)
						{ return	MgVect3D( -v1.x, -v1.y, v1.z);}
	// �E90�K��]�����x�N�g�������߂�
	static MgVect3D RotR90Vect3D( const MgVect3D& v1)
						{ return	MgVect3D( v1.y, -v1.x, v1.z);}
	// �_��̓�����W���߂�
	static int PackSamePoint3D( MgPoint3D* io_pPt, int* io_pn);

	static int PackSamePoint3D( MREAL* io_pPt, int* io_pn)
						{ return PackSamePoint3D( (MgPoint3D*)io_pPt, io_pn);}

	// �_����t���ɂ���
	static int ReversePoint3D( MgPoint3D* i_pPt, int i_n, MgPoint3D* o__pPt);
	static int ReversePoint3D( MREAL* i_pPt, int i_n, MREAL* o__pPt)
						{ return ReversePoint3D( (MgPoint3D*)i_pPt, i_n, (MgPoint3D*)o__pPt);}

	// �_�񂩂璼���ɑΏۈʒu�̓_������߂�
	static int SymmetryPointULine3D( MgPoint3D* i_pPt, int i_n, MgULine3D& uln, MgPoint3D* o_pPt);

#ifdef _MgPoint3DA
	//
	//======================( �Q���� )==============================
	//static MgVect2D MgUnitizeVect2D( const MgVect2D& v, MREAL i_Tol = MGPTOL->D);		//	(  O) �P�ʃx�N�g��
	static MgPoint2Da Norma( const MgPoint2D& p);
#endif
	
#ifdef _MgPoint3DA
	//
	//======================( �R���� )==============================
	//		�x�N�g���̒P�ʃx�N�g�������߂�
	//
	//static MgVect3D MgUnitizeVect3D( const MgVect3D& v, MREAL i_Tol = MGPTOL->D);		//	(  O) �P�ʃx�N�g��
	static MgPoint3Da Norma( const MgPoint3D& p);
#endif
	
	// ---------------------( �Q���� )------------------------------
	//
	//	�Q��������
	//
	// �������]
	static MgULine2D RevULine2D( const MgULine2D& ULn1)
						{ return MgULine2DC( ULn1.p, - ULn1.v);}
	//	�Q��������
	//
	// ���� ���]
	static MgLine2D RevLine2D( const MgLine2D& Ln1)
						{ return MgLine2D( Ln1.p[1], Ln1.p[0]);}

	// Line1��Line2�����s�ł��邩���m�F
	static bool ParallelLine2D( const MgLine2D& Ln1, const MgLine2D& Ln2)
				 		{ MgVect2D v1 = MgVect2DC(Ln1); MgVect2D v2 = MgVect2DC(Ln2);
						  return ParallelVect2D( v1, v2);}
	// Line1��Line2�����s�ł��邩���m�F���A�O�ςƓ��ς��o��
	static bool ParallelLine2D( const MgLine2D& Ln1, const MgLine2D& Ln2, MREAL* so, MREAL* si)
				 		{ MgVect2D v1 = MgVect2DC(Ln1); MgVect2D v2 = MgVect2DC(Ln2);
						  return ParallelVect2DWS( v1, v2, so, si);}

	// ---------------------( �R���� )------------------------------
	//
	//	�R��������
	//
	// �������]
	static MgULine3D RevLine3D( const MgULine3D& ULn1)
						{ return MgULine3D(ULn1.p, - ULn1.v);}

	// ���� ���]
	static MgLine3D RevLine3D( const MgLine3D& Ln1)
						{ return MgLine3D( Ln1.p[1], Ln1.p[0]);}

	// Line1��Line2�����s�ł��邩���m�F
	static bool ParallelLine3D( const MgLine3D& Ln1, const MgLine3D& Ln2)
				 		{ MgVect3D v1 = MgVect3DC(Ln1); MgVect3D v2 = MgVect3DC(Ln2);
						  return ParallelVect3D( v1, v2);}
	// Line1��Line2�����s�ł��邩���m�F���A�O�ςƓ��ς��o��
	static bool ParallelLine3D( const MgLine3D& Ln1, const MgLine3D& Ln2, MgVect3D *pso, MREAL* si)
				 		{ MgVect3D v1 = MgVect3DC(Ln1); MgVect3D v2 = MgVect3DC(Ln2);
						  return ParallelVect3DWP( v1, v2, pso, si);}

	// ---------------------( �Q���� )------------------------------
	//
	//	�Q�����~��
	//
	// arc1��arc2�����s�ł��邩���m�F
	static bool ParallelArc2D( const MgArc2D& arc1, const MgArc2D& arc2)
				 		{ return ( arc1.pc == arc2.pc);}

	// �~�ʂ�n��������
	static MINT Arc2Divide( const MgArc2D& arc1, MINT n, const MgGPoint2D *gpto);

	// ---------------------( �R���� )------------------------------
	//
	//	�R�����~��
	//
	// Arc1��Arc2�����s�ł��邩���m�F
	static bool ParallelArc3D( const MgArc3D& Arc1, const MgArc3D& Arc2)
				 		{ return ( Arc1.Pc == Arc2.Pc) &&
								   ParallelVect3D( Arc1.V, Arc2.V);}

	// �~�ʂ�n��������
	static MINT Arc3Divide( const MgArc3D& arc1, MINT n, const MgGPoint3D *gPto);

	// ---------------------( �Q���� )------------------------------
	//
	//	�Q�����~
	//
	static bool ParallelCir2D( const MgCir2D& cir1, const MgCir2D& cir2)
		// cir1��cir2�����s�ł��邩���m�F
				 		{ return ( cir1.pc == cir2.pc);}

	// ---------------------( �R���� )------------------------------
	//
	//	�R�����~
	//
	static bool ParallelCir3D( const MgCir3D& Cir1, const MgCir3D& Cir2)
		// Cir1��Cir2�����s�ł��邩���m�F
				 		{ return ( Cir1.Pc == Cir2.Pc) &&
								   ParallelVect3D( Cir1.V, Cir2.V);}

	/////////////////////////////////////////////////////////////////////////////
	//		�����@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	
	/////////////////////////////////////////////////////////////////////////////
	//	������(X����)����x�N�g���܂ł̊p�x(���W�A��)�����߂�
	//
	static MREAL AngleXVect2D(						// (  O) ����]�p�x�@�i���W�A���j
													//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgVect2D&	i_v1		// (I  ) �x�N�g��
			);

	/////////////////////////////////////////////////////////////////////////////
	//	������(Y����)����x�N�g���܂ł̊p�x(���W�A��)�����߂�
	//
	static MREAL AngleYVect2D(						// (  O) ����]�p�x�@�i���W�A���j
													//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgVect2D&	i_v1		// (I  ) �x�N�g��
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�Q�x�N�g���̊p�x�����߂�
	//
	static MREAL Angle2Vect2D(						// (  O) ����]�p�x�@�i���W�A���j
													//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgVect2D&	i_v1,		// (I  ) �x�N�g��1
					const	MgVect2D&	i_v2		// (I  ) �x�N�g��2
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�R�_�ō����Q�����̊p�x�����߂�
	//
	static MREAL Angle3Point2D(						// (  O) ����]�p�x�@�i���W�A���j
													//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgPoint2D&	i_p2,		// (I  ) �_2
					const	MgPoint2D&	i_p3		// (I  ) �_3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�Q�x�N�g���̊p�x�����߂�
	//
	static MREAL Angle2Vect3D(						// (  O) ����]�p�x�@�i���W�A���j
													//		�x�N�g���̒�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgVect3D&	i_v1,		// (I  ) �x�N�g��1
					const	MgVect3D&	i_v2,		// (I  ) �x�N�g��2
					const	MgVect3D&	i_vn		// (I  ) �Q�x�N�g���ɒ�������P�ʃx�N�g��
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�R�_�ō����Q�����̊p�x�����߂�
	//
	static MREAL Angle3Point3D(						// (  O) ����]�p�x�@�i���W�A���j
													//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgPoint3D&	i_p2,		// (I  ) �_2
					const	MgPoint3D&	i_p3,		// (I  ) �_3
					const	MgVect3D&	i_vn		// (I  ) �_1,�_,2�_3��ʂ镽�ʂɒ�������P�ʃx�N�g��
			);

	/////////////////////////////////////////////////////////////////////////////
	//		�����@���ʁ@�`�󉉎Z
	//
	// ---------------------( �R���� )------------------------------
	
	/////////////////////////////////////////////////////////////////////////////
	//	�x�N�g���ƕ��ʂ̊p�x�����߂�
	//
	static MREAL AngleVectPln3D(					// (  O) ����]�p�x�@�i���W�A���j
													//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgVect3D&	i_v1,		// (I  ) �x�N�g��1
					const	MgPlane3D&	i_Pln2		// (I  ) ����2
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�x�N�g����XY���ʂ̊p�x�����߂�
	//
	static MREAL AngleVectXYPln3D(					// (  O) �p�x�@�i���W�A���j Z��������
													//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgVect3D&	i_v1		// (I  ) �x�N�g��1
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�x�N�g����YZ���ʂ̊p�x�����߂�
	//
	static MREAL AngleVectYZPln3D(					// (  O) �p�x�@�i���W�A���j X��������
													//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgVect3D&	i_v1		// (I  ) �x�N�g��1
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�x�N�g����ZX���ʂ̊p�x�����߂�
	//
	static MREAL AngleVectZXPln3D(					// (  O) �p�x�@�i���W�A���j Y��������
													//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
					const	MgVect3D&	i_v1		// (I  ) �x�N�g��1
			);

//S	/////////////////////////////////////////////////////////////////////////////
//	//	�����ƕ��ʂ̊p�x�����߂�
//	//
//	static MREAL AngleULinePln3D(					// (  O) ����]�p�x�@�i���W�A���j
//													//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
//					const	MgULine3D&	i_ULn1,		// (I  ) ����1
//					const	MgPlane3D&	i_Pln2		// (I  ) ����2
//			);
//
//	/////////////////////////////////////////////////////////////////////////////
//	//	�����ƕ��ʂ̊p�x�����߂�
//	//
//	static MREAL AngleLinePln3D(					// (  O) ����]�p�x�@�i���W�A���j
//													//		2�_�Ԃ̋�����MGPTOL->D�����̏ꍇ��0�x��Ԃ�
//					const	MgLine3D&	i_Ln1,		// (I  ) ����1
//					const	MgPlane3D&	i_Pln2		// (I  ) ����2
//			);

	/////////////////////////////////////////////////////////////////////////////
	//		�����@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	//
	//	�Q�����Ԃ̊p��2�����������߂�
	//
	static void Bisector2ULine2D(					// (  O) �X�e�[�^�X
					const	MgULine2D&	i_ULn1,		// (I  ) ����1
					const	MgULine2D&	i_ULn2,		// (I  ) ����2
							MgULine2D*	o_pULn3		// (  O) ����3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�����Ɛ����Ԃ̊p��2�����������߂�
	//
	static void BisectorULineLine2D(				// (  O) �X�e�[�^�X
					const	MgULine2D&	i_ULn1,		// (I  ) ����1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MgULine2D*	o_pULn3		// (  O) ����3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�����ƒ����Ԃ̊p��2�����������߂�
	//
	static void BisectorLineULine2D(				// (  O) �X�e�[�^�X
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgULine2D&	i_ULn2,		// (I  ) ����2
							MgULine2D*	o_pULn3		// (  O) ����3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�����Ɛ����Ԃ̊p��2�����������߂�
	//
	static void Bisector2Line2D(					// (  O) �X�e�[�^�X
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MgULine2D*	o_pULn3		// (  O) ����3
			);

	/////////////////////////////////////////////////////////////////////////////
	//
	// ---------------------( �R���� )------------------------------
	//
	//	�Q�����Ԃ̊p��2�����������߂�
	//
	static void Bisector2ULine3D(					// (  O) �X�e�[�^�X
					const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgULine3D&	i_ULn2,		// (I  ) ����2
							MgULine3D*	o_pULn3		// (  O) ����3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�����Ɛ����Ԃ̊p��2�����������߂�
	//
	static void BisectorULineLine3D(				// (  O) �X�e�[�^�X
					const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
							MgULine3D*	o_pULn3		// (  O) ����3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�����ƒ����Ԃ̊p��2�����������߂�
	//
	static void BisectorLineULine3D(				//
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgULine3D&	i_ULn2,		// (I  ) ����2
							MgULine3D*	o_pULn3		// (  O) ����3
			);

	/////////////////////////////////////////////////////////////////////////////
	//	�����Ɛ����Ԃ̊p��2�����������߂�
	//
	static void Bisector2Line3D(					//
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
							MgULine3D*	o_pULn3		// (  O) ����3
			);

	//======================( �Q�����A�R���� )==============================
	//	�Q�����A�R�������W�ϊ��}�g���b�N�X
	
	//======================( �Q���� )==============================
	//		���_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat2E Mat2ERot( MREAL rd)
	{
		return Mat2ERotV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �Q���� )==============================
	//		���_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat2E Mat2ERotRev( MREAL rd)
	{
		return Mat2ERotRevV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�w�x���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotZ( MREAL rd)
	{
		return Mat3ERotZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�w�x���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotRevZ( MREAL rd)
	{
		return Mat3ERotRevZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�x�y���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotTX( MREAL rd)
	{
		return  Mat3ERotTXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�x�y���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotRevX( MREAL rd)
	{
		return Mat3ERotRevXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�y�w���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotY( MREAL rd)
	{
		return Mat3ERotYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�y�w���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERotRevY( MREAL rd)
	{
		return Mat3ERotRevYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�̉��Z
	//
	//	�g�p�@
	//		MgMat2E3 = MgMat2E1 + MgMat2E2;
	//
	//	| m11 m12 0 |     | n11 n12 0 |
	//	| m21 m22 0 |  +  | n21 n22 0 |
	//	| m31 m32 1 |     | n31 n32 1 |
	//
	static MgMat2E Mat2EPlus( const MgMat2E& i_mt1, const MgMat2E& i_mt2);

	//
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
	static MgMat2E Mat2EPlusEqual( MgMat2E& io_mt1, const MgMat2E& i_mt2);

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
	static MgMat2E Mat2ESingleMinus( const MgMat2E& m1);

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
	static MgMat2E Mat2EMinusSingle( const MgMat2E& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̈��Z
	//
	//	�g�p�@
	//		MgMat3E = MgMat2E1 - MgMat2E2;
	//
	//	  | m11 m12 0 |     | n11 n12 0 |
	//	  | m21 m22 0 |  -  | n21 n22 0 |
	//	  | m31 m32 1 |     | n31 n32 1 |
	//
	static MgMat2E Mat2EMinus( const MgMat2E& i_mt1, const MgMat2E& i_mt2);

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
	static MgMat2E Mat2EMinusEqual( MgMat2E& io_mt1, const MgMat2E& i_mt2);

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
	static MgMat2E Mat2EMult( const MgMat2E& i_mt1, const MgMat2E& i_mt2);

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
	static MgMat2E Mat2EMultEqual( MgMat2E& io_mt1, const MgMat2E& i_mt2);
//==
	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�̕��s�ړ�
	//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����Ɉړ�����}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat2E = MgMat2E1 * MgPoint2D1;
	//
	//	| m11 m12 0 |     | m11 m12 0 |     |  1  0  0 |
	//	| m21 m22 0 |  =  | m21 m22 0 |  X  |  0  1  0 |
	//	| m31 m32 1 |     | m31 m32 1 |     |  vx vy 1 |
	//
//E	inline	MgMat2E operator + ( const MgMat2E& i_m1, const MgVect2D& i_v)			// +	���s�ړ�
	static	MgMat2E Mat2EMoveVect2D( const MgMat2E& i_m1, const MgVect2D& i_v)		// +	���s�ړ�
	{
		MgMat2E mw;
		mw = i_m1;
		mw += i_v;
		return mw;
	}
//==
	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint2Dpo = MgPoint2Dp * MgMat2Etm;
	//
	//					   | m11 m12 0 |
	//	| px  py  1  |  X  | m21 m22 0 |
	//					   | m31 m32 1 |     
	//
	static MgPoint2D Mat2EMultPoint2D( const MgPoint2D& i_pt, const MgMat2E& i_mt);

	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect2Dvo = MgVect2Dv * MgMat2Etm;
	//
	//					   | m11 m12 0 |
	//	| vx  vy  0  |  X  | m21 m22 0 |
	//					   | m31 m32 1 |     
	//
	static MgVect2D Mat2EMultVect2D( const MgVect2D& i_pt, const MgMat2E& i_mt);

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
//	inline	MgLine2D operator * ( const MgLine2D& i_ln, const MgMat2E& i_mt)		// *	���W�ϊ�
	static MgLine2D Mat2EMultLine2D( const MgLine2D& i_ln, const MgMat2E& i_mt)
	{ 
		MgLine2D ln;
		ln.p[0] = i_ln.p[0] * i_mt;
		ln.p[1] = i_ln.p[1] * i_mt;
		return ln;
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
//	inline	MgULine2D operator * ( const MgULine2D& i_uln, const MgMat2E& i_mt)		// *	���W�ϊ�
	static MgULine2D Mat2EMultULine2D( const MgULine2D& i_uln, const MgMat2E& i_mt)
	{ 
		MgULine2D uln;
		uln.p = i_uln.p * i_mt;
		uln.v = i_uln.v * i_mt;
		return i_uln;
	}

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint2Dp *= MgMat2Em;
	//
	//										  | m11 m12 0 |
	//	| px  py  0  |  =  | px  py  0  |  X  | m21 m22 0 |
	//				   						  | m31 m32 1 |
	//
	static MgPoint2D Mat2EMultEqualPoint2D( MgPoint2D& io_pt, const MgMat2E& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint2Dp *= MgMat2Em;
	//
	//										  | m11 m12 0 |
	//	| vx  vy  0  |  =  | vx  vy  0  |  X  | m21 m22 0 |
	//				   						  | m31 m32 1 |
	//
	static MgVect2D Mat2EMultEqualVect2D( MgVect2D& io_pt, const MgMat2E& i_mt);

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
//S	inline	MgLine2D operator *= ( MgLine2D& io_ln, const MgMat2E& i_mt)				// *=	���W�ϊ�
	static MgLine2D Mat2EMultEqualLine2D( MgLine2D& io_ln, const MgMat2E& i_mt)
	{ 
		io_ln.p[0] *= i_mt;
		io_ln.p[1] *= i_mt;
		return io_ln;
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
//S	inline	MgULine2D operator *= ( MgULine2D& i_uln, const MgMat2E& i_mt)			// *=	���W�ϊ�
	static MgULine2D Mat2EMultEqualULine2D( MgULine2D& io_uln, const MgMat2E& i_mt)
	{ 
		io_uln.p *= i_mt;
		io_uln.v *= i_mt;
		return io_uln;
	}

	//===============( �Q�������W�ϊ��}�g���b�N�X�łR�������W���� )==============

	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint3D2 = MgPoint3D1 * MgMat2E1;
	//
	//						  | m11 m12 0 0 |     
	//	| px  py  pz  1 |  X  | m21 m22 0 0 |
	//						  |  0   0  1 0 |
	//						  | m31 m32 0 1 |
	//
	static MgPoint3D Mat2EMultPoint3D( const MgPoint3D& i_Pt, const MgMat2E& i_mt);

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
	static MgVect3D Mat2EMultVect3D( const MgVect3D& i_Pt, const MgMat2E& i_mt);

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
//S	inline	MgLine3D operator * ( const MgLine3D& i_Ln, const MgMat2E& i_mt)		// *	���W�ϊ�
	static MgLine3D Mat2EMultLine3D( const MgLine3D& i_Ln, const MgMat2E& i_mt)
	{
		MgLine3D Ln;
		Ln.p[0] = i_Ln.p[0] * i_mt;
		Ln.p[1] = i_Ln.p[1] * i_mt;
		return Ln;
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
//S	inline	MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat2E& i_mt)		// *	���W�ϊ�
	static MgULine3D Mat2EMultULine3D( const MgULine3D& i_ULn, const MgMat2E& i_mt)
	{
		MgULine3D ULn;
		ULn.p = i_ULn.p * i_mt;
		ULn.v = i_ULn.v * i_mt;
		return ULn;
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
	static MgPoint3D Mat2EMultEqualPoint3D( MgPoint3D& io_Pt, const MgMat2E& i_mt);

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
	static MgVect3D Mat2EMultEqualVect3D( MgVect3D& io_Pt, const MgMat2E& i_mt);

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
//S	inline	MgLine3D operator *= ( MgLine3D& io_Ln, const MgMat2E& i_mt)			// *=	���W�ϊ�
	static MgLine3D Mat2EMultLine3D( MgLine3D& io_Ln, const MgMat2E& i_mt)
	{
		io_Ln.p[0] *= i_mt;
		io_Ln.p[1] *= i_mt;
		return io_Ln;
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
//S	inline	MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat2E& i_mt)			// *=	���W�ϊ�
	static MgULine3D Mat2EMultEqualLine3D( MgULine3D& io_ULn, const MgMat2E& i_mt)
	{ 
		io_ULn.p *= i_mt;
		io_ULn.v *= i_mt;
		return io_ULn;
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
	//	| m11 m12 m13 0 |     | m11 m12 m13 0 |
	//	| m21 m22 m23 0 |  +  | m21 m22 m23 0 |
	//	| m31 m32 m33 0 |     | m31 m32 m33 0 |
	//	| m41 m42 m43 1 |     | m41 m42 m43 1 |    
	//
	static MgMat3E Mat3EPlus( const MgMat3E& i_Mt1, const MgMat3E& i_Mt2);

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
	static MgMat3E Mat3EPlusEqual( MgMat3E& io_Mt1, const MgMat3E& i_Mt2);

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
	static MgMat3E Mat3ESingleMinus( const MgMat3E& i_Mt);

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
	static MgMat3E Mat3EMinus( const MgMat3E& i_Mt1, const MgMat3E& i_Mt2);

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
	static MgMat3E Mat3EMinusEqual( MgMat3E& io_Mt1, const MgMat3E& i_Mt2);

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
	static MgMat3E Mat3EMult( const MgMat3E& i_Mt1, const MgMat3E& i_Mt2);

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
	static MgMat3E Mat3EMultEqual( MgMat3E& io_Mt1, const MgMat3E& i_Mt2);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgMat3E_2 = MgPoint2D * MgMat3E_1;
	//
	//						    | m11 m12 m13 0 |
	//	| px  py  0   1   |  X  | m21 m22 m23 0 |
	//						    | m31 m32 m33 0 |
	//						    | m41 m42 m43 1 |
	//
	static MgPoint2D Mat3EMultPoint2D( const MgPoint2D& i_Pt, const MgMat3E& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgMat3E_2 = MgVect2D * MgMat3E_1;
	//
	//						    | m11 m12 m13 0 |
	//	| vx  vy  0   0   |  X  | m21 m22 m23 0 |
	//						    | m31 m32 m33 0 |
	//						    | m41 m42 m43 1 |
	//
	static MgVect2D Mat3EMultVect2D( const MgVect2D& i_Pt, const MgMat3E& i_Mt);

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
//S	inline MgLine2D operator * ( const MgLine2D& i_ln, const MgMat3E &i_Mt)			// ���W�ϊ�
	static MgLine2D	Mat3EMultLine2D( const MgLine2D& i_ln, const MgMat3E& i_Mt)
	{
		MgLine2D ln;
		ln.p[0] = i_ln.p[0] * i_Mt;
		ln.p[1] = i_ln.p[1] * i_Mt;
		return ln;
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
//S	inline MgULine2D operator * ( const MgULine2D& i_uln, const MgMat3E& i_Mt)		// ���W�ϊ�
	static MgULine2D Mat3EMultULine2D( const MgULine2D& i_uln, const MgMat3E& i_Mt)
	{
		MgULine2D uln;
		uln.p = i_uln.p * i_Mt;
		uln.v = i_uln.v * i_Mt;
		return uln;
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
	static MgPoint2D Mat3EMultEqualPoint2D( MgPoint2D& io_Pt, const MgMat3E& i_Mt);

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
	static MgVect2D Mat3EMultEqualVect2D( MgVect2D& io_Pt, const MgMat3E& i_Mt);

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
//S	inline MgLine2D operator *= ( MgLine2D& io_ln, const MgMat3E &i_Mt)					// ���W�ϊ�
	static MgLine2D Mat3EMultEqualLine2D( MgLine2D& io_ln, const MgMat3E& i_Mt)
	{
		io_ln.p[0] *= i_Mt;
		io_ln.p[1] *= i_Mt;
		return io_ln;
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
//S	inline MgULine2D operator *= ( MgULine2D& io_uln, const MgMat3E& i_Mt)				// ���W�ϊ�
	static MgULine2D MGeo::Mat3EMultEqualULine2D( MgULine2D& io_uln, const MgMat3E& i_Mt)
	{
		io_uln.p *= i_Mt;
		io_uln.v *= i_Mt;
		return io_uln;
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
	static MgPoint3D Mat3EMultPoint3D( const MgPoint3D& i_Pt, const MgMat3E& i_Mt);

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
	static MgVect3D Mat3EMultVect3D( const MgVect3D& i_Pt, const MgMat3E& i_Mt);

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
//S	inline MgLine3D operator * ( const MgLine3D& i_Ln, const MgMat3E &i_Mt)			// ���W�ϊ�
	static MgLine3D Mat3EMultLine3D( const MgLine3D& i_Ln, const MgMat3E& i_Mt)
	{
		MgLine3D Ln;
		Ln.p[0] = i_Ln.p[0] * i_Mt;
		Ln.p[1] = i_Ln.p[1] * i_Mt;
		return Ln;
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
//S	inline MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat3E& i_Mt)		// ���W�ϊ�
	static MgULine3D Mat3EMultULine3D( const MgULine3D& i_ULn, const MgMat3E& i_Mt)
	{
		MgULine3D ULn;
		ULn.p = i_ULn.p * i_Mt;
		ULn.v = i_ULn.v * i_Mt;
		return ULn;
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
	static MgPoint3D Mat3EMultEqualPoint3D( MgPoint3D& io_Pt, const MgMat3E& i_Mt);

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
	static MgVect3D Mat3EMultEqualVect3D( MgVect3D& io_Pt, const MgMat3E& i_Mt);

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
//S	inline MgLine3D operator *= ( MgLine3D& io_Ln, const MgMat3E &i_Mt)					// ���W�ϊ�
	static MgLine3D Mat3EMultEqualLine3D( MgLine3D& io_Ln, const MgMat3E& i_Mt)
	{
		io_Ln.p[0] *= i_Mt;
		io_Ln.p[1] *= i_Mt;
		return io_Ln;
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
//S	inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat3E& i_Mt)			// ���W�ϊ�
	static MgULine3D Mat3EMultEqualULine3D( MgULine3D& io_ULn, const MgMat3E& i_Mt)
	{
		io_ULn.p *= i_Mt;
		io_ULn.v *= i_Mt;
		return io_ULn;
	}

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
	static MgMat2E Mat2ERotV( const MgVect2D& v);

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
	static MgMat2E Mat2ERotRevV( const MgVect2D& v);

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
	static MgMat3E Mat3ERotZV( const MgVect2D& v);

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
	static MgMat3E Mat3ERotRevZV( const MgVect2D& v);

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
	static MgMat3E Mat3ERotTXV( const MgVect2D& v);

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
	static MgMat3E Mat3ERotRevXV( const MgVect2D& v);

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
	static MgMat3E Mat3ERotYV( const MgVect2D& v);

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
	static MgMat3E Mat3ERotRevYV( const MgVect2D& v);

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
	static MgMat2E Mat2EScl( const MgVect2D& vs);

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
	static MgMat3E Mat3EScl( const MgVect3D& vs);

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
	static MgMat2E Mat2EMov( const MgVect2D& v);
	static MgMat2E Mat2EMov( const MgPoint2D& p)
						{ return Mat2EMov( (MgVect2D&)p);}

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
	static MgMat3E Mat3EMov( const MgVect3D& v);
	static MgMat3E Mat3EMov( const MgPoint3D& p)
						{ return Mat3EMov( (MgVect3D&)p);}

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
//U	static MgMat2E Mat2EInv( const MgMat2E& i_mt);
	static MgMat2E Mat2EInv( MgMat2E& i_mt);

	//======================( �R���� )==============================
	//	�������e
	//	    �ϊ��}�g���b�N�X�̋t�ϊ��}�g���b�N�X���쐬����
	//
	//	�g�p�@
	//		Mgmat3_2 = MgMat3EInv(MgMat3E_1);
	//
	//	| m11 m21 m31 0 |
	//	| m12 m22 m32 0 |     	�i���͍s��͒P�ʍs��ł��鎖 ???�j
	//	| m13 m23 m33 0 |
	//	| M14 m24 m34 1 |
	//
//U	static MgMat3E Mat3EInv( const MgMat3E& i_Mt);
	static MgMat3E Mat3EInv( MgMat3E& i_Mt);

	//======================( �Q���� )==============================
	//		�����Ɋւ��鋾�f�ϊ��s����쐬
	//
	static MgMat2E Mat2EMirror(						// (  O) �����ϊ��s��
					const	MgULine2D&	i_uln		// (I  ) ���f�̎��Ƃ��钼��
			);

	//======================( �R���� )==============================
	//		���ʂɊւ��鋾�f�ϊ��s����쐬
	//
	static MgMat3E Mat3EMirror(						// (  O) �����ϊ��s��
					const	MgPlane3D& i_Pln		// (I  ) ���f�̖ʂƂ��镽��
			);

	//======================( �Q���� )==============================
	//		���S�_�Ɖ�]�p�����W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat2E Mat2ERot(						// (  O) �ϊ��s��
					const	MgPoint2D&	i_ptc, 		// (I  ) ��]�̒��S�ƂȂ�_
							MREAL		i_rd		// (I  ) ��]�p (���W�A��)
			);

	//======================( �R���� )==============================
	//		��]���ƂȂ钼���Ɖ�]�p�����W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3E Mat3ERot(						// (  O) �ϊ��s��
					const	MgULine3D&	i_ULn, 		// (I  ) ��]���ƂȂ钼��
							MREAL		i_ar		// (I  ) ��]�p(Degree)
			);

	//======================( �R���� )==============================
	//		�����ۍ��W�ϊ��}�g���b�N�X���v�Z����
	//
	static MgMat3E Mat3ENProj(						// (  O) �����ەϊ��s��
					const	MgMat3E&	i_Mt,		// (I  ) ���͍��W�ϊ��s��
					const	MgPlane3D&	i_Pln		// (I  ) ���ۖ�
			);

	//======================( �R���� )==============================
	//		�Γ��ۍ��W�ϊ��}�g���b�N�X���v�Z����
	//
	static MgMat3E Mat3ESProj(						// (  O) �Γ��ەύ��W�ϊ��s��
					const	MgMat3E&	i_Mt,		// (I  ) ���͍��W�ϊ��s��
					const	MgPlane3D&	i_Pln,		// (I  ) ���ۖ�
					const	MgVect3D&	i_V			// (I  ) ���ە����������P�ʃx�N�g��
			);

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
	//
	static void Mat3EPlntoXY(
					const	MgPlane3D&	i_Pln,		// (I  ) �ϊ��Ώە���
					const	MgPoint3D&	i_PtOrg,	// (I  ) ���_���W			
							MgMat3E*	o_pMatXY,	// (  O) Pln to XY���� �R�c�}�g���b�N�X
							MgMat3E*	o_pMatPln	// (  O) XY���� to Pln �R�c�}�g���b�N�X
					);
	
	//===================(�R���� �� �Q����)=========================
	//		�R�c���W���Q�c���W�֕ϊ�����
	//
	static void Point3Dto2D(
					const	MgPoint3D&	i_P,		// (I  ) �R�c���W
					const	MgMat3E&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgPoint2D*	o_pP		// (  O) �Q�c���W
					);

	//===================(�R���� �� �Q����)=========================
	//		�R�c�������Q�c�����֍��W�ϊ�����
	//
	static inline void Line3Dto2D(
					const MgLine3D&		i_Lni,		// (I  ) �R�c����
					const MgMat3E&		i_Mat,		// (I  ) ���W�ϊ��}�g���b�N�X
						  MgLine2D*		o_plno		// (  O) �Q�c����
					)
	{
		Point3Dto2D( i_Lni.p[0], i_Mat, &o_plno->p[0]); 
		Point3Dto2D( i_Lni.p[1], i_Mat, &o_plno->p[1]);
	}

	//===================(�R���� �� �Q����)=========================
	//		�R�c�������Q�c�����֍��W�ϊ�����
	//
	static void ULine3Dto2D(
					const	MgULine3D&	i_ULn,		// (I  ) �R�c����
					const	MgMat3E&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
						 	MgULine2D*	o_puln		// (  O) �Q�c����
					);

	//===================(�R���� �� �Q����)=========================
	//		�R�c���W���Q�c���W�֕ϊ�����
	//
	static MgPoint2D Point3Dto2D2(					// (  O) �Q�c���W
					const	MgPoint3D&	i_P,		// (I  ) �R�c���W
					const	MgMat3E&	i_Mt		// (I  ) ���W�ϊ��}�g���b�N�X
					);

	//===================(�R���� �� �Q����)=========================
	//		�R�c�������Q�c�����֍��W�ϊ�����
	//
	static inline MgLine2D Line3Dto2D2(				// (  O) �Q�c����
					const MgLine3D&		Lni,		// (I  ) �R�c����
					const MgMat3E&		Mat			// (I  ) ���W�ϊ��}�g���b�N�X
					)
	{
		return MgLine2D( 
					  Point3Dto2D2( Lni.p[0], Mat), 
					  Point3Dto2D2( Lni.p[1], Mat));
	}  

	//===================(�R���� �� �Q����)=========================
	//		�R�c�������Q�c�����֍��W�ϊ�����
	//
	static MgULine2D ULine3Dto2D2(					// (  O) �Q�c����
					const	MgULine3D&	i_ULn,		// (I  ) �R�c����
					const	MgMat3E&	i_Mt		// (I  ) ���W�ϊ��}�g���b�N�X
					);

	//===================(�R���� �� �Q����)=========================
	//		�R�c���W�Q���Q�c���W�Q�֕ϊ�����
	//
	static void	GPoint3Dto2D(
					const	MgGPoint3D&	i_GP,		// (I  ) �R�c���W�Q
					const	MgMat3E&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgGPoint2D*	o_pGP		// (  O) �Q�c���W�Q
					);
	
	//===================(�R���� �� �Q����)=========================
	//		�R�c���W�Q�i�|�����C���j���Q�c���W�Q�֕ϊ�����
	//
	static void	Polyg3Dto2D(
					const	MgPolyg3D&	i_Pg,		// (I  ) �R�c���W�Q
					const	MgMat3E&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgPolyg2D*	o_pPg		// (  O) �Q�c���W�Q
					);
	
	//===================(�R���� �� �Q����)=========================
	//		�R�c�����Q���Q�c�����Q�֕ϊ�����
	//
	static void	GLine3Dto2D(
					const	MgGLine3D&	i_GLn,		// (I  ) �R�c�����Q
					const	MgMat3E&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgGLine2D*	o_pgln		// (  O) �Q�c�����Q
					);
	
	//===================(�R���� �� �Q����)=========================
	//		�R�c���p�`�Q�i�|�����C���Q�j���Q�c���p�`�Q�֕ϊ�����
	//
	static void GPolyg3Dto2D(
					const	MgGPolyg3D&	i_GPg,		// (I  ) �R�c���p�`�Q
					const	MgMat3E&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
						 	MgGPolyg2D*	o_pgpg		// (  O) �Q�c���p�`�Q
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c���W���R�c���W�֕ϊ�����
	//
	static void	Point2Dto3D(
					const	MgPoint2D&	i_pt,		// (I  ) �Q�c���W
					const	MgMat3E&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgPoint3D*	o_pPt		// (  O) �R�c���W
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c�������R�c�����֍��W�ϊ�����
	//
	static inline void Line2Dto3D(
					const MgLine2D&		i_lni,		// (I  ) �Q�c����
					const MgMat3E&		i_Mat,		// (I  ) ���W�ϊ��}�g���b�N�X
						  MgLine3D*		o_pLno		// (  O) �R�c����
					)
	{
		Point2Dto3D( i_lni.p[0], i_Mat, &o_pLno->p[0]); 
		Point2Dto3D( i_lni.p[1], i_Mat, &o_pLno->p[1]);
	}  


	//===================(�Q���� �� �R����)=========================
	//		�Q�c�������R�c�����֍��W�ϊ�����
	//
	static void ULine2Dto3D(
					const	MgULine2D&	i_uln,		// (I  ) �Q�c����
					const	MgMat3E&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
						 	MgULine3D*	o_ULn		// (  O) �R�c����
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c���W���R�c���W�֕ϊ�����
	//
	static MgPoint3D Point2Dto3D3(					// (  O) �R�c���W
					const	MgPoint2D&	i_Pt,		// (I  ) �Q�c���W
					const	MgMat3E		&i_Mt		// (I  ) ���W�ϊ��}�g���b�N�X
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c�������R�c�����֍��W�ϊ�����
	//
	static MgLine3D Line2Dto3D3(					// (  O) �R�c����
					const MgLine2D&		lni,		// (I  ) �Q�c����
					const MgMat3E		&Mat		// (I  ) ���W�ϊ��}�g���b�N�X
					)
	{
		return MgLine3D(
					  Point2Dto3D3( lni.p[0], Mat), 
					  Point2Dto3D3( lni.p[1], Mat));
	}  

	//===================(�Q���� �� �R����)=========================
	//		�Q�c�������R�c�����֍��W�ϊ�����
	//
	static MgULine3D ULine2Dto3D3(					// (  O) �R�c����
					const	MgULine2D	&i_uln,		// (I  ) �Q�c����
					const	MgMat3E		&i_Mt		// (I  ) ���W�ϊ��}�g���b�N�X
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c���W�Q���R�c���W�Q�֕ϊ�����
	//
	static void	GPoint2Dto3D(
					const	MgGPoint2D	&i_GPt,		// (I  ) �Q�c���W�Q
					const	MgMat3E		&i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgGPoint3D	*o_GPt		// (  O) �R�c���W�Q
					);
	
	//===================(�Q���� �� �R����)=========================
	//		�Q�c���W�Q�i�|�����C���j���R�c���W�Q�֕ϊ�����
	//
	static void	Polyg2Dto3D(
					const	MgPolyg2D&	i_Pg,		// (I  ) �Q�c���W�Q
					const	MgMat3E		&i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgPolyg3D*	o_Pg		// (  O) �R�c���W�Q
					);
	
	//===================(�Q���� �� �R����)=========================
	//		�Q�c�����Q���R�c�����Q�֕ϊ�����
	//
	static void	GLine2Dto3D(
					const	MgGLine2D&	i_gln,		// (I  ) �Q�c�����Q
					const	MgMat3E		&i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgGLine3D	*o_GLn		// (  O) �R�c�����Q
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c���p�`�Q�i�|�����C���Q�j���R�c���p�`�Q�֕ϊ�����
	//
	static void GPolyg2Dto3D(
					const	MgGPolyg2D	&i_GPg,		// (I  ) �Q�c���p�`�Q
					const	MgMat3E		&i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
						 	MgGPolyg3D	*o_GPg		// (  O) �R�c���p�`�Q
					);

	//
	//======================( �Q�c�C�R�c )==============================
	//	�Q�c�C�R�c�}�g���b�N�X
	//
	//======================( �Q���� )==============================
	//		���_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat2D Mat2DRot( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2DRotV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �Q���� )==============================
	//		���_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat2D Mat2DRotRev( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2DRotRevV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�w�x���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3D Mat3DRotZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�w�x���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3D Mat3DRotRevZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotRevZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�x�y���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3D Mat3DRotTX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return  Mat3DRotTXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�x�y���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3D Mat3DRotRevX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotRevXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�y�w���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3D Mat3DRotY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( �R���� )==============================
	//		�y�w���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3D Mat3DRotRevY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotRevYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�̉��Z
	//
	//	�g�p�@
	//		MgMat2D= MgMat2D1 + MgMat2D2;
	//
	//	| m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  +  | n21 n22 n23 |
	//	| m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2D Mat2DPlus( const MgMat2D& i_mt1, const MgMat2D& i_mt2);

	//
	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̉��Z
	//
	//	�g�p�@
	//		MgMat2D1 += MgMat2D2;
	//
	//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  =  | m21 m22 m23 |  +  | n21 n22 n23 |
	//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2D Mat2DPlusEqual( MgMat2D& io_mt1, const MgMat2D& i_mt2);

	//===========================================================================
	//	�������e
	//		���̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat2D2 = - MgMat2D1;
	//
	//	  | m11 m12 m13 |
	//	- | m21 m22 m23 |
	//	  | m31 m32 m33 |
	//
	static MgMat2D Mat2DSingleMinus( const MgMat2D& m1);

	//===========================================================================
	//	�������e
	//		���̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat2D2 = - MgMat2D1;
	//
	//	  | m11 m12 m13 |
	//	- | m21 m22 m23 |
	//	  | m31 m32 m33 |
	//
	static MgMat2D MatMinusSingle2( const MgMat2D& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̈��Z
	//
	//	�g�p�@
	//		MgMat2D= MgMat2D1 - MgMat2D2;
	//
	//	  | m11 m12 m13 |     | n11 n12 n13 |
	//	  | m21 m22 m23 |  -  | n21 n22 n23 |
	//	  | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2D Mat2DMinus( const MgMat2D& i_mt1, const MgMat2D& i_mt2);

	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�̈��Z
	//
	//	�g�p�@
	//		MgMat2D1 -= MgMat2D2;
	//
	//	| m11 m12 m13 |    | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  = | m21 m22 m23 |  -  | n21 n22 n23 |
	//	| m31 m32 m33 |    | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2D Mat2DMinusEqual( MgMat2D& io_mt1, const MgMat2D& i_mt2);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̂����Z
	//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɍ��W�ϊ��}�g���b�N�X�ɂ��ϊ�����}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat2D= MgMat2D1 * MgMat2D2;
	//
	//	| m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  X  | n21 n22 n23 |
	//	| m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2D Mat2DMult( const MgMat2D& i_mt1, const MgMat2D& i_mt2);

	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�̂����Z
	//	    ���W�ϊ��}�g���b�N�X�ɂ��ϊ���ɁA����ɍ��W�ϊ��}�g���b�N�X�ɂ��ϊ�����}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat2D2 *= MgMat2D1;
	//
	//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
	//	| m21 m22 m23 |  =  | m21 m22 m23 |  X  | n21 n22 n23 |
	//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
	//
	static MgMat2D Mat2DMultEqual( MgMat2D& io_mt1, const MgMat2D& i_mt2);

	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint2Dpo = MgPoint2Dp * MgMat2Dtm;
	//
	//					   | m11 m12 m13 |
	//	| px  py  1  |  X  | m21 m22 m23 |
	//					   | m31 m32 m33 |     
	//
	static MgPoint2D Mat2DMultPoint2D( const MgPoint2D& i_pt, const MgMat2D& i_mt);

	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect2Dpo = MgVect2Dp * MgMat2Dtm;
	//
	//					   | m11 m12 m13 |
	//	| vx  vy  0  |  X  | m21 m22 m23 |
	//					   | m31 m32 m33 |     
	//
	static MgVect2D Mat2DMultVect2D( const MgVect2D& i_pt, const MgMat2D& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint2Dp *= MgMat2Dm;
	//
	//										  | m11 m12 m13 |
	//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 m23 |
	//				   						  | m31 m32 m33 |
	//
	static MgPoint2D Mat2DMultEqualPoint2D( MgPoint2D& io_pt, const MgMat2D& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect2Dp *= MgMat2Dm;
	//
	//										  | m11 m12 m13 |
	//	| vx  vy  0  |  =  | vx  vy  0  |  X  | m21 m22 m23 |
	//				   						  | m31 m32 m33 |
	//
	static MgVect2D Mat2DMultEqualVect2D( MgVect2D& io_pt, const MgMat2D& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgULine2D = MgULine2D *  MgMat2D;
	//
	//	| px  py  1  |     | m11 m12 m13 |
	//	| vx  vy  0  |  X  | m21 m22 m23 |
	//					   | m31 m32 m33 |
	//
	static MgULine2D Mat2DMultULine2D( const MgULine2D& i_uln, const MgMat2D& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgULine2D *= MgMat2D;
	//
	//	| px  py  1  |     | px  py  1  |     | m11 m12 m13 |
	//	| vx  vy  0  |  =  | vx  vy  1  |  X  | m21 m22 m23 |
	//			             				  | m31 m32 m33 |
	//
	static MgULine2D Mat2DMultEqualULine2D( MgULine2D& io_uln, const MgMat2D& i_mt);

	//===============( �Q�������W�ϊ��}�g���b�N�X�łR�������W���� )==============
	//
	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint3D2 = MgPoint3D1 * MgMat2D1;
	//
	//						  | m11 m12 0 m13 |     
	//	| px  py  pz  1 |  X  | m21 m22 0 m23 |
	//						  |  0   0  1  0  |
	//						  | m31 m32 0 m33 |
	//
	static MgPoint3D Mat2DMultPoint3D( const MgPoint3D& i_Pt, const MgMat2D& i_mt);

	//
	//===========================================================================
	//	�������e
	//	    ���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect3D2 = MgVect3D1 * MgMat2D1;
	//
	//						  | m11 m12 0 m13 |     
	//	| vx  vy  vz  0 |  X  | m21 m22 0 m23 |
	//						  |  0   0  1  0  |
	//						  | m31 m32 0 m33 |
	//
	static MgVect3D Mat2DMultVect3D( const MgVect3D& i_Pt, const MgMat2D& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint3D *= MgMat2D;
	//
	//						 						| m11 m12 0 m13 |
	//	| px  py  pz  1 |  =  | px  py  pz  1 |  X  | m21 m22 0 m23 |
	//			   									|  0   0  1  0  |
	//			   									| m31 m32 0 m33 |
	
	static MgPoint3D Mat2DMultEqualPoint3D( MgPoint3D& io_Pt, const MgMat2D& i_mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect3D *= MgMat2D;
	//
	//						 						| m11 m12 0 m13 |
	//	| vx  vy  vz  0 |  =  | vx  vy  vz  0 |  X  | m21 m22 0 m23 |
	//			   									|  0   0  1  0  |
	//			   									| m31 m32 0 m33 |
	
	static MgVect3D Mat2DMultEqualVect3D( MgVect3D& io_Pt, const MgMat2D& i_mt);

//S	//===========================================================================
//	//	�������e
//	//		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
//	//
//	//	�g�p�@
//	//		MgULine2D = MgULine2D * MgMat2D;
//	//
//	//	| px  py  pz  1 |	  | m11 m12 0 m13 |
//	//	| vx  vy  vz  0 |  X  | m21 m22 0 m23 |
//	//						  |  0   0  1  0  |
//	//			   			  | m31 m32 0 m33 |
//	//
//	static MgULine3D Mat2DMultULine3D( const MgULine3D& ULn1, const MgMat2D& m2);

	////===========================================================================
	////	�������e
	////		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	////
	////	�g�p�@
	////		MgULine2D = MgULine2D * MgMat2D;
	////
	////	| px  py  pz  1 |	  | m11 m12 0 m13 |
	////	| vx  vy  vz  0 |  X  | m21 m22 0 m23 |
	////						  |  0   0  1  0  |
	////						  | m31 m32 0 m33 |
	////
	//static MgULine3D Mat2DMultULine3D( const MgULine3D& i_ULn, const MgMat2D& i_mt);

	////===========================================================================
	////	�������e
	////		���W�ϊ��}�g���b�N�X�ɂ����W�ϊ�����
	////
	////	�g�p�@
	////		MgULine2D *= MgMat2D;
	////
	////	| px  py  pz  1 |     | px  py  pz  1 |		| m11 m12 0 m13 |
	////	| vx  vy  vz  0 |  =  | vx  vy  vz  0 |  X  | m21 m22 0 m23 |
	////												|  0   0  1  0  |
	////				 				   				| m31 m32 0 m33 |
	////
	//static MgULine3D Mat2DMultEqualULine3D( MgULine3D& io_ULn, const MgMat2D& i_mt);

	//===========================================================================
	//
	//	�R�c���W�ϊ��}�g���b�N�X�̌v�Z
	//
	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̉��Z
	//
	//	�g�p�@
	//		MgMat3D_3 = MgMat3D_1 + MgMat3D_2;
	//
	//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat3D Mat3DPlus( const MgMat3D& i_Mt, const MgMat3D& i_Mt2);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̉��Z
	//
	//	�g�p�@
	//		MgMat3D+= MgMat3D;
	//
	//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat3D Mat3DPlusEqual( MgMat3D& io_Mt1, const MgMat3D& i_Mt2);

	//===========================================================================
	//	�������e
	//		���̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat3D_2 = - MgMat3D_1;
	//
	//	  | m11 m12 m13 m14 |
	//	- | m21 m22 m23 m24 |
	//	  | m31 m32 m33 m34 |
	//	  | m41 m42 m43 m44 |     
	//
	static MgMat3D Mat3DSingleMinus( const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̈��Z
	//
	//	�g�p�@
	//		MgMat3D_3 = MgMat3D_1 - MgMat3D_2;
	//
	//	  | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
	//	  | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	  | m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat3D Mat3DMinus( const MgMat3D& i_Mt1, const MgMat3D& i_Mt2);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̈��Z
	//
	//	�g�p�@
	//		MgMat3D-= MgMat3D;
	//
	//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat3D Mat3DMinusEqual( MgMat3D& io_Mt1, const MgMat3D& i_Mt2);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̂����Z
	//
	//	�g�p�@
	//		MgMat3D_3 = MgMat3D_1 * MgMat3D_2;
	//
	//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
	//
	static MgMat3D Mat3DMult( const MgMat3D& i_Mt1, const MgMat3D& i_Mt2);

	//===========================================================================
	//	�������e
	//		���W�ϊ��}�g���b�N�X�̂����Z
	//
	//	�g�p�@
	//		MgMat3D*= MgMat3D;
	//
	//	| m11 m12 m13 m14 |     | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
	//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
	//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
	//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
	//
	static MgMat3D Mat3DMultEqual( MgMat3D& io_Mt1, const MgMat3D& i_Mt2);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgMat3D_2 = MgPoint2D * MgMat3D_1;
	//
	//						    | m11 m12 m13 m14 |
	//	| px  py  0   1   |  X  | m21 m22 m23 m24 |
	//						    | m31 m32 m33 m34 |
	//						    | m41 m42 m43 m44 |
	//
	static MgPoint2D Mat3DMultPoint2D( const MgPoint2D& i_Pt, const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgMat3D_2 = MgVect2D * MgMat3D_1;
	//
	//						    | m11 m12 m13 m14 |
	//	| vx  vy  0   0   |  X  | m21 m22 m23 m24 |
	//						    | m31 m32 m33 m34 |
	//						    | m41 m42 m43 m44 |
	//
	static MgVect2D Mat3DMultVect2D( const MgVect2D& i_Pt, const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint2D *= MgMat3D;
	//
	//						     					    | m11 m12 m13 m14 |
	//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 m24 |
	//	           									    | m31 m32 m33 m34 |
	//	           									    | m41 m42 m43 m44 |
	//
	static MgPoint2D Mat3DMultEqualPoint2D( MgPoint2D& io_Pt, const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��Q�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect2D *= MgMat3D;
	//
	//						     					    | m11 m12 m13 m14 |
	//	| vx  vy  0   0   |  =  | vx  vy  0   0   |  X  | m21 m22 m23 m24 |
	//	           									    | m31 m32 m33 m34 |
	//	           									    | m41 m42 m43 m44 |
	//
	static MgVect2D Mat3DMultEqualVect2D( MgVect2D& io_Pt, const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint3D_2 = MgVect3D_1 * MgMat3D;
	//
	//	 					    | m11 m12 m13 m14 |
	//	| px  py  pz  1   |  X  | m21 m22 m23 m24 |
	//						    | m31 m32 m33 m34 |
	//						    | m41 m42 m43 m44 |
	//
	static MgPoint3D Mat3DMultPoint3D( const MgPoint3D& i_Pt, const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect3D_2 = MgVect3D_1 * MgMat3D;
	//
	//	 					    | m11 m12 m13 m14 |
	//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
	//						    | m31 m32 m33 m34 |
	//						    | m41 m42 m43 m44 |
	//
	static MgVect3D Mat3DMultVect3D( const MgVect3D& i_Pt, const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgPoint3D *= MgMat3D;
	//
	//							 					    | m11 m12 m13 m14 |
	//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
	//												    | m31 m32 m33 m34 |
	//												    | m41 m42 m43 m44 |
	//
	static MgPoint3D Mat3DMultEqualPoint3D( MgPoint3D& io_Pt, const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect3D *= MgMat3D;
	//
	//							 					    | m11 m12 m13 m14 |
	//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
	//												    | m31 m32 m33 m34 |
	//												    | m41 m42 m43 m44 |
	//
	static MgVect3D Mat3DMultEqualVect3D( MgVect3D& io_Pt, const MgMat3D& i_Mt);

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgLine3D = MgLine3D_1 * MgMat3D;
	//
	//	| px  py  pz  1   |     | m11 m12 m13 m14 |
	//	| px  py  pz  1   |  X  | m21 m22 m23 m24 |
	//							| m31 m32 m33 m34 |
	//							| m41 m42 m43 m44 |
	//
//S	inline MgLine3D operator * ( const MgLine3D& io_Ln, const MgMat3D &i_Mt)	// ���W�ϊ�
	static MgLine3D Mat3DMultLine3D( const MgLine3D& i_Ln, const MgMat3D& i_Mt)
	{
		MgLine3D Ln;
		Ln.p[0] = i_Ln.p[0] * i_Mt;
		Ln.p[1] = i_Ln.p[1] * i_Mt;
		return Ln;
	}

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgULine3D_2 = MgULine3D_1 * MgMat3D;
	//
	//	| px  py  pz  1   |     | m11 m12 m13 m14 |
	//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
	//							| m31 m32 m33 m34 |
	//							| m41 m42 m43 m44 |
	//
//S	inline MgULine3D operator * ( const MgULine3D& i_Ln, const MgMat3E& i_Mt)	// ���W�ϊ�
	static MgULine3D Mat3DMultULine3D( const MgULine3D& i_ULn, const MgMat3D& i_Mt)
	{
		MgULine3D ULn;
		ULn.p = i_ULn.p * i_Mt;
		ULn.v = i_ULn.v * i_Mt;
		return ULn;
	}

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgLine3D *= MgMat3D;
	//
	//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
	//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
	//													| m31 m32 m33 m34 |
	//													| m41 m42 m43 m44 |
	//
//S	inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat3E& i_Mt)			// ���W�ϊ�
	static MgLine3D Mat3DMultEqualLine3D( MgLine3D& io_Ln, const MgMat3D& i_Mt)
	{
		io_Ln.p[0] *= i_Mt;
		io_Ln.p[1] *= i_Mt;
		return io_Ln;
	}

	//===========================================================================
	//	�������e
	//		�R�������W�ϊ��}�g���b�N�X�ɂ��R�����f�[�^�����W�ϊ�����
	//
	//	�g�p�@
	//		MgVect3D *= MgMat3D;
	//
	//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
	//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
	//													| m31 m32 m33 m34 |
	//													| m41 m42 m43 m44 |
	//
//S	inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat3E& i_Mt)			// ���W�ϊ�
	static MgULine3D Mat3DMultEqualULine3D( MgULine3D& io_ULn, const MgMat3D& i_Mt)
	{
		io_ULn.p *= i_Mt;
		io_ULn.v *= i_Mt;
		return io_ULn;
	}

	//======================( �Q���� )==============================
	//	�������e
	//		���_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat2D= MgMat3DRotV(MgVect2D);
	//
	//		( MgVect2D: �P�ʃx�N�g��)
	//
	//	|  cos  sin  0. |
	//	| -sin  cos  0. |
	//	|   0.   0.  1. |
	//
	static MgMat2D Mat2DRotV( const MgVect2D& v);

	//======================( �Q���� )==============================
	//	�������e
	//		���_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat2D= MgMat3DRotRevV(MgVect2D);
	//
	//		( MgVect2D: �P�ʃx�N�g��)
	//
	//	| cos -sin  0. |
	//	| sin  cos  0. |
	//	|  0.   0.  1. |
	//
	static MgMat2D Mat2DRotRevV( const MgVect2D& v);

	//======================( �R���� )==============================
	//	�������e
	//		�w�x���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat3D= MgMat3DRotZV(MgVect2D);
	//
	//		( MgVect2D: �P�ʃx�N�g��)
	//
	//	|  cos  sin  0.  0. |
	//	| -sin  cos  0.  0. |
	//	|   0.   0.  1.  0. |
	//	|   0.   0.  0.  1. |
	//
	static MgMat3D Mat3DRotZV( const MgVect2D& v);

	//======================( �R���� )==============================
	//	�������e
	//		�w�x���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat3D= MgMat3DRotRevZV(MgVect2D);
	//
	//		( MgVect2D: �P�ʃx�N�g��)
	//
	//	|  cos -sin  0.  0. |
	//	|  sin  cos  0.  0. |
	//	|   0.   0.  1.  0. |
	//	|   0.   0.  0.  1. |
	//
	static MgMat3D Mat3DRotRevZV( const MgVect2D& v);

	//======================( �R���� )==============================
	//	�������e
	//		�x�y���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat3D= MgMat3DRotTXV(MgVect2D);
	//
	//		( MgVect2D: �P�ʃx�N�g��)
	//
	//	|  1.   0.   0.  0. |
	//	|  0.  cos  sin  0. |
	//	|  0. -sin  cos  0. |
	//	|  0.   0.   0.  1. |
	//
	static MgMat3D Mat3DRotTXV( const MgVect2D& v);

	//======================( �R���� )==============================
	//	�������e
	//		�x�y���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat3D= MgMat3DRotRevXV(MgVect2D);
	//
	//		( MgVect2D: �P�ʃx�N�g��)
	//
	//	|  1.   0.   0.  0. |
	//	|  0.  cos -sin  0. |
	//	|  0.  sin  cos  0. |
	//	|  0.   0.   0.  1. |
	//
	static MgMat3D Mat3DRotRevXV( const MgVect2D& v);

	//======================( �R���� )==============================
	//	�������e
	//		�y�w���ʂŌ��_�𒆐S�ɉ�]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat3D= MgMat3DRotYV(MgVect2D);
	//
	//		( MgVect2D: �P�ʃx�N�g��)
	//
	//	|  cos   0. -sin   0. |
	//	|   0.   1.   0.   0. |
	//	|  sin   0.  cos   0. |
	//	|   0.   0.   0.   1. |
	//
	static MgMat3D Mat3DRotYV( const MgVect2D& v);

	//======================( �R���� )==============================
	//	�������e
	//		�y�w���ʂŌ��_�𒆐S�ɋt��]�̍��W�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat3D= MgMat3DRotRevYV(MgVect2D);
	//
	//		( MgVect2D: �P�ʃx�N�g��)
	//
	//	|  cos   0.  sin   0. |
	//	|   0.   1.   0.   0. |
	//	| -sin   0.  cos   0. |
	//	|   0.   0.   0.   1. |
	//
	static MgMat3D Mat3DRotRevYV( const MgVect2D& v);

	//======================( �Q���� )==============================
	//	�������e
	//	    �w�C�x�����Ɋg��^�k������}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		Mgmat_2 = MgMat2DScl(MgVect2D_1);
	//
	//	| sx  0   0  |
	//	| 0   xy  0  |
	//	| 0   0   1  |
	//
	static MgMat2D Mat2DScl( const MgVect2D& vs);

	//======================( �R���� )==============================
	//	�������e
	//	    �w�C�x�C�y�����Ɋg��^�k������}�g���b�N�X���쐬����
	//
	//	�g�p�@
	//		Mgmat3_2 = MgMat3DScl(MgMat3D_1);
	//
	//	| sx  0   0   0  |
	//	| 0   xy  0   0  |
	//	| 0   0   sz  0  |
	//	| 0   0   0   1  |
	//
	static MgMat3D Mat3DScl( const MgVect3D& vs);

	//======================( �Q���� )==============================
	//	�������e
	//		���s�ړ��̕ϊ��}�g���b�N�X���쐬����
	//
	//	�g�p�@
	//		MgMat2D= MgMat3DMov(MgVect2D)
	//
	//	|  1.  0.  0. |
	//	|  0.  1.  0. |
	//	|  v.x v.y 1. |
	//
	static MgMat2D Mat2DMov( const MgVect2D& v);
	static MgMat2D Mat2DMov( const MgPoint2D& p)
						{ return Mat2DMov( (MgVect2D&)p);}

	//======================( �R���� )==============================
	//	�������e
	//		���s�ړ��̕ϊ��}�g���b�N�X���쐬����
	//
	//	�g�p�@
	//		Mgmat3 = MgMat3DMov(MgVect3D)
	//
	//	| 1.  0.  0.  0. |
	//	| 0.  1.  0.  0. |
	//	| 0.  0.  1.  0. |
	//	| v.x v.y v.z 1. |
	//
	static MgMat3D Mat3DMov( const MgVect3D& v);
	static MgMat3D Mat3DMov( const MgPoint3D& p)
						{ return Mat3DMov( (MgVect3D&)p);}

	//======================( �Q���� )==============================
	//	�������e
	//		�ϊ��}�g���b�N�X�̋t�ϊ��}�g���b�N�X���쐬
	//
	//	�g�p�@
	//		MgMat2D= MgMat2DInv(MgMat2D);
	//
	//	| m11 m21 m31 |
	//	| m12 m22 m32 |			�i���͍s��͒P�ʍs��ł��鎖 ???�j
	//	| m13 m23 m33 |
	//
//U	static MgMat2D Mat2DInv( const MgMat2D& i_mt);
	static MgMat2D Mat2DInv( MgMat2D& i_mt);

	//======================( �R���� )==============================
	//	�������e
	//	    �ϊ��}�g���b�N�X�̋t�ϊ��}�g���b�N�X���쐬����
	//
	//	�g�p�@
	//		Mgmat3_2 = MgMat3DInv(MgMat3D_1);
	//
	//	| m11 m21 m31 m41 |
	//	| m12 m22 m32 m42 |     �i���͍s��͒P�ʍs��ł��鎖 ???�j
	//	| m13 m23 m33 m43 |
	//	| M14 m24 m34 m44 |
	//
//U	static MgMat3D Mat3DInv( const MgMat3D& i_Mt);
	static MgMat3D Mat3DInv( MgMat3D& i_Mt);

	//======================( �Q���� )==============================
	//		�����Ɋւ��鋾�f�ϊ��s����쐬
	//
	static MgMat2D Mat2DMirror(						// (  O) �����ϊ��s��
					const	MgULine2D&	i_uln		// (I  ) ���f�̎��Ƃ��钼��
			);

	//======================( �R���� )==============================
	//		���ʂɊւ��鋾�f�ϊ��s����쐬
	//
	static MgMat3D Mat3DMirror(						// (  O) �����ϊ��s��
					const	MgPlane3D& i_Pln		// (I  ) ���f�̖ʂƂ��镽��
			);

	//======================( �Q���� )==============================
	//		���S�_�Ɖ�]�p�����W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat2D Mat2DRot(						// (  O) �ϊ��s��
					const	MgPoint2D&	i_ptc, 		// (I  ) ��]�̒��S�ƂȂ�_
							MREAL		i_rd		// (I  ) ��]�p (���W�A��)
			);

	//======================( �R���� )==============================
	//		��]���ƂȂ钼���Ɖ�]�p�����W�ϊ��}�g���b�N�X���쐬
	//
	static MgMat3D Mat3DRot(						// (  O) �ϊ��s��
					const	MgULine3D&	i_ULn, 		// (I  ) ��]���ƂȂ钼��
							MREAL		i_ar		// (I  ) ��]�p(Degree)
			);

	//======================( �R���� )==============================
	//		�����ۍ��W�ϊ��}�g���b�N�X���v�Z����
	//
	static MgMat3D Mat3DNProj(						// (  O) �����ەϊ��s��
					const	MgMat3D&	i_Mt,		// (I  ) ���͍��W�ϊ��s��
					const	MgPlane3D&	i_Pln		// (I  ) ���ۖ�
			);

	//======================( �R���� )==============================
	//		�Γ��ۍ��W�ϊ��}�g���b�N�X���v�Z����
	//
	static MgMat3D Mat3DSProj(						// (  O) �Γ��ەύ��W�ϊ��s��
					const	MgMat3D&	i_Mt,		// (I  ) ���͍��W�ϊ��s��
					const	MgPlane3D&	i_Pln,		// (I  ) ���ۖ�
					const	MgVect3D&	i_V			// (I  ) ���ە����������P�ʃx�N�g��
			);

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
	
	static void Mat3DPlntoXY(
					const	MgPlane3D&	i_Pln,		// (I  ) �ϊ��Ώە���
					const	MgPoint3D&	i_PtOrg,	// (I  ) ���_���W			
							MgMat3D*	o_MatXY,	// (  O) Pln to XY���� �R�c�}�g���b�N�X
							MgMat3D*	o_MatPln	// (  O) XY���� to Pln �R�c�}�g���b�N�X
					);
	
	//===================(�R���� �� �Q����)=========================
	//		�R�c���W���Q�c���W�֕ϊ�����
	//
	static void Point3Dto2D(
					const	MgPoint3D&	i_P,		// (I  ) �R�c���W
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgPoint2D*	o_P			// (  O) �Q�c���W
					);

	//===================(�R���� �� �Q����)=========================
	//		�R�c�������Q�c�����֍��W�ϊ�����
	//
	static inline void Line3Dto2D(
					const MgLine3D&		i_Lni,		// (I  ) �R�c����
					const MgMat3D&		i_Mat,		// (I  ) ���W�ϊ��}�g���b�N�X
						  MgLine2D*		o_plno		// (  O) �Q�c����
					)
	{
		Point3Dto2D( i_Lni.p[0], i_Mat, &o_plno->p[0]); 
		Point3Dto2D( i_Lni.p[1], i_Mat, &o_plno->p[1]);
	}

	//===================(�R���� �� �Q����)=========================
	//		�R�c�������Q�c�����֍��W�ϊ�����
	//
	static void ULine3Dto2D(
					const	MgULine3D&	i_ULn,		// (I  ) �R�c����
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
						 	MgULine2D*	o_puln		// (  O) �Q�c����
					);

	//===================(�R���� �� �Q����)=========================
	//		�R�c���W���Q�c���W�֕ϊ�����
	//
	static MgPoint2D Point3Dto2D2(					// (  O) �Q�c���W
					const	MgPoint3D&	i_P,		// (I  ) �R�c���W
					const	MgMat3D&	i_Mt		// (I  ) ���W�ϊ��}�g���b�N�X
					);

	//===================(�R���� �� �Q����)=========================
	//		�R�c�������Q�c�����֍��W�ϊ�����
	//
	static inline MgLine2D Line3Dto2D2(				// (  O) �Q�c����
					const MgLine3D&		i_Lni,		// (I  ) �R�c����
					const MgMat3D&		i_Mat		// (I  ) ���W�ϊ��}�g���b�N�X
					)
	{
		return MgLine2D( 
					  Point3Dto2D2( i_Lni.p[0], i_Mat), 
					  Point3Dto2D2( i_Lni.p[1], i_Mat));
	}  

	//===================(�R���� �� �Q����)=========================
	//		�R�c�������Q�c�����֍��W�ϊ�����
	//
	static MgULine2D ULine3Dto2D2(					// (  O) �Q�c����
					const	MgULine3D&	i_ULn,		// (I  ) �R�c����
					const	MgMat3D&	i_Mt		// (I  ) ���W�ϊ��}�g���b�N�X
					);

	//===================(�R���� �� �Q����)=========================
	//		�R�c���W�Q���Q�c���W�Q�֕ϊ�����
	//
	static void	GPoint3Dto2D(
					const	MgGPoint3D&	i_GP,		// (I  ) �R�c���W�Q
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgGPoint2D*	o_pGP		// (  O) �Q�c���W�Q
					);
	
	//===================(�R���� �� �Q����)=========================
	//		�R�c���W�Q�i�|�����C���j���Q�c���W�Q�֕ϊ�����
	//
	static void	Polyg3Dto2D(
					const	MgPolyg3D&	i_Pg,		// (I  ) �R�c���W�Q
					const	MgMat3D&	i_iTm,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgPolyg2D*	o_pPg		// (  O) �Q�c���W�Q
					);
	
	//===================(�R���� �� �Q����)=========================
	//		�R�c�����Q���Q�c�����Q�֕ϊ�����
	//
	static void	GLine3Dto2D(
					const	MgGLine3D&	i_GLn,		// (I  ) �R�c�����Q
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgGLine2D*	o_pgln		// (  O) �Q�c�����Q
					);
	
	//===================(�R���� �� �Q����)=========================
	//		�R�c���p�`�Q�i�|�����C���Q�j���Q�c���p�`�Q�֕ϊ�����
	//
	static void GPolyg3Dto2D(
					const	MgGPolyg3D&	i_GPg,		// (I  ) �R�c���p�`�Q
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
						 	MgGPolyg2D*	o_pgpg		// (  O) �Q�c���p�`�Q
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c���W���R�c���W�֕ϊ�����
	//
	static void	Point2Dto3D(
					const	MgPoint2D&	i_pt,		// (I  ) �Q�c���W
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgPoint3D*	o_pPt		// (  O) �R�c���W
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c�������R�c�����֍��W�ϊ�����
	//
	static inline void Line2Dto3D(
					const MgLine2D&		i_lni,		// (I  ) �Q�c����
					const MgMat3D&		i_Mat,		// (I  ) ���W�ϊ��}�g���b�N�X
						  MgLine3D*		o_pLno		// (  O) �R�c����
					)
	{
		Point2Dto3D( i_lni.p[0], i_Mat, &o_pLno->p[0]); 
		Point2Dto3D( i_lni.p[1], i_Mat, &o_pLno->p[1]);
	}  


	//===================(�Q���� �� �R����)=========================
	//		�Q�c�������R�c�����֍��W�ϊ�����
	//
	static void ULine2Dto3D(
					const	MgULine2D&	i_uln,		// (I  ) �Q�c����
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
						 	MgULine3D*	o_pULn		// (  O) �R�c����
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c���W���R�c���W�֕ϊ�����
	//
	static MgPoint3D Point2Dto3D3(					// (  O) �R�c���W
					const	MgPoint2D&	i_Pt,		// (I  ) �Q�c���W
					const	MgMat3D&	i_Mt		// (I  ) ���W�ϊ��}�g���b�N�X
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c�������R�c�����֍��W�ϊ�����
	//
	static MgLine3D Line2Dto3D3(					// (  O) �R�c����
					const MgLine2D&		i_lni,		// (I  ) �Q�c����
					const MgMat3D&		i_Mat		// (I  ) ���W�ϊ��}�g���b�N�X
					)
	{
		return MgLine3D(
					  Point2Dto3D3( i_lni.p[0], i_Mat), 
					  Point2Dto3D3( i_lni.p[1], i_Mat));
	}  

	//===================(�Q���� �� �R����)=========================
	//		�Q�c�������R�c�����֍��W�ϊ�����
	//
	static MgULine3D ULine2Dto3D3(					// (  O) �R�c����
					const	MgULine2D&	i_uln,		// (I  ) �Q�c����
					const	MgMat3D&	i_Mt		// (I  ) ���W�ϊ��}�g���b�N�X
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c���W�Q���R�c���W�Q�֕ϊ�����
	//
	static void	GPoint2Dto3D(
					const	MgGPoint2D&	i_GPt,		// (I  ) �Q�c���W�Q
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgGPoint3D*	o_pGPt		// (  O) �R�c���W�Q
					);
	
	//===================(�Q���� �� �R����)=========================
	//		�Q�c���W�Q�i�|�����C���j���R�c���W�Q�֕ϊ�����
	//
	static void	Polyg2Dto3D(
					const	MgPolyg2D&	i_Pg,		// (I  ) �Q�c���W�Q
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgPolyg3D*	o_pPg		// (  O) �R�c���W�Q
					);
	
	//===================(�Q���� �� �R����)=========================
	//		�Q�c�����Q���R�c�����Q�֕ϊ�����
	//
	static void	GLine2Dto3D(
					const	MgGLine2D&	i_gln,		// (I  ) �Q�c�����Q
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
							MgGLine3D*	o_pGLn		// (  O) �R�c�����Q
					);

	//===================(�Q���� �� �R����)=========================
	//		�Q�c���p�`�Q�i�|�����C���Q�j���R�c���p�`�Q�֕ϊ�����
	//
	static void GPolyg2Dto3D(
					const	MgGPolyg2D&	i_GPg,		// (I  ) �Q�c���p�`�Q
					const	MgMat3D&	i_Mt,		// (I  ) ���W�ϊ��}�g���b�N�X
						 	MgGPolyg3D*	o_pGPg		// (  O) �R�c���p�`�Q
					);
	//
	//======================( �Q�����C�R���� )==============================
	//		�}�`����
	//
	// ---------------------( �Q���� )------------------------------
	//		�w��������n�܂�����Q�̐������������čŏ��̑��p�`���쐬����
	//
	static bool	MakeGPolygonFromLineInGLine2D(		// (  O) �X�e�C�^�X�@true: ����쐬�@false: �쐬�s��
					const	MgLine2D&	i_Ln1,		// (I  ) �w�����
							MgGLine2D*	io_GLn2,	// (I O) ������������Q
							MINT*		io_pnHk,	// (I O) ������������̒��̐��������������������i�擪�������\���j
							MgPolyg2D*	o_pPg3		// (  O) �̈�
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���p�`�𒼐��Ő؂�A�����̎w�葤�̗̈�𓾂�			<���p�`�����̏ꍇ�̍l���s��?>
	//
	static MINT DividePolygonULine2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_LEFT			(010): �����̗̈�
													//			MC_RIGHT		(040): �E���̗̈�
					const	MgPolyg2D&	i_Pg1,		// (I  ) ���p�`
					const	MgULine2D&	i_ULn2,		// (I  ) ����
							MgGPolyg2D*	o_pGPg3		// (  O) ���t�����p�`�Q
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���t�����p�`�𒼐��Ő؂�A�����̎w�葤�̗̈�𓾂�
	//
	static MINT DivideGPolygonULine2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_LEFT			(010): �����̗̈�
													//			MC_RIGHT		(040): �E���̗̈�
					const	MgGPolyg2D&	i_GPg1,		// (I  ) ���t�����p�`
					const	MgULine2D&	i_ULn2,		// (I  ) ����
							MgGPolyg2D*	o_pGPg3		// (  O) ���t�����p�`�Q
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���p�`1�𑽊p�`2�ŕ������A���p�`2�̎w�葤�i�����܂��͊O���j�̗̈�𓾂�
	//
	static MINT Divide2Polygon2D(					// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_OUT_BORDER	(004): �O��
													//									
					const	MgPolyg2D&	i_Pg1,		// (I  ) ���p�`1
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`2
							MgGPolyg2D*	o_ppGPgo	// (  O) ���t�����p�`3
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���t�����p�`�����t�����p�`�ŕ������A�I�������ɍ����̈�𓾂�
	//
	static MINT Divide2GPolygon2D(					// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_OUT_BORDER	(004): �O��
					const	MgGPolyg2D&	i_GPg1,		// (I  ) ���t�����p�`1
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`2
							MgGPolyg2D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �R���� )------------------------------
	//		���p�`1�𑽊p�`2�ŕ������A���p�`2�̎w�葤�i�����܂��͊O���j�̗̈�𓾂�
	//
	static MINT Divide2Polygon3D(					// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_OUT_BORDER	(004): �O��
													//									
					const	MgPolyg3D&	i_Pg1,		// (I  ) ���p�`1
					const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`2
							MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �R���� )------------------------------
	//		���t�����p�`�����t�����p�`�ŕ������A�I�������ɍ����̈�𓾂�
	//
	static MINT Divide2GPolygon3D(					// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_OUT_BORDER	(004): �O��
					const	MgGPolyg3D&	i_GPg1,		// (I  ) ���t�����p�`1
					const	MgGPolyg3D&	i_GPg2,		// (I  ) ���t�����p�`2
							MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���p�`�Ƒ��p�`�̘a�A���A�ς̌��t�����p�`�����߂�
	//
	static MINT Merge2PgtoGPolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_OR			(1): �a
													//			MC_DIFF			(2): ��
													//			MC_AND			(4): ��
					const	MgPolyg2D&	i_Pg1,		// (I  ) ���p�`1
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`2
							MgGPolyg2D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���p�`�ƌ��t�����p�`�̘a�A���A�ς̌��t�����p�`�����߂�
	//
	static MINT MergePgGPgtoGPolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_OR			(1): �a
													//			MC_DIFF			(2): ��
													//			MC_AND			(4): ��
					const	MgPolyg2D&	i_Pg1,		// (I  ) ���p�`1
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`2
							MgGPolyg2D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���t�����p�`�Ƒ��p�`�̘a�A���A�ς̌��t�����p�`�����߂�
	//
	static MINT MergeGPgPgtoGPolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_OR			(1): �a
													//			MC_DIFF			(2): ��
													//			MC_AND			(4): ��
					const	MgGPolyg2D&	i_GPg1,		// (I  ) ���t�����p�`1
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`2
							MgGPolyg2D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���t�����p�`�ƌ��t�����p�`�̘a�A���A�ς̌��t�����p�`�����߂�
	//
	static MINT Merge2GPgtoGPolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(x01): �����Ȃ�
													//			MC_INT			(x02): ��������
													//			MC_MATCH		(x10): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_OR			(1): �a
													//			MC_DIFF			(2): ��
													//			MC_AND			(4): ��
					const	MgGPolyg2D&	i_GPg1,		// (I  ) ���t�����p�`1
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`2
							MgGPolyg2D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �R���� )------------------------------
	//		���p�`�Ƒ��p�`�̘a�A���A�ς̌��t�����p�`�����߂�
	//
	static MINT Merge2PgtoGPolygon3D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_OR			(1): �a
													//			MC_DIFF			(2): ��
													//			MC_AND			(4): ��
					const	MgPolyg3D&	i_Pg1,		// (I  ) ���p�`1
					const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`2
							MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �R���� )------------------------------
	//		���p�`�ƌ��t�����p�`�̘a�A���A�ς̌��t�����p�`�����߂�
	//
	static MINT MergePgGPgtoGPolygon3D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_OR			(1): �a
													//			MC_DIFF			(2): ��
													//			MC_AND			(4): ��
					const	MgPolyg3D&	i_Pg1,		// (I  ) ���p�`1
					const	MgGPolyg3D&	i_GPg2,		// (I  ) ���t�����p�`2
							MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �R���� )------------------------------
	//		���t�����p�`�Ƒ��p�`�̘a�A���A�ς̌��t�����p�`�����߂�
	//
	static MINT MergeGPgPgtoGPolygon3D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_OR			(1): �a
													//			MC_DIFF			(2): ��
													//			MC_AND			(4): ��
					const	MgGPolyg3D&	i_GPg1,		// (I  ) ���t�����p�`1
					const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`2
							MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �R���� )------------------------------
	//		���t�����p�`�ƌ��t�����p�`�̘a�A���A�ς̌��t�����p�`�����߂�
	//
	static MINT Merge2GPgtoGPolygon3D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_OR			(1): �a
													//			MC_DIFF			(2): ��
													//			MC_AND			(4): ��
					const	MgGPolyg3D&	i_GPg1,		// (I  ) ���t�����p�`1
					const	MgGPolyg3D&	i_GPg2,		// (I  ) ���t�����p�`2
							MgGPolyg3D*	o_pGPgo		// (  O) ���t�����p�`3
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���p�`�̕Ӂi�����j�𑼂̑��p�`�ŕ������A�w�肵�����̐������c��
	//								���������p�`�̕ӏ�ɂ���ꍇ�́A
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
	//				(3) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideAdd2Polygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel1,		// (I  ) �I������1�@���p�`1�̐������c������
													//			MC_IN_BORDER	(001):	���p�`2�̗̈�̓���
													//			MC_ON_BORDER	(002):  ���p�`2�̕ӏ�
													//			MC_OUT_BORDER	(004):	���p�`2�̗̈�̊O��
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
													//			MC_REV_DIR		(0200):	�ӏ�t����
					const	bool		i_fRev,		// (I  ) ���]�t���O	
													//		 true: �����̕����𔽓]����
					const	MgPolyg2D&	i_Pg1,		// (I  ) ���p�`1
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`2
							MgGLine2D*	io_pGLno,	// (I O) �����Q
							MgGPolyg2D*	io_pGPgo	// (I O) ���t�����p�`
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���p�`�̕Ӂi�����j�����t�����p�`�ŕ������A�w�肵�����̐������c��
	//								���������p�`�̕ӏ�ɂ���ꍇ�́A
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
	//				(3) ���̑��̏ꍇ�͎̂Ă�
	//
	
	static MINT DivideAddPolygonGPolygon2D(			// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel1,		// (I  ) �I������1�@���p�`1�̐������c������
													//			MC_IN_BORDER	(001): ���p�`2�̗̈�̓���
													//			MC_ON_BORDER	(002): ���p�`2�̕ӏ�
													//			MC_OUT_BORDER	(004): ���p�`2�̗̈�̊O��
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
													//			MC_REV_DIR		(0200):	�ӏ�t����
					const	bool		i_fRev,		// (I  ) ���]�t���O	
													//		 true: �����̕����𔽓]����
					const	MgPolyg2D&	i_Pg1,		// (I  ) ���p�`1
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`2
							MgGLine2D*	io_pGLno,	// (I O) �����Q
							MgGPolyg2D*	io_pGPgo	// (I O) ���t�����p�`
					);
	
	// ---------------------( �Q���� )------------------------------
	//		GLine1�̕������l�����Đڑ����̈�Q���쐬����
	//
	
	#define	MX_AREA_BY_PT	20						// �P�_�̎���̍ő�̈搔
	
	static void MakeGPolygonInGLine2D(
					const	MgGLine2D&	i_GLn1,		// (I  ) �������������������Q
							MgGPolyg2D*	o_GPg3		// (  O) �̈�Q
					);
	
	// ---------------------( �Q���� )------------------------------
	//		GLine1�̕������l�����Ē�����������GLine2��ǉ����̈�Q���쐬����
	//
	static void MakeGPolygonIn2GLine2D(
					const	MgGLine2D&	i_GLn1,		// (I  ) �������������������Q
					const	MgGLine2D&	i_GLn2,		// (I  ) �s���m�ȕ����̐����Q
							MgGPolyg2D*	o_GPg3		// (  O) �̈�Q
					);
	
	// ---------------------( �Q���� )------------------------------
	//		�w��������n�܂�����Q�̐�������_�ŕ�����Ɍ������čŏ��̑��p�`���쐬����
	//
	static bool MakeGPolygonFromLineInGLine2D(		// (  O) �X�e�C�^�X�@true: ����쐬�@false: �쐬�s��
					const	MgLine2D&	i_Ln1,		// (I  ) �w�����
					const	MgGLine2D&	i_GLn2,		// (I  ) ������������Q
							MgPolyg2D*	o_Pg3		// (  O) �̈�
					);
	
//	// ---------------------( �Q���� )------------------------------
//	//		�w��������n�܂�����Q�̐������������čŏ��̑��p�`���쐬����
//	//
//	static bool	MgMakeGPolygonFromLineInGLine2D(	// (  O) �X�e�C�^�X�@true: ����쐬�@false: �쐬�s��
//					const	MgLine2D&	i_Ln1,		// (I  ) �w�����
//							MgGLine2D*	io_pGLn2,	// (I O) ������������Q
//							MINT*		io_pnHk,	// (I O) ������������̒��̐��������������������i�擪�������\���j
//							MgPolyg2D*	o_pPg3		// (  O) �̈�
//					);
	
	// ---------------------( �Q���� )------------------------------
	//		���t�����p�`�𑽊p�`�Ɍ�������
	//
	static void ConnectGPolygontoPolygon2D(			//
					const	MgGPolyg2D&	i_GpgI,		// (I  ) ���t�����p�`
							MgPolyg2D*	o_pgO		// (  O) ������̑��p�`
					);
	
	// ---------------------( �R���� )------------------------------
	//		���t�����p�`�𑽊p�`�Ɍ�������
	//
	static void ConnectGPolygontoPolygon3D(			//
					const	MgGPolyg3D&	i_GPgI,		// (I  ) ���t�����p�`
					const	MgVect3D&	i_VuH,		// (I  ) �@������
							MgPolyg3D*	o_pPgO		// (  O) ������̑��p�`
					);

	//===========================================================================
	//		�����@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	//
	//		��������_�܂ł̐��������t�����������߂�B
	//
	static MREAL DistPointULine2D(					// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgULine2D&	i_ULn2		// (I  ) ����2
					);
	
	//	------------------------
	//		��������_�܂ł̐��������t�����������߂�B	(�����Ɠ��l)
	
	//
	static MREAL DistPointLine2D(					// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
													//	�����̒�����0�̏ꍇ�͓_��������̎n�_�܂ł̋���
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgLine2D&	i_Ln2		// (I  ) ����2
					);
	
	// ---------------------( �R���� )------------------------------
	//		��������_�܂ł̋��������߂�B
	//
	static MREAL DistPointULine3D(					// (  O) ��������_�܂ł̋���
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgULine3D&	i_ULn2		// (I  ) ����2
					);

	//
	//		��������_�܂ł̋��������߂�B(�����Ɠ��l)
	//
	static MREAL DistPointLine3D(					// (  O) ��������_�܂ł̋���
													//	�����̒�����0�̏ꍇ�͓_��������̎n�_�܂ł̋���
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgLine3D&	i_Ln2		// (I  ) ����2
					);
	
	// ---------------------( �R���� )------------------------------
	//		��������_�܂ł̐��������t�����������߂�B
	//
	static MREAL DistPointULineVect3D(				// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgULine3D&	i_ULn2,		// (I  ) ����2
					const	MgVect3D&	i_vn		// (I  ) �_�ƒ����ɒ�������P�ʃx�N�g��
					);

	//
	//		��������_�܂ł̐��������t�����������߂�B(�����Ɠ��l)
	//
	static MREAL DistPointLine3DWH(					// (  O) ��������_�܂ł̋��� >0:���� <0:�E��
													//		 �����̒�����0�̏ꍇ�͓_��������̎n�_�܂ł̋���
													//		 �����̒�����0�̏ꍇ�͓_��������̎n�_�܂ł̋���
				const	MgPoint3D&	i_p1,			// (I  ) �_1
				const	MgLine3D&	i_Ln2,			// (I  ) ����2
				const	MgVect3D&	i_vn			// (I  ) �_�ƒ����ɒ�������P�ʃx�N�g��
				);
	
	// ---------------------( �R���� )------------------------------
	//		���ʂ���_�܂ł̐��������t�����������߂�B
	//
	static MREAL DistPointPln3D(					// (  O) �_���畽�ʂ܂ł̋��� >0:�\���i���ʂ̒P�ʃx�N�g���������j<0:����
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgPlane3D&	i_Pln2		// (I  ) ����2
					);

	// ---------------------( �Q���� )------------------------------
	//		����������ŕ�������
	//		(�����P�̒[���ł̌����͌��������Ƃ���������)
	//
	static MINT Divide2Line2D(						// (  O) �X�e�C�^�X
													//			MC_NINT			(0): ��������
													//			MC_INT			(1): ��������
					const	MgLine2D&	i_Ln1, 		// (I  ) �����Ώې���
					const	MgLine2D&	i_Ln2, 		// (I  ) ��������
							MgGLine2D*	o_pGLn3		// (  O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		�����𒼐��ŕ�������
	//		(�����P�̒[���ł̌����͌��������Ƃ���������)
	//
	static MINT DivideLineULine2D(					// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
					const	MgLine2D&	i_Ln1, 		// (I  ) �����Ώې���
					const	MgULine2D&	i_ULn2,		// (I  ) ��������
							MgGLine2D*	o_pGLn3		// (  O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		�����𒼐��ŕ����������̑I�𑤂̐����𕪊���̐����Q�ɒǉ�����
	//		(�����̒[���ł̌����͌����Ȃ��Ƃ���)
	//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
	//			���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
	//				(3) ���̑��̏ꍇ�͎̂Ă�
	//		//			(1) �I�������������̍���|������̏ꍇ�́A��������̎��c��
	//		//			(2) �I�������������̉E��|������̏ꍇ�́A�t�����̎��c��
	//		//			(3) ���̑��̏ꍇ�͎̂Ă�
	//
	// 		sels = MC_LEFT | MC_ON_BORDER | MC_SAME_DIR;
	
	//
	static MINT DivideAddLineULine2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_LEFT			(010): �����̍���
													//			MC_ON_LINE		(020): ������
													//			MC_RIGHT		(040): �����̉E��
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
													//			MC_REV_DIR		(0200):	�ӏ�t����
					const	MgLine2D&	i_Ln1, 		// (I  ) �����Ώې���
					const	MgULine2D&	i_ULn2,		// (I  ) ��������
							MgGLine2D*	o_pGLn3		// (I O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		����������Q�Ƃ̌�_�ŕ�������
	//		(�����̒[���ł̌����͌����Ȃ��Ƃ���)
	//
	static MINT DivideLineGLine2D(					// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
					const	MgLine2D&	i_Ln1, 		// (I  ) �����Ώې���
					const	MgGLine2D&	i_GLn2,		// (I  ) ���������Q
							MgGLine2D*	o_pGLn3		// (  O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		�����Q����_�ŕ�������������͏�����{�ɂ���i�t�����������j
	//		��������łQ�������d�Ȃ�ꍇ�͒[�_�ŕ�������
	//
	static MINT DivideGLine2D(						// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
					const	MgGLine2D&	i_GLn1,		// (I  ) �����Q
							MgGLine2D*	o_pGLn2		// (  O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		�����𑽊p�`�ŕ������A�I�������ɍ��������Q�����o��
	//			�I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
	//			���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideULinePolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
					const	MgULine2D&	i_ULn1,		// (I  ) ����
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`
							MgGLine2D*	o_pGLn3		// (  O) ������̐����Q
					);
	
	// ---------------------( �Q���� )------------------------------
	//		�����𑽊p�`�ŕ������A�I�������ɍ��������𕪊���̐����Q�ɒǉ�����
	//			�I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
	//			���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideAddULinePolygon2D(			// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
					const	MgULine2D&	i_ULn1,		// (I  ) ����
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`
							MgGLine2D*	io_pGLn3	// (I O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		�����𑽊p�`�ŕ������A�I�������ɍ��������Q�𓾂�
	//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
	//			���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
	//				(3) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideLinePolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_OUT_BORDER	(004): �O��
													//			MC_FOR_POLYGON	(0100): ���p�`�쐬�p
					const	MgLine2D&	i_Ln1,		// (I  ) ����
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`
							MgGLine2D*	o_pGLn3		// (  O) ������̐����Q
					);
	
	// ---------------------( �Q���� )------------------------------
	//		�����𑽊p�`�ŕ������A�I�������ɍ��������𕪊���̐����Q�ɒǉ�����
	//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
	//			���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
	//				(3) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideAddLinePolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_OUT_BORDER	(004): �O��
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
													//			MC_REV_DIR		(0200):	�ӏ�t����
					const	MgLine2D&	i_Ln1,		// (I  ) ����
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`
							MgGLine2D*	o_pGLn3		// (I O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		���������t�����p�`�ŕ������A�I�������ɍ��������Q�𓾂�
	//			�I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
	//			���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideULineGPolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �I�������ɍ��������Ȃ�
													//			MC_INT			(1): �I�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
					const	MgULine2D&	i_ULn1,		// (I  ) ����
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`
							MgGLine2D*	o_pGLn3		// (  O) ������̐����Q
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���������t�����p�`�ŕ������A�I�������ɍ��������𕪊���̐����Q�ɒǉ�����
	//			�I�������Ɂu�ӏ㓯������v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideAddULineGPolygon2D(			// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �I�������ɍ��������Ȃ�
													//			MC_INT			(1): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
					const	MgULine2D&	i_ULn1,		// (I  ) ����
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`
							MgGLine2D*	o_pGLn3		// (I O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		���������t�����p�`�ŕ������A�I�������ɍ��������Q�𓾂�
	//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
	//			���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
	//				(3) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideLineGPolygon2D(				// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_OUT_BORDER	(004): �O��
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
													//			MC_REV_DIR		(0200):	�ӏ�t����
					const	MgLine2D&	i_Ln1,		// (I  ) ����
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`
							MgGLine2D*	o_pGLn3		// (  O) ������̐����Q
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���������t�����p�`�ŕ������A�I�������ɍ��������𕪊���̐����Q�ɒǉ�����
	//			�I�������Ɂu�ӏ㓯������܂��͕ӏ�t�����v���ݒ肳��Ă���A������̐��������t�����p�`�̕ӏ�ɂ���ꍇ�ɂ́A
	//			���̂悤�ɑI������
	//				(1) �I���������ӏ㓯������̏ꍇ�́A��������̎��c��
	//				(2) �I���������ӏ�t�����̏ꍇ�́A�t�����̎��c��
	//				(3) ���̑��̏ꍇ�͎̂Ă�
	//
	static MINT DivideAddLineGPolygon2D(			// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
													//			MC_OUT_BORDER	(004): �O��
													//			MC_SAME_DIR		(0100):	�ӏ㓯�����
													//			MC_REV_DIR		(0200):	�ӏ�t����
					const	MgLine2D&	i_Ln1,		// (I  ) ����
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`
							MgGLine2D*	io_pGLn3	// (I O) ������̐����Q
					);

	// ---------------------( �Q���� )------------------------------
	//		�d�Ȃ��Ă���������폜����{�ɂ��� (�t�������܂�)				<�v����UP?>
	//
	static void MergeGLine2D(
							MgGLine2D*	io_pGln		// (I O) �����Q
					);
	
	//===========================================================================
	// ---------------------( �R���� )------------------------------
	//		�����𑽊p�`�ŕ������A�I�������ɍ��������Q�����o��
	//
	static MINT DivideULinePolygon3D(				// (  O) �X�e�C�^�X
													//		 MC_NINT		(0): �����Ȃ�
													//		 MC_INT			(1): ��������
							MINT		i_Sel,		// (I  ) �I������
													//		 MC_IN_BORDER	(001): ����
													//		 MC_ON_BORDER	(002): �ӏ�
					const	MgULine3D&	i_ULn1,		// (I  ) ����
					const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`
							MgGLine3D*	o_pGLn3		// (  O) ������̐����Q
					);

	//---------------------( �R���� )------------------------------
	//		�����𑽊p�`�ŕ������A���������ɍ��������𕪊���̐����Q�ɒǉ�����
	//
	static MINT DivideAddULinePolygon3D(			// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
													//			MC_MATCH		(4): �I�������ɍ�����������
													//	��	 (STS == MC_NINT):				���������őI�������ɍ��������Ȃ� 
													//		 (STS == (MC_NINT | MC_MATCH)):	���������ł��邪�I�������ɍ���
													//		 (STS == (MC_INT | MC_MATCH)):	��������őI�������ɍ�����������
							MINT		i_Sel,		// (I  ) �I������
													//			MC_IN_BORDER	(001): ����
													//			MC_ON_BORDER	(002): �ӏ�
					const	MgULine3D&	i_ULn1,		// (I  ) ����
					const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`
							MgGLine3D*	io_pGLn3	// (I O) ������̐����Q
					);

	//// ---------------------( �Q���� )------------------------------
	////	�Q�̐����Ԃ̊p�x�̑召�ɏ]�����lCC�����߂�
	////	[p0����p1�Ɍ���������]����[p1����p2�Ɍ���������]�ւ̊p�x�ɂ��
	////		0.: -0�K, 0.5: 90�K, 1.: 180�K, 1.5: -90�K, <2.: <360(-)�K
	////
	//static MREAL AngSSa3Point2D( 
	//				const	MgPoint2D&	i_p0,
	//				const	MgPoint2D&	i_p1,
	//				const	MgPoint2D&	i_p2
	//				)
	////
	//// ---------------------( �R���� )------------------------------
	////	�Q�̐����Ԃ̊p�x�̑召�ɏ]�����lCC�����߂�
	////	����pln3���[p0����p1�Ɍ���������]����[p1����p2�Ɍ���������]�ւ̊p�x�ɂ��
	////		0.: -0�K, 0.5: 90�K, 1.: 180�K, 1.5: -90�K, <2.: <360(-)�K
	////
	//static MREAL AngSSa3Point3D( 
	//				const	MgPoint3D&	i_P0,
	//				const	MgPoint3D&	i_P1,
	//				const	MgPoint3D&	i_P2,
	//				const	MgPlane3D&	i_Pln3
	//				)
	////
	//// ---------------------( �Q���� )------------------------------
	////	�Q�̐����Ԃ̊p�x�̑召�ɏ]�����lCC�����߂�
	////	[p0����p1�Ɍ���������]����[p1����p2�Ɍ���������]�ւ̊p�x�ɂ��
	////		>-1.: >-180�K, -0.5: -90�K, 0.: -0�K, 0.5: 90�K, 1.: 180�K
	////
	//static MREAL AngSSb3Point2D( 
	//				const	MgPoint2D&	i_p0,
	//				const	MgPoint2D&	i_p1,
	//				const	MgPoint2D&	i_p2
	//				)
	////
	//// ---------------------( �R���� )------------------------------
	////	�Q�̐����Ԃ̊p�x�̑召�ɏ]�����lCC�����߂�
	////	����pln3���[p0����p1�Ɍ���������]����[p1����p2�Ɍ���������]�ւ̊p�x�ɂ��
	////		>-1.: >-180�K, -0.5: -90�K, 0.: -0�K, 0.5: 90�K, 1.: 180�K
	////
	//static MREAL AngSSb3Point3D( 
	//				const	MgPoint3D&	i_P0,
	//				const	MgPoint3D&	i_P1,
	//				const	MgPoint3D&	i_P2,
	//				const	MgPlane3D&	i_Pln3
	//				)
	//
	// ---------------------( �Q���� )------------------------------
	//	�I���R�p�`�������\�����ׂ�
	//			 0: �ʐς�0
	//			 1: �����\
	//			-1: �O�p�`���ɑ��̓����_�����蕪���s��(�R�p�`�̕ӏ�͑ΏۊO)
	//
	static MINT ChkDivTriPtPolygon2D( 
							MgPoint2D*	i_p3,		// �I���R�p�`
					const	MgPolyg2D&	i_Pgw,		// �������p�`
					const	MgGInt&		i_iGIrisumi	// �����_���X�g
					);
	
	// ---------------------( �R���� )------------------------------
	//	�I���R�p�`�������\�����ׂ�
	//			 0: �ʐς�0
	//			 1: �����\
	//			-1: �O�p�`��܂��͓��ɑ��̓����_�����蕪���s��(�R�p�`�̕ӏ�͑ΏۊO)
	//
	static MINT ChkDivTriPtPolygon3D( 
							MgPoint3D*	i_p3,		// �I���R�p�`
					const	MgPolyg3D&	i_Pgw,		// �������p�`
					const	MgGInt&		i_iGIrisumi,// �����_���X�g
					const	MgVect3D&	i_VuPg1		// ���p�`�̖@������
					);
	
	// ---------------------( �Q���� )------------------------------
	//		���p�`���R�p�`�ɕ�������
	//
	static MINT DivideTriPolygon2D(					// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
					const	MgPolyg2D&	i_Pg1,		// (I  ) ���p�`
							MgGPolyg2D*	o_pGPg2		// (  O) ������̂R�p�`�Q
					);
	
	//
	// ---------------------( �R���� )------------------------------
	//		���p�`���R�p�`�ɕ�������
	//
	static MINT DivideTriPolygon3D(					// (  O) �X�e�C�^�X
													//			MC_NINT			(0): �����Ȃ�
													//			MC_INT			(1): ��������
					const	MgPolyg3D&	i_Pg1,		// (I  ) ���p�`
					const	MgVect3D&	i_VuPg1,	// (I  ) ���p�`�̖@������
							MgGPolyg3D*	o_pGPg2		// (  O) ������̂R�p�`�Q
					);
	
	//===========================================================================
	//		�����ƒ����̌�_�@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	//�@�Q�{�̒����̌�_�����߂�B
	//
	static MINT Intr2ULine2D(						// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgULine2D&	i_ULn1,		// (I  ) ����1
					const	MgULine2D&	i_ULn2,		// (I  ) ����2
							MgPoint2D*	o_ppo		// (  O) �Q������_
					);
	
	// ---------------------( �Q���� )------------------------------
	//�@�����Ɛ����̌�_�����߂�B
	//�@�d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�B
	//
	static MINT IntrULineLine2D(					// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgULine2D&	i_ULn1,		// (I  ) ����1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MgPoint2D*	o_ppo		// (  O) �Q������_
					);
	
	// ---------------------( �Q���� )------------------------------
	//�@�����ƒ����̌�_�����߂�B
	//�@�d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�B
	//
	static inline MINT IntrLineULine2D(				// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgULine2D&	i_ULn2,		// (I  ) ����2
							MgPoint2D*	o_ppo		// (  O) �Q������_
					)
	{
		return IntrULineLine2D( i_ULn2, i_Ln1, o_ppo);
	}
	
	// ---------------------( �Q���� )------------------------------
	//�@�����Ɛ����̌�_�����߂�B
	//�@�Q�������d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�B
	//  �Q�������d�Ȃ�Ȃ������I�ɒ[���Őڍ����Ă���ꍇ�͂��̐ڍ��_����_�B
	static MINT Intr2Line2D(						// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//  MC_CONNECTION(4) �ڑ�	 �i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MgPoint2D*	o_ppo		// (  O) �Q������_
					);

	// ---------------------( �Q���� )------------------------------
	//	�����P�ƒ����Q�Ƃ̌�_�����߁A�_�Q�ɒǉ�����B
	//�@�d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�B
	//
	static MINT IntrAddLineULine2D(					// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgULine2D&	i_ULn2,		// (I  ) ����2
							MgGPoint2D*	io_pGPt3	// (I O) ��_��ǉ�����_�Q
													//		 �ǉ���_��(0:�����Ȃ��A�����̒[���Ō����A�܂��͏d�Ȃ�
													//					1:��������i�����̒[���ł̌����͊܂܂�))
					);
	
	// ---------------------( �Q���� )------------------------------
	//	�����P�Ɛ����Q�Ƃ̌�_�Əd�Ȃ蕔���̒[�_�����߁A�_�Q�ɒǉ�����B
	//  ��_�܂��͏d�Ȃ蕔���̒[�_�������P�̒[�_�ł���ꍇ�́A���̓_��ΏۊO�Ƃ���B
	//
	static MINT IntrAdd2Line2D(						// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
													//  MC_REP	    (2)	��������i�d�Ȃ�j
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MgGPoint2D*	io_pGPt3	// (I O) ��_��ǉ���������Q
													// 		 �ǉ���_��(0:���������܂��͐���1������2�̓����ɂ���d�Ȃ�(�[�����m�̏d�Ȃ�܂�) |
													//					1:����2�ƌ����i����2�̒[���ł̌������܂ށj�܂��͈ꕔ�d�Ȃ�(�В[�d�Ȃ�܂�) |
													//					2:����2������1�̓����ɂ���d�Ȃ�(�[�����m�̏d�Ȃ�Ȃ�)) 
					);

	// ---------------------( �Q���� )------------------------------
	//	�����P�Ɛ����Q�Ƃ̌�_�܂��͏d�Ȃ蕔���̒[�_�����߁A�_�Q�ɒǉ�����B
	//
	static MINT IntrAddULineLine2D(					// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
													//  MC_REP	    (2)	��������i�d�Ȃ�j
					const	MgULine2D&	i_ULn1,		// (I  ) ����1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MgGPoint2D*	io_pGPt3	// (I O) ��_��ǉ���������Q
													// 		 �ǉ���_��(0:�������� |
													//					1:����1�Ɛ���2�������i����2�̒[���ł̌������܂ށj|
													//					2:����1�Ɛ���2���d�Ȃ� 
					);

	// ---------------------( �R���� )------------------------------
	//	�Q�{�̒����̌�_�����߂�B
	//
	static MINT Intr2ULine3D(						// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_TWIST	(-2) �����Ȃ��i�˂���j
													//	MC_INT      (1)	��������
					const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgULine3D&	i_ULn2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_
					);

	// ---------------------( �R���� )------------------------------
	//�@�����Ɛ����̌�_�����߂�B
	//
	static MINT IntrULineLine3D(					// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_TWIST    (-2) �����Ȃ��i�˂���j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_
					);
	
	// ---------------------( �R���� )------------------------------
	//�@�����ƒ����̌�_�����߂�B
	//
	static inline MINT IntrLineULine3D(				// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_TWIST    (-2) �����Ȃ��i�˂���j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgULine3D&	i_ULn2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_
					)
	{
		return IntrULineLine3D( i_ULn2, i_Ln1, o_ppo);
	}
	
	// ---------------------( �R���� )------------------------------
	//�@�����Ɛ����̌�_�����߂�B
	//�@�Q�������d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�B
	//  �Q�������d�Ȃ�Ȃ������I�ɒ[���Őڍ����Ă���ꍇ�͂��̐ڍ��_������_�B
	//
	static MINT Intr2Line3D(						// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//  MC_CONNECTION(4) �ڑ�	 �i���s�j
													//	MC_TWIST    (-2) �����Ȃ��i�˂���j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_
					);
	
	//===========================================================================
	//		���ʂƒ����̌�_�@�`�󉉎Z
	//
	// ---------------------( �R���� )------------------------------
	//
	//	���ʂƒ����̌�_�����߂�B
	//
	static MINT IntrPlnULine3D(						// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_INT      (1)	��������
					const	MgPlane3D&	i_Pln1,		// (I  ) ����1
					const	MgULine3D&	i_ULn2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_(�_�̕W���`��)
					);

	// ---------------------( �R���� )------------------------------
	//	���ʂƐ����̌�_�����߂�B
	//
	static MINT IntrPlnLine3D(						// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgPlane3D&	i_Pln1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_(�_�̕W���`��)
					);
	
	// ---------------------( �R���� )------------------------------
	//	�����ƕ��ʂ̌�_�����߂�B
	//
	static inline MINT IntrULinePln3D(				// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_INT      (1)	��������
					const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgPlane3D&	i_Pln2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_(�_�̕W���`��)
					)
	{
		return IntrPlnULine3D( i_Pln2, i_ULn1, o_ppo);
	}
	
	// ---------------------( �R���� )------------------------------
	//	�����ƕ��ʂ̌�_�����߂�B
	//
	static inline MINT IntrLinePln3D(				// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1) �����Ȃ��i���s�j
													//	MC_NINT	    (0)	�����Ȃ�
													//	MC_INT      (1)	��������
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgPlane3D&	i_Pln2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_(�_�̕W���`��)
					)
	{
		return IntrPlnLine3D( i_Pln2, i_Ln1, o_ppo);
	}
	
	//===========================================================================
	//		���ʂƕ��ʂ̌���@�`�󉉎Z
	//
	// ---------------------( �R���� )------------------------------
	//
	//	���ʂƕ��ʂ̌�������߂�B
	//
	static MINT Intr2Pln3D(							// (  O) �X�e�C�^�X
													//	MC_PARALLEL (-1)	�����Ȃ��i���s�j
													//	MC_INT		(1)		��������
					const	MgPlane3D&	i_Pln1,		// (I  ) ����1
					const	MgPlane3D&	i_Pln2,		// (I  ) ����2
							MgULine3D*	o_pULn3		// (  O) ����3
					);


	//===========================================================================
	//		�`�󉉎Z
	//
	//	-------------------------�Q�c�k�h�m�d�E�o�n�h�m�s----------------------
	//
	// ---------------------( �Q���� )------------------------------
	//		�_���璼���ւ̐����̑��ʒu�����߂�
	static inline void PerpULinePoint2D(
					const	MgULine2D&	i_ULn1,		// (I  ) ����1
					const	MgPoint2D&	i_p2,		// (I  ) �_2
							MgPoint2D*	o_ppo		// (  O) �_���璼���ւ̐����̑�
					)
	{
		MREAL		pa1;							//	����1�̎n�_���琂���̑��܂ł̋���
	//
		pa1 = ( i_p2 - i_ULn1.p) * i_ULn1.v;				//	cos��v12v2
		*o_ppo = i_ULn1.p + i_ULn1.v * pa1;
	}
	
	// ---------------------( �Q���� )------------------------------
	//		�_��������ւ̐����̑��ʒu�����߂�
	static inline MINT PerpLinePoint2D(				// (  O) �X�e�C�^�X(=MC_ON_LINE	:������,
													//					=0			:�����͈͊O)
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgPoint2D&	i_p2,		// (I  ) �_2
							MgPoint2D*	o_ppo		// (  O) �_���璼���ւ̐����̑�
					)
	{
		MINT		ist;
		MgVect2D	vd1, vd2;
		MREAL		ss, se;
	
		vd1 = i_Ln1.p[1] - i_Ln1.p[0];
		vd2 = RotL90Vect2D(vd1);
	
		SVal( i_Ln1.p[0], i_Ln1.p[1], i_p2, vd2, &ss, &se);
	
		*o_ppo = i_Ln1.p[0] + (vd1 * (ss / (ss - se)));					//	��_
	
		if (ss * se < 0 ||											//	������
			*o_ppo == i_Ln1.p[0] || *o_ppo == i_Ln1.p[1]) ist = MC_ON_LINE;
		else ist =  0;												//	�����̊O
		return ist;
	}
	
	// ---------------------( �Q���� )------------------------------
	//		�_���璼���ւ̐����̑��ʒu�����߂�
	static inline void	MgPerpPointULine2D(			// (  O) �X�e�C�^�X
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgULine2D&	i_ULn2,		// (I  ) ����2
							MgPoint2D*	o_ppo		// (  O) �Q������_(�_�̕W���`��)
			)
	{
		PerpULinePoint2D( i_ULn2, i_p1, o_ppo);
	}
	
	// ---------------------( �Q���� )------------------------------
	//		�_��������ւ̐����̑��ʒu�����߂�
	static inline MINT PerpPointLine2D(				// (  O) �X�e�C�^�X(=MC_ON_LINE	:������,
													//					=0			:�����͈͊O)
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MgPoint2D*	o_ppo		// (  O) �Q������_(�_�̕W���`��)
			)
	{
		return PerpLinePoint2D( i_Ln2, i_p1, o_ppo);
	}
	
	// ---------------------( �R���� )------------------------------
	//		�_���璼���ւ̐����̑��ʒu�����߂�
	static inline void PerpULinePoint3D(
					const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgPoint3D&	i_p2,		// (I  ) �_2
							MgPoint3D*	o_ppo		// (  O) �_���璼���ւ̐����̑�
					)
	{
		MREAL	pa1;								//	����1�̎n�_���琂���̑��܂ł̋���
	//
		pa1 = ( i_p2 - i_ULn1.p) * i_ULn1.v;					//	cos��v12v2
		*o_ppo = i_ULn1.p + i_ULn1.v * pa1;
	}
	
	// ---------------------( �R���� )------------------------------
	//		�_��������ւ̐����̑��ʒu�����߂�
	static inline MINT	PerpLinePoint3D(			// (  O) �X�e�C�^�X(=MC_ON_LINE	:������,
													//					=0			:�����͈͊O)
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgPoint3D&	i_p2,		// (I  ) �_2
							MgPoint3D*	o_ppo		// (  O) �R������_(�_�̕W���`��)
					)
	{
		MINT		ist;
		MgVect3D	vd1, vd2;
		MREAL		ss, se;
		MREAL		d;
	
		vd1 = i_Ln1.p[1] - i_Ln1.p[0];
	
		d  = i_p2 * vd1;
		ss = ( i_Ln1.p[0] * vd1) - d;
		se = ( i_Ln1.p[1] * vd1) - d;
	
		*o_ppo = i_Ln1.p[0] + (vd1 * (ss / (ss - se)));				//	��_
	
		if (ss * se < 0 ||											//	������
			*o_ppo == i_Ln1.p[0] || *o_ppo == i_Ln1.p[1])
			ist = MC_ON_LINE;
		else ist = 0;												//	�����̊O
	
		return ist;
	}

	// ---------------------( �R���� )------------------------------
	//		�_��������ւ̐����̑��ʒu�����߂�
	static inline MINT	MgPerpPointLine3D(			// (  O) �X�e�C�^�X(=MC_ON_LINE	:������,
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_(�_�̕W���`��)
					)
	{
		return PerpLinePoint3D( i_Ln2, i_p1, o_ppo);
	}
	
	// ---------------------( �R���� )------------------------------
	//		�_���璼���ւ̐����̑��ʒu�����߂�
	static inline void	MgPerpPointULine3D(
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgULine3D&	i_ULn2,		// (I  ) ����2
							MgPoint3D*	o_ppo		// (  O) �R������_(�_�̕W���`��)
					)
	{
		PerpULinePoint3D( i_ULn2, i_p1, o_ppo);
	}
	
	//	-------------------------�R�c�ʁE�o�n�h�m�s----------------------
	//
	// ---------------------( �R���� )------------------------------
	//		�_����ʂւ̐����̑��ʒu�����߂�
	//
	static inline void PerpPlnPoint3D(
					const	MgPlane3D&	i_Pln1,		// (I  ) ��1
					const	MgPoint3D&	i_p2,		// (I  ) �_2
							MgPoint3D*	o_ppo		// (  O) �_���璼���ւ̐����̑�
					)
	{
		MREAL	pa1;								//	�_2���琂���̑��܂ł̋���
	//
		pa1 = ( i_p2 * i_Pln1.v) + i_Pln1.d;
		*o_ppo = i_p2 - i_Pln1.v * pa1;
	}
	
	// ---------------------( �R���� )------------------------------
	//		�_����ʂւ̐����̑��ʒu�����߂�
	//
	static inline void PerpPointPln3D(
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgPlane3D&	i_Pln2,		// (I  ) ��2
							MgPoint3D*	o_ppo		// (  O) �R������_(�_�̕W���`��)
					)
	{
		PerpPlnPoint3D( i_Pln2, i_p1, o_ppo);
	}

	//===========================================================================
	//		�_�̈ړ��@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	//
	static inline void MovePt2InDirOfVt2(			//
					const	MgPoint2D&	i_p1,		//  (I  ) �ړ��_1
					const	MgVect2D&	i_v2,		//	(I  ) �ړ������������x�N�g��
							MREAL		i_dl,		//	(I  ) �ړ�����
							MgPoint2D*	o_pp3,		//	(  O) �ړ����ꂽ�_3
							MREAL i_Tol = MGPTOL->D	//	(I  ) ���e�덷
					)
	{
		*o_pp3 = i_p1 + i_dl * UnitizeVect2D( i_v2, i_Tol);
	}

	//	------------------------
	static inline void MovePt2AlongULine2D(			//
					const	MgPoint2D&	i_p1,		//  (I  ) �ړ��_1
					const	MgULine2D&	i_ULn2,		//	(I  ) �ړ���������������2
							MREAL		i_dl,		//	(I  ) �ړ�����
							MgPoint2D*	o_pp3		//	(  O) �ړ����ꂽ�_3
					)
	{
		*o_pp3 = i_p1 + i_dl * i_ULn2.v;
	}

	//	------------------------
	static inline void MovePt2AlongLine2D(				//
					const	MgPoint2D&	i_p1,		//  (I  ) �ړ��_1
					const	MgLine2D&	i_Ln2,		//	(I  ) �ړ���������������2
							MREAL		i_dl,		//	(I  ) �ړ�����
							MgPoint2D*	o_pp3,		//	(  O) �ړ����ꂽ�_3
							MREAL i_Tol = MGPTOL->D	//	(I  ) ���e�덷
					)
	{
		MgVect2D	vd, vn;
	
		vd = i_Ln2.p[1] - i_Ln2.p[0];
		vn = UnitizeVect2D( vd, i_Tol);
		*o_pp3 = i_p1 + i_dl * vn;
	}

	//
	// ---------------------( �R���� )------------------------------
	//
	static inline void MovePt3InDirOfVt3(			//
					const	MgPoint3D&	i_p1,		//  (I  ) �ړ��_1
					const	MgVect3D&	i_v2,		//	(I  ) �ړ������������x�N�g��
							MREAL		i_dl,		//	(I  ) �ړ�����
							MgPoint3D	*o_pp3,		//	(  O) �ړ����ꂽ�_3
							MREAL i_Tol = MGPTOL->D	//	(I  ) ���e�덷
					)
	{
		*o_pp3 = i_p1 + i_dl * UnitizeVect3D( i_v2, i_Tol);
	}

	//	------------------------
	static inline void MovePt3AlongULine3D(			//	(  O) �X�e�C�^�X
					const	MgPoint3D&	i_p1,		//  (I  ) �ړ��_1
					const	MgULine3D&	i_ULn2,		//	(I  ) �ړ���������������2
							MREAL		i_dl,		//	(I  ) �ړ�����
							MgPoint3D*	o_pp3		//	(  O) �ړ����ꂽ�_3
					)
	{
		*o_pp3 = i_p1 + i_dl * i_ULn2.v;
	}

	//	------------------------
	static inline void MovePt3AlongLine3D(				//	(  O) �X�e�C�^�X
					const	MgPoint3D&	i_p1,		//  (I  ) �ړ��_1
					const	MgLine3D&	i_Ln2,		//	(I  ) �ړ���������������2
							MREAL		i_dl,		//	(I  ) �ړ�����
							MgPoint3D*	o_pp3,		//	(  O) �ړ����ꂽ�_3
							MREAL i_Tol = MGPTOL->D	//	(I  ) ���e�덷
					)
	{
		MgVect3D	vd, vn;
	
		vd = i_Ln2.p[1] - i_Ln2.p[0];
		vn = UnitizeVect3D(vd, i_Tol);
		*o_pp3 = i_p1 + i_dl * vn;
	}

	//===========================================================================
	//		�����̃I�t�Z�b�g�@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	//
	//	�������I�t�Z�b�g����B
	//
	static inline void OffsetULine2D(					//	(  O) �X�e�C�^�X (=1)
					const	MgULine2D&	i_ULn1,		//	(I  ) ����1
							MREAL		i_dl,		//	(I  ) �I�t�Z�b�g��
							MgULine2D* 	o_pULn2		//	(  O) �I�t�Z�b�g���ꂽ����2
					)
	{
	
		o_pULn2->p = i_ULn1.p + i_dl * RotL90Vect2D( i_ULn1.v);
		o_pULn2->v = i_ULn1.v;
	}

	//	------------------------
	static inline void OffsetLine2D(					//	(  O) �X�e�C�^�X
					const	MgLine2D&	i_Ln1,		//	(I  ) ����1
							MREAL		i_dl,		//	(I  ) �I�t�Z�b�g��
							MgLine2D*	o_pLn2,		//	(  O) �I�t�Z�b�g���ꂽ����2
							MREAL i_Tol = MGPTOL->D	//	(I  ) ���e�덷
					)
	{
		MgVect2D	vd, vn;
	
		vd = i_Ln1.p[1] - i_Ln1.p[0];
		vn = UnitizeVect2D( vd, i_Tol);
		o_pLn2->p[0] = i_Ln1.p[0] + i_dl * RotL90Vect2D(vn);
		o_pLn2->p[1] = o_pLn2->p[0] + vd;
	}

	//
	// ---------------------( �R���� )------------------------------
	//
	static inline void OffsetULine3D(					//	(  O) �X�e�C�^�X
					const	MgULine3D&	i_ULn1,		//	(I  ) ����1
					const	MgPlane3D&	i_Pln2,		//	(I  ) ����1����镽��2
							MREAL		i_dl,		//	(I  ) �I�t�Z�b�g��
							MgULine3D*	o_pULn3		//	(  O) �I�t�Z�b�g���ꂽ����3
					)
	{
		o_pULn3->p = i_ULn1.p + i_dl * ( i_Pln2.v ^ i_ULn1.v);
		o_pULn3->v = i_ULn1.v;
	}

	//	------------------------
	static inline void OffsetLine3D(					//	(  O) �X�e�C�^�X
					const	MgLine3D&	i_Ln1,		//	(I  ) ����1
					const	MgPlane3D&	i_Pln2,		//	(I  ) ����1����镽��2
							MREAL		i_dl,		//	(I  ) �I�t�Z�b�g��
							MgLine3D*	o_pLn3,		//	(  O) �I�t�Z�b�g���ꂽ����3
							MREAL i_Tol = MGPTOL->D	//	(I  ) ���e�덷
					)
	{
		MgVect3D	vd, vn;
		//
		vd = i_Ln1.p[1] - i_Ln1.p[0];
		vn = UnitizeVect3D( vd, i_Tol);
		MgVect3D vv = vn ^ i_Pln2.v;
		o_pLn3->p[0] = i_Ln1.p[0] + i_dl * ( i_Pln2.v ^ vn);
		o_pLn3->p[1] = o_pLn3->p[0] + vd;
	}
	
	//===========================================================================
	//		�_�@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	//
	//	�_���_��ɂ��邩�𒲂ׂ�B
	//
	static inline bool On(							// (  O) �X�e�C�^�X
													//			true:	�_��ɂ���
													//			false:	�_��ɂȂ�
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgPoint2D&	i_p2,		// (I  ) �_2
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
	//	return (p1 == p2);
		MgVect2D	V1 = i_p2 - i_p1;
		return ( SqLenVect2D( V1) <= rTol * rTol);
	}
	
	//===========================================================================
	//		�_�@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	//		�_���_��ɂ��邩�𒲂ׂ�B
	//
	static bool	MgChkPointOnPoint2D(				// (  O) �X�e�C�^�X
													//		 true:  �_��ɂ���
													//		 false: �_��ɂȂ�
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgPoint2D&	i_p2,		// (I  ) �_2
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);

	// ---------------------( �R���� )------------------------------
	//
	//	�_���_��ɂ��邩�𒲂ׂ�B
	//
	static inline bool ChkPointOnPoint3D(			// (  O) �X�e�C�^�X
													//			true:	�_��ɂ���
													//			false:	�_��ɂȂ�
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgPoint3D&	i_p2,		// (I  ) �_2
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
	//	return (p1 == p2);
		MgVect3D	V1 = i_p2 - i_p1;
		return ( SqLenVect3D( V1) <= rTol * rTol);
	}
	
	//===========================================================================
	//		�����@�`�󉉎Z
	//
	// ---------------------( �Q���� )------------------------------
	//
	//	�_��������ɂ��邩�𒲂ׂ�B
	//
	static bool ChkPointOnULine2DWS(				// (  O) �X�e�C�^�X
													//		 	true:	������ɂ���
													//		 	false:	������ɂȂ�
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgULine2D&	i_ULn2,		// (I  ) ����2
							MINT*		o_pist,		// (  O) �⏕�X�e�C�^�X
													//			MC_RIGHT			(010): �_�������̉E��
													//			MC_ON_LINE			(020): �_��������
													//			MC_LEFT				(040): �_�������̍���
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);
	
	// ---------------------( �Q���� )------------------------------
	//
	//	�_����������ɂ��邩�𒲂ׂ�B
	//
	static bool ChkPointOnHLine2DWS(				// (  O) �X�e�C�^�X
													//		 	true:	��������ɂ���
													//		 	false:	��������ɂȂ�
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgHLine2D&	i_HLn2,		// (I  ) ������2
							MINT*		o_pist,		// (  O) �⏕�X�e�C�^�X
													//			MC_RIGHT			(010): �_���������̉E��
													//			MC_ON_LINE			(020): �_����������
													//			MC_LEFT				(040): �_���������̍���
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);

	// ---------------------( �Q���� )------------------------------
	//
	//	�_��������ɂ��邩�𒲂ׂ�B
	//
	static bool ChkPointOnLine2DWS(					// (  O) �X�e�C�^�X
													//			true:	������ɂ���
													//			false:	������ɂȂ�
					const	MgPoint2D&	i_p1,		// (I  ) �_1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MINT*		o_pist,		// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
													//		 �X�e�C�^�X1
													//			MC_RIGHT			(010): �_�������̉E��
													//			MC_ON_LINE			(020): �_����������������
													//			MC_LEFT				(040): �_�������̍���
													//		 �X�e�C�^�X2
													//			MC_ON_PS			(001): �_�������̎n�_��
													//			MC_INSIDE			(002): �_�������̓�����
													//			MC_ON_PE			(004): �_�������̏I�_��
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);
	
	// ---------------------( �Q���� )------------------------------
	//
	//	�����̒��S�_��������ɂ��邩�𒲂ׂ�B
	//
	
	static inline bool ChkLineOnULine2DWS(			// (  O) �X�e�C�^�X
													//			true:	������ɂ���
													//			false:	������ɂȂ�
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgULine2D&	i_ULn2,		// (I  ) ����2
							MINT*		o_pist,		// (  O) �X�e�C�^�X
													//			MC_RIGHT			(010): �_�������̉E��
													//			MC_ON_LINE			(020): �_��������
													//			MC_LEFT				(040): �_�������̍���
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		MgPoint2D Pt1;
		Pt1 = ( i_Ln1.p[0] + i_Ln1.p[1]) * 0.5;
		return ChkPointOnULine2DWS( Pt1, i_ULn2, o_pist);
	}
	
	// ---------------------( �Q���� )------------------------------
	//
	//	�����Ɛ������d�Ȃ��Ă��邩�𒲂ׂ�B
	//
	static bool	ChkLineOnLine2D(					// (  O) �X�e�C�^�X
													//			true:	�d�Ȃ��Ă���
													//			false:	�d�Ȃ��Ă��Ȃ�
					const	MgLine2D&	i_Ln1,		// (I  ) ����1
					const	MgLine2D&	i_Ln2,		// (I  ) ����2
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);
	
	// ---------------------( �R���� )------------------------------
	//
	//	�_��������ɂ��邩�𒲂ׂ�B
	//
	static inline bool ChkPointOnULine3D(			// (  O) �X�e�C�^�X
													//			true:	������ɂ���
													//			false:	������ɂȂ�
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgULine3D&	i_ULn2,		// (I  ) ����2
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		MgVect3D		v21, va1;
	//	MREAL		pa_2;							//	����2����_1�܂ł̉�������**2
	//
		v21 = i_p1 - i_ULn2.p;
		va1 = v21 ^ i_ULn2.v;
	//	pa_2 = Abs_2(va1);
	//	return ( pa_2 <= rTol * rTol);
		return ( SqLenVect3D(va1) <= rTol * rTol);
	}
	
	// ---------------------( �R���� )------------------------------
	//
	//	�_����������ɂ��邩�𒲂ׂ�B
	//
	static inline bool ChkPointOnHLine3D(			// (  O) �X�e�C�^�X
													//			true:	������ɂ���
													//			false:	������ɂȂ�
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgHLine3D&	i_HLn2,		// (I  ) ������2
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		MgVect3D	v21, va1;
		MREAL		c1;
	//	MREAL		pa_2;							//	����2����_1�܂ł̉�������**2
	//
		v21 = i_p1 - i_HLn2.p;
		va1 = v21 ^ i_HLn2.v;
		c1 = v21 * i_HLn2.v;
	//	pa_2 = Abs_2(va1);
	//	return ( pa_2 <= rTol * rTol);
		return ( SqLenVect3D(va1) <= rTol * rTol && c1 > -rTol);
	}
	
	// ---------------------( �R���� )------------------------------
	//
	//	�_��������ɂ��邩�𒲂ׂ�B
	//
	static bool	ChkPointOnLine3DWS(					// (  O) �X�e�C�^�X
													//			true:	������ɂ���
													//			false:	������ɂȂ�
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgLine3D&	i_Line2,	// (I  ) ����2
							MINT*		o_pist,		// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
													//		 �X�e�C�^�X1
													//			MC_ON_LINE			(020): �_����������������
													//		 �X�e�C�^�X2
													//			MC_ON_PS			(001): �_�������̎n�_��
													//			MC_INSIDE			(002): �_�������̓�����
													//			MC_ON_PE			(004): �_�������̏I�_��
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);
	
	// ---------------------( �R���� )------------------------------
	//
	//	�����Ɛ������d�Ȃ��Ă��邩�𒲂ׂ�B
	//
	static bool	ChkLineOnLine3D(					// (  O) �X�e�C�^�X
													//			true:	�d�Ȃ��Ă���
													//			false:	�d�Ȃ��Ă��Ȃ�
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);
	
	// ---------------------( �R���� )------------------------------
	//
	//	�����Ɛ������d�Ȃ��Ă��邩�𒲂ׂ�B
	//
	static bool	ChkLineOnLine3DWS(					// (  O) �X�e�C�^�X
													//			true:	�d�Ȃ��Ă���
													//			false:	�d�Ȃ��Ă��Ȃ�
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
							MINT*		o_pist,		// (  O) �⏕�X�e�C�^�X�@�d�Ȃ肠��̏ꍇ�͎��̒ʂ�
													//        -4    -3   -2   -1    0     1    2    3    4 		   	
													//		|--   |--  |--- | -- | --- |----| ---|  --|   --|           	  	
													//		|   --|  --| ---|----| --- | -- |--- |--  |--   |                �@	
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);

	// ---------------------( �Q���� )------------------------------
	//		�x�N�g���ƃx�N�g���������ł��邩���m�F����
	static inline bool ChkPerpVect2D(				// (  O) �X�e�C�^�X true: ���� 
					const	MgVect2D&	i_v1,		// (I  ) �x�N�g��1
					const	MgVect2D&	i_v2		// (I  ) �x�N�g��2
					)
	{
		MREAL fo = i_v1 ^ i_v2; MREAL fi = i_v1 * i_v2;
		return ( MGABS(fi/fo)  <= MGPTOL->A);
	}

	// ---------------------( �Q���� )------------------------------
	//		�x�N�g���ƃx�N�g���������ł��邩���m�F���A�O�ςƓ��ς��o�͂���
	static inline bool ChkPerpVect2DS(				// (  O) �X�e�C�^�X true: ����
					const	MgVect2D&	i_v1,		// (I  ) �x�N�g��1
					const	MgVect2D&	i_v2,		// (I  ) �x�N�g��2
							MREAL*		o_pso,		// (  O) �O��
							MREAL*		o_psi		// (  O) ����
				)
	{
		*o_pso = i_v1 ^ i_v2;
		*o_psi = i_v1 * i_v2;
		return ( MGABS( *o_psi / *o_pso) <= MGPTOL->A);
	}

	// ---------------------( �R���� )------------------------------
	//		�x�N�g���ƃx�N�g���������ł��邩���m�F����
	static inline bool ChkPerpVect3D(				// (  O) �X�e�C�^�X true: ����
					const	MgVect3D&	i_v1,		// (I  ) �x�N�g��1
					const	MgVect3D&	i_v2		// (I  ) �x�N�g��2
					)
	{
		MgVect3D vo = i_v1 ^ i_v2;
		MREAL fi = i_v1 * i_v2;
		return (fi * fi <= SqLenVect3D(vo) * MGPTOL->A_2);
	}

	// ---------------------( �R���� )------------------------------
	//		�x�N�g���ƃx�N�g���������ł��邩���m�F���A�O�ςƓ��ς��o�͂���
	static inline bool ChkPerpVect3DS(				// (  O) �X�e�C�^�X true: ����
					const	MgVect3D&	i_v1,		// (I  ) �x�N�g��1
					const	MgVect3D&	i_v2,		// (I  ) �x�N�g��2
							MgVect3D*	o_ppso,		// (  O) �O��
							MREAL*		o_psi		// (  O) ����
					)
	{
		MgVect3D vo = i_v1 ^ i_v2;
		MREAL fi = i_v1 * i_v2;
		*o_ppso = vo; *o_psi = fi;
		return (fi * fi <= SqLenVect3D(vo) * MGPTOL->A_2);
	}

	//===========================================================================
	//		�_ ���p�` ���Z
	// ---------------------( �Q���� )------------------------------
	//	�_�Ƒ��p�`�̈ʒu�֌W�����߂�
	//
	
	static inline bool ChkPointOnPolygon2DWS(		// (  O) �X�e�C�^�X
													//			true:	���p�`�̓����܂��͕ӏ�
													//			false:	���p�`�̊O��
					const	MgPoint2D&	i_Pt,		// (I  ) �_
					const	MgPolyg2D&	i_Pg,		// (I  ) ���p�`
							MINT*		o_pist,		// (  O) �X�e�C�^�X
													//			MC_IN_BORDER		(001): �_�����p�`�̓���
													//			MC_ON_BORDER		(002): �_�����p�`�̕ӏ�(�܂��͒��_��)
													//			MC_OUT_BORDER		(004): �_�����p�`�̊O��
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		bool	bst;
		MINT	ist1;
		MINT	ict;
		
		ist1 = CountPolygonAroundPoint2D( i_Pt, NULL, i_Pg, &ict, rTol);
		if ( ist1) {
			*o_pist = MC_ON_BORDER;
			bst = true;												// ���p�`�̕ӏ�(�܂��͒��_��)
		} else {
			if ( ict) {
				*o_pist = MC_IN_BORDER;
				bst = true;											// ���p�`�̓���
			}
			else {
				*o_pist = MC_OUT_BORDER;
				bst = false;										// ���p�`�̊O��
			}
		}
		return bst;
	}
	
	// ---------------------( �Q���� )------------------------------
	//	�����̒��S�_�Ƒ��p�`�̈ʒu�֌W�����߂� �Q�c
	//
	static inline bool ChkLineOnPolygon2DWS(		// (  O) �X�e�C�^�X
													//			true:	���p�`�̓����܂��͕ӏ�
													//			false:	���p�`�̊O��
					const	MgLine2D&	i_Ln1,		// (I  ) ����
					const	MgPolyg2D&	i_Pg2,		// (I  ) ���p�`
							MINT*		o_pisth,	// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
													// 		 �e�C�^�X1
													//			MC_IN_BORDER		(001):	�_�����p�`�̓���
													//			MC_ON_BORDER		(002):	�_�����p�`�̕ӏ�(�܂��͒��_��)
													//			MC_OUT_BORDER		(004):	�_�����p�`�̊O��
													//		�X�e�C�^�X2
													//			MC_ON_SIDE_SAME 	(010):	�ӏ�(�������)
													//			MC_ON_SIDE_REV		(020):	�ӏ�(�t����)
													//			MC_ON_TOP			(040): ���_��
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		bool		bst;
		MgPoint2D	pt1;
		MgVect2D		vt1;
		MINT		ist1;
		MINT		ict;
		
		pt1 = ( i_Ln1.p[0] + i_Ln1.p[1]) * 0.5;
		vt1 = i_Ln1.p[1] - i_Ln1.p[0];
		
		ist1 = CountPolygonAroundPoint2D( pt1, &vt1, i_Pg2, &ict, rTol);
		if ( ist1) {
			*o_pisth = MC_ON_BORDER | ist1;
			bst = true;												// ���p�`�̕ӏ�(�܂��͒��_��)
		} else {
			if ( ict) {
				*o_pisth = MC_IN_BORDER;
				bst = true;											// ���p�`�̓���
			}
			else {
				*o_pisth = MC_OUT_BORDER;
				bst = false;										// ���p�`�̊O��
			}
		}
		return bst;
	}
	
	// ---------------------( �Q���� )------------------------------
	//	�_�ƌ��t�����p�`�̈ʒu�֌W�����߂�
	//
	static bool ChkPointOnGPolygon2DWS(				// (  O) �X�e�C�^�X
													//			true:	���t�����p�`�̓����܂��͕ӏ�
													//			false:	���t�����p�`�̊O��
					const	MgPoint2D&	i_Pt,		// (I  ) �_
					const	MgGPolyg2D&	i_GPg,		// (I  ) ���t�����p�`
							MINT*		o_pist,		// (  O) �X�e�C�^�X
													//			MC_IN_BORDER		(001): �_�����t�����p�`�̓���
													//			MC_ON_BORDER		(002): �_�����t�����p�`�̕ӏ�(�܂��͒��_��)
													//			MC_OUT_BORDER		(004): �_�����t�����p�`�̊O��
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);

	// ---------------------( �Q���� )------------------------------
	//	�����̒��S�_�ƌ��t�����p�`�̈ʒu�֌W�����߂�
	//
	static bool ChkLineOnGPolygon2DWS(				// (  O) �X�e�C�^�X
													//			true:	���t�����p�`�̓����܂��͕ӏ�
													//			false:	���t�����p�`�̊O��
					const	MgLine2D&	i_Ln1,		// (I  ) ����
					const	MgGPolyg2D&	i_GPg2,		// (I  ) ���t�����p�`
							MINT*		o_pisth,	// (  O) �⏕�X�e�C�^�X	(�X�e�C�^�X1 | �X�e�C�^�X2)
													// 		 �e�C�^�X1
													//			MC_IN_BORDER		(001): �_�����t�����p�`�̓���
													//			MC_ON_BORDER		(002): �_�����t�����p�`�̕ӏ�(�܂��͒��_��)
													//			MC_OUT_BORDER		(004): �_�����t�����p�`�̊O��
													// 		 �e�C�^�X2
													//			MC_ON_SIDE_SAME		(010): �ӏ�(�������)	(MC_ON_BORDER�Ƌ��ɐݒ�)
													//			MC_ON_SIDE_REV		(020): �ӏ�(�t����)		(MC_ON_BORDER�Ƌ��ɐݒ�)
													//			MC_ON_TOP			(040): ���_��			(MC_ON_BORDER�Ƌ��ɐݒ�)
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);
	
	// ---------------------( �Q���� )------------------------------
	// �_�Ƒ��p�`�̈ʒu�֌W�����߂�
	// ���p�`�̕ӂ��_�̎���������񐔂����߂�i���̈��:1�@�����:-1�j
	static MINT	CountPolygonAroundPoint2D(			// (  O) �X�e�C�^�X
													//								(000): ���p�`�̒��܂��͊O	
													//			MC_ON_SIDE_SAME		(010): �ӏ�(�������)
													//			MC_ON_SIDE_REV		(020): �ӏ�(�t����)
													//			MC_ON_SIDE			(030): �ӏ�(��������=NULL: ���������w�薳��)
													//			MC_ON_TOP			(040): ���_��
					const	MgPoint2D&	i_Pt,		// (I  ) �_
					const	MgVect2D*	i_pvst,		// (I  ) �������� �܂��� NULL
													//		 ������NULL�Ŗ�����Γ_���ӏ�̏ꍇ�A
													//		 �ӂ̐��������Ɣ�r����
					const	MgPolyg2D&	i_Pg,		// (I  ) ���p�`
							MINT*		o_pict,		// (  O) ����J�E���g
													//			>0: ���p�`�����̂̏ꍇ�̎���	(1:1��)
													//			=0: ���_�A�ӏ�A���p�`�̊O
													//			<0: ���p�`�����̏ꍇ�̎���	(-1:1��)	
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);
	
	// ---------------------( �R���� )------------------------------
	//	�_�Ƒ��p�`�̈ʒu�֌W�����߂� �R�c
	//
	/*
	static bool ChkPointOnPolygon3DWS(				// (  O) �X�e�C�^�X
													//			true:	���p�`�̓����܂��͕ӏ�
													//			false:	���p�`�̊O��
					const	MgPoint3D&	i_Pt,		// (I  ) �_
					const	MgPolyg3D&	i_Pg,		// (I  ) ���p�`
							MINT*		o_pist,		// (  O) �X�e�C�^�X
								  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
													//			MC_UPPER			(010): �_�����ʂ̏㑤	
													//			MC_ON_PLANE			(020): �_�����ʏ�
													//			MC_LOWER			(040): �_�����ʂ̉���
													//		 ���p�`�Ɠ_�̈ʒu�֌W
													//			MC_IN_BORDER		(001): �_�����p�`�̓���
													//			MC_ON_BORDER		(002): �_�����p�`�̕ӏ�
													//			MC_OUT_BORDER		(004): �_�����p�`�̊O��
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					);
	
	*/
	//
	// ---------------------( �R���� )------------------------------
	//	�����̒��S�_�Ƒ��p�`�̈ʒu�֌W�����߂�
	//
	/*
	static inline bool ChkLineOnPolygon3DWS(		// (  O) �X�e�C�^�X
													//			true:	���p�`��
													//			false:	���p�`�O
					const	MgLine3D&	i_Ln1,		// (I  ) ����
					const	MgPolyg3D&	i_Pg2,		// (I  ) ���p�`
							MINT*		o_pist,		// (  O) �⏕�X�e�C�^�X
								  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
													//			MC_UPPER			(010): �_�����ʂ̏㑤	
													//			MC_ON_PLANE			(020): �_�����ʏ�
													//			MC_LOWER			(040): �_�����ʂ̉���
													//       ���p�`�Ɠ_�̈ʒu�֌W
													//			MC_IN_BORDER		(001): �_�����p�`�̓���
													//			MC_ON_BORDER		(002): �_�����p�`�̕ӏ�
													//			MC_OUT_BORDER		(004): �_�����p�`�̊O��
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		MgPoint3D	Pt1;
		Pt1 = ( i_Ln1.p[0] + i_Ln1.p[1]) * 0.5;
		return OnPtPolygon3D( Pt1, i_Pg2, o_pist);
	}

	*/
	//		���ʁ@�`�󉉎Z
	//
	// ---------------------( �R���� )------------------------------
	//
	//	�_�����ʏ�ɂ��邩�𒲂ׂ�B
	//
	static inline bool ChkPointOnPln3DWS(			// (  O) �X�e�C�^�X
													//			true:  ���ʏ�
													//			false: ���ʊO
					const	MgPoint3D&	i_p1,		// (I  ) �_1
					const	MgPlane3D&	i_Pln2,		// (I  ) ����2
							MINT*		o_pist,		// (  O) �⑫�X�e�C�^�X
													//			MC_UPPER			(010): �_�����ʂ̏㑤	
													//			MC_ON_PLANE			(020): �_�����ʏ�
													//			MC_LOWER			(040): �_�����ʂ̉���
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		bool	bst;
		MREAL	pa1;								//	�_���畽�ʂ܂ł̋���
	//
		pa1 = ( i_Pln2.v * i_p1) + i_Pln2.d;
		if ( pa1 > rTol) {
			*o_pist = MC_UPPER;
			bst = false;
		} else if ( pa1 < -rTol) {
			*o_pist = MC_LOWER;
			bst = false;
		} else {
			*o_pist = MC_ON_PLANE;
			bst = true;
		}
		return bst;
	}

	// ---------------------( �R���� )------------------------------
	//	���������ʏ�ɂ��邩�𒲂ׂ�B
	//
	static inline bool ChkULineOnPln3D(				// (  O) �X�e�C�^�X
													//			true:  ���ʏ�
													//			false: ���ʊO
					const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgPlane3D&	i_Pln2,		// (I  ) ����2
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		int		ist;
		if ( ChkPointOnPln3DWS( i_ULn1.p, i_Pln2, &ist)) {
	//
	//	���s�̃`�F�b�N
	//
			if ( ChkPerpVect3D( i_ULn1.v, i_Pln2.v))
				return true;									//	���ʏ�
		}
		return false;
	}
	
	// ---------------------( �R���� )------------------------------
	//	���������ʏ�ɂ��邩�𒲂ׂ�B
	//
	static inline bool ChkLineOnPln3DWS(			// (  O) �X�e�C�^�X
													//			true:  ���ʏ�
													//			false: ���ʊO
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgPlane3D&	i_Pln2,		// (I  ) ����2
							MINT*		o_pist,		// (  O) �⑫�X�e�C�^�X
								  					//		 ���p�`�̕��ʂƓ_�̈ʒu�֌W
													//			MC_PS_UPPER			(001): �n�_�����ʂ̏㑤	
													//			MC_PS_ON_PLANE		(002): �n�_�����ʏ�
													//			MC_PS_LOWER			(004): �n�_�����ʂ̉���
													//       ���p�`�Ɠ_�̈ʒu�֌W
													//			MC_PE_UPPER			(010): �I�_�����ʂ̏㑤	
													//			MC_PE_ON_PLANE		(020): �I�_�����ʏ�
													//			MC_PE_LOWER			(040): �I�_�����ʂ̉���
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		bool	bs, be;
		MINT	ists, iste;
	
		bs = ChkPointOnPln3DWS( i_Ln1.p[0], i_Pln2, &ists);
		be = ChkPointOnPln3DWS( i_Ln1.p[1], i_Pln2, &iste);
		*o_pist = (ists * MC_PS_UPPER + iste * MC_PE_UPPER)/ MC_UPPER;
		return (bs && be);
	}
	
	// ---------------------( �Q���� )------------------------------
	//
	//		�Q�̂S�p�`���d�Ȃ邩�ۂ����`�F�b�N����B
	// 
	static inline bool	MgChkRectOnRect2D(			// (  O) �X�e�C�^�X
													//		 true   ��������
													//		 false  �����Ȃ�
					const	MgRect2D&	i_rct10,	// (I  ) �S�p�`1 (min,max)
					const	MgRect2D&	i_rct20,	// (I  ) �S�p�`2 (min,max)
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		return i_rct10.p[0].x < i_rct20.p[1].x + MGPTOL->D &&
			   i_rct20.p[0].x < i_rct10.p[1].x + MGPTOL->D &&
			   i_rct10.p[0].y < i_rct20.p[1].y + MGPTOL->D &&
			   i_rct20.p[0].y < i_rct10.p[1].y + MGPTOL->D;
	}

	// ---------------------( �R���� )------------------------------
	//
	//		�Q�̂S�p�`���d�Ȃ邩�ۂ����`�F�b�N����B
	//
	static inline bool	MgChkRectOnRect3D(			// (  O) �X�e�C�^�X
													//		 true   ��������
													//		 false  �����Ȃ�
					const	MgRect3D&	i_rct10,	// (I  ) �S�p�`1 (min,max)
					const	MgRect3D&	i_rct20,	// (I  ) �S�p�`2 (min,max)
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		return i_rct10.p[0].x < i_rct20.p[1].x + MGPTOL->D &&
			   i_rct20.p[0].x < i_rct10.p[1].x + MGPTOL->D &&
			   i_rct10.p[0].y < i_rct20.p[1].y + MGPTOL->D &&
			   i_rct20.p[0].y < i_rct10.p[1].y + MGPTOL->D &&
			   i_rct10.p[0].z < i_rct20.p[1].z + MGPTOL->D &&
			   i_rct20.p[0].z < i_rct10.p[1].z + MGPTOL->D;
	}
	
	// ---------------------( �Q���� )------------------------------
	//
	//		�_���l�h�m�^�l�`�w�̈悪���ɂ��邩�ۂ����`�F�b�N����B
	//
	static inline	bool ChkPointInMinmaxR2D(
					const	MgPoint2D&		i_pt1,	// Point
					const	MgMinMaxR2D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		return i_pt1.x < i_mx2.max.x + MGPTOL->D && i_mx2.min.x - MGPTOL->D < i_pt1.x &&
			   i_pt1.y < i_mx2.max.y + MGPTOL->D && i_mx2.min.y - MGPTOL->D < i_pt1.y;
	}
	
	// ---------------------( �R���� )------------------------------
	//
	//		�_���l�h�m�^�l�`�w�̈悪���ɂ��邩�ۂ����`�F�b�N����B
	//
	static inline	bool ChkPt3InMinmaxR3D(
					const	MgPoint3D&		i_pt1,	// Point
					const	MgMinMaxR3D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		return i_pt1.x < i_mx2.max.x + MGPTOL->D && i_mx2.min.x - MGPTOL->D < i_pt1.x &&
			   i_pt1.y < i_mx2.max.y + MGPTOL->D && i_mx2.min.y - MGPTOL->D < i_pt1.y &&
			   i_pt1.z < i_mx2.max.z + MGPTOL->D && i_mx2.min.z - MGPTOL->D < i_pt1.z;
	}

	// ---------------------( �Q���� )------------------------------
	//
	//		�Q�̂l�h�m�^�l�`�w�̈悪�d�Ȃ邩�ۂ����`�F�b�N����B
	//
	static inline	bool ChkMinmaxIOnMinmaxI2D(
					const	MgMinMaxI2D&	i_mx1,	// MIN/MAX
					const	MgMinMaxI2D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		return i_mx1.min.x <= i_mx2.max.x && i_mx2.min.x <= i_mx1.max.x &&
			   i_mx1.min.y <= i_mx2.max.y && i_mx2.min.y <= i_mx1.max.y;
	}

	// ---------------------( �Q���� )------------------------------
	//
	//		�Q�̂l�h�m�^�l�`�w�̈悪�d�Ȃ邩�ۂ����`�F�b�N����B
	//
	static inline	bool ChkMinmaxROnMinmaxR2D(
					const	MgMinMaxR2D&	i_mx1,	// MIN/MAX
					const	MgMinMaxR2D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		return i_mx1.min.x < i_mx2.max.x + MGPTOL->D && i_mx2.min.x < i_mx1.max.x + MGPTOL->D &&
			   i_mx1.min.y < i_mx2.max.y + MGPTOL->D && i_mx2.min.y < i_mx1.max.y + MGPTOL->D;
	}

	// ---------------------( �R���� )------------------------------
	//
	//		�Q�̂l�h�m�^�l�`�w�̈悪�d�Ȃ邩�ۂ����`�F�b�N����B
	//
	static inline	bool ChkMinmaxROnMinmaxR3D(
					const	MgMinMaxR3D&	i_mx1,	// MIN/MAX
					const	MgMinMaxR3D&	i_mx2,	// MIN/MAX
							MREAL rTol= MGPTOL->D	// (I  ) �g�������X
					)
	{
		return i_mx1.min.x < i_mx2.max.x + MGPTOL->D && i_mx2.min.x < i_mx1.max.x + MGPTOL->D &&
			   i_mx1.min.y < i_mx2.max.y + MGPTOL->D && i_mx2.min.y < i_mx1.max.y + MGPTOL->D &&
			   i_mx1.min.z < i_mx2.max.z + MGPTOL->D && i_mx2.min.z < i_mx1.max.z + MGPTOL->D;
	}

	// ---------------------( �Q���� )------------------------------
	// P1�����_�Ƃ���P2�̈ʒu�̏ی������߂�
	//
	static inline MINT Quadrant	(					// (  O) 1�`4: �ی�
					const	MgPoint2D&	i_p1,		// (I  ) P1
					const	MgPoint2D&	i_p2		// (I  ) P2
					)
	{
		return ( ( i_p2.x > i_p1.x) ? ( ( i_p2.y > i_p1.y) ? 1 : 4) : ( ( i_p2.y > i_p1.y) ? 2 : 3));
	}
		
	// ---------------------( �Q���� )------------------------------
	//		�_�����ו����ɏ]�������W���ɕ��ׂ�i����_�͊Ԉ����j
	//
	static void	SortVectGPoint2D(
					const	MgVect2D&	i_v1,		// (I  ) �_��̕��ו���
							MgGPoint2D*	io_pGPt2	// (I O) ���ׂ�_��
					);

	// ---------------------( �Q���� )------------------------------
	//		�_�������̎n�_����I�_�Ɍ����������ɏ]�������W���ɕ��ׂ�i����_�͊Ԉ����j
	//
	static inline void	SortLineGPoint2D(
					const	MgLine2D&	i_Ln1,		// (I  ) �_��̕��ו�������������
							MgGPoint2D*	io_pGPt2	// (I O) ���ׂ�_��
					)
	{
		MgVect2D		v1;
		v1 = i_Ln1.p[1] - i_Ln1.p[0];
		SortVectGPoint2D( v1, io_pGPt2);
	}

	//// ---------------------( �R���� )------------------------------
	////		�_�����ו����ɏ]�������W���ɕ��ׂ�i����_�͊Ԉ����j
	////
	//static void	MgSortVGPoint3D(
	//				const	MgVect3D&	i_V1,		// (I  ) �_��̕��ו���
	//						MgGPoint3D*	io_pGPt2	// (I O) ���ׂ�_��
	//				);

	//// ---------------------( �R���� )------------------------------
	////		�_�������̎n�_����I�_�Ɍ����������ɏ]�������W���ɕ��ׂ�i����_�͊Ԉ����j
	////
	//static inline void	MgSortLineGPoint3D(
	//				const	MgLine3D&	i_Ln1,		// (I  ) �_��̕��ו�������������
	//						MgGPoint3D*	io_pGPt2	// (I O) ���ׂ�_��
	//				)
	//	{
	//		MgVect3D		V1;
	//		V1 = i_Ln1.p[1] - i_Ln1.p[0];
	//		MgSortVGPoint3D( V1, io_pGPt2);
	//	}

	//===========================================================================
	//	�����Q�𐳋K������B�i�����̋t�����̏d�Ȃ����������j
	//
	static inline void Norm(						//
					const	MgGLine2D&	i_GLn1,		// (I  ) ����
							MgGLine2D*	o_pGLn2		// (  O) �d�Ȃ��������̐���
					)
	{
		MgLine2D	work[MX_LIN1+1];				// �����̐��p�̃G���A��ǉ�������ƃG���A���m�ۂ���
		MgGLine2D	*GLn = (MgGLine2D*)work;
		DivideGLine2D( i_GLn1, o_pGLn2);				// ��������_�ŕ�������
	//	ThinOut( *GLn, GLn2);						// ���������ƊJ���[�����������Ԉ���
	}
	
	//===========================================================================
	//		���ʁ@�`�󉉎Z
	//
	//	------------- �r�l�̎Z�o�@------------------
	//
	// ---------------------( �R���� )------------------------------
	//		�����Ɠ_�̈ʒu�֌W��\���r�l
	//
	static inline MREAL SVal2ULine3D(				// (  O) �r�l(�Q�����̕����x�N�g������Ȃ镽�s�U�ʑ̂̑̐ρj
				    const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgULine3D&	i_ULn2		// (I  ) ����2
					)
	{
	//		( (ULn1.p.x*ULn1.v.y-ULn1.p.y*ULn1.v.x) * (ULn2.p.z*ULn2.v.w-ULn2.p.w*ULn2.v.z)
	//		- (ULn1.p.x*ULn1.v.z-ULn1.p.z*ULn1.v.x) * (ULn2.p.y*ULn2.v.w-ULn2.p.w*ULn2.v.y)
	//		+ (ULn1.p.x*ULn1.v.w-ULn1.p.w*ULn1.v.x) * (ULn2.p.y*ULn2.v.z-ULn2.p.z*ULn2.v.y)
	//		+ (ULn1.p.y*ULn1.v.z-ULn1.p.z*ULn1.v.y) * (ULn2.p.x*ULn2.v.w-ULn2.p.w*ULn2.v.x)
	//		- (ULn1.p.y*ULn1.v.w-ULn1.p.w*ULn1.v.y) * (ULn2.p.x*ULn2.v.z-ULn2.p.z*ULn2.v.x)
	//		+ (ULn1.p.z*ULn1.v.w-ULn1.p.w*ULn1.v.z) * (ULn2.p.x*ULn2.v.y-ULn2.p.y*ULn2.v.x))
	//
		return	( ( i_ULn1.p.x * i_ULn1.v.y - i_ULn1.p.y * i_ULn1.v.x) * ( -i_ULn2.v.z)
				- ( i_ULn1.p.x * i_ULn1.v.z - i_ULn1.p.z * i_ULn1.v.x) * ( -i_ULn2.v.y)
				+ ( -i_ULn1.v.x) * ( i_ULn2.p.y * i_ULn2.v.z - i_ULn2.p.z * i_ULn2.v.y)
				+ ( i_ULn1.p.y * i_ULn1.v.z - i_ULn1.p.z * i_ULn1.v.y) * ( -i_ULn2.v.x)
				- ( -i_ULn1.v.y) * ( i_ULn2.p.x * i_ULn2.v.z - i_ULn2.p.z * i_ULn2.v.x)
				+ ( -i_ULn1.v.z) * ( i_ULn2.p.x * i_ULn2.v.y - i_ULn2.p.y * i_ULn2.v.x));
	}

	// ---------------------( �R���� )------------------------------
	//		�����Ɠ_�̈ʒu�֌W��\���r�l
	//
	static inline MREAL SValULineLine3D(			// (  O) �r�l(�����̕����x�N�g���Ɛ�������Ȃ镽�s�U�ʑ̂̑̐ρj
				    const	MgULine3D&	i_ULn1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2		// (I  ) ����2
					)
	{
	//		( (ULn1.p.x*ULn1.v.y-ULn1.p.y*ULn1.v.x) * (Ln2.p[0].z*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].z)
	//		- (ULn1.p.x*ULn1.v.z-ULn1.p.z*ULn1.v.x) * (Ln2.p[0].y*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].y)
	//		+ (ULn1.p.x*ULn1.v.w-ULn1.p.w*ULn1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
	//		+ (ULn1.p.y*ULn1.v.z-ULn1.p.z*ULn1.v.y) * (Ln2.p[0].x*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].x)
	//		- (ULn1.p.y*ULn1.v.w-ULn1.p.w*ULn1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
	//		+ (ULn1.p.z*ULn1.v.w-ULn1.p.w*ULn1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x))
	//
		return
		(	  ( i_ULn1.p.x * i_ULn1.v.y - i_ULn1.p.y * i_ULn1.v.x) * ( i_Ln2.p[0].z - i_Ln2.p[1].z)
			- ( i_ULn1.p.x * i_ULn1.v.z - i_ULn1.p.z * i_ULn1.v.x) * ( i_Ln2.p[0].y - i_Ln2.p[1].y)
			+ ( -i_ULn1.v.x) * ( i_Ln2.p[0].y * i_Ln2.p[1].z - i_Ln2.p[0].z * i_Ln2.p[1].y)
			+ ( i_ULn1.p.y * i_ULn1.v.z - i_ULn1.p.z * i_ULn1.v.y) * ( i_Ln2.p[0].x - i_Ln2.p[1].x)
			- ( -i_ULn1.v.y) * ( i_Ln2.p[0].x * i_Ln2.p[1].z - i_Ln2.p[0].z * i_Ln2.p[1].x)
			+ ( -i_ULn1.v.z) * ( i_Ln2.p[0].x * i_Ln2.p[1].y - i_Ln2.p[0].y * i_Ln2.p[1].x));
	}

	// ---------------------( �R���� )------------------------------
	//		�����Ɠ_�̈ʒu�֌W��\���r�l
	//
	static inline MREAL SVal2Line3D(				// (  O) �r�l(2��������Ȃ镽�s�U�ʑ̂̑̐ρj
				    const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2		// (I  ) ����2
					)
	{
	//		( (Ln1.p[0].x*Ln1.v.y-Ln1.p[0].y*Ln1.v.x) * (Ln2.p[0].z*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].z)
	//		- (Ln1.p[0].x*Ln1.v.z-Ln1.p[0].z*Ln1.v.x) * (Ln2.p[0].y*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].y)
	//		+ (Ln1.p[0].x*Ln1.v.w-Ln1.p[0].w*Ln1.v.x) * (Ln2.p[0].y*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].y)
	//		+ (Ln1.p[0].y*Ln1.v.z-Ln1.p[0].z*Ln1.v.y) * (Ln2.p[0].x*Ln2.p[1].w-Ln2.p[0].w*Ln2.p[1].x)
	//		- (Ln1.p[0].y*Ln1.v.w-Ln1.p[0].w*Ln1.v.y) * (Ln2.p[0].x*Ln2.p[1].z-Ln2.p[0].z*Ln2.p[1].x)
	//		+ (Ln1.p[0].z*Ln1.v.w-Ln1.p[0].w*Ln1.v.z) * (Ln2.p[0].x*Ln2.p[1].y-Ln2.p[0].y*Ln2.p[1].x))
	//
		return
		(	  ( i_Ln1.p[0].x * i_Ln1.p[1].y - i_Ln1.p[0].y * i_Ln1.p[1].x) * ( i_Ln2.p[0].z - i_Ln2.p[1].z)
			- ( i_Ln1.p[0].x * i_Ln1.p[1].z - i_Ln1.p[0].z * i_Ln1.p[1].x) * ( i_Ln2.p[0].y - i_Ln2.p[1].y)
			+ ( i_Ln1.p[0].x - i_Ln1.p[1].x) * ( i_Ln2.p[0].y * i_Ln2.p[1].z - i_Ln2.p[0].z * i_Ln2.p[1].y)
			+ ( i_Ln1.p[0].y * i_Ln1.p[1].z - i_Ln1.p[0].z * i_Ln1.p[1].y) * ( i_Ln2.p[0].x - i_Ln2.p[1].x)
			- ( i_Ln1.p[0].y - i_Ln1.p[1].y) * ( i_Ln2.p[0].x * i_Ln2.p[1].z - i_Ln2.p[0].z * i_Ln2.p[1].x)
			+ ( i_Ln1.p[0].z - i_Ln1.p[1].z) * ( i_Ln2.p[0].x * i_Ln2.p[1].y - i_Ln2.p[0].y * i_Ln2.p[1].x));
	}

	// ---------------------( �R���� )------------------------------
	//		�����Ɠ_�̈ʒu�֌W��\���r�l
	//
	static inline void SSValLineULine3D(					//
					const	MgLine3D&	i_Ln1,		// (I  ) ����1
				    const	MgULine3D&	i_ULn2,		// (I  ) ����2
					const	MgVect3D&	i_vso,		// (I  ) ����1�ƒ���2�����镽�ʂ̖@���x�N�g��
							MREAL*		o_pss,		// (  O) �����P�̎n�_���r�l
													//		(����2�̕����x�N�g���ƕ��ʂ̖@���x�N�g����
													//		 ����1�̎n�_�ŏo���镽�s�U�ʑ̂̑̐�)
							MREAL*		o_pse		// (  O) �����P�̏I�_���r�l
													//		(����2�̕����x�N�g���ƕ��ʂ̖@���x�N�g����
													//		 ����1�̏I�_�ŏo���镽�s�U�ʑ̂̑̐�)
					)
	{
		MgVect3D	N;								//	�����Q�Ɛ����x�N�g������Ȃ镽�ʂ̌W��
		MREAL		d;								//	��_���璼��1�̎n�_�܂ł̓����ʂɐ�������
	//
		N = i_ULn2.v ^ i_vso;
		d =  i_ULn2.p * N;
		*o_pss = ( i_Ln1.p[0] * N) - d;
		*o_pse = ( i_Ln1.p[1] * N) - d;
	}

	// ---------------------( �R���� )------------------------------
	//		�����Ɠ_�̈ʒu�֌W��\���r�l
	//
	static inline void SSVal2Line3D(				// (  O) �X�e�C�^�X
				    const	MgLine3D&	i_Ln1,		// (I  ) ����1
					const	MgLine3D&	i_Ln2,		// (I  ) ����2
					const	MgVect3D&	i_vso,		// (I  ) ����1�Ɛ���2�����镽�ʂ̖@���x�N�g��
							MREAL*		o_pss,		// (  O) �����P�̎n�_���r�l
													//		(����2�ƕ��ʂ̖@���x�N�g���Ɛ���1�̎n�_��
													//		 �o���镽�s�U�ʑ̂̑̐�)
							MREAL*		o_pse		// (  O) �����P�̏I�_���r�l
													//		(����2�ƕ��ʂ̖@���x�N�g���Ɛ���1�̏I�_��
													//		 �o���镽�s�U�ʑ̂̑̐�)
			)
	{
		MgVect3D	N;								//	�����Q�Ɛ����x�N�g������Ȃ镽�ʂ̌W��
		MREAL		d;								//	��_���璼��1�̎n�_�܂ł̓����ʂɐ�������
		MgVect3D	vd;								//	�����Q�̃x�N�g��
	//
		vd = i_Ln2.p[1] - i_Ln2.p[0];
		N = vd ^ i_vso;
		d =  i_Ln2.p[0] * N;
		*o_pss = ( i_Ln1.p[0] * N) - d;
		*o_pse = ( i_Ln1.p[1] * N) - d;
	}

		
		
	//===========================================================================
	//		���� �`�󉉎Z
	//

	static MgPlane3D Plane3pPoint3D( const MgPoint3D *pt);							// �R�_��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j

	static MgPlane3D Plane3Point3D( const MgPoint3D& p0, const MgPoint3D& p1,		// �R�_��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
					   const MgPoint3D& p2);

	static MgPlane3D Plane3DPolygon3D( const MgPolyg3D &pg);							// ���p�`��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j

	static MgPlane3D Plane2PointSlope3D( const MgPoint2D& p1, const MgPoint2D& p2,	// �n�_�ƏI�_�̂Q�_�ƌ��z��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
						 MREAL rkb, MREAL z);

	static MgPlane3D PlaneLineSlope3D( const MgLine2D& ln1,							// �����ƌ��z��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
						MREAL rkb, MREAL z = 0.);

	//===========================================================================
	//		���ʂ̕������̌W���ƒ萔�𐳋K���������ʂ����߂�
	//		ax+by+cz+d=0	(a*a+b*b+c*c=1.0)
	//
	static MgPlane3D NormPln(						// (  O) ���K����̂R��������
				const	MgPlane3D&	i_pl,			// (I  ) �R��������
						MREAL i_Tol = MGPTOL->D);	// (I  ) ���e�덷





	////===========================================================================
	////		�R�_��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
	////
	////	ax+by+cz+d=0
	////
	//static inline MgPlane3D Plane3pPoint3D(		// (  O) ���ʎ�
	//				const	MgPoint3D*	i_pt,		// (I  ) �R�_���W
	//						MREAL i_Tol = MGPTOL->D	// (I  ) ���e�덷
	//				)
	//{
	//	MgPlane3D	Plno;
	//	MgVect3D	v1, v2;
	//
	//	v1 = i_pt[1] - i_pt[0];
	//	v2 = i_pt[2] - i_pt[0];
	//
	//	Plno.v = UnitizeVect3D( v1 ^ v2, i_Tol);
	//	Plno.d = -( Plno.v * i_pt[0]);
	//	return Plno;
	//}

	////===========================================================================
	////		�R�_��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
	////
	//static inline MgPlane3D Plane3Point3D(		// (  O) ���ʎ�
	//				const	MgPoint3D&	i_p0,		// (I  ) �_�P
	//				const	MgPoint3D&	i_p1,		// (I  ) �_�Q
	//				const	MgPoint3D&	i_p2,		// (I  ) �_�R
	//						MREAL i_Tol = MGPTOL->D	// (I  ) ���e�덷
	//				)
	//{
	//	MgPlane3D	Plno;
	//	MgVect3D	v1, v2;
	//
	//	v1 = i_p1 - i_p0;
	//	v2 = i_p2 - i_p0;
	//
	//	Plno.v = UnitizeVect3D( v1 ^ v2, i_Tol);
	//	Plno.d = -(Plno.v * i_p0);
	//	return Plno;
	//}
	
	////===========================================================================
	////		���p�`��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
	////													pkm	�ʐς̐�Βl�̍��v�ŋ��ߕ����͎��ʐςŋ��߂�����ǂ��� pkm
	//static MgPlane3D Plane3DPolygon3D(			// (  O) ���ʎ�
	//				const	MgPolyg3D&	i_pg		// (I  ) ���p�`
	//				);
	
	////===========================================================================
	////		�Q�����n�_�ƂQ�����I�_�̂Q�_�A���z�Ƃy���W��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
	////
	//static MgPlane3D Plane2PointSlope3D(
	//				const	MgPoint2D&	i_p1,		// (I  ) �Q�����n�_
	//				const	MgPoint2D&	i_p2,		// (I  ) �Q�����I�_
	//						MREAL		i_rkb,		// (I  ) ���z	(�n�_����I�_�Ɍ�����������=0 tan)
	//						MREAL		i_z			// (I  ) �y���W
	//				);
	
	////===========================================================================
	////		�Q���������A���z�Ƃy���W��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
	////
	//static MgPlane3D PlaneLineSlope3D(
	//				const	MgLine2D&	i_ln1,		// (I  ) �Q��������
	//						MREAL		i_rkb,		// (I  ) ���z	(�����̎n�_����I�_�Ɍ�����������=0 tan)
	//						MREAL		i_z			// (I  ) �y���W
	//				);
	
	////===========================================================================
	////		���ʂ̕������̌W���ƒ萔�𐳋K������(�W��a,b,c��P�ʃx�N�g���ɕϊ�����)���ʂ����߂�
	////
	//static MgPlane3D NormPln(
	//				const	MgPlane3D&	i_pl,
	//						MREAL		i_Tol
	//				)
	//{
	//	MREAL	d1 = Abs( i_pl.v);
	//		MBCHECK_ZEROVECT( d1, MBCstr( "MgPlane3D Norm"), i_Tol);
	//	MREAL	d2 = 1.f / d1;
	//	return Plane3( i_pl.v.x * d2, i_pl.v.y * d2, i_pl.v.z * d2, i_pl.d * d2);
	//}

};

//	;�K�v�ł��邪�����@MgChkLine2OnLine2WS

//===========================================================================
//		���� �`�󉉎Z
//
inline MgPlane3D MgPlane3Point3D(									// �R�_��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
					const	MgPoint3D*	i_ppt)
						{ return MGeo::Plane3pPoint3D( i_ppt);}

inline MgPlane3D MgPlane3Point3D(									// �R�_��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
					const	MgPoint3D&	i_p0,
					const	MgPoint3D&	i_p1,
					const	MgPoint3D&	i_p2)
						{ return MGeo::Plane3Point3D( i_p0, i_p1, i_p2);}

inline MgPlane3D MgPlanePolygon3D(									// ���p�`��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
					const	MgPolyg3D&	i_pg)
						{ return MGeo::Plane3DPolygon3D( i_pg);}

inline MgPlane3D MgPlane2PointSlope3D(								// �n�_�ƏI�_�̂Q�_�ƌ��z��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
					const	MgPoint2D&	i_p1,
					const	MgPoint2D&	i_p2,
							MREAL		i_rkb,
							MREAL		i_z = 0.)
						{ return MGeo::Plane2PointSlope3D( i_p1, i_p2, i_rkb, i_z);}

inline MgPlane3D PlaneLineSlope3D(									// �����ƌ��z��蕽�ʂ̕������̌W���ƒ萔�����߂�i���K���j
					const	MgLine2D&	i_ln1,
							MREAL		i_rkb,
							MREAL		i_z = 0.)
						{ return MGeo::PlaneLineSlope3D( i_ln1, i_rkb, i_z);}
//
//===========================================================================
//		���ʂ̕������̌W���ƒ萔�𐳋K���������ʂ����߂�
//		ax+by+cz+d=0	(a*a+b*b+c*c=1.0)
//
inline MgPlane3D MgPlane3DNorm(									// (  O) ���K����̂R��������
					const	MgPlane3D&	i_pl)					// (I  ) �R��������
						{ return MGeo::NormPln( i_pl);}
//
//===========================================================================
//		MgPlane3D���g�p�̃C�����C���֐�
//	
inline MgPoint3D::MgPoint3D(									// �Q�������R����
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ x = i_v1.x; y = i_v1.y; z = i_Pln.GetZ( i_v1);} 

//======================( �R���� )==============================
//		�R�����x�N�g�����Z
inline MgVect3D MgVect3DC(										// �Q�������R����
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ MgVect3D Vto; Vto.x = i_v1.x; Vto.y = i_v1.y;
									    Vto.z = i_Pln.GetZ( i_v1); return Vto;} 
inline MgPoint3D MgPoint3D::Set(								// �Q�������R����
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ x = i_v1.x; y = i_v1.y; z = i_Pln.GetZ( i_v1); return *this;} 

inline MgULine3D MgULine3DC(									// �Q�������R����
					const	MgULine2D&	i_uln,
					const	MgPlane3D&	i_Pln,
							MREAL	i_Tol = MGPTOL->D)
						{ MgULine3D ULno; ULno.p.x = i_uln.p.x; ULno.p.y = i_uln.p.y;
										 ULno.p.z = i_Pln.GetZ( i_uln.p);
						  ULno.v = MgVect3DC( i_uln.v, - ( i_Pln.v.x * i_uln.v.x + i_Pln.v.y * i_uln.v.y) / i_Pln.v.z);
						  ULno.v.SetUnitize( i_Tol); return ULno;} 

inline MgULine3D MgULine3D::Set(								// �Q�������R����
					const	MgULine2D&	i_uln,
					const	MgPlane3D&	i_Pln,
							MREAL	i_Tol)
						{ p.x = i_uln.p.x; p.y = i_uln.p.y; p.z = i_Pln.GetZ( i_uln.p);
						  v = MgVect3DC( i_uln.v, - ( i_Pln.v.x * i_uln.v.x + i_Pln.v.y * i_uln.v.y) / i_Pln.v.z);
						  v.SetUnitize( i_Tol); return *this;} 
	
inline MgLine3D MgLine3DC(										// �Q�������R����
					const	MgLine2D&	i_ln,
					const	MgPlane3D&	i_Pln)
						{ MgLine3D Lno; Lno.p[0].x = i_ln.p[0].x; Lno.p[0].y = i_ln.p[0].y;
									   Lno.p[0].z = i_Pln.GetZ( i_ln.p[0]);
									   Lno.p[1].x = i_ln.p[1].x; Lno.p[1].y = i_ln.p[1].y;
									   Lno.p[0].z = i_Pln.GetZ( i_ln.p[1]); return Lno;}

inline MgLine3D MgLine3D::Set(									// �Q�������R����
					const	MgLine2D&	i_ln,
					const	MgPlane3D&	i_Pln)
						{ p[0].x = i_ln.p[0].x; p[0].y = i_ln.p[0].y; p[0].z = i_Pln.GetZ( i_ln.p[0]);
						  p[1].x = i_ln.p[1].x; p[1].y = i_ln.p[1].y; p[0].z = i_Pln.GetZ( i_ln.p[1]);
						  return *this;}

// ���ʃf�[�^�T�C�Y(bytes)
inline int SZMgPlane3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPlane3D));}
inline int SZMgPlane3D()			{ return  (int)sizeof( MgPlane3D);}

// ���ʃf�[�^�T�C�Y(words)
inline int WSZMgPlane3D( int i_sz)	{ return  ( i_sz * (int)sizeof( MgPlane3D) / SZMINT());}
inline int WSZMgPlane3D()			{ return  (int)sizeof( MgPlane3D) / SZMINT();}

} // namespace MC
		
#include "MgMatDf.h"
#include "MgMatEf.h"
