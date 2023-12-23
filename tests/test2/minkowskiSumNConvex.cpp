#include "../../src/MinkowskiSumNConvexPoly.h"
#include "../bookcode/template.h"

// Remove points that are collinear with their adjacent points
// such that no three points will lie on the same after
// Assumes the first point is valid. 
vector<Point> remove_collinear(vector<Point> &pts) {
    vector<Point> ans;

    // Make points wrap around
    pts.push_back(pts[0]);
    
    for (int i = 0; i < sz(pts); i++) {
        Point cur = pts[i];

        // Pop collinear points
        while(sz(ans) >= 2) {
            Point prev = ans[sz(ans) - 1];
            Point two_prev = ans[sz(ans) - 2];
            if ((prev - two_prev).cross(cur - prev) == 0) {
                ans.pop_back();
                continue;
            }
            break;
        }
        // Add current point to stack
        ans.push_back(cur);
    }

    // Pop the extra point added initally
    ans.pop_back();
    return ans;
}

int main() {
    int n; cin >> n;
    vector<vector<Point>> polygons;
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        vector<Point> polygon;
        for (int j = 0; j < m; j++) {
            ll x, y;
            cin >> x >> y;
            polygon.push_back(Point(x, y));
        }
        polygons.push_back(polygon);
    }
    vector<Point> sm = minkowski(polygons);
    // for (auto &pt: sm) {
    //     cout << pt.x << " " << pt.y << endl;
    // }
    sm = remove_collinear(sm);
    int N = sm.size();

    // Find the min point
    int idx = 0;
    for (int i = 1; i < N; i++) {
        if (sm[i] < sm[idx]) idx = i;
    }
    
    // Output size of answer
    cout << N << endl;

    // Output points starting with min point
    for (int _ = 0; _ < N; _++) {
        cout << sm[idx].x << " " << sm[idx].y << endl;
        idx = (idx + 1) % N;
    }
    return 0;
}
