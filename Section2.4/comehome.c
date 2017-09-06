/*
ID: lizhita1
LANG: C
TASK: comehome
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) ((a)<(b))?(a):(b)

#define MAXN 52
#define MAXP 10000
#define MAXNUM 0x7fffffff

struct edge_t {
    int dst, len;
    struct edge_t *next; 
};

int used[MAXN], dist[MAXN];
int p;
struct edge_t *edges[MAXN];

void initialize() {
    for (int i=0; i<MAXN; ++i) {
        edges[i] = NULL;
        dist[i] = MAXNUM;
        used[i] = 0;
    }
}

void add_edge(int x, int y, int len) {
    struct edge_t *newEdge = (struct edge_t *)malloc(sizeof(struct edge_t));
    newEdge->len = len;
    newEdge->dst = y;
    newEdge->next = edges[x];
    edges[x] = newEdge;
}

int convert_pst(char ch) {
    if (ch<='Z') 
        return (int)(ch-'A');
    else
        return (int)(ch-'a')+26;
}

void update_dist(int src) {
    struct edge_t *curEdge = edges[src];
    while (curEdge) {
        dist[curEdge->dst] = min(dist[curEdge->dst], dist[src]+curEdge->len);
        curEdge = curEdge->next;
    }
}

void dijkstra() {
    dist[convert_pst('Z')] = 0;
    used[convert_pst('Z')] = 1;
    update_dist(convert_pst('Z'));
    for (int i=0; i<MAXN-1; ++i) {
        int minDist = MAXNUM;
        int nextPst = -1;
        for (int j=0; j<MAXN; ++j) 
            if (!used[j] && dist[j]<minDist) {
                minDist = dist[j];
                nextPst = j;
            }
        if (nextPst==-1)
            break;
        used[nextPst] = 1;
        update_dist(nextPst); 
    }
}


int main() {
    initialize(); 

    FILE *fin = fopen("comehome.in", "r");
    fscanf(fin, "%d\n", &p);
    for (int i=0; i<p; ++i) {
        char x, y, ch;
        int len;
        fscanf(fin, "%c%c%c%d%c", &x, &ch, &y, &len, &ch);
        int pstx = convert_pst(x);
        int psty = convert_pst(y);
        //printf("%c(%d) %c(%d) %d\n", x, pstx, y, psty, len);
        add_edge(pstx, psty, len);
        add_edge(psty, pstx, len);
    }
    fclose(fin);

    dijkstra();

    char ans = ' ';
    int minLen = MAXNUM;
    for (char ch='A'; ch<='Y'; ++ch)
        if (minLen>dist[convert_pst(ch)]) {
            minLen = dist[convert_pst(ch)];
            ans = ch; 
        }

    FILE *fout = fopen("comehome.out", "w");
    fprintf(fout, "%c %d\n", ans, minLen);
    fclose(fout);
    return 0;
}
