/*

Duff in the Army

https://codeforces.com/contest/588/problem/E

persistent segment tree
LCA (binary lifting)
graphs

*2200

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

const int _MAX = 1e5 + 1;
int idx = 0;
struct N {
    int l, r, s;
} nodes[22 * _MAX];
int create(int s) {
    nodes[idx].s = s;
    return idx++;
}
int merge(int l, int r) {
    nodes[idx].l = l;
    nodes[idx].r = r;
    nodes[idx].s = 0;
    if (l != -1) nodes[idx].s += nodes[l].s;
    if (r != -1) nodes[idx].s += nodes[r].s;
    return idx++;
}
struct PST {
    int *roots;
    PST(int n, int m) {
        roots = new int[n];
        roots[0] = build(0, m - 1);
    }
    int build(int l, int r) {
        if (l == r) return create(0);
        int m = mid(l, r);
        return merge(build(l, m), build(m + 1, r));
    }
    int update(int n, int l, int r, int at) {
        if (l == r) return create(nodes[n].s + 1);
        int m = mid(l, r);
        if (at <= m) return merge(update(nodes[n].l, l, m, at), nodes[n].r);
        return merge(nodes[n].l, update(nodes[n].r, m + 1, r, at));
    }
    int query(int u, int v, int anc, int panc, int l, int r, int k) {
        if (l == r) return l;
        int cnt = nodes[nodes[u].l].s + nodes[nodes[v].l].s - nodes[nodes[anc].l].s - nodes[nodes[panc].l].s;
        int m = mid(l, r);
        if (cnt >= k)
            return query(nodes[u].l, nodes[v].l, nodes[anc].l, nodes[panc].l, l, m, k);
        return query(nodes[u].r, nodes[v].r, nodes[anc].r, nodes[panc].r, m + 1, r, k - cnt);
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vvi adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vvi at(n + 1);
    for (int i = 0; i < m; ++i) {
        int u;
        cin >> u;
        at[u].pb(i);
    }
    const int lg = 20;
    vvi up(n + 1, vi(lg));
    vi d(n + 1);
    PST pst(n + 1, m);
    function<void(int, int)> dfs = [&](int u, int p) {
        d[u] = d[p] + 1;
        up[u][0] = p;
        for (int i = 0; i + 1 < lg; ++i) {
            up[u][i + 1] = up[up[u][i]][i];
        }
        pst.roots[u] = pst.roots[p];
        for (auto i : at[u]) {
            pst.roots[u] = pst.update(pst.roots[u], 0, m - 1, i);
        }
        for (auto v : adj[u]) {
            if (v != p) dfs(v, u);
        }
    };
    dfs(1, 0);
    function<int(int, int)> lca = [&](int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        int diff = d[u] - d[v];
        for (int i = 0; i < lg; ++i) {
            if (diff >> i & 1) u = up[u][i];
        }
        if (u == v) return u;
        for (int i = lg - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i])
                u = up[u][i], v = up[v][i];
        }
        return up[u][0];
    };
    while (q--) {
        int u, v, k;
        cin >> u >> v >> k;
        int anc = lca(u, v);
        int panc = up[anc][0];
        k = min(k, nodes[pst.roots[u]].s + nodes[pst.roots[v]].s - nodes[pst.roots[anc]].s - nodes[pst.roots[panc]].s);
        cout << k << spc;
        for (int i = 0; i < k; ++i) {
            int res = pst.query(pst.roots[u], pst.roots[v], pst.roots[anc], pst.roots[panc], 0, m - 1, i + 1);
            cout << res + 1 << spc;
        }
        cout << endl;
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