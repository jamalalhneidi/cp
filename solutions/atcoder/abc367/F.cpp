/*

Rearrange Query

https://atcoder.jp/contests/abc367/tasks/abc367_f

Hashing

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

const int HASH_CNT = 2;
static_assert(HASH_CNT <= 2);
typedef __int128 lll;
typedef array<lll, HASH_CNT> H;
const lll P[2] = {53, 59};
const lll M[2] = {984162944621615729, 984162944621615797};

array<vector<lll>, 2> p{vector<lll>(1, 1), vector<lll>(1, 1)};

void pre(int n) {
    while (p[0].size() < n + 1) {
        p[0].pb(p[0].back() * P[0] % M[0]);
        p[1].pb(p[1].back() * P[1] % M[1]);
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    vi a(n), b(n);
    cin(a);
    cin(b);
    pre(n);
    vector<H> ha(n + 1), hb(n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < HASH_CNT; ++j) {
            ha[i + 1][j] = (ha[i][j] + a[i] * p[j][a[i]]) % M[j];
            hb[i + 1][j] = (hb[i][j] + b[i] * p[j][b[i]]) % M[j];
        }
    }
    auto f = [&](vector<H> &h, int l, int r) {
        H res;
        for (int i = 0; i < HASH_CNT; ++i) {
            res[i] = (h[r][i] - h[l - 1][i] + M[i]) % M[i];
        }
        return res;
    };
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if (f(ha, l1, r1) == f(hb, l2, r2))
            cout
                << "Yes";
        else
            cout << "No";
        cout << endl;
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