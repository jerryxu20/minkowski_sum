// http://usaco.org/index.php?page=viewproblem2&cpid=1190
// Convex hull based on Second Thread: https://www.youtube.com/watch?v=G51AjY8tIcA
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

bool ccw(Point &A, Point &B, Point &C) {
    return (B-A).cross(C-B) > 0;
}

vector<Point> convexHull(vector<Point> &pts) {
    if (sz(pts) <= 1) return pts;
    vector<Point> top(sz(pts)), bot(sz(pts));
    sort(all(pts));
    rep(_, 0, 2) {
        int n = 0;
        for (auto &p: pts) {
	        // pop from stack 
            while (n >= 2 && !ccw(bot[n - 2], bot[n - 1], p)) n--;

			// push current point to stack
			bot[n++] = p;
        }
        reverse(all(pts));
        bot.resize(n);
        swap(top, bot);
    }
    bot.insert(bot.end(), 1 + all(top) - 1);
    return bot;
}

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
    vector<vector<Point>> groups(n);

    for (auto &group: groups) {
        int m; cin >> m;
        while(m--) {
            int x, y;
            cin >> x >> y;
            group.pb(Point(x, y));
        }
        group = convexHull(group);
    }

    vector<Point> sm = minkowski(groups);

    ll ans = 0;
    for (auto &pt: sm) {
        ans = max(ans, pt.x * pt.x + pt.y * pt.y);
    }
    cout << ans << endl;
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}