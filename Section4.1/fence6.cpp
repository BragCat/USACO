/*
 ID: bragcat1
 LANG: C++11
 TASK: fence6
 */

#include <fstream>
#include <iostream>

using namespace std;

const int MAX_N = 100;
const int MAX_INT = 0x7fffffff;

int edgeCode[MAX_N];
int edgeLength[MAX_N];
int nodeCode[MAX_N][2];
int linkList[MAX_N][2][MAX_N];
int linkNumber[MAX_N][2];
int dist[2 * MAX_N][2 * MAX_N], path[2 * MAX_N][2 * MAX_N];

int n;
int minCycle = MAX_INT;
int nodeCount;

void bfsEdge(int edgeIndex, int nodeLabel, int code) {
    nodeCode[edgeIndex][nodeLabel] = code;
    for (int i = 0; i < linkNumber[edgeIndex][nodeLabel]; ++i) {
        int nextEdgeCode = linkList[edgeIndex][nodeLabel][i];
        int nextEdgeIndex = -1;
        for (int j = 0; j < n; ++j) {
            if (edgeCode[j] == nextEdgeCode) {
                nextEdgeIndex = j;
                break;
            }
        }
        int nextNodeLabel = 0;
        for (int j = 0; j < linkNumber[nextEdgeIndex][1]; ++j) {
            if (linkList[nextEdgeIndex][1][j] == edgeCode[edgeIndex]) {
                nextNodeLabel = 1;
                break;
            }
        }
        nodeCode[nextEdgeIndex][nextNodeLabel] = code;
    }
}

void generateGraph() {
    for (int i = 0; i < n; ++i) {
        nodeCode[i][0] = nodeCode[i][1] = -1;
    }
    // enumerate the nodes
    for (int i = 0; i < n; ++i) {
        if (nodeCode[i][0] == -1) {
            bfsEdge(i, 0, nodeCount++);
        }
        if (nodeCode[i][1] == -1) {
            bfsEdge(i, 1, nodeCount++);
        }
    }

    // get dist matrix
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = 0; j < nodeCount; ++j) {
            path[i][j] = dist[i][j] = MAX_INT;
        }
    }
    for (int i = 0; i < n; ++i) {
        int x = nodeCode[i][0], y = nodeCode[i][1];
        // consider cycles of length 2
        if (path[x][y] != MAX_INT) {
            minCycle = min(minCycle, path[x][y] + edgeLength[i]);
        }
        path[x][y] = path[y][x] = dist[x][y] = dist[y][x] = min(path[x][y], edgeLength[i]);
    }
    // consider cycles of length 1
    for (int i = 0; i < nodeCount; ++i) {
        minCycle = min(minCycle, dist[i][i]);
    }
}

void getMinCycle() {
    for (int k = 0; k < nodeCount; ++k) {
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dist[j][i] != MAX_INT && path[i][k] != MAX_INT && path[k][j] != MAX_INT) {
                    minCycle = min(minCycle, dist[j][i] + path[i][k] + path[k][j]);
                }
            }
        }

        for (int i = 0; i < nodeCount; ++i) {
            for (int j = 0; j < nodeCount; ++j) {
                if (dist[i][k] != MAX_INT && dist[k][j] != MAX_INT) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    ifstream fin("fence6.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> edgeCode[i] >> edgeLength[i] >> linkNumber[i][0] >> linkNumber[i][1];
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < linkNumber[i][j]; ++k) {
                fin >> linkList[i][j][k];
            }
        }
    }
    fin.close();

    generateGraph();

    // floyed to find the minimal cycle
    getMinCycle();

    ofstream fout("fence6.out");
    fout << minCycle << endl;
    fout.close();

    return 0;
}
