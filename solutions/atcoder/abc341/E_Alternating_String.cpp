/*

Alternating String

https://atcoder.jp/contests/abc341/tasks/abc341_e

segment tree (lazy propagation)

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
    struct D {
        int v = 0;
        D() {}
        D(int v) : v(v) {}
        void reset() {
            v = 0;
        }
        // combine
        D operator+=(const D &x) {
            v ^= x.v;
            return *this;
        }
        // return true if nothing to propagate
        bool operator!() {
            return !v;
        }
    };

    struct T {
        int l = -1, r = -1;
        bool isGood = true;
        // combine
        T operator+(const T &that) const {
            T res;
            res.l = l == -1 ? that.l : l;
            res.r = that.r == -1 ? r : that.r;
            res.isGood = isGood && that.isGood && r != that.l;
            return res;
        }
        // combine with lazy
        T operator+=(const D &d) {
            l ^= d.v;
            r ^= d.v;
            return *this;
        }
        // the final useful piece of info we're interested in
        // make sure the return type matches the actual type of the returned value
        bool res() {
            return isGood;
        }
    };

    int n, h;
    vector<T> t;
    vector<D> d;
    vi ln;

    ST(int n) {
        this->n = n;
        this->h = 31 - countl_zero(unsigned(n));
        t.resize(n << 1);
        ln.resize(n << 1);
        d.resize(n);
        for (int i = 0; i < n; ++i) ln[i + n] = 1;
        for (int i = n - 1; i; --i) ln[i] = ln[i << 1] + ln[i << 1 | 1];
    }
    ST(string &s) : ST(s.length()) {
        for (int i = 0; i < n; ++i) {
            t[i + n] = {s[i] - '0', s[i] - '0', true};
        }
        for (int i = n - 1; i; --i) calc(i);
    }
    void update(int l, int r, D x) {
        l += n, r += n + 1;
        int l0 = l, r0 = r;
        push(l, r);
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, x);
            if (r & 1) apply(--r, x);
        }
        pull(l0, r0);
    }
    T query(int l, int r) {
        l += n, r += n + 1;
        push(l, r);
        T resl, resr;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + t[l++];
            if (r & 1) resr = t[--r] + resr;
        }
        return resl + resr;
    }

   private:
    void calc(int i) {
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void apply(int i, D x) {
        t[i] += x;
        if (i < n) d[i] += x;
    }
    void push(int i) {
        if (!d[i]) return;
        apply(i << 1, d[i]);
        apply(i << 1 | 1, d[i]);
        d[i].reset();
    }
    void push(int l, int r) {
        for (int i = h; i; --i) {
            if (l >> i << i != l) push(l >> i);
            if (r >> i << i != r) push(r >> i);
        }
    }
    void pull(int l, int r) {
        for (int i = 1; i <= h; ++i) {
            if (l >> i << i != l) calc(l >> i);
            if (r >> i << i != r) calc(r >> i);
        }
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    ST st(s);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        --l, --r;
        if (t == 1) {
            st.update(l, r, 1);
        } else {
            cout << (st.query(l, r).res() ? "Yes" : "No") << endl;
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