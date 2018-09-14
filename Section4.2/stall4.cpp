/*
 ID: bragcat1
 LANG: C++11
 TASK: stall4
 */

#include <fstream>
#include <deque>

using namespace std;

const int MAX_N = 200;
const int MAX_M = 200;
const int MAX_INT = ~0u >> 1;

int n, m;
int d[MAX_N + MAX_M + 2], countD[MAX_N + MAX_M + 3], preNode[MAX_N + MAX_M + 2];
int flow[MAX_N + MAX_M + 2][MAX_N + MAX_M + 2];

int getMaxFlow(int source, int sink) {
    int totalNode = n + m + 2;
    for (int i = 0; i < totalNode; ++i) {
        d[i] = totalNode;
    }
    deque<int> q{sink};
    d[sink] = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop_front();
        for (int i = 0; i < totalNode; ++i) {
            if (flow[i][node] > 0 && d[i] == totalNode) {
                d[i] = d[node] + 1;
                q.push_back(i);
            }
        }
    }
    for (int i = 0; i < totalNode; ++i) {
        ++countD[d[i]];
    }

    int node = source;
    int maxFlow = 0;
    while (d[source] < totalNode) {
        int nextNode = -1;
        for (int i = 0; i < totalNode; ++i) {
            if (flow[node][i] > 0 && d[node] == d[i] + 1) {
                nextNode = i;
                break;
            }
        }
        if (nextNode != -1) {
            preNode[nextNode] = node;
            node = nextNode;
            if (node == sink) {
                int minCap = MAX_INT;
                while (node != source) {
                    minCap = min(minCap, flow[preNode[node]][node]);
                    node = preNode[node];
                }
                node = sink;
                while (node != source) {
                    flow[preNode[node]][node] -= minCap;
                    flow[node][preNode[node]] += minCap;
                    node = preNode[node];
                }
                maxFlow += minCap;
            }
        }
        else {
            --countD[d[node]];
            if (countD[d[node]] == 0) {
                break;
            }
            d[node] = totalNode;
            for (int i = 0; i < totalNode; ++i) {
                if (flow[node][i] > 0) {
                    d[node] = min(d[node], d[i] + 1);
                }
            }
            ++countD[d[node]];
            if (node != source) {
                node = preNode[node];
            }
        }
    }
    return maxFlow;
}

int main() {
    ifstream fin("stall4.in");
    fin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int number, x;
        fin >> number;
        for (int j = 0; j < number; ++j) {
            fin >> x;
            flow[i + 1][x + n] = 1;
        }
    }
    fin.close();

    for (int i = 0; i < n; ++i) {
        flow[0][i + 1] = 1;
    }
    for (int i = 0; i < m; ++i) {
        flow[i + n + 1][n + m + 1] = 1;
    }


    ofstream fout("stall4.out");
    fout << getMaxFlow(0, n + m + 1) << endl;
    fout.close();

    return 0;
}
