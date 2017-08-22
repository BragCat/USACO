/*
ID: lizhita1
LANG: C
TASK: prefix
*/

#include <stdio.h>
#include <string.h>

#define MAXS 200000
#define MAXL 10
#define MAXP 200

int lenS, numP;
int composed[MAXS+1];
char prim[MAXP+1][MAXL+1];
char seq[MAXS+1];

int main() {
    FILE *fin = fopen("prefix.in", "r");
    numP = 0;
    while (1) {
        fscanf(fin, "%s", prim[numP]);
        if (prim[numP][0]=='.')
            break;
        else 
            ++numP;
    }	
    lenS = 0;
    while (fscanf(fin, "%s", seq+lenS)==1) 
        lenS += strlen(seq+lenS);
    fclose(fin);

    composed[0] = 1;
    int ans = 0;
    for (int i=0; i<=lenS; ++i)
        if (composed[i]) {
            ans = i;
            for (int j=0; j<numP; ++j)   
                if (i+strlen(prim[j])<=lenS) {
                    int same = 1;
                    for (int k=0; k<strlen(prim[j]); ++k)
                        if (prim[j][k]!=seq[i+k]) {
                            same = 0;
                            break;
                        }
                    if (same)
                        composed[i+strlen(prim[j])] = 1;
                }
        }
    
    FILE *fout = fopen("prefix.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
}
