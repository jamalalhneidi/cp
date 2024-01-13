/*

String Hashing

https://open.kattis.com/problems/hashing

hashing

very big base needed
m = 1e9+9 won't work (WA)

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

typedef __int128 lll;

lll p = 31, m = 984162944621615797;

lll binpow(lll a, lll b) {
    lll res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void solve() {
    string s;
    cin >> s;
    int n = s.length();
    int q;
    cin >> q;
    vector<lll> h(n + 1), pow(n), inv(n);
    pow[0] = inv[0] = 1;
    for (int i = 1; i < n; ++i) {
        pow[i] = pow[i - 1] * p % m;
        inv[i] = binpow(pow[i], m - 2);
    }
    for (int i = 0; i < n; ++i) {
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * pow[i]) % m;
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        --r;
        lll lh = h[l];
        lll rh = h[r + 1];
        lll res = ((rh - lh + m) % m) * inv[l] % m;
        string ans;
        while (res) {
            ans += res % 10 + '0';
            res /= 10;
        }
        reverse(all(ans));
        cout << ans << endl;
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