/*
ID: lizhita1
LANG: C
TASK: dualpal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_N = 15;
const int MAX_BASE = 10;
const int MIN_BASE = 2;
const int MAX_LEN = 32;

int is_pali(int num, int base) {
    int *newNum = (int *)calloc(MAX_LEN, sizeof(int));
    int len = 0;
    int left, right;

    while (num>0) {
        newNum[len++] = num%base;
        num /= base;
    }

    --len;
    left = 0;
    right = len;
    while (left<right) 
        if (newNum[left++]!=newNum[right--]) {
            free(newNum);
            return 0;
        }
    
    free(newNum);
    return 1;
}

int main() {
    int n, s, num, base;

    FILE *fin = fopen("dualpal.in", "r");
    fscanf(fin, "%d%d", &n, &s);
    fclose(fin);

    num = s;
    FILE *fout = fopen("dualpal.out", "w");
    while (n>0) {
        int count = 0;
        ++num;
        for (base=MIN_BASE; base<=MAX_BASE; ++base) 
            if (is_pali(num, base)) {
                ++count;
                if (count>=2)
                    break;
            }
        if (count>=2) {
            --n;
            fprintf(fout, "%d\n", num);
        }
    }
    fclose(fout);

    return 0;
}

