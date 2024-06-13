/*

Transit Tree Path

https://atcoder.jp/contests/abc070/tasks/abc070_d

graphs (trees)
LCA (binary lifting)

 */

#include "bits/stdc++.h"

#ifdef COTATO

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
#define ceil(a, b) (!(a) ? 0 : ((a) - 1) / (b) + 1)
#define yn(b) ((b) ? yes : no)
#define between(x, l, r) ((x) >= (l) && (x) <= (r))
#define between2(i, j, n, m) (between(i, 0, n - 1) && between(j, 0, m - 1))

void solve() {
    int n;
    cin >> n;
    vector<vpii> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    int q, k;
    cin >> q >> k;
    int m = 20;
    vector up(n + 1, vpll(m));
    vi d(n + 1);
    function<void(int, int)> dfs = [&](int u, int p) {
        for (int i = 0; i + 1 < m; ++i) {
            auto [v, w] = up[u][i];
            up[u][i + 1] = {up[v][i].F, up[v][i].S + w};
        }
        for (auto [v, w] : adj[u]) {
            if (v == p) continue;
            up[v][0] = {u, w};
            d[v] = d[u] + 1;
            dfs(v, u);
        }
    };
    dfs(1, 0);
    auto f = [&](int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        int diff = d[u] - d[v];
        ll w = 0;
        for (int i = 0; i < m; ++i) {
            if (diff >> i & 1) {
                w += up[u][i].S;
                u = up[u][i].F;
            }
        }
        if (u == v) return w;
        for (int i = m - 1; i >= 0; --i) {
            if (up[u][i].F != up[v][i].F) {
                w += up[u][i].S + up[v][i].S;
                u = up[u][i].F;
                v = up[v][i].F;
            }
        }
        return w + up[u][0].S + up[v][0].S;
    };
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << min(f(u, k) + f(k, v), f(v, k) + f(k, u)) << endl;
    }
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