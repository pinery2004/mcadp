/******************************************************************************************************************
[ �@�\ ] IJG �����ŃG���[�����������ꍇ�̏���
[ �Ԓl ] �Ȃ�
******************************************************************************************************************/
#include "stdafx.h"
#define			 XMD_H																	/* X11/xmd.h correctly defines INT32 */

#include		"cdjpeg.h"																// IJG �w�b�_�t�@�C��
#include		"MbBasic.h"
#include		"MsLib.h"
#include		"MsJpegLib.h"

//HHHH
void MsJpegErrExit(
								j_common_ptr		cinfo)								// (I ) JPEG���k��L�������Ұ��p�\���̂ւ��߲��
{
	PiIjgErrorPtr		myerr;
	char				buffer[JMSG_LENGTH_MAX];
//	MCHAR*				uni_buffer;


	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	myerr = (PiIjgErrorPtr) cinfo->err;

	/* �G���[���b�Z�[�W�̕\�� */
	(*cinfo->err->format_message) ( cinfo, buffer);

	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);

}
