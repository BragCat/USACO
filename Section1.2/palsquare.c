/*
ID: lizhita1
LANG: C
TASK: palsquare
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_N = 300;
const int MAX_LEN = 18;

char * change_base(int num, int base) {
    char *result = (char *)malloc(MAX_LEN);
    int len = 0;
    memset(result, 0, MAX_LEN);
    while (num>0) {
        int digit = num%base;
        if (digit<10)
            result[len] = '0'+digit;
        else
            result[len] = 'A'+digit-10;
        ++len;
        num /= base;
    }
    result[len] = '\0';
    return result;
}

int is_palin(char *num) {
    int left = 0, right = strlen(num)-1;
    while (left<right) {
        if (num[left]!=num[right])
            return 0;
        ++left;
        --right;
    }
    return 1;
}

void reverse(char *number) {
    int left = 0, right = strlen(number)-1;
    while (left<right) {
        char temp = number[left];
        number[left] = number[right];
        number[right] = temp;
        ++left;
        --right;
    }
}

int main() {
    int base, i, j;

    FILE *fin = fopen("palsquare.in", "r");
    FILE *fout = fopen("palsquare.out", "w");

    fscanf(fin, "%d", &base);
    fclose(fin);

    for (i=1; i<=MAX_N; ++i) {
        char *square = change_base(i*i, base);
        if (is_palin(square)) {
            char *number = change_base(i, base);
            reverse(number);
            fprintf(fout, "%s %s\n", number, square);
        }
        free(square);
    }

    fclose(fout);
    return 0;
}
