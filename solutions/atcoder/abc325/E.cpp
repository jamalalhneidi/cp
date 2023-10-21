/*
https://atcoder.jp/contests/abc325/tasks/abc325_e

dijkstra
shortest paths


 */

#include "bits/stdc++.h"

#ifdef LOCAL

#include "templates/dbg.cpp"

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

void solve() {
    int n, A, B, C;
    cin >> n >> A >> B >> C;
    vvll c(n, vll(n)), t(n, vll(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ll x;
            cin >> x;
            c[i][j] = x * A;
            t[i][j] = x * B + C;
        }
    }
    vvll dist(n, vll(2, LLINF));
    dist[0][0] = dist[0][1] = 0;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    const int car = 0, train = 1;
    pq.push({0, 0, car});
    while (!pq.empty()) {
        auto [d, u, byCar] = pq.top();
        pq.pop();
        if (d != dist[u][byCar]) continue;
        for (int v = 0; v < n; ++v) {
            if (byCar == car) {
                if (dist[v][car] > d + c[u][v]) {
                    dist[v][car] = d + c[u][v];
                    pq.push({dist[v][car], v, car});
                }
            }
            if (dist[v][train] > d + t[u][v]) {
                dist[v][train] = d + t[u][v];
                pq.push({dist[v][train], v, train});
            }
        }
    }
    cout << min(dist[n - 1][0], dist[n - 1][1]);
}

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