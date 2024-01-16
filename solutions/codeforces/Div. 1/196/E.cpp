/*

Optimize!

https://codeforces.com/contest/338/problem/E

segment tree (lazy propagation)

*2600


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
    int n;
    vll t, d;

    ST(int n, vi &a) {
        this->n = n;
        t.resize(n << 2);
        d.resize(n << 2);
        build(1, 0, n - 1, a);
    }

    void build(int i, int l, int r, vi &a) {
        if (l == r) {
            t[i] = a[l];
            return;
        }
        int m = mid(l, r);
        build(i << 1, l, m, a);
        build(i << 1 | 1, m + 1, r, a);
        t[i] = min(t[i << 1], t[i << 1 | 1]);
    }

    void push(int i) {
        if (!d[i]) return;
        t[i << 1] += d[i];
        t[i << 1 | 1] += d[i];
        d[i << 1] += d[i];
        d[i << 1 | 1] += d[i];
        d[i] = 0;
    }

    void update(int ql, int qr, int x, int i, int l, int r) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            t[i] += x;
            d[i] += x;
            return;
        }
        push(i);
        int m = mid(l, r);
        update(ql, qr, x, i << 1, l, m);
        update(ql, qr, x, i << 1 | 1, m + 1, r);
        t[i] = min(t[i << 1], t[i << 1 | 1]);
    }

    ll query(int ql, int qr, int i, int l, int r) {
        if (l > qr || r < ql) return LLINF;
        if (l >= ql && r <= qr) return t[i];
        push(i);
        int m = mid(l, r);
        return min(query(ql, qr, i << 1, l, m), query(ql, qr, i << 1 | 1, m + 1, r));
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vi a(n), b(m);
    cin(b);
    cin(a);
    sort(all(b));
    vi c(m + 1);
    iota(all(c), 0);
    reverse(all(c));
    ST st(m + 1, c);
    auto f = [&](int x) {
        return upper_bound(all(b), x, [&](int x, int v) {
                   return v + x >= k;
               }) -
               b.begin();
    };
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = f(a[i]);
        st.update(0, j, -1, 1, 0, m);
        if (i >= m - 1) {
            ans += st.query(0, m, 1, 0, m) >= 0;
            j = f(a[i - m + 1]);
            st.update(0, j, 1, 1, 0, m);
        }
    }
    cout << ans;
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