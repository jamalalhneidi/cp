/*

Kefa and Watch

https://codeforces.com/contest/580/problem/E

segment tree (lazy propagation - range assignment)
hashing

*2500


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

const int P = 31;
const int MOD = 1e9 + 9;

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

vll p, inv, prefp;

void pre() {
    if (p.size()) return;
    int n = 1e5 + 1;
    p.resize(n);
    inv.resize(n);
    prefp.resize(n);
    p[0] = prefp[0] = 1;
    for (int i = 1; i < n; ++i) {
        p[i] = p[i - 1] * P % MOD;
        inv[i] = binpow(p[i], MOD - 2);
        prefp[i] = (prefp[i - 1] + p[i]) % MOD;
    }
}

struct ST {
    int n;
    vll t;
    vi d;

    ST(int n, string &s) {
        this->n = n;
        t.resize(n << 2);
        d.resize(n << 2, -1);
        build(1, 0, n - 1, s);
    }

    void build(int i, int l, int r, string &s) {
        if (l == r) {
            t[i] = (s[l] - '0' + 1) * p[l] % MOD;
            return;
        }
        int m = mid(l, r);
        build(i << 1, l, m, s);
        build(i << 1 | 1, m + 1, r, s);
        t[i] = (t[i << 1] + t[i << 1 | 1]) % MOD;
    }

    void set(int i, int l, int r, int x) {
        t[i] = (x + 1) * ((prefp[r] - (l - 1 >= 0 ? prefp[l - 1] : 0) + MOD) % MOD) % MOD;
    }

    void push(int i, int l, int r) {
        if (d[i] == -1) return;
        int m = mid(l, r);
        set(i << 1, l, m, d[i]);
        set(i << 1 | 1, m + 1, r, d[i]);
        d[i << 1] = d[i << 1 | 1] = d[i];
        d[i] = -1;
    }

    void update(int ql, int qr, int x, int i, int l, int r) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            set(i, l, r, x);
            d[i] = x;
            return;
        }
        push(i, l, r);
        int m = mid(l, r);
        update(ql, qr, x, i << 1, l, m);
        update(ql, qr, x, i << 1 | 1, m + 1, r);
        t[i] = (t[i << 1] + t[i << 1 | 1]) % MOD;
    }

    ll query(int l, int r) {
        if (!l) return query(l, r, 1, 0, n - 1);
        ll hr = query(0, r, 1, 0, n - 1);
        ll hl = query(0, l - 1, 1, 0, n - 1);
        ll res = (hr - hl + MOD) % MOD;
        res = res * inv[l] % MOD;
        return res;
    }

    ll query(int ql, int qr, int i, int l, int r) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return t[i];
        push(i, l, r);
        int m = mid(l, r);
        return (query(ql, qr, i << 1, l, m) + query(ql, qr, i << 1 | 1, m + 1, r)) % MOD;
    }
};

void solve() {
    pre();
    int n, m, k;
    cin >> n >> m >> k;
    int q = m + k;
    string s;
    cin >> s;
    ST st(n, s);
    while (q--) {
        int t, l, r, x;
        cin >> t >> l >> r >> x;
        --l, --r;
        if (t == 1) {
            st.update(l, r, x, 1, 0, n - 1);
        } else {
            ll h1 = st.query(l, r - x);
            ll h2 = st.query(l + x, r);
            cout << yn(h1 == h2) << endl;
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