//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: .cpp
//
//		
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"

#define	DLL_EXPORT_COD_DO

#include "MgTol.h"

#include "MsDefine.h"
#include "MgMatD.h"

#include "MgLib.h"
#include "MsCod.h"

#define		MCFIXEDSZ		10

namespace MC
{

/////////////////////////////////////////////////////////////////////////////
//  �X�^�e�B�b�N�����l�̏����ݒ�
MINT		msCod::z_iLineStyle		= MPS_SOLID;					// �y���X�^�C��
MREAL		msCod::z_fLineWidth		= 4.;							// �y����				(�P�ʁ@MT_FIXEDSIZE:�|�C���g, MT_FREESIZE:mm)
DWORD		msCod::z_rgbLine		= RGB( 200, 128, 100);			// �F(RGB)
bool		msCod::z_bFixedLineWidth = TRUE;						// �����Œ�T�C�Y�t���O

MCHAR		msCod::z_sTextFont[]	= _T("�l�r �o�S�V�b�N");		// �t�H���g
MREAL		msCod::z_fTextHeight	= 10.;							// ��������				(�P�ʁ@MT_FIXEDSIZE:�|�C���g, MT_FREESIZE:mm)
MINT		msCod::z_iTextPosUL		= 3;							// ������㉺������ʒu(TA_TOP(1:��,2:��),TA_BOTTOM(3:��),TA_BASELINE(4:�x�[�X))
MINT		msCod::z_iTextPosLR		= 1;							// �����񍶉E������ʒu(TA_LEFT(1:��),TA_CENTER(2:��),TA_RIGHT(3:�E))
DWORD		msCod::z_rgbText		= RGB( 200, 128, 100);			// �F(RGB)
MgVect2D		msCod::z_vTextDirect	= MgVect2D( 1.f, 0.);			// ������\������
MgVect2D		msCod::z_pTextOffset	= MgVect2D( 0., 0.);				// �����ʒu�I�t�Z�b�g	(�P�ʁ@MT_FIXEDSIZE:�|�C���g, MT_FREESIZE:mm)
bool		msCod::z_bFixedTextSize	= TRUE;							// ������Œ�T�C�Y�t���O

/////////////////////////////////////////////////////////////////////////////
//  �y���^�C�v�̕ϊ��e�[�u��
static MINT PSTbl[] = {
	PS_SOLID,				// MPS_SOLID		0:�����̃y�����쐬���܂��B 
	PS_DASH,				// MPS_DASH			1:�j���̃y�����쐬���܂��B�y�������f�o�C�X�P�� 1 �ȉ��̏ꍇ�����L���ł��B 
	PS_DOT,					// MPS_DOT 			2:�_���̃y�����쐬���܂��B�y�������f�o�C�X�P�� 1 �ȉ��̏ꍇ�����L���ł��B 
	PS_DASHDOT,				// MPS_DASHDOT 		3:��_�j���̃y�����쐬���܂��B�y�������f�o�C�X�P�� 1 �ȉ��̏ꍇ�����L���ł��B 
	PS_DASHDOTDOT,			// MPS_DASHDOTDOT	4:��_�j���̃y�����쐬���܂��B�y�������f�o�C�X�P�� 1 �ȉ��̏ꍇ�����L���ł��B 
	PS_NULL					// MPS_NULL			5:null �̃y�����쐬���܂��B 
};

//     �ȉ���iPen�̓v���O�����쐬���̃T���v���ŕs�v
MINT	iPen[] = {
// nPenStyle 
// �y���̃X�^�C�����w�肵�܂��B�ŏ��̍\���̃R���X�g���N�^�̃p�����[�^�ɂ́A���̂����ꂩ�̒l���w��ł��܂��B 
	PS_SOLID,				// 0:�����̃y�����쐬���܂��B 
	PS_DASH,				// 1:�j���̃y�����쐬���܂��B�y�������f�o�C�X�P�� 1 �ȉ��̏ꍇ�����L���ł��B 
	PS_DOT,					// 2:�_���̃y�����쐬���܂��B�y�������f�o�C�X�P�� 1 �ȉ��̏ꍇ�����L���ł��B 
	PS_DASHDOT,				// 3:��_�j���̃y�����쐬���܂��B�y�������f�o�C�X�P�� 1 �ȉ��̏ꍇ�����L���ł��B 
	PS_DASHDOTDOT,			// 4:��_�j���̃y�����쐬���܂��B�y�������f�o�C�X�P�� 1 �ȉ��̏ꍇ�����L���ł��B 
	PS_NULL,				// 5:null �̃y�����쐬���܂��B 
	PS_INSIDEFRAME,			// 6:�O�ڂ���l�p�`���w�肷�� Windows �� GDI �̏o�͊֐� (���Ƃ��΁AEllipse�ARectangle�ARoundRect�APie�AChord �����o�֐�) �ō쐬���������}�`�̘g�̓����ɒ�����`�悷��y�����쐬���܂��B�O�ڂ���l�p�`���w�肵�Ȃ� Windows �� GDI �o�͊֐� (���Ƃ��΁ALineTo �����o�֐�) �ō쐬�����}�`�̂Ƃ��́A�y���̕`��̈�͐}�`�̘g�ɐ�������܂���B 

// CPen �R���X�g���N�^�� 2 �Ԗڂ̍\���ł́A�^�A�X�^�C���A�[�_�L���b�v�A���������̑g�ݍ��킹���w�肵�܂��B�e�J�e�S���̒l�̓r�b�g���Ƃ� OR ���Z�q (| ) ���g���đg�ݍ��킹�܂��B). �y���̌^�͎��̂����ꂩ�ł��B 

	PS_GEOMETRIC,			// 0x10000:�W�I���g���b�N �y�����쐬���܂��B 
	PS_COSMETIC,			// 0:�R�X���e�B�b�N �y�����쐬���܂��B 

// CPen �R���X�g���N�^�� 2 �Ԗڂ̍\���� nPenStyle �Ɏw�肷��y�� �X�^�C���Ɏ��̃X�^�C�����ǉ�����܂��B 

	PS_ALTERNATE,			// 8:1 �����Ƀs�N�Z����ݒ肷��y�����쐬���܂��B(���̃X�^�C���́A�R�X���e�B�b�N �y�������ɓK�p�ł��܂��B 
	PS_USERSTYLE,			// 7:���[�U�[���񋟂���X�^�C���z����g���y�����쐬���܂��B 

// �[�_�L���b�v�͎��̂����ꂩ�̒l�ɂȂ�܂��B 

	PS_ENDCAP_ROUND,		// 0:�[�_�L���b�v�͉~�ɂȂ�܂��B 
	PS_ENDCAP_SQUARE,		// 0x100:�[�_�L���b�v�͎l�p�`�ɂȂ�܂��B 
	PS_ENDCAP_FLAT,			// 0x200:�[�_�L���b�v�͕��ʂɂȂ�܂��B 

// �����͎��̂����ꂩ�̒l�ɂȂ�܂��B 

	PS_JOIN_BEVEL,			// 0x1000:�΂ߌ����ɂȂ�܂��B 
	PS_JOIN_MITER,			// 0x2000:SetMiterLimit �֐��Őݒ肵�����݂̐������̏ꍇ�A�}�C�^�[�����ɂȂ�܂��B�����𒴂����Ƃ��͎΂ߌ����ɂȂ�܂��B 
	PS_JOIN_ROUND			// 0:�~�����ɂȂ�܂��B 
};

/////////////////////////////////////////////////////////////////////////////
//  ���W�ϊ�
msCod::msCod()
{
	MREAL rr = MGPTOL->S;

	m_iMinMaxD.SetUnit();
	m_iMinMaxL.SetUnit();
	m_rMinMaxRS[0].SetUnit();
	SetMat();
}

/////////////////////////////////////////////////////////////////////////////
//  �_�����W��ʘg��ݒ肷��(�������Y���W���̏ꍇ�͐ݒ莞�ɁAY���W *= (-1))
void msCod::SetWinL(
						MINT	iStX,			// �\�����W�@�n�_(����)X
						MINT	iStY,			// �\�����W�@�n�_(����)�n�_Y
						MINT	iWidth,			// �\�����W�@��
						MINT	iHeight			// �\�����W�@����
				)
{
	m_iMinMaxL.min.x = iStX;
	m_iMinMaxL.max.x = iStX + iWidth;
	if ( iHeight < 0) {
		m_iUpY = 1;
		m_iMinMaxL.min.y = iStY + iHeight;
		m_iMinMaxL.max.y = iStY;
	} else {
		m_iUpY = -1;
		m_iMinMaxL.min.y = -(iStY + iHeight);
		m_iMinMaxL.max.y = -iStY;
	}
}

/////////////////////////////////////////////////////////////////////////////
//  �_�����W��ʘg�𓾂�(�������Y���W���̏ꍇ�͓ǂݍ��ݎ��ɁAY���W *= (-1))
void msCod::GetWinL(
						MINT	*piStX,			// �\�����W�@�n�_(����)X
						MINT	*piStY,			// �\�����W�@�n�_(����)Y
						MINT	*piWidth,		// �\�����W�@��
						MINT	*piHeight		// �\�����W�@����
				)
{
	*piStX = m_iMinMaxL.min.x;
	*piStY = m_iMinMaxL.max.y * m_iUpY;
	*piWidth = m_iMinMaxL.max.x - m_iMinMaxL.min.x;
	*piHeight =(m_iMinMaxL.min.y - m_iMinMaxL.max.y) * m_iUpY;
}

/////////////////////////////////////////////////////////////////////////////
//  �}�b�v���[�h��ݒ肷��
// �p�����[�^
// nMapMode 
//	�V�����}�b�v ���[�h���w�肷��B���̂����ꂩ�̒l�ɂȂ�B 
//	�ȉ��́����x ���W�̐������͉E�Ay ���W�̐������͏�ɂȂ�B	
//
//	�EMM_ANISOTROPIC  �_���P�ʂ́A�C�ӂɃX�P�[�����O���ꂽ����̔C�ӂ̒P�ʂɕϊ������B
//						�}�b�v ���[�h�� MM_ANISOTROPIC ��ݒ肵�Ă��A���݂̃E�B���h�E�܂���
//						�r���[�|�[�g�̐ݒ�͕ύX����Ȃ��B�P�ʁA�����A�X�P�[�����O��ύX
//						����Ƃ��́ASetWindowExt �����o�֐��� SetViewportExt �����o�֐���
//						�g���K�v������B 
//	��MM_HIENGLISH	  ���ꂼ��̘_���P�ʂ́A0.001 �C���`�ɕϊ������B
//	��MM_HIMETRIC	  ���ꂼ��̘_���P�ʂ́A0.01 mm �ɕϊ������B
//	�EMM_ISOTROPIC	  �_���P�ʂ́A�������X�P�[�����O���ꂽ����̔C�ӂ̒P�ʂɕϊ������B
//						x �������� 1 �P�ʂ́Ay �������� 1 �P�ʂƓ����ɂȂ�B
//						�����̊�]����P�ʂƌ������w�肷��Ƃ��́ASetWindowExt �����o�֐���
//						SetViewportExt �����o�֐����g���B�@GDI �́A�K�v�ɉ����āAx �P�ʂ�
//						y �P�ʂ������T�C�Y�ɂȂ�悤�ɒ�������B 
//	��MM_LOENGLISH    ���ꂼ��̘_���P�ʂ́A0.01 �C���`�ɕϊ������B
//	��MM_LOMETRIC     ���ꂼ��̘_���P�ʂ́A0.1 mm �ɕϊ������B
//	�EMM_TEXT		  ���ꂼ��̘_���P�ʂ́A1 �f�o�C�X �s�N�Z���ɕϊ������B
//	��MM_TWIPS		  ���ꂼ��̘_���P�ʂ́A1 �|�C���g�� 1/20 �ɕϊ������B
//						1 �|�C���g�� 1/72 �C���`�Ȃ̂ŁA1 twip �� 1/1440 �C���`�ɂȂ�B
// �߂�l
//	���O�̃}�b�v ���[�h��Ԃ��B
//
// ���
//	�}�b�v ���[�h�́A�_���P�ʂ��f�o�C�X�P�ʂɕϊ�����Ƃ��̏k�ڂ��`���A�f�o�C�X�� x ���� y ����
//	��������`����B�@GDI �́A�}�b�v ���[�h���g���āA�_�����W��K�؂ȃf�o�C�X���W�ɕϊ�����B
//	MM_TEXT ���[�h���g���ƁA�A�v���P�[�V��������Ƃ���f�o�C�X �s�N�Z���́A1 �s�N�Z���� 1 �P�ʂɂȂ�B
//	�s�N�Z���̕����T�C�Y�́A�f�o�C�X���ƂɈقȂ�B 
//
//	MM_HIENGLISH�AMM_HIMETRIC�AMM_LOENGLISH�AMM_LOMETRIC�AMM_TWIPS ���[�h�́A�A�v���P�[�V�����������P��
//	(�C���`�� mm �̂悤��) �ŕ`�悷��Ƃ��ɕ֗��ł���B
//	MM_ISOTROPIC ���[�h�́A�c���䂪 1:1 �Ȃ̂ŁA�C���[�W�̐��m�Ȍ`��ۑ�����K�v������Ƃ��ɕ֗��ł���B
//	MM_ANISOTROPIC ���[�h�́Ax ���W�� y ���W���ʂɒ��߂ł���悤�ɂ���B
//
// ���� 
//	�f�o�C�X �R���e�L�X�g���E���獶�ւ̃��C�A�E�g�ɕύX���邽�߂� SetLayout ���Ăяo���ƁA
//	SetLayout �������I�Ƀ}�b�v ���[�h�� MM_ISOTROPIC �ɕύX����B
//
MINT msCod::SetMapMode(
						MINT		iMapMode
				)
{
	if ( iMapMode != 0) {
		m_iMapMode = iMapMode;
	}
	return m_pDC->SetMapMode( m_iMapMode);
}

/////////////////////////////////////////////////////////////////////////////
//  �����W����_�����W�ւ̍��W�ϊ��}�g���b�N�X��
//	�_�����W����\�����W�ւ̕ϊ��{����ݒ肷��
void msCod::SetMat()
{
	MREAL s0, s1, s2;
	m_mat.SetUnit();
	s1 = (m_iMinMaxL.max.x - m_iMinMaxL.min.x) /
		 (m_rMinMaxRS[0].max.x - m_rMinMaxRS[0].min.x);
	s2 = (m_iMinMaxL.max.y - m_iMinMaxL.min.y) /
		 (m_rMinMaxRS[0].max.y - m_rMinMaxRS[0].min.y);
	s0 = __min(s1, s2);
	m_mat.m[0][0] = s0;
	m_mat.m[1][1] = s0;

	m_mat.m[2][2] = s0;
	m_mat.m[3][0] = (m_iMinMaxL.min.x + m_iMinMaxL.max.x) * 0.5f -
					s0*(m_rMinMaxRS[0].min.x + m_rMinMaxRS[0].max.x) * 0.5f;
	m_mat.m[3][1] = (m_iMinMaxL.min.y + m_iMinMaxL.max.y) * 0.5f -
					s0*(m_rMinMaxRS[0].min.y + m_rMinMaxRS[0].max.y) * 0.5f;

	m_sclRPtoLP = s0;

	m_vsclLPtoDP.x = MREAL( m_iMinMaxD.max.x - m_iMinMaxD.min.x) /
					 MREAL( m_iMinMaxL.max.x - m_iMinMaxL.min.x);
	m_vsclLPtoDP.y = - MREAL( m_iMinMaxD.max.y - m_iMinMaxD.min.y) /
					 MREAL( m_iMinMaxL.max.y - m_iMinMaxL.min.y);
}

/////////////////////////////////////////////////////////////////////////////
// �`�揈��
//#define			MT_LEFT			1
//#define			MT_CENTER		2
//#define			MT_RIGHT		3
//#define			MT_UPPER		1
//#define			MT_LOWER		3

//#define			MT_FIXEDSIZE	TRUE
//#define			MT_FREESIZE		FALSE

/////////////////////////////////////////////////////////////////////////////
//  ����A�����A���F��ݒ肷��
void msCod::SetLineAttr(
						MPENSTYLE	iLineStyle,					// ����
																//			MPS_SOLID		(0) :	����
																//			MPS_DASH		(1) :	�j��
																//			MPS_DOT			(2) :	�_��
																//			MPS_DASHDOT		(3) :	�P�_����
																//			MPS_DASHDOTDOT	(4) :	�Q�_����
																//			MPS_NULL		(5) :	���F
						MREAL		fLineWidth,					// ����
																//			�����Œ胂�[�h�̏ꍇ�̓h�b�g���A
																//			�������R���[�h�̏ꍇ��(1/10)mm
						DWORD		rgbLine,					// ���F	RGB
						bool		bFixedLineWidth				// �����Œ胂�[�h�t���O
																//			TRUE  :	�����Œ�
																//			FALSE : �������R
				)
{
	z_iLineStyle 		= iLineStyle;
	z_fLineWidth 		= fLineWidth;
	z_rgbLine 			= rgbLine;
	z_bFixedLineWidth	= bFixedLineWidth;
}

/////////////////////////////////////////////////////////////////////////////
//  	�����ݒ肷��
void msCod::SetLineStyle(
						MPENSTYLE	iLineStyle					// ����
																//			MPS_SOLID		(0) :	����
																//			MPS_DASH		(1) :	�j��
																//			MPS_DOT			(2) :	�_��
																//			MPS_DASHDOT		(3) :	�P�_����
																//			MPS_DASHDOTDOT	(4) :	�Q�_����
																//			MPS_NULL		(5) :	���F
				)
{
	z_iLineStyle = iLineStyle;
}

/////////////////////////////////////////////////////////////////////////////
//  	������ݒ肷��
void msCod::SetLineWidth(
						MREAL		fLineWidth					// ����
																//			�����Œ胂�[�h�̏ꍇ�̓h�b�g���A
																//			�������R���[�h�̏ꍇ��mm
				)
{
	z_fLineWidth = fLineWidth;
}

/////////////////////////////////////////////////////////////////////////////
//  	���F��ݒ肷��
void msCod::SetLineColor(
							DWORD	rgbLine						// ���F	RGB
					)
{
	z_rgbLine = rgbLine;
}

/////////////////////////////////////////////////////////////////////////////
//  	�����Œ�t���O��ݒ肷��
void msCod::SetFixedLineWidth(
							bool	bFixedLineWidth)			// �\�������Œ�t���O
																//			TRUE  :	�����Œ�
																//			FALSE : �������R
{
	z_bFixedLineWidth = bFixedLineWidth;
}

/////////////////////////////////////////////////////////////////////////////
//  	�t�H���g�A���������A���������A�I�t�Z�b�g�����ʒu��ݒ肷��
void msCod::SetTextAttr(
						MCHAR*		sFont,						// �����t�H���g
						MREAL		fHeight,					// ��������	
																//			���������Œ胂�[�h�̏ꍇ�̓h�b�g���A
																//			�����������R���[�h�̏ꍇ��(1/10)mm
						MINT		iPosUL,						// �����㉺��ʒu
																//			MT_UPPER	: ��
																//			MT_CENTER	: ��
																//			MT_LOWER	: ��
						MINT		iPosLR,						// �������E��ʒu
																//			MT_LEFT		: ��
																//			MT_CENTER	: ��
																//			MT_RIGHT	: �E
						DWORD		rgbText,					// �����F	RGB
						MgVect2D&	vDirect,					// �����\������	(dx, dy)	(�������R)
						MgVect2D&	pOffset,					// �����\���ʒu�I�t�Z�b�g (x, y)
																//			���������Œ胂�[�h�̏ꍇ�̓h�b�g���A
																//			�����������R���[�h�̏ꍇ��(1/10)mm
						bool		bFixedTextSize				// ���������Œ胂�[�h
																//			MT_FIXEDSIZE : ���������Œ�(TRUE)
																//			MT_FREESIZE	 : �����������R(FALSE)
				)
{
	SetTextFont( sFont);
	z_fTextHeight = fHeight;
	SetTextIchi( iPosUL, iPosLR);

	z_rgbText			= rgbText;
	z_vTextDirect		= vDirect.Unitize();
	z_pTextOffset		= pOffset;
	z_bFixedTextSize	= bFixedTextSize;
}

/////////////////////////////////////////////////////////////////////////////
//  	�t�H���g��ݒ肷��
void msCod::SetTextFont(
						MCHAR*		sFont						// �t�H���g
				)
{
	if (sFont == NULL)
		Mstrcpy_s( z_sTextFont, Mstr( "�l�r �S�V�b�N"));
	else
		Mstrcpy_s( z_sTextFont, sFont);
}

/////////////////////////////////////////////////////////////////////////////
//  	����������ݒ肷��
void msCod::SetTextHeight(
						MREAL		fHeight						// ��������	
																//			���������Œ胂�[�h�̏ꍇ�̓h�b�g���A
																//			�����������R���[�h�̏ꍇ��mm
				)
{
	z_fTextHeight = fHeight;
}

/////////////////////////////////////////////////////////////////////////////
//  	������̔z�u��ʒu��ݒ肷��
void msCod::SetTextIchi(
						MINT		iPosUL,						// �����㉺��ʒu
																//			MT_UPPER	: ��
																//			MT_CENTER	: ��
																//			MT_LOWER	: ��
						MINT		iPosLR						// �������E��ʒu
																//			MT_LEFT		: ��
																//			MT_CENTER	: ��
																//			MT_RIGHT	: �E
				)
{
	if ( iPosUL >= 1 && iPosUL <= 3)
		z_iTextPosUL = iPosUL;
	else
		z_iTextPosUL = 1;

	if ( iPosLR >= 1 && iPosLR <= 3)
		z_iTextPosLR = iPosLR;
	else
		z_iTextPosLR = 1;
}

/////////////////////////////////////////////////////////////////////////////
//  	�����F��ݒ肷��
void msCod::SetTextColor(
						DWORD		rgbText						// �����F	RGB
				)
{
	z_rgbText = rgbText;
}

/////////////////////////////////////////////////////////////////////////////
//  	����������ݒ肷��
void msCod::SetTextDirect(
						MgVect2D&	vDirect						// �����\������	(dx, dy)	(�������R)
				)
{
	z_vTextDirect = vDirect.Unitize();
}

/////////////////////////////////////////////////////////////////////////////
//  	�I�t�Z�b�g��ݒ肷��
void msCod::SetTextOffset(
						MgVect2D&	pOffset						// �����\���ʒu�I�t�Z�b�g (x, y)
																//			���������Œ胂�[�h�̏ꍇ�̓h�b�g���A
																//			�����������R���[�h�̏ꍇ��mm
				)
{
	z_pTextOffset = pOffset;
}

/////////////////////////////////////////////////////////////////////////////
//  	�\�������T�C�Y�Œ�t���O��ݒ肷��
void msCod::SetFixedTextSize(
						bool		bFixedTextSize				//	�\�������T�C�Y�Œ胂�[�h
																//			TRUE  :	�\�������T�C�Y�Œ�
																//			FALSE : �\�������T�C�Y���R
				)
{
	z_bFixedTextSize = bFixedTextSize;
}
/////////////////////////////////////////////////////////////////////////////
//  �������\������
void msCod::Text(
						const	MgPoint2D	&pa1,
								MCHAR*		str
				)
{
	MgPoint2D	p1r;											// �\���ʒu
	CPoint		p1s;											// �\���ʒu
	MREAL		fAngle;											// �\���p�x�i�x�j
	MINT		iAngle;											// �\���p�x�i�x�j �~ 10
	MINT		iTextPosLR;
	MINT		iTextPosUL;
	MgVect2D	vDirect;										// �\�������i�P�ʃx�N�g���j
	MgVect2D	vOffset;										// �\���I�t�Z�b�g

//	MINT		TAUD[] = { TA_TOP, TA_TOP, TA_BOTTOM};			// �㉺������ʒu�ϊ��e�[�u���@TA_BASELINE�͖��g�p
	MINT		TAUD[] = { TA_TOP, TA_TOP, TA_BASELINE};		// �㉺������ʒu�ϊ��e�[�u���@TA_BOTTOM�͖��g�p
	MINT		TALR[] = { TA_LEFT, TA_CENTER, TA_RIGHT};		// ���E������ʒu�ϊ��e�[�u��
	MINT		iTextPos;

	CPen		Pen;
	LOGFONT		lf;
	CFont		font;
	MINT		iTextHeight;									// �����\������

	memset( &lf, 0, sizeof( LOGFONT));

	vDirect = z_vTextDirect;
	vOffset = z_pTextOffset;

	fAngle = MGDEGREE( MGeo::AngleXVect2D( vDirect));			// ����]�p�x(�x)
	if (fAngle <= 105 && fAngle >= -75) {
		iTextPosUL = z_iTextPosUL;
		iTextPosLR = z_iTextPosLR;
	} else {													// �\���p�x�ɂ�蕶���\���������]
		fAngle -= 180.;	if (fAngle <= -180) fAngle += 360;
		vDirect.SetRot180();
		vOffset.SetRot180();
		iTextPosUL = 4 - z_iTextPosUL;
		iTextPosLR = 4 - z_iTextPosLR;
	
	}
	iAngle = MINT( fAngle * 10);								// ������\�������@����]�p�x(1/10�x �l�̌ܓ�) 
	lf.lfEscapement	= - iAngle * m_iUpY;						// �����\���p�x	������I���W�i���_��Y���W��̏ꍇ�͉E��](1/10�x)
																//				������I���W�i���_��Y���W���̏ꍇ�͍���](1/10�x)
	if (z_bFixedTextSize) {
		iTextHeight = MINT( z_fTextHeight * 10);
		if (z_iTextPosUL == 2) 
			vOffset.y += (z_fTextHeight * 0.5f * 1.2f);			// ���i�\���p�␳ ( /2 /10 * (�␳�@1.2)
		vOffset /= (m_sclRPtoLP * m_vsclLPtoDP.x);				// x������y�����Ƃł��ꂪ�قȂ�������m_vsclLPtoDP.y�͕s�g�p
	} else {
		iTextHeight = MINT( z_fTextHeight * m_sclRPtoLP * 10 *
			(MGeo::AbsVect2D( MgVect2D( abs(m_vsclLPtoDP.y * vDirect.x),
									    abs(m_vsclLPtoDP.x * vDirect.y)))));
//		vOffset *= (m_sclRPtoLP * m_vsclLPtoDP.x);				// x������y�����Ƃł��ꂪ�قȂ�������m_vsclLPtoDP.y�͕s�g�p
		if (z_iTextPosUL == 2) 
			vOffset.y += (z_fTextHeight * 0.5f * 1.2f);			// ���i�\���p�␳ ( /2 /10 * (�␳�@1.2)
	}
	lf.lfHeight		= iTextHeight;								// �����\������	�P�� 1/10�|�C���g

	Mstrcpy_s( lf.lfFaceName, z_sTextFont);						// ����
	VERIFY( font.CreatePointFontIndirect( &lf, m_pDC));
	
	CFont* pBackup = m_pDC->SelectObject( &font);				// �t�H���g�̐ݒ�

	iTextPos = TAUD[iTextPosUL - 1] | TALR[iTextPosLR - 1];
	m_pDC->SetTextAlign( iTextPos);								// ������\����ʒu�̎w��

//	m_pDC->SetBkColor( RGB( 100, 100, 100));
	m_pDC->SetBkMode( TRANSPARENT);								// �����w�i�F
	m_pDC->SetTextColor( z_rgbText);							// �����F


	vOffset.SetRot( vDirect);

	p1r = pa1 + vOffset;
	p1s = RPtoLP( p1r);

//	m_pDC->TextOut( (MINT)p1s.x, (MINT)p1s.y * m_iUpY, str, (MINT)strlen(str));
	m_pDC->TextOut( (MINT)p1s.x, (MINT)p1s.y * m_iUpY, str);

	m_pDC->SelectObject( pBackup);
	font.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
//  ������\������	( "MsCod.h" �� ��`�ς� )
//void msCod::Line(
//				const	MgLine2D		&ln1
//				)
//{
//	Line( ln1.p[0], ln1.p[1]);
//}

/////////////////////////////////////////////////////////////////////////////
//  ������\������
void msCod::Line(
				const	MgPoint2D	&pa1,
				const	MgPoint2D	&pa2
				)
{
	CPoint		p1, p2;
	MINT		iPenStyle;
	CPen		Pen;
	CGdiObject* pBackup;
	MINT		iLineWidth;										// ����

	p1 = RPtoLP( pa1);
	p2 = RPtoLP( pa2);

	iPenStyle = PSTbl[z_iLineStyle];

	if (z_bFixedLineWidth)
		iLineWidth = MGMAX( MINT( z_fLineWidth / m_vsclLPtoDP.x), 1);
	else
		iLineWidth = MINT( z_fLineWidth * m_sclRPtoLP);

	Pen.CreatePen(iPenStyle, iLineWidth, z_rgbLine);
	pBackup = m_pDC->SelectObject( &Pen);

	m_pDC->MoveTo( p1.x, p1.y * m_iUpY);
	m_pDC->LineTo( p2.x, p2.y * m_iUpY);

	m_pDC->SelectObject( pBackup);
	Pen.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
//  �����`��\������
void msCod::Rect(
				const	MgPoint2D	&pa1,
				const	MgPoint2D	&pa2
				)
{
	CPoint		p1, p2;
	MINT		iPenStyle;
	CPen		Pen;
	CGdiObject* pBackup;
	MINT		iLineWidth;										// ����

	p1 = RPtoLP( pa1);
	p2 = RPtoLP( pa2);

	iPenStyle = PSTbl[z_iLineStyle];

	if (z_bFixedLineWidth)
		iLineWidth = MGMAX( MINT( z_fLineWidth / m_vsclLPtoDP.x), 1);
	else
		iLineWidth = MINT( z_fLineWidth * m_sclRPtoLP);

	Pen.CreatePen(iPenStyle, iLineWidth, z_rgbLine);
	pBackup = m_pDC->SelectObject( &Pen);

	m_pDC->Rectangle( (MINT)p1.x, (MINT)p1.y * m_iUpY, (MINT)p2.x, (MINT)p2.y * m_iUpY);
	m_pDC->SelectObject( pBackup);
	Pen.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
//  �܂����\������
void msCod::Polyline(
						MgPoint2D*	pb,
						MINT		inpb
				)
{
	CPoint		p1;
	CPoint		lpb[200];
	MINT		iPenStyle;
	CPen		Pen;
	CGdiObject* pBackup;
	MINT		iLineWidth;										// ����

	for (int lpc=0; lpc<inpb; lpc++) {
		p1 = RPtoLP( pb[lpc]);
		lpb[lpc].x = p1.x;
		lpb[lpc].y = p1.y * m_iUpY;
	}
	
	iPenStyle = PSTbl[z_iLineStyle];

	if (z_bFixedLineWidth)
		iLineWidth = MGMAX( MINT( z_fLineWidth / m_vsclLPtoDP.x), 1);
	else
		iLineWidth = MINT( z_fLineWidth * m_sclRPtoLP);


	Pen.CreatePen( iPenStyle, iLineWidth, z_rgbLine);
	pBackup = m_pDC->SelectObject( &Pen);

	m_pDC->Polyline( lpb, inpb);
	m_pDC->SelectObject( pBackup);
	Pen.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
//  ���p�`��\������
void msCod::Polygon(
						MgPoint2D*	pb,
						int			inpb
				)
{
	MINT		lpc;
	CPoint		p1;
	CPoint		lpb[200];
	MINT		iPenStyle;
	CPen		Pen;
	CGdiObject* pBackup;
	MINT		iLineWidth;										// ����

	for (lpc=0; lpc<inpb; lpc++) {
		p1 = RPtoLP( pb[lpc]);
		lpb[lpc].x = p1.x;
		lpb[lpc].y = p1.y * m_iUpY;
	}
	lpb[lpc] = lpb[0];
	inpb++;
	
	iPenStyle = PSTbl[z_iLineStyle];

	if (z_bFixedLineWidth)
		iLineWidth = MGMAX( MINT( z_fLineWidth / m_vsclLPtoDP.x), 1);
	else
		iLineWidth = MINT( z_fLineWidth * m_sclRPtoLP);


	Pen.CreatePen( iPenStyle, iLineWidth, z_rgbLine);
	pBackup = m_pDC->SelectObject( &Pen);

	m_pDC->Polyline( lpb, inpb);
	m_pDC->SelectObject( pBackup);

	Pen.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
//  �~�ʂ�\������
void msCod::Arc1(
				const MgPoint2D	&pac,
				MREAL			rh,
				MREAL			a1,
				MREAL			a2
				)
{
	CPoint		pc;
	MREAL		rhw;
	MINT		ihw;

	CPoint		plu, prd, pst, ped;
	MINT		iPenStyle;
	CPen		Pen;
	CGdiObject* pBackup;
	MINT		iLineWidth;										// ����

	pc = RPtoLP( pac);
	rhw = m_sclRPtoLP * rh;
	ihw = MINT( rhw);
	CPoint pr( ihw, -ihw);
	plu = pc - pr;
	prd = pc + pr;

	MREAL a3 = a1 + a2;
	pst.x = MINT( rhw * (MREAL)cos(a1 * MC_DTR)) + pc.x;
	pst.y = MINT( rhw * (MREAL)sin(a1 * MC_DTR)) + pc.y;
	ped.x = MINT( rhw * (MREAL)cos(a3 * MC_DTR)) + pc.x;
	ped.y = MINT( rhw * (MREAL)sin(a3 * MC_DTR)) + pc.y;

	iPenStyle = PSTbl[z_iLineStyle];

	if (z_bFixedLineWidth)
		iLineWidth = MGMAX( MINT( z_fLineWidth / m_vsclLPtoDP.x), 1);
	else
		iLineWidth = MINT( z_fLineWidth * m_sclRPtoLP);

	Pen.CreatePen( iPenStyle, iLineWidth, z_rgbLine);
	pBackup = m_pDC->SelectObject( &Pen);

	m_pDC->Arc(	plu.x, plu.y * m_iUpY, 
				prd.x, prd.y * m_iUpY, 
				pst.x, pst.y * m_iUpY, 
				ped.x, ped.y * m_iUpY);
	m_pDC->SelectObject( pBackup);
	Pen.DeleteObject();
}

} // namespace MC