//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
// MtAskForPoint.CPP
// 
//	�@�\	�����C�x���g�擾
//								���W����
// 
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include	"MsMCAD.h"
#include	"MtAskForPoint.h"
#include	"MsDefConst.h"
#include	"MtPrcEvent.h"
#include	"MtPrcEventQueue.h"
//#include	"MtThread.h"
#include	"MsMCadApi.h"

namespace MC
{

static	MCHAR	MT_zthekeyword[MC_MCADBUF];
static	CString	MT_zKeywords;
static	MINT	MT_znflag;

////////////////////////////////////////////////////////////////////////////////
// (Command_3) �ΏۂƂȂ�C�x���g�@( ���́A �R�}���h�A�V�X�e���X�g�b�v) ������܂ő҂�
//
MINT	MtAskForPoint(
						MgPoint2D*		o_ptResultPoint		// where
					 )
{
	MINT		ist = 0;
	MINT		ret2 = MTRT_FAIL;
	MINT		retcode = MTRT_NORM;
	MCHAR		fs1[MC_MCADBUF];

	if ( MtChkStopThread()) {
		retcode = MTRT_SYSTEMSTOP;
		MQUIT;
	} 

	MFOREVER {
		while (MtWaitLoop()) {									// 2nd.
			if ( MtChkStopThread()) {
				retcode = MTRT_SYSTEMSTOP;
				MQUIT;
			}
			if ( MtGetCommandQueue()->IsNotEmpty())
				break;
		} // end of while( MtWaitLoop())

		MINT irestype = MtGetCommandQueue()->PeekItem()->m_restype;

		if( irestype == MTRT_CAN) {
			MtGetCommandQueue()->AdvanceNext();
			retcode = MTRT_CAN; 
			break;

		} else if ( irestype == MTRT_LBTNDWN) {
			MtSetNFlag( MtGetCommandQueue()->PeekItem()->m_nflag);
//			o_ptResultPoint->Set( MtGetCommandQueue()->PeekItem()->m_resval.rpoint);
			*o_ptResultPoint = MtGetCommandQueue()->PeekItem()->m_resval.rpoint;
			MtGetCommandQueue()->AdvanceNext();
            retcode = MTRT_LBTNDWN; 
			break;

		} else if ( irestype == MTRT_MBTNDWN) {
			MtSetNFlag( MtGetCommandQueue()->PeekItem()->m_nflag);
//			o_ptResultPoint->Set( MtGetCommandQueue()->PeekItem()->m_resval.rpoint);
			*o_ptResultPoint = MtGetCommandQueue()->PeekItem()->m_resval.rpoint;
			MtGetCommandQueue()->AdvanceNext();
            retcode = MTRT_MBTNDWN; 
			break;

		} else if ( irestype == MTRT_RBTNDWN) {
			MtSetNFlag( MtGetCommandQueue()->PeekItem()->m_nflag);
//			o_ptResultPoint->Set( MtGetCommandQueue()->PeekItem()->m_resval.rpoint);
			*o_ptResultPoint = MtGetCommandQueue()->PeekItem()->m_resval.rpoint;
			MtGetCommandQueue()->AdvanceNext();
            retcode = MTRT_RBTNDWN; 
			break;

	    } else if( (irestype == MTRT_MENUCOMMAND) && 
            (MtGetCommandQueue()->PeekItem()->m_resval.rstring != NULL)) {
			ASSERT( Mstrlen( MtGetCommandQueue()->PeekItem()->m_resval.rstring) <= Msizeof( fs1));
            Mstrncpy_s( fs1, MtGetCommandQueue()->PeekItem()->m_resval.rstring, Msizeof(fs1));
			ret2 = MtSetKeyWord( MtGetCommandQueue()->PeekItem()->m_resval.rstring);
			MtGetCommandQueue()->AdvanceNext();
			retcode = MTRT_KWORD; 
			break; 

		} else {
			MtGetCommandQueue()->AdvanceNext();
//            retcode = MTRT_NONE; 
//			break;

		} // end
	} // end of for(;;)
exit:
	if( retcode == MTRT_SYSTEMSTOP)
		MtGetCommandQueue()->Flush();
	return(retcode);

}	// END OF MtAskForPoint

MINT MtSetKeyWord( const MCHAR* str) {

	Mstrcpy_s( MT_zthekeyword, str);
	return MTRT_KWORD;
}

MINT MtGetInp( MCHAR* o_sEntry, int i_nEntry)
{
    Mstrcpy_s( o_sEntry, i_nEntry, MT_zthekeyword);
	return MTRT_NORM;
}

void MtSetNFlag( MINT nflag) {
	MT_znflag = nflag;
}

MINT MtGetNFlag( void) {
	return MT_znflag;
}

} // namespace MC