/*
https://codeforces.com/contest/87/problem/E
Kactl Point: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/Point.h
Kactl Point Inside Hull: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/PointInsideHull.h
Kactl Side Of: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/sideOf.h
Kactl On Segment: https://github.com/kth-competitive-programming/kactl/blob//content/geometry/OnSegment.h
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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

typedef Point<ll> P;
bool inHull(const vector<P>& l, P p, bool strict = true) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}

vector<P> minkowski(vector<P> &A, vector<P> &B) {
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

    vector<P> ans;
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
    vector<vector<Point<ll>>> polygons(3);
    for (int i = 0; i < 3; i++) {
        int n; cin >> n;
        while(n--) {
            int x, y;
            cin >> x >> y;
            polygons[i].push_back(Point<ll>(x, y));
        }
    }
    // Compute the Minkowski sum of the three polygons
    vector<Point<ll>> sm = minkowski(polygons[0], polygons[1]);
    sm = minkowski(sm, polygons[2]);

    
    int m; cin >> m;
    while(m--) {
        int x, y;
        cin >> x >> y;
        if (inHull(sm, Point<ll>(3*x, 3*y), false)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    solve();
}