#ifndef XK_CAPTCHA_H
#define XK_CAPTCHA_H

#include <stdint.h>
#include "xk.h"

/*
 * captcha char implementation
 * 
 * size: 24 rows, 10 cols
 * char row range: ch1 [3, 13) , ch2 [13, 23)
 *                 ch3 [23, 33), ch4 [33, 43)
 * array subscript:
 *   for 32 bit:      for 64 bit:
 *     6000000007       3000000003
 *     6000000007       3000000003
 *     6000000007       3000000003
 *     6000000007       3000000003
 *     6111111117       3000000003
 *     6111111117       3000000003
 *     6111111117       3000000003
 *     6111111117       3000000003
 *     6222222227       3111111113
 *     6222222227       3111111113
 *     6222222227       3111111113
 *     6222222227       3111111113
 *     6333333337       3111111113
 *     6333333337       3111111113
 *     6333333337       3111111113
 *     6333333337       3111111113
 *     6444444447       3222222223
 *     6444444447       3222222223
 *     6444444447       3222222223
 *     6444444447       3222222223
 *     6555555557       3222222223
 *     6555555557       3222222223
 *     6555555557       3222222223
 *     6555555557       3222222223
 *
 */

#define XK_CAPTCHA_THRESHOLD 200
#define XK_CAPTCHA_CHARDIFFINF (24 * 10 + 1)

#ifdef XK_64BIT
/* 64 bit implementation */
#define is_black(x) ((uint64_t) ((x) < XK_CAPTCHA_THRESHOLD))
typedef uint64_t xk_captcha_char[4];
#else
/* 32 bit implementation */
#define is_black(x) ((uint32_t) ((x) < XK_CAPTCHA_THRESHOLD))
typedef uint32_t xk_captcha_char[8];
#endif

typedef xk_captcha_char xk_captcha[4];

int xk_captcha_char_diff(const xk_captcha_char p1, const xk_captcha_char p2);
void xk_captcha_char_setrow(xk_captcha_char p, int row, unsigned char s[]);
void xk_captcha_shift_up(xk_captcha_char p);
void xk_captcha_shift_down(xk_captcha_char p);
void xk_captcha_clear(xk_captcha_char p[]);
void xk_captcha_setrow(xk_captcha_char p[], int row, unsigned char s[], int len);


#endif
