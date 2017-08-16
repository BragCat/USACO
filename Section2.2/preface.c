/*
ID: lizhita1
LANG: C
TASK: preface
*/

#include <stdio.h>
#include <string.h>

const int romanNum[7] = {1, 5, 10, 50, 100, 500, 1000};
const char romanChar[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

int n;
int ans[7];

void calc_roman_digit(int num) {
    int digitCount = 0;
    while (num>0) {
        int digit = num%10;
        int romanCnt[3];

        memset(romanCnt, 0, sizeof(romanCnt));
        if (digit<=3)
            romanCnt[0] += digit;
        else if (digit<=5) {
            ++romanCnt[1];
            romanCnt[0] += 5-digit;
        }
        else if (digit<=8) {
            ++romanCnt[1];
            romanCnt[0] += digit-5;
        }
        else {
            ++romanCnt[2];
            ++romanCnt[0]; 
        }

        for (int i=0; i<3; ++i)
            ans[digitCount+i] += romanCnt[i];
        
        num = num/10;
        digitCount += 2;
    }
}

int main() {
    FILE *fin = fopen("preface.in", "r");
    fscanf(fin, "%d", &n);
    fclose(fin);

    memset(ans, 0, sizeof(ans));
    for (int i=1; i<=n; ++i)
        calc_roman_digit(i);

    FILE *fout = fopen("preface.out", "w");
    for (int i=0; i<7; ++i)
        if (ans[i])
            fprintf(fout, "%c %d\n", romanChar[i], ans[i]);
        else
            break;
    fclose(fout);
    return 0;
}
