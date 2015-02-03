/*
 * This software is the work of Tom Lane, Guido Vollbeding, Philip Gladstone,
 * Bill Allombert, Jim Boucher, Lee Crocker, Bob Friesenhahn, Ben Jackson,
 * Julian Minguillon, Luis Ortiz, George Phillips, Davide Rossi, Ge' Weijers,
 * and other members of the Independent JPEG Group.
 */

#include <stdio.h>
#include <stddef.h>
#include <setjmp.h>
#include "jpeglib.h"
#include "xk.h"
#include "captcha.h"
#include "jpeg.h"

struct my_error_mgr {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};
typedef struct my_error_mgr * my_error_ptr;

static void output_message(j_common_ptr cinfo) {}

static void my_error_exit(j_common_ptr cinfo)
{
    my_error_ptr myerr = (my_error_ptr) cinfo->err;
    (*cinfo->err->output_message) (cinfo);
    longjmp(myerr->setjmp_buffer, 1);
}

int load_jpeg_captcha(xk_captcha p, void *buf, int len)
{
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;
    JSAMPARRAY buffer;
    int row_stride;
    
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;
    jerr.pub.output_message = output_message;
    if (setjmp(jerr.setjmp_buffer)) { /* error */
        jpeg_destroy_decompress(&cinfo);
        return -1;
    }
    
    jpeg_create_decompress(&cinfo);
    jpeg_mem_src(&cinfo, (unsigned char *) buf, len);
    jpeg_read_header(&cinfo, TRUE);
    cinfo.out_color_space = JCS_GRAYSCALE;
    jpeg_start_decompress(&cinfo);
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)
             ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    
    xk_captcha_clear(p);
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        xk_captcha_setrow(p, cinfo.output_scanline - 1, buffer[0], row_stride);
    }
    
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    
    return 0;
}

