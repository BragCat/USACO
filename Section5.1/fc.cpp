/*
 ID: bragcat1
 TASK: fc
 LANG: C++11
 */

#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_N = 10000;
const double MAX_X = 1000000;
const double ZERO_PRECISION = 1e-6;

typedef struct PointType {
    double x, y;
} Point;

int n;
Point points[MAX_N];
Point stPoint;
vector<Point> stack;

double CrossProduct(const Point &h1, const Point &t1, const Point &h2, const Point &t2) {
    double x1 = h1.x - t1.x, y1 = h1.y - t1.y;
    double x2 = h2.x - t2.x, y2 = h2.y - t2.y;
    return x1 * y2 - y1 * x2;
}

double Distance(const Point &p1, const Point &p2) {
    double x = p1.x - p2.x, y = p1.y - p2.y;
    return sqrt(x * x + y * y);
}

bool Cmp(const Point &a, const Point &b) {
    double cp = CrossProduct(a, stPoint, b, stPoint);
    if (abs(cp) < ZERO_PRECISION) {
        return Distance(a, stPoint) > Distance(b, stPoint);
    }
    else {
        return cp > 0;
    }
}

void Init() {
    ifstream fin("fc.in");
    double maxX = -MAX_X;
    int stIndex = -1;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> points[i].x >> points[i].y;
        if (points[i].x > maxX) {
            maxX = points[i].x;
            stIndex = i;
        }
    }
    fin.close();
    stPoint = points[stIndex];
    points[stIndex] = points[--n];
    sort(begin(points), begin(points) + n, Cmp);
}

void Graham() {
    stack.push_back(stPoint);
    stack.push_back(points[0]);
    for (int i = 1; i < n; ++i) {
        while (stack.size() > 1 && CrossProduct(points[i], stack.back(), stack[stack.size() - 2], stack.back())< -ZERO_PRECISION) {
            stack.pop_back();
        }
        stack.push_back(points[i]);
    }
}

void Print() {
    double ans = Distance(stack[0], stack.back());
    for (int i = 1; i < stack.size(); ++i) {
        ans += Distance(stack[i - 1], stack[i]);
    }
    ofstream fout("fc.out");
    fout.setf(ios::fixed);
    fout.precision(2);
    fout << ans << endl;
    fout.close();
}

int main() {
    Init();
    Graham();
    Print();
    return 0;
}
