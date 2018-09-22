/*
 ID: bragcat1
 LANG: C++11
 TASK: milk6
 */

#include <fstream>
#include <vector>
#include <deque>
#include <cstring>

using namespace std;

const int MAX_N = 32;
const int MAX_M = 1000;
const int MAX_INT = ~0u >> 1;

int d[MAX_N], cntD[MAX_N + 1], preNode[MAX_N];
int flow[MAX_N][MAX_N];
int edge[MAX_M][3];
int n, m;
vector<bool> inMinCut;

void initGraph(int edgeIndex) {
    memset(flow, 0, sizeof(flow));
    memset(cntD, 0, sizeof(cntD));
    for (int i = 0; i < m; ++i) {
        if (i != edgeIndex && !inMinCut[i]) {
            int x = edge[i][0] - 1, y = edge[i][1] - 1, v = edge[i][2];
            flow[x][y] += v + (edgeIndex != -1);
        }
    }
    for (int i = 0; i < n; ++i) {
        d[i] = n;
    }
}

void bfsGraph() {
    d[n - 1] = 0;
    deque<int> q{n - 1};
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        for (int i = 0; i < n; ++i) {
            if (d[i] == n && flow[i][x]) {
                d[i] = d[x] + 1;
                q.push_back(i);
            }
        }
    }
}

int sap(int edgeIndex) {
    initGraph(edgeIndex);
    bfsGraph();

    for (int i = 0; i < n; ++i) {
        ++cntD[d[i]];
    }

    int x = 0, maxFlow = 0;
    while (d[0] != n) {
        int nextX = -1;
        for (int i = 0; i < n; ++i) {
            if (d[i] == d[x] - 1 && flow[x][i]) {
                nextX = i;
                break;
            }
        }
        if (nextX == -1) {
            --cntD[d[x]];
            if (cntD[d[x]] == 0) {
                break;
            }
            d[x] = n;
            for (int i = 0; i < n; ++i) {
                if (flow[x][i] && d[x] > d[i] + 1) {
                    d[x] = d[i] + 1;
                }
            }
            ++cntD[d[x]];
            x = preNode[x];
        }
        else {
            preNode[nextX] = x;
            x = nextX;
            if (x == n - 1) {
                int minCap = MAX_INT;
                while (x != 0) {
                    minCap = min(minCap, flow[preNode[x]][x]);
                    x = preNode[x];
                }
                x = n - 1;
                while (x != 0) {
                    flow[preNode[x]][x]  -= minCap;
                    x = preNode[x];
                }
                maxFlow += minCap;
            }
        }
    }
    return maxFlow;
}

int main() {
    ifstream fin("milk6.in");
    fin >> n >> m;
    for (int i = 0; i < m; ++i) {
        fin >> edge[i][0] >> edge[i][1] >> edge[i][2];
    }
    fin.close();

    for (int i = 0; i < m; ++i) {
        inMinCut.push_back(false);
    }
    int maxFlow = sap(-1);
    int minEdgeNumber = sap(-2) - maxFlow;
    int aimFlow = maxFlow + minEdgeNumber;

    for (int i = 0; i < m; ++i) {
        int currentFlow = sap(i);
        if (currentFlow + edge[i][2] + 1 == aimFlow) {
            inMinCut[i] = true;
            aimFlow = currentFlow;
        }
    }

    ofstream fout("milk6.out");
    fout << maxFlow << ' ' << minEdgeNumber << endl;
    for (int i = 0; i < m; ++i) {
        if (inMinCut[i]) {
            fout << i + 1 << endl;
        }
    }
    fout.close();

    return 0;
}
