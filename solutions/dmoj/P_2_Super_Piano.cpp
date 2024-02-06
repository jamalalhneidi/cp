/*

NOI '10 P2 - Super Piano

https://dmoj.ca/problem/noi10p2

persistent segment tree

Notes:
Heavy optimization required
DO NOT GIVE STRUCT FIELDS DEFAULT VALUES WHEN ALLOCATING HUGE ARRAY OF STRUCT OBJECTS
a huge preallocated array of objects + object fields have default values = compilation time skyrocket

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

template <class T>
bool chmin(T &a, T b) {
    return a > b ? a = b, true : false;
}

const int MAX = 5e5 + 5;
struct N {
    int l, r, mn, at;
} nodes[22 * MAX];
int roots[MAX];
int idx = 0;

int create(int mn, int at) {
    nodes[idx].mn = mn;
    nodes[idx].at = at;
    nodes[idx].l = nodes[idx].r = at;
    return idx++;
}
int merge(int l, int r) {
    nodes[idx].l = l;
    nodes[idx].r = r;
    nodes[idx].mn = INF;
    nodes[idx].at = -1;
    if (l != -1 && chmin(nodes[idx].mn, nodes[l].mn))
        nodes[idx].at = nodes[l].at;
    if (r != -1 && chmin(nodes[idx].mn, nodes[r].mn))
        nodes[idx].at = nodes[r].at;
    return idx++;
}

struct PST {
    int n;
    PST(int n, int a[]) {
        this->n = n;
        roots[0] = build(0, n - 1, a);
        for (int i = 0; i < n; ++i) {
            roots[i + 1] = roots[0];
        }
    }
    int build(int l, int r, int a[]) {
        if (l == r) return create(a[l], l);
        int m = mid(l, r);
        return merge(build(l, m, a), build(m + 1, r, a));
    }
    void update(int i, int at, int x) {
        roots[i + 1] = update(roots[i + 1], at, x, 0, n - 1);
    }
    int update(int i, int at, int x, int l, int r) {
        if (l == r) return create(x, at);
        int m = mid(l, r);
        if (at <= m) return merge(update(nodes[i].l, at, x, l, m), nodes[i].r);
        return merge(nodes[i].l, update(nodes[i].r, at, x, m + 1, r));
    }
    int query(int i, int l, int r) {
        return (query(roots[i + 1], l, r, 0, n - 1)).S;
    }
    pii query(int i, int ql, int qr, int l, int r) {
        if (l > qr || r < ql) return {INF, -1};
        if (l >= ql && r <= qr) return {nodes[i].mn, nodes[i].at};
        int m = mid(l, r);
        auto resl = query(nodes[i].l, ql, qr, l, m);
        auto resr = query(nodes[i].r, ql, qr, m + 1, r);
        if (resl.F < resr.F) return resl;
        return resr;
    }
};

void solve() {
    int n, k, L, R;
    cin >> n >> k >> L >> R;
    int a[n + 1]{0};
    for (int i = 0; i < n; ++i) {
        cin >> a[i + 1];
        a[i + 1] += a[i];
    }
    PST pst(n + 1, a);
    ll ans = 0;
    priority_queue<tuple<int, int, int>> pq;
    for (int i = 0; i <= n; ++i) {
        if (i - L < 0) continue;
        int at = pst.query(i, max(0, i - R), i - L);
        if (at != -1) pq.emplace(a[i] - a[at], at, i);
    }
    for (int _ = 0; _ < k; ++_) {
        auto [x, at, i] = pq.top();
        pq.pop();
        ans += x;
        pst.update(i, at, INF);
        at = pst.query(i, max(0, i - R), i - L);
        if (at != -1) pq.emplace(a[i] - a[at], at, i);
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


 */