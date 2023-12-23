// A simple Point stuct based on Kactl Point
// https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/Point.h
#pragma once
struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0): x(x), y(y) {};
    Point operator+(Point rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(Point rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    bool operator<(Point rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
    long long cross(Point p) const {
        return x * p.y - y * p.x;
    }
};
