#include <stdio.h>
#include "ocr.h"

void ocr_file(char *fn)
{
    char ans[5];
    char buf[5000];
    FILE *f = fopen(fn, "rb");
    int len = fread(buf, 1, sizeof(buf), f);
    fclose(f);
    ocr_jpeg(buf, len, ans);
    ans[4] = '\0';
    printf("%s\n", ans);
}

int main(int argc, char *argv[])
{
    if (argc < 2) { puts("no filename!"); return 0; }
    ocr_file(argv[1]);
    return 0;
}
