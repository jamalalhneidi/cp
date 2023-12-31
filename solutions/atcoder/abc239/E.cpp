/*

Subtree K-th Max

https://atcoder.jp/contests/abc239/tasks/abc239_e

graphs
trees

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

void solve() {
    int n, q;
    cin >> n >> q;
    vi a(n);
    cin(a);
    vvi adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vvi ans(n);
    function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v : adj[u]) {
            if (v != p) dfs(v, u);
        }
        vi idx(adj[u].size() + 1);
        while (ans[u].size() < 20) {
            int mx = -1, j = -1;
            for (int i = 0; i < adj[u].size() + 1; ++i) {
                if (i == adj[u].size()) {
                    if (!idx[i] && a[u] > mx) {
                        mx = a[u];
                        j = i;
                    }
                    continue;
                }
                int v = adj[u][i];
                if (idx[i] == ans[v].size()) continue;
                if (ans[v][idx[i]] > mx) {
                    mx = ans[v][idx[i]];
                    j = i;
                }
            }
            if (mx == -1) break;
            ans[u].pb(mx);
            idx[j]++;
        }
    };
    dfs(0, -1);
    while (q--) {
        int u, k;
        cin >> u >> k;
        --u, --k;
        cout << ans[u][k] << endl;
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