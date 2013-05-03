#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdmGeo.h
//
//		ＭＣＡＤモデル
//						Geometory
//
//==========================================================================================
//	２親を持つ子IDセット
#include	"MdmFig.h"

namespace MC
{

class MdmGeo
{
public:
//		static void Vec2DRotateL90 ( double vec1[2], double vec2[2] );
//		static void Vec2DRotateR90 ( double vec1[2], double vec2[2] );
		static long VecLen ( long nd, double vec[], double *len );
		static long VecAdd ( long nd, double vec1[], double vec2[], double vec[] );
		static long VecSub ( long nd, double vec1[], double vec2[], double vec[] );
		static long Vec2DAngle ( double vec1[2], double vec2[2], double nv, double *agl );
		static long Vec3DAngle ( double vec1[3], double vec2[3], double nv[3], double *agl );
		static long Vec2DAngleAOB ( double pa[2], double po[2], double pb[2], double nv, double *agl );
		static long Vec3DAngleAOB ( double pa[3], double po[3], double pb[3], double nv[3], double *agl );
		static long Vec2DAngleX ( double vec[2], double *agl );
		static long Vec2DAngleY ( double vec[2], double *agl );
		static long Vec3DAngleX ( double vec[3], double *agl );
		static long Vec3DAngleY ( double vec[3], double *agl );
		static long Vec3DAngleZ ( double vec[3], double *agl );
		static long Vec3DAngleXY ( double vec[3], double *agl );
		static long Vec3DAngleYZ ( double vec[3], double *agl );
		static long Vec3DAngleZX ( double vec[3], double *agl );
		static void Vec2DOuterProduct ( double vec1[2], double vec2[2], double *vepr );
		static void Vec3DOuterProduct ( double vec1[3], double vec2[3], double vec[3] );
		static long VecInnerProduct ( long nd, double vec1[], double vec2[], double *vipr );
		static long Vec2DUnit ( double vec1[2], double vec2[2] );
		static long Vec3DUnit ( double vec1[3], double vec2[3] );
		static void Vec2DRotate ( double vec1[2], double agl, double vec2[2] );
		static long VecExpansion ( long nd, double vec1[], double erate, double vec2[] );

		static long Point3DPressSamePoint ( double lp[], long *n );
		static long Point3DPressSamePointV ( double lp[], long *n );
		static long PointPressSamePointEx ( long nd, double lp[], long *n, long m );
		static long PointReverse ( long nd, double lp1[], long n, double lp2[] );
		static long PointMirrorStraight ( long nd, double lp1[], long n, double slin[], double lp2[] );

		static long PLCond2DLine ( double p[2], double lin[4], long *cond );
		static long PLCond3DLine ( double p[3], double lin[6], long *cond );
		static long PLCond2DStraight ( double p[2], double slin[4], long *cond );
		static long PLCond3DStraight ( double p[3], double slin[6], long *cond );
		static long PLCond2DHalf ( double p[2], double hlin[4], long *cond );

		static long LLCond2DStraightStraight ( double slin1[4], double slin2[4], double p[2], long *cond );
		static long LLCond3DStraightStraight ( double slin1[6], double slin2[6], double p[3], long *cond );
		static long LLCond2DLineLine ( double lin1[4], double lin2[4], double p[2], long *cond1, long *cond2 );
		static long LLCond3DLineLine ( double lin1[6], double lin2[6], double p[3], long *cond1, long *cond2 );
		static long LLCond2DLineStraight ( double lin1[4], double slin2[4], double p[2], long *cond );
		static long LLCond2DLineLineOn ( double lin1[4], double lin2[4], long *cond1, long *cond2 );

		static void Matrix2DMult ( double mtx1[6], double mtx2[6], double mtx[6] );
		static void Matrix3DMult ( double mtx1[12], double mtx2[12], double mtx[12] );
		static void MatrixMult44 ( double mtx1[16], double mtx2[16], double mtx[16] );
		static long Matrix2DInverse ( double mtx1[6], double mtx2[6] );
		static long Matrix3DInverse ( double mtx1[12], double mtx2[12] );
		static void Matrix3DGetMove ( double vec[3], double mtx[12] );
		static long Matrix3DGetExpansion ( double xerate, double yerate, double zerate, double mtx[12] );
		static long Matrix3DGetMirror ( double pl[6], double mtx[12] );
		static void Matrix2DGetRotateP ( double p[2], double agl, double mtx[6] );
		static long Matrix3DGetRotateL ( double axis[6], double agl, double mtx[12] );
		static void Matrix3DGetRotateX ( double agl, double mtx[12] );
		static void Matrix3DGetRotateY ( double agl, double mtx[12] );
		static void Matrix3DGetRotateZ ( double agl, double mtx[12] );
		static void Matrix2DGetFromTbl ( double tbl[6], double mtx[6] );
		static void Matrix3DGetFromTbl ( double tbl[12], double mtx[12] );
		static long Matrix2DTransPoint ( double mtx[6], double p1[], long n, double p2[] );
		static long Matrix3DTransPoint ( double mtx[12], double p1[], long n, double p2[] );
		static long Matrix2DTransVec ( double mtx[6], double vec1[], long n, double vec2[] );
		static long Matrix3DTransVec ( double mtx[12], double vec1[], long n, double vec2[] );

		static long Line2DParallelStraight ( double slin1[4], double dd, double slin2[4] );

		static long DisPointPoint ( long nd, double p1[], double p2[], double *len );
		static long DisPointPointSq ( long nd, double p1[], double p2[], double *lensq );
		static long DisFootStraight ( long nd, double p1[], double slin[], double p2[] );
		static long DisFootLine ( long nd, double p1[], double lin[], double p2[], long *cond );
		static long Dis3DFootPolygon ( double lp[], long n, double nv[3], double p1[3], double p2[3], double *idx, long *cond );
		static void Dis3DFootPlane ( double pl[6], double p1[3], double *len, double p2[3] );
		static long Dis2DFootArc ( double p1[2], double arc[7], double p2[2], double *len );

		static long Div2DAngle ( double pa[2], double po[2], double pb[2], long n, double *agl, double p[] );
		static long DivLine ( long nd, double lin[], long n, double *dis, double p[] );
		static long Div2DCircle ( double cir[3], long n, double agl, double p[] );
		static long Div3DCircle ( double cir[7], long n, double ps[3], double p[] );
		static long Div2DArc ( double arc[7], long n, double p[], double *agl );
		static long Div3DArc ( double arc[13], long n, double p[], double *agl );
		static long Div2DEllipse ( double el[8], long n, double p[] );
		static long Div3DEllipse ( double el[14], long n, double p[] );
		static long Div2DEllipseArc ( double ela[10], long n, double p[] );
		static long Div3DEllipseArc ( double ela[17], long n, double p[] );

		static long Loop2DCheckLoop ( double lp1[], long n1, double box1[4], double lp2[], long n2, double box2[4], long *cond );
		static long Loop2DCheckCross ( double lp[], long n, long *cond );
		static long Loop2DCheckPoint ( double p[2], double lp[], long n, double box[4], long *cond );
		static long Loop2DCrossPointStraight ( double slin[4], double lp[], long n, double p[], long siz, long *ars );
		static long Loop2DGetInnerLineStraight ( double lp[], long n, double box[4], double slin[4], double lin[], long siz, long *ars );
		static long Loop2DGetInnerLineLoop ( double lp1[], long n1, double lp2[], long n2, double lin[], long siz, long *ars );
		static long Loop2DAddHole ( double lp1[], long n1, double lp2[], long n2, double lp3[], long siz, long *ars );
		static long Loop2DCreate ( double lin[], long n1, double lp[], long siz1, long n2[], long siz2, long *ars );

		static long Polygon2DCheckDirection ( double lp[], long n, long *cond );
		static long Polygon2DLen ( double lp[], long n, double *len );
		static long Polygon2DGetArea ( double lp[], long n, double *area );
		static long Polygon3DGetAreaVec ( double lp[], long n, double avec[3] );
		static long Polygon3DGetAreaVecV ( double lp[], long n, double avec[3] );
		static long Polygon3DGetAreaVecEx ( double lp[], long n, long m, double avec[3] );
		static long Polygon3DGetNVec ( double lp[], long n, double vec[3] );
		static long Polygon3DGetNVecV ( double lp[], long n, double vec[3] );
		static long Polygon3DGetNVecEx ( double lp[], long n, long m, double vec[3] );
		static long Polygon2DGravityPoint ( double lp[], long n, double p[2] );
		static long Polygon3DGravityPoint ( double lp[], long n, double p[3] );
		static long Polygon2DGetBox ( double lp[], long n, double box[4] );
		static long Polygon2DDivideTriangle ( double lp1[], long n1, double lp2[], long siz, long *ars );
		static long Triangle2DCreate( double p[], long n, double triangle[], long siz, long *ars );
		static long Triangle3DCreate( double p[], long n, double triangle[], long siz, long *ars );
		static long Triangle2DAltitude( double triangle[6], double lin1[4], double lin2[4] );

		static void PlaneCond3DPoint ( double pl[6], double p[3], long *cond );
		static long PlaneCond3DLine ( double pl[6], double lin[6], double p[3], long *cond1, long *cond2 );
		static long PlaneCond3DStraight ( double pl[6], double slin[6], double p[3], long *cond );
		static void PlaneCond3DPlane ( double pl1[6], double pl2[6], double lin[6], long *cond );
		static void PlaneCond3DCheckSame ( double pl1[6], double pl2[6], long *cond );

		static long Circle2DCondPoint ( double cir[3], double p[2], long *cond );
		static long Circle2DCondLine ( double cir[3], double lin[4], double p[4], long *cond1, long *cond2 );
		static long Circle2DCondStraight ( double cir[3], double slin[4], double p[4], long *cond );
		static long Circle2DCondCircle ( double cir1[3], double cir2[3], double p[4], long *cond );
		static long Circle2DTangentPoint ( double cir[3], double p[2], double lin[8], long *ars );
		static long Circle2DTangentCircle ( double cir1[3], double cir2[3], double lin[16], long *ars );
		static long Circle2DTangentArc ( double cir[3], double arc[7], double lin[16], long *ars );
		static long Circle2DInscribe2Line ( double lin1[4], double lin2[4], double r, double p[2], double cir[3] );

		static void Arc2DGetAngle ( double arc[7], double *agl );
		static void Arc3DGetAngle ( double arc[13], double *agl );
		static void Arc2DGetMidPoint ( double arc[7], double p[2] );
		static void Arc3DGetMidPoint ( double arc[13], double p[3] );
		static long Arc2DGetLen ( double arc[7], double *len );
		static long Arc2DGetSectorArea ( double arc[7], double *area );
		static long Arc2DGetChordArea ( double arc[7], double *area );
		static long Arc2DGetSectorGravityPoint ( double arc[7], double p[2] );
		static long Arc2DGetChordGravityPoint ( double arc[7], double p[2] );
		static long Arc2DCondPoint ( double arc[7], double p[2], long *cond );
		static void Arc2DCondPointOnCircle ( double arc[7], double p[2], long *cond );
		static long Arc3DCondPoint ( double arc[13], double p[3], long *cond );
		static long Arc2DCondLine ( double arc[7], double lin[4], double p[4], long *ars, long *cond );
		static long Arc2DCondStraight ( double arc[7], double slin[4], double p[4], long *cond1, long *cond2 );
		static long Arc2DCondArc ( double arc1[7], double arc2[7], double p[8], long *ars, long *cond );
		static void Arc2DCondArcOnCircle ( double arc1[7], double arc2[7], long *ars, double p[8], long cond1[4], long cond2[4] );
		static long Arc2DCondSector ( double arc[7], double p[2], long *cond );
		static long Arc2DTangentPoint ( double arc[7], double p[2], double lin[8], long *ars, long *cond1, long *cond2 );
		static long Arc2DTangentArc ( double arc1[7], double arc2[7], double lin[16], long *ars );
		static long Arc2DCreate3Point ( double ps[2], double pe[2], double pp[2], double po[2], double *r );
		static long Arc3DCreate3Point ( double ps[3], double pe[3], double pp[3], double po[3], double *r, double nv[3] );
		static long Arc2DInscribe2Line ( double lin1[4], double lin2[4], double r, double p[2], double arc[7] );
		static long Arc2DFixAngle ( long flg, double *fig, double *p );	//	端点を指定し、角度を維持した円弧の中心点、半径を得る（2d）
		static long Arc3DFixAngle ( long flg, double *fig, double *p );	//	端点を指定し、角度を維持した円弧の中心点、半径を得る（3d）
		static void Arc2DGetLengthPoint( double arc[], double len, double p[] );
		static void Arc3DGetLengthPoint( double arc[], double len, double p[] );

		static double __stdcall EtcGetEps ();
		static long   __stdcall EtcSetEps ( double eps );
		static double __stdcall EtcGetPi ();
		static double __stdcall ToDegree ( double agl );
		static double __stdcall ToRadian ( double agl );

		static void Tbl2DMult ( double tbl1[6], double tbl2[6], double tbl[6] );
		static void Tbl3DMult ( double tbl1[12], double tbl2[12], double tbl[12] );
		static void Tbl2DInverse ( double tbl1[6], double tbl2[6] );
		static long Tbl3DInverse ( double tbl1[12], double tbl2[12] );
		static void Tbl2DGet ( double po[2], double px[2], double tbl[6] );
		static void Tbl3DGet ( double po[3], double px[3], double pxy[3], double tbl[12] );


		static void Tbl2DGetUnit ( double tbl[6] );
		static void Tbl3DGetUnit ( double tbl[12] );
		static long Tbl3DGetFromLoop ( double lp[], long n, double tbl[12] );
		static long Tbl3DGetFromLoopV ( double lp[], long n, double tbl[12] );
		static void Tbl2DGetFromMatrix ( double mtx[6], double tbl[6] );
		static void Tbl3DGetFromMatrix ( double mtx[12], double tbl[12] );
		static void Tbl3DUnit ( double tbl1[12], double tbl2[12] );
		static long Tbl3DGetBaseXYZ ( long mode, double tbl[12] );
		static long Tbl2DTransPoint ( double tbl[6], double p1[], long n, double p2[] );
		static long Tbl3DTransPoint ( double tbl[12], double p1[], long n, double p2[] );
		static long Tbl2DTransVec ( double tbl[6], double vec1[], long n, double vec2[] );
		static long Tbl3DTransVec ( double tbl[12], double vec1[], long n, double vec2[] );
		static long TblTransPoint32 ( double tbl[12], double p1[], long n, double p2[] );
		static long TblTransPoint23 ( double tbl[12], double p1[], long n, double p2[] );

		static long Ellipse2DCreate ( double p0[2], double px[2], double p1[2], double el[8] );
		static long Ellipse3DCreate ( double p0[3], double px[3], double p1[3], double el[14] );

};

} // namespace MC
