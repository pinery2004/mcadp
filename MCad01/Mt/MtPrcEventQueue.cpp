//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
// MtPrcEventQueue.cpp
// 
//	�@�\	�R�}���h�L���[�Ǘ�
// 
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsMCad.h" /*DNT*/
#include "MsMCadApi.h"
#include "MtPrcEvent.h"
#include "MdList.h"
#include "MtPrcEventQueue.h" /*DNT*/

namespace MC
{

//	��̑S�ẴR�}���h����������i�����̈���܂ށj
void MtPrcEventQueue::Flush( void)
{
	SYNCHRONIZEMETHOD();

	MtPrcEvent*	pRb;
	MPOSITION	pos1;
	
	// �S���R�[�h�̍��ڂ̑����̈���J������
	for (pRb=(MtPrcEvent*)GetHead( &pos1); pRb!=0; pRb=(MtPrcEvent*)GetNext( &pos1)) {
		if ( pRb)
			pRb->Free();
	}
	RemoveAll();												// �L���[�̑S���R�[�h������
}

//	��̐擪�̃R�}���h����������i�����̈���܂ށj
void MtPrcEventQueue::FreeNext(void) 
{
	SYNCHRONIZEMETHOD();

	MtPrcEvent	Rb;

	Pop( &Rb);													// �擪�̃R�}���h�����o���L���[����J������
	Rb.Free();
}

//	��̐擪�̃R�}���h���������i�����̈���܂ށj���̃R�}���h���擾����
MtPrcEvent* MtPrcEventQueue::AdvanceNext( void)
{
	SYNCHRONIZEMETHOD();

	FreeNext();

	return this->PeekItem();
}

//	��̖����ɃR�}���h��ǉ�����(�������ڂ̓|�C���^�̂݃R�s�[���������̈�����̂܂܈����p��)
void MtPrcEventQueue::AddItem( MtPrcEvent *pItem)
{
	SYNCHRONIZEMETHOD();

	Inject( pItem);
}

//	��̐擪�ɃR�}���h��ǉ�����(�������ڂ̓|�C���^�̂݃R�s�[���������̈�����̂܂܈����p��)
void MtPrcEventQueue::AddItemToFront( MtPrcEvent *pItem)
{
	SYNCHRONIZEMETHOD();

	Push( pItem);
}

//	��̖����ɑ��̗��ǉ�����(���F�������ڂ̓|�C���^�̂݃R�s�[���������̈�����̂܂܈����p��)
void MtPrcEventQueue::AddQueue( MtPrcEventQueue *pOther)
{
	SYNCHRONIZEMETHOD();

	ASSERT( pOther != this);  // maybe we should allow to concat to itself, but....

	CNode* pNode = pOther->GetFirst();							// start at Head
	for (; pNode != &(pOther->m_sStart); pNode = pNode->pNext)
		Push( (MtPrcEvent*)&(pNode->pEnt));
}

//	��̐擪�̃R�}���h�����o���A�񂩂��������(���F�������ڂ̓|�C���^�̂݃R�s�[���������̈�����̂܂܈����p��)
void MtPrcEventQueue::PopItem( MtPrcEvent* pRb)
{
	SYNCHRONIZEMETHOD();

	Pop( pRb);
}

bool MtPrcEventQueue::IsCommandPause( void)
{
	SYNCHRONIZEMETHOD();

	MPOSITION	Pos;
	MtPrcEvent*	pRb;

	bool bRv = false;
	if ( (pRb = (MtPrcEvent*)GetHead( &Pos)) != 0)
		if ( (pRb->m_restype == MTRT_MENUCOMMAND) && (pRb->m_resval.rstring[0] == '\\'))
			bRv = true;
	return bRv;
}

} // namespace MC