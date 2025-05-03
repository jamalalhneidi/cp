/*

Payment Required

https://atcoder.jp/contests/abc402/tasks/abc402_e

Bitmask DP
Expected value

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

typedef long double ld;

void solve() {
    int n, k;
    cin >> n >> k;
    vi s(n), c = s;
    vector<ld> p(n), q = p;
    for (int i = 0; i < n; ++i) {
        cin >> s[i] >> c[i] >> p[i];
        p[i] /= 100;
        q[i] = 1 - p[i];
    }
    vector<vector<ld>> dp(1 << n, vector<ld>(k + 1, -1));
    function<ld(int, int)> f = [&](int mask, int k) {
        if (k < 0) return ld(-1);
        if (dp[mask][k] != -1) return dp[mask][k];
        ld res = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i & 1) || c[i] > k) continue;
            res = max(res, p[i] * (f(mask | (1 << i), k - c[i]) + s[i]) +
                               q[i] * f(mask, k - c[i]));
        }
        return dp[mask][k] = res;
    };
    cout << fixed << setprecision(10) << f(0, k);
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

E(i,x) = expected value of score where we're at problem #i and have x yen left
         (need to permute the list of problems to determine the correct order)
two cases:
            1. we solve it correctly increase the score and move on to the next one
            2. we don't. two cases:
                                    1. we try again 2. move on

E(i,x) =    p[i]*(E(i+1,x-c[i]) + s[i]) +
            q[i]*(E(i,x-c[i]) + E(i+1,x-c[i]))

time complexity: n! * n * X (too expensive)

maybe we can do 2^n * X?

 */