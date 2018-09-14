/*
 ID: bragcat1
 LANG: C++11
 TASK: job
 */

#include <fstream>
#include <vector>

using namespace std;

const int MAX_INT = ~0u >> 1;
const int MAX_N = 1000;
const int MAX_M = 30;

int n, ma, mb;
int timeA[MAX_M], timeB[MAX_M];
int finishA[MAX_N], finishB[MAX_N];

void getTimeline(vector<int> &timeline, int time[], int m, int finish[]) {
    for (int i = 0; i < n; ++i) {
        int minIndex = 0;
        for (int j = 1; j < m; ++j) {
            if (timeline[j] + time[j] < timeline[minIndex] + time[minIndex]) {
                minIndex = j;
            }
        }
        timeline[minIndex] += time[minIndex];
        finish[i] = timeline[minIndex];
    }
}

int main() {
    ifstream fin("job.in");
    fin >> n >> ma >> mb;
    for (int i = 0; i < ma; ++i) {
        fin >> timeA[i];
    }
    for (int i = 0; i < mb; ++i) {
        fin >> timeB[i];
    }
    fin.close();

    vector<int> timelineA(ma, 0), timelineB(mb, 0);
    getTimeline(timelineA, timeA, ma, finishA);
    getTimeline(timelineB, timeB, mb, finishB);

    int minTime = 0;
    for (int i = 0; i < ma; ++i) {
        minTime = max(minTime, timelineA[i]);
    }
    ofstream fout("job.out");
    fout << minTime << ' ';
    minTime = 0;
    for (int i = 0; i < n; ++i) {
        minTime = max(minTime, finishA[i] + finishB[n - 1 -i]);
    }
    fout << minTime << endl;
    fout.close();

    return 0;
}

