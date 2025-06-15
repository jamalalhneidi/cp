/*

Ruler (hard version)

https://codeforces.com/contest/1999/problem/G2

ternary search (left half-open interval)

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
    auto ask = [&](int a, int b) {
        cout << "? " << a << spc << b << endl
             << flush;
        int x;
        cin >> x;
        if (x == -1) exit(0);
        return x;
    };
    auto ans = [&](int x) {
        cout << "! " << x << endl
             << flush;
    };
    int l = 1, r = 1000;
    while (r - l > 1) {
        int m1 = (2 * l + r) / 3;
        int m2 = (l + 2 * r) / 3;
        int x = ask(m1, m2);
        if (x == m1 * m2) {
            l = m2;
        } else if (x == (m1 + 1) * (m2 + 1)) {
            r = m1;
        } else {
            l = m1, r = m2;
        }
    }
    ans(r);
}

#define MULTI

int main() {
    fast;
    int t = 1;
#ifdef MULTI
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i) {
        solve();
    }
}
/*



 */