/*

Kth Number

https://www.hackerrank.com/contests/morgan-stanley-2015/challenges/wet-shark-and-kth-largest-number/problem

persistent segment tree


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

const int _MAX = 1e5 + 1;
int idx = 0;
struct N {
    int l, r, s;
} nodes[22 * _MAX];
int create(int s) {
    nodes[idx].s = s;
    return idx++;
}
int merge(int l, int r) {
    nodes[idx].l = l;
    nodes[idx].r = r;
    nodes[idx].s = 0;
    if (l != -1) nodes[idx].s += nodes[l].s;
    if (r != -1) nodes[idx].s += nodes[r].s;
    return idx++;
}
struct PST {
    int n;
    int *roots;
    PST(int n, vi &a) {
        this->n = n;
        int mx = *max_element(all(a));
        vvi p(mx + 1);
        for (int i = 0; i < n; ++i) {
            p[a[i]].pb(i);
        }
        roots = new int[mx + 2];
        roots[mx + 1] = build(0, n - 1);
        for (int i = mx; i >= 0; --i) {
            roots[i] = roots[i + 1];
            for (auto j : p[i]) {
                roots[i] = update(roots[i], 0, n - 1, j);
            }
        }
    }
    int build(int l, int r) {
        if (l == r) return create(0);
        int m = mid(l, r);
        return merge(build(l, m), build(m + 1, r));
    }
    int update(int n, int l, int r, int at) {
        if (l == r) return create(nodes[n].s + 1);
        int m = mid(l, r);
        if (at <= m) return merge(update(nodes[n].l, l, m, at), nodes[n].r);
        return merge(nodes[n].l, update(nodes[n].r, m + 1, r, at));
    }
    int query(int x, int k) {
        return query(roots[x], k, 0, n - 1);
    }
    int query(int n, int k, int l, int r) {
        if (l == r) return l;
        int m = mid(l, r);
        int cnt = nodes[nodes[n].l].s;
        if (cnt >= k) return query(nodes[n].l, k, l, m);
        return query(nodes[n].r, k - cnt, m + 1, r);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vi a(n);
    cin(a);
    PST pst(n, a);
    while (q--) {
        int x, k;
        cin >> x >> k;
        cout << a[pst.query(x, k)] << endl;
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