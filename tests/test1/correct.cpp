#include "../bookcode/MinkowskiCpAlgorithms.h"
#include "../bookcode/template.h"

int main() {
    // Read in the first polygon
    int n; cin >> n;
    vector<pt> A;
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        A.push_back(pt(x, y));
    }

    // Read in the second polygon
    int m; cin >> m;
    vector<pt> B;
    for (int i = 0; i < m; i++) {
        ll x, y; cin >> x >> y;
        B.push_back(pt(x, y));
    }

    // Compute their minkowski sum
    vector<pt> sm = minkowski(A, B);
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
