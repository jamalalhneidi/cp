/*

Vova Escapes the Matrix

https://codeforces.com/contest/1898/problem/F

brute force
bfs
multisource bfs
divide and conquer
shortest paths

*2600

first 2600 to solve


 */

#include "bits/stdc++.h"

#ifdef LOCAL

#include "templates/others/dbg.cpp"

#else
#define dbg(...)
#define dbgln(...)
#endif

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef queue<int> qi;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool>> vvb;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vector<pll>> vvpll;
typedef vector<char> vc;
typedef vector<vector<char>> vvc;
typedef vector<string> vs;
typedef set<int> si;
typedef set<ll> sll;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
#define fast ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define endl '\n'
#define all(a) a.begin(), a.end()
#define yes "YES"
#define no "NO"
#define spc ' '
#define INF INT_MAX
#define LLINF LONG_LONG_MAX
#define NINF INT_MIN
#define LLNINF LONG_LONG_MIN
#define pb push_back
#define pf push_front
#define eb emplace_back
#define F first
#define S second
#define cin(a) \
    for (auto &_x : (a)) cin >> _x
#define cin2(a)          \
    for (auto &_x : (a)) \
        for (auto &__x : _x) cin >> __x
#define cout(a) \
    for (auto &_x : (a)) cout << _x << spc
#define len(l, r) ((r) - (l) + 1)
#define mid(l, r) ((l) + ((r) - (l)) / 2)
#define ceil(a, b) (!(a) ? 0 : ((a)-1) / (b) + 1)
#define yn(b) ((b) ? yes : no)
#define between(x, l, r) ((x) >= (l) && (x) <= (r))
#define between2(i, j, n, m) (between(i, 0, n - 1) && between(j, 0, m - 1))

struct N {
    int id, d;
};

void solve() {
    int n, m;
    cin >> n >> m;
    vvc a(n, vc(m));
    cin2(a);
    int open = 0;
    int x, y;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            open += a[i][j] == '.';
            if (a[i][j] == 'V') x = i, y = j;
        }
    }
    vpii dir = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
    };
    auto isEdge = [&](int i, int j) {
        return !i || i == n - 1 || !j || j == m - 1;
    };
    auto getId = [&](int i, int j) {
        return i * m + j;
    };
    auto multisourceBFS = [&]() {
        queue<array<int, 4>> q;  // {i,j,id,d}
        vector dist(n, vector(m, vector<N>()));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] != '#' && isEdge(i, j)) {
                    q.push({i, j, getId(i, j), 0});
                    dist[i][j].pb({getId(i, j), 0});
                }
            }
        }
        while (!q.empty()) {
            auto [i, j, id, d] = q.front();
            q.pop();
            for (auto [di, dj] : dir) {
                int ii = i + di, jj = j + dj;
                if (between2(ii, jj, n, m) && a[ii][jj] != '#' && dist[ii][jj].size() < 2) {
                    bool skip = false;
                    for (auto [_id, _] : dist[ii][jj]) {
                        skip |= id == _id;
                    }
                    if (skip) continue;
                    dist[ii][jj].pb({id, d + 1});
                    q.push({ii, jj, id, d + 1});
                }
            }
        }
        return dist;
    };
    auto dist = multisourceBFS();
    if (dist[x][y].empty()) {
        cout << open;
        return;
    }
    if (dist[x][y].size() == 1) {
        cout << open - dist[x][y].front().d;
        return;
    }
    auto bfs = [&]() {
        int ans = 0;
        queue<array<int, 3>> q;
        vvb visited(n, vb(m));
        q.push({x, y, 0});
        visited[x][y] = true;
        while (!q.empty()) {
            auto [i, j, d] = q.front();
            q.pop();
            if (dist[i][j].size() == 2) {
                int totalD = d + dist[i][j][0].d + dist[i][j][1].d;
                ans = max(ans, open - totalD);
            }
            for (auto [di, dj] : dir) {
                int ii = i + di, jj = j + dj;
                if (between2(ii, jj, n, m) && a[ii][jj] == '.' && !visited[ii][jj]) {
                    visited[ii][jj] = true;
                    q.push({ii, jj, d + 1});
                }
            }
        }
        return ans;
    };
    cout << bfs();
}

#define MULTI

int main() {
    fast;
    int t = 1;
#ifdef MULTI
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i) {
        solve();
        i != t &&cout << endl;
    }
}
/*



 */