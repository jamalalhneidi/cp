/*

Multiset

https://codeforces.com/problemset/problem/1354/D

fenwick tree

*1900

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

struct FT {
    int n;
    int *t;

    FT(int n) {
        this->n = n + 1;
        t = new int[n + 1]{0};
    }

    void add(int i, int x) {
        for (++i; i < n; i += i & -i) t[i] += x;
    }

    int kth(int k) {
        int l = 0, r = n;
        while (r - l > 1) {
            int m = mid(l, r);
            if (sum(m) >= k)
                r = m;
            else
                l = m;
        }
        return r;
    }

    int sum(int i) {
        int res = 0;
        for (++i; i; i -= i & -i) res += t[i];
        return res;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    FT ft(n + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ft.add(x, 1);
    }
    while (q--) {
        int x;
        cin >> x;
        if (x > 0)
            ft.add(x, 1);
        else
            ft.add(ft.kth(-x), -1);
    }
    int ans = ft.kth(1);
    if (ans == n + 2)
        cout
            << 0;
    else
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