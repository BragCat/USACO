/*
ID: bragcat1
LANG: C
TASK: ratios
*/

#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

#define GRAIN_NUMBER 3
#define MIXTURE_NUMBER 3
#define MAX_UNIT 100

int main(void) {
    int goal[GRAIN_NUMBER], mixtures[MIXTURE_NUMBER][GRAIN_NUMBER];

    FILE *fin = fopen("ratios.in", "r");
    for (int i = 0; i < GRAIN_NUMBER; ++i) {
        fscanf(fin, "%d", &goal[i]);
    }
    for (int i = 0; i < MIXTURE_NUMBER; ++i) {
        for (int j = 0; j < GRAIN_NUMBER; ++j) {
            fscanf(fin, "%d", &mixtures[i][j]);
        }
    }
    fclose(fin);

    bool find = false;
    int barley, oats, wheat, multiple;
    for (int total = 1; total <= (MAX_UNIT - 1) * 3; ++total) {
        for (int i = 0; i <= total; ++i) {
            for (int j = 0; j <= total - i; ++j) {
                int k = total - i - j;
                int currentMixture[GRAIN_NUMBER];
                memset(currentMixture, 0, sizeof(currentMixture));
                for (int it = 0; it < GRAIN_NUMBER; ++it) {
                    currentMixture[it] += i * mixtures[0][it] + j * mixtures[1][it] + k * mixtures[2][it];
                }
                int divide = -1;
                bool isMultiple = true;
                for (int it = 0; it < GRAIN_NUMBER; ++it) {
                    if (goal[it] == 0 && currentMixture[it] == 0) {
                        continue;
                    }
                    if (goal[it] == 0 || currentMixture[it] == 0) {
                        isMultiple = false;
                        break;
                    }
                    if (currentMixture[it] % goal[it] == 0) {
                        if (divide == -1) {
                            divide = currentMixture[it] / goal[it];
                        }
                        else {
                            if (divide != currentMixture[it] / goal[it]) {
                                isMultiple = false;
                                break;
                            }
                        }
                    }
                    else {
                        isMultiple = false;
                        break;
                    }
                }
                if (isMultiple) {
                    find = true;
                    barley = i;
                    oats = j;
                    wheat = k;
                    multiple = divide;
                    break;
                }
            }
            if (find) {
                break;
            }
        }
        if (find) {
            break;
        }
    }

    FILE *fout = fopen("ratios.out", "w");
    if (find) {
        fprintf(fout, "%d %d %d %d\n", barley, oats, wheat, multiple);
    }
    else {
        fprintf(fout, "NONE\n");
    }
    fclose(fout);
    return 0;
}
