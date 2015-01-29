#include <string.h>
#include "xk.h"
#include "captcha.h"
#include "popcnt.h"

#ifdef XK_64BIT
/* 64 bit implementation */
int xk_captcha_char_diff(const xk_captcha_char p1, const xk_captcha_char p2)
{
    int i, ret = 0;
    for (i = 0; i < 4; i++)
        ret += popcnt(p1[i] ^ p2[i]);
    return ret;
}

void xk_captcha_char_setrow(xk_captcha_char p, int row, unsigned char s[])
{
    int i;
    uint64_t t = 0;
    for (i = 0; i < 8; i++)
        t |= is_black(s[i + 1]) << i;
    p[row / 8] |= t << ((row % 8) * 8);
    p[3] |= is_black(s[0]) << row;
    p[3] |= is_black(s[9]) << (row + 24);
}

void xk_captcha_shift_up(xk_captcha_char p)
{
    int i;
    p[0] >>= 8;
    for (i = 1; i < 3; i++) {
        p[i - 1] |= p[i] << 56;
        p[i] >>= 8;
    }
    p[3] >>= 1;
    p[3] &= ~((uint64_t) 1 << 23);
}

void xk_captcha_shift_down(xk_captcha_char p)
{
    int i;
    for (i = 2; i > 0; i--) {
        p[i] <<= 8;
        p[i] |= p[i - 1] >> 56;
    }
    p[0] <<= 8;
    p[3] <<= 1;
    p[3] &= ~((uint64_t) 1 << 24);
}
#else
/* 32 bit implementation */
int xk_captcha_char_diff(const xk_captcha_char p1, const xk_captcha_char p2)
{
    int i, ret = 0;
    for (i = 0; i < 8; i++)
        ret += popcnt(p1[i] ^ p2[i]);
    return ret;
}

void xk_captcha_char_setrow(xk_captcha_char p, int row, unsigned char s[])
{
    int i;
    uint32_t t = 0;
    for (i = 0; i < 8; i++)
        t |= is_black(s[i + 1]) << i;
    p[row / 4] |= t << ((row % 4) * 8);
    p[6] |= is_black(s[0]) << row;
    p[7] |= is_black(s[9]) << row;
}

void xk_captcha_shift_up(xk_captcha_char p)
{
    int i;
    p[0] >>= 8;
    for (i = 1; i < 6; i++) {
        p[i - 1] |= p[i] << 24;
        p[i] >>= 8;
    }
    p[6] >>= 1;
    p[7] >>= 1;
}

void xk_captcha_shift_down(xk_captcha_char p)
{
    int i;
    for (i = 5; i > 0; i--) {
        p[i] <<= 8;
        p[i] |= p[i - 1] >> 24;
    }
    p[0] <<= 8;
    p[6] = (p[6] << 1) & 0xffffff;
    p[7] = (p[7] << 1) & 0xffffff;
}
#endif


void xk_captcha_clear(xk_captcha_char p[])
{
    int ch;
    for (ch = 0; ch < 4; ch++)
        memset(p[ch], 0, sizeof(xk_captcha_char));
}

void xk_captcha_setrow(xk_captcha_char p[], int row, unsigned char s[], int len)
{
    const static int c[] = {3, 13, 23, 33};
    int ch;
    for (ch = 0; ch < 4; ch++)
        xk_captcha_char_setrow(p[ch], row, s + c[ch]);
}

