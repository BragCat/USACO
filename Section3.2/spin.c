/*
ID: bragcat1
LANG: C
TASK: spin
*/

#include <stdio.h>
#include <memory.h>

#define N 5
#define MAXW 5
#define TOTAL_ANGLE 360

int start[N][MAXW], extend[N][MAXW];
int velocity[N], wedgeNumber[N];

int main(void) {
    FILE *fin = fopen("spin.in", "r");
    for (int i = 0; i < N; ++i) {
        fscanf(fin, "%d%d", &velocity[i], &wedgeNumber[i]);
        for (int j = 0; j < wedgeNumber[i]; ++j) {
            fscanf(fin, "%d%d", &start[i][j], &extend[i][j]);
        }
    }
    fclose(fin);

    int answer = -1;
    for (int t = 0; t < 360; ++t) {
        int angles[TOTAL_ANGLE];
        memset(angles, 0, sizeof(angles));
        for (int i = 0; i < N; ++i) {
            int rotateAngle = t * velocity[i];
            for (int j = 0; j < wedgeNumber[i]; ++j) {
                for (int k = start[i][j] + rotateAngle; k <= start[i][j] + extend[i][j] + rotateAngle; ++k) {
                    ++angles[k % TOTAL_ANGLE];
                }
            }
        }
        for (int i = 0; i < TOTAL_ANGLE; ++i) {
            if (angles[i] == N) {
                answer = t;
                break;
            }
        }
        if (answer != -1) {
            break;
        }
    }

    FILE *fout = fopen("spin.out", "w");
    if (answer == -1) {
        fprintf(fout, "none\n");
    }
    else {
        fprintf(fout, "%d\n", answer);
    }
    fclose(fout);
    return 0;
}
