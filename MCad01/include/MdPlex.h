#pragma once
//==========================================================================================
//  Copyright (C) K.Matsubayashi All rights reserved.
//
//  MODULE: mdPlex.h
//
//		
//
//  K.Matsu           13/02/20    Created.
//==========================================================================================
#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_PLEX_DO
	#define DLL_EXPORT							__declspec( dllexport)
#else
//	#define DLL_EXPORT							__declspec( dllimport)
	#define DLL_EXPORT
#endif

struct	mdPlex;

struct DLL_EXPORT mdPlex	   // warning variable length structure
{
	mdPlex* pNext;

	void* data( ) { return this+1; }

	static mdPlex* Create( mdPlex*& head, MINT nMax, MINT cbElement);
			// like 'calloc' but no zero fill
			// may throw memory exceptions

	void FreeDataChain( );       // free this one and links
};
