/*
 ID: bragcat1
 LANG: C++11
 TASK: ditch
 */

#include <fstream>
#include <deque>

using namespace std;

const int MAX_N = 200;
const int MAX_M = 200;
const int MAX_INT = ~0u >> 1;

int d[MAX_N], preNode[MAX_N], countD[MAX_N + 1];
int edge[MAX_N][MAX_N];

int n, m;

int getMaxFlow(int source, int sink) {
    for (int i = 0; i < n; ++i) {
        d[i] = n;
    }
    d[sink] = 0;
    deque<int> q{sink};
    while (!q.empty()) {
        int node = q.front();
        q.pop_front();
        for (int i = 0; i < n; ++i) {
            if (edge[i][node] > 0 && d[i] == n) {
                d[i] = d[node] + 1;
                q.push_back(i);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        ++countD[d[i]];
    }
    int node = source;
    int maxFlow = 0;
    while (d[source] < n) {
        int nextNode = -1;
        for (int i = 0; i < n; ++i) {
            if (edge[node][i] > 0 && d[node] == d[i] + 1) {
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
                    minCap = min(minCap, edge[preNode[node]][node]);
                    node = preNode[node];
                }
                node = sink;
                while (node != source) {
                    edge[preNode[node]][node] -= minCap;
                    edge[node][preNode[node]] += minCap;
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
            d[node] = n;
            for (int i = 0; i < n; ++i) {
                if (edge[node][i] > 0) {
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
    ifstream fin("ditch.in");
    fin >> m >> n;
    for (int i = 0; i < m; ++i) {
        int x, y, c;
        fin >> x >> y >> c;
        edge[x - 1][y - 1] += c;
    }
    fin.close();


    ofstream fout("ditch.out");
    fout << getMaxFlow(0, n - 1) << endl;
    fout.close();

    return 0;
}
