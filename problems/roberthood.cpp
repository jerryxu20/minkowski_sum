// https://open.kattis.com/problems/roberthood
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


vector<Point> minkowski(vector<Point> &A, vector<Point> &B) {
    int n = sz(A);
    int m = sz(B);
    if (n == 0 || m == 0) return {};

    // Find the index of the min point in each polygon
    int mn_a, mn_b;
    mn_a = mn_b = 0;
    for (int i = 1; i < sz(A); i++) {
        if (A[i] < A[mn_a]) mn_a = i;
    }
    for (int i = 1; i < sz(B); i++) {
        if (B[i] < B[mn_b]) mn_b = i;
    }

    vector<Point> ans;
    int i = mn_a;
    int j = mn_b;
    do {
        ans.push_back(A[i] + B[j]);
        int ii = (i + 1) % n;
        int jj = (j + 1) % m;

        // Consider edges a[i] -> a[ii] and b[j] -> b[jj]
        // Advance the pointer that changes our polar angle the least
        ll c = (A[ii] - A[i]).cross(B[jj] - B[j]);
        if (c >= 0) {
            i = ii;
        }
        if (c <= 0) {
            j = jj;
        }
    } while(i != mn_a || j != mn_b);
    return ans;
}


int solve() {
    int n; cin >> n;
    vector<Point> pts, pts_negated;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pts.push_back(Point(x, y));
        pts_negated.push_back(Point(-x, -y));
    }

    pts = convexHull(pts);
    pts_negated = convexHull(pts_negated);

    vector<Point> res = minkowski(pts, pts_negated);
    
    ll ans = 0;
    for(auto &pt: res) {
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