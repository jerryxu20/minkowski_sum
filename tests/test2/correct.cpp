#include "../bookcode/MinkowskiCpAlgorithms.h"
#include "../bookcode/template.h"

int main() {
    int n; cin >> n;

    // a set with just (0, 0) is the identity for Minkowski sums
    // so we can safely start with it 
    vector<pt> sm = {pt(0, 0)};

    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        vector<pt> polygon;
        for (int j = 0; j < m; j++) {
            ll x, y;
            cin >> x >> y;
            polygon.push_back(pt(x, y));
        }

        // compute the new Minkowski sum
        sm = minkowski(sm, polygon);
    }
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
