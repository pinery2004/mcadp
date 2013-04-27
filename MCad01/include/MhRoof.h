///////////////////////////////////////////////////////////////////////////////
//	  ����
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include	"MgGrp.h"
#include	"MhZukei.h"
#include	"MhPlcPartsLib.h"

#define HDBID MINT

#define		MC_PRI_MIN_AREA		0					// �ʐς�����D��ɉ����ʂ�����
#define		MC_PRI_MIN_HIGHT	1					// ����������D��ɉ����ʂ�����
#define		MC_PRI_MAX_HIGHT	2					// ���������D��ɉ����ʂ�����

namespace MC
{

class MmWndInfo;

//	�����\�����^�C�v�R�[�h
typedef enum _roof_sen_type {
	MHRL_DUMMY,										// �_�~�[
	MHRL_NOKI,										// ��
	MHRL_KERABA,									// �����
	MHRL_MUNE,										// ��
	MHRL_RYOU,										// ��
	MHRL_TANI,										// �J
	NHRL_MIZUKIRI,									// ���؂�
	MHRL_KATANAGARENOKI,							// �З��ꌬ
	MHRL_YANEUEMIZUKIRI,							// �e�����̏�ɏ��q�����̍\����
	MHRL_YAGIRI										// ���
} ROOF_SEN_TYPE;

//	�����^�C�v�R�[�h
typedef enum _roof_type {
	MHRF_YOSEMUNE,									// ��
	MHRF_KIRITUMA,									// �؍�
	MHRF_HANKIRITUMA,								// ���؍�
	MHRF_IRIMOYA,									// ���ꉮ
	MHRF_KATANAGARE,								// �З���
	MHRF_MANSADO,									// �}���T�[�h
	MHRF_YOSEMUNEOSAMARI,							// �񓏔[�܂�
	MHRF_FUKIOROSI,									// ���~�낵
	MHRF_CUT,										// �J�b�g
	MHRF_DOMA,										// �h�[�}
	MHRF_KAIKOU,									// �J��
	MHRF_FLAT,										// �t���b�g
	MHRF_MANUALMEN									// �}�j���A����
} ROOF_TYPE;

typedef enum _mgrdtp{
	MGRDTP_GROUP = 100,
	MGRDTP_GJIM1,									// �n�����i���́j
	MGRDTP_GJIM2,									// �n�����i������j
	MGRDTP_GKS1,									// �\�����i���́j
	MGRDTP_GKS2,									// �\�����i������j
	MGRDTP_GTN,										// �J��
	MGRDTP_GTRFM									// ������
} MGRDTp;

class MhRoofInfo;

class	MhRfm;
//
//======================( �Q���� )==============================
//		MhJim �n�����i���́j
//

class MhJim
{
public:
	MgPoint2	m_p;								// �n�����E�[�̒��_
	MINT		m_icd;								// �n�����R�[�h
	MINT		m_ifInp;							// ���̓t���O
	MREAL		m_rKb;								// ���z
	MINT		m_iRfm;								// �����ʔz��ԍ�
	MgLine3		m_LnR;								// �E�������\�����i�����j
	MINT		m_icdLnR;							// �E�������\�����R�[�h
public:
	void Free()			{}

	MINT Save(								// �c�a�ւP���R�[�h��������
				MhMdlIO*		i_phMdl		// �������݃t�@�C���@�n���h��
				);
	MINT Load(								// �c�a���P���R�[�h�ǂݍ���
				MhMdlIO*		i_phMdl		// �ǂݍ��݃t�@�C���@�n���h��
				);

	void Print( MCHAR* s, MINT ic = -1);
};
//
//======================( �R���� )==============================
//		MgKs1 �\�����i���́j
//

class MgKs1
{
public:
	MgLine3		m_Ln;							// �\������
	MINT		m_itpLn;						// �����^�C�v(0: �������@1:����)
	MINT		m_iCd;							// �\���R�[�h
	MINT		m_ifProc;						// �v�Z�����p�t���O
	MINT		m_iRfm[2];						// �����ʔz��ԍ� (���A�E)
public:
	void Free()			{}

	MINT Save(									// �c�a�ւP���R�[�h��������
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				);
	MINT Load(									// �c�a���P���R�[�h�ǂݍ���
				MhMdlIO*		i_phMdl			// �ǂݍ��݃t�@�C���@�n���h��
				);

	void Print( MCHAR* s, MINT ic = -1);
};
//
//======================( �R���� )==============================
//		MhRfm ������
//

class MhRfm
{
public:
	MgPlane3	m_Pln;							// �����ʌW��
	MgPolyg3	m_Pg;							// �����ʌ`��i�����\�����j
	MgGInt		m_cdPg;							// �����\�����R�[�h
	MINT		m_icd;							// �\���R�[�h
public:
	void Init()	
						{ m_Pg.Init(); m_cdPg.Init();}
	void Free()													// �̈�J��
						{ m_Pg.Free(); m_cdPg.Free();}

	MINT Save(									// �c�a�ւP���R�[�h��������
				MhMdlIO*		i_phMdl			// �������݃t�@�C���@�n���h��
				);
	MINT Load(									// �c�a���P���R�[�h�ǂݍ���
				MhMdlIO*		i_phMdl			// �ǂݍ��݃t�@�C���@�n���h��
				);

	void Print( MCHAR* s, MINT ic = -1);
};

//
////////////////////////////////////////////////////////////////
//		����

class MhRoofInfo: public MOBJECT
{

	friend	class	mhHaitiIn;							//ZZZZZ 091115
	friend	class	MdRoofQueue;
	friend	MINT	MdRoofModify( MhRoofInfo *pRfInfoR, MhRoofInfo* *ppRfInfoM);
	friend	void	MdRoofDelete( MPOSITION pPosition);
	friend	MINT	RoofPlc( const MgPolyg2 &pgJim, const MgGInt &gint, const MgPoint2 &pth);
	friend	void	MmWndKDrawRoof( MmWndInfo* pWndInfo);

//public:
	MINT				m_iKai;						// �K( 1, 2, 3)
	MgGrpS<MhJim>		m_GJim1;					// �n�����i���́j
													// �i�i���_�E�n�����R�[�h�E���̓t���O)n�j
	MgPoint2			m_ptH;						// �����������_�i���́j
	MgGrpS<MgKs1>		m_GKs1;						// �\�����i���́j
													// �i�i�\�������E�\���R�[�h�E�\�������)n�j
	MgGrpF<MhRfm>		m_GRfm;						// ������
													// �i�i(���_�E�\���R�[�h)n)n�j
	MgGPolyg3			m_GNUm;						// ������
													// �i�i(���_)n)n�j
	MgGPolyg3			m_GHm;						// �ւ��
													// �i�i(���_)n)n�j
	
//	MhRoofInfo*			m_Oya;						// �e����
	MINT				m_itpRf;					// �����^�C�v
	MREAL				m_rKb;						// ���z
	MREAL				m_rRkH;						// ����������ύX��
	MREAL				m_rRfmA;					// �����ʌ���(89,140,182)
	MREAL				m_rNUmA;					// �����ʌ���(89,140)
	MREAL				m_rMnZ[2];					// ������ʂP�E�Q
	MREAL				m_rNkD[2];					// ���̏o
	MREAL				m_rKrD[2];					// ����΂̏o
	MINT				m_itpNU;					// �����^�C�v�P�E�Q
	MINT				m_itpNS;					// ����^�C�v�P�E�Q
	MREAL				m_rHKmA;					// �@�B���ʌ���
	MREAL				m_rNUk;						// �����Ԃ���
	MREAL				m_rNkH;						// ���̍����i��`�h�[�}�p�j
	MINT				m_icdURS;					// �������R�[�h
//	MINT				m_icdRR;					// �剮���R�[�h
	MhZukei*			m_pZukei;					// �}�`

	MINT				m_imdDsp;					// �\�����[�h (0: ������  1:�\����)
	COLORREF			m_colDispD;					// �\���F�i�f�[�^�w��j
	COLORREF			m_colDispC;					// �\���F�i���݁j
//	MnDisp*				m_iDispM;					// �\�����i�ʁj
//	MnDisp*				m_iDispL;					// �\�����i�����j

	MINT				m_nRtm;						// ���ʐ�
	MINT*				m_pifRitm;					// ���ʕ\��(�ʃt���O)  0:��  1:��
	MINT*				m_pnPtRitm;					// ���ʕ\��(���_��)
	MgPoint3*			m_pPtRitm;					// ���ʕ\��(���_)
//	MnDisp*				m_pLnRitm;					// ���ʕ\�����i�����j

//	MhTexture*			m_KsInfo[NKSINFO];			// �\�����

	MsBitSet*			m_pVer;					// �o�[�W�������� (0: �S�o�[�W�����ŕ\��)
	MsBitSet*			m_pOpt1;					// �\���I��OPT�Q�Z�b�g (NULL: �I�v�V�����ݒ薳���ł��\��)
	MsBitSet*			m_pOpt2;					// �\���I�tOPT�Q�Z�b�g (NULL: ����)

public:
	MhRoofInfo();
	~MhRoofInfo();

	MINT Save(								// �c�a�ւP���R�[�h��������
				MhMdlIO*		i_phMdl		// �������݃t�@�C���@�n���h��
				);
	MINT Load(								// �c�a���P���R�[�h�ǂݍ���
				MhMdlIO*		i_phMdl		// �ǂݍ��݃t�@�C���@�n���h��
				);

	
	MgGrpS<MhJim>*	GetpGJim1()
								{
									return	&m_GJim1;
								}
	MgGrpS<MgKs1>*	GetpGKs1()
								{
									return	&m_GKs1;
								}
	MgGrpF<MhRfm>*	GetpGRfm()
								{
									return	&m_GRfm;
								}
	MhZukei*		GetpZukei()
								{
									return	m_pZukei;
								}
	
	void SetInpKai( int i_iKai)
								{
									m_iKai = i_iKai;
								}
	MINT	GetInpKai()
								{
									return m_iKai;
								}
	

	void	FreeAllAtr();										// �����p�Ɋm�ۂ����̈���J������
	void	InitAllAtr( MINT ifPtr = 1);						// �������C�j�V�����C�Y�A�̈�ւ̃|�C���^���N���A
	void	SetPIVer( MsBitSet* pVer)
								{
									m_pVer = pVer;
								}								// �o�[�W��������
	void	SetPIOpt1( MsBitSet* pOptv)
								{
									m_pOpt1 = pOptv;
								}								// �\���I��OPT�Q�Z�b�g
	void	FreePIOpt1()
								{
									MBFREE( m_pOpt1);
								}								// �\���I��OPT�Q�Z�b�g�𖳂��ɐݒ�
	void	SetPIOpt2( MsBitSet* pOptv)
								{
									m_pOpt2 = pOptv;
								}								// �\���I�tOPT�Q�Z�b�g
	void	FreePIOpt2()
								{
									MBFREE( m_pOpt1);
								}								// �n�o�s�Q�\���n�e�e�𖳂��ɐݒ�

	MsBitSet*	GetPIVer()
								{
									return m_pVer;
								}								// �o�[�W��������
	MsBitSet*	GetPIOpt1()
								{
									return m_pOpt1;
								}								// �\���I��OPT�Q�Z�b�g
	MsBitSet*	GetPIOpt2()
								{
									return m_pOpt2;
								}								// �\���I�tOPT�Q�Z�b�g

//	{ if ( m_pZukei) { MBFREE( m_pZukei->m_pNext); free( m_pZukei);}}

	// �n�����ɃR�[�h��ݒ肷��
	void SetJimCd(
				const	MgPolyg2	&pgJim,			// (I  ) �n�����
				const	MgGInt		&GifInp,		// (I  ) �n�������(���z�L�[(nflag)  MK_SHIFT(004): �V�t�g�L�[)
				const	MgPoint2	&pth			// (I  ) �����_
				);

	// �������͒l����荞�ݐݒ肷�� 
	void SetAttr();

	// �n�����ɑΉ����鉮���ʂ��쐬���� 
	void CreateRfmForJim();

	// �n�����ɐڑ�����\�������쐬���� 
	void CreateKsCwJim();

	// ���̉����ʂƂ̌����𒲂׌��������ŉ����ʌ`����J�b�g����
	MINT AdjustRfm1();								// (  O) �X�e�C�^�X�@0: ����@-1: �����ʌ`��쐬�G���[

	// ��K�O�ǂƂ̌����𒲂׌��������ŉ����ʌ`����J�b�g����
	MINT AdjustRfm2();								// (  O) �X�e�C�^�X�@0: ����@-1: �����ʌ`��쐬�G���[

	// �d�Ȃ鉮���ʂ�1�ɂ܂Ƃ߂�
	void ConnectRfm();

	// �����ʂ̌����A����ΐ����I�t�Z�b�g����
	void OffsetRfm();

	// �����ʂ̐}�`���쐬����
	void CreateRfmZukei();

	// �g���[�X
	void Print( MCHAR* s);
};

////////////////////////////////////////////////////////////////////////////
//    �R���X�g���N�^
inline	MhRoofInfo::MhRoofInfo()
{
	InitAllAtr();
}

////////////////////////////////////////////////////////////////////////////
//	�f�X�g���N�^
inline	MhRoofInfo::~MhRoofInfo()
{
	FreeAllAtr();
}

} // namespace MC
