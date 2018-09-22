/*
 ID: bragcat1
 LANG: C++11
 TASK: race3
 */

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 50;
const int MAX_M = 100;

int n, source, destination;
int nextNodes[MAX_N][MAX_N];
int inDegree[MAX_N], outDegree[MAX_N];
bool visited[MAX_N];
int label[MAX_N];
vector<int> firstAnswerNodes, secondAnswerNodes;

void dfs(int node, int labelFlag) {
    visited[node] = true;
    if (labelFlag) {
        label[node] = 1;
    }
    for (int i = 0; i < outDegree[node]; ++i) {
        if (!visited[nextNodes[node][i]]) {
            dfs(nextNodes[node][i], labelFlag);
        }
    }
}

bool dfsToSearchLabel(int node) {
    visited[node] = true;
    for (int i = 0; i < outDegree[node]; ++i) {
        if (!visited[nextNodes[node][i]]) {
            if (dfsToSearchLabel(nextNodes[node][i])) {
                return true;
            }
        }
        else if (label[nextNodes[node][i]]){
            return true;
        }
    }
    return false;
}

bool judgeUnavoidableNode(int node) {
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    visited[node] = true;
    dfs(source, 0);
    if (!visited[destination]) {
        return true;
    }
    return false;
}

bool judgeSplittingNode(int node) {
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        label[i] = 0;
    }
    visited[node] = true;
    dfs(source, 1);
    if (dfsToSearchLabel(node)) {
        return false;
    }
    return true;
}

int main() {
    ifstream fin("race3.in");
    int x;
    fin >> x;
    n = 0;
    while (x != -1) {
        while (x != -2) {
            ++inDegree[x];
            nextNodes[n][outDegree[n]] = x;
            ++outDegree[n];
            fin >> x;
        }
        fin >> x;
        ++n;
    }
    fin.close();

    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) {
            source = i;
        }
        if (outDegree[i] == 0) {
            destination = i;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i != source && i != destination && judgeUnavoidableNode(i)) {
            firstAnswerNodes.push_back(i);
        }
    }

    for (int node : firstAnswerNodes) {
        if (judgeSplittingNode(node)) {
            secondAnswerNodes.push_back(node);
        }
    }

    sort(firstAnswerNodes.begin(), firstAnswerNodes.end());
    ofstream fout("race3.out");
    fout << firstAnswerNodes.size();
    for (int node : firstAnswerNodes) {
        fout << " " << node;
    }
    fout << endl;
    fout << secondAnswerNodes.size();
    for (int node : secondAnswerNodes) {
        fout << " " << node;
    }
    fout << endl;
    fout.close();
    return 0;
}
