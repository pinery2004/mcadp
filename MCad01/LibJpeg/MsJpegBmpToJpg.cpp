/******************************************************************************************************************
[ �@�\ ] BMAP�t�@�C����JPEG�t�H�[�}�b�g�Ɉ��k�E�ϊ�
[ �Ԓl ] �X�e�[�^�X        0 : ����     -1 : �ُ�
******************************************************************************************************************/
#include "stdafx.h"
#define			 XMD_H																	/* X11/xmd.h correctly defines INT32 */

#include		"cdjpeg.h"																// IJG �w�b�_�t�@�C��
#include		"MbBasic.h"
#include		"MsJpegLib.h"

//HHHH
MINT MsJpegBmpToJpg(							// (  O) �ð��
						MCHAR*	FLName1,		// (I  ) �ϊ����摜̧�ٖ�
						MCHAR*	FLName2,		// (I  ) �ϊ���摜̧�ٖ�
						MUINT	Quality,		// (I  ) ���k��   (0�`100)
						MUINT	Smooth)			// (I  ) �Ѱ��ݸ� (0�`100)
{
	MINT						Status;			// �ð��
	struct jpeg_compress_struct	CInfo;			// JPEG���k�����Ұ����܂ލ\����
	PiIjgErrorMgr				JpErr;			// IJG �̴װ�� DigiD �ɕԂ��d�g��
	cjpeg_source_ptr			SrcMgr;			// ����̧�ق̊Ǘ��p�\����
	FILE*						InFile;			// ����̧���߲��
	FILE*						OutFile;		// �o��̧���߲��
	JDIMENSION					NScan;			//


	Status = -1;

	// �t�@�C�����J��
	if ((InFile = Mfopen( FLName1, READ_BINARY)) == NULL)    goto  PRG_EXIT;

	if ((OutFile = Mfopen( FLName2, WRITE_BINARY)) == NULL) {
		fclose( InFile);
		goto  PRG_EXIT;
	}

	// �G���[�����̏�����
	CInfo.err = jpeg_std_error(&JpErr.pub);
	JpErr.pub.error_exit = MsJpegErrExit;												// �װ������u������
	if (setjmp(JpErr.setjmp_buffer)) {													// �װ����ٔ���
		jpeg_destroy_compress(&CInfo);
		fclose(InFile); fclose(OutFile);
		goto  PRG_EXIT;
	}

	jpeg_create_compress(&CInfo);														// JPEG���k�����Ұ���������

	CInfo.in_color_space = JCS_RGB;														// ���̒l
	jpeg_set_defaults(&CInfo);															// ��̫�Ă����Ұ���ݒ�

	SrcMgr = jinit_read_bmp(&CInfo);													// BMP�t�@�C���Ǎ��ݐݒ�
	SrcMgr->input_file = InFile;

	(*SrcMgr->start_input) (&CInfo, SrcMgr);											// ����̧�ق�ͯ�ނ���̧�ٻ��ނƶװ��߰��𓾂�

	jpeg_default_colorspace(&CInfo);													// �װ��߰��Ɉˑ�������̫�ď����Đݒ�

	CInfo.smoothing_factor = Smooth;													// �Ѱ��ݸ�
	jpeg_set_quality( &CInfo,Quality, true);											// ���k��

	jpeg_stdio_dest(&CInfo, OutFile);													// �o�͐�̧�ق�ݒ�

	// ���k�����J�n
	jpeg_start_compress(&CInfo, TRUE);

	// �ް��o��/
	while (CInfo.next_scanline < CInfo.image_height) {
		NScan = (*SrcMgr->get_pixel_rows) (&CInfo, SrcMgr);
		(void) jpeg_write_scanlines(&CInfo, SrcMgr->buffer, NScan);
	}

	// �I�������������؂̉��
	(*SrcMgr->finish_input) (&CInfo, SrcMgr);
	jpeg_finish_compress(&CInfo);
	jpeg_destroy_compress(&CInfo);

	// ̧�� �۰��
	fclose(InFile);
	fclose(OutFile);

	// �x������
	if (JpErr.pub.num_warnings) {
		Status = JpErr.pub.num_warnings + 1;
	} else {
		Status = 0;
	}

PRG_EXIT:

	return(Status);
}
