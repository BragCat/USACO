/*
ID: lizhita1
LANG: C
TASK: frac1
*/

#include <stdio.h>

#define MAX_N 160

struct Fraction {
    int num, den;
} fractions[MAX_N*MAX_N];

int n;

int gcd(int a, int b) {
    if (a%b==0)
        return b;
    else 
        return gcd(b, a%b);
}

int less(struct Fraction a, struct Fraction b) {
    int denA = a.den, denB = b.den;
    if (denA<denB) {
        int t = denA;
        denA = denB;
        denB = t;
    }
    int cd = gcd(denA, denB);
    int cm = denA*denB/cd;
    int numA = a.num*cm/a.den;
    int numB = b.num*cm/b.den;
    return (numA<numB);
}

void sort(int l, int r) {
    int mid = l+(r-l)/2;
    struct Fraction cmpFrac = fractions[mid];
    int i = l, j = r;
    while (i<=j) {
        while (less(fractions[i], cmpFrac)) ++i;
        while (less(cmpFrac, fractions[j])) --j;
        if (i<=j) {
            struct Fraction temp = fractions[i];
            fractions[i] = fractions[j];
            fractions[j] = temp;
            ++i;
            --j;
        }
    }
    if (j>l)
        sort(l, j);
    if (i<r)
        sort(i, r);
}

int main() {
    int fracNum = 0;
    FILE *fin = fopen("frac1.in", "r");
    fscanf(fin, "%d", &n);
    fclose(fin);

    fractions[0].num = 0, fractions[0].den = 1; 
    fractions[1].num = 1, fractions[1].den = 1;
    fracNum = 2;
    for (int i=1; i<=n; ++i)
        for (int j=1; j<i; ++j)
            if (gcd(i, j)==1)
                fractions[fracNum].num = j, fractions[fracNum++].den = i;

    sort(0, fracNum-1);

    FILE *fout = fopen("frac1.out", "w");
    for (int i=0; i<fracNum; ++i)
        fprintf(fout, "%d/%d\n", fractions[i].num, fractions[i].den);
    fclose(fout);
    return 0;
}
