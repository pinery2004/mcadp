#pragma once
/////////////////////////////////////////////////////////////////////////////
//  �E�B���h�E�Ǘ�

#define			MGRID_GRP_MAX		10

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_GRIDNUM_DO
	#pragma message( "<<< GridNum�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== GridNum�Edll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

//class	DLL_EXPORT	MmWndInfo;
class	MmWndInfo;
/////////////////////////////////////////////////////////////////////////////
//	MmGridNum.h 

class DLL_EXPORT MmGridNum
{
public :

	bool			m_bFlgDrawG;				// �O���b�h�\���t���O
	MgPoint2		m_PtOriginG;				// �O���b�h���_���W
	MINT			m_iMinG[2];					// �c(0)��(1)�̃O���b�h�ŏ��ʒu
	MINT			m_nGrpG[2];				// �c(0)��(1)�̃O���b�h�O���[�v��
	MINT			m_nGrid[2][MGRID_GRP_MAX];	// �c(0)��(1)�̃O���b�h��
	MREAL			m_PichG[2][MGRID_GRP_MAX];	// �c(0)��(1)�̃O���b�h�Ԋu�i�s�b�`�j
	MgMinMaxR2		m_rMinMaxG;					// �O���b�h�̈�̍ŏ��ő�
	
	// �R���X�g���N�^
	MmGridNum();
	
	// �f�X�g���N�^
	~MmGridNum()	{};

	// �����ǂݏ���
	void	SetDrawDispFlgG( bool bFlgDrawG)					// �O���b�h�\���t���O�̐ݒ�
						{ m_bFlgDrawG = bFlgDrawG;}
	bool	GetDrawFlgG()										// �O���b�h�\���t���O���擾
						{ return m_bFlgDrawG;}
	void	SetOriginPtG( MgPoint2 PtOriginG)					// �O���b�h���_���W�̐ݒ�
						{ m_PtOriginG = PtOriginG;}
	MgPoint2 GetOriginPtG()										// �O���b�h���_���W���擾
						{ return m_PtOriginG;}
	void	SetMinG( MINT*	iMinG)								// �c���̃O���b�h�ŏ��ʒu�̐ݒ�
						{ m_iMinG[0] = iMinG[0];
						  m_iMinG[0] = iMinG[0];}
	void	GetMinG( MINT*	iMinG)								// �c���̃O���b�h�ŏ��ʒu���擾
						{ iMinG[0] = m_iMinG[0];
						  iMinG[0] = m_iMinG[0];}
						
	void 	SetGridNum( MINT* nGrid);							// �O���b�h���i�k�A���A��A���j

	void 	GetGridNum( MINT* nGrid);							// �O���b�h���i�k�A���A��A���j

	void	SetNumG( MINT nGrid[2][MGRID_GRP_MAX]);				// �c���̃O���b�h���̐ݒ�

	void	GetNumG( MINT nGrid[2][MGRID_GRP_MAX]);				// �c���̃O���b�h�����擾

	void	SetPichG( MREAL PichG[2][MGRID_GRP_MAX]);			// �c���̃O���b�h�Ԋu�̐ݒ�

	void	GetPichG( MREAL PichG[2][MGRID_GRP_MAX]);			// �c���̃O���b�h�Ԋu���擾
	
	void	SetMinMaxG( MgMinMaxR2& rMinMaxG)					// �O���b�h�̈�̍ŏ��ő�̐ݒ�
						{ m_rMinMaxG = rMinMaxG;} 
	MgMinMaxR2 GetMinMaxG()										// �O���b�h�̈�̍ŏ��ő���擾
						{ return m_rMinMaxG;}
	MgMinMaxR2 GetMinMaxGA(
						msCod*		pCod
				);

	void	DrawGrid(											// �O���b�h��\������
						 MmWndInfo*	pWndInfo,
						 msCod*		pCod
				);

	////void	Marume(												// ���W�l���ۂ߂�
	////			const	MgPoint2	&Pi,						// ���͍��W
	////					MgPoint2	*pPo						// �ۂߌ�̍��W
	////			);

	void	GetMarumeGridLine(									// �Ŋ�̃O���b�h�ۂߐ����擾����
						MINT		iCdMarume,					// �O���b�h�ۂߕ����l
				const	MgPoint2	&Pi,      					// ���͍��W
						MgLine2		*pLn						// �c���̍Ŋ�̃O���b�h�ۂߐ���[2�{]
				);

//	friend	bool operator == ( const MmWndInfo &W1, const MmWndInfo &W2);	// b = (W1 == W2) ����
};

} // namespace MC
