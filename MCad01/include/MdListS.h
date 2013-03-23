#pragma once
//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MbSlist.h
//
//		�����^�̑o�������X�g
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "mdPlex.h"

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_SLIST_DO
	#define DLL_EXPORT							__declspec( dllexport)
#else
//	#define DLL_EXPORT							__declspec( dllimport)
	#define DLL_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
//
// �o�������X�g ���̃����N�^
//

class DLL_EXPORT MbSListO : public MbSynchroObj
{
protected:
	struct CNode
	{
		CNode*		pNext;							// ���̎��̂ւ̃����N
		CNode*		pPrev;							// �O�̎��̂ւ̃����N
		MOBJECT*	pEnt;						// ���̂ւ̃|�C���^
	};
public:
	CNode		m_sStart;							// ��_
	MINT		m_nCount;							// ���̐�

	CNode*		m_pFree;						// �J���m�[�h�̊�_
	MINT		m_nRecSize;							// ���R�[�h�T�C�Y( byte)

	mdPlex*		m_pBlocks;							// �m�[�h�m�ۗ̈�
	MINT		m_nBlockSize;						// �m�[�h�m�ےP��

	// ���߂̃����N�̎��o��	 return			  : �ŏ��̃����N
	CNode*		GetFirst ( )
						{ return m_sStart.pNext;}

	// �Ō�̃����N�̎��o��	 return			  : �Ō�̃����N
	CNode*		GetLast  ( )
						{ return m_sStart.pPrev;}

public:

	// �R���X�g���N�^
	MbSListO( MINT nBlockSize);

	// �R�s�[�R���X�g���N�^
//	MbSListO( MbSListO& List);
	
	// �f�X�g���N�^
	~MbSListO( );

// Attributes ( head and tail)
	// count of elements
	// ���X�g���󂩂ǂ���							return: True: ��, False: ���̂�����
	bool 		IsEmpty( )
						{ return m_nCount == 0;}
	bool 		IsNotEmpty( )
						{ return m_nCount != 0;}
	// ���X�g�̎��̐��𓾂�							return: ���̂̐�
	MINT		GetCount( )
						{ return m_nCount;}
	MINT		GetSize( )
						{ return m_nCount;}
	
	// peek at head or tail
	// �擪�̎��̂𓾂�								return  : �擪���̂̃|�C���^�A�G���[�Ȃ�O
	MOBJECT*		GetHead( MPOSITION* pPosition)
						{
							SYNCHRONIZEMETHOD( );
							CNode* pNode = m_sStart.pNext;
							*pPosition = ( MPOSITION) pNode;
							if ( pNode == &m_sStart)
								return 0;
							return pNode->pEnt;
						}
	// �����̎��̂𓾂�								return  : �������̂̃|�C���^�A�G���[�Ȃ�O
	MOBJECT*	GetTail( MPOSITION* pPosition)
						{
							SYNCHRONIZEMETHOD( );
							CNode* pNode = m_sStart.pPrev;
							*pPosition = ( MPOSITION) pNode;
							if ( pNode == &m_sStart)
								return 0;
							return pNode->pEnt;
						}

// Operations
	// ���X�g�̐擪�Ɏ��̂�����						pEnt	: �}���������
	MPOSITION	Push( MOBJECT*  pEnt);
	MPOSITION	Push( class MbListO*  pListO);
	MPOSITION 	AddHead( MOBJECT*  pEnt)
						{ return Push( pEnt);}
	// ���X�g�̐擪�̎��̂����o���m�[�h����������		return	: 0: ���̖����@��0:���̂̃|�C���^
	MOBJECT* Pop( );
	MOBJECT* RemoveHead( )
						{ return Pop( );}

	// ���X�g�̖����Ɏ��̂�����						pEnt	: �}���������
	MPOSITION	Inject( MOBJECT*  pEnt);
	MPOSITION	Inject( class MbListO*  pListO);
	MPOSITION 	AddTail( MOBJECT*  pEnt)
						{ return Inject( pEnt);}
	// ���X�g�̖����̎��̂����o���m�[�h����������		return	: 0: ���̖����@��0:���̂̃|�C���^
	MOBJECT*	Eject( );
	MOBJECT*	RemoveTail( )
						{ return Eject( );}

	// remove all elements
	// ���ׂĂ̎��̂��폜����
	void		RemoveAll( );

	// iteration
	// �擪�̃m�[�h�ʒu�𓾂�
	MPOSITION 	GetHeadPosition( )
						{ return ( MPOSITION) m_sStart.pNext;}

	// �����̃m�[�h�ʒu�𓾂�
	MPOSITION 	GetTailPosition( )
						{ return ( MPOSITION) m_sStart.pPrev;}

	// �m�[�h�ʒu��i�߁A���̎��̂𓾂�					return: ���̂̃|�C���^�A�ŏI����Ȃ�O
	MOBJECT*	GetNext( MPOSITION* pPosition)			// ( i O) pPosition: �m�[�h�ʒu
						{
							SYNCHRONIZEMETHOD( );
							*pPosition = ( MPOSITION) ( ( CNode*) *pPosition)->pNext;
							if ( *pPosition == ( MPOSITION) &m_sStart) 
								return NULL;
							return ( ( CNode*) *pPosition)->pEnt;
						}

	// �m�[�h�ʒu��߂��A��O�̎��̂𓾂�				return: ���̂̃|�C���^�A�擪���O�Ȃ�O
	MOBJECT*	GetPrev( MPOSITION* pPosition)			// ( i O) pPosition: ���̃m�[�h�ʒu
						{
							SYNCHRONIZEMETHOD( );
							*pPosition = ( MPOSITION) ( ( CNode*) *pPosition)->pPrev;
							if ( *pPosition == ( MPOSITION) &m_sStart) 
								return NULL;
							return ( ( CNode*) *pPosition)->pEnt;
						}

	// �w��ʒu�̎��̂𓾂�								return	: 0: ���̖����@��0:���̂̃|�C���^
	MOBJECT*	GetAt( MPOSITION* pPosition)
						{ return ( ( CNode*) *pPosition)->pEnt;}

	// �w��ʒu�Ɏ��̂���������
	void 		SetAt( MPOSITION* *pPosition, MOBJECT* pEnt)
						{ ( ( CNode*) *pPosition)->pEnt = pEnt;}

	// �w��ʒu�̃m�[�h�Ǝ��̂��폜���A��O�̃m�[�h�ʒu��Ԃ�	pPosition   : �폜������̂̃m�[�h�ʒu
	void		RemoveAt( MPOSITION* pPosition);

	// inserting before or after a given position
	// �w��ʒu�̑O�ɑ}��							 pEnt	: �}���������
	//											     pPosition	: ���̎��̂̑O�ɑ}�������
	void		InsertBefore( MOBJECT* pEnt, MPOSITION* pPosition);
	// �w��ʒu�̌�ɑ}��							 pEnt    : �}���������
	//											     pPosition	: ���̎��̂̌�ɑ}�������
	void		InsertAfter( MOBJECT* pEnt, MPOSITION* pPosition);

	// helper functions ( note: O( n) speed)
	MPOSITION Find( MOBJECT* searchValue, MPOSITION startAfter = NULL);
		// defaults to starting at the HEAD, return NULL if not found
	MPOSITION FindIndex( MINT nIndex);
		// get the 'nIndex'th element ( may return NULL)

//	Implementation
protected:
	//	�m�[�h�̒ǉ�
	CNode*		NewNode( MOBJECT* pEnt, CNode* pPrev, CNode* pNext);
	
	//	�m�[�h�̊J��
	void		FreeNode( CNode* pNode);
};

/////////////////////////////////////////////////////////////////////////////
//
// �o�������X�g ���̑g���^
//

class DLL_EXPORT MbSListE : public MbSynchroObj
{

protected:
	struct CNode
	{
		CNode*		pNext;							// ���̎��̂ւ̃����N
		CNode*		pPrev;							// �O�̎��̂ւ̃����N
		MOBJECT*	pEnt;						// ���̂ւ̃|�C���^
	};
public:
	CNode		m_sStart;							// ��_
	MINT		m_nCount;							// ���̐�

	CNode*		m_pFree;						// �J���m�[�h�̊�_
	MINT		m_nEntType;						// ���̃T�C�Y( byte)
	MINT		m_nRecSize;							// ���R�[�h�T�C�Y( byte)

	mdPlex*		m_pBlocks;							// �m�[�h�m�ۗ̈�
	MINT		m_nBlockSize;						// �m�[�h�m�ےP��

	// ���߂̃����N�̎��o��	 return			  : �ŏ��̃����N
	CNode*		GetFirst ( )
						{ return m_sStart.pNext;}

	// �Ō�̃����N�̎��o��	 return			  : �Ō�̃����N
	CNode*		GetLast  ( )
						{ return m_sStart.pPrev;}

public:

	// �R���X�g���N�^
	MbSListE( MINT nBlockSize, MINT nRecSize);

	// �R�s�[�R���X�g���N�^
//	MbSListE( MbSListE& List);
	
	// �f�X�g���N�^
	~MbSListE( );

// Attributes ( head and tail)
	// count of elements
	// ���X�g���󂩂ǂ���							return: True: ��, False: ���̂�����
	bool 		IsEmpty( )
						{ return m_nCount == 0;}
	bool 		IsNotEmpty( )
						{ return m_nCount != 0;}
	// ���X�g�̎��̐��𓾂�							return: ���̂̐�
	MINT		GetCount( )
						{ return m_nCount;}
	MINT		GetSize( )
						{ return m_nCount;}
	
	// peek at head or tail
	// �擪�̎��̂̃|�C���^�𓾂�					return  : �擪���̂̃|�C���^�A�G���[�Ȃ�O
	MOBJECT*	GetHead( MPOSITION* pPosition)
						{
							SYNCHRONIZEMETHOD( );
							CNode* pNode = m_sStart.pNext;
							*pPosition = ( MPOSITION) pNode;
							if ( pNode == &m_sStart)
								return 0;
							return ( MOBJECT*) &( pNode->pEnt);
						}
	// �����̎��̂̃|�C���^�𓾂�					return  : �������̂̃|�C���^�A�G���[�Ȃ�O
	MOBJECT*	GetTail( MPOSITION* pPosition)
						{
							SYNCHRONIZEMETHOD( );
							CNode* pNode = m_sStart.pPrev;
							*pPosition = ( MPOSITION) pNode;
							if ( pNode == &m_sStart)
								return 0;
							return ( MOBJECT*) &( pNode->pEnt);
						}

// Operations
	// ���X�g�̐擪�Ɏ��̂�����						pEnt	: �}���������
	MPOSITION	Push( MOBJECT*  pEnt);
	MPOSITION	Push( class MbListE*  pListE);
	MPOSITION 	AddHead( MOBJECT*  pEnt)
						{ return Push( pEnt);}
	// ���X�g�̐擪�̎��̂����o����������				return	: 0: ���̖����@1:���̗L��
	MINT		Pop( MOBJECT* pEnt);
	MINT		RemoveHead( MOBJECT* pEnt)
						{ return Pop( pEnt);}

	// ���X�g�̖����Ɏ��̂�����						pEnt	: �}���������
	MPOSITION	Inject( MOBJECT*  pEnt);
	MPOSITION	Inject( class MbListE*  pListE);
	MPOSITION 	AddTail( MOBJECT*  pEnt)
						{ return Inject( pEnt);}
	// ���X�g�̖����̎��̂����o����������				return	: 0: ���̖����@1:���̗L��
	MINT		Eject( MOBJECT* pEnt);
	MINT		RemoveTail( MOBJECT* &pEnt)
						{ return Eject( pEnt);}

	// remove all elements
	// ���ׂĂ̎��̂��폜����
	void		RemoveAll( );

	// iteration
	// �擪�̃m�[�h�ʒu�𓾂�
	MPOSITION 	GetHeadPosition( )
						{ return ( MPOSITION) m_sStart.pNext;}

	// �����̃m�[�h�ʒu�𓾂�
	MPOSITION 	GetTailPosition( )
						{ return ( MPOSITION) m_sStart.pPrev;}

	// �m�[�h�ʒu��i�߁A���̎��̂̃|�C���^�𓾂�	return: ���̂̃|�C���^�A�ŏI����Ȃ�O
	MOBJECT*	GetNext( MPOSITION* pPosition)			// ( i O) pPosition: �m�[�h�ʒu
						{
							SYNCHRONIZEMETHOD( );
							*pPosition = ( MPOSITION) ( ( CNode*) *pPosition)->pNext;
							if ( *pPosition == ( MPOSITION) &m_sStart) 
								return NULL;
							return ( MOBJECT*) &( ( CNode*) *pPosition)->pEnt;
						}

	// �m�[�h�ʒu��߂��A��O�̎��̂̃|�C���^�𓾂�	return: ���̂̃|�C���^�A�擪���O�Ȃ�O
	MOBJECT*	GetPrev( MPOSITION* pPosition)			// ( i O) pPosition: �m�[�h�ʒu
						{
							SYNCHRONIZEMETHOD( );
							*pPosition = ( MPOSITION) ( ( CNode*) *pPosition)->pPrev;
							if ( *pPosition == ( MPOSITION) &m_sStart) 
								return NULL;
							return ( MOBJECT*) &( ( CNode*) *pPosition)->pEnt;
						}

	// �w��ʒu�̎��̂̃|�C���^�𓾂�
	MOBJECT*	GetAt( MPOSITION* pPosition)
						{ return ( MOBJECT*) &( ( CNode*) *pPosition)->pEnt;}

	// �w��ʒu�Ɏ��̂���������
	void 		SetAt( MPOSITION* pPosition, MOBJECT* pEnt)
						{ memcpy( &( ( CNode*) *pPosition)->pEnt, pEnt, m_nEntType);}

	// �w��ʒu�̃m�[�h�Ǝ��̂��폜���A��O�̃m�[�h�ʒu��Ԃ�	pPosition   : �폜������̂̃m�[�h�ʒu
	void		RemoveAt( MPOSITION* pPosition);

	// inserting before or after a given position
	// �w��ʒu�̑O�Ɏ��̂�}������					 pEnt	: �}���������
	//											     pPosition	: ���̎��̂̑O�ɑ}�������
	void		InsertBefore( MOBJECT* pEnt, MPOSITION* pPosition);
	// �w��ʒu�̌�Ɏ��̂�}������					 pEnt    : �}���������
	//											     pPosition	: ���̎��̂̌�ɑ}�������
	void		InsertAfter( MOBJECT* pEnt, MPOSITION* pPosition);

	// helper functions ( note: O( n) speed)
	MPOSITION Find( MOBJECT* searchValue, MPOSITION startAfter = NULL);
		// defaults to starting at the HEAD, return NULL if not found
	MPOSITION FindIndex( MINT nIndex);
		// get the 'nIndex'th element ( may return NULL)

//	Implementation
protected:
	//	�m�[�h�̒ǉ�
	CNode*		NewNode( MOBJECT* pEnt, CNode* pPrev, CNode* pNext);
	
	//	�m�[�h�̊J��
	void		FreeNode( CNode* pNode);
};

