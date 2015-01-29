#include <string.h>
#include "xk.h"
#include "jpeg.h"
#include "captcha.h"
#include "ocr.h"

#ifdef XK_64BIT
#include "ocr_data64.h"
#else
#include "ocr_data.h"
#endif

int ocr_char(const xk_captcha_char p, int ch, char *ret)
{
    int i;
    int len = dict_len[ch];
    const char *val = dict_val[ch];
    const xk_captcha_char *dict = dict_ptr[ch];
    int diff, mindiff = XK_CAPTCHA_CHARDIFFINF;
    for (i = 0; i < len; i++) {
        diff = xk_captcha_char_diff(p, dict[i]);
        if (diff < mindiff) {
            mindiff = diff;
            *ret = val[i];
        }
    }
    return mindiff;
}

int ocr_captcha(xk_captcha p, char ret[])
{
    int ch;
    int diff, mindiff, maxdiff = 0;
    char tch = 0;
    xk_captcha_char t;
    
    for (ch = 0; ch < 4; ch++) {
        mindiff = ocr_char(p[ch], ch, &ret[ch]);

        memcpy(t, p[ch], sizeof(xk_captcha_char));
        xk_captcha_shift_up(t);
        diff = ocr_char(t, ch, &tch);
        if (diff < mindiff) {
            mindiff = diff;
            ret[ch] = tch;
        }
        
        memcpy(t, p[ch], sizeof(xk_captcha_char));
        xk_captcha_shift_down(t);
        diff = ocr_char(t, ch, &tch);
        if (diff < mindiff) {
            mindiff = diff;
            ret[ch] = tch;
        }
        
        if (mindiff > maxdiff)
            maxdiff = mindiff;
    }
    
    return maxdiff;
}

int ocr_jpeg(void *buf, int len, char ret[])
{
    xk_captcha p;
    int r = load_jpeg_captcha(p, buf, len);
    return r < 0 ? r : ocr_captcha(p, ret);
}

