/*
https://codeforces.com/contest/1195/problem/F
Kactl Seg Tree: https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h 
*/
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
    ll cross(Point p) {
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

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void add(int pos, T val) {
		for (s[pos += n] += val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int solve() {
    int n; cin >> n;

    vector<pair<Point, int>> offsets;
    int N = 0;

    // polygon[i]: the indices of offsets of the ith polygon
    vector<vector<int>> polygon(n);
    rep(i, 0, n) {
        int m; cin >> m;
        vector<Point> pts(m);
        for (auto &pt: pts) {
            cin >> pt.x >> pt.y;
        }
        
        rep(j, 0, m) {
            Point delta = pts[(j + 1) % m] - pts[j];
            offsets.pb({delta, N});
            polygon[i].pb(N);
            N++;
        }
    }

    // map each polar angle to an int
    sort(all(offsets), [] (auto &a, auto &b) {
        return polarcomp(a.first, b.first);
    });

    vector<int> angle(N);
    rep(i, 1, N) {
        auto [cur, idx1] = offsets[i];
        auto [prev, idx2] = offsets[i - 1];
        if (section(cur) == section(prev) && cur.cross(prev) == 0) {
            angle[idx1] = angle[idx2];
        } else {
            angle[idx1] = angle[idx2] + 1;
        }   
    } 

    int q; cin >> q;
    vector<tuple<int, int, int>> queries;
    rep(i, 0, q) {
        int l, r; 
        cin >> l >> r;
        queries.pb({r - 1, l - 1, i});
    } 
    sort(all(queries));

    vector<int> last_seen(N, -1), ans(q);

    int mx = -1;
    Tree seg(n);
    for (auto &[r, l, idx]: queries) {
        for (int i = mx + 1; i <= r; i++) {
            for (auto &side: polygon[i]) {
                int ang = angle[side];

                if (last_seen[ang] != -1) {
                    seg.add(last_seen[ang], -1);
                }

                last_seen[ang] = i;
                seg.add(i, 1);
            }
        }
        ans[idx] = seg.query(l, r + 1);

        mx = max(mx, r);
    }

    for (int x: ans) {
        cout << x << endl;
    }


    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}