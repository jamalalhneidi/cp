/*

Army Creation

https://codeforces.com/problemset/problem/813/E

persistent segment tree

notes:
kinda finding the number of distinct values in range,
but instead of keeping the last position of each value active,
we keep the last k positions active

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

const int _MAX = 2e5 + 1;
int idx = 0;
struct N {
    int l, r, s;
} nodes[22 * _MAX];
int roots[_MAX];

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

int build(int l, int r) {
    if (l == r) return create(0);
    int m = mid(l, r);
    return merge(build(l, m), build(m + 1, r));
}
int update(int i, int l, int r, int at, int x) {
    if (l == r) return create(nodes[i].s + x);
    int m = mid(l, r);
    if (at <= m) return merge(update(nodes[i].l, l, m, at, x), nodes[i].r);
    return merge(nodes[i].l, update(nodes[i].r, m + 1, r, at, x));
}
int query(int i, int ql, int qr, int l, int r) {
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return nodes[i].s;
    int m = mid(l, r);
    return query(nodes[i].l, ql, qr, l, m) + query(nodes[i].r, ql, qr, m + 1, r);
}

void solve() {
    int n, k;
    cin >> n >> k;
    vi a(n);
    cin(a);
    vector p(_MAX, queue<int>());
    roots[0] = build(0, n - 1);
    for (int i = 0; i < n; ++i) {
        int rt = roots[i];
        if (p[a[i]].size() == k) {
            rt = update(rt, 0, n - 1, p[a[i]].front(), -1);
            p[a[i]].pop();
        }
        roots[i + 1] = update(rt, 0, n - 1, i, 1);
        p[a[i]].push(i);
    }
    int q;
    cin >> q;
    int ans = 0;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l = (l + ans) % n;
        r = (r + ans) % n;
        if (l > r) swap(l, r);
        ans = query(roots[r + 1], l, r, 0, n - 1);
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