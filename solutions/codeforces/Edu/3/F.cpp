/*

Frogs and mosquitoes

https://codeforces.com/contest/609/problem/F

segment tree
binary search

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

struct ST {
    struct N {
        int i;
        ll mx = LLNINF;
        N operator+(N &that) {
            if (mx >= that.mx) return {i, mx};
            return {that.i, that.mx};
        }
    };

    int n;
    vector<N> t;

    ST(int n) {
        this->n = n;
        t.resize(n << 1);
        for (int i = 0; i < n; ++i) {
            t[i + n].i = i;
        }
    }

    void update(int i, int x) {
        i += n;
        t[i].mx = x;
        for (i >>= 1; i; i >>= 1) t[i] = t[i << 1] + t[i << 1 | 1];
    }

    N query(int l, int r) {
        N resl, resr;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + t[l++];
            if (r & 1) resr = t[--r] + resr;
        }
        return resl + resr;
    }
};

struct Frog {
    int x;
    ll y;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<Frog> a(n);
    mii m, mr;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
        a[i].y += a[i].x;
        m[a[i].x];
    }
    vpll b(q);
    for (int i = 0; i < q; ++i) {
        cin >> b[i].F >> b[i].S;
        m[b[i].F];
    }
    int id = 0;
    for (auto &[k, v] : m) v = id++, mr[v] = k;
    ST st(id);
    mii p;
    for (int i = 0; i < n; ++i) {
        auto &frog = a[i];
        frog.x = m[frog.x];
        p[frog.x] = i;
        st.update(frog.x, frog.y);
    }
    vpll ans(n);
    map<ll, pll> mos;
    for (auto [x, sz] : b) {
        int l = 0, r = m[x];
        int frogx = -1;
        while (l <= r) {
            int m = mid(l, r);
            auto res = st.query(0, m);
            if (res.mx >= x) {
                frogx = res.i;
                r = m - 1;
            } else
                l = m + 1;
        }
        if (frogx == -1) {
            auto &[cnt, ssz] = mos[x];
            ++cnt;
            ssz += sz;
            continue;
        }
        int i = p[frogx];
        auto &frog = a[i];
        int rx = mr[frog.x];
        int oldy = frog.y;
        frog.y += sz;
        ans[i].F++;
        while (mos.size()) {
            auto it = mos.lower_bound(rx);
            if (it == mos.end() || it->F > frog.y) break;
            auto [cnt, ssz] = it->S;
            oldy = frog.y;
            ans[i].F += cnt;
            frog.y += ssz;
            mos.erase(it);
        }
        st.update(frog.x, frog.y);
    }
    for (int i = 0; i < n; ++i) {
        ans[i].S = a[i].y - mr[a[i].x];
    }
    for (auto [cnt, l] : ans) cout << cnt << spc << l << endl;
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