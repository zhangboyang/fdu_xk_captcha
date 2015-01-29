#include <stdio.h>
#include "ocr.h"

void ocr_file(char *fnp, int id)
{
    char ans[5];
    char buf[5000];
    char fn[1000];
    FILE *f;
    int len;
    sprintf(fn, fnp, id);
    f = fopen(fn, "rb");
    len = fread(buf, 1, sizeof(buf), f);
    fclose(f);
    ocr_jpeg(buf, len, ans);
    ans[4] = '\0';
    printf("%d %s\n", id, ans);
}

int main()
{
    int i;
    for (i = 1; i <= 50000; i++)
        ocr_file("../../test/testdata/%d.jpg", i);
    return 0;
}
