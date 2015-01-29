#ifndef XK_POPCNT_H
#define XK_POPCNT_H

#ifdef XK_HARD_POPCNT

/* use SSE4.2 popcnt (gcc builtin) */
#ifdef XK_64BIT
#define popcnt(x) __builtin_popcountll(x)
#else
#define popcnt(x) __builtin_popcount(x)
#endif


#else

/* software implementation of popcnt */
#include "popcnt_data.h"
#ifdef XK_64BIT
static int popcnt(uint64_t x)
{
    return popcnt_table[x & 0xffff] + popcnt_table[(x >> 16) & 0xffff] +
           popcnt_table[(x >> 32) & 0xffff] + popcnt_table[(x >> 48) & 0xffff];
}
#else
static int popcnt(uint32_t x)
{
    return popcnt_table[x & 0xffff] + popcnt_table[(x >> 16) & 0xffff];
}
#endif

#endif

#endif
