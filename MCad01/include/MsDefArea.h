#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: MsBasic.h
//
//		基本　領域定義
//
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================

//===========================================================================
//		バッファ管理
//

//===========================================================================
//	MbMAlcBuf
//
//		サイズ付きバッファ
//
class	MbMAlcBuf
{
public:
	MINT	sz;
	void*	m_Buf;
public:
	MbMAlcBuf( )				{ m_Buf = NULL;}

	~MbMAlcBuf( )				{ if ( m_Buf) delete [] ( char*)m_Buf;}
};

//===========================================================================
//	MBMALLOC( アロケーションメモリアドレス設定ポインタ, 変数型, 確保要求サイズ);
//
//		データ型を指定したメモリアロケーション
//
//	例	MBMALLOC( dd, MREAL, MX_PNT1);
//			↓
//		MREAL	*dd = ( MREAL*)new char[MX_PNT1 * sizeof( MREAL)];
//				MBCHECK_POINTER( dd);
//
#define		MBMALLOC( P, T, S)	{ P = ( T*)new char[( S) * sizeof( T)]; MBCHECK_POINTER( P);}
#define		MBMALLOCF( F, P, T, S)	{ P = ( F*)new char[( S) * sizeof( T)]; MBCHECK_POINTER( P);}

//===========================================================================
//	MBFREE( アロケーションメモリアドレス設定ポインタ);
//
//		メモリアロケーション領域の開放
//
//	例	MBFREE( dd);
//			↓
//		if ( dd) {
//			delete [] ( char*)dd;
//			dd = NULL;
//		}
//
#define		MBFREE( P)			{ if ( P) { delete [] ( char*)P; P = NULL;}}

//===========================================================================
//	MBFREEST( アロケーションメモリアドレス設定ポインタ);
//
//		構造体の開放とメモリアロケーション領域の開放
//
//	例	MBFREE( dd);
//			↓
//		if ( dd) {
//			dd->Freee( );
//			delete [] ( char*)dd;
//			dd = NULL;
//		}
//
#define		MBFREEST( P)		{ if ( P) { P->Free( ); delete [] ( char*)P; P = NULL;}}

////===========================================================================
////	MBDELETE( newで作成配列領域の先頭アドレス設定ポインタ);
////
////	例	MBDELETEH( dd);
////			↓
////		if ( dd) {
////			delete [] dd;
////			dd = NULL;
////		}
////
//#define		MBDELETEH( P)	{ if ( P) {delete [] ( char*)P ; P = NULL;}}

//===========================================================================
//	MBDELETE( newで作成領域の先頭アドレス設定ポインタ);
//
//	例	MBDELETE( dd);
//			↓
//		if ( dd) {
//			delete dd;
//			dd = NULL;
//		}
//
#define		MBDELETE( P)		{ if ( P) { delete P ; P = NULL;}}

//===========================================================================
//	定数で指定したサイズの配列を確保する
//
//	MBBUFF( 作成領域の先頭アドレス設定ポインタ, 変数型, 初期配列サイズ( 定数)); 
//
//	例	MBBUFF( dd, MREAL, MX_PNT1);
//			↓
//		MREAL		*dd;
//		MbMAlcBuf	MAB_dd;
//		MREAL		MHB_dd[MX_PNT1];
//		MAB_dd.sz = MX_PNT1;
//		dd = MHB_dd;
//
//	MBBUFF( 	iPtW1,	MINT,	20); 
//		MINT *iPtW1; MbMAlcBuf MAB_iPtW1; MINT MHB_iPtW1[20]; MAB_iPtW1.sz = 20; iPtW1 = MHB_iPtW1;

#define		MBBUFF( P, T, M)\
								 T *P; MbMAlcBuf MAB_ ## P; T MHB_ ## P[M]; MAB_ ## P.sz = ( M); P = MHB_ ## P;

//===========================================================================
//	定数で指定したサイズの配列を確保する
//		初期に定数で指定したサイズの配列を定義しているが変数で指定したサイズの方が大きい場合にmallocで作成する。
//		mallocで確保された領域はProgのリターン時に自動的に削除される
//
//	MBMALCBUFF( 作成領域の先頭アドレス設定ポインタ, 変数型, 確保要求サイズ, 初期配列サイズ( 定数)); 
//
//	例	MBMALCBUFF( dd, MREAL, GPt2->n, MX_PNT1);
//			↓
//		MREAL		*dd;
//		MbMAlcBuf	MAB_dd;
//		MREAL		MHB_dd[MX_PNT1];
//		if ( GPt2->n > MX_PNT1) {
//			MAB_dd.sz = GPt2->n;
//			MAB_dd.m_Buf = dd = ( MREAL *)new char[GPt2->n * sizeof( MREAL)];
//					MBCHECK_POINTER( dd);
//		} else {
//			MAB_dd.sz = MX_PNT1;
//			dd = MHB_dd;
//		}
//
#define		MBMALCBUFF( P, T, S, M)\
								 T *P; MbMAlcBuf MAB_ ## P; T MHB_ ## P[M];\
								 if ( ( S) > ( M)) {MAB_dd.sz = ( S); MAB_ ## P.m_Buf = P = ( T *)new char[( S) * sizeof( T)]; MBCHECK_POINTER( P);}\
								 else {MAB_dd.sz = ( M); P = MHB_ ## P;}

////===========================================================================
////	MBBUFFまたはMBMALCBUFFで確保した領域のサイズを変更する
////
////	MBREALCBUFF( リアロケーションメモリアドレス設定ポインタ, 変数型, 確保要求サイズ);
////
////	例	MBREALCBUFF( dd, MREAL, GPt2->n);
////			↓
////		if ( GPt2->n > MAB_dd.sz) {
////			if ( MAB_dd.m_Buf) {
////				MAB_dd.m_Buf = dd = ( MREAL*)realloc( dd, sizeof( MREAL) * GPt2->n);
////			} else {
////				MAB_dd.m_Buf = dd = new char[GPt2->n * sizeof( MREAL)];
////				memcpy( dd, MHB_dd, sizeof( MREAL) * MAB_dd.sz);
////			}
////			MAB_dd.sz = GPt2->n;
////		}
////				MBCHECK_POINTER( dd);
////
////#define		MBREALCBUFF( P, T, S)\
////								if ( S > MAB_ ## P.sz) {\
////									if ( MAB_ ## P.m_Buf) {MAB_ ## P.m_Buf = P = ( T*)realloc( P, sizeof( T) * S);}\
////									else {MAB_ ## P.m_Buf = P = ( T*)new char[S * sizeof( T)]; memcpy( P, MHB_ ## P, sizeof( T) * MAB_ ## P.sz);}\
////									MAB_ ## P.sz = S;\
////								} MBCHECK_POINTER( P);}
//#define		MBREALCBUFF( P, T, S)\
//								if ( S > MAB_ ## P.sz) {\
//									if ( MAB_ ## P.m_Buf) {MAB_ ## P.m_Buf = P = ( T*)realloc( P, sizeof( T) * S);}\
//									else {MAB_ ## P.m_Buf = P = new T[ S]; memcpy( P, MHB_ ## P, sizeof( T) * MAB_ ## P.sz);}\
//									MAB_ ## P.sz = S;\
//								} MBCHECK_POINTER( P);}

