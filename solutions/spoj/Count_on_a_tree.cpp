/*

COT - Count on a tree

https://www.spoj.com/problems/COT/

persistent segment tree
LCA (binary lifting)


a very beautiful problem

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

const int _MAX = 1e5 + 1;
int idx = 0;
struct N {
    int l, r, s;
} nodes[22 * _MAX];
int roots[_MAX];
int n;

int create(int s) {
    nodes[idx].s = s;
    return idx++;
}
int merge(int l, int r) {
    nodes[idx].l = l;
    nodes[idx].r = r;
    if (l != -1) nodes[idx].s += nodes[l].s;
    if (r != -1) nodes[idx].s += nodes[r].s;
    return idx++;
}
N get(int i) {
    return nodes[i];
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
int query(int u, int v, int z, int k, int vz, int l, int r) {
    if (l == r) return l;
    int m = mid(l, r);
    int cnt = get(get(u).l).s + get(get(v).l).s - 2 * get(get(z).l).s;
    cnt += between(vz, l, m);
    if (cnt >= k) return query(nodes[u].l, nodes[v].l, nodes[z].l, k, vz, l, m);
    return query(nodes[u].r, nodes[v].r, nodes[z].r, k - cnt, vz, m + 1, r);
}

const int lg = 20;
int tin[_MAX], tout[_MAX];
int up[_MAX][lg + 1];

bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (isAncestor(u, v)) return u;
    if (isAncestor(v, u)) return v;
    for (int i = lg; i >= 0 && u != -1; --i) {
        if (up[u][i] != -1 && !isAncestor(up[u][i], v))
            u = up[u][i];
    }
    if (u == -1) return u;
    return up[u][0];
}

void solve() {
    int q;
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
    mii m, rm;
    for (auto x : a) m[x];
    int id = 0;
    for (auto &[k, v] : m) v = id++, rm[v] = k;
    for (auto &x : a) x = m[x];
    memset(up, -1, sizeof(up));
    int time = 0;
    roots[0] = build(0, id - 1);
    function<void(int, int)> dfs = [&](int u, int p) {
        tin[u] = time++;
        up[u][0] = p;
        for (int i = 1; i < lg + 1; ++i) {
            if (up[u][i - 1] == -1) break;
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        roots[u + 1] = update(roots[p + 1], 0, id - 1, a[u]);
        for (auto v : adj[u]) {
            if (v != p) dfs(v, u);
        }
        tout[u] = time++;
    };
    dfs(0, -1);
    while (q--) {
        int u, v, k;
        cin >> u >> v >> k;
        --u, --v;
        int z = lca(u, v);
        int res = query(roots[u + 1], roots[v + 1], roots[z + 1], k, a[z], 0, id - 1);
        cout << rm[res] << endl;
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

6, 0, 5, 1, 4, 2, 3, 3
105 2 9 3 8 5 7 7

u => 6 0
v => 6 5 4
z =>

 */