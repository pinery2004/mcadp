// OpenGL �g�p �֐�
#pragma once

// OpenGL
class GlLib{
public:
	static GLint InitializeOpenGL( void);

	static int MakeGLObject( void);

	static void DrawGLobject( void);
	static void GlLib::DrawGLobject1(
						int			i_iFWire,	// �\���^�C�v�@0: �ʕ\���A1:�������A2:���ނ̂݁A3:���C���t���[���\��
						MREAL		i_rScl,		// �g�嗦
						MREAL		i_rRotX,	// ��]�p	V3( ���C���C��)
						MREAL		i_rRotY,	// ��]�p	V3( ���C���C��)
						MREAL		i_rRotZ,	// ��]�p	V3( ���C���C��)
						MREAL		i_rMovX,	// �ړ���	V3( ���C���C��)
						MREAL		i_rMovY,	// �ړ���	V3( ���C���C��)
						MREAL		i_rMovZ		// �ړ���	V3( ���C���C��)
	);
	static int SetDCPixelFormat( HDC hdc);

	static void ViewSetting(GLint w,GLint h);

	static void Lighting();

	static GLint DrawPlane( GLdouble w, GLdouble d ,GLdouble h);

	static GLint DrawBox(GLdouble d, GLdouble w, GLdouble h);

};