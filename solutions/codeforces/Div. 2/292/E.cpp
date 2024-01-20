/*

Drazil and Park

https://codeforces.com/contest/515/problem/E

segment tree (circular into flat segments trick)

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

template <class T>
bool chmax(T &a, T b) {
    return a < b ? a = b, true : false;
}

struct ST {
    struct N {
        vpll mxl, mxr;

        N operator+(N &that) {
            N res;
            for (auto [v, i] : mxl) res.mxl.eb(v, i);
            for (auto [v, i] : mxr) res.mxr.eb(v, i);
            for (auto [v, i] : that.mxl) res.mxl.eb(v, i);
            for (auto [v, i] : that.mxr) res.mxr.eb(v, i);
            sort(all(res.mxl), greater());
            sort(all(res.mxr), greater());
            if (res.mxl.size() > 2) res.mxl.resize(2);
            if (res.mxr.size() > 2) res.mxr.resize(2);
            return res;
        }
    };

    int n;
    vector<N> t;
    ST(int n, vll &l, vll &r) {
        this->n = n;
        t.resize(n << 1);
        for (int i = 0; i < n; ++i) {
            t[i + n].mxl.eb(l[i], i);
            t[i + n].mxr.eb(r[i], i);
        }
        for (int i = n - 1; i; --i) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    ll query(int l, int r) {
        l += n, r += n + 1;
        int r0 = r;
        N res;
        while (l < r) {
            if (l & 1) res = res + t[l++];
            if (r & 1) res = t[--r] + res;
            l >>= 1, r >>= 1;
        }
        ll ret = LLNINF;
        for (auto [v1, i] : res.mxl) {
            for (auto [v2, j] : res.mxr) {
                if (i == j) continue;
                chmax(ret, v1 + v2);
            }
        }
        return ret;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vi d(2 * n), h(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
        d[i + n] = d[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
        h[i + n] = h[i];
    }
    vll l(2 * n), r(2 * n);
    ll s = 0;
    for (int i = 0; i < 2 * n; ++i) {
        l[i] = 2 * h[i] - s;
        r[i] = 2 * h[i] + s;
        s += d[i];
    }
    ST st(2 * n, l, r);
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        if (l <= r)
            cout << st.query(r + 1, l - 1 + n) << endl;
        else
            cout << st.query(r + 1, l - 1) << endl;
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

0 1 2 3 4 0 1 2 3 4

x < y:
d[x] + d[x+1] + .. + d[y-1] + 2h[x] +2h[y]
=  2h[y] +  d[0] + d[1] + .. + d[y-1]
+ (2h[x] - (d[0] + d[1] + .. + d[x-1]))

l[i] = 2h[i] - d[0..i-1]
r[i] = 2h[i] + d[0..i-1]


ans = max(l[i] + r[j]); l <= i < j <= r

 */