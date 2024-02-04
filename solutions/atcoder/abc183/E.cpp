/*

Queen on Grid

https://atcoder.jp/contests/abc183/tasks/abc183_e

DP

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

void solve() {
    int n, m;
    cin >> n >> m;
    vvc a(n, vc(m));
    cin2(a);
    vvmi dp(n + 1, vmi(m + 1));
    vvmi r(n + 1, vmi(m + 1));
    vvmi c(n + 1, vmi(m + 1));
    vvmi d(n + 1, vmi(m + 1));
    dp[1][1] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '#') continue;
            dp[i + 1][j + 1] += r[i + 1][j];
            dp[i + 1][j + 1] += c[i][j + 1];
            dp[i + 1][j + 1] += d[i][j];
            r[i + 1][j + 1] = r[i + 1][j] + dp[i + 1][j + 1];
            c[i + 1][j + 1] = c[i][j + 1] + dp[i + 1][j + 1];
            d[i + 1][j + 1] = d[i][j] + dp[i + 1][j + 1];
        }
    }
    cout << dp[n][m];
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