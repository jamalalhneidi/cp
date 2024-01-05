/*

Make Bipartite

https://atcoder.jp/contests/abc229/tasks/abc229_f

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

void solve() {
    int n;
    cin >> n;
    vi a(n + 1), b(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i + 1];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i + 1];
    }
    vector dp(n + 1, vector(2, vll(2, 1e18)));
    // dp[first i vertices][vertex i color][vertex 1 color] = ans
    // assume vertex 0's color is 0
    dp[1][0][0] = a[1];
    dp[1][1][1] = 0;
    for (int i = 2; i <= n; ++i) {
        dp[i][0][0] = min(dp[i - 1][1][0], dp[i - 1][0][0] + b[i - 1]) + a[i];
        dp[i][1][0] = min(dp[i - 1][0][0], dp[i - 1][1][0] + b[i - 1]);
        dp[i][0][1] = min(dp[i - 1][1][1], dp[i - 1][0][1] + b[i - 1]) + a[i];
        dp[i][1][1] = min(dp[i - 1][0][1], dp[i - 1][1][1] + b[i - 1]);
    }
    ll ans = LLINF;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ans = min(ans, dp[n][i][j] + (i == j ? b[n] : 0));
        }
    }
    cout << ans;
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