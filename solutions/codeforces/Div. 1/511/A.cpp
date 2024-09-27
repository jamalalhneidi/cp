/*

Enlarge GCD

https://codeforces.com/contest/1034/problem/A

number theory
sieve of euler


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
#define ceil(a, b) (!(a) ? 0 : ((a) - 1) / (b) + 1)
#define yn(b) ((b) ? yes : no)
#define between(x, l, r) ((x) >= (l) && (x) <= (r))
#define between2(i, j, n, m) (between(i, 0, n - 1) && between(j, 0, m - 1))

const int MAX = 2e7;
int *d;
void pre() {
    d = new int[MAX]{0};
    vi primes;
    for (int i = 2; i < MAX; ++i) {
        if (!d[i]) d[i] = i, primes.pb(i);
        for (auto p : primes) {
            if (i * p >= MAX) break;
            d[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

void solve() {
    pre();
    int n;
    cin >> n;
    vi a(n);
    cin(a);
    int g = 0;
    for (auto x : a) g = gcd(g, x);
    for (auto &x : a) x /= g;
    if (count(all(a), 1) == n) {
        cout << -1;
        return;
    }
    mii m;
    int ans = INF;
    for (auto x : a) {
        int prv = 0;
        while (d[x]) {
            if (prv != d[x]) {
                ans = min(ans, n - ++m[d[x]]);
            }
            prv = d[x];
            x /= d[x];
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

6 9 15 30
2 3 3  2
3   5  3
       5

2 3 5 10

 */