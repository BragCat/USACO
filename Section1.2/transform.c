/*
ID: lizhita1
LANG: C
PROG: transform
*/

#include <stdio.h>

const int MAX_N = 10;

void read_square(FILE *fin, int n, char square[][MAX_N]) {
    int i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j)
            square[i][j] = getc(fin);
        getc(fin);
    }
}

void copy(int n, char src[][MAX_N], char dst[][MAX_N]) {
    int i, j;
    for (i=0; i<n; ++i)
        for (j=0; j<n; ++j)
            dst[i][j] = src[i][j];
}

void rotate(int n, char src[][MAX_N], char dst[][MAX_N]) {
    int i, j;
    char temp[MAX_N][MAX_N];
    copy(n, src, temp);
    for (i=0; i<n; ++i)
        for (j=0; j<n; ++j)
            dst[j][n-1-i] = temp[i][j];
}

void reflect(int n, char src[][MAX_N], char dst[][MAX_N]) {
    int i, j;
    char temp[MAX_N][MAX_N];
    copy(n, src, temp);
    for (i=0; i<n; ++i)
        for (j=0; j<n; ++j)
            dst[i][n-1-j] = temp[i][j];
}

int isSame(int n, char sqA[][MAX_N], char sqB[][MAX_N]) {
    int i, j;
    for (i=0; i<n; ++i)
        for (j=0; j<n; ++j)
            if (sqA[i][j]!=sqB[i][j])
                return 0;
    return 1;
}

int try_transform(int n, char before[][MAX_N], char after[][MAX_N]) {
    int i, j;
    char change[MAX_N][MAX_N];
    
    copy(n, before, change);
    for (i=1; i<=3; ++i) {
        rotate(n, change, change);
        if (isSame(n, change, after))
            return i;
    }
    reflect(n, before, change);
    if (isSame(n, change, after))
        return 4;
    for (int i=1; i<=3; ++i) {
        rotate(n, change, change);
        if (isSame(n, change, after))
            return 5;
    }
    if (isSame(n, before, after))
        return 6;
    return 7;
}

int main() {
    int n, i, j;
    char before[MAX_N][MAX_N], after[MAX_N][MAX_N];

    FILE *fin = fopen("transform.in", "r");
    FILE *fout = fopen("transform.out", "w");

    fscanf(fin, "%d", &n);
    getc(fin);
    read_square(fin, n, before);
    read_square(fin, n, after);

    fprintf(fout, "%d\n", try_transform(n, before, after));

    fclose(fin);
    fclose(fout);
    return 0;
}
