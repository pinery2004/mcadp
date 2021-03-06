#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgDefine.h 
//	CPR
// 
//	説明
//
//	MCADで使用する用語の定義
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <TCHAR.h>
#include <float.h>
#include <limits.h>
#define		_USE_MATH_DEFINES 
#include <math.h>
#include <time.h>

#ifndef	WINVER
#define		WINVER		 0x0501
#endif

#define	MGPTOL (&g_gTol)

//===========================================================================
//		図形演算 選択条件／ステータス
#define		MC_UNDEF			0				// 未設定状態

#define		MC_NINT				0x001			// 交差なし
#define		MC_INT				0x002			// 交差あり
#define		MC_REP				0x004			// 重なり
#define		MC_CONNECTION		0x010			// 接続：平行
#define		MC_MATCH			0x020			// 選択条件に合う線分あり
#define		MC_PARALLEL			0x100			// 無接続：平行
#define		MC_TWIST			0x200			// ねじれ

#define		MC_SAME_DIR			0x1000			// 辺上同一方向
#define		MC_REV_DIR			0x2000			// 辺上逆方向

#define		MC_ON_PS			0x001			// 点が線分の始点上
#define		MC_INSIDE			0x002			// 点が線分の内側上
#define		MC_ON_PE			0x004			// 点が線分の終点上
#define		MC_OUT_PS			0x010			// 点が線分の始点側延長線上
#define		MC_OUT_PE			0x040			// 点が線分の終点側延長線上

#define		MC_LEFT				0x100			// 点が線分の左側
#define		MC_ON_SLINE			0x200			// 点が線分または延長直線上
#define		MC_RIGHT			0x400			// 点が線分の右側

#define		MC_CLOSS			0x1000			// 線分が線分と交差

#define		MC_NEAR_PS			0x010			// 始点が終点より近い
#define		MC_NEAR_PE			0x020			// 終点が始点より近い

#define		MC_FAR_PS			0x002			// 始点が終点より離れている
#define		MC_FAR_PE			0x001			// 終点が始点より離れている

#define		MC_ROT_LEFT			0x010			// 左回転
#define		MC_ROT_RIGHT		0x040			// 右回転
#define		MC_REAL				0x010			// 実ポリゴン
#define		MC_HOLE				0x040			// 穴ポリゴン

#define		MC_OR				0x001			// 和
#define		MC_DIFF				0x002			// 差
#define		MC_AND				0x004			// 積

#define		MC_IN_BORDER		0x001			// 点が多角形の内側
#define		MC_ON_BORDER		0x002			// 点が多角形の辺上
#define		MC_OUT_BORDER		0x004			// 点が多角形の外側

#define		MC_ON_SIDE_SAME		0x010			// 線分方向と同一方向の辺上
#define		MC_ON_SIDE_REV		0x020			// 線分方向と逆方向の辺上
#define		MC_ON_SIDE			0x030			// 辺上（線分方向指定無し）
#define		MC_ON_TOP			0x040			// 頂点上

#define		MC_UPPER			0x010			// 点が平面の表側（法線ベクトル方向）
#define		MC_ON_PLANE			0x020			// 点が平面上
#define		MC_LOWER			0x040			// 点が平面の裏側（法線ベクトル逆方向）

#define		MC_PS_UPPER			0x001			// 始点が平面の表側（法線ベクトル方向）
#define		MC_PS_ON_PLANE		0x002			// 始点が平面上
#define		MC_PS_LOWER			0x004			// 始点が平面の裏側（法線ベクトル逆方向）

#define		MC_PE_UPPER			0x010			// 終点が平面の表側（法線ベクトル方向）
#define		MC_PE_ON_PLANE		0x020			// 終点が平面上
#define		MC_PE_LOWER			0x040			// 終点が平面の裏側（法線ベクトル逆方向）

//===========================================================================
//	図形演算ステータス	(システムエラー)

#define		MC_ERR_INPUT	   1100				// 入力エラー
#define		MC_ERR_NUM_OVER	   1101				// 処理可能個数超えエラー
//#define	MC_ERR_BAD_SPLINE  1102				// 
#define		MC_ERR_VECT_ZERO   1103				// ゼロベクトルで処理不可エラー
#define		MC_ERR_VALUE_ZERO  1104				// 数値ゼロで処理不可エラー
#define		MC_ERR_OFFSET	   1105				// オフセット誤りエラー


//===========================================================================
//		図形演算 作業領域サイズ
#define		MX_PNT0				 20				// 点バッファサイズ０
#define		MX_PNT1				 40				// 点バッファサイズ１
#define		MX_PNT2				130				// 点バッファサイズ２
#define		MX_PNT3				400				// 点バッファサイズ３
#define		MX_PNT4			   1300				// 点バッファサイズ４
#define		MX_PNT5			   4000				// 点バッファサイズ５
#define		MX_LIN0				 20				// 線分バッファサイズ０
#define		MX_LIN1				 40				// 線分バッファサイズ１
#define		MX_LIN2				130				// 線分バッファサイズ２
#define		MX_LIN3				400				// 線分バッファサイズ３
#define		MX_LIN4			   1300				// 線分バッファサイズ４
#define		MX_LIN5			   4000				// 線分バッファサイズ５

//===========================================================================
//
//	マクロ定義
//

#define		MGABS(X) 			(((X) > 0)		? (X)  : -(X))
#define		MGMAX(X1, X2) 		(((X1) > (X2))	? (X1) : (X2))
#define		MGMIN(X1, X2) 		(((X1) < (X2))	? (X1) : (X2))
#define		MGSIGN(X) 			(((X) > 0)		?  1   : -1)
#define		MGLEFT(X)			((X) > 0)
#define		MGRIGHT(X)			((X) < 0)
#define		MGDEGREE(X) 		((X) * MC_RTD)					//	* 180.0f / MC_PIE
#define		MGRADIAN(X) 		((X) * MC_DTR)					//	* MC_PIE / 180.0f

template<class T>
inline T MAX( T& t1, T& t2)
{
	return (((t1) > (t2)) ? (t1) : (t2));
}

//
//	定数で指定したサイズの点データ配列を持つ多角形を作成する
//
//	MGPOLYG( 多角形名, 配列サイズ(定数)); 
//
//	例	MGPOLYG( dd, MX_PNT1);
//			↓
//		MgPoint2D	MPB_dd[MX_PNT1];
//		MgPolyg2D	dd;
//		dd.sz = MX_PNT1;
//		dd.p = MPB_dd;
//
#define		MGPOLYG2( P, M)	MgPoint2D MPB_ ## P[M]; MgPolyg2D P; P.m_isz = M; P.m_p = MPB_ ## P;
//
//	定数で指定したサイズの点データ配列を持つ多角形を作成する
//
//	MGPOLYG3( 多角形名, 配列サイズ(定数)); 
//
//	例	MGPOLYG3( dd, MX_PNT1);
//			↓
//		MgPoint3D	MPB_dd[MX_PNT1];
//		MgPolyg3D	dd;
//		dd.sz = MX_PNT1;
//		dd.p = MPB_dd;
//
#define		MGPOLYG3( P, M)	MgPoint3D MPB_ ## P[M]; MgPolyg3D P; P.m_isz = M; P.m_P = MPB_ ## P;
//
//	定数で指定したサイズの点データ配列を持つ多角形の配列を持つ多角形群を作成する
//
//	MGGPOLYG2( 多角形名, 点配列サイズ１(定数),  点配列サイズ２(定数),  点配列サイズ３(定数)); 
//
//	例	MGGPOLYG2( dd, MX_PNT1, 20, 10);
//			↓
//		MgPolyg2D	MPGB_dd[3];
//		MgPoint2D	MPB1_dd[MX_PNT1];
//		MgPoint2D	MPB2_dd[20];
//		MgPoint2D	MPB3_dd[10];
//		MgGPolyg2D	dd;
//		dd.sz = 3;
//		dd.pg = MPGB_dd;
//		dd.pg[0].sz = MX_PNT1;
//		dd.pg[0].p = MPB1_dd;
//		dd.pg[1].sz = 20;
//		dd.pg[1].p = MPB2_dd;
//		dd.pg[2].sz = 10;
//		dd.pg[2].p = MPB3_dd;
//
#define		MGGPOLYG2( P, M1, M2, M3)\
								MgPolyg2D MPGB_ ## P[3]; MgPoint2D MPB1_ ## P[M1];\
								MgPoint2D MPB2_ ## P[M2]; MgPoint2D MPB3_ ## P[M3];\
								MgGPolyg2D P; P.m_isz = 3; P.m_pg = MPGB_ ## P;\
								P.m_pg[0].m_isz = M1; P.m_pg[0].m_p = MPB1_ ## P;\
								P.m_pg[1].m_isz = M2; P.m_pg[1].m_p = MPB2_ ## P;\
								P.m_pg[2].m_isz = M3; P.m_pg[2].m_p = MPB3_ ## P;
//
//	MBMALCPOLYG( 線分群名, 確保要求サイズ(変数), 初期配列サイズ(定数)); 
//
//	例	MBMALCPOLYG( dd, GPt2->n, MX_PNT1);
//			↓
//		MgPoint2D	MPB_dd[MX_PNT1];
//		MgPolyg2D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.p = (MgPoint2D *)new char[sizeof( MgPoint2D) * GPt2->n];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.p = MLB_dd;
//		}
//
#define		MBMALCPOLYG2( P, S, M)\
								 MgPoint2D MLB_ ## P[M]; MgPolyg2D P;\
								 if (S > M) {P.m_isz = S; P.m_p = (MgPoint2D *)new char[S * sizeof(MgPoint2D)]; MBCHECK_POINTER( P.m_p);}\
								 else {P.sz = M; P.m_p = MLB_ ## P;}
//
//	MBMALCPOLYG3( 線分群名, 確保要求サイズ(変数), 初期配列サイズ(定数)); 
//
//	例	MBMALCPOLYG3( dd, GPt2->n, MX_PNT1);
//			↓
//		MgPoint3D	MPB_dd[MX_PNT1];
//		MgPolyg3D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.p = (MgPoint3D *)new char[GPt2->n * sizeof( MgPoint3D)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.p = MLB_dd;
//		}
//
#define		MBMALCPOLYG3( P, S, M)\
								MgPoint3D MLB_ ## P[M]; MgPolyg3D P;\
								if (S > M) {P.m_isz = S; P.m_p = (MgPoint3D *)new char[S * sizeof(MgPoint3D)]; MBCHECK_POINTER( P.m_p);}\
								else {P.m_isz = M; P.m_p = MLB_ ## P;}
//
//	定数で指定したサイズの点データ配列を持つ多角形の配列を持つ多角形群を作成する
//
//	MGPOLYG( 多角形名, 点配列サイズ１(定数),  点配列サイズ２(定数),  点配列サイズ３(定数)); 
//
//	例	MGGPOLYG3( dd, MX_PNT1, 20, 10);
//			↓
//		MgPolyg3D	MPGB_dd[3];
//		MgPoint3D	MPB1_dd[MX_PNT1];
//		MgPoint3D	MPB2_dd[20];
//		MgPoint3D	MPB3_dd[10];
//		MgGPolyg3D	dd;
//		dd.sz = 3;
//		dd.pg = MPGB_dd;
//		dd.pg[0].sz = MX_PNT1;
//		dd.pg[0].p = MPB1_dd;
//		dd.pg[1].sz = 20;
//		dd.pg[1].p = MPB2_dd;
//		dd.pg[2].sz = 10;
//		dd.pg[2].p = MPB3_dd;
//
#define		MGGPOLYG3( P, M1, M2, M3)\
								MgPolyg3D MPGB_ ## P[3]; MgPoint3D MPB1_ ## P[M1];\
								MgPoint3D MPB2_ ## P[M2]; MgPoint3D MPB3_ ## P[M3];\
								MgGPolyg2D P; P.m_isz = 3; P.m_pg = MPGB_ ## P;\
								P.m_pg[0].m_isz = M1; P.m_pg[0].p = MPB1_ ## P;\
								P.m_pg[1].m_isz = M2; P.m_pg[1].p = MPB2_ ## P;\
								P.m_pg[2].m_isz = M3; P.m_pg[2].p = MPB3_ ## P;
//
//	定数で指定したサイズの線分データ配列を持つ線分群を作成する
//
//	MGGLINE( 線分群名, 配列サイズ(定数)); 
//
//	例	MGGLINE2( dd, MX_PNT1);
//			↓
//		MgLine2D		MLB_dd[MX_PNT1];
//		MgGLine2D		dd;
//		dd.sz = MX_PNT1;
//		dd.ln = MLB_dd;
//
#define		MGGLINE2( P, M)	MgLine2D MLB_ ## P[M]; MgGLine2D P; P.m_isz = M; P.m_ln = MLB_ ## P;
//
//
//	定数で指定したサイズの線分データ配列を持つ線分群を作成する
//
//	MgGLine3D( 線分群名, 配列サイズ(定数)); 
//
//	例	MgGLine3D( dd, MX_PNT1);
//			↓
//		MgLine3D		MLB_dd[MX_PNT1];
//		MgGLine3D	dd;
//		dd.sz = MX_PNT1;
//		dd.ln = MLB_dd;
//
#define		MGGLINE3( P, M)	MgLine3D MLB_ ## P[M]; MgGLine3D P; P.m_isz = M; P.m_ln = MLB_ ## P;
//
//	定数で指定したサイズの線分データ配列を線分群を作成する
//		初期に定数で指定したサイズの配列を定義しているが変数で指定したサイズの方が大きい場合にmallocで作成する。
//		mallocで確保された領域はProgのリターン時に自動的に削除される
//
//	MBMALCGLINE2( 線分群名, 確保要求サイズ(変数), 初期配列サイズ(定数)); 
//
//	例	MBMALCGLINE2( dd, GPt2->n, MX_PNT1);
//			↓
//		MgLine2D		MLB_dd[MX_PNT1];
//		MgGLine2D		dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.ln = (MgLine2D *)new char[GPt2->n * sizeof( MgLine2D)];
//					MBCHECK_POINTER( dd.ln);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.ln = MLB_dd;
//		}
//
#define		MBMALCGLINE2( P, S, M)\
								 MgLine2D MLB_ ## P[M]; MgGLine2D P;\
								 if (S > M) {P.m_isz = S; P.m_ln = (MgLine2D *)new char[S * sizeof(MgLine2D)]; MBCHECK_POINTER( P.m_ln);}\
								 else {P.m_isz = M; P.m_ln = MLB_ ## P;}
//
//	定数で指定したサイズの線分データ配列を線分群を作成する
//		初期に定数で指定したサイズの配列を定義しているが変数で指定したサイズの方が大きい場合にmallocで作成する。
//		mallocで確保された領域はProgのリターン時に自動的に削除される
//
//	MBMALCGLINE3( 線分群名, 確保要求サイズ(変数), 初期配列サイズ(定数)); 
//
//	例	MBMALCGLINE3( dd, GPt2->n, MX_PNT1);
//			↓
//		MgLine3D		MLB_dd[MX_PNT1];
//		MgGLine3D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.ln = (MgLine3D *)new char[GPt2->n * sizeof( MgLine3D)];
//					MBCHECK_POINTER( dd.ln);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.ln = MLB_dd;
//		}
//
#define		MBMALCGLINE3( P, S, M)\
								 MgLine3D MLB_ ## P[M]; MgGLine3D P;\
								 if (S > M) {P.m_isz = S; P.m_ln = (MgLine3D *)new char[S * sizeof(MgLine3D)]; MBCHECK_POINTER( P.m_ln);}\
								 else {P.m_isz = M; P.m_ln = MLB_ ## P;}
//
//
//	定数で指定したサイズの整数データ配列を持つ整数群を作成する
//
//	MGGINT( 整数群名, 配列サイズ(定数)); 
//
//	例	MGGINT( dd, MX_INT1);
//			↓
//		MINT		MIB_dd[MX_INT1];
//		MgGInt		dd;
//		dd.sz = MX_INT1;
//		dd.i = MIB_dd;
//
#define		MGGINT( P, M)	MINT MIB_ ## P[M]; MgGInt P; P.m_isz = M; P.m_i = MIB_ ## P;
//
//	定数で指定したサイズの実数データ配列を持つ実数群を作成する
//
//	MGGFLOAT( 実数群名, 配列サイズ(定数)); 
//
//	例	MGGFLOAT( dd, MX_FLT1);
//			↓
//		MREAL		MFB_dd[MX_FLT1];
//		MgGReal	dd;
//		dd.sz = MX_FLT1;
//		dd.r = MFB_dd;
//
#define		MGGFLOAT( P, M)	MREAL MFB_ ## P[M]; MgGReal P; P.m_isz = M; P.m_r = MFB_ ## P;
//
//	定数で指定したサイズの整数データ配列を持つ整数群を作成する
//		初期に定数で指定したサイズの配列を定義しているが変数で指定したサイズの方が大きい場合にmallocで作成する。
//		mallocで確保された領域はProgのリターン時に自動的に削除される
//
//	MBMALCGINT( 整数群名, 確保要求サイズ(変数), 初期配列サイズ(定数)); 
//
//	例	MBMALCGINT( dd, GInt->n, MX_INT1);
//			↓
//		MINT		MIB_dd[MX_INT1];
//		MgGInt		dd;
//		if (GInt->n > MX_INT1) {
//			dd.sz = GInt->n;
//			dd.i = (MINT *)new char[GInt->n * sizeof( MINT)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_INT1;
//			dd.i = MIB_dd;
//		}
//
#define		MBMALCGINT( P, S, M)\
								 MINT MIB_ ## P[M]; MgGInt P;\
								 if (S > M) {P.sz = S; P.m_i = (MgPoint2D *)new char[S * sizeof(MgPoint2D)]; MBCHECK_POINTER( P.m_i);}\
								 else {P.m_isz = M; P.m_i = MIB_ ## P;}
//
//
//	定数で指定したサイズの実数データ配列を持つ実数群を作成する
//		初期に定数で指定したサイズの配列を定義しているが変数で指定したサイズの方が大きい場合にmallocで作成する。
//		mallocで確保された領域はProgのリターン時に自動的に削除される
//
//	MBMALCGFLOAT( 実数群名, 確保要求サイズ(変数), 初期配列サイズ(定数)); 
//
//	例	MBMALCGFLOAT( dd, GFlt->n, MX_FLT1);
//			↓
//		MREAL		MFB_dd[MX_FLT1];
//		MgGReal	dd;
//		if (GFlt->n > MX_FLT1) {
//			dd.sz = GFlt->n;
//			dd.p = (MgPoint3D *)new char[GPt2->n * sizeof( MgPoint3D)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_FLT1;
//			dd.p = MFB_dd;
//		}
//
#define		MBMALCGFLOAT( P, S, M)\
								 MREAL MFB_ ## P[M]; MgGReal P;\
								 if (S > M) {P.m_isz = S; P.m_r = (MREAL* )new char[S * sizeof(MREAL)]; MBCHECK_POINTER( P.m_r);}\
								 else {P.m_isz = M; P.m_r = MLB_ ## P;}
//
//
//
//	定数で指定したサイズの点データ配列を持つ点群を作成する
//
//	MGGPOINT2( 点群名, 配列サイズ(定数)); 
//
//	例	MGGPOINT2( dd, MX_PNT1);
//			↓
//		MgPoint2D	MPB_dd[MX_PNT1];
//		MgGPoint2D	dd;
//		dd.sz = MX_PNT1;
//		dd.p = MPB_dd;
//
#define		MGGPOINT2( P, M)	MgPoint2D MPB_ ## P[M]; MgGPoint2D P; P.m_isz = M; P.m_p = MPB_ ## P;
//
//	定数で指定したサイズの点データ配列を持つ点群を作成する
//
//	MgGPoint3D( 点群名, 配列サイズ(定数)); 
//
//	例	MgGPoint3D( dd, MX_PNT1);
//			↓
//		MgPoint3D	MPB_dd[MX_PNT1];
//		MgGPoint3D	dd;
//		dd.sz = MX_PNT1;
//		dd.p = MPB_dd;
//
#define		MGGPOINT3( P, M)	MgPoint3D MPB_ ## P[M]; MgGPoint3D P; P.m_isz = M; P.m_p = MPB_ ## P;
//
//	定数で指定したサイズの点データ配列を持つ点群を作成する
//		初期に定数で指定したサイズの配列を定義しているが変数で指定したサイズの方が大きい場合にmallocで作成する。
//		mallocで確保された領域はProgのリターン時に自動的に削除される
//
//	MBMALCGPOINT2( 線分群名, 確保要求サイズ(変数), 初期配列サイズ(定数)); 
//
//	例	MBMALCGPOINT2( dd, GPt2->n, MX_PNT1);
//			↓
//		MgPoint2D	MPB_dd[MX_PNT1];
//		MgGPoint2D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.p = (MgPoint2D *)new char[GPt2->n * sizeof( MgPoint2D)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.p = MPB_dd;
//		}
//
#define		MBMALCGPOINT2( P, S, M)\
								 MgPoint2D MLB_ ## P[M]; MgGPoint2D P;\
								 if (S > M) {P.m_isz = S; P.m_p = (MgPoint2D *)new char[S * sizeof(MgPoint2D)]; MBCHECK_POINTER( P.m_p);}\
								 else {P.m_isz = M; P.m_p = MLB_ ## P;}
//
//
//	定数で指定したサイズの点データ配列を持つ点群を作成する
//		初期に定数で指定したサイズの配列を定義しているが変数で指定したサイズの方が大きい場合にmallocで作成する。
//		mallocで確保された領域はProgのリターン時に自動的に削除される
//
//	MBMALCGPOINT3( 線分群名, 確保要求サイズ(変数), 初期配列サイズ(定数)); 
//
//	例	MBMALCGPOINT3( dd, GPt2->n, MX_PNT1);
//			↓
//		MgPoint3D	MPB_dd[MX_PNT1];
//		MgGPoint3D	dd;
//		if (GPt2->n > MX_PNT1) {
//			dd.sz = GPt2->n;
//			dd.p = (MgPoint3D *)new char[GPt2->n * sizeof( MgPoint3D)];
//					MBCHECK_POINTER( dd.p);
//		} else {
//			dd.sz = MX_PNT1;
//			dd.p = MPB_dd;
//		}
//
#define		MBMALCGPOINT3( P, S, M)\
								 MgPoint3D MLB_ ## P[M]; MgGPoint3D P;\
								 if (S > M) {P.m_isz = S; P.m_p = (MgPoint3D *)new char[S * sizeof(MgPoint3D)]; MBCHECK_POINTER( P.m_p);}\
								 else {P.m_isz = M; P.m_p = MLB_ ## P;}

/////////////////////////////////////////////////////////////////////////////
//	図形データタイプ
#define		MGTP_POINT			1								// 点
#define		MGTP_LINE			2								// 線分
#define		MGTP_ILINE			3								// 直線
#define		MGTP_POLYLN			4								// 折れ線
#define		MGTP_CIR			5								// 円
#define		MGTP_ARC			6								// 円弧
#define		MGTP_POLYGN			7								// 多角形(面)
#define		MGTP_TXT			8								// 文字列
#define		MGTP_MSH			9								// ﾒｯｼｭ
#define		MGTP_GINT			10								// 整数群
#define		MGTP_GREAL			11								// 実数群
#define		MGTP_GPOINT2		22								// ２次元点群
#define		MGTP_GPOINT3		23								// ３次元点群
#define		MGTP_GLINE			32								// ２次元線分群
#define		MGTP_GLINE3			33								// ３次元線分群
#define		MGTP_POLYG			42								// ２次元多角形
#define		MGTP_POLYG3			43								// ３次元多角形
#define		MGTP_GPOLYG			52								// ２次元多角形群
#define		MGTP_GPOLYG3		53								// ３次元多角形群
