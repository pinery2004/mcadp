#include	"StdAfx.h"
#include	"MCAD.h"
#include	< GL/gl.h >
#include	< GL/glu.h >
#include	"MoGlLib.h"
// OpenGL

GLint MoGlLib::InitializeOpenGL(void)
{
	//3D�V�[���̔w�i�����ɂ���B
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f) ;	

	glDepthFunc(GL_LEQUAL) ;
	//�f�v�X�o�b�t�@��L����
	glEnable(GL_DEPTH_TEST) ;

	//Lighting��L����
	glEnable(GL_LIGHTING) ; 
	glEnable(GL_LIGHT0) ;
	glEnable(GL_LIGHT1) ;

	return (0) ;
}

int MoGlLib::MakeGLObject()
{
	//�����Ɏ��O�ɍ쐬���Ă����I�u�W�F�N�g�̋L�q��������
	//

	return (0) ;
}

#if(1)
void MoGlLib::DrawGLobject1(
						int			i_iFWire,	// �\���^�C�v�@0: �ʕ\���A1:�������A2:���ނ̂݁A3:���C���t���[���\��
						MREAL		i_rScl,		// �g�嗦
						MREAL		i_rRotX,	// ��]�p	V3( ���C���C��)
						MREAL		i_rRotY,	// ��]�p	V3( ���C���C��)
						MREAL		i_rRotZ,	// ��]�p	V3( ���C���C��)
						MREAL		i_rMovX,	// �ړ���	V3( ���C���C��)
						MREAL		i_rMovY,	// �ړ���	V3( ���C���C��)
						MREAL		i_rMovZ		// �ړ���	V3( ���C���C��)
	)
{
	//�V�[�����N���A����B�F���A�f�v�X�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT) ;
	//�I�u�W�F�N�g�`�惂�[�h�ɂ���B
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;
	//////////////////////////////////////////////
	//�K�v�ȋ@�\�̗L����
	//
	glEnable(GL_NORMALIZE) ;
	glEnable(GL_AUTO_NORMAL) ;
	glShadeModel (GL_SMOOTH);
	glEnable( GL_DEPTH_TEST ); //Z�o�b�t�@���g�p����

	// �}�g���b�N�X�̃X�^�b�N
	glPushMatrix();

	//�����ŌĂяo���ƁA�J�������W��Ɍ������u�����B
//	Lighting();

	//gluLookAt( ���_�̈ʒux,y,z,  ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z, ���E�̏�����̃x�N�g��x,y,z);
	// �ȉ��̂悤�ɌĂяo����,���_(0,2,-5)�C���_���������āC���̂Ƃ�y������ɂȂ�悤�ɒ��߂�
	gluLookAt(0, 2.0, -5.0,   0,0,0,    0,1,0);

	Lighting();

	//�Ɩ���_������B
	glEnable(GL_LIGHTING) ; 
	glEnable(GL_LIGHT0) ;

	GLfloat light0_position[] = {1.0, 5.0, -3.0, 1.0} ;
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	
#if(1)
	// ��] X��Y��Z�̏��ɉ�]
    glRotatef( i_rRotZ, 0.0f, 0.0f, 1.0f );
    glRotatef( i_rRotY, 0.0f, 1.0f, 0.0f );
	glRotatef( i_rRotX, 1.0f, 0.0f, 0.0f );

	// �g��k��
	glScalef( i_rScl, i_rScl, i_rScl); 

	// �ړ�
	glTranslatef( i_rMovX, i_rMovY, i_rMovZ);
#endif

	DrawBox(2.0, 3.0, 1.0);
	DrawPlane( 5.0, 5.0 , 0.0);

	//���W�n��߂��Ă���
	glPopMatrix();

	glDisable(GL_AUTO_NORMAL) ;
	glDisable(GL_NORMALIZE) ;
	return;
}
#endif 

int MoGlLib::SetDCPixelFormat( HDC hdc)
{

    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof (PIXELFORMATDESCRIPTOR), 		// Specifies the size of this data structure
        1,                                          			// Specifies the version of this data structure
        PFD_DRAW_TO_WINDOW |					// �s�N�Z���o�b�t�@�̃r�b�g�t���O�̐ݒ�
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,							// RGBA pixel values
        32,										// 32-bit�J���[�Ǝw��
        0, 0, 0, 0, 0, 0,						// Specifies the number of red bitplanes in each RGBA color buffer
        0, 0,									// Specifies the number of alpha bitplanes in each RGBA color buffer
        0, 0, 0, 0, 0,							// Specifies the total number of bitplanes in the accumulation buffer
        32,										// Specifies the depth(bit) of the depth (z-axis) buffer
        32,										// Specifies the depth of the stencil buffer
        0,										// Specifies the number of auxiliary buffers
        PFD_MAIN_PLANE,							// Layer type�@Ignored...
        0,										// Specifies the number of overlay and underlay planes
        0,										// Ignored
		0,										// Specifies the transparent color or index of an underlay plane
        0										// Ignored
    };

    int nPixelFormat;
    
    nPixelFormat = ChoosePixelFormat (hdc, &pfd);
    if (SetPixelFormat(hdc, nPixelFormat, &pfd) == FALSE) {
      return FALSE ;
    }

    if (DescribePixelFormat(hdc, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd) == 0) {
      return FALSE ;
    }

    return TRUE ;
}

void MoGlLib::ViewSetting(GLint w,GLint h)
{
	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	// gluPerspective( ����p�x[deg],  �A�X�y�N�g��(�E�B���h�E�̕�/����), 
	//		�`�悷�鋗���͈́i���_����ł��߂��_�܂ł̋����j, ���_����ł������_�܂ł̋���);
	gluPerspective(60, (GLfloat)w/(GLfloat)h, 0.5, 15.0) ;
	// glViewport( �����̃s�N�Z�����WX, �����̃s�N�Z�����WY, �E�B���h�E���C���� );
	glViewport (0, 0, w , h) ;
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity ();
	return;
}

void MoGlLib::Lighting()
{
	//�ƌ�������L����
	glEnable(GL_LIGHTING);
	//���ʏƌ����[�h�ɐݒ肷��
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE );
	//�����Ɋ֌W���Ȃ�������ݒ�
	GLfloat model_ambient[]={0.4f,0.4f,0.4f,1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	//�����̊���(ambient),�g�U��(diffuse),���ʌ�(specular)��ݒ�
	GLfloat light0_ambient[]={0.5f,0.5f,0.5f,1.0f};
	GLfloat light0_diffuse[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat light0_specular[]={1.0f,1.0f,1.0f,1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	//�����̈ʒu��ݒ肷��D
	GLfloat light0_position[]={0.0f,0.0f,1.0f,1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	//���C�g0��L����
	glEnable(GL_LIGHT0);
}

GLint MoGlLib::DrawPlane( GLdouble w, GLdouble d ,GLdouble h)
{
	GLdouble norm[3];
	glPushMatrix();
	glBegin( GL_POLYGON );
		norm[0]=1;norm[1]=0;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( w/2.0 , h ,   d/2.0 );
		glVertex3d( w/2.0 , h ,  -d/2.0  );
		glVertex3d(-w/2.0 , h ,  -d/2.0  );
		glVertex3d(-w/2.0 , h ,   d/2.0  );
	glEnd();
	glPopMatrix();

	return(0) ;
}

GLint MoGlLib::DrawBox(GLdouble d, GLdouble w, GLdouble h)
{
	GLdouble norm[3];
	
	glPushMatrix();
	glTranslated(-d/2.0,-w/2.0,-h/2.0);
	glBegin( GL_POLYGON );
		norm[0]=0;norm[1]=-1;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( d , 0 , 0 );
		glVertex3d( d , 0 , h );
		glVertex3d( 0 , 0 , h );
	glEnd();
	glBegin( GL_POLYGON );
		norm[0]=0;norm[1]=-1;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( 0 , w , 0 );
		glVertex3d( d , w , 0 );
		glVertex3d( d , w , h );
		glVertex3d( 0 , w , h );
	glEnd();

	glBegin( GL_POLYGON );
		norm[0]=0;norm[1]=0;norm[2]=1;
		glNormal3dv (norm);
		glVertex3d( 0 , 0 , h );
		glVertex3d( d , 0 , h );
		glVertex3d( d , w , h );
		glVertex3d( 0 , w , h );
	glEnd();
	glBegin( GL_POLYGON );
		norm[0]=0;norm[1]=0;norm[2]=1;
		glNormal3dv (norm);
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( d , 0 , 0 );
		glVertex3d( d , w , 0 );
		glVertex3d( 0 , w , 0 );
	glEnd();

	glBegin( GL_POLYGON );
		norm[0]=-1;norm[1]=0;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( 0 , 0 , h );
		glVertex3d( 0 , w , h );
		glVertex3d( 0 , w , 0 );
	glEnd();
	glBegin( GL_POLYGON );
		norm[0]=-1;norm[1]=0;norm[2]=0;
		glNormal3dv (norm);
		glVertex3d( d , 0 , 0 );
		glVertex3d( d , 0 , h );
		glVertex3d( d , w , h );
		glVertex3d( d , w , 0 );
	glEnd();
	glPopMatrix();


	return(0) ;

}
