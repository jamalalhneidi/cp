/*

Permute K times

https://atcoder.jp/contests/abc367/tasks/abc367_e

binary lifting

// Important notes below

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

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vi to(n), a(n);
    cin(to), --_x;
    cin(a);
    int m = 2;
    while ((1ll << m) <= k) ++m;
    vvi up(m, vi(n));
    for (int i = 0; i < n; ++i) {
        up[0][i] = to[i];
    }
    // swapping loops order is wrong
    // not all ancestors of the ancestors of a vertex are defined
    // therefore should process them in order, aka. first layer, second layer, and so on...
    for (int j = 0; j < m - 1; ++j) {
        for (int i = 0; i < n; ++i) {
            up[j + 1][i] = up[j][up[j][i]];
        }
    }
    ll cnt = 0;
    vi b(n);
    iota(all(b), 0);
    // swapping loops order produces the corrcet answer
    // HOWEVER it's ~17 times slower in practice (79 ms -> 1341 ms)
    // even tho ther're identical in terms of complexity
    // cuz that way for every vertex we're looping through all levels
    // but this way we only loop through vertices of the levels we're interested in
    for (int j = 0; j < m; ++j) {
        if (k >> j & 1) {
            for (int i = 0; i < n; ++i) {
                ++cnt;
                b[i] = up[j][b[i]];
            }
        }
    }
    for (auto i : b) cout << a[i] << spc;
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
