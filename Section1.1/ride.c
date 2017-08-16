/*
ID: lizhita1
LANG: C
TASK: ride
*/

#include <stdio.h>

int main() {
    FILE *fin = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");
    
    const int modulus = 47;
    char ch;
    int comet = 1, group = 1;

    while ((ch=getc(fin))!='\n') 
        comet = (comet*(ch-'A'+1)) % modulus;
    while ((ch=getc(fin))!='\n') 
        group = (group*(ch-'A'+1)) % modulus;

    if (comet==group)
        fprintf(fout, "GO\n");
    else
        fprintf(fout, "STAY\n");

    fclose(fin);
    fclose(fout);
    return 0;
}
