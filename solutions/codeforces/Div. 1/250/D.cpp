/*

The Child and Sequence

https://codeforces.com/contest/438/problem/D

segment tree (recursive update required.. probably)

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

struct N {
    int l, r;
    ll s, mx;
};

struct ST {
    int n;
    vector<N> t;

    ST(int n, vi &a) {
        this->n = n;
        t.resize(2 * n);
        for (int i = 0; i < n; ++i) {
            t[i + n] = {i, i, a[i], a[i]};
        }
        for (int i = n - 1; i; --i) {
            t[i] = {t[i << 1].l, t[i << 1 | 1].r};
            calc(i);
        }
    }

    void calc(int i) {
        t[i].s = t[i << 1].s + t[i << 1 | 1].s;
        t[i].mx = max(t[i << 1].mx, t[i << 1 | 1].mx);
    }

    void update(int l, int r, int x, int i = 1) {
        if (t[i].l > t[i].r) {
            update(l, r, x, i << 1);
            update(l, r, x, i << 1 | 1);
            return;
        }
        if (t[i].r < l || t[i].l > r || t[i].mx < x) return;
        if (i >= n) {
            t[i].s %= x;
            t[i].mx %= x;
            return;
        }
        update(l, r, x, i << 1);
        update(l, r, x, i << 1 | 1);
        calc(i);
    }

    void update(int i, int x) {
        i += n;
        t[i].s = t[i].mx = x;
        for (i >>= 1; i; i >>= 1) {
            calc(i);
        }
    }

    ll query(int l, int r) {
        ll res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++].s;
            if (r & 1) res += t[--r].s;
        }
        return res;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vi a(n);
    cin(a);
    ST st(n, a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            cout << st.query(l - 1, r - 1) << endl;
        } else if (t == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            st.update(l - 1, r - 1, x);
        } else {
            int i, x;
            cin >> i >> x;
            st.update(i - 1, x);
        }
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