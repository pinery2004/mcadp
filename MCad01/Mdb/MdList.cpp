//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: Mblist.h
//
//		�o�������X�g�@���̃����N�^
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#define	 DLL_EXPORT_LIST_DO
#include "MdList.h"

/******************************************************************************************************************
  MbListO �̃��\�b�h ���̃����N�^
******************************************************************************************************************/

//////////////////////////////////////////////////////////////
//	���X�g�̐V�K�쐬�@�R���X�g���N�^
MbListO::MbListO(
					MINT	i_nBlockSize		// 1�u���b�N������̃m�[�h��
				)
{
	m_sStart.pEnt = NULL;
	m_sStart.pNext = &m_sStart;
	m_sStart.pPrev = &m_sStart;
	m_nCount = 0;

	m_nRecSize = sizeof( CNode);

	m_pFree = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = i_nBlockSize;
}

MbListO::~MbListO( )
{
	RemoveAll( );
}
//////////////////////////////////////////////////////////////
//	���X�g�̐擪�Ɏ��̂�ǉ�����
MPOSITION MbListO::Push(
					MOBJECT*	i_pEnt			// �G���e�B�e�B�ւ̃|�C���^ 
				)
{
	return ( MPOSITION) NewNode( i_pEnt, &m_sStart, GetFirst( ));
}

//////////////////////////////////////////////////////////////
//	���X�g�̐擪������̂����o���i���X�g�̐擪�̃m�[�h�͍폜�A
//									���R�[�h�^�C�v���O�̎��͎��̂ւ̃|�C���^��Ԃ��A���͎̂c��
//									���R�[�h�^�C�v���O�̎��͎��̂�Ԃ��j
MOBJECT* MbListO::Pop( )
{
	CNode*		pNode = m_sStart.pNext;
	MOBJECT*	ret = pNode->pEnt;
	if ( pNode != &m_sStart)
		FreeNode( pNode);
	return	ret;
}

//////////////////////////////////////////////////////////////
//	���X�g�̖����Ɏ��̂�ǉ�����
MPOSITION MbListO::Inject(
					MOBJECT*	i_pEnt			// �G���e�B�e�B�ւ̃|�C���^
				)
{
 	return ( MPOSITION) NewNode( i_pEnt, GetLast( ), &m_sStart);
}

//////////////////////////////////////////////////////////////
//	���X�g�̖���������̂����o���i���X�g�̐擪�̃m�[�h�͍폜�A
//									���R�[�h�^�C�v���O�̎��͎��̂ւ̃|�C���^��Ԃ��A���͎̂c��
//									���R�[�h�^�C�v���O�̎��͎��̂�Ԃ��j
MOBJECT* MbListO::Eject( )
{
	CNode*	pNode = GetLast( );
	MOBJECT* ret = pNode->pEnt;
	if ( pNode != &m_sStart)
		FreeNode( pNode);
	return	ret;
}

//////////////////////////////////////////////////////////////
//	�w��m�[�h�̒��O�Ɏ��̂�ǉ�����
void MbListO::InsertBefore(
					MOBJECT*	i_pEnt,			// �G���e�B�e�B�ւ̃|�C���^
					MPOSITION*	io_pPosition	// �m�[�h�ʒu
				)
{
	NewNode( i_pEnt, ( ( CNode*)*io_pPosition)->pPrev, ( ( CNode*)*io_pPosition));
}

//////////////////////////////////////////////////////////////
//	�w��m�[�h�̒���Ɏ��̂�ǉ�����
void MbListO::InsertAfter(
					MOBJECT*	i_pEnt,			// �G���e�B�e�B�ւ̃|�C���^
					MPOSITION*	io_pPosition	// �m�[�h�ʒu
				)
{
	NewNode( i_pEnt, ( CNode*)*io_pPosition, ( ( CNode*)*io_pPosition)->pNext);
}

//////////////////////////////////////////////////////////////
//	�w��m�[�h�ʒu�̃G���e�B�e�B���폜���A���O�̃m�[�h�ʒu��Ԃ�
void MbListO::RemoveAt(
					MPOSITION*	io_pPosition	// (in)�폜�m�[�h�ʒu�A(out)���O�̃m�[�h�ʒu
				)
{
	CNode* pNode = ( CNode*) *io_pPosition;
	*io_pPosition = ( MPOSITION) pNode->pPrev;
	MBDELETE( pNode->pEnt);
	FreeNode( pNode);
}

//////////////////////////////////////////////////////////////
//	�S�m�[�h�ʒu�̃G���e�B�e�B���폜����
void MbListO::RemoveAll( )
{
	CNode*	pNode;
	CNode*	pNext;
	for ( pNode = GetFirst( ); pNode != &m_sStart; pNode = pNext) {
		pNext = pNode->pNext;
		MBDELETE( pNode->pEnt);
	}
	m_nCount = 0;
	m_sStart.pNext = &m_sStart;
	m_sStart.pPrev = &m_sStart;

	m_pBlocks->FreeDataChain( );
	m_pBlocks = NULL;
	m_pFree = NULL;
}

/////////////////////////////////////////////////////////////////////////////
//		�擪�܂��͎w��m�[�h�̎��̃m�[�h���G���e�B�e�B����������
MPOSITION MbListO::FindIndex(
					MINT		i_nIndex			// 
				)
{
	CNode*	pNode;
	_ASSERTE( this);

	if ( i_nIndex >= m_nCount || i_nIndex < 0)
		return NULL;											// went too far

	pNode = &m_sStart;
	while ( i_nIndex--)
	{
		pNode = pNode->pNext;
	}
	return ( MPOSITION) pNode;
}

/////////////////////////////////////////////////////////////////////////////
//		�擪�܂��͎w��m�[�h�̎��̃m�[�h���G���e�B�e�B����������
MPOSITION MbListO::Find(
					MOBJECT*	i_pSrchEnt,		// �����G���e�B�e�B
					MPOSITION	i_startAfter	// �������O�̃m�[�h�ʒu�@=0:�擪�m�[�h�A!=0:�w��m�[�h
				)
{
	_ASSERTE( this);

	CNode* pNode = ( CNode*) i_startAfter;
	if ( pNode == NULL)
	{
		pNode = GetFirst( );										// start at head
	}
	else
	{
		_ASSERTE( pNode);
		pNode = pNode->pNext;									// start after the one specified
	}

	for ( ; pNode != &m_sStart; pNode = pNode->pNext)
		if ( pNode->pEnt == i_pSrchEnt)
			return ( MPOSITION) pNode;
	return NULL;
}

//////////////////////////////////////////////////////////////
//	�m�[�h�̑}��
MbListO::CNode*
MbListO::NewNode(
					MOBJECT*	i_pEnt,			// 
					CNode*		io_pPrev,		// 
					CNode*		io_pNext		// 
				)
{
	if ( m_pFree == NULL) {
		// �󂫃m�[�h���Ȃ��ꍇ�́A�m�[�h�u���b�N��ǉ�
		mdPlex* pNewBlock = mdPlex::Create( m_pBlocks, m_nBlockSize, m_nRecSize);
		// chain them into free list
		CNode* pNode = ( CNode*) pNewBlock->data( );
		// free in reverse order to make it easier to debug
		pNode = ( CNode*)( ( char*)pNode + m_nRecSize * ( m_nBlockSize - 1));
		for ( MINT i = m_nBlockSize-1; i >= 0; i--)
		{
			pNode->pNext = m_pFree;
			m_pFree = pNode;
			pNode = ( CNode*)( ( char*)pNode - m_nRecSize);
		}
	}
	_ASSERTE( m_pFree);  // we must have something

	CNode*	pNode = m_pFree;
	m_pFree = m_pFree->pNext;
	
	pNode->pEnt = i_pEnt;

	pNode->pPrev = io_pPrev;
	pNode->pNext = io_pNext;
	io_pPrev->pNext = pNode;
	io_pNext->pPrev = pNode;
	
	m_nCount++;
	return pNode;
}

//////////////////////////////////////////////////////////////
//	�m�[�h�̊J��
void	MbListO::FreeNode(
					CNode*		i_pNode
				)
{
//	_ASSERTE( pNode != 0);
	i_pNode->pPrev->pNext = i_pNode->pNext;
	i_pNode->pNext->pPrev = i_pNode->pPrev;

	i_pNode->pNext = m_pFree;
	m_pFree = i_pNode;
	
	m_nCount--;
	_ASSERTE( m_nCount >= 0);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if ( m_nCount == 0)
		RemoveAll( );
}
//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: Mblist.h
//
//		�o�������X�g	���̑g���^
//
//  Modification History
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

/******************************************************************************************************************
  MbListE �̃��\�b�h
******************************************************************************************************************/

MbListE::MbListE(
					MINT	i_nBlockSize,		// 1�u���b�N������̃m�[�h��
					MINT	i_nRecSize			// ���R�[�h�T�C�Y
				)
{
	m_sStart.pEnt = NULL;
	m_sStart.pNext = &m_sStart;
	m_sStart.pPrev = &m_sStart;
	m_nCount = 0;

	m_nEntType = i_nRecSize;
	m_nRecSize = sizeof( CNode) + ( i_nRecSize - sizeof( char*));

	m_pFree = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = i_nBlockSize;
}

MbListE::~MbListE( )
{
	RemoveAll( );
}
//////////////////////////////////////////////////////////////
//	���X�g�̐擪�Ɏ��̂�ǉ�����
MPOSITION MbListE::Push(
					MOBJECT*	i_pEnt			// �G���e�B�e�B�ւ̃|�C���^
				)
{
	return ( MPOSITION) NewNode( i_pEnt, &m_sStart, GetFirst( ));
}

//////////////////////////////////////////////////////////////
//	���X�g�̐擪������̂����o���i���X�g�̐擪�̃m�[�h�͍폜�A
//									���R�[�h�^�C�v���O�̎��͎��̂ւ̃|�C���^��Ԃ��A���͎̂c��
//									���R�[�h�^�C�v���O�̎��͎��̂�Ԃ��j
MINT MbListE::Pop(
					MOBJECT*	o_pEnt			// �G���e�B�e�B�ւ̃|�C���^
				)
{
	CNode*	pNode = GetFirst( );
	if ( pNode == &m_sStart)
		return 0;
	memcpy( o_pEnt, &pNode->pEnt, m_nEntType);

	if ( pNode != &m_sStart)
		FreeNode( pNode);
	return 1;
}

//////////////////////////////////////////////////////////////
//	���X�g�̖����Ɏ��̂�ǉ�����
MPOSITION MbListE::Inject(
					MOBJECT*	i_pEnt			// �G���e�B�e�B�ւ̃|�C���^
				)
{
 	return ( MPOSITION) NewNode( i_pEnt, GetLast( ), &m_sStart);
}

//////////////////////////////////////////////////////////////
//	���X�g�̖���������̂����o���i���X�g�̐擪�̃m�[�h�͍폜�A
//									���R�[�h�^�C�v���O�̎��͎��̂ւ̃|�C���^��Ԃ��A���͎̂c��
//									���R�[�h�^�C�v���O�̎��͎��̂�Ԃ��j
MINT MbListE::Eject(
					MOBJECT*	o_pEnt			// �G���e�B�e�B�ւ̃|�C���^
				)
{
	CNode*	pNode = GetLast( );
	if ( pNode == &m_sStart)
		return 0;
	memcpy( o_pEnt, &( pNode->pEnt), m_nEntType);

	if ( pNode != &m_sStart)
		FreeNode( pNode);
	return 1;
}

//////////////////////////////////////////////////////////////
//	�w��m�[�h�̒��O�Ɏ��̂�ǉ�����
void MbListE::InsertBefore(
					MOBJECT*	i_pEnt,			// �G���e�B�e�B�ւ̃|�C���^
					MPOSITION*	io_pPosition	// �m�[�h�ʒu
				)
{
	NewNode( i_pEnt, ( ( CNode*)*io_pPosition)->pPrev, ( ( CNode*)*io_pPosition));
}

//////////////////////////////////////////////////////////////
//	�w��m�[�h�̒���Ɏ��̂�ǉ�����
void MbListE::InsertAfter(
					MOBJECT*	i_pEnt,			// �G���e�B�e�B�ւ̃|�C���^
					MPOSITION*	io_pPosition	// �m�[�h�ʒu
				)
{
	NewNode( i_pEnt, ( CNode*)*io_pPosition, ( ( CNode*)*io_pPosition)->pNext);
}

//////////////////////////////////////////////////////////////
//	�w��m�[�h�ʒu�̃G���e�B�e�B���폜���A���O�̃m�[�h�ʒu��Ԃ�
void MbListE::RemoveAt(
					MPOSITION*	io_pPosition	// (in)�폜�m�[�h�ʒu�A(out)���O�̃m�[�h�ʒu
				)
{
	_ASSERTE( *io_pPosition);
	CNode* pNode = ( CNode*) *io_pPosition;
	*io_pPosition = ( MPOSITION) pNode->pPrev;
	FreeNode( pNode);
}

//////////////////////////////////////////////////////////////
//	�S�m�[�h�ʒu�̃G���e�B�e�B���폜����
void MbListE::RemoveAll( )
{
	m_nCount = 0;
	m_sStart.pNext = &m_sStart;
	m_sStart.pPrev = &m_sStart;

	m_pBlocks->FreeDataChain( );
	m_pBlocks = NULL;
	m_pFree = NULL;
}

/////////////////////////////////////////////////////////////////////////////
//		�w��h�c�̃G���e�B�e�B�𓾂�
MPOSITION MbListE::FindIndex(
					MINT		i_nIndex
				)
{
	CNode*	pNode;
	_ASSERTE( this);

	if ( i_nIndex >= m_nCount || i_nIndex < 0)
		return NULL;											// went too far

	pNode = &m_sStart;
	while ( i_nIndex--)
	{
		pNode = pNode->pNext;
	}
	return ( MPOSITION) pNode;
}

/////////////////////////////////////////////////////////////////////////////
//		�擪�܂��͎w��m�[�h�̎��̃m�[�h���G���e�B�e�B����������
MPOSITION MbListE::Find(
					MOBJECT*	i_pSrchEnt,		// �����G���e�B�e�B
					MPOSITION	i_startAfter	// �������O�̃m�[�h�ʒu�@=0:�擪�m�[�h�A!=0:�w��m�[�h
				)
{
	_ASSERTE( this);

	CNode* pNode = ( CNode*) i_startAfter;
	if ( pNode == NULL)
	{
		pNode = GetFirst( );										// start at head
	}
	else
	{
		_ASSERTE( pNode);
		pNode = pNode->pNext;									// start after the one specified
	}

	for ( ; pNode != &m_sStart; pNode = pNode->pNext)
		if ( ( MOBJECT*)&( pNode->pEnt) == i_pSrchEnt)
			return ( MPOSITION) pNode;
	return NULL;
}

//////////////////////////////////////////////////////////////
//	�G���e�B�e�B�m�[�h�̑}��
MbListE::CNode*
MbListE::NewNode(
					MOBJECT*	i_pEnt,
					CNode*		io_pPrev,
					CNode*		io_pNext
				)
{
	if ( m_pFree == NULL) {
		// �󂫃m�[�h���Ȃ��ꍇ�́A�m�[�h�u���b�N��ǉ�
		mdPlex* pNewBlock = mdPlex::Create( m_pBlocks, m_nBlockSize, m_nRecSize);
		// chain them into free list
		CNode* pNode = ( CNode*) pNewBlock->data( );
		// free in reverse order to make it easier to debug
		pNode = ( CNode*)( ( char*)pNode + m_nRecSize * ( m_nBlockSize - 1));
		for ( MINT i = m_nBlockSize-1; i >= 0; i--)
		{
			pNode->pNext = m_pFree;
			m_pFree = pNode;
			pNode = ( CNode*)( ( char*)pNode - m_nRecSize);
		}
	}
	_ASSERTE( m_pFree);  // we must have something

	CNode*	pNode = m_pFree;
	m_pFree = m_pFree->pNext;
	
	memcpy( &( pNode->pEnt), i_pEnt, m_nEntType);

	pNode->pPrev = io_pPrev;
	pNode->pNext = io_pNext;
	io_pPrev->pNext = pNode;
	io_pNext->pPrev = pNode;
	
	m_nCount++;
	return pNode;
}

//////////////////////////////////////////////////////////////
//	�m�[�h�̊J��
void	MbListE::FreeNode(
					CNode*		i_pNode
				)
{
//	_ASSERTE( pNode != 0);
	i_pNode->pPrev->pNext = i_pNode->pNext;
	i_pNode->pNext->pPrev = i_pNode->pPrev;

	i_pNode->pNext = m_pFree;
	m_pFree = i_pNode;
	
	m_nCount--;
	_ASSERTE( m_nCount >= 0);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if ( m_nCount == 0)
		RemoveAll( );
}

