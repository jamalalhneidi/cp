/*

Count Descendants

https://atcoder.jp/contests/abc202/tasks/abc202_e

segment tree
euler tour

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
    struct N {
        unordered_map<int, int> m;
        N operator+(N &that) {
            unordered_map<int, int> *sm, res;
            if (m.size() < that.m.size()) {
                res = that.m;
                sm = &m;
            } else {
                res = m;
                sm = &that.m;
            }
            for (auto [k, v] : *sm) res[k] += v;
            return {res};
        }
    };

    int n;
    vector<N> t;

    ST(int n, vi &a) {
        this->n = n;
        t.resize(n << 2);
        build(1, 0, n - 1, a);
    }

    void build(int i, int l, int r, vi &a) {
        if (l == r) {
            t[i].m[a[l]]++;
            return;
        }
        int m = mid(l, r);
        build(i << 1, l, m, a);
        build(i << 1 | 1, m + 1, r, a);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }

    int query(int ql, int qr, int x, int i, int l, int r) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) {
            if (t[i].m.count(x)) return t[i].m[x];
            return 0;
        }
        int m = mid(l, r);
        return query(ql, qr, x, i << 1, l, m) + query(ql, qr, x, i << 1 | 1, m + 1, r);
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
    vi l(n), r(n), dist(n);
    int time = 0;
    function<void(int, int)> dfs = [&](int u, int d) {
        l[u] = time++;
        dist[u] = d;
        for (auto v : adj[u]) {
            dfs(v, d + 1);
        }
        r[u] = time++;
    };
    dfs(0, 0);
    vi b(time);
    for (int i = 0; i < n; ++i) {
        b[l[i]] = b[r[i]] = dist[i];
    }
    ST st(time, b);
    int q;
    cin >> q;
    while (q--) {
        int u, d;
        cin >> u >> d;
        --u;
        int ans = st.query(l[u], r[u], d, 1, 0, time - 1);
        ans /= 2;
        cout << ans << endl;
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