/*
ID: lizhita1
LANG: C
TASK: barn1
*/

#include <stdio.h>

#define min(a, b) ((a<b)?a:b)

const int MAX_M = 50, MAX_S = 200;

void sort(int array[], int l, int r, int ascend) {
    int mid = l+(r-l)/2;
    int cmpNum = array[mid]*ascend;
    int i = l, j = r;
    while (i<=j) {
        while (array[i]*ascend<cmpNum) ++i;
        while (array[j]*ascend>cmpNum) --j;
        if (i<=j) {
            int t = array[i];
            array[i] = array[j];
            array[j] = t;
            ++i;
            --j;
        }
    }
    if (j>l)
        sort(array, l, j, ascend);
    if (i<r) 
        sort(array, i, r, ascend);
}

int main() {
    int m, s, c, i, ans;
    int stallNum[MAX_S], deltaNum[MAX_S];

    FILE *fin = fopen("barn1.in", "r");
    fscanf(fin, "%d%d%d", &m, &s, &c);
    for (i=0; i<c; ++i)
        fscanf(fin, "%d", &stallNum[i]);
    fclose(fin);

    sort(stallNum, 0, c-1, 1);

    ans = stallNum[c-1]-stallNum[0]+1;

    for (i=0; i<c-1; ++i)
        deltaNum[i] = stallNum[i+1]-stallNum[i]-1;

    sort(deltaNum, 0, c-2, -1);

    for (i=0; i<min(m-1, c-1); ++i)
        ans -= deltaNum[i];

    FILE *fout = fopen("barn1.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    return 0;
}
