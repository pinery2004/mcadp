#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgMatAf.h
//
//		図形マトリックス演算処理
//
//
//  K.Matsu           13/05/07    Created.
//==========================================================================================
//
namespace MC
{

	//======================( ２Ｄ，３Ｄ )==============================
	//	２Ｄ，３Ｄマトリックス
	//
/*	//======================( ２次元 )==============================
	//		原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat2D Mat2DRot( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2DRotV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ２次元 )==============================
	//		原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat2D Mat2DRotRev( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat2DRotRevV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＸＹ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3D Mat3DRotZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＸＹ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat3D Mat3DRotRevZ( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotRevZV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＹＺ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3D Mat3DRotTX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return  Mat3DRotTXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＹＺ平面で原点を中心に逆回転の座標変換マトリックスを作成
	//
	static MgMat3D Mat3DRotRevX( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotRevXV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3D Mat3DRotY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

	//======================( ３次元 )==============================
	//		ＺＸ平面で原点を中心に回転の座標変換マトリックスを作成
	//
	static MgMat3D Mat3DRotRevY( MREAL dg)
	{
		MREAL	rd = MGRADIAN( dg);
		return Mat3DRotRevYV( MgVect2D( MREAL( cos( rd)), MREAL( sin( rd))));
	}

*/

//======================( ３Ｄ，４Ｄ )==============================
//	３Ｄ，４Ｄマトリックス
//
//===========================================================================
//	処理内容
//	    座標変換マトリックスの加算
//
//	使用法
//		MgMat3D= MgMat3D1 + MgMat3D2;
//
//	| m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  +  | n21 n22 n23 |
//	| m31 m32 m33 |     | n31 n32 n33 |
//
inline MgMat2D operator + ( const MgMat2D& i_mt, const MgMat2D& i_mt2)			// +
{
	return MGeo::Mat2DPlus( i_mt, i_mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat2D1 += MgMat2D2;
//
//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  =  | m21 m22 m23 |  +  | n21 n22 n23 |
//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2D operator += ( MgMat2D& io_mt, const MgMat2D& i_mt2)				// +=
{
	return MGeo::Mat2DPlusEqual( io_mt, i_mt2);
}

//===========================================================================
//	処理内容
//		負の座標変換マトリックスを作成
//
//	使用法
//		MgMat2D2 = - MgMat2D1;
//
//	  | m11 m12 m13 |
//	- | m21 m22 m23 |
//	  | m31 m32 m33 |
//
inline	MgMat2D operator - ( const MgMat2D& i_mt)								// -
{
	return MGeo::Mat2DSingleMinus( i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat3D= MgMat3D1 - MgMat3D2;
//
//	  | m11 m12 m13 |     | n11 n12 n13 |
//	  | m21 m22 m23 |  -  | n21 n22 n23 |
//	  | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2D operator - ( const MgMat2D& i_mt, const MgMat2D& i_mt2)			// -
{
	return MGeo::Mat2DMinus( i_mt, i_mt2);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスの引算
//
//	使用法
//		MgMat2D1 -= MgMat2D2;
//
//	| m11 m12 m13 |    | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  = | m21 m22 m23 |  -  | n21 n22 n23 |
//	| m31 m32 m33 |    | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2D operator -= ( MgMat2D& io_mt, const MgMat2D& i_mt2)				// -=
{
	return MGeo::Mat2DMinusEqual( io_mt, i_mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
//
//	使用法
//		MgMat2D= MgMat2D1 * MgMat2D2;
//
//	| m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  X  | n21 n22 n23 |
//	| m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2D operator * ( const MgMat2D& i_mt, const MgMat2D& i_mt2)			// *
{
	return MGeo::Mat2DMult( i_mt, i_mt2);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスのかけ算
//	    座標変換マトリックスによる変換後に、さらに座標変換マトリックスによる変換するマトリックスを作成
//
//	使用法
//		MgMat2D2 *= MgMat2D1;
//
//	| m11 m12 m13 |     | m11 m12 m13 |     | n11 n12 n13 |
//	| m21 m22 m23 |  =  | m21 m22 m23 |  X  | n21 n22 n23 |
//	| m31 m32 m33 |     | m31 m32 m33 |     | n31 n32 n33 |
//
inline	MgMat2D operator *= ( MgMat2D& io_mt, const MgMat2D& i_mt2)				// *=
{
	return MGeo::Mat2DMultEqual( io_mt, i_mt2);
}

inline	MgMat2D operator + ( const MgMat2D& i_m1, const MgVect2D& i_pt)			// +	平行移動
{ 
	MgMat2D mw;
	mw = i_m1;
	mw += i_pt;
	return mw;
}
inline	MgMat2D operator +  ( const MgMat2D& i_m1, const MgPoint2D& i_pt)		// +	平行移動
{
	return i_m1 + (MgVect2D&)i_pt;
}
inline	MgMat2D operator += ( MgMat2D& i_m1, const MgVect2D& i_pt)				// +=	平行移動
{
	i_m1.m[2][0] += i_pt.x;
	i_m1.m[2][1] += i_pt.y;
	return i_m1;
}
inline	MgMat2D operator += ( MgMat2D& i_m1, const MgPoint2D& i_pt)				// +=	平行移動
{
	return i_m1 += (MgVect2D&)i_pt;
}
inline	MgMat2D operator - ( const MgMat2D& i_m1, const MgVect2D& i_pt)			// -	平行移動
{
	MgMat2D mw = i_m1;
	mw -= i_pt;
	return mw;
}
inline	MgMat2D operator -  ( const MgMat2D& i_m1, const MgPoint2D& i_pt)		// -	平行移動
{
	return i_m1 - (MgVect2D&)i_pt;
}
inline	MgMat2D operator -= ( MgMat2D& i_m1, const MgVect2D& i_pt)				// -=	平行移動
{
	i_m1.m[2][0] -= i_pt.x;
	i_m1.m[2][1] -= i_pt.y;
	return i_m1;
}
inline	MgMat2D operator -= ( MgMat2D& i_m1, const MgPoint2D& i_pt)				// -=	平行移動
{
	return i_m1 -= (MgVect2D&)i_pt;
}

	
	
//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgPoint2D = MgPoint2D * MgMat2D;
//
//					   | m11 m12 m13 |
//	| px  py  1  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |     
//
inline	MgPoint2D operator * ( const MgPoint2D& i_pt, const MgMat2D& i_mt)		// *	座標変換
{
	return MGeo::Mat2DMultPoint2D( i_pt, i_mt);
}

//===========================================================================
//	処理内容
//	    座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D = MgVect2D * MgMat2D;
//
//					   | m11 m12 m13 |
//	| vx  vy  0  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |     
//
inline	MgVect2D operator * ( const MgVect2D& i_pt, const MgMat2D& i_mt)		// *	座標変換
{
	return MGeo::Mat2DMultVect2D( i_pt, i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgPoint2D *= MgMat2D;
//
//										  | m11 m12 m13 |
//	| px  py  1  |  =  | px  py  1  |  X  | m21 m22 m23 |
//				   						  | m31 m32 m33 |
//
inline	MgPoint2D operator *= ( MgPoint2D& io_vt, const MgMat2D& i_mt)			// *=	座標変換
{
	return MGeo::Mat2DMultEqualPoint2D( io_vt, i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgVect2D *= MgMat2D;
//
//										  | m11 m12 m13 |
//	| vx  vy  0  |  =  | vx  vy  0  |  X  | m21 m22 m23 |
//				   						  | m31 m32 m33 |
//
inline	MgVect2D operator *= ( MgVect2D& io_pt, const MgMat2D& i_mt)			// *=	座標変換
{
	return MGeo::Mat2DMultEqualVect2D( io_pt, i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D = MgULine2D*  MgMat2D;
//
//	| px  py  1  |     | m11 m12 m13 |
//	| vx  vy  0  |  X  | m21 m22 m23 |
//					   | m31 m32 m33 |
//
inline	MgULine2D operator * ( const MgULine2D& i_uln, const MgMat2D& i_mt)	// *	座標変換
{
	return MGeo::Mat2DMultULine2D( i_uln, i_mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスにより座標変換する
//
//	使用法
//		MgULine2D* = MgMat2D;
//
//	| px  py  1  |     | px  py  1  |     | m11 m12 m13 |
//	| vx  vy  0  |  =  | vx  vy  1  |  X  | m21 m22 m23 |
//			             				  | m31 m32 m33 |
//
inline	MgULine2D operator *= ( MgULine2D& io_uln, const MgMat2D& i_mt)		// *=	座標変換
{
	return MGeo::Mat2DMultEqualULine2D( io_uln, i_mt);
}

//U1 //===============( ２次元座標変換マトリックスで３次元座標処理 )==============
////
////===========================================================================
////	処理内容
////	    座標変換マトリックスにより座標変換する
////
////	使用法
////		MgVect3D2 = MgVect3D1 * MgMat2D1;
////
////						  | m11 m12 0 m13 |     
////	| vx  vy  vz  0 |  X  | m21 m22 0 m23 |
////						  |  0   0  1  0  |
////						  | m31 m32 0 m33 |
////
//inline	MgVect3D operator * ( const MgVect3D& i_Pt, const MgMat2D& i_mt)		// *	座標変換
//{
//	return MGeo::Mat2DMultPointt3D( i_Pt, i_mt);
//}
//
////===========================================================================
////	処理内容
////		座標変換マトリックスにより座標変換する
////
////	使用法
////		MgVect3D *= MgMat2D;
////
////						 						| m11 m12 0 m13 |
////	| vx  vy  vz  0 |  =  | vx  vy  vz  0 |  X  | m21 m22 0 m23 |
////			   									|  0   0  1  0  |
////			   									| m31 m32 0 m33 |
////
//inline	MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat2D& i_mt)			// *=	座標変換
//
//{
//	return MGeo::Mat2DMultEqualPoint3D( io_Pt, i_mt);
//}
//
////===========================================================================
////	処理内容
////		座標変換マトリックスにより座標変換する
////
////	使用法
////		MgULine2D = MgULine2D*  MgMat2D;
////
////	| px  py  pz  1 |	  | m11 m12 0 m13 |
////	| vx  vy  vz  0 |  X  | m21 m22 0 m23 |
////						  |  0   0  1  0  |
////			   			  | m31 m32 0 m33 |
////
//inline MgULine3D operator * ( const MgULine3D& i_ULn, const MgMat2D& i_mt)	// *	座標変換
//{
//	return MGeo::Mat2DMultULine3D( i_ULn, i_mt);
//}
//
////===========================================================================
////	処理内容
////		座標変換マトリックスにより座標変換する
////
////	使用法
////		MgULine2D* = MgMat2D;
////
////	| px  py  pz  1 |     | px  py  pz  1 |		| m11 m12 0 m13 |
////	| vx  vy  vz  0 |  =  | vx  vy  vz  0 |  X  | m21 m22 0 m23 |
////												|  0   0  1  0  |
////				 				   				| m31 m32 0 m33 |
////
//inline MgULine3D operator *= ( MgULine3D& io_ULn, const MgMat2D& i_mt)		// *=	座標変換
//{
//	return MGeo::Mat2DMultEqualULine3D( io_ULn, i_mt);
//}

//===========================================================================
//
//	３Ｄ座標変換マトリックスの計算
//
//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat3D_3 = MgMat3D_1 + MgMat3D_2;
//
//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline	MgMat3D operator + ( const MgMat3D& i_Mt, const MgMat3D& i_Mt2)			// +
{
	return MGeo::Mat3DPlus( i_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの加算
//
//	使用法
//		MgMat3D+= MgMat3D;
//
//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  +  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline	MgMat3D operator += ( MgMat3D& io_Mt, const MgMat3D& i_Mt2)				// +=
{
	return MGeo::Mat3DPlusEqual( io_Mt, i_Mt2);
}	

//===========================================================================
//	処理内容
//		負の座標変換マトリックスを作成
//
//	使用法
//		MgMat3D_2 = - MgMat3D_1;
//
//	  | m11 m12 m13 m14 |
//	- | m21 m22 m23 m24 |
//	  | m31 m32 m33 m34 |
//	  | m41 m42 m43 m44 |     
//
inline	MgMat3D operator - ( const MgMat3D& i_Mt)								// -
{
	return MGeo::Mat3DSingleMinus( i_Mt);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat3D_3 = MgMat3D_1 - MgMat3D_2;
//
//	  | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
//	  | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	  | m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline	MgMat3D operator - ( const MgMat3D& i_Mt, const MgMat3D& i_Mt2)			// -
{
	return MGeo::Mat3DMinus( i_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスの引算
//
//	使用法
//		MgMat3D-= MgMat3D;
//
//	| m11 m12 m13 m14 |		| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  -  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline MgMat3D operator -= ( MgMat3D& io_Mt, const MgMat3D& i_Mt2)				// -=
{
	return MGeo::Mat3DMinusEqual( io_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//
//	使用法
//		MgMat3D_3 = MgMat3D_1 * MgMat3D_2;
//
//	| m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | n41 n42 n43 n44 |    
//
inline MgMat3D operator * ( const MgMat3D& i_Mt, const MgMat3D& i_Mt2)			// *
{
	return MGeo::Mat3DMult( i_Mt, i_Mt2);
}

//===========================================================================
//	処理内容
//		座標変換マトリックスのかけ算
//
//	使用法
//		MgMat3D*= MgMat3D;
//
//	| m11 m12 m13 m14 |     | m11 m12 m13 m14 |     | n11 n12 n13 n14 |
//	| m21 m22 m23 m24 |  =  | m21 m22 m23 m24 |  X  | n21 n22 n23 n24 |
//	| m31 m32 m33 m34 |     | m31 m32 m33 m34 |     | n31 n32 n33 n34 |
//	| m41 m42 m43 m44 |     | m41 m42 m43 m44 |     | n41 n42 n43 n44 |     
//
inline MgMat3D operator *= ( MgMat3D& io_Mt, const MgMat3D& i_Mt2)
{
	return MGeo::Mat3DMultEqual( io_Mt, i_Mt2);
}

inline MgMat3D operator + ( const MgMat3D& i_M1, const MgVect3D& i_Vt)			// +	平行移動
{
	MgMat3D mw;
	mw = i_M1;
	mw += i_Vt;
	return mw;
}
inline MgMat3D operator += ( MgMat3D& i_M1, const MgVect3D& i_Vt)				// +=	平行移動
{ 
	i_M1.m[3][0] += i_Vt.x;
	i_M1.m[3][1] += i_Vt.y;
	i_M1.m[3][2] += i_Vt.z;
	return i_M1;
} 
inline MgMat3D operator - ( const MgMat3D& i_M1, const MgVect3D& i_Vt)			// -	平行移動
{
	MgMat3D mw;
	mw = i_M1;
	mw -= i_Vt;
	return mw;
}
inline MgMat3D operator -= ( MgMat3D& i_M1, const MgVect3D& i_Vt)				// -=	平行移動
{
	i_M1.m[3][0] -= i_Vt.x;
	i_M1.m[3][1] -= i_Vt.y;
	i_M1.m[3][2] -= i_Vt.z;
	return i_M1;
} 

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgPoint2D_2 = MgPoint2D * MgMat3D_1;
//
//						    | m11 m12 m13 m14 |
//	| px  py  0   1   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
inline MgPoint2D operator * ( const MgPoint2D& i_Pt, const MgMat3D& i_Mt)		// 座標変換
{
	return MGeo::Mat3DMultPoint2D( i_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgVect2D_2 = MgVect2D * MgMat3D_1;
//
//						    | m11 m12 m13 m14 |
//	| vx  vy  0   0   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
inline MgVect2D operator * ( const MgVect2D& i_Pt, const MgMat3D& i_Mt)			// 座標変換
{
	return MGeo::Mat3DMultVect2D( i_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgPoint2D *= MgMat3D;
//
//						     					    | m11 m12 m13 m14 |
//	| px  py  0   1   |  =  | px  py  0   1   |  X  | m21 m22 m23 m24 |
//	           									    | m31 m32 m33 m34 |
//	           									    | m41 m42 m43 m44 |
//
inline MgPoint2D operator *= ( MgPoint2D& io_Pt, const MgMat3D& i_Mt)			// 座標変換
{
	return MGeo::Mat3DMultEqualPoint2D( io_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより２次元データを座標変換する
//
//	使用法
//		MgVect2D *= MgMat3D;
//
//						     					    | m11 m12 m13 m14 |
//	| vx  vy  0   0   |  =  | vx  vy  0   0   |  X  | m21 m22 m23 m24 |
//	           									    | m31 m32 m33 m34 |
//	           									    | m41 m42 m43 m44 |
//
inline MgVect2D operator *= ( MgVect2D& io_Pt, const MgMat3D& i_Mt)			// 座標変換
{
	return MGeo::Mat3DMultEqualVect2D( io_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgPoint3D_2 = MgPoint3D_1 * MgMat3D;
//
//	 					    | m11 m12 m13 m14 |
//	| px  py  pz  0   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
inline MgPoint3D operator * ( const MgPoint3D& i_Pt, const MgMat3D& i_Mt)		// 座標変換
{
	return MGeo::Mat3DMultPoint3D( i_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D_2 = MgVect3D_1 * MgMat3D;
//
//	 					    | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//						    | m31 m32 m33 m34 |
//						    | m41 m42 m43 m44 |
//
inline MgVect3D operator * ( const MgVect3D& i_Pt, const MgMat3D& i_Mt)		// 座標変換
{
	return MGeo::Mat3DMultVect3D( i_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgPoint3D *= MgMat3D;
//
//							 					    | m11 m12 m13 m14 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
//												    | m31 m32 m33 m34 |
//												    | m41 m42 m43 m44 |
//
inline MgPoint3D operator *= ( MgPoint3D& io_Pt, const MgMat3D& i_Mt)				// 座標変換
{
	return MGeo::Mat3DMultEqualPoint3D( io_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgVect3D *= MgMat3D;
//
//							 					    | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//												    | m31 m32 m33 m34 |
//												    | m41 m42 m43 m44 |
//
inline MgVect3D operator *= ( MgVect3D& io_Pt, const MgMat3D& i_Mt)				// 座標変換
{
	return MGeo::Mat3DMultEqualVect3D( io_Pt, i_Mt);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgLine3D = MgLine3D_1 * MgMat3D;
//
//	| px  py  pz  1   |     | m11 m12 m13 m14 |
//	| px  py  pz  1   |  X  | m21 m22 m23 m24 |
//							| m31 m32 m33 m34 |
//							| m41 m42 m43 m44 |
//
inline MgLine3D operator * ( const MgLine3D& i_Ln1, const MgMat3D& i_Mt2)		// 座標変換
{
//S	MgLine3D Ln;
//	Ln.p[0] = i_Ln1.p[0] * i_M2;
//	Ln.p[1] = i_Ln1.p[1] * i_M2;
//	return Ln;
	return MGeo::Mat3DMultLine3D( i_Ln1, i_Mt2);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgULine3D = MgULine3D_1 * MgMat3D;
//
//	| px  py  pz  1   |     | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//							| m31 m32 m33 m34 |
//							| m41 m42 m43 m44 |
//
inline MgULine3D operator * ( const MgULine3D& i_ULn1, const MgMat3D& i_Mt2)		// 座標変換
{
	return MGeo::Mat3DMultULine3D( i_ULn1, i_Mt2);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgULine3D *= MgMat3D;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
//	| px  py  pz  1   |  =  | px  py  pz  1   |  X  | m21 m22 m23 m24 |
//													| m31 m32 m33 m34 |
//													| m41 m42 m43 m44 |
//
inline MgLine3D operator *= ( MgLine3D& io_Ln1, const MgMat3D& i_Mt2)			// 座標変換
{
//S	i_Ln1.p[0] *= i_M2;
//	i_Ln1.p[1] *= i_M2;
//	return i_Ln1;
	return MGeo::Mat3DMultEqualLine3D( io_Ln1, i_Mt2);
}

//===========================================================================
//	処理内容
//		３次元座標変換マトリックスにより３次元データを座標変換する
//
//	使用法
//		MgULine3D *= MgMat3D;
//
//	| px  py  pz  1   |     | px  py  pz  1   |     | m11 m12 m13 m14 |
//	| vx  vy  vz  0   |  =  | vx  vy  vz  0   |  X  | m21 m22 m23 m24 |
//													| m31 m32 m33 m34 |
//													| m41 m42 m43 m44 |
//
inline MgULine3D operator *= ( MgULine3D& io_ULn1, const MgMat3D& i_Mt2)			// 座標変換
{
	return MGeo::Mat3DMultEqualULine3D( io_ULn1, i_Mt2);
}

/*
//===========================================================================
//		平面 形状演算
//
inline MgPlane3D MgPlane3Point3D(									// ３点より平面の方程式の係数と定数を求める（正規化）
					const	MgPoint3D*	i_ppt)
						{ return MGeo::Plane3pPoint3D( i_ppt);}

inline MgPlane3D MgPlane3Point3D(									// ３点より平面の方程式の係数と定数を求める（正規化）
					const	MgPoint3D&	i_p0,
					const	MgPoint3D&	i_p1,
					const	MgPoint3D&	i_p2)
						{ return MGeo::Plane3Point3D( i_p0, i_p1, i_p2);}

inline MgPlane3D MgPlanePolygon3D(									// 多角形より平面の方程式の係数と定数を求める（正規化）
					const	MgPolyg3D&	i_pg)
						{ return MGeo::Plane3DPolygon3D( i_pg);}

inline MgPlane3D MgPlane2PointSlope3D(									// 始点と終点の２点と勾配より平面の方程式の係数と定数を求める（正規化）
					const	MgPoint2D&	i_p1,
					const	MgPoint2D&	i_p2,
							MREAL		i_rkb,
							MREAL		i_z = 0.)
						{ return MGeo::Plane2PointSlope3D( i_p1, i_p2, i_rkb, i_z);}

inline MgPlane3D PlaneLineSlope3D(										// 線分と勾配より平面の方程式の係数と定数を求める（正規化）
					const	MgLine2D&	i_ln1,
							MREAL		i_rkb,
							MREAL		i_z = 0.)
						{ return MGeo::PlaneLineSlope3D( i_ln1, i_rkb, i_z);}

//
//===========================================================================
//		平面の方程式の係数と定数を正規化した平面を求める
//		ax+by+cz+d=0	(a*a+b*b+c*c=1.0)
//
inline MgPlane3D MgPlane3DNorm(							// (  O) 正規化後の３次元平面
					const	MgPlane3D&	i_pl)		// (I  ) ３次元平面
						{ return MGeo::NormPln( i_pl);}
//
//===========================================================================
//		MgPlane3Dを使用のインライン関数
//	
inline MgPoint3D::MgPoint3D(									// ２次元→３次元
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ x = i_v1.x; y = i_v1.y; z = i_Pln.GetZ( i_v1);} 

//======================( ３次元 )==============================
//		３次元ベクトル演算
inline MgVect3D MgVect3DC(										// ２次元→３次元
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ MgVect3D Vto; Vto.x = i_v1.x; Vto.y = i_v1.y;
									    Vto.z = i_Pln.GetZ( i_v1); return Vto;} 
inline MgPoint3D MgPoint3D::Set(								// ２次元→３次元
					const	MgPoint2D&	i_v1,
					const	MgPlane3D&	i_Pln)
						{ x = i_v1.x; y = i_v1.y; z = i_Pln.GetZ( i_v1); return *this;} 

inline MgULine3D MgULine3DC(									// ２次元→３次元
					const	MgULine2D&	i_uln,
					const	MgPlane3D&	i_Pln,
							MREAL	i_Tol = MGPTOL->D)
						{ MgULine3D ULno; ULno.p.x = i_uln.p.x; ULno.p.y = i_uln.p.y;
										 ULno.p.z = i_Pln.GetZ( i_uln.p);
						  ULno.v = MgVect3DC( i_uln.v, - ( i_Pln.v.x * i_uln.v.x + i_Pln.v.y * i_uln.v.y) / i_Pln.v.z);
						  ULno.v.SetUnitize( i_Tol); return ULno;} 

inline MgULine3D MgULine3D::Set(								// ２次元→３次元
					const	MgULine2D&	i_uln,
					const	MgPlane3D&	i_Pln,
							MREAL	i_Tol)
						{ p.x = i_uln.p.x; p.y = i_uln.p.y; p.z = i_Pln.GetZ( i_uln.p);
						  v = MgVect3DC( i_uln.v, - ( i_Pln.v.x * i_uln.v.x + i_Pln.v.y * i_uln.v.y) / i_Pln.v.z);
						  v.SetUnitize( i_Tol); return *this;} 
	
inline MgLine3D MgLine3DC(										// ２次元→３次元
					const	MgLine2D&	i_ln,
					const	MgPlane3D&	i_Pln)
						{ MgLine3D Lno; Lno.p[0].x = i_ln.p[0].x; Lno.p[0].y = i_ln.p[0].y;
									   Lno.p[0].z = i_Pln.GetZ( i_ln.p[0]);
									   Lno.p[1].x = i_ln.p[1].x; Lno.p[1].y = i_ln.p[1].y;
									   Lno.p[0].z = i_Pln.GetZ( i_ln.p[1]); return Lno;}

inline MgLine3D MgLine3D::Set(									// ２次元→３次元
					const	MgLine2D&	i_ln,
					const	MgPlane3D&	i_Pln)
						{ p[0].x = i_ln.p[0].x; p[0].y = i_ln.p[0].y; p[0].z = i_Pln.GetZ( i_ln.p[0]);
						  p[1].x = i_ln.p[1].x; p[1].y = i_ln.p[1].y; p[0].z = i_Pln.GetZ( i_ln.p[1]);
						  return *this;}
*/
} // namespace MC
