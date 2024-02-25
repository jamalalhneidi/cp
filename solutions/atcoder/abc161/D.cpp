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

int d[20];
ll dp[20][11];

ll f(int i, int last, bool lower) {
    if (i < 0) return last == -1 ? 0 : 1;
    if (lower && dp[i][last + 1] != -1) return dp[i][last + 1];
    int from;
    int to;
    if (lower) {
        if (last == -1) {
            from = 0;
            to = 9;
        } else {
            from = max(0, last - 1);
            to = min(9, last + 1);
        }
    } else {
        if (last == -1) {
            from = 0;
            to = d[i];
        } else {
            from = max(0, last - 1);
            to = min(d[i], last + 1);
        }
    }
    ll res = 0;
    for (int j = from; j <= to; ++j) {
        res += f(i - 1, last == -1 && !j ? -1 : j, lower || j != d[i]);
    }
    if (lower) dp[i][last + 1] = res;
    return res;
}

ll f(ll x) {
    int i = -1;
    while (x) {
        d[++i] = x % 10;
        x /= 10;
    }
    return f(i, -1, false);
}

void solve() {
    memset(dp, -1, sizeof(dp));
    int n;
    cin >> n;
    ll l = 0, r = LLINF;
    while (r - l > 1) {
        ll m = mid(l, r);
        if (f(m) >= n)
            r = m;
        else
            l = m;
    }
    cout << r;
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

4611686018427387903

 */