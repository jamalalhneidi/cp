/*

Linear Kingdom Races

https://codeforces.com/contest/115/problem/E

DP
segment tree (lazy propagation)

*2400

ref:
https://blog.csdn.net/DERITt/article/details/50267747

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
    int l, r, p;
    bool operator<(N &that) {
        if (r == that.r) return l < that.l;
        return r < that.r;
    }
};

struct ST {
    int n, h;
    vll t, d;

    ST(int n) {
        this->n = n;
        h = 32 - countl_zero(unsigned(n));
        t.resize(2 * n);
        d.resize(n);
    }

    void apply(int i, ll x) {
        t[i] += x;
        if (i < n) d[i] += x;
    }

    void push(int p) {
        for (int j = h; j; --j) {
            int i = p >> j;
            if (d[i]) {
                apply(i << 1, d[i]);
                apply(i << 1 | 1, d[i]);
                d[i] = 0;
            }
        }
    }

    void build(int i) {
        for (i >>= 1; i; i >>= 1)
            t[i] = max(t[i << 1], t[i << 1 | 1]) + d[i];
    }

    void update(int l, int r, ll x) {
        l += n, r += n + 1;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, x);
            if (r & 1) apply(--r, x);
        }
        build(l0);
        build(r0 - 1);
    }

    ll query(int l, int r) {
        l += n, r += n + 1;
        push(l);
        push(r - 1);
        ll res = LLNINF;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vi c(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> c[i + 1];
    }
    vector<N> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i].l >> a[i].r >> a[i].p;
    }
    sort(all(a));
    ST st(n + 1);
    vll dp(n + 1);
    for (int i = 1, j = 0; i <= n; ++i) {
        st.update(0, i - 1, -c[i]);
        while (j < m && a[j].r <= i) {
            st.update(0, a[j].l - 1, a[j].p);
            ++j;
        }
        dp[i] = max(dp[i - 1], st.query(0, i - 1));
        st.update(i, i, dp[i]);
    }
    cout << dp[n];
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