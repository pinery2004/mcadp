//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgPoint.cpp
//
//		
//
//
//  K.Matsu           13/01/23    Created.
//==========================================================================================
//
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"

#include "MgDefine.h"
#include "MgTol.h"
#include "MgAngle.h"

#define DLL_EXPORT_POINT_DO

#include "MgPoint.h"

#define DLL_EXPORT_GEO_DO

#include "MgGeo.h"

namespace MC
{

//======================( �Q���� )==============================
//		2D�_���g���[�X����
//
void MgPoint2D::Print(MCHAR* s) const							// Print
{
#ifdef LOGOUT
	MBLOGOUT( Mstr( "%s	MgPoint2D	: (%7.1f,%7.1f)\n"), s, x, y);
#endif
}

//======================( �Q���� )==============================
//		2D�x�N�g����P�ʃx�N�g���ɕϊ�����
//
MgVect2D MgVect2D::SetUnitize()									//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::LenVect2D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D Unitize"));
	MREAL	d2 = 1.f / d1;
	x *= d2;
	y *= d2;
	return *this;
}

//======================( �Q���� )==============================
// �_��̓�����W���߂�
int MGeo::PackSamePoint2D( MgPoint2D* io_pPt, int* io_pn)
{
	int iC1, iC2;
	int iN;
	bool bPack;
	if( *io_pn != 0) {
		bPack = false;
		iN = *io_pn;
		iC1 = 0;
		for ( iC2=1; iC2<iN; iC2++) {
			if( io_pPt[iC1] == io_pPt[iC2]) {
				bPack = true;
			} else {
				iC1++;
				if( bPack)
					memcpy( &io_pPt[iC1], &io_pPt[iC2], SZMgPoint2D());
			}
		}
		*io_pn = iC1 + 1;
	}
	return 0;
}

// �_����t���ɂ���
int MGeo::ReversePoint2D( MgPoint2D* i_pPt, int i_n, MgPoint2D* o_pPt)
{
	int i1, i2;
	if( i_pPt == o_pPt) {
		for( i1=0,i2=i_n-1; i1<i2;i1++,i2--) {
			msSwap( o_pPt[i1], o_pPt[i2]);
		}
	} else {
		for( i1=0,i2=i_n-1; i2>=0; i1++,i2--) {
																								//E			memcpy( &o_pPt[i2], &i_pPt[i1], SZMgPoint2D());
			o_pPt[i2] = i_pPt[i1];
		}
	}
	return 0;
}

//======================( �Q���� )==============================
//		2D�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect2D MgVect2D::Unitize() const					//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::LenVect2D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"));
	MREAL	d2 = 1.f / d1;
    return	MgVect2D(x * d2, y * d2);
}

//======================( �Q���� )==============================
//		2D�x�N�g�����g���[�X����
//
void MgVect2D::Print(MCHAR* s) const							// Print
{
#ifdef LOGOUT
	MBLOGOUT( Mstr( "%s	MgVect2D	: (%7.1f,%7.1f)\n"), s, x, y);
#endif
}

//======================( �Q���� )==============================
//		2D�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect2D MGeo::UnitizeVect2D( const MgVect2D& i_v)				//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::LenVect2D( i_v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"));
	MREAL	d2 = 1.f / d1;
    return	MgVect2D( i_v.x * d2, i_v.y * d2);
}

//======================( �R���� )==============================
//
MgVect3D MGeo::TaniVect3D( const MgVect3D& i_v)
{
	MgVect3D vo;
	MREAL	ax, ay, az;

	ax = MGeo::Abs( i_v.x);
	ay = MGeo::Abs( i_v.y);
	az = MGeo::Abs( i_v.z);
	vo.x = vo.y = vo.z = 1.;

	if (ax > ay && ax > az)	
		vo.x = - ( i_v.y + i_v.z) / i_v.x;
	else if ( ay >= ax && ay >= az)
		vo.y = - ( i_v.x + i_v.z) / i_v.y;
	else					 
		vo.z = - ( i_v.x + i_v.y) / i_v.z;

	return MGeo::UnitizeVect3D( vo);
}

//======================( �R���� )==============================
//		�_��̓�����W���߂�
//
int MGeo::PackSamePoint3D( MgPoint3D* io_pPt, int* io_pn)
{
	int iC1, iC2;
	int iN;
	bool bPack;
	if( *io_pn != 0) {
		bPack = false;
		iN = *io_pn;
		iC1 = 0;
		for ( iC2=1; iC2<iN; iC2++) {
			if( io_pPt[iC1] == io_pPt[iC2]) {
				bPack = true;
			} else {
				iC1++;
				if( bPack)
					memcpy( &io_pPt[iC1], &io_pPt[iC2], SZMgPoint2D());
			}
		}
		*io_pn = iC1 + 1;
	}
	return 0;
}


// �_����t���ɂ���
int MGeo::ReversePoint3D( MgPoint3D* i_pPt, int i_n, MgPoint3D* o_pPt)
{
	int i1, i2;
	if( i_pPt == o_pPt) {
		for( i1=0,i2=i_n-1; i1<i2;i1++,i2--) {
			msSwap( o_pPt[i1], o_pPt[i2]);
		}
	} else {
		for( i1=0,i2=i_n-1; i2>=0; i1++,i2--) {
																								//E			memcpy( &o_pPt[i2], &i_pPt[i1], SZMgPoint3D());
			o_pPt[i2] = i_pPt[i1];
		}
	}
	return 0;
}
	// �_�񂩂璼���ɑΏۈʒu�̓_������߂�
	static int SymmetryPointSLine3D( MgPoint3D* i_pPt, int i_n, MgSLine3D& sln, MgPoint3D* o_pPt);

//======================( �R���� )==============================
//		3D�_���g���[�X����
//
void MgPoint3D::Print(MCHAR* s) const							// Print
{
#ifdef LOGOUT
	MBLOGOUT( Mstr( "%s 	MgPoint3D	: (%7.1f, %7.1f, %7.1f)\n"), s, x, y, z);
#endif
}

//======================( �R���� )==============================
//		3D�x�N�g����P�ʃx�N�g���ɕϊ�����
//
MgVect3D MgVect3D::SetUnitize()									//	(  O) �P�ʃx�N�g��
{
	MREAL	d1 = MGeo::LenVect3D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect3D Unitize"));
	MREAL	d2 = 1.f / d1;
	x *= d2;
	y *= d2;
	z *= d2;
	return *this;
}

//======================( �R���� )==============================
//		3D�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect3D MgVect3D::Unitize() const								//	(  O) �P�ʃx�N�g��
{
	MREAL	d1= MGeo::LenVect3D( *this);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect2D MgUnitize"));
	MREAL	d2 = 1.f / d1;
	return MgVect3D( x * d2, y * d2, z * d2);
}

//======================( �R���� )==============================
//		3D�x�N�g�����g���[�X����
//
void MgVect3D::Print(MCHAR* s) const							// Print
{
#ifdef LOGOUT
	MBLOGOUT( Mstr( "%s 	MgVect3D	: (%7.1f, %7.1f, %7.1f)\n"), s, x, y, z);
#endif
}

//======================( �R���� )==============================
//		3D�x�N�g���̒P�ʃx�N�g�������߂�
//
MgVect3D MGeo::UnitizeVect3D( const MgVect3D& i_v)				//	(  O) �P�ʃx�N�g��
{
	MREAL	d1= MGeo::LenVect3D( i_v);
		MBCHECK_ZEROVECT( d1, MBCstr( "MgVect3D MgUnitize"));
	MREAL	d2 = 1.f / d1;
	return MgVect3D( i_v.x * d2, i_v.y * d2, i_v.z * d2);
}

} // namespace MC
