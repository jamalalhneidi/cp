/*

Persistent Bookcase

https://codeforces.com/contest/707/problem/D

persistent segment tree (lazy propagation, 2D to 1D)

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

int ni = 0;
const int _MAX = 1e6 + 1;
struct N {
    int l, r, s, k;
    bool d;
} nodes[22 * _MAX];
int create(int s, int k) {
    nodes[ni].s = s;
    nodes[ni].k = k;
    nodes[ni].d = false;
    return ni++;
}
int merge(int l, int r, int k) {
    nodes[ni].l = l;
    nodes[ni].r = r;
    nodes[ni].s = 0;
    nodes[ni].k = k;
    nodes[ni].d = false;
    nodes[ni].s += nodes[l].s;
    nodes[ni].s += nodes[r].s;
    return ni++;
}
int copy(int i) {
    nodes[ni] = nodes[i];
    return ni++;
}
struct PST {
    int n;
    int version = 0;
    vi roots;
    PST(int n) {
        this->n = n;
        roots.pb(build(0, n - 1));
    }
    int build(int l, int r) {
        if (l == r) return create(0, 1);
        int m = mid(l, r);
        return merge(build(l, m), build(m + 1, r), len(l, r));
    }
    int push(int i) {
        if (!nodes[i].d) return i;
        i = copy(i);
        nodes[i].l = copy(nodes[i].l);
        nodes[i].r = copy(nodes[i].r);
        nodes[nodes[i].l].s = nodes[nodes[i].l].k - nodes[nodes[i].l].s;
        nodes[nodes[i].l].d ^= 1;
        nodes[nodes[i].r].s = nodes[nodes[i].r].k - nodes[nodes[i].r].s;
        nodes[nodes[i].r].d ^= 1;
        nodes[i].d = false;
        return i;
    }
    void update(int at, int x) {
        roots.pb(update(roots[version], at, x, 0, n - 1));
        ++version;
    }
    int update(int i, int at, int x, int l, int r) {
        if (l == r) return create(x, 1);
        i = push(i);
        int m = mid(l, r);
        if (at <= m) return merge(update(nodes[i].l, at, x, l, m), nodes[i].r, len(l, r));
        return merge(nodes[i].l, update(nodes[i].r, at, x, m + 1, r), len(l, r));
    }
    void invert(int l, int r) {
        roots.pb(invert(roots[version], l, r, 0, n - 1));
        ++version;
    }
    int invert(int i, int ql, int qr, int l, int r) {
        if (l > qr || r < ql) return i;
        if (l >= ql && r <= qr) {
            int nw = copy(i);
            nodes[nw].s = nodes[i].k - nodes[i].s;
            nodes[nw].d ^= 1;
            return nw;
        }
        i = push(i);
        int m = mid(l, r);
        return merge(invert(nodes[i].l, ql, qr, l, m),
                     invert(nodes[i].r, ql, qr, m + 1, r), len(l, r));
    }
    int query() {
        return query(roots[version], 0, n - 1, 0, n - 1);
    }
    int query(int i, int ql, int qr, int l, int r) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return nodes[i].s;
        i = push(i);
        int m = mid(l, r);
        return query(nodes[i].l, ql, qr, l, m) + query(nodes[i].r, ql, qr, m + 1, r);
    }
    void setVersion(int v) {
        roots.pb(roots[v]);
        ++version;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    PST pst(n * m);
    vi ans = {0};
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            pst.update(x * m + y, 1);
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            pst.update(x * m + y, 0);
        } else if (t == 3) {
            int x;
            cin >> x;
            --x;
            pst.invert(x * m, (x + 1) * m - 1);
        } else {
            int k;
            cin >> k;
            pst.setVersion(k);
        }
        cout << pst.query() << endl;
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