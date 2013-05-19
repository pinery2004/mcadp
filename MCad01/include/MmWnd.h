#pragma once
/////////////////////////////////////////////////////////////////////////////**************
//  �E�B���h�E�Ǘ�

#include "MsBasic.h"
#include "MsCod.h"
#include "MmGridNum.h"
#include "MmDrag.h"


// �}���
#define			MTSIKITI			100			// 		100:�~�n
#define			MTHEIMENZU			101			// 		101:���ʐ}
#define			MTRITUMENZU			102			// 		102:���ʐ}
#define			MTSEKKEI3DZU		103			// 		103:�R�����}
#define			MTKOUZOU3DZU		104			// 		104:�\���R�����}
#define			MTKISOFUSEZU		200			// 		200:��b���}
#define			MTDODAIFUSEZU		210			// 		210:�y�䕚�}
#define			MTYUKAFUSEZU		220			//		220:�����}
#define			MTKABEFUSEZU		230			// 		230:�Ǖ��} 
#define			MTTENJOFUSEZU		240			// 		240:�V�䕚�}
#define			MTYANEFUSEZU		250			// 		250:�������}
#define			MTYUKAPANERUZU		320			//		320:���p�l��
#define			MTKABEPANERUZU		330			//		330:�ǃp�l��
#define			MTTENJOPANERUZU		340			//		340:�V��p�l��
#define			MTYANEPANERUZU		350			//		350:�����p�l��

// �V�t�g�L�[�ƃR���g���[���L�[�̗�����������Ă��鎖���m�F
#define CONTROL_SHIFT_FLAGS(n)  ((n & (MK_SHIFT|MK_CONTROL)) == (MK_SHIFT|MK_CONTROL))

// �R���g���[���L�[��������Ă��鎖���m�F
#define CONTROL_FLAGS(n)  ((n & MK_CONTROL) == MK_CONTROL)

// �V�t�g�L�[��������Ă��鎖���m�F
#define SHIFT_FLAGS(n)  ((n & MK_SHIFT) == MK_SHIFT)

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_WNDINFO_DO
	#pragma message( "<<< WndInfo�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef _DEBUG								// Release Mode �� inline�֐���undef�ɂȂ�s��Ή�
		#ifdef DLL_NO_IMPORT_MD_DO
			#define DLL_EXPORT
		#else
//			#pragma message( "=== WndInfo�Edll_IMport ===")
			#define DLL_EXPORT						__declspec( dllimport)
		#endif
	#else
		#define DLL_EXPORT
	#endif
#endif

namespace MC
{

class MmWndInfo;

/////////////////////////////////////////////////////////////////////////////
//	�E�B���h�E�Ǘ���� 

//class	MmWndInfo: public MOBJECT, public MmGridNum, public msCod
class DLL_EXPORT MmWndInfo: public MOBJECT, public MmGridNum, public msCod
{
public :
	MINT			m_iWndSyu;					// �E�B���h�E���(1,2,3,4,5)
	MINT			m_iZuSyu;					// �}���
												// 		100:�~�n
												// 		101:���ʐ}
												// 		102:���ʐ}
												// 		103:�R�����}
												// 		104:�\���R�����}
												// 		200:��b���}
												// 		210:�y�䕚�}
												//		220:�����}
												// 		230:�Ǖ��} 
												// 		240:�V�䕚�}
												// 		250:�������}
												//		320:���p�l��
												//		330:�ǃp�l��
												//		340:�V��p�l��
												//		350:�����p�l��
	MINT			m_iKai;						// �K      (0:�s�g�p -2�`5�K)
	MINT			m_iZuNum;					// �}�ԍ��@(0:�s�g�p�b�}�했�ǔԁb�p�l���ԍ��j
	MINT			m_iHoko;					// �����@�@0:�s�g�p�@1:�k 2:�� 3:�� 4:��
	CWnd*			m_pWnd;						// �E�B���h�E�̃C���X�^���X
	CMDIChildWnd*	m_pChildFrm;				// �t���[���̃C���X�^���X
	
	MINT			m_iCursor;					// �J�����g�J�[�\���ԍ�
	
	MmDrag*			m_pDrag;					// �h���b�M���O������

	CBitmap*		m_pMemBmp;					// �E�B���h�E�C���[�W�r�b�g�}�b�v
	CBitmap*		m_pOldMemBmp;				// �ۑ��p�E�B���h�E�C���[�W�r�b�g�}�b�v
	CDC*			m_pMemDC;					// �E�B���h�E�C���[�W�������c�b

	// �R���X�g���N�^
	MmWndInfo()		{};

	MmWndInfo(
						MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
						MINT		iZuSYu,			// (I  ) �}���
						MINT		iKai,			// (I  ) �K
						MINT		iZuNum			// (I  ) �}�ԍ�
				);

	// �f�X�g���N�^
	~MmWndInfo();

	// �����ǂݏ���
	void	SetWndSyu( MINT iWndSyu)
						{ 
							m_iWndSyu = iWndSyu;}
	MINT	GetWndSyu()
						{ return m_iWndSyu;}
	void	SetZuSyu( MINT iZuSyu)
						{ m_iZuSyu = iZuSyu;}
	MINT	GetZuSyu()
						{ return m_iZuSyu;}
	void	SetInpKai( MINT iKai)
						{ m_iKai = iKai;}
	MINT	GetInpKai()
						{ return m_iKai;}
	void	SetZuNum( MINT iZuNum)
						{ m_iZuNum = iZuNum;}
	MINT	GetZuNum()
						{ return m_iZuNum;}
	void	SetWnd( CWnd* pWnd) {
						m_pWnd = pWnd;}
	CWnd*	GetWnd()
						{ return m_pWnd;}
	void	SetFrame( CMDIChildWnd* pChildFrm)
						{
							m_pChildFrm = pChildFrm;}
	CMDIChildWnd* GetFrame()
						{
							return m_pChildFrm;}
	MINT	SetCursor( MINT iCursor)
						{ MINT iPrevCursor = m_iCursor;
						  m_iCursor = iCursor;
						  return iPrevCursor;}
	MINT	GetCursor()
						{ return m_iCursor;}
	void	SetDrag( MmDrag* pDrag)
						{ m_pDrag = pDrag;}
	MmDrag*	GetDrag()
						{ return m_pDrag;}
	void	DeleteDrag();

//	void	SetMemBmp( CBitmap*	pMemBmp)
//						{ m_pMemBmp = pMemBmp;}
//	CBitmap* GetMemBmp()
//						{ return m_pMemBmp;}
//	void	SetOldMemBmp( CBitmap*	pOldMemBmp)
//						{ m_pOldMemBmp = pOldMemBmp;}
//	CBitmap* GetOldMemBmp()
//						{ return m_pOldMemBmp;}

	void	SetMemDC( CDC*	pMemDC)
						{ m_pMemDC = pMemDC;}
	CDC*	GetMemDC()
						{ return m_pMemDC;}

	void	CreateMDC();
	void	DeleteMDC();
	void	AsignMDC();
	void	FreeMDC();
	void 	ClearMDC();
};

#ifdef DLL_EXPORT
	#undef DLL_EXPORT
#endif

#ifdef DLL_EXPORT_MC_WINDOWCTRL_DO
	#pragma message( "<<< MC::WindowCtrl�Edll_EXport >>>")
	#define DLL_EXPORT							__declspec( dllexport)
#else
	#ifdef DLL_NO_IMPORT_MD_DO
		#define DLL_EXPORT
	#else
//		#pragma message( "=== MC::WindowCtrl�Edll_IMport ===")
		#define DLL_EXPORT						__declspec( dllimport)
	#endif
#endif

class DLL_EXPORT WindowCtrl
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E�Ǘ�

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ύX����
	static void MmGridNumInp(
					CWnd*		pWnd					// (I  ) �E�B���h�E�̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ݒ�	�i�V���O���O���b�h�p�j
	static void MmGridNumSet(
					MINT*		nGrid					// (I  ) �O���b�h���i�k�A���A��A���j
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ǂݍ���	�i�V���O���O���b�h�p�j
	static void MmGridNumGet(
					MINT*		nGrid					// (  O) �O���b�h���i�k�A���A��A���j
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ύX�\�����s
	static void MmGridNumXqt();

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ύX�L�����Z��
	static void MmGridNumCancel();

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ύX�I��
	static void MmGridNumEnd();

public:
	/////////////////////////////////////////////////////////////////////////////
	//	�擪�̃E�B���h�E���擾
	//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�|�C���^
	static MmWndInfo* MmGetHeadWnd(
							MPOSITION	*pWndPos = NULL
					);

	/////////////////////////////////////////////////////////////////////////////
	//	���̃E�B���h�E���擾
	//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�|�C���^
	static MmWndInfo* MmGetNextWnd(
							MPOSITION	*pWndPos = NULL
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�̃E�B���h�E��ʂ�ݒ�

	static void	MmWndSetSyubetsuC(
							MINT		iWndSyu,		// (I  ) �E�B���h�E���
							MINT		iZuSyu,			// (I  ) �}���
							MINT		iKai,			// (I  ) �K
							MINT		iZuNum			// (I  ) �}�ԍ�
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�E�B���h�E�̃t���[���̃C���X�^���X��ݒ�

	static void	MmWndSetFrameC(
							MINT		iWndSyu,		// (I  ) �E�B���h�E���
							CMDIChildWnd* pChildFrm		// (I  ) �t���[���̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�E�B���h�E�̃E�B���h�E�̃C���X�^���X��ݒ�

	static void	MmWndSetWndC(
							MINT		iWndSyu,		// (I  ) �E�B���h�E���
							CWnd*		m_pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�R�}���h���j���[����
	static void MmWndKCmdXqt(
							MINT		i_idCmd			// �R�}���hID
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �J�����g�E�B���h�E��ǉ�����

	static MINT MmWndKAddC();									// (  O) �X�e�C�^�X 0:����  1:�G���[

	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E��ǉ�����

	static MINT MmWndKAdd(										// (  O) �X�e�C�^�X 0:����  1:�G���[
							MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
							MINT		iZuSYu,			// (I  ) �}���
							MINT		iKai,			// (I  ) �K
							MINT		iZuNum			// (I  ) �}�ԍ�
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E����������

	static MmWndInfo* MmWndKFindSyu(							// (  O) �E�B���h�E�Ǘ�sg���̃|�C���^
							MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
							MINT		iZuSYu,			// (I  ) �}���
							MINT		iKai,			// (I  ) �K
							MINT		iZuNum			// (I  ) �}�ԍ�
					);

	static MmWndInfo* MmWndKFindWnd(							// (  O) �E�B���h�E�Ǘ����̃|�C���^
							CWnd*		m_pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
					);

	static MmWndInfo* MmWndKFindFrm(							// (  O) �E�B���h�E���ւ��߲��
							CMDIChildWnd* pChildFrm		// (I  ) �t���[���̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�E�B���h�E���폜����
	/*
	static MINT MmWndKDelete(									// (  O) �X�e�C�^�X 0:����  1:�G���[
					MINT		iWndSyu,				// (I  ) �E�B���h�E���(1,2,3,4,5)
					MINT		iZuSYu,					// (I  ) �}���
					MINT		iKai,					// (I  ) �K
					MINT		iZuNum					// (I  ) �}�ԍ�
					);

	static MINT MmWndKDelete(									// (  O) �X�e�C�^�X 0:����  1:�G���[
					CWnd*		pWnd					// (I  ) �E�B���h�E�̃C���X�^���X
					);
	*/
	static MINT MmWndKDelete(									// (  O) �X�e�C�^�X 0:����  1:�G���[
							MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�E�B���h�E���J������

	static MINT MmWndKFree(									// (  O) �X�e�C�^�X 0:����  1:�G���[
							MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
							MINT		iZuSYu,			// (I  ) �}���
							MINT		iKai,			// (I  ) �K
							MINT		iZuNum			// (I  ) �}�ԍ�
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�S�E�B���h�E���폜����

	static MINT MmWndKDeleteAll();								// (  O) �X�e�C�^�X 0:����  1:�G���[

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�̃E�B���h�E���擾����

	static MmWndInfo* MmWndKGetCurWnd();					// (  O) �X�e�C�^�X  NULL : �G���[ 

	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E���ĕ\������i�������[�c�b�ɏ������݉�ʂɕ\������j

	static MINT MmWndKReDraw();

	/////////////////////////////////////////////////////////////////////////////
	//  �S�E�B���h�E���ĕ\������i�������[�c�b�ɏ������݉�ʂɕ\������j

	static MINT MmWndKReDrawAll();

	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E��\������

	static MINT MmWndKDraw(									// (  O) �X�e�C�^�X 0:����  1:�G���[
							MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
					);

	//=====================================================================================
	//�ȉ������F�v���O����


	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E�C���[�W�������c�b�ɃE�B���h�E��\��

	static void MmWndKDrawMDC(									// (  O) �X�e�C�^�X 0:����  1:�G���[
							MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h��\������

	static void MmWndKDrawGrid(
							MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����
							msCod*		pCod
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�ǐc����\������

	static void MmWndKDrawKabe(
							msCod*		pCod,			// ���W�n
							MINT		iKaiC,			// �K  	(1,2,3)
							MINT		iGpC			// �\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	��b�c����\������

	static void MmWndKDrawKiso(
							msCod*		pCod,			// ���W�n
							MINT		iKaiC,			// �K  	(1,2,3)
							MINT		iGpC			// �\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�z�u���i��\������

	static void MmWndKDrawParts(
							msCod*		pCod,			// ���W�n
							MINT		iKaiC,			// �K  	(1,2,3)
							MINT		iGpC			// �\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	������\������

	static void MmWndKDrawRoof(
							msCod*		pCod,			// ���W�n
							MINT		iKaiC,			// �K  	(1,2,3)
							MINT		iGpC			// �\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�e���|�����\��

	static void MmWndKDrawTemp(
							MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����
							msCod*		pCod
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E�C���[�W�������c�b�ɕ��ʐ}��\��

	static MINT MmWndKDrawHeimenzu(
							MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
					);

	/////////////////////////////////////////////////////////////////////////////
	//  ���W�n�̐ݒ�

	static MINT MmWndKSetCod(
							msCod*		pCod			// (�@O) �\�����W�n
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �c�b�ɍ\���}��`��

	static void MmDrawStructure(								// (  O) �X�e�C�^�X�@0:����  1:�G���[
						MmWndInfo*	pWndInfo,			// (I  ) �E�B���h�E�Ǘ����
						msCod*		pCod
					);
};

} // namespace MC
