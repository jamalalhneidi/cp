/*

Valera and Queries

https://codeforces.com/contest/369/problem/E

BIT

*2200


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

struct BIT {
    int n;
    vi t;

    BIT(int n) {
        this->n = n + 1;
        t.resize(n + 1);
    }

    void add(int i) {
        for (++i; i < n; i += i & -i) ++t[i];
    }

    int sum(int i) {
        int res = 0;
        for (++i; i; i -= i & -i) res += t[i];
        return res;
    }
};

struct N {
    int l, r, i, f;

    bool operator<(const N &that) const {
        if (l == that.l) return f < that.f;
        return l > that.l;
    }
};

void solve() {
    int MAX = 1e6;
    int n, q;
    cin >> n >> q;
    vector<N> a;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        a.pb({l, r, i, 0});
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        int prv = 0;
        for (int j = 0; j < k; ++j) {
            int x;
            cin >> x;
            if (prv + 1 <= x - 1)
                a.pb({prv + 1, x - 1, i, 1});
            prv = x;
        }
        if (prv + 1 <= MAX)
            a.pb({prv + 1, MAX, i, 1});
    }
    sort(all(a));
    vi ans(q, n);
    BIT bit(MAX + 1);
    for (auto [l, r, i, f] : a) {
        if (!f)
            bit.add(r);
        else
            ans[i] -= bit.sum(r);
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