#pragma once
//==========================================================================================
//  Copyright ( C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MbArray.h
//
//		�v�f�̏W�����Ǘ������{�N���X
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================

#ifndef ASSERT
	#define IC_DYNARRAY_H_ASSERT	
	#define ASSERT( a )			assert( ( a) )
#endif

template <class elementType>
class MbArray
	{	
	
public:
	MbArray( unsigned int nGran = 10 )
	{
		ASSERT( nGran != 0 );

	    m_nGran = nGran;
	    m_nEntries = 0;
	    m_nSize = nGran;

		m_pElements = ( elementType *)::new char[m_nGran * sizeof( elementType )];
		ASSERT( m_pElements != NULL );
	}

	~MbArray( void)
	{					 	
		delete ( char*)m_pElements;
		m_pElements = NULL;
		m_nEntries = -1;
		m_nSize = -1;
		m_nGran = -1;
	}

public:
	// �v�f�e�[�u���̐ݒ�ςݗv�f�����擾����
	//
	unsigned int Number( void)
	{ 
	 	return m_nEntries; 
	}

	// �v�f�e�[�u��( �̌��)�ɗv�f��ǉ�����
	//
	bool Add( elementType pItem )
	{
	    if ( m_nEntries == m_nSize)
			if ( !expand( )) {
				ASSERT( FALSE );
		    	return( FALSE );
			}

		m_pElements[ m_nEntries ] = pItem;
		m_nEntries = m_nEntries+1;
	    return( TRUE );
	}

	// �v�f�e�[�u����( �z���)�w��v�f���폜���l�߂�
	// �e�[�u���g�����̒ǉ��T�C�Y�P�ʈȏ�̋󂫂��o�����ꍇ�͗v�f�e�[�u���̃T�C�Y���k������
	//
	void Remove( unsigned int nItem )
	{ 
		compress( nItem ); 
	}

	// �v�f�e�[�u����( �z���)�w��v�f���擾����
	//
	bool Get( unsigned int nItem, elementType *theelement )
	{		
		if ( nItem < m_nEntries )
		{
			*theelement=m_pElements[nItem];
			return TRUE;
		}		
		ASSERT( FALSE );
		return FALSE;
	}


	// �v�f�e�[�u���̃|�C���^���擾����
	//
	elementType *GetArray( ) const
	{		
	    return( m_pElements );
	}

	// �v�f�e�[�u����( �z���)�w��v�f���C������( ������)
	//
	void Set( unsigned int nItem, elementType lpItem )
	{
		if ( nItem < m_nEntries )
			m_pElements[nItem] = lpItem;
	}

private:

	// �v�f�e�[�u���̃T�C�Y��ύX����
	//
	bool changeSize( unsigned int nNewSize )
	{
		ASSERT( nNewSize >= m_nEntries );
		unsigned int wMemSize = nNewSize * sizeof( elementType );

		elementType* lpNew = ( elementType*)::realloc( m_pElements, wMemSize );
		ASSERT( lpNew != NULL );
		if ( lpNew != NULL )
		{
			m_pElements = lpNew;
			m_nSize = nNewSize;
		}
	
	    return( lpNew != NULL );
	}

	// �v�f�e�[�u�����g������
	// �g���T�C�Y��( m_nEntries:�e�[�u���g�����̒ǉ��T�C�Y�P��)
	//
	bool expand( )
	{
		unsigned int wNewSize = m_nSize + m_nGran;
	
		return ( changeSize( wNewSize ) );
	}

	// �v�f�e�[�u����( �z���)�w��v�f���폜���l�߂�
	// �e�[�u���g�����̒ǉ��T�C�Y�P�ʈȏ�̋󂫂��o�����ꍇ�͗v�f�e�[�u���̃T�C�Y���k������
	//
	void compress( unsigned int nIndex )
	{
		if ( nIndex == -1)
		{
			return;
		}

		elementType* lpElement = m_pElements + nIndex;

		unsigned int wEntriesAfterIndex = ( m_nEntries - ( nIndex + 1 ) );
	    if ( wEntriesAfterIndex > 0)
	   {
			::memmove( lpElement, lpElement + 1, wEntriesAfterIndex * sizeof( elementType ) );
		}
	    m_nEntries--;

		// �e�[�u���g�����̒ǉ��T�C�Y�P�ʈȏ�̋󂫂��o�����ꍇ�͗v�f�e�[�u���̃T�C�Y���k������
		//
		if ( ( m_nEntries > 0 ) &&
			 ( m_nEntries <= ( m_nSize - m_nGran) ) )
		{
			// �e�[�u���g�����̒ǉ��T�C�Y�P�ʂ̐����{�̃T�C�Y�ł��鎖���m�F
			//
			ASSERT( ( m_nEntries % m_nGran) == 0 );
	
			changeSize( m_nEntries );
		}
	}

	// �f�[�^
private:
   	unsigned int	m_nGran;			// �e�[�u���g�����̒ǉ��T�C�Y�P��
	unsigned int	m_nSize;			// �S�e�[�u���T�C�Y
	unsigned int	m_nEntries;			// �ݒ�ςݗv�f��
	elementType *	m_pElements;		// �v�f�e�[�u��
};


#ifdef IC_DYNARRAY_H_ASSERT
	#undef ASSERT
#endif

