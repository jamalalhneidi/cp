/*

Two Sequence Queries

https://atcoder.jp/contests/abc357/tasks/abc357_f

segment tree (lazy propagation)

 */

#include "bits/stdc++.h"

#ifdef COTATO

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
#define ceil(a, b) (!(a) ? 0 : ((a) - 1) / (b) + 1)
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

const int MOD = 998244353;

typedef ModInt<MOD> mint;
typedef vector<mint> vmi;
typedef vector<vmi> vvmi;

struct ST {
    struct D {
        mint a, b;
        D() {}
        D(mint a, mint b) : a(a), b(b) {}
        void reset() {
            a = b = 0;
        }
        // combine
        D operator+=(const D &x) {
            a += x.a;
            b += x.b;
            return *this;
        }
        // return true if nothing to propagate
        bool operator!() {
            return a == 0 && b == 0;
        }
    };

    struct T {
        mint a, b, ab;
        // combine
        T operator+(const T &that) const {
            return {a + that.a, b + that.b, ab + that.ab};
        }
        // combine with lazy
        void combineWithLazy(const D d, int ln) {
            ab += d.a * b + d.b * a + d.a * d.b * ln;
            a += d.a * ln;
            b += d.b * ln;
        }
        // the final useful piece of info we're interested in
        // make sure the return type matches the actual type of the returned value
        mint res() {
            return ab;
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
    ST(vi &a, vi &b) : ST(a.size()) {
        for (int i = 0; i < n; ++i) t[i + n] = T(a[i], b[i], mint(a[i]) * b[i]);
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
        t[i].combineWithLazy(x, ln[i]);
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
    vi a(n), b(n);
    cin(a);
    cin(b);
    ST st(a, b);
    while (q--) {
        int t, l, r, x;
        cin >> t >> l >> r;
        --l, --r;
        if (t == 3) {
            cout << st.query(l, r).res() << endl;
        } else {
            cin >> x;
            if (t == 1)
                st.update(l, r, {x, 0});
            else
                st.update(l, r, {0, x});
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

(a[i] + x)*b[i] + (a[i+1] + x)*b[i+1]
a[i]*b[i] + a[i+1]*b[i+1] + x*(b[i] + b[i+1])
T[i]                      + B[i]*x

(a[i] + x)*(b[i] + y) + (a[i+1] + x)*(b[i+1] + y)

T[i] + x*B[i] + y*A[i] + xy*ln

 */