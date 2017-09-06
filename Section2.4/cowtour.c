/*
ID: lizhita1
LANG: C
TASK: cowtour
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 150
#define sqr(a)  ((a)*(a))

int n, adj[MAXN][MAXN];
double loca[MAXN][2];
double dist[MAXN][MAXN];

int main() {
    FILE *fin = fopen("cowtour.in", "r");
    fscanf(fin, "%d", &n);
    for (int i=0; i<n; ++i)
        fscanf(fin, "%lf%lf", &loca[i][0], &loca[i][1]);
    char ch;
    fscanf(fin, "%c", &ch);
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            fscanf(fin, "%c", &ch);
            adj[i][j] = (ch=='1');
            if (adj[i][j])
                dist[i][j] = sqrt(sqr(loca[i][0]-loca[j][0])+sqr(loca[i][1]-loca[j][1])); 
            else 
                dist[i][j] = -1;
        }
        fscanf(fin, "%c", &ch);
    }
    fclose(fin);

    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            if (dist[i][k]>0)
                for (int j=0; j<n; ++j)
                    if (i!=j && dist[k][j]>0 && (dist[i][j]<0 || dist[i][k]+dist[k][j]<dist[i][j]))
                        dist[i][j] = dist[i][k]+dist[k][j];
    
    /*
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) 
            printf("%.6f ", dist[i][j]);
        printf("\n");
    }
    */


    double ans = -1;
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            if (i!=j && dist[i][j]<0) {
                double max1 = 0;
                for (int k=0; k<n; ++k) 
                    if (dist[i][k]>0 && dist[i][k]>max1)
                        max1 = dist[i][k];
                double max2 = 0;
                for (int k=0; k<n; ++k)
                    if (dist[k][j]>0 && dist[k][j]>max2)
                        max2 = dist[k][j];
                double line = sqrt(sqr(loca[i][0]-loca[j][0])+sqr(loca[i][1]-loca[j][1])); 
                if (ans<0 || line+max1+max2<ans)
                    ans = line+max1+max2;
            }

    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            if (i!=j && dist[i][j]>0 && dist[i][j]>ans)
                ans = dist[i][j];

    FILE *fout = fopen("cowtour.out", "w");
    fprintf(fout, "%.6f\n", ans);
    fclose(fout);
}
