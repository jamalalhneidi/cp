/*

DQUERY - D-query

https://www.spoj.com/problems/DQUERY/

fenwick tree (offline)

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

template <class T = int>
struct FT {
    int n;
    vector<T> t;

    FT(int n) {
        this->n = n + 1;
        t.resize(n + 1);
    }

    FT(vector<T> &a) : FT(a.size()) {
        for (int i = 1; i <= a.size(); ++i) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j < n + 1) t[j] += t[i];
        }
    }

    void add(int i, T x) {
        for (++i; i < n; i += i & -i) t[i] += x;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    int sum(int i) {
        T res = 0;
        for (++i; i; i -= i & -i) res += t[i];
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin(a);
    int q;
    cin >> q;
    vector<vpii> qr(n);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        qr[r].pb({l, i});
    }
    int MAX = *max_element(all(a)) + 1;
    vi last(MAX, -1);
    FT<int> ft(n);
    vi ans(q);
    for (int i = 0; i < n; ++i) {
        if (last[a[i]] != -1) ft.add(last[a[i]], -1);
        last[a[i]] = i;
        ft.add(i, 1);
        for (auto [l, j] : qr[i]) {
            ans[j] = ft.sum(l, i);
        }
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