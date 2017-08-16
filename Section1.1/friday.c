/*
ID: lizhita1
LANG: C
PROG: friday
*/

#include <stdio.h>
#include <string.h>

int main() {
    int n;
    int count[7];
    int month, weekday, year, delta;
    int i;
    
    FILE *fin = fopen("friday.in", "r");
    FILE *fout = fopen("friday.out", "w");

    fscanf(fin, "%d", &n);

    year = 1900;
    month = 1;
    weekday = 6;
    memset(count, 0, sizeof(count));    

    while (n>0) {
        --n;
        while (month<=12) {
            ++count[weekday];
            switch (month) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
                    delta = 31; break;
                case 4: case 6: case 9: case 11: 
                    delta = 30; break;
                case 2: 
                    if (year%400==0)
                        delta = 29;
                    else if (year%100==0)
                        delta = 28;
                    else if (year%4==0)
                        delta = 29;
                    else 
                        delta = 28;
            }
            ++month;
            weekday = (weekday+delta)%7;
        }
        month = 1;
        ++year;
    }

    fprintf(fout, "%d %d", count[6], count[0]);
    for (i=1; i<6; ++i)
        fprintf(fout, " %d", count[i]);
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);

    return 0;
}
