//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MCmdLine.cpp
//
//		線部材の配置コマンド
//
//	[機能] 
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MrAPI.h"
#include "MmCmd.h"
#include "MainFrm.h"
#include "MmDialogKAttr.h"
#include "MmCmdMsg.h"

#define		MC_YANE_TAKASA_HOSEI 97.

namespace MC
{

void MCmdLineAdd();
void MCmdLineDelete();

////////////////////////////////////////////////////////////////////////////
//	次のコマンド入力まで待つ

void MCmdWait()
{
	MINT		irt;
	MgPoint2D	pt1;

	Msg::OperationMsg( MC_OPRT_WAIT);							// ステイタスバーの操作表示部へ"操作待ち"を表示

	MFOREVER {
		irt = MtAskForPoint( &pt1);								// システムストップまたはキャンセルまで待つ
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;
		if ( irt == MTRT_RBTNDWN || irt == MTRT_KWORD)			// マウス右ボタン || メニュー入力
			continue;
	}
}

////////////////////////////////////////////////////////////////////////////
//	入力モードに従い部材を追加または削除する

void MCmdLine(
						CWnd*		pWnd			// (I  ) ウィンドウのインスタンス
	)
{
	MINT iMode;
	iMode = z_mnIA.GetMode();
	if ( iMode == MP_MD_CREATE) {
		z_mmIA.MmDialogKAttr();
		MCmdLineAdd();
	} else {
		if ( iMode == MP_MD_DELETE)
			MCmdLineDelete();
	}
}

////////////////////////////////////////////////////////////////////////////
//	部材を追加する

void MCmdLineAdd()
{
	MINT		ist;
	MINT		irt;
	MgPoint2D	pt1, pt2, pt1_org;
	MgPoint3D	PtMltBziAr;
	MgPoint2D	ptln1[3], ptln1_org[3], ptln1_chk[2];
	MgLine3D		Ln1;
	MgVect2D		vln;
	MgVect3D		vUp;
	MgLine2D		ln1;
	MgPolyg2D	pg1(20);
	MINT		iIdPartsSpec;
	mhPartsSpec*	pPartsSpec;
	bool		bFirst = TRUE;
	MINT		iMode;

	MhRfm	*pRfm1, *pRfm2;

	MgPlane3D	plnYane;

	MREAL rIntrv;												// 間隔
	MgVect3D VtArea;
	MgVect3D VtBziIntrv;

	MINT iNum;
	MINT ic1;

	Window::CurWndFocus();
	CMainFrame*	pMainFrame;
	pMainFrame = MC::System::GetpMainFrame();
	pMainFrame->SendMessage( WM_MYMESSAGE_RIBBONIO);

	Msg::ClearErrorMsg();
	Msg::OperationMsg( MC_OPRT_PARTS);							// ステイタスバーの操作表示部へ"部材追加"を表示

																								//SS	z_mnIA.RibbonIO( MINIT_COMBO_ATTR, MP_AT_AUTO);				// 部材入力種類に合った属性入力コンボボックスを表示
	z_mmIA.InitComboAttrEntry( MP_AT_AUTO);						// 部材入力種類に合った属性入力コンボボックスを表示

	iIdPartsSpec = z_mnIA.GetCurPartsNmId();
	pPartsSpec = BuzaiCode::MhGetpPartsSpec( iIdPartsSpec);
																								//SS	z_mnIA.RibbonIO( MSET_INPUT_KUBUN_CD, pPartsSpec->GetPTCdInpKbn());	// 入力点区分選択用のコンボボックスに表示する
	z_mnIA.SelectComboInpKbnByInpKbnCdEntry( pPartsSpec->GetPTCdInpKbn());	// 入力点区分選択用のコンボボックスに表示する
																								//SS	z_mnIA.RibbonIO( MSET_INPUT_MARUME_CD, pPartsSpec->GetPTCdMarume());// 丸めコードを選択用のコンボボックスに表示する
	z_mnIA.SelectComboMarumeByMarumeCdEntry( pPartsSpec->GetPTCdMarume());	// 丸めコードを選択用のコンボボックスに表示する

		mhHaitiIn::SetCurRfm( NULL);

	MFOREVER {
		// 配置座標入力
		//
		switch (pPartsSpec->GetPTCdInpKbn())
		{
		case MP_INPKB_1PT:										// 1点入力
			irt = mhInput::Get1Pt( &pt1, &pt1_org);
			break;
		case MP_INPKB_DIR1PT:									// 方向１点入力
			iMode = 2;
			irt = mhInput::GetLen2Pt( iMode, ptln1, ptln1_org);
			break;
		case  MP_INPKB_LEN2PT:									// 長さ２点入力
			if ( Mstrcmp( pPartsSpec->GetPTNmParts1(), Mstr( "外壁")) == 0 && !bFirst) {
				// 外壁の2番目以降の壁は連続長さ２点入力とし最後に配置した終点を始点として終点のみ入力する
				iMode = 1;
			} else {
				iMode = 0;										// 他は、長さ２点入力
			}
			irt = mhInput::GetLen2Pt( iMode, ptln1, ptln1_org);
			bFirst = FALSE;
			break;
		case MP_INPKB_AREA:										// 領域(区画)入力
			pg1.m_n = 0;
			irt = mhInput::GetArea( &pg1);
//			irt = mtInput::GetRect2Pt( &ptln1);
			break;
		case MP_INPKB_FREE:
			pg1.m_n = 0;
			irt = mhInput::GetArea( &pg1);
			break;
        default:
			irt = 0;
//			ASSERT( 0);											// 入力点区分エラー　<ERROR>
			break;
		}
		if ( irt == MTRT_SYSTEMSTOP || irt == MTRT_CAN)
			break;

		// 配置
		//
		if ( pPartsSpec->GetPTCdInpKbn() == MP_INPKB_AREA) {
			// 領域(区画)配置、１点目と２点目を始点終点として配置する
			Ln1.p[0] = MgPoint3DC( pg1.m_p[0]);
			Ln1.p[1] = MgPoint3DC( pg1.m_p[1]);
																								//SS			z_mnIA.RibbonIO( MGET_PARTS_ATTRA, NULL);			//		部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
			z_mmIA.GetComboAttrAEntry();							//		部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
			HaitiCmd::MmPartsPlc( Ln1.p, MgVect3D( 0., 0., 1.), &pg1);	// 領域型の部品配置
			
		} else {												// その他
			// 部材配置
			ist = z_mmIA.GetComboAttrI( MC_CMB_HONS, &iNum);	// 複数部材の配置本数
			vUp = MgVect3D( 0., 0., 1.);
			
			if ( pPartsSpec->GetPTCdIzon() >= MP_IZNCD_YANEMENNARI) {
				// 屋根面なりの場合は対象屋根面に沿った高さを設定し、部材の上方向を屋根面に垂直方向に設定する
				if ( mhHaitiIn::GetCurRfm()) {
					// カレント屋根面が選択されている場合はその屋根面なりにZ座標を求める
					plnYane = mhHaitiIn::GetCurRfm()->m_Pln;
					
				} else {
					// 選択されていない場合は、入力点の位置により屋根面を選択する
					vln = ptln1[1] - ptln1[0];
					vln.SetUnitize();
					ptln1_chk[0] = ptln1[0] + 10.f * vln;
					ptln1_chk[1] = ptln1[1] - 10.f * vln;
					pRfm1 = mhHaitiIn::SrchRfm( MC_PRI_MIN_HIGHT, ptln1_chk[0]);
					pRfm2 = mhHaitiIn::SrchRfm( MC_PRI_MIN_HIGHT, ptln1_chk[1]);
					if ( pRfm1) {								//
						plnYane = pRfm1->m_Pln;					//	入力点の１点目が屋根面上の場合は、その屋根面なりにZ座標を求める
					} else if ( pRfm2) {						//
						plnYane = pRfm2->m_Pln;					//	入力点の２点目のみ屋根面上の場合は、その屋根面なりにZ座標を求める
					} else {
						plnYane = MgPlane3D( MgVect3D( 0., 0., 1.), 0.);	//	入力点が屋根面上でない場合の仮想屋根面(Z=0.)
					}
				}
				Ln1 = MgLine3D( MgPoint3DC( ptln1[0], plnYane.GetZ( ptln1[0])),
							   MgPoint3DC( ptln1[1], plnYane.GetZ( ptln1[1])));
				if ( iNum == MC_INT_AREA)						//		本数を領域で指定する複数部材配置タイプか
					PtMltBziAr = MgPoint3DC( ptln1[2], plnYane.GetZ( ptln1[2]));

				MREAL rYHHosei = MC_YANE_TAKASA_HOSEI;
				if ( !MGeo::CheckZero( plnYane.v.z) ) 
					rYHHosei /= plnYane.v.z;
				Ln1.p[0] += MgVect3D( 0., 0., rYHHosei);
				Ln1.p[1] += MgVect3D( 0., 0., rYHHosei);
				PtMltBziAr += MgVect3D( 0., 0., rYHHosei);
				if ( pPartsSpec->GetPTCdIzon() == MP_IZNCD_YANEMENNARIENCYOKU)
					vUp = plnYane.v;
			} else {
				// その他の場合(屋根面なりでない場合)
				Ln1 = MgLine3DC( MgLine2D(ptln1));				//			Z座標=0
				PtMltBziAr = MgPoint3DC( ptln1[2]);
			}
			
			// 配置本数と方向付き間隔を求める
			//
			ist = z_mmIA.GetComboAttrR( MC_CMB_INTR, &rIntrv);	//		間隔
			if ( iNum == MC_INT_AREA) {							//			本数を領域で指定する複数部材の配置
				VtArea = PtMltBziAr - Ln1.p[0];
				iNum = MGMIN( MINT( MGeo::LenVect3D( VtArea) / rIntrv + 1.0 + MGPTOL->D),
							  MMAX_BZI_HONSU);					//			部材配置本数を最大100本に限定
				if ( iNum > 1)
					VtBziIntrv = rIntrv * MGeo::UnitizeVect3D( VtArea);
				else
				VtBziIntrv = MgVect3D( 1., 0., 0.);				//			dumy
					
			} else {											//			本数指定による複数部材の配置
				MgVect2D vtutBzi = MGeo::UnitizeVect2D( MgVect2DC( Ln1.p[1] - Ln1.p[0]));
				if ( pPartsSpec->GetPTCdInpKbn() != MP_INPKB_DIR1PT)	//			方向１点の場合は方向に向かって複数配置する
					vtutBzi.SetRotR90();						//			長さ２点の場合は右側方向に複数配置する
				VtBziIntrv = rIntrv * MgVect3DC( vtutBzi);
				
			}
			// Undoをきる
			HaitiCmd::MmPresetCmd();
			// 入力した属性を設定する
			if ( pPartsSpec->IsPanel() || pPartsSpec->IsKaiko()) {
																								//SS				z_mnIA.RibbonIO( MGET_PARTS_ATTRA, NULL);		//		部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
				z_mmIA.GetComboAttrAEntry();					//		部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
			} else {
																								//SS				z_mnIA.RibbonIO( MGET_PARTS_ATTRA, NULL);		//		部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
				z_mmIA.GetComboAttrAEntry();					//		部品仕様,寸法形式と属性値入力用コンボボックスの値を部品配置入力データに取り込む
			}
			// 本数分配置する
			if ( iNum == 0) iNum = 1;							//		本数未入力の場合は１本とする
			for ( ic1=0; ic1<iNum; ic1++) {
				HaitiCmd::MmPartsPlc( Ln1.p, vUp);				//		<<< 部材を配置する >>>
				Ln1 = Ln1 + VtBziIntrv;
			}
		}
		// 壁の整合性を整える
		if ( pPartsSpec->GetPTCdBr() == MP_BR_KABE)
			IeModel::MhKabeSetUpFlg();							//		壁データの場合は接続壁を追加、修正する
		IeModel::MhNormKabe( 1);
		// 基礎の整合性を整える
		if ( pPartsSpec->GetPTCdBr() == MP_BR_KISO)
			IeModel::MhKisoSetUpFlg();							//		壁データの場合は接続壁を追加、修正する
		IeModel::MhNormKiso( 1);
		// 再表示し修正を反映する
		WindowCtrl::ReDrawWnd();
		// 正常終了で、エラー標示をクリアする
		Msg::ClearErrorMsg();
	}
	if ( mhHaitiIn::GetCurRfm()) {
		mhHaitiIn::SetCurRfm( NULL);							// 屋根面の選択を開放する
		WindowCtrl::ReDrawWnd();
	}
	Msg::OperationMsg( MC_OPRT_BASE);							// ステイタスバーの操作表示部へ""を表示
}

/////////////////////////////////////////////////////////////////////////////
//	構造屋根入力

/*
	MP_GP_KISO = 1,							// "基礎"
	MP_GP_DODAI,							// "土台"
	MP_GP_YUKA,								// "床組"
	MP_GP_KABE,								// "壁枠組"
	MP_GP_TAIRYOKU,							// "耐力壁"
	MP_GP_TENJO,							// "天井組"
	MP_GP_KOYA,								// "小屋組"
	MP_GP_YAGIRI,							// "矢切"
	MP_GP_YANE								// "屋根"

	MP_BR_BUZAI,							// "部材"
	MP_BR_KANAGU,							// "金物"
	MP_BR_PANEL,							// "パネル"
	MP_BR_YANE,								// "屋根"
	MP_BR_KABE,								// "壁"
	MP_BR_SENBUN,							// "線分"
	MP_BR_KUKAKU,							// "区画"
	MP_BR_CYUKI,							// "注記"
	MP_BR_OTHER = 9							// "その他"
*/

/////////////////////////////////////////////////////////////////////////////
//	屋根入力

void MCmdStructRoof()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

	// 部品選択用のコンボボックスに表示する
	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_YANE, MP_BR_BUZAI, Mstr( "垂木"), Mstr( "204"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	構造天井入力

void MCmdStructCeiling()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

	// 部品選択用のコンボボックスに表示する
	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_TENJO, MP_BR_BUZAI, Mstr( "天井根太"), Mstr( "204"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	構造壁入力

void MCmdStructWall()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

	// 部品選択用のコンボボックスに表示する
	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_KABE, MP_BR_BUZAI, Mstr( "たて枠"), Mstr( "204"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	構造床入力

void MCmdStructFloor()
{
	MINT	ist1;

	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

	// 部品選択用のコンボボックスに表示する
	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_YUKA, MP_BR_BUZAI, Mstr( "床根太"), Mstr( "210"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	構造土台入力

void MCmdStructDodai()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

	// 部品選択用のコンボボックスに表示する
	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_DODAI, MP_BR_BUZAI, Mstr( "土台"), Mstr( "404G"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}

/////////////////////////////////////////////////////////////////////////////
//	基礎入力

void MCmdKiso()
{
	MINT	ist1;
	MmWndInfo*	pWndInfo = WindowCtrl::GetCurWndInfo();					// カレントウィンドウを取得する
	CWnd*		pWnd = pWndInfo->GetWnd();

	// 部品選択用のコンボボックスに表示する
	ist1 = z_mnIA.SetRibbonBarEntry( MP_GP_KISO, MP_BR_OTHER, Mstr( "外部布基礎"), Mstr( "120"));
	if ( ist1 == 0)
		MCmdLine( pWnd);
}


} // namespace MC