/*
 ID: bragcat1
 TASK: telecow
 LANG: C++11
 */

#include <cstring>
#include <fstream>
#include <vector>
#include <deque>


using namespace std;

const int MAX_N = 100;
const int MAX_INT = ~0u >> 1;

int n, m, st, ed;
int d[MAX_N * 2], cntD[MAX_N * 2 + 1], pre[MAX_N * 2];
int edge[MAX_N * 2][MAX_N * 2], flow[MAX_N * 2][MAX_N * 2];
vector<int> ansList;

void markD(int st) {
    for (int i = 0; i < n * 2; ++i) {
        d[i] = n * 2;
    }
    d[st] = 0;
    deque<int> q{st};
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        for (int i = 0; i < n * 2; ++i) {
            if (d[i] == n * 2 && flow[i][x]) {
                d[i] = d[x] + 1;
                q.push_back(i);
            }
        }
    }

    for (int i = 0; i < n * 2; ++i) {
        ++cntD[d[i]];
    }
}

int sap(int source, int sink, int except) {
    memset(cntD, 0, sizeof(cntD));
    memcpy(flow, edge, sizeof(edge));
    for (int x : ansList) {
        flow[x - 1][x - 1 + n] =  0;
    }
    if (except != -1) {
        flow[except][except + n] = 0;
    }

    markD(sink);

    int x = source, maxFlow = 0;
    while (d[source] != n * 2) {
        int next = -1;
        for (int i = 0; i < n * 2; ++i) {
            if (flow[x][i] && d[x] == d[i] + 1) {
                next = i;
                break;
            }
        }
        if (next == -1) {
            --cntD[d[x]];
            if (cntD[d[x]] == 0) {
                break;
            }
            d[x] = n * 2;
            for (int i = 0; i < n * 2; ++i) {
                if (flow[x][i]) {
                    d[x] = min(d[x], d[i] + 1);
                }
            }
            ++cntD[d[x]];
            if (x != source) {
                x = pre[x];
            }
        } else {
            pre[next] = x;
            x = next;
            if (x == sink) {
                int minCap = MAX_INT;
                while (x != source) {
                    minCap = min(minCap, flow[pre[x]][x]);
                    x = pre[x];
                }
                x = sink;
                while (x != source) {
                    flow[pre[x]][x] -= minCap;
                    flow[x][pre[x]] += minCap;
                    x = pre[x];
                }
                maxFlow += minCap;
            }
        }
    }
    return maxFlow;
}

int main() {
    ifstream fin("telecow.in");
    fin >> n >> m >> st >> ed;
    --st, --ed;
    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        --x, --y;
        edge[x + n][y] = edge[y + n][x] = MAX_INT;
    }
    fin.close();

    for (int i = 0; i < n; ++i) {
        edge[i][i + n] = 1;
    }
    edge[st][st + n] = edge[ed][ed + n] = MAX_INT;

    int maxFlow = sap(st, ed + n, -1);

    ofstream fout("telecow.out");
    fout << maxFlow << endl;
    for (int i = 0; i < n; ++i) {
        if (i != st && i != ed) {
            int nowFlow = sap(st, ed + n, i);
            if (nowFlow + 1 == maxFlow) {
                ansList.push_back(i + 1);
                maxFlow = nowFlow;
            }
        }
    }
    if (!ansList.empty()) {
        fout << ansList[0];
        for (int i = 1; i < ansList.size(); ++i) {
            fout << ' ' << ansList[i];
        }
        fout << endl;
    }
    fout.close();
    return 0;
}
