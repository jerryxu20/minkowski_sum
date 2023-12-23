// https://atcoder.jp/contests/abc139/tasks/abc139_f
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0): x(x), y(y) {};
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
    ll cross(Point p) const {
        return x * p.y - y * p.x;
    }
};

int section(Point p) {
    if (p.x > 0 || (p.x == 0 && p.y > 0)) return 0;
    return 1;
}


bool polarcomp(Point a, Point b) {
    if (section(a) != section(b)) return section(a) < section(b);
    return a.cross(b) > 0;
}

vector<Point> minkowski(vector<vector<Point>> &poly) {
    vector<Point> offsets;
    Point cur(0, 0);
    
    // Compute the offsets for each polygon
    for (auto &pts: poly) {
        if (sz(pts) == 0) return {};
        Point mn = pts[0];
        
        rep(i, 0, sz(pts)) {
            mn = min(mn, pts[i]);

            Point delta = pts[(i + 1) % sz(pts)] - pts[i];
            if (delta.x == 0 && delta.y == 0) continue;
            offsets.push_back(delta);
        }

        cur = cur + mn;
    }

    vector<Point> ans;

    sort(all(offsets), polarcomp);
    for (auto &offset: offsets) {
        ans.push_back(cur);
        cur = cur + offset;
    }
    return ans;
}

int solve() {
    int n; cin >> n;
    vector<vector<Point>> engines;
    rep(i, 0, n) {
        int x, y;
        cin >> x >> y;
        // Can either use the engine or not, so line segment
        // representing choice is [(x, y), (0, 0)]
        engines.push_back({Point(x, y), Point(0, 0)});
    }

    vector<Point> sm = minkowski(engines);
    
    ll ans = 0;
    for (auto &pt: sm) {
        ans = max(ans, pt.x * pt.x + pt.y * pt.y);
    }
    cout << setprecision(20) << sqrt(ans) << endl;
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}