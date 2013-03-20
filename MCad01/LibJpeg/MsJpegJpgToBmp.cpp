/******************************************************************************************************************
[ �@�\ ] JPEG�t�@�C����BMAP�t�H�[�}�b�g�ɕϊ�
[ �Ԓl ] �X�e�[�^�X        0 : ����     -1 : �ُ�
******************************************************************************************************************/
#include "stdafx.h"
#define			 XMD_H																	/* X11/xmd.h correctly defines INT32 */

#include		"cdjpeg.h"																// IJG �w�b�_�t�@�C��
#include		"MbBasic.h"
#include		"MsJpegLib.h"

//HHHH
MINT MsJpegJpgToBmp            (														// (  O) �ð��
								MCHAR*				FLName1,							// (I  ) �ϊ����摜̧�ٖ�
								MCHAR*				FLName2,							// (I  ) �ϊ���摜̧�ٖ�
								MINT				MFlag,								// (I  ) 1:���E�װ
								MREAL				Scale,								// (I  ) �摜���ނ̏k����
								MUINT				Colors,								// (I  ) �F���i==0�F�팸���Ȃ��j
								MUINT				DitherOpt)							// (I  ) �ި���ݸނ̎��
{
	MINT							Status;
	struct jpeg_decompress_struct	CInfo;												// JPEG�L�������Ұ����܂ލ\����
	PiIjgErrorMgr					JpErr;												// IJG �̴װ�� DigiD �ɕԂ��d�g��
	djpeg_dest_ptr					DstMgr;												// ���̓t�@�C���̊Ǘ��p�\����
	FILE*							InFile;												// ����̧���߲��
	FILE*							OutFile;											// �o��̧���߲��
	JDIMENSION						NScan;												//


	Status = -1;

	// �t�@�C�����J��
	if ( ( InFile = Mfopen( FLName1, READ_BINARY)) == NULL)
		goto  PRG_EXIT;

	if ( ( OutFile = Mfopen(FLName2, WRITE_BINARY)) == NULL) {
		fclose(InFile);
		goto  PRG_EXIT;
	}


	// �G���[�����̏�����
	CInfo.err = jpeg_std_error(&JpErr.pub);
	JpErr.pub.error_exit = MsJpegErrExit;												// �װ������u������
	if (setjmp(JpErr.setjmp_buffer)) {													// �װ����ٔ���
		jpeg_destroy_decompress(&CInfo);
		fclose(InFile); fclose(OutFile);
		goto  PRG_EXIT;
	}

	jpeg_create_decompress(&CInfo);														// JPEG�L���̂��߂����Ұ���������


	jpeg_stdio_src(&CInfo, InFile);														// ���͌�̧�ق�ݒ�
	(void)jpeg_read_header(&CInfo, TRUE);												// ̧��ͯ�ނ�Ǎ���

	// �X�P�[��  �����Ŏw�肳�ꂽ�l���A1/1�A1/2�A1/4�A1/8�̂����ꂩ�ɋߎ�
	if (Scale <= (MREAL)0.1875 ) {														// 1/8
		CInfo.scale_num   = 1;
		CInfo.scale_denom = 8;	
	} else if ( Scale <= (MREAL)0.375) {												// 1/4
		CInfo.scale_num   = 1;
		CInfo.scale_denom = 4;
	} else if ( Scale <= (MREAL)0.75) {													// 1/2
		CInfo.scale_num   = 1;
		CInfo.scale_denom = 2;
	} else {																			// 1/1
		CInfo.scale_num   = 1;
		CInfo.scale_denom = 1;
	}

	// �F���̍팸�i�ʎq���j
	if (Colors > 0) {
		CInfo.quantize_colors          = TRUE;
		CInfo.desired_number_of_colors = Colors;
	}

	// �f�B�U�����O�̎w��
	if (DitherOpt == HJPDTORD) {														// �����ݸޕ���
		CInfo.dither_mode = JDITHER_ORDERED;
	} else if (DitherOpt == HJPDTFS) {													// �۲�ޥ������ٸޕ���
		CInfo.dither_mode = JDITHER_FS;			
	} else {																			// �ި���ݸނ��s��Ȃ��i����`�̒l���܂ށj
		CInfo.dither_mode = JDITHER_NONE;
	}

	// �o�̓t�@�C���̏���
	DstMgr = jinit_write_bmp(&CInfo,FALSE);

	DstMgr->output_file = OutFile;

	// �L�������J�n
	(void) jpeg_start_decompress(&CInfo);

	// �ް��o��
	(*DstMgr->start_output) (&CInfo, DstMgr);											// �o��̧�ق�ͯ�ޏ����o��

	while (CInfo.output_scanline < CInfo.output_height) {
		NScan = jpeg_read_scanlines(&CInfo, DstMgr->buffer, DstMgr->buffer_height);
		(*DstMgr->put_pixel_rows) (&CInfo, DstMgr, NScan, MFlag);
	}

	// �I�������������؂̉��
	(*DstMgr->finish_output) (&CInfo, DstMgr);
	(void) jpeg_finish_decompress(&CInfo);
	jpeg_destroy_decompress(&CInfo);


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
