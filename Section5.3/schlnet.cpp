/*
 ID: bragcat1
 TASK: schlnet
 LANG: C++11
 */

#include <fstream>
#include <stack>
#include <vector>

using namespace std;

const int MAX_N = 100;

int n, newN, t;
vector<vector<int>> edges;
vector<int> dfn, low, labels, inDegrees, outDegrees;
vector<bool> visited, inStack;
stack<int> s;

void tarjan(int node) {
    visited[node] = true;
    dfn[node] = low[node] = t++;
    s.push(node);
    inStack[node] = true;
    for (int x : edges[node]) {
        if (!visited[x]) {
            tarjan(x);
            low[node] = min(low[node], low[x]);
        } else if (inStack[x]) {
            low[node] = min(low[node], low[x]);
        }
    }
    if (dfn[node] == low[node]) {
        int x = s.top();
        s.pop();
        inStack[x] = false;
        labels[x] = newN;
        while (x != node) {
            x = s.top();
            s.pop();
            inStack[x] = false;
            labels[x] = newN;
        }
        ++newN;
    }
}

int main() {
    ifstream fin("schlnet.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        fin >> x;
        edges.emplace_back();
        while (x != 0) {
            edges.back().push_back(x - 1);
            fin >> x;
        }
        visited.push_back(false);
        inStack.push_back(false);
        labels.push_back(-1);
        inDegrees.push_back(0);
        outDegrees.push_back(0);
        dfn.push_back(0);
        low.push_back(0);
    }
    fin.close();

    t = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (auto x : edges[i]) {
            if (labels[x] != labels[i]) {
                ++inDegrees[labels[x]];
                ++outDegrees[labels[i]];
            }
        }
    }

    int in0Cnt = 0, out0Cnt = 0;
    for (int i = 0; i < newN; ++i) {
        in0Cnt += (inDegrees[i] == 0);
        out0Cnt += (outDegrees[i] == 0);
    }

    ofstream fout("schlnet.out");
    if (newN == 1) {
        fout << 1 << endl << 0 << endl;
    } else {
        fout << in0Cnt << endl << max(in0Cnt, out0Cnt) << endl;
    }
    fout.close();
    return 0;
}
