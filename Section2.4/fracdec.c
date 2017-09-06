/*
ID: lizhita1
LANG: C
TASK: fracdec
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 100000

int nume, deco;
int rep[MAXNUM];
char ans[MAXNUM];

int main() {
    FILE *fin = fopen("fracdec.in", "r");
    fscanf(fin, "%d%d", &nume, &deco);
    fclose(fin);

    int len = 0;
    int divide = nume/deco;
    if (divide==0)
        ans[len++] = '0';
    while (divide>0) {
        ans[len++] = (char)(divide%10+'0');
        divide /= 10;
    }
    for (int i=0; i<len/2; ++i) {
        char temp = ans[i];
        ans[i] = ans[len-1-i];
        ans[len-1-i] = temp;
    }
        
    ans[len++] = '.';
    nume = nume%deco; 

    memset(rep, 0, sizeof(rep));
    rep[nume] = len;

    while (1) {
        nume *= 10;
        ans[len++] = (char)(nume/deco+'0');
        nume = nume%deco;
        if (nume==0) {
            ans[len] = '\0';
            break;
        }
        if (!rep[nume]) {
            rep[nume] = len;    
        }
        else {
            ans[len++] = ')';
            ans[len] = '\0';
            for (int i=len; i>=rep[nume]; --i)
                ans[i+1] = ans[i];
            ans[rep[nume]] = '(';
            break;
        }
    }

    FILE *fout = fopen("fracdec.out", "w");
    len = strlen(ans);
    for (int i=0; i<len; ++i) {
        fprintf(fout, "%c", ans[i]);
        if ((i+1)%76==0) 
            fprintf(fout, "\n");
    }
    if (len%76!=0)
        fprintf(fout, "\n");
    fclose(fout);
}
