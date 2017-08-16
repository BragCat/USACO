/*
ID: lizhita1
LANG: C
TASK: holstein
*/

#include <stdio.h>
#include <string.h>

#define MAX_INT 0x7fffffff
#define MAX_V 25
#define MAX_G 15

int v, g;
int require[MAX_V], provide[MAX_G][MAX_V];

int main() {
    FILE *fin = fopen("holstein.in", "r"); 
    fscanf(fin, "%d", &v);
    for (int i=0; i<v; ++i)
        fscanf(fin, "%d", &require[i]);
    fscanf(fin, "%d", &g);
    for (int i=0; i<g; ++i)
        for (int j=0; j<v; ++j)
            fscanf(fin, "%d", &provide[i][j]);
    fclose(fin);

    int ans = MAX_INT;
    int ansList[MAX_G];
    for (int combi=0; combi<(1<<g); ++combi) {
        int count[MAX_V];
        memset(count, 0, sizeof(count));
        int scoop = 0;
        for (int i=0; i<g; ++i)
            if (combi & (1<<i)) {
                ++scoop;
                for (int j=0; j<v; ++j)
                    count[j] += provide[i][j];
            }
        if (scoop>=ans)
            continue;
        int satis = 1;
        for (int i=0; i<v; ++i)
            if (require[i]>count[i]) {
                satis = 0;
                break;
            }
        if (satis) {
            ans = scoop;
            int index = 0;
            for (int i=0; i<g; ++i)
                if (combi & (1<<i))
                    ansList[index++] = i+1;
        }
    }

    FILE *fout = fopen("holstein.out", "w");
    fprintf(fout, "%d", ans);
    for (int i=0; i<ans; ++i)
        fprintf(fout, " %d", ansList[i]);
    fprintf(fout, "\n");
    fclose(fout);

    return 0;
}
