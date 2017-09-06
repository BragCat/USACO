/*
ID: lizhita1
LANG: C
TASK: maze1
 */

#include <stdio.h>
#include <string.h>

#define MAXW 38
#define MAXH 100
#define MAX_NUM 0x7fffffff
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

int isFirst = -1;
int ans, w, h;
int dist[MAXH][MAXW], dist1[MAXH][MAXW], dist2[MAXH][MAXW], visited[MAXH][MAXW];
char map[MAXH*2+1][MAXW*2+1];

void update_dist(int x, int y) {
    if (x>0 && dist[x][y]+1<dist[x-1][y] && map[x*2][y*2+1]==' ')
        dist[x-1][y] = dist[x][y]+1;
    if (y>0 && dist[x][y]+1<dist[x][y-1] && map[x*2+1][y*2]==' ')
        dist[x][y-1] = dist[x][y]+1;
    if (x<h-1 && dist[x][y]+1<dist[x+1][y] && map[x*2+2][y*2+1]==' ')
        dist[x+1][y] = dist[x][y]+1;
    if (y<w-1 && dist[x][y]+1<dist[x][y+1] && map[x*2+1][y*2+2]==' ')
        dist[x][y+1] = dist[x][y]+1;
}

void dijkstra(int sx, int sy) {
    if (isFirst==-1)
        isFirst = 1;
    else 
        isFirst = 0;
    memset(visited, 0, sizeof(visited));
    for (int i=0; i<h; ++i)
        for (int j=0; j<w; ++j)
            dist[i][j] = MAX_NUM;
    dist[sx][sy] = 1;
    visited[sx][sy] = 1;
    update_dist(sx, sy);
    for (int l=0; l<w*h-1; ++l) {
        int nx, ny, mind = MAX_NUM;
        for (int i=0; i<h; ++i) 
            for (int j=0; j<w; ++j)
                if (!visited[i][j] && dist[i][j]<mind) {
                    nx = i;
                    ny = j;
                    mind = dist[i][j];
                }
        visited[nx][ny] = 1;
        update_dist(nx, ny);
    }
    if (isFirst)
        memcpy(dist1, dist, sizeof(dist));
    else 
        memcpy(dist2, dist, sizeof(dist)); 
}

int main() {
    FILE *fin = fopen("maze1.in", "r");
    fscanf(fin, "%d%d", &w, &h);
    char ch;
    fscanf(fin, "%c", &ch);
    for (int i=0; i<h*2+1; ++i) {
        for (int j=0; j<w*2+1; ++j) 
            fscanf(fin, "%c", &map[i][j]);
        fscanf(fin, "%c", &ch);
    }
    fclose(fin);

    for (int i=1; i<2*w+1; i+=2) {
        if (map[0][i]==' ')  
            dijkstra(0, i/2);
        if (map[2*h][i]==' ') 
            dijkstra(h-1, i/2);
    }
             
    for (int i=1; i<2*h+1; i+=2) {
        if (map[i][0]==' ')
            dijkstra(i/2, 0);
        if (map[i][2*w]==' ')
            dijkstra(i/2, w-1);
    }

    ans = 0;
    for (int i=0; i<h; ++i)
        for (int j=0; j<w; ++j) {
            dist[i][j] = min(dist1[i][j], dist2[i][j]);
            ans = max(ans, dist[i][j]);
        }

    FILE *fout = fopen("maze1.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    return 0;
} 
