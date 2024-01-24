/*

REQ

https://codeforces.com/contest/594/problem/D

segment tree

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

const int MOD = 1e9 + 7;

typedef ModInt<MOD> mint;
typedef vector<mint> vmi;
typedef vector<vmi> vvmi;

vi primes;

void pre() {
    if (primes.size()) return;
    int n = 1e3 + 1;
    vb is(n, true);
    is[0] = is[1] = false;
    for (int i = 2; i < n; ++i) {
        if (!is[i]) continue;
        primes.pb(i);
        for (ll j = (ll)i * i; j < n; j += i) {
            is[j] = false;
        }
    }
}

struct ST {
    int n;
    vmi t;

    ST(int n, vi &a) {
        this->n = n;
        t.resize(n << 1);
        for (int i = 0; i < n; ++i) {
            t[i + n] = a[i];
        }
        for (int i = n - 1; i; --i) {
            t[i] = t[i << 1] * t[i << 1 | 1];
        }
    }

    void update(int i, mint x) {
        i += n;
        t[i] *= x;
        for (i >>= 1; i; i >>= 1) t[i] = t[i << 1] * t[i << 1 | 1];
    }

    mint query(int l, int r) {
        mint res = 1;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res *= t[l++];
            if (r & 1) res *= t[--r];
        }
        return res;
    }
};

void solve() {
    pre();
    int n;
    cin >> n;
    vi a(n);
    cin(a);
    int q;
    cin >> q;
    vector<array<int, 3>> queries(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        queries[i] = {l - 1, r - 1, i};
    }
    sort(all(queries));
    ST st(n, a);
    vvi d(n);
    map<int, qi> pos;
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        for (auto p : primes) {
            if (p > x) break;
            if (x % p == 0) d[i].pb(p), pos[p].push(i);
            while (x % p == 0) x /= p;
        }
        if (x > 1) d[i].pb(x), pos[x].push(i);
    }
    for (auto &[k, que] : pos) {
        if (que.empty()) continue;
        st.update(que.front(), mint(k - 1) / k);
    }
    vmi ans(q);
    int at = 0;
    for (auto [l, r, i] : queries) {
        while (at < l) {
            for (auto p : d[at]) {
                if (pos[p].size() && pos[p].front() == at) {
                    pos[p].pop();
                    if (pos[p].empty()) continue;
                    st.update(pos[p].front(), mint(p - 1) / p);
                }
            }
            ++at;
        }
        ans[i] = st.query(l, r);
    }
    for (auto x : ans) cout << x << endl;
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