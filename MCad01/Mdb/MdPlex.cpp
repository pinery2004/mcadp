//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: mdPlex.cpp
//
//		MbList, MbSList ‚Ì—ÌˆæŠm•Û
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#define	DLL_EXPORT_PLEX_DO
#include "mdPlex.h"

#define		BYTE	char

mdPlex* mdPlex::Create( mdPlex*& pHead, MINT nMax, MINT cbElement)
{
	MINT	iSz = sizeof( mdPlex) + nMax * cbElement;
	mdPlex* p = ( mdPlex*) new BYTE[iSz];
			// may throw exception
	p->pNext = pHead;
	pHead = p;  // change head ( adds in reverse order for simplicity)
	return p;
}

void mdPlex::FreeDataChain( )     // free this one and links
{
	mdPlex* p = this;
	while ( p != NULL)
	{
		BYTE* pBytes = ( BYTE*) p;
		mdPlex* pNext = p->pNext;
		MBDELETE( pBytes);
		p = pNext;
	}
}
