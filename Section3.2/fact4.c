/*
ID: lizhita1
LANG: C
TASK: fact4
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 4220

int n;

int main() {
    FILE *fin = fopen("fact4.in", "r");
    fscanf(fin, "%d", &n);
    fclose(fin);

    int ans = 1;
    int count = 0, p = 5;
    while (p<=n) {
        count += n/p;
        p *= 5; 
    }

    for (int i=2; i<=n; ++i) {
        ans *= i;
        while (ans%5==0)
            ans /= 5;
        while (count>0 && ans%2==0) {
            ans /= 2;
            --count; 
        }
        ans = ans%10;
    }

    FILE *fout = fopen("fact4.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);

    exit(0);
}
