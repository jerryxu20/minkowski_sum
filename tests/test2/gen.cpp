#include "../bookcode/template.h"
#include "../bookcode/ConvexHull.h"

const int MX = 1e3;

long long rand(long long a, long long b) {
    return a + rand() % (b - a + 1);
}

vector<Point<ll>> generate_points(int n) {
    assert(n >= 0);
    vector<Point<ll>> ans;
    while(n--) {
        ll x = rand(-MX, MX);
        ll y = rand(-MX, MX);
        ans.push_back(Point<ll>(x, y));
    }
    return ans;
} 

int main(int argc, char* argv[]) {
    // seed the generator
    srand(atoi(argv[1]));

    int n = rand(2, 100);
    cout << n << endl;
    while(n--) {
        // Generate a convex polygon with at least 3 points
        vector<Point<ll>> hull;
        do {
            int cnt = rand(3, 10000);
            hull = convexHull(generate_points(cnt));
        } while(sz(hull) <= 2);

        cout << hull.size() << endl;
        for (auto &pt: hull) {
            cout << pt.x << " " << pt.y << endl;
        }
    }
    return 0;
}