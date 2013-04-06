#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdPartsQueue.h
//
//		配置物 データベース
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
namespace MC
{


//	部材キュー
class MdPartsQueue : public MbListE
{
public:
	MdPartsQueue(  MINT nBk, MINT iSz);
	virtual ~MdPartsQueue( void);

	MPOSITION Push( mhPlcInfo *pPlcEn);
	MPOSITION Inject( mhPlcInfo *pPlcEn);

	void RemoveAll( void);
};

} // namespace MC
