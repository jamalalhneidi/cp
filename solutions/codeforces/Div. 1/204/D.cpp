/*

Jeff and Removing Periods

https://codeforces.com/contest/351/problem/D

segment tree

*2700


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
    struct V {
        int l = 0, d = 0, cnt = 0;
        bool isGood = false;

        V operator+(V &that) {
            V res;
            res.l = min(l, that.l);
            res.cnt = cnt + that.cnt;
            if (!isGood || !that.isGood) {
                res.isGood = false;
                return res;
            }
            if (l < that.l)
                res.d = that.l - (l + d * (cnt - 1));
            else
                res.d = l - (that.l + that.d * (that.cnt - 1));
            res.isGood = (cnt == 1 || res.d == d) && (that.cnt == 1 || res.d == that.d);
            if (!res.isGood) res.d = 0;
            return res;
        }
    };

    struct N {
        int good = 0;
        map<int, V> m;

        N operator+(N &that) {
            N res;
            res.good = good + that.good;
            map<int, V> *sm;
            if (m.size() < that.m.size()) {
                res.m = that.m;
                sm = &m;
            } else {
                res.m = m;
                sm = &that.m;
            }
            for (auto &[k, v] : *sm) {
                if (!res.m.count(k)) {
                    res.m[k] = v;
                    continue;
                }
                V &tmp = res.m[k];
                res.good -= tmp.isGood;
                res.good -= v.isGood;
                tmp = tmp + v;
                res.good += tmp.isGood;
            }
            return res;
        }
    };

    int n;
    vector<N> t;

    ST(int n, vi &a) {
        this->n = n;
        t.resize(n << 1);
        for (int i = 0; i < n; ++i) {
            t[i + n].good = 1;
            t[i + n].m[a[i]] = {i, 0, 1, true};
        }
        for (int i = n - 1; i; --i) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
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

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin(a);
    ST st(n, a);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        auto x = st.query(l, r);
        cout << int(x.m.size()) + !x.good << endl;
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

1 1 2 2 3 3 1 2 3

 */