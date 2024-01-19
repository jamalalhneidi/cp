/*

Happy Life in University

https://codeforces.com/contest/1916/problem/E

graphs
trees
segment tree (lazy propagation)
euler tour

*2300



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

struct ST {
    int n, h;
    vi t, d;

    ST(int n) {
        this->n = n;
        h = 32 - countl_zero((unsigned)n);
        t.resize(2 * n);
        d.resize(n);
    }

    void apply(int i, int x) {
        t[i] += x;
        if (i < n) d[i] += x;
    }

    void push(int p) {
        for (int i = h; i > 0; --i) {
            int j = p >> i;
            if (d[j]) {
                apply(j << 1, d[j]);
                apply(j << 1 | 1, d[j]);
                d[j] = 0;
            }
        }
    }

    void build(int i) {
        for (i >>= 1; i; i >>= 1) {
            t[i] = max(t[i << 1], t[i << 1 | 1]) + d[i];
        }
    }

    void update(int l, int r, int x) {
        l += n, r += n + 1;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, x);
            if (r & 1) apply(--r, x);
        }
        build(l0);
        build(r0 - 1);
    }

    int query(int l, int r) {
        l += n, r += n + 1;
        push(l);
        push(r - 1);
        int res = NINF;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vvi adj(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        adj[p - 1].pb(i);
    }
    vi a(n);
    cin(a), --_x;
    vi l(n), r(n);
    int time = 0;
    vvi down(n), up(n);
    // down[vertex] = {closest vertices in its children subtrees with the same color}
    // up[color].back() = closest parent with the same color
    function<void(int)> dfs1 = [&](int u) {
        l[u] = time++;
        up[a[u]].pb(u);
        for (auto v : adj[u]) {
            if (up[a[v]].size())
                down[up[a[v]].back()].pb(v);
            dfs1(v);
        }
        up[a[u]].pop_back();
        r[u] = time - 1;
    };
    dfs1(0);
    ST st(time);
    ll ans = 0;
    function<void(int)> dfs = [&](int u) {
        for (auto v : adj[u]) {
            dfs(v);
        }
        st.update(l[u], r[u], 1);
        for (auto v : down[u]) {
            st.update(l[v], r[v], -1);
        }
        int mx1 = 1, mx2 = 1;
        for (auto v : adj[u]) {
            int x = st.query(l[v], r[v]);
            if (x > mx1)
                mx2 = mx1, mx1 = x;
            else
                mx2 = max(mx2, x);
        }
        ans = max(ans, (ll)mx1 * mx2);
    };
    dfs(0);
    cout << ans;
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