/*
 ID: bragcat1
 LANG: C++11
 TASK: fence4
 */

#include <cmath>
#include <fstream>

using namespace std;

class Point {
public:
    double x_, y_;
    Point(double x = 0, double y = 0) : x_(x), y_(y) {}
    Point(const Point& p) : x_(p.x_), y_(p.y_) {}
    void operator =(const Point &p) {
        x_ = p.x_;
        y_ = p.y_;
    }
};

class Seg {
public:
    Point st_, end_;
};

const double EPS = 1e-6;

int n = 0;
Point eye;
Seg segs[200];
bool segsVisible[200];

ifstream fin("fence4.in");
ofstream fout("fence4.out");

double crossProduct(const Point &p1, const Point &p2) {
    return p1.x_ * p2.y_ - p2.x_ * p1.y_;
}

Point point2Vector(Point a, Point b) {
    b.x_ = b.x_ - a.x_;
    b.y_ = b.y_ - a.y_;
    return b;
}

bool diffSide(Seg &s1, Seg &s2) {
    Point v1 = point2Vector(s1.st_, s1.end_);
    double t1 = crossProduct(v1, point2Vector(s1.end_, s2.st_));
    double t2 = crossProduct(v1, point2Vector(s1.end_, s2.end_));
    if (t1 == 0 && t2 == 0) {
        return false;
    }
    if (t1 * t2 <= 0) {
        return true;
    }
    else {
        return false;
    }
}

bool segCross(Seg &s1, Seg &s2) {
    return diffSide(s1, s2) && diffSide(s2, s1);
}

bool isValid() {
    for (int i = 2; i < n - 1; i++) {
        if (segCross(segs[0], segs[i])) {
            return false;
        }
    }
    for (int i = 1; i < n - 2; i++) {
        for (int j = i + 2; j < n; j++) {
            if (segCross(segs[i], segs[j])) {
                return false;
            }
        }
    }
    return true;
}

bool isSame(const Point &a, const Point &b) {
    if (fabs(a.x_ - b.x_) >= EPS) {
        return false;
    }
    if (fabs(a.y_ - b.y_) >= EPS) {
        return false;
    }
    return true;
}

bool canSeen(const Seg &a, int index) {
    if (isSame(a.st_, a.end_)) {
        return false;
    }
    Seg leye, reye;
    leye.st_ = eye, leye.end_ = a.st_;
    reye.st_ = eye, reye.end_ = a.end_;
    bool ok = 0;
    for (int i = 0; i < n; i++) {
        if (i == index) {
            continue;
        }
        bool t1 = segCross(leye, segs[i]);
        bool t2 = segCross(reye, segs[i]);
        if (t1 && t2) {
            return false;
        }
        ok |= t1 || t2;
    }
    if (!ok) {
        return true;
    }
    Seg a_l, a_r;
    Point mid((a.st_.x_ + a.end_.x_) / 2, (a.st_.y_ + a.end_.y_) / 2);
    a_l.st_ = a.st_;
    a_l.end_ = mid;
    a_r.st_ = mid;
    a_r.end_ = a.end_;
    return  canSeen(a_l, index) || canSeen(a_r, index);
}

int main() {
    fin >> n;
    double x = 0, y = 0;
    fin >> x >> y;
    eye.x_ = x, eye.y_ = y;
    fin >> x >> y;
    Point st(x, y);
    for (int i = 0; i < n - 1; i++) {
        fin >> x >> y;
        Point end(x, y);
        segs[i].st_ = st;
        segs[i].end_ = end;
        st = end;
    }
    fin.close();

    segs[n - 1].st_ = segs[0].st_;
    segs[n - 1].end_ = st;
    if (!isValid()) {
        fout << "NOFENCE" << endl;
    } else {
        int seen_num = 0;
        for (int i = 0; i < n; i++) {
            if (canSeen(segs[i], i)) {
                segsVisible[i] = true;
                seen_num++;
            }
        }
        fout << seen_num << endl;
        for (int i = 0; i < n - 2; i++) {
            if (segsVisible[i])
                fout << segs[i].st_.x_ << " " << segs[i].st_.y_ << " "
                    << segs[i].end_.x_ << " " << segs[i].end_.y_ << endl;
        }
        if (segsVisible[n - 1])
            fout << segs[n - 1].st_.x_ << " " << segs[n - 1].st_.y_ << " "
                << segs[n - 1].end_.x_ << " " << segs[n - 1].end_.y_ << endl;
        if (segsVisible[n - 2])
            fout << segs[n - 2].st_.x_ << " " << segs[n - 2].st_.y_ << " "
                << segs[n - 2].end_.x_ << " " << segs[n - 2].end_.y_ << endl;
    }
    fout.close();
    return 0;
}