/*

DZY Loves Fibonacci Numbers

https://codeforces.com/contest/446/problem/C

segment tree (lazy propagation)

*2400

helpful refs:
https://blog.csdn.net/qq_43521140/article/details/107870316
https://codeforces.com/blog/entry/13036?#comment-177607

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

template <int MOD>
struct ModInt {
    int value;

    ModInt(long long v = 0) {
        value = v % MOD;
        if (value < 0) value += MOD;
    }

    ModInt &operator+=(ModInt const &b) {
        value += b.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    ModInt &operator-=(ModInt const &b) {
        value -= b.value;
        if (value < 0) value += MOD;
        return *this;
    }

    ModInt &operator*=(ModInt const &b) {
        value = (long long)value * b.value % MOD;
        return *this;
    }

    ModInt &operator/=(const ModInt &b) { return *this *= b.inv(); }

    friend ModInt operator+(ModInt a, ModInt const b) { return a += b; }

    friend ModInt operator-(ModInt a, ModInt const b) { return a -= b; }

    friend ModInt operator-(ModInt const a) { return 0 - a; }

    friend ModInt operator*(ModInt a, ModInt const b) { return a *= b; }

    friend ModInt operator/(ModInt a, ModInt const b) { return a /= b; }

    friend ostream &operator<<(std::ostream &os, ModInt const &a) { return os << a.value; }

    friend bool operator==(ModInt const &a, ModInt const &b) { return a.value == b.value; }

    friend bool operator!=(ModInt const &a, ModInt const &b) { return a.value != b.value; }

    ModInt &operator++() {
        *this += 1;
        return *this;
    }

    ModInt operator++(int) {
        ModInt old = *this;
        operator++();
        return old;
    }

    ModInt &operator--() {
        *this -= 1;
        return *this;
    }

    ModInt operator--(int) {
        ModInt old = *this;
        operator--();
        return old;
    }

    ModInt pow(long long e) const {
        if (e < 0) return inv().pow(-e);
        ModInt a = *this, res = 1;
        while (e) {
            if (e & 1) res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }

    ModInt inv() const { return pow(MOD - 2); }
};

const int MOD = 1e9 + 9;

typedef ModInt<MOD> mint;
typedef vector<mint> vmi;
typedef vector<vmi> vvmi;

vmi fib;

mint g(mint a, mint b, int i);
mint gs(mint a, mint b, int i);

struct LazyN {
    bool f = false;
    mint a, b, x;
    int k;
};

struct ST {
    int n, h;
    vmi t;
    vector<LazyN> d;

    ST(int n, vi &a) {
        this->n = n;
        h = 32 - countl_zero(unsigned(n));
        t.resize(2 * n);
        d.resize(n);
        for (int i = 0; i < n; ++i) {
            t[i + n] = a[i];
        }
        for (int i = n - 1; i; --i) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    void apply(int i, mint a, mint b, int k) {
        mint x = gs(a, b, k);
        t[i] += x;
        if (i < n) {
            d[i].f = true;
            d[i].a += a;
            d[i].b += b;
            d[i].x = gs(d[i].a, d[i].b, k);
            d[i].k = k;
        }
    }

    void push(int p) {
        for (int j = h; j; --j) {
            int i = p >> j;
            if (d[i].f) {
                int k = d[i].k >> 1;
                apply(i << 1, d[i].a, d[i].b, k);
                apply(i << 1 | 1, g(d[i].a, d[i].b, k + 1), g(d[i].a, d[i].b, k + 2), k);
                d[i].f = false;
                d[i].a = d[i].b = d[i].x = 0;
            }
        }
    }

    void build(int i) {
        for (i >>= 1; i; i >>= 1) {
            t[i] = t[i << 1] + t[i << 1 | 1] + d[i].x;
        }
    }

    void update(int l, int r) {
        int k = 1, fl = 1, fr = r - l + 1;
        l += n, r += n + 1;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) {
                mint a = g(1, 1, fl);
                mint b = g(1, 1, fl + 1);
                apply(l++, a, b, k);
                fl += k;
            }
            if (r & 1) {
                mint a = g(1, 1, fr - k + 1);
                mint b = g(1, 1, fr - k + 2);
                apply(--r, a, b, k);
                fr -= k;
            }
        }
        build(l0);
        build(r0 - 1);
    }

    mint query(int l, int r) {
        l += n, r += n + 1;
        push(l);
        push(r - 1);
        mint res = 0;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};

// get ith term of fib-like sequence
// starting with a, b
mint g(mint a, mint b, int i) {
    if (i == 1)
        return a;
    else if (i == 2)
        return b;
    return a * fib[i - 2] + b * fib[i - 1];
}

// get sum of first i terms of fib-like sequence
// starting with a, b
mint gs(mint a, mint b, int i) {
    if (i == 1)
        return a;
    else if (i == 2)
        return a + b;
    return g(a, b, i + 2) - g(a, b, 2);
}

void calcFib() {
    if (fib.size()) return;
    int n = 3e5 + 5;
    fib.resize(n);
    fib[1] = fib[2] = 1;
    for (int i = 3; i < n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

void solve() {
    calcFib();
    int n, q;
    cin >> n >> q;
    vi a(n);
    cin(a);
    ST st(n, a);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        --l, --r;
        if (t == 1)
            st.update(l, r);
        else
            cout << st.query(l, r) << endl;
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