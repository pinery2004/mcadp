//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsJpeg.cpp
//
//		JPEG�t�@�C���̓ǂݏ���
//
//
//  K.Matsu           11/17/07    Created.
//==========================================================================================
#include "stdafx.h"
#include "MbBasic.h"

#include "afxdlgs.h"

/*
 * example.c
 *
 * This file illustrates how to use the IJG code as a subroutine library
 * to read or write JPEG image files.  You should look at this code in
 * conjunction with the documentation file libjpeg.doc.
 *
 * This code will not do anything useful as-is, but it may be helpful as a
 * skeleton for constructing routines that call the JPEG library.  
 *
 * We present these routines in the same coding style used in the JPEG code
 * (ANSI function definitions, etc); but you are of course free to code your
 * routines in a different style if you prefer.
 */

#include <stdio.h>

/*
 * Include file for users of JPEG library.
 * You will need to have included system headers that define at least
 * the typedefs FILE and size_t before you can include jpeglib.h.
 * (stdio.h is sufficient on ANSI-conforming systems.)
 * You may also wish to include "jerror.h".
 */

#include "cdjpeg.h"																// IJG �w�b�_�t�@�C��
#include "jpeglib.h"

/*
 * <setjmp.h> is used for the optional error recovery mechanism shown in
 * the second part of the example.
 */

#include <setjmp.h>

#include "MsJpegLib.h"

/******************** JPEG COMPRESSION SAMPLE INTERFACE *******************/

/* This half of the example shows how to feed data into the JPEG compressor.
 * We present a minimal version that does not worry about refinements such
 * as error recovery (the JPEG code will just exit() if it gets an error).
 */


/*
 * IMAGE DATA FORMATS:
 *
 * The standard input image format is a rectangular array of pixels, with
 * each pixel having the same number of "component" values (color channels).
 * Each pixel row is an array of JSAMPLEs (which typically are unsigned chars).
 * If you are working with color data, then the color values for each pixel
 * must be adjacent in the row; for example, R,G,B,R,G,B,R,G,B,... for 24-bit
 * RGB color.
 *
 * For this example, we'll assume that this data structure matches the way
 * our application has stored the image in memory, so we can just pass a
 * pointer to our image buffer.  In particular, let's say that the image is
 * RGB color and is described by:
 */

// extern JSAMPLE * image_buffer;	/* Points to large array of R,G,B-order data */
// extern int image_height;	/* Number of rows in image */
// extern int image_width;		/* Number of columns in image */
//
////HHHH
///////////////////////////////////////////////////////////////
//// JPEG�t�@�C����������
//GLOBAL(void)
//write_JPEG_file (char * filename, int quality)
//{
//	MINT	ist;
//
//	FILE *	outfile;
//	int		row_stride;							// physical row width in image buffer
//	struct jpeg_compress_struct	cinfo;
//	struct jpeg_error_mgr		jerr;
//	JSAMPROW row_pointer[1];					// pointer to JSAMPLE row[s]
//
// 	// ������
//	cinfo.err = jpeg_std_error( &jerr);
//	jpeg_create_compress( &cinfo);
//
//	if (( ist = fopen_s( &outfile, filename, "wb")) != 0) {
//		fprintf(stderr, "can't open %s\n", filename);
//		exit(1);
//	}
//	jpeg_stdio_dest( &cinfo, outfile);
//
//	cinfo.image_width = image_width; 	/* image width and height, in pixels */
//	cinfo.image_height = image_height;
//	cinfo.input_components = 3;		/* # of color components per pixel */
//	cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
//
//	// ���k�p�����[�^�ݒ�
//	jpeg_set_defaults( &cinfo);
// 	jpeg_set_quality( &cinfo, quality, TRUE /* limit to baseline-JPEG values */);
//
//	// ���k�����J�n
//	jpeg_start_compress( &cinfo, TRUE);
//
//	// �o��
//	row_stride = image_width * 3;	/* JSAMPLEs per row in image_buffer */
//
//	while (cinfo.next_scanline < cinfo.image_height) {
//		row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
//		(void) jpeg_write_scanlines( &cinfo, row_pointer, 1);
//	}
//
//	// ���k�I��
//	jpeg_finish_compress( &cinfo);
//	jpeg_destroy_compress( &cinfo);
//	fclose(outfile);
//}


/*
 * SOME FINE POINTS:
 *
 * In the above loop, we ignored the return value of jpeg_write_scanlines,
 * which is the number of scanlines actually written.  We could get away
 * with this because we were only relying on the value of cinfo.next_scanline,
 * which will be incremented correctly.  If you maintain additional loop
 * variables then you should be careful to increment them properly.
 * Actually, for output to a stdio stream you needn't worry, because
 * then jpeg_write_scanlines will write all the lines passed (or else exit
 * with a fatal error).  Partial writes can only occur if you use a data
 * destination module that can demand suspension of the compressor.
 * (If you don't know what that's for, you don't need it.)
 *
 * If the compressor requires full-image buffers (for entropy-coding
 * optimization or a multi-scan JPEG file), it will create temporary
 * files for anything that doesn't fit within the maximum-memory setting.
 * (Note that temp files are NOT needed if you use the default parameters.)
 * On some systems you may need to set up a signal handler to ensure that
 * temporary files are deleted if the program is interrupted.  See libjpeg.doc.
 *
 * Scanlines MUST be supplied in top-to-bottom order if you want your JPEG
 * files to be compatible with everyone else's.  If you cannot readily read
 * your data in that order, you'll need an intermediate array to hold the
 * image.  See rdtarga.c or rdbmp.c for examples of handling bottom-to-top
 * source data using the JPEG code's internal virtual-array mechanisms.
 */



/******************** JPEG DECOMPRESSION SAMPLE INTERFACE *******************/

/* This half of the example shows how to read data from the JPEG decompressor.
 * It's a bit more refined than the above, in that we show:
 *   (a) how to modify the JPEG library's standard error-reporting behavior;
 *   (b) how to allocate workspace using the library's memory manager.
 *
 * Just to make this example a little different from the first one, we'll
 * assume that we do not intend to put the whole image into an in-memory
 * buffer, but to send it line-by-line someplace else.  We need a one-
 * scanline-high JSAMPLE array as a work buffer, and we will let the JPEG
 * memory manager allocate it for us.  This approach is actually quite useful
 * because we don't need to remember to deallocate the buffer separately: it
 * will go away automatically when the JPEG object is cleaned up.
 */


/*
 * ERROR HANDLING:
 *
 * The JPEG library's standard error handler (jerror.c) is divided into
 * several "methods" which you can override individually.  This lets you
 * adjust the behavior without duplicating a lot of code, which you might
 * have to update with each future release.
 *
 * Our example here shows how to override the "error_exit" method so that
 * control is returned to the library's caller when a fatal error occurs,
 * rather than calling exit() as the standard error_exit method does.
 *
 * We use C's setjmp/longjmp facility to return control.  This means that the
 * routine which calls the JPEG library must first execute a setjmp() call to
 * establish the return point.  We want the replacement error_exit to do a
 * longjmp().  But we need to make the setjmp buffer accessible to the
 * error_exit routine.  To do this, we make a private extension of the
 * standard JPEG error handler object.  (If we were using C++, we'd say we
 * were making a subclass of the regular error handler.)
 *
 * Here's the extended error handler struct:
 */

struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */

	jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
	(*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}
//U
///////////////////////////////////////////////////////////////
//// JPEG�t�@�C���ǂݍ���
//GLOBAL(int)
//MsReadJpegFile(									// �X�e�[�^�X (0:����AMC_E_IO:JPEG�t�@�C�������
//						MCHAR*	i_cFileName		// JPEG�t�@�C����
//				)
//{
//	MINT	iSt;
//	struct	jpeg_decompress_struct cinfo;
//	struct	my_error_mgr jerr;
//	FILE* 	infile;								// source file
//	JSAMPARRAY buffer;							// Output row buffer
//	int		row_stride;							// physical row width in output buffer
//
//	if (( iSt = _tfopen_s( &infile, i_cFileName, Mstr( "rb"))) != 0) {
//		MQUIT_STS( MC_E_IO);
//	}
//
//	// ������
//  	cinfo.err = jpeg_std_error( &jerr.pub);
//	jerr.pub.error_exit = my_error_exit;
//
//	if ( setjmp( jerr.setjmp_buffer)) {
//		jpeg_destroy_decompress( &cinfo);
//		fclose( infile);
//		return 0;
//	}
//  /* Now we can initialize the JPEG decompression object. */
//	jpeg_create_decompress( &cinfo);
//
//  /* Step 2: specify data source (eg, a file) */
//
//	jpeg_stdio_src( &cinfo, infile);
//
//  /* Step 3: read file parameters with jpeg_read_header() */
//
//	(void) jpeg_read_header( &cinfo, TRUE);
//  /* We can ignore the return value from jpeg_read_header since
//   *   (a) suspension is not possible with the stdio data source, and
//   *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
//   * See libjpeg.doc for more info.
//   */
//
//  /* Step 4: set parameters for decompression */
//
//  /* In this example, we don't need to change any of the defaults set by
//   * jpeg_read_header(), so we do nothing here.
//   */
//
//  /* Step 5: Start decompressor */
//
//	(void) jpeg_start_decompress( &cinfo);
//  /* We can ignore the return value since suspension is not possible
//   * with the stdio data source.
//   */
//
//  /* We may need to do some setup of our own at this point before reading
//   * the data.  After jpeg_start_decompress() we have the correct scaled
//   * output image dimensions available, as well as the output colormap
//   * if we asked for color quantization.
//   * In this example, we need to make an output work buffer of the right size.
//   */ 
//  /* JSAMPLEs per row in output buffer */
//	row_stride = cinfo.output_width * cinfo.output_components;
//  /* Make a one-row-high sample array that will go away when done with image */
//	buffer = (*cinfo.mem->alloc_sarray)
//		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
//
//  /* Step 6: while (scan lines remain to be read) */
//  /*           jpeg_read_scanlines(...); */
//
//  /* Here we use the library's state variable cinfo.output_scanline as the
//   * loop counter, so that we don't have to keep track ourselves.
//   */
//	while (cinfo.output_scanline < cinfo.output_height) {
//		(void) jpeg_read_scanlines( &cinfo, buffer, 1);
////		put_scanline_someplace(buffer[0], row_stride);
//	}
//
//	// �I������
//	(void) jpeg_finish_decompress( &cinfo);
//	jpeg_destroy_decompress( &cinfo);
//	fclose( infile);
//	iSt = 0;
//
//exit:
//	return iSt;
//}
