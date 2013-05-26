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

class DLL_EXPORT GridDispCtrl
{
	/////////////////////////////////////////////////////////////////////////////
	//  �O���b�h�\������

public:
	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ύX����
	static void GridNumInp(
					CWnd*		pWnd					// (I  ) �E�B���h�E�̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ݒ�	�i�V���O���O���b�h�p�j
	static void SetGridNum(
					MINT*		nGrid					// (I  ) �O���b�h���i�k�A���A��A���j
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ǂݍ���	�i�V���O���O���b�h�p�j
	static void GetGridNum(
					MINT*		nGrid					// (  O) �O���b�h���i�k�A���A��A���j
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ύX�\�����s
	static void XqtGridNum();

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ύX�L�����Z��
	static void CancelGridNum();

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h���ύX�I��
	static void EndGridNum();
};

class DLL_EXPORT WindowCtrl
{
	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E�Ǘ�

public:
	/////////////////////////////////////////////////////////////////////////////
	//	�擪�̃E�B���h�E���擾
	//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�|�C���^
	static MmWndInfo* GetHeadWnd(
							MPOSITION	*pWndPos = NULL
					);

	/////////////////////////////////////////////////////////////////////////////
	//	���̃E�B���h�E���擾
	//	�Ԓl =NULL: ���R�[�h�Ȃ� !=NULL: �ǂݍ���[���i�z�u]�|�C���^
	static MmWndInfo* GetNextWnd(
							MPOSITION	*pWndPos = NULL
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�̃E�B���h�E��ʂ�ݒ�

	static void	SetCurWndSyubetsu(
							MINT		iWndSyu,		// (I  ) �E�B���h�E���
							MINT		iZuSyu,			// (I  ) �}���
							MINT		iKai,			// (I  ) �K
							MINT		iZuNum			// (I  ) �}�ԍ�
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�E�B���h�E�̃t���[���̃C���X�^���X��ݒ�

	static void	SetCurWndFrame(
							MINT		iWndSyu,		// (I  ) �E�B���h�E���
							CMDIChildWnd* pChildFrm		// (I  ) �t���[���̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�E�B���h�E�̃E�B���h�E�̃C���X�^���X��ݒ�

	static void	SetCurWnd(
							MINT		iWndSyu,		// (I  ) �E�B���h�E���
							CWnd*		m_pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�R�}���h���j���[����
	static void XqtMenuCmd(
							MINT		i_idCmd			// �R�}���hID
					);

	/////////////////////////////////////////////////////////////////////////////
	//  �J�����g�E�B���h�E��ǉ�����

	static MINT AddCurWnd();							// (  O) �X�e�C�^�X 0:����  1:�G���[

	///////////////////////////////////////////////////////////////////////////////
	////  �E�B���h�E��ǉ�����

	//static MINT AddWnd(									// (  O) �X�e�C�^�X 0:����  1:�G���[
	//						MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
	//						MINT		iZuSYu,			// (I  ) �}���
	//						MINT		iKai,			// (I  ) �K
	//						MINT		iZuNum			// (I  ) �}�ԍ�
	//				);

	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E����������

	static MmWndInfo* GetWndInfoBySyu(					// (  O) �E�B���h�E�Ǘ�sg���̃|�C���^
							MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
							MINT		iZuSYu,			// (I  ) �}���
							MINT		iKai,			// (I  ) �K
							MINT		iZuNum			// (I  ) �}�ԍ�
					);

	static MmWndInfo* GetWndInfoObWnd(					// (  O) �E�B���h�E�Ǘ����̃|�C���^
							CWnd*		i_pWnd			// (I  ) �E�B���h�E�̃C���X�^���X
					);

	static MmWndInfo* GetWndInfoOfFrm(					// (  O) �E�B���h�E���ւ��߲��
							CMDIChildWnd* pChildFrm		// (I  ) �t���[���̃C���X�^���X
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�E�B���h�E���폜����

	//
	//static MINT DeleteWnd(							// (  O) �X�e�C�^�X 0:����  1:�G���[
	//				MINT		iWndSyu,				// (I  ) �E�B���h�E���(1,2,3,4,5)
	//				MINT		iZuSYu,					// (I  ) �}���
	//				MINT		iKai,					// (I  ) �K
	//				MINT		iZuNum					// (I  ) �}�ԍ�
	//				);
	//
	//static MINT DeleteWnd(							// (  O) �X�e�C�^�X 0:����  1:�G���[
	//				CWnd*		pWnd					// (I  ) �E�B���h�E�̃C���X�^���X
	//				);

	static MINT DeleteWnd(								// (  O) �X�e�C�^�X 0:����  1:�G���[
							MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
					);

	///////////////////////////////////////////////////////////////////////////////
	////	�E�B���h�E���J������

	//static MINT WndFree(								// (  O) �X�e�C�^�X 0:����  1:�G���[
	//						MINT		iWndSyu,		// (I  ) �E�B���h�E���(1,2,3,4,5)
	//						MINT		iZuSYu,			// (I  ) �}���
	//						MINT		iKai,			// (I  ) �K
	//						MINT		iZuNum			// (I  ) �}�ԍ�
	//				);

	/////////////////////////////////////////////////////////////////////////////
	//	�S�E�B���h�E���폜����

	static MINT DeleteAllWnd();							// (  O) �X�e�C�^�X 0:����  1:�G���[

	/////////////////////////////////////////////////////////////////////////////
	//	�J�����g�̃E�B���h�E���擾����

	static MmWndInfo* GetCurWndInfo();					// (  O) �X�e�C�^�X  NULL : �G���[ 

	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E���ĕ\������i�������[�c�b�ɏ������݉�ʂɕ\������j

	static MINT ReDrawWnd();

	/////////////////////////////////////////////////////////////////////////////
	//  �S�E�B���h�E���ĕ\������i�������[�c�b�ɏ������݉�ʂɕ\������j

	static MINT ReDrawAllWnd();

	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E��\������

	static MINT DrawWnd(								// (  O) �X�e�C�^�X 0:����  1:�G���[
							MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
					);

	//=====================================================================================
	//�ȉ������F�v���O����


	/////////////////////////////////////////////////////////////////////////////
	//  �E�B���h�E�C���[�W�������c�b�ɃE�B���h�E��\��

	static void DrawWndMDC(								// (  O) �X�e�C�^�X 0:����  1:�G���[
							MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�O���b�h��\������

	static void DrawGridLine(
							MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����
							msCod*		pCod
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�ǐc����\������

	static void DrawKabeSin(
							msCod*		pCod,			// ���W�n
							MINT		iKaiC,			// �K  	(1,2,3)
							MINT		iGpC			// �\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	��b�c����\������

	static void DrawKisoSin(
							msCod*		pCod,			// ���W�n
							MINT		iKaiC,			// �K  	(1,2,3)
							MINT		iGpC			// �\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�z�u���i��\������

	static void DrawHaitiParts(
							msCod*		pCod,			// ���W�n
							MINT		iKaiC,			// �K  	(1,2,3)
							MINT		iGpC			// �\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	������\������

	static void DrawRoof(
							msCod*		pCod,			// ���W�n
							MINT		iKaiC,			// �K  	(1,2,3)
							MINT		iGpC			// �\��
					);

	/////////////////////////////////////////////////////////////////////////////
	//	�e���|�����\��

	static void DrawWndTemp(
							MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����
							msCod*		pCod
					);

	///////////////////////////////////////////////////////////////////////////////
	////  �E�B���h�E�C���[�W�������c�b�ɕ��ʐ}��\��

	//static MINT DrawWndHeimenzu(
	//						MmWndInfo*	pWndInfo		// (I  ) �E�B���h�E�Ǘ����
	//				);

	///////////////////////////////////////////////////////////////////////////////
	////  ���W�n�̐ݒ�

	//static MINT SetWndCod(
	//						msCod*		pCod			// (�@O) �\�����W�n
	//				);

	/////////////////////////////////////////////////////////////////////////////
	//  �c�b�ɍ\���}��`��

	static void DrawStructure(							// (  O) �X�e�C�^�X�@0:����  1:�G���[
							MmWndInfo*	pWndInfo,		// (I  ) �E�B���h�E�Ǘ����
							msCod*		pCod
					);
};

} // namespace MC
