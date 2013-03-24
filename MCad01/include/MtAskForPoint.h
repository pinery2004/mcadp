#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MtAskForPoint.h
//
//	機能	コマンド処理イベント取得			
//
//  K.Matsu           08/01/04    Created.
//
#include "MgPoint.h"

namespace MC
{

void MtOpen();
void MtClose();
MINT MtWaitLoop( void);

MINT MtAskForPoint(
						MgPoint2*		pt1
						);

struct MT_InternalCmdList {
    MCHAR* globalName;
	void* funcPtr;
	short cmdFlags;
    MCHAR* localName;
    int   cmdIndex;
};

MINT MtSetKeyWord( const MCHAR* str);

MINT MtGetInp( MCHAR* o_sEntry, int i_nEntry);

template<size_t SIZE>
MINT MtGetInp( MCHAR (&o_sEntry)[SIZE])
{
    return MtGetInp( o_sEntry, SIZE);
}

void MtSetNFlag( const MINT nflag);
MINT MtGetNFlag( void);
MINT MtSendMessage( MINT message, MINT nFlags, MgPoint2* pPtMR);

class	MtPrcEventQueue *MtGetCommandQueue( void);
class	MtPrcEventQueue *MtGetMenuQueue();
void	MtMnuStrToRB( class MtPrcEventQueue* pRbQue, MCHAR* mnustr);
MINT	MtSendMessage( MINT message, MINT nFlags, MgPoint2* pPtMR);
MINT	MtDoOneCommand(MCHAR* cmd, int pushlsp);
MINT	MtCmdThread( void);

} // namespace MC