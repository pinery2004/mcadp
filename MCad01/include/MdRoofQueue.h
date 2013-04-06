#pragma once
//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MdPartsQueue.h
//
//		���� �f�[�^�x�[�X
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
namespace MC
{

//	�����L���[
class MdRoofQueue : public MbListE
{
public:
	MdRoofQueue(  MINT nBk, MINT iSz);
	virtual ~MdRoofQueue( void);

	MPOSITION Push( MhRoofInfo *pRoofEn);
	MPOSITION Inject( MhRoofInfo *pRoofEn);

	void RemoveAll( void);
};

} // namespace MC
