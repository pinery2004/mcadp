#pragma once

#include "MgMat.h"

namespace MC
{

class	M3View
{
public:
    HGLRC	m_hRC;

	MINT	m_iFWire;											// ���C���n�[�l�X�\���t���O
																//�@(1: ���C���n�[�l�X�\�� 0:�ʕ\��)

	MREAL	m_rRotX;											// �w����]�p
	MREAL	m_rRotY;											// �x����]�p
	MREAL	m_rRotZ;											// �y����]�p

	MREAL	m_rMovX;											// �w�������ړ���
	MREAL	m_rMovY;											// �x�������ړ���
	MREAL	m_rMovZ;											// �y�������ړ���

	MREAL	m_rScl;												// ���W�ϊ��X�P�[��
	MgMat3E	m_mTrans;											// ���W�ϊ��}�g���b�N�X

	M3View();
	int OnCreate( HDC hdc);
	void OnDestroy();
	void OnPaint();
	void OnSize( UINT nType, int cx, int cy);
	void OnMouseMove( MINT nFlags, MgVect3	PtDnt, MgVect3	RtDnt, MREAL SclD);
	BOOL RenderScene( void );
    BOOL SetDCPixelFormat( HDC hdc);
    BOOL InitializeOpenGL( void);

};

//�y�@�\�z�`��
//BOOL RenderScene( int i_iFWire,	MREAL i_rScl, MgVect3& i_VRot, MgVect3& i_VMov);
BOOL MsRenderScene1( MINT i_iFWire, MREAL i_rScl,
				  MREAL i_rRotX, MREAL i_rRotY, MREAL i_rRotZ,
				  MREAL i_rMovX, MREAL i_rMovY, MREAL i_rMovZ);

} // namespace MC
