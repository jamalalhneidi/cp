/*

TTM - To the moon

https://www.spoj.com/problems/TTM/

persistent segment tree (lazy propagation)

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
int version = 0;
int n;
int roots[_MAX];
int a[_MAX];
int idxAtVersion[_MAX];

struct N {
    int l, r;
    ll s, d;
} nodes[22 * _MAX];
int create(ll s, ll d = 0) {
    nodes[idx].s = s;
    nodes[idx].d = d;
    return idx++;
}
int copy(int i) {
    nodes[idx] = nodes[i];
    return idx++;
}
int merge(int l, int r) {
    nodes[idx].s = 0;
    nodes[idx].d = 0;
    nodes[idx].l = l;
    nodes[idx].r = r;
    nodes[idx].s += nodes[l].s;
    nodes[idx].s += nodes[r].s;
    return idx++;
}

int build(int l, int r) {
    if (l == r) return create(a[l]);
    int m = mid(l, r);
    return merge(build(l, m), build(m + 1, r));
}
int push(int i, int l, int r) {
    ll d = nodes[i].d;
    if (!d) return i;
    int m = mid(l, r);
    i = copy(i);
    nodes[i].l = copy(nodes[i].l);
    nodes[i].r = copy(nodes[i].r);
    nodes[nodes[i].l].s += len(l, m) * d;
    nodes[nodes[i].l].d += d;
    nodes[nodes[i].r].s += len(m + 1, r) * d;
    nodes[nodes[i].r].d += d;
    nodes[i].d = 0;
    return i;
}
int update(int i, int ql, int qr, ll x, int l = 0, int r = n - 1) {
    if (l > qr || r < ql) return i;
    if (l >= ql && r <= qr) {
        int res = copy(i);
        nodes[res].s += len(l, r) * x;
        nodes[res].d += x;
        return res;
    }
    i = push(i, l, r);
    int m = mid(l, r);
    return merge(update(nodes[i].l, ql, qr, x, l, m),
                 update(nodes[i].r, ql, qr, x, m + 1, r));
}
ll query(int i, int ql, int qr, int l = 0, int r = n - 1) {
    if (l > qr || r < ql) return 0ll;
    if (l >= ql && r <= qr) return nodes[i].s;
    i = push(i, l, r);
    int m = mid(l, r);
    return query(nodes[i].l, ql, qr, l, m) +
           query(nodes[i].r, ql, qr, m + 1, r);
}
void solve() {
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    roots[version] = build(0, n - 1);
    while (q--) {
        char c;
        cin >> c;
        if (c == 'Q') {
            int l, r;
            cin >> l >> r;
            --l, --r;
            cout << query(roots[version], l, r) << endl;
        } else if (c == 'H') {
            int l, r, t;
            cin >> l >> r >> t;
            --l, --r;
            cout << query(roots[t], l, r) << endl;
        } else if (c == 'B') {
            int t;
            cin >> t;
            version = t;
            idx = idxAtVersion[version];
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            --l, --r;
            idxAtVersion[version] = idx;
            roots[version + 1] = update(roots[version], l, r, x);
            ++version;
        }
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