/*
ID: lizhita1
LANG: C
TASK: castle
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 50
#define max(a, b) ((a>b)?a:b)

struct Location {
    int x, y;
};

const int xDelta[4] = {0, -1, 0, 1};
const int yDelta[4] = {-1, 0, 1, 0};
int roomNum, largestSize, largestSizeRemove;
int removeRow, removeCol, removeDir;
int m, n;
int castle[MAX_N][MAX_N], roomMark[MAX_N][MAX_N];
int roomSize[MAX_N*MAX_N+1];

void count_rooms() {
    roomNum = 0;
    memset(roomMark, 0, sizeof(roomMark));
    for (int i=0; i<m; ++i)
        for (int j=0; j<n; ++j)
            if (roomMark[i][j]==0) {
                struct Location deque[MAX_N*MAX_N];
                memset(deque, 0, sizeof(deque));
                int head = 0, tail = 0, size = 1;
                roomMark[i][j] = ++roomNum;
                deque[0].x = i, deque[0].y = j;
                while (head<=tail) {
                    int x = deque[head].x, y = deque[head++].y, status = castle[x][y];
                    int nx, ny;
                    for (int k=0; k<4; ++k) 
                        if ((status & (1<<k))==0) {
                            nx = x+xDelta[k], ny = y+yDelta[k];
                            if (roomMark[nx][ny]==0) {
                                roomMark[nx][ny] = roomNum;
                                ++size;
                                deque[++tail].x = nx, deque[tail].y = ny;
                            }
                        }
                }
                roomSize[roomNum] = size;
            }
}

void search_remove_wall() {
    largestSizeRemove = 0;
    for (int i=0; i<m; ++i)
        for (int j=0; j<n; ++j) {
            int roomA = roomMark[i][j];
            for (int k=1; k<3; ++k)
                if (castle[i][j] & (1<<k)) {
                    int nx = i+xDelta[k], ny = j+yDelta[k];
                    int roomB = roomMark[nx][ny];
                    if (roomA==roomB)
                        continue;
                    if (roomSize[roomA]+roomSize[roomB]>largestSizeRemove) {
                        largestSizeRemove = roomSize[roomA]+roomSize[roomB];
                        removeRow = i, removeCol = j, removeDir = k; 
                    }
                    else if (roomSize[roomA]+roomSize[roomB]==largestSizeRemove) {
                        if (j<removeCol || (j==removeCol && i>removeRow))
                            removeRow = i, removeCol = j, removeDir = k;
                    }
                }
        }
}

int main() {
    FILE *fin = fopen("castle.in", "r");
    fscanf(fin, "%d%d", &n, &m);
    for (int i=0; i<m; ++i)
        for (int j=0; j<n; ++j)
            fscanf(fin, "%d", &castle[i][j]);
    fclose(fin);

    count_rooms();

    largestSize = 0;
    for (int i=1; i<=roomNum; ++i)
        largestSize = max(largestSize, roomSize[i]);

    search_remove_wall();

    FILE *fout = fopen("castle.out", "w");
    fprintf(fout, "%d\n%d\n%d\n%d %d %c\n", roomNum, largestSize, largestSizeRemove, removeRow+1, removeCol+1, (removeDir==1)?'N':'E');
    fclose(fout);

    return 0;
}
