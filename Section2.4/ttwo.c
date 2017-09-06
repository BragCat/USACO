/*
ID: lizhita1
LANG: C
TASK: ttwo
 */

#include <stdio.h>
#include <string.h>

#define SQ_LEN 10

char map[SQ_LEN][SQ_LEN];
int happened[SQ_LEN*SQ_LEN*4][SQ_LEN*SQ_LEN*4];
int fx, fy, fd, cx, cy, cd;

void move(int *px, int *py, int *pd) {
    switch (*pd) {
        case 0: //north
            if (*px==0 || map[*px-1][*py]=='*') 
                *pd = 1;
            else 
                --(*px);
            break;
        case 1: //east
            if (*py==SQ_LEN-1 || map[*px][*py+1]=='*')
                *pd = 2;
            else
                ++(*py);
            break;
        case 2: //south
            if (*px==SQ_LEN-1 || map[*px+1][*py]=='*')
                *pd = 3;
                else
                    ++(*px);
                break;
            case 3: //west
                if (*py==0 || map[*px][*py-1]=='*')
                    *pd = 0;
                else 
                    --(*py);
                break;
    } 
}

int main() {
    FILE *fin = fopen("ttwo.in", "r"); 
    for (int i=0; i<SQ_LEN; ++i) {
        for (int j=0; j<SQ_LEN; ++j) {
            fscanf(fin, "%c", &map[i][j]); 
            if (map[i][j]=='F') {
                fx = i;
                fy = j; 
                map[i][j] = '.';
            }       
            else if (map[i][j]=='C') {
                cx = i;
                cy = j; 
                map[i][j] = '.';
            }
        }
        char ch;
        fscanf(fin, "%c", &ch);
    }
    fclose(fin);

    memset(happened, 0, sizeof(happened));
    happened[(fx*SQ_LEN+fy)*4][(cx*SQ_LEN+cy)*4] = 1;
    fd = cd = 0;
    int step = 0;
    int never = 0;

    while (1) {
        ++step;
        move(&fx, &fy, &fd);
        move(&cx, &cy, &cd);
        if (fx==cx && fy==cy) 
            break;
        int fstatus = (fx*SQ_LEN+fy)*4+fd;
        int cstatus = (cx*SQ_LEN+cy)*4+cd;
        if (happened[fstatus][cstatus]) {
            never = 1;
            break; 
        }
        happened[fstatus][cstatus] = 1;
    }

    FILE *fout = fopen("ttwo.out", "w");
    fprintf(fout, "%d\n", (never)?0:step);
    fclose(fout);

    return 0;
}
