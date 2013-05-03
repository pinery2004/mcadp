//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdGeo.cpp
//
//		論理演算
//
//
//  K.Matsu           13/05/03    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MlLog.h"
#include "MgDefine.h"

#include "MdModel.h"
#define DLL_EXPORT_DGRP_DO
#include "MdmGeo.h"
#include "Mdm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace MC
{

////===========================================================================
////		ベクトルを半時計回りに90度回転したベクトルを求める
////
//void MdmGeo::Vec2DRotateL90 (
//					MgVect2&		vec1,		// 
//					MgVect2*		vec2		// 
//				)
//{
//}

//void MdmGeo::Vec2DRotateL90 ( double vec1[2], double vec2[2] ) { };
//void MdmGeo::Vec2DRotateR90 ( double vec1[2], double vec2[2] ) { };
long MdmGeo::VecLen ( long nd, double vec[], double *len ) { return 0;};
long MdmGeo::VecAdd ( long nd, double vec1[], double vec2[], double vec[] ) { return 0;};
long MdmGeo::VecSub ( long nd, double vec1[], double vec2[], double vec[] ) { return 0;};
long MdmGeo::Vec2DAngle ( double vec1[2], double vec2[2], double nv, double *agl ) { return 0;};
long MdmGeo::Vec3DAngle ( double vec1[3], double vec2[3], double nv[3], double *agl ) { return 0;};
long MdmGeo::Vec2DAngleAOB ( double pa[2], double po[2], double pb[2], double nv, double *agl ) { return 0;};
long MdmGeo::Vec3DAngleAOB ( double pa[3], double po[3], double pb[3], double nv[3], double *agl ) { return 0;};
long MdmGeo::Vec2DAngleX ( double vec[2], double *agl ) { return 0;};
long MdmGeo::Vec2DAngleY ( double vec[2], double *agl ) { return 0;};
long MdmGeo::Vec3DAngleX ( double vec[3], double *agl ) { return 0;};
long MdmGeo::Vec3DAngleY ( double vec[3], double *agl ) { return 0;};
long MdmGeo::Vec3DAngleZ ( double vec[3], double *agl ) { return 0;};
long MdmGeo::Vec3DAngleXY ( double vec[3], double *agl ) { return 0;};
long MdmGeo::Vec3DAngleYZ ( double vec[3], double *agl ) { return 0;};
long MdmGeo::Vec3DAngleZX ( double vec[3], double *agl ) { return 0;};
void MdmGeo::Vec2DOuterProduct ( double vec1[2], double vec2[2], double *vepr ) { };
void MdmGeo::Vec3DOuterProduct ( double vec1[3], double vec2[3], double vec[3] ) { };
long MdmGeo::VecInnerProduct ( long nd, double vec1[], double vec2[], double *vipr ) { return 0;};
long MdmGeo::Vec2DUnit ( double vec1[2], double vec2[2] ) { return 0;};
long MdmGeo::Vec3DUnit ( double vec1[3], double vec2[3] ) { return 0;};
//void MdmGeo::Vec2DRotate ( double vec1[2], double agl, double vec2[2] ) { };
long MdmGeo::VecExpansion ( long nd, double vec1[], double erate, double vec2[] ) { return 0;};

long MdmGeo::Point3DPressSamePoint ( double lp[], long *n ) { return 0;};
long MdmGeo::Point3DPressSamePointV ( double lp[], long *n ) { return 0;};
long MdmGeo::PointPressSamePointEx ( long nd, double lp[], long *n, long m ) { return 0;};
long MdmGeo::PointReverse ( long nd, double lp1[], long n, double lp2[] ) { return 0;};
long MdmGeo::PointMirrorStraight ( long nd, double lp1[], long n, double slin[], double lp2[] ) { return 0;};

long MdmGeo::PLCond2DLine ( double p[2], double lin[4], long *cond ) { return 0;};
long MdmGeo::PLCond3DLine ( double p[3], double lin[6], long *cond ) { return 0;};
long MdmGeo::PLCond2DStraight ( double p[2], double slin[4], long *cond ) { return 0;};
long MdmGeo::PLCond3DStraight ( double p[3], double slin[6], long *cond ) { return 0;};
long MdmGeo::PLCond2DHalf ( double p[2], double hlin[4], long *cond ) { return 0;};

long MdmGeo::LLCond2DStraightStraight ( double slin1[4], double slin2[4], double p[2], long *cond ) { return 0;};
long MdmGeo::LLCond3DStraightStraight ( double slin1[6], double slin2[6], double p[3], long *cond ) { return 0;};
long MdmGeo::LLCond2DLineLine ( double lin1[4], double lin2[4], double p[2], long *cond1, long *cond2 ) { return 0;};
long MdmGeo::LLCond3DLineLine ( double lin1[6], double lin2[6], double p[3], long *cond1, long *cond2 ) { return 0;};
long MdmGeo::LLCond2DLineStraight ( double lin1[4], double slin2[4], double p[2], long *cond ) { return 0;};
long MdmGeo::LLCond2DLineLineOn ( double lin1[4], double lin2[4], long *cond1, long *cond2 ) { return 0;};

void MdmGeo::Matrix2DMult ( double mtx1[6], double mtx2[6], double mtx[6] ) { };
void MdmGeo::Matrix3DMult ( double mtx1[12], double mtx2[12], double mtx[12] ) { };
void MdmGeo::MatrixMult44 ( double mtx1[16], double mtx2[16], double mtx[16] ) { };
long MdmGeo::Matrix2DInverse ( double mtx1[6], double mtx2[6] ) { return 0;};
long MdmGeo::Matrix3DInverse ( double mtx1[12], double mtx2[12] ) { return 0;};
void MdmGeo::Matrix3DGetMove ( double vec[3], double mtx[12] ) { };
long MdmGeo::Matrix3DGetExpansion ( double xerate, double yerate, double zerate, double mtx[12] ) { return 0;};
long MdmGeo::Matrix3DGetMirror ( double pl[6], double mtx[12] ) { return 0;};
void MdmGeo::Matrix2DGetRotateP ( double p[2], double agl, double mtx[6] ) { };
long MdmGeo::Matrix3DGetRotateL ( double axis[6], double agl, double mtx[12] ) { return 0;};
void MdmGeo::Matrix3DGetRotateX ( double agl, double mtx[12] ) { };
void MdmGeo::Matrix3DGetRotateY ( double agl, double mtx[12] ) { };
void MdmGeo::Matrix3DGetRotateZ ( double agl, double mtx[12] ) { };
void MdmGeo::Matrix2DGetFromTbl ( double tbl[6], double mtx[6] ) { };
void MdmGeo::Matrix3DGetFromTbl ( double tbl[12], double mtx[12] ) { };
long MdmGeo::Matrix2DTransPoint ( double mtx[6], double p1[], long n, double p2[] ) { return 0;};
long MdmGeo::Matrix3DTransPoint ( double mtx[12], double p1[], long n, double p2[] ) { return 0;};
long MdmGeo::Matrix2DTransVec ( double mtx[6], double vec1[], long n, double vec2[] ) { return 0;};
long MdmGeo::Matrix3DTransVec ( double mtx[12], double vec1[], long n, double vec2[] ) { return 0;};

long MdmGeo::Line2DParallelStraight ( double slin1[4], double dd, double slin2[4] ) { return 0;};

long MdmGeo::DisPointPoint ( long nd, double p1[], double p2[], double *len ) { return 0;};
long MdmGeo::DisPointPointSq ( long nd, double p1[], double p2[], double *lensq ) { return 0;};
long MdmGeo::DisFootStraight ( long nd, double p1[], double slin[], double p2[] ) { return 0;};
long MdmGeo::DisFootLine ( long nd, double p1[], double lin[], double p2[], long *cond ) { return 0;};
long MdmGeo::Dis3DFootPolygon ( double lp[], long n, double nv[3], double p1[3], double p2[3], double *idx, long *cond ) { return 0;};
void MdmGeo::Dis3DFootPlane ( double pl[6], double p1[3], double *len, double p2[3] ) { };
long MdmGeo::Dis2DFootArc ( double p1[2], double arc[7], double p2[2], double *len ) { return 0;};

long MdmGeo::Div2DAngle ( double pa[2], double po[2], double pb[2], long n, double *agl, double p[] ) { return 0;};
long MdmGeo::DivLine ( long nd, double lin[], long n, double *dis, double p[] ) { return 0;};
long MdmGeo::Div2DCircle ( double cir[3], long n, double agl, double p[] ) { return 0;};
long MdmGeo::Div3DCircle ( double cir[7], long n, double ps[3], double p[] ) { return 0;};
long MdmGeo::Div2DArc ( double arc[7], long n, double p[], double *agl ) { return 0;};
long MdmGeo::Div3DArc ( double arc[13], long n, double p[], double *agl ) { return 0;};
long MdmGeo::Div2DEllipse ( double el[8], long n, double p[] ) { return 0;};
long MdmGeo::Div3DEllipse ( double el[14], long n, double p[] ) { return 0;};
long MdmGeo::Div2DEllipseArc ( double ela[10], long n, double p[] ) { return 0;};
long MdmGeo::Div3DEllipseArc ( double ela[17], long n, double p[] ) { return 0;};

long MdmGeo::Loop2DCheckLoop ( double lp1[], long n1, double box1[4], double lp2[], long n2, double box2[4], long *cond ) { return 0;};
long MdmGeo::Loop2DCheckCross ( double lp[], long n, long *cond ) { return 0;};
long MdmGeo::Loop2DCheckPoint ( double p[2], double lp[], long n, double box[4], long *cond ) { return 0;};
long MdmGeo::Loop2DCrossPointStraight ( double slin[4], double lp[], long n, double p[], long siz, long *ars ) { return 0;};
long MdmGeo::Loop2DGetInnerLineStraight ( double lp[], long n, double box[4], double slin[4], double lin[], long siz, long *ars ) { return 0;};
long MdmGeo::Loop2DGetInnerLineLoop ( double lp1[], long n1, double lp2[], long n2, double lin[], long siz, long *ars ) { return 0;};
long MdmGeo::Loop2DAddHole ( double lp1[], long n1, double lp2[], long n2, double lp3[], long siz, long *ars ) { return 0;};
long MdmGeo::Loop2DCreate ( double lin[], long n1, double lp[], long siz1, long n2[], long siz2, long *ars ) { return 0;};

long MdmGeo::Polygon2DCheckDirection ( double lp[], long n, long *cond ) { return 0;};
long MdmGeo::Polygon2DLen ( double lp[], long n, double *len ) { return 0;};
long MdmGeo::Polygon2DGetArea ( double lp[], long n, double *area ) { return 0;};
long MdmGeo::Polygon3DGetAreaVec ( double lp[], long n, double avec[3] ) { return 0;};
long MdmGeo::Polygon3DGetAreaVecV ( double lp[], long n, double avec[3] ) { return 0;};
long MdmGeo::Polygon3DGetAreaVecEx ( double lp[], long n, long m, double avec[3] ) { return 0;};
long MdmGeo::Polygon3DGetNVec ( double lp[], long n, double vec[3] ) { return 0;};
long MdmGeo::Polygon3DGetNVecV ( double lp[], long n, double vec[3] ) { return 0;};
long MdmGeo::Polygon3DGetNVecEx ( double lp[], long n, long m, double vec[3] ) { return 0;};
long MdmGeo::Polygon2DGravityPoint ( double lp[], long n, double p[2] ) { return 0;};
long MdmGeo::Polygon3DGravityPoint ( double lp[], long n, double p[3] ) { return 0;};
long MdmGeo::Polygon2DGetBox ( double lp[], long n, double box[4] ) { return 0;};
long MdmGeo::Polygon2DDivideTriangle ( double lp1[], long n1, double lp2[], long siz, long *ars ) { return 0;};
long MdmGeo::Triangle2DCreate( double p[], long n, double triangle[], long siz, long *ars ) { return 0;};
long MdmGeo::Triangle3DCreate( double p[], long n, double triangle[], long siz, long *ars ) { return 0;};
long MdmGeo::Triangle2DAltitude( double triangle[6], double lin1[4], double lin2[4] ) { return 0;};

void MdmGeo::PlaneCond3DPoint ( double pl[6], double p[3], long *cond ) { };
long MdmGeo::PlaneCond3DLine ( double pl[6], double lin[6], double p[3], long *cond1, long *cond2 ) { return 0;};
long MdmGeo::PlaneCond3DStraight ( double pl[6], double slin[6], double p[3], long *cond ) { return 0;};
void MdmGeo::PlaneCond3DPlane ( double pl1[6], double pl2[6], double lin[6], long *cond ) { };
void MdmGeo::PlaneCond3DCheckSame ( double pl1[6], double pl2[6], long *cond ) { };

long MdmGeo::Circle2DCondPoint ( double cir[3], double p[2], long *cond ) { return 0;};
long MdmGeo::Circle2DCondLine ( double cir[3], double lin[4], double p[4], long *cond1, long *cond2 ) { return 0;};
long MdmGeo::Circle2DCondStraight ( double cir[3], double slin[4], double p[4], long *cond ) { return 0;};
long MdmGeo::Circle2DCondCircle ( double cir1[3], double cir2[3], double p[4], long *cond ) { return 0;};
long MdmGeo::Circle2DTangentPoint ( double cir[3], double p[2], double lin[8], long *ars ) { return 0;};
long MdmGeo::Circle2DTangentCircle ( double cir1[3], double cir2[3], double lin[16], long *ars ) { return 0;};
long MdmGeo::Circle2DTangentArc ( double cir[3], double arc[7], double lin[16], long *ars ) { return 0;};
long MdmGeo::Circle2DInscribe2Line ( double lin1[4], double lin2[4], double r, double p[2], double cir[3] ) { return 0;};

void MdmGeo::Arc2DGetAngle ( double arc[7], double *agl ) { };
void MdmGeo::Arc3DGetAngle ( double arc[13], double *agl ) { };
void MdmGeo::Arc2DGetMidPoint ( double arc[7], double p[2] ) { };
void MdmGeo::Arc3DGetMidPoint ( double arc[13], double p[3] ) { };
long MdmGeo::Arc2DGetLen ( double arc[7], double *len ) { return 0;};
long MdmGeo::Arc2DGetSectorArea ( double arc[7], double *area ) { return 0;};
long MdmGeo::Arc2DGetChordArea ( double arc[7], double *area ) { return 0;};
long MdmGeo::Arc2DGetSectorGravityPoint ( double arc[7], double p[2] ) { return 0;};
long MdmGeo::Arc2DGetChordGravityPoint ( double arc[7], double p[2] ) { return 0;};
long MdmGeo::Arc2DCondPoint ( double arc[7], double p[2], long *cond ) { return 0;};
void MdmGeo::Arc2DCondPointOnCircle ( double arc[7], double p[2], long *cond ) { };
long MdmGeo::Arc3DCondPoint ( double arc[13], double p[3], long *cond ) { return 0;};
long MdmGeo::Arc2DCondLine ( double arc[7], double lin[4], double p[4], long *ars, long *cond ) { return 0;};
long MdmGeo::Arc2DCondStraight ( double arc[7], double slin[4], double p[4], long *cond1, long *cond2 ) { return 0;};
long MdmGeo::Arc2DCondArc ( double arc1[7], double arc2[7], double p[8], long *ars, long *cond ) { return 0;};
void MdmGeo::Arc2DCondArcOnCircle ( double arc1[7], double arc2[7], long *ars, double p[8], long cond1[4], long cond2[4] ) { };
long MdmGeo::Arc2DCondSector ( double arc[7], double p[2], long *cond ) { return 0;};
long MdmGeo::Arc2DTangentPoint ( double arc[7], double p[2], double lin[8], long *ars, long *cond1, long *cond2 ) { return 0;};
long MdmGeo::Arc2DTangentArc ( double arc1[7], double arc2[7], double lin[16], long *ars ) { return 0;};
long MdmGeo::Arc2DCreate3Point ( double ps[2], double pe[2], double pp[2], double po[2], double *r ) { return 0;};
long MdmGeo::Arc3DCreate3Point ( double ps[3], double pe[3], double pp[3], double po[3], double *r, double nv[3] ) { return 0;};
long MdmGeo::Arc2DInscribe2Line ( double lin1[4], double lin2[4], double r, double p[2], double arc[7] ) { return 0;};
long MdmGeo::Arc2DFixAngle ( long flg, double *fig, double *p ) { return 0;};	//	端点を指定し、角度を維持した円弧の中心点、半径を得る（2d）
long MdmGeo::Arc3DFixAngle ( long flg, double *fig, double *p ) { return 0;};	//	端点を指定し、角度を維持した円弧の中心点、半径を得る（3d）
void MdmGeo::Arc2DGetLengthPoint( double arc[], double len, double p[] ) { };
void MdmGeo::Arc3DGetLengthPoint( double arc[], double len, double p[] ) { };

double MdmGeo::EtcGetEps () { return 0;};
long   MdmGeo::EtcSetEps ( double eps ) { return 0;};
double MdmGeo::EtcGetPi () { return 0;};
double MdmGeo::ToDegree ( double agl ) { return 0;};
double MdmGeo::ToRadian ( double agl ) { return 0;};

void MdmGeo::Tbl2DMult ( double tbl1[6], double tbl2[6], double tbl[6] ) { };
void MdmGeo::Tbl3DMult ( double tbl1[12], double tbl2[12], double tbl[12] ) { };
void MdmGeo::Tbl2DInverse ( double tbl1[6], double tbl2[6] ) { };
long MdmGeo::Tbl3DInverse ( double tbl1[12], double tbl2[12] ) { return 0;};
void MdmGeo::Tbl2DGet ( double po[2], double px[2], double tbl[6] ) { };
void MdmGeo::Tbl3DGet ( double po[3], double px[3], double pxy[3], double tbl[12] ) { };


void MdmGeo::Tbl2DGetUnit ( double tbl[6] ) { };
void MdmGeo::Tbl3DGetUnit ( double tbl[12] ) { };
long MdmGeo::Tbl3DGetFromLoop ( double lp[], long n, double tbl[12] ) { return 0;};
long MdmGeo::Tbl3DGetFromLoopV ( double lp[], long n, double tbl[12] ) { return 0;};
void MdmGeo::Tbl2DGetFromMatrix ( double mtx[6], double tbl[6] ) { };
void MdmGeo::Tbl3DGetFromMatrix ( double mtx[12], double tbl[12] ) { };
void MdmGeo::Tbl3DUnit ( double tbl1[12], double tbl2[12] ) { };
long MdmGeo::Tbl3DGetBaseXYZ ( long mode, double tbl[12] ) { return 0;};
long MdmGeo::Tbl2DTransPoint ( double tbl[6], double p1[], long n, double p2[] ) { return 0;};
long MdmGeo::Tbl3DTransPoint ( double tbl[12], double p1[], long n, double p2[] ) { return 0;};
long MdmGeo::Tbl2DTransVec ( double tbl[6], double vec1[], long n, double vec2[] ) { return 0;};
long MdmGeo::Tbl3DTransVec ( double tbl[12], double vec1[], long n, double vec2[] ) { return 0;};
long MdmGeo::TblTransPoint32 ( double tbl[12], double p1[], long n, double p2[] ) { return 0;};
long MdmGeo::TblTransPoint23 ( double tbl[12], double p1[], long n, double p2[] ) { return 0;};

long MdmGeo::Ellipse2DCreate ( double p0[2], double px[2], double p1[2], double el[8] ) { return 0;};
long MdmGeo::Ellipse3DCreate ( double p0[3], double px[3], double p1[3], double el[14] ) { return 0;};

} // namespace MC
